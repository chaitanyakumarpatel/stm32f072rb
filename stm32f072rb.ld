/*
 * STM32F072RB Linker Script
 * Flash: 128KB, RAM: 16KB
 */

MEMORY
{
    FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 128K
    RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 16K
}

SECTIONS
{
    /* Vector table at the beginning of flash */
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } >FLASH

    /* Code section */
    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
        _etext = .;
    } >FLASH

    /* Initialized data section */
    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } >RAM AT> FLASH

    _sidata = LOADADDR(.data);

    /* Uninitialized data section */
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } >RAM

    /* Stack section */
    ._stack :
    {
        . = ALIGN(8);
        . = . + 0x1000;  /* 4KB stack */
        . = ALIGN(8);
        _estack = .;
    } >RAM
}
