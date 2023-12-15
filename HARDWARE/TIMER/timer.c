#include "timer.h"

uint8_t M2 = 0; 
uint8_t M5 = 0;
uint8_t M10 = 0;
uint8_t M100 = 0;
uint8_t M200 = 0;
uint8_t M400 = 0;

TIM_HandleTypeDef TIM4_Handler;      //定时器句柄 


void TIM4_Init(u16 arr,u16 psc)
{  
    TIM4_Handler.Instance=TIM4;                          //通用定时器4
    TIM4_Handler.Init.Prescaler=psc;                     //分频系数
    TIM4_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM4_Handler.Init.Period=arr;                        //自动装载值
    TIM4_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM4_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM4_Handler); //使能定时器4更新中断：TIM_IT_UPDATE   
}


void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM4)
	{
		__HAL_RCC_TIM4_CLK_ENABLE();            //使能TIM3时钟
		HAL_NVIC_SetPriority(TIM4_IRQn,1,3);    //设置中断优先级，抢占优先级1，子优先级3
		HAL_NVIC_EnableIRQ(TIM4_IRQn);          //开启ITM3中断   
	}
}


void TIM4_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM4_Handler);

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  	static uint16_t ms2 = 0,ms5 = 0,ms10 = 0,ms100 = 0,ms200 = 0,ms400 = 0;
	  if(htim==(&TIM4_Handler))
		{
		   ms2++;
			 ms5++;
			 ms10++;
			 ms100++;
			 ms200++;
			 ms400++;
			 if(ms2 >= 2)
			 {
			   ms2 = 0;
				 M2 = 1;
			 }
			 if(ms5 >= 5)
			 {
			   ms5 = 0;
				 M5 = 1;
			 }
			 if(ms10 >= 10)
			 {
			   ms10 = 0;
				 M10 = 1;
			 }
			 if(ms100 >= 100)
			 {
			   ms100 = 0;
				 M100 = 1;
			 }
			 if(ms200 >= 200)
			 {
			   ms200 = 0;
				 M200 = 1;
			 }
			 if(ms400 >= 400)
			 {
			   ms400 = 0;
				 M400 = 1;
			 }
		}
}

