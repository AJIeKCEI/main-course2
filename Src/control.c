#include "stm32f7xx.h"
#include "control.h"
#include "dsp.h"
#include "timer.h"

Control_Struct Boost_Control;
Measure_Struct Boost_Measure = {
#define V25 (0.76)
#define AV_SLOPE (2.5*0.001)

		.shift = {
				.inj = 0, // устанавливается при нажатии SW1
				.u2 = 100.4,
				.iL = 0,
				.temperature = 25.f - V25 / AV_SLOPE,
				.u1 = 0, .in = 0 },
				.scale = { .inj = 3.3 / 4095.,
				.u2 = -0.001880341880341881,
				.iL = 1.9794e-03,
				.temperature = 3.3/ (4095. * AV_SLOPE),
				.u1 = 0.024982,
				.in = 9.8970e-04

		},



		.dac[0] = { .shift = 4095 / 2, .scale = 4095. / 3.3 },
		.dac[1] = {	.shift = 4095 / 2, .scale = 4095. / 3.3 },
};

Protect_Struct Boost_Protect =
{
		.iL_max = 6.,
		.in_max = 3.,
		.u1_max = 90.,
		.u2_max = 100.,


		.iL_n =2.,
		.iL_int_max = 1. *5.

};

void shift_and_scale(void);
void set_shifts(void);
void protect_software(void);
void integral_protect(void);

void DMA2_Stream0_IRQHandler(void) {
	// Сброс флага прерывания DMA2_Stream0 по окончанию передачи данных.
	DMA2->LIFCR |= DMA_LIFCR_CTCIF0;

	// Ожидание выполнения всех инструкций в конвейере (pipeline).
	__ISB();

	shift_and_scale();
	protect_software();
	set_shifts();
	unsigned int dac1, dac2;
	// вывод температуры
	Boost_Measure.dac[0].data = Boost_Measure.data.inj;
	//Boost_Measure.dac[1].data = MovingFloatFilter(&FILTER_MOV, Boost_Measure.data.inj);
	Boost_Measure.dac[1].data = Low_Filter_1st_Order(&FILTER_1ORD,Boost_Measure.data.inj);


	dac1 = Boost_Measure.dac[0].scale * Boost_Measure.dac[0].data
			+ Boost_Measure.dac[0].shift;
	dac2 = Boost_Measure.dac[1].scale * Boost_Measure.dac[1].data
			+ Boost_Measure.dac[1].shift;

	// Запись чисел в ЦАП1 и ЦАП2.
	DAC->DHR12RD = dac1 | (dac2 << 16);

}

/**
 * *\
 *
 */

void shift_and_scale(void) {
	extern volatile unsigned int ADC_Buffer[];

	Boost_Measure.data.inj = Boost_Measure.scale.inj * ADC_Buffer[0]
			+ Boost_Measure.shift.inj;
	Boost_Measure.data.u2 = Boost_Measure.scale.u2 * ADC_Buffer[1]
			+ Boost_Measure.shift.u2;
	Boost_Measure.data.iL = Boost_Measure.scale.iL * ADC_Buffer[2]
			+ Boost_Measure.shift.iL;
	Boost_Measure.data.temperature = Boost_Measure.scale.temperature
			* ADC_Buffer[3] + Boost_Measure.shift.temperature;
	Boost_Measure.data.u1 = Boost_Measure.scale.u1 * ADC_Buffer[4]
			+ Boost_Measure.shift.u1;
	Boost_Measure.data.in = Boost_Measure.scale.in * ADC_Buffer[5]
			+ Boost_Measure.shift.in;

}

void set_shifts(void) {
	if (Boost_Measure.count == 0)
		return;

	if (Boost_Measure.count == SET_SHIFTS_MAX_COUNT)
		Boost_Measure.shift.inj = Boost_Measure.sum.inj = 0;
	//
	// Накапливаем сумму.
	Boost_Measure.sum.inj += Boost_Measure.data.inj
			* (1.f / SET_SHIFTS_MAX_COUNT);

	// Декремент счётчика и проверка окончания автоопределения смещений.
	if (--Boost_Measure.count == 0)
		Boost_Measure.shift.inj = -Boost_Measure.sum.inj;

}

/**
 * \brief Функция программных защит
 */
void protect_software(void)
{
	if(Boost_Measure.data.iL > Boost_Protect.iL_max)
	{
		timer_PWM_off();
		GPIOD->ODR|= 1<<2;
	}
	if(Boost_Measure.data.in > Boost_Protect.in_max)
	{
		timer_PWM_off();
		GPIOD->ODR|= 1<<3;
	}
	if(Boost_Measure.data.u1 > Boost_Protect.u1_max)
	{
		timer_PWM_off();
		GPIOD->ODR|= 1<<4;
	}
	if(Boost_Measure.data.u2 > Boost_Protect.u2_max)
	{
		timer_PWM_off();
		GPIOD->ODR|= 1<<5;
	}
	//
integral_protect();
}

/**
 *\brief Функция интегрально-токовой защиты по ток реактора(входному току)
 *
 */
void integral_protect(void)
{
	//Разница между токами реактора и номинальным значением
	float x = Boost_Measure.data.iL - Boost_Protect.iL_n;

	Boost_Protect.iL_int_sum = Boost_Protect.iL_int_sum +x*TS;

	//Обнулим интегратор сумму в нормальном режиме работы.
	if (Boost_Protect.iL_int_sum<0)
		Boost_Protect.iL_int_sum =0;

	//Условия срабатывания защиты
	if(Boost_Protect.iL_int_sum> Boost_Protect.iL_int_max)
	{
		Boost_Protect.iL_int_sum = 0;
		timer_PWM_off();
		GPIOD->ODR|= 1<<1;

	}
}
