/*
 * stm32f407d.h
 *
 *  Created on: Sep 25, 2025
 *      Author: tiberius
 */

#ifndef INC_STM32F407D_H_
#define INC_STM32F407D_H_

#include <stddef.h>
#include <stdint.h>
#define __vo volatile
#define __weak __attribute__((weak))
#define __NA	NULL
//***********************************************************************************************************************
//***********************************************START:ARM Process Specific Details**************************************
//***********************************************************************************************************************
/*This region has the specification defined particularly for the ARM Cortex M4 processor
 *
 * */
//***********************NVIC Set*Enable Registers*************************
#define NVIC_ISER0_BADDR					((__vo uint32_t*)(0xE000E100U))			//@Reg is 32bit or 4 byte
#define NVIC_ISER1_BADDR					((__vo uint32_t*)(0xE000E104U))
#define NVIC_ISER2_BADDR					((__vo uint32_t*)(0xE000E108U))
#define NVIC_ISER3_BADDR					((__vo uint32_t*)(0xE000E10CU))
//***********************NVIC Clear*Enable Registers***********************
#define NVIC_ICER0_BADDR					((__vo uint32_t*)(0xE000E180U))			//@Reg is 32bit or 4 byte
#define NVIC_ICER1_BADDR					((__vo uint32_t*)(0xE000E184U))
#define NVIC_ICER2_BADDR					((__vo uint32_t*)(0xE000E188U))
#define NVIC_ICER3_BADDR					((__vo uint32_t*)(0xE000E18CU))
//**********************IRQ Priority Register******************************
#define NVIC_IPR_BADDR						((__vo uint32_t*)(0xE000E400))

//***********************************************************************************************************************
//***********************************************START:MCU Specific Details**********************************************
//***********************************************************************************************************************
/*This region has the specification defined particularly for the STMf40x MCU Family
 *
 * */
#define FLASH_MEM_B_ADDR					0x08000000U							//Flash ROM add

#define ROM_BADDR							0x1FFF0000U							//System Memory BASE address

#define OTP_BADDR							0x1FFF7800U

//******************SRAM*******************************
#define SRAM1_BADDR							0x20000000U
#define SRAM2_BADDR							0x2001C000U
#define SRAM3_BADDR							0x20020000U
#define SRAM								SRAM1_BADDR

//*****************Peripheral**************************
#define PHERI_BADDR							0x40000000U
#define APB1_BADDR							PHERI_BADDR
#define APB2_BADDR							0x40010000U
#define AHB1_BADDR							0x40020000U
#define AHB2_BADDR							0x50000000U
#define AHB3_BADDR							0xA0000000U


//****************AHB1_Peripherals_ADDR**************************
#define RCC_BADDR							(AHB1_BADDR + 0x3800)
//****************GPIOX_ADDR*************************************
#define GPIOA_BADDR							(AHB1_BADDR + 0x0000)
#define GPIOB_BADDR							(AHB1_BADDR + 0x0400)
#define GPIOC_BADDR							(AHB1_BADDR + 0x0800)
#define GPIOD_BADDR							(AHB1_BADDR + 0x0C00)
#define GPIOE_BADDR							(AHB1_BADDR + 0x1000)
#define GPIOF_BADDR							(AHB1_BADDR + 0x1400)
#define GPIOG_BADDR							(AHB1_BADDR + 0x1800)
#define GPIOH_BADDR							(AHB1_BADDR + 0x1C00)
#define GPIOI_BADDR							(AHB1_BADDR + 0x2000)
#define GPIOJ_BADDR							(AHB1_BADDR + 0x2400)
#define GPIOK_BADDR							(AHB1_BADDR + 0x2800)



