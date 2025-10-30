/*
 * stm32f44xx_gpio_driver.c
 *
 *  Created on: Sep 26, 2025
 *      Author: tiberius
 */

#include "stm32f4xx_gpio_driver.h"

//-----------------Initialize & Deinitialize--------------------
/***************************************************************
 * @fn						-GPIO_Init
 *
 * @brief					-Initializing the GPIO peripheral ports
 *
 * @param[1]				-
 * @param[2]				-
 * @param[3]				-
 *
 * @return					-none
 *
 * @note					-noe
 *
 *
 * */
void GPIO_Init(GPIO_HANDLE_t *pGPIO_HNDL)
{
	uint32_t temp=0;
	GPIO_CLK_Ctrl(pGPIO_HNDL->pGPIO, ENABLE);
	if(pGPIO_HNDL->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANLG )
	{
		temp = (pGPIO_HNDL->GPIO_PinConfig.GPIO_PinMode <<(2*pGPIO_HNDL->GPIO_PinConfig.GPIO_PinNum));
		pGPIO_HNDL->pGPIO->MODER &= ~(0x3 << 2*pGPIO_HNDL->GPIO_PinConfig.GPIO_PinNum ); 						// Clearing of bits
		pGPIO_HNDL->pGPIO->MODER |= temp;																		// Setting of bits
	}
	else
	{
		//-----------------Code for interrupt modes-----------------------------
		if(pGPIO_HNDL->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_FT)
		{
			//Falling trigger
			EXTI_REG->EXTI_FTSR |=(1<<pGPIO_HNDL->GPIO_PinConfig.GPIO_PinNum);
			//Clearing of RTSR BIT
			EXTI_REG->EXTI_RTSR &= ~(1<<pGPIO_HNDL->GPIO_PinConfig.GPIO_PinNum);
		}
		if(pGPIO_HNDL->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_RT)
		{
			//Rising trigger
			EXTI_REG->EXTI_RTSR |= (1<<pGPIO_HNDL->GPIO_PinConfig.GPIO_PinNum);
			//Clearing of FTSR
			EXTI_REG->EXTI_FTSR &= ~(1<<pGPIO_HNDL->GPIO_PinConfig.GPIO_PinNum);
		}
		if(pGPIO_HNDL->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_RFT)
		{
			//Rising Falling trigger
			//FTSR Set
			EXTI_REG->EXTI_FTSR |= (1<<pGPIO_HNDL->GPIO_PinConfig.GPIO_PinNum);
			//RTSR Set
			EXTI_REG->EXTI_RTSR |= (1<<pGPIO_HNDL->GPIO_PinConfig.GPIO_PinNum);
		}

		//SYSCFG reg setting
		uint8_t EXTI_Arr_Num =pGPIO_HNDL->GPIO_PinConfig.GPIO_PinNum/4;
		uint8_t POS_NUM =pGPIO_HNDL->GPIO_PinConfig.GPIO_PinMode %4;
		uint8_t PORT_DECIMAL =GPIOx_PORT_TO_NUM(pGPIO_HNDL->pGPIO);
		SYSCFG_PCLK_EN();
		SYSCFG_REG->SYSCFG_EXTICR[EXTI_Arr_Num]=PORT_DECIMAL<<(4*POS_NUM);

		//IMR Reg set
		//@note -Settting value to one for pin will not mask interrupt for the corresponding bit
		EXTI_REG->EXTI_IMR |= 1<<pGPIO_HNDL->GPIO_PinConfig.GPIO_PinNum;
	}

	temp=temp ^ temp;
	temp=pGPIO_HNDL->GPIO_PinConfig.GPIO_PinSpeed<<(2* pGPIO_HNDL->GPIO_PinConfig.GPIO_PinNum);
	pGPIO_HNDL->pGPIO->OSPEEDR &= ~(0x3<<2*pGPIO_HNDL->GPIO_PinConfig.GPIO_PinNum);
	pGPIO_HNDL->pGPIO->OSPEEDR |= temp;
	temp=temp ^ temp;
	temp=pGPIO_HNDL->GPIO_PinConfig.GPIO_PinPuPdCtrl<<(2*pGPIO_HNDL->GPIO_PinConfig.GPIO_PinNum);
	pGPIO_HNDL->pGPIO->PUPDR &=~(0x3<<2*pGPIO_HNDL->GPIO_PinConfig.GPIO_PinNum);
	pGPIO_HNDL->pGPIO->PUPDR |= temp;
	temp=temp ^ temp;
	temp=pGPIO_HNDL->GPIO_PinConfig.GPIO_PinOType<<pGPIO_HNDL->GPIO_PinConfig.GPIO_PinNum;
	pGPIO_HNDL->pGPIO->OTYPER &=~(0x1<<pGPIO_HNDL->GPIO_PinConfig.GPIO_PinNum);
	pGPIO_HNDL->pGPIO->OTYPER |= temp;
	temp=temp ^ temp;
	if(pGPIO_HNDL->GPIO_PinConfig.GPIO_PinMode== GPIO_MODE_ALT)
	{

		uint8_t arr_pos=pGPIO_HNDL->GPIO_PinConfig.GPIO_PinNum/8;
		uint8_t bit_pos=pGPIO_HNDL->GPIO_PinConfig.GPIO_PinNum % 8;
		pGPIO_HNDL->pGPIO->AFR[arr_pos] &= ~(0xF<<(4*bit_pos));
		pGPIO_HNDL->pGPIO->AFR[arr_pos] |= pGPIO_HNDL->GPIO_PinConfig.GPIO_PinAltFunc<<(4*bit_pos);
	}
	//@note -XORED temp to set it to zero, better to keep it that way. Maybe used in future.
	temp=temp ^ temp;
}
/***************************************************************
 * @fn						-
 *
 * @brief					-
 *
 * @param[1]				-
 * @param[2]				-
 * @param[3]				-
 *
 * @return					-
 *
 * @note					-
 *
 *
 * */
