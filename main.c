/*******************************************************************************
 * @file    main.c
 * @brief   STM32F072RB Nucleo Board - Bare Metal LED Blink Application
 * @details This application demonstrates bare-metal GPIO control by blinking
 *          the onboard green LED connected to pin PA5.
 * 
 * @hardware
 *          - Target: STM32F072RB Nucleo Development Board
 *          - LED: Green onboard LED connected to GPIO Port A, Pin 5 (PA5)
 * 
 * @compliance
 *          - MISRA C:2012 compliant where applicable
 *          - NASA Power of Ten Coding Rules adhered to
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
 * HARDWARE REGISTER DEFINITIONS
 * Note: All addresses are memory-mapped I/O per STM32F072 Reference Manual
 ******************************************************************************/

/**
 * @defgroup Peripheral_Base_Addresses Peripheral Base Addresses
 * @{
 */
#define RCC_BASE_ADDR       (0x40021000UL)    /**< Reset and Clock Control base */
#define GPIOA_BASE_ADDR     (0x48000000UL)    /**< GPIO Port A base address */
/** @} */

/*******************************************************************************
 * RCC (Reset and Clock Control) REGISTER DEFINITIONS
 ******************************************************************************/

/**
 * @brief AHB Peripheral Clock Enable Register
 * @note Offset: 0x14 from RCC_BASE_ADDR
 * @detail Controls clock enable for AHB peripherals including GPIO ports
 */
#define RCC_AHBENR_REG      (*(volatile uint32_t *)(RCC_BASE_ADDR + 0x14UL))

/*******************************************************************************
 * GPIO PORT A REGISTER DEFINITIONS
 ******************************************************************************/

/**
 * @brief GPIO Mode Register
 * @note Offset: 0x00 from GPIOA_BASE_ADDR
 * @detail Configures I/O direction and mode for each pin (2 bits per pin)
 */
#define GPIOA_MODER_REG     (*(volatile uint32_t *)(GPIOA_BASE_ADDR + 0x00UL))

/**
 * @brief GPIO Output Type Register
 * @note Offset: 0x04 from GPIOA_BASE_ADDR
 * @detail Configures output type: push-pull or open-drain (1 bit per pin)
 */
#define GPIOA_OTYPER_REG    (*(volatile uint32_t *)(GPIOA_BASE_ADDR + 0x04UL))

/**
 * @brief GPIO Output Speed Register
 * @note Offset: 0x08 from GPIOA_BASE_ADDR
 * @detail Configures output speed for each pin (2 bits per pin)
 */
#define GPIOA_OSPEEDR_REG   (*(volatile uint32_t *)(GPIOA_BASE_ADDR + 0x08UL))

/**
 * @brief GPIO Pull-up/Pull-down Register
 * @note Offset: 0x0C from GPIOA_BASE_ADDR
 * @detail Configures internal resistors for each pin (2 bits per pin)
 */
#define GPIOA_PUPDR_REG     (*(volatile uint32_t *)(GPIOA_BASE_ADDR + 0x0CUL))

/**
 * @brief GPIO Bit Set/Reset Register
 * @note Offset: 0x18 from GPIOA_BASE_ADDR
 * @detail Atomic set/reset operations for output pins
 *        Bits 0-15: Set corresponding output
 *        Bits 16-31: Reset corresponding output
 */
#define GPIOA_BSRR_REG      (*(volatile uint32_t *)(GPIOA_BASE_ADDR + 0x18UL))

/*******************************************************************************
 * BIT FIELD DEFINITIONS AND MASKS
 ******************************************************************************/

/**
 * @brief GPIO Port A Clock Enable Mask
 * @detail Bit 17 of RCC_AHBENR enables clock to GPIO Port A
 * @note MISRA C Rule 10.5: Using UL suffix for unsigned long constants
 */
#define RCC_AHBENR_GPIOAEN_MASK     (1UL << 17U)

/**
 * @brief GPIO Pin Configuration Masks for PA5
 * @detail Each pin uses 2 bits in mode registers
 *         PA5 corresponds to bits 10-11 (pin_number * 2)
 */
#define GPIO_PIN5_BIT_POSITION      (10U)              /**< Bit position for PA5 */
#define GPIO_PIN_MASK               (3UL << 10U)       /**< Mask for 2-bit field */

/**
 * @brief GPIO Mode Register Value for PA5 as General Purpose Output
 * @detail Bits 10-11 = 01b (General purpose output mode)
 */
#define GPIOA_MODER_PA5_OUTPUT      (1UL << 10U)

/**
 * @brief GPIO Output Speed Register Value for PA5 High Speed
 * @detail Bits 10-11 = 11b (High speed configuration)
 */
#define GPIOA_OSPEEDR_PA5_HIGH      (3UL << 10U)

/**
 * @brief GPIO Pull-up/Pull-down Register Value for PA5 No Pull
 * @detail Bits 10-11 = 00b (No pull-up, no pull-down)
 */
#define GPIOA_PUPDR_PA5_NOPULL      (0UL << 10U)

/**
 * @brief GPIO BSRR Set Bit for PA5
 * @detail Writing 1 to bit 5 sets PA5 output high
 */
#define GPIOA_BSRR_SET_PIN5         (1UL << 5U)

/**
 * @brief GPIO BSRR Reset Bit for PA5
 * @detail Writing 1 to bit 21 (16 + 5) resets PA5 output low
 */
