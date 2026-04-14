#include "stm32f4xx.h"

void EXTI15_10_IRQHandler(void) {
    if (EXTI->PR & (1 << 13)) {
        GPIOA->ODR ^= (1 << 5);   // Toggle LED
        EXTI->PR   |= (1 << 13);  // Clear pending flag
    }
}

int main(void) {
    // Step 1: Enable clocks
    RCC->AHB1ENR |= (1 << 0);   // GPIOA
    RCC->AHB1ENR |= (1 << 2);   // GPIOC
    RCC->APB2ENR |= (1 << 14);  // SYSCFG

    // Step 2: Configure PA5 as output (LED)
    GPIOA->MODER &= ~(3 << 10);
    GPIOA->MODER |=  (1 << 10);

    // Step 3: Configure PC13 as input with pull-up
    GPIOC->MODER &= ~(3 << 26);
    GPIOC->PUPDR &= ~(3 << 26);
    GPIOC->PUPDR |=  (1 << 26);

    // Step 4: Configure EXTI13 for falling edge on PC13
    SYSCFG->EXTICR[3] &= ~(0xF << 4);
    SYSCFG->EXTICR[3] |=  (2   << 4);
    EXTI->FTSR        |=  (1 << 13);
    EXTI->IMR         |=  (1 << 13);

    // Step 5: Enable EXTI15_10 in NVIC
    NVIC_EnableIRQ(EXTI15_10_IRQn);
    NVIC_SetPriority(EXTI15_10_IRQn, 1);

    // Step 6: Wait for interrupts
    while (1);
}
