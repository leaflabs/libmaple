/* Copyright (c) 2014, Nordic Semiconductor ASA
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 *
 * IMPORTANT: This example still is not compatible with CHIPKIT
 *
 * Click on the "Serial Monitor" button on the Arduino IDE to get reset the Arduino and start the application.
 * The setup() function is called first and is called only one for each reset of the Arduino.
 * The loop() function as the name implies is called in a loop.
 * The setup() and loop() function are called in this way.
 * main()
 *  {
 *   setup();
 *   while(1)
 *   {
 *     loop();
 *   }
 * }
 *
 * Use the PERSONAL HEALTH DEVICES TRANSCODING WHITE PAPER in bluetooth.org to understand the
 * format of the temperature measurement characteristic.
 * The format used is IEEE 11073-20601 FLOAT
 */
#include <SPI.h>
#include <avr/sleep.h>
#include <avr/power.h>

#include "services.h"
#include <lib_aci.h>

#include <aci_setup.h>
#include "health_thermometer.h"
#include "timer1.h"

#ifdef SERVICES_PIPE_TYPE_MAPPING_CONTENT
  static services_pipe_type_mapping_t
      services_pipe_type_mapping[NUMBER_OF_PIPES] = SERVICES_PIPE_TYPE_MAPPING_CONTENT;
#else
  #define NUMBER_OF_PIPES 0
  static services_pipe_type_mapping_t * services_pipe_type_mapping = NULL;
#endif

#define TEMPERATURE_NUM_SAMPLES  10

static hal_aci_data_t setup_msgs[NB_SETUP_MESSAGES] PROGMEM = SETUP_MESSAGES_CONTENT;
// aci_struct that will contain
// total initial credits
// current credit
// current state of the aci (setup/standby/active/sleep)
// open remote pipe pending
// close remote pipe pending
// Current pipe available bitmap
// Current pipe closed bitmap
// Current connection interval, slave latency and link supervision timeout
// Current State of the the GATT client (Service Discovery)
static struct aci_state_t aci_state;
static hal_aci_evt_t aci_data;

/**
Counter in seconds.
When this counter counts down to zero -> wakeup the nRF8001
*/
static int16_t sleep_to_wakeup_timeout;

/*
Variables used for the temperature measurement and transmission
*/
//static h_thermo_temp_measure_t h_temperature;
//static h_temp_type_t current_type;

static int32_t temperature = 0; // Needs to be an int32 to measure negative values
static float temperature_f;
static uint8_t temperature_count = TEMPERATURE_NUM_SAMPLES;
static int32_t temperature_total = 0;
static bool ack_temp_measure_pending = false; /* Initial value */

/*
Variables used for the timer on the AVR
*/
volatile uint8_t timer1_f = 0;

/* Define how assert should function in the BLE library */
void __ble_assert(const char *file, uint16_t line)
{
  Serial.print("ERROR ");
  Serial.print(file);
  Serial.print(": ");
  Serial.print(line);
  Serial.print("\n");
  while(1);
}

