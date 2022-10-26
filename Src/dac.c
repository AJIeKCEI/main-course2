
#include "stm32f7xx.h"
#include "dac.h"

void init_DAC(void)
{
    // Вкл. тактирование ЦАП.
    RCC->APB1ENR |= RCC_APB1ENR_DACEN;

    // Вкл. ЦАП1 и ЦАП2.
    DAC->CR |= DAC_CR_EN1 | DAC_CR_EN2;
}
