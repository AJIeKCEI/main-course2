
#include "stm32f7xx.h"
#include "control.h"
#include "dsp.h"
#include "timer.h"

Control_Struct Boost_Control =
{
    .pid_current =
    {
        // Пропорциональный коэффициент.
        .kp = 0.133399262551201,

        .integrator =
        {
            // Интегральный коэффициент.
            .k = 438.310314391716 * (TS / 2.),
            .sat = { .min = 0.02, .max = 0.98 }
        },

        .diff =
        {
            // Дифференциальный коэффициент.
            .k = 2.09748906707283e-7 * FS
        },

        .sat = { .min = 0.02, .max = 0.98 }
    }
};
Measure_Struct Boost_Measure =
{
#define V25 (0.76)
#define AV_SLOPE (2.5 * 0.001)

    .shift =
    {
        .inj = 0,   // Устанавливается по нажатию кнопки SW1.
        .u2 = 100.4,
        .iL = 0,
        .temperature = 25.f - V25 / AV_SLOPE,
        .u1 = 0,
        .in = 0
    },

    .scale =
    {
        .inj = 3.3/4095.,
        .u2 = -0.001880341880341881,
        .iL = 1.9794e-03,
        .temperature = 3.3 / (4095. * AV_SLOPE),
        .u1 = 0.024982, // 31 / 4095 * 3.3
        .in = 9.8970e-04
    },

    .dac[0] = { .shift = 0, .scale = 4095. },
    .dac[1] = { .shift = 0, .scale = 4095. },
};
Protect_Struct Boost_Protect =
{
    .iL_max = 8.,
    .in_max = 3.,
    .u1_max = 90.,
    .u2_max = 100.,

#define T_INT_MAX   (10.)       // Время срабатывания интегрально-токовой защиты при перегрузке на I_INT_MAX.
#define I_INT_MAX   (2.)        // Ток перегрузки соответствующий времени срабатывания интегрально-токовой защиты T_INT_MAX.

    .iL_n = 5.,
    .iL_int_max = I_INT_MAX * T_INT_MAX,

    .sat =
    {
        .duty_min = 0.02,
        .duty_max = 0.98
    }
};

LinearRamp_Struct LINEAR_RAMP =
{
    .integrator =
    {
        .k = 1. / 10. * TS,
        .sat = { .min = -999999., .max = 999999. }
    }
};

SShapedRamp_Struct SSHAPED_RAMP =
{
    .integrator[0] =
    {
        .k = 1. * TS,
        .sat = { .min = -999999., .max = 999999. }
    },

    .integrator[1] =
    {
        .k = 0.25 * TS,
        .sat = { .min = -999999., .max = 999999. }
    },

    .k3 = 0.125
};

PID_Controller_Struct PID_CONTROLLER =
{
    .kp = 0.5,

    .integrator =
    {
        .k = 0.5 / 0.05 * (TS / 2.),
        .sat = { .min = 0., .max = 1. }
    },

    .sat = { .min = 0., .max = 1. }
};
//

float REF_CONTROLLER = 0.;

unsigned int TIC, TOC;

void shift_and_scale(void);
void set_shifts(void);
void protect_software(void);
void integral_protect(void);

void DMA2_Stream0_IRQHandler(void)
{
    TIC = DWT->CYCCNT;
	// Сброс флага прерывания DMA2_Stream0 по окончанию передачи данных.
    DMA2->LIFCR |= DMA_LIFCR_CTCIF0;

    // Ожидание выполнения всех инструкций в конвейере (pipeline).
    // __ISB();

    // Пересчёт значений из ADC_Buffer в физические величины.
    shift_and_scale();

    // Программные защиты.
    protect_software();

    // Автоопределение смещений.
    set_shifts();

    static unsigned int cnt =0;

    cnt ++;
    if(cnt<50)	//50=(0.01/2)*FS
    	REF_CONTROLLER = 3.5F;
    else if (cnt<100)
    	REF_CONTROLLER = 4.5F;
    else
    	cnt=0;

    //уСТАВКА ТОКА
    REF_CONTROLLER = 4.F;
    // Линейный задатчик уставки тока реактора.
  //  float iL_ramp = Linear_Ramp(&LINEAR_RAMP, REF_CONTROLLER);

    // Ошибка регулирования тока реактора.
    float error = REF_CONTROLLER - Boost_Measure.data.iL;

    // Расчёт ПИД-регулятора тока реактора.
    float out = PID_Controller(&Boost_Control.pid_current, error);

    // Выводим переменную на ЦАП2.

    float dac2_data = out;
    //Boost_Measure.dac[1].data = out;

    // Расчёт коэффициента заполнения.
    Boost_Control.duty = out + Boost_Measure.data.inj*(0.04f/1.65f);

    // Выводим переменную на ЦАП1.
    float dac1_data = Boost_Control.duty;
    //Boost_Measure.dac[0].data = Boost_Control.duty;

    // Регистр сравнения: ARR * (коэфф. заполнения).
    TIM8->CCR1 = TIM8->ARR * LIMIT(Boost_Control.duty, Boost_Protect.sat.duty_min, Boost_Protect.sat.duty_max);

    // Пересчитываем внутренние переменные в значения регистров ЦАП1 и ЦАП2.
    unsigned int dac1 = Boost_Measure.dac[0].scale * dac1_data + Boost_Measure.dac[0].shift;
    unsigned int dac2 = Boost_Measure.dac[1].scale * dac2_data + Boost_Measure.dac[1].shift;

   // unsigned int dac1 = Boost_Measure.dac[0].scale * Boost_Measure.dac[0].data + Boost_Measure.dac[0].shift;
   // unsigned int dac2 = Boost_Measure.dac[1].scale * Boost_Measure.dac[1].data + Boost_Measure.dac[1].shift;

    // Запись чисел в ЦАП1 и ЦАП2.
    DAC->DHR12RD = dac1 | (dac2 << 16);

    TOC = DWT->CYCCNT-TIC;
}

