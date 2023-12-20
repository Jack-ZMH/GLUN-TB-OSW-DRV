#ifndef BSP_D2X2B_H
#define BSP_D2X2B_H
#include "sys.h"
#include "bsp_nxp9698.h"
#include "bsp_MxN.h"


#define D2X2B_GPIO_MA_PIN       GPIO_PIN_4
#define D2X2B_GPIO_MA_PORT      GPIOB
#define D2X2B_GPIO_MA_CLK()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define D2X2B_GPIO_MA_H()		do{HAL_GPIO_WritePin(D2X2B_GPIO_MA_PORT,D2X2B_GPIO_MA_PIN,GPIO_PIN_SET);}while(0)
#define D2X2B_GPIO_MA_L()		do{HAL_GPIO_WritePin(D2X2B_GPIO_MA_PORT,D2X2B_GPIO_MA_PIN,GPIO_PIN_RESET);}while(0)
		
#define D2X2B_GPIO_MB_PIN       GPIO_PIN_3
#define D2X2B_GPIO_MB_PORT      GPIOB
#define D2X2B_GPIO_MB_CLK()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define D2X2B_GPIO_MB_H()		do{HAL_GPIO_WritePin(D2X2B_GPIO_MB_PORT,D2X2B_GPIO_MB_PIN,GPIO_PIN_SET);}while(0)
#define D2X2B_GPIO_MB_L()		do{HAL_GPIO_WritePin(D2X2B_GPIO_MB_PORT,D2X2B_GPIO_MB_PIN,GPIO_PIN_RESET);}while(0)



#define D2X2B_READ_PIN3_PORT    IP1_CMD //只有PIN3需要
#define D2X2B_READ_MA_PIN3      GPIO_Pin_0

#define D2X2B_READ_PIN10_PORT   IP0_CMD
#define D2X2B_READ_MB_PIN10     GPIO_Pin_5

#define D2X2B_READ_PIN5_PORT   IP0_CMD
#define D2X2B_READ_MA_PIN5      GPIO_Pin_7

#define D2X2B_READ_PIN8_PORT   IP0_CMD
#define D2X2B_READ_MB_PIN8      GPIO_Pin_6


void D2X2B_GPIO_Init(void);
void D2X2B_CHENCK(uint16_t time,uint32_t num);
uint8_t D2X2B_State_Cross(uint16_t time);
uint8_t D2X2B_State_Bar(uint16_t time);

#endif


