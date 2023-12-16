#include "bsp_key.h"

void KEY_GPIO_Init(void)
{
	KEY_PIN_CLK();
	
	GPIO_InitTypeDef  GPIO_InitureStruct;
	GPIO_InitureStruct.Pin = KEY_AUTO_PIN;
	GPIO_InitureStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitureStruct.Pull = GPIO_PULLUP;
	GPIO_InitureStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;	
	HAL_GPIO_Init(KEY_AUTO_PORT,&GPIO_InitureStruct);
	
	GPIO_InitureStruct.Pin = KEY_SELET_PIN;
	HAL_GPIO_Init(KEY_AUTO_PORT,&GPIO_InitureStruct);
	
	HAL_NVIC_SetPriority(EXTI2_IRQn,0,1);
	HAL_NVIC_EnableIRQ(EXTI2_IRQn);
	
	HAL_NVIC_SetPriority(EXTI3_IRQn,0,0);
	HAL_NVIC_EnableIRQ(EXTI3_IRQn);	
	
}

u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY_AUTO_READ==0||KEY_SELET_READ==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY_AUTO_READ==0)return KEY_AUTO_PRES;
		else if(KEY_SELET_READ==0)return KEY_SELET_PRES;

	}else if(KEY_AUTO_READ==1&&KEY_SELET_READ==1)key_up=1; 	     
	return 0;// 无按键按下
}

void EXTI2_IRQHandler()
{
	HAL_GPIO_EXTI_IRQHandler(KEY_SELET_PIN);
}
void EXTI3_IRQHandler()
{
	HAL_GPIO_EXTI_IRQHandler(KEY_AUTO_PIN);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	delay_ms(20);
	switch(GPIO_Pin)
	{
		case KEY_AUTO_PIN: //printf("KEY_AUTO_PIN\n");
							if(Switch == OFF) Switch =ON;
							else if(Switch == ON) Switch =OFF;
							break;
		case KEY_SELET_PIN:printf("KEY_SELET_PIN\n");break;
		default:
			break;
	}
	
}

