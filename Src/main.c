/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "stm32f7xx.h"

#include "rcc.h"
#include "gpio.h"
#include "timer.h"
#include "interrupt.h"
#include "adc.h"
#include "dma.h"
#include "dac.h"

#include "control.h"

volatile float TEMPERATURE;

int main(void)
{
    // Глобальное отключение прерываний.
    __disable_irq();

    init_INTERRUPT();
    init_RCC();
    init_GPIO();
    init_DMA();
    init_ADC();
    init_TIMER8();
    init_DAC();

    // Глобальное включение прерываний.
    __enable_irq();

    /* Loop forever */
    for(;;)
    {
        //for(int i = 0; i < 100000; i++);
        //GPIOD->ODR ^= 1 << 1;

        // Проверяем PB1 (SW1) на ноль.
        if (!(GPIOB->IDR & (1 << 1)))
            Boost_Measure.count = SET_SHIFTS_MAX_COUNT;

        // Проверяем PB2 (SW2) на ноль.
        if (!(GPIOB->IDR & (1 << 2)))
        {
        	extern float REF_CONTROLLER;
        	REF_CONTROLLER = 1.f;

            timer_PWM_On();
            GPIOD->ODR &= ~((1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5));
        }
    }
}









