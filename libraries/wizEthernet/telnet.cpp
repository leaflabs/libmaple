//telnet.cpp

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




#include "telnet.h"
#include "wirish.h"
#include "stdio.h"
#include "string.h"
#include "stdbool.h"
#include <ctype.h>


#define TN_DEBUG false


enum tel_cmd {
  HELP_CMD,
  EXIT_CMD  
};

// Command table
const char *commands[] = {
  "help",
  "exit",
  NULL
};

// Telnet options
const char *tel_options[] = {
	"Transmit Binary",
    "Echo",
	"",
	"Suppress Go Ahead",
	"",
	"Status",
	"Timing Mark"
};

//empty constructor for the IDE
Telnet::Telnet(){
}
Telnet::Telnet(wiz820io *wiz, HardwareSerial *ser){
	Telnet(wiz, IPPORT_TELNET, ser);
}
	
Telnet::Telnet(wiz820io *wiz, uint16 port, HardwareSerial *ser){
	ser->println("In Telnet constructor");
	this->wiz = wiz;
	this->ser = ser;
	command_count = 0;


	socket.begin(wiz, wiz->get_available_socket_index(), SOCK_MR_TCP, IPPORT_TELNET, 0x00);
	//socket.set_remote_ip(remote_ip);
	//socket.set_remote_port(port);
	//socket.close();
	if (socket.listen()){
		ser->println("socket opened for listening");
	}
	buf_index = 0;
	user_state = USERNAME;
	sock_state = ready_state;
	telnet_ID = strdup(TELNET_USERNAME);
	telnet_PW = strdup(TELNET_PASSWORD);

	ser->println("opened telnet device");


}

void Telnet::begin(wiz820io *wiz, HardwareSerial *ser){
	begin(wiz, IPPORT_TELNET, ser);
}
void Telnet::begin(wiz820io *wiz, uint16 port, HardwareSerial *ser){
	this->wiz = wiz;
	this->ser = ser;
	command_count = 0;


	socket.begin(wiz, wiz->get_available_socket_index(), SOCK_MR_TCP, IPPORT_TELNET, 0x00);
	//socket.set_remote_ip(remote_ip);
	//socket.set_remote_port(port);
	//socket.close();
	socket.listen();
	buf_index = 0;
	user_state = USERNAME;
	sock_state = ready_state;
	telnet_ID = strdup(TELNET_USERNAME);
	telnet_PW = strdup(TELNET_PASSWORD);

	ser->println("opened telnet device");

}




void Telnet::periodic(){
	switch(socket.get_status()){
		case SOCK_ESTABLISHED:
			//if (TN_DEBUG) ser->println("Socket established");
			if (sock_state == ready_state){
				snprintf(&prbuf[0], BUF_SIZE, "\r\nTelnet server established in socket index: %d", socket.get_socket_index());
				if (TN_DEBUG) ser->print(&prbuf[0]);
				init_telopts();
				sock_state = connected_state;
				snprintf (&buf[0], BUF_SIZE, "Welcome to Telnet\r\nID:");
				socket.send((uint8 const *)buf, strlen(buf), false);
			}
			if (socket.get_read_count() > 0){
				input();
			}
			break;
		case SOCK_CLOSE_WAIT:
			if (TN_DEBUG) ser->print("\r\nSocket ");
			snprintf(&prbuf[0], BUF_SIZE, "\r\nSocket %d: CLOSE_WAIT", socket.get_socket_index());
			if (TN_DEBUG) ser->print(&prbuf[0]);
			socket.disconnect();
			break;
		case SOCK_CLOSED:
			//ser->println("closed");
			if (sock_state == close_state){
				ser->print("\r\n---------------------------\r\n");
				ser->print("\r\nW5200 Maple TELNET server start!");
				sock_state = ready_state;
			}

			if (socket.listen()){
				snprintf (&prbuf[0], BUF_SIZE, "\r\nSocket %d : LISTEN\r\n", socket.get_socket_index());	
				ser->print(&prbuf[0]);
				user_state = USERNAME;
				sock_state = ready_state;
				delay(100);
			}
			else {
				//ser->println("Failed to put socket in listen mode");
				socket.close();
				if (TN_DEBUG) ser->print(".");
			}

			break;
	}
}

