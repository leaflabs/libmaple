/* This value should be set to the starting address of the bootloader on your
 * device. On Arduino platforms using the ATMega328(p), 0x7000 is correct.
 */
#define BOOTLOADER_START_ADDR 0x7000

/* This way of jumping to bootloader is inspired by bootloaders written by
 * Dean Camera.
 */
#define BOOTLOADER_KEY        0xDC42

/* Store data needed for the bootloader to use BLE in EEPROM
 * Returns true if the write was successful, or false
 */
bool bootloader_data_store (aci_state_t *state, uint16_t conn_timeout,
    uint16_t adv_interval);

/* bootloader_jump_check is placed in the .init3 section, which means it runs
 * before ordinary C code on reset.
 * We verify that the reset cause was a watchdog reset, and that boot_key
 * has been set, before doing a jump to bootloader.
 */
void bootloader_jump_check(void) __attribute__ ((used, naked, section (".init3")));

/* Perform the jump to bootloader. Returns only if the jump wasn't possible. */
void bootloader_jump(void);
