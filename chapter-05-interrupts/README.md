# Chapter 05 — Interrupts

Button interrupt on PC13 toggles LED on PA5

## Prerequisites

Chapter 0 environment setup complete

## Hardware

- LED + 330Ω resistor on PA5 (D13)
- No extra wiring needed for button (B1 is onboard)

## Build

```
cd chapter-05-interrupts && make
```

## Flash

```
make flash
```

## Expected Result

Pressing the blue B1 button toggles the LED.
