/*******************************************************************************
 * @file    startup.c
 * @brief   STM32F072RB Microcontroller Startup Code and Vector Table
 * @details This file contains the interrupt vector table, reset handler,
 *          and default exception/interrupt handlers for the STM32F072RB
 *          microcontroller. It performs essential initialization tasks
 *          including data section copying and BSS zero-fill before calling
 *          the main application.
 * 
 * @hardware
 *          - Target: STM32F072RB (ARM Cortex-M0+)
 *          - Architecture: ARMv6-M
 * 
 * @compliance
 *          - MISRA C:2012 compliant where applicable
 *          - NASA Power of Ten Coding Rules adhered to
 * 
 * @initialization_sequence
 *          1. Load initial stack pointer value from address 0x00000000
 *          2. Execute Reset_Handler on reset event
 *          3. Copy .data section from flash to RAM
 *          4. Zero-fill .bss section in RAM
 *          5. Call main() application entry point
 * 
 * @author  Generated
 * @date    Current
 ******************************************************************************/

/*******************************************************************************
 * HEADER FILES
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 * EXTERNAL SYMBOLS (DEFINED IN LINKER SCRIPT)
 ******************************************************************************/

extern uint32_t _sidata;  /**< Initial value for data section (flash) */
extern uint32_t _sdata;   /**< Start address of .data section in RAM */
extern uint32_t _edata;   /**< End address of .data section in RAM */
extern uint32_t _sbss;    /**< Start address of .bss section in RAM */
extern uint32_t _ebss;    /**< End address of .bss section in RAM */
extern uint32_t _estack;  /**< Top of stack */

/*******************************************************************************
 * FUNCTION PROTOTYPES
 ******************************************************************************/

static void Reset_Handler(void);
static void Default_Handler(void);
int32_t main(void);

/*******************************************************************************
 * VECTOR TABLE DEFINITION
 ******************************************************************************/

/** @brief Interrupt Vector Table placed at start of flash */
__attribute__((section(".isr_vector")))
static const uint32_t vector_table[] = {
    /* ARM Cortex-M0+ Core Exceptions */
    (uint32_t)&_estack,            /**< Initial SP */
    (uint32_t)Reset_Handler,       /**< Reset Handler */
    (uint32_t)Default_Handler,     /**< NMI Handler */
    (uint32_t)Default_Handler,     /**< Hard Fault Handler */
    (uint32_t)Default_Handler,     /**< MPU Handler (reserved) */
    (uint32_t)Default_Handler,     /**< Bus Fault Handler (reserved) */
    (uint32_t)Default_Handler,     /**< Usage Fault Handler (reserved) */
    (uint32_t)0UL,                 /**< Reserved */
    (uint32_t)0UL,                 /**< Reserved */
    (uint32_t)0UL,                 /**< Reserved */
    (uint32_t)0UL,                 /**< Reserved */
    (uint32_t)Default_Handler,     /**< SVCall Handler */
    (uint32_t)Default_Handler,     /**< Debug Monitor Handler (reserved) */
    (uint32_t)0UL,                 /**< Reserved */
    (uint32_t)Default_Handler,     /**< PendSV Handler */
    (uint32_t)Default_Handler,     /**< SysTick Handler */

    /* STM32F072RB Specific Interrupts */
    (uint32_t)Default_Handler,     /**< WWDG Interrupt */
    (uint32_t)Default_Handler,     /**< PVD Interrupt */
    (uint32_t)Default_Handler,     /**< RTC Interrupt */
    (uint32_t)Default_Handler,     /**< FLASH Interrupt */
    (uint32_t)Default_Handler,     /**< RCC Interrupt */
    (uint32_t)Default_Handler,     /**< EXTI0_1 Interrupt */
    (uint32_t)Default_Handler,     /**< EXTI2_3 Interrupt */
    (uint32_t)Default_Handler,     /**< EXTI4_15 Interrupt */
    (uint32_t)Default_Handler,     /**< TSC Interrupt */
    (uint32_t)Default_Handler,     /**< DMA1_Channel1 Interrupt */
    (uint32_t)Default_Handler,     /**< DMA1_Channel2_3 Interrupt */
    (uint32_t)Default_Handler,     /**< DMA1_Channel4_5_6_7 Interrupt */
    (uint32_t)Default_Handler,     /**< ADC1_COMP Interrupt */
    (uint32_t)Default_Handler,     /**< TIM1_BRK_UP_TRG_COM Interrupt */
    (uint32_t)Default_Handler,     /**< TIM1_CC Interrupt */
    (uint32_t)Default_Handler,     /**< TIM2 Interrupt */
    (uint32_t)Default_Handler,     /**< TIM3 Interrupt */
    (uint32_t)Default_Handler,     /**< TIM6_DAC Interrupt */
    (uint32_t)Default_Handler,     /**< TIM7 Interrupt */
    (uint32_t)Default_Handler,     /**< TIM14 Interrupt */
    (uint32_t)Default_Handler,     /**< TIM15 Interrupt */
    (uint32_t)Default_Handler,     /**< TIM16 Interrupt */
    (uint32_t)Default_Handler,     /**< TIM17 Interrupt */
    (uint32_t)Default_Handler,     /**< I2C1 Interrupt */
    (uint32_t)Default_Handler,     /**< I2C2 Interrupt */
    (uint32_t)Default_Handler,     /**< SPI1 Interrupt */
    (uint32_t)Default_Handler,     /**< SPI2 Interrupt */
    (uint32_t)Default_Handler,     /**< USART1 Interrupt */
    (uint32_t)Default_Handler,     /**< USART2 Interrupt */
    (uint32_t)Default_Handler,     /**< USART3_4 Interrupt */
    (uint32_t)Default_Handler,     /**< CEC Interrupt */
    (uint32_t)Default_Handler      /**< USB Interrupt */
};

/*******************************************************************************
 * FUNCTION DEFINITIONS
 ******************************************************************************/

/**
 * @brief Reset Handler - First code executed after microcontroller reset
 * @detail Copies .data from flash to RAM, zeros .bss, then calls main()
 */
static void Reset_Handler(void)
{
    const uint32_t *src_ptr = &_sidata;
    uint32_t *dst_ptr = &_sdata;

    /* Copy .data section from Flash to RAM */
    while (dst_ptr < &_edata)
    {
        *dst_ptr = *src_ptr;
        dst_ptr++;
        src_ptr++;
    }

    /* Zero-fill .bss section in RAM */
    dst_ptr = &_sbss;
    while (dst_ptr < &_ebss)
    {
        *dst_ptr = 0U;
        dst_ptr++;
    }

    /* Call main application function */
    (void)main();

    /* Error trap - should never be reached */
    while (1U)
    {
        __asm__ volatile ("nop" ::: "memory");
    }
}

/**
 * @brief Default interrupt/exception handler
 * @detail Catch-all handler for unimplemented interrupts
 */
static void Default_Handler(void)
{
    while (1U)
    {
        __asm__ volatile ("nop" ::: "memory");
    }
}

/*******************************************************************************
 * ALIAS DEFINITIONS
 ******************************************************************************/

/** @brief Alias for Reset_Handler for toolchain compatibility */
void _start(void) __attribute__((alias("Reset_Handler")));
