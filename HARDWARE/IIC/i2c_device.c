#include "i2c_device.h"

I2C_HandleTypeDef  hi2c;

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	if(hi2c->Instance == I2C1)
	{	
		__HAL_RCC_I2C1_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GPIO_InitStruct.Pin = GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate =GPIO_AF4_I2C1;
		
		HAL_GPIO_Init(GPIOB,&GPIO_InitStruct);
		
		GPIO_InitStruct.Pin = GPIO_PIN_7;
		GPIO_InitStruct.Alternate =GPIO_AF4_I2C1;
		HAL_GPIO_Init(GPIOB,&GPIO_InitStruct);
		
		/*强制 I2C 外设时钟复位*/
		I2Cx_FORCE_RESET() ;
		
		/*释放 I2C 外设时钟复位*/
		I2Cx_RELEASE_RESET();

#ifdef UAER_IRQ		
		HAL_NVIC_SetPriority(I2C1_EV_IRQn,4,3);
		HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
#endif
	}
}

void Bsp_I2c_Init(void)
{
	__HAL_RCC_I2C1_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	hi2c.Instance = I2C1;
	hi2c.Init.ClockSpeed = 400000;
	hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c.Init.NoStretchMode	=I2C_NOSTRETCH_DISABLE;
	hi2c.Init.OwnAddress1 = 0x0A;
	hi2c.Init.OwnAddress2 = 0;
	
	if(HAL_I2C_Init(&hi2c) != HAL_OK)
	{
		printf("I2C INIT ERROR\n");
	}
	
	//HAL_I2CEx_AnalogFilter_Config(&hi2c,I2C_ANALOGFILTER_ENABLE);
}
