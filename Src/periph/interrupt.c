
#include "stm32f7xx.h"
#include "interrupt.h"

void init_INTERRUPT(void)
{
    // Выбор варианта группирования прерываний 3 (16 групп по 16 подприоритет).
    NVIC_SetPriorityGrouping(3);

    // Установка приоритет прерывания TIM8_UP_TIM13: группа 1, подприоритет 1.
    //NVIC_SetPriority(TIM8_UP_TIM13_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 1));

    // Включаем прерываний TIM8_UP_TIM13 в NVIC.
    //NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);

    // Установка приоритет прерывания DMA2_Stream0_IRQn: группа 2, подприоритет 1.
    NVIC_SetPriority(DMA2_Stream0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 1));

    // Включаем прерываний DMA2_Stream0_IRQn в NVIC.
    NVIC_EnableIRQ(DMA2_Stream0_IRQn);
}

void TIM8_UP_TIM13_IRQHandler(void)
{
    // Сброс флага прерывания TIM8 по обновлению.
    TIM8->SR &= ~TIM_SR_UIF;

    // Ожидание выполнения всех инструкций в конвейере (pipeline).
    __ISB();

    //GPIOD->ODR ^= 1 << 6;
    //GPIOD->ODR ^= GPIO_ODR_OD6;
    //GPIOD->ODR = GPIOD->ODR ^ (1 << 6);
}