//****************GPIO_Defined Type********************************************************
typedef struct{
	__vo uint32_t MODER;					//Port mode register(Input,Gen purp,Alt,Analog)
	__vo uint32_t OTYPER;					//Output Type Register
	__vo uint32_t OSPEEDR;					//Output Speed REgister
	__vo uint32_t PUPDR;					//Push up Pull down
	__vo uint32_t IDR;						//Input Data register
	__vo uint32_t ODR;						//Output Data register
	__vo uint16_t BSRRL;					//Bit set/reset register (Lower)
	__vo uint16_t BSRRH;					//Bit set/reset register (Higher)
	__vo uint32_t LCKR;						//Port Config Lock register
	__vo uint32_t AFR[2];					//Alternate Functionality [0] => Lower reg , Alternate Functionality [1] => Higher reg
}GPIO_REG_DEF;

//****************GPIOX (casted to typedef of GPIO)*********************
#define GPIOA								((GPIO_REG_DEF*)GPIOA_BADDR)
#define GPIOB								((GPIO_REG_DEF*)GPIOB_BADDR)
#define GPIOC								((GPIO_REG_DEF*)GPIOC_BADDR)
#define GPIOD								((GPIO_REG_DEF*)GPIOD_BADDR)
#define GPIOE								((GPIO_REG_DEF*)GPIOE_BADDR)
#define GPIOF								((GPIO_REG_DEF*)GPIOF_BADDR)
#define GPIOG								((GPIO_REG_DEF*)GPIOG_BADDR)
#define GPIOH								((GPIO_REG_DEF*)GPIOH_BADDR)
#define GPIOI								((GPIO_REG_DEF*)GPIOI_BADDR)
#define GPIOJ								((GPIO_REG_DEF*)GPIOJ_BADDR)
#define GPIOK								((GPIO_REG_DEF*)GPIOK_BADDR)

//****************GPIOX (casted pointer to typedef of GPIO)*************


//****************RCC Defined Struct************************************
typedef struct{
	__vo uint32_t RCC_CR;						//Clock Control Register
	__vo uint32_t RCC_PLLCFGR;					//PLL configure Register
	__vo uint32_t RCC_CFGR;						//Clock Configure Register
	__vo uint32_t RCC_CIR;						//Clock Interrupt Register
	__vo uint32_t RCC_AHB1RSTR;					//AHB1 Peripheral reset Register
	__vo uint32_t RCC_AHB2RSTR;					//AHB2 Peripheral reset Register
	__vo uint32_t RCC_AHB3RSTR;					//AHB3 Peripheral reset Register
	uint32_t	  RESERVED0;
	__vo uint32_t RCC_APB1RSTR;					//APB1 Peripheral reset Register
	__vo uint32_t RCC_APB2RSTR;					//APB2 Peripheral reset Register
	uint32_t	  RESERVED1[2];
	__vo uint32_t RCC_AHB1ENR;					//AHB1 Peripheral clock EN register
	__vo uint32_t RCC_AHB2ENR;					//AHB2 Peripheral clock EN register
	__vo uint32_t RCC_AHB3ENR;					//AHB3 Peripheral clock EN register
	uint32_t	  RESERVED3;
	__vo uint32_t RCC_APB1ENR;					//APB1 Peripheral clock EN register
	__vo uint32_t RCC_APB2ENR;					//APB2 Peripheral clock EN register
	uint32_t	  RESERVED4[2];
	__vo uint32_t RCC_AHB1LPENR;				//AHB1 Peripheral clock  EN reg (Low power)
	__vo uint32_t RCC_AHB2LPENR;				//AHB2 Peripheral clock  EN reg (Low power)
	__vo uint32_t RCC_AHB3LPENR;				//AHB3 Peripheral clock  EN reg (Low power)
	uint32_t	  RESERVED5;
	__vo uint32_t RCC_APB1LPENR;				//APB1 Peripheral clock  EN reg (Low power)
	__vo uint32_t RCC_APB2LPENR;				//APB2 Peripheral clock  EN reg (Low power)
	uint32_t	  RESERVED6[2];
	__vo uint32_t RCC_BDCR;						//Backup domain control reg
	__vo uint32_t RCC_CSR;						//Clock Control & status reg
	uint32_t	  RESERVED7[2];
	__vo uint32_t RCC_SSCGR;					//Spread spectrum clock generationreg
	__vo uint32_t RCC_PLLI2SCFGR;				//PLLI2S config reg
	__vo uint32_t RCC_PLLSAICFGR;				//PLL config reg
	__vo uint32_t RCC_DCKCFGR;					//Dedicated Clock config reg
}RCC_REG_Def;

