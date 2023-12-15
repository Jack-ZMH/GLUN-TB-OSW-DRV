#include "bsp_i2c.h"

#define uTime	4



void I2c_Init(void)
{
	I2C_GPIO_CLK();	
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	//��©�����û�����������衢����ٶ�
	GPIO_InitStruct.Pin = I2C_SCL_PIN | I2C_SDA_PIN;							
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;				
	GPIO_InitStruct.Pull = GPIO_NOPULL;								
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(I2C_GPIO_PORT, &GPIO_InitStruct);	
	
	i2c_stop();
}

//��ʼ�ź�
void i2c_start(void)
{
	I2C_SCL_1;
	I2C_SDA_1;	
	delay_us(uTime);
	I2C_SDA_0;
	delay_us(uTime);
	I2C_SCL_0;
}

//�����ź�
void i2c_stop(void)
{
	I2C_SCL_1;
	I2C_SDA_0;
	delay_us(uTime);
	I2C_SDA_1;
}


//Ӧ���ź�
void i2c_ask(void)
{
	I2C_SDA_0; //���������ͣ�����Ӧ��
	I2C_SCL_1;
	delay_us(uTime);
	
	I2C_SCL_0;	//������9��ʱ������
	delay_us(uTime);
	I2C_SDA_1; 	//SDA���ߣ��ͷ�����
	delay_us(uTime);
}
//��Ӧ���ź�
void i2c_nask(void)
{
	I2C_SDA_1; //���������ߣ�������Ӧ��
	I2C_SCL_1;
	delay_us(uTime);
	
	I2C_SCL_0;	//������9��ʱ������
	delay_us(uTime);	
}


// �ȴ�Ӧ���źţ�NASK :1  ASK:0
uint8_t i2c_wait_ask(void)
{
	uint8_t reply;
	//uint16_t ucErrTime=0;
	I2C_SDA_1;	//�ͷ����߿���Ȩ
	I2C_SCL_1;
	delay_us(uTime);
	
	if(I2C_SDA_READ() == 1)
	{
		reply = 1;		//EEPROM��Ӧ��
	}
	else
	{
		reply = 0;	  //EEPROMӦ��
	}
	
	I2C_SCL_0;	//����ʱ�ź���
	delay_us(uTime);
	
	return reply;
}

void i2c_write_byte(uint8_t data)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		if(data&0x80)
			I2C_SDA_1;
		else
			I2C_SDA_0;
		delay_us(uTime);
		
		I2C_SCL_1;
		delay_us(uTime);
		I2C_SCL_0;
		delay_us(uTime);
		
		if(i==7)
			I2C_SDA_1; //������ɣ��ͷ�����
		
		data <<= 1; //��������
	}
}

uint8_t i2c_read_byte(void)
{
	uint8_t i;
	uint8_t temp = 0;
	for(i=0;i<8;i++)
	{
		temp <<=1;
		I2C_SCL_1;
		delay_us(uTime);
		
		if(I2C_SDA_READ() == 1)
			temp +=1;
		
		I2C_SCL_0;
		delay_us(uTime);
	}
	return temp;
}

void i2c_rest(void)
{
	I2C_SDA_1; 		//�ͷ�����
	I2C_SCL_1;		//����ʱ��,������ʮ������
	delay_us(uTime);
	I2C_SDA_0;
	delay_us(uTime);
	I2C_SCL_0;
}


/// @brief I2C Device chenck
void CHENCK_DRIVER(uint8_t addr)
{
	uint8_t result;
	char *Ptr;
	
	delay_ms(100);
	i2c_start();
	i2c_write_byte(addr);
	result = i2c_wait_ask();
	switch(addr>>1){
		case 0x20:	Ptr = "PAC9868";break;
		case 0x2c:	Ptr = "AD5175";break;
		default:Ptr = NULL;
	}
	if(result)
		printf("%s ASK ERROE��\r\n",Ptr);
	else
		printf("%s ASK SUCCUS��\r\n",Ptr);
	i2c_stop();
}
