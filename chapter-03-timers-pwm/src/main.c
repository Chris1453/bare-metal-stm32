#include "stm32f4xx.h"

void delay(volatile uint32_t count) {
    while (count--);
}

int main(void) {
    // Step 1: Enable clocks
    RCC->AHB1ENR |= (1 << 0);   // GPIOA
    RCC->APB1ENR |= (1 << 0);   // TIM2

    // Step 2: Configure PA5 as TIM2_CH1 (AF1)
    GPIOA->MODER  &= ~(3 << 10);
    GPIOA->MODER  |=  (2 << 10);
    GPIOA->AFR[0] &= ~(0xF << 20);
    GPIOA->AFR[0] |=  (1   << 20);

    // Step 3: Configure TIM2 for 1kHz PWM
    TIM2->PSC    =  15;
    TIM2->ARR    =  999;
    TIM2->CCMR1 &= ~(7 << 4);
    TIM2->CCMR1 |=  (6 << 4);
    TIM2->CCMR1 |=  (1 << 3);
    TIM2->CCER  |=  (1 << 0);
    TIM2->CR1   |=  (1 << 7);

    // Step 4: Initial duty cycle
    TIM2->CCR1 = 0;

    // Step 5: Start timer
    TIM2->CR1 |= (1 << 0);

    // Step 6: Breathing effect
    while (1) {
        for (int i = 0; i <= 999; i++) {
            TIM2->CCR1 = i;
            delay(2000);
        }
        for (int i = 999; i >= 0; i--) {
            TIM2->CCR1 = i;
            delay(2000);
        }
    }
}
