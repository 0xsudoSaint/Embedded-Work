/*
 * stm32f4XX_I2C_driver.h
 *
 *  Created on: Oct 18, 2025
 *      Author: tiberius
 */

#ifndef INC_STM32F4XX_I2C_DRIVER_H_
#define INC_STM32F4XX_I2C_DRIVER_H_
#include "stm32f407d.h"

typedef struct{
	uint32_t 		I2C_SCLSpeed;									//ref - @I2C_SCLSPeed
	uint16_t 		I2C_DeviceAddress;								//Only need when the device in slave mode, given by user
	uint8_t 		I2C_ACKControl;									//ref - @I2C_ACK_CTRL
	uint16_t 		I2C_FMDutyCycle;								//ref - @I2C_FMDutyCyc
	uint8_t			I2C_10BitADDEN;
}I2C_Config_t;

typedef struct
{
	__vo uint32_t		I2C_CR1;
	__vo uint32_t		I2C_CR2;
	__vo uint32_t		I2C_OAR1;
	__vo uint32_t		I2C_OAR2;
	__vo uint32_t		I2C_DR;
	__vo uint32_t		I2C_SR1;
	__vo uint32_t		I2C_SR2;
	__vo uint32_t		I2C_CCR;
	__vo uint32_t		I2C_TRISE;
	__vo uint32_t		I2C_FLTR;
}I2C_RegDef_t;
//--------I2Cx Registers (casted to Reg Struct)---------
#define I2C1		((I2C_RegDef_t*)I2C1_BADDR)
#define I2C2		((I2C_RegDef_t*)I2C2_BADDR)
#define I2C3		((I2C_RegDef_t*)I2C3_BADDR)

typedef struct
{
	I2C_Config_t	I2C_Config;
	I2C_RegDef_t*	pI2Cx;
}I2C_Handle_t;


/*------------------------------------Functions Prototypes---------------------------
-------------------------------------------------------------------------------------*/
//------------------------------------Initialize & Deinitialize-----------------------
void I2C_Init(I2C_Handle_t *pI2C_HNDL);
void I2C_Deinit(I2C_RegDef_t* pI2C);
//------------------------------------Clock (Enable & Disable)------------------------
void I2C_EnableClock(I2C_RegDef_t* pI2C,uint8_t EN_DI);
//------------------------------------SEND & RECIEVE DATA-----------------------------
void I2C_MasterSendData(I2C_Handle_t *pI2C_HDL,uint8_t slaveADDR,uint8_t * pTxBuffer,uint32_t len);
//------------------------------------Interrupts--------------------------------------
void I2C_IRQConfig(uint8_t IRQ_Num,uint8_t IRQ_EN_DI);
void I2C_IRQPriorityConfig(uint8_t IRQ_Num,uint8_t IRQ_Priority);
//------------------------------------I2C Peri EN/DI--------------------------------------
void I2C_Peripereal_ENORDI(I2C_RegDef_t *pI2C,uint8_t EN_DI);
//------------------------------------I2C Event Handler callback--------------------------------------
__weak void I2C_ApplicationEventCallBack(I2C_Handle_t *I2C_HNDL,uint8_t I2C_EVENT_OVR_ERR);
//*********************I2C Macros******************************
/*
 * @I2C_SCLSPeed
 * */
#define I2C_SCL_SPEED_SM				100000
#define I2C_SCL_SPEED_FM_4kHz			400000
#define I2C_SCL_SPEED_FM_16kHz			1600000
/*
 * @I2C_ACK_CTRL
 * */
#define I2C_ACK_CTRL_DI					0
#define I2C_ACK_CTRL_EN					1

/*
 * @I2C_FMDutyCyc
 * */
#define I2C_FM_Duty_Cycle_2				0
#define I2C_FM_Duty_Cycle_16_9			1


/*
 * @I2C_GetFlags
 * */
#define I2C_GET_TXE_FLAG				(1<<I2C_SR1_TxE)
#define I2C_GET_RENE_FLAG				(1<<I2C_SR1_RxNE)
#define I2C_GET_SB_FLAG					(1<<I2C_SR1_SB)
#define I2C_GET_BTF_FLAG				(1<<I2C_SR1_BTF)
#endif /* INC_STM32F4XX_I2C_DRIVER_H_ */
