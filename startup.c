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

/* Include standard integer type definitions with explicit widths */
#include <stdint.h>

/*******************************************************************************
 * EXTERNAL SYMBOLS (DEFINED IN LINKER SCRIPT)
 * Note: These symbols are defined in the linker script (stm32f072rb.ld)
 *       and represent memory section boundaries.
 ******************************************************************************/

/**
 * @brief Initial value for data section (source in flash)
 * @extern Defined by linker script as start of initialized data in flash
 */
extern uint32_t _sidata;

/**
 * @brief Start address of data section in RAM
 * @extern Defined by linker script as start of .data section in RAM
 */
extern uint32_t _sdata;

/**
 * @brief End address of data section in RAM
 * @extern Defined by linker script as end of .data section in RAM
 */
extern uint32_t _edata;

/**
 * @brief Start address of BSS section in RAM
 * @extern Defined by linker script as start of .bss section
 */
extern uint32_t _sbss;

/**
 * @brief End address of BSS section in RAM
 * @extern Defined by linker script as end of .bss section
 */
extern uint32_t _ebss;

/**
 * @brief Top of stack (end of RAM, stack grows downward)
 * @extern Defined by linker script as _estack symbol
 */
extern uint32_t _estack;

/*******************************************************************************
 * FUNCTION PROTOTYPES
 * Note: Forward declarations required per NASA Rule 4 (single function per task)
 ******************************************************************************/

/**
 * @brief Reset handler - entry point after reset
 * @detail Performs low-level initialization and calls main()
 */
static void Reset_Handler(void);

/**
 * @brief Default handler for unimplemented interrupts
 * @detail Infinite loop to catch unhandled exceptions
 */
static void Default_Handler(void);

/**
 * @brief Main application entry point (declared here, defined in main.c)
 * @return Should never return in embedded applications
 */
static int32_t main(void);

/*******************************************************************************
 * VECTOR TABLE DEFINITION
 * @note Placed in .isr_vector section per linker script requirements
 * @detail Contains initial SP value and all exception/interrupt vectors
 *         Order is mandated by ARM Cortex-M0+ architecture
 ******************************************************************************/

/**
 * @brief Interrupt Vector Table
 * @note Section attribute places this at start of flash (address 0x08000000)
 * @detail Array of 32-bit addresses pointing to handler functions
 *         Index 0: Initial Stack Pointer value
 *         Index 1: Reset Handler
 *         Index 2-15: Core exceptions (NMI, HardFault, etc.)
 *         Index 16+: Device-specific interrupts (IRQs)
 * 
 * @misra_note
 *         - Rule 11.3: Casts between pointers and integers used for vector table
 *           (required for hardware vector table format)
 *         - Rule 8.7: External linkage not used to minimize coupling
 */
