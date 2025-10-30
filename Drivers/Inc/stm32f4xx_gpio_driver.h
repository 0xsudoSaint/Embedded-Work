/*
 * stm32f4xx_gpio_driver.h
 *
 *  Created on: Sep 26, 2025
 *      Author: tiberius
 */

#ifndef INC_STM32F4XX_GPIO_DRIVER_H_
#define INC_STM32F4XX_GPIO_DRIVER_H_

#include "stm32f407d.h"
typedef struct
{
	char GPIO_PName;
	uint8_t GPIO_PinNum;								/*!<Selection of the pin, refer to @GPIO_PIN_NUM_MACROS >*/
	uint8_t GPIO_PinMode;								/*!<Determine the PIN mode of GPIO port,refer to @GPIO_PIN_MODE_MACROS >*/
	uint8_t GPIO_PinSpeed;								/*!<Speed of pin, refer to @GPIO_PORT_OUT_SPEED_MACROS >*/
	uint8_t GPIO_PinOType;								/*!<Configure the output state of the GPIO port, reference @GPIO_PORT_OUTPUT_TYPE >*/
	uint8_t GPIO_PinPuPdCtrl;							/*!<Pull up,pull down register, refer to @GPIO_PORT_PULL_UP_PULL_DOWN_MACROS >*/
	uint8_t GPIO_PinAltFunc;							/*!<Configure the alternate functionality of GPIO port , reference @GPIO_PORT_ALTERNATE_FUNCTIONALITY>*/

}GPIO_PinConfig_t;
typedef struct
{
	GPIO_REG_DEF* pGPIO;								//Pointer to the GPIO port
	GPIO_PinConfig_t GPIO_PinConfig;					//Configration Struct (which has cnofigration of GPIO)
}GPIO_HANDLE_t;

/*------------------------------------Functions Prototypes---------------------------
-------------------------------------------------------------------------------------*/
//------------------------------------Initialize & Deinitialize-----------------------
void GPIO_Init(GPIO_HANDLE_t *pGPIO_HNDL);
void GPIO_Deinit(GPIO_REG_DEF* pGPIO);
//------------------------------------Clock (Enable & Disable)------------------------
void GPIO_CLK_Ctrl(GPIO_REG_DEF* pGPIO,uint8_t EN_DI);
//------------------------------------Read (Pin & Port)-------------------------------
uint8_t GPIO_ReadFromInputPin(GPIO_REG_DEF *pGPIO,uint8_t PinNum);
uint16_t GPIO_ReadFromInputPort(GPIO_REG_DEF *pGPIO);
//------------------------------------Write (Pin & Port-------------------------------
void GPIO_WriteToOutputPin(GPIO_REG_DEF* pGPIO,uint8_t PinNum,uint8_t Value);
void GPIO_WritetoOutputPort(GPIO_REG_DEF* pGPIO,uint16_t Value);
void GPIO_Toggle_OPin(GPIO_REG_DEF* pGPIO,uint8_t PinNum);
//------------------------------------Interrupts--------------------------------------
void GPIO_IRQ_INT_Config(uint8_t IRQ_Num,uint8_t IRQ_EN_DI);
void GPIO_IRQ_Priority_Config(uint8_t IRQ_Num,uint8_t IRQ_Priority);
void GPIO_InterruptHandling(uint8_t PinNum);
//------------------------------Reserved Bit in Int Priority--------------------------
#define RESRVED_PBITS				4
/*************************************************************************************
 ** 							GPIO MACROS											**
 *************************************************************************************/
/*******************************PIN MODE *********************************************
 * @GPIO_PIN_MODE_MACROS
 * @note -Three Extra modes for the rising,falling and rising or falling edge trigger
 */
#define GPIO_MODE_IN				0
#define GPIO_MODE_OUT				1
#define GPIO_MODE_ALT				2
#define GPIO_MODE_ANLG				3
#define GPIO_MODE_RT				4
#define GPIO_MODE_FT				5
#define GPIO_MODE_RFT				6

/*******************************PIN Number *********************************************
 * @GPIO_PIN_NUM_MACROS
*/
#define GPIO_PIN_0					0
#define GPIO_PIN_1					1
#define GPIO_PIN_2					2
#define GPIO_PIN_3					3
#define GPIO_PIN_4					4
#define GPIO_PIN_5					5
#define GPIO_PIN_6					6
#define GPIO_PIN_7					7
#define GPIO_PIN_8					8
#define GPIO_PIN_9					9
#define GPIO_PIN_10					10
#define GPIO_PIN_11					11
#define GPIO_PIN_12					12
#define GPIO_PIN_13					13
#define GPIO_PIN_14					14
#define GPIO_PIN_15					15

/*******************************Output Speed************************************
 * @GPIO_PORT_OUT_SPEED_MACROS
*/
#define GPIO_L_SPEED				0
#define GPIO_MED_SPEED				1
#define GPIO_H_SPEED				2
#define GPIO_VH_SPEED				3
/*******************************Pull up/down config*****************************
 * @GPIO_PORT_PULL_UP_PULL_DOWN_MACROS
*/
#define	GPIO_PORT_NO_PUP_PD			0
#define GIPO_PUP					1
#define GPIO_PD						2
#define GPIO_RESERVED				3
/*******************************Output TYPE*************************************
 * @GPIO_PORT_OUTPUT_TYPE
*/
#define GPIO_OUT_PUSHPULL			0						//@note -RESET STATE
#define GPIO_OUT_OPEN_DRAIN			1
/*******************************Alternate Functionality*************************
 * @GPIO_PORT_ALTERNATE_FUNCTIONALITY
*/
#define GPIO_ALT_0					0
#define GPIO_ALT_1					1
#define GPIO_ALT_2					2
#define GPIO_ALT_3					3
#define GPIO_ALT_4					4
#define GPIO_ALT_5					5
#define GPIO_ALT_6					6
#define GPIO_ALT_7					7


#endif /* INC_STM32F4XX_GPIO_DRIVER_H_ */
