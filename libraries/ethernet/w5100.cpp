#include "wirish.h"
#include "w5100.h"


extern HardwareSPI spi;

void w5100_init(k) {

}

void w5100_reset(void) {
   w5100_write(MR, MR_RST);
}

void w5100_write_buf(uint16 addr, uint8 *buf, uint8 len) {
   uint32 i;
   for (i = 0; i < len; i++) {
      w5100_write(addr + i, buf[i]);
   }
}

void w5100_read_buf(uint16 addr, uint8 *buf, uint8 len) {
   uint32 i;
   for (i = 0; i < len; i++) {
      buf[i] = w5100_read(addr + i);
   }
}

uint8 w5100_send_cmd(uint8 opcode, uint16 addr, uint8 data) {
   uint8 buf[4];
   uint8 rc = 0;

   buf[0] = opcode;
   buf[1] = (addr >> 8);
   buf[2] = (addr & 0xFF);
   buf[3] = data;

   digitalWrite(SS, LOW);
   rc = spi.send(buf, 4);
   digitalWrite(SS, HIGH);

#ifdef SPI_DEBUG
   if (opcode == OPCODE_WRITE) {
      iprintf("\tWrite: 0x%04x = 0x%x\n", addr, data);
   } else {
      iprintf("\tRead: 0x%04x = 0x%x\n", addr, rc);
   }
#endif

   return rc;
}
