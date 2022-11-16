#include "stm32f7xx.h"
#include "interrupt.h"
#include "dsp.h"

//volatile float TEMPERATURA;
//extern volatile float TEMPERATURE;
void init_INTERRUPT(void) {
	//Выбор варианта группирования прерывания 3 ( 16 групп по 16 подприоритет)
	NVIC_SetPriorityGrouping(3);
	//Установка приоретета прерывания TIM8_UP_TIM13: группа 1, подприоритет 1.
	//NVIC_SetPriority(TIM8_UP_TIM13_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 1));

	//Включаем прерываний TIM8_UP_TIM13 в NVIC
	//NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);

	// Установка приоритет прерывания DMA2_Stream0_IRQn: группа 2, подприоритет 1.
	NVIC_SetPriority(DMA2_Stream0_IRQn,
			NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 1));

	// Включаем прерываний DMA2_Stream0_IRQn в NVIC.
	NVIC_EnableIRQ(DMA2_Stream0_IRQn);
}

void TIM8_UP_TIM13_IRQHandler(void) {
// Сброс флага прерывания TIM8 по обновлению.
	TIM8->SR &= ~TIM_SR_UIF;

// Ожидание выполнения всех инструкций в конвейере (pipeline).
	__ISB();

//GPIOD->ODR ^= 1 << 6;
//GPIOD->ODR ^= GPIO_ODR_OD6;
//GPIOD->ODR = GPIOD->ODR ^ (1 << 6);
}

/*void ADC_IRQHandler(void)
 {
 //Сброс флага прерывания по окончанию преобразования
 ADC1->SR &= ~ADC_SR_EOC;

 // Ожидание выполнения  всех инструкций в конвеере архитектуры АРМ(pipline)
 __ISB();

 const float av_slope = 2.5f*0.001f;
 const float v25 = 0.76;

 float v_sense = ADC1->DR *(3.3f/4095.f);

 TEMPERATURE = (v_sense - v25)/av_slope * 25.f;

 }*/

