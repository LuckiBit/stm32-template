#ifndef APPLICATION_BOOT_H
#define APPLICATION_BOOT_H

#include <stdbool.h>

/**
 * @brief Check whether the Application vector table contains valid entry values.
 *
 * @return true when the initial stack pointer and reset handler are valid.
 */
bool application_is_valid(void);

/**
 * @brief Stop the Bootloader runtime and transfer control to the Application.
 *
 * This function does not return when the Application image is valid. The caller
 * must call application_is_valid() before invoking it.
 */
void application_start(void);

#endif /* APPLICATION_BOOT_H */
