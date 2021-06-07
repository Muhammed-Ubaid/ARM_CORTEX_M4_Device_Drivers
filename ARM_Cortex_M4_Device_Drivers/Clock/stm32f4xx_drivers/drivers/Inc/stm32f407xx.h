/*
 * stm32f407xx.h
 *
 *  Created on: May 27, 2021
 *      Author: Mohammed Ubaid
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>

#define __vo volatile

/* ARM Cortex Mx Processor NVIC ISERx (Interrupt Set-enable Registers) register addresses */
#define NVIC_ISER0		((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1		((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2		((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3		((__vo uint32_t*)0xE000E10c)


/* ARM Cortex Mx Processor NVIC ICERx (Interrupt Set-enable Registers) register addresses */
#define NVIC_ICER0		((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1		((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2		((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3		((__vo uint32_t*)0xE000E18c)

/* base address for ARM Cortex Mx priority register */
#define NVIC_PR_BASE_ADDR		((__vo uint32_t*)0xE000E400)

/* Number of priority bits implemented in 8 bit IPR */
#define NO_OF_PR_BITS_IMPLEMENTED	4

/*
 *  base addresses of FLASH and SRAM
 */
#define FLASH_BASEADDR 	0x08000000U
#define SRAM1_BASEADDR 	0x20000000U
#define SRAM2_BASEADDR	0x2001C000U /* SRAM1_BASEADDR + (112KB * 1024)bytes */
#define ROM_BASEADDR	0x1FFF0000U /* From embedded SRAM table, also known as system memory */
#define SRAM 			SRAM1_BASEADDR


/*
 * AHBx and APBx peripheral base addresses
 */
#define PERIPH_BASEADDR			0x40000000U
#define APB1PERIPH_BASEADDR		PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR		0x40010000U
#define AHB1PERIPH_BASEADDR		0x40020000U
#define AHB2PERIPH_BASEADDR		0x50000000U


/*
 * Defining base addresses of all peripherals interfaced with AHB1 bus
 */
#define GPIOA_BASEADDR			(AHB1PERIPH_BASEADDR+0x0000)
#define GPIOB_BASEADDR			(AHB1PERIPH_BASEADDR+0x0400)
#define GPIOC_BASEADDR			(AHB1PERIPH_BASEADDR+0x0800)
#define GPIOD_BASEADDR			(AHB1PERIPH_BASEADDR+0x0C00)
#define GPIOE_BASEADDR			(AHB1PERIPH_BASEADDR+0x1000)
#define GPIOF_BASEADDR			(AHB1PERIPH_BASEADDR+0x1400)
#define GPIOG_BASEADDR			(AHB1PERIPH_BASEADDR+0x1800)
#define GPIOH_BASEADDR			(AHB1PERIPH_BASEADDR+0x1C00)
#define GPIOI_BASEADDR			(AHB1PERIPH_BASEADDR+0x2000)
#define GPIOJ_BASEADDR			(AHB1PERIPH_BASEADDR+0x2400)
#define GPIOK_BASEADDR			(AHB1PERIPH_BASEADDR+0x2800)
#define RCC_BASEADDR			(AHB1PERIPH_BASEADDR+0x3800)


/*
 * Defining base addresses of all peripherals interfaced with APB1 bus
 */
#define I2C1_BASEADDR			(APB1PERIPH_BASEADDR+0x5400)
#define I2C2_BASEADDR			(APB1PERIPH_BASEADDR+0x5800)
#define I2C3_BASEADDR			(APB1PERIPH_BASEADDR+0x5C00)
#define SPI2_BASEADDR			(APB1PERIPH_BASEADDR+0x3800)
#define SPI3_BASEADDR			(APB1PERIPH_BASEADDR+0x3C00)

#define USART2_BASEADDR			(APB1PERIPH_BASEADDR+0x4400)
#define USART3_BASEADDR			(APB1PERIPH_BASEADDR+0x4800)

#define UART4_BASEADDR			(APB1PERIPH_BASEADDR+0x4C00)
#define UART5_BASEADDR			(APB1PERIPH_BASEADDR+0x5000)

#define CAN1_BASEADDR			(APB1PERIPH_BASEADDR+0x6400)
#define CAN2_BASEADDR			(APB1PERIPH_BASEADDR+0x6800)
#define PWR_BASEADDR			(APB1PERIPH_BASEADDR+0x7000)
#define DAC_BASEADDR			(APB1PERIPH_BASEADDR+0x7400)
#define UART7_BASEADDR			(APB1PERIPH_BASEADDR+0x7800)
#define UART8_BASEADDR			(APB1PERIPH_BASEADDR+0x7C00)



