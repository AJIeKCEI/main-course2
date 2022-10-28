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

}Protect_Struct;

extern Control_Struct Boost_Control;
extern  Measure_Struct Boost_Measure;
extern  Protect_Struct Boost_Protect;

#endif