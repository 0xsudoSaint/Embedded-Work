/*
 * stm32f4xx_spi_driver.c
 *
 *  Created on: Oct 2, 2025
 *      Author: tiberius
 */

#include "stm32f4xx_spi_driver.h"
//------------------------------------SPI Interrupt Handlers (Helping Functions)-----------------------------

void spi_txe_intr_handler(SPI_Handle_t* SPI_HNDL)
{
	if(SPI_HNDL->pSPI->SPI_CR1 & (1<<SPI_BIT_DFF))				//16 Bit data frame mode
	{
		SPI_HNDL->pSPI->SPI_DR=*(uint16_t*)SPI_HNDL->pTX_Buffer;
		(uint16_t*)SPI_HNDL->pTX_Buffer++;
		SPI_HNDL->TX_Buf_Len-=2;
	}
	else														//8 Bit data frame mode
	{
		SPI_HNDL->pSPI->SPI_DR=*SPI_HNDL->pTX_Buffer;
		SPI_HNDL->pTX_Buffer++;
		SPI_HNDL->TX_Buf_Len-=1;
	}


	if(!SPI_HNDL->TX_Buf_Len)									//Negation of len means , it will work for LEN>
	{
		close_transmission(SPI_HNDL);
		SPI_ApplicationEventCallBack(SPI_HNDL,SPI_EVENT_TX_CMPLT);
	}
}
void spi_rxne_intr_handler(SPI_Handle_t* SPI_HNDL)
{
	if(SPI_HNDL->pSPI->SPI_CR1 & SPI_BIT_DFF)					//16 bit Data frame formate
	{
		*(uint16_t*)SPI_HNDL->pRXT_Buffer=SPI_HNDL->pSPI->SPI_DR;
		(uint16_t*)SPI_HNDL->pRXT_Buffer++;
		SPI_HNDL->RX_Buf_Len-=2;
	}
	else														//8 bit data frame formate
	{
		*SPI_HNDL->pRXT_Buffer=SPI_HNDL->pSPI->SPI_DR;
		SPI_HNDL->pRXT_Buffer++;
		SPI_HNDL->RX_Buf_Len-=1;
	}

	if(!SPI_HNDL->RX_Buf_Len)
	{
		close_receiver(SPI_HNDL);
		SPI_ApplicationEventCallBack(SPI_HNDL,SPI_EVENT_RX_CMPLT);
	}
}
void spi_ovr_err_intr_handler(SPI_Handle_t* SPI_HNDL)
{
	uint8_t temp=0;
	if(SPI_HNDL->TX_Status!=SPI_TX_BZY)
	{
		temp = SPI_HNDL->pSPI->SPI_DR;
		temp = SPI_HNDL->pSPI->SPI_SR;
	}
	SPI_ApplicationEventCallBack(SPI_HNDL,SPI_EVENT_OVER_ERR_CMPLT);
}
//------------------------------------SPI Transmission / Receiver Close APIs--------------
void close_transmission(SPI_Handle_t*SPI_HNDL)
{
	//Clearing the TXEIE bit
	SPI_HNDL->pSPI->SPI_CR2 &=~(1<<SPI_BIT_CR2_TXEIE);
	//Clearing the global TX realted data in SPI Handle
	SPI_HNDL->TX_Buf_Len=0;
	SPI_HNDL->TX_Status=SPI_FREE;
	SPI_HNDL->pTX_Buffer=NULL;
}
void close_receiver(SPI_Handle_t*SPI_HNDL)
{
	//Clearing of the RXNIE flag
	SPI_HNDL->pSPI->SPI_CR2 &=~(1<<SPI_BIT_CR2_RXNEIE);
	//Clearing of the Global RX data of SPI handle
	SPI_HNDL->RX_Buf_Len=0;
	SPI_HNDL->RX_Status=SPI_FREE;
	SPI_HNDL->pRXT_Buffer=NULL;
}

//------------------------------------SPI Event Handler callback--------------------------------------
__weak void SPI_ApplicationEventCallBack(SPI_Handle_t *SPI_HNDL,uint8_t SPI_EVENT_OVR_ERR)
{
	return;
}
////------------------------------------SPI Get Flags status------
///***************************************************************
// * @fn					-SPI_GetFlagStatus
// *
// * @brief					-Get status of X SPI flag
// *
// * @param[1]				-SPI register base address
// * @param[2]				-Flag name (Macros ref : @Get_Flags)
// * @param[3]				-
// *
// * @return				-unsiged int 32
// *
// * @note					-
// *
// *
// * */
uint32_t SPI_GetFlagStatus(SPI_RegDef_t* pSPI,uint8_t FLG_NAME)
{
	if(pSPI->SPI_SR & FLG_NAME)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}
