#include "stm32f4xx.h"

void uart_send_char(char c) {
    while (!(USART2->SR & (1 << 7)));
    USART2->DR = c;
}

void uart_send_string(const char *str) {
    while (*str) {
        uart_send_char(*str++);
    }
}

void delay(volatile uint32_t count) {
    while (count--);
}

int main(void) {
    // Step 1: Enable clocks
    RCC->AHB1ENR  |= (1 << 0);   // GPIOA
    RCC->APB1ENR  |= (1 << 17);  // USART2

    // Step 2: Configure PA2 as alternate function (USART2 TX)
    GPIOA->MODER  &= ~(3 << 4);
    GPIOA->MODER  |=  (2 << 4);
    GPIOA->AFR[0] &= ~(0xF << 8);
    GPIOA->AFR[0] |=  (7   << 8);

    // Step 3: Set baud rate (16MHz / 115200)
    USART2->BRR = 139;

    // Step 4: Enable transmitter and USART
    USART2->CR1 |= (1 << 3);
    USART2->CR1 |= (1 << 13);

    // Step 5: Send repeatedly
    while (1) {
        uart_send_string("Hello from bare-metal STM32!\r\n");
        delay(500000);
    }
}
