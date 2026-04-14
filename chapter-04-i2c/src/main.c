#include "stm32f4xx.h"

volatile uint8_t received_byte = 0;

void i2c_master_send(uint8_t addr, uint8_t data) {
    I2C1->CR1 |= (1 << 8);
    while (!(I2C1->SR1 & (1 << 0)));
    I2C1->DR = (addr << 1) | 0;
    while (!(I2C1->SR1 & (1 << 1)));
    (void)I2C1->SR2;
    I2C1->DR = data;
    while (!(I2C1->SR1 & (1 << 2)));
    I2C1->CR1 |= (1 << 9);
}

uint8_t i2c_slave_receive(void) {
    while (!(I2C1->SR1 & (1 << 1)));
    (void)I2C1->SR2;
    while (!(I2C1->SR1 & (1 << 6)));
    return I2C1->DR;
}

int main(void) {
    // Step 1: Enable clocks
    RCC->AHB1ENR |= (1 << 1);   // GPIOB
    RCC->APB1ENR |= (1 << 21);  // I2C1

    // Step 2: Configure PB6 (SCL) and PB7 (SDA) as AF4, open-drain
    GPIOB->MODER  &= ~(3 << 12);
    GPIOB->MODER  |=  (2 << 12);
    GPIOB->OTYPER |=  (1 << 6);
    GPIOB->AFR[0] &= ~(0xF << 24);
    GPIOB->AFR[0] |=  (4   << 24);

    GPIOB->MODER  &= ~(3 << 14);
    GPIOB->MODER  |=  (2 << 14);
    GPIOB->OTYPER |=  (1 << 7);
    GPIOB->AFR[0] &= ~(0xF << 28);
    GPIOB->AFR[0] |=  (4   << 28);

    // Step 3: Configure I2C1 master
    I2C1->CR2    =  16;
    I2C1->CCR    =  80;
    I2C1->TRISE  =  17;
    I2C1->CR1   |=  (1 << 0);

    // Step 4: Configure slave address 0x52
    I2C1->CR1   &= ~(1 << 0);
    I2C1->OAR1   =  (0x52 << 1);
    I2C1->OAR1  |=  (1 << 14);
    I2C1->CR1   |=  (1 << 0);
    I2C1->CR1   |=  (1 << 10);

    // Step 5: Send and receive
    i2c_master_send(0x52, 0xAB);
    received_byte = i2c_slave_receive();

    // Verify: inspect received_byte in debugger, should be 0xAB
    while (1);
}