////------------------------------------Initialize & Deinitialize-----------------------
///***************************************************************
// * @fn						-SPI_Init
// *
// * @brief					-Initializing the SPI peripheral
// *
// * @param[1]				-SPI handle
// * @param[2]				-
// * @param[3]				-
// *
// * @return				-none
// *
// * @note					-noe
// *
// *
// * */
void SPI_Init(SPI_Handle_t *pSPI_HNDL)
{
	uint32_t temp=0;
	SPI_CLK_Ctrl(pSPI_HNDL->pSPI, ENABLE);
	//Setting of master bit
	temp |= (pSPI_HNDL->SPI_CFG.DEV_MODE<<SPI_BIT_MSTR);

	if(pSPI_HNDL->SPI_CFG.BUS_CFG==SPI_BUS_FDUPLEX)
	{
		//Clearing of BI_DIR_MODE
		temp &=~(1<<SPI_BIT_BIDIMODE);
	}
	else if(pSPI_HNDL->SPI_CFG.BUS_CFG==SPI_BUS_HDUPLEX)
	{
		temp |=(1<<SPI_BIT_BIDIMODE);
	}
	else if(pSPI_HNDL->SPI_CFG.BUS_CFG==SPI_BUS_RXONLY_SIMPLEX)
	{
		temp &=~(1<<SPI_BIT_BIDIMODE);
		temp |=(1<<SPI_BIT_RXONLY);
	}

	//*******************************Data frame Size setting *****************
	temp |= pSPI_HNDL->SPI_CFG.Baud_Rate<<SPI_BIT_BR;
	temp |= pSPI_HNDL->SPI_CFG.DFF<<SPI_BIT_DFF;
	temp |= pSPI_HNDL->SPI_CFG.CPHA<<SPI_BIT_CPHA;
	temp |= pSPI_HNDL->SPI_CFG.CPOL<<SPI_BIT_CPOL;
	temp |= pSPI_HNDL->SPI_CFG.SSM<<SPI_BIT_SSM;

	pSPI_HNDL->pSPI->SPI_CR1=temp;

}
////------------------------------------Initialize & Deinitialize-----------------------
///***************************************************************
// * @fn					-SPI_DeInit
// *
// * @brief					-Deinitializing the SPI peripheral
// *
// * @param[1]				-SPI Register Base address
// * @param[2]				-
// * @param[3]				-
// *
// * @return				-none
// *
// * @note					-noe
// *
// *
// * */
void SPI_Deinit(SPI_RegDef_t* pSPI)
{
	uint32_t rest_val=0;
	pSPI->SPI_CR1=rest_val;
}
//------------------------------------Clock (Enable & Disable)------------------------
///***************************************************************
// * @fn					-SPI_CLK_Ctrl
// *
// * @brief					-Enable or Disable the Peripheral clock
// *
// * @param[1]				-SPI registers base address
// * @param[2]				-ENABLE or Disable Macro
// * @param[3]				-
// *
// * @return				-none
// *
// * @note					-noe
// *
// *
// * */
void SPI_CLK_Ctrl(SPI_RegDef_t* pSPI,uint8_t EN_DI)
{
	if(EN_DI==ENABLE)
	{
		if(pSPI==SPI1)
		{
			SPI1_PCLK_EN();return;
		}
		if(pSPI==SPI2)
		{
			SPI2_PCLK_EN();return;
		}
		if(pSPI==SPI3)
		{
			SPI3_PCLK_EN();return;
		}
		if(pSPI==SPI4)
		{
			SPI4_PCLK_EN();return;
		}
		if(pSPI==SPI5)
		{
			SPI5_PCLK_EN();return;
		}
		if(pSPI==SPI6)
		{
			SPI6_PCLK_EN();return;
		}
	}
	else
	{
		if(pSPI==SPI1)
		{
			SPI1_PCLK_DI();return;
		}
		if(pSPI==SPI2)
		{
			SPI2_PCLK_DI();return;
		}
		if(pSPI==SPI3)
		{
			SPI3_PCLK_DI();return;
		}
		if(pSPI==SPI4)
		{
			SPI4_PCLK_DI();return;
		}
		if(pSPI==SPI5)
		{
			SPI5_PCLK_DI();return;
		}
		if(pSPI==SPI6)
		{
			SPI6_PCLK_DI();return;
		}
	}
}
//------------------------------------SEND & RECIEVE DATA-----------------------------
/***************************************************************
 * @fn						-SPI_SEND_DATA
 *
 * @brief					-Sending of the SPI_DATA (in bytes)
 *
 * @param[1]				-SPI registers base address
 * @param[2]				-Pointer to data buffer
 * @param[3]				-length of the string/buffer
 *
 * @return					-none
 *
 * @note					-This is a blocking call, or a polling function (while loop polls till we get set flag)
 *
 *
 * */
