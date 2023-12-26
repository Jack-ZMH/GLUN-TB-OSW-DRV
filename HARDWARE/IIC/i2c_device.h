#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H
#include "sys.h"
extern I2C_HandleTypeDef  hi2c;

#define I2Cx_FORCE_RESET() 		__HAL_RCC_I2C1_FORCE_RESET()
#define I2Cx_RELEASE_RESET() 	__HAL_RCC_I2C1_RELEASE_RESET()


void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c);
void Bsp_I2c_Init(void);


#endif


