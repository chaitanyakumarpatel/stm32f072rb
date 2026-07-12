# STM32F072RB Nucleo Bare Metal LED Blink Demo

This project demonstrates bare-metal programming for the STM32F072RB Nucleo board to blink the onboard green LED (PA5).

## Files

- `main.c` - Main application code that configures GPIOA Pin 5 and blinks the LED
- `startup.c` - Startup code with vector table and reset handler
- `stm32f072rb.ld` - Linker script for STM32F072RB (128KB Flash, 16KB RAM)
- `Makefile` - Build configuration

## Requirements

- ARM GCC toolchain (`arm-none-eabi-gcc`)
- Make
- For flashing: `st-flash` (stlink-tools) or OpenOCD

### Installing ARM GCC Toolchain

**Ubuntu/Debian:**
```bash
sudo apt-get install gcc-arm-none-eabi
```

**macOS (Homebrew):**
```bash
brew install arm-none-eabi-gcc
```

**Windows:**
Download from: https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads

## Building

```bash
make clean
make
```

This will produce:
- `blink.elf` - ELF format binary
- `blink.bin` - Raw binary for flashing
- `blink.hex` - Intel HEX format

## Flashing

### Using st-flash (ST-LINK utility):
```bash
make flash
```

### Using OpenOCD:
```bash
make flash-openocd
```

### Manual flashing with OpenOCD:
```bash
openocd -f interface/stlink.cfg -f target/stm32f0x.cfg -c "program blink.bin 0x08000000 verify reset exit"
```

## Hardware

- **Board**: STM32F072RB Nucleo
- **LED**: Onboard green LED connected to PA5
- **Debugger**: Built-in ST-LINK/V2-1

## How It Works

1. The startup code initializes the stack pointer and copies initialized data from flash to RAM
2. The main function enables the GPIOA clock via RCC
3. PA5 is configured as a push-pull output
4. The main loop toggles PA5 high and low with delays to create a blinking effect

## Register Addresses Used

- RCC Base: 0x40021000
- GPIOA Base: 0x48000000
- RCC AHBENR: Offset 0x14 (bit 17 enables GPIOA)
- GPIO MODER: Offset 0x00 (mode register)
- GPIO OSPEEDR: Offset 0x08 (speed register)
- GPIO PUPDR: Offset 0x0C (pull-up/pull-down register)
- GPIO BSRR: Offset 0x18 (set/reset register)
