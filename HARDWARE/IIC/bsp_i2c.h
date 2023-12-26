#ifndef BSP_I2C_H
#define BSP_I2C_H

#include "sys.h"

//#define USER_I2C

#define I2C_SCL_PIN					GPIO_PIN_6
#define I2C_SDA_PIN					GPIO_PIN_7
#define I2C_GPIO_PORT            	GPIOB
#define I2C_GPIO_CLK()				__HAL_RCC_GPIOB_CLK_ENABLE() 

#define I2C_SCL_1					do{HAL_GPIO_WritePin(I2C_GPIO_PORT,I2C_SCL_PIN,GPIO_PIN_SET);}while(0)
#define I2C_SCL_0					do{HAL_GPIO_WritePin(I2C_GPIO_PORT,I2C_SCL_PIN,GPIO_PIN_RESET);}while(0)

#define I2C_SDA_1					do{HAL_GPIO_WritePin(I2C_GPIO_PORT,I2C_SDA_PIN,GPIO_PIN_SET);}while(0)
#define I2C_SDA_0					do{HAL_GPIO_WritePin(I2C_GPIO_PORT,I2C_SDA_PIN,GPIO_PIN_RESET);}while(0)

#define I2C_SDA_READ()   			HAL_GPIO_ReadPin(I2C_GPIO_PORT,I2C_SDA_PIN)


void I2c_Init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_ask(void);
void i2c_nask(void);
uint8_t i2c_wait_ask(void);
void i2c_write_byte(uint8_t data);
uint8_t i2c_read_byte(void);
void i2c_rest(void);

void CHENCK_DRIVER(uint8_t addr);

#endif

