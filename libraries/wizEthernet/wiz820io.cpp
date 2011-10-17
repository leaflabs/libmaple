//wiz820io.cpp

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



#include "wirish.h"
#include "wiz820io.h"
#include "string.h"

static char init_ip[4] = {192, 168, 100, 2};
static char init_gw[4] = {192, 168, 100, 1};
static char init_sm[4] = {255, 255, 255, 0};
static char init_mc[6] = {0x0A, 0x1B, 0x3C, 0x4D, 0x5E, 0x6F};
//static char init_mc[6] = {0x00, 0x08, 0xDC, 0x01, 0x02, 0x03};

//default 2 Kb for all sockets
static char txsize[8] = {2, 2, 2, 2, 2, 2, 2, 2};
static char rxsize[8] = {2, 2, 2, 2, 2, 2, 2, 2};


//this is required for interrupts
static wiz820io *w = NULL;



static void wiz_interrupt (){
	w->interrupt_handler();
}


//constructors
wiz820io::wiz820io(){
//	this->spi = new HardwareSPI(DEFAULT_SPI); 
//	this->private_initialize();
}
wiz820io::wiz820io(HardwareSPI * spi_dev){
	this->spi = spi_dev;
	this->private_initialize();
}
wiz820io::wiz820io(int spi_index){
	this->spi = new HardwareSPI(DEFAULT_SPI); 
	this->private_initialize();
}

//destructor
wiz820io::~wiz820io(){
}

void wiz820io::begin(){
	this->spi = new HardwareSPI(DEFAULT_SPI); 
	this->private_initialize();
}
void wiz820io::begin(HardwareSPI * spi_dev){
	this->spi = spi_dev;
	this->private_initialize();
}
void wiz820io::begin(int spi_index){
	this->spi = new HardwareSPI(DEFAULT_SPI); 
	this->private_initialize();
}


//private pin initialization
void wiz820io::private_initialize(){
	
	int i = 0;
	this->local_port = 1000;

	//set all the control pins up
	this->set_interrupt_pin(DEFAULT_INTERRUPT_PIN);
	this->set_reset_pin(DEFAULT_RESET_PIN);
	this->set_power_pin(DEFAULT_POWER_PIN);

	//initialize all sockets to share the 16Kb of memory space evenly (all 2's)
	for (i = 0; i < MAX_SOCK_NUM; i++){
		this->tx_kb_size[i] = txsize[i];
		this->rx_kb_size[i] = rxsize[i];
	}

	//set this global variable so that we can call interrupts
	w = this;
	
	//initialize all the sockets to NULL
	for (i = 0; i < MAX_SOCK_NUM; i++){
		sockets[i] = NULL;
	}

}

//initialization
void wiz820io::init_mac(){
	this->init_mac(&init_mc[0], &init_ip[0], &init_sm[0], &init_gw[0]);
}
void wiz820io::init_mac(char *mac_addr, char *ip, char *subnet_mask, char *gateway){


	//initialize all the pins
	pinMode(interrupt_pin, INPUT);
	pinMode(power_pin, OUTPUT);
	pinMode(reset_pin, OUTPUT);


	this->spi->begin(SPI_140_625KHZ, MSBFIRST, SPI_MODE_0);

	pinMode(this->spi->nssPin(), OUTPUT);
	digitalWrite(this->spi->nssPin(), HIGH);

	//set the chip to be in normal power mode
	digitalWrite(power_pin, LOW);
	
	
	//send a reset signal to the chip
	digitalWrite(reset_pin, LOW);
	delayMicroseconds(10);
	digitalWrite(reset_pin, HIGH);
	delay(150);



	write_register(MR, 0x80);

	write_register(IMR, 0xA0);

	this->set_mac_addr(mac_addr);
	this->set_gateway(gateway);
	this->set_subnet_mask(subnet_mask);
	this->set_ip(ip);


	set_timeout_millis(6000);
	set_timeout_retries(3);
	

	//setup the memory for the sockets
	this->initialize_socket_memory();
}

	


void wiz820io::set_ip(char *in_ip){
	write(0x0F, in_ip, 4);
}

void wiz820io::set_gateway(char *gateway){
	write(0x01, gateway, 4);
}
void wiz820io::set_subnet_mask(char *subnet_mask){
	write(0x05, subnet_mask, 4);
}
void wiz820io::set_mac_addr(char *mac_addr){
	write(0x09, mac_addr, 6);
}


void wiz820io::set_reset_pin(int rst){
	reset_pin = rst;
}
void wiz820io::set_power_pin(int power){
	power_pin = power;
}
void wiz820io::set_interrupt_pin(int interrupt){
	interrupt_pin = interrupt;
}


