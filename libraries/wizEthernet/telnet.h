//telnet.h

/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011 Dave McCoy.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/



#include "wiz820io.h"
#include "socket.h"
#include "abst_wiz.h"
#include "wiz_defines.h"
#include "wirish.h"


//Telnet
#define TELNET_PROMPT "maple_tn>"
#define TELNET_USERNAME "maple"
#define TELNET_PASSWORD "1234"

//telnet defines
#define close_state 0
#define ready_state 1
#define connected_state 2

#define IPPORT_TELNET 23            // Telnet port
#define LINELEN 400
#define BUF_SIZE 100

#define USERNAME 1
#define	PASSWORD 2
#define	LOGIN 3
#define	LOGOUT 4

/* Telnet Commands */
#define	IAC 0xFF                    // Interpret as command
#define WILL 0xFB
#define WONT 0xFC
#define DO 0xFD
#define DONT 0xFE 
/* Telnet Commands end */

/* Telnet options */
#define NOPTIONS 6

#define TN_TRANSMIT_BINARY 0	    // TelNet transmit binary
#define TN_ECHO 1
#define TN_SUPPRESS_GA 3            // Supress Go Ahead
#define TN_STATUS 5
#define TN_TIMING_MARK 6
#define EXOPL 0xff	            // EXtended OPtion List
#define TN_TERMINAL_TYPE 0x18
#define TN_NE_WIN_SIZE 0x1f         // TelNet Negotiate Window SIZE
#define TN_ENVIRONMENT 0x24
#define TN_NEW_ENVIRONMENT 0x27
#define TN_NAOLFD 16


#define TF_MAX 10
#define TF_NAME_SIZE 20
#define TF_OUT_BUF_SIZE 40

typedef void (*user_func_t) (const char * args, const void * user_data, const char *out_buffer);

typedef struct _telnet_commands_t{
	const char *name;
	const char *description;
	user_func_t function;
	const void * user_data;
} telnet_commands_t;


//inherit from abst_wiz in order to recieve interrupts
class Telnet: abst_wiz {
	private:

	wiz820io *wiz;
	Socket socket;
	HardwareSerial *ser;

	char *telnet_ID;
	char *telnet_PW;

	uint8 user_name[BUF_SIZE];
	uint8 user_password[BUF_SIZE];
	char buf[LINELEN];
	char data_buf[BUF_SIZE];
	char prbuf[BUF_SIZE];

	uint8 remote[NOPTIONS];

	uint16 buf_index;
	uint8 sock_state;
	uint8 user_state;

	uint8 remote_ip[4];
	uint16 remote_port;

	telnet_commands_t telnet_commands[TF_MAX];
	int command_count;

	public:
	//support for the IDE
	Telnet();
	//default constructor with port 23
	Telnet(wiz820io *wiz, HardwareSerial *ser);
	//default contructor with alternative port
	Telnet(wiz820io *wiz, uint16 port, HardwareSerial *ser);

	void begin(wiz820io *wiz, HardwareSerial *ser);
	void begin(wiz820io *wiz, uint16 port, HardwareSerial *ser);

	void periodic();

	//telnet commands
	void send_IAC(uint8 r1, uint8 r2);
	void init_telopts();
	void input();
	void will_opt(uint16 opt);
	void wont_opt(uint16 opt);
	void do_opt(uint16 opt);
	void dont_opt(uint16 opt);
	void process_command();
	void login();

	void add_command(const char * name, const char * description, user_func_t function, const void *user_data);

};