#define GPIOA_BSRR_RESET_PIN5       (1UL << 21U)

/*******************************************************************************
 * CONSTANTS AND CONFIGURATION PARAMETERS
 ******************************************************************************/

/**
 * @brief Delay loop iteration count for LED blink timing
 * @detail Approximate delay value - actual time depends on system clock
 * @note Should be calibrated based on actual CPU frequency
 */
static const uint32_t LED_BLINK_DELAY_COUNT = 500000UL;

/*******************************************************************************
 * FUNCTION PROTOTYPES
 ******************************************************************************/

/* Forward declaration of main function per C standard */
static int32_t main(void);

/**
 * @brief Simple software delay routine using busy-wait loop
 * @param[in] count Number of iterations to execute
 * @detail Executes NOP instructions in a loop to create time delay
 * @note Not suitable for precise timing; use hardware timers for accuracy
 */
static void delay_loop(uint32_t count);

/*******************************************************************************
 * FUNCTION DEFINITIONS
 ******************************************************************************/

/**
 * @brief Simple software delay routine using busy-wait loop
 * @param[in] count Number of iterations to execute
 * @detail Executes NOP instructions in a loop to create time delay.
 *         The 'volatile' qualifier prevents compiler optimization.
 * @note Not suitable for precise timing applications.
 *       Use hardware timers for accurate delays.
 */
static void delay_loop(uint32_t count)
{
    /**
     * @brief Loop counter variable
     * @note volatile prevents compiler from optimizing away the loop
     */
    volatile uint32_t loop_counter;

    /* Busy-wait loop with inline assembly NOP for each iteration */
    for (loop_counter = 0U; loop_counter < count; loop_counter++)
    {
        /* Execute no-operation instruction to consume clock cycles */
        __asm__ volatile ("nop" ::: "memory");
    }
}

/**
 * @brief Main entry point for the application
 * @return Exit status (never returns in this embedded application)
 * @detail Initializes GPIO for LED control and executes infinite blink loop
 * 
 * @steps
 *        1. Enable clock to GPIO Port A
 *        2. Configure PA5 as push-pull output
 *        3. Set output speed to high
 *        4. Disable pull-up/pull-down resistors
 *        5. Enter infinite loop toggling LED state
 * 
 * @compliance_notes
 *        - All variables initialized before use (NASA Rule 1)
 *        - No dynamic memory allocation (NASA Rule 2)
 *        - Fixed loop bounds (NASA Rule 3)
 *        - Single function per logical task (NASA Rule 4)
 * 
 * @note In embedded systems, main() is typically called from startup code
 *       and should never return. Static linkage is not used to maintain
 *       standard C program structure.
 */
int32_t main(void)
{
    /*=========================================================================
     * STEP 1: Enable clock to GPIO Port A peripheral
     *=======================================================================*/
    /* Set bit 17 in RCC_AHBENR to enable GPIOA clock */
    RCC_AHBENR_REG |= RCC_AHBENR_GPIOAEN_MASK;

    /*=========================================================================
     * STEP 2: Configure PA5 as General Purpose Output, Push-Pull
     *=======================================================================*/
    /* Clear existing mode bits (bits 10-11) for PA5 */
    GPIOA_MODER_REG &= ~GPIO_PIN_MASK;
    /* Set PA5 to output mode (01b) */
    GPIOA_MODER_REG |= GPIOA_MODER_PA5_OUTPUT;

    /*=========================================================================
     * STEP 3: Configure PA5 output speed to High
     *=======================================================================*/
    /* Clear existing speed bits (bits 10-11) for PA5 */
    GPIOA_OSPEEDR_REG &= ~GPIO_PIN_MASK;
    /* Set PA5 to high speed (11b) */
    GPIOA_OSPEEDR_REG |= GPIOA_OSPEEDR_PA5_HIGH;

    /*=========================================================================
     * STEP 4: Configure PA5 with no pull-up/pull-down resistors
     *=======================================================================*/
    /* Clear existing pupd bits (bits 10-11) for PA5 */
    GPIOA_PUPDR_REG &= ~GPIO_PIN_MASK;
    /* Set PA5 to no pull-up/pull-down (00b) */
    GPIOA_PUPDR_REG |= GPIOA_PUPDR_PA5_NOPULL;

    /*=========================================================================
     * STEP 5: Main application loop - blink LED indefinitely
     *=======================================================================*/
    /* Infinite loop per embedded application design */
    while (1U == 1U)
    {
        /*-------------------------------------------------------------
         * Turn LED ON: Set PA5 output high
         * Write to BSRR bit 5 (lower 16 bits set the pin)
         *-----------------------------------------------------------*/
        GPIOA_BSRR_REG = GPIOA_BSRR_SET_PIN5;
        
        /* Execute delay to maintain LED on state */
        delay_loop(LED_BLINK_DELAY_COUNT);

        /*-------------------------------------------------------------
         * Turn LED OFF: Set PA5 output low
         * Write to BSRR bit 21 (upper 16 bits reset the pin)
         *-----------------------------------------------------------*/
        GPIOA_BSRR_REG = GPIOA_BSRR_RESET_PIN5;
        
        /* Execute delay to maintain LED off state */
        delay_loop(LED_BLINK_DELAY_COUNT);
    }
    /* LCOV_EXCL_START - Unreachable code */
    /* Return statement included for completeness but never executed */
    return 0;
    /* LCOV_EXCL_STOP */
}
