#include "sys.h"
#include "bsp_i2c.h"
#include "ad517x_lib.h"
#include "bsp_nxp9698.h"
#include "i2c_device.h"
#include "uart_cmd.h"
#include "adc.h"
#include "bsp_key.h"

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
void C1X2G_Chenck_Fun(CMD_Parame *parame);
void C1X2G_StateSwitch(CMD_Parame *parame);

void D2X2B_Chenck_Fun(CMD_Parame *parame);
void D2X2B_StateSwitch(CMD_Parame *parame);

void M1X1_Chenck_Fun(CMD_Parame *parame);
void M1X1_StateSwitch(CMD_Parame *parame);

void M1X4_Chenck_Fun(CMD_Parame *parame);
void M1X4_StateSwitch(CMD_Parame *parame);

void S1X4_Chenck_Fun(CMD_Parame *parame);
void S1X4_StateSwitch(CMD_Parame *parame);

void S1X8_Chenck_Fun(CMD_Parame *parame);
void S1X8_StateSwitch(CMD_Parame *parame);




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
	
#ifdef USER_SIMULATE_I2C
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
	KEY_GPIO_Init();
#endif
	
	
}

int main(void)
{
	uint8_t key = 0;
	uint8_t auto_falg = 0;
	HAL_Init(); 
	Stm32_Clock_Init(96,8,2,4);
	delay_init(96);	
	uart_init(115200);
	bsp_Init();
	
	Cmd_Class cmdTable[]={
							{"C1X2G",C1X2G_Chenck_Fun},
							{"C1X2_STATE",C1X2G_StateSwitch},
							{"D2X2B",D2X2B_Chenck_Fun},
							{"D2X2B_STATE",D2X2B_StateSwitch},
							{"M1X1",M1X1_Chenck_Fun},
							{"M1X1_STATE",M1X1_StateSwitch},
							{"M1X4",M1X4_Chenck_Fun},
							{"M1X4_STATE",M1X4_StateSwitch},
							{"S1X4",S1X4_Chenck_Fun},
							{"S1X4_STATE",S1X4_StateSwitch},
							{"S1X8",S1X8_Chenck_Fun},
							{"S1X8_STATE",S1X8_StateSwitch}
						 };
					   
	Logic_CmdFun(cmdTable,SIZE_ARRAY(cmdTable));

	if(HAL_I2C_IsDeviceReady(&hi2c,0x58,10,1000) == HAL_OK) 
		printf("AD5175 SUCCES\n");
	if(HAL_I2C_IsDeviceReady(&hi2c,0x40,10,1000) == HAL_OK) 
		printf("PCA9698 SUCCES\n");
	
	//初始化PCA9698 IO口为输入
	uint8_t Data[] ={0xff,0xff,0xff,0xff,0xff};
	WireMoreByteToReg(IOC0_CMD,Data,5);
	
	
	while(1)
	{
		if(Cmd_flag){
			Cmd_flag = 0;
			CmdTable_Traversal((char*)CmdBuffer);
		}
		if(Switch)
			C1X2G_CHENCK(20,1000,0);
	}
}


//重复切换
void C1X2G_Chenck_Fun(CMD_Parame *parame)
{
	Switch = ON;
	C1X2G_CHENCK(parame->parame1,parame->parame2,parame->type);
}
//状态切换
void C1X2G_StateSwitch(CMD_Parame *parame)
{
	
	switch(parame->status){
		case A:Latch_C1X2_StateA(20);break;
		case B:Latch_C1X2_StateB(20);break;
		default:printf("C1X2G State Error\n");
			break;
	}
}

/// @brief D2X2B_Chenck_Fun
/// @param parame 
void D2X2B_Chenck_Fun(CMD_Parame *parame)
{
	Switch = ON;
	D2X2B_CHENCK(parame->parame1,parame->parame2);

}
void D2X2B_StateSwitch(CMD_Parame *parame)
{
	switch(parame->status){
		case A:D2X2B_State_Cross(20);break;
		case B:D2X2B_State_Bar(20);break;
		default:printf("D2X2B State Error\n");
			break;
	}
}

