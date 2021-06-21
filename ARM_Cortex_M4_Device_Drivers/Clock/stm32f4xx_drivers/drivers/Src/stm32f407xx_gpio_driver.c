/*
 * stm32f407xx_gpio_driver.c
 *
 *  Created on: 29-May-2021
 *      Author: Mohammed Ubaid
 */

#include "stm32f407xx_gpio_driver.h"


/*
*GPIO_PeriClockControl()
*	- This API enables or disables the peripheral clock for the GPIO port
*	- GPIO_RegDef_t is the base address of GPIO peripheral
*	- EnOrDi is a macro ENABLE or DISABLE for clock
*	-
*	-
*	- This function does not return anything
*	- No remarks
*/
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}
		else if(pGPIOx == GPIOI)
		{
			GPIOI_PCLK_EN();
		}
	}
	else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DIS();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DIS();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DIS();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DIS();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DIS();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_DIS();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_DIS();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DIS();
		}
		else if(pGPIOx == GPIOI)
		{
			GPIOI_PCLK_DIS();
		}

	}

}



/*
*GPIO_Init()
*	- This API initialized GPIO pin for use
*	- GPIO_Handle_t is the handle for GPIO pin
*	-
*	-
*	-
*	- This function does not return anything
*	- No remarks
*/
void GPIO_Init(GPIO_Handle_t* pGPIOHandle)
{

	GPIO_PeriClockControl(pGPIOHandle->pGPIOx,ENABLE);

	uint32_t temp = 0;
	//configure GPIO pin mode
	if((pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ANALOG)||(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode < GPIO_MODE_ALTFN)) //mode is non interrupt
	{
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //since each pin mode takes 2 bits *2
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));//clearing reg, to clear 2 bits, we & with ~3
		pGPIOHandle->pGPIOx->MODER |= temp;//setting reg
	}
	else //mode is interrupt based
	{
		// configure edge trigger
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);//Clear corresponding RTSR bit
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);//Clear corresponding FTSR bit
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else
		{

		}

		//configure which GPIO port(A,B,C,D,E,F,G,H,I) Should takeover EXTI pin for interrupt via SYSCFG_EXTICR register,
		uint8_t temp1 = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4);
		uint8_t temp2 = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4);
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] =portcode << (temp2 * 4);


		//enable EXTI interrupt delivery using IMR (interrupt mode register)
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

	}

	temp = 0;
	//configure the GPIO pin speed
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //since each pin speed mode takes 2 bits *2
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));//clearing reg, to clear 2 bits, we & with ~3
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;//setting reg


	temp = 0;
	//configure the pull up pull down mode
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber))); //since each pin PUPD mode is off 1 bit
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));//clearing reg,
	pGPIOHandle->pGPIOx->PUPDR |= temp;//setting reg


	temp = 0;
	//configure the pin output type mode
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));//since each pin Output mode is off 1 bit
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);//clearing reg,
	pGPIOHandle->pGPIOx->OTYPER |= temp;//setting reg


	temp = 0;
	//configure the alternating functionality mode if the mode is other than GPIO
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		uint8_t temp1, temp2;

		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2));//clearing reg,
		pGPIOHandle->pGPIOx->AFR[temp1] |= ((pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode) << (4 * temp2));//setting reg

	}

}

/*
*GPIO_DeInit()
*	- This API resets the GPIO pin
*	- GPIO_RegDef_t register structure to reset the ports peripheral register
*	-
*	-
*	-
*	- This function does not return anything
*	- No remarks
*/
void GPIO_DeInit(GPIO_RegDef_t* pGPIOx)
{

	if(pGPIOx == GPIOA)
	{
		GPIOA_PCLK_RESET();
	}
	else if(pGPIOx == GPIOB)
	{
		GPIOB_PCLK_RESET();
	}
	else if(pGPIOx == GPIOC)
	{
		GPIOC_PCLK_RESET();
	}
	else if(pGPIOx == GPIOD)
	{
		GPIOD_PCLK_RESET();
	}
	else if(pGPIOx == GPIOE)
	{
		GPIOE_PCLK_RESET();
	}
	else if(pGPIOx == GPIOF)
	{
		GPIOF_PCLK_RESET();
	}
	else if(pGPIOx == GPIOG)
	{
		GPIOG_PCLK_RESET();
	}
	else if(pGPIOx == GPIOH)
	{
		GPIOH_PCLK_RESET();
	}
	else if(pGPIOx == GPIOI)
	{
		GPIOI_PCLK_RESET();
	}


}



/*
*GPIO_ReadFromInputPin()
*	- This API reads from the GPIO pin
*	- GPIO_RegDef_t is the base address of GPIO peripheral
*	- PinNumber is the pin number in the port
*	-
*	-
*	- This function returns 8 bit read data
*	- No remarks
*/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001); //& with 0x00000001 to just extract the shifted value and mask the rest
	return value;
}

