#include "stm32f7xx.h"
#include "dsp.h"
#include <stdlib.h>

MovingFloatFilter_Struct FILTER_MOV;

MovingFloatFilter_Struct FILTER_MFF;

Low_Filter_1st_Order_Struct FILTER_1ORD =
{
		.b0= TS /(TAU_1ORD + TS),
		.a1 = -TAU_1ORD / (TAU_1ORD+TS)
};

//y = MovingFloatFilter(&TEMPERATURE_MFF, TEMPERATURE)
/**
 * \brief	Функция фильтра скользящего среднего.
 *
 * \param	fiter:  структура с параметром фильтра
 * \param	x: входная переменная.
 *
 *\return y: среднее значение
 */

float MovingFloatFilter(MovingFloatFilter_Struct * filter, float x)
{
	//отнимаем от суммы н-1 точку и прибавляем х0ъ точку.
	filter->sum = filter->sum - filter->buf[filter->pointer]+x;
	//добавляем новую точку в массив точек.
	filter->buf[filter->pointer]=x;

	//инкриментируем указатель счетчика
	if(++filter->pointer>= MAX_MOVING_FLOAT_SIZE)
		filter->pointer=0;

	//Вычисляем среднее значение
	return filter->sum*(1.f/MAX_MOVING_FLOAT_SIZE);





}

int cmp(const float *a, const float *b){
	return *a -*b;

}

float MedianFloatFilter(MedianFloatFilter_Struct * filter, float x)
{
	//отнимаем от суммы н-1 точку и прибавляем х0ъ точку.
	//filter->sum = filter->sum - filter->buf[filter->pointer]+x;
	//добавляем новую точку в массив точек.
	filter->buf[filter->pointer]=x;

	//инкриментируем указатель счетчика
	if(++filter->pointer>= MAX_MEDIAN_FLOAT_SIZE)
		filter->pointer=0;

	//Вычисляем среднее значение


	for(int i=0; i<MAX_MEDIAN_FLOAT_SIZE; i++)
		filter->buf_sorted[i]=filter->buf[i];
   //memcpy(filter->buf_sorted,filter->buf, sixeof(filter->buf));
	// Ждем окончания копирования (выхода всех инструкций и данных из конвейера).
	__ISB();
	__DSB();
	//сортируем массив
	qsort(filter->buf_sorted, MAX_MEDIAN_FLOAT_SIZE, sizeof(filter->buf_sorted[0]),(int (*)(const void*, const void *))cmp);

	//return filter->buf_sorted[MAX_MEDIAN_FLOAT_SIZE/2];
	return filter->buf_sorted[MAX_MEDIAN_FLOAT_SIZE>>1];




}

/**
 *\brief функция фильтра нижних частот 1го порядка.
 *\
 *
 */
float Low_Filter_1st_Order(Low_Filter_1st_Order_Struct*filter, float x)
{
	float y = x*filter->b0-filter->yn*filter->a1;
	// сохраняем выходную переменную для следущего такта расчета.
	filter->yn = y;

	return y;
}