/*
 * Defining base addresses of all peripherals interfaced with APB2 bus
 */
#define SPI1_BASEADDR			(APB2PERIPH_BASEADDR+0x3000)
#define EXTI_BASEADDR			(APB2PERIPH_BASEADDR+0x3C00)
#define SYSCFG_BASEADDR			(APB2PERIPH_BASEADDR+0x3800)

#define USART1_BASEADDR			(APB2PERIPH_BASEADDR+0x1000)
#define USART6_BASEADDR			(APB2PERIPH_BASEADDR+0x1400)

#define TIM9_BASEADDR			(APB2PERIPH_BASEADDR+0x4000)
#define TIM10_BASEADDR			(APB2PERIPH_BASEADDR+0x4400)
#define TIM11_BASEADDR			(APB2PERIPH_BASEADDR+0x4800)
#define SPI5_BASEADDR			(APB2PERIPH_BASEADDR+0x5000)
#define SPI6_BASEADDR			(APB2PERIPH_BASEADDR+0x5400)
#define SAI1_BASEADDR			(APB2PERIPH_BASEADDR+0x5800)
#define LCD_BASEADDR			(APB2PERIPH_BASEADDR+0x6800)


/****** Peripheral register definition structure *******/
typedef struct
{
	__vo uint32_t MODER;		/* GPIO port mode register (GPIOx_MODER) 0x00 offset */
	__vo uint32_t OTYPER;		/* GPIO port output type register (GPIOx_OTYPER) 0x04 offset */
	__vo uint32_t OSPEEDR;		/* GPIO port output speed register (GPIOx_OSPEEDR) 0x08 */
	__vo uint32_t PUPDR;		/* GPIO port pull-up/pull-down register (GPIOx_PUPDR) 0x0C */
	__vo uint32_t IDR;			/* GPIO port input data register (GPIOx_IDR) 0x10 */
	__vo uint32_t ODR;			/* GPIO port output data register (GPIOx_ODR) 0x14*/
	__vo uint32_t BSRR;			/* GPIO port bit set/reset register (GPIOx_BSRR) 0x18*/
	__vo uint32_t LCKR;			/* GPIO port configuration lock register (GPIOx_LCKR) 0x1C*/
	__vo uint32_t AFR[2];		/* GPIO alternate function low register (GPIOx_AFRL) 0x20 offset for low-AFR and 0x24 offset for high-AFR*/
}GPIO_RegDef_t;


/****** Peripheral port base addresses definition for RCC *******/
typedef struct
{
	__vo uint32_t CR; /*RCC clock control register (RCC_CR) */
	__vo uint32_t PLLCFGR; /* RCC PLL configuration register (RCC_PLLCFGR)*/
	__vo uint32_t CFGR; /*RCC clock configuration register (RCC_CFGR) */
	__vo uint32_t CIR; /*RCC clock interrupt register (RCC_CIR) */
	__vo uint32_t AHB1RSTR; /* RCC AHB1 peripheral reset register (RCC_AHB1RSTR)*/
	__vo uint32_t AHB2RSTR; /*RCC AHB2 peripheral reset register (RCC_AHB2RSTR) */
	__vo uint32_t AHB3RSTR; /*RCC AHB3 peripheral reset register (RCC_AHB3RSTR) */
	uint32_t Reserved0; /* */
	__vo uint32_t APB1RSTR; /*RCC APB1 peripheral reset register (RCC_APB1RSTR) */
	__vo uint32_t APB2RSTR; /*RCC APB2 peripheral reset register (RCC_APB1RSTR) */
	uint32_t Reserved1[2]; /* */
	__vo uint32_t AHB1ENR; /*RCC AHB1 peripheral clock enable register (RCC_AHB1ENR) */
	__vo uint32_t AHB2ENR; /*RCC AHB2 peripheral clock enable register (RCC_AHB1ENR) */
	__vo uint32_t AHB3ENR; /*RCC AHB3 peripheral clock enable register (RCC_AHB1ENR) */
	uint32_t Reserved2; /* */
	__vo uint32_t APB1ENR; /*RCC APB1 peripheral clock enable register (RCC_AHB1ENR) */
	__vo uint32_t APB2ENR; /*RCC APB2 peripheral clock enable register (RCC_AHB1ENR) */
	uint32_t Reserved3[2];
	__vo uint32_t AHB1LPENR; /*RCC APB1 peripheral clock enable register (RCC_AHB1ENR) */
	__vo uint32_t AHB2LPENR; /*RCC APB1 peripheral clock enable register (RCC_AHB1ENR) */
	__vo uint32_t AHB3LPENR; /*RCC APB1 peripheral clock enable register (RCC_AHB1ENR) */
	uint32_t Reserved4; /* */
	__vo uint32_t APB1LPENR; /*RCC APB1 peripheral clock enable register (RCC_AHB1ENR) */
	__vo uint32_t APB2LPENR; /*RCC APB1 peripheral clock enable register (RCC_AHB1ENR) */
	uint32_t Reserved5[2];
	__vo uint32_t RCC_BDCR; /* */
	__vo uint32_t RCC_CSR; /* */
	uint32_t Reserved6[2];/* */
	__vo uint32_t RCC_SSCGR; /* */
	__vo uint32_t RCC_PLLI2SCFGR; /* */

}RCC_RegDef_t;




