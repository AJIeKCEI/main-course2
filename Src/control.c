#include "stm32f7xx.h"
#include "control.h"
#include "dsp.h"



Control_Struct Boost_Control;
Measure_Struct Boost_Measure =
{
#define V25 (0.76)
#define AV_SLOPE (2.5*0.001)

	.shift =
	{
		.inj =0,// устанавливается при нажатии SW1
		.u2 = 2.6106,
		.iL =0,
		.temperature =25.f - V25/ AV_SLOPE,
		.u1 =0,
		.in =0
	},
	.scale =
	{
			.u2 = -4.4559e-04,
			.iL = 1.9794e-03,
			.temperature = 3.3 / (4095. * AV_SLOPE),
			.u1 = 0.024982,
			.in = 9.8970e-04

	},


	.dac[0] = { .shift = 4095/2, .scale = 4095./3.3},
	.dac[1] = { .shift = 4095/2, .scale = 4095./3.3},
};

Protect_Struct Boost_Protect;

void shift_and_scale(void);
void set_shifts(void);

void DMA2_Stream0_IRQHandler(void)
{
    // Сброс флага прерывания DMA2_Stream0 по окончанию передачи данных.
    DMA2->LIFCR |= DMA_LIFCR_CTCIF0;

    // Ожидание выполнения всех инструкций в конвейере (pipeline).
    __ISB();

   shift_and_scale();

    unsigned int dac1, dac2;
    // вывод температуры
    Boost_Measure.dac[0].data = Boost_Measure.data.inj;
    Boost_Measure.dac[1].data = MovingFloatFilter(&FILTER_MOV,Boost_Measure.data.inj);


    dac1 = Boost_Measure.dac[0].scale*Boost_Measure.dac[0].data+Boost_Measure.dac[0].shift;
    dac2 = Boost_Measure.dac[1].scale*Boost_Measure.dac[1].data+Boost_Measure.dac[0].shift;



    // Запись чисел в ЦАП1 и ЦАП2.
    DAC->DHR12RD = dac1 | (dac2 << 16);

}

/**
 * *\
 *
 */

void shift_and_scale(void)
{
	extern volatile unsigned int ADC_Buffer[];

	Boost_Measure.data.inj = Boost_Measure.scale.inj*ADC_Buffer[0]+Boost_Measure.shift.inj;
	Boost_Measure.data.u2 = Boost_Measure.scale.u2*ADC_Buffer[1]+Boost_Measure.shift.u2;
	Boost_Measure.data.iL = Boost_Measure.scale.iL*ADC_Buffer[2]+Boost_Measure.shift.iL;
	Boost_Measure.data.temperature = Boost_Measure.scale.temperature*ADC_Buffer[3]+Boost_Measure.shift.temperature;
	Boost_Measure.data.u1 = Boost_Measure.scale.u1*ADC_Buffer[4]+Boost_Measure.shift.u1;
	Boost_Measure.data.in = Boost_Measure.scale.in*ADC_Buffer[5]+Boost_Measure.shift.in;

}

void set_shifts(void)
{
	if (Boost_Measure.count == 0)
		return;

	if (Boost_Measure.count == SET_SHIFTS_MAX_COUNT)
		Boost_Measure.shift.inj = Boost_Measure.sum.inj=0;
	//
	Boost_Measure.sum.inj += Boost_Measure.sum.inj;

	//
	if (--Boost_Measure.count ==0)
		Boost_Measure.shift.inj = -Boost_Measure.sum.inj*(1.f/SET_SHIFTS_MAX_COUNT);

}