void GPIO_Deinit(GPIO_REG_DEF* pGPIO)
{
			if(pGPIO == GPIOA)
			{
				GPIOA_RSTR();
			}
			if(pGPIO == GPIOB)
			{
				GPIOB_RSTR();
			}
			if(pGPIO == GPIOC)
			{
						GPIOC_RSTR();
			}
			if(pGPIO == GPIOD)
			{
						GPIOD_RSTR();
			}
			if(pGPIO == GPIOE)
					{
						GPIOE_RSTR();
					}
			if(pGPIO == GPIOF)
					{
						GPIOF_RSTR();
					}
			if(pGPIO == GPIOG)
					{
						GPIOG_RSTR();
					}
			if(pGPIO == GPIOH)
					{
						GPIOH_RSTR();
					}
			if(pGPIO == GPIOI)
					{
						GPIOI_RSTR();
					}
}

//------------------------------------Clock (Enable & Disable)------------------------
/***************************************************************
 * @fn						-GPIO_CLK_Ctrl
 *
 * @brief					-To Enable or Disable the peripheral GPIOx Clock
 *
 * @param[1]				-Base Address of the GPIOx Port
 * @param[2]				-ENABLE or DISABLE macro
 * @param[3]				-none
 *
 * @return					-none
 *
 * @note					-The ENABLE & DISABLE macros are defined in the stm32f407d.h file
 *
 *
 * */
