#ifndef BSP_C1X2G_H
#define BSP_C1X2G_H

#include "sys.h"
#include "bsp_nxp9698.h"
#include "bsp_MxN.h"

/// @brief C1X2G_宏定义
#define C1X2G_GPIO_CTRL_PIN     GPIO_PIN_10
#define C1X2G_GPIO_CTRL_PORT    GPIOC
#define C1X2G_GPIO_CTRL_CLK()   __HAL_RCC_GPIOC_CLK_ENABLE()
#define C1X2G_GPIO_CTRL_H()		do{HAL_GPIO_WritePin(C1X2G_GPIO_CTRL_PORT,C1X2G_GPIO_CTRL_PIN,GPIO_PIN_SET);}while(0)
#define C1X2G_GPIO_CTRL_L()		do{HAL_GPIO_WritePin(C1X2G_GPIO_CTRL_PORT,C1X2G_GPIO_CTRL_PIN,GPIO_PIN_RESET);}while(0)

#define C1X2G_GPIO_MA_PIN       GPIO_PIN_12
#define C1X2G_GPIO_MA_PORT      GPIOC
#define C1X2G_GPIO_MA_CLK()     __HAL_RCC_GPIOC_CLK_ENABLE()
#define C1X2G_GPIO_MA_H()		do{HAL_GPIO_WritePin(C1X2G_GPIO_MA_PORT,C1X2G_GPIO_MA_PIN,GPIO_PIN_SET);}while(0)
#define C1X2G_GPIO_MA_L()		do{HAL_GPIO_WritePin(C1X2G_GPIO_MA_PORT,C1X2G_GPIO_MA_PIN,GPIO_PIN_RESET);}while(0)

#define C1X2G_GPIO_MB_PIN       GPIO_PIN_11
#define C1X2G_GPIO_MB_PORT      GPIOC
#define C1X2G_GPIO_MB_CLK()     __HAL_RCC_GPIOC_CLK_ENABLE()
#define C1X2G_GPIO_MB_H()		do{HAL_GPIO_WritePin(C1X2G_GPIO_MB_PORT,C1X2G_GPIO_MB_PIN,GPIO_PIN_SET);}while(0)
#define C1X2G_GPIO_MB_L()		do{HAL_GPIO_WritePin(C1X2G_GPIO_MB_PORT,C1X2G_GPIO_MB_PIN,GPIO_PIN_RESET);}while(0)


#define C1X2G_READ_PORT         IP0_CMD
#define C1X2G_READ_MA_PIN2      GPIO_Pin_2
#define C1X2G_READ_MA_PIN4      GPIO_Pin_3
#define C1X2G_READ_MB_PIN7      GPIO_Pin_0
#define C1X2G_READ_MB_PIN9      GPIO_Pin_1


void C1X2G_GPIO_Init(void);
void C1X2G_CHENCK(uint16_t time,uint32_t num,uint8_t lock);

uint8_t Latch_C1X2_StateA(uint16_t time);
uint8_t Latch_C1X2_StateB(uint16_t time);

uint8_t NonLatch_C1X2_StateA(uint16_t time);
uint8_t NonLatch_C1X2_StateA(uint16_t time);

#endif

