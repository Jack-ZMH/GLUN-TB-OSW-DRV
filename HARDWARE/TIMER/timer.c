#include "timer.h"

uint8_t M2 = 0; 
uint8_t M5 = 0;
uint8_t M10 = 0;
uint8_t M100 = 0;
uint8_t M200 = 0;
uint8_t M400 = 0;

TIM_HandleTypeDef TIM4_Handler;      //��ʱ����� 


void TIM4_Init(u16 arr,u16 psc)
{  
    TIM4_Handler.Instance=TIM4;                          //ͨ�ö�ʱ��4
    TIM4_Handler.Init.Prescaler=psc;                     //��Ƶϵ��
    TIM4_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM4_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
    TIM4_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM4_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM4_Handler); //ʹ�ܶ�ʱ��4�����жϣ�TIM_IT_UPDATE   
}


void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM4)
	{
		__HAL_RCC_TIM4_CLK_ENABLE();            //ʹ��TIM3ʱ��
		HAL_NVIC_SetPriority(TIM4_IRQn,1,3);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM4_IRQn);          //����ITM3�ж�   
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

