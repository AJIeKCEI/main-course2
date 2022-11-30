
#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "dsp.h"

#define SET_SHIFTS_MAX_COUNT    ((unsigned int)(0.5*100.e3))

//  Уставки тока реактора, [А].
#define IL_REF_1    (2.f)
#define IL_REF_2    (3.f)

typedef struct
{
    float duty;     // Коэфф. заполнения, [о.е.].

    PID_Controller_Struct pid_current;  // Структура регулятора тока реактора.

} Control_Struct;   // Структура с параметрами системы управления.

typedef struct
{
    unsigned int count;     // 0 - режим измерения (не происходит автоопределения смещений).
                            // > 0 - режим автоопределения смещений.

    struct
    {
        float inj;          // Сигнал инжекции (частотные характеристики).
        float u2;           // Выходное напряжения, [В].
        float iL;           // Ток реактора (входной ток), [А].
        float temperature;  // Температура, [град Ц.].
        float u1;           // Входное напряжение, [В].
        float in;           // Выходной ток, [А].

    } data, shift, scale, sum;  // data = scale * x + shift - рассчитанные значения.
                                // shift - смещения значений.
                                // scale - коэффициенты масштабирования.
                                // sum - переменные для накопления сумм при автоопределении смещений.

    struct
    {
        float data;         // Значение переменной для вывода на ЦАП.
        float shift;        // Смещение значения переменной.
        float scale;        // Коэффициент масштабирования переменной.

    } dac[2];   // Структура с параметрами ЦАП1 и ЦАП2.

} Measure_Struct;   // Структура с параметрами измерений.

typedef struct
{
    float iL_max;   // Условие срабатывания защиты по максимальному току реактора (входной ток), [А].
    float in_max;   // Условие срабатывания защиты по максимальному выходному току, [А].
    float u1_max;   // Условие срабатывания защиты по максимальному входному напряжнию, [В].
    float u2_max;   // Условие срабатывания защиты по максимальному выходному напряжнию, [В].

    float iL_int_sum;   // Сумма (выход интегратора) интегрально-токовой защиты, [А*с].
    float iL_int_max;   // Уставка условия срабатывания интегрально-токовй защиты, [А*с].
    float iL_n;         // Номинальный ток реактора (входной ток), [А].

    struct
    {
        float duty_min;     // Мин. коэфф. заполнения.
        float duty_max;     // Макс. коэфф. заполнения.

    } sat;      // Параметры ограничителей.

} Protect_Struct;   // Структура с параметрами защит.

extern Control_Struct Boost_Control;
extern Measure_Struct Boost_Measure;
extern Protect_Struct Boost_Protect;

#endif
















