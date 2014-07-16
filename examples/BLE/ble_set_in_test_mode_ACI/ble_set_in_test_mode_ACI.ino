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
 * Test project to put the nRF8001 in Test mode and allow DTM commands over the Arduino Serial interface.
 * Note: The serial interface of some arduino boards is reset on startup, so some work is needed on the nRFgo studio
 * before it can be used with this project.
 */

/** @defgroup ble_set_in_test_mode ble_set_in_test_mode
@{
@ingroup projects
@brief Put the nRF8001 in test mode.

@details
This project is to put the nRF8001 in test mode and enable the nRF8001 to accept DTM commands over ACI using the Arduino serial interface.
Note: Serial Event is NOT compatible with Leonardo, Micro, Esplora
@todo: Test this to make sure it works with both the pyhon script and nRFgo studio: You can send the DTM commands from the nRFgo studio or from a Nordic Semiconductor supplied python script on a Windows PC.
 */
#include <SPI.h>
#include <hal_aci_tl.h>
#include <lib_aci.h>

// aci_struct that will contain
// total initial credits
// current credit
// current state of the aci (setup/test/standby/active/sleep)
// open remote pipe pending
// close remote pipe pending
// Current pipe available bitmap
// Current pipe closed bitmap
// Current connection interval, slave latency and link supervision timeout
// Current State of the the GATT client (Service Discovery)
// Status of the bond (R) Peer address
static struct aci_state_t aci_state;

static hal_aci_evt_t aci_data;
static hal_aci_data_t aci_cmd;

uint8_t dtm_report[2];           // DTM output
static uint8_t uart_buffer[20];
static uint8_t uart_buffer_len = 0;
static uint8_t dummychar = 0;
boolean stringComplete = false;  // whether the string is complete
uint8_t stringIndex = 0;         //Initialize the index to store incoming chars
boolean dtmMode = false;         //is the device in dtm mode

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
  Serial.begin(19200);
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
  
  //Tell the ACI library, the MCU to nRF8001 pin connections
  aci_state.aci_pins.board_name = BOARD_DEFAULT; //See board.h for details REDBEARLAB_SHIELD_V1_1 or BOARD_DEFAULT
  aci_state.aci_pins.reqn_pin   = 9; //SS for Nordic board, 9 for REDBEARLAB_SHIELD_V1_1
  aci_state.aci_pins.rdyn_pin   = 8; //3 for Nordic board, 8 for REDBEARLAB_SHIELD_V1_1
  aci_state.aci_pins.mosi_pin   = MOSI;
  aci_state.aci_pins.miso_pin   = MISO;
  aci_state.aci_pins.sck_pin    = SCK;

  aci_state.aci_pins.spi_clock_divider      = SPI_CLOCK_DIV8;//SPI_CLOCK_DIV8  = 2MHz SPI speed
                                                             //SPI_CLOCK_DIV16 = 1MHz SPI speed

  aci_state.aci_pins.reset_pin              = 4; //4 for Nordic board, UNUSED for REDBEARLABS
  aci_state.aci_pins.active_pin             = UNUSED;
  aci_state.aci_pins.optional_chip_sel_pin  = UNUSED;

  aci_state.aci_pins.interface_is_interrupt = false;
  aci_state.aci_pins.interrupt_number       = 1;

  //We reset the nRF8001 here by toggling the RESET line connected to the nRF8001
  //and initialize the data structures required to setup the nRF8001
  //The second parameter is for turning debug printing on for the ACI Commands and Events so they be printed on the Serial
  lib_aci_init(&aci_state, false);

  Serial.println(F("nRF8001 Reset done"));
}

