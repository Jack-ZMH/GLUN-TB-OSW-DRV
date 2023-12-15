#include "myiic.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK NANO STM32F4������
//IIC��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2019/4/23
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2019-2029
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//IIC��ʼ��
void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOB_CLK_ENABLE();   //ʹ��GPIOBʱ��
    
    //PB6,7��ʼ������
    GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_OD;  //�������
    GPIO_Initure.Pull=GPIO_NOPULL;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
    
    IIC_SDA=1;
    IIC_SCL=1;  
}

//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(5);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(6);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(5);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	delay_us(6);	

  	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u16 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA=1;delay_us(2);	   
	IIC_SCL=1;delay_us(2);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>2500)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(5);
	IIC_SCL=0;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(5);
	IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(4);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		delay_us(4); 
		IIC_SCL=0;	
		delay_us(4);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}


u8 IIC_ReadByteFromSlave(u8 I2C_Addr,u8 reg,u8 *buf)
{
	IIC_Start();	
	IIC_Send_Byte(I2C_Addr);	 //���ʹӻ���ַ
	if(IIC_Wait_Ack()) //����ӻ�δӦ�������ݷ���ʧ��
	{
		IIC_Stop();
		return 1;
	}
	IIC_Send_Byte(reg); //���ͼĴ�����ַ
	IIC_Wait_Ack();	  
	
	IIC_Start();
	IIC_Send_Byte(I2C_Addr+1); //�������ģʽ			   
	IIC_Wait_Ack();
	*buf=IIC_Read_Byte(0);	   
  IIC_Stop(); //����һ��ֹͣ����
	return 0;
}

u8 IIC_WriteByteToSlave(u8 I2C_Addr,u8 reg,u8 data)
{
	IIC_Start();
	IIC_Send_Byte(I2C_Addr); //���ʹӻ���ַ
	if(IIC_Wait_Ack())
	{
		IIC_Stop();
		return 1; //�ӻ���ַд��ʧ��
	}
	IIC_Send_Byte(reg); //���ͼĴ�����ַ
	IIC_Wait_Ack();	  
	IIC_Send_Byte(data); 
	if(IIC_Wait_Ack())
	{
		IIC_Stop(); 
		return 1; //����д��ʧ��
	}
	IIC_Stop(); //����һ��ֹͣ����

  //return 1; //status == 0;
	return 0;
}

u8 IIC_ReadMultByteFromSlave(u8 dev, u8 reg, u8 length, uint8_t *data)
{
  u8 count = 0;
	u8 temp;
	IIC_Start();
	IIC_Send_Byte(dev); //���ʹӻ���ַ
	if(IIC_Wait_Ack())
	{
		IIC_Stop(); 
		return 1; //�ӻ���ַд��ʧ��
	}
	IIC_Send_Byte(reg); //���ͼĴ�����ַ
  IIC_Wait_Ack();	  
	IIC_Start();
	IIC_Send_Byte(dev+1); //�������ģʽ	
	IIC_Wait_Ack();
  for(count=0;count<length;count++)
	{
		if(count!=(length-1))
		temp = IIC_Read_Byte(1); //��ACK�Ķ�����
		else  
		temp = IIC_Read_Byte(0); //���һ���ֽ�NACK

		data[count] = temp;
	}
    IIC_Stop(); //����һ��ֹͣ����
    //return count;
	 return 0;
}

u8 IIC_WriteMultByteToSlave(u8 dev, u8 reg, u8 length, uint8_t* data)
{
  
 	u8 count = 0;
	IIC_Start();
	IIC_Send_Byte(dev); //���ʹӻ���ַ
	if(IIC_Wait_Ack())
	{
		IIC_Stop();
		return 1; //�ӻ���ַд��ʧ��
	}
	IIC_Send_Byte(reg); //���ͼĴ�����ַ
  IIC_Wait_Ack();	  
	for(count=0;count<length;count++)
	{
		IIC_Send_Byte(data[count]); 
		if(IIC_Wait_Ack()) //ÿһ���ֽڶ�Ҫ�ȴӻ�Ӧ��
		{
			IIC_Stop();
			return 1; //����д��ʧ��
		}
	}
	IIC_Stop(); //����һ��ֹͣ����

	return 0;
}