void aci_loop()
{
  static bool setup_required = false;

  // We enter the if statement only when there is a ACI event available to be processed
  if (lib_aci_event_get(&aci_state, &aci_data))
  {
    aci_evt_t * aci_evt;
    aci_evt = &aci_data.evt;

    switch(aci_evt->evt_opcode)
    {
      case ACI_EVT_DEVICE_STARTED:
      {
        aci_state.data_credit_available = aci_evt->params.device_started.credit_available;
        switch(aci_evt->params.device_started.device_mode)
        {
          case ACI_DEVICE_SETUP:
            /**
            When the device is in the setup mode
            */
            aci_state.device_state = ACI_DEVICE_SETUP;
            Serial.println(F("Evt Device Started: Setup"));
            setup_required = true;
            break;

          case ACI_DEVICE_STANDBY:
            aci_state.device_state = ACI_DEVICE_STANDBY;
            sleep_to_wakeup_timeout = 30;
            Serial.println(F("Evt Device Started: Standby"));
            if (aci_evt->params.device_started.hw_error)
            {
              delay(20); //Magic number used to make sure the HW error event is handled correctly.
            }
            else
            {
              lib_aci_connect(30/* in seconds */, 0x0100 /* advertising interval 100ms*/);
              Serial.println(F("Advertising started"));
            }
            break;
        }
      }
        break; //ACI Device Started Event

      case ACI_EVT_CMD_RSP:
        //If an ACI command response event comes with an error -> stop
        if (ACI_STATUS_SUCCESS != aci_evt->params.cmd_rsp.cmd_status )
        {
          //ACI ReadDynamicData and ACI WriteDynamicData will have status codes of
          //TRANSACTION_CONTINUE and TRANSACTION_COMPLETE
          //all other ACI commands will have status code of ACI_STATUS_SCUCCESS for a successful command

          Serial.print(F("ACI Status of ACI Evt Cmd Rsp 0x"));
          Serial.println(aci_evt->params.cmd_rsp.cmd_status, HEX);
          Serial.print(F("ACI Command 0x"));
          Serial.println(aci_evt->params.cmd_rsp.cmd_opcode, HEX);
          Serial.println(F("Evt Cmd respone: Error. Arduino is in an while(1); loop"));
          while (1);
        }
        else
        {
          switch (aci_evt->params.cmd_rsp.cmd_opcode)
          {
            case ACI_CMD_GET_TEMPERATURE:
              if (0 != temperature_count)
              {
                temperature_total  = temperature_total +
                                    (aci_evt->params.cmd_rsp.params.get_temperature.temperature_value);
                Serial.print(F("Sampling Temperature "));
                Serial.print(temperature_count);
                Serial.print(F(" "));
                Serial.println(aci_evt->params.cmd_rsp.params.get_temperature.temperature_value);
                temperature_count--;
              }
              if (0 == temperature_count)
              {
                Serial.println(temperature_total);
                temperature_count = TEMPERATURE_NUM_SAMPLES;
                /**
                Multiply by 100 for exp = -2 : divide by 4 -> See ACI GetTemperature in datasheet
                */
                temperature = temperature_total * (float)(25/(float)TEMPERATURE_NUM_SAMPLES);
                temperature_total = 0;
                temperature_f = (float)temperature/100.00;
                Serial.print(F("Temperature :"));
                Serial.print(temperature_f, 2);
                Serial.println(" C");
                if (lib_aci_is_pipe_available(&aci_state, PIPE_HEALTH_THERMOMETER_TEMPERATURE_MEASUREMENT_TX_ACK))
                {
                  Serial.println(F("Sending the temperature"));
                  temperature &= 0x00FFFFFF; //Mask the exponent part
                  temperature |= 0xFE000000; //Exponent is -2 since we multipled by 100
                  health_thermometer_send_measure(temperature);
                  //We cannot send a new temperature measurement Indiction until we get back an ACK for it.
                  ack_temp_measure_pending = true;
                }
              }
              break;
          }
        }
        break;

      case ACI_EVT_CONNECTED:
        /*
        The nRF8001 is now connected to the peer device.
        */
        Serial.println(F("Evt Connected"));
        ack_temp_measure_pending = false;
        break;

      case ACI_EVT_DATA_CREDIT:
        Serial.println(F("Evt Credit: Peer Radio acked our temperature measurement"));
        /**
        Bluetooth Radio ack received from the peer radio for the data packet sent.
        This also signals that the buffer used by the nRF8001 for the data packet is available again.
        Since the temperature measurement uses Indications we need to wait for the Confirmation from the peer
        GATT client for the data packet sent.
        The confirmation is the ack from the peer GATT client is sent as a ACI_EVT_DATA_ACK.
        */
        break;

      case ACI_EVT_DISCONNECTED:
        /**
        Advertise again if the advertising timed out.
        */
        if(ACI_STATUS_ERROR_ADVT_TIMEOUT == aci_evt->params.disconnected.aci_status)
        {
          Serial.println(F("Evt Disconnected -> Advertising timed out"));
          {
            Serial.println(F("nRF8001 going to sleep"));
            lib_aci_sleep();
            aci_state.device_state = ACI_DEVICE_SLEEP;
            Timer1start();
          }
        }
        else
        {
          Serial.println(F("Evt Disconnected -> Link lost."));
          lib_aci_connect(30/* in seconds */, 0x0050 /* advertising interval 50ms*/);
          Serial.println(F("Advertising started"));
          //Timer1.stop();
        }
        break;

      case ACI_EVT_PIPE_STATUS:
        {
          Serial.println(F("Evt Pipe Status"));
          /** check if the peer has subscribed to the Temperature Characteristic
          */
          if (lib_aci_is_pipe_available(&aci_state, PIPE_HEALTH_THERMOMETER_TEMPERATURE_MEASUREMENT_TX_ACK))
          {
            Timer1start();
          }

        }
        break;

      case ACI_EVT_PIPE_ERROR:
        //See the appendix in the nRF8001 Product Specication for details on the error codes
        Serial.print(F("ACI Evt Pipe Error: Pipe #:"));
        Serial.print(aci_evt->params.pipe_error.pipe_number, DEC);
        Serial.print(F("  Pipe Error Code: 0x"));
        Serial.println(aci_evt->params.pipe_error.error_code, HEX);

        //Increment the credit available as the data packet was not sent.
        //The pipe error also represents the Attribute protocol Error Response sent from the peer and that should not be counted
        //for the credit.
        if (ACI_STATUS_ERROR_PEER_ATT_ERROR != aci_evt->params.pipe_error.error_code)
        {
          aci_state.data_credit_available++;
        }
        break;


      case ACI_EVT_DATA_ACK:
        {
          Serial.println(F("Attribute protocol ACK for Temp. measurement Indication"));
          /*
          We can now send the next temperature measurement.
          */
          ack_temp_measure_pending = false;
        }
        break;

      case ACI_EVT_HW_ERROR:
        Serial.println(F("HW error: "));
        Serial.println(aci_evt->params.hw_error.line_num, DEC);

        for(uint8_t counter = 0; counter <= (aci_evt->len - 3); counter++)
        {
          Serial.write(aci_evt->params.hw_error.file_name[counter]); //uint8_t file_name[20];
        }
        Serial.println();
        lib_aci_connect(30/* in seconds */, 0x0100 /* advertising interval 100ms*/);
        Serial.println(F("Advertising started"));
        break;

      default:
        Serial.print(F("Evt Opcode 0x"));
        Serial.print(aci_evt->evt_opcode, HEX);
        Serial.println(F(" unhandled"));
        break;
    }
  }
  else
  {
    /**
    No event in the ACI Event queue and if there are no commands in the command queue
    Arduino can go to sleep
    */
  }
  
  /* setup_required is set to true when the device starts up and enters setup mode.
   * It indicates that do_aci_setup() should be called. The flag should be cleared if
   * do_aci_setup() returns ACI_STATUS_TRANSACTION_COMPLETE.
   */
  if(setup_required)
  {
    if (SETUP_SUCCESS == do_aci_setup(&aci_state))
    {
      setup_required = false;
    }
  }
}