__attribute__((section(".isr_vector")))
static const uint32_t vector_table[] =
{
    /*---------------------------------------------------------
     * ARM Cortex-M0+ Core Exceptions
     *-------------------------------------------------------*/
    
    /** @brief Index 0: Initial Stack Pointer value */
    (uint32_t)&_estack,                    /**< Initial SP (top of RAM) */
    
    /** @brief Index 1: Reset Vector */
    (uint32_t)Reset_Handler,               /**< Reset Handler */
    
    /** @brief Index 2: Non-Maskable Interrupt */
    (uint32_t)Default_Handler,             /**< NMI Handler */
    
    /** @brief Index 3: Hard Fault */
    (uint32_t)Default_Handler,             /**< Hard Fault Handler */
    
    /** @brief Index 4: Memory Protection Unit (not present on M0+, reserved) */
    (uint32_t)Default_Handler,             /**< MPU Handler (reserved) */
    
    /** @brief Index 5: Bus Fault (not present on M0+, reserved) */
    (uint32_t)Default_Handler,             /**< Bus Fault Handler (reserved) */
    
    /** @brief Index 6: Usage Fault (not present on M0+, reserved) */
    (uint32_t)Default_Handler,             /**< Usage Fault Handler (reserved) */
    
    /** @brief Index 7-9: Reserved */
    (uint32_t)0UL,                         /**< Reserved */
    (uint32_t)0UL,                         /**< Reserved */
    (uint32_t)0UL,                         /**< Reserved */
    
    /** @brief Index 10: Reserved */
    (uint32_t)0UL,                         /**< Reserved */
    
    /** @brief Index 11: Supervisor Call */
    (uint32_t)Default_Handler,             /**< SVCall Handler */
    
    /** @brief Index 12: Debug Monitor (not present on M0+, reserved) */
    (uint32_t)Default_Handler,             /**< Debug Monitor Handler (reserved) */
    
    /** @brief Index 13: Reserved */
    (uint32_t)0UL,                         /**< Reserved */
    
    /** @brief Index 14: Pendable Request for System Service */
    (uint32_t)Default_Handler,             /**< PendSV Handler */
    
    /** @brief Index 15: System Tick Timer */
    (uint32_t)Default_Handler,             /**< SysTick Handler */
    
    /*---------------------------------------------------------
     * STM32F072RB Specific Interrupts (IRQs)
     * All use default handler as they are application-specific
     *-------------------------------------------------------*/
    
    /** @brief IRQ 0: Window Watchdog */
    (uint32_t)Default_Handler,             /**< WWDG Interrupt */
    
    /** @brief IRQ 1: Programmable Voltage Detector */
    (uint32_t)Default_Handler,             /**< PVD Interrupt */
    
    /** @brief IRQ 2: Real-Time Clock */
    (uint32_t)Default_Handler,             /**< RTC Interrupt */
    
    /** @brief IRQ 3: Flash Memory */
    (uint32_t)Default_Handler,             /**< FLASH Interrupt */
    
    /** @brief IRQ 4: Reset and Clock Control */
    (uint32_t)Default_Handler,             /**< RCC Interrupt */
    
    /** @brief IRQ 5: EXTI Lines 0 and 1 */
    (uint32_t)Default_Handler,             /**< EXTI0_1 Interrupt */
    
    /** @brief IRQ 6: EXTI Lines 2 and 3 */
    (uint32_t)Default_Handler,             /**< EXTI2_3 Interrupt */
    
    /** @brief IRQ 7: EXTI Lines 4 to 15 */
    (uint32_t)Default_Handler,             /**< EXTI4_15 Interrupt */
    
    /** @brief IRQ 8: Touch Sensing Controller */
    (uint32_t)Default_Handler,             /**< TSC Interrupt */
    
    /** @brief IRQ 9: DMA1 Channel 1 */
    (uint32_t)Default_Handler,             /**< DMA1_Channel1 Interrupt */
    
    /** @brief IRQ 10: DMA1 Channels 2 and 3 */
    (uint32_t)Default_Handler,             /**< DMA1_Channel2_3 Interrupt */
    
    /** @brief IRQ 11: DMA1 Channels 4, 5, 6, and 7 */
    (uint32_t)Default_Handler,             /**< DMA1_Channel4_5_6_7 Interrupt */
    
    /** @brief IRQ 12: ADC1 and COMP1/2 */
    (uint32_t)Default_Handler,             /**< ADC1_COMP Interrupt */
    
    /** @brief IRQ 13: TIM1 Break, Update, Trigger, Commutation */
    (uint32_t)Default_Handler,             /**< TIM1_BRK_UP_TRG_COM Interrupt */
    
    /** @brief IRQ 14: TIM1 Capture Compare */
    (uint32_t)Default_Handler,             /**< TIM1_CC Interrupt */
    
    /** @brief IRQ 15: TIM2 Global */
    (uint32_t)Default_Handler,             /**< TIM2 Interrupt */
    
    /** @brief IRQ 16: TIM3 Global */
    (uint32_t)Default_Handler,             /**< TIM3 Interrupt */
    
    /** @brief IRQ 17: TIM6 Global and DAC underrun */
    (uint32_t)Default_Handler,             /**< TIM6_DAC Interrupt */
    
    /** @brief IRQ 18: TIM7 Global */
    (uint32_t)Default_Handler,             /**< TIM7 Interrupt */
    
    /** @brief IRQ 19: TIM14 Global */
    (uint32_t)Default_Handler,             /**< TIM14 Interrupt */
    
    /** @brief IRQ 20: TIM15 Global */
    (uint32_t)Default_Handler,             /**< TIM15 Interrupt */
    
    /** @brief IRQ 21: TIM16 Global */
    (uint32_t)Default_Handler,             /**< TIM16 Interrupt */
    
    /** @brief IRQ 22: TIM17 Global */
    (uint32_t)Default_Handler,             /**< TIM17 Interrupt */
    
    /** @brief IRQ 23: I2C1 Event */
    (uint32_t)Default_Handler,             /**< I2C1 Interrupt */
    
    /** @brief IRQ 24: I2C2 Event */
    (uint32_t)Default_Handler,             /**< I2C2 Interrupt */
    
    /** @brief IRQ 25: SPI1 Global */
    (uint32_t)Default_Handler,             /**< SPI1 Interrupt */
    
    /** @brief IRQ 26: SPI2 Global */
    (uint32_t)Default_Handler,             /**< SPI2 Interrupt */
    
    /** @brief IRQ 27: USART1 Global */
    (uint32_t)Default_Handler,             /**< USART1 Interrupt */
    
    /** @brief IRQ 28: USART2 Global */
    (uint32_t)Default_Handler,             /**< USART2 Interrupt */
    
    /** @brief IRQ 29: USART3 and UART4 Global */
    (uint32_t)Default_Handler,             /**< USART3_4 Interrupt */
    
    /** @brief IRQ 30: HDMI-CEC */
    (uint32_t)Default_Handler,             /**< CEC Interrupt */
    
    /** @brief IRQ 31: USB Global */
    (uint32_t)Default_Handler              /**< USB Interrupt */
};

