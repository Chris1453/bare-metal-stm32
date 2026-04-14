# Bare Metal STM32: From Zero to Register-Level Confidence

A project-driven guide for ECE students and makers who want to actually 
understand what's happening inside the chip — not just copy-paste HAL code 
that magically works.

## What's Inside

| Chapter | Topic | What You Build |
|---------|-------|----------------|
| 0 | Environment Setup | ARM GCC, OpenOCD, Make, VS Code |
| 1 | GPIO | Blinking LED — no HAL, no CubeMX |
| 2 | UART | Serial debug output over USART2 |
| 3 | Timers & PWM | Breathing LED effect with TIM2 |
| 4 | I2C | Protocol fundamentals via loopback |
| 5 | Interrupts & NVIC | Button toggle with EXTI |

## Hardware Required

- STM32 Nucleo-F411RE
- USB Type-A to Mini-B cable
- LED + 330Ω resistor (Chapters 1, 3, 5)
- Male-to-male jumper wires

## Getting Started

Clone the repo and start with Chapter 0:
``` bash
git clone https://github.com/Chris1453/bare-metal-stm32.git
cd bare-metal-stm32/chapter-00-setup
```

Each chapter folder is self-contained:
``` bash
cd chapter-01-gpio
make
make flash
```
## Reference Manuals

- UM1724 — Nucleo-F411RE board user manual
- RM0383 — STM32F411xC/E reference manual (register descriptions)
- DS10314 — STM32F411xC/E datasheet (alternate function mapping)

All available free from st.com.

## The Full Guide

The complete PDF guide with detailed explanations, binary diagrams, 
HAL comparisons, and debugging sections is available on Gumroad:

[Get the guide →](https://chriskim3.gumroad.com/l/832)

## Author

Chris Kim — Computer Engineering, Syracuse University  