void SPI_SEND_DATA(SPI_RegDef_t* pSPI,uint8_t* SND_BUFF,uint32_t Len)
{
	while(Len>0)
	{
		while(SPI_GetFlagStatus(pSPI, SPI_GET_TXE_FLAG)==FLAG_RESET);
		if(pSPI->SPI_CR1 & SPI_GET_DFF_FLAG)							//16 Bit / 2 Byte Frame
		{
			pSPI->SPI_DR=*(uint16_t*)SND_BUFF;
			Len-=2;
			(uint16_t*)SND_BUFF++;
		}
		else 															//8 Bit / 1 Byte Frame
		{
			pSPI->SPI_DR=*SND_BUFF;
			Len-=1;
			SND_BUFF++;
		}
	}
}
void SPI_RECIEVE_DATA(SPI_RegDef_t* pSPI,uint8_t* RCVD_BUFF,uint32_t Len)
{
	while(Len>0)
	{
		while((SPI_GetFlagStatus(pSPI, SPI_GET_RENE_FLAG))==FLAG_RESET);
		if(pSPI->SPI_CR1 & SPI_GET_DFF_FLAG)
		{
			*(uint16_t*)RCVD_BUFF=pSPI->SPI_DR;
			Len-=2;
			(uint16_t*)RCVD_BUFF++;
		}
		else
		{
			*RCVD_BUFF=pSPI->SPI_DR;
			Len-=1;
			RCVD_BUFF++;
		}
	}
}
//------------------------------------SEND & RECIEVE DATA Interrupt-------------------
uint8_t SPI_SEND_DATA_INTR(SPI_Handle_t* SPI_HNDL,uint8_t *TX_BUFF,uint32_t Len)
{
	uint8_t status=SPI_HNDL->TX_Status;
	if(SPI_HNDL->TX_Status!=SPI_TX_BZY)
	{
		SPI_HNDL->TX_Buf_Len=Len;
		SPI_HNDL->pTX_Buffer=TX_BUFF;

		SPI_HNDL->TX_Status=SPI_TX_BZY;

		SPI_HNDL->pSPI->SPI_CR2 |=(1<<SPI_BIT_CR2_TXEIE);
	}
	return status;
}
uint8_t SPI_RECIEVE_DATA_INTR(SPI_Handle_t* SPI_HNDL,uint8_t *RX_BUFF,uint32_t Len)
{
	uint8_t status=SPI_HNDL->RX_Status;
	if(status!=SPI_RX_BZY)
	{
		SPI_HNDL->RX_Buf_Len=Len;
		SPI_HNDL->pRXT_Buffer=RX_BUFF;

		SPI_HNDL->RX_Status=SPI_RX_BZY;
		SPI_HNDL->pSPI->SPI_CR2 |= (1<<SPI_BIT_CR2_RXNEIE);
	}

	return status;
}
//------------------------------------Interrupts--------------------------------------
void SPI_IRQ_INT_Config(uint8_t IRQ_Num,uint8_t IRQ_EN_DI)
{
	if(IRQ_EN_DI==ENABLE)
	{
		if(IRQ_Num<=31)
		{
			*NVIC_ICER0_BADDR |= (1<<IRQ_Num);
		}
		else if(IRQ_Num>=32 && IRQ_Num<=63)
		{
			*NVIC_ICER1_BADDR |= (1<<(IRQ_Num%32));
		}
		else if(IRQ_Num>=64 && IRQ_Num <=95)
		{
			*NVIC_ICER2_BADDR |= (1<<(IRQ_Num%32));
		}
	}
	else
	{
		if(IRQ_Num<=31)
		{
			*NVIC_ICER0_BADDR &= ~(1<<IRQ_Num);
		}
		else if(IRQ_Num>=32 && IRQ_Num<=63)
		{
			*NVIC_ICER1_BADDR &= ~(1<<(IRQ_Num%32));
		}
		else if(IRQ_Num>=64 && IRQ_Num <=95)
		{
			*NVIC_ICER2_BADDR &= ~(1<<(IRQ_Num%32));
		}
	}
}
void SPI_IRQ_Priority_Config(uint8_t IRQ_Num,uint8_t IRQ_Priority)
{
	uint8_t ipr_section=IRQ_Num/4;
	uint8_t ipr_offset=IRQ_Num%4;
	uint8_t lft_shf_value=(ipr_offset*8)+(8-RESRVED_PBITS);
	*(NVIC_IPR_BADDR + (ipr_section*4))|=(IRQ_Priority<<lft_shf_value);
}
void SPI_InterruptHandling(SPI_Handle_t* SPI_HNDL)
{
	uint8_t temp1, temp2;

	//TX Int Handling
	temp1= SPI_HNDL->pSPI->SPI_CR2 & (1<< SPI_BIT_CR2_TXEIE);
	temp2=SPI_HNDL->pSPI->SPI_SR & (1<<SPI_BIT_TXE);
	if(temp1 && temp2)
	{
		spi_txe_intr_handler(SPI_HNDL);
	}

	//RX Int Handling
	temp1=SPI_HNDL->pSPI->SPI_CR2 & (1<<SPI_BIT_CR2_RXNEIE);
	temp2=SPI_HNDL->pSPI->SPI_SR & (1<<SPI_BIT_RXNE);
	if(temp1 & temp2)
	{
		spi_rxne_intr_handler(SPI_HNDL);
	}

	//OVR Int Handling
	temp1 = SPI_HNDL->pSPI->SPI_SR & (1<<SPI_BIT_SR_MODF);
	if(temp1)
	{
		spi_ovr_err_intr_handler(SPI_HNDL);
	}

	//MODF Int Handling
	temp1=SPI_HNDL->pSPI->SPI_SR & (1<<SPI_BIT_SR_MODF);
	if(temp1)
	{
		spi_modf_intr_handler();
	}

	//CRC Int Handling

	//TI Int Handling
}


