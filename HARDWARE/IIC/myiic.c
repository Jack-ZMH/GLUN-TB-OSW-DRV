#include "myiic.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK NANO STM32F4开发板
//IIC驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2019/4/23
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2019-2029
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//IIC初始化
void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOB_CLK_ENABLE();   //使能GPIOB时钟
    
    //PB6,7初始化设置
    GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_OD;  //推挽输出
    GPIO_Initure.Pull=GPIO_NOPULL;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
    
    IIC_SDA=1;
    IIC_SCL=1;  
}

//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(5);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(6);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(5);
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	delay_us(6);	

  	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u16 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
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
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
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
//不产生ACK应答		    
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
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(4);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay_us(4); 
		IIC_SCL=0;	
		delay_us(4);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
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
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}


u8 IIC_ReadByteFromSlave(u8 I2C_Addr,u8 reg,u8 *buf)
{
	IIC_Start();	
	IIC_Send_Byte(I2C_Addr);	 //发送从机地址
	if(IIC_Wait_Ack()) //如果从机未应答则数据发送失败
	{
		IIC_Stop();
		return 1;
	}
	IIC_Send_Byte(reg); //发送寄存器地址
	IIC_Wait_Ack();	  
	
	IIC_Start();
	IIC_Send_Byte(I2C_Addr+1); //进入接收模式			   
	IIC_Wait_Ack();
	*buf=IIC_Read_Byte(0);	   
  IIC_Stop(); //产生一个停止条件
	return 0;
}

u8 IIC_WriteByteToSlave(u8 I2C_Addr,u8 reg,u8 data)
{
	IIC_Start();
	IIC_Send_Byte(I2C_Addr); //发送从机地址
	if(IIC_Wait_Ack())
	{
		IIC_Stop();
		return 1; //从机地址写入失败
	}
	IIC_Send_Byte(reg); //发送寄存器地址
	IIC_Wait_Ack();	  
	IIC_Send_Byte(data); 
	if(IIC_Wait_Ack())
	{
		IIC_Stop(); 
		return 1; //数据写入失败
	}
	IIC_Stop(); //产生一个停止条件

  //return 1; //status == 0;
	return 0;
}

u8 IIC_ReadMultByteFromSlave(u8 dev, u8 reg, u8 length, uint8_t *data)
{
  u8 count = 0;
	u8 temp;
	IIC_Start();
	IIC_Send_Byte(dev); //发送从机地址
	if(IIC_Wait_Ack())
	{
		IIC_Stop(); 
		return 1; //从机地址写入失败
	}
	IIC_Send_Byte(reg); //发送寄存器地址
  IIC_Wait_Ack();	  
	IIC_Start();
	IIC_Send_Byte(dev+1); //进入接收模式	
	IIC_Wait_Ack();
  for(count=0;count<length;count++)
	{
		if(count!=(length-1))
		temp = IIC_Read_Byte(1); //带ACK的读数据
		else  
		temp = IIC_Read_Byte(0); //最后一个字节NACK

		data[count] = temp;
	}
    IIC_Stop(); //产生一个停止条件
    //return count;
	 return 0;
}

u8 IIC_WriteMultByteToSlave(u8 dev, u8 reg, u8 length, uint8_t* data)
{
  
 	u8 count = 0;
	IIC_Start();
	IIC_Send_Byte(dev); //发送从机地址
	if(IIC_Wait_Ack())
	{
		IIC_Stop();
		return 1; //从机地址写入失败
	}
	IIC_Send_Byte(reg); //发送寄存器地址
  IIC_Wait_Ack();	  
	for(count=0;count<length;count++)
	{
		IIC_Send_Byte(data[count]); 
		if(IIC_Wait_Ack()) //每一个字节都要等从机应答
		{
			IIC_Stop();
			return 1; //数据写入失败
		}
	}
	IIC_Stop(); //产生一个停止条件

	return 0;
}


