/**
 *  @brief 
 */

#ifndef _FLASH_H_
#define _FLASH_H_

#define FLASH_BASE              0x40022000
#define FLASH_ACR               FLASH_BASE

void flash_enable_prefetch(void);
void flash_set_latency(void);

#endif


