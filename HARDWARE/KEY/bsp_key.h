#ifndef BSP_KEY_H
#define BSP_KEY_H
#include "sys.h"
#include "bsp_MxN.h"

#define KEY_PIN_CLK()		__HAL_RCC_GPIOA_CLK_ENABLE()
#define KEY_AUTO_PIN		GPIO_PIN_3
#define KEY_AUTO_PORT		GPIOA

#define KEY_SELET_PIN		GPIO_PIN_2
#define KEY_SELET_PORT		GPIOA


//����ķ�ʽ��ͨ��ֱ�Ӳ���HAL�⺯����ʽ��ȡIO
#define KEY_AUTO_READ       	HAL_GPIO_ReadPin(KEY_AUTO_PORT,KEY_AUTO_PIN)  //KEY2����PD2
#define KEY_SELET_READ      	HAL_GPIO_ReadPin(KEY_SELET_PORT,KEY_SELET_PIN)  //WKUP����PA0

#define KEY_AUTO_PRES	1	//KEY0  
#define KEY_SELET_PRES	2	//KEY1 

void KEY_GPIO_Init(void);
u8 KEY_Scan(u8 mode);
#endif
