#ifndef BSP_S1X4_H
#define BSP_S1X4_H

#include "sys.h"
#include "bsp_nxp9698.h"
#include "bsp_MxN.h"

/* A组继电器引脚宏定义 */
#define S1X4_A_GPIO_CTRL_PIN              GPIO_PIN_8
#define S1X4_A_GPIO_CTRL_PORT             GPIOC
#define S1X4_A_GPIO_CTRL_CLK()            __HAL_RCC_GPIOC_CLK_ENABLE()
#define S1X4_A_GPIO_CTRL_H()		      do{HAL_GPIO_WritePin(S1X4_A_GPIO_CTRL_PORT,S1X4_A_GPIO_CTRL_PIN,GPIO_PIN_SET);}while(0)
#define S1X4_A_GPIO_CTRL_L()		      do{HAL_GPIO_WritePin(S1X4_A_GPIO_CTRL_PORT,S1X4_A_GPIO_CTRL_PIN,GPIO_PIN_RESET);}while(0)

#define S1X4_A_GPIO_MA_PIN                GPIO_PIN_7
#define S1X4_A_GPIO_MA_PORT               GPIOC
#define S1X4_A_GPIO_MA_CLK()              __HAL_RCC_GPIOC_CLK_ENABLE()
#define S1X4_A_GPIO_MA_H()		          do{HAL_GPIO_WritePin(S1X4_A_GPIO_MA_PORT,S1X4_A_GPIO_MA_PIN,GPIO_PIN_SET);}while(0)
#define S1X4_A_GPIO_MA_L()		          do{HAL_GPIO_WritePin(S1X4_A_GPIO_MA_PORT,S1X4_A_GPIO_MA_PIN,GPIO_PIN_RESET);}while(0)

#define S1X4_A_GPIO_MB_PIN                GPIO_PIN_6
#define S1X4_A_GPIO_MB_PORT               GPIOC
#define S1X4_A_GPIO_MB_CLK()              __HAL_RCC_GPIOC_CLK_ENABLE()
#define S1X4_A_GPIO_MB_H()		          do{HAL_GPIO_WritePin(S1X4_A_GPIO_MB_PORT,S1X4_A_GPIO_MB_PIN,GPIO_PIN_SET);}while(0)
#define S1X4_A_GPIO_MB_L()		          do{HAL_GPIO_WritePin(S1X4_A_GPIO_MB_PORT,S1X4_A_GPIO_MB_PIN,GPIO_PIN_RESET);}while(0)


/* B组继电器引脚宏定义 */
#define S1X4_B_GPIO_CTRL_PIN              GPIO_PIN_9
#define S1X4_B_GPIO_CTRL_PORT             GPIOC
#define S1X4_B_GPIO_CTRL_CLK()            __HAL_RCC_GPIOC_CLK_ENABLE()
#define S1X4_B_GPIO_CTRL_H()		      do{HAL_GPIO_WritePin(S1X4_B_GPIO_CTRL_PORT,S1X4_B_GPIO_CTRL_PIN,GPIO_PIN_SET);}while(0)
#define S1X4_B_GPIO_CTRL_L()		      do{HAL_GPIO_WritePin(S1X4_B_GPIO_CTRL_PORT,S1X4_B_GPIO_CTRL_PIN,GPIO_PIN_RESET);}while(0)

#define S1X4_B_GPIO_MA_PIN                GPIO_PIN_15
#define S1X4_B_GPIO_MA_PORT               GPIOB
#define S1X4_B_GPIO_MA_CLK()              __HAL_RCC_GPIOB_CLK_ENABLE()
#define S1X4_B_GPIO_MA_H()		          do{HAL_GPIO_WritePin(S1X4_B_GPIO_MA_PORT,S1X4_B_GPIO_MA_PIN,GPIO_PIN_SET);}while(0)
#define S1X4_B_GPIO_MA_L()		          do{HAL_GPIO_WritePin(S1X4_B_GPIO_MA_PORT,S1X4_B_GPIO_MA_PIN,GPIO_PIN_RESET);}while(0)

#define S1X4_B_GPIO_MB_PIN                GPIO_PIN_14
#define S1X4_B_GPIO_MB_PORT               GPIOB
#define S1X4_B_GPIO_MB_CLK()              __HAL_RCC_GPIOB_CLK_ENABLE()
#define S1X4_B_GPIO_MB_H()		          do{HAL_GPIO_WritePin(S1X4_B_GPIO_MB_PORT,S1X4_B_GPIO_MB_PIN,GPIO_PIN_SET);}while(0)
#define S1X4_B_GPIO_MB_L()		          do{HAL_GPIO_WritePin(S1X4_B_GPIO_MB_PORT,S1X4_B_GPIO_MB_PIN,GPIO_PIN_RESET);}while(0)



/* A组读取引脚宏定义 */
#define S1X4_A_READ_PORT1                 IP1_CMD
#define S1X4_A_READ_PIN4                  GPIO_Pin_2
#define S1X4_A_READ_PIN7                  GPIO_Pin_3

#define S1X4_A_READ_PORT2                 IP3_CMD 
#define S1X4_A_READ_PIN2                  GPIO_Pin_4
#define S1X4_A_READ_PIN9                  GPIO_Pin_5


/* B组读取引脚宏定义 */
#define S1X4_B_READ_PORT                  IP3_CMD
#define S1X4_B_READ_PIN2                  GPIO_Pin_2
#define S1X4_B_READ_PIN4                  GPIO_Pin_1
#define S1X4_B_READ_PIN7                  GPIO_Pin_0
#define S1X4_B_READ_PIN9                  GPIO_Pin_3



void S1X4_GPIO_Init(void);

/// @brief Lacthing Switch
/// @param  
void S1X4_CHENCK(uint16_t time,uint32_t num,LockTypedef SwitchType);
void Latch_S1X4_COMP1(uint16_t time);
void Latch_S1X4_COMP2(uint16_t time);
void Latch_S1X4_COMP3(uint16_t time);
void Latch_S1X4_COMP4(uint16_t time);


/// @brief Non-Lacthing Switch
/// @param 
void NonLatch_S1X4_COMP1(uint16_t time);
void NonLatch_S1X4_COMP2(uint16_t time);
void NonLatch_S1X4_COMP3(uint16_t time);
void NonLatch_S1X4_COMP4(uint16_t time);
#endif

