
#ifndef __DSP_H__
#define __DSP_H__

#define MAX_MOVING_FLOAT_SIZE   (500)
#define MAX_MEDIAN_FLOAT_SIZE   (500)
#define MAX_ORDER_DIGITAL_FILTER (2)

#define FS (100.e3)             // Частота дискретизации (частота коммутации), [Гц].
#define TS (1./(FS))            // Период дискретизации (период коммутации), [с].
//#define TAU_1ORD    (0.001)   // Постоянная времени фильтра 1го порядка [с].
#define WC_1ORD     (2.*3.1415*1000.)
#define TAU_1ORD    (1./WC_1ORD)

#define LIMIT(x, min, max) ( ((x) < (min)) ? (min) : ( ((x) > (max)) ? (max) : (x) ) )

typedef struct
{
    float buf[MAX_MOVING_FLOAT_SIZE];

    unsigned int pointer;

    float sum;

} MovingFloatFilter_Struct;     // // Структура фильтра скользящего среднего.

typedef struct
{
    float buf[MAX_MEDIAN_FLOAT_SIZE];
    float buf_sorted[MAX_MEDIAN_FLOAT_SIZE];

    unsigned int pointer;

} MedianFloatFilter_Struct;     // Структура медианного фильтра.

typedef struct
{
    float yn;   // Переменная для хранения значения выходной переменной
                // с предыдущего такта расчёта.

    float b0;   // Коэффициент числитель ПФ фильтра.
    float a1;   // Коэффициент знаменателя ПФ фильтра.

} Low_Filter_1st_Order_Struct;  // Структура фильтра нижних частот 1го порядка.

typedef struct
{
    float a[MAX_ORDER_DIGITAL_FILTER+1];      // Коэффициенты знаменателя ПФ фильтра.
    float b[MAX_ORDER_DIGITAL_FILTER+1];      // Коэффициенты числителя ПФ фильтра.

    float z[2][MAX_ORDER_DIGITAL_FILTER+1];   // Массив для хранения предыдущих значений.
                                              // z[0][...] - используются для хранений значений 'w' в прямой форме II
                                              //             и 'x' в прямой форме I.
                                              // z[1][...] - используется для хранений значений 'y' в прямой форме I.

    float tmp;

} DigitalFilter_Struct;

typedef struct
{
    float k;        // Коэффициент интегратора (включает период дискретизации).
    float sum;      // Сумма интегратора (выход).
    float c;        // Переменая для накопления погрешности интегрирования в алгоритме Кэхэна.

    struct
    {
        float min;  // Мин. значение суммы.
        float max;  // Макс. значение суммы.

    } sat;  // Структура с параметрами ограничителя суммы.

} Integrator_Struct;  // Структура параметров интегратора.

typedef struct
{
    float k;        // Коэффициент диффернциатора (включает период дискретизации).
    float xz;       // Переменная для хранения предыдущего значение входа.

} Diff_Struct;  // Структура параметров дифференциатора.

typedef struct
{
    float kp;       // Коэффициент пропорциональной части.
    float kb;       // Коэффициент обратной связи в алгоритме Back-calculation.

    Integrator_Struct integrator;   // Интегральная часть.
    Diff_Struct diff;       // Дифференциальная часть.

    float bc;        // Переменная обратной связи в алгоритме Back-calculation.

    struct
    {
        float min;  // Мин. значение выхода.
        float max;  // Макс. значение выхода.

    } sat;  // Структура с параметрами ограничителя выхода.

} PID_Controller_Struct;    // Структура параметров ПИД-регулятора.

typedef struct
{
    Integrator_Struct integrator;

} LinearRamp_Struct;    // Структура параметров линейного задатчика.

typedef struct
{
    Integrator_Struct integrator[2];

    float k3;           // Коэффициент дополнительной нелинейной связи.

} SShapedRamp_Struct;   // Структура параметров S-образного задатчика.

float MovingFloatFilter(MovingFloatFilter_Struct * filter, float x);
float MedianFloatFilter(MedianFloatFilter_Struct * filter, float x);
float Low_Filter_1st_Order(Low_Filter_1st_Order_Struct * filter, float x);
float DirectFormII_FloatFilter(DigitalFilter_Struct * filter, float x);
float DirectFormI_FloatFilter(DigitalFilter_Struct * filter, float x);

float BackwardEuler_Integrator(Integrator_Struct * integrator, float x);
float Trapezoidal_Integrator(Integrator_Struct * integrator, float x);
float BackwardEuler_Kahan_Integrator(Integrator_Struct * integrator, float x);
float Trapezoidal_Kahan_Integrator(Integrator_Struct * integrator, float x);

float BackwardEuler_Diff(Diff_Struct * diff, float x);

float PID_Controller(PID_Controller_Struct * pid, float x);
float PID_BackCalc_Controller(PID_Controller_Struct * pid, float x);
float PID_Clamp_Controller(PID_Controller_Struct * pid, float x);

float Linear_Ramp(LinearRamp_Struct * ramp, float x);
float SShaped_Ramp(SShapedRamp_Struct * ramp, float x);

extern MovingFloatFilter_Struct FILTER_MOV;
extern MedianFloatFilter_Struct FILTER_MED;
extern Low_Filter_1st_Order_Struct FILTER_1ORD;
extern DigitalFilter_Struct FILTER_DIG1;
extern DigitalFilter_Struct FILTER_DIG2;

#endif













