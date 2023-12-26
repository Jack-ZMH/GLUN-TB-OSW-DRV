#ifndef BSP_AD5175_H
#define BSP_AD5175_H
#include "bsp_i2c.h"

/*
* 1、AD5175使用前需要打开C0、C1控制位
*/

#define AD5175_eRST	 				GPIO_PIN_0
#define AD5175_GPIO_PORT            GPIOC

//7位地址位
#define AD5175_ADDR					0x2C	//addr connect VCC
#define AD5175_WIRE_ADDR			(AD5175_ADDR << 1) | 0x00
#define AD5175_READ_ADDR			(AD5175_ADDR << 1) | 0x01

/* 定义操作命令 */
#define COMMAND_NOP                     0x00	//NOP
#define COMMAND_W_RDAC                  0x01	//将串行寄存器数据内容写入RDAC。
#define COMMAND_R_RDAC                  0x02	//读取RDAC游标寄存器的内容。
#define COMMAND_STORE_RDAC_50TP         0x03	//存储游标设置：将RDAC设置存储到50-TP中。
#define COMMAND_SOFTWARE_RESET          0x04	//软件复位：利用最后一个50-TP存储器存储的值来刷新RDAC。
#define COMMAND_R_50TP_NEXT_FRAME       0x05	//在下一帧中从SDO输出读取50-TP的内容。
#define COMMAND_R_LAST_50TP_LOCATION    0x06	//读取最后一次50-TP编程存储器位置的地址。
#define COMMAND_W_CONTROL               0x07	//将串行寄存器数据内容写入控制寄存器。
#define COMMAND_R_CONTROL               0x08	//读取控制寄存器的内容。
#define COMMAND_SOFTWARE_SHUTDOWN       0x09	//软件关断。D0 = 0；正常模式。D0 = 1；关断模式


//定义控制寄存器命令
#define RADC_ENABLE						0x20
#define RADC_DISABL						0x00

#define AD5175_50TP_ENABLE				0x01
#define AD5175_50TP_DISABL				0x00

/* 定义软件关断模式 */	
#define SOFT_NORMAL_MODE				0x00	//正常模式
#define SOFT_SHUTOFF_MODE				0x01	//关断模式



void ad5175_Init(void);

uint8_t AD5175_WriteByte(uint8_t * pucByte); /*写字节函数*/
uint16_t AD5175_ReadByte(uint8_t * pucByte); /*读字节函数*/

uint8_t AD5175_WriteCmd(uint8_t ucCmd, uint16_t nData);//写入命令
uint16_t AD5175_Read16Bit(void);//读取16BIT寄存器

//功能函数
void AD5175_WriteRDAC(uint16_t nRDAC);//写入RDAC数据
uint16_t AD5175_ReadRDAC(void);//读取RDAC数据
void AD5175_WriteRadcTo50tp(void);//将RDAC数据写入50-Tp中
void AD5175_SoftwareRest(void);//软件复位
uint16_t AD5175_Read50TP(uint8_t _50TpAddr);//读取50TP中的内容
uint16_t AD5175_Read50TPAddress(void);//读取50TP地址
void AD5175_WriteControl(uint8_t nData);//写控制寄存器
uint16_t AD5175_ReadControl(void);//读控制寄存器
void AD5175_SoftwareSwitch(uint8_t nData);//软件掉电

//使用函数



#endif

