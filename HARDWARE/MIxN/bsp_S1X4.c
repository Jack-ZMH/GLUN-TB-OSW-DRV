#include "bsp_S1X4.h"

void S1X4_GPIO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = S1X4_A_GPIO_CTRL_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(S1X4_A_GPIO_CTRL_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = S1X4_A_GPIO_MA_PIN;
    HAL_GPIO_Init(S1X4_A_GPIO_MA_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = S1X4_A_GPIO_MB_PIN;
    HAL_GPIO_Init(S1X4_A_GPIO_MB_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = S1X4_B_GPIO_CTRL_PIN;
    HAL_GPIO_Init(S1X4_B_GPIO_CTRL_PORT, &GPIO_InitStruct);

   	GPIO_InitStruct.Pin = S1X4_B_GPIO_MA_PIN;							
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;				
	GPIO_InitStruct.Pull = GPIO_PULLUP;								
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(S1X4_B_GPIO_MA_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = S1X4_B_GPIO_MB_PIN;
    HAL_GPIO_Init(S1X4_B_GPIO_MB_PORT, &GPIO_InitStruct);

    /* 上电默认不在任何状态 */
    S1X4_A_GPIO_CTRL_L();
    S1X4_B_GPIO_CTRL_L();

    S1X4_A_GPIO_MA_L();
    S1X4_A_GPIO_MB_H();

    S1X4_B_GPIO_MA_L();
    S1X4_B_GPIO_MB_H();   
}

/// @brief 重复检测
/// @param time 
/// @param num 
void S1X4_CHENCK(uint16_t time,uint32_t num,LockTypedef SwitchType)
{	
    // 轮询切换四种状态
	while(num--) {	
		if(Switch){
            if( SwitchType == lock)
			{
				Latch_S1X4_COMP1(time);
				Latch_S1X4_COMP2(time);
				Latch_S1X4_COMP3(time);
			    Latch_S1X4_COMP4(time);
			}
			else if(SwitchType == nolock)
			{
				NonLatch_S1X4_COMP1(time);
			    NonLatch_S1X4_COMP2(time);
			    NonLatch_S1X4_COMP3(time);
			    NonLatch_S1X4_COMP4(time);
			}
			else 
			{
				printf("S1X4 Typedef Error\n");
			}

		}
		else {	
			printf("Latch_S1X4 Switch:%d",Switch);
			num = 0;
		}
	}   
}

/// @brief Latch_S1X4_COMP1
/// @param  
void Latch_S1X4_COMP1(uint16_t time)
{
    //状态A
    //A
    S1X4_A_GPIO_MA_H();
    S1X4_A_GPIO_MB_L();
    S1X4_A_GPIO_CTRL_H();
    //B
    S1X4_B_GPIO_MA_H();
    S1X4_B_GPIO_MB_L();
    S1X4_B_GPIO_CTRL_H();
    delay_ms(time);
    if(READ_TwoPin(S1X4_A_READ_PORT1,S1X4_A_READ_PIN4,S1X4_A_READ_PIN7) ||
       READ_TwoPin(S1X4_B_READ_PORT,S1X4_B_READ_PIN4,S1X4_B_READ_PIN7))
       printf("S1X4 COM-P1 Erroe\n");
    else
        printf("S1X4 COM-P1 Nermol\n");   
}

/// @brief Latch_S1X4_COMP2
/// @param  
void Latch_S1X4_COMP2(uint16_t time)
{
    //状态B
    //A
    S1X4_A_GPIO_MA_L();
    S1X4_A_GPIO_MB_L();
    S1X4_A_GPIO_CTRL_L();
    //B
    S1X4_B_GPIO_MA_H();
    S1X4_B_GPIO_MB_L();
    S1X4_B_GPIO_CTRL_H();
     delay_ms(time);
    if(READ_TwoPin(S1X4_A_READ_PORT2,S1X4_A_READ_PIN2,S1X4_A_READ_PIN9) || 
       READ_TwoPin(S1X4_B_READ_PORT,S1X4_B_READ_PIN4,S1X4_B_READ_PIN7))
        printf("S1X4 COM-P2 Erroe\n");
    else
        printf("S1X4 COM-P2 Nermol\n");   
}

/// @brief Latch_S1X4_COMP3
/// @param  
void Latch_S1X4_COMP3(uint16_t time)
{
    //状态C
    //A
    S1X4_A_GPIO_MA_H();
    S1X4_A_GPIO_MB_L();
    S1X4_A_GPIO_CTRL_H();
    //B
    S1X4_B_GPIO_MA_L();
    S1X4_B_GPIO_MB_L();
    S1X4_B_GPIO_CTRL_L();
    delay_ms(time);
    if(READ_TwoPin(S1X4_A_READ_PORT1,S1X4_A_READ_PIN4,S1X4_A_READ_PIN7) ||
       READ_TwoPin(S1X4_B_READ_PORT,S1X4_B_READ_PIN2,S1X4_B_READ_PIN9))
        printf("S1X4 COM-P3 Erroe\n");
    else
        printf("S1X4 COM-P3 Nermol\n");
}

/// @brief Latch_S1X4_COMP4
/// @param  
void Latch_S1X4_COMP4(uint16_t time)
{
    //状态D
    //A
    S1X4_A_GPIO_MA_L();
    S1X4_A_GPIO_MB_L();
    S1X4_A_GPIO_CTRL_L();
    //b
    S1X4_B_GPIO_MA_L();
    S1X4_B_GPIO_MB_L();
    S1X4_B_GPIO_CTRL_L();
     delay_ms(time);
    if(READ_TwoPin(S1X4_A_READ_PORT2,S1X4_A_READ_PIN2,S1X4_A_READ_PIN9) ||
       READ_TwoPin(S1X4_B_READ_PORT,S1X4_B_READ_PIN2,S1X4_B_READ_PIN9))
        printf("S1X4 COM-P4 Erroe\n");
    else
        printf("S1X4 COM-P4 Nermol\n");

}



/// @brief NonLatch_S1X4_COMP1
/// @param  
void NonLatch_S1X4_COMP1(uint16_t time)
{
    //状态A
    //A
    S1X4_A_GPIO_CTRL_H();
    //B
    S1X4_B_GPIO_CTRL_H();

    delay_ms(time);
    if(READ_TwoPin(S1X4_A_READ_PORT1,S1X4_A_READ_PIN4,S1X4_A_READ_PIN7) ||
       READ_TwoPin(S1X4_B_READ_PORT,S1X4_B_READ_PIN4,S1X4_B_READ_PIN7))
        printf("Non latch S1X4 COM-P1 Erroe\n");
    else
        printf("Non latch S1X4 COM-P1 Nermol\n");   

}

/// @brief NonLatch_S1X4_COMP2
/// @param  
void NonLatch_S1X4_COMP2(uint16_t time)
{
    //状态b
    //A
    S1X4_A_GPIO_CTRL_L();
    //B
    S1X4_B_GPIO_CTRL_H();

    delay_ms(time);
    if(READ_TwoPin(S1X4_A_READ_PORT2,S1X4_A_READ_PIN2,S1X4_A_READ_PIN9) ||
       READ_TwoPin(S1X4_B_READ_PORT,S1X4_B_READ_PIN4,S1X4_B_READ_PIN7))
        printf("Non latch S1X4 COM-P2 Erroe\n");
    else
        printf("Non latch S1X4 COM-P2 Nermol\n");

}

/// @brief NonLatch_S1X4_COMP3
/// @param  
void NonLatch_S1X4_COMP3(uint16_t time)
{
    //状态c   
    //A
    S1X4_A_GPIO_CTRL_H();
    //b
    S1X4_B_GPIO_CTRL_L();

    delay_ms(time);
    if(READ_TwoPin(S1X4_A_READ_PORT1,S1X4_A_READ_PIN4,S1X4_A_READ_PIN7) ||
       READ_TwoPin(S1X4_B_READ_PORT,S1X4_B_READ_PIN2,S1X4_B_READ_PIN9))
        printf("Non latch S1X4 COM-P3 Erroe\n");
    else
        printf("Non latch S1X4 COM-P3 Nermol\n");

}

/// @brief NonLatch_S1X4_COMP4
/// @param  
void NonLatch_S1X4_COMP4(uint16_t time)
{
    //状态D
    //A
    S1X4_A_GPIO_CTRL_L();
    //b
    S1X4_B_GPIO_CTRL_L();

    delay_ms(time);
    if(READ_TwoPin(S1X4_A_READ_PORT2,S1X4_A_READ_PIN2,S1X4_A_READ_PIN9) ||
       READ_TwoPin(S1X4_B_READ_PORT,S1X4_B_READ_PIN2,S1X4_B_READ_PIN9))
        printf("Non latch S1X4 COM-P3 Erroe\n");
    else
        printf("Non latch S1X4 COM-P3 Nermol\n");

}