void M1X1_Chenck_Fun(CMD_Parame *parame)
{
	Switch = ON;
	M1X1_CHENCK(parame->parame1,parame->parame2);
}
void M1X1_StateSwitch(CMD_Parame *parame)
{
	switch(parame->status){
		case A:M1X1_StateA(20);break;
		case B:M1X1_StateB(20);break;
		default:printf("M1X1 State Error\n");
			break;
	}
}

void M1X4_Chenck_Fun(CMD_Parame *parame)
{
	Switch = ON;
	M1X4_CHENCK(parame->parame1,parame->parame2,parame->type);
}
void M1X4_StateSwitch(CMD_Parame *parame)
{
	if(parame->type == lock){
		switch(parame->status){
			case A:M1X4_State_A(20);break;
			case B:M1X4_State_B(20);break;
			case C:M1X4_State_C(20);break;
			case D:M1X4_State_D(20);break;
			default:printf("M1X4 State Error\n");
				break;
		}
	}
	else if(parame->type == nolock) {
		switch(parame->status){
			case A:NonLatching_M1X4State_A(20);break;
			case B:NonLatching_M1X4State_B(20);break;
			case C:NonLatching_M1X4State_C(20);break;
			case D:NonLatching_M1X4State_D(20);break;
			default:printf("M1X4 State Error\n");
				break;
		}

	}
	else 
	{
		printf("M1X4 TYPE Error\n");
	}
}

void S1X4_Chenck_Fun(CMD_Parame *parame)
{
	Switch = ON;
	S1X4_CHENCK(parame->parame1,parame->parame2,parame->type);

}
void S1X4_StateSwitch(CMD_Parame *parame)
{
	if(parame->type == lock){
		switch(parame->status){
			case A:Latch_S1X4_COMP1(20);break;
			case B:Latch_S1X4_COMP2(20);break;
			case C:Latch_S1X4_COMP3(20);break;
			case D:Latch_S1X4_COMP4(20);break;
			default:printf("S1X4 State Error\n");
				break;
		}
	}
	else if(parame->type == nolock) {
		switch(parame->status){
			case A:NonLatch_S1X4_COMP1(20);break;
			case B:NonLatch_S1X4_COMP2(20);break;
			case C:NonLatch_S1X4_COMP3(20);break;
			case D:NonLatch_S1X4_COMP4(20);break;
			default:printf("S1X4 State Error\n");
				break;
		}

	}
	else 
	{
		printf("S1X4 TYPE Error\n");
	}	

}

void S1X8_Chenck_Fun(CMD_Parame *parame)
{
	Switch = ON;
	Latch_S1X8_CHENCH(parame->parame1,parame->parame2,parame->type);
}
void S1X8_StateSwitch(CMD_Parame *parame)
{
	if(parame->type == lock){
		switch(parame->status){
			case A:Latch_S1X8_COM_P1(20);break;
			case B:Latch_S1X8_COM_P2(20);break;
			case C:Latch_S1X8_COM_P3(20);break;
			case D:Latch_S1X8_COM_P4(20);break;
			case E:Latch_S1X8_COM_P5(20);break;
			case F:Latch_S1X8_COM_P6(20);break;
			case G:Latch_S1X8_COM_P7(20);break;
			case H:Latch_S1X8_COM_P8(20);break;
			default:printf("S1X8 State Error\n");
				break;
		}
	}
	else if(parame->type == nolock) {
		switch(parame->status){
			case A:NonLatch_S1X8_COM_P1(20);break;
			case B:NonLatch_S1X8_COM_P2(20);break;
			case C:NonLatch_S1X8_COM_P3(20);break;
			case D:NonLatch_S1X8_COM_P4(20);break;
			case E:NonLatch_S1X8_COM_P5(20);break;
			case F:NonLatch_S1X8_COM_P6(20);break;
			case G:NonLatch_S1X8_COM_P7(20);break;
			case H:NonLatch_S1X8_COM_P8(20);break;
			default:printf("S1X8 State Error\n");
				break;
		}

	}
	else 
	{
		printf("S1X8 TYPE Error\n");
	}

}

