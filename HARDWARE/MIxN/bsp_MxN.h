#ifndef BSP_MXN_H
#define BSP_MXN_H

#include "sys.h"
#include "bsp_nxp9698.h"

/// @brief M1X1_宏定�?
#define M1X1_GPIO_PIN           GPIO_PIN_2
#define M1X1_GPIO_PORT          GPIOD
#define M1X1_GPIO_CLK()         __HAL_RCC_GPIOD_CLK_ENABLE()
#define M1X1_GPIO_H()			do{HAL_GPIO_WritePin(M1X1_GPIO_PORT,M1X1_GPIO_PIN,GPIO_PIN_SET);}while(0)
#define M1X1_GPIO_L()			do{HAL_GPIO_WritePin(M1X1_GPIO_PORT,M1X1_GPIO_PIN,GPIO_PIN_RESET);}while(0)

#define M1X1_READ_PORT          IP2_CMD
#define M1X1_READ_PIN2          GPIO_Pin_6
#define M1X1_READ_PIN7          GPIO_Pin_5
#define M1X1_READ_PIN4          GPIO_Pin_7
#define M1X1_READ_PIN5          GPIO_Pin_4


#define   C1X2G		0x00
#define   D2X2B		0x01
#define   M1X1		0x02
#define   M1X4		0x03
#define   S1X4		0x04
#define   S1X8		0x05
#define   N_C1X2G		0x06
#define   N_M1X4		0x07
#define   N_S1X4		0x08
#define   N_S1X8		0x09


typedef enum Typedef_Select
{
	C1X2G_t = 0,
	D2X2B_t,
	M1X1_t,
	M1X4_t,
	S1X4_t,
	S1X8_t,
	N_C1X2G_t,
	N_M1X4_t,
	N_S1X4_t,
	N_S1X8_t
	
}Typedef_Select;


extern uint8_t Switch;
extern Typedef_Select TYPEFEF_SELECT;


void M1X1_GPIO_Init(void);
void M1X1_CHENCK(uint16_t time,uint32_t num);
uint8_t M1X1_StateA(uint16_t time);
uint8_t M1X1_StateB(uint16_t time);

#endif

