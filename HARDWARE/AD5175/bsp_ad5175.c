#include "bsp_ad5175.h"




void ad5175_Init(void)
{
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	//开漏输出、没有上下拉电阻、最高速度
	GPIO_InitStruct.Pin = AD5175_eRST;							
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;				
	GPIO_InitStruct.Pull = GPIO_PULLUP;								
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(AD5175_GPIO_PORT, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(AD5175_GPIO_PORT,AD5175_eRST,GPIO_PIN_RESET);
	delay_ms(100);
	HAL_GPIO_WritePin(AD5175_GPIO_PORT,AD5175_eRST,GPIO_PIN_SET);
	
	//AD5175_RESET();
	AD5175_SoftwareRest();
}


//发送2字节
uint8_t AD5175_WriteByte(uint8_t * pucByte) 
{
    uint8_t Ask = NULL;
	i2c_start();	//开始信号
    i2c_write_byte(AD5175_WIRE_ADDR); //发送地址

	Ask = i2c_wait_ask(); //等待ADK
	if(Ask)return 1;  
		
    i2c_write_byte(*(pucByte ++)); //发送高8位
    Ask = i2c_wait_ask();
	if(Ask)return 2;
		
    i2c_write_byte(*pucByte);//发送低8位
    Ask = i2c_wait_ask();
	if(Ask)return 3;  
		
    i2c_stop();
    return 0; 
}

//读取2字节
uint16_t AD5175_ReadByte(uint8_t * pucByte) 
{
    i2c_start();
    i2c_write_byte(AD5175_READ_ADDR);
    if(i2c_wait_ask()) return 1;
    
    *(pucByte++) = i2c_read_byte(); //读取高8位
    i2c_ask(); //发送应答
	
    *pucByte = i2c_read_byte();//读取低8位
    i2c_nask(); //发送非应答
	
    i2c_stop();//结束通信
    return *pucByte;    
}

//写入命令
uint8_t AD5175_WriteCmd(uint8_t ucCmd, uint16_t nData) 
{
    uint8_t ucData[2];
    
    ucData[0] = (uint8_t)((ucCmd << 2) | (nData >> 8));
    ucData[1] = (uint8_t)(nData & 0xff);
    
    return AD5175_WriteByte(ucData);
}

//读取16BIT寄存器
uint16_t AD5175_Read16Bit(void) 
{
    uint8_t ucData[2];
   	uint16_t nNumber;
    
    AD5175_ReadByte(ucData);
    nNumber = ucData[0] & 0x3;
    nNumber = (nNumber << 8) + ucData[1];
    return nNumber; 
}



//写入RDAC数据
void AD5175_WriteRDAC(uint16_t nRDAC) 
{
    AD5175_WriteCmd(COMMAND_W_RDAC, nRDAC);
}

//读取RDAC数据
uint16_t AD5175_ReadRDAC(void) 
{
    AD5175_WriteCmd(COMMAND_R_RDAC, 0x00);
    return AD5175_Read16Bit();
}

//将RDAC数据写入50-Tp中
void AD5175_WriteRadcTo50tp(void)
{
	AD5175_WriteCmd(COMMAND_STORE_RDAC_50TP,0x00);
	delay_ms(500);  //写入50TP需要等待350ms以上
}

//软件复位
void AD5175_SoftwareRest(void)
{
	AD5175_WriteCmd(COMMAND_SOFTWARE_RESET,0x00);
	delay_ms(1000); //软件复位之后，等待100MS
}

//读取50TP中的内容
uint16_t AD5175_Read50TP(uint8_t _50TpAddr)
{
    AD5175_WriteCmd(COMMAND_R_50TP_NEXT_FRAME, _50TpAddr);
    return AD5175_Read16Bit();
}

//读取50TP地址
uint16_t AD5175_Read50TPAddress(void) 
{
    AD5175_WriteCmd(COMMAND_R_LAST_50TP_LOCATION, 0x00);
    return AD5175_Read16Bit();
}

//写控制寄存器
void AD5175_WriteControl(uint8_t nData)
{
	AD5175_WriteCmd(COMMAND_W_CONTROL,nData);
}
//读控制寄存器
uint16_t AD5175_ReadControl(void)
{
	AD5175_WriteCmd(COMMAND_R_CONTROL,0x00);
	return AD5175_Read16Bit();
}

//软件掉电
void AD5175_SoftwareSwitch(uint8_t nData)
{
	AD5175_WriteCmd(COMMAND_SOFTWARE_SHUTDOWN,nData);
}

