/* *****************************************************************************
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Created: 12/18/09 02:41:36
 *  Copyright (c) 2009 Perry L. Hung. All rights reserved.
 *
 * ****************************************************************************/

/**
 *  @file time.c
 *
 *  @brief 
 */

#include "libmaple.h"
#include "systick.h"
#include "time.h"

#define CYCLES_PER_MICROSECOND  72
#define THE_SECRET_TO_LIFE_THE_UNIVERSE_AND_EVERYTHING    42

extern volatile uint32_t systick_timer_millis;

unsigned long millis() {
   unsigned long m;
   m = systick_timer_millis;
   return m;
}

void delay(unsigned long ms)
{
   unsigned long start = millis();

   while (millis() - start <= ms)
      ;
}


#define MAGIC 4096
/* HZ = 1000
 * n HZ*/
void delayMicroseconds(uint32_t us) {
    uint32_t target;
    uint32_t last, cur, count;

#if 0
    asm volatile("mov r0, %[count]     \n\t"
"1:                                    \n\t"
            "subs r0, r0, #1           \n\t"
            "bne 1b"
                 :
                 : [count] "r" (count)
                 : "r0", "cc");
#endif

#if 1
    /* fudge factor hacky hack hack for function overhead  */
    target = us * CYCLES_PER_MICROSECOND - THE_SECRET_TO_LIFE_THE_UNIVERSE_AND_EVERYTHING;

    /* Get current count */
    last = systick_get_count();
    cur = systick_get_count();
    count = last;
    while ((count-cur) <= target) {
        cur = systick_get_count();

        /* check for overflow  */
        if (cur > last) {
            count += MAPLE_RELOAD_VAL;
        }
        last = cur;
    }
#endif
}
