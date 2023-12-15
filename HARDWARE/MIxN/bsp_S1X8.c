#include "bsp_S1X8.h"


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
    S1X8_A_GPIO_MB_L();
    S1X8_A_GPIO_MA_H();
    S1X8_B_GPIO_CTRL_H();
    S1X8_B_GPIO_MB_L();
    S1X8_B_GPIO_MA_H();
    S1X8_C_GPIO_CTRL_L();
    S1X8_C_GPIO_MB_L();
    S1X8_C_GPIO_MA_L();

}

/// @brief Latch_S1X8_CHENCH
/// @param time 
/// @param num 
void Latch_S1X8_CHENCH(uint16_t time,uint32_t num)
{
    while (num--)
    {
        /* code */
        if(Switch)
        {           
            Latch_S1X8_COM_P1(time);
            Latch_S1X8_COM_P2(time);
            Latch_S1X8_COM_P3(time);
            Latch_S1X8_COM_P4(time);
            Latch_S1X8_COM_P5(time);
            Latch_S1X8_COM_P6(time);
            Latch_S1X8_COM_P7(time);
            Latch_S1X8_COM_P8(time);
        }
        else
        {
            printf("Latching S1X8 Switch:%d",Switch);
            num=0;
        } 
    }
}
void Latch_S1X8_COM_P1(uint16_t time)
{
    //COM-P1
    //A
    S1X8_A_GPIO_CTRL_H();
    S1X8_A_GPIO_MB_L();
    S1X8_A_GPIO_MA_H();
    //B
    S1X8_B_GPIO_CTRL_H();
    S1X8_B_GPIO_MB_L();
    S1X8_B_GPIO_MA_H();
    //C
    S1X8_C_GPIO_CTRL_L();
    S1X8_C_GPIO_MB_L();
    S1X8_C_GPIO_MA_L();
    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN4_PORT,S1X8_A_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN7_PORT,S1X8_A_READ_PIN7) ||
        READ_TwoPin(S1X8_B_READ_PIN4_PORT,S1X8_B_READ_PIN4,S1X8_B_READ_PIN7) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN2_PORT,S1X8_C_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN9_PORT,S1X8_C_READ_PIN9))
    {
        /* code */
        printf("Latching S1X8 COM-P1 Error\n");
    }
    else
    {
        printf("Latching S1X8 COM-P1 Nermol\n");
    }


}
void Latch_S1X8_COM_P2(uint16_t time)
{
    //COM-P2
    //A
    S1X8_A_GPIO_CTRL_L();
    S1X8_A_GPIO_MB_L();
    S1X8_A_GPIO_MA_L();
    //B
    S1X8_B_GPIO_CTRL_H();
    S1X8_B_GPIO_MB_L();
    S1X8_B_GPIO_MA_H();
    //C
    S1X8_C_GPIO_CTRL_L();
    S1X8_C_GPIO_MB_L();
    S1X8_C_GPIO_MA_L();
    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN2_PORT,S1X8_A_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN9_PORT,S1X8_A_READ_PIN9) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN2_PORT,S1X8_C_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN9_PORT,S1X8_C_READ_PIN9) ||
        READ_TwoPin(S1X8_B_READ_PIN4_PORT,S1X8_B_READ_PIN4,S1X8_B_READ_PIN7))
    {
        /* code */
        printf("Latching S1X8 COM-P2 Error\n");
    }
    else
    {
        printf("Latching S1X8 COM-P2 Nermol\n");
    }
}
void Latch_S1X8_COM_P3(uint16_t time)
{
    //COM-P3
    //A
    S1X8_A_GPIO_CTRL_H();
    S1X8_A_GPIO_MB_L();
    S1X8_A_GPIO_MA_H();
    //B
    S1X8_B_GPIO_CTRL_L();
    S1X8_B_GPIO_MB_L();
    S1X8_B_GPIO_MA_L();
    //C
    S1X8_C_GPIO_CTRL_L();
    S1X8_C_GPIO_MB_L();
    S1X8_C_GPIO_MA_L();
    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN4_PORT,S1X8_A_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN7_PORT,S1X8_A_READ_PIN7) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN2_PORT,S1X8_C_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN9_PORT,S1X8_C_READ_PIN9) ||
        READ_TwoPin(S1X8_B_READ_PIN2_PORT,S1X8_B_READ_PIN2,S1X8_B_READ_PIN9))
    {
        /* code */
        printf("Latching S1X8 COM-P3 Error\n");
    }
    else
    {
        printf("Latching S1X8 COM-P3 Nermol\n");
    }
}
void Latch_S1X8_COM_P4(uint16_t time)
{
    //COM-P4
    //A
    S1X8_A_GPIO_CTRL_L();
    S1X8_A_GPIO_MB_L();
    S1X8_A_GPIO_MA_L();
    //B
    S1X8_B_GPIO_CTRL_L();
    S1X8_B_GPIO_MB_L();
    S1X8_B_GPIO_MA_L();
    //C
    S1X8_C_GPIO_CTRL_L();
    S1X8_C_GPIO_MB_L();
    S1X8_C_GPIO_MA_L();
    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN2_PORT,S1X8_A_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN9_PORT,S1X8_A_READ_PIN9) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN2_PORT,S1X8_C_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN9_PORT,S1X8_C_READ_PIN9) ||
        READ_TwoPin(S1X8_B_READ_PIN2_PORT,S1X8_B_READ_PIN2,S1X8_B_READ_PIN9))
    {
        /* code */
        printf("Latching S1X8 COM-P3 Error\n");
    }
    else
    {
        printf("Latching S1X8 COM-P3 Nermol\n");
    }

}
void Latch_S1X8_COM_P5(uint16_t time)
{
    //COM-P5
    //A
    S1X8_A_GPIO_CTRL_H();
    S1X8_A_GPIO_MB_L();
    S1X8_A_GPIO_MA_H();
    //B
    S1X8_B_GPIO_CTRL_H();
    S1X8_B_GPIO_MB_L();
    S1X8_B_GPIO_MA_H();
    //c
    S1X8_C_GPIO_CTRL_H();
    S1X8_C_GPIO_MB_L();
    S1X8_C_GPIO_MA_H();
    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN4_PORT,S1X8_A_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN7_PORT,S1X8_A_READ_PIN7) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN4_PORT,S1X8_C_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN7_PORT,S1X8_C_READ_PIN7) ||
        READ_TwoPin(S1X8_B_READ_PIN4_PORT,S1X8_B_READ_PIN4,S1X8_B_READ_PIN7))
    {
        /* code */
        printf("Latching S1X8 COM-P3 Error\n");
    }
    else
    {
        printf("Latching S1X8 COM-P3 Nermol\n");
    }

}
void Latch_S1X8_COM_P6(uint16_t time)
{
    //COM-P6
    //A
    S1X8_A_GPIO_CTRL_L();
    S1X8_A_GPIO_MB_L();
    S1X8_A_GPIO_MA_L();
    //B
    S1X8_B_GPIO_CTRL_H();
    S1X8_B_GPIO_MB_L();
    S1X8_B_GPIO_MA_H();
    //c
    S1X8_C_GPIO_CTRL_H();
    S1X8_C_GPIO_MB_L();
    S1X8_C_GPIO_MA_H();
    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN2_PORT,S1X8_A_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN9_PORT,S1X8_A_READ_PIN9) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN4_PORT,S1X8_C_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN7_PORT,S1X8_C_READ_PIN7) ||
        READ_TwoPin(S1X8_B_READ_PIN4_PORT,S1X8_B_READ_PIN4,S1X8_B_READ_PIN7))
    {
        /* code */
        printf("Latching S1X8 COM-P3 Error\n");
    }
    else
    {
        printf("Latching S1X8 COM-P3 Nermol\n");
    }
}
void Latch_S1X8_COM_P7(uint16_t time)
{
    //COM-P7
    //A
    S1X8_A_GPIO_CTRL_H();
    S1X8_A_GPIO_MB_L();
    S1X8_A_GPIO_MA_H();
    //B
    S1X8_B_GPIO_CTRL_L();
    S1X8_B_GPIO_MB_L();
    S1X8_B_GPIO_MA_L();
    //c
    S1X8_C_GPIO_CTRL_H();
    S1X8_C_GPIO_MB_L();
    S1X8_C_GPIO_MA_H();
    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN4_PORT,S1X8_A_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN7_PORT,S1X8_A_READ_PIN7) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN4_PORT,S1X8_C_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN7_PORT,S1X8_C_READ_PIN7) ||
        READ_TwoPin(S1X8_B_READ_PIN2_PORT,S1X8_B_READ_PIN2,S1X8_B_READ_PIN9))
    {
        /* code */
        printf("Latching S1X8 COM-P3 Error\n");
    }
    else
    {
        printf("Latching S1X8 COM-P3 Nermol\n");
    }

}
void Latch_S1X8_COM_P8(uint16_t time)
{
    //COM-P8
    //A
    S1X8_A_GPIO_CTRL_L();
    S1X8_A_GPIO_MB_L();
    S1X8_A_GPIO_MA_L();
    //B
    S1X8_B_GPIO_CTRL_L();
    S1X8_B_GPIO_MB_L();
    S1X8_B_GPIO_MA_L();
    //C
    S1X8_C_GPIO_CTRL_H();
    S1X8_C_GPIO_MB_L();
    S1X8_C_GPIO_MA_H();
    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN2_PORT,S1X8_A_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN9_PORT,S1X8_A_READ_PIN9) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN4_PORT,S1X8_C_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN7_PORT,S1X8_C_READ_PIN7) ||
        READ_TwoPin(S1X8_B_READ_PIN2_PORT,S1X8_B_READ_PIN2,S1X8_B_READ_PIN9))
    {
        /* code */
        printf("Latching S1X8 COM-P3 Error\n");
    }
    else
    {
        printf("Latching S1X8 COM-P3 Nermol\n");
    }

}


