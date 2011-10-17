//socket.cpp

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



#include "socket.h"
#include "string.h"

#define SK_DEBUG false


//constructor
Socket::Socket(){
}
Socket::Socket(wiz820io *wiz, uint8 Socket_index, uint8 protocol, uint16 port, uint8 flag){

	//set all the class variables
	this->wiz = wiz;
	this->Socket_index = Socket_index;
	this->Socket_base = CH_BASE + (CH_SIZE * Socket_index);

	//check if user selected a valid protocol
	if ((protocol == SOCK_MR_TCP) || \
		(protocol == SOCK_MR_UDP) || \
		(protocol == SOCK_MR_IPRAW) || \
		(protocol == SOCK_MR_MACRAW) || \
		(protocol == SOCK_MR_PPPOE)){
		//protocol is cool

		//reset the current Socket
		close();
		set_mode(protocol | flag);
		if (port != 0){
			set_local_port(port);
		}
		else{
			//grab a local port from wiz820io
			set_local_port(wiz->get_a_local_port());
		}
		//open up the socket
		set_control_reg(SOCK_CR_OPEN);
		//wait for wiz to set control reg to zero (ack)
		while (get_control_reg()){}
		
	}
	else {
		 //Serial3.println("Unknown protocol");
		//unknown protocol
//XXX: need a way to tell the user something went wrong
		return;
	}
}

//destructor
Socket::~Socket(){
	//close the Socket
	 //Serial3.println("Socket destroyed");
	close();
}

//initialization

void Socket::close(){
	set_control_reg(SOCK_CR_CLOSE);
	//wait until the command is finished
	while (this->get_control_reg()){}
	//clear interrupt register
	set_interrupts(0xFF);
}

void Socket::begin(wiz820io *wiz, uint8 Socket_index, uint8 protocol, uint16 port, uint8 flag){

	//set all the class variables
	this->wiz = wiz;
	this->Socket_index = Socket_index;
	this->Socket_base = CH_BASE + (CH_SIZE * Socket_index);

	//check if user selected a valid protocol
	if ((protocol == SOCK_MR_TCP) || \
		(protocol == SOCK_MR_UDP) || \
		(protocol == SOCK_MR_IPRAW) || \
		(protocol == SOCK_MR_MACRAW) || \
		(protocol == SOCK_MR_PPPOE)){
		//protocol is cool

		//reset the current Socket
		close();
		set_mode(protocol | flag);
		if (port != 0){
			set_local_port(port);
		}
		else{
			//grab a local port from wiz820io
			set_local_port(wiz->get_a_local_port());
		}
		//open up the socket
		set_control_reg(SOCK_CR_OPEN);
		//wait for wiz to set control reg to zero (ack)
		while (get_control_reg()){}
		
	}
	else {
		 //Serial3.println("Unknown protocol");
		//unknown protocol
//XXX: need a way to tell the user something went wrong
		return;
	}

}

