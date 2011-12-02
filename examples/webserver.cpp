//main.cpp
#include "wirish.h"
#include "wiz820io.h"
#include "socket.h"
#include "telnet.h"
#include "string.h"


//char remote_ip[4] = {192, 168, 100, 1};
static char local_ip[4] = {192, 168, 100, 2};
static char gateway[4] = {192, 168, 100, 1};
static char subnet[4] = {255, 255, 255, 0};
static char mac[6] = {0x0A, 0x1B, 0x3C, 0x4D, 0x5E, 0x6F};


//simple HTML hello world
const char html_hello_world[] = \
"HTTP/1.1 200 OK\r\n\
Content-Type: text/html\r\n\
\r\n\
<html>\r\n\
<head>\r\n\
<title>baby skynet</title>\r\n\
</head>\r\n\
<body>\r\n\
<br/>\r\n\
<p align=\"center\"> \r\n\
<FONT COlOR=\"green\">M</FONT>\r\n\
<FONT COLOR=\"orange\">a</FONT>\r\n\
<FONT COLOR=\"green\">p</FONT>\r\n\
<FONT COLOR=\"yellow\">l</FONT>\r\n\
<FONT COLOR=\"red\">e</FONT>\r\n\
</p><br />\r\n\
<form name=\"input\" action=\"main\" method=\"get\">\r\n\
<p align=\"center\">\r\n\
<input type=\"text\" name=\"user_name\" /><br />\r\n\
<input type=\"submit\" value=\"search\"/>\r\n\
</p>\r\n\
</form>\r\n\
</body>\r\n\
<html>\r\n\
\r\n";


const char html_response[] = \
"HTTP/1.1 200 OK\r\n\
Content-Type: text/html\r\n\
\r\n\
<html>\r\n\
<body>\r\n\
you typed in: %s\r\n\
</body>\r\n\
</html>\r\n\
\r\n";



const char html_not_found[] = \
"HTTP/1.1 404 Not Found\r\n\
<HTML><BODY><H1>404 Not Found</H1>\r\n\
The requested URL was not found on this server.\r\n\
</BODY></HTML>\r\n\
\r\n";


// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need libmaple may fail.
__attribute__((constructor)) void premain() {
    init();
}


HardwareSPI spi2(2);


int toggle = 1;
void loop(){
    digitalWrite(BOARD_LED_PIN, toggle);
    toggle ^= 1;
   	delay(100);

}

void setup(){

	Serial3.begin(115200);
	pinMode(BOARD_BUTTON_PIN, INPUT);
    pinMode(BOARD_LED_PIN, OUTPUT);
	toggleLED();
}


int main(void){

	Socket *sock = NULL;
	setup();



	Serial3.println("Starting WizzEthernet Main Project");
	wiz820io wiz = wiz820io(&spi2);
	Serial3.println("Opened up WizzEthernet");

	//pre MAC stuff
	//set all the pins to values
	//wiz.set_interrupt_pin(9);
	//wiz.set_reset_pin(7);
	//wiz.set_power_pin(8);

	
	Serial3.println("Initializing the MAC and PHY layer");
	wiz.init_mac();
	Serial3.println("Initialized");
	
	//wiz.set_DHCP(1);

	//wiz.set_timeout_millis(6000);
	//wiz.set_timeout_retries(3);
	
	wiz.set_ip(&local_ip[0]);
	wiz.set_subnet_mask(&subnet[0]);
	wiz.set_gateway(&gateway[0]);
	wiz.set_mac_addr(&mac[0]);

	sock = new Socket(&wiz, 0, SOCK_MR_TCP, 80, 0x00);  
	if (sock->listen()){
		Serial3.println("Listen responded!");
	}

	uint8 read_length = 0;
	uint8 read_buffer[200];
	char write_buffer[500];
	char user_buffer[100];
	bool sock_opened = false;
	bool send_response = false;
	char *user_data = NULL;
	strncpy(&write_buffer[0], &html_hello_world[0], sizeof(write_buffer)); 

	while (1){
		loop();
		if (sock->get_status() == SOCK_ESTABLISHED && !sock_opened){
			Serial3.println("Socket Opened, User getting a request!");
			sock_opened = true;
		}
		if (sock_opened){
			read_length = sock->get_read_count();
			if (read_length > 0){
				user_data = NULL;
				while (read_length > 0 ){
					if (read_length > sizeof(read_buffer)){
						sock->recv(&read_buffer[0], sizeof(read_buffer));
						read_length = read_length - sizeof(read_buffer);
					}
					else {
						sock->recv(&read_buffer[0], read_length);
						read_buffer[read_length + 1] = 0;
						read_length = 0;
					}


					//Serial3.print((const char*)&read_buffer[0]);
					// treat favicon.ico
					if (strstr((const char*)&read_buffer[0], "GET /favicon") != NULL) {
							Serial3.println("Favicon");
							sock->send((const uint8 *)&html_not_found[0], sizeof(html_not_found), false);
					}
					//
					user_data = strstr((const char*)&read_buffer[0], "GET /main");
					if (user_data != NULL){
						Serial3.println();
						Serial3.println();
						Serial3.println("Got a response from a form item");
						Serial3.println();
						Serial3.println();
						sscanf(user_data, "GET /main?user_name=%s HTTP", &user_buffer[0]);
						send_response = true;
						user_data = NULL;
					}
				}

				Serial3.println();
				delay(10);
				if (send_response){
					Serial3.println("Got some data from the webpage!");
					snprintf (&write_buffer[0], sizeof(write_buffer), &html_response[0], &user_buffer[0]);

					sock->send((const uint8*)&write_buffer[0], (uint16)strlen(&write_buffer[0]), false);
					send_response = false;
				}
				else {
					sock->send((const uint8 *)&html_hello_world[0], sizeof(html_hello_world), false);
				}
				Serial3.println("Sent HTML response");
				Serial3.println("dicsonnect");
				delay(10);
				sock->disconnect();
				sock_opened = false;
				sock->listen();

                //added by jbkim
                Serial3.println("\r\nListen...");


			}
		}
	}

	return 0;
}
