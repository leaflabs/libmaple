//wiznet 820io registers


#define WINDOWFULL_FLAG_ON 1
#define WINDOWFULL_FLAG_OFF 0 
#define WINDOWFULL_MAX_RETRY_NUM 3
#define WINDOWFULL_WAIT_TIME 1000

#include "Types.h"

#define MR				(COMMON_BASE + 0x0000) 
/**
 @brief Gateway IP Register address
 */
#define GAR0			        (COMMON_BASE + 0x0001)
/**
 @brief Subnet mask Register address
 */
#define SUBR0			        (COMMON_BASE + 0x0005)
/**
 @brief Source MAC Register address
 */
#define SHAR0				(COMMON_BASE + 0x0009)
/**
 @brief Source IP Register address
 */
#define SIPR0				(COMMON_BASE + 0x000F)
/**
 @brief Interrupt Register
 */
#define IR				(COMMON_BASE + 0x0015)
/**
 @brief Socket Interrupt Register
 */
#define IR2				(COMMON_BASE + 0x0034) 
/**
 @brief PHY Status Register
 */
#define PHY				(COMMON_BASE + 0x0035)
/**
 @brief Interrupt mask register
 */
#define IMR				(COMMON_BASE + 0x0036)
/**
 @brief Socket Interrupt Mask Register
 */
#define IMR2				(COMMON_BASE + 0x0016)
/**
 @brief Timeout register address( 1 is 100us )
 */
#define RTR0				(COMMON_BASE + 0x0017)
#define RTR1				(COMMON_BASE + 0x0018)
/**
 @brief Retry count reigster
 */
#define RCR				(COMMON_BASE + 0x0019)
/**
 @brief Authentication type register address in PPPoE mode
 */
#define PATR0			        (COMMON_BASE + 0x001C)
#define PPPALGO                         (COMMON_BASE + 0x001E)
/**
 @briefPPP LCP Request Timer register  in PPPoE mode
 */
#define PTIMER 		                (COMMON_BASE + 0x0028)
/**
 @brief PPP LCP Magic number register  in PPPoE mode
 */
#define PMAGIC 		                (COMMON_BASE + 0x0029)
/**
 @brief chip version register address
 */
#define VERSIONR			(COMMON_BASE + 0x001F)   
/**
 @brief Unreachable IP register address in UDP mode
 */
#define UIPR0				(COMMON_BASE + 0x002A)
/**
 @brief Unreachable Port register address in UDP mode
 */
#define UPORT0			        (COMMON_BASE + 0x002E)
/**
 @brief set Interrupt low level timer register address
 */
#define INTLEVEL0			(COMMON_BASE + 0x0030)
#define INTLEVEL1			(COMMON_BASE + 0x0031)




/**
 @brief socket register
*/
#define CH_BASE                         (COMMON_BASE + 0x4000)
/**
 @brief	size of each channel register map
 */
#define CH_SIZE		                0x0100




//SOCKET specific
/**
 @brief socket Mode register
 */
#define SOCK_MR		        (0x0000)
/**
 @brief channel SOCK_CR register
 */
#define SOCK_CR			(0x0001)
/**
 @brief channel interrupt register
 */
#define SOCK_IR			(0x0002)
/**
 @brief channel status register
 */
#define SOCK_SR			(0x0003)
/**
 @brief source port register
 */
#define SOCK_PORT0			(0x0004)
/**
 @brief Peer MAC register address
 */
#define SOCK_DHAR0			(0x0006)
/**
 @brief Peer IP register address
 */
#define SOCK_DIPR0			(0x000C)
/**
 @brief Peer port register address
 */
#define SOCK_DPORT0			(0x0010)
/**
 @brief Maximum Segment Size(SOCK_MSSR0) register address
 */
#define SOCK_MSSR0			(0x0012)
/**
 @brief Protocol of IP Header field register in IP raw mode
 */
#define SOCK_PROTO			(0x0014)

/** 
 @brief IP Type of Service(TOS) Register 
 */
#define SOCK_TOS			(0x0015)
/**
 @brief IP Time to live(TTL) Register 
 */
#define SOCK_TTL			(0x0016)
/**
 @brief Receive memory size reigster
 */
#define SOCK_RXMEM_SIZE	        (0x001E)
/**
 @brief Transmit memory size reigster
 */
#define SOCK_TXMEM_SIZE	        (0x001F)
/**
 @brief Transmit free memory size register
 */
#define SOCK_TX_FSR0		        (0x0020)
/**
 @brief Transmit memory read pointer register address
 */
#define SOCK_TX_RD0			(0x0022)
/**
 @brief Transmit memory write pointer register address
 */
#define SOCK_TX_WR0			(0x0024)
/**
 @brief Received data size register
 */
#define SOCK_RX_RSR0		        (0x0026)
/**
 @brief Read point of Receive memory
 */
#define SOCK_RX_RD0			(0x0028)
/**
 @brief Write point of Receive memory
 */
#define SOCK_RX_WR0			(0x002A)
/**
 @brief socket interrupt mask register
 */
#define SOCK_IMR			(0x002C)
/**
 @brief frag field value in IP header register
 */
#define SOCK_FRAG			(0x002D)
/**
 @brief Keep Timer register
 */