//****************RCC  (castedto typedef of RCC)***********************
#define RCC_REG							((RCC_REG_Def*)RCC_BADDR)

//****************APB1_Peripherals_ADDR**************************
//****************I2C Peripherals********************************
#define I2C1_BADDR							(APB1_BADDR + 0x5400)
#define I2C2_BADDR							(APB1_BADDR + 0x5800)
#define I2C3_BADDR							(APB1_BADDR + 0x5C00)

//****************SPI Peripherals********************************
#define SPI2_BADDR							(APB1_BADDR + 0x3800)
#define SPI3_BADDR							(APB1_BADDR + 0x3C00)

//****************USART Peripherals******************************
#define USART2_BADDR						(APB1_BADDR + 0x4400)
#define USART3_BADDR						(APB1_BADDR + 0x4800)

//****************UART Peripherals*******************************
#define UART4_BADDR							(APB1_BADDR + 0x4C00)
#define UART5_BADDR							(APB1_BADDR + 0x5000)


//****************APB2_Peripherals_ADDR*************************
//****************SPI Peripherals*******************************
#define SPI1_BADDR							(APB2_BADDR + 0x3000)
#define SPI4_BADDR							(APB2_BADDR + 0x3400)
#define SPI5_BADDR							(APB2_BADDR + 0x5000)
#define SPI6_BADDR							(APB2_BADDR + 0x5400)

//****************USART Peripherals******************************
#define USART1_BADDR						(APB2_BADDR + 0x1000)
#define USART6_BADDR						(APB2_BADDR + 0x1400)
//****************EXTI*******************************************
#define EXTI_BADDR							(APB2_BADDR + 0x3C00)
//****************SYSCNFG Peripherals****************************
#define SYSCFG_BADDR						(APB2_BADDR + 0x3800)

//****************EXTI Reg Strucut Definition__************************
typedef struct
{
	__vo uint32_t EXTI_IMR;
	__vo uint32_t EXTI_EMR;
	__vo uint32_t EXTI_RTSR;
	__vo uint32_t EXTI_FTSR;
	__vo uint32_t EXTI_SWIER;
	__vo uint32_t EXTI_PR;
}EXTI_RegDef_t;
//****************EXTI Reg (Pointer) Marcro****************************
#define EXTI_REG						((EXTI_RegDef_t*) EXTI_BADDR)
//****************SYSCFG Struct Definition*****************************
typedef struct
{
	__vo uint32_t SYSCFG_MEMRMP;										//ADDR OFFSET: 0x00
	__vo uint32_t SYSCFG_PMC;											//ADDR OFFSET: 0x04
	__vo uint32_t SYSCFG_EXTICR[4];										//ADDR OFFSET: 0x08 * 0x18 (ICLUSIVE: +4 bytes of last reg)
	uint32_t SYSCFG_RESERVED[2];										//ADDR OFFSET: 0x18 * 0x20 (ICLUSIVE: +4)
	__vo uint32_t SYSCFG_CMPCR;											//ADDR OFFSET: 0x20
}SYSCFG_RegDef_t;
//****************SYSCFG Reg (Pointer) Marcro***************************
#define SYSCFG_REG						((SYSCFG_RegDef_t *)SYSCFG_BADDR)
//**************** PORT to Number***************************************
#define GPIOx_PORT_TO_NUM(x)			((x==GPIOA)?0:\
										(x==GPIOB)?1:\
										(x==GPIOC)?2:\
										(x==GPIOD)?3:\
										(x==GPIOE)?4:\
										(x==GPIOF)?5:\
										(x==GPIOG)?6:\
										(x==GPIOH)?7:\
										(x==GPIOI)?8:0);

