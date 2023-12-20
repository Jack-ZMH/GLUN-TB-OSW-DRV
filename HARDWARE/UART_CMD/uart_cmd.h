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


#define LATCH			0x00
#define NONLATCH		0x01

#define SET				0x00
#define AUTO			0x01
#define STATE			0x02

#define ON				0x00
#define OFF				0x01

#define A			0x00
#define B			0x01
#define C			0x02
#define D			0x03
#define E			0x04
#define F			0x05
#define G			0x06
#define H			0x07

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

typedef struct CMD_ParameTypeDef
{
	string cmd; //√¸¡Ó
	uint8_t type;
	uint8_t option;
	uint8_t onoff;
	uint8_t state;
	uint16_t timer;
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


typedef struct {
    const char* str;
    uint8_t value;
} SwitchType;

extern CMD_ParameTypeDef Cmd_Parame;
extern SwitchType switch_types[];

uint8_t Logic_CmdFun(const Cmd_Class *cmdList,uint8_t listLen);
uint8_t CmdTable_Traversal(char *cmd);
__weak uint8_t Cmd_PreproccessCallBack(char *cmd);

#endif

