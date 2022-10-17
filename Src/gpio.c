#include "stm32f7xx.h"
#include "gpio.h"


void init_GPIO_Output(GPIO_TypeDef * gpio, unsigned int pin);
void init_GPIO_AFunction(GPIO_TypeDef *gpio, unsigned int pin, unsigned int AF);

//void init_GPIO(void)
//{
//
//	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
//	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
//	init_GPIO_Output(GPIOD,1);
//	init_GPIO_AFunction(GPIOC,6,3);
//}
//
//void init_GPIO_Output(GPIO_TypeDef * gpio, unsigned int pin){
//
//	gpio->MODER |= 1 << (2*pin);
//}
//
//void init_GPIO_AFunction(GPIO_TypeDef *gpio, unsigned int pin, unsigned int AF){
//	if (pin < 8) gpio->AFR[0] |= AF <<(4*pin);
//	else gpio->AFR[1] |= AF <<(4*(pin - 8));
//	gpio->MODER |= 2 << (2*pin);
//	gpio ->OSPEEDR |= 3 << (2*pin);
//}

void init_GPIO(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	init_GPIO_Output(GPIOD, 1);
	init_GPIO_AFunction(GPIOC,6,3);
	//init_GPIO_Output(GPIOD, 1);
	init_GPIO_AFunction(GPIOC,7,3);
}



void init_GPIO_Output(GPIO_TypeDef *gpio, unsigned int pin)//инициализации установки порта
{
	gpio->MODER |= 1<<(2*pin);//выставляем порт в General purpose output mode, 2*(pin=1) или сдвиг на 1 << (1 << 1)

}

void init_GPIO_AFunction(GPIO_TypeDef *gpio, unsigned int pin, unsigned int AF)//инициализации установки порта в альтернативную функцию page 148 max speed table 58
{
	if (pin < 8)
		gpio->AFR[0]|= AF<<(4*pin);//в таблице номер порта AF6  в данном случае тройку в шестой порт
	else gpio->AFR[1]|= AF<<(4*(pin - 8));//c,hjc lj gthdjuj gbyf

	gpio->MODER |= 2 << (2*pin);//выставляем порт в 10: Alternate function mode 2*(pin=1) или сдвиг на 1 << (1 << 1)
	gpio->OSPEEDR |= 3 << (2*pin);// page 148 max speed table 58
}
