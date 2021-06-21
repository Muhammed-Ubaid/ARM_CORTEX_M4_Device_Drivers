/*
 * stm32f407xx_spi_drivers.h
 *
 *  Created on: 13-Jun-2021
 *      Author: Mohammed Ubaid
 */

#ifndef INC_STM32F407XX_SPI_DRIVERS_H_
#define INC_STM32F407XX_SPI_DRIVERS_H_

#include "stm32f407xx.h"

/* SPI config structure*/
typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;

}SPI_Config_t;


/* SPI handle structure*/
typedef struct
{
	SPI_RegDef_t *pSPIx; /* holds the base address of SPI peripheral register*/
	SPI_Config_t SPIConfig;

}SPI_Handle_t;


/* @SPI_DeviceMode */
#define SPI_DEVICE_MODE_MASTER	1
#define SPI_DEVICE_MODE_SLAVE	0

/* @SPI_BusConfig */
#define SPI_BUS_CONFIG_FD				1
#define SPI_BUS_CONFIG_HD				2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY	3


/* (perscaler) @SPI_SclkSpeed in CR1 baud rate control reg 3,4,5*/
#define SPI_SCLK_SPEED_DIV2				0
#define SPI_SCLK_SPEED_DIV4				1
#define SPI_SCLK_SPEED_DIV8				2
#define SPI_SCLK_SPEED_DIV16			3
#define SPI_SCLK_SPEED_DIV32			4
#define SPI_SCLK_SPEED_DIV64			5
#define SPI_SCLK_SPEED_DIV128			6
#define SPI_SCLK_SPEED_DIV256			7



/* @SPI_DFF */
#define SPI_DFF_8BITS			0
#define SPI_DFF_16BITS			1


/* @SPI_CPOL */
#define SPI_CPOL_HIGH			1
#define SPI_CPOL_LOW			0

/* @SPI_CPHA */
#define SPI_CPHA_HIGH			1
#define SPI_CPHA_LOW			0

/* @SPI_SSM */
#define SPI_SSM_EN			1
#define SPI_SSM_DI			0


#define SPI_TXE_FLAG			(1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG			(1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG			(1 << SPI_SR_BSY)


/* APIs for SPI driver, supported by this implementation */


/* SPI Peripheral clock setup */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);


/* SPI init and de-init */
void SPI_Init(SPI_Handle_t* pSPIHandle); /* for initializing the SPI pin/port */
void SPI_DeInit(SPI_RegDef_t* pSPIx); /* for de-initializing(reset) the SPI pin/port */


/* SPI data send and receive (Blocking, Polling, Non-interrupt based APIs) */
void SPI_SendData(SPI_RegDef_t* pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t* pSPIx, uint8_t *pRxBuffer, uint32_t Len);

/* SPI IRQ config and ISR handling */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnOrDi);
void SPI_IRQHandling(SPI_Handle_t* *pHandle);
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority);

/* Other peripheral control APIs */
uint8_t SPI_GetFlagStatus(SPI_RegDef_t* pSPIx, uint32_t FlagName);

void SPI_PeripheralControl(SPI_RegDef_t* pSPIx, uint8_t EnOrDi);
void SPI_SSIConfig(SPI_RegDef_t* pSPIx, uint8_t EnOrDi);


/* */













#endif /* INC_STM32F407XX_SPI_DRIVERS_H_ */
