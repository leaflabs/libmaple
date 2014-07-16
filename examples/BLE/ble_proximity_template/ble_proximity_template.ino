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


/** @defgroup ble_proximity_template ble_proximity_template
@{
@ingroup projects
@brief Empty project that can be used as a template for new proximity projects.

@details
This project is a firmware template for new proximity projects.
The project will run correctly in its current state.
With this project you have a starting point for adding your own application functionality.

The following instructions describe the steps to be made on the Windows PC:

 -# Install the Master Control Panel on your computer. Connect the Master Emulator
    (nRF2739) and make sure the hardware drivers are installed.

-# You can use the nRF proximity app in the Apple iOS app store with this proximity template app

Note: Pin #6 on Arduino -> PAIRING CLEAR pin: Connect to 3.3v to clear the pairing

 *
 * Click on the "Serial Monitor" button on the Arduino IDE to reset the Arduino and start the application.
 * The setup() function is called first and is called only once for each reset of the Arduino.
 * The loop() function as the name implies is called in a loop.
 *
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
#include <lib_aci.h>

#include <aci_setup.h>
#include "immediate_alert.h"
#include "link_loss.h"
#include <EEPROM.h>

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

/* Store the setup for the nRF8001 in the flash of the AVR to save on RAM */
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
// Status of the bond (R) Peer address
static struct aci_state_t aci_state;

/*
Temporary buffers for sending ACI commands
*/
static hal_aci_evt_t  aci_data;
static hal_aci_data_t aci_cmd;

/*
We will store the bonding info for the nRF8001 in the EEPROM/Flash of the MCU to recover from a power loss situation
*/
static bool bonded_first_time = true;

/*
Timing change state variable
*/
static bool timing_change_done = false;

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

/*************NOTE**********
Scroll to the end of the file and read the loop() and setup() functions.
The loop/setup functions is the equivalent of the main() function
*/

/*
Read the Dymamic data from the EEPROM and send then as ACI Write Dynamic Data to the nRF8001
This will restore the nRF8001 to the situation when the Dynamic Data was Read out
*/
aci_status_code_t bond_data_restore(aci_state_t *aci_stat, uint8_t eeprom_status, bool *bonded_first_time_state)
{
  aci_evt_t *aci_evt;
  uint8_t eeprom_offset_read = 1;
  uint8_t write_dyn_num_msgs = 0;
  uint8_t len =0;

  // Get the number of messages to write for the eeprom_status
  write_dyn_num_msgs = eeprom_status & 0x7F;

  //Read from the EEPROM
  while(1)
  {
    len = EEPROM.read(eeprom_offset_read);
    eeprom_offset_read++;
    aci_cmd.buffer[0] = len;

    for (uint8_t i=1; i<=len; i++)
    {
        aci_cmd.buffer[i] = EEPROM.read(eeprom_offset_read);
        eeprom_offset_read++;
    }
    //Send the ACI Write Dynamic Data
    if (!hal_aci_tl_send(&aci_cmd))
    {
      Serial.println(F("bond_data_restore: Cmd Q Full"));
      return ACI_STATUS_ERROR_INTERNAL;
    }

    //Spin in the while loop waiting for an event
    while (1)
    {
      if (lib_aci_event_get(aci_stat, &aci_data))
      {
        aci_evt = &aci_data.evt;

        if (ACI_EVT_CMD_RSP != aci_evt->evt_opcode)
        {
          //Got something other than a command response evt -> Error
          Serial.print(F("bond_data_restore: Expected cmd rsp evt. Got: 0x"));
          Serial.println(aci_evt->evt_opcode, HEX);
          return ACI_STATUS_ERROR_INTERNAL;
        }
        else
        {
          write_dyn_num_msgs--;

          //ACI Evt Command Response
          if (ACI_STATUS_TRANSACTION_COMPLETE == aci_evt->params.cmd_rsp.cmd_status)
          {
            //Set the state variables correctly
            *bonded_first_time_state = false;
            aci_stat->bonded = ACI_BOND_STATUS_SUCCESS;

            delay(10);

            return ACI_STATUS_TRANSACTION_COMPLETE;
          }
          if (0 >= write_dyn_num_msgs)
          {
            //should have returned earlier
            return ACI_STATUS_ERROR_INTERNAL;
          }
          if (ACI_STATUS_TRANSACTION_CONTINUE == aci_evt->params.cmd_rsp.cmd_status)
          {
            //break and write the next ACI Write Dynamic Data
            break;
          }
        }
      }
    }
  }
}


