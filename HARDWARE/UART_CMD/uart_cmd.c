#include "uart_cmd.h"
#include <string.h>
#include <ctype.h>


static int strToInt(const char *str, size_t length);
static uint8_t isNumeric(const char *str);
static void extractCommand(const char *input, char *output, size_t outputSize);
static int isAllLetters(const char *str);
static int isAllDigits(const char *str);

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




/// @brief CmdTable_Traversal
/// @param rx 
/// @param listLen 
uint8_t CmdTable_Traversal(char *cmd)
{
	char *cmd_initadrr = cmd;
	static CMD_ParameTypeDef Cmd_Parame;
	char buff[50];
	
	Cmd_Table.cmdPreproccessCallBack(cmd);
	/* �޳� \r\n */
    while(*cmd != '\0'){
		if(*cmd == '\r' || *cmd == '\n')
			*cmd = '\0';
		cmd++;
	}
    *cmd = '\0';	
	cmd = cmd_initadrr;
	
	memset(buff,0,sizeof(buff));
	extractCommand(cmd,buff,sizeof(buff)); //��ȡ<>�е�����
	if(buff[0] == '\0') return 1;
	
	memset(&Cmd_Parame, 0, sizeof(Cmd_Parame)); //��ղ����ṹ��

	if(strchr(buff ,':')!=NULL) //�ж������Ƿ��зָ���
	{
		char *token = strtok(buff, ":");
		if(token!=NULL)
		{
			if(strlen(token)>MAX_CMD_LEN) return 1;
			strncpy(Cmd_Parame.cmd,token,strlen(token));
			Cmd_Parame.cmd[sizeof(Cmd_Parame.cmd) - 1] = '\0'; //�ֶ���ӽ�������
			
			char *parame = strtok(NULL, ":");
			char *parame1 = strtok(NULL, ":");	
			char *parame2 = strtok(NULL, ":");
			
            /* ��ȡ�⿪�������� */
			if(strcmp(parame,"LOCK") == 0) 
				Cmd_Parame.type = lock;
			else if(strcmp(parame,"NOLOCK") == 0)
				Cmd_Parame.type = nolock;
			else if(isAllDigits(parame))
				Cmd_Parame.timer = atoi(parame);
			else 
				return 1;
			
            /* �ж��������Ĳ�����Ϊ���ַ� */
			if(isAllLetters(parame1)){
				if(strcmp(parame1,"A") == 0)
					Cmd_Parame.status = A;
				else if(strcmp(parame1,"B") == 0)
					Cmd_Parame.status = B;
				else if(strcmp(parame1,"C") == 0)
					Cmd_Parame.status = C;
				else if(strcmp(parame1,"D") == 0)
					Cmd_Parame.status = D;
				else if(strcmp(parame1,"E") == 0)
					Cmd_Parame.status = E;
				else if(strcmp(parame1,"F") == 0)
					Cmd_Parame.status = F;
				else if(strcmp(parame1,"G") == 0)
					Cmd_Parame.status = G;
				else if(strcmp(parame1,"H") == 0)
					Cmd_Parame.status = H;
				else 
					return 1;
			}
            /* �ж��������Ĳ�����Ϊ������ */
			else if(isAllDigits(parame1)){
				Cmd_Parame.parame1 = (parame1 != NULL) ? atoi(parame1) : 0;
			    Cmd_Parame.parame2 = (parame2 != NULL) ? atoi(parame2) : 0;
			}
			else{ 
				return 1;
			}
		}
	}
	else //���û�зָ���ֱ��ִ������
	{
		if(strlen(buff)>MAX_CMD_LEN) return 1;
		strncpy(Cmd_Parame.cmd,buff,strlen(cmd));
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


/// @brief isNumeric
/// @param str 
/// @return 
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

/// @brief extractCommand
/// @param input 
/// @param output 
/// @param outputSize 
static void extractCommand(const char *input, char *output, size_t outputSize) 
{
    const char *start = strchr(input, '<');  // ����'<'
    const char *end = strchr(input, '>');    // ����'>'

    // ����ҵ�'<>'������'>'��'<'֮��
    if (start != NULL && end != NULL && start < end) 
	{
        size_t length = end - start - 1;  // �������ݳ���
        length = (length < outputSize - 1) ? length : outputSize - 1;  //ȷ�������������������С
        strncpy(output, start + 1, length);  // �������ݵ����������
        output[length] = '\0';  // ����ַ���������
    } else {
        // ���δ�ҵ�'<>'������'>'��'<'֮ǰ
        output[0] = '\0';  // ���Ϊ���ַ���
    }
}

/// @brief isAllLetters
/// @param str 
/// @return 
static int isAllLetters(const char *str) 
{
    while (*str) {
        if (!isalpha((unsigned char)*str)) {
            return 0; // ��������ĸ�ַ�
        }
        str++;
    }
    return 1; // ȫΪ��ĸ
}


/// @brief isAllDigits
/// @param str 
/// @return 
static int isAllDigits(const char *str) 
{
    while (*str) {
        if (!isdigit((unsigned char)*str)) {
            return 0; // �����������ַ�
        }
        str++;
    }
    return 1; // ȫΪ����
}