void aci_loop(void)
{

  // We enter the if statement only when there is a ACI event available to be processed
  if (lib_aci_event_get(&aci_state, &aci_data))
  {
    aci_evt_t * aci_evt;
    aci_evt = &aci_data.evt;

    switch(aci_evt->evt_opcode)
    {
      /**
      As soon as you reset the nRF8001 you will get an ACI Device Started Event
      */
      case ACI_EVT_DEVICE_STARTED:
      {
        aci_state.data_credit_available = aci_evt->params.device_started.credit_available;
        switch(aci_evt->params.device_started.device_mode)
        {
          case ACI_DEVICE_SETUP:
            Serial.println(F("Evt Device Started: Setup"));
            //Put the nRF8001 in Test mode.
            //See ACI Test Command in Section 24 (System Commands) of the nRF8001 datasheet.
            //Use ACI_TEST_MODE_DTM_ACI to send DTM commands over ACI
            //lib_aci_test(ACI_TEST_MODE_DTM_UART);
            lib_aci_test(ACI_TEST_MODE_DTM_ACI);
            break;

          case ACI_DEVICE_TEST:
          {
            uint8_t i = 0;
            Serial.println(F("Evt Device Started: Test"));
            Serial.println(F("Device in DTM over ACI mode"));
            Serial.println(F("Use DTM over UART with the Arduino serial interface to send DTM commands to the nRF8001"));
      dtmMode = true;
          }
            break;
        }
      }
        break; //ACI Device Started Event

      case ACI_EVT_CMD_RSP:
        //If an ACI command response event comes with an error -> stop
        if (ACI_STATUS_SUCCESS != aci_evt->params.cmd_rsp.cmd_status)
        {
          //ACI ReadDynamicData and ACI WriteDynamicData will have status codes of
          //TRANSACTION_CONTINUE and TRANSACTION_COMPLETE
          //all other ACI commands will have status code of ACI_STATUS_SCUCCESS for a successful command
          Serial.print(F("ACI Command 0x"));
          Serial.println(aci_evt->params.cmd_rsp.cmd_opcode, HEX);
          Serial.println(F("Evt Cmd respone: Error. Arduino is in an while(1); loop"));
          while (1);
        }
        else if (ACI_CMD_DTM_CMD == aci_evt->params.cmd_rsp.cmd_opcode)
        {
          dtm_report[0] = aci_evt->params.cmd_rsp.params.dtm_cmd.evt_msb;
          dtm_report[1] = aci_evt->params.cmd_rsp.params.dtm_cmd.evt_lsb;
          Serial.write(dtm_report,2);
        }
        break;
    }
  }
  else
  {
    // No event in the ACI Event queue
  }
}

void dtm_command_loop(void)
{
  if(dtmMode)
  {
     uart_buffer_len = stringIndex + 1;
    // print the string when a newline arrives:
    if (stringComplete) 
    {
      if (uart_buffer_len > 2)
      {
        Serial.println(F("DTM command to long")); //Not compatible with DTM tester?
      }
      else
      {
        //Forwarding DTM command to the nRF8001
        lib_aci_dtm_command(uart_buffer[0], uart_buffer[1]);
      }

      // clear the uart_buffer:
      for (stringIndex = 0; stringIndex < 20; stringIndex++)
      {
        uart_buffer[stringIndex] = ' ';
      }

      // reset the flag and the index in order to receive more data
      stringIndex    = 0;
      stringComplete = false;
    }
  }
}

void loop()
{
   //Process any ACI commands or events
  aci_loop();

  //Process any DTM command, DTM Events is processed in the aci_loop
  dtm_command_loop();
  
  //For ChipKit you have to call the function that reads from Serial
  #if defined (__PIC32MX__)
    if (Serial.available())
    {
      serialEvent();
    }
  #endif
}

/*
 COMMENT ONLY FOR ARDUINO
 SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 Serial Event is NOT compatible with Leonardo, Micro, Esplora
 */
void serialEvent() {

  while(Serial.available() > 0){
    // get the new byte:
    dummychar = (uint8_t)Serial.read();
    if(!stringComplete)
    {
      if (dummychar == '\n')
      {
        // if the incoming character is a newline, set a flag
        // so the main loop can do something about it
        stringIndex--;
        stringComplete = true;
      }
      else
      {
        if(stringIndex > 19)
        {
          Serial.println("Serial input truncated");
          stringIndex--;
          stringComplete = true;
        }
        else
        {
          // add it to the uart_buffer
          uart_buffer[stringIndex] = dummychar;
          stringIndex++;
        }
      }
    }
  }
}
