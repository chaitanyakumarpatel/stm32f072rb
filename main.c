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

#include <stdint.h>

/*******************************************************************************
 * HARDWARE REGISTER DEFINITIONS
 ******************************************************************************/

/** @defgroup Peripheral_Base_Addresses Peripheral Base Addresses */
#define RCC_BASE_ADDR       (0x40021000UL)    /**< Reset and Clock Control base */
#define GPIOA_BASE_ADDR     (0x48000000UL)    /**< GPIO Port A base address */

/** @brief AHB Peripheral Clock Enable Register */
#define RCC_AHBENR_REG      (*(volatile uint32_t *)(RCC_BASE_ADDR + 0x14UL))

/** @brief GPIO Mode Register */
#define GPIOA_MODER_REG     (*(volatile uint32_t *)(GPIOA_BASE_ADDR + 0x00UL))

/** @brief GPIO Output Type Register */
#define GPIOA_OTYPER_REG    (*(volatile uint32_t *)(GPIOA_BASE_ADDR + 0x04UL))

/** @brief GPIO Output Speed Register */
#define GPIOA_OSPEEDR_REG   (*(volatile uint32_t *)(GPIOA_BASE_ADDR + 0x08UL))

/** @brief GPIO Pull-up/Pull-down Register */
#define GPIOA_PUPDR_REG     (*(volatile uint32_t *)(GPIOA_BASE_ADDR + 0x0CUL))

/** @brief GPIO Bit Set/Reset Register */
#define GPIOA_BSRR_REG      (*(volatile uint32_t *)(GPIOA_BASE_ADDR + 0x18UL))

/*******************************************************************************
 * BIT FIELD DEFINITIONS AND MASKS
 ******************************************************************************/

/** @brief GPIO Port A Clock Enable Mask (bit 17 of RCC_AHBENR) */
#define RCC_AHBENR_GPIOAEN_MASK     (1UL << 17U)

/** @brief Bit position for PA5 in mode registers */
#define GPIO_PIN5_BIT_POSITION      (10U)
/** @brief Mask for 2-bit field at PA5 position */
#define GPIO_PIN_MASK               (3UL << 10U)

/** @brief GPIOA MODER value for PA5 as output (01b) */
#define GPIOA_MODER_PA5_OUTPUT      (1UL << 10U)

/** @brief GPIOA OSPEEDR value for PA5 high speed (11b) */
#define GPIOA_OSPEEDR_PA5_HIGH      (3UL << 10U)

/** @brief GPIOA PUPDR value for PA5 no pull-up/pull-down (00b) */
#define GPIOA_PUPDR_PA5_NOPULL      (0UL << 10U)

/** @brief GPIOA BSRR value to set PA5 high */
#define GPIOA_BSRR_SET_PIN5         (1UL << 5U)

/** @brief GPIOA BSRR value to reset PA5 low */
#define GPIOA_BSRR_RESET_PIN5       (1UL << 21U)

/*******************************************************************************
 * CONSTANTS AND CONFIGURATION PARAMETERS
 ******************************************************************************/

/** @brief Delay loop iteration count for LED blink timing */
static const uint32_t LED_BLINK_DELAY_COUNT = 500000UL;

/*******************************************************************************
 * FUNCTION PROTOTYPES
 ******************************************************************************/

int32_t main(void);
static void delay_loop(uint32_t count);

/*******************************************************************************
 * FUNCTION DEFINITIONS
 ******************************************************************************/

/**
 * @brief Simple software delay routine using busy-wait loop
 * @param[in] count Number of iterations to execute
 */
static void delay_loop(uint32_t count)
{
    while (count-- > 0U)
    {
        /* Empty loop body */
    }
}

/**
 * @brief Main entry point for the application
 * @return Exit status (never returns in this embedded application)
 * 
 * Steps:
 *   1. Enable clock to GPIO Port A
 *   2. Configure PA5 as push-pull output
 *   3. Set output speed to high
 *   4. Disable pull-up/pull-down resistors
 *   5. Enter infinite loop toggling LED state
 */
int32_t main(void)
{
    /* Enable clock to GPIO Port A */
    RCC_AHBENR_REG |= RCC_AHBENR_GPIOAEN_MASK;

    /* Configure PA5 as general purpose output, push-pull */
    GPIOA_MODER_REG &= ~GPIO_PIN_MASK;
    GPIOA_MODER_REG |= GPIOA_MODER_PA5_OUTPUT;

    /* Configure PA5 output speed to high */
    GPIOA_OSPEEDR_REG &= ~GPIO_PIN_MASK;
    GPIOA_OSPEEDR_REG |= GPIOA_OSPEEDR_PA5_HIGH;

    /* Configure PA5 with no pull-up/pull-down resistors */
    GPIOA_PUPDR_REG &= ~GPIO_PIN_MASK;
    GPIOA_PUPDR_REG |= GPIOA_PUPDR_PA5_NOPULL;

    /* Main application loop - blink LED indefinitely */
    while (1U)
    {
        GPIOA_BSRR_REG = GPIOA_BSRR_SET_PIN5;
        delay_loop(LED_BLINK_DELAY_COUNT);

        GPIOA_BSRR_REG = GPIOA_BSRR_RESET_PIN5;
        delay_loop(LED_BLINK_DELAY_COUNT);
    }

    return 0;
}
