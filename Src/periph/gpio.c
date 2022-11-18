
#include "stm32f7xx.h"
#include "gpio.h"

void init_GPIO_Output(GPIO_TypeDef * gpio, unsigned int pin);
void init_GPIO_AFunction(GPIO_TypeDef * gpio, unsigned int pin, unsigned int AF);
void init_GPIO_Analog(GPIO_TypeDef * gpio, unsigned int pin);

void init_GPIO(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
// led
    init_GPIO_Output(GPIOD, 1); //HL1.
    init_GPIO_Output(GPIOD, 2); //HL1.
    init_GPIO_Output(GPIOD, 3); //HL1.
    init_GPIO_Output(GPIOD, 4); //HL1.
    init_GPIO_Output(GPIOD, 5); //HL5.

 // Тестовые выводы
    init_GPIO_Output(GPIOD, 6); //5
    init_GPIO_Output(GPIOD, 7); //6
    init_GPIO_Output(GPIOG, 9);  //7
    init_GPIO_Output(GPIOG, 10);  //8
    init_GPIO_Output(GPIOG, 11);  //9

    //
    init_GPIO_AFunction(GPIOC, 6, 3);

    init_GPIO_Analog(GPIOA, 0);     // Выходное напряжение.
    init_GPIO_Analog(GPIOC, 2);     // Выходной ток.
    init_GPIO_Analog(GPIOC, 3);     // Входное напряжение.
    init_GPIO_Analog(GPIOF, 4);     // Ток дросселя (входной ток).
    init_GPIO_Analog(GPIOA, 3);     // Сигнал инжекции (для частотных характеристик).

    init_GPIO_Analog(GPIOA, 4);     // ЦАП1.
    init_GPIO_Analog(GPIOA, 5);     // ЦАП2.

    SYSCFG->EXTICR[0]|=1<<4; // настраиваем pb1
    EXTI->IMR|=EXTI_IMR_IM1;
    EXTI->FTSR|=EXTI_FTSR_TR1; //настройка по линии 1 по спадающему фронту
    EXTI->RTSR|=EXTI_RTSR_TR1; //настройка по линии 1 по спадающему фронту
}

void init_GPIO_Output(GPIO_TypeDef * gpio, unsigned int pin)
{
    gpio->MODER |= 1 << (2*pin);
}

void init_GPIO_AFunction(GPIO_TypeDef * gpio, unsigned int pin, unsigned int AF)
{
    if (pin < 8)
        gpio->AFR[0] |= AF << (4*pin);
    else
        gpio->AFR[1] |= AF << (4*(pin - 8));

    gpio->MODER |= 2 << (2*pin);
    gpio->OSPEEDR |= 3 << (2*pin);
}

void init_GPIO_Analog(GPIO_TypeDef * gpio, unsigned int pin)
{
    gpio->MODER |= 3 << (2*pin);
}

