#ifndef BSP_S1X8_H
#define BSP_S1X8_H
#include "sys.h"
#include "bsp_nxp9698.h"
#include "bsp_MxN.h"

/* A组继电器引脚宏定义 */
#define S1X8_A_GPIO_CTRL_PIN              GPIO_PIN_6
#define S1X8_A_GPIO_CTRL_PORT             GPIOA
#define S1X8_A_GPIO_CTRL_CLK()            __HAL_RCC_GPIOA_CLK_ENABLE()
#define S1X8_A_GPIO_CTRL_H()		      do{HAL_GPIO_WritePin(S1X8_A_GPIO_CTRL_PORT,S1X8_A_GPIO_CTRL_PIN,GPIO_PIN_SET);}while(0)
#define S1X8_A_GPIO_CTRL_L()		      do{HAL_GPIO_WritePin(S1X8_A_GPIO_CTRL_PORT,S1X8_A_GPIO_CTRL_PIN,GPIO_PIN_RESET);}while(0)

#define S1X8_A_GPIO_MA_PIN                GPIO_PIN_13
#define S1X8_A_GPIO_MA_PORT               GPIOB
#define S1X8_A_GPIO_MA_CLK()              __HAL_RCC_GPIOB_CLK_ENABLE()
#define S1X8_A_GPIO_MA_H()		          do{HAL_GPIO_WritePin(S1X8_A_GPIO_MA_PORT,S1X8_A_GPIO_MA_PIN,GPIO_PIN_SET);}while(0)
#define S1X8_A_GPIO_MA_L()		          do{HAL_GPIO_WritePin(S1X8_A_GPIO_MA_PORT,S1X8_A_GPIO_MA_PIN,GPIO_PIN_RESET);}while(0)

#define S1X8_A_GPIO_MB_PIN                GPIO_PIN_12
#define S1X8_A_GPIO_MB_PORT               GPIOB
#define S1X8_A_GPIO_MB_CLK()              __HAL_RCC_GPIOC_CLK_ENABLE()
#define S1X8_A_GPIO_MB_H()		          do{HAL_GPIO_WritePin(S1X8_A_GPIO_MB_PORT,S1X8_A_GPIO_MB_PIN,GPIO_PIN_SET);}while(0)
#define S1X8_A_GPIO_MB_L()		          do{HAL_GPIO_WritePin(S1X8_A_GPIO_MB_PORT,S1X8_A_GPIO_MB_PIN,GPIO_PIN_RESET);}while(0)

/* B组继电器引脚宏定义 */
#define S1X8_B_GPIO_CTRL_PIN              GPIO_PIN_7
#define S1X8_B_GPIO_CTRL_PORT             GPIOA
#define S1X8_B_GPIO_CTRL_CLK()            __HAL_RCC_GPIOA_CLK_ENABLE()
#define S1X8_B_GPIO_CTRL_H()		      do{HAL_GPIO_WritePin(S1X8_B_GPIO_CTRL_PORT,S1X8_B_GPIO_CTRL_PIN,GPIO_PIN_SET);}while(0)
#define S1X8_B_GPIO_CTRL_L()		      do{HAL_GPIO_WritePin(S1X8_B_GPIO_CTRL_PORT,S1X8_B_GPIO_CTRL_PIN,GPIO_PIN_RESET);}while(0)

#define S1X8_B_GPIO_MA_PIN                GPIO_PIN_10
#define S1X8_B_GPIO_MA_PORT               GPIOB
#define S1X8_B_GPIO_MA_CLK()              __HAL_RCC_GPIOB_CLK_ENABLE()
#define S1X8_B_GPIO_MA_H()		          do{HAL_GPIO_WritePin(S1X8_B_GPIO_MA_PORT,S1X8_B_GPIO_MA_PIN,GPIO_PIN_SET);}while(0)
#define S1X8_B_GPIO_MA_L()		          do{HAL_GPIO_WritePin(S1X8_B_GPIO_MA_PORT,S1X8_B_GPIO_MA_PIN,GPIO_PIN_RESET);}while(0)

#define S1X8_B_GPIO_MB_PIN                GPIO_PIN_1
#define S1X8_B_GPIO_MB_PORT               GPIOB
#define S1X8_B_GPIO_MB_CLK()              __HAL_RCC_GPIOB_CLK_ENABLE()
#define S1X8_B_GPIO_MB_H()		          do{HAL_GPIO_WritePin(S1X8_B_GPIO_MB_PORT,S1X8_B_GPIO_MB_PIN,GPIO_PIN_SET);}while(0)
#define S1X8_B_GPIO_MB_L()		          do{HAL_GPIO_WritePin(S1X8_B_GPIO_MB_PORT,S1X8_B_GPIO_MB_PIN,GPIO_PIN_RESET);}while(0)

