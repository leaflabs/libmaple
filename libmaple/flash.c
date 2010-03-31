#include "libmaple.h"
#include "flash.h"

#define ACR_PRFTBE                ((uint32)0xFFFFFFEF)
#define ACR_PRFTBE_ENABLE ((uint32)0x00000010)  /* FLASH Prefetch Buffer Enable */
#define ACR_PRFTBE_DISABLE ((uint32)0x00000000)  /* FLASH Prefetch Buffer Disable */

#define ACR_LATENCY               ((uint32)0x00000038)
#define ACR_LATENCY_0                ((uint32)0x00000000)  /* FLASH Zero Latency cycle */
#define ACR_LATENCY_1                ((uint32)0x00000001)  /* FLASH One Latency cycle */
#define ACR_LATENCY_2                ((uint32)0x00000002)  /* FLASH Two Latency cycles */

void flash_enable_prefetch(void) {
   uint32 acr = __read(FLASH_ACR);

   acr &= ACR_PRFTBE;
   acr |= ACR_PRFTBE_ENABLE;

   __write(FLASH_ACR, acr);
}

void flash_set_latency(void) {
   uint32 acr = __read(FLASH_ACR);

   acr &= ACR_LATENCY;
   acr |= ACR_LATENCY_2;

   __write(FLASH_ACR, acr);
}
