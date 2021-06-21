/*
 * stm32f407xx_spi_drivers.c
 *
 *  Created on: 13-Jun-2021
 *      Author: Mohammed Ubaid
 */

#include "stm32f407xx_spi_drivers.h"

/*
*SPI_PeriClockControl()
*	- This API enables or disables the peripheral clock for the SPI port
*	- SPI_RegDef_t is the base address of SPI peripheral
*	- EnOrDi is a macro ENABLE or DISABLE for clock
*	-
*	-
*	- This function does not return anything
*	- No remarks
*/
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}
	}
	else
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DIS();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_PCLK_DIS();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_PCLK_DIS();
		}
	}

}


/*
*SPI_Init()
*	- This API initialized SPI pin for use
*	- SPI_Handle_t is the handle for GPIO pin
*	-
*	-
*	-
*	- This function does not return anything
*	- No remarks
*/
void SPI_Init(SPI_Handle_t* pSPIHandle)/* for initializing the SPI pin/port */
{

	SPI_PeriClockControl(pSPIHandle->pSPIx,ENABLE);
	uint32_t tempreg = 0;

	//configure device mode
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << 2;

	//configure bus config
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		//bi directional mode to be cleared
		tempreg &= ~(1<<15);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		//bi directional mode to be set
		tempreg |= (1<<15);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		//bi directional mode to be cleared
		tempreg &= ~(1<<15);
		//RXONLY in CR1 must be set to force the clock
		tempreg |= (1 << 10);
	}

	//configure SPI serial clock speed  (baud rate)
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << 3;

	//configure SPI DFF frame format
	tempreg |= pSPIHandle->SPIConfig.SPI_DFF << 11;

	//configure SPI CPOL
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << 1;

	//configure SPI CPHA
	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << 0;

	pSPIHandle->pSPIx->CR1 = tempreg;

}
/*
*SPI_DeInit()
*	- This API resets the SPI pin
*	- SPI_RegDef_t register structure to reset the ports peripheral register
*	-
*	-
*	-
*	- This function does not return anything
*	- No remarks
*/
void SPI_DeInit(SPI_RegDef_t* pSPIx) /* for de-initializing(reset) the SPI pin/port */
{

	if(pSPIx == SPI1)
	{
		SPI1_PCLK_RES();
	}
	else if(pSPIx == SPI2)
	{
		SPI2_PCLK_RES();
	}
	else if(pSPIx == SPI3)
	{
		SPI3_PCLK_RES();
	}

}

uint8_t SPI_GetFlagStatus(SPI_RegDef_t* pSPIx, uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

/* SPI data send and receive (Blocking, Polling, Non-interrupt based APIs) */
// Called blocking API as waits until all bytes of "Len" are transmitted and while loops can hang permanently
void SPI_SendData(SPI_RegDef_t* pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
	while(Len > 0)
	{
		//wait while TXE reg is set, always check TXE before writing data
		//while(!(pSPIx->SR & (1 << 1))); //waits until set, instead implementing a function
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);

		//check DFF bit in CR1
		if((pSPIx->CR1 & (1 << SPI_CR1_DFF))) //16 bit data
		{
			pSPIx->DR = *((uint16_t*)pTxBuffer);
			Len--;
			Len--;
			(uint16_t*)pTxBuffer++; //increment the TXBUFFER
		}
		else
		{
			pSPIx->DR = *(pTxBuffer);
			Len--;
			pTxBuffer++; //increment the TXBUFFER
		}
	}
}

void SPI_PeripheralControl(SPI_RegDef_t* pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SPE); //SPE bit is SPI ENABLE bit
	}
	else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}

void SPI_SSIConfig(SPI_RegDef_t* pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SSI);
	}
	else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
	}

}

void SPI_ReceiveData(SPI_RegDef_t* pSPIx, uint8_t *pRxBuffer, uint32_t Len);

/* SPI IRQ config and ISR handling */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnOrDi);
void SPI_IRQHandling(SPI_Handle_t* *pHandle);
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority);

/* Other peripheral control APIs */

