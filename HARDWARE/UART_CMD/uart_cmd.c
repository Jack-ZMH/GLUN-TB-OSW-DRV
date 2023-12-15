#include "uart_cmd.h"
#include <string.h>

/// @brief ȫ�ֱ������洢�Ѿ�ע������
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

    // �����ע�����������Ƿ�ﵽ����
    if(Cmd_Table.cmd_num >= 50 ) return 1;
		
    // ���������Ƿ�Ϸ�
    if ((strlen(cmdList->cmd) >= MAX_CMD_LEN)) 
        return 1;  

    //�����Ҫע������������Ƿ����ʣ������
    if(listLen > ( MAX_CMD_NUM - Cmd_Table.cmd_num)){
        printf("MEMORY_EXCEEDED:%d \n",listLen-(MAX_CMD_NUM - Cmd_Table.cmd_num)); //���������ָ������
        return 1;
    }
	
	//ע��
    for(uint8_t i = 0;i < listLen ;i++){
        strcpy(Cmd_Table.cmd_list[Cmd_Table.cmd_num].cmd , cmdList[i].cmd);
        Cmd_Table.cmd_list[Cmd_Table.cmd_num].option = cmdList[i].option;
        Cmd_Table.cmd_num++;
    }
    return 0;
}

/// @brief �ַ���ת����
/// @param str 
/// @param length
static int strToInt(const char *str, size_t length) 
{
    // ����һ����ʱ��������ע��+1��Ϊ�˴���ַ��������� '\0'
    char buffer[length + 1];
    
    // ��ָ�����ȵ��ַ������Ƶ�������
    strncpy(buffer, str, length);
    
    // ȷ���������� null ��β
    buffer[length] = '\0';
    
    // ʹ�� atoi ���ַ���ת��Ϊ����
    return atoi(buffer);
}

static uint8_t isNumeric(const char *str)
{
    while (*str != '\0')
    {
        if (*str < '0' || *str > '9')
        {
            return 1; // ������
        }
        str++;
    }
    return 0; // ȫ��������	
}
/// @brief CmdTable_Traversal
/// @param rx 
/// @param listLen 
uint8_t CmdTable_Traversal(char *cmd)
{
	char *cmd_initadrr = cmd;
	static CMD_ParameTypeDef Cmd_Parame;
	
	Cmd_Table.cmdPreproccessCallBack(cmd);
	/* �޳� \r\n */
    while(*cmd != '\0'){
		if(*cmd == '\r' || *cmd == '\n')
			*cmd = '\0';
		cmd++;
	}
    *cmd = '\0';	
	cmd = cmd_initadrr;

	memset(&Cmd_Parame, 0, sizeof(Cmd_Parame)); //��ղ����ṹ��
	if(strchr(cmd ,':')!=NULL) //�ж������Ƿ��зָ���
	{
		char *token = strtok(cmd, ":");
		if(token!=NULL)
		{
			if(strlen(token)>MAX_CMD_LEN) return 1;
			strncpy(Cmd_Parame.cmd,token,strlen(token));
			Cmd_Parame.cmd[sizeof(Cmd_Parame.cmd) - 1] = '\0'; //�ֶ���ӽ�������
	
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
	else //���û�зָ���ֱ��ִ������
	{
		if(strlen(cmd)>MAX_CMD_LEN) return 1;
		strncpy(Cmd_Parame.cmd,cmd,strlen(cmd));
		Cmd_Parame.cmd[sizeof(Cmd_Parame.cmd) - 1] = '\0'; //�ֶ���ӽ�������
	}
	
	for(uint8_t i=0;i<Cmd_Table.cmd_num;i++)
    {
        if(strcmp(Cmd_Parame.cmd, Cmd_Table.cmd_list[i].cmd)==0){  
            Cmd_Table.cmd_list[i].option(&Cmd_Parame);
			goto end; //ִ�����˳�
        }   
    }
	
	
end:
	memset(cmd,0,strlen(cmd));
	return 0;
}

/// @brief Ԥ��������
/// @param cmd 
__weak uint8_t Cmd_PreproccessCallBack(char *cmd)
{
    char *cmd_initaddr = cmd;
    char *temp_addr = cmd;
    //Сдת��д
    while(*cmd != '\0'){
        if(*cmd >= 'a' && *cmd <= 'z') 
            (*cmd) -= 0x20;
        cmd++;
    }
    cmd = cmd_initaddr;
    //ȥ�ո�
    while(*cmd != '\0'){
        if(*cmd != ' ')
            *temp_addr++ = *cmd;
        cmd++;
    }
    *temp_addr = '\0';
    cmd = cmd_initaddr;
	return 0;
}


