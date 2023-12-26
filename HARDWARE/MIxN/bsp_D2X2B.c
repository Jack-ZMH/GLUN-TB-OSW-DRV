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
	
	//ÉÏµçÄ¬ÈÏ
	D2X2B_GPIO_MA_H();
	D2X2B_GPIO_MB_H();
} 


/// @brief ÖØ¸´ÇÐ»»
/// @param time 
/// @param num 
void D2X2B_CHENCK(uint16_t time,uint32_t num)
{	
	uint32_t success = 0;
	uint32_t fail = 0;
	
	uint8_t i = 0 ,j = 0;
	while(num) 
	{	
		if(Switch == ON)
		{
			i = D2X2B_State_Cross(time);
			j = D2X2B_State_Bar(time);
			if( i || j )
				fail++;
			else 
				success++;
		}
		else if(Switch == OFF)
		{
			num = 0;
			printf("C1X2G Switch OFF\n");
			printf("C1X2G Auto Success Num %d ; Fail Num %d \n",success,fail);
			break;
		}
		if(num++  == 0 ){
			Switch = OFF;
			printf("Test count overflow,Text Stop\n");
			printf("C1X2G Auto Success Num %d ; Fail Num %d \n",success,fail);	
			break;
		}
	}   
}

/// @brief ÇÐ»»ÎªCross×´Ì¬
/// @param  
uint8_t D2X2B_State_Cross(uint16_t time)
{
	D2X2B_GPIO_MA_L();
	D2X2B_GPIO_MB_H();
	delay_ms(time);
	if(READ_TwoPin(IP0_CMD,D2X2B_READ_MA_PIN5,D2X2B_READ_MB_PIN8)){
		printf("D2X2B_Cross Error\n");
		return 1;
	}	
	else{	
		printf("D2X2B_Cross Normel\n");
		return 0;
	}			
}

/// @brief ÇÐ»»ÎªBar×´Ì¬
/// @param  
uint8_t D2X2B_State_Bar(uint16_t time)
{
	D2X2B_GPIO_MA_H();
	D2X2B_GPIO_MB_L();
	delay_ms(time);
	if(PCA_GPIO_ReadPin(D2X2B_READ_PIN3_PORT,D2X2B_READ_MA_PIN3)||
	   PCA_GPIO_ReadPin(D2X2B_READ_PIN10_PORT,D2X2B_READ_MB_PIN10)){
		printf("D2X2B_Bar Error\n");
		return 1;
	   }
	else{	
		printf("D2X2B_Bar Normel\n");	
		return 0;
	}
}


























