#include "bsp_MxN.h"

Switch_Status Switch = ON;

/// @brief M1X1_GPIO_Init
/// @param  
void M1X1_GPIO_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStruct;
	M1X1_GPIO_CLK();
	
	GPIO_InitStruct.Pin = M1X1_GPIO_PIN;							
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;				
	GPIO_InitStruct.Pull = GPIO_PULLUP;								
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(M1X1_GPIO_PORT, &GPIO_InitStruct);	

	M1X1_GPIO_L(); //Ä¬ÈÏ×´Ì¬B
}

/// @brief M1X1_CHENCK
/// @param  
void M1X1_CHENCK(uint16_t time,uint32_t num)
{
	while(num--){
	
		if(Switch==ON){
			
			M1X1_GPIO_H();
			delay_ms(20);
			
			if(READ_TwoPin(M1X1_READ_PORT,M1X1_READ_PIN2,M1X1_READ_PIN7)) 
				printf("M1X1_StateA error\n");
			else 
				printf("M1X1_StateA Normal\n");
			
			M1X1_GPIO_L();
			delay_ms(20);
			if(READ_TwoPin(M1X1_READ_PORT,M1X1_READ_PIN4,M1X1_READ_PIN5))
				printf("M1X1_StateB error\n");
			else 
				printf("M1X1_StateB Normal\n");
		}
		else{
		
			printf("C1X2G Switch OFF\n");
			num = 0;
		}
	}

}

void M1X1_StateA(void)
{
	M1X1_GPIO_H();
	delay_ms(20);
	if(READ_TwoPin(M1X1_READ_PORT,M1X1_READ_PIN2,M1X1_READ_PIN7)) 
		printf("M1X1_StateA error\n");
	else 
		printf("M1X1_StateA Normal\n");
}

void M1X1_StateB(void)
{
	M1X1_GPIO_L();
	delay_ms(20);
	if(READ_TwoPin(M1X1_READ_PORT,M1X1_READ_PIN4,M1X1_READ_PIN5))
		printf("M1X1_StateB error\n");
	else 
		printf("M1X1_StateB Normal\n");
}




