#include "stm32f7xx.h"
#include "interrupt.h"


volatile float TEMPERATURA;

void init_INTERRUPT(void)
{
	//Выбор варианта группирования прерывания 3 ( 16 групп по 16 подприоритет)
	NVIC_SetPriorityGrouping(3);
	//Установка приоретета прерывания TIM8_UP_TIM13: группа 1, подприоритет 1.
	NVIC_SetPriority(TIM8_UP_TIM13_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,1));

	//Включаем прерываний TIM8_UP_TIM13 в NVIC
	NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);


	//Установка приоретета прерывания TIM8_UP_TIM13: группа 1, подприоритет 1.
	NVIC_SetPriority(ADC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,1));

	//Включаем прерываний TADC в NVIC
	NVIC_EnableIRQ(ADC_IRQn);

}

void TIM8_UP_TIM13_IRQHandler(void)
{
	// Сбрасываем флаг прерывания ТИМ8 по обновлению.
	TIM8-> SR &= ~TIM_SR_UIF;

	// Ожидание выполнения  всех инструкций в конвеере архитектуры АРМ(pipline)
	__ISB();

	GPIOD->ODR ^= 1<<6;

}

void ADC_IRQHandler(void)
{
	//Сброс флага прерывания по окончанию преобразования
	ADC1->SR &= ~ADC_SR_EOC;

	// Ожидание выполнения  всех инструкций в конвеере архитектуры АРМ(pipline)
	__ISB();

	const float av_slope = 2.5f*0.001f;
	const float v25 = 0.76;

	float v_sense = ADC1->DR *(3.3f/4095.f);

	TEMPERATURA = (v_sense - v25)/av_slope * 25.f;

}
