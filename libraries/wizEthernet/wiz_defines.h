//wiznet 820io registers

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



#define WINDOWFULL_FLAG_ON 			1
#define WINDOWFULL_FLAG_OFF 		0 
#define WINDOWFULL_MAX_RETRY_NUM 	3
#define WINDOWFULL_WAIT_TIME 		1000

#define MR							0x0000 
#define GAR0			        	0x0001
#define SUBR0			        	0x0005
#define SHAR0						0x0009
#define SIPR0						0x000F
#define IR							0x0015
#define IR2							0x0034 
#define PHY							0x0035
#define IMR							0x0036
#define IMR2						0x0016
#define RTR0						0x0017
#define RTR1						0x0018
#define RCR							0x0019
#define PATR0			        	0x001C
#define PPPALGO						0x001E
#define PTIMER						0x0028
#define PMAGIC						0x0029
#define VERSIONR					0x001F
#define UIPR0						0x002A
#define UPORT0						0x002E

#define INTLEVEL0					0x0030
#define INTLEVEL1					0x0031

//Socket Registers
#define CH_BASE						0x4000
#define CH_SIZE		                0x0100

//SOCKET specific
#define SOCK_MR		        		0x0000
#define SOCK_CR						0x0001
#define SOCK_IR						0x0002
#define SOCK_SR						0x0003
#define SOCK_PORT0					0x0004
#define SOCK_DHAR0					0x0006
#define SOCK_DIPR0					0x000C
#define SOCK_DPORT0					0x0010
#define SOCK_MSSR0					0x0012
#define SOCK_PROTO					0x0014

#define SOCK_TOS					0x0015
#define SOCK_TTL					0x0016
#define SOCK_RXMEM_SIZE	        	0x001E
#define SOCK_TXMEM_SIZE	        	0x001F
#define SOCK_TX_FSR0		        0x0020
#define SOCK_TX_RD0					0x0022
#define SOCK_TX_WR0					0x0024
#define SOCK_RX_RSR0		        0x0026
#define SOCK_RX_RD0					0x0028
#define SOCK_RX_WR0					0x002A
#define SOCK_IMR					0x002C
#define SOCK_FRAG					0x002D
#define SOCK_KEEP_TIMER				0x002F

//Mode Register Defines
#define MR_RST						0x80
#define MR_WOL						0x20
#define MR_PB						0x10
#define MR_PPPOE					0x08
#define MR_LB  		    			0x04
#define MR_AI						0x02
#define MR_IND						0x01

//Interrupt Register
#define IR_CONFLICT					0x80 
#define IR_UNREACH					0x40 
#define IR_PPPoE					0x20 
#define IR_MAGIC					0x10 
#define IR_SOCK(ch)					(0x01 << ch) 

//Socket Mode Register
#define SOCK_MR_CLOSE				0x00		
#define SOCK_MR_TCP					0x01		
#define SOCK_MR_UDP					0x02		
#define SOCK_MR_IPRAW	        	0x03
#define SOCK_MR_MACRAW	        	0x04
#define SOCK_MR_PPPOE				0x05		
#define SOCK_MR_ND					0x20
#define SOCK_MR_MULTI				0x80		

//Socket Control Register
#define SOCK_CR_OPEN				0x01	
#define SOCK_CR_LISTEN				0x02
#define SOCK_CR_CONNECT				0x04
#define SOCK_CR_DISCON				0x08
#define SOCK_CR_CLOSE				0x10
#define SOCK_CR_SEND				0x20
#define SOCK_CR_SEND_MAC			0x21
#define SOCK_CR_SEND_KEEP			0x22	
#define SOCK_CR_RECV				0x40	

//Socket Interrupt Register
#define SOCK_IR_SEND_OK				0x10
#define SOCK_IR_TIMEOUT				0x08
#define SOCK_IR_RECV				0x04
#define SOCK_IR_DISCON				0x02
#define SOCK_IR_CON					0x01	

//Socket Status Register
#define SOCK_CLOSED					0x00		
#define SOCK_INIT 					0x13		
#define SOCK_LISTEN					0x14		
#define SOCK_SYNSENT	   			0x15
#define SOCK_SYNRECV		   		0x16
#define SOCK_ESTABLISHED			0x17
#define SOCK_FIN_WAIT				0x18
#define SOCK_CLOSING		   		0x1A
#define SOCK_TIME_WAIT				0x1B
#define SOCK_CLOSE_WAIT				0x1C
#define SOCK_LAST_ACK				0x1D
#define SOCK_UDP					0x22	
#define SOCK_IPRAW					0x32	
#define SOCK_MACRAW					0x42	
#define SOCK_PPPOE					0x5F		

//IP Protocol
#define IPPROTO_IP              	0
#define IPPROTO_ICMP            	1
#define IPPROTO_IGMP            	2
#define IPPROTO_GGP             	3
#define IPPROTO_TCP             	6
#define IPPROTO_PUP             	12
#define IPPROTO_UDP             	17
#define IPPROTO_IDP             	22
#define IPPROTO_ND              	77
#define IPPROTO_RAW             	255


