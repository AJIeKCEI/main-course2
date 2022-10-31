#include "stm32f7xx.h"
#include "adc.h"

void init_ADC(void) {
	//
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
	RCC->APB2ENR |= RCC_APB2ENR_ADC3EN;

	//Вкл АЦП 1 2 3
	ADC1->CR2 |= ADC_CR2_ADON;
	ADC2->CR2 |= ADC_CR2_ADON;
	ADC3->CR2 |= ADC_CR2_ADON;

	// Выбираем 18 канал ADC1(датчик температуры)
	ADC1->SQR3 |= 3; // Cигнал инжекции
	ADC2->SQR3 |= 0; //Выходное напряжение
	ADC3->SQR3 |= 14; //Ток реактора

	//Выбираем каналы
	ADC1->SQR3 |= 18 << 5; //Температура
	ADC2->SQR3 |= 13 << 5; //Выходное напряжение
	ADC3->SQR3 |= 12 << 5; //Выходной ток
	//Выбираем
	ADC1->SQR1 |= 1 << 20;
	ADC2->SQR1 |= 1 << 20;
	ADC3->SQR1 |= 1 << 20;

	//Включение режима сканирования
	ADC1->CR1 |= ADC_CR1_SCAN;
	ADC2->CR1 |= ADC_CR1_SCAN;
	ADC3->CR1 |= ADC_CR1_SCAN;

	// ВКл режим преобразования непрерывный
	//ADC1->CR2 |= ADC_CR2_CONT;

	//Устанавливаем циклов 480
	ADC1->SMPR1 |= ADC_SMPR1_SMP18_0;
	ADC1->SMPR2 |= ADC_SMPR2_SMP3_0;

	ADC2->SMPR2 |= ADC_SMPR2_SMP0_0;
	ADC2->SMPR1 |= ADC_SMPR1_SMP13_0;

	ADC3->SMPR1 |= ADC_SMPR1_SMP14_0;
	ADC3->SMPR1 |= ADC_SMPR1_SMP12_0;

	// Вкл запуск ацп от сигнала Tim8 TRG0
	ADC1->CR2 |= ADC_CR2_EXTSEL_0 | ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_2;

	// Запуск АЦП от TIM8 TRGO по нарастающему фронту.
	ADC1->CR2 |= ADC_CR2_EXTEN_0;

	ADC->CCR |= ADC_CCR_TSVREFE;

	//Режим работы с ДМА 1
	ADC->CCR |= ADC_CCR_DMA_0;
	//Вкл запуск запрооса дма по окончанию преобразования
	ADC->CCR |= ADC_CCR_DDS;

	//Прерывание при окончании преобразования
	//ADC1->CR1 |= ADC_CR1_EOCIE;

	/*
	 if(num<=6)
	 ADC1->SQR3|= 18<<(5*(num-1)); //передвигать на пять битов и выбрать нужный регистр SQR
	 if else (num<=12)
	 ADC1->SQR2|= 18<<(5*(num-1));
	 */

	// Режим Triple ADC Mode.
	ADC->CCR |= ADC_CCR_MULTI_1 | ADC_CCR_MULTI_2 | ADC_CCR_MULTI_4;

}