//telnet commands
void Telnet::send_IAC(uint8 r1, uint8 r2){
	switch(r1){
		case WILL:
			if (TN_DEBUG) ser->print("sent : will");
			break;
		case WONT:
			if (TN_DEBUG) ser->print("send : wont");
			break;
		case DO:
			if (TN_DEBUG) ser->print("send : do");
			break;
		case DONT:
			if (TN_DEBUG) ser->print("send : dont");
			break;

		case IAC:
			break;
	}

	if (r2 <= NOPTIONS){
		snprintf(&prbuf[0], BUF_SIZE, "%s\r\n", tel_options[r2]);
		if (TN_DEBUG) ser->print(&prbuf[0]);
	}
	else {
		snprintf(&prbuf[0], BUF_SIZE, "%u\r\n", r2);
		if (TN_DEBUG) ser->print(&prbuf[0]);
	}
	snprintf (&buf[0], BUF_SIZE, "%c%c%c", IAC, r1, r2);
	//send IAC to the client
	socket.send((uint8 const *)buf, strlen(buf), false);

}

void Telnet::init_telopts(){
	//send_IAC(DO, TN_ENVIRONMENT);
	//send_IAC(WILL, TN_ECHO);
}
void Telnet::input(){
	uint8 c;
	uint8 input_command[] = TELNET_PROMPT;
	while (1){
		if (socket.get_read_count() == 0) break; //if no receive data	
		if (socket.recv(&c, 1) == 0) break; //if received 0 break
		if (user_state == LOGOUT) break; //break on logout

		//if the recieve data is not a control character
		if (c != IAC){
			data_buf[buf_index++] = c;	
			ser->print((char) c);
			if (user_state != PASSWORD){

//removed these lines so that the double characters wont be sent back to the user 
//				snprintf (prbuf, BUF_SIZE, "%c", c);
//				socket.send((uint8 const *)prbuf, strlen(prbuf), false);
			}


			if (c == '\n'){
				//ser->println("found a return");
				if (buf_index > 1){
					if (data_buf[buf_index - 2] == '\r'){
						data_buf[buf_index - 2] = '\0';
					}
					else{
						data_buf[buf_index - 1] = '\0';
					}
					if (user_state != LOGIN) login();
					else process_command();
					
					if (user_state == LOGIN){
						socket.send(input_command, strlen(TELNET_PROMPT), false);
					}
				}
				else {
					socket.send(input_command, strlen(TELNET_PROMPT), false);
				}
				buf_index = 0;
			}
			continue;
		}
		//ser->print("command ");
		if (socket.recv(&c, 1) == 0) break;
		switch (c){
			case WILL:
				if (socket.recv(&c, 1) == 0) break;
				//ser->print("WILL:");
				//ser->println(c, HEX);
				will_opt(c);
				break;
			case WONT:
				if (socket.recv(&c, 1) == 0) break;
				//ser->print("WONT:");
				//ser->println(c, HEX);
				wont_opt(c);
				break;
			case DO:
				if (socket.recv(&c, 1) == 0) break;
				//ser->print("DO:");
				//ser->println(c, HEX);
				do_opt(c);
				break;
			case DONT:
				if (socket.recv(&c, 1) == 0) break;
				//ser->print("DONT:");
				//ser->println(c, HEX);
				dont_opt(c);
				break;
			case IAC:
				break;
		}
		break;
	}
}
void Telnet::will_opt(uint16 opt){
	int ack;
	//ser->print("recv: will ");
	if (opt <= NOPTIONS){
		snprintf(&prbuf[0], BUF_SIZE, "%s\r\n", tel_options[opt]);
		if (TN_DEBUG) ser->print(&prbuf[0]);
	}
	else {
		snprintf(&prbuf[0], BUF_SIZE, "%u\r\n", opt);
		if (TN_DEBUG) ser->print(&prbuf[0]);
	}

	switch (opt){
		case TN_TRANSMIT_BINARY:
		case TN_ECHO:
//		case TN_NAOLFD:
		case TN_SUPPRESS_GA:
			ack = DO;
			break;
		default:
			//ser->print("not recognized command: ");
			//ser->println(opt, HEX);

			ack = DONT;
			break;
	}
	send_IAC(ack, opt);
}
void Telnet::wont_opt(uint16 opt){
	//ser->print("recv: wont ");
	if (opt <= NOPTIONS){
		snprintf(&prbuf[0], BUF_SIZE, "%s\r\n", tel_options[opt]);
		if (TN_DEBUG) ser->print(&prbuf[0]);
	}

	switch(opt){
		case TN_TRANSMIT_BINARY:
		case TN_ECHO:
		case TN_SUPPRESS_GA:
			if (remote[opt] == 0){
				remote[opt] = 1;
				send_IAC(DONT, opt);
			}
			break;
/*
		case TN_NAOLFD:
			ser->println("wont do line feed control");
			lf_flag = false;	
			break;
*/
		default:
			//ser->print("not recognized command: ");
			//ser->println(opt, HEX);
			break;
	}

}
void Telnet::do_opt(uint16 opt){
	//ser->print("recv: do ");
	if (opt <= NOPTIONS){
		snprintf(&prbuf[0], BUF_SIZE, "%s\r\n", tel_options[opt]);
		if (TN_DEBUG) ser->print(&prbuf[0]);
	}

	switch (opt){
		case TN_SUPPRESS_GA:
			send_IAC(WILL, opt);
			break;
		case TN_ECHO:
			snprintf (buf, BUF_SIZE, "Welcome!\r\nID : ");
			socket.send((uint8 const *)buf, strlen(buf), false);
			break;
		default:
			//ser->print("not recognized command: ");
			//ser->println(opt, HEX);
			send_IAC(WONT, opt);
			break;
	}

}
void Telnet::dont_opt(uint16 opt){
	//ser->print("recv: dont ");
	if (opt <= NOPTIONS){
		snprintf(&prbuf[0], BUF_SIZE, "%s\r\n", tel_options[opt]);
		if (TN_DEBUG) ser->print(&prbuf[0]);
	}

	switch (opt){
		case TN_TRANSMIT_BINARY:
		case TN_ECHO:
		case TN_SUPPRESS_GA:
			if (remote[opt] == 0){
				remote[opt] = 1;
			}
			break;
		default:
			//ser->print("not recognized command: ");
			//ser->println(opt, HEX);
			break;
	}

}
void Telnet::process_command(){
	const char **cmdp;
	char *cp;
	char user_cp[TF_NAME_SIZE];
	int i = 0;
	int j = 0;
	int name_len;
	char out_buffer[TF_OUT_BUF_SIZE];


	const char *help = { "HELP: Show all available commands\r\nEXIT: Exit from W5200 maple TELNET server\r\n" };

	for (cp = data_buf; *cp != '\0'; cp++){
		*cp = tolower(*cp);
	}
	if (*data_buf != '\0'){
		for (cmdp = commands; *cmdp != NULL; cmdp++){
			if (strncmp ( *cmdp, data_buf, strlen(*cmdp)) == 0) break;
		}
		if (*cmdp == NULL){
			//didn't find one of the default commands
			//check the user commands
			for (i = 0; i < command_count; i++){
				name_len = strlen(telnet_commands[i].name);
				for(j = 0; j < name_len; j++){
					user_cp[j] = tolower(telnet_commands[i].name[j]);
				}
				if (TN_DEBUG) ser->print("comparing: ");
				if (TN_DEBUG) ser->print(user_cp);
				if (TN_DEBUG) ser->print(" with ");
				if (TN_DEBUG) ser->println(data_buf);
				if (strncmp (user_cp, data_buf, name_len) == 0){
					if (TN_DEBUG) ser->print("Found: ");
					if (TN_DEBUG) ser->println(user_cp);
					memset(&out_buffer[0], 0, TF_OUT_BUF_SIZE);
					telnet_commands[i].function(&data_buf[name_len], telnet_commands[i].user_data, &out_buffer[0]);
					if (strlen(&out_buffer[0]) > 0){
						socket.send((uint8 const*)&out_buffer[0], strlen(&out_buffer[0]), false);	
					}
					if (TN_DEBUG) ser->println("executed user command");
					return;
				}
			}
		}
		if (*cmdp == NULL){
			if (TN_DEBUG) ser->print("unrecognized command\r\n");
			snprintf (buf, BUF_SIZE, "%s : BAD command\r\n", data_buf);
			socket.send((uint8 const *)buf, strlen(buf), false);
			return;
		}
		switch (cmdp - commands){
			case HELP_CMD:
				if (TN_DEBUG) ser->println("HELP_CMD\r\n");
				snprintf (buf, BUF_SIZE, help);
				socket.send((uint8 const *)buf, strlen(buf), false);
				for (i = 0; i < command_count; i++){
					snprintf (buf, BUF_SIZE, "%s : %s\r\n", telnet_commands[i].name, telnet_commands[i].description);
					socket.send((uint8 const *)buf, strlen(buf), false);
				}
				break;
			case EXIT_CMD:
				if (TN_DEBUG) ser->println("Exit telnet");
				snprintf (buf, BUF_SIZE, "EXIT command\r\nGood Bye!\r\n Logout from W5200 maple telnet\r\n");
				socket.send((uint8 const *)buf, strlen(buf), false);
				user_state = LOGOUT;
				socket.close();
				sock_state = close_state;
				break;
			default:
				break;
		}
	}
}
void Telnet::login(){
	int i = 0;
//	ser->println("in login");
	if (user_state == USERNAME){
		//ser->println("got to password state");
		snprintf((char *) user_name, BUF_SIZE, data_buf);
		snprintf (buf, BUF_SIZE, "PASSWORD : ");			
		socket.send((uint8 const *)buf, strlen(buf), false);
		user_state = PASSWORD;
		return;
	}
	else if (user_state == PASSWORD){
		snprintf((char *) user_password, BUF_SIZE, data_buf);	
		//check client ID and password
		if (!(strcmp((char const *)user_name, (char const *)telnet_ID)) &&
			!(strcmp((char const *)user_password, (char const *)telnet_PW))){
			snprintf (buf, BUF_SIZE, "\r\n=============================\r\n");	
			socket.send((uint8 const *)buf, strlen(buf), false);
			snprintf (buf, BUF_SIZE, "Successfully connected!\r\n");
			socket.send((uint8 const *)buf, strlen(buf), false);
			snprintf (buf, BUF_SIZE, "Implemented Commands: \r\n");
			socket.send((uint8 const *)buf, strlen(buf), false);
			snprintf (buf, BUF_SIZE, "HELP\r\n");
			socket.send((uint8 const *)buf, strlen(buf), false);
			snprintf (buf, BUF_SIZE, "EXIT\r\n");
			socket.send((uint8 const *)buf, strlen(buf), false);
			//write out all the user implemneted commands
			for (i = 0; i < command_count; i++){
				if (TN_DEBUG) ser->println(telnet_commands[i].name);
				snprintf (buf, BUF_SIZE, "%s\r\n", telnet_commands[i].name);
				socket.send((uint8 const *)buf, strlen(buf), false);
			}

			snprintf (buf, BUF_SIZE, "=============================\r\n");
			socket.send((uint8 const *)buf, strlen(buf), false);
			user_state = LOGIN;
			return;
		}
		else {
			socket.send((uint8 const *)buf, strlen(buf), false);
			snprintf (buf, BUF_SIZE, "\r\nID or Password incorrect!\r\n");
			socket.send((uint8 const *)buf, strlen(buf), false);
			snprintf (buf, BUF_SIZE, "ID : ");
			socket.send((uint8 const *)buf, strlen(buf), false);
			user_state = USERNAME;
			return;
		}
	}
}

void Telnet::add_command(const char * name, const char * description, user_func_t function, const void * user_data){
	this->telnet_commands[command_count].name = strdup(name);	
	this->telnet_commands[command_count].description = strdup(description);
	this->telnet_commands[command_count].function = function;
	this->telnet_commands[command_count].user_data = user_data;

	if (TN_DEBUG) ser->print("Added: ");
	if (TN_DEBUG) ser->print(name);
	if (TN_DEBUG) ser->println(" to function list");

	command_count++;
}

