#include "stm32f4xx.h"

void delay(volatile uint32_t count) {
    while (count--);
}

int main(void) {
    // Enable GPIOA clock
    RCC->AHB1ENR |= (1 << 0);

    // Configure PA5 as general purpose output
    GPIOA->MODER &= ~(3 << 10);
    GPIOA->MODER |=  (1 << 10);

    while (1) {
        GPIOA->ODR |=  (1 << 5);  // LED on
        delay(500000);
        GPIOA->ODR &= ~(1 << 5);  // LED off
        delay(500000);
    }
}