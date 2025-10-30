/*
 * stm32f4xx_spi_driver.h
 *
 *  Created on: Oct 2, 2025
 *      Author: tiberius
 */

#ifndef INC_STM32F4XX_SPI_DRIVER_H_
#define INC_STM32F4XX_SPI_DRIVER_H_
#include "stm32f407d.h"


//--------SPIx Configrations---------------------------
typedef struct
{
	__vo uint8_t DEV_MODE;								//Master or Slave - @ref : SPI_MSTR_SELECTION
	__vo uint8_t BUS_CFG;								//Transfering mode of the bus - @ref : SPI_BUS_CGF
	__vo uint8_t DFF;									//Data Frame Formate. 16 or 8 bit mode - @ref : SPI_BUS_CGF
	__vo uint8_t CPHA;									//Clock Phase, Input sample register at (0 leading or 1 trailing) - @ref : SPI_CLK_PHASE_MACROS
	__vo uint8_t CPOL;									//Clock Ploarity, idle state of clock - @ref : SPI_POL
	__vo uint8_t SSM;									//Software Slave Select Management - @ref : SPI_SSM_SELECTION
	__vo uint8_t Baud_Rate;								//Setting the Clock frequency - @ref : SPI_BR_CTRL (SysCLK/X)
}SPI_Config_t;
//--------SPIx Regsiter sStruct Definitions-------------
typedef struct
{
	__vo uint32_t SPI_CR1;
	__vo uint32_t SPI_CR2;
	__vo uint32_t SPI_SR;
	__vo uint32_t SPI_DR;
	__vo uint32_t SPI_CRCPR;
	__vo uint32_t SPI_RXCRCR;
	__vo uint32_t SPI_TXCRCR;
	__vo uint32_t SPI_I2SCFGR;
	__vo uint32_t SPI_I2SPR;
}SPI_RegDef_t;
//--------SPIx Registers (casted to Reg Struct)---------
#define SPI1				((SPI_RegDef_t*)SPI1_BADDR)
#define SPI2				((SPI_RegDef_t*)SPI2_BADDR)
#define SPI3				((SPI_RegDef_t*)SPI3_BADDR)
#define SPI4				((SPI_RegDef_t*)SPI4_BADDR)
#define SPI5				((SPI_RegDef_t*)SPI5_BADDR)
#define SPI6				((SPI_RegDef_t*)SPI6_BADDR)
//--------SPIx Handles----------------------------------
typedef struct
{
	SPI_Config_t SPI_CFG;
	SPI_RegDef_t* pSPI;
	uint8_t* pRXT_Buffer;
	uint8_t RX_Buf_Len;
	uint8_t RX_Status;
	uint8_t* pTX_Buffer;
	uint8_t TX_Buf_Len;
	uint8_t TX_Status;
}SPI_Handle_t;


/*------------------------------------Functions Prototypes---------------------------
-------------------------------------------------------------------------------------*/
//------------------------------------Initialize & Deinitialize-----------------------
void SPI_Init(SPI_Handle_t *pSPI_HNDL);
void SPI_Deinit(SPI_RegDef_t* pSPI);
//------------------------------------Clock (Enable & Disable)------------------------
void SPI_CLK_Ctrl(SPI_RegDef_t* pSPI,uint8_t EN_DI);
//------------------------------------SEND & RECIEVE DATA-----------------------------
void SPI_SEND_DATA(SPI_RegDef_t *sPI,uint8_t *SND_BUFF,uint32_t Len);
void SPI_RECIEVE_DATA(SPI_RegDef_t *sSPI,uint8_t *RCVD_BUFF,uint32_t Len);
//------------------------------------SEND & RECIEVE DATA Interrupt-------------------
uint8_t SPI_SEND_DATA_INTR(SPI_Handle_t* SPI_HNDL,uint8_t *SND_BUFF,uint32_t Len);
uint8_t SPI_RECIEVE_DATA_INTR(SPI_Handle_t* SPI_HNDL,uint8_t *RCVD_BUFF,uint32_t Len);
//------------------------------------Interrupts--------------------------------------
void SPI_IRQ_INT_Config(uint8_t IRQ_Num,uint8_t IRQ_EN_DI);
void SPI_IRQ_Priority_Config(uint8_t IRQ_Num,uint8_t IRQ_Priority);
void SPI_InterruptHandling(SPI_Handle_t* SPI_HNDL);
//------------------------------------SPI Peri EN/DI--------------------------------------
void SPI_Peripereal_ENORDI(SPI_RegDef_t *pSPI,uint8_t EN_DI);
//------------------------------------SPI SSI EN/DI--------------------------------------
void SPI_SSI_ENORDI(SPI_RegDef_t *pSPI,uint8_t EN_DI);
//------------------------------------SPI SSOE EN/DI--------------------------------------
void SPI_SSOE_ENORDI(SPI_RegDef_t *pSPI,uint8_t EN_DI);
//------------------------------------SPI Transmission / Receiver Close APIs--------------
void close_transmission(SPI_Handle_t*SPI_HNDL);
void close_receiver(SPI_Handle_t*SPI_HNDL);
//------------------------------------SPI Event Handler callback--------------------------------------
__weak void SPI_ApplicationEventCallBack(SPI_Handle_t *SPI_HNDL,uint8_t SPI_EVENT_OVR_ERR);
////------------------------------------SPI Get Flags status------
uint32_t SPI_GetFlagStatus(SPI_RegDef_t* pSPI,uint8_t FLG_NAME);




//**********************************SPI MACROS****************************************
//**********************************SPI CLOCK PHASE***********************************
/*
 * @SPI_CLK_PHASE_MACROS
 * @note- The pahse at which data should be recieved
 * */
#define SPI_CPHA_LEADING					0
#define SPI_CPHA_TRAILING					1
//**********************************SPI CLOCK POLARITY*********************************
/*
 * @SPI_POL
 * @note- The Volt level (1/0) at rest phase
 * */
#define SPI_CPOL_LOW						0
#define SPI_CPOL_HIGH						1
//**********************************SPI Master Selection************************
/*
 * @SPI_MSTR_SELECTION
 * */
#define SPI_SLV								0
#define SPI_MSTR							1
//**********************************SPI Baud Rate*******************************
/*
 * @SPI_BR_CTRL (SysCLK/X)
 * */
#define SPI_BR_DIV_2						0
#define SPI_BR_DIV_4						1
#define SPI_BR_DIV_8						2
#define SPI_BR_DIV_16						3
#define SPI_BR_DIV_32						4
#define SPI_BR_DIV_64						5
#define SPI_BR_DIV_128						6
#define SPI_BR_DIV_256						7
//**********************************SPI Software Slave Management*****************
/*
 * @SPI_SSM_SELECTION
 * */
#define SPI_SSM_DI							0
#define SPI_SSM_EN							1
//**********************************SPI Receive Only******************************
/*
 * @SPI_RXONLY
 * */
#define SPI_RXONLY_DI						0
#define SPI_RXONLY_EI						1
//**********************************SPI Data Frame Format*************************
/*
 * @SPI_DFF
 * */
#define SPI_DFF_8Bit						0
#define SPI_DFF_16Bit						1
//**********************************SPI Bus Config*******************************
/*
 * @SPI_BUS_CGF
 * */
#define SPI_BUS_FDUPLEX					0
#define SPI_BUS_HDUPLEX					1
#define SPI_BUS_RXONLY_SIMPLEX			3
//**********************************SPI Busy Macros*******************************
/*
 * @SPI_BUSY_Macros
 * */
#define SPI_FREE						0
#define SPI_TX_BZY						1
#define SPI_RX_BZY						2

/**********************************SPI Get Flags*******************************
@Get_Flags
*/
#define SPI_GET_TXE_FLAG				(1<<SPI_BIT_TXE)
#define SPI_GET_DFF_FLAG				(1<<SPI_BIT_DFF)
#define SPI_GET_BSY_FLAG				(1<<SPI_BIT_BSY)
#define SPI_GET_RENE_FLAG				(1<<SPI_BIT_RXNE)


#endif /* INC_STM32F4XX_SPI_DRIVER_H_ */