/* C组继电器引脚宏定义 */
#define S1X8_C_GPIO_CTRL_PIN              GPIO_PIN_4
#define S1X8_C_GPIO_CTRL_PORT             GPIOC
#define S1X8_C_GPIO_CTRL_CLK()            __HAL_RCC_GPIOC_CLK_ENABLE()
#define S1X8_C_GPIO_CTRL_H()		      do{HAL_GPIO_WritePin(S1X8_C_GPIO_CTRL_PORT,S1X8_C_GPIO_CTRL_PIN,GPIO_PIN_SET);}while(0)
#define S1X8_C_GPIO_CTRL_L()		      do{HAL_GPIO_WritePin(S1X8_C_GPIO_CTRL_PORT,S1X8_C_GPIO_CTRL_PIN,GPIO_PIN_RESET);}while(0)

#define S1X8_C_GPIO_MA_PIN                GPIO_PIN_0
#define S1X8_C_GPIO_MA_PORT               GPIOB
#define S1X8_C_GPIO_MA_CLK()              __HAL_RCC_GPIOB_CLK_ENABLE()
#define S1X8_C_GPIO_MA_H()		          do{HAL_GPIO_WritePin(S1X8_C_GPIO_MA_PORT,S1X8_C_GPIO_MA_PIN,GPIO_PIN_SET);}while(0)
#define S1X8_C_GPIO_MA_L()		          do{HAL_GPIO_WritePin(S1X8_C_GPIO_MA_PORT,S1X8_C_GPIO_MA_PIN,GPIO_PIN_RESET);}while(0)

#define S1X8_C_GPIO_MB_PIN                GPIO_PIN_5
#define S1X8_C_GPIO_MB_PORT               GPIOC
#define S1X8_C_GPIO_MB_CLK()              __HAL_RCC_GPIOB_CLK_ENABLE()
#define S1X8_C_GPIO_MB_H()		          do{HAL_GPIO_WritePin(S1X8_C_GPIO_MB_PORT,S1X8_C_GPIO_MB_PIN,GPIO_PIN_SET);}while(0)
#define S1X8_C_GPIO_MB_L()		          do{HAL_GPIO_WritePin(S1X8_C_GPIO_MB_PORT,S1X8_C_GPIO_MB_PIN,GPIO_PIN_RESET);}while(0)



/* A组读取引脚宏定义 */
#define S1X8_A_READ_PIN2_PORT             IP0_CMD
#define S1X8_A_READ_PIN2                  GPIO_Pin_4
#define S1X8_A_READ_PIN4_PORT             IP4_CMD
#define S1X8_A_READ_PIN4                  GPIO_Pin_7
#define S1X8_A_READ_PIN7_PORT             IP3_CMD
#define S1X8_A_READ_PIN7                  GPIO_Pin_6
#define S1X8_A_READ_PIN9_PORT             IP1_CMD
#define S1X8_A_READ_PIN9                  GPIO_Pin_1

/* B组读取引脚宏定义 */
#define S1X8_B_READ_PIN2_PORT             IP4_CMD
#define S1X8_B_READ_PIN2                  GPIO_Pin_4
#define S1X8_B_READ_PIN4_PORT             IP4_CMD
#define S1X8_B_READ_PIN4                  GPIO_Pin_3
#define S1X8_B_READ_PIN7_PORT             IP4_CMD
#define S1X8_B_READ_PIN7                  GPIO_Pin_6
#define S1X8_B_READ_PIN9_PORT             IP4_CMD
#define S1X8_B_READ_PIN9                  GPIO_Pin_5

/* C组读取引脚宏定义 */
#define S1X8_C_READ_PIN2_PORT             IP4_CMD
#define S1X8_C_READ_PIN2                  GPIO_Pin_0
#define S1X8_C_READ_PIN4_PORT             IP4_CMD
#define S1X8_C_READ_PIN4                  GPIO_Pin_1
#define S1X8_C_READ_PIN7_PORT             IP4_CMD
#define S1X8_C_READ_PIN7                  GPIO_Pin_2
#define S1X8_C_READ_PIN9_PORT             IP3_CMD
#define S1X8_C_READ_PIN9                  GPIO_Pin_3


void S1X8_GPIO_Init(void);
void Latch_S1X8_COM_P1(uint16_t time);
void Latch_S1X8_COM_P2(uint16_t time);
void Latch_S1X8_COM_P3(uint16_t time);
void Latch_S1X8_COM_P4(uint16_t time);
void Latch_S1X8_COM_P5(uint16_t time);
void Latch_S1X8_COM_P6(uint16_t time);
void Latch_S1X8_COM_P7(uint16_t time);
void Latch_S1X8_COM_P8(uint16_t time);
void Latch_S1X8_CHENCH(uint16_t time,uint32_t num,LockTypedef SwitchType);

void NonLatch_S1X8_COM_P1(uint16_t time);
void NonLatch_S1X8_COM_P2(uint16_t time);
void NonLatch_S1X8_COM_P3(uint16_t time);
void NonLatch_S1X8_COM_P4(uint16_t time);
void NonLatch_S1X8_COM_P5(uint16_t time);
void NonLatch_S1X8_COM_P6(uint16_t time);
void NonLatch_S1X8_COM_P7(uint16_t time);
void NonLatch_S1X8_COM_P8(uint16_t time);

#endif

