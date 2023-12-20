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

/********************命令表*******************************
* 1、自动检测：< 型号：LATCH/NONLATCH:AUTO:ON >
* 2、状态切换：< 型号：LATCH/NONLATCH:STATE:状态 >
* 3、型号选择：< SWITCH:型号 >
* 4、时间设置：< TIMER SET:时间>
* 5、时间获取：< TIMER?>
* 6、电压获取：< AD?:VOLTAGE >
* 7、功率获取：< AD?:POWER >
**********************************************************/

/// @brief 定义全局对象
AD527xObjectType Ad5175_object;
Typedef_Select TYPEFEF_SELECT;

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

void Switch_select(CMD_Parame *parame);
void GetADDATA(CMD_Parame *parame);
void Get_TextTimer(CMD_Parame *parame);
void Set_Timer(CMD_Parame *parame);

/// @brief BSP INIT
void bsp_Init(void)
{
	ad5175_Init();
	nxp_Init();
	Adc_Init();

	C1X2G_GPIO_Init();
	D2X2B_GPIO_Init();
	M1X1_GPIO_Init();
	M1X4_GPIO_Init();
	S1X4_GPIO_Init();
	S1X8_GPIO_Init();
	
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

	HAL_Init(); 
	Stm32_Clock_Init(96,8,2,4);
	delay_init(96);	
	uart_init(115200);
	bsp_Init();
	
	Cmd_Class cmdTable[]={
							{"C1X2G",C1X2G_Chenck_Fun},
							{"D2X2B",D2X2B_Chenck_Fun},
							{"M1X4",M1X1_Chenck_Fun},
							{"M1X4",M1X4_Chenck_Fun},
							{"S1X4",S1X4_Chenck_Fun},
							{"S1X8",S1X8_Chenck_Fun},
							{"SWITCH",Switch_select},
							{"AD?",GetADDATA},
							{"TIMERSET",Set_Timer},
							{"TIMER?",Get_TextTimer}							
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
		if(Cmd_flag)
		{
			Cmd_flag = 0;
			CmdTable_Traversal((char*)CmdBuffer);
		}
		if(sel_falg)
		{
			sel_falg = false;
			TYPEFEF_SELECT++;
			if(TYPEFEF_SELECT > 0x05)
				TYPEFEF_SELECT = C1X2G_t;
			printf("Switch Type :%s\n",switch_types[TYPEFEF_SELECT].str);
		}
		if(Switch == ON)
		{
			switch(TYPEFEF_SELECT)
			{
				case C1X2G	:C1X2G_CHENCK(Cmd_Parame.timer,1,Cmd_Parame.type);break;
				case D2X2B	:D2X2B_CHENCK(Cmd_Parame.timer,1);break;
				case M1X1	:M1X1_CHENCK(Cmd_Parame.timer,1);break;
				case M1X4	:M1X4_CHENCK(Cmd_Parame.timer,1,Cmd_Parame.type);break;
				case S1X4	:S1X4_CHENCK(Cmd_Parame.timer,1,Cmd_Parame.type);break;
				case S1X8	:Latch_S1X8_CHENCH(Cmd_Parame.timer,1,Cmd_Parame.type);break;
				default:break;
			
			}
		}
	}
}

/// @brief Set_Timer
/// @param parame 
void Set_Timer(CMD_Parame *parame){
	char *current = parame->cmd;
	while (*current) {
        if (!isdigit((unsigned char)*current)){
            
			printf("Timer Set Cmd Error\n");
			return;
        }
        current++;
    }
	Cmd_Parame.timer = atoi(parame->cmd);
	printf("Timer Set Succes:%d\n",Cmd_Parame.timer);
}
/// @brief Get_TextTimer
/// @brief 获取切换时间间隔
/// @param parame 
void Get_TextTimer(CMD_Parame *parame){
	printf("Timer:%d\n",parame->timer);
}

/// @brief GetADDATA 获取电压
/// @param parame 
void GetADDATA(CMD_Parame *parame){
	// 总电压
	if(strcmp(parame->cmd,"VOLTAGE") == 0){
		printf("VCC CURRENT:%0.2f V\n",(float)(Get_Adc_Average(ADC_CHANNEL_4,50)-100)*12/1000);
	}
	// 功率
	else if(strcmp(parame->cmd,"POWER") == 0)
	{
		printf("VCC:%0.2f\n",(float)(Get_Adc_Average(ADC_CHANNEL_5,50)));
	}
	else
	{
		printf("AD? Cmd Error\n");
	}
}

/// @brief 光开关类型选择
/// @param parame 
void Switch_select(CMD_Parame *parame){
	for(uint8_t i =0;i<6;i++)
	{
		if(strcmp(parame->cmd,switch_types[i].str) == 0)
		{
			TYPEFEF_SELECT = (Typedef_Select)switch_types[i].value;
			printf("Switch Type :%s\n",switch_types[i].str);
		}
	}
}


