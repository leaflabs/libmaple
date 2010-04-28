/**
 *  @brief 
 */

#ifndef _ETHERNET_H_
#define _ETHERNET_H_

#define MR              0x0000
#define MR_RST            0x80

/* Gateway IP Address Register  */
#define GAR0            0x0001
#define GAR1            0x0002
#define GAR2            0x0003
#define GAR3            0x0004
#define GAR               GAR0

/* Subnet mask register  */
#define SUBR0           0x0005
#define SUBR1           0x0006
#define SUBR2           0x0007
#define SUBR3           0x0008
#define SUBR             SUBR0

/* Source Hardware Address Register  */
#define SHAR0           0x0009
#define SHAR1           0x000A
#define SHAR2           0x000B
#define SHAR3           0x000C
#define SHAR4           0x000D
#define SHAR5           0x000E
#define SHAR             SHAR0

/* Source IP Address register  */
#define SIPR0           0x000F
#define SIPR1           0x0010
#define SIPR2           0x0011
#define SIPR3           0x0012
#define SIPR             SIPR0

/* Interrupt register  */
#define IR              0x0015
#define IR_CONFLICT     BIT(7)
#define IR_UNREACH      BIT(6)
#define IR_PPOE         BIT(5)
#define IR_S3_INT       BIT(3)
#define IR_S2_INT       BIT(2)
#define IR_S1_INT       BIT(1)
#define IR_S0_INT       BIT(0)

/* Interrupt mask register  */
#define IMR             0x0016
#define IMR_CONFLICT    BIT(7)
#define IMR_UNREACH     BIT(6)
#define IMR_PPOE        BIT(5)
#define IMR_S3_INT      BIT(3)
#define IMR_S2_INT      BIT(2)
#define IMR_S1_INT      BIT(1)
#define IMR_S0_INT      BIT(0)

/* Retry time, 1 = 100us  */
#define RTR0            0x0017
#define RTR1            0x0018

/* Retry count register, default 0x08  */
#define RCR             0x0019

/* rx memory size register, default 0x55, 2KB each socket  */
#define RMSR            0x001A

/* tx memory size register, default 0x55 2kb each socket  */
#define TMSR            0x001B

/* spi opcodes  */
#define OPCODE_WRITE      0xF0
#define OPCODE_READ       0x0F

/* Sockets  */
#define SOCKET0_BASE      0x0400
#define SOCKET1_BASE      0x0500
#define SOCKET2_BASE      0x0600
#define SOCKET3_BASE      0x0700

/* socket register offsets  */
#define SN_MR             0x00
#define SN_CR             0x01
#define SN_IR             0x02
#define SN_SR             0x03
#define SN_PORT0          0x04
#define SN_PORT1          0x05
#define SN_DHAR0          0x06
#define SN_DHAR1          0x07
#define SN_DHAR2          0x08
#define SN_DHAR3          0x09
#define SN_DHAR4          0x0A
#define SN_DHAR5          0x0B
#define SN_DIPR0          0x0C
#define SN_DIPR1          0x0D
#define SN_DIPR2          0x0E
#define SN_DIPR3          0x0F
#define SN_DPORT0         0x10
#define SN_DPORT1         0x11
#define SN_MSSR0          0x12
#define SN_MSSR1          0x13
#define SN_PROTO          0x14
#define SN_TOS            0x15
#define SN_TTL            0x16
#define SN_TX_FSR0        0x20
#define SN_TX_FSR1        0x21
#define SN_TX_RD0         0x22
#define SN_TX_RD1         0x23
#define SN_TX_WR0         0x24
#define SN_TX_WR1         0x25
#define SN_RX_RSR0        0x26
#define SN_RX_RSR1        0x27
#define SN_RX_RD0         0x28
#define SN_RX_RD1         0x29

/* socket command codes  */
#define CR_OPEN           0x01
#define CR_LISTEN         0x02
#define CR_CONNECT        0x04
#define CR_DISCON         0x08
#define CR_CLOSE          0x10
#define CR_SEND           0x20
#define CR_SEND_MAC       0x21
#define CR_SEND_KEEP      0x22
#define CR_REC            0x40

/* socket status codes  */
#define SOCK_CLOSED       0x00
#define SOCK_INIT         0x13
#define SOCK_LISTEN       0x14
#define SOCK_ESTABLISHED  0x17
#define SOCK_CLOSE_WAIT   0x1C
#define SOCK_UDP          0x22
#define SOCK_IPRAW        0x32
#define SOCK_MACRAW       0x42
#define SOCK_PPOE         0x5F

/* socket changing status codes  */
#define SOCK_SYNSENT      0x15
#define SOCK_SYNRECV      0x16
#define SOCK_FIN_WAIT     0x18
#define SOCK_CLOSING      0x1A
#define SOCK_TIME_WAIT    0x1B
#define SOCK_LAST_ACK     0x1D
#define SOCK_ARP          0x11

#define SOCK_ADDR(n, reg) (                \
   __builtin_constant_p(n) ? (              \
         (n == 0) ? (SOCKET0_BASE + reg) : \
         (n == 1) ? (SOCKET1_BASE + reg) : \
         (n == 2) ? (SOCKET2_BASE + reg) : \
         (n == 3) ? (SOCKET3_BASE + reg) : \
         0xFF                              \
      ) : 0x00 \
)

#endif

