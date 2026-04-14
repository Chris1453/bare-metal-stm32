# Chapter 04 — I2C

I2C loopback demo using I2C1 on PB6/PB7

## Prerequisites

Chapter 0 environment setup complete

## Hardware

Connect PB6 to PB7 with a single male-to-male jumper wire

## Build

```
cd chapter-04-i2c && make
```

## Flash

```
make flash
```

## Verification

Inspect `received_byte` in debugger — should be `0xAB`