/// @brief 自动检测
/// @param parame 
void C1X2G_Chenck_Fun(CMD_Parame *parame){
	if(parame->option == AUTO&&parame->onoff == ON){
		Switch = ON;
		C1X2G_CHENCK(parame->timer,1,parame->type);
	}
	else if(parame->option == STATE)
	{
		C1X2G_StateSwitch(parame);
	}
}
/// @brief 状态切换
/// @param parame 
void C1X2G_StateSwitch(CMD_Parame *parame){
	
	switch(parame->state){
		case A:Latch_C1X2_StateA(20);break;
		case B:Latch_C1X2_StateB(20);break;
		default:printf("C1X2G State Error\n");
			break;
	}
}

/// @brief D2X2B_Chenck_Fun
/// @param parame 
void D2X2B_Chenck_Fun(CMD_Parame *parame){
	if(parame->option == AUTO&&parame->onoff == ON){
		Switch = ON;
		D2X2B_CHENCK(parame->timer,1);
	}
	else if(parame->option == STATE)
	{
		D2X2B_StateSwitch(parame);
	}

}

/// @brief D2X2B_StateSwitch
/// @param parame 
void D2X2B_StateSwitch(CMD_Parame *parame){
	switch(parame->state){
		case A:D2X2B_State_Cross(20);break;
		case B:D2X2B_State_Bar(20);break;
		default:printf("D2X2B State Error\n");
			break;
	}
}

/// @brief M1X1_Chenck_Fun
/// @param parame 
void M1X1_Chenck_Fun(CMD_Parame *parame){
	if(parame->option == AUTO&&parame->onoff == ON){
		Switch = ON;
		M1X1_CHENCK(parame->timer,1);
	}
	else if(parame->option == STATE){
		M1X1_StateSwitch(parame);
	}
}

/// @brief M1X1_StateSwitch
/// @param parame 
void M1X1_StateSwitch(CMD_Parame *parame){
	switch(parame->state){
		case A:M1X1_StateA(20);break;
		case B:M1X1_StateB(20);break;
		default:printf("M1X1 State Error\n");
			break;
	}
}

/// @brief M1X4_Chenck_Fun
/// @param parame 
void M1X4_Chenck_Fun(CMD_Parame *parame){
	if(parame->option == AUTO&&parame->onoff == ON){
		Switch = ON;
		M1X4_CHENCK(parame->timer,1,parame->type);
	}
	else if(parame->option == STATE){
		M1X4_StateSwitch(parame);
	}
}

/// @brief M1X4_StateSwitch
/// @param parame 
void M1X4_StateSwitch(CMD_Parame *parame){
	if(parame->type == LATCH){
		switch(parame->state){
			case A:M1X4_State_A(20);break;
			case B:M1X4_State_B(20);break;
			case C:M1X4_State_C(20);break;
			case D:M1X4_State_D(20);break;
			default:printf("M1X4 State Error\n");
				break;
		}
	}
	else if(parame->type == NONLATCH) {
		switch(parame->state){
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

/// @brief S1X4_Chenck_Fun
/// @param parame 
void S1X4_Chenck_Fun(CMD_Parame *parame){
	if(parame->option == AUTO &&parame->onoff == ON){
		Switch = ON;
		S1X4_CHENCK(parame->timer,1,parame->type);
	}
	else if(parame->option == STATE){
		S1X4_StateSwitch(parame);
	}

}

/// @brief S1X4_StateSwitch
/// @param parame 
void S1X4_StateSwitch(CMD_Parame *parame){
	if(parame->type == LATCH){
		switch(parame->state){
			case A:Latch_S1X4_COMP1(20);break;
			case B:Latch_S1X4_COMP2(20);break;
			case C:Latch_S1X4_COMP3(20);break;
			case D:Latch_S1X4_COMP4(20);break;
			default:printf("S1X4 State Error\n");
				break;
		}
	}
	else if(parame->type == NONLATCH) {
		switch(parame->state){
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

/// @brief S1X8_Chenck_Fun
/// @param parame 
void S1X8_Chenck_Fun(CMD_Parame *parame){
	if(parame->option == AUTO&&parame->onoff == ON){
		Switch = ON;
		Latch_S1X8_CHENCH(parame->timer,1,parame->type);
	}
	else if(parame->option == STATE){
		S1X8_StateSwitch(parame);
	}
}

/// @brief S1X8_StateSwitch
/// @param parame 
void S1X8_StateSwitch(CMD_Parame *parame){
	
	if(parame->type == LATCH){
		switch(parame->state){
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
	else if(parame->type == NONLATCH) {
		switch(parame->state){
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