//call this connect if the remote ip, and port were set previously
uint8 Socket::connect(){
	uint8 retval = 0;
	uint8 remote_ip[4];
	uint16 remote_port;
	//Serial3.println("in connect");
	remote_port = get_remote_port();
	get_remote_ip(&remote_ip[0]);
	 //Serial3.println("got comm ports");

	if (
		((remote_ip[0] == 0xFF) && (remote_ip[1] == 0xFF) && (remote_ip[2] == 0xFF) && (remote_ip[3] == 0xFF)) ||
		((remote_ip[0] == 0x00) && (remote_ip[1] == 0x00) && (remote_ip[2] == 0x00) && (remote_ip[3] == 0x00)) ||
		(remote_port == 0x00)){
			retval = 0;
			//Serial3.println("Invalid port or IP");
			//Serial3.print("Remote IP: ");
			//Serial3.print(remote_ip[0], DEC);
			//Serial3.print(".");
			//Serial3.print(remote_ip[1], DEC);
			//Serial3.print(".");
			//Serial3.print(remote_ip[2], DEC);
			//Serial3.print(".");
			//Serial3.println(remote_ip[3], DEC);
			//Serial3.print("Remote Port: ");
			//Serial3.println(remote_port, DEC);
	}
	else {
		retval = 1;
		//get the remote ip and the remote port
		set_control_reg(SOCK_CR_CONNECT);
		//wait until the command is finished
		while (get_control_reg()){}
	}
	 //Serial3.println("Finished!");
	return retval;
}
uint8 Socket::connect(uint8 * addr, uint16 port){
	 //Serial3.println("in connect with addr, and port");

	 //Serial3.print("base: ");
	 //Serial3.println(Socket_base, HEX);

	 //Serial3.print("Socket addr: ");
	 //Serial3.println((uint32) this, HEX);
	 //Serial3.print("Local port: ");
	uint16 local_port = get_local_port();
	Serial2.println(local_port, DEC);
	

	uint8 remote_ip[4];
	uint16 remote_port = 0x00;

	uint8 retval = 0;
	if (
		((addr[0] == 0xFF) && (addr[1] == 0xFF) && (addr[2] == 0xFF) && (addr[3] == 0xFF)) ||
		((addr[0] == 0x00) && (addr[1] == 0x00) && (addr[2] == 0x00) && (addr[3] == 0x00)) ||
		(port == 0x00)){
			retval = 0;
	}
	else {

		retval = 1;
		set_remote_ip(addr);
		set_remote_port(port);

		get_remote_ip(&remote_ip[0]);
		remote_port = get_remote_port();

		 //Serial3.print("Remote IP: ");
		 //Serial3.print(remote_ip[0], DEC);
		 //Serial3.print(".");
		 //Serial3.print(remote_ip[1], DEC);
		 //Serial3.print(".");
		 //Serial3.print(remote_ip[2], DEC);
		 //Serial3.print(".");
		 //Serial3.println(remote_ip[3], DEC);
		 //Serial3.print("Remote Port: ");
		 //Serial3.println(remote_port, DEC);

		this->set_control_reg(SOCK_CR_CONNECT);
		//wait until the command is finished
		while (this->get_control_reg()){}
	}
	return retval;	
}
void Socket::disconnect(){
	this->set_control_reg(SOCK_CR_DISCON);
	//wait until the command is finished
	while (this->get_control_reg()){}

}
uint8 Socket::listen(){
	uint8 retval = 0;
	if (get_status() == SOCK_CLOSED){
		//try and re-open the socket
		set_control_reg(SOCK_CR_OPEN);
		while (get_control_reg()){}
	}
	if (get_status() == SOCK_INIT){
		set_control_reg(SOCK_CR_LISTEN);
		//wait for the command to process
		while (get_control_reg()){}
		retval = 1;
	}
	else {
		retval = 0;
	}
	return retval;
}
uint16 Socket::send(const uint8 * buf, uint16 len, bool retry){
	uint8 status = 0;
	uint16 retval = 0;
	uint16 freesize = 0;
	uint16 txrd;
	uint16 txrd_before_send;
	if (retry);
	else{
		if (len > wiz->get_tx_buffer_size(Socket_index)) {
			retval = wiz->get_tx_buffer_size(Socket_index);
		}
		else {
			retval = len;
		}

		//whenever the buffer is free start
		do {
			freesize = this->get_tx_free();
			status = this->get_status();
			if ((status != SOCK_ESTABLISHED) &&
				(status != SOCK_CLOSE_WAIT)){
				retval = 0;
				break;
			}
		} while(freesize < retval);
		//copy data to the chip
		this->send_data_processing((uint8 *) buf, retval);
	}

	txrd_before_send = this->wiz->read(this->Socket_base + SOCK_TX_RD0);  
	txrd_before_send = (txrd_before_send << 8) + this->wiz->read(this->Socket_base + SOCK_TX_RD0);

	this->set_control_reg(SOCK_CR_SEND);
	//wait for the command to process
	while (this->get_control_reg()){}

	while ((this->get_status() & SOCK_IR_SEND_OK) != SOCK_IR_SEND_OK){
		if (this->get_status() == SOCK_CLOSED){
			this->close();
			retval = 0;
		}
	}
	set_interrupts(SOCK_IR_SEND_OK);
	txrd = wiz->read(this->Socket_base + SOCK_TX_RD0);
	txrd = (txrd << 8) + this->wiz->read(this->Socket_base + SOCK_TX_RD0 + 1);

	if (txrd + txrd_before_send){
		retval = txrd - txrd_before_send;
	}
	else {
		retval = (0xFFFF - txrd_before_send) + txrd + 1;
	}
	return retval;
}
uint16 Socket::recv(uint8 *buf, uint16 len){
	uint16 retval = 0;
	memset((char *)buf, 0, len);
	if (len > 0){
		read_data_processing(buf, len);
		set_control_reg(SOCK_CR_RECV);
		//wait for the command to process
		while (this->get_control_reg()){}
		retval = len;
	}
//	 //Serial3.print("length read: ");
//	 //Serial3.println(retval, DEC);
	return retval;
}
uint16 Socket::sendto (uint8 *buf, uint16 len, uint8 * addr, uint16 port){
	uint16 retval = 0;
	if (len > this->wiz->get_tx_buffer_size(this->Socket_index)){
		retval = this->wiz->get_tx_buffer_size(this->Socket_index);
	}
	else {
		retval = len;
	}

	if(
		((addr[0] == 0x00) && (addr[1] == 0x00) && (addr[2] == 0x00) && (addr[3] == 0x00)) ||
		((port == 0x00)) || (retval == 0)
	){
		retval = 0;
		//FAIL!
	}
	else {
		this->set_remote_ip(addr);
		this->set_remote_port(port);
		this->set_control_reg(SOCK_CR_SEND);
		//wait for the command to process
		while (this->get_control_reg()){}

		while ((this->get_interrupts() & SOCK_IR_SEND_OK) != SOCK_IR_SEND_OK){
			if (this->get_interrupts() & SOCK_IR_TIMEOUT){
				//SEND FAIL!!
				this->set_interrupts(SOCK_IR_SEND_OK | SOCK_IR_TIMEOUT);
				return 0;
			}
		}
		this->set_interrupts(SOCK_IR_SEND_OK);

	}
	return retval;
}
uint16 Socket::recvfrom (uint8 *buf, uint16 len, uint8 *addr, uint16 *port){
	uint8 head[8];
	uint16 data_len = 0;
	uint16 ptr = 0;

	if (len > 0){
		ptr = wiz->read(Socket_base + SOCK_RX_RD0);
		ptr = (ptr << 8) + wiz->read(Socket_base + SOCK_RX_RD0 + 1);
		switch (get_mode() & 0x07){
			case (SOCK_MR_UDP):
				this->read_data((uint8 *) ptr, &head[0], 0x08);
				ptr += 8;
				//read remote IP address, and port
				addr[0] = head[0];
				addr[1] = head[1];
				addr[2] = head[2];
				addr[3] = head[3];
				*port = head[4];
				*port = (*port << 8) + head[5];
				data_len = head[6];
				data_len = (data_len << 8) + head[7];

				//UDP message arrived from the above port, and address
				read_data((uint8 *)ptr, buf, data_len);
				ptr += data_len;
				this->wiz->write(this->Socket_base + SOCK_RX_RD0, (uint8) ((ptr >> 8) & 0x00FF));
				this->wiz->write(this->Socket_base + SOCK_RX_RD0 + 1, (uint8) (ptr & 0x00FF));
			break;
			case (SOCK_MR_IPRAW):
				wiz->read(ptr, (char *)&head[0], 0x06);
				ptr += 6;
				addr[0] = head[0];
				addr[1] = head[1];
				addr[2] = head[2];
				addr[3] = head[3];
				data_len = head[4];
				data_len = (data_len << 8) + head[5];

				//IPRAW MESSAGE RECEIVED

				read_data((uint8 *) ptr, buf, data_len);
				ptr += data_len;
				this->wiz->write(this->Socket_base + SOCK_RX_RD0, (uint8) ((ptr >> 8) & 0x00FF));
				this->wiz->write(this->Socket_base + SOCK_RX_RD0 + 1, (uint8) (ptr & 0x00FF));


			break;
			case (SOCK_MR_MACRAW):
				read_data((uint8 *)ptr, &head[0], 2);
				ptr += 2;
				data_len = head[0];
				data_len = (data_len << 8) + head[1];
				this->wiz->write(this->Socket_base + SOCK_RX_RD0, (uint8) ((ptr >> 8) & 0x00FF));
				this->wiz->write(this->Socket_base + SOCK_RX_RD0 + 1, (uint8) (ptr & 0x00FF));


			break;
			default:
			break;
		}
		this->set_control_reg(SOCK_CR_RECV);
		//wait for the command to process
		while (this->get_control_reg()){}
	}

	return data_len;
}
uint16 Socket::igmpsend(uint8 * buf, uint16 len){
	return 0;
}

//ports and ip functions
void Socket::set_local_port(uint16 port){
	wiz->write(Socket_base + SOCK_PORT0, (uint8) ((port >> 8) & 0x00FF));	
	wiz->write(Socket_base + SOCK_PORT0 + 1, (uint8) (port & 0x00FF));
}
uint16 Socket::get_local_port(){
	uint16 local_port = 0;
	local_port = wiz->read(Socket_base + SOCK_PORT0);
	local_port = (local_port << 8) + wiz->read(Socket_base + SOCK_PORT0 + 1);
	return local_port;
}
void Socket::set_remote_port(uint16 port){
	wiz->write(Socket_base + SOCK_DPORT0, (uint8) ((port >> 8) & 0x00FF));
	wiz->write(Socket_base + SOCK_DPORT0 + 1, (uint8) (port * 0x00FF));
}
uint16 Socket::get_remote_port(){
	uint16 remote_port = 0;
	remote_port = wiz->read(Socket_base + SOCK_DPORT0);
	remote_port = (remote_port << 8) + wiz->read(Socket_base + SOCK_DPORT0 + 1);
	return remote_port;
}
void Socket::set_remote_ip(uint8 * ip){
	this->wiz->write(Socket_base + SOCK_DIPR0, (char *) ip, 4);
}
void Socket::get_remote_ip(uint8 *remote_ip){
	wiz->read(Socket_base + SOCK_DIPR0, (char *) remote_ip, 4);
}
void Socket::set_remote_mac(char * mac){
	this->wiz->write(Socket_base + SOCK_DHAR0, mac, 6);
}



