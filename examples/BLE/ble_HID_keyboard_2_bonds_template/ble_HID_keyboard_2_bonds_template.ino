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
 * HID (Human Interface Device) template
 */

/** @defgroup HID_keyboard_2_bonds_template project
@{
@ingroup projects
@brief HID Keyboard project that can be used as a template for new projects.

@details

IMPORTANT: This example still is not compatible with CHIPKIT

This project is a firmware template for new HID keyboard projects which need to use 2 bonds.
The project will run correctly in its current state.
This will show the Arduino board as a HID Keybaord to the Win 8.
After HID Keyboard has been bonded with Win 8.
The letter 'A' is sent to the Win 8 every 4 seconds.
With this project you have a starting point for adding your own application functionality.

The following instructions describe the steps to be made on the Windows PC:

 -# Install the Master Control Panel on your computer. Connect the Master Emulator
    (nRF2739) and make sure the hardware drivers are installed.

 -# Alternatively you should be able to get the board to work directly with a Win 8/Win RT PC after adding
 the required buttons for I/O.

Note:
Pin #6 on Arduino -> PAIRING CLEAR pin: Connect to 3.3v to clear the pairing
Pin #2 on Arduino -> Add new bond pin: Connect to 3.3v to add a new bond.

The bonding information is stored in the EEPROM of the ATmega328 in the Arduino UNO

The setup() and the loop() functions are the equvivlent of main() .

 */
#include <SPI.h>
#include "services.h"

#include <lib_aci.h>
#include "aci_setup.h"
#include "EEPROM.h"

#ifdef SERVICES_PIPE_TYPE_MAPPING_CONTENT
    static services_pipe_type_mapping_t
        services_pipe_type_mapping[NUMBER_OF_PIPES] = SERVICES_PIPE_TYPE_MAPPING_CONTENT;
#else
    #define NUMBER_OF_PIPES 0
    static services_pipe_type_mapping_t * services_pipe_type_mapping = NULL;
#endif

static hal_aci_data_t setup_msgs[NB_SETUP_MESSAGES] PROGMEM = SETUP_MESSAGES_CONTENT;

#define BYTES_PER_BOND_IN_HEADER       2
#define BONDS_MAX                      2
#define BOND_DOES_NOT_EXIST_AT_INDEX   0xF0


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
static hal_aci_evt_t aci_data;
static hal_aci_data_t aci_cmd;

/*
We will store the bonding info for the nRF8001 in the MCU to recover from a power loss situation
*/
static uint8_t bond_number          = 0;
static uint8_t current_bond_index   = 0xFF;
static uint16_t eeprom_write_offset = BONDS_MAX * BYTES_PER_BOND_IN_HEADER;

/*
We will do the timing change for the link only once
*/
static bool timing_change_done = false;
static bool disconnect_started = false;

/*
Variables used for the timer on the AVR
*/
volatile uint8_t timer1_f = 0;

/*
The keyboard report is 8 bytes
0 Modifier keys
1 Reserved
2 Keycode 1
3 Keycode 2
4 Keycode 3
5 Keycode 4
6 Keycode 5
7 Keycode 6
*/
uint8_t keypressA[8]={ 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 };

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


Parameters: void

