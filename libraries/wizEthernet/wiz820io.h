//wiz820io.h

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



#ifndef __WIZ820IO_H__
#define __WIZ820IO_H__

#include "wirish.h"
#include "abst_wiz.h"


#define DEFAULT_SPI 2

#define DEFAULT_RESET_PIN 7
#define DEFAULT_POWER_PIN 8
#define DEFAULT_INTERRUPT_PIN 9


#include "wiz_defines.h"

class wiz820io {
	
	private:
	HardwareSPI *spi;

	int interrupt_pin;
	int power_pin;
	int reset_pin;
	uint8 DHCP;
	void private_initialize();


	//socket
	
	//when an interrupt happens call these base classes
	abst_wiz * sockets[MAX_SOCK_NUM];
	void initialize_socket_memory();
	
	unsigned short local_port;

	unsigned char tx_kb_size[MAX_SOCK_NUM];
	unsigned char rx_kb_size[MAX_SOCK_NUM];

	unsigned short tx_buffer_size[MAX_SOCK_NUM];
	unsigned short rx_buffer_size[MAX_SOCK_NUM];

	unsigned short tx_buffer_mask[MAX_SOCK_NUM];
	unsigned short rx_buffer_mask[MAX_SOCK_NUM];

	unsigned short tx_buffer_base[MAX_SOCK_NUM];
	unsigned short rx_buffer_base[MAX_SOCK_NUM];

	


	public:
	//Constructor
	wiz820io();
	wiz820io(HardwareSPI *spi_dev);
	wiz820io(int spi_index);

	//Destructor
	~wiz820io();

	void begin();
	void begin(HardwareSPI *spi_dev);
	void begin(int spi_index);

	//initialize wiz
	void init_mac();
	void init_mac(char * mac_addr, char * gateway, char * subnet_mask, char *ip);
	
	void set_reset_pin(int rst);
	void set_power_pin(int power);
	void set_interrupt_pin(int interrupt);


	//low level settings
	void set_ip(char * in_ip);
	void set_gateway(char * gateway);
	void set_subnet_mask(char * subnet_mask);
	void set_mac_addr(char * mac_addr);

	//send data to chip
	void write (unsigned int addr, char * buf, int len);
	void write (unsigned int addr, char val);
	char read (unsigned int addr, char * buf, int len);
	char read (unsigned int addr);


	//wiznet registers, even though these are redundant it makes things easier
	void write_register(unsigned int reg, unsigned char value);
	unsigned char read_register(unsigned int reg);


	//MAC level control
	void set_DHCP(uint8 enable);
	uint8 get_DHCP(void);

	void set_timeout_millis(unsigned int timeout);
	unsigned int get_timeout_millis(void);
	
	void set_timeout_retries(uint8 retries);
	uint8 get_timeout_retries(void);


	//socket and MAC interrupt handler
	void interrupt_handler(void);
	//registering sockets allows the MAC (this class) to call all the sockets
	void register_socket(unsigned char socket_num, abst_wiz * socket);
	void unregister_socket(unsigned char socket_num);

	unsigned short get_tx_buffer_size(unsigned char socket_num);
	unsigned short get_rx_buffer_size(unsigned char socket_num);

	unsigned short get_tx_buffer_base(unsigned char socket_num);
	unsigned short get_rx_buffer_base(unsigned char socket_num);

	unsigned short get_tx_buffer_mask(unsigned char socket_num);
	unsigned short get_rx_buffer_mask(unsigned char socket_num);
	
	
	unsigned short get_a_local_port();

	char get_available_socket_index();

};


#endif
