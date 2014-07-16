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
 *IMPORTANT: This example still is not compatible with CHIPKIT
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
 */

#include <SPI.h>
#include "services.h"
#include <lib_aci.h>
#include <aci_setup.h>
#include "heart_rate.h"
#include "battery.h"
#include "lib_battery_level.h"
#include "hrm_definitions.h"
#include "EEPROM.h"


#ifdef SERVICES_PIPE_TYPE_MAPPING_CONTENT
    static services_pipe_type_mapping_t
        services_pipe_type_mapping[NUMBER_OF_PIPES] = SERVICES_PIPE_TYPE_MAPPING_CONTENT;
#else
    #define NUMBER_OF_PIPES 0
    static services_pipe_type_mapping_t * services_pipe_type_mapping = NULL;
#endif

#define BATT_MEASUREMENT_DELAY                   3      //Prescaler for the battery measurement frequency, offset to Timer event frequency TCCR1B
#define HEART_RATE_MEASUREMENT_DELAY             5      //Prescaler for the heart rate measurement frequency, offset to Timer event frequency TCCR1B

#define ENABLE_BATTERY_MEASUREMENT_PRINTOUT      1     //Set to 1 to enable, set to 0 to disable. Only valid with battery_level_data_source = MEASUREMENT
#define ENABLE_CREDIT_PRINTOUT                   0     //Set to 1 to enable, set to 0 to disable

/*
Store the nRF8001 setup information generated on the flash of the AVR.
This reduces the RAM requirements for the nRF8001.
*/
static hal_aci_data_t setup_msgs[NB_SETUP_MESSAGES] PROGMEM = SETUP_MESSAGES_CONTENT;

// an aci_struct that will contain
// total initial credits
// current credit
// current state of the aci (setup/standby/active/sleep)
// open remote pipe pending
// close remote pipe pending
// Current pipe available bitmap
// Current pipe closed bitmap
// Current connection interval, slave latency and link supervision timeout
// Current State of the the GATT client (Service Discovery)
static aci_state_t aci_state;

static hal_aci_evt_t aci_data;
static hal_aci_data_t aci_cmd;

static bool timing_change_done = false;

static uint8_t battery_measurement_delay_counter    = 0;    //Variable to control frequency of battery data handling
static uint8_t heart_rate_measurement_delay_counter = 0;    //Variable to control frequency of heart-rate data handling

static data_source_t battery_level_data_source = MEASUREMENT;  //Selects the data source for the battery data
static data_source_t heart_rate_data_source = SIMULATION;     //Selects the data source for the heart-rate data

static volatile uint8_t credit_printout_flag     = 0;      //flag to enable data credit printout only once after timer execution
static volatile uint8_t battery_measurement_flag = 0;      //flag to enable battery measurement printout only once after timer execution
static uint8_t battery_percent_level;                      //Battery measurement value
static uint8_t heart_rate                        = 0;      //Heart-rate measurement value


/*** FUNC
Name:           Timer1start
Function:       Start timer 1 to interrupt periodically. Call this from
                the Arduino setup() function.
Description:    The pre-scaler and the timer count divide the timer-counter
                clock frequency to give a timer overflow interrupt rate:

                Interrupt rate =  16MHz / (prescaler * (255 - TCNT2))

        TCCR2B[b2:0]   Prescaler    Freq [KHz], Period [usec] after prescale
          0x0            (TC stopped)     0         0
          0x1                1        16000.        0.0625
          0x2                8         2000.        0.500
          0x3               32          500.        2.000
          0x4               64          250.        4.000
          0x5              128          125.        8.000
          0x6              256           62.5      16.000
          0x7             1024           15.625    64.000
FUNC ***/

void Timer1start()
{
  // Setup Timer1 overflow to fire every 4000ms
  //   period [sec] = (1 / f_clock [sec]) * prescale * (count)
  //                  (1/16000000)  * 1024 * (count) = 4000 ms


  TCCR1B  = 0x00;        // Disable Timer1 while we set it up
  TCNT1H  = 11;          // Approx 4000ms when prescaler is set to 1024
  TCNT1L  = 0;
  TIFR1   = 0x00;        // Timer1 INT Flag Reg: Clear Timer Overflow Flag
  TIMSK1  = 0x01;        // Timer1 INT Reg: Timer1 Overflow Interrupt Enable
  TCCR1A  = 0x00;        // Timer1 Control Reg A: Wave Gen Mode normal
  TCCR1B  = 0x03;        // Timer1 Control Reg B: Timer prescaler.
}

void Timer1stop()
{
  TCCR1B = 0x00;
  TIMSK1 = 0x00;
}

