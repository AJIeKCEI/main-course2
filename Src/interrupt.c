#include "stm32f7xx.h"
#include "interrupt.h"

void init_INTERRUPT(void)
{
	//Выбор варианта группирования прерывания 3 ( 16 групп по 16 подприоритет)
	NVIC_SetPriorityGrouping(3);
	//Установка приоретета прерывания TIM8_UP_TIM13: группа 1, подприоритет 1.
	NVIC_SetPriority(TIM8_UP_TIM13_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,1));

	//Включаем прерываний TIM8_UP_TIM13 в NVIC
	NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);


}

void TIM8_UP_TIM13_IRQHandler(void)
{
	// Сбрасываем флаг прерывания ТИМ8 по обновлению.
	TIM8-> SR &= ~TIM_SR_UIF;

	GPIOD->ODR ^= 1<<6;

}