//------------------------------------SPI Peripheral EN/DI-----------------------------
/***************************************************************
 * @fn						-SPI_Peripereal_ENORDI
 *
 * @brief					-EN or DI the SPE bit of CR1 register of SPI
 *
 * @param[1]				-SPI registers base address
 * @param[2]				-Enable or Disable macro
 * @param[3]				-
 *
 * @return					-none
 *
 * @note					-
 *
 *
 * */
void SPI_Peripereal_ENORDI(SPI_RegDef_t *pSPI,uint8_t EN_DI)
{
	if(EN_DI==ENABLE)
	{
		pSPI->SPI_CR1|=(1<<SPI_BIT_EN);
	}
	else
	{
		pSPI->SPI_CR1&=~(1<<SPI_BIT_EN);
	}
}
//------------------------------------SPI SSI EN/DI-----------------------------
/***************************************************************
 * @fn						-SPI_SSI_ENORDI
 *
 * @brief					-EN or DI the SSI bit of CR1 register of SPI
 *
 * @param[1]				-SPI registers base address
 * @param[2]				-Enable or Disable macro
 * @param[3]				-
 *
 * @return					-none
 *
 * @note					-
 *
 *
 * */
void SPI_SSI_ENORDI(SPI_RegDef_t *pSPI,uint8_t EN_DI)
{
	if(EN_DI==ENABLE)
	{
		pSPI->SPI_CR1|=(1<<SPI_BIT_SSI);
	}
	else
	{
		pSPI->SPI_CR1&=~(1<<SPI_BIT_SSI);
	}
}

//------------------------------------SPI SSOE EN/DI--------------------------------------
/***************************************************************
 * @fn						-SPI_SSOE_ENORDI
 *
 * @brief					-EN or DI the SSOE bit of CR2 register of SPI
 *
 * @param[1]				-SPI registers base address
 * @param[2]				-Enable or Disable macro
 * @param[3]				-
 *
 * @return					-none
 *
 * @note					-
 *
 *
 * */
void SPI_SSOE_ENORDI(SPI_RegDef_t *pSPI,uint8_t EN_DI)
{
	if(EN_DI==ENABLE)
	{
		pSPI->SPI_CR2 |=(1<<SPI_BIT_SSOE);
	}
	else
	{
		pSPI->SPI_CR2 &=~(1<<SPI_BIT_SSOE);
	}
}
