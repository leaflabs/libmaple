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
 * My project template
 */

/** @defgroup my_project my_project
@{
@ingroup projects
@brief Empty project that can be used as a template for new projects.

@details
This project is a firmware template for new projects.
The project will run correctly in its current state, but does nothing.
With this project you have a starting point for adding your own application functionality.

The following instructions describe the steps to be made on the Windows PC:

 -# Install the Master Control Panel on your computer. Connect the Master Emulator
    (nRF2739) and make sure the hardware drivers are installed.

 */
#include <wirish/wirish.h>
#include <BLE/lib_aci.h>
#include <BLE/aci_setup.h>

/**
Put the nRF8001 setup in the RAM of the nRF8001.
*/
#include "services.h"
/**
Include the services_lock.h to put the setup in the OTP memory of the nRF8001.
This would mean that the setup cannot be changed once put in.
However this removes the need to do the setup of the nRF8001 on every reset.
*/


#ifdef SERVICES_PIPE_TYPE_MAPPING_CONTENT
    static services_pipe_type_mapping_t
        services_pipe_type_mapping[NUMBER_OF_PIPES] = SERVICES_PIPE_TYPE_MAPPING_CONTENT;
#else
    #define NUMBER_OF_PIPES 0
    static services_pipe_type_mapping_t * services_pipe_type_mapping = NULL;
#endif
static hal_aci_data_t setup_msgs[NB_SETUP_MESSAGES] PROGMEM = SETUP_MESSAGES_CONTENT;

// aci_struct will contain
// total initial credits
// current credit
// current state of the aci (setup/standby/active/sleep)
// open remote pipe pending
// close remote pipe pending
// Current pipe available bitmap
// Current pipe closed bitmap
// Current connection interval, slave latency and link supervision timeout
// Current State of the the GATT client (Service Discovery)
// Status of the bond (R) Peer address
static struct aci_state_t aci_state;
static hal_aci_evt_t aci_data;
//static hal_aci_data_t aci_cmd;

/* Define how assert should function in the BLE library */
void __ble_assert(const char *file, uint16_t line)
{
  SerialUSB.print("ERROR ");
  SerialUSB.print(file);
  SerialUSB.print(": ");
  SerialUSB.print(line);
  SerialUSB.print("\n");
  while(1);
}

void setup(void)
{
  Serial2.begin(115200);
  
  //Wait until the serial port is available 
  delay(1000);


  SerialUSB.println(F("Maple setup"));
  SerialUSB.println(F("Set line ending to newline to send data from the serial monitor"));
  
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
  aci_state.aci_pins.mosi_pin   = BOARD_SPI1_MOSI_PIN;
  aci_state.aci_pins.miso_pin   = BOARD_SPI1_MISO_PIN;
  aci_state.aci_pins.sck_pin    = BOARD_SPI1_SCK_PIN;

  aci_state.aci_pins.spi_clock_divider      = SPI_2_25MHZ;
                                                         

  aci_state.aci_pins.reset_pin              = 7; 
  aci_state.aci_pins.active_pin             = UNUSED;
  aci_state.aci_pins.optional_chip_sel_pin  = UNUSED;

  aci_state.aci_pins.interface_is_interrupt = false; //Interrups disabled for Maple Board
  aci_state.aci_pins.interrupt_number       = 1;

  /* We initialize the data structures required to setup the nRF8001
  */
  //The second parameter is for turning debug printing on for the ACI Commands and Events so they be printed on the Serial
  lib_aci_init(&aci_state, false);
}


void loop()
{
  static bool setup_required = false;

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
            /**
            When the device is in the setup mode
            */
            SerialUSB.println(F("Evt Device Started: Setup"));
            setup_required = true;
            break;

          case ACI_DEVICE_STANDBY:
            SerialUSB.println(F("Evt Device Started: Standby"));
            if (aci_evt->params.device_started.hw_error)
            {
              delay(20); //Magic number used to make sure the HW error event is handled correctly.
            }
            else
            {
            lib_aci_connect(180/* in seconds */, 0x0100 /* advertising interval 100ms*/);
            SerialUSB.println(F("Advertising started"));
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
          SerialUSB.print(F("ACI Command "));
          SerialUSB.println(aci_evt->params.cmd_rsp.cmd_opcode, HEX);
          SerialUSB.println(F("Evt Cmd respone: Error. Maple Board is in an while(1); loop"));
          while (1);
        }
        break;

      case ACI_EVT_CONNECTED:
        SerialUSB.println(F("Evt Connected"));
        break;

      case ACI_EVT_PIPE_STATUS:
        SerialUSB.println(F("Evt Pipe Status"));
        break;

      case ACI_EVT_DISCONNECTED:
        SerialUSB.println(F("Evt Disconnected/Advertising timed out"));
        lib_aci_connect(180/* in seconds */, 0x0100 /* advertising interval 100ms*/);
        SerialUSB.println(F("Advertising started"));
        break;

      case ACI_EVT_PIPE_ERROR:
        //See the appendix in the nRF8001 Product Specication for details on the error codes
        SerialUSB.print(F("ACI Evt Pipe Error: Pipe #:"));
        SerialUSB.print(aci_evt->params.pipe_error.pipe_number, DEC);
        SerialUSB.print(F("  Pipe Error Code: 0x"));
        SerialUSB.println(aci_evt->params.pipe_error.error_code, HEX);

        //Increment the credit available as the data packet was not sent.
        //The pipe error also represents the Attribute protocol Error Response sent from the peer and that should not be counted
        //for the credit.
        if (ACI_STATUS_ERROR_PEER_ATT_ERROR != aci_evt->params.pipe_error.error_code)
        {
          aci_state.data_credit_available++;
        }
        break;

      case ACI_EVT_DATA_RECEIVED:
        SerialUSB.print(F("Pipe #: 0x"));
        SerialUSB.print(aci_evt->params.data_received.rx_data.pipe_number, HEX);
        {
          int i=0;
          SerialUSB.print(F(" Data(Hex) : "));
          for(i=0; i<aci_evt->len - 2; i++)
          {
            SerialUSB.print(aci_evt->params.data_received.rx_data.aci_data[i], HEX);
            SerialUSB.print(F(" "));
          }
        }
        SerialUSB.println(F(""));
        break;

      case ACI_EVT_HW_ERROR:
        SerialUSB.print(F("HW error: "));
        SerialUSB.println(aci_evt->params.hw_error.line_num, DEC);

        for(uint8_t counter = 0; counter <= (aci_evt->len - 3); counter++)
        {
        SerialUSB.write(aci_evt->params.hw_error.file_name[counter]); //uint8_t file_name[20];
        }
        SerialUSB.println();
        lib_aci_connect(180/* in seconds */, 0x0050 /* advertising interval 50ms*/);
        SerialUSB.println(F("Advertising started"));
        break;
    }
  }
  else
  {
    //SerialUSB.println(F("No ACI Events available"));
    // No event in the ACI Event queue
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




// -- init() and main() ---------------------------------------------------

__attribute__((constructor)) void premain()
{
  init();
}

int main(void)
{
  setup();

  while (true)
  {
    loop();
  }
  return 0;
}