void NonLatch_S1X8_COM_P1(uint16_t time)
{
    //A
    S1X8_A_GPIO_CTRL_H();
    //B
    S1X8_B_GPIO_CTRL_H();
    //C
    S1X8_C_GPIO_CTRL_L();

    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN4_PORT,S1X8_A_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN7_PORT,S1X8_A_READ_PIN7) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN2_PORT,S1X8_C_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN9_PORT,S1X8_C_READ_PIN9) ||
        READ_TwoPin(S1X8_B_READ_PIN4_PORT,S1X8_B_READ_PIN4,S1X8_B_READ_PIN7))
    {
        /* code */
        printf("NonLatching S1X8 COM-P1 Error\n");
    }
    else
    {
        printf("NonLatching S1X8 COM-P1 Nermol\n");
    }
}
void NonLatch_S1X8_COM_P2(uint16_t time)
{
    //COM-P2
    //A
    S1X8_A_GPIO_MA_L();
    S1X8_A_GPIO_CTRL_L();
    S1X8_A_GPIO_MB_L();
    //B
    S1X8_B_GPIO_CTRL_L();
    S1X8_B_GPIO_MB_L();
    S1X8_B_GPIO_MA_L();
    //C
    S1X8_C_GPIO_CTRL_L();
    S1X8_C_GPIO_MB_L();
    S1X8_C_GPIO_MA_L();
    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN2_PORT,S1X8_A_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN9_PORT,S1X8_A_READ_PIN9) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN2_PORT,S1X8_C_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN9_PORT,S1X8_C_READ_PIN9) ||
        READ_TwoPin(S1X8_B_READ_PIN4_PORT,S1X8_B_READ_PIN4,S1X8_B_READ_PIN7))
    {
        /* code */
        printf("Latching S1X8 COM-P2 Error\n");
    }
    else
    {
        printf("Latching S1X8 COM-P2 Nermol\n");
    }

}
void NonLatch_S1X8_COM_P3(uint16_t time)
{
    //COM-P3
    //A
    S1X8_A_GPIO_CTRL_L();
    //B
    S1X8_B_GPIO_CTRL_H();
    //C
    S1X8_C_GPIO_CTRL_L();
    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN4_PORT,S1X8_A_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN7_PORT,S1X8_A_READ_PIN7) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN2_PORT,S1X8_C_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN9_PORT,S1X8_C_READ_PIN9) ||
        READ_TwoPin(S1X8_B_READ_PIN2_PORT,S1X8_B_READ_PIN2,S1X8_B_READ_PIN9))
    {
        /* code */
        printf("Latching S1X8 COM-P3 Error\n");
    }
    else
    {
        printf("Latching S1X8 COM-P3 Nermol\n");
    }

}
void NonLatch_S1X8_COM_P4(uint16_t time)
{
    //COM-P4
    //A
    S1X8_A_GPIO_CTRL_L();
    //B
    S1X8_B_GPIO_CTRL_L();
    //C
    S1X8_C_GPIO_CTRL_L();

    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN2_PORT,S1X8_A_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN9_PORT,S1X8_A_READ_PIN9) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN2_PORT,S1X8_C_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN9_PORT,S1X8_C_READ_PIN9) ||
        READ_TwoPin(S1X8_B_READ_PIN2_PORT,S1X8_B_READ_PIN2,S1X8_B_READ_PIN9))
    {
        /* code */
        printf("Latching S1X8 COM-P3 Error\n");
    }
    else
    {
        printf("Latching S1X8 COM-P3 Nermol\n");
    }

}
void NonLatch_S1X8_COM_P5(uint16_t time)
{
    //COM-P5
    //A
    S1X8_A_GPIO_CTRL_H();
    //B
    S1X8_B_GPIO_CTRL_H();
    //c
    S1X8_C_GPIO_CTRL_H();

    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN4_PORT,S1X8_A_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN7_PORT,S1X8_A_READ_PIN7) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN4_PORT,S1X8_C_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN7_PORT,S1X8_C_READ_PIN7) ||
        READ_TwoPin(S1X8_B_READ_PIN4_PORT,S1X8_B_READ_PIN4,S1X8_B_READ_PIN7))
    {
        /* code */
        printf("Latching S1X8 COM-P3 Error\n");
    }
    else
    {
        printf("Latching S1X8 COM-P3 Nermol\n");
    }

}
void NonLatch_S1X8_COM_P6(uint16_t time)
{
    //COM-P6
    //A
    S1X8_A_GPIO_CTRL_L();
    //B
    S1X8_B_GPIO_CTRL_H();
    //c
    S1X8_C_GPIO_CTRL_H();

    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN2_PORT,S1X8_A_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN9_PORT,S1X8_A_READ_PIN9) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN4_PORT,S1X8_C_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN7_PORT,S1X8_C_READ_PIN7) ||
        READ_TwoPin(S1X8_B_READ_PIN4_PORT,S1X8_B_READ_PIN4,S1X8_B_READ_PIN7))
    {
        /* code */
        printf("Latching S1X8 COM-P3 Error\n");
    }
    else
    {
        printf("Latching S1X8 COM-P3 Nermol\n");
    }

}
void NonLatch_S1X8_COM_P7(uint16_t time)
{
    //COM-P7
    //A
    S1X8_A_GPIO_CTRL_H();
    //B
    S1X8_B_GPIO_CTRL_L();
    //c
    S1X8_C_GPIO_CTRL_H();

    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN4_PORT,S1X8_A_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN7_PORT,S1X8_A_READ_PIN7) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN4_PORT,S1X8_C_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN7_PORT,S1X8_C_READ_PIN7) ||
        READ_TwoPin(S1X8_B_READ_PIN2_PORT,S1X8_B_READ_PIN2,S1X8_B_READ_PIN9))
    {
        /* code */
        printf("Latching S1X8 COM-P3 Error\n");
    }
    else
    {
        printf("Latching S1X8 COM-P3 Nermol\n");
    }

}
void NonLatch_S1X8_COM_P8(uint16_t time)
{
    //COM-P8
    //A
    S1X8_A_GPIO_CTRL_L();
    //B
    S1X8_B_GPIO_CTRL_L();
    //C
    S1X8_C_GPIO_CTRL_H();

    delay_ms(time);
    if (PCA_GPIO_ReadPin(S1X8_A_READ_PIN2_PORT,S1X8_A_READ_PIN2) ||
        PCA_GPIO_ReadPin(S1X8_A_READ_PIN9_PORT,S1X8_A_READ_PIN9) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN4_PORT,S1X8_C_READ_PIN4) ||
        PCA_GPIO_ReadPin(S1X8_C_READ_PIN7_PORT,S1X8_C_READ_PIN7) ||
        READ_TwoPin(S1X8_B_READ_PIN2_PORT,S1X8_B_READ_PIN2,S1X8_B_READ_PIN9))
    {
        /* code */
        printf("Latching S1X8 COM-P3 Error\n");
    }
    else
    {
        printf("Latching S1X8 COM-P3 Nermol\n");
    }

}