/**
 * \brief       Функция пересчёта значений физических величин.
 *
 */
void shift_and_scale(void)
{
    extern volatile unsigned int ADC_Buffer[];

    Boost_Measure.data.inj = Boost_Measure.scale.inj * ADC_Buffer[0] + Boost_Measure.shift.inj;
    Boost_Measure.data.u2 = Boost_Measure.scale.u2 * ADC_Buffer[1] + Boost_Measure.shift.u2;
    Boost_Measure.data.iL = Boost_Measure.scale.iL * ADC_Buffer[2] + Boost_Measure.shift.iL;
    Boost_Measure.data.temperature = Boost_Measure.scale.temperature * ADC_Buffer[3] + Boost_Measure.shift.temperature;
    Boost_Measure.data.u1 = Boost_Measure.scale.u1 * ADC_Buffer[4] + Boost_Measure.shift.u1;
    Boost_Measure.data.in = Boost_Measure.scale.in * ADC_Buffer[5] + Boost_Measure.shift.in;
}

/**
 * \brief       Функция автоопределения смещений для АЦП.
 *
 */
void set_shifts(void)
{
    if (Boost_Measure.count == 0)
        return;

    // Обнуление текущего смещения и суммы при старте алгоритма автоопределения смещения.
    if (Boost_Measure.count == SET_SHIFTS_MAX_COUNT)
        Boost_Measure.shift.inj = Boost_Measure.sum.inj = 0;

    // Накапливаем сумму.
    Boost_Measure.sum.inj += Boost_Measure.data.inj * (1.f / SET_SHIFTS_MAX_COUNT);

    // Декремент счётчика и проверка окончания автоопределения смещений.
    if (--Boost_Measure.count == 0)
        Boost_Measure.shift.inj = -Boost_Measure.sum.inj;
}

/**
 * \brief       Функция программных защит.
 *
 */
void protect_software(void)
{
    // Защита по максимальному току реактора.
    if (Boost_Measure.data.iL > Boost_Protect.iL_max)
    {
        timer_PWM_Off();
        GPIOD->ODR |= 1 << 2;
    }

    // Защита по максимальному выходному току.
    if (Boost_Measure.data.in > Boost_Protect.in_max)
    {
        timer_PWM_Off();
        GPIOD->ODR |= 1 << 3;
    }

    // Защита по максимальному входному напряжению.
    if (Boost_Measure.data.u1 > Boost_Protect.u1_max)
    {
        timer_PWM_Off();
        GPIOD->ODR |= 1 << 4;
    }

    // Защита по максимальному выходному напряжению.
    if (Boost_Measure.data.u2 > Boost_Protect.u2_max)
    {
        timer_PWM_Off();
        GPIOD->ODR |= 1 << 5;
    }

    // Интегрально-токовая защита.
    integral_protect();
}

/**
 * \brief       Функция интегрально-токовой защиты по току реактора (входному току).
 *
 */
void integral_protect(void)
{
    // Разница между током реактора и его номинальным значением.
    float x = Boost_Measure.data.iL - Boost_Protect.iL_n;

    // Расчёт выхода интегратора (суммы).
    Boost_Protect.iL_int_sum = Boost_Protect.iL_int_sum + x * TS;

    // Обнуляем интегратор (сумму) в нормальном режиме работы.
    if (Boost_Protect.iL_int_sum < 0)
        Boost_Protect.iL_int_sum = 0;

    // Проверяем условие срабатывания защиты.
    else if (Boost_Protect.iL_int_sum > Boost_Protect.iL_int_max)
    {
        Boost_Protect.iL_int_sum = 0;
        timer_PWM_Off();
        GPIOD->ODR |= 1 << 1;
    }
}






