/****** Peripheral register structure definition for EXTI *******/
typedef struct
{
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;
}EXTI_RegDef_t;


/****** Peripheral register structure definition for SYSCFG *******/
typedef struct
{
	__vo uint32_t MEMRMP;
	__vo uint32_t PMC;
	__vo uint32_t EXTICR[4];
	uint32_t Reserved1[2];
	__vo uint32_t CMPCR;
	uint32_t Reserved2[2];
	__vo uint32_t CFGR;
}SYSCFG_RegDef_t;


/****** Peripheral port base addresses definition typecasted *******/
#define GPIOA ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH ((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI ((GPIO_RegDef_t*)GPIOI_BASEADDR)

#define RCC 	((RCC_RegDef_t*)RCC_BASEADDR)

#define EXTI	 ((EXTI_RegDef_t*)EXTI_BASEADDR)

#define SYSCFG	 ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

/* Clock enable macros for GPIOx peripherals*/
#define GPIOA_PCLK_EN() 		((RCC->AHB1ENR) |= (1<<0))
#define GPIOB_PCLK_EN() 		((RCC->AHB1ENR) |= (1<<1))
#define GPIOC_PCLK_EN() 		((RCC->AHB1ENR) |= (1<<2))
#define GPIOD_PCLK_EN() 		((RCC->AHB1ENR) |= (1<<3))
#define GPIOE_PCLK_EN() 		((RCC->AHB1ENR) |= (1<<4))
#define GPIOF_PCLK_EN() 		((RCC->AHB1ENR) |= (1<<5))
#define GPIOG_PCLK_EN() 		((RCC->AHB1ENR) |= (1<<6))
#define GPIOH_PCLK_EN() 		((RCC->AHB1ENR) |= (1<<7))
#define GPIOI_PCLK_EN() 		((RCC->AHB1ENR) |= (1<<8))


/* Clock enable macros for I2Cx peripherals*/
#define I2C1_PCLK_EN()			((RCC->APB1ENR) |= (1<<21))
#define I2C2_PCLK_EN()			((RCC->APB1ENR) |= (1<<22))
#define I2C3_PCLK_EN()			((RCC->APB1ENR) |= (1<<23))


/* Clock enable macros for SPIx peripherals*/
#define SPI1_PCLK_EN()			((RCC->APB2ENR) |= (1<<12))
#define SPI2_PCLK_EN()			((RCC->APB1ENR) |= (1<<14))
#define SPI3_PCLK_EN()			((RCC->APB1ENR) |= (1<<15))


/* Clock enable macros for USARTx peripherals*/
#define USART1_PCLK_EN()			((RCC->APB2ENR) |= (1<<4))
#define USART2_PCLK_EN()			((RCC->APB1ENR) |= (1<<17))
#define USART3_PCLK_EN()			((RCC->APB1ENR) |= (1<<18))
#define USART4_PCLK_EN()			((RCC->APB1ENR) |= (1<<19))
#define USART5_PCLK_EN()			((RCC->APB1ENR) |= (1<<20))
#define USART6_PCLK_EN()			((RCC->APB2ENR) |= (1<<5))


/* Clock enable macros for SYSCFG peripherals*/
#define SYSCFG_PCLK_EN()			((RCC->APB2ENR) |= (1<<14))


/* Clock disable macros for GPIOx peripherals*/
#define GPIOA_PCLK_DIS() 		((RCC->AHB1ENR) &= ~(1<<0))
#define GPIOB_PCLK_DIS() 		((RCC->AHB1ENR) &= ~(1<<1))
#define GPIOC_PCLK_DIS() 		((RCC->AHB1ENR) &= ~(1<<2))
#define GPIOD_PCLK_DIS() 		((RCC->AHB1ENR) &= ~(1<<3))
#define GPIOE_PCLK_DIS() 		((RCC->AHB1ENR) &= ~(1<<4))
#define GPIOF_PCLK_DIS() 		((RCC->AHB1ENR) &= ~(1<<5))
#define GPIOG_PCLK_DIS() 		((RCC->AHB1ENR) &= ~(1<<6))
#define GPIOH_PCLK_DIS() 		((RCC->AHB1ENR) &= ~(1<<7))
#define GPIOI_PCLK_DIS() 		((RCC->AHB1ENR) &= ~(1<<8))