//private functions
void Socket::set_mode(uint8 mode){
	this->wiz->write(this->Socket_base + SOCK_MR, (uint8) mode); 
}
uint8 Socket::get_mode(){
	return this->wiz->read(this->Socket_base + SOCK_MR);
}
void Socket::set_max_segment_size(uint16 mss){
	this->wiz->write(this->Socket_base + SOCK_MSSR0, (uint8) ((mss >> 8) & 0x00FF));
	this->wiz->write(this->Socket_base + SOCK_MSSR0 + 1, (uint8) (mss & 0x00FF));
}
void Socket::set_time_to_live(uint8 ttl){
	this->wiz->write(this->Socket_base + SOCK_TTL, (uint8) ttl); 
}
void Socket::set_control_reg(uint8 data){
	this->wiz->write(this->Socket_base + SOCK_CR, (uint8) data);
}
uint8 Socket::get_control_reg(){
	//Serial3.print("Scoket control register: ");
	//Serial3.println(this->Socket_base + SOCK_CR, HEX);
	return this->wiz->read(this->Socket_base + SOCK_CR);
}
void Socket::set_protocol(uint8 data){
	this->wiz->write(this->Socket_base + SOCK_PROTO, (uint8) data);
}
void Socket::set_type_of_service(uint8 data){
	this->wiz->write(this->Socket_base + SOCK_TOS, (uint8) data);
}

/*data buffers */
uint8 Socket::get_read_mem_size(){
	return wiz->read(Socket_base + SOCK_RXMEM_SIZE);
}
uint8 Socket::get_send_mem_size(){
	return wiz->read(Socket_base + SOCK_TXMEM_SIZE);
}

uint16 Socket::get_read_count(){
	uint16 read_size = 0;
	read_size = wiz->read(Socket_base + SOCK_RX_RSR0);
	read_size = (read_size << 8) + wiz->read(Socket_base + SOCK_RX_RSR0 + 1);
	return read_size;
}
uint8 Socket::get_socket_index(){
	return Socket_index;
}

//interrupt/status
void Socket::set_interrupt_mask(uint8 mask){
	wiz->write(Socket_base + SOCK_IMR, (uint8) mask);
}
void Socket::set_interrupts(uint8 data){
	wiz->write(Socket_base + SOCK_IR, data);
}
uint8 Socket::get_interrupts(){
	return wiz->read(Socket_base + SOCK_IR);
}
uint8 Socket::get_status(){
	return wiz->read(Socket_base + SOCK_SR);
}

