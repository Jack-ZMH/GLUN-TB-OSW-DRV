#include "bsp_S1X8.h"

/// @brief S1X8_GPIO_Init
/// @param  
void S1X8_GPIO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
    //A
	GPIO_InitStruct.Pin = S1X8_A_GPIO_CTRL_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(S1X8_A_GPIO_CTRL_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = S1X8_A_GPIO_MA_PIN;
    HAL_GPIO_Init(S1X8_A_GPIO_MA_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = S1X8_A_GPIO_MB_PIN;
    HAL_GPIO_Init(S1X8_A_GPIO_MB_PORT, &GPIO_InitStruct);
    //B
    GPIO_InitStruct.Pin = S1X8_B_GPIO_CTRL_PIN;
    HAL_GPIO_Init(S1X8_B_GPIO_CTRL_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = S1X8_B_GPIO_MA_PIN;
    HAL_GPIO_Init(S1X8_B_GPIO_MA_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = S1X8_B_GPIO_MB_PIN;
    HAL_GPIO_Init(S1X8_B_GPIO_MB_PORT, &GPIO_InitStruct);
    //C
    GPIO_InitStruct.Pin = S1X8_C_GPIO_CTRL_PIN;
    HAL_GPIO_Init(S1X8_C_GPIO_CTRL_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = S1X8_C_GPIO_MA_PIN;
    HAL_GPIO_Init(S1X8_C_GPIO_MA_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = S1X8_C_GPIO_MB_PIN;
    HAL_GPIO_Init(S1X8_C_GPIO_MB_PORT, &GPIO_InitStruct);

    //默认状态A
    S1X8_A_GPIO_CTRL_H();
    S1X8_A_GPIO_MB_H();
    S1X8_A_GPIO_MA_H();
    S1X8_B_GPIO_CTRL_H();
    S1X8_B_GPIO_MB_H();
    S1X8_B_GPIO_MA_H();
    S1X8_C_GPIO_CTRL_H();
    S1X8_C_GPIO_MB_H();
    S1X8_C_GPIO_MA_H();
}

/// @brief Latch_S1X8_CHENCH
/// @param time 
/// @param num 
void Latch_S1X8_CHENCH(uint16_t time,uint32_t num,uint8_t SwitchType)
{
    uint8_t a,b,c,d,e,f,g,h;
	uint32_t success = 0,fail = 0;
    while (num)
    {
        /* code */
        if(Switch == ON)
        {   
			if(SwitchType == LATCH)
			{	
				a = Latch_S1X8_COM_P1(time);
				b = Latch_S1X8_COM_P2(time);
				c = Latch_S1X8_COM_P3(time);
				d = Latch_S1X8_COM_P4(time);
				e = Latch_S1X8_COM_P5(time);
				f = Latch_S1X8_COM_P6(time);
				g = Latch_S1X8_COM_P7(time);
				h = Latch_S1X8_COM_P8(time);
                if(a||b||c||d||e||f||g||h)
                    fail++;
                else 
                    success++;
			}
			else if(SwitchType == NONLATCH)
			{
				a = NonLatch_S1X8_COM_P1(time);
			    b = NonLatch_S1X8_COM_P2(time);
			    c = NonLatch_S1X8_COM_P3(time);
			    d = NonLatch_S1X8_COM_P4(time);
			    e = NonLatch_S1X8_COM_P5(time);
			    f = NonLatch_S1X8_COM_P6(time);
			    g = NonLatch_S1X8_COM_P7(time);
				h = NonLatch_S1X8_COM_P8(time);
                if(a||b||c||d||e||f||g||h)
                    fail++;
                else 
                    success++;
			} 
			else 
			{
				printf("S1X8 Typedef Error\n");
			}
        }
        else if(Switch == OFF)
        {
            num=0;
            printf("Latching S1X8 Switch OFF\n");
            printf("S1X8 Auto Success Num %d ; Fail Num %d \n",success,fail);
            break;
        } 
		if(num++  == 0 ){
			Switch = OFF;
            printf("Test count overflow\n");
			printf("S1X8 Auto Success Num %d ; Fail Num %d \n",success,fail);
			break;
		}
    }
}

/// @brief A组状态1
/// @param  
void S1X8_A_GROUP_P1(void)
{
	S1X8_A_GPIO_MA_L(); 	//PIN5 		0
	S1X8_A_GPIO_CTRL_H();	//PIN 10 	1
	S1X8_A_GPIO_MB_H(); 	//PIN6 		1
}
/// @brief A组状态2
/// @param  
void S1X8_A_GROUP_P2(void)
{
	S1X8_A_GPIO_MA_H();		//PIN5 		1
	S1X8_A_GPIO_CTRL_H();   //PIN 10 	1
	S1X8_A_GPIO_MB_L();     //PIN6 		0
}

/// @brief B组状态1
/// @param  
void S1X8_B_GROUP_P1(void)
{
	S1X8_B_GPIO_MA_L(); 	//PIN5 		0
	S1X8_B_GPIO_CTRL_H();	//PIN 10 	1
	S1X8_B_GPIO_MB_H(); 	//PIN6 		1
}
/// @brief B组状态2
/// @param  
void S1X8_B_GROUP_P2(void)
{
	S1X8_B_GPIO_MA_H();		//PIN5 		1
	S1X8_B_GPIO_CTRL_H();   //PIN 10 	1
	S1X8_B_GPIO_MB_L();     //PIN6 		0
}

/// @brief B组状态1
/// @param  
void S1X8_C_GROUP_P1(void)
{
	S1X8_C_GPIO_MA_L(); 	//PIN5 		0
	S1X8_C_GPIO_CTRL_H();	//PIN 10 	1
	S1X8_C_GPIO_MB_H(); 	//PIN6 		1
}
/// @brief B组状态2
/// @param  
void S1X8_C_GROUP_P2(void)
{
	S1X8_C_GPIO_MA_H();		//PIN5 		1
	S1X8_C_GPIO_CTRL_H();   //PIN 10 	1
	S1X8_C_GPIO_MB_L();     //PIN6 		0
}

uint8_t Latch_S1X8_COM_P1(uint16_t time)
{
    //COM-P1
	S1X8_A_GROUP_P2();
	S1X8_B_GROUP_P2();
	S1X8_C_GROUP_P1();
    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN2_PORT,S1X8_A_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN9_PORT,S1X8_A_READ_PIN9) ||
        READ_TwoPin(IP4_CMD,S1X8_B_READ_PIN2,S1X8_B_READ_PIN9)   ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN4_PORT,S1X8_C_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN7_PORT,S1X8_C_READ_PIN7))
    {
        /* code */
        printf("Latching S1X8 COM-P1 Error\n");
		return 1;
    }
    else
    {
        printf("Latching S1X8 COM-P1 Nermol\n");
		return 0;
    }


}
uint8_t Latch_S1X8_COM_P2(uint16_t time)
{
    //COM-P2
	S1X8_A_GROUP_P1();
	S1X8_B_GROUP_P2();
	S1X8_C_GROUP_P1();
    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN4_PORT,S1X8_A_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN7_PORT,S1X8_A_READ_PIN7) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN4_PORT,S1X8_C_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN7_PORT,S1X8_C_READ_PIN7) ||
        READ_TwoPin(IP4_CMD,S1X8_B_READ_PIN2,S1X8_B_READ_PIN9))
    {
        /* code */
        printf("Latching S1X8 COM-P2 Error\n");
		return 1;
    }
    else
    {
        printf("Latching S1X8 COM-P2 Nermol\n");
		return 0;
    }
}
uint8_t Latch_S1X8_COM_P3(uint16_t time)
{
    //COM-P3
    //A
    S1X8_A_GROUP_P2();
	S1X8_B_GROUP_P1();
	S1X8_C_GROUP_P1();
    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN2_PORT,S1X8_A_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN9_PORT,S1X8_A_READ_PIN9) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN4_PORT,S1X8_C_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN7_PORT,S1X8_C_READ_PIN7) ||
        READ_TwoPin(IP4_CMD,S1X8_B_READ_PIN4,S1X8_B_READ_PIN7))
    {
        /* code */
        printf("Latching S1X8 COM-P3 Error\n");
		return 1;
    }
    else
    {
        printf("Latching S1X8 COM-P3 Nermol\n");
		return 0;
    }
}
uint8_t Latch_S1X8_COM_P4(uint16_t time)
{
    //COM-P4
    //A
    S1X8_A_GROUP_P1();
	S1X8_B_GROUP_P1();
	S1X8_C_GROUP_P1();
    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN4_PORT,S1X8_A_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN7_PORT,S1X8_A_READ_PIN7) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN4_PORT,S1X8_C_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN7_PORT,S1X8_C_READ_PIN7) ||
        READ_TwoPin(IP4_CMD,S1X8_B_READ_PIN4,S1X8_B_READ_PIN7))
    {
        /* code */
        printf("Latching S1X8 COM-P4 Error\n");
		return 1;
    }
    else
    {
        printf("Latching S1X8 COM-P4 Nermol\n");
		return 0;
    }

}
uint8_t Latch_S1X8_COM_P5(uint16_t time)
{
    //COM-P5
    S1X8_A_GROUP_P2();
	S1X8_B_GROUP_P2();
	S1X8_C_GROUP_P2();
    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN2_PORT,S1X8_A_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN9_PORT,S1X8_A_READ_PIN9) ||
		PCA_GPIO_ReadPin(S1X8_C_READ_PIN2_PORT,S1X8_C_READ_PIN2) ||
	    PCA_GPIO_ReadPin(S1X8_C_READ_PIN9_PORT,S1X8_C_READ_PIN9) ||
		READ_TwoPin(IP4_CMD,S1X8_B_READ_PIN2,S1X8_B_READ_PIN9))
	{
		printf("Latching S1X8 COM-P5 Error\n");
		return 1;
	}
    else
    {
        printf("Latching S1X8 COM-P5 Nermol\n");
		return 0;
    }

}
uint8_t Latch_S1X8_COM_P6(uint16_t time)
{
    //COM-P6
    S1X8_A_GROUP_P1();
	S1X8_B_GROUP_P2();
	S1X8_C_GROUP_P2();
    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN4_PORT,S1X8_A_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN7_PORT,S1X8_A_READ_PIN7) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN2_PORT,S1X8_C_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN9_PORT,S1X8_C_READ_PIN9) ||
        READ_TwoPin(IP4_CMD,S1X8_B_READ_PIN2,S1X8_B_READ_PIN9))
    {
        /* code */
        printf("Latching S1X8 COM-P6 Error\n");
		return 1;
    }
    else
    {
        printf("Latching S1X8 COM-P6 Nermol\n");
		return 0;
    }
}
uint8_t Latch_S1X8_COM_P7(uint16_t time)
{
    //COM-P7
    S1X8_A_GROUP_P2();
	S1X8_B_GROUP_P1();
	S1X8_C_GROUP_P2();
    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN2_PORT,S1X8_A_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN9_PORT,S1X8_A_READ_PIN9) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN2_PORT,S1X8_C_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN9_PORT,S1X8_C_READ_PIN9) ||
        READ_TwoPin(IP4_CMD,S1X8_B_READ_PIN4,S1X8_B_READ_PIN7))
    {
        /* code */
        printf("Latching S1X8 COM-P7 Error\n");
		return 1;
    }
    else
    {
        printf("Latching S1X8 COM-P7 Nermol\n");
		return 0;
    }

}
uint8_t Latch_S1X8_COM_P8(uint16_t time)
{
    //COM-P8
    S1X8_A_GROUP_P1();
	S1X8_B_GROUP_P1();
	S1X8_C_GROUP_P2();
    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN4_PORT,S1X8_A_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN7_PORT,S1X8_A_READ_PIN7) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN2_PORT,S1X8_C_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN9_PORT,S1X8_C_READ_PIN9) ||
        READ_TwoPin(IP4_CMD,S1X8_B_READ_PIN4,S1X8_B_READ_PIN7))
    {
        /* code */
        printf("Latching S1X8 COM-P8 Error\n");
		return 1;
    }
    else
    {
        printf("Latching S1X8 COM-P8 Nermol\n");
		return 0;
    }

}