Returns:    void

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
  TCCR1B  = 0x05;        // Timer1 Control Reg B: Timer Prescaler set to 1024
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
  if (0 == timer1_f)
  {
    timer1_f = 1;
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

/*************NOTE**********
Scroll to the end of the file and read the loop() and setup() functions.
The loop/setup functions is the equivalent of the main() function
*/

/*
Read the Dymamic data from the EEPROM and send then as ACI Write Dynamic Data to the nRF8001
This will restore the nRF8001 to the situation when the Dynamic Data was Read out

Header in the EEPROM:
2 bytes are used in the header for each master the nRF8001 has bonded with.
The code supports 2 masters so the header uses 4 bytes.

Byte 0:
Bit 0  :Valid
Bit 1-7:Number of messages for restore
Byte 1:
Bit 0-7: Offset in EEPROM bytes to the ACI msg stored
Byte 2:
Bit 0  :Valid
Bit 1-7:Number of messages for restore
Byte 3:
Bit 0-7: Offset in EEPROM bytes to the ACI msg stored

bond_index : The index of the stored bonds in the EEPROM. Value: 0 or 1, when max 2 bonds can be stored.
*/
aci_status_code_t bond_data_restore(aci_state_t *aci_stat, uint8_t bond_index)
{
  aci_evt_t *aci_evt;
  uint8_t eeprom_status       = 0;
  uint16_t eeprom_offset_read = 0;
  uint8_t write_dyn_num_msgs  = 0;
  uint8_t len =0;

  eeprom_status      = EEPROM.read(bond_index * BYTES_PER_BOND_IN_HEADER);
  if (0x00 == eeprom_status)
  {
    return (aci_status_code_t)BOND_DOES_NOT_EXIST_AT_INDEX;
  }

  eeprom_offset_read = EEPROM.read((bond_index * BYTES_PER_BOND_IN_HEADER) + 1); //Offset from the start of the EEPROM
  //Since the size of the header is 4 bytes for 2 bonds. The first bond is stored from location 4 and the offset is 4.

  //Print the EEPROM header of 4 bytes
  Serial.println(F("EEPROM Header (4 bytes):"));
  Serial.println(EEPROM.read(0), HEX);
  Serial.println(EEPROM.read(1), HEX);
  Serial.println(EEPROM.read(2), HEX);
  Serial.println(EEPROM.read(3), HEX);
  Serial.println(F("--"));

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

    //@todo : Fix this bug that is changing this byte
    aci_cmd.buffer[1] = ACI_CMD_WRITE_DYNAMIC_DATA;

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
Uses the global   static int eeprom_write_offset to track the EEPROM write offset
*/
void bond_data_store(aci_evt_t *evt)
{
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

bool bond_data_read_store(aci_state_t *aci_stat, uint8_t new_bond_index)
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
        EEPROM.write(new_bond_index * BYTES_PER_BOND_IN_HEADER, 0x80|read_dyn_num_msgs );
        //Set the offset for the next bond as well
        EEPROM.write(((new_bond_index+1) * BYTES_PER_BOND_IN_HEADER)+1, eeprom_write_offset);

        //Finished with reading the dynamic data
        status = true;

        break;
      }

      if (!(ACI_STATUS_TRANSACTION_CONTINUE == aci_evt->params.cmd_rsp.cmd_status))
      {
        //We failed the read dymanic data
        //Set the flag in the EEPROM that the contents of the EEPROM is invalid
        EEPROM.write(new_bond_index * BYTES_PER_BOND_IN_HEADER, 0x00);

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

//Process all ACI events here
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

                  //Reset the number of bonds and count from the EEPROM header
                  bond_number = 0;
                  eeprom_status = EEPROM.read(0);
                  if (eeprom_status != 0x00)
                  {
                    bond_number++;
                    //Update the write offset to the correct number
                    eeprom_write_offset = EEPROM.read(bond_number * BYTES_PER_BOND_IN_HEADER + 1);
                    if (0x00 != EEPROM.read(2))
                    {
                      bond_number++;
                      //This is needed only if we wanted to add a 3rd bond
                      eeprom_write_offset = EEPROM.read(bond_number * BYTES_PER_BOND_IN_HEADER + 1);
                    }
                    //bond 0
                    current_bond_index = 0;
                    Serial.println(F("Previous Bond present. Restoring bond 0"));
                    //We must have lost power and restarted and must restore the bonding infromation using the ACI Write Dynamic Data
                    if (ACI_STATUS_TRANSACTION_COMPLETE == bond_data_restore(&aci_state, current_bond_index))
                    {
                      Serial.println(F("Bond 0 restored successfully"));
                      current_bond_index++;
                    }
                    else
                    {
                      Serial.println(F("Bond 0 restore failed"));
                    }
                  }
                }

                // Start bonding if no bonds are available
                if (bond_number == 0)
                {
                  lib_aci_bond(180/* in seconds */, 0x0050 /* advertising interval 50ms*/);
                  Serial.println(F("Advertising started : Waiting to be connected and bonded"));
                }
                else
                {
                  //connect to an already bonded device
                  //Use lib_aci_direct_connect for faster re-connections
                  lib_aci_connect(10/* in seconds */, 0x0020 /* advertising interval 20ms*/);
                  Serial.println(F("Already bonded : Advertising started : Waiting to be connected"));
                }
              }
              break;
          }
        }
          break; //ACI Device Started Event

      case ACI_EVT_CMD_RSP:
        //If an ACI command response event comes with an error -> stop
        if ((ACI_STATUS_SUCCESS != aci_evt->params.cmd_rsp.cmd_status )
            && (ACI_CMD_READ_DYNAMIC_DATA  != aci_evt->params.cmd_rsp.cmd_opcode)
            && (ACI_CMD_WRITE_DYNAMIC_DATA != aci_evt->params.cmd_rsp.cmd_opcode))
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
          lib_aci_set_local_data(&aci_state, PIPE_DEVICE_INFORMATION_HARDWARE_REVISION_STRING_SET,
               (uint8_t *)&(aci_evt->params.cmd_rsp.params.get_device_version),
                   sizeof(aci_evt_cmd_rsp_params_get_device_version_t));
        }
        break;

      case ACI_EVT_CONNECTED:
        /*
        reset the credit available when the link gets connected
        */
        aci_state.data_credit_available = aci_state.data_credit_total;
        Serial.println(F("Evt Connected"));
        /*
         Get the Device Version of the nRF8001 and place it in the
         Hardware Revision String Characteristic of the Device Info. GATT Service
         */
        lib_aci_device_version();
        timing_change_done = false;
        Timer1stop();
        break;

      case ACI_EVT_PIPE_STATUS:
        Serial.println(F("Evt Pipe Status"));
        if (lib_aci_is_pipe_available(&aci_state, PIPE_HID_SERVICE_HID_REPORT_TX)
            && (false == timing_change_done))
        {
          lib_aci_change_timing_GAP_PPCP(); //Uses the GAP preferred timing as put in the nRFGo studio xml file-> See also in services.h
          timing_change_done = true;
          Serial.println(F("Timer started"));
          Timer1start();
        }
        break;

      case ACI_EVT_TIMING:
        Serial.print(F("Timing change received conn Interval: 0x"));
        Serial.println(aci_evt->params.timing.conn_rf_interval, HEX);
        break;

      case ACI_EVT_DATA_CREDIT:
        /**
        Bluetooth Radio ack received from the peer radio for the data packet sent.
        Multiple data packets can be acked in a single aci data credit event.
        */
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

      case ACI_EVT_BOND_STATUS:
        Serial.println(F("Evt Bond Status"));
        aci_state.bonded = aci_evt->params.bond_status.status_code;
        break;

      case ACI_EVT_DISCONNECTED:
        //Stop the timer
        Timer1stop();
        Serial.println(F("Disconnected/timed out"));
        /**
        Advertise again if the advertising timed out.
        */
        if(ACI_STATUS_ERROR_ADVT_TIMEOUT == aci_evt->params.disconnected.aci_status)
        {
          aci_status_code_t bond_restore_status;

          Serial.print(F("Previous Bond present. Restoring bond "));

          //We must have lost power and restarted and must restore the bonding infromation using the ACI Write Dynamic Data
          //Switch to the next bond
          Serial.println(current_bond_index);
          if (current_bond_index >= BONDS_MAX)
          {
            current_bond_index = 0;
          }
          bond_restore_status = bond_data_restore(&aci_state, current_bond_index);
          current_bond_index++;

          if (ACI_STATUS_TRANSACTION_COMPLETE == bond_restore_status)
          {
            Serial.println(F("Bond restored successfully"));
          }
          if (BOND_DOES_NOT_EXIST_AT_INDEX == bond_restore_status)
          {
            Serial.println(F("Bond does not exist"));
            current_bond_index = 0;
          }
        }
        else
        {
          if (ACI_BOND_STATUS_SUCCESS == aci_state.bonded) //Were bonded in the just disconnected connection.
          {
            aci_state.bonded = ACI_BOND_STATUS_FAILED;
            //Store away the dynamic data of the nRF8001 in the Flash or EEPROM of the MCU
            // so we can restore the bond information of the nRF8001 in the event of power loss
            //Update the header offset with the previous value of the eeprom_write_offset
            EEPROM.write((bond_number * BYTES_PER_BOND_IN_HEADER)+ 1, eeprom_write_offset );

            Serial.println(F("eeprom_write_offset"));
            Serial.println(eeprom_write_offset);
            Serial.println(F("bond_number"));
            Serial.println(bond_number);


            // pass the bond_number before increment to use it as an index
            if (bond_data_read_store(&aci_state, bond_number))
            {
              bond_number++;
              Serial.println(F("Dynamic Data read and stored successfully"));
            }
          }
        }

        //If a new bond is to be added, PIN 2 must tbe high or no bond exists
        if (0x01 == digitalRead(2) || (0 == bond_number))
        {
          //Start bonding
          //Less than 2 bonds. We can add one more
          if (bond_number < BONDS_MAX)
          {
            // Previous bonding failed. Try to bond again.
            lib_aci_bond(180/* in seconds */, 0x0050 /* advertising interval 50ms*/);
            Serial.println(F("Advertising started : Waiting to be connected and bonded for a new bond to be added"));
          }
        }
        else
        {
          //connect to an already bonded device
          //Use lib_aci_direct_connect for faster re-connections (advertising interval of 3.75 ms is used for directed advertising)
          lib_aci_connect(10/* in seconds */, 0x0020 /* advertising interval 20ms*/);
          Serial.println(F("Already bonded : Advertising started : Waiting to be connected"));
        }
        break;

      case ACI_EVT_DATA_RECEIVED:
        Serial.print(F("Pipe #: 0x"));
        Serial.print(aci_evt->params.data_received.rx_data.pipe_number, HEX);
        {
          int i;
          Serial.print(F(" Data(Hex) : "));
          for(i=0; i<aci_evt->len - 2; i++)
          {
            Serial.print(aci_evt->params.data_received.rx_data.aci_data[i], HEX);
            Serial.print(F(" "));
          }
        }
        Serial.println(F(""));
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

          //Reset the number of bonds and count from the EEPROM header
          bond_number = 0;
          eeprom_status = EEPROM.read(0);
          if (eeprom_status != 0x00)
          {
            bond_number++;
            //Update the write offset to the correct number
            eeprom_write_offset = EEPROM.read(bond_number * BYTES_PER_BOND_IN_HEADER + 1);
            if (0x00 != EEPROM.read(2))
            {
              bond_number++;
              //This is needed only if we wanted to add a 3rd bond
              eeprom_write_offset = EEPROM.read(bond_number * BYTES_PER_BOND_IN_HEADER + 1);
            }
            //bond 0
            current_bond_index = 0;
            Serial.println(F("Previous Bond present. Restoring bond 0"));
            //We must have lost power and restarted and must restore the bonding infromation using the ACI Write Dynamic Data
            if (ACI_STATUS_TRANSACTION_COMPLETE == bond_data_restore(&aci_state, current_bond_index))
            {
              Serial.println(F("Bond 0 restored successfully"));
              current_bond_index++;
            }
            else
            {
              Serial.println(F("Bond 0 restore failed"));
            }
          }
        }

        // Start bonding if no bonds are available
        if (bond_number == 0)
        {
          lib_aci_bond(180/* in seconds */, 0x0050 /* advertising interval 50ms*/);
          Serial.println(F("Advertising started : Waiting to be connected and bonded"));
        }
        else
        {
          //connect to an already bonded device
          //Use lib_aci_direct_connect for faster re-connections
          lib_aci_connect(10/* in seconds */, 0x0020 /* advertising interval 20ms*/);
          Serial.println(F("Already bonded : Advertising started : Waiting to be connected"));
        }
      break;
    }
  }
  else
  {
    //Serial.println(F("No ACI Events available"));
    // No event in the ACI Event queue
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

/*
This is called only once after a reset of the AVR
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

  /*
  Tell the ACI library, the MCU to nRF8001 pin connections.
  The Active pin is optional and can be marked UNUSED
  */
  aci_state.aci_pins.board_name = BOARD_DEFAULT; //See board.h for details REDBEARLAB_SHIELD_V1_1
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

  //Initialize the state variables
  aci_state.bonded   = ACI_BOND_STATUS_FAILED;
  disconnect_started = false;

  pinMode(2, INPUT); //Pin #2 on Arduino -> Bonding pin: Connect to 3.3v to start bonding
  pinMode(6, INPUT); //Pin #6 on Arduino -> PAIRING CLEAR pin: Connect to 3.3v to clear the stored bonding information

  if (0x01 == digitalRead(6))
  {
    //Clear the pairing
    Serial.println(F("Pairing cleared. Remove the wire on Pin 6 and reset the board for normal operation."));
    //Address. Value
    EEPROM.write(0, 0);
    EEPROM.write(1, 0);
    EEPROM.write(2, 0);
    EEPROM.write(3, 0);
    while(1) {};
  }
}

/* This is like a main() { while(1) { loop() } }
*/
void loop(void)
{

  aci_loop();

  /*
  Method for sending HID Reports
  */
  if (lib_aci_is_pipe_available(&aci_state, PIPE_HID_SERVICE_HID_REPORT_TX)
      && (aci_state.data_credit_available == 2)
      && (1 == timer1_f) )
  {
    timer1_f = 0;
    keypressA[2] = 0x04;
    lib_aci_send_data(PIPE_HID_SERVICE_HID_REPORT_TX, &keypressA[0], 8);
    aci_state.data_credit_available--;
    keypressA[2] = 0x00;
    lib_aci_send_data(PIPE_HID_SERVICE_HID_REPORT_TX, &keypressA[0], 8);
    aci_state.data_credit_available--;
  }
  
  if (0x01 == digitalRead(2) && (disconnect_started == false))
  {
    //Disconnect the link by ACI Disconnect
    Serial.println(F("Disconnect Started"));
    lib_aci_disconnect(&aci_state, ACI_REASON_TERMINATE);
    disconnect_started = true;
  }

}

