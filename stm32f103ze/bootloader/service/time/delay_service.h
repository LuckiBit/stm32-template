/**
 * @file delay_service.h
 * @brief Declares blocking delay capabilities used before the scheduler starts.
 */

#ifndef DELAY_SERVICE_H
#define DELAY_SERVICE_H

#include <stdint.h>

void delay_service_wait_ms(uint32_t duration_ms);

#endif /* DELAY_SERVICE_H */
