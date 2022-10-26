#ifndef __DSP_H__//защита т пере
#define __DSP_H__

#define MAX_MOVING_FLOAT_SIZE (500)
#define MAX_MEDIAN_FLOAT_SIZE (250)


void init_DSP(void);

typedef struct
{
	float buf[MAX_MOVING_FLOAT_SIZE];

	unsigned int pointer;

	float sum;

}MovingFloatFilter_Struct;

typedef struct
{
	float buf[MAX_MEDIAN_FLOAT_SIZE];
	float buf_sorted[MAX_MEDIAN_FLOAT_SIZE];

	unsigned int pointer;



}MedianFloatFilter_Struct;


float MovingFloatFilter(MovingFloatFilter_Struct * filter, float x);
float MedianFloatFilter(MedianFloatFilter_Struct * filter, float x);

extern MovingFloatFilter_Struct TEMPERATURE_MOV;

extern MovingFloatFilter_Struct TEMPERATURE_MFF;

#endif