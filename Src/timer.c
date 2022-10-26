
#include "stm32f7xx.h"
#include "timer.h"

void init_TIMER8(void)
{
    // Вкл. тактирование модуля TIM8.
    RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;

    // Настраиваем:
    //      Предделитель: 1
    //      Макс. счёт: 1080 (100 кГц)
    TIM8->PSC = 0;
    TIM8->ARR = 216000000/100000/2;

    // Регистр сравнения: 540 (50% заполнение).
    TIM8->CCR1 = TIM8->ARR / 2;

    // Симметричный счёт (режим 2).
    TIM8->CR1 |= TIM_CR1_CMS_1;

    // Вкл. канал сравнения.
    TIM8->CCER |= TIM_CCER_CC1E;

    // Режим ШИМ 1.
    TIM8->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;

    // Вкл. буферизацию.
    TIM8->CCMR1 |= TIM_CCMR1_OC1PE;

    // Вкл. физический канал выхода.
    TIM8->BDTR |= TIM_BDTR_MOE;

    // Включение прерывания по обновлению.
    TIM8->DIER |= TIM_DIER_UIE;

    // Вкл. генерацию TRGO по событию обновления (Update).
    TIM8->CR2 |= TIM_CR2_MMS_1;

    // Вкл. счёт таймера.
    TIM8->CR1 |= TIM_CR1_CEN;
}
