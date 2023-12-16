#ifndef BSP_M1X4_H
#define BSP_M1X4_H

#include "sys.h"
#include "bsp_nxp9698.h"
#include "bsp_MxN.h"


#define M1X4_GPIO_PIN1                  GPIO_PIN_15
#define M1X4_GPIO_PIN1_PORT             GPIOA
#define M1X4_GPIO_PIN1_CLK()            _HAL_RCC_GPIOA_CLK_ENABLE()
#define M1X4_GPIO_PIN1_H()		        do{HAL_GPIO_WritePin(M1X4_GPIO_PIN1_PORT,M1X4_GPIO_PIN1,GPIO_PIN_SET);}while(0)
#define M1X4_GPIO_PIN1_L()		        do{HAL_GPIO_WritePin(M1X4_GPIO_PIN1_PORT,M1X4_GPIO_PIN1,GPIO_PIN_RESET);}while(0)

#define M1X4_GPIO_PIN8                  GPIO_PIN_12
#define M1X4_GPIO_PIN8_PORT             GPIOA
#define M1X4_GPIO_PIN8_CLK()            _HAL_RCC_GPIOA_CLK_ENABLE()
#define M1X4_GPIO_PIN8_H()		        do{HAL_GPIO_WritePin(M1X4_GPIO_PIN8_PORT,M1X4_GPIO_PIN8,GPIO_PIN_SET);}while(0)
#define M1X4_GPIO_PIN8_L()		        do{HAL_GPIO_WritePin(M1X4_GPIO_PIN8_PORT,M1X4_GPIO_PIN8,GPIO_PIN_RESET);}while(0)


#define M1X4_GPIO_PIN21                 GPIO_PIN_11
#define M1X4_GPIO_PIN21_PORT            GPIOA
#define M1X4_GPIO_PIN21_CLK()           __HAL_RCC_GPIOA_CLK_ENABLE()
#define M1X4_GPIO_PIN21_H()		        do{HAL_GPIO_WritePin(M1X4_GPIO_PIN21_PORT,M1X4_GPIO_PIN21,GPIO_PIN_SET);}while(0)
#define M1X4_GPIO_PIN21_L()		        do{HAL_GPIO_WritePin(M1X4_GPIO_PIN21_PORT,M1X4_GPIO_PIN21,GPIO_PIN_RESET);}while(0)

#define M1X4_GPIO_PIN28                 GPIO_PIN_8
#define M1X4_GPIO_PIN28_PORT            GPIOA
#define M1X4_GPIO_PIN28_CLK()           __HAL_RCC_GPIOA_CLK_ENABLE()
#define M1X4_GPIO_PIN28_H()		        do{HAL_GPIO_WritePin(M1X4_GPIO_PIN28_PORT,M1X4_GPIO_PIN28,GPIO_PIN_SET);}while(0)
#define M1X4_GPIO_PIN28_L()		        do{HAL_GPIO_WritePin(M1X4_GPIO_PIN28_PORT,M1X4_GPIO_PIN28,GPIO_PIN_RESET);}while(0)


#define M1X4_READ_PORT1                 IP1_CMD
#define M1X4_READ_PIN2                  GPIO_Pin_5
#define M1X4_READ_PIN4                  GPIO_Pin_6
#define M1X4_READ_PIN5                  GPIO_Pin_7
#define M1X4_READ_PIN7                  GPIO_Pin_4

#define M1X4_READ_PORT2                 IP2_CMD
#define M1X4_READ_PIN22                 GPIO_Pin_3
#define M1X4_READ_PIN24                 GPIO_Pin_0
#define M1X4_READ_PIN25                 GPIO_Pin_1
#define M1X4_READ_PIN27                 GPIO_Pin_2




void M1X4_GPIO_Init(void);

void M1X4_CHENCK(uint16_t time,uint32_t num,LockTypedef SwitchType);

void M1X4_State_A(uint16_t time);
void M1X4_State_B(uint16_t time);
void M1X4_State_C(uint16_t time);
void M1X4_State_D(uint16_t time);

void NonLatching_M1X4State_A(uint16_t time);
void NonLatching_M1X4State_B(uint16_t time);
void NonLatching_M1X4State_C(uint16_t time);
void NonLatching_M1X4State_D(uint16_t time);

#endif


