#include "application_boot.h"

#include "flash_layout.h"
#include "stm32f1xx_hal.h"

#include <stdint.h>

#define APPLICATION_STACK_ALIGNMENT 0x00000008U
#define APPLICATION_THUMB_STATE_BIT 0x00000001U

static uint32_t application_read_vector_entry(uint32_t offset);
static void     application_start_context(uint32_t initial_stack_pointer __attribute__((unused)),
                                          uint32_t reset_handler_address __attribute__((unused)))
    __attribute__((naked, noreturn));

bool application_is_valid(void)
{
    bool     reset_handler_in_application;
    bool     reset_handler_uses_thumb;
    bool     stack_pointer_aligned;
    bool     stack_pointer_in_sram;
    bool     vector_table_is_valid;
    uint32_t initial_stack_pointer      = application_read_vector_entry(0U);
    uint32_t reset_handler_address      = application_read_vector_entry(sizeof(uint32_t));
    uint32_t reset_handler_code_address = reset_handler_address & ~APPLICATION_THUMB_STATE_BIT;

    stack_pointer_in_sram = initial_stack_pointer >= MCU_SRAM_BASE_ADDRESS;
    stack_pointer_in_sram = stack_pointer_in_sram && initial_stack_pointer <= MCU_SRAM_END_ADDRESS;
    stack_pointer_aligned = (initial_stack_pointer % APPLICATION_STACK_ALIGNMENT) == 0U;

    reset_handler_in_application = reset_handler_code_address >= APP_START_ADDRESS;
    reset_handler_in_application =
        reset_handler_in_application && reset_handler_code_address < APP_END_ADDRESS;
    reset_handler_uses_thumb = (reset_handler_address & APPLICATION_THUMB_STATE_BIT) != 0U;

    vector_table_is_valid = stack_pointer_in_sram && stack_pointer_aligned;
    vector_table_is_valid =
        vector_table_is_valid && reset_handler_in_application && reset_handler_uses_thumb;

    return vector_table_is_valid;
}

void application_start(void)
{
    uint32_t initial_stack_pointer = application_read_vector_entry(0U);
    uint32_t reset_handler_address = application_read_vector_entry(sizeof(uint32_t));

    __disable_irq();

    SysTick->CTRL = 0U;
    SysTick->LOAD = 0U;
    SysTick->VAL  = 0U;

    NVIC->ICER[0] = UINT32_MAX;
    NVIC->ICER[1] = UINT32_MAX;
    NVIC->ICPR[0] = UINT32_MAX;
    NVIC->ICPR[1] = UINT32_MAX;

    SCB->VTOR = APP_START_ADDRESS;
    __DSB();
    __ISB();

    application_start_context(initial_stack_pointer, reset_handler_address);
}

static uint32_t application_read_vector_entry(uint32_t offset)
{
    const volatile uint32_t *vector_entry =
        (const volatile uint32_t *)(uintptr_t)(APP_START_ADDRESS + offset);

    return *vector_entry;
}

static void application_start_context(uint32_t initial_stack_pointer __attribute__((unused)),
                                      uint32_t reset_handler_address __attribute__((unused)))
{
    __asm volatile("msr msp, r0\n"
                   "cpsie i\n"
                   "bx r1\n");
}