/*******************************************************************************
 * FUNCTION DEFINITIONS
 ******************************************************************************/

/**
 * @brief Reset Handler - First code executed after microcontroller reset
 * @detail This function performs critical initialization before main():
 *         1. Copy initialized data (.data) from flash to RAM
 *         2. Zero-fill uninitialized data (.bss) in RAM
 *         3. Call main() application entry point
 *         4. Enter infinite loop if main() returns (should never happen)
 * 
 * @steps
 *        - Initialize source/destination pointers for .data copy
 *        - Copy .data section word-by-word from flash to RAM
 *        - Initialize destination pointer for .bss zero-fill
 *        - Clear .bss section word-by-word
 *        - Branch to main()
 *        - Trap in infinite loop (error condition if reached)
 * 
 * @compliance_notes
 *        - No dynamic memory allocation (NASA Rule 2)
 *        - All variables initialized before use (NASA Rule 1)
 *        - Fixed loop bounds based on linker symbols (NASA Rule 3)
 *        - Single responsibility: system initialization (NASA Rule 4)
 */
static void Reset_Handler(void)
{
    /*=========================================================================
     * STEP 1: Copy .data section from Flash to RAM
     *=======================================================================*/
    /** @brief Source pointer: start of initialized data in Flash */
    const uint32_t *src_ptr;
    
    /** @brief Destination pointer: start of .data section in RAM */
    uint32_t *dst_ptr;
    
    /* Initialize source pointer to flash location of initialized data */
    src_ptr = &_sidata;
    
    /* Initialize destination pointer to RAM location for .data section */
    dst_ptr = &_sdata;
    
    /* Copy initialized data from flash to RAM, word by word */
    /* Loop continues until destination reaches end of .data section */
    while (dst_ptr < &_edata)
    {
        *dst_ptr = *src_ptr;
        dst_ptr++;
        src_ptr++;
    }
    
    /*=========================================================================
     * STEP 2: Zero-fill .bss section in RAM
     *=======================================================================*/
    /* Initialize destination pointer to start of .bss section */
    dst_ptr = &_sbss;
    
    /* Clear .bss section by writing zeros, word by word */
    /* Loop continues until destination reaches end of .bss section */
    while (dst_ptr < &_ebss)
    {
        *dst_ptr = 0U;
        dst_ptr++;
    }
    
    /*=========================================================================
     * STEP 3: Call main application function
     *=======================================================================*/
    /* Transfer control to user application */
    (void)main();
    
    /*=========================================================================
     * STEP 4: Error trap (should never be reached)
     *=======================================================================*/
    /* LCOV_EXCL_START - Unreachable code under normal operation */
    /* Infinite loop to prevent execution past main() return */
    /* This indicates a critical error if main() ever returns */
    while (1U == 1U)
    {
        /* Stay here forever - critical error condition */
        __asm__ volatile ("nop" ::: "memory");
    }
    /* LCOV_EXCL_STOP */
}

/**
 * @brief Default interrupt/exception handler
 * @detail Catch-all handler for unimplemented or unexpected interrupts.
 *         Enters infinite loop to prevent undefined behavior and facilitate
 *         debugging via halt mode.
 * 
 * @usage
 *        - Assigned to all unused interrupt vectors in vector table
 *        - Provides safe fallback for unhandled exceptions
 * 
 * @compliance_notes
 *        - No dynamic memory allocation (NASA Rule 2)
 *        - Prevents undefined behavior from unhandled interrupts
 *        - Single responsibility: error trapping (NASA Rule 4)
 */
static void Default_Handler(void)
{
    /* LCOV_EXCL_START - Only entered on unexpected interrupt */
    /* Infinite loop to trap unexpected interrupts */
    /* Prevents execution of undefined code paths */
    while (1U == 1U)
    {
        /* Execute NOP to allow debugger attachment */
        __asm__ volatile ("nop" ::: "memory");
    }
    /* LCOV_EXCL_STOP */
}

/*******************************************************************************
 * ALIAS DEFINITIONS
 * Note: Provides alternative entry point name for compatibility
 ******************************************************************************/

/**
 * @brief Alias for Reset_Handler
 * @detail Creates _start symbol as alias to Reset_Handler for compatibility
 *         with various toolchain conventions.
 * @note Uses GCC __attribute__ extension for symbol aliasing
 */
/* Entry point alias - _start maps to Reset_Handler */
void _start(void) __attribute__((alias("Reset_Handler")));
