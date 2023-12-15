#ifndef BSP_NXP9868_H
#define BSP_NXP9868_H
#include "sys.h"
#include "bsp_i2c.h"
#include "i2c_device.h"

#define NXP9868_eRST	 			GPIO_PIN_8
#define NXP9868_eINT	 			GPIO_PIN_9
#define NXP9868_eOE		 			GPIO_PIN_5
#define NXP9868_GPIO_PORT           GPIOB

#define NXP_9868_ADDR				0x40 //基地址
#define NXP_9868_WIRE               (NXP_9868_ADDR|0X00) //写地址
#define NXP_9868_READ               (NXP_9868_ADDR|0X01) //读地址
#define AUTO_INCREMENT              0x80

#define RESPONES_ADDR				0x19  //警报输出
#define ALLCAL_ADDR					0xDC  //所有GPIO
#define DEVICEID_ADDR				0xF8  //设备ID

#define OUTCONF_CMD                 0x28  //输出结构
#define ALLBANK_CMD                 0x29  //所有bank 
#define MODESEL_CMD                 0x2A  //芯片模式选择

#define ALLBANK_BSEL_ON             0x80    //BSEL 过滤器
#define ALLBANK_BSEL_OFF            0x00

/* 控制BANK页指令 */
#define ALLBANK_BANK0               0x01    /* bank0 所有IO 为 H*/
#define ALLBANK_BANK1               0x02
#define ALLBANK_BANK2               0x04
#define ALLBANK_BANK3               0x08
#define ALLBANK_BANK4               0x10

/* pca9698模式配置指令 */
#define MODESEL_OE_L                0x00  
#define MODESEL_OE_H                0x01
#define MODESEL_OCH_STOP            0x00
#define MODESEL_OCH_ASK             0x02 //默认使用
#define MODESEL_IOAC_NOCALL         0x00
#define MODESEL_IOAC_CALL           0x80 //开启 GPIO All Call 命令后，芯片只能写，不能读
#define MODESEL_SMBA_NASK           0x00
#define MODESEL_SMBA_ASK            0x10 //开启后，GPIO状态再I2C应答时候就会改变，否则实在I2C产生STOP信号之后改变    

//GPIO宏
#define GPIO_Pin_0                 	0x00
#define GPIO_Pin_1                 	0x01
#define GPIO_Pin_2                 	0x02
#define GPIO_Pin_3                 	0x03
#define GPIO_Pin_4                 	0x04
#define GPIO_Pin_5                 	0x05
#define GPIO_Pin_6                 	0x06
#define GPIO_Pin_7                 	0x07


typedef enum
{
  PCA_PIN_RESET = 0,
  PCA_PIN_SET
}PCA_PIN_State;

typedef enum
{
  PCA_PIN_OUTPUT = 0,
  PCA_PIN_INPUT
}PCA_PIN_Dir;

typedef enum
{
  PCA_MSK_ENABLE = 0,
  PCA_PIN_DISABLE
}PCA_PIN_Mask;

typedef enum
{
  PCA_MSK_OD = 0,
  PCA_PIN_PP
}PCA_PIN_Mode;

/// @brief ip 输入寄存器命令
/// @brief 只读 H:1 L:0
typedef enum {
    IP0_CMD = 0x00,
    IP1_CMD,
    IP2_CMD,
    IP3_CMD,
    IP4_CMD
}CMD_IPTypeDef;

/// @brief OP 输出寄存器命令
/// @brief 输出 H:1 L:0
typedef enum {
    OP0_CMD = 0x08,
    OP1_CMD,
    OP2_CMD,
    OP3_CMD,
    OP4_CMD
}CMD_OPTypeDef;

/// @brief PI 反转寄存器命令
/// @brief 反转IO极性 高有效
typedef enum {
    PI0_CMD = 0x10,
    PI1_CMD,
    PI2_CMD,
    PI3_CMD,
    PI4_CMD
}CMD_PITypeDef;

/// @brief IOC IO配置寄存器
/// @brief 配置IO方向
typedef enum {
    IOC0_CMD = 0x18,
    IOC1_CMD,
    IOC2_CMD,
    IOC3_CMD,
    IOC4_CMD
}CMD_IOCTypeDef;

/// @brief MASK IRQ CTRL寄存器
/// @brief 1 不产生中断 0 产生中断 
/// @brief 初始化时应该关闭中断产生
typedef enum {
    MASK0_CMD = 0x20,
    MASK1_CMD,
    MASK2_CMD,
    MASK3_CMD,
    MASK4_CMD
}CMD_MASKTypeDef;

uint8_t nxp_Init(void);

//读取设备信息
void ReadDeviceID(void);

//写寄存器函数
uint8_t WriteMoreByteData(uint8_t DviceAddr,uint8_t cmd,uint8_t *nData,uint8_t len);
uint8_t WriteSpecificPort(uint8_t DviceAddr,uint8_t cmd,uint8_t nData);
uint8_t WireStructBankModeSElReg(uint8_t DviceAddr,uint8_t cmd,uint8_t nData);

//读寄存器函数
uint8_t ReadMoreRegData(uint8_t Addr,uint8_t cmd,uint8_t *nData,uint8_t len);
uint8_t ReadRegData(uint8_t DviceAddr,uint8_t cmd);
uint8_t ReadStructBankModeSelReg(uint8_t DviceAddr,uint8_t cmd);



/// @brief 硬件I2C使用 
uint8_t ReadByteForReg(uint8_t regaddr,uint8_t *Data);
uint8_t ReadMoreByteForReg(uint8_t regaddr, uint8_t Data[],uint8_t size);
uint8_t WireMoreByteToReg(uint8_t regaddr, uint8_t Data[],uint8_t size);
uint8_t WireByteToReg(uint8_t regaddr,uint8_t Data);

uint8_t PCA_GPIO_DirConfig(CMD_IOCTypeDef GPIOx,uint8_t GPIO_Pin,PCA_PIN_Dir GPIO_Dir);
uint8_t PCA_GPIO_WritePin(CMD_OPTypeDef GPIOx,uint8_t GPIO_Pin,PCA_PIN_State PinState);
uint8_t PCA_GPIO_ReadPin(CMD_IPTypeDef GPIOx,uint8_t GPIO_Pin);
uint8_t PCA_GPIO_Pin_Toggle(CMD_PITypeDef GPIOx,uint8_t GPIO_Pin);
uint8_t PCA_GPIO_Pin_Mask(CMD_MASKTypeDef GPIOx,uint8_t GPIO_Pin,PCA_PIN_Mask PinMask);

uint8_t PCA_GPIO_PinModeCtrl(PCA_PIN_Mode Pin_Mode);
uint8_t PCA_AllBANK_Ctrl(uint8_t BankState);
uint8_t PCA_MODE_Config(void);


uint8_t READ_TwoPin(CMD_IPTypeDef GPIOx,uint8_t GPIO_Pin1,uint8_t GPIO_Pin2);
#endif

