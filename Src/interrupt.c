#include "stm32f7xx.h"
#include "interrupt.h"
#include "dsp.h"


//volatile float TEMPERATURA;
//extern volatile float TEMPERATURE;
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

void DMA2_Stream0_IRQHandler(void)
{
    // Сброс флага прерывания DMA2_Stream0 по окончанию передачи данных.
    DMA2->LIFCR |= DMA_LIFCR_CTCIF0;

    // Ожидание выполнения всех инструкций в конвейере (pipeline).
    __ISB();

    const float av_slope = 2.5 * 0.001;
    const float v25 = 0.76;

    extern volatile unsigned int ADC_Buffer[];

    float v_sense = (float)ADC_Buffer[3] * (3.3f/4095.f);

    volatile float TEMPERATURE;

    TEMPERATURE = (v_sense - v25)/av_slope + 25.f;

    unsigned int dac1, dac2;
    // вывод температуры
    dac1 = TEMPERATURE*(4095.f/100.f);

    dac2 = MovingFloatFilter(&TEMPERATURE_MOV, TEMPERATURE) * (4095.f/100.f);



    // Запись чисел в ЦАП1 и ЦАП2.
    DAC->DHR12RD = dac1 | (dac2 << 16);

}


