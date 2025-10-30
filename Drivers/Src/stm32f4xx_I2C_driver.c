/*
 * stm32f4xx_I2C_driver.c
 *
 *  Created on: Oct 18, 2025
 *      Author: tiberius
 */

#include "stm32f4XX_I2C_driver.h"

uint16_t AHB_PRESC[]={1,2,4,8,16,32,64,128,256,512};
uint16_t APB_PRESC[]={1,2,4,8,16};

//------------------------------------I2C Flags Status Registers--------------------------------------
static uint32_t I2C_GetFlagStatus_SR1(I2C_RegDef_t* pI2C,uint8_t FLG_NAME);
static void I2C_GenStartCond(I2C_RegDef_t* pI2Cx);
static void I2C_GenEndCond(I2C_RegDef_t* pI2Cx);
static void I2C_ExecAddrSndPhase(I2C_RegDef_t* pI2Cx,uint8_t SlaveAddr);
static void I2C_AddrRead(I2C_RegDef_t* pI2Cx);
static uint32_t RCC_GetPCLK1value(void);
static uint32_t I2C_GetFlagStatus_SR1(I2C_RegDef_t* pI2C,uint8_t FLG_NAME)
{
	if(pI2C->I2C_SR1 & FLG_NAME)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

static void I2C_GenStartCond(I2C_RegDef_t* pI2Cx)
{
	pI2Cx->I2C_CR1 |= (ENABLE<<I2C_CR1_START);
}
static void I2C_GenEndCond(I2C_RegDef_t* pI2Cx)
{
	pI2Cx->I2C_CR1 |= (ENABLE<<I2C_CR1_STOP);
}
static void I2C_ExecAddrSndPhase(I2C_RegDef_t* pI2Cx,uint8_t SlaveAddr)
{
	uint8_t temp8_reg =0;
	temp8_reg |= (SlaveAddr<<1);
	pI2Cx->I2C_DR=temp8_reg;
}

static void I2C_AddrRead(I2C_RegDef_t* pI2Cx)
{
	uint32_t temp32_reg;
	temp32_reg=pI2Cx->I2C_SR1;
	temp32_reg=pI2Cx->I2C_SR2;
}

static uint32_t RCC_GetPLLvalue(void)
{
	//TODO
	//implement the get PLL function
	return 1;
}
static uint32_t RCC_GetPCLK1value(void)
{
	uint32_t PCLK,SysCLKval;

	uint8_t SYSCLK_SW_STATUS= (RCC_REG->RCC_CFGR>>2) & 0x3;					//last 2 bits and with 3 (11) => last two bits

	if(SYSCLK_SW_STATUS==SYSCLK_SW_STATUS_HSI)
	{
		SysCLKval=16000000;
	}
	else if(SYSCLK_SW_STATUS==SYSCLK_SW_STATUS_HSE)
	{
		SysCLKval=8000000;
	}
	else if(SYSCLK_SW_STATUS==SYSCLK_SW_STATUS_PLL)
	{
		SysCLKval=RCC_GetPLLvalue();
	}
	else if(SYSCLK_SW_STATUS==SYSCLK_SW_STATUS_NA)
	{
		SysCLKval=__NA;
	}

	uint8_t AHBPRESCstatus= (RCC_REG->RCC_CFGR>>4) & 0xF;
	uint8_t temp=8;
	uint16_t AHBPRESECval;
	if(AHBPRESCstatus<temp)
	{
		AHBPRESECval=AHB_PRESC[temp-8];
	}
	else if(AHBPRESCstatus==temp)
	{
		AHBPRESECval=AHB_PRESC[temp-7];
	}
	else if(AHBPRESCstatus==temp+1)
	{
		AHBPRESECval=AHB_PRESC[temp-6];
	}
	else if(AHBPRESCstatus==temp+2)
	{
		AHBPRESECval=AHB_PRESC[temp-5];
	}
	else if(AHBPRESCstatus==temp+3)
	{
		AHBPRESECval=AHB_PRESC[temp-4];
	}
	else if(AHBPRESCstatus==temp+4)
	{
		AHBPRESECval=AHB_PRESC[temp-3];
	}
	else if(AHBPRESCstatus==temp+5)
	{
		AHBPRESECval=AHB_PRESC[temp-2];
	}
	else if(AHBPRESCstatus==temp+6)
	{
		AHBPRESECval=AHB_PRESC[temp-1];
	}
	else if(AHBPRESCstatus==temp+7)
	{
		AHBPRESECval=AHB_PRESC[temp];
	}
	uint8_t APBPRESCstatus= (RCC_REG->RCC_CFGR>>10) & 0x7;
	uint8_t APBPRESECval;
	temp=4;
	if(APBPRESCstatus<temp)
	{
		APBPRESECval=APB_PRESC[temp-4];
	}
	if(APBPRESCstatus==temp)
	{
		APBPRESECval=APB_PRESC[temp-3];
	}
	else if(APBPRESCstatus==temp+1)
	{
		APBPRESECval=APB_PRESC[temp-2];
	}
	else if(APBPRESCstatus==temp+2)
	{
		APBPRESECval=APB_PRESC[temp-1];
	}
	else if(APBPRESCstatus==temp+3)
	{
		APBPRESECval=APB_PRESC[temp];
	}
	PCLK=(SysCLKval/AHBPRESECval)/APBPRESECval;
	return PCLK;
}

//**************************************************************************************/
//************************************Initialize & Deinitialize***********************
void I2C_Init(I2C_Handle_t *pI2C_HNDL)
{
	uint16_t temp=0;
	//I2C FREQ bits setting
	temp=RCC_GetPCLK1value()/1000000U;				//As we dont need the value in MHz
	pI2C_HNDL->pI2Cx->I2C_CR2 |= temp & 0x3F;
	//ACKCTRL
	temp=pI2C_HNDL->I2C_Config.I2C_ACKControl;
	pI2C_HNDL->pI2Cx->I2C_CR1 |= (temp<<I2C_CR1_ACK);
	//Device address bit setting for slave mode
	//TODO::Handle 10-bit address condition
	temp=pI2C_HNDL->I2C_Config.I2C_DeviceAddress;
	pI2C_HNDL->pI2Cx->I2C_OAR1 |= (1<<14);
	pI2C_HNDL->pI2Cx->I2C_OAR1 |= (temp<<1);

	//CCR setting
	uint16_t ccr_reg;

	if(pI2C_HNDL->I2C_Config.I2C_SCLSpeed<=I2C_SCL_SPEED_SM)
	{
		/*
		 * @NOTE - Calculation ==> @ref at CCR reg section of ref manual
		 *
		 * T_h+T_low= 2 (CCR/T_pclk)
		 *
		 * ccr=F_pclk/(2 F_SCL)
		 *
		 */
		ccr_reg=RCC_GetPCLK1value() / (2 * pI2C_HNDL->I2C_Config.I2C_SCLSpeed);
		pI2C_HNDL->pI2Cx->I2C_CCR |= ccr_reg &  0x7FF;
	}
	else
	{
		pI2C_HNDL->pI2Cx->I2C_CCR |= (ENABLE<<I2C_CCR_FST_SLW_MODE);

		if(pI2C_HNDL->I2C_Config.I2C_FMDutyCycle == I2C_FM_Duty_Cycle_2) 						//Duty Disable
		{
		/*
		 * @NOTE - Calculation ==> @ref at CCR reg section of ref manual
		 *
		 * T_h+T_low= 1.7 (ccr * T_pclk)
		 *
		 * ccr=F_pclk/(1.7 F_SCL)
		 *
		 */
			pI2C_HNDL->pI2Cx->I2C_CCR |= (DISABLE<<I2C_CCR_DUTY);
			ccr_reg=RCC_GetPCLK1value() / (3 * pI2C_HNDL->I2C_Config.I2C_SCLSpeed);
			pI2C_HNDL->pI2Cx->I2C_CCR |= ccr_reg &  0x7FF;
		}
		else if(pI2C_HNDL->I2C_Config.I2C_FMDutyCycle == I2C_FM_Duty_Cycle_16_9)				//Duty Enable
		{
			pI2C_HNDL->pI2Cx->I2C_CCR |= (ENABLE<<I2C_CCR_DUTY);
			ccr_reg=RCC_GetPCLK1value() / (25 * pI2C_HNDL->I2C_Config.I2C_SCLSpeed);
			pI2C_HNDL->pI2Cx->I2C_CCR |= ccr_reg &  0x7FF;
		}
	}
	/*
	 * ts/2tpck= CCR ==> CCR = Fpclk/2F
	 * */


	if(pI2C_HNDL->I2C_Config->I2C_SCLSpeed<=I2C_SCL_SPEED_SM)
	{
		temp=(RCC_GetPCLK1value()/1000000U)+1;
	}
	else
	{
		temp=(RCC_GetPCLK1value()/1000000000U)+1;
	}

	pI2C_HNDL->pI2Cx->I2C_TRISE|= (temp & 0x3F);
}
void I2C_Deinit(I2C_RegDef_t* pI2C)
{
	uint16_t reset_value=0;
	pI2C->I2C_CR1=reset_value;
	pI2C->I2C_CCR=reset_value;
	pI2C->I2C_CR2=reset_value;
	pI2C->I2C_SR1=reset_value;
	pI2C->I2C_SR2=reset_value;
}
//************************************Clock (Enable & Disable)************************
void I2C_EnableClock(I2C_RegDef_t* pI2Cx,uint8_t EN_DI)
{
	if(EN_DI==ENABLE)
	{
		if(I2C1==pI2Cx)
		{
			I2C1_PCLK_EN();
		}
		if(I2C2==pI2Cx)
		{
			I2C2_PCLK_EN();
		}
		if(I2C3==pI2Cx)
		{
			I2C3_PCLK_EN();
		}
	}
	else
	{
		if(I2C1==pI2Cx)
		{
			I2C1_PCLK_DI();
		}
		if(I2C2==pI2Cx)
		{
			I2C2_PCLK_DI();
		}
		if(I2C3==pI2Cx)
		{
			I2C3_PCLK_DI();
		}
	}
}
//************************************SEND & RECIEVE DATA*****************************

void I2C_MasterSendData(I2C_Handle_t *pI2C_HDL,uint8_t SlaveAddr,uint8_t * pTxBuffer,uint32_t len)
{
	//Generation os start conditiom by setting SB=1 in CR1
	I2C_GenStartCond(pI2C_HDL->pI2Cx);
	//Poll till the SB in SR1 is not set to 1
	while(!I2C_GetFlagStatus_SR1(pI2C_HDL->pI2Cx, I2C_GET_SB_FLAG));								//Polling till we get this flag as set
	//Send of the slave addr on the bus
	I2C_ExecAddrSndPhase(pI2C_HDL->pI2Cx, SlaveAddr);
	//Reading of these flags clear ADDR flag
	I2C_AddrRead(pI2C_HDL->pI2Cx);

	//Transmission while len!=0
	while(len>0)
	{
		while(!I2C_GetFlagStatus_SR1(pI2C_HDL->pI2Cx, I2C_GET_TXE_FLAG));
		pI2C_HDL->pI2Cx->I2C_DR=*pTxBuffer;
		pTxBuffer++;
		len--;
	}
	//TxE=1 (Transfer buffer empty) & BTF=1 (Byte Transfer finished)
	while(!(I2C_GetFlagStatus_SR1(pI2C_HDL->pI2Cx, I2C_GET_TXE_FLAG)&& I2C_GetFlagStatus_SR1(pI2C_HDL->pI2Cx, I2C_GET_BTF_FLAG)));
	//Ending of the I2C communication
	I2C_GenEndCond(pI2C_HDL->pI2Cx);


}
//************************************Interrupts**************************************
void I2C_IRQConfig(uint8_t IRQ_Num,uint8_t IRQ_EN_DI)
{
	if(IRQ_EN_DI==ENABLE)
	{
		if(IRQ_Num<=31)
		{
			(* NVIC_ICER0_BADDR )|= (1<<IRQ_Num);return;
		}
		if(IRQ_Num>=32 && IRQ_Num <=63)
		{
			(* NVIC_ICER1_BADDR )|= (1<<(IRQ_Num%32));return;
		}
		if(IRQ_Num >=64 && IRQ_Num <=95)
		{
			(* NVIC_ICER2_BADDR )|= (1<<(IRQ_Num%32));return;
		}
	}
	else if (IRQ_EN_DI==DISABLE)
	{
		if(IRQ_Num<=31)
		{
			(* NVIC_ICER0_BADDR )&= ~(1<<IRQ_Num);return;
		}
		if(IRQ_Num>=32 && IRQ_Num <=63)
		{
			(* NVIC_ICER1_BADDR )&= ~(1<<(IRQ_Num%32));return;
		}
		if(IRQ_Num >=64 && IRQ_Num <=95)
		{
			(* NVIC_ICER2_BADDR )&= ~(1<<(IRQ_Num%32));return;
		}
	}
}
void I2C_IRQPriorityConfig(uint8_t IRQ_Num,uint8_t IRQ_Priority)
{

}
//************************************I2C Peri EN/DI**************************************
void I2C_Peripereal_ENORDI(I2C_RegDef_t *pI2C,uint8_t EN_DI);
//************************************I2C Event Handler callback**************************************
__weak void I2C_ApplicationEventCallBack(I2C_Handle_t *I2C_HNDL,uint8_t I2C_EVENT_OVR_ERR);
