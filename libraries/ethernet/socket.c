#include "wirish.h"
#include "w5100.h"
#include "socket.h"

#define ETHERNET_DEBUG 

#ifdef ETHERNET_DEBUG
   #define ETH_DBG(...) iprintf(__VA_ARGS__)
#else
   #define ETH_DBG(...)
#endif


int32 socket(int32 type) {
   /* tcp  */
   w5100_write(SOCKET0_BASE + SN_MR, 0x01);
}

int32 bind(int32 sockfd, uint16 port) {
   int32 rc;
   /* port 80 */
   w5100_write(SOCKET0_BASE + SN_PORT0, 0x00);
   w5100_write(SOCKET0_BASE + SN_PORT1, 80);  // low byte

   /* open */
   ETH_DBG("open()\n");
   w5100_write(SOCKET0_BASE + SN_CR, CR_OPEN);
   rc = w5100_read(SOCKET0_BASE + SN_SR);
   ETH_DBG("SR: 0x%0x\n", rc);

}

static char buf[2048];

int32 listen(int32 sockfd) {
   uint16 bytesAvailable = 0;
   uint32 i;
   int32 rc;

   /* listen  */
   ETH_DBG("listen()\n");
   w5100_write(SOCKET0_BASE + SN_CR, CR_LISTEN);
   rc = w5100_read(SOCK_ADDR(0, SN_SR));
   ETH_DBG("SR: 0x%0x\n", rc);

   /* wait for connection  */
   while(1) {
      if (w5100_read(SOCK_ADDR(0, SN_SR)) == SOCK_ESTABLISHED) {
         ETH_DBG("Connection received\n");
         break;
      }
   }
   /* wait for data  */
   while (!bytesAvailable) {
      bytesAvailable += (w5100_read(SOCK_ADDR(0, SN_RX_RSR0)) << 8);
      bytesAvailable += w5100_read(SOCK_ADDR(0, SN_RX_RSR1));
   }
   ETH_DBG("recv: %u bytes\n", bytesAvailable);

   /* Read them out  */
   uint32 rxrd = w5100_read(SOCK_ADDR(0, SN_RX_RD0)) << 8;
   rxrd += w5100_read(SOCK_ADDR(0, SN_RX_RD1));
   ETH_DBG("rxrd: %u\n", rxrd);

   for (i = 0; i < bytesAvailable; i++) {
      buf[i] = w5100_read(0x6000 + i);
      iprintf("%c", buf[i]);
   }

   sprintf(buf, "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n\r\n"
                "analogInput(2):  %u<BR>"
                "analogInput(15): %u<BR>"
                "analogInput(16): %u<BR>"
                "analogInput(17): %u<BR>"
                "analogInput(18): %u<BR>"
                "analogInput(19): %u<BR>"
                "analogInput(20): %u<BR>"
                "analogInput(27): %u<BR>"
                "analogInput(28): %u<BR>"
                "watch out for cows",
                analogRead(2),
                analogRead(15),
                analogRead(16),
                analogRead(17),
                analogRead(18),
                analogRead(19),
                analogRead(20),
                analogRead(27),
                analogRead(28));

   uint32 send_size = strlen(buf);

   iprintf("sending %u bytes()\n", send_size);

   uint16 txwr;
   uint16 get_offset;
   uint16 get_start_address;
   uint16 tx_mask = 0x07ff;
   /* calculate offset address  */
   txwr  = w5100_read(SOCK_ADDR(0, SN_TX_WR0)) << 8;
   txwr += w5100_read(SOCK_ADDR(0, SN_TX_WR1));
   iprintf("SN_TX_WR: %x\n", txwr);

   get_offset = txwr & tx_mask;
   get_start_address = 0x4000 + get_offset;

   iprintf("get_offset: %x send_size: %u\n" , get_offset, send_size);

   /* copy data to get_start_address */
   for (i = 0; i < send_size; i++) {
      w5100_write(get_start_address + i, buf[i]);
   }

   txwr += send_size;

   w5100_write(SOCK_ADDR(0, SN_TX_WR0), (txwr & 0xFF00) >> 8 );
   w5100_write(SOCK_ADDR(0, SN_TX_WR1), (txwr & 0x00FF));
   w5100_write(SOCK_ADDR(0, SN_CR), CR_SEND);

   delay(1);
   w5100_write(SOCK_ADDR(0, SN_CR), CR_DISCON);
   delay(1);
   w5100_write(SOCK_ADDR(0, SN_CR), CR_CLOSE);
}


