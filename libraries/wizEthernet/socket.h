//socket.h

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


#ifndef __SOCKET_H__
#define __SOCKET_H__


#include "wirish.h"
#include "abst_wiz.h"
#include "wiz820io.h"



class Socket : public abst_wiz{
	private:
	
	uint8 Socket_index;
	uint16 Socket_base;
	wiz820io *wiz;


	//set control
	void set_mode(uint8 data);
	uint8 get_mode();
	void set_control_reg(uint8 data);
	uint8 get_control_reg();
	void set_protocol(uint8 data);
	void set_type_of_service(uint8 data);
	void set_max_segment_size(uint16 mss);
	void set_time_to_live(uint8 ttl);

	//status/interrupt
	void set_interrupt_mask(uint8 mask);
	uint8 get_interrupts();
	void set_interrupts(uint8 data);

	uint16 get_tx_free();
	uint16 get_rx_free();

	void send_data_processing(uint8 *data, uint16 len);
	void read_data_processing(uint8 *data, uint16 len);

	void write_data(vuint8 * src, vuint8 * dst, uint16 len);
	void read_data(vuint8 *src, vuint8 *dst, uint16 len);


	public:

	uint8 get_status();
	void set_local_port(uint16 port);
	uint16 get_local_port();
	void set_remote_port(uint16 port);
	uint16 get_remote_port();
	void set_remote_ip(uint8 * ip);
	void get_remote_ip(uint8 * remote_ip);
	void set_remote_mac(char * mac);

	//data buffers
	uint16 get_read_count();
	uint8 get_read_mem_size();
	uint8 get_send_mem_size();

	uint8 get_socket_index();


	/*	constructor, the wiz MAC needs to be initialized before anything
		There are too many variables that need to be modified
		therefore NO DEFAULT CONSTRUCTOR
	*/
	Socket(wiz820io *wiz, uint8 Socket_index, uint8 protocol, uint16 port, uint8 flag);
	Socket();


	/*
		Destructor needs to free any resources
	*/
	~Socket();

	void begin(wiz820io *wiz, uint8 Socket_index, uint8 protocol, uint16 port, uint8 flag);	

	void close();
	uint8 connect();
	uint8 connect(uint8 * addr, uint16 port);
	void disconnect();
	uint8 listen();
	uint16 send(const uint8 * buf, uint16 len, bool retry);
	uint16 recv(uint8 *buf, uint16 len);
	uint16 sendto (uint8 *buf, uint16 len, uint8 * addr, uint16 port);
	uint16 recvfrom (uint8 *buf, uint16 len, uint8 *addr, uint16 *port);

	uint16 igmpsend(uint8 * buf, uint16 len);
};

#endif