void GPIO_CLK_Ctrl(GPIO_REG_DEF* pGPIO,uint8_t EN_DI)
{
	if(EN_DI==ENABLE)
	{
		if(pGPIO == GPIOA)
		{
			GPIOA_PCLK_EN();
			return;
		}
		if(pGPIO == GPIOB)
		{
			GPIOB_PCLK_EN();
			return;
		}
		if(pGPIO == GPIOC)
				{
					GPIOC_PCLK_EN();return;
				}
		if(pGPIO == GPIOD)
				{
					GPIOD_PCLK_EN();return;
				}
		if(pGPIO == GPIOE)
				{
					GPIOE_PCLK_EN();return;
				}
		if(pGPIO == GPIOF)
				{
					GPIOF_PCLK_EN();return;
				}
		if(pGPIO == GPIOG)
				{
					GPIOG_PCLK_EN();return;
				}
		if(pGPIO == GPIOH)
				{
					GPIOH_PCLK_EN();return;
				}
		if(pGPIO == GPIOI)
				{
					GPIOI_PCLK_EN();return;
				}
		if(pGPIO == GPIOJ)
				{
					GPIOJ_PCLK_EN();return;
				}
		if(pGPIO == GPIOK)
				{
					GPIOK_PCLK_EN();return;
				}
	}
	else
	{
		if(pGPIO == GPIOA)
				{
					GPIOA_PCLK_DI();return;
				}
				if(pGPIO == GPIOB)
				{
					GPIOB_PCLK_DI();return;
				}
				if(pGPIO == GPIOC)
						{
							GPIOC_PCLK_DI();return;
						}
				if(pGPIO == GPIOD)
						{
							GPIOD_PCLK_DI();return;
						}
				if(pGPIO == GPIOE)
						{
							GPIOE_PCLK_DI();return;
						}
				if(pGPIO == GPIOF)
						{
							GPIOF_PCLK_DI();return;
						}
				if(pGPIO == GPIOG)
						{
							GPIOG_PCLK_DI();return;
						}
				if(pGPIO == GPIOH)
						{
							GPIOH_PCLK_DI();return;
						}
				if(pGPIO == GPIOI)
						{
							GPIOI_PCLK_DI();return;
						}
				if(pGPIO == GPIOJ)
						{
							GPIOJ_PCLK_DI();return;
						}
				if(pGPIO == GPIOK)
						{
							GPIOK_PCLK_DI();return;
						}
	}
}

//------------------------------------Read (Pin & Port)-------------------------------
/***************************************************************
 * @fn						-GPIO_ReadFromInputPin
 *
 * @brief					-Read from the specified GPIOx input pin of the port
 *
 * @param[1]				-Base address of the GPIOx Port
 * @param[2]				-Pin number to be read from
 * @param[3]				-
 *
 * @return					-8bit integer
 *
 * @note					-none
 *
 *
 * */
uint8_t GPIO_ReadFromInputPin(GPIO_REG_DEF *pGPIO,uint8_t PinNum)
{
	uint8_t value;
	value = (uint8_t)((pGPIO->IDR >> PinNum) & (0x00000001));
	return value;
}
/***************************************************************
 * @fn						-GPIO_ReadFromInputPort
 *
 * @brief					-Read from the specified GPIOx input port
 *
 * @param[1]				-BASE address of the GPIOx
 * @param[2]				-
 * @param[3]				-
 *
 * @return					-16 bit integer
 *
 * @note					-none
 *
 *
 * */
uint16_t GPIO_ReadFromInputPort(GPIO_REG_DEF *pGPIO)
{
	return (uint16_t)pGPIO->IDR;
}
//------------------------------------Write (Pin & Port-------------------------------
/***************************************************************
 * @fn						-GPIO_WriteToOutputPin
 *
 * @brief					-Write to the specified output GPIOx pin of the port
 *
 * @param[1]				-BASE address of the GPIOx port
 * @param[2]				-Pin number to be written
 * @param[3]				-Value to be written
 *
 * @return					-none
 *
 * @note					-none
 *
 *
 * */
void GPIO_WriteToOutputPin(GPIO_REG_DEF* pGPIO,uint8_t PinNum,uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		pGPIO->ODR |=(1 <<PinNum);
	}
	else
	{
		pGPIO->ODR &=~(1<<PinNum);
	}
}
/***************************************************************
 * @fn						-GPIO_WritetoOutputPort
 *
 * @brief					-Write to the specified output GPIOx port
 *
 * @param[1]				-BASE address of the GPIOx port
 * @param[2]				-Value to be written at Port
 * @param[3]				-
 *
 * @return					-
 *
 * @note					-
 *
 *
 * */