void setup(void)
{
  Serial.begin(115200);
  //Wait until the serial port is available (useful only for the Leonardo)
  //As the Leonardo board is not reseted every time you open the Serial Monitor
  #if defined (__AVR_ATmega32U4__)
    while(!Serial)
    {}
    delay(5000);  //5 seconds delay for enabling to see the start up comments on the serial board
  #elif defined(__PIC32MX__)
    delay(1000);
  #endif

  Serial.println(F("Arduino setup"));

  /**
  Point ACI data structures to the the setup data that the nRFgo studio generated for the nRF8001
  */
  if (NULL != services_pipe_type_mapping)
  {
    aci_state.aci_setup_info.services_pipe_type_mapping = &services_pipe_type_mapping[0];
  }
  else
  {
    aci_state.aci_setup_info.services_pipe_type_mapping = NULL;
  }
  aci_state.aci_setup_info.number_of_pipes    = NUMBER_OF_PIPES;
  aci_state.aci_setup_info.setup_msgs         = setup_msgs;
  aci_state.aci_setup_info.num_setup_msgs     = NB_SETUP_MESSAGES;

  /*
  Tell the ACI library, the MCU to nRF8001 pin connections.
  The Active pin is optional and can be marked UNUSED
  */
  aci_state.aci_pins.board_name = BOARD_DEFAULT; //See board.h for details
  aci_state.aci_pins.reqn_pin   = 9;
  aci_state.aci_pins.rdyn_pin   = 8;
  aci_state.aci_pins.mosi_pin   = MOSI;
  aci_state.aci_pins.miso_pin   = MISO;
  aci_state.aci_pins.sck_pin    = SCK;

  aci_state.aci_pins.spi_clock_divider      = SPI_CLOCK_DIV8;//SPI_CLOCK_DIV8  = 2MHz SPI speed
                                                             //SPI_CLOCK_DIV16 = 1MHz SPI speed
  
  aci_state.aci_pins.reset_pin              = 4; //4 for Nordic board, UNUSED for REDBEARLAB_SHIELD_V1_1
  aci_state.aci_pins.active_pin             = UNUSED;
  aci_state.aci_pins.optional_chip_sel_pin  = UNUSED;

  aci_state.aci_pins.interface_is_interrupt = false; //Interrupts still not available in Chipkit
  aci_state.aci_pins.interrupt_number       = 1;

  /** We reset the nRF8001 here by toggling the RESET line connected to the nRF8001
   *  and initialize the data structures required to setup the nRF8001
   */
  //The second parameter is for turning debug printing on for the ACI Commands and Events so they be printed on the Serial
  lib_aci_init(&aci_state, false);

  /**
   * Initalize the data structures required for the GATT Health Thermometer Service
   */
  health_thermometer_init();
  health_thermometer_set_unit_c();
}

void loop()
{
  aci_loop();

  /**
  Temperature sampling application that samples the temperature every 4 seconds
  OR
  Wakes up the sleeping nRF8001 every 4 seconds
  */
  if (1 == timer1_f)
  {
    uint8_t i = 0;
    timer1_f  = 0;

    if((ACI_DEVICE_STANDBY == aci_state.device_state)
        && (lib_aci_is_pipe_available(&aci_state, PIPE_HEALTH_THERMOMETER_TEMPERATURE_MEASUREMENT_TX_ACK))
        && (false == ack_temp_measure_pending))
    {
      for(i=0; i<TEMPERATURE_NUM_SAMPLES; i++)
      {
        Serial.println(F("Get temperature from nRF8001 sensor"));
        lib_aci_get_temperature();
      }
    }

    if(ACI_DEVICE_SLEEP == aci_state.device_state)
    {
      /*
      */
      sleep_to_wakeup_timeout = sleep_to_wakeup_timeout - 4; // we are running the timer callback after 4 seconds
      if (0 > sleep_to_wakeup_timeout)
      {
        Timer1stop();
        sleep_to_wakeup_timeout = 30;
        lib_aci_wakeup();
        aci_state.device_state = ACI_DEVICE_INVALID;
      }
    }
  }
}