/*** FUNC
Name:       Timer1 ISR
Function:   Handles the Timer1-overflow interrupt
FUNC ***/
ISR(TIMER1_OVF_vect)
{
  uint8_t return_value;

  //Get heart-rate data and send it over the BLE link
  if(heart_rate_measurement_delay_counter == HEART_RATE_MEASUREMENT_DELAY)
  {
    //Get heart-rate data
    if(heart_rate_data_source == SIMULATION)
    {
      heart_rate++;
      if (heart_rate == 200)
      {
        heart_rate = 0;
      }
    }
    else if(heart_rate_data_source == MEASUREMENT)
    {
      heart_rate = get_heart_rate_measurement();
    }

    //Send heart-rate data
    if(HEART_RATE_DATA_BUFF_SIZE == 0)
    {
      update_heart_rate(&aci_state, heart_rate);    //Send heart-rate data over the air
    }
    else
    {
      insert_data_into_heart_rate_buffer(heart_rate);   //Insert heart-rate data into send buffer to be sent over the BLE link via nRF8001
    }

    heart_rate_measurement_delay_counter = 0;
  }
  heart_rate_measurement_delay_counter++;

  //Get battery data and send it over the BLE link
  if(battery_measurement_delay_counter >= BATT_MEASUREMENT_DELAY)
  {
    //Get battery data
    if(battery_level_data_source == SIMULATION)
    {
      battery_percent_level = get_simulated_battery_value();    //Get simulated battery value
    }
    else if(battery_level_data_source == MEASUREMENT)
    {
      battery_percent_level = measure_battery(&aci_state);      //Sample actual battery voltage
    }

    //Send battery data
    if(BATTERY_DATA_BUFF_SIZE == 0)
    {
      update_battery(&aci_state, battery_percent_level);    //Send battery data over the air
    }
    else
    {
      insert_data_into_battery_buffer(battery_percent_level);   //Insert battery data into send buffer to be sent over the BLE link via nRF8001
    }

    battery_measurement_delay_counter = 0;
    battery_measurement_flag = 1;             //Enable battery measurement printout after timer execution
  }
  battery_measurement_delay_counter++;

    //Enable credit printout after timer execution
    if (credit_printout_flag == 0)
    {
      credit_printout_flag = 1;
    }

    TCNT1H = 11;    // Approx 4000 ms - Reload
    TCNT1L = 0;
    TIFR1  = 0x00;    // timer1 int flag reg: clear timer overflow flag
};

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

  aci_state.aci_pins.reset_pin              = 4;
  aci_state.aci_pins.active_pin             = UNUSED;
  aci_state.aci_pins.optional_chip_sel_pin  = UNUSED;

  aci_state.aci_pins.interface_is_interrupt = false;
  aci_state.aci_pins.interrupt_number       = 1;


  /** We reset the nRF8001 here by toggling the RESET line connected to the nRF8001
   *  and initialize the data structures required to setup the nRF8001
   */
  //The second parameter is for turning debug printing on for the ACI Commands and Events so they be printed on the Serial
  lib_aci_init(&aci_state, false);

  pinMode(6, INPUT); //Pin #6 on Arduino -> PAIRING CLEAR pin: Connect to 3.3v to clear the pairing
  if (0x01 == digitalRead(6))
  {
    //Clear the pairing
    Serial.println(F("Pairing cleared. Remove the wire on Pin 6 and reset the board for normal operation."));
    //Address. Value
    EEPROM.write(0, 0);
    while(1) {};
  }

  //Initialize the state of the bond
  aci_state.bonded = ACI_BOND_STATUS_FAILED;

  heart_rate_init();
  init_battery_data_buffers();
}

