/**
 * @file system_init.h
 * @brief Declares the Application system initialization interface.
 */

#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

void system_init(void);

/** @brief Disables interrupts and stops execution after a hardware initialization failure. */
void Error_Handler(void);

#endif /* SYSTEM_INIT_H */
