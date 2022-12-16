
#include "stm32f7xx.h"
#include "dsp.h"

#include <string.h>
#include <stdlib.h>
#include <math.h>



/**
 * \brief       Функция фильтра скользящего среднего.
 *
 * \param       filter: структура с параметрами фильтра.
 * \param       x: входная переменная.
 *
 * \return      y: среднее значение.
 *
 */
float  MovingFloatFilter(MovingFloatFilter_Struct * filter, float x)
{
    // Отнимаем от суммы [n-1] точку и прибавляем [0] точку.
    filter->sum = filter->sum - filter->buf[filter->pointer] + x;

    // Добавляем новую точку в массив точек.
    filter->buf[filter->pointer] = x;

    // Инкрементируем указатель (счётчик).
    if (++filter->pointer >= MAX_MOVING_FLOAT_SIZE)
        filter->pointer = 0;

    // Вычисляем среднее значение.
    return filter->sum * (1.f / MAX_MOVING_FLOAT_SIZE);
}

int cmp(const void *a, const void *b)
{
    float *af = (float *)a;
    float *bf = (float *)b;

    if (*af > *bf)
        return 1;

    if (*af < *bf)
        return -1;

    return 0;
}

/**
 * \brief       Функция медианного фильтра.
 *
 * \param       filter: структура с параметрами фильтра.
 * \param       x: входная переменная.
 *
 * \return      y: среднее значение.
 *
 */
float MedianFloatFilter(MedianFloatFilter_Struct * filter, float x)
{
    // Добавляем новую точку в массив точек.
    filter->buf[filter->pointer] = x;

    // Инкрементируем указатель (счётчик).
    if (++filter->pointer >= MAX_MEDIAN_FLOAT_SIZE)
        filter->pointer = 0;

    // Делаем копию массива точек.
    for(int i = 0; i < MAX_MEDIAN_FLOAT_SIZE; i++)
        filter->buf_sorted[i] = filter->buf[i];

    //memcpy(filter->buf_sorted, filter->buf, sizeof(filter->buf));

    // Ждём окончания копирования (выхода всех инструкций и данных из конвейера).
    __ISB();
    __DSB();

    // Сортируем массив.
    qsort(filter->buf_sorted, MAX_MEDIAN_FLOAT_SIZE, sizeof(filter->buf_sorted[0]), (int (*)(const void *, const void *))cmp);

    return filter->buf_sorted[MAX_MEDIAN_FLOAT_SIZE >> 1];
    //return filter->buf_sorted[MAX_MEDIAN_FLOAT_SIZE / 2];
}

/**
 * \brief   Функция фильтра нижних частот 1го порядка.
 *
 * \param       filter: структура с параметрами фильтра.
 * \param       x: входная переменная.
 *
 * \return      y: значение после фильтрации.
 *
 */
float Low_Filter_1st_Order(Low_Filter_1st_Order_Struct * filter, float x)
{
    // Рассчитываем выходную переменную для текущего такта.
    float y = x * filter->b0 - filter->yn * filter->a1;

    // Сохраняем выходную переменную для следующего такта расчёта.
    filter->yn = y;

    return y;
}

/**
 * \brief   Функция цифрового фильтра в прямой форме II.
 *
 * \param   filter: структура с параметрами фильтра.
 * \param   x: входная переменная.
 *
 * \return  y: значение после фильтрации.
 *
 */
float DirectFormII_FloatFilter(DigitalFilter_Struct * filter, float x)
{
    float y = 0;

    // w = x.
    filter->z[0][0] = x;

    for (int i = MAX_ORDER_DIGITAL_FILTER; i >= 1; i--)
    {
        // Суммирование ветвей с коэффициентами 'a'.
        // w = w - ai * w * z^(-i).
        filter->z[0][0] -= filter->z[0][i] * filter->a[i];

        // Суммирование ветвей с коэффициентами 'b'.
        // y = y + bi * w * z^(-i).
        y += filter->z[0][i] * filter->b[i];

        // Сохранение предыдущих значений.
        // z^(-i) <--- z^(-(i-1)).
        filter->z[0][i] = filter->z[0][i-1];
    }

    // y += w * b0.
    y += filter->z[0][0] * filter->b[0];

    return y;
}

