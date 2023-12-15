#include "uart_cmd.h"
#include <string.h>

/// @brief 全局变量，存储已经注册命令
LogicExeCmd_Class Cmd_Table = {
								.cmd_list = NULL,
								.cmd_num = 0,  
								.cmdPreproccessCallBack = Cmd_PreproccessCallBack 
};

/// @brief Logic_CmdFun
/// @param cmdList 
/// @param listLen 
uint8_t Logic_CmdFun(const Cmd_Class *cmdList,uint8_t listLen)
{    

    // 检查已注册命令数量是否达到上限
    if(Cmd_Table.cmd_num >= 50 ) return 1;
		
    // 检查命令长度是否合法
    if ((strlen(cmdList->cmd) >= MAX_CMD_LEN)) 
        return 1;  

    //检查需要注册的命令数量是否大于剩余容量
    if(listLen > ( MAX_CMD_NUM - Cmd_Table.cmd_num)){
        printf("MEMORY_EXCEEDED:%d \n",listLen-(MAX_CMD_NUM - Cmd_Table.cmd_num)); //输出超出的指令数量
        return 1;
    }
	
	//注册
    for(uint8_t i = 0;i < listLen ;i++){
        strcpy(Cmd_Table.cmd_list[Cmd_Table.cmd_num].cmd , cmdList[i].cmd);
        Cmd_Table.cmd_list[Cmd_Table.cmd_num].option = cmdList[i].option;
        Cmd_Table.cmd_num++;
    }
    return 0;
}

/// @brief 字符串转整形
/// @param str 
/// @param length
static int strToInt(const char *str, size_t length) 
{
    // 创建一个临时缓冲区，注意+1是为了存放字符串结束符 '\0'
    char buffer[length + 1];
    
    // 将指定长度的字符串复制到缓冲区
    strncpy(buffer, str, length);
    
    // 确保缓冲区以 null 结尾
    buffer[length] = '\0';
    
    // 使用 atoi 将字符串转换为整数
    return atoi(buffer);
}

static uint8_t isNumeric(const char *str)
{
    while (*str != '\0')
    {
        if (*str < '0' || *str > '9')
        {
            return 1; // 非数字
        }
        str++;
    }
    return 0; // 全部是数字	
}
/// @brief CmdTable_Traversal
/// @param rx 
/// @param listLen 
uint8_t CmdTable_Traversal(char *cmd)
{
	char *cmd_initadrr = cmd;
	static CMD_ParameTypeDef Cmd_Parame;
	
	Cmd_Table.cmdPreproccessCallBack(cmd);
	/* 剔除 \r\n */
    while(*cmd != '\0'){
		if(*cmd == '\r' || *cmd == '\n')
			*cmd = '\0';
		cmd++;
	}
    *cmd = '\0';	
	cmd = cmd_initadrr;

	memset(&Cmd_Parame, 0, sizeof(Cmd_Parame)); //清空参数结构体
	if(strchr(cmd ,':')!=NULL) //判断命令是否有分隔符
	{
		char *token = strtok(cmd, ":");
		if(token!=NULL)
		{
			if(strlen(token)>MAX_CMD_LEN) return 1;
			strncpy(Cmd_Parame.cmd,token,strlen(token));
			Cmd_Parame.cmd[sizeof(Cmd_Parame.cmd) - 1] = '\0'; //手动添加结束符号
	
			char *parame1 = strtok(NULL, ":");	
			char *parame2 = strtok(NULL, ":");
			if(isNumeric(parame1)){		
				strncpy(Cmd_Parame.para,parame1,strlen(parame1));
				Cmd_Parame.para[sizeof(Cmd_Parame.para) - 1] = '\0';
			}
			else {
				Cmd_Parame.parame1 = (parame1 != NULL) ? atoi(parame1) : 0;
				Cmd_Parame.parame2 = (parame2 != NULL) ? atoi(parame2) : 0;		
			}
		}
	}
	else //如果没有分隔符直接执行命令
	{
		if(strlen(cmd)>MAX_CMD_LEN) return 1;
		strncpy(Cmd_Parame.cmd,cmd,strlen(cmd));
		Cmd_Parame.cmd[sizeof(Cmd_Parame.cmd) - 1] = '\0'; //手动添加结束符号
	}
	
	for(uint8_t i=0;i<Cmd_Table.cmd_num;i++)
    {
        if(strcmp(Cmd_Parame.cmd, Cmd_Table.cmd_list[i].cmd)==0){  
            Cmd_Table.cmd_list[i].option(&Cmd_Parame);
			goto end; //执行完退出
        }   
    }
	
	
end:
	memset(cmd,0,strlen(cmd));
	return 0;
}

/// @brief 预处理命令
/// @param cmd 
__weak uint8_t Cmd_PreproccessCallBack(char *cmd)
{
    char *cmd_initaddr = cmd;
    char *temp_addr = cmd;
    //小写转大写
    while(*cmd != '\0'){
        if(*cmd >= 'a' && *cmd <= 'z') 
            (*cmd) -= 0x20;
        cmd++;
    }
    cmd = cmd_initaddr;
    //去空格
    while(*cmd != '\0'){
        if(*cmd != ' ')
            *temp_addr++ = *cmd;
        cmd++;
    }
    *temp_addr = '\0';
    cmd = cmd_initaddr;
	return 0;
}