void aci_loop()
{
  static bool setup_required = false;

  // We enter the if statement only when there is a ACI event available to be processed
  if (lib_aci_event_get(&aci_state, &aci_data))
  {
    aci_evt_t * aci_evt;
    aci_evt = &aci_data.evt;
    //@todo change this so that the commands and events can be processed here in a switch case instead of callbacks
    //hal_aci_tl_msg_rcv_hook(&aci_data);
    switch(aci_evt->evt_opcode)
    {
      case ACI_EVT_DEVICE_STARTED:
      {
        aci_state.data_credit_total = aci_evt->params.device_started.credit_available;
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
            Serial.println(F("Evt Device Started: Standby"));

            if (aci_evt->params.device_started.hw_error)
            {
              delay(20); //Magic number used to make sure the HW error event is handled correctly.
            }
            else
            {
              Timer1start();
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
            case ACI_CMD_GET_BATTERY_LEVEL:
              break;
          }
        }
        break;

      case ACI_EVT_PIPE_STATUS:
        Serial.println(F("Evt Pipe Status"));
        /** check if the peer has subscribed to the Heart Rate Measurement Characteristic for Notifications
        */
        if (lib_aci_is_pipe_available(&aci_state, PIPE_HEART_RATE_HEART_RATE_MEASUREMENT_TX)
            && (false == timing_change_done) )
        {
          /*
          Request a change to the link timing as set in the GAP -> Preferred Peripheral Connection Parameters
          Change the setting in nRFgo studio -> nRF8001 configuration -> GAP Settings and recompile the xml file.
          */
          lib_aci_change_timing_GAP_PPCP();
          timing_change_done = true;
        }
        break;

      case ACI_EVT_TIMING:
        /*
        Link timing has changed.
        */
        Serial.print(F("Timing changed. New connection interval: "));
        Serial.print(aci_evt->params.timing.conn_rf_interval * 1.25, 0);
        Serial.println(F(" ms"));
        break;

      case ACI_EVT_CONNECTED:
        //radio_ack_pending  = false;
        aci_state.data_credit_available = aci_state.data_credit_total;
        timing_change_done = false;
        Serial.println(F("Evt Connected"));
        break;

      case ACI_EVT_DATA_CREDIT:
        aci_state.data_credit_available = aci_state.data_credit_available + aci_evt->params.data_credit.credit;
        /**
        Bluetooth Radio ack received from the peer radio for the data packet sent.
        This also signals that the buffer used by the nRF8001 for the data packet is available again.
        */
        break;

      case ACI_EVT_PIPE_ERROR:
        //See the appendix in the nRF8001 Product Specication for details on the error codes

        //Increment the credit available as the data packet was not sent.
        //The pipe error also represents the Attribute protocol Error Response sent from the peer and that should not be counted
        //for the credit.
        if (ACI_STATUS_ERROR_PEER_ATT_ERROR != aci_evt->params.pipe_error.error_code)
        {
          aci_state.data_credit_available++;
        }
        /**
        Send data failed. ACI_EVT_DATA_CREDIT will not come.
        This can happen if the pipe becomes unavailable by the peer unsubscribing to the Heart Rate
        Measurement characteristic.
        This can also happen when the link is disconnected after the data packet has been sent.
        */
        //radio_ack_pending = false;
        break;

       case ACI_EVT_DISCONNECTED:
        /**
        Advertise again if the advertising timed out.
        */
        Serial.println(F("Evt Disconnected !!!"));
        if(ACI_STATUS_ERROR_ADVT_TIMEOUT == aci_evt->params.disconnected.aci_status)
        {
          Serial.println(F("Evt Disconnected -> Advertising timed out"));
          {
            Serial.println(F("nRF8001 going to sleep"));
            lib_aci_sleep();
            aci_state.device_state = ACI_DEVICE_SLEEP;
          }
        }
        else
        {
          Serial.println(F("Evt Disconnected -> Link lost."));
          lib_aci_connect(180/* in seconds */, 0x0050 /* advertising interval 50ms*/);
          Serial.println(F("Advertising started"));
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
        Timer1start();
        lib_aci_connect(30/* in seconds */, 0x0100 /* advertising interval 100ms*/);
        Serial.println(F("Advertising started"));
        break;
    }
  }
  else
  {
    // If No event in the ACI Event queue and No event in the ACI Command queue
    // Arduino can go to sleep
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

/*
Use this function to reset the expended energy if the Heart Rate Control Point is present.
*/
#ifdef PIPE_HEART_RATE_HEART_RATE_CONTROL_POINT_RX_ACK
void hook_for_resetting_energy_expended(void)
{
}
#endif


void loop()
{
  //Perform any serial printout here when timer is inactive
  //This will prevent conflicts with the timer interrupt and the serial interrupt

  //Data credits printout
  if(ENABLE_CREDIT_PRINTOUT == 1 && credit_printout_flag == 1)
  {
    Serial.print(F("Credit available: "));
    Serial.println(aci_state.data_credit_available);
    Serial.print(F("Credit total: "));
    Serial.println(aci_state.data_credit_total);
    credit_printout_flag = 0;    //Clear flag to allow only one printout per timer interrupt
  }

  //Battery measurement printout
  if(ENABLE_BATTERY_MEASUREMENT_PRINTOUT == 1 && battery_measurement_flag == 1)
  {
    print_battery_measurement_data();
    battery_measurement_flag = 0;   //Clear flag to allow only one printout per timer interrupt
  }

  //Send data from data buffers
  if(aci_state.data_credit_available > 0)             //Check if there are any data credits available
  {
    if(HEART_RATE_DATA_BUFF_SIZE != 0)                //If there is no heart-rate data buffer, there is nothing to send
      send_data_from_heart_rate_buffer(&aci_state);   //Send any buffered heart-rate data over the BLE link via nRF8001
    if(BATTERY_DATA_BUFF_SIZE != 0)										//If there is no heart-rate data buffer, there is nothing to send
      send_data_from_battery_buffer(&aci_state);      //Send any buffered battery data over the BLE link via nRF8001
  }

  //Check for any incoming events
  aci_loop();
}

