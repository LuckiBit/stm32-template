/**
 * ============================================================================
 * STM32F429IG MEMORY MAP
 * ============================================================================
 *
 * MCU:
 *   STM32F429IG
 *
 * Internal Flash:
 *   Base : 0x08000000
 *   Size : 1024 KiB
 *   End  : 0x08100000
 *
 * Internal SRAM:
 *   Base : 0x20000000
 *   Size : 192 KiB
 *   End  : 0x20030000
 *
 *
 * FLASH MEMORY
 * ============================================================================
 *
 * 0x08000000  +---------------------------------------+
 *             |                                       |
 *             |              BOOTLOADER               |
 *             |               32 KiB                  |
 *             |                                       |
 * 0x08008000  +---------------------------------------+
 *             |                                       |
 *             |              APPLICATION              |
 *             |               864 KiB                 |
 *             |                                       |
 * 0x080E0000  +---------------------------------------+
 *             |               BOOT INFO               |
 *             |               128 KiB                 |
 * 0x08100000  +---------------------------------------+
 *             |              FLASH END                |
 *             +---------------------------------------+
 *
 *
 * SRAM MEMORY
 * ============================================================================
 *
 * 0x20000000  +---------------------------------------+
 *             |                                       |
 *             |                 SRAM                  |
 *             |               192 KiB                 |
 *             |                                       |
 * 0x20030000  +---------------------------------------+
 *             |               SRAM END                |
 *             +---------------------------------------+
 *
 * ============================================================================
 */
#ifndef FLASH_LAYOUT_H
#define FLASH_LAYOUT_H

#define MCU_FLASH_BASE_ADDRESS 0x08000000UL
#define MCU_FLASH_SIZE         (1024UL * 1024UL)
#define MCU_SRAM_BASE_ADDRESS  0x20000000UL
#define MCU_SRAM_SIZE          (192UL * 1024UL)

#define MCU_FLASH_END_ADDRESS (MCU_FLASH_BASE_ADDRESS + MCU_FLASH_SIZE)
#define MCU_SRAM_END_ADDRESS  (MCU_SRAM_BASE_ADDRESS + MCU_SRAM_SIZE)

#define FLASH_BOOT_INFO_SECTOR_SIZE (128UL * 1024UL)

#define BOOTLOADER_START_ADDRESS MCU_FLASH_BASE_ADDRESS
#define BOOTLOADER_SIZE          (32UL * 1024UL)
#define BOOTLOADER_END_ADDRESS   (BOOTLOADER_START_ADDRESS + BOOTLOADER_SIZE)

#define APP_START_ADDRESS BOOTLOADER_END_ADDRESS

#define BOOT_INFO_SIZE          FLASH_BOOT_INFO_SECTOR_SIZE
#define BOOT_INFO_START_ADDRESS (MCU_FLASH_END_ADDRESS - BOOT_INFO_SIZE)

#define APP_END_ADDRESS BOOT_INFO_START_ADDRESS
#define APP_SIZE        (APP_END_ADDRESS - APP_START_ADDRESS)

#endif /* FLASH_LAYOUT_H */
