/*
 * 003_ledButton_ext.c
 *
 *  Created on: 30-May-2021
 *      Author: Mohammed Ubaid
 */


#include "stm32f407xx.h"
#include <string.h>

#define HIGH 1
#define LOW 0
#define BTN_PRESSED LOW

void delay(void)
{
	for(uint32_t i = 0; i < 500000/2; i++);
}


int main(void)
{
	GPIO_Handle_t GpioLed, GPIOBtn;

	memset(&GpioLed,0,sizeof(GpioLed));
	memset(&GPIOBtn,0,sizeof(GPIOBtn));


	/*LED code*/
		GpioLed.pGPIOx = GPIOD;
		GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
		GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
		GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
		GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
		GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD; //internal PU resistor value is very high, hence LED glows with low intensity,
																//recommended to connect external pullup of 320ohm via jumper in between PD12 and Vcc and use GPIO_NO_PUPD

		GPIO_PeriClockControl(GPIOD,ENABLE);

		GPIO_Init(&GpioLed);

		GPIOBtn.pGPIOx = GPIOD;
		GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
		GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
		GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
		GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

		GPIO_PeriClockControl(GPIOD,ENABLE);

		GPIO_Init(&GPIOBtn);

		// IRQ configurations
		GPIO_IRQPriorityConfig(IRQ_NO_EXTI9_5, NVIC_IRQ_PRIO15);
		GPIO_IRQInterruptConfig(IRQ_NO_EXTI9_5, ENABLE);




	return 0;
}


void EXTI9_5_IRQHandler(void)
{
	delay();//wait 200ms after event to stabilize debouncing impulses
	GPIO_IRQHandling(GPIO_PIN_NO_5); //clear out interrupt
	GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
}