//****************Peripherals Clock Disable & Enable**************************
//****************************************************************************
//****************Peripherals Clock Enable************************************
//****************GPIOX Peripheral Clocks*************************************
#define GPIOA_PCLK_EN()						(RCC_REG->RCC_AHB1ENR |= (1<<0))				//Port A Clock Enable
#define GPIOB_PCLK_EN()						(RCC_REG->RCC_AHB1ENR |= (1<<1))				//Port // Clock Enable
#define GPIOC_PCLK_EN()						(RCC_REG->RCC_AHB1ENR |= (1<<2))				//Port // Clock Enable
#define GPIOD_PCLK_EN()						(RCC_REG->RCC_AHB1ENR |= (1<<3))				//Port // Clock Enable
#define GPIOE_PCLK_EN()						(RCC_REG->RCC_AHB1ENR |= (1<<4))				//Port // Clock Enable
#define GPIOF_PCLK_EN()						(RCC_REG->RCC_AHB1ENR |= (1<<5))				//Port // Clock Enable
#define GPIOG_PCLK_EN()						(RCC_REG->RCC_AHB1ENR |= (1<<6))				//Port // Clock Enable
#define GPIOH_PCLK_EN()						(RCC_REG->RCC_AHB1ENR |= (1<<7))				//Port // Clock Enable
#define GPIOI_PCLK_EN()						(RCC_REG->RCC_AHB1ENR |= (1<<8))				//Port // Clock Enable
#define GPIOJ_PCLK_EN()						(RCC_REG->RCC_AHB1ENR |= (1<<9))				//Port // Clock Enable
#define GPIOK_PCLK_EN()						(RCC_REG->RCC_AHB1ENR |= (1<<10))				//Port // Clock Enable
//****************I2C Peripheral Clocks*****************************************
#define I2C1_PCLK_EN()						(RCC_REG->RCC_APB1ENR |= (1<<21))
#define I2C2_PCLK_EN()						(RCC_REG->RCC_APB1ENR |= (1<<22))
#define I2C3_PCLK_EN()						(RCC_REG->RCC_APB1ENR |= (1<<23))
//****************SPI Peripheral Clocks*****************************************
//****************APB2 SPIs*****************************************************
#define SPI1_PCLK_EN()						(RCC_REG->RCC_APB2ENR |= (1<<12))
#define SPI4_PCLK_EN()						(RCC_REG->RCC_APB2ENR |= (1<<13))
#define SPI5_PCLK_EN()						(RCC_REG->RCC_APB2ENR |= (1<<20))
#define SPI6_PCLK_EN()						(RCC_REG->RCC_APB2ENR |= (1<<21))
//****************APB1 SPIs*****************************************************
#define SPI2_PCLK_EN()						(RCC_REG->RCC_APB1ENR |= (1<<14))
#define SPI3_PCLK_EN()						(RCC_REG->RCC_APB1ENR |= (1<<15))
//****************USART Peripheral Clocks*****************************************
//****************USART (APB1)****************************************************
#define USART2_PCLK_EN()					(RCC_REG->RCC_APB1ENR |= (1<<17))
#define USART3_PCLK_EN()					(RCC_REG->RCC_APB1ENR |= (1<<18))
//****************USART (APB2)****************************************************
#define USART1_PCLK_EN()					(RCC_REG->RCC_APB1ENR |= (1<<4))
#define USART6_PCLK_EN()					(RCC_REG->RCC_APB1ENR |= (1<<5))
//****************SYSCFG Peripheral Clocks*****************************************
#define SYSCFG_PCLK_EN()					(RCC_REG->RCC_APB2ENR |=(1<<14))
//****************UART Peripheral Clocks*****************************************
//****************UART (APB1)****************************************************
#define UART4_PCLK_EN()					(RCC_REG->RCC_APB1ENR |= (1<<19))
#define UART5_PCLK_EN()					(RCC_REG->RCC_APB1ENR |= (1<<20))
#define UART7_PCLK_EN()					(RCC_REG->RCC_APB1ENR |= (1<<30))
#define UART8_PCLK_EN()					(RCC_REG->RCC_APB1ENR |= (1<<31))

