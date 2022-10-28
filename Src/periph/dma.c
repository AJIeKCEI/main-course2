#include "stm32f7xx.h"
#include "dma.h"

unsigned int ADC_Buffer[6];

void init_DMA(void)
{
	//Включение тактирования ДМА
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

	//настраиваем адрес источника данных
	DMA2_Stream0->PAR = (unsigned int)&ADC->CDR;

	//Адрес места записи данных ацп , назначение массива

	DMA2_Stream0->M0AR = (unsigned int)&ADC_Buffer[0];

	//Колличество
	DMA2_Stream0->NDTR = 6;
	//Выбираем канал 0 , из таблиы 26 ДМА2  стрим 0 --> каналу о, нам надо 0 в регистре сдвинуть на 25
	DMA2_Stream0->CR|= 0<<25;

	// Установка приоритета при выборе потоков ДМА для передачи
	//данных по шине данных = very high.

	DMA2_Stream0->CR|=DMA_SxCR_PL_0|DMA_SxCR_PL_1;

	// Размер данных в месте назначения(ADC) = 32 бита
	DMA2_Stream0->CR|=DMA_SxCR_PSIZE_1;

	// Размер данных в месте назначения(массив) = 32 бита
	DMA2_Stream0->CR|=DMA_SxCR_MSIZE_1;

	// Вкл режим  циклической передачи
	DMA2_Stream0->CR|=DMA_SxCR_CIRC;

	//ВКл. прерывание по окончанию передачи
	DMA2_Stream0->CR|=DMA_SxCR_TCIE;

	//ВКл. DMA2 Stream0
	DMA2_Stream0->CR|=DMA_SxCR_EN;





}