/****************************************NonLatching*********************************************************/



uint8_t NonLatch_S1X8_COM_P1(uint16_t time)
{
    //A
    S1X8_A_GPIO_CTRL_H();
    //B
    S1X8_B_GPIO_CTRL_H();
    //C
    S1X8_C_GPIO_CTRL_L();

    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN2_PORT,S1X8_A_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN9_PORT,S1X8_A_READ_PIN9) ||
        READ_TwoPin(IP4_CMD,S1X8_B_READ_PIN2,S1X8_B_READ_PIN9)   ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN4_PORT,S1X8_C_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN7_PORT,S1X8_C_READ_PIN7))
    {
        /* code */
        printf("NonLatching S1X8 COM-P1 Error\n");
		return 1;
    }
    else
    {
        printf("NonLatching S1X8 COM-P1 Nermol\n");
		return 0;
    }
}
uint8_t NonLatch_S1X8_COM_P2(uint16_t time)
{
    //COM-P2
    //A
    S1X8_A_GPIO_CTRL_L();
    //B
    S1X8_B_GPIO_CTRL_H();
    //C
    S1X8_C_GPIO_CTRL_L();
    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN4_PORT,S1X8_A_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN7_PORT,S1X8_A_READ_PIN7) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN4_PORT,S1X8_C_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN7_PORT,S1X8_C_READ_PIN7) ||
        READ_TwoPin(IP4_CMD,S1X8_B_READ_PIN2,S1X8_B_READ_PIN9))
    {
        /* code */
        printf("NonLatching S1X8 COM-P2 Error\n");
		return 1;
    }
    else
    {
        printf("NonLatching S1X8 COM-P2 Nermol\n");
		return 0;
    }

}
uint8_t NonLatch_S1X8_COM_P3(uint16_t time)
{
    //COM-P3
    //A
    S1X8_A_GPIO_CTRL_H();
    //B
    S1X8_B_GPIO_CTRL_L();
    //C
    S1X8_C_GPIO_CTRL_L();
    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN2_PORT,S1X8_A_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN9_PORT,S1X8_A_READ_PIN9) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN4_PORT,S1X8_C_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN7_PORT,S1X8_C_READ_PIN7) ||
        READ_TwoPin(IP4_CMD,S1X8_B_READ_PIN4,S1X8_B_READ_PIN7))
    {
        /* code */
        printf("NonLatching S1X8 COM-P3 Error\n");
		return 1;
    }
    else
    {
        printf("NonLatching S1X8 COM-P3 Nermol\n");
		return 0;
    }

}
uint8_t NonLatch_S1X8_COM_P4(uint16_t time)
{
    //COM-P4
    //A
    S1X8_A_GPIO_CTRL_L();
    //B
    S1X8_B_GPIO_CTRL_L();
    //C
    S1X8_C_GPIO_CTRL_L();

    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN4_PORT,S1X8_A_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN7_PORT,S1X8_A_READ_PIN7) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN4_PORT,S1X8_C_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN7_PORT,S1X8_C_READ_PIN7) ||
        READ_TwoPin(IP4_CMD,S1X8_B_READ_PIN4,S1X8_B_READ_PIN7))
    {
        /* code */
        printf("NonLatching S1X8 COM-P4 Error\n");
		return 1;
    }
    else
    {
        printf("NonLatching S1X8 COM-P4 Nermol\n");
		return 0;
    }

}
uint8_t NonLatch_S1X8_COM_P5(uint16_t time)
{
    //COM-P5
    //A
    S1X8_A_GPIO_CTRL_H();
    //B
    S1X8_B_GPIO_CTRL_H();
    //c
    S1X8_C_GPIO_CTRL_H();

    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN2_PORT,S1X8_A_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN9_PORT,S1X8_A_READ_PIN9) ||
		PCA_GPIO_ReadPin(S1X8_C_READ_PIN2_PORT,S1X8_C_READ_PIN2) ||
	    PCA_GPIO_ReadPin(S1X8_C_READ_PIN9_PORT,S1X8_C_READ_PIN9) ||
		READ_TwoPin(IP4_CMD,S1X8_B_READ_PIN2,S1X8_B_READ_PIN9))
	{
		printf("NonLatching S1X8 COM-P5 Error\n");
		return 1;
	}
    else
    {
        printf("NonLatching S1X8 COM-P5 Nermol\n");
		return 0;
    }

}
uint8_t NonLatch_S1X8_COM_P6(uint16_t time)
{
    //COM-P6
    //A
    S1X8_A_GPIO_CTRL_L();
    //B
    S1X8_B_GPIO_CTRL_H();
    //c
    S1X8_C_GPIO_CTRL_H();

    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN4_PORT,S1X8_A_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN7_PORT,S1X8_A_READ_PIN7) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN2_PORT,S1X8_C_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN9_PORT,S1X8_C_READ_PIN9) ||
        READ_TwoPin(IP4_CMD,S1X8_B_READ_PIN2,S1X8_B_READ_PIN9))
    {
        /* code */
        printf("NonLatching S1X8 COM-P6 Error\n");
		return 1;
    }
    else
    {
        printf("NonLatching S1X8 COM-P6 Nermol\n");
		return 0;
    }

}
uint8_t NonLatch_S1X8_COM_P7(uint16_t time)
{
    //COM-P7
    //A
    S1X8_A_GPIO_CTRL_H();
    //B
    S1X8_B_GPIO_CTRL_L();
    //c
    S1X8_C_GPIO_CTRL_H();

    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN2_PORT,S1X8_A_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN9_PORT,S1X8_A_READ_PIN9) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN2_PORT,S1X8_C_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN9_PORT,S1X8_C_READ_PIN9) ||
        READ_TwoPin(IP4_CMD,S1X8_B_READ_PIN4,S1X8_B_READ_PIN7))
    {
        /* code */
        printf("NonLatching S1X8 COM-P7 Error\n");
		return 1;
    }
    else
    {
        printf("NonLatching S1X8 COM-P7 Nermol\n");
		return 0;
    }

}
uint8_t NonLatch_S1X8_COM_P8(uint16_t time)
{
    //COM-P8
    //A
    S1X8_A_GPIO_CTRL_L();
    //B
    S1X8_B_GPIO_CTRL_L();
    //C
    S1X8_C_GPIO_CTRL_H();

    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN4_PORT,S1X8_A_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN7_PORT,S1X8_A_READ_PIN7) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN2_PORT,S1X8_C_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN9_PORT,S1X8_C_READ_PIN9) ||
        READ_TwoPin(IP4_CMD,S1X8_B_READ_PIN4,S1X8_B_READ_PIN7))
    {
        /* code */
        printf("NonLatching S1X8 COM-P8 Error\n");
		return 1;
    }
    else
    {
        printf("NonLatching S1X8 COM-P8 Nermol\n");
		return 0;
    }

}