//data transfer functions
uint16 Socket::get_tx_free(){
	uint16 val = 0;
	uint16 val1 = 0;
	do {
		//get the free amount
		val1 = this->wiz->read(this->Socket_base + SOCK_TX_FSR0);
		val1 = (val1 << 8) + this->wiz->read(this->Socket_base + SOCK_TX_FSR0 + 1);
		//if we are not at 0, or there is some space free
		if (val1 != 0){
			//read a second time to make sure this value is stationary	
			val = wiz->read(this->Socket_base + SOCK_TX_FSR0);
			val = (val << 8) + this->wiz->read(this->Socket_base + SOCK_TX_FSR0 + 1);
		}
	} while (val != val1);
	return val;
}
uint16 Socket::get_rx_free(){
	uint16 val = 0;
	uint16 val1 = 0;
	do {
		val1 = this->wiz->read(this->Socket_base + SOCK_RX_RSR0);
		val1 = (val << 8) + this->wiz->read(this->Socket_base + SOCK_RX_RSR0 + 1);
		if (val1 != 0){
			val = this->wiz->read(this->Socket_base + SOCK_RX_RSR0);
			val = (val << 8) + this->wiz->read(this->Socket_base + SOCK_RX_RSR0 + 1);
		}
	} while (val != val1);
	return val;
}
void Socket::send_data_processing(uint8 *data, uint16 len){
	uint16 ptr;
	ptr = wiz->read(Socket_base + SOCK_TX_WR0);
	ptr = (ptr << 8) + wiz->read(Socket_base + SOCK_TX_WR0 + 1);

	write_data(data, (uint8 *) (ptr), len);
	ptr += len;

	wiz->write(Socket_base + SOCK_TX_WR0, (uint8) ((ptr >> 8) & 0x00FF));
	wiz->write(Socket_base + SOCK_TX_WR0 + 1, (uint8) (ptr & 0x00FF));

}

void Socket::read_data_processing(uint8 *data, uint16 len){
	uint16 ptr;
	ptr = wiz->read(Socket_base + SOCK_RX_RD0);
	ptr = (ptr << 8) + wiz->read(Socket_base + SOCK_RX_RD0 + 1);
	read_data((uint8 *) ptr, data, len);
	ptr += len;
	wiz->write(Socket_base + SOCK_RX_RD0, (uint8) ((ptr >> 8) & 0x00FF));
	wiz->write(Socket_base + SOCK_RX_RD0 + 1, (uint8) (ptr & 0x00FF));
}
void Socket::write_data(vuint8 *src, vuint8 *dst, uint16 len){
	uint16 size;
	uint16 dst_mask;
	uint16 dst_ptr;

	dst_mask = (uint32) dst & wiz->get_tx_buffer_mask(Socket_index);
	dst_ptr = (uint16)(wiz->get_tx_buffer_base(Socket_index) + dst_mask);

//Serial3.print("tx buffer mask: ");
//Serial3.println(wiz->get_tx_buffer_mask(Socket_index), HEX);

//Serial3.print("tx buffer base: ");
//Serial3.println(wiz->get_tx_buffer_base(Socket_index), HEX);


	if (dst_mask + len > wiz->get_tx_buffer_size(Socket_index)){
		size = wiz->get_tx_buffer_size(Socket_index) - dst_mask;
		wiz->write(dst_ptr, (char *)src, size);
		src += size;
		size = len - size;
		dst_ptr = wiz->get_tx_buffer_base(Socket_index); 
		wiz->write((uint16)dst_ptr, (char *)src, size);
	}
	else {
		//all the data will fit into the buffer	
		wiz->write((uint16)dst_ptr, (char *)src, len);
	}

}
void Socket::read_data(vuint8 *src, vuint8 *dst, uint16 len){
	uint16 size;
	uint16 src_mask;
	uint16 src_ptr;

	src_mask = (uint32)src & wiz->get_rx_buffer_mask(Socket_index);
	src_ptr = (uint16) (wiz->get_rx_buffer_base(Socket_index) + src_mask);

	if ( (src_mask + len) > wiz->get_rx_buffer_size(Socket_index)){
		size = wiz->get_rx_buffer_size(Socket_index) - src_mask;
		wiz->read(src_ptr, (char *) dst, size);
		dst += size;
		size = len - size;
		src_ptr = wiz->get_rx_buffer_base(Socket_index);
		wiz->read(src_ptr, (char *) dst, size);
	}
	else {
		wiz->read(src_ptr, (char *) dst, len);
	}
}


