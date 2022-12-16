#include "c_math.h"
#define C_MATH_TABLE_SIZE (512)

extern const float asineTable_f32[C_MATH_TABLE_SIZE];
/**
 * \brief Функция арксинуса.
 * \param  x: аргумент функции
 * \return y: арксинус аргумента
 *
 */
float asine_f32(float x)
{
	float in = (x+1.f)*0.5f;

	float findex = in*(C_MATH_TABLE_SIZE - 1);
	//Получаем целый индекс
	unsigned int index = (unsigned int)findex;

	float a = asineTable_f32[index];
	float b = asineTable_f32[index+1];

	float c = (b-a)*(findex - index)+a;

	return c;

}

//ПРедварительная рассчитанная таблица значений арксинуса для аргументов [-1;1]

 float  афые_sqrt(const float x)
{
  const float xhalf = 0.5f*x;

  union // get bits for floating value
  {
    float x;
    int i;
  } u;
  u.x = x;
  u.i = SQRT_MAGIC_F - (u.i >> 1);  // gives initial guess y0
  return x*u.x*(1.5f - xhalf*u.x*u.x);// Newton step, repeating increases accuracy
}

const float asineTable_f32[C_MATH_TABLE_SIZE] =
{
		-1.5708f, -1.4823f, -1.4456f, -1.4174f,
		-1.3936f, -1.3726f, -1.3537f, -1.3362f,
		-1.3199f, -1.3046f, -1.2901f, -1.2763f,
		-1.2631f, -1.2504f, -1.2382f, -1.2264f,
		-1.215f, -1.204f, -1.1932f, -1.1827f,
		-1.1725f, -1.1625f, -1.1528f, -1.1432f,
		-1.1339f, -1.1247f, -1.1157f, -1.1069f,
		-1.0982f, -1.0897f, -1.0813f, -1.0731f,
		-1.0649f, -1.0569f, -1.049f, -1.0412f,
		-1.0335f, -1.0259f, -1.0184f, -1.011f,
		-1.0037f, -0.99642f, -0.98925f, -0.98217f,
		-0.97515f, -0.96821f, -0.96134f, -0.95454f,
		-0.9478f, -0.94112f, -0.93451f, -0.92795f,
		-0.92145f, -0.915f, -0.90861f, -0.90227f,
		-0.89598f, -0.88974f, -0.88355f, -0.8774f,
		-0.8713f, -0.86524f, -0.85923f, -0.85325f,
		-0.84732f, -0.84143f, -0.83558f, -0.82976f,
		-0.82398f, -0.81824f, -0.81253f, -0.80685f,
		-0.80121f, -0.7956f, -0.79003f, -0.78448f,
		-0.77897f, -0.77348f, -0.76803f, -0.7626f,
		-0.7572f, -0.75183f, -0.74648f, -0.74116f,
		-0.73587f, -0.7306f, -0.72536f, -0.72014f,
		-0.71495f, -0.70978f, -0.70463f, -0.6995f,
		-0.6944f, -0.68931f, -0.68425f, -0.67921f,
		-0.67419f, -0.66919f, -0.66421f, -0.65925f,
		-0.65431f, -0.64938f, -0.64448f, -0.63959f,
		-0.63472f, -0.62987f, -0.62504f, -0.62022f,
		-0.61542f, -0.61063f, -0.60586f, -0.60111f,
		-0.59637f, -0.59165f, -0.58694f, -0.58225f,
		-0.57757f, -0.5729f, -0.56825f, -0.56362f,
		-0.55899f, -0.55438f, -0.54979f, -0.5452f,
		-0.54063f, -0.53607f, -0.53153f, -0.52699f,
		-0.52247f, -0.51796f, -0.51346f, -0.50897f,
		-0.5045f, -0.50003f, -0.49558f, -0.49113f,
		-0.4867f, -0.48228f, -0.47786f, -0.47346f,
		-0.46907f, -0.46468f, -0.46031f, -0.45595f,
		-0.45159f, -0.44725f, -0.44291f, -0.43858f,
		-0.43426f, -0.42995f, -0.42565f, -0.42136f,
		-0.41708f, -0.4128f, -0.40853f, -0.40427f,
		-0.40002f, -0.39577f, -0.39153f, -0.3873f,
		-0.38308f, -0.37886f, -0.37465f, -0.37045f,
		-0.36625f, -0.36207f, -0.35788f, -0.35371f,
		-0.34954f, -0.34538f, -0.34122f, -0.33707f,
		-0.33293f, -0.32879f, -0.32466f, -0.32053f,
		-0.31641f, -0.31229f, -0.30818f, -0.30408f,
		-0.29998f, -0.29588f, -0.29179f, -0.28771f,
		-0.28363f, -0.27956f, -0.27549f, -0.27142f,
		-0.26736f, -0.26331f, -0.25925f, -0.25521f,
		-0.25116f, -0.24713f, -0.24309f, -0.23906f,
		-0.23503f, -0.23101f, -0.22699f, -0.22298f,
		-0.21897f, -0.21496f, -0.21095f, -0.20695f,
		-0.20296f, -0.19896f, -0.19497f, -0.19098f,
		-0.187f, -0.18302f, -0.17904f, -0.17506f,
		-0.17109f, -0.16712f, -0.16315f, -0.15918f,
		-0.15522f, -0.15126f, -0.1473f, -0.14335f,
		-0.13939f, -0.13544f, -0.13149f, -0.12755f,
		-0.1236f, -0.11966f, -0.11572f, -0.11178f,
		-0.10784f, -0.10391f, -0.099971f, -0.096038f,
		-0.092107f, -0.088177f, -0.084248f, -0.080321f,
		-0.076395f, -0.07247f, -0.068547f, -0.064624f,
		-0.060703f, -0.056782f, -0.052862f, -0.048943f,
		-0.045025f, -0.041107f, -0.037191f, -0.033274f,
		-0.029358f, -0.025443f, -0.021528f, -0.017613f,
		-0.013699f, -0.0097849f, -0.0058709f, -0.0019569f,
		0.0019569f, 0.0058709f, 0.0097849f, 0.013699f,
		0.017613f, 0.021528f, 0.025443f, 0.029358f,
		0.033274f, 0.037191f, 0.041107f, 0.045025f,
		0.048943f, 0.052862f, 0.056782f, 0.060703f,
		0.064624f, 0.068547f, 0.07247f, 0.076395f,
		0.080321f, 0.084248f, 0.088177f, 0.092107f,
		0.096038f, 0.099971f, 0.10391f, 0.10784f,
		0.11178f, 0.11572f, 0.11966f, 0.1236f,
		0.12755f, 0.13149f, 0.13544f, 0.13939f,
		0.14335f, 0.1473f, 0.15126f, 0.15522f,
		0.15918f, 0.16315f, 0.16712f, 0.17109f,
		0.17506f, 0.17904f, 0.18302f, 0.187f,
		0.19098f, 0.19497f, 0.19896f, 0.20296f,
		0.20695f, 0.21095f, 0.21496f, 0.21897f,
		0.22298f, 0.22699f, 0.23101f, 0.23503f,
		0.23906f, 0.24309f, 0.24713f, 0.25116f,
		0.25521f, 0.25925f, 0.26331f, 0.26736f,
		0.27142f, 0.27549f, 0.27956f, 0.28363f,
		0.28771f, 0.29179f, 0.29588f, 0.29998f,
		0.30408f, 0.30818f, 0.31229f, 0.31641f,
		0.32053f, 0.32466f, 0.32879f, 0.33293f,
		0.33707f, 0.34122f, 0.34538f, 0.34954f,
		0.35371f, 0.35788f, 0.36207f, 0.36625f,
		0.37045f, 0.37465f, 0.37886f, 0.38308f,
		0.3873f, 0.39153f, 0.39577f, 0.40002f,
		0.40427f, 0.40853f, 0.4128f, 0.41708f,
		0.42136f, 0.42565f, 0.42995f, 0.43426f,
		0.43858f, 0.44291f, 0.44725f, 0.45159f,
		0.45595f, 0.46031f, 0.46468f, 0.46907f,
		0.47346f, 0.47786f, 0.48228f, 0.4867f,
		0.49113f, 0.49558f, 0.50003f, 0.5045f,
		0.50897f, 0.51346f, 0.51796f, 0.52247f,
		0.52699f, 0.53153f, 0.53607f, 0.54063f,
		0.5452f, 0.54979f, 0.55438f, 0.55899f,
		0.56362f, 0.56825f, 0.5729f, 0.57757f,
		0.58225f, 0.58694f, 0.59165f, 0.59637f,
		0.60111f, 0.60586f, 0.61063f, 0.61542f,
		0.62022f, 0.62504f, 0.62987f, 0.63472f,
		0.63959f, 0.64448f, 0.64938f, 0.65431f,
		0.65925f, 0.66421f, 0.66919f, 0.67419f,
		0.67921f, 0.68425f, 0.68931f, 0.6944f,
		0.6995f, 0.70463f, 0.70978f, 0.71495f,
		0.72014f, 0.72536f, 0.7306f, 0.73587f,
		0.74116f, 0.74648f, 0.75183f, 0.7572f,
		0.7626f, 0.76803f, 0.77348f, 0.77897f,
		0.78448f, 0.79003f, 0.7956f, 0.80121f,
		0.80685f, 0.81253f, 0.81824f, 0.82398f,
		0.82976f, 0.83558f, 0.84143f, 0.84732f,
		0.85325f, 0.85923f, 0.86524f, 0.8713f,
		0.8774f, 0.88355f, 0.88974f, 0.89598f,
		0.90227f, 0.90861f, 0.915f, 0.92145f,
		0.92795f, 0.93451f, 0.94112f, 0.9478f,
		0.95454f, 0.96134f, 0.96821f, 0.97515f,
		0.98217f, 0.98925f, 0.99642f, 1.0037f,
		1.011f, 1.0184f, 1.0259f, 1.0335f,
		1.0412f, 1.049f, 1.0569f, 1.0649f,
		1.0731f, 1.0813f, 1.0897f, 1.0982f,
		1.1069f, 1.1157f, 1.1247f, 1.1339f,
		1.1432f, 1.1528f, 1.1625f, 1.1725f,
		1.1827f, 1.1932f, 1.204f, 1.215f,
		1.2264f, 1.2382f, 1.2504f, 1.2631f,
		1.2763f, 1.2901f, 1.3046f, 1.3199f,
		1.3362f, 1.3537f, 1.3726f, 1.3936f,
		1.4174f, 1.4456f, 1.4823f, 1.5708f
};