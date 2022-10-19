#include "stm32f7xx.h"
#include "adc.h"

void init_ADC(void)
{
	//
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	//Вкл АЦП 1
	ADC1->CR2 |= ADC_CR2_ADON;

	// Выбираем 18 канал ADC1(датчик температуры)
	ADC1->SQR3|= 18;

	// ВКл режим преобразования ytghthsdyjuj
	ADC1->CR2 |= ADC_CR2_CONT;


	//Устанавливаем циклов 480
	ADC1->SMPR1 |= ADC_SMPR1_SMP18_0 |ADC_SMPR1_SMP18_1|ADC_SMPR1_SMP18_2;

	// Датчика температуры включение
	ADC->CCR |= ADC_CCR_TSVREFE;

	//Прерывание при окончании преобразования
	ADC1->CR1 |= ADC_CR1_EOCIE;

	/*
	if(num<=6)
		ADC1->SQR3|= 18<<(5*(num-1)); //передвигать на пять битов и выбрать нужный регистр SQR
	if else (num<=12)
		ADC1->SQR2|= 18<<(5*(num-1));
	*/


	//Запуск преобразования
	ADC1->CR2 |= ADC_CR2_SWSTART;


}