//****************Peripherals Clock Disable************************************
//****************GPIOX Peripheral Clocks*************************************
#define GPIOA_PCLK_DI()						(RCC_REG->RCC_AHB1ENR &= ~(1<<0))				//Port A Clock Disable
#define GPIOB_PCLK_DI()						(RCC_REG->RCC_AHB1ENR &= ~(1<<1))				//Port // Clock Disable
#define GPIOC_PCLK_DI()						(RCC_REG->RCC_AHB1ENR &= ~(1<<2))				//Port // Clock Disable
#define GPIOD_PCLK_DI()						(RCC_REG->RCC_AHB1ENR &= ~(1<<3))				//Port // Clock Disable
#define GPIOE_PCLK_DI()						(RCC_REG->RCC_AHB1ENR &= ~(1<<4))				//Port // Clock Disable
#define GPIOF_PCLK_DI()						(RCC_REG->RCC_AHB1ENR &= ~(1<<5))				//Port // Clock Disable
#define GPIOG_PCLK_DI()						(RCC_REG->RCC_AHB1ENR &= ~(1<<6))				//Port // Clock Disable
#define GPIOH_PCLK_DI()						(RCC_REG->RCC_AHB1ENR &= ~(1<<7))				//Port // Clock Disable
#define GPIOI_PCLK_DI()						(RCC_REG->RCC_AHB1ENR &= ~(1<<8))				//Port // Clock Disable
#define GPIOJ_PCLK_DI()						(RCC_REG->RCC_AHB1ENR &= ~(1<<9))				//Port // Clock Disable
#define GPIOK_PCLK_DI()						(RCC_REG->RCC_AHB1ENR &= ~(1<<10))				//Port // Clock Disable
//****************I2C Peripheral Clocks*****************************************
#define I2C1_PCLK_DI()						(RCC_REG->RCC_APB1ENR &= ~(1<<21))
#define I2C2_PCLK_DI()						(RCC_REG->RCC_APB1ENR &= ~(1<<22))
#define I2C3_PCLK_DI()						(RCC_REG->RCC_APB1ENR &= ~(1<<23))
//****************SPI Peripheral Clocks*****************************************
//****************APB2 SPIs*****************************************************
#define SPI1_PCLK_DI()						(RCC_REG->RCC_APB2ENR &= ~(1<<12))
#define SPI4_PCLK_DI()						(RCC_REG->RCC_APB2ENR &= ~(1<<13))
#define SPI5_PCLK_DI()						(RCC_REG->RCC_APB2ENR &= ~(1<<20))
#define SPI6_PCLK_DI()						(RCC_REG->RCC_APB2ENR &= ~(1<<21))
//****************APB1 SPIs*****************************************************
#define SPI2_PCLK_DI()						(RCC_REG->RCC_APB2ENR &= ~(1<<14))
#define SPI3_PCLK_DI()						(RCC_REG->RCC_APB2ENR &= ~(1<<15))
//****************USART Peripheral Clocks*****************************************
//****************USART (APB1)****************************************************
#define USART2_PCLK_DI()					(RCC_REG->RCC_APB1ENR &= ~(1<<17))
#define USART3_PCLK_DI()					(RCC_REG->RCC_APB1ENR &= ~(1<<18))
//****************USART (APB2)****************************************************
#define USART1_PCLK_DI()					(RCC_REG->RCC_APB1ENR &= ~(1<<4))
#define USART6_PCLK_DI()					(RCC_REG->RCC_APB1ENR &= ~(1<<5))
//****************SYSCFG Peripheral Clocks*****************************************
#define SYSCFG_PCLK_DI()					(RCC_REG->RCC_APB2ENR &= ~(1<<14))
//****************UART Peripheral Clocks*****************************************
//****************UART (APB1)****************************************************
#define UART4_PCLK_DI()					(RCC_REG->RCC_APB1ENR &= ~(1<<19))
#define UART5_PCLK_DI()					(RCC_REG->RCC_APB1ENR &= ~(1<<20))
#define UART7_PCLK_DI()					(RCC_REG->RCC_APB1ENR &= ~(1<<30))
#define UART8_PCLK_DI()					(RCC_REG->RCC_APB1ENR &= ~(1<<31))