/*
*GPIO_ReadFromInputPort()
*	- This API reads from the GPIO port
*	- GPIO_RegDef_t is the base address of GPIO peripheral
*	-
*	-
*	-
*	- This function returns 16 bit read data
*	- No remarks
*/
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t* pGPIOx)
{
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR;//Though IDR is 32 bits, we only use 16 bits for pin data, rest 16 bits are reserved, hence typecasted
	return value;

}

/*
*GPIO_WriteToOutputPin()
*	- This API writes value to the GPIO pin
*	- GPIO_RegDef_t is the base address of GPIO peripheral
*	- PinNumber is the pin number in the port
*	- value is the value to be written on the pin
*	-
*	- This function does not return anything
*	- No remarks
*/
void GPIO_WriteToOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber, uint8_t value)
{
	if(value == GPIO_PIN_SET)
	{
		pGPIOx->ODR |= (1 << PinNumber); //Write HIGH
	}
	else
	{
		pGPIOx->ODR &= ~(1 << PinNumber); //Write LOW
	}
}

/*
*GPIO_WriteToOutputPort()
*	- This API writes value to the GPIO port
*	- GPIO_RegDef_t is the base address of GPIO peripheral
*	-
*	- value is the value to be written on the port
*	-
*	- This function does not return anything
*	- No remarks
*/
void GPIO_WriteToOutputPort(GPIO_RegDef_t* pGPIOx, uint16_t value)
{
	pGPIOx->ODR = value;
}

/*
*GPIO_ToggleOutputPin()
*	- This API toggles value on the GPIO pin
*	- GPIO_RegDef_t is the base address of GPIO peripheral
*	- PinNumber is the pin number in the port
*	-
*	-
*	- This function does not return anything
*	- No remarks
*/
void GPIO_ToggleOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1 << PinNumber);
}



/*
*GPIO_IRQConfig()
*	- This API initializes an IRQ on GPIO
*	- IRQNumber number on which IRQ is to be configured
*	- IRQPriority priority of interrupt
*	- EnOrDi macro enable or disable interrupt
*	-
*	- This function does not return anything
*	- No remarks
*/
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		if(IRQNumber <= 31) //since each register is 32 bits long, it can have 32 IRQ numbers
		{
			//program ISER0 register
			*NVIC_ISER0 |= (1 << IRQNumber);

		}
		else if(IRQNumber > 31 && IRQNumber < 64)
		{
			//program ISER1 register
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));//since each register is 32 bits long, it can have 32 IRQ numbers

		}
		else if(IRQNumber >=64 && IRQNumber < 96)
		{
			//program ISER2 register
			*NVIC_ISER2 |= (1 << (IRQNumber % 64));//since each register is 32 bits long, it can have 32 IRQ numbers

		}
	}
	else
	{
		if(IRQNumber <= 31)
		{
			//program ICER0 register
			*NVIC_ICER0 |= (1 << IRQNumber);

		}
		else if(IRQNumber > 31 && IRQNumber < 64)
		{
			//program ICER1 register
			*NVIC_ICER1 |= (1 << (IRQNumber % 32));//since each register is 32 bits long, it can have 32 IRQ numbers

		}
		else if(IRQNumber >=64 && IRQNumber < 96)
		{
			//program ICER2 register
			*NVIC_ICER2 |= (1 << (IRQNumber % 64));//since each register is 32 bits long, it can have 32 IRQ numbers

		}
	}

}


/*
*GPIO_IRQPriorityConfig()
*	- This API sets priority for an interrupt
*	- IRQNumber number on which IRQ is to be configured
*	- IRQPriority priority of interrupt
*	-
*	-
*	- This function does not return anything
*	- No remarks
*/
void GPIO_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority)
{
	//find out IPR register
	// there are 60 IPR registers with each register 32 bit long, dividing each register into 4 sections of 8 bits each,
	//i.e 4 IRQs can be set priority in each section
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;
	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_OF_PR_BITS_IMPLEMENTED);//in a section each register 8 bit long hence (IRQPriority << (8 * iprx_section))
																				// off 8 bits the 4 MSBs are implemented and 4 LSBs are don't care, hence (8 - 4)
	//(8 * iprx_section) is to move over iprx_section and + (8-4) is to move over to 4 MSB bits of iprx section and ignore the 4 LSB bits of iprx_section register

	*(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << (shift_amount));
	//*(NVIC_PR_BASE_ADDR + (iprx)) since NVIC_PR_BASE_ADDR is 32 bit variable, increment it by iprx

}

/*
*GPIO_IRQHandling()
*	- This API registers ISR against an interrupt
*	-
*	- PinNumber is the pin number for interrupt occurrence
*	-
*	-
*	- This function does not return anything
*	- No remarks
*/
void GPIO_IRQHandling(uint8_t pinNumber)
{
	//CLear the EXTI PR register for the corresponding pin numer
	if(EXTI->PR & (1 << pinNumber))
	{
		EXTI->PR |= (1 << pinNumber);
	}

}

