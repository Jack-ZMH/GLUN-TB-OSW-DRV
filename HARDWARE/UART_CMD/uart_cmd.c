#include "uart_cmd.h"
#include <string.h>
#include <ctype.h>


static int strToInt(const char *str, size_t length);
static uint8_t isNumeric(const char *str);
static void extractCommand(const char *input, char *output, size_t outputSize);
static int isAllLetters(const char *str);
static int isAllDigits(const char *str);



SwitchType switch_types[] = {
    {"C1X2G",0},
    {"D2X2B",1},
	{"M1X1", 2},
	{"M1X4", 3},
	{"S1X4", 4},
	{"S1X8", 5},
	    
  {"N_C1X2G",6},
	{"N_M1X4", 7},
	{"N_S1X4", 8},
	{"N_S1X8", 9}
	
    // 添加其他元素...
};

/// @brief 全局变量，存储已经注册命令
LogicExeCmd_Class Cmd_Table = {
								.cmd_list = NULL,
								.cmd_num = 0,  
								.cmdPreproccessCallBack = Cmd_PreproccessCallBack 
};

CMD_ParameTypeDef  Cmd_Parame = {
									"\0",
									LATCH,
									AUTO,
									OFF,
									A,
									500  //默认500ms切换一次
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




/// @brief CmdTable_Traversal
/// @param rx 
/// @param listLen 
uint8_t CmdTable_Traversal(char *cmd)
{
	bool falg = false;
	char *cmd_initadrr = cmd;
	//static CMD_ParameTypeDef Cmd_Parame;
	char buff[50];
	string temp_cmd;
	Cmd_Table.cmdPreproccessCallBack(cmd);
	/* 剔除 \r\n */
    while(*cmd != '\0'){
		if(*cmd == '\r' || *cmd == '\n')
			*cmd = '\0';
		cmd++;
	}
    *cmd = '\0';	
	cmd = cmd_initadrr;
	
	memset(buff,0,sizeof(buff));
	extractCommand(cmd,buff,sizeof(buff)); //提取<>中的命令
	if(buff[0] == '\0') return 1;
		
	memset(temp_cmd,0,sizeof(temp_cmd));
	
	if(strchr(buff ,':')!=NULL) //获取 ：的位置
	{
		char *token = strtok(buff, ":");
		if(token!=NULL)
		{
			if(strlen(token)>MAX_CMD_LEN) 
				goto error;
			strncpy(temp_cmd,token,strlen(token));
			temp_cmd[sizeof(temp_cmd) - 1] = '\0'; //手动添加结束符号
			
			char *parame1 = strtok(NULL, ":");
			char *parame2 = strtok(NULL, ":");	
			char *parame3 = strtok(NULL, ":");
			
            if(parame1 != NULL){
				if(strcmp(parame1,"LATCH") == 0) {
					Cmd_Parame.type = LATCH;
					falg = true;
				}
				else if(strcmp(parame1,"NONLATCH") == 0){
					Cmd_Parame.type = NONLATCH;
					falg = true;
				}
				else {
					memset(Cmd_Parame.cmd,0,strlen(Cmd_Parame.cmd));
					strncpy(Cmd_Parame.cmd,parame1,strlen(parame1));
				}
			}
			if(parame2 != NULL){
			
				if(strcmp(parame2,"AUTO") == 0)
				{
					Cmd_Parame.option = AUTO;
					if(parame3 != NULL){
						if(strcmp(parame3,"ON") == 0){
							Cmd_Parame.onoff = ON;
							Switch = ON;
						}
						else if(strcmp(parame3,"OFF") == 0){
							Cmd_Parame.onoff = OFF;
							Switch = OFF;
						}
						else {
							printf("Auto Cmd Error\n");
							goto error;
						}
					}
					else{
						goto error;
					}
						
				}
				else if(strcmp(parame2,"STATUS") == 0)
				{
					Cmd_Parame.option = STATE;
					/* 判断命令后面的参数否为纯字符 */
					if(isAllLetters(parame3)){
						if(strcmp(parame3,"A") == 0)
							Cmd_Parame.state = A;
						else if(strcmp(parame3,"B") == 0)
							Cmd_Parame.state = B;
						else if(strcmp(parame3,"C") == 0)
							Cmd_Parame.state = C;
						else if(strcmp(parame3,"D") == 0)
							Cmd_Parame.state = D;
						else if(strcmp(parame3,"E") == 0)
							Cmd_Parame.state = E;
						else if(strcmp(parame3,"F") == 0)
							Cmd_Parame.state = F;
						else if(strcmp(parame3,"G") == 0)
							Cmd_Parame.state = G;
						else if(strcmp(parame3,"H") == 0)
							Cmd_Parame.state = H;
						else {
							printf("State Cmd Error\n");
							goto error;
						}
							
					}
				}
#if 0
				else if(strcmp(parame2,"SET") == 0)
				{
					Cmd_Parame.option = SET;
					if(parame3 != NULL){
						if(isAllDigits(parame3))
							Cmd_Parame.timer = (parame3 != NULL) ? atoi(parame3) : 500;
		
						printf("Set Timer:%d\n",Cmd_Parame.timer);
					}
				}
#endif
				else{ 
					goto error;
				}
			}
			else if(parame2 == NULL && falg){
				falg = false;
				goto error;
			}
		}
	}
	else //如果没有分隔符直接执行命令
	{
		if(strlen(buff)>MAX_CMD_LEN) 
			goto error;
		strncpy(temp_cmd,buff,strlen(cmd));
		temp_cmd[sizeof(temp_cmd) - 1] = '\0'; //手动添加结束符号
	}
	
	for(uint8_t i=0;i<Cmd_Table.cmd_num;i++)
    {
        if(strcmp(temp_cmd, Cmd_Table.cmd_list[i].cmd)==0){  
            Cmd_Table.cmd_list[i].option(&Cmd_Parame);
			goto end; //执行完退出
        }   
    }
	
	
end:
	memset(cmd,0,strlen(cmd));
	printf(">");
	return 0;
	
error:
	printf("Cmd Error\r\n>");
	return 1;
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


/// @brief isNumeric
/// @param str 
/// @return 
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

/// @brief extractCommand
/// @param input 
/// @param output 
/// @param outputSize 
static void extractCommand(const char *input, char *output, size_t outputSize) 
{
    const char *start = strchr(input, '<');  // 查找'<'
    const char *end = strchr(input, '>');    // 查找'>'

    // 如果找到'<>'，并且'>'在'<'之后
    if (start != NULL && end != NULL && start < end) 
	{
        size_t length = end - start - 1;  // 计算内容长度
        length = (length < outputSize - 1) ? length : outputSize - 1;  //确保不超过输出缓冲区大小
        strncpy(output, start + 1, length);  // 复制内容到输出缓冲区
        output[length] = '\0';  // 添加字符串结束符
    } else {
        // 如果未找到'<>'，或者'>'在'<'之前
        output[0] = '\0';  // 输出为空字符串
    }
}

/// @brief isAllLetters
/// @param str 
/// @return 
static int isAllLetters(const char *str) 
{
    while (*str) {
        if (!isalpha((unsigned char)*str)) {
            return 0; // 包含非字母字符
        }
        str++;
    }
    return 1; // 全为字母
}


/// @brief isAllDigits
/// @param str 
/// @return 
static int isAllDigits(const char *str) 
{
    while (*str) {
        if (!isdigit((unsigned char)*str)) {
            return 0; // 包含非数字字符
        }
        str++;
    }
    return 1; // 全为数字
}