//****************GPIOx Reset Registers__****************************************
#define GPIOA_RSTR()					do{(RCC_REG->RCC_AHB1RSTR |= (1<<0)); (RCC_REG->RCC_AHB1RSTR &= ~(1<<0)); }while(0)
#define GPIOB_RSTR()					do{(RCC_REG->RCC_AHB1RSTR |= (1<<1)); (RCC_REG->RCC_AHB1RSTR &= ~(1<<0)); }while(0)
#define GPIOC_RSTR()					do{(RCC_REG->RCC_AHB1RSTR |= (1<<2)); (RCC_REG->RCC_AHB1RSTR &= ~(1<<0)); }while(0)
#define GPIOD_RSTR()					do{(RCC_REG->RCC_AHB1RSTR |= (1<<3)); (RCC_REG->RCC_AHB1RSTR &= ~(1<<0)); }while(0)
#define GPIOE_RSTR()					do{(RCC_REG->RCC_AHB1RSTR |= (1<<4)); (RCC_REG->RCC_AHB1RSTR &= ~(1<<0)); }while(0)
#define GPIOF_RSTR()					do{(RCC_REG->RCC_AHB1RSTR |= (1<<5)); (RCC_REG->RCC_AHB1RSTR &= ~(1<<0)); }while(0)
#define GPIOG_RSTR()					do{(RCC_REG->RCC_AHB1RSTR |= (1<<6)); (RCC_REG->RCC_AHB1RSTR &= ~(1<<0)); }while(0)
#define GPIOH_RSTR()					do{(RCC_REG->RCC_AHB1RSTR |= (1<<7)); (RCC_REG->RCC_AHB1RSTR &= ~(1<<0)); }while(0)
#define GPIOI_RSTR()					do{(RCC_REG->RCC_AHB1RSTR |= (1<<8)); (RCC_REG->RCC_AHB1RSTR &= ~(1<<0)); }while(0)

//****************SPI Peripheral Macros**************************************
//****************SPI BITS numbers*******************************************
//****************SPI BITS numbers CR1***************************************
#define SPI_BIT_CPHA					0
#define SPI_BIT_CPOL					1
#define SPI_BIT_MSTR					2
#define SPI_BIT_BR						3
#define SPI_BIT_EN						6						//Enables SPI , @Warning: Always set this bit at the end after setting the SPI settings of the other bits, once initiated, does not allow setting SPI
#define SPI_BIT_SSI						8
#define SPI_BIT_SSM						9
#define SPI_BIT_RXONLY					10
#define SPI_BIT_DFF						11
#define SPI_BIT_BIDIOE					14						//Bidir Output enable mode
#define SPI_BIT_BIDIMODE				15						//Bidir Bus mode
//****************SPI BITS numbers CR2*******************************************
#define SPI_BIT_SSOE					2
#define SPI_BIT_CR2_RXNEIE				6
#define SPI_BIT_CR2_TXEIE				7
//****************SPI BITS numbers SR*******************************************
#define SPI_BIT_RXNE					0						//Receiver buffer not empty
#define SPI_BIT_TXE						1						//Tramitter buffer empty
#define SPI_BIT_SR_MODF					5
#define SPI_BIT_OVR						6
#define SPI_BIT_BSY						7
//****************SPI BITS numbers SR*******************************************
#define SPI_EVENT_TX_CMPLT				0
#define SPI_EVENT_RX_CMPLT				2
#define SPI_EVENT_OVER_ERR_CMPLT		3


