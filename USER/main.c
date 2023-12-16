#include "sys.h"
#include "bsp_i2c.h"
#include "ad517x_lib.h"
#include "bsp_nxp9698.h"
#include "i2c_device.h"
#include "uart_cmd.h"
#include "adc.h"

#include "bsp_MxN.h"
#include "bsp_C1X2G.h"
#include "bsp_D2X2B.h"
#include "bsp_M1X4.h"
#include "bsp_S1X4.h"
#include "bsp_S1X8.h"



#define UART_CMD_LIB


/// @brief 定义全局对象
AD527xObjectType Ad5175_object;

/// @brief 函数声明
void SetRadcPlace(uint16_t value);
void ReadRDACValue(uint16_t value);
void AD5175_RST(uint16_t value);

void PCA9698_READ(uint16_t value);
void I2C_GetPcaID(uint16_t value);
void I2C_GetIoStata(uint16_t value);
void I2C_ReadPcaGPIO(uint16_t value);
void Get_ADC1_4_Value(uint16_t value);
void MXN_TOOGLE(uint16_t value);

void C1X2G_Chenck_Fun(CMD_Parame *parame);
void C1X2G_State_B(CMD_Parame *parame);
void C1X2G_State_A(CMD_Parame *parame);
void C1X2G_StateSwitch(CMD_Parame *parame);


/// @brief BSP INIT
void bsp_Init(void)
{
	ad5175_Init();
	nxp_Init();
	Adc_Init();

	M1X1_GPIO_Init();
	C1X2G_GPIO_Init();
	D2X2B_GPIO_Init();
	M1X4_GPIO_Init();
	S1X4_GPIO_Init();
	
#ifdef USER_I2C
	I2c_Init();
	
	CHENCK_DRIVER(0x40);
	CHENCK_DRIVER(0x58);

		
	AD527xInitialization(&Ad5175_object,
						 0x58,
						 AD5270,
						 AD517x_Receive,
						 AD517x_Ttansmit,
						 AD517x_delay);	
	//AD5175 控制寄存器初始化
	ad5175_Crtl_Init(&Ad5175_object);
#else 	

	Bsp_I2c_Init();
#endif
	
	
}

int main(void)
{
	HAL_Init(); 
	Stm32_Clock_Init(96,8,2,4);
	delay_init(96);	
	uart_init(115200);
	bsp_Init();
	
	Cmd_Class cmdTable[]={
							{"C1X2G",C1X2G_Chenck_Fun},
							{"C1X2_STATE",C1X2G_StateSwitch}
						 };
					   
	Logic_CmdFun(cmdTable,SIZE_ARRAY(cmdTable));

	if(HAL_I2C_IsDeviceReady(&hi2c,0x58,10,1000) == HAL_OK) 
		printf("AD5175 SUCCES\n");
	if(HAL_I2C_IsDeviceReady(&hi2c,0x40,10,1000) == HAL_OK) 
		printf("PCA9698 SUCCES\n");
	
	uint8_t Data[] ={0xff,0xff,0xff,0xff,0xff};
	WireMoreByteToReg(IOC0_CMD,Data,5);
	
	
	while(1)
	{
		if(Cmd_flag){
			Cmd_flag = 0;
			CmdTable_Traversal((char*)CmdBuffer);
		}
	}
}


//重复切换
void C1X2G_Chenck_Fun(CMD_Parame *parame)
{
	Switch = ON;
	C1X2G_CHENCK(parame->parame1,parame->parame2,lock);
}
//状态切换
void C1X2G_StateSwitch(CMD_Parame *parame)
{
	
	switch(*parame->para){
		case 'A':Latch_C1X2_StateA(20);break;
		case 'B':Latch_C1X2_StateB(20);break;
		default:printf("C1X2G State Error\n");
			break;
	}
}
