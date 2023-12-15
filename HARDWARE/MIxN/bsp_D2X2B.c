#include "bsp_D2X2B.h"


/// @brief C1X2G_GPIO_Init
/// @param  
void D2X2B_GPIO_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStruct;
	D2X2B_GPIO_MA_CLK();
	D2X2B_GPIO_MB_CLK();
	
	GPIO_InitStruct.Pin = D2X2B_GPIO_MA_PIN;							
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;				
	GPIO_InitStruct.Pull = GPIO_PULLUP;								
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(D2X2B_GPIO_MA_PORT, &GPIO_InitStruct);	

    GPIO_InitStruct.Pin = D2X2B_GPIO_MB_PIN;
    HAL_GPIO_Init(D2X2B_GPIO_MB_PORT, &GPIO_InitStruct);
	
	D2X2B_GPIO_MA_H();
	D2X2B_GPIO_MB_H();
} 


/// @brief ÖØ¸´ÇÐ»»
/// @param time 
/// @param num 
void D2X2B_CHENCK(uint16_t time,uint32_t num)
{	
	while(num--) 
	{	
		if(Switch)
		{
			D2X2B_GPIO_MA_L();
			D2X2B_GPIO_MB_H();
			delay_ms(time);
			if(PCA_GPIO_ReadPin(D2X2B_READ_PORT2,D2X2B_READ_MA_PIN3)&&
			   PCA_GPIO_ReadPin(D2X2B_READ_PORT1,D2X2B_READ_MB_PIN10))
				printf("D2X2B_Cross Error\n");
			else	
				printf("D2X2B_Cross Normel\n");
			  
			
			D2X2B_GPIO_MA_H();
			D2X2B_GPIO_MB_L();
			delay_ms(time);	
			if(READ_TwoPin(D2X2B_READ_PORT1,D2X2B_READ_MA_PIN5,D2X2B_READ_MB_PIN8))
				printf("D2X2B_Bar Error\n");
			else 
				printf("D2X2B_Bar Normel\n");
			 
		}
		else 
		{
			printf("C1X2G STOP\n");
			num = 0;
		}
	}   
}

/// @brief ÇÐ»»ÎªCross×´Ì¬
/// @param  
void D2X2B_State_Cross(void)
{
	D2X2B_GPIO_MA_L();
	D2X2B_GPIO_MB_H();
	delay_ms(20);	 
}

/// @brief ÇÐ»»ÎªBar×´Ì¬
/// @param  
void D2X2B_State_Bar(void)
{
	D2X2B_GPIO_MA_H();
	D2X2B_GPIO_MB_L();
	delay_ms(20);	 
}


























