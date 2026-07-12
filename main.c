/*
 * STM32F072RB Nucleo Board - Bare Metal LED Blink
 * Onboard LED: PA5 (Green LED)
 */

#include <stdint.h>

/* Register Definitions */
#define RCC_BASE        0x40021000
#define GPIOA_BASE      0x48000000

/* RCC Registers */
#define RCC_AHBENR      (*(volatile uint32_t *)(RCC_BASE + 0x14))

/* GPIOA Registers */
#define GPIOA_MODER     (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_OTYPER    (*(volatile uint32_t *)(GPIOA_BASE + 0x04))
#define GPIOA_OSPEEDR   (*(volatile uint32_t *)(GPIOA_BASE + 0x08))
#define GPIOA_PUPDR     (*(volatile uint32_t *)(GPIOA_BASE + 0x0C))
#define GPIOA_BSRR      (*(volatile uint32_t *)(GPIOA_BASE + 0x18))

/* Bit Definitions */
#define RCC_AHBENR_IOPAEN     (1 << 17)  /* Enable GPIOA clock */

#define GPIO_MODER_OUTPUT     (1 << 10)  /* PA5 as output (bits 10-11) */
#define GPIO_OSPEEDR_HIGH     (3 << 10)  /* PA5 high speed (bits 10-11) */
#define GPIO_PUPDR_NOPULL     (0 << 10)  /* PA5 no pull-up/pull-down */

#define GPIO_BSRR_BS5         (1 << 5)   /* Set PA5 */
#define GPIO_BSRR_BR5         (1 << 21)  /* Reset PA5 */

/* Simple delay loop */
static void delay(uint32_t count)
{
    volatile uint32_t i;
    for (i = 0; i < count; i++) {
        __asm__("nop");
    }
}

int main(void)
{
    /* Enable GPIOA clock */
    RCC_AHBENR |= RCC_AHBENR_IOPAEN;

    /* Configure PA5 as output push-pull */
    GPIOA_MODER &= ~(3 << 10);      /* Clear bits 10-11 */
    GPIOA_MODER |= GPIO_MODER_OUTPUT;

    /* Set output speed to high */
    GPIOA_OSPEEDR &= ~(3 << 10);    /* Clear bits 10-11 */
    GPIOA_OSPEEDR |= GPIO_OSPEEDR_HIGH;

    /* No pull-up, no pull-down */
    GPIOA_PUPDR &= ~(3 << 10);      /* Clear bits 10-11 */
    GPIOA_PUPDR |= GPIO_PUPDR_NOPULL;

    /* Main loop - blink LED */
    while (1) {
        /* Turn LED on (set PA5 high) */
        GPIOA_BSRR = GPIO_BSRR_BS5;
        delay(500000);

        /* Turn LED off (set PA5 low) */
        GPIOA_BSRR = GPIO_BSRR_BR5;
        delay(500000);
    }

    return 0;
}
