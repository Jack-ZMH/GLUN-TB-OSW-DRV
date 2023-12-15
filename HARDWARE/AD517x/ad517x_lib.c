#include "ad517x_lib.h"
#include "bsp_i2c.h"

/* 定义操作命令 */
#define COMMAND_NOP                     (0x00)
#define COMMAND_W_RDAC                  (0x01)
#define COMMAND_R_RDAC                  (0x02)
#define COMMAND_STORE_RDAC_50TP         (0x03)
#define COMMAND_SOFTWARE_RESET          (0x04)
#define COMMAND_R_50TP_NEXT_FRAME       (0x05)
#define COMMAND_R_LAST_50TP_LOCATION    (0x06)
#define COMMAND_W_CONTROL               (0x07)
#define COMMAND_R_CONTROL               (0x08)
#define COMMAND_SOFTWARE_SHUTDOWN       (0x09)

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
}

void ad5175_Crtl_Init(AD527xObjectType *rx)
{
	//AD5175初始化
	SetControlRegister(rx,0x03); //开启C0 C1
	ReadControlRegister(rx);
	printf("AD51Dvice:%d ConReg = %d\n",rx->type,rx->conreg);
}


// 写两字节
uint8_t AD517x_Ttansmit(AD527xObjectType *rx,uint8_t *wData)
{
	
	bool Ask = false;
	i2c_start();	//开始信号
    i2c_write_byte(rx->devAddress); //发送地址

	Ask = i2c_wait_ask(); //等待ADK
	if(Ask)	
		goto error2;  
		
    i2c_write_byte(*(wData ++)); //发送高8位
    Ask = i2c_wait_ask();
	if(Ask)
		goto error2;
		
    i2c_write_byte(*wData);//发送低8位
    Ask = i2c_wait_ask();
	if(Ask)
		goto error2;
		
    i2c_stop();
    return 0; 
	
error2:
   printf("SEND ERROR!\r\n");
   return 1;
}


// 读取两字节
uint16_t AD517x_Receive(AD527xObjectType *rx,uint8_t *rData)
{
    i2c_start();
    i2c_write_byte(rx->devAddress|0x01);
    if(i2c_wait_ask()) 
			goto error1;
    
    *(rData++) = i2c_read_byte(); //读取高8位
    i2c_ask(); //发送应答
	
    *rData = i2c_read_byte();//读取低8位
    i2c_nask(); //发送非应答
	
    i2c_stop();//结束通信
    return *rData; 
	
error1:
	printf("READ ERROR!\r\n");
    return 1;
}
// 延迟
void AD517x_delay(volatile uint32_t nTime)
{
    delay_ms(nTime);
}


//初始化LIB
void AD527xInitialization(AD527xObjectType *rx,
                          uint8_t address,
                          AD527xType type,
                          AD527xReceive recieve,
                          AD527xTransmit transmit,
                          AD527xDelayms delayms)
{
    if(rx==NULL)return;
    if((address==0x58)||(address==0x5C)||(address==0x5E)){
        rx->devAddress=address;
    }
    else if((address==0x2C)||(address==0x2E)||(address==0x2F)){
        rx->devAddress=address<<1;
    }
    else{
        rx->devAddress=0x00;
        goto error;
    }
    rx->type=type;
    rx->conreg=0x00;
    rx->rdac=0x0000;
	
    rx->Receive=recieve;  //函数指针指向回调函数
    rx->Transmit=transmit;
    rx->Delayms=delayms; 
	return;
error:
	printf("Driver ERROR!\n");
}


/* 写寄存器操作 */
uint8_t AD527xWriteRegister(AD527xObjectType *rx,uint8_t cmd,uint16_t nData)
{
    uint8_t tData[2];    
    tData[0] = (uint8_t)((cmd << 2) | (nData >> 8));
    tData[1] = (uint8_t)(nData & 0xff);
    return rx->Transmit(rx,tData);
}

/* 读寄存器操作 */
uint16_t AD527xReadRegister(AD527xObjectType *rx,uint8_t cmd,uint8_t addr)
{
    uint8_t ucData[2];
   	uint16_t nNumber;
	
	ucData[0] = cmd << 2;
	ucData[1] = 0x00;
    rx->Transmit(rx,ucData);//先发送读命令
	
    rx->Receive(rx,ucData);
    nNumber = ucData[0] & 0x3;
    nNumber = (nNumber << 8) + ucData[1];
    return nNumber;     
}


//读控制寄存器的值
void ReadControlRegister(AD527xObjectType *rx)
{
	rx->conreg = AD527xReadRegister(rx,COMMAND_R_CONTROL,0x00); 
}
//设置控制寄存器的值
void SetControlRegister(AD527xObjectType *rx,uint16_t value)
{
	AD527xWriteRegister(rx,COMMAND_W_CONTROL,value);
	rx->Delayms(10);
	ReadControlRegister(rx);	
}

//设置软件关断模式
void SetSoftShutMode(AD527xObjectType *rx,uint8_t mode)
{
	 AD527xWriteRegister(rx,COMMAND_SOFTWARE_SHUTDOWN,mode);
}

/* 读取最后一次50-TP编程存储器位置的地址 */
uint16_t ReadLast50TPAddress(AD527xObjectType *rx)
{
  uint8_t cmd=COMMAND_R_LAST_50TP_LOCATION;	
  return AD527xReadRegister(rx,cmd,0x00);

}

/* 读指定存储位置的数据 */
uint16_t ReadGivenAddressValue(AD527xObjectType *rx,uint8_t address)
{
  uint8_t cmd = COMMAND_R_50TP_NEXT_FRAME;	
  return   AD527xReadRegister(rx,cmd,address);
}

/* 软件复位 */
void AD527xSoftwareReset(AD527xObjectType *rx)
{
  uint8_t cmd=COMMAND_SOFTWARE_RESET;

  AD527xWriteRegister(rx,cmd,0x00);
  rx->Delayms(10); //软件复位之后需要个延时
}

/* 存储游标设置：将RDAC设置存储到50-TP中 */
void StoreRDACTo50TP(AD527xObjectType *rx)
{
  uint16_t cmd=COMMAND_STORE_RDAC_50TP;
	
  if(((rx->conreg)&0x01)!=0x01)
  {
	  SetControlRegister(rx,0x03);
  }
	
  AD527xWriteRegister(rx,cmd,0x00);
  rx->Delayms(500);	//将RDAC值写入50TP需要用350ms时间
}

/* 读取RDAC游标寄存器的内容 */
uint16_t ReadRDACFromAd527x(AD527xObjectType *rx)
{
  uint8_t cmd=COMMAND_R_RDAC;
  AD527xWriteRegister(rx,cmd,0x00);
  rx->rdac=AD527xReadRegister(rx,cmd,0x00); 
  return rx->rdac;
}

/* 设置AD527x游标位置 */
void SetRDACForAd527x(AD527xObjectType *rx,uint16_t data)
{
  uint16_t temp=0;
  
  if((rx->type==AD5271)||(rx->type==AD5274))	//256档
  {
    temp=data>255?255:data;
  }
  else if((rx->type==AD5270)||(rx->type==AD5272)||(rx->type==AD5175))	//1024档
  {
    temp=data>1023?1023:data;
  }
	
  //temp=COMMAND_W_RDAC|temp;
	
  if(((rx->conreg)&0x02)!=0x02)
  {
    SetControlRegister(rx,0x20);
  }
  AD527xWriteRegister(rx,COMMAND_W_RDAC,temp);
  //ReadRDACFromAd527x(rx);
}