void wiz820io::write(unsigned int addr, char *buf, int len){
	int i = 0;
	
	digitalWrite(this->spi->nssPin(), LOW);
	//set up a call for a write
	this->spi->transfer((char) (addr >> 8) & 0xFF);
	this->spi->transfer((char) addr & 0xFF);
	this->spi->transfer((char) (0x80 | ((len >> 8) & 0x7F)));
	this->spi->transfer((char) (len & 0xFF));
	while (i < len){
		this->spi->transfer(buf[i]);
		i++;
	}
	digitalWrite(this->spi->nssPin(), HIGH);

}
void wiz820io::write(unsigned int addr, char val){
	this->write(addr, &val, 1);
}
char wiz820io::read(unsigned int addr, char *buf, int len){	
	//set up a call for a read
	int i = 0;
	
	//set up a call for a write
	digitalWrite(this->spi->nssPin(), LOW);
	this->spi->transfer((char) (addr >> 8) & 0xFF);
	this->spi->transfer((char) addr & 0xFF);
	this->spi->transfer((char) (0x00 | ((len >> 8) & 0x7F)));
	this->spi->transfer((char) (len & 0xFF));
	while (i < len){
		buf[i] = this->spi->transfer(0);
		i++;
	}
	digitalWrite(this->spi->nssPin(), HIGH);

	return 0;
}
char wiz820io::read(unsigned int addr){
	char val = 0;
	this->read(addr, &val, 1);
	return val;
}

void wiz820io::write_register(unsigned int reg, unsigned char value){
	this->write(reg, (char) value);
}
unsigned char wiz820io::read_register(unsigned int reg){
	return (unsigned char) this->read(reg);
}

void wiz820io::set_DHCP(uint8 enable){
	this->DHCP = enable;	
}
uint8 wiz820io::get_DHCP(){
	return this->DHCP;
}

void wiz820io::set_timeout_millis(unsigned int timeout){
	//only taking the bottom 16 bits
	char top_byte = (char) ((timeout >> 8) & 0xFF);
	char bot_byte = (char) ((timeout) & 0xFF);
	this->write_register(RTR0, top_byte);
	this->write_register(RTR1, bot_byte);
}
unsigned int wiz820io::get_timeout_millis(){
	char top_byte = 0;
	char bot_byte = 0;

	top_byte = this->read_register(RTR0);
	bot_byte = this->read_register(RTR1);

	return (unsigned int) (top_byte << 8 | bot_byte);
}
void wiz820io::set_timeout_retries(uint8 retries){
	this->write_register(RCR, (char) retries);
}
uint8 wiz820io::get_timeout_retries(void){
	return (uint8) this->read_register(RCR);
}


void wiz820io::initialize_socket_memory(){

	int tx_sum = 0;
	int rx_sum = 0;

	for (int i = 0; i < MAX_SOCK_NUM; i++){
		//write all the sizes
		write(CH_BASE + (i * CH_SIZE) + SOCK_TXMEM_SIZE, tx_kb_size[i]);
		write(CH_BASE + (i * CH_SIZE) + SOCK_RXMEM_SIZE, rx_kb_size[i]);

		//initialize all byte sizes to zero
		tx_buffer_size[i] = 0;
		rx_buffer_size[i] = 0;

		//descretize things a bit by only setting by multiples of kilobytes
		if (tx_sum <= 16384){
			switch( tx_kb_size[i] ){
				case 1:
					this->tx_buffer_size[i] = (int16)(1024);
					this->tx_buffer_mask[i] = (uint16)(0x03FF);
					break;
				case 2:
					this->tx_buffer_size[i] = (int16)(2048);
					this->tx_buffer_mask[i] = (uint16)(0x07FF);
					break;
				case 4:
					this->tx_buffer_size[i] = (int16)(4096);
					this->tx_buffer_mask[i] = (uint16)(0x0FFF);
					break;
				case 8:
					this->tx_buffer_size[i] = (int16)(8192);
					this->tx_buffer_mask[i] = (uint16)(0x1FFF);
					break;
				case 16:
					this->tx_buffer_size[i] = (int16)(16384);
					this->tx_buffer_mask[i] = (uint16)(0x3FFF);
					break;
			}
		}

		if (rx_sum <= 16384){
			switch( rx_kb_size[i] ){
				case 1:
					this->rx_buffer_size[i] = (int16)(1024);
					this->rx_buffer_mask[i] = (uint16)(0x03FF);
					break;
				case 2:
					this->rx_buffer_size[i] = (int16)(2048);
					this->rx_buffer_mask[i] = (uint16)(0x07FF);
					break;
				case 4:
					this->rx_buffer_size[i] = (int16)(4096);
					this->rx_buffer_mask[i] = (uint16)(0x0FFF);
					break;
				case 8:
					this->rx_buffer_size[i] = (int16)(8192);
					this->rx_buffer_mask[i] = (uint16)(0x1FFF);
					break;
				case 16:
					this->rx_buffer_size[i] = (int16)(16384);
					this->rx_buffer_mask[i] = (uint16)(0x3FFF);
					break;
			}
		}

		tx_sum += tx_buffer_size[i];
		rx_sum += rx_buffer_size[i];
		
		//write out the base address of each of the memory locations into an easily accessible location

		
		if (i == 0){
			tx_buffer_base[0] = (uint16) (__DEF_IINCHIP_MAP_TXBUF__);
			rx_buffer_base[0] = (uint16) (__DEF_IINCHIP_MAP_RXBUF__);
		}
		else {
			tx_buffer_base[i] = tx_buffer_base[i - 1] + tx_buffer_size[i - 1];
			rx_buffer_base[i] = rx_buffer_base[i - 1] + rx_buffer_size[i - 1];
		}
	
	}
}