#define SOCK_KEEP_TIMER		(0x002F)

/* MODE register values */
#define MR_RST			0x80 /**< reset */
#define MR_WOL			0x20 /**< Wake on Lan */
#define MR_PB			0x10 /**< ping block */
#define MR_PPPOE		0x08 /**< enable pppoe */
#define MR_LB  		        0x04 /**< little or big endian selector in indirect mode */
#define MR_AI			0x02 /**< auto-increment in indirect mode */
#define MR_IND			0x01 /**< enable indirect mode */

/* IR register values */
#define IR_CONFLICT	        0x80 /**< check ip confict */
#define IR_UNREACH	        0x40 /**< get the destination unreachable message in UDP sending */
#define IR_PPPoE		0x20 /**< get the PPPoE close message */
#define IR_MAGIC		0x10 /**< get the magic packet interrupt */
#define IR_SOCK(ch)	        (0x01 << ch) /**< check socket interrupt */

/* SOCK_MR values */
#define SOCK_MR_CLOSE		0x00		/**< unused socket */
#define SOCK_MR_TCP		0x01		/**< TCP */
#define SOCK_MR_UDP		0x02		/**< UDP */
#define SOCK_MR_IPRAW	        0x03		/**< IP LAYER RAW SOCK */
#define SOCK_MR_MACRAW	        0x04		/**< MAC LAYER RAW SOCK */
#define SOCK_MR_PPPOE		0x05		/**< PPPoE */
#define SOCK_MR_ND		0x20		/**< No Delayed Ack(TCP) flag */
#define SOCK_MR_MULTI		0x80		/**< support multicating */

/* SOCK_CR values */
#define SOCK_CR_OPEN		0x01		/**< initialize or open socket */
#define SOCK_CR_LISTEN		0x02		/**< wait connection request in tcp mode(Server mode) */
#define SOCK_CR_CONNECT	        0x04		/**< send connection request in tcp mode(Client mode) */
#define SOCK_CR_DISCON		0x08		/**< send closing reqeuset in tcp mode */
#define SOCK_CR_CLOSE		0x10		/**< close socket */
#define SOCK_CR_SEND		0x20		/**< update txbuf pointer, send data */
#define SOCK_CR_SEND_MAC	        0x21		/**< send data with MAC address, so without ARP process */
#define SOCK_CR_SEND_KEEP     	0x22		/**<  send keep alive message */
#define SOCK_CR_RECV		0x40		/**< update rxbuf pointer, recv data */

#ifdef __DEF_IINCHIP_PPP__
	#define SOCK_CR_PCON		0x23		 
	#define SOCK_CR_PDISCON		0x24		 
	#define SOCK_CR_PCR		0x25		 
	#define SOCK_CR_PCN		0x26		
	#define SOCK_CR_PCJ		0x27		
#endif

/* SOCK_IR values */
#ifdef __DEF_IINCHIP_PPP__
	#define SOCK_IR_PRECV		0x80		
	#define SOCK_IR_PFAIL		0x40		
	#define SOCK_IR_PNEXT		0x20		
#endif
#define SOCK_IR_SEND_OK			0x10		/**< complete sending */
#define SOCK_IR_TIMEOUT			0x08		/**< assert timeout */
#define SOCK_IR_RECV			0x04		/**< receiving data */
#define SOCK_IR_DISCON			0x02		/**< closed socket */
#define SOCK_IR_CON			0x01		/**< established connection */

/* SOCK_SR values */
#define SOCK_CLOSED			0x00		/**< closed */
#define SOCK_INIT 			0x13		/**< init state */
#define SOCK_LISTEN			0x14		/**< listen state */
#define SOCK_SYNSENT	   		0x15		/**< connection state */
#define SOCK_SYNRECV		   	0x16		/**< connection state */
#define SOCK_ESTABLISHED		0x17		/**< success to connect */
#define SOCK_FIN_WAIT			0x18		/**< closing state */
#define SOCK_CLOSING		   	0x1A		/**< closing state */
#define SOCK_TIME_WAIT			0x1B		/**< closing state */
#define SOCK_CLOSE_WAIT			0x1C		/**< closing state */
#define SOCK_LAST_ACK			0x1D		/**< closing state */
#define SOCK_UDP			0x22		/**< udp socket */
#define SOCK_IPRAW			0x32		/**< ip raw mode socket */
#define SOCK_MACRAW			0x42		/**< mac raw mode socket */
#define SOCK_PPPOE			0x5F		/**< pppoe socket */

/* IP PROTOCOL */
#define IPPROTO_IP              0           /**< Dummy for IP */
#define IPPROTO_ICMP            1           /**< Control message protocol */
#define IPPROTO_IGMP            2           /**< Internet group management protocol */
#define IPPROTO_GGP             3           /**< Gateway^2 (deprecated) */
#define IPPROTO_TCP             6           /**< TCP */
#define IPPROTO_PUP             12          /**< PUP */
#define IPPROTO_UDP             17          /**< UDP */
#define IPPROTO_IDP             22          /**< XNS idp */
#define IPPROTO_ND              77          /**< UNOFFICIAL net disk protocol */
#define IPPROTO_RAW             255         /**< Raw IP packet */


