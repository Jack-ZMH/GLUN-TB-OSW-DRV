#include "bsp_C1X2G.h"


/// @brief C1X2G_GPIO_Init
/// @param  
void C1X2G_GPIO_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStruct;
	C1X2G_GPIO_CTRL_CLK();
    C1X2G_GPIO_MA_CLK();
    C1X2G_GPIO_MB_CLK();
	
	GPIO_InitStruct.Pin = C1X2G_GPIO_CTRL_PIN;							
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;				
	GPIO_InitStruct.Pull = GPIO_PULLUP;								
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(C1X2G_GPIO_CTRL_PORT, &GPIO_InitStruct);	

    GPIO_InitStruct.Pin = C1X2G_GPIO_MA_PIN;
    HAL_GPIO_Init(C1X2G_GPIO_CTRL_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = C1X2G_GPIO_MB_PIN;
    HAL_GPIO_Init(C1X2G_GPIO_CTRL_PORT, &GPIO_InitStruct);  

	//上电默认状态A
    C1X2G_GPIO_CTRL_H();    
    C1X2G_GPIO_MA_L();
    C1X2G_GPIO_MB_L();
} 


/// @brief 重复切换
/// @param time 
/// @param num 
void C1X2G_CHENCK(uint16_t time,uint32_t num,uint8_t SwitchType)
{	
	uint32_t success = 0;
	uint32_t fail = 0;
	
	uint8_t i,j;
	while(num) 
	{	
		if(Switch == ON)
		{
			if(SwitchType == LATCH){
				
				i=Latch_C1X2_StateA(time);
				j=Latch_C1X2_StateB(time);
				//printf("C1X2G Current:%0.2f\n",(float)((Get_Adc_Average(ADC_CHANNEL_5,50)-100)*12)*0.02*50*120);
				if( i || j )
					success++;
				else 
					fail++;	
			}
			else if(SwitchType == NONLATCH)
			{
				NonLatch_C1X2_StateA(time);
				NonLatch_C1X2_StateA(time);
			}
		}
		else if(Switch == OFF)
		{
			printf("C1X2G Switch:OFF\n");
			printf("Success Num %d ; Fail Num %d \n",success,fail);
			num = 0;
			break;
		}
		if(num++  == 0 ){
			Switch = OFF;
			printf("Test count overflow\n");
			printf("Success Num %d ; Fail Num %d \n",success,fail);
			break;
		}
	}   
}


/// @brief C1X2_SateA
/// @param  
uint8_t Latch_C1X2_StateA(uint16_t time)
{

	// 0 0 0 1
	C1X2G_GPIO_MA_H();//PIN5
	C1X2G_GPIO_CTRL_H();//PIN6
	C1X2G_GPIO_MB_L();//PIN10
	delay_ms(time);
	if(READ_TwoPin(C1X2G_READ_PORT,C1X2G_READ_MA_PIN2,C1X2G_READ_MB_PIN9))
	{
		printf("Latch_C1X2G_MA Error\n");
		return 0;
	}		
	else
	{		
		printf("Latch_C1X2G_MA Normel\n");
		return 1;
	}
}


/// @brief C1X2_SateB
/// @param  
uint8_t Latch_C1X2_StateB(uint16_t time)
{
	// 1 0 0 0
	C1X2G_GPIO_MA_L(); //PIN5
	C1X2G_GPIO_CTRL_H(); //PIN6
	C1X2G_GPIO_MB_H(); //PIN10
	delay_ms(time);
	if(READ_TwoPin(C1X2G_READ_PORT,C1X2G_READ_MA_PIN4,C1X2G_READ_MB_PIN7))
	{
		printf("Latch_C1X2G_MB Error\n");
		return 0;
	}		
	else 
	{
		printf("Latch_C1X2G_MB Normel\n");
		return 1;
	}
}

/// @brief NonLatch_C1X2_StateA
/// @param  
uint8_t NonLatch_C1X2_StateA(uint16_t time)
{
	C1X2G_GPIO_CTRL_H();
	delay_ms(time);
	if(READ_TwoPin(C1X2G_READ_PORT,C1X2G_READ_MA_PIN4,C1X2G_READ_MB_PIN7)){
		printf("NonLatch_C1X2G_MB Error\n");
		return 1;
	}
	else{ 
		printf("NonLatch_C1X2G_MB Normel\n");
		return 0;
	}
}

/// @brief NonLatch_C1X2_StateB
/// @param  
uint8_t NonLatch_C1X2_StateB(uint16_t time)
{
	C1X2G_GPIO_CTRL_L();
	delay_ms(time);
	if(READ_TwoPin(C1X2G_READ_PORT,C1X2G_READ_MA_PIN2,C1X2G_READ_MB_PIN9)){
		printf("NonLatch_C1X2G_MA Error\n");
		return 1;
	}
	else{ 
		printf("NonLatch_C1X2G_MA Normel\n");
		return 0;
	}
}



