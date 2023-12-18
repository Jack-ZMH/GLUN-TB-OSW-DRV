#ifndef UART_CMD_H
#define UART_CMD_H
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "bsp_MxN.h"
#include "sys.h"

#define MAX_CMD_LEN 20
#define MAX_CMD_NUM 50

#define SIZE_ARRAY(x)	   sizeof(x)/sizeof(x[0])

/// @brief 
typedef char string[MAX_CMD_LEN+1];
typedef struct CMD_ParameTypeDef CMD_Parame;
typedef void (*handler_CallBack)(CMD_Parame* parame);
typedef uint8_t (*logicexe_CallBack)(char *cmd);


/// @brief 
typedef struct Cmd_Class
{
    /* data */
    string cmd;             
    /* option */
    handler_CallBack option;
	
}Cmd_Class;

typedef enum Sw_Fun
{
	Auto = 0,
	Set,
	Status
}Sw_Fun;

typedef struct CMD_ParameTypeDef
{
	string cmd; //命令
	LockTypedef type; //类型
	Sw_Fun fun; //功能
	bool sw;
	uint16_t timer; //时间
	SwitchStatusTypedef status; //状态	
	uint16_t parame1;
	uint32_t parame2;
}CMD_ParameTypeDef;

/// @brief 
typedef struct LogicExeCmd_Class
{
    /* data */
    Cmd_Class cmd_list[MAX_CMD_NUM];
    uint8_t cmd_num;
	 /* option */
    logicexe_CallBack cmdPreproccessCallBack; 
}LogicExeCmd_Class;

extern CMD_ParameTypeDef Cmd_Parame;

uint8_t Logic_CmdFun(const Cmd_Class *cmdList,uint8_t listLen);
uint8_t CmdTable_Traversal(char *cmd);
__weak uint8_t Cmd_PreproccessCallBack(char *cmd);

#endif