void wiz820io::interrupt_handler(){
	//read the interrupt register
	unsigned char interrupts = 0x00;
	interrupts = read_register(IR);

	//do I need to read socket specific interrupts?

	//if any of the sockets are the ones being targeted for the interrupt
	//call their interrupt

	//check the interrupt status

	//if it is a low level MAC PHY thing, handle it here

	//otherwise if it is a socket thing, find it's index
	//confirm its not NULL
	//sockets[i]->socket_interrupt()
}

void wiz820io::register_socket(unsigned char socket_num, abst_wiz * socket){
	if (socket_num > MAX_SOCK_NUM){
//XXX ERROR SOCKET OUT OF RANGE
//		assert(0);
		return;
	}
	sockets[socket_num] = socket;

}
void wiz820io::unregister_socket(unsigned char socket_num){
	if (socket_num > MAX_SOCK_NUM){
//XXX ERROR SOCKET OUT OF RANGE
//		assert(0);
		return;
	}
	sockets[socket_num] = NULL;
}

unsigned short wiz820io::get_tx_buffer_size(unsigned char socket_num){
	if (socket_num > MAX_SOCK_NUM){
//XXX ERROR SOCKET OUT OF RANGE
//		assert(0);
		return 0;
	}

	return tx_buffer_size[socket_num];	
}
unsigned short wiz820io::get_rx_buffer_size(unsigned char socket_num){
	if (socket_num > MAX_SOCK_NUM){
//XXX ERROR SOCKET OUT OF RANGE
//		assert(0);
		return 0;
	}

	return rx_buffer_size[socket_num];	

}

unsigned short wiz820io::get_tx_buffer_base(unsigned char socket_num){
	if (socket_num > MAX_SOCK_NUM){
//XXX ERROR SOCKET OUT OF RANGE
//		assert(0);
		return 0;
	}

	return tx_buffer_base[socket_num];	
}
unsigned short wiz820io::get_rx_buffer_base(unsigned char socket_num){
	if (socket_num > MAX_SOCK_NUM){
//XXX ERROR SOCKET OUT OF RANGE
//		assert(0);
		return 0;
	}

	return rx_buffer_base[socket_num];	

}

unsigned short wiz820io::get_tx_buffer_mask(unsigned char socket_num){
	if (socket_num > MAX_SOCK_NUM){
//XXX ERROR SOCKET OUT OF RANGE
//		assert(0);
		return 0;
	}

	return tx_buffer_mask[socket_num];	
}
unsigned short wiz820io::get_rx_buffer_mask(unsigned char socket_num){
	if (socket_num > MAX_SOCK_NUM){
//XXX ERROR SOCKET OUT OF RANGE
//		assert(0);
		return 0;
	}

	return rx_buffer_mask[socket_num];	

}


unsigned short wiz820io::get_a_local_port(){
	unsigned short lp = this->local_port;
	this->local_port++;
	if (local_port == 0xFFFE){
		local_port = 2000;
	}
	return lp;
}

char wiz820io::get_available_socket_index(){
//XXX this could lead to an error if the user opens a socket without checking this

	//go through all of the socket status and if one is closed then return that
	//index
	int i = 0;
	char socket_status = 0;

	for (i = 0; i < MAX_SOCK_NUM; i++){
		socket_status = read(CH_BASE + (i * CH_SIZE) + SOCK_MR);	
		if (socket_status == SOCK_MR_CLOSE){
			return i;
		}
	}
	//there are no sockets open
	return -1;
}
