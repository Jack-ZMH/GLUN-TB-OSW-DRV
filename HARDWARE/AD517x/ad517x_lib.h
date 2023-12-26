#ifndef AD517X_LIB_H
#define AD517X_LIB_H

#include "sys.h"
#include "stdint.h"
#include "stdbool.h"

#define AD5175_eRST	 				GPIO_PIN_0
#define AD5175_GPIO_PORT            GPIOC

void ad5175_Init(void);

#define AD5175_ADDR				0x58
#define AD5175_50TP_ENABLE		0x01
#define AD5175_50TP_DISABLE		0x00
#define AD5175_RDAC_ENABLE		0x02
#define AD5175_RDAC_DISABLE		0x00

#define SOFT_NORMAL_MODE		0x00
#define SOFT_SHUTOFF_MODE		0x01

typedef enum AD527x {
  AD5270 = 1,
  AD5271,
  AD5272,
  AD5274,
  AD5175
}AD527xType;

//申明结构体名称
typedef struct AD527xObject AD527xObjectType;



/*定义用于SPI接口的对象类型*/
typedef struct AD527xObject {
  AD527xType type;      //设备类型
  uint8_t devAddress;   //设备地址,用于I2C接口
  uint8_t conreg;       //控制寄存器
  uint16_t rdac;        //游标寄存器现值
  uint16_t (*Receive)(struct AD527xObject *rx,uint8_t *rData);
  uint8_t (*Transmit)(struct AD527xObject *rx,uint8_t *wData);
  void (*Delayms)(volatile uint32_t nTime);//ms延时操作指针
}AD527xObjectType;

/*定义接收数据函数指针类型*/
typedef uint16_t (*AD527xReceive)(AD527xObjectType *rx,uint8_t *rData);
/*定义发送数据函数指针类型*/
typedef uint8_t (*AD527xTransmit)(AD527xObjectType *rx,uint8_t *wData);
/*定义ms延时操作指针*/
typedef void (*AD527xDelayms)(volatile uint32_t nTime);

uint16_t AD517x_Receive(AD527xObjectType *rx,uint8_t *rData);
uint8_t AD517x_Ttansmit(AD527xObjectType *rx,uint8_t *wData);
void AD517x_delay(volatile uint32_t nTime);

void AD527xInitialization(AD527xObjectType *rx,
                          uint8_t address,
                          AD527xType type,
                          AD527xReceive recieve,
                          AD527xTransmit transmit,
                          AD527xDelayms delayms);

//写命令函数
uint8_t AD527xWriteRegister(AD527xObjectType *rx,uint8_t cmd,uint16_t nData);
//读命令函数
uint16_t AD527xReadRegister(AD527xObjectType *rx,uint8_t cmd,uint8_t addr);

//AD5175设备初始化
void ad5175_Crtl_Init(AD527xObjectType *rx);

//设置控制寄存器的值
void SetControlRegister(AD527xObjectType *rx,uint16_t value);
//读控制寄存器的值
void ReadControlRegister(AD527xObjectType *rx);

//设置软件关断模式
void SetSoftShutMode(AD527xObjectType *rx,uint8_t mode);

/* 读取最后一次50-TP编程存储器位置的地址 */
uint16_t ReadLast50TPAddress(AD527xObjectType *rx);
/* 读指定存储位置的数据 */
uint16_t ReadGivenAddressValue(AD527xObjectType *rx,uint8_t address);

/* 软件复位 */
void AD527xSoftwareReset(AD527xObjectType *rx);

/* 存储游标设置：将RDAC设置存储到50-TP中 */
void StoreRDACTo50TP(AD527xObjectType *rx);

/* 读取RDAC游标寄存器的内容 */
uint16_t ReadRDACFromAd527x(AD527xObjectType *rx);
/* 设置AD527x游标位置 */
void SetRDACForAd527x(AD527xObjectType *rx,uint16_t data);

#endif



