#include "bsp_S1X4.h"

/// @brief S1X4_GPIO_Init
/// @param  
void S1X4_GPIO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	// PC8
	GPIO_InitStruct.Pin = S1X4_A_GPIO_CTRL_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(S1X4_A_GPIO_CTRL_PORT, &GPIO_InitStruct);
	//PC7
    GPIO_InitStruct.Pin = S1X4_A_GPIO_MA_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;				
	GPIO_InitStruct.Pull = GPIO_PULLUP;								
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(S1X4_A_GPIO_MA_PORT, &GPIO_InitStruct);
	
	//PC6
    GPIO_InitStruct.Pin = S1X4_A_GPIO_MB_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;				
	GPIO_InitStruct.Pull = GPIO_PULLUP;								
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(S1X4_A_GPIO_MB_PORT, &GPIO_InitStruct);

	//PC9
    GPIO_InitStruct.Pin = S1X4_B_GPIO_CTRL_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;				
	GPIO_InitStruct.Pull = GPIO_PULLUP;								
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(S1X4_B_GPIO_CTRL_PORT, &GPIO_InitStruct);
	//PB15
   	GPIO_InitStruct.Pin = S1X4_B_GPIO_MA_PIN;							
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;				
	GPIO_InitStruct.Pull = GPIO_PULLUP;								
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(S1X4_B_GPIO_MA_PORT, &GPIO_InitStruct);
	//PB14
    GPIO_InitStruct.Pin = S1X4_B_GPIO_MB_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;				
	GPIO_InitStruct.Pull = GPIO_PULLUP;								
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(S1X4_B_GPIO_MB_PORT, &GPIO_InitStruct);

    /* 上电默认不在任何状态 */
    S1X4_A_GPIO_CTRL_H();
    S1X4_B_GPIO_CTRL_H();

    S1X4_A_GPIO_MA_H();
    S1X4_A_GPIO_MB_H();

    S1X4_B_GPIO_MA_H();
    S1X4_B_GPIO_MB_H();   
}

/// @brief 重复检测
/// @param time 
/// @param num 
void S1X4_CHENCK(uint16_t time,uint32_t num,uint8_t SwitchType)
{	
	uint8_t a,b,c,d;
	uint32_t success = 0,fail = 0;
    // 轮询切换四种状态
	while(num) {	
		if(Switch == ON){
            if( SwitchType == LATCH)
			{
				a = Latch_S1X4_COMP1(time);
				b = Latch_S1X4_COMP2(time);
				c = Latch_S1X4_COMP3(time);
			    d = Latch_S1X4_COMP4(time);
				if(a||b||c||d){ //有一个切换错误就算失败
					fail++;
				}
				else {
					success++;
				}
			}	
			else if(SwitchType == NONLATCH)
			{
				a = NonLatch_S1X4_COMP1(time);
			    b = NonLatch_S1X4_COMP2(time);
			    c = NonLatch_S1X4_COMP3(time);
			    d = NonLatch_S1X4_COMP4(time);
				if(a||b||c||d){ //有一个切换错误就算失败
					fail++;
				}
				else {
					success++;
				}
			}
			else 
			{
				printf("S1X4 Typedef Error\n");
			}

		}
		else if(Switch == OFF){	
			printf("Latch_S1X4 Switch OFF\n");
			printf("S1X4 Auto Success Num %d ; Fail Num %d \n",success,fail);
			num = 0;
			break;
		}
		if(num++  == 0 ){
			Switch = OFF;
			printf("Test count overflow\n");
			printf("S1X4 Auto Success Num %d ; Fail Num %d \n",success,fail);
			break;
		}
	}   
}

/// @brief A组状态1
/// @param  
void A_GROUP_P1(void)
{
	S1X4_A_GPIO_MA_L(); 	//PIN5 		0
	S1X4_A_GPIO_CTRL_H();	//PIN 10 	1
	S1X4_A_GPIO_MB_H(); 	//PIN6 		1
}
/// @brief A组状态2
/// @param  
void A_GROUP_P2(void)
{
	S1X4_A_GPIO_MA_H();		//PIN5 		1
	S1X4_A_GPIO_CTRL_H();   //PIN 10 	1
	S1X4_A_GPIO_MB_L();     //PIN6 		0
}

/// @brief B组状态1
/// @param  
void B_GROUP_P1(void)
{
	S1X4_B_GPIO_MA_L(); 	//PIN5 		0
	S1X4_B_GPIO_CTRL_H();	//PIN 10 	1
	S1X4_B_GPIO_MB_H(); 	//PIN6 		1
}
/// @brief B组状态2
/// @param  
void B_GROUP_P2(void)
{
	S1X4_B_GPIO_MA_H();		//PIN5 		1
	S1X4_B_GPIO_CTRL_H();   //PIN 10 	1
	S1X4_B_GPIO_MB_L();     //PIN6 		0
}

/// @brief Latch_S1X4_COMP1
/// @param  
uint8_t Latch_S1X4_COMP1(uint16_t time)
{	
	A_GROUP_P2();
	B_GROUP_P2();
	delay_ms(time);
	if(READ_TwoPin(S1X4_A_READ_PIN2_PORT,S1X4_A_READ_PIN2,S1X4_A_READ_PIN9) ||
	   READ_TwoPin(S1X4_B_READ_PORT,S1X4_B_READ_PIN2,S1X4_B_READ_PIN9)){
	    printf("S1X4 COM-P1 Erroe\n");
		return 1;
	}
	else {
	    printf("S1X4 COM-P1 Nermol\n");
		return 0;
	}
  	
}