/*
This function is specific to the atmega328
@params ACI Command Response Evt received from the Read Dynmaic Data
*/
void bond_data_store(aci_evt_t *evt)
{
  static int eeprom_write_offset = 1;

  //Write it to non-volatile storage
  EEPROM.write( eeprom_write_offset, evt->len -2 );
  eeprom_write_offset++;

  EEPROM.write( eeprom_write_offset, ACI_CMD_WRITE_DYNAMIC_DATA);
  eeprom_write_offset++;

  for (uint8_t i=0; i< (evt->len-3); i++)
  {
    EEPROM.write( eeprom_write_offset, evt->params.cmd_rsp.params.padding[i]);
    eeprom_write_offset++;
  }
}

bool bond_data_read_store(aci_state_t *aci_stat)
{
  /*
  The size of the dynamic data for a specific Bluetooth Low Energy configuration
  is present in the ublue_setup.gen.out.txt generated by the nRFgo studio as "dynamic data size".
  */
  bool status = false;
  aci_evt_t * aci_evt = NULL;
  uint8_t read_dyn_num_msgs = 0;

  //Start reading the dynamic data
  lib_aci_read_dynamic_data();
  read_dyn_num_msgs++;

  while (1)
  {
    if (true == lib_aci_event_get(aci_stat, &aci_data))
    {
      aci_evt = &aci_data.evt;

      if (ACI_EVT_CMD_RSP != aci_evt->evt_opcode )
      {
        //Got something other than a command response evt -> Error
        status = false;
        break;
      }

      if (ACI_STATUS_TRANSACTION_COMPLETE == aci_evt->params.cmd_rsp.cmd_status)
      {
        //Store the contents of the command response event in the EEPROM
        //(len, cmd, seq-no, data) : cmd ->Write Dynamic Data so it can be used directly
        bond_data_store(aci_evt);

        //Set the flag in the EEPROM that the contents of the EEPROM is valid
        EEPROM.write(0, 0x80|read_dyn_num_msgs );
        //Finished with reading the dynamic data
        status = true;

        break;
      }

      if (!(ACI_STATUS_TRANSACTION_CONTINUE == aci_evt->params.cmd_rsp.cmd_status))
      {
        //We failed the read dymanic data
        //Set the flag in the EEPROM that the contents of the EEPROM is invalid
        EEPROM.write(0, 0x00);

        status = false;
        break;
      }
      else
      {
        //Store the contents of the command response event in the EEPROM
        // (len, cmd, seq-no, data) : cmd ->Write Dynamic Data so it can be used directly when re-storing the dynamic data
        bond_data_store(aci_evt);

        //Read the next dynamic data message
        lib_aci_read_dynamic_data();
        read_dyn_num_msgs++;
      }
    }
  }
  return status;
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
      /**
      As soon as you reset the nRF8001 you will get an ACI Device Started Event
      */
      case ACI_EVT_DEVICE_STARTED:
      {
        aci_state.data_credit_total = aci_evt->params.device_started.credit_available;
        switch(aci_evt->params.device_started.device_mode)
        {
          case ACI_DEVICE_SETUP:
            /**
            When the device is in the setup mode
            */
            Serial.println(F("Evt Device Started: Setup"));
            setup_required = true;
            break;

          case ACI_DEVICE_STANDBY:
            Serial.println(F("Evt Device Started: Standby"));
            if (aci_evt->params.device_started.hw_error)
            {
              delay(20); //Magic number used to make sure the HW error event is handled correctly.
            }
            else
            {
              //Manage the bond in EEPROM of the AVR
              {
                uint8_t eeprom_status = 0;
                eeprom_status = EEPROM.read(0);
                if (eeprom_status != 0x00)
                {
                  Serial.println(F("Previous Bond present. Restoring"));
                  Serial.println(F("Using existing bond stored in EEPROM."));
                  Serial.println(F("   To delete the bond stored in EEPROM, connect Pin 6 to 3.3v and Reset."));
                  Serial.println(F("   Make sure that the bond on the phone/PC is deleted as well."));
                  //We must have lost power and restarted and must restore the bonding infromation using the ACI Write Dynamic Data
                  if (ACI_STATUS_TRANSACTION_COMPLETE == bond_data_restore(&aci_state, eeprom_status, &bonded_first_time))
                  {
                    Serial.println(F("Bond restored successfully"));
                  }
                  else
                  {
                    Serial.println(F("Bond restore failed. Delete the bond and try again."));
                  }
                }
              }

              // Start bonding as all proximity devices need to be bonded to be usable
              if (ACI_BOND_STATUS_SUCCESS != aci_state.bonded)
              {
                lib_aci_bond(180/* in seconds */, 0x0050 /* advertising interval 50ms*/);
                Serial.println(F("No Bond present in EEPROM."));
                Serial.println(F("Advertising started : Waiting to be connected and bonded"));
              }
              else
              {
                //connect to an already bonded device
                //Use lib_aci_direct_connect for faster re-connections with PC, not recommended to use with iOS/OS X
                lib_aci_connect(100/* in seconds */, 0x0020 /* advertising interval 20ms*/);
                Serial.println(F("Already bonded : Advertising started : Waiting to be connected"));
              }
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
          Serial.print(F("ACI Command "));
          Serial.println(aci_evt->params.cmd_rsp.cmd_opcode, HEX);
          Serial.print(F("Evt Cmd respone: Status "));
          Serial.println(aci_evt->params.cmd_rsp.cmd_status, HEX);
        }
        if (ACI_CMD_GET_DEVICE_VERSION == aci_evt->params.cmd_rsp.cmd_opcode)
        {
          //Store the version and configuration information of the nRF8001 in the Hardware Revision String Characteristic
          lib_aci_set_local_data(&aci_state, PIPE_DEVICE_INFORMATION_HARDWARE_REVISION_STRING_SET,
            (uint8_t *)&(aci_evt->params.cmd_rsp.params.get_device_version), sizeof(aci_evt_cmd_rsp_params_get_device_version_t));
        }
        break;

      case ACI_EVT_CONNECTED:
        Serial.println(F("Evt Connected"));
        aci_state.data_credit_available = aci_state.data_credit_total;
        timing_change_done = false;
        /*
        Get the device version of the nRF8001 and store it in the Hardware Revision String
        */
        lib_aci_device_version();
        break;

      case ACI_EVT_BOND_STATUS:
        aci_state.bonded = aci_evt->params.bond_status.status_code;
        break;

      case ACI_EVT_PIPE_STATUS:
        Serial.println(F("Evt Pipe Status"));
        //Link is encrypted when the PIPE_LINK_LOSS_ALERT_ALERT_LEVEL_RX_ACK_AUTO is available
        if ((false == timing_change_done) &&
          lib_aci_is_pipe_available(&aci_state, PIPE_LINK_LOSS_ALERT_ALERT_LEVEL_RX_ACK_AUTO))
        {
          lib_aci_change_timing_GAP_PPCP(); // change the timing on the link as specified in the nRFgo studio -> nRF8001 conf. -> GAP.
                                            // Used to increase or decrease bandwidth
          timing_change_done = true;
        }
        // The pipe will be available only in an encrpyted link to the phone
        if ((ACI_BOND_STATUS_SUCCESS == aci_state.bonded) &&
              (lib_aci_is_pipe_available(&aci_state, PIPE_LINK_LOSS_ALERT_ALERT_LEVEL_RX_ACK_AUTO)) &&
              (lib_aci_is_pipe_available(&aci_state, PIPE_IMMEDIATE_ALERT_ALERT_LEVEL_RX)))
        {
          //Note: This may be called multiple times after the Arduino has connected to the right phone
          Serial.println(F("phone Detected."));
          Serial.println(F("Do more stuff here. when your phone is detected"));
        }
        break;

      case ACI_EVT_TIMING:
        Serial.println(F("Evt link connection interval changed"));
        //Disconnect as soon as we are bonded and required pipes are available
        //This is used to store the bonding info on disconnect and then re-connect to verify the bond
        if((ACI_BOND_STATUS_SUCCESS == aci_state.bonded) &&
           (true == bonded_first_time) &&
           (GAP_PPCP_MAX_CONN_INT >= aci_state.connection_interval) &&
           (GAP_PPCP_MIN_CONN_INT <= aci_state.connection_interval) && //Timing change already done: Provide time for the the peer to finish
           (lib_aci_is_pipe_available(&aci_state, PIPE_LINK_LOSS_ALERT_ALERT_LEVEL_RX_ACK_AUTO)) &&
           (lib_aci_is_pipe_available(&aci_state, PIPE_IMMEDIATE_ALERT_ALERT_LEVEL_RX)))
         {
           lib_aci_disconnect(&aci_state, ACI_REASON_TERMINATE);
         }
          break;

      case ACI_EVT_DISCONNECTED:
        Serial.println(F("Evt Disconnected. Link Lost or Advertising timed out"));
        if (ACI_BOND_STATUS_SUCCESS == aci_state.bonded)
        {
          if (ACI_STATUS_EXTENDED == aci_evt->params.disconnected.aci_status) //Link was disconnected
          {
            if (bonded_first_time)
            {
              bonded_first_time = false;
              //Store away the dynamic data of the nRF8001 in the Flash or EEPROM of the MCU
              // so we can restore the bond information of the nRF8001 in the event of power loss
              if (bond_data_read_store(&aci_state))
              {
                Serial.println(F("Dynamic Data read and stored successfully"));
              }
            }
            if (0x24 == aci_evt->params.disconnected.btle_status)
            {
              //The error code appears when phone or Arduino has deleted the pairing/bonding information.
              //The Arduino stores the bonding information in EEPROM, which is deleted only by
              // the user action of connecting pin 6 to 3.3v and then followed by a reset.
              //While deleting bonding information delete on the Arduino and on the phone.
              Serial.println(F("phone/Arduino has deleted the bonding/pairing information"));
            }

            proximity_disconect_evt_rcvd (aci_evt->params.disconnected.btle_status);
          }
          lib_aci_connect(180/* in seconds */, 0x0100 /* advertising interval 100ms*/);
          Serial.println(F("Using existing bond stored in EEPROM."));
          Serial.println(F("   To delete the bond stored in EEPROM, connect Pin 6 to 3.3v and Reset."));
          Serial.println(F("   Make sure that the bond on the phone/PC is deleted as well."));
          Serial.println(F("Advertising started. Connecting."));
        }
        else
        {
          //There is no existing bond. Try to bond.
          lib_aci_bond(180/* in seconds */, 0x0050 /* advertising interval 50ms*/);
          Serial.println(F("Advertising started. Bonding."));
        }
        break;

      case ACI_EVT_DATA_RECEIVED:
        Serial.print(F("Pipe #"));
        Serial.print(aci_evt->params.data_received.rx_data.pipe_number, DEC);
        Serial.print(F("-> "));
        Serial.println(aci_evt->params.data_received.rx_data.aci_data[0], DEC);
        link_loss_pipes_updated_evt_rcvd(aci_evt->params.data_received.rx_data.pipe_number,
                                         &aci_evt->params.data_received.rx_data.aci_data[0]);
        break;

      case ACI_EVT_DATA_CREDIT:
        aci_state.data_credit_available = aci_state.data_credit_available + aci_evt->params.data_credit.credit;
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

      case ACI_EVT_HW_ERROR:
        Serial.print(F("HW error: "));
        Serial.println(aci_evt->params.hw_error.line_num, DEC);

        for(uint8_t counter = 0; counter <= (aci_evt->len - 3); counter++)
        {
        Serial.write(aci_evt->params.hw_error.file_name[counter]); //uint8_t file_name[20];
        }
        Serial.println();

        //Manage the bond in EEPROM of the AVR
        {
          uint8_t eeprom_status = 0;
          eeprom_status = EEPROM.read(0);
          if (eeprom_status != 0x00)
          {
            Serial.println(F("Previous Bond present. Restoring"));
            Serial.println(F("Using existing bond stored in EEPROM."));
            Serial.println(F("   To delete the bond stored in EEPROM, connect Pin 6 to 3.3v and Reset."));
            Serial.println(F("   Make sure that the bond on the phone/PC is deleted as well."));
            //We must have lost power and restarted and must restore the bonding infromation using the ACI Write Dynamic Data
            if (ACI_STATUS_TRANSACTION_COMPLETE == bond_data_restore(&aci_state, eeprom_status, &bonded_first_time))
            {
              Serial.println(F("Bond restored successfully"));
            }
            else
            {
              Serial.println(F("Bond restore failed. Delete the bond and try again."));
            }
          }
        }

        // Start bonding as all proximity devices need to be bonded to be usable
        if (ACI_BOND_STATUS_SUCCESS != aci_state.bonded)
        {
          lib_aci_bond(180/* in seconds */, 0x0050 /* advertising interval 50ms*/);
          Serial.println(F("No Bond present in EEPROM."));
          Serial.println(F("Advertising started : Waiting to be connected and bonded"));
        }
        else
        {
          //connect to an already bonded device
          //Use lib_aci_direct_connect for faster re-connections with PC, not recommended to use with iOS/OS X
          lib_aci_connect(100/* in seconds */, 0x0020 /* advertising interval 20ms*/);
          Serial.println(F("Already bonded : Advertising started : Waiting to be connected"));
        }
        break;

    }
  }
  else
  {
    //Serial.println(F("No ACI Events available"));
    // No event in the ACI Event queue and if there is no event in the ACI command queue the arduino can go to sleep
    // Arduino can go to sleep now
    // Wakeup from sleep from the RDYN line
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

void alert_level_print(alert_level_t level)
{
  switch (level)
  {
    case ALERT_LEVEL_NO_ALERT:
      Serial.println(F("NO_ALERT"));
      break;

    case ALERT_LEVEL_MILD_ALERT:
      Serial.println(F("MILD_ALERT"));
      break;

    case ALERT_LEVEL_HIGH_ALERT:
      Serial.println(F("HIGH_ALERT"));
      break;
  }
}

void immediate_alert_hook(alert_level_t level)
{
  Serial.println(F("Immediate Alert: Alert level = "));
  alert_level_print(level);
}

void link_loss_alert_hook(alert_level_t level)
{
  Serial.println(F("Link Loss Alert: Alert level = "));
  alert_level_print(level);
}

/*
Description:

<Add description of the proximity application.

The ACI Evt Data Credit provides the radio level ack of a transmitted packet.
*/
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

  //Tell the ACI library, the MCU to nRF8001 pin connections
  aci_state.aci_pins.board_name = BOARD_DEFAULT; //See board.h for details
  aci_state.aci_pins.reqn_pin   = 9;
  aci_state.aci_pins.rdyn_pin   = 8;
  aci_state.aci_pins.mosi_pin   = MOSI;
  aci_state.aci_pins.miso_pin   = MISO;
  aci_state.aci_pins.sck_pin    = SCK;

  aci_state.aci_pins.spi_clock_divider      = SPI_CLOCK_DIV8;//SPI_CLOCK_DIV8  = 2MHz SPI speed
                                                             //SPI_CLOCK_DIV16 = 1MHz SPI speed

  aci_state.aci_pins.reset_pin              = 4; //4 for Nordic board, UNUSED for REDBEARLABS
  aci_state.aci_pins.active_pin             = UNUSED;
  aci_state.aci_pins.optional_chip_sel_pin  = UNUSED;

  aci_state.aci_pins.interface_is_interrupt = false;
  aci_state.aci_pins.interrupt_number       = UNUSED;

  //We reset the nRF8001 here by toggling the RESET line connected to the nRF8001
  //and initialize the data structures required to setup the nRF8001
  //The second parameter is for turning debug printing on for the ACI Commands and Events so they be printed on the Serial
  lib_aci_init(&aci_state, false);
  aci_state.bonded = ACI_BOND_STATUS_FAILED;

  pinMode(6, INPUT); //Pin #6 on Arduino -> PAIRING CLEAR pin: Connect to 3.3v to clear the pairing
  if (0x01 == digitalRead(6))
  {
    //Clear the pairing
    Serial.println(F("Pairing/Bonding info cleared from EEPROM."));
    Serial.println(F("Remove the wire on Pin 6 and reset the board for normal operation."));
    //Address. Value
    EEPROM.write(0, 0);
    while(1) {};
  }
}


void loop()
{
  aci_loop();
}


