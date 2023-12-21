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
void M1X4_CHENCK(uint16_t time,uint32_t num,uint8_t SwitchType)
{	
    uint32_t success = 0;
	uint32_t fail = 0;
	
	uint8_t i = 0,j = 0,b = 0,t = 0;
    // 轮询切换四种状态
	while(num) {	
		if(Switch == ON){
			 if(SwitchType == LATCH)
			 {
				i = M1X4_State_A(time);
				j = M1X4_State_B(time); 
				b = M1X4_State_C(time); 
				t = M1X4_State_D(time);
                if(i||j||b||t)
                    fail++;
                else 
                    success++;				 
			 }
			 else if(SwitchType == NONLATCH)
			 {
				i = NonLatching_M1X4State_A(time);
			    j = NonLatching_M1X4State_B(time);
			    b = NonLatching_M1X4State_C(time);
			    t = NonLatching_M1X4State_D(time);
                if(i||j||b||t)
                    fail++;
                else 
                    success++;
			 }
             else{
                printf("Switch Type Error\n");
             }
		}
        else if(Switch == OFF){
            num = 0;
            printf("C1X2G Switch:OFF\n");
			printf("M1X4 Auto Success Num %d ; Fail Num %d \n",success,fail);	
			break;
        }
		if(num++  == 0 ){
			Switch = OFF;
            printf("Test count overflow,Text Stop\n");
			printf("M1X4 Auto Success Num %d ; Fail Num %d \n",success,fail);	
			break;
		}
	}   
}

/// @brief M1X4_State_A
/// @param  
uint8_t M1X4_State_A(uint16_t time)
{
    M1X4_GPIO_PIN1_L(); 
    M1X4_GPIO_PIN8_H();
    M1X4_GPIO_PIN21_L();
    M1X4_GPIO_PIN28_H();
    delay_ms(time);
    if(READ_TwoPin(M1X4_READ_PORT1,M1X4_READ_PIN4,M1X4_READ_PIN5) ||
       READ_TwoPin(M1X4_READ_PORT2,M1X4_READ_PIN24,M1X4_READ_PIN25)){
        printf("M1X4 State A Error\n");
        return 1;
       }
    else{
        printf("M1X4 State A Normel\n");
        return 0;
    }    
}

/// @brief M1X4_State_B
/// @param  
uint8_t M1X4_State_B(uint16_t time)
{
    M1X4_GPIO_PIN1_H(); 
    M1X4_GPIO_PIN8_L();
    M1X4_GPIO_PIN21_L();
    M1X4_GPIO_PIN28_H();
    delay_ms(time);
    if(READ_TwoPin(M1X4_READ_PORT1,M1X4_READ_PIN2,M1X4_READ_PIN7) ||
        READ_TwoPin(M1X4_READ_PORT2,M1X4_READ_PIN24,M1X4_READ_PIN25)){
        printf("M1X4 State B Error\n");
        return 1;
       }
    else{
        printf("M1X4 State B Normel\n");
        return 0;
    } 
}

/// @brief M1X4_State_C
/// @param  
uint8_t M1X4_State_C(uint16_t time)
{
    M1X4_GPIO_PIN1_L(); 
    M1X4_GPIO_PIN8_H();
    M1X4_GPIO_PIN21_H();
    M1X4_GPIO_PIN28_L();
    delay_ms(time);
    if(READ_TwoPin(M1X4_READ_PORT1,M1X4_READ_PIN4,M1X4_READ_PIN5) ||
       READ_TwoPin(M1X4_READ_PORT2,M1X4_READ_PIN22,M1X4_READ_PIN27)){
        printf("M1X4 State C Error\n");
        return 1;
       }
    else{
        printf("M1X4 State C Normel\n");
        return 0;
    } 
}

/// @brief M1X4_State_D
/// @param  
uint8_t M1X4_State_D(uint16_t time)
{
    M1X4_GPIO_PIN1_H(); 
    M1X4_GPIO_PIN8_L();
    M1X4_GPIO_PIN21_H();
    M1X4_GPIO_PIN28_L();
    delay_ms(time);
    if(READ_TwoPin(M1X4_READ_PORT1,M1X4_READ_PIN2,M1X4_READ_PIN7) ||
       READ_TwoPin(M1X4_READ_PORT2,M1X4_READ_PIN22,M1X4_READ_PIN27)){
        printf("M1X4 State D Error\n");
        return 1;
       }
    else{
        printf("M1X4 State D Normel\n");
        return 0;
    } 
}

/// @brief NonLatching_M1X4State_A
/// @param  
uint8_t NonLatching_M1X4State_A(uint16_t time)
{
	M1X4_GPIO_PIN1_L();
    M1X4_GPIO_PIN8_L();
    M1X4_GPIO_PIN21_L();
    M1X4_GPIO_PIN28_L();
	delay_ms(time);
    if(READ_TwoPin(M1X4_READ_PORT1,M1X4_READ_PIN4,M1X4_READ_PIN5) ||
       READ_TwoPin(M1X4_READ_PORT2,M1X4_READ_PIN24,M1X4_READ_PIN25)){
        printf("NonLatching M1X4 State A Error\n");
        return 1;
       }
    else{
        printf("NonLatching M1X4 State A Normel\n");
        return 0;
    }
}

/// @brief NonLatching_M1X4State_B
/// @param  
uint8_t NonLatching_M1X4State_B(uint16_t time)
{
	M1X4_GPIO_PIN1_H();
    M1X4_GPIO_PIN8_L();
    M1X4_GPIO_PIN21_L();
    M1X4_GPIO_PIN28_L();
	delay_ms(time);
    if(READ_TwoPin(M1X4_READ_PORT1,M1X4_READ_PIN2,M1X4_READ_PIN7) ||
        READ_TwoPin(M1X4_READ_PORT2,M1X4_READ_PIN24,M1X4_READ_PIN25)){
        printf("NonLatching M1X4 State B Error\n");
        return 1;
       }
    else{
        printf("NonLatching M1X4 State B Normel\n");
        return 0;
    }
}

/// @brief NonLatching_M1X4State_C
/// @param  
uint8_t NonLatching_M1X4State_C(uint16_t time)
{
	M1X4_GPIO_PIN1_L();
    M1X4_GPIO_PIN8_L();
    M1X4_GPIO_PIN21_H();
    M1X4_GPIO_PIN28_L();
	delay_ms(time);
    if(READ_TwoPin(M1X4_READ_PORT1,M1X4_READ_PIN4,M1X4_READ_PIN5) ||
       READ_TwoPin(M1X4_READ_PORT2,M1X4_READ_PIN22,M1X4_READ_PIN27)){
        printf("NonLatching M1X4 State C Error\n");
        return 1;
       }
    else{
        printf("NonLatching M1X4 State C Normel\n");
        return 0;
    }
}

/// @brief NonLatching_M1X4State_D
/// @param  
uint8_t NonLatching_M1X4State_D(uint16_t time)
{
	M1X4_GPIO_PIN1_H();
    M1X4_GPIO_PIN8_L();
    M1X4_GPIO_PIN21_H();
    M1X4_GPIO_PIN28_L();
	delay_ms(time);
    if(READ_TwoPin(M1X4_READ_PORT1,M1X4_READ_PIN2,M1X4_READ_PIN7) ||
       READ_TwoPin(M1X4_READ_PORT2,M1X4_READ_PIN22,M1X4_READ_PIN27)){
        printf("NonLatching M1X4 State D Error\n");
        return 1;
       }
    else{
        printf("NonLatching M1X4 State D Normel\n");
        return 0;
    }
}