/// @brief Latch_S1X4_COMP2
/// @param  
uint8_t Latch_S1X4_COMP2(uint16_t time)
{
    //状态B	
	A_GROUP_P1();
	B_GROUP_P2();
	delay_ms(time);
	if(READ_TwoPin(S1X4_A_READ_PIN4_PORT,S1X4_A_READ_PIN4,S1X4_A_READ_PIN7) ||
	   READ_TwoPin(S1X4_B_READ_PORT,S1X4_B_READ_PIN2,S1X4_B_READ_PIN9)){
	   printf("S1X4 COM-P2 Erroe\n");	  
	   return 1;
	}
	else{
	   printf("S1X4 COM-P2 Nermol\n");
	   return 0;
	}
}

/// @brief Latch_S1X4_COMP3
/// @param  
uint8_t Latch_S1X4_COMP3(uint16_t time)
{
    //状态C
	A_GROUP_P2();
	B_GROUP_P1();
    delay_ms(time);
    if(READ_TwoPin(S1X4_A_READ_PIN2_PORT,S1X4_A_READ_PIN2,S1X4_A_READ_PIN9) ||
       READ_TwoPin(S1X4_B_READ_PORT,S1X4_B_READ_PIN4,S1X4_B_READ_PIN7)){
        printf("S1X4 COM-P3 Erroe\n");
		return 1;
	   }
    else{
        printf("S1X4 COM-P3 Nermol\n");
		return 0;
	}
}

/// @brief Latch_S1X4_COMP4
/// @param  
uint8_t Latch_S1X4_COMP4(uint16_t time)
{
    //状态D
	A_GROUP_P1();
	B_GROUP_P1();
    delay_ms(time);
    if(READ_TwoPin(S1X4_A_READ_PIN4_PORT,S1X4_A_READ_PIN4,S1X4_A_READ_PIN7) ||
       READ_TwoPin(S1X4_B_READ_PORT,S1X4_B_READ_PIN4,S1X4_B_READ_PIN7)){
        printf("S1X4 COM-P4 Erroe\n");
		return 1;
	}
    else {
        printf("S1X4 COM-P4 Nermol\n");
		return 0;
	}

}



/*******************************NonLatching******************************************/

/// @brief NonLatch_S1X4_COMP1
/// @param  
uint8_t NonLatch_S1X4_COMP1(uint16_t time)
{
    //状态A
    //A
    S1X4_A_GPIO_CTRL_H();
    //B
    S1X4_B_GPIO_CTRL_H();

    delay_ms(time);
    if(READ_TwoPin(S1X4_A_READ_PIN2_PORT,S1X4_A_READ_PIN2,S1X4_A_READ_PIN9) ||
	   READ_TwoPin(S1X4_B_READ_PORT,S1X4_B_READ_PIN2,S1X4_B_READ_PIN9)){
        printf("Non latch S1X4 COM-P1 Erroe\n");
		return 1;
	}
    else{
        printf("Non latch S1X4 COM-P1 Nermol\n");   
		return 0;
	}
}

/// @brief NonLatch_S1X4_COMP2
/// @param  
uint8_t NonLatch_S1X4_COMP2(uint16_t time)
{
    //状态b
    //A
    S1X4_A_GPIO_CTRL_L();
    //B
    S1X4_B_GPIO_CTRL_H();

    delay_ms(time);
    if(READ_TwoPin(S1X4_A_READ_PIN4_PORT,S1X4_A_READ_PIN4,S1X4_A_READ_PIN7) ||
	   READ_TwoPin(S1X4_B_READ_PORT,S1X4_B_READ_PIN2,S1X4_B_READ_PIN9)){
        printf("Non latch S1X4 COM-P2 Erroe\n");
		return 1;
	}
    else{
        printf("Non latch S1X4 COM-P2 Nermol\n");
		return 0;
	}

}

/// @brief NonLatch_S1X4_COMP3
/// @param  
uint8_t NonLatch_S1X4_COMP3(uint16_t time)
{
    //状态c   
    //A
    S1X4_A_GPIO_CTRL_H();
    //b
    S1X4_B_GPIO_CTRL_L();

    delay_ms(time);
    if(READ_TwoPin(S1X4_A_READ_PIN2_PORT,S1X4_A_READ_PIN2,S1X4_A_READ_PIN9) ||
       READ_TwoPin(S1X4_B_READ_PORT,S1X4_B_READ_PIN4,S1X4_B_READ_PIN7)){
        printf("Non latch S1X4 COM-P3 Erroe\n");
		return 1;
	}
    else{
        printf("Non latch S1X4 COM-P3 Nermol\n");
		return 0;
	}
}

/// @brief NonLatch_S1X4_COMP4
/// @param  
uint8_t NonLatch_S1X4_COMP4(uint16_t time)
{
    //状态D
    //A
    S1X4_A_GPIO_CTRL_L();
    //b
    S1X4_B_GPIO_CTRL_L();

    delay_ms(time);
    if(READ_TwoPin(S1X4_A_READ_PIN4_PORT,S1X4_A_READ_PIN4,S1X4_A_READ_PIN7) ||
       READ_TwoPin(S1X4_B_READ_PORT,S1X4_B_READ_PIN4,S1X4_B_READ_PIN7)){
        printf("Non latch S1X4 COM-P3 Erroe\n");
		return 1;
	}
    else{
        printf("Non latch S1X4 COM-P3 Nermol\n");
		return 0;
	}
}
/*************************************************************************************/

