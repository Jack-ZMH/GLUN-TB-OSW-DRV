#include "bsp_M1X4.h"

/// @brief M1X4_GPIO_Init
/// @param  
void M1X4_GPIO_Init(void)
{
 	GPIO_InitTypeDef  GPIO_InitStruct;

	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitStruct.Pin = M1X4_GPIO_PIN1;							
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;				
	GPIO_InitStruct.Pull = GPIO_PULLUP;								
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(M1X4_GPIO_PIN1_PORT, &GPIO_InitStruct);	

    GPIO_InitStruct.Pin = M1X4_GPIO_PIN8;
    HAL_GPIO_Init(M1X4_GPIO_PIN8_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = M1X4_GPIO_PIN21;
    HAL_GPIO_Init(M1X4_GPIO_PIN21_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = M1X4_GPIO_PIN28;
    HAL_GPIO_Init(M1X4_GPIO_PIN28_PORT, &GPIO_InitStruct);

    //默认都为低
    M1X4_GPIO_PIN1_L();
    M1X4_GPIO_PIN8_L();
    M1X4_GPIO_PIN21_L();
    M1X4_GPIO_PIN28_L();

}

/// @brief 重复检测
/// @param time 
/// @param num 
void M1X4_CHENCK(uint16_t time,uint32_t num)
{	
    // 轮询切换四种状态
	while(num--) {	
		if(Switch){
            // 0 1 0 1
            M1X4_GPIO_PIN1_L(); 
            M1X4_GPIO_PIN8_H();
            M1X4_GPIO_PIN21_L();
            M1X4_GPIO_PIN28_H();
            delay_ms(20);
            if(READ_TwoPin(M1X4_READ_PORT1,M1X4_READ_PIN4,M1X4_READ_PIN5) &&
               READ_TwoPin(M1X4_READ_PORT2,M1X4_READ_PIN24,M1X4_READ_PIN25))
                printf("M1X4 State:A Error\n");
            else 
                printf("M1X4 State:A Normel\n");
            // 1 0 0 1
            M1X4_GPIO_PIN1_H(); 
            M1X4_GPIO_PIN8_L();
            M1X4_GPIO_PIN21_L();
            M1X4_GPIO_PIN28_H();
            delay_ms(20);
            if(READ_TwoPin(M1X4_READ_PORT1,M1X4_READ_PIN2,M1X4_READ_PIN7) &&
               READ_TwoPin(M1X4_READ_PORT2,M1X4_READ_PIN24,M1X4_READ_PIN25))
                printf("M1X4 State:B Error\n");
            else 
                printf("M1X4 State:B Normel\n");

            // 0 1 1 0
            M1X4_GPIO_PIN1_L(); 
            M1X4_GPIO_PIN8_H();
            M1X4_GPIO_PIN21_H();
            M1X4_GPIO_PIN28_L();
            delay_ms(20);
            if(READ_TwoPin(M1X4_READ_PORT1,M1X4_READ_PIN4,M1X4_READ_PIN5) &&
               READ_TwoPin(M1X4_READ_PORT2,M1X4_READ_PIN22,M1X4_READ_PIN27))
                printf("M1X4 State:C Error\n");
            else 
                printf("M1X4 State:C Normel\n");

             // 1 0 1 0
            M1X4_GPIO_PIN1_H(); 
            M1X4_GPIO_PIN8_L();
            M1X4_GPIO_PIN21_H();
            M1X4_GPIO_PIN28_L();
            delay_ms(20);
            if(READ_TwoPin(M1X4_READ_PORT1,M1X4_READ_PIN2,M1X4_READ_PIN7) &&
               READ_TwoPin(M1X4_READ_PORT2,M1X4_READ_PIN22,M1X4_READ_PIN27))
                printf("M1X4 State:C Error\n");
            else 
                printf("M1X4 State:C Normel\n");
		}
		else {
		
			printf("C1X2G STOP\n");
			num = 0;
		}
	}   
}

/// @brief M1X4_State_A
/// @param  
void M1X4_State_A(void)
{
    M1X4_GPIO_PIN1_L(); 
    M1X4_GPIO_PIN8_H();
    M1X4_GPIO_PIN21_L();
    M1X4_GPIO_PIN28_H();
    delay_ms(20);
    if(READ_TwoPin(M1X4_READ_PORT1,M1X4_READ_PIN4,M1X4_READ_PIN5)&&
       READ_TwoPin(M1X4_READ_PORT2,M1X4_READ_PIN24,M1X4_READ_PIN25))
        printf("M1X4 State A Error\n");
    else
        printf("M1X4 State A Normel\n");
}

/// @brief M1X4_State_B
/// @param  
void M1X4_State_B(void)
{
    M1X4_GPIO_PIN1_H(); 
    M1X4_GPIO_PIN8_L();
    M1X4_GPIO_PIN21_L();
    M1X4_GPIO_PIN28_H();
    delay_ms(20);
    if(READ_TwoPin(M1X4_READ_PORT1,M1X4_READ_PIN2,M1X4_READ_PIN7) &&
        READ_TwoPin(M1X4_READ_PORT2,M1X4_READ_PIN24,M1X4_READ_PIN25))
        printf("M1X4 State:B Error\n");
    else 
        printf("M1X4 State:B Normel\n");
}

/// @brief M1X4_State_C
/// @param  
void M1X4_State_C(void)
{
    M1X4_GPIO_PIN1_L(); 
    M1X4_GPIO_PIN8_H();
    M1X4_GPIO_PIN21_H();
    M1X4_GPIO_PIN28_L();
    delay_ms(20);
    if(READ_TwoPin(M1X4_READ_PORT1,M1X4_READ_PIN4,M1X4_READ_PIN5) &&
       READ_TwoPin(M1X4_READ_PORT2,M1X4_READ_PIN22,M1X4_READ_PIN27))
        printf("M1X4 State:C Error\n");
    else 
        printf("M1X4 State:C Normel\n");
}

/// @brief M1X4_State_D
/// @param  
void M1X4_State_D(void)
{
    M1X4_GPIO_PIN1_H(); 
    M1X4_GPIO_PIN8_L();
    M1X4_GPIO_PIN21_H();
    M1X4_GPIO_PIN28_L();
    delay_ms(20);
    if(READ_TwoPin(M1X4_READ_PORT1,M1X4_READ_PIN2,M1X4_READ_PIN7) &&
       READ_TwoPin(M1X4_READ_PORT2,M1X4_READ_PIN22,M1X4_READ_PIN27))
        printf("M1X4 State:C Error\n");
    else 
        printf("M1X4 State:C Normel\n");
}

/// @brief NonLatching_M1X4State_A
/// @param  
void NonLatching_M1X4State_A(void)
{
	M1X4_GPIO_PIN1_L();
    M1X4_GPIO_PIN8_L();
    M1X4_GPIO_PIN21_L();
    M1X4_GPIO_PIN28_L();
	delay_ms(20);
    if(READ_TwoPin(M1X4_READ_PORT1,M1X4_READ_PIN4,M1X4_READ_PIN5)&&
       READ_TwoPin(M1X4_READ_PORT2,M1X4_READ_PIN24,M1X4_READ_PIN25))
        printf("M1X4 State A Error\n");
    else
        printf("M1X4 State A Normel\n");
}

/// @brief NonLatching_M1X4State_B
/// @param  
void NonLatching_M1X4State_B(void)
{
	M1X4_GPIO_PIN1_H();
    M1X4_GPIO_PIN8_L();
    M1X4_GPIO_PIN21_L();
    M1X4_GPIO_PIN28_L();
	delay_ms(20);
    if(READ_TwoPin(M1X4_READ_PORT1,M1X4_READ_PIN2,M1X4_READ_PIN7) &&
        READ_TwoPin(M1X4_READ_PORT2,M1X4_READ_PIN24,M1X4_READ_PIN25))
        printf("M1X4 State:B Error\n");
    else 
        printf("M1X4 State:B Normel\n");
}

/// @brief NonLatching_M1X4State_C
/// @param  
void NonLatching_M1X4State_C(void)
{
	M1X4_GPIO_PIN1_L();
    M1X4_GPIO_PIN8_L();
    M1X4_GPIO_PIN21_H();
    M1X4_GPIO_PIN28_L();
	delay_ms(20);
    if(READ_TwoPin(M1X4_READ_PORT1,M1X4_READ_PIN4,M1X4_READ_PIN5) &&
       READ_TwoPin(M1X4_READ_PORT2,M1X4_READ_PIN22,M1X4_READ_PIN27))
        printf("M1X4 State:C Error\n");
    else 
        printf("M1X4 State:C Normel\n");
}

/// @brief NonLatching_M1X4State_D
/// @param  
void NonLatching_M1X4State_D(void)
{
	M1X4_GPIO_PIN1_H();
    M1X4_GPIO_PIN8_L();
    M1X4_GPIO_PIN21_H();
    M1X4_GPIO_PIN28_L();
	delay_ms(20);
    if(READ_TwoPin(M1X4_READ_PORT1,M1X4_READ_PIN2,M1X4_READ_PIN7) &&
       READ_TwoPin(M1X4_READ_PORT2,M1X4_READ_PIN22,M1X4_READ_PIN27))
        printf("M1X4 State:C Error\n");
    else 
        printf("M1X4 State:C Normel\n");
}