/**
 * \brief   Функция цифрового фильтра в прямой форме I.
 *
 * \param   filter: структура с параметрами фильтра.
 * \param   x: входная переменная.
 *
 * \return  y: значение после фильтрации.
 *
 */
float DirectFormI_FloatFilter(DigitalFilter_Struct * filter, float x)
{
    filter->z[0][0] = x;
    filter->z[1][0] = x * filter->b[0];

    // Вычисление первого каскада (с коэффициентами 'b').
    for (int i = MAX_ORDER_DIGITAL_FILTER; i >= 1; i--)
    {
        // v = v + bi * x * z^(-i).
        filter->z[1][0] += filter->z[0][i] * filter->b[i];

        // Сохранение предыдущих значений.
        // z^(-i) <--- z^(-(i-1)).
        filter->z[0][i] = filter->z[0][i-1];
    }

    // После вычислений в первом цикле:
    //  filter->z[1][0] = v.

    // Вычисление второго каскада (с коэффициентами 'a').
    for (int i = MAX_ORDER_DIGITAL_FILTER; i >= 1; i--)
    {
        // y = y - ai * y * z^(-i).
        filter->z[1][0] -= filter->z[1][i] * filter->a[i];

        // Сохранение предыдущих значений.
        // z^(-i) <--- z^(-(i-1)).
        filter->z[1][i] = filter->z[1][i-1];
    }

    // После вычислений во втором цикле:
    //  filter->z[1][0] = y.

    return filter->z[1][0];
}

/**
 * \brief       Функция интегратора методом прямоугольников (Backward Euler).
 *
 * \param       integrator: структура с параметрами интегратора.
 * \param       x: вход интегратора.
 *
 * \return      y: сумму интегратора (выход).
 *
 */
float BackwardEuler_Integrator(Integrator_Struct * integrator, float x)
{
    // Накапливаем сумму.
    integrator->sum = LIMIT(integrator->sum + integrator->k * x, integrator->sat.min, integrator->sat.max);

    // Возвращаем значение суммы.
    return integrator->sum;
}

/**
 * \brief       Функция интегратора методом прямоугольников (Backward Euler)
 *              с алгоритмом компенсационного суммирования Кэхэна.
 *
 * \param       integrator: структура с параметрами интегратора.
 * \param       x: вход интегратора.
 *
 * \return      y: сумму интегратора (выход).
 *
 */
float BackwardEuler_Kahan_Integrator(Integrator_Struct * integrator, float x)
{
    // y = input - c.
    float y = integrator->k * x - integrator->c;

    // t = sum + y.
    float t = integrator->sum + y;

    // c = (t - sum) - y.
    integrator->c = (t - integrator->sum) - y;

    // Накапливаем сумму.
    integrator->sum = LIMIT(t, integrator->sat.min, integrator->sat.max);

    // Возвращаем значение суммы.
    return integrator->sum;
}

/**
 * \brief       Функция интегратора методом трапеций (Trapezoidal).
 *
 * \param       integrator: структура с параметрами интегратора.
 * \param       x: вход интегратора.
 *
 * \return      y: сумму интегратора (выход).
 *
 */
float Trapezoidal_Integrator(Integrator_Struct * integrator, float x)
{
    // out[n] = s[n-1] + x[n] * k.
    float out = LIMIT(integrator->sum + x * integrator->k, integrator->sat.min, integrator->sat.max);

    // s[n] = out[n] + x[n] * k.
    integrator->sum = out + x * integrator->k;

    return out;
}

/**
 * \brief       Функция интегратора методом трапеций (Trapezoidal)
 *              с алгоритмом компенсационного суммирования Кэхэна.
 *
 * \param       integrator: структура с параметрами интегратора.
 * \param       x: вход интегратора.
 *
 * \return      y: сумму интегратора (выход).
 *
 */
float Trapezoidal_Kahan_Integrator(Integrator_Struct * integrator, float x)
{
    // out[n] = s[n-1] + x[n] * k.
    float out = LIMIT(integrator->sum + x * integrator->k, integrator->sat.min, integrator->sat.max);

    // y = input - c.
    float y = 2.f * x * integrator->k - integrator->c;

    // t = sum + y.
    float t = integrator->sum + y;

    // c = (t - sum) - y.
    integrator->c = (t - integrator->sum) - y;

    // s[n] = out[n] + x[n] * k.
    integrator->sum = t;

    return out;
}

