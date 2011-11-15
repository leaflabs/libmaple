/* CS3 start_c routine.
 *
 * Copyright (c) 2006, 2007 CodeSourcery Inc
 *
 * The authors hereby grant permission to use, copy, modify, distribute,
 * and license this software and its documentation for any purpose, provided
 * that existing copyright notices are retained in all copies and that this
 * notice is included verbatim in any distributions. No written agreement,
 * license, or royalty fee is required for any of the authorized uses.
 * Modifications to this software may be copyrighted by their authors
 * and need not follow the licensing terms described here, provided that
 * the new terms are clearly indicated on the first page of each file where
 * they apply.
 */

#include <stddef.h>

extern void __libc_init_array (void);

extern int main (int, char **, char **);

extern void exit (int) __attribute__ ((noreturn, weak));

extern char _data, _edata;
extern char _bss, _ebss;

struct rom_img_cfg {
  long long *img_start;
};

extern char _lm_rom_img_cfgp;

void  __attribute__ ((noreturn))
__cs3_start_c (void)
{
  struct rom_img_cfg *img_cfg = (struct rom_img_cfg*)&_lm_rom_img_cfgp;
  long long *src;
  long long *dst;
  int exit_code;

  /* Initialize .data, if necessary. */
  src = img_cfg->img_start;
  dst = (long long*)&_data;
  if (src != dst) {
    while (dst < (long long*)&_edata) {
      *dst++ = *src++;
    }
  }

  /* Zero .bss. */
  dst = (long long*)&_bss;
  while (dst < (long long*)&_ebss) {
    *dst++ = 0;
  }

  /* Run initializers.  */
  __libc_init_array ();

  exit_code = main (0, NULL, NULL);
  if (exit)
    exit (exit_code);
  /* If exit is NULL, make sure we don't return. */
  for (;;)
    continue;
}
