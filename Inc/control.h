#ifndef __CONTROL_H__//защита oт пере
#define __CONTROL_H__

void init_CONTROL(void);
#define SET_SHIFTS_MAX_COUNT ((unsigned int)(0.5*100.e3))

typedef struct
{
	}Control_Struct;

typedef struct
{
	unsigned int count;// 0 - режим измерения(не происходит смещение)
	//>0  - режим автоопределения смещения.
	struct
	{
		float inj;
		float u2;
		float iL;//Ток реактора
		float temperature;// температура в град ц
		float u1;
		float in; // выходной ток А
	}data, shift, scale, sum;//data = scale*x+shift - расчитанные значения
						// shift - смещение значения
						// scale -  масштабирование
	struct
	{
		float data;
		float shift;
		float scale;

	} dac[2]; //Структура с параметрами ЦАП1 и ЦАП2.

}Measure_Struct; //структура с параметрами измерения.

typedef struct
{
	float iL_max; //Условие срабатывания по максимальному току реактора {A]
	float in_max; //Условие срабатывания по максимальному току входному {A]
	float u1_max; //Условие срабатывания по максимальному напряжению реактора {В]
	float u2_max; //Условие срабатывания по максимальному напряжению реактора {В]

	float iL_int_sum; //сумма интегрально-токовой защиты. [А*с]
	float iL_int_max; // уставка условия срабатывания интегрально-токовой защиты [А*с]
	float iL_n; // номинальный ток реактора(входной ток) {A].



}Protect_Struct;

extern Control_Struct Boost_Control;
extern  Measure_Struct Boost_Measure;
extern  Protect_Struct Boost_Protect;

#endif