//*********************I2C  Macros*********************************************
//*********************I2C  Bit NUmbers****************************************
//*********************I2C  CR1 Register***************************************
#define I2C_CR1_PE						0
#define I2C_CR1_SMBUS					1
//#define I2C_CR1_Res1					2						//A reserved reg bit, must be kept at reset value
#define I2C_CR1_SMBTYPE					3
#define I2C_CR1_ENARP					4
#define I2C_CR1_ENPEC					5
#define I2C_CR1_ENGC					6
#define I2C_CR1_NOSTRECH				7
#define I2C_CR1_START					8
#define I2C_CR1_STOP					9
#define I2C_CR1_ACK						10
#define I2C_CR1_POS						11
#define I2C_CR1_PEC						12
#define I2C_CR1_ALERT					13
//#define I2C_CR1_Res2					14						//Reserved bit
#define I2C_CR1_SWRST
//*********************I2C  CR2 Register***************************************
#define I2C_CR2_FREQ					0
#define I2C_CR2_Res1					6
#define I2C_CR2_ITERREN					8
#define I2C_CR2_ITEVTEN					9
#define I2C_CR2_ITBUFEN					10
#define I2C_CR2_DMAEN					11
#define I2C_CR2_LAST					12
#define I2C_CR2_Res2					13
//*********************I2C  SR1 Register***************************************
#define I2C_SR1_SB						0
#define I2C_SR1_ADDR					1
#define I2C_SR1_BTF						2
#define I2C_SR1_ADD10					3
#define I2C_SR1_STOPF					4
#define I2C_SR1_RES1					5
#define I2C_SR1_RxNE					6
#define I2C_SR1_TxE						7
#define I2C_SR1_BERR					8
#define I2C_SR1_ARLO					9
#define I2C_SR1_AF						10
#define I2C_SR1_OVR						11
#define I2C_SR1_PECERR					12
#define I2C_SR1_RES2					13
#define I2C_SR1_TIMEOUT					14
#define I2C_SR1_SMBALERT				15
//*********************I2C  SR2 Register***************************************
#define I2C_SR2_MSL						0
#define I2C_SR2_BUSY					1
#define I2C_SR2_TRA						2
#define I2C_SR2_RES1					3
#define I2C_SR2_GENCALL					4
#define I2C_SR2_SMBDEFAULT				5
#define I2C_SR2_SMBHOST					6
#define I2C_SR2_DUALF					7
#define I2C_SR2_PEC						8
//*********************I2C  CCR Register***************************************
#define I2C_CCR_CCR						0
#define I2C_CCR_RES1					12
#define I2C_CCR_DUTY					14
#define I2C_CCR_FST_SLW_MODE			15
//**************IRQ numbers*******************************************************
//**************IRQ number of EXTI (External Interrupt/Event Macros)**************
//@note * These are the EXTI Position by default of STM32F40XX
#define IRQ_EXIT_0						6
#define IRQ_EXIT_1						7
#define IRQ_EXIT_2						8
#define IRQ_EXIT_3						9
#define IRQ_EXIT_4						10
#define IRQ_EXTI_9_5					23
#define IRQ_EXTI_15_10					40
//**************IRQ number of SPI**********************************************
#define IRQ_SPI1						42
#define IRQ_SPI2						43
#define IRQ_SPI3						51
//**************Sys CLK status Reg**********************************************
#define SYSCLK_SW_STATUS_HSI			0
#define SYSCLK_SW_STATUS_HSE			1
#define SYSCLK_SW_STATUS_PLL			2
#define SYSCLK_SW_STATUS_NA				3
//****************Generic Macros*************************************************
#define ENABLE							1
#define DISABLE							0
#define SET								ENABLE
#define RESET							DISABLE
#define GPIO_PIN_SET					SET
#define GPIO_PIN_RESET					RESET
#define FLAG_SET						ENABLE
#define FLAG_RESET						DISABLE

#include "stm32f4xx_gpio_driver.h"
#include "stm32f4xx_spi_driver.h"
#include "stm32f4XX_I2C_driver.h"
#endif /* INC_STM32F407D_H_ */