void GPIO_WritetoOutputPort(GPIO_REG_DEF* pGPIO,uint16_t Value)
{
	pGPIO->ODR = Value;
}
/**************************************************************
 * @fn						-GPIO_WritetoOutputPort
 *
 * @brief					-A function which toggle the specified pin
 *
 * @param[1]				-BASE address of the GPIOx port
 * @param[2]				-Pin number to be toggle
 * @param[3]				-
 *
 * @return					-none
 *
 * @note					-none
 *
 *
 * */
void GPIO_Toggle_OPin(GPIO_REG_DEF* pGPIO,uint8_t PinNum)
{
	pGPIO->ODR ^=(1<<PinNum);
}
//------------------------------------Interrupts--------------------------------------
/**************************************************************
 * @fn						-GPIO_IRQ_INT_Config
 *
 * @brief					-Enable or Disable the relative IRQ
 *
 * @param[1]				-Interrupt service routine number
 * @param[2]				-ENABLE or DISABLE macros
 * @param[3]				-
 *
 * @return					-none
 *
 * @note					-none
 *
 *
 * */
void GPIO_IRQ_INT_Config(uint8_t IRQ_Num,uint8_t IRQ_EN_DI)
{
	if(IRQ_EN_DI==ENABLE)
	{
		if(IRQ_Num <=31)											//IRQ 0 to 31
		{
			*NVIC_ISER0_BADDR |= (1<<IRQ_Num);
		}
		if(IRQ_Num >31 && IRQ_Num <=63)								//IRQ 32 to 63
		{
			*NVIC_ISER1_BADDR |= (1<<(IRQ_Num % 32));
		}
		if(IRQ_Num >63 && IRQ_Num <=95)								//IRQ 64 to 95
		{
			*NVIC_ISER2_BADDR |= (1<<(IRQ_Num % 32));
		}
	}
	else
	{
		if(IRQ_Num <=31)											//IRQ 0 to 31
				{
					*NVIC_ICER0_BADDR &= ~(1<<IRQ_Num);
				}
				if(IRQ_Num >31 && IRQ_Num <=63)								//IRQ 32 to 63
				{
					*NVIC_ICER1_BADDR &= ~(1<<(IRQ_Num % 32));
				}
				if(IRQ_Num >63 && IRQ_Num <=95)								//IRQ 64 to 95
				{
					*NVIC_ICER2_BADDR &= ~(1<<(IRQ_Num % 32));
				}
	}
}
/**************************************************************
 * @fn						-GPIO_IRQ_Priority_Config
 *
 * @brief					-To configure the Priority of Interrupt serviec routines of the MCU
 *
 * @param[1]				-Interrupt service routine number
 * @param[2]				-Interrupt Priority
 * @param[3]				-
 *
 * @return					-none
 *
 * @note					-none
 *
 *
 * */
void GPIO_IRQ_Priority_Config(uint8_t IRQ_Num,uint8_t IRQ_Priority)
{
	uint8_t ipr_section=IRQ_Num/4;
	uint8_t ipr_offset=IRQ_Num%4;
	uint8_t lft_shf_value = (ipr_offset*8)+(8-RESRVED_PBITS);
	*(NVIC_IPR_BADDR + (ipr_section *4 )) |=(IRQ_Priority<<lft_shf_value);
}
/**************************************************************
 * @fn						-GPIO_InterruptHandling
 *
 * @brief					-The interrupt to be handled at specified pin number of the GPIOx port
 *
 * @param[1]				-Pin number of the GPIOx
 * @param[2]				-
 * @param[3]				-
 *
 * @return					-none
 *
 * @note					-none
 *
 *
 * */
void GPIO_InterruptHandling(uint8_t PinNum)
{
	//If
	if(EXTI_REG->EXTI_PR & (1<<PinNum))
	{
		//Clear The pending BIT reg
		EXTI_REG->EXTI_PR |= (1<<PinNum);
	}
}
