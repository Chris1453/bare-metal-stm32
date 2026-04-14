# Bare-Metal STM32F411RE

A minimal bare-metal project for the STM32F411RE (Nucleo-64 board) with no HAL dependency.

## Prerequisites

- `arm-none-eabi-gcc` toolchain on your PATH
- `openocd` on your PATH (for flashing)

Install on Ubuntu/Debian:
```bash
sudo apt install gcc-arm-none-eabi openocd
```

Install on Windows (via Chocolatey):
```powershell
choco install gcc-arm-embedded openocd
```

## Project Structure

```
bare-metal-stm32/
  src/
    main.c                   # Application entry point
  startup/
    startup_stm32f411re.s    # Vector table, Reset_Handler, data/BSS init
  linker/
    stm32f411re.ld           # Linker script (512KB flash / 128KB RAM)
  Makefile
  README.md
```

## Build

```bash
make
```

The compiled output lands in `build/`:
- `firmware.elf` — ELF with debug symbols
- `firmware.bin` — Raw binary for flashing
- `firmware.map` — Linker map file

## Flash

Connect your Nucleo board via USB (ST-LINK), then:

```bash
make flash
```

This uses OpenOCD with the ST-LINK interface and STM32F4 target configuration.

## Clean

```bash
make clean
```

## Memory Map (STM32F411RE)

| Region | Start      | Size  |
|--------|-----------|-------|
| FLASH  | 0x08000000 | 512KB |
| RAM    | 0x20000000 | 128KB |