/**
 * \brief       Функция дифференциатора методом Эйлера (Backward Euler).
 *
 * \param       diff: структура с параметрами дифференциатором.
 * \param       x: вход дифференциатора.
 *
 * \return      y: выход дифференциатора.
 *
 */
float BackwardEuler_Diff(Diff_Struct * diff, float x)
{
    // y[n] = (x[n] - x[n-1]) * k.
    float out = (x - diff->xz) * diff->k;

    // Сохраняем текущее значение x для следующего расчёта.
    diff->xz = x;

    return out;
}

/**
 * \brief       Функция ПИД-регулятора.
 *
 * \param       pid: структура с параметрами регулятора.
 * \param       x: вход регулятора.
 *
 * \return      y: выход регулятора.
 *
 */
float PID_Controller(PID_Controller_Struct * pid, float x)
{
    // Расчёт пропорциональной части.
    float out_p = x * pid->kp;

    // Расчёт интегральной части.
    float out_i = Trapezoidal_Integrator(&pid->integrator, x);

    // Расчёт дифференциальной части.
    float out_d = BackwardEuler_Diff(&pid->diff, x);

    return LIMIT(out_p + out_i + out_d, pid->sat.min, pid->sat.max);
}

/**
 * \brief       Функция ПИД-регулятора с защитой от насыщения интегратора
 *              методом Back-Calculation.
 *
 * \param       pid: структура с параметрами регулятора.
 * \param       x: вход регулятора.
 *
 * \return      y: выход регулятора.
 *
 */
float PID_BackCalc_Controller(PID_Controller_Struct * pid, float x)
{
    // Расчёт пропорциональной части.
    float out_p = x * pid->kp;

    // Расчёт интегральной части.
    float out_i = Trapezoidal_Integrator(&pid->integrator, x + pid->bc);

    // Расчёт дифференциальной части.
    float out_d = BackwardEuler_Diff(&pid->diff, x);

    // Выход регулятора до ограничения.
    float out = out_p + out_i + out_d;

    // Выход регулятора после ограничения.
    float out_limit = LIMIT(out, pid->sat.min, pid->sat.max);

    // bc = (us - u) * kb.
    // kb = 1 / Tt / ki.
    pid->bc = (out_limit - out) * pid->kb;

    return out_limit;
}

/**
 * \brief       Функция линейного задатчика.
 *
 * \param       ramp: структура с параметрами задатчика.
 * \param       x: вход задатчика.
 *
 * \return      y: выход задатчика.
 *
 */
float Linear_Ramp(LinearRamp_Struct * ramp, float x)
{
    // s = x - r.
    float s = x - ramp->integrator.sum;

    // Функция знака (sign).
    if (signbit(s))     // Если s имеет знак минус (число отрицательное).
        s = -1.f;
    else                // Иначе...
        s = 1.f;

    // Интегрируем выход функции знака.
    return BackwardEuler_Integrator(&ramp->integrator, s);
}

/**
 * \brief       Функция S-образного задатчика.
 *
 * \param       ramp: структура с параметрами задатчика.
 * \param       x: вход задатчика.
 *
 * \return      y: выход задатчика.
 *
 */
float SShaped_Ramp(SShapedRamp_Struct * ramp, float x)
{
    // s1 = x - (r +- k3 * p^2) = x - r -+ k3 * p^2.
    float s1 = x - ramp->integrator[1].sum - ramp->k3 * ramp->integrator[0].sum * fabsf(ramp->integrator[0].sum);

    // Функция знака (sign).
    if (signbit(s1))    // Если s1 имеет знак минус (число отрицательное).
        s1 = -1.f;
    else                // Иначе...
        s1 = 1.f;

    // s2 = s1 - p.
    float s2 = s1 - ramp->integrator[0].sum;

    // Функция знака (sign).
    if (signbit(s2))    // Если s2 имеет знак минус (число отрицательное).
        s2 = -1.f;
    else                // Иначе...
        s2 = 1.f;

    float p = BackwardEuler_Integrator(&ramp->integrator[0], s2);
    return BackwardEuler_Integrator(&ramp->integrator[1], p);
}


















