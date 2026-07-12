/*
 * STM32F072RB Startup Code
 */

#include <stdint.h>

/* Linker defined symbols */
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _estack;

/* Function prototypes */
void Reset_Handler(void);
void Default_Handler(void);

/* Vector Table */
__attribute__((section(".isr_vector")))
const uint32_t vector_table[] = {
    (uint32_t)&_estack,              /* Initial Stack Pointer Value */
    (uint32_t)Reset_Handler,         /* Reset Handler */
    (uint32_t)Default_Handler,       /* NMI Handler */
    (uint32_t)Default_Handler,       /* Hard Fault Handler */
    (uint32_t)Default_Handler,       /* MPU Handler */
    (uint32_t)Default_Handler,       /* Bus Fault Handler */
    (uint32_t)Default_Handler,       /* Usage Fault Handler */
    0,                               /* Reserved */
    0,                               /* Reserved */
    0,                               /* Reserved */
    0,                               /* Reserved */
    (uint32_t)Default_Handler,       /* SVCall Handler */
    (uint32_t)Default_Handler,       /* Debug Monitor Handler */
    0,                               /* Reserved */
    (uint32_t)Default_Handler,       /* PendSV Handler */
    (uint32_t)Default_Handler,       /* SysTick Handler */
    /* External Interrupts - using default handler for all */
    (uint32_t)Default_Handler,       /* WWDG */
    (uint32_t)Default_Handler,       /* PVD */
    (uint32_t)Default_Handler,       /* RTC */
    (uint32_t)Default_Handler,       /* FLASH */
    (uint32_t)Default_Handler,       /* RCC */
    (uint32_t)Default_Handler,       /* EXTI0_1 */
    (uint32_t)Default_Handler,       /* EXTI2_3 */
    (uint32_t)Default_Handler,       /* EXTI4_15 */
    (uint32_t)Default_Handler,       /* TSC */
    (uint32_t)Default_Handler,       /* DMA1_Channel1 */
    (uint32_t)Default_Handler,       /* DMA1_Channel2_3 */
    (uint32_t)Default_Handler,       /* DMA1_Channel4_5_6_7 */
    (uint32_t)Default_Handler,       /* ADC1_COMP */
    (uint32_t)Default_Handler,       /* TIM1_BRK_UP_TRG_COM */
    (uint32_t)Default_Handler,       /* TIM1_CC */
    (uint32_t)Default_Handler,       /* TIM2 */
    (uint32_t)Default_Handler,       /* TIM3 */
    (uint32_t)Default_Handler,       /* TIM6_DAC */
    (uint32_t)Default_Handler,       /* TIM7 */
    (uint32_t)Default_Handler,       /* TIM14 */
    (uint32_t)Default_Handler,       /* TIM15 */
    (uint32_t)Default_Handler,       /* TIM16 */
    (uint32_t)Default_Handler,       /* TIM17 */
    (uint32_t)Default_Handler,       /* I2C1 */
    (uint32_t)Default_Handler,       /* I2C2 */
    (uint32_t)Default_Handler,       /* SPI1 */
    (uint32_t)Default_Handler,       /* SPI2 */
    (uint32_t)Default_Handler,       /* USART1 */
    (uint32_t)Default_Handler,       /* USART2 */
    (uint32_t)Default_Handler,       /* USART3_4 */
    (uint32_t)Default_Handler,       /* CEC */
    (uint32_t)Default_Handler,       /* USB */
};

/* Reset Handler */
void Reset_Handler(void)
{
    uint32_t *src, *dst;

    /* Copy .data section from flash to RAM */
    src = &_sidata;
    dst = &_sdata;
    while (dst < &_edata) {
        *dst++ = *src++;
    }

    /* Zero fill .bss section */
    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0;
    }

    /* Call main function */
    main();

    /* Should never reach here */
    while (1);
}

/* Default interrupt handler */
void Default_Handler(void)
{
    while (1);
}

/* Entry point */
void _start(void) __attribute__((alias("Reset_Handler")));
