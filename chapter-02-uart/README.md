# Chapter 2: UART — Sending text over a serial port using bare-metal register writes

## Prerequisites

Chapter 0 environment setup complete (arm-none-eabi toolchain, OpenOCD, make).

## Build

```bash
cd chapter-02-uart && make
```

## Flash

```bash
make flash
```

## View output

Open PuTTY, select the COM port for your ST-LINK adapter, and set the baud rate to **115200**.
