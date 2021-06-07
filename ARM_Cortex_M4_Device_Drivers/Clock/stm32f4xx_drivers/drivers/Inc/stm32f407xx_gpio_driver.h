/*
 * stm32f407xx_gpio_driver.h
 *
 *  Created on: 29-May-2021
 *      Author: Mohammed Ubaid
 */

#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_

#include "stm32f407xx.h"


typedef struct
{
	uint8_t GPIO_PinNumber; 		/* for possible values refer @GPIO_PIN_NO*/
	uint8_t GPIO_PinMode;			/* for possible values refer @GPIO_MODE*/
	uint8_t GPIO_PinSpeed;			/* for possible values refer @GPIO_SPEED*/
	uint8_t GPIO_PinPuPdControl;	/* for possible values refer @GPIO_PUPD*/
	uint8_t GPIO_PinOPType;			/* for possible values refer @GPIO_OP_TYPE*/
	uint8_t GPIO_PinAltFunMode;

}GPIO_PinConfig_t;


/* Handle structure for a gpio pin*/
typedef struct
{
	GPIO_RegDef_t* pGPIOx; /* holds the base address of to the gpio port to which the pin belongs */
	GPIO_PinConfig_t GPIO_PinConfig;
}GPIO_Handle_t;





/*@GPIO_PIN_NO
 * Macros for Possible pin mnumbers
 *
 */
#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15



/*@GPIO_MODE
 * Macros for Possible pin modes
 *
 */
#define GPIO_MODE_IN		0
#define GPIO_MODE_OUT		1
#define GPIO_MODE_ALTFN		2
#define GPIO_MODE_ANALOG	3
#define GPIO_MODE_IT_FT		4 //Interrupt configuration Falling edge detection
#define GPIO_MODE_IT_RT		5 //Interrupt configuration Rising edge detection
#define GPIO_MODE_IT_RFT	6 //Interrupt configuration Rising and Falling edge detection


/*@GPIO_OP_TYPE
 * Macros for Possible pin output types
 *
 */
#define GPIO_OP_TYPE_PP		0
#define GPIO_OP_TYPE_OD		1


/*@GPIO_SPEED
 * Macros for Possible pin output speed
 *
 */
#define GPIO_SPEED_LOW		0
#define GPIO_SPEED_MEDIUM	1
#define GPIO_SPEED_FAST		2
#define GPIO_SPEED_HIGH		3


/*@GPIO_PUPD
 * Macros for Possible pin Pull Up and Pull down config
 *
 */
#define GPIO_NO_PUPD		0
#define GPIO_PIN_PU			1
#define GPIO_PIN_PD			2




/*
 * APIs supported by this driver, for implementation details, check the API definitions
 *
 */

/* peripheral clock setup*/
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi);


/* GPIO Init and de-init */
void GPIO_Init(GPIO_Handle_t* pGPIOHandle); /* for initializing the GPIO pin/port */
void GPIO_DeInit(GPIO_RegDef_t* pGPIOx); /* for de-initializing(reset) the GPIO pin/port */

/*Data read and write*/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t* pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber, uint8_t value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t* pGPIOx, uint16_t value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber);


/* IRQ config and ISR handling*/
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnOrDi);
void GPIO_IRQHandling(uint8_t pinNumber);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority);







#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */
