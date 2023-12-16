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



typedef enum Switch_Status
{
	OFF = 0,
	ON
}Switch_Status;


typedef enum LockTypedef
{
	lock  = 0,
	nolock
}LockTypedef;


extern Switch_Status Switch;

void M1X1_GPIO_Init(void);
void M1X1_CHENCK(uint16_t time,uint32_t num);
void M1X1_StateA(uint16_t time);
void M1X1_StateB(uint16_t time);

#endif

