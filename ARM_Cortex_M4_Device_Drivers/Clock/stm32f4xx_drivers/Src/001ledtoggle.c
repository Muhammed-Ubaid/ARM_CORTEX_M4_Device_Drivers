/*
 * 001ledtoggle.c
 *
 *  Created on: 30-May-2021
 *      Author: Mohammed Ubaid
 */

#include "stm32f407xx.h"

void delay(void)
{
	for(uint32_t i = 0; i < 500000; i++);
}

int main(void)
{
	GPIO_Handle_t GpioLed;

	/*1. LED toggle PP config*/
//	GpioLed.pGPIOx = GPIOD;
//	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
//	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
//	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
//	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
//	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
//
//	GPIO_PeriClockControl(GPIOD,ENABLE);
//
//	GPIO_Init(&GpioLed);
//
//	while(1)
//	{
//		GPIO_ToggleOutputPin(GPIOD,GPIO_PIN_NO_12);
//		delay();
//	}


	/*2. LED toggle Open Drain with pull up config*/
		GpioLed.pGPIOx = GPIOD;
		GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
		GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
		GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
		GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
		GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU; //internal PU resistor value is very high, hence LED glows with low intensity,
																//recommended to connect external pullup of 320ohm via jumper in between PD12 and Vcc and use GPIO_NO_PUPD

		GPIO_PeriClockControl(GPIOD,ENABLE);

		GPIO_Init(&GpioLed);

		while(1)
		{
			GPIO_ToggleOutputPin(GPIOD,GPIO_PIN_NO_12);
			delay();
		}

	return 0;
}


