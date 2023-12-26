#include "bsp_MxN.h"

uint8_t Switch = OFF;

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

	M1X1_GPIO_H(); //Ä¬ÈÏ×´Ì¬A
}

/// @brief M1X1_CHENCK
/// @param  
void M1X1_CHENCK(uint16_t time,uint32_t num)
{
	uint32_t success = 0;
	uint32_t fail = 0;
	
	uint8_t i = 0,j = 0;
	while(num){
		if(Switch==ON){
			i = M1X1_StateA(time);
			j = M1X1_StateB(time);
			if(i||j)
				fail++;
			else
				success++;
		}
		else if(Switch==OFF){
			printf("C1X2G Switch OFF\n");
			printf("M1X1 Auto Success Num %d ; Fail Num %d \n",success,fail);
			num = 0;
			break;
		}
		if(num++ == 0){
			Switch = OFF;
			printf("Test count overflow\n");
			printf("M1X1 Auto Success Num %d ; Fail Num %d \n",success,fail);
			break;
		}
	}

}

/// @brief M1X1_StateA
/// @param time 
/// @return 
uint8_t M1X1_StateA(uint16_t time)
{
	M1X1_GPIO_H();
	delay_ms(time);
	if(READ_TwoPin(M1X1_READ_PORT,M1X1_READ_PIN4,M1X1_READ_PIN5)){
		printf("M1X1_StateA error\n");
		return 1;
	}
	else{ 
		printf("M1X1_StateA Normal\n");
		return 0;
	}
}

/// @brief M1X1_StateB
/// @param time 
/// @return 
uint8_t M1X1_StateB(uint16_t time)
{
	M1X1_GPIO_L();
	delay_ms(time);
	if(READ_TwoPin(M1X1_READ_PORT,M1X1_READ_PIN2,M1X1_READ_PIN7)){
		printf("M1X1_StateB error\n");
		return 1;
	}
	else{ 
		printf("M1X1_StateB Normal\n");
		return 0;
	}
}