/* Clock disable macros for I2Cx peripherals*/
#define I2C1_PCLK_DIS()			((RCC->APB1ENR) &= ~(1<<21))
#define I2C2_PCLK_DIS()			((RCC->APB1ENR) &= ~(1<<22))
#define I2C3_PCLK_DIS()			((RCC->APB1ENR) &= ~(1<<23))


/* Clock disable macros for SPIx peripherals*/
#define SPI1_PCLK_DIS()			((RCC->APB2ENR) &= ~(1<<12))
#define SPI2_PCLK_DIS()			((RCC->APB1ENR) &= ~(1<<14))
#define SPI3_PCLK_DIS()			((RCC->APB1ENR) &= ~(1<<15))


/* Clock disable macros for USARTx peripherals*/
#define USART1_PCLK_DIS()			((RCC->APB2ENR) &= ~(1<<4))
#define USART2_PCLK_DIS()			((RCC->APB1ENR) &= ~(1<<17))
#define USART3_PCLK_DIS()			((RCC->APB1ENR) &= ~(1<<18))
#define USART4_PCLK_DIS()			((RCC->APB1ENR) &= ~(1<<19))
#define USART5_PCLK_DIS()			((RCC->APB1ENR) &= ~(1<<20))
#define USART6_PCLK_DIS()			((RCC->APB2ENR) &= ~(1<<5))


/* Clock disable macros for SYSCFG peripherals*/
#define SYSCFG_PCLK_DIS()			((RCC->APB2ENR) &= ~(1<<14))

/* GPIO port reset macros*/
#define GPIOA_PCLK_RESET()			do { ((RCC->AHB1RSTR) |= (1<<0));	((RCC->AHB1RSTR) &= ~(1<<0)); } while(0)
#define GPIOB_PCLK_RESET()			do { ((RCC->AHB1RSTR) |= (1<<1));	((RCC->AHB1RSTR) &= ~(1<<1)); } while(0)
#define GPIOC_PCLK_RESET()			do { ((RCC->AHB1RSTR) |= (1<<2));	((RCC->AHB1RSTR) &= ~(1<<2)); } while(0)
#define GPIOD_PCLK_RESET()			do { ((RCC->AHB1RSTR) |= (1<<3));	((RCC->AHB1RSTR) &= ~(1<<3)); } while(0)
#define GPIOE_PCLK_RESET()			do { ((RCC->AHB1RSTR) |= (1<<4));	((RCC->AHB1RSTR) &= ~(1<<4)); } while(0)
#define GPIOF_PCLK_RESET()			do { ((RCC->AHB1RSTR) |= (1<<5));	((RCC->AHB1RSTR) &= ~(1<<5)); } while(0)
#define GPIOG_PCLK_RESET()			do { ((RCC->AHB1RSTR) |= (1<<6));	((RCC->AHB1RSTR) &= ~(1<<6)); } while(0)
#define GPIOH_PCLK_RESET()			do { ((RCC->AHB1RSTR) |= (1<<7));	((RCC->AHB1RSTR) &= ~(1<<7)); } while(0)
#define GPIOI_PCLK_RESET()			do { ((RCC->AHB1RSTR) |= (1<<8));	((RCC->AHB1RSTR) &= ~(1<<8)); } while(0)

#define GPIO_BASEADDR_TO_CODE(x)	(	(x == GPIOA)?0:\
										(x == GPIOB)?1:\
										(x == GPIOC)?2:\
										(x == GPIOD)?3:\
										(x == GPIOE)?4:\
										(x == GPIOF)?5:\
										(x == GPIOG)?6:\
										(x == GPIOH)?7:0)

/* Interrupt Request (IRQ) numbers */
#define IRQ_NO_EXTI0				6
#define IRQ_NO_EXTI1				7
#define IRQ_NO_EXTI2				8
#define IRQ_NO_EXTI3				9
#define IRQ_NO_EXTI4				10
#define IRQ_NO_EXTI9_5				23
#define IRQ_NO_EXTI15_10			40

/* macros for possible priority levels */
#define NVIC_IRQ_PRIO15 15



#define ENABLE			1
#define DISABLE			0
#define SET				ENABLE
#define RESET			DISABLE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET



#include "stm32f407xx_gpio_driver.h"


#endif /* INC_STM32F407XX_H_ */