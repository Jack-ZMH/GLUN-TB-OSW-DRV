#include "bsp_nxp9698.h"

uint8_t nxp_Init(void)
{

	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	//��©�����û�����������衢����ٶ�
	GPIO_InitStruct.Pin = NXP9868_eRST;							
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;				
	GPIO_InitStruct.Pull = GPIO_PULLUP;								
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(NXP9868_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = NXP9868_eOE;
	HAL_GPIO_Init(NXP9868_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = NXP9868_eINT;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;	
	HAL_GPIO_Init(NXP9868_GPIO_PORT, &GPIO_InitStruct);	
	
	HAL_GPIO_WritePin(NXP9868_GPIO_PORT,NXP9868_eRST,GPIO_PIN_SET);
	HAL_GPIO_WritePin(NXP9868_GPIO_PORT,NXP9868_eOE,GPIO_PIN_RESET);
	
	if(HAL_GPIO_ReadPin(NXP9868_GPIO_PORT,NXP9868_eINT)!= SET)
	{
		return 0;
	}
	return 1;
}

#ifdef USER_I2C
/// @brief ��ȡ�豸ID
/// @param addr READ:0x41  WRITE:0x40
/// @param 0XF8 ��ȡID
void ReadDeviceID(void)//(nxp96xx_GetID* Device , uint8_t addr)
{
	uint8_t *device_Id;
	uint16_t manufacturer ;
	uint16_t part;
	uint8_t revision;
		
	i2c_start();
	i2c_write_byte(0xF8);
	if(i2c_wait_ask()) 	goto ERROR;

	i2c_write_byte(0x40);
	if(i2c_wait_ask()) 	goto ERROR;

	//i2c_rest(); //���������ź�
	i2c_start();
	
	i2c_write_byte(0xF9);	//�豸����
	if(i2c_wait_ask()) 	goto ERROR;

	*(device_Id++) = i2c_read_byte();  //�߰�λ
	i2c_ask();
	*(device_Id++) = i2c_read_byte();  //�а�λ
	i2c_ask();	
	*(device_Id) = i2c_read_byte();	//�ڰ�λ
	i2c_nask();
	i2c_stop();

	manufacturer = device_Id[0] << 4 | (device_Id[1]&0xF0);
	printf("manufacturer = %x\n",manufacturer);

	part = (device_Id[1]&0x0F) << 5 | (device_Id[2]&0xF8);
	printf("part = %x\n",part);
	
	revision = device_Id[2] & 0x07; //����λ
	printf("revision = %x\n",revision);
	return;
ERROR:
	i2c_stop();
	printf("DEVICE ERROR\n");
}

/// @brief д�뵽�ض�����˿�
/// @param DviceAddr ���豸��ַ
/// @param cmd ��bank��ַ
/// @param nData ��bangk����
/// @return 
uint8_t WriteSpecificPort(uint8_t DviceAddr,uint8_t cmd,uint8_t nData)
{
	i2c_start();
	i2c_write_byte(DviceAddr);
	if(i2c_wait_ask()) 	printf("WRITE ASK ERROR\n");	
	i2c_write_byte(cmd);
	if(i2c_wait_ask()) 	printf("WRITE CMD ASK ERROR\n");	
	i2c_write_byte(nData);
	if(i2c_wait_ask()) 	printf("WRITE ASK ERROR\n");	
	i2c_stop();
	printf("WRITE DONE\n");
	return 0;
ERROR2:
	i2c_stop();
	return 1;
}

/// @brief �����˿ڼĴ���д��������,��ʼ AI= 1��PC9698���Զ�����BANK�Ĵ����ĵ�ַ��ֻ��Ҫ����������LEN���ȵ�IO�����ݼ���
/// @param DviceAddr  �豸д��ַ
/// @param cmd  BANK�Ĵ�����ַ
/// @param nData IO������׵�ַ
/// @param len 
/// @return 0
uint8_t WriteMoreByteData(uint8_t DviceAddr,uint8_t cmd,uint8_t *nData,uint8_t len)
{
	i2c_start();
	i2c_write_byte(DviceAddr); 
	if(i2c_wait_ask()) 	printf("WRITE ASK ERROR\n");

	i2c_write_byte(cmd | AUTO_INCREMENT); //�����Զ����������ַ
	if(i2c_wait_ask()) 	printf("WRITE CMD ASK ERROR\n");

	for(uint8_t i = 0;i<len;i++) //����len������
	{
		i2c_write_byte(nData[i]);
		if(i2c_wait_ask()) printf("WRITE ASK ERROR\n");		
	}
	printf("WRITE DONE\n");
	i2c_stop();
	return 0;
	
ERROR1:
	i2c_stop();
	return 1;
}

/// @brief д�����ģʽѡ��BANG���ơ�PCA9698ģʽ�Ĵ��� ��оƬ��ʼ��ʱʹ�ã�
/// @param DviceAddr 
/// @param cmd 
/// @param nData 
/// @return 
uint8_t WireStructBankModeSElReg(uint8_t DviceAddr,uint8_t cmd,uint8_t nData)
{
	uint8_t cmd_ctrl = cmd & 0x7f; 		//����AIλΪ 0 
	return WriteSpecificPort(DviceAddr,cmd_ctrl,nData);
}

/// @brief	��ȡָ���������� max:5
/// @param Addr 
/// @param cmd 
/// @param nData 
/// @param len 
/// @return 
uint8_t ReadMoreRegData(uint8_t Addr,uint8_t cmd,uint8_t *nData,uint8_t len)
{
	
	i2c_start();
	i2c_write_byte(0X40);	
	if(i2c_wait_ask()) printf("READ ASK ERROR\n");
	
	i2c_write_byte(cmd | AUTO_INCREMENT);
	if(i2c_wait_ask()) printf("READ CMD ASK ERROR\n");

	i2c_start();

	i2c_write_byte(Addr);
	if(i2c_wait_ask()) printf("READ ASK ERROR\n");	
		

	for (uint8_t i = 0; i < len; i++)
	{
		nData[i]= i2c_read_byte();
		i2c_ask();
	}
	i2c_nask();
	i2c_stop();
	return 0;
	
ERROR3:
	i2c_stop();
	return 1;
}

/// @brief ��ȡ�Ĵ�������
/// @param DviceAddr 
/// @param cmd 
/// @return 
uint8_t ReadRegData(uint8_t DviceAddr,uint8_t cmd)
{
	uint8_t nData;
	
	i2c_start();
	i2c_write_byte(0X40);	
	if(i2c_wait_ask()) printf("READ ASK ERROR\n");
	
	i2c_write_byte(cmd);
	if(i2c_wait_ask()) printf("READ CMD ASK ERROR\n");
	
	i2c_start();
	i2c_write_byte(DviceAddr);
	if(i2c_wait_ask()) printf("READ ASK ERROR\n");
	nData = i2c_read_byte();
	i2c_nask();
	i2c_stop();
	
	return nData;	
}

/// @brief ReadStructBankModeSelReg
/// @param DviceAddr 
/// @param cmd 
/// @return 
uint8_t ReadStructBankModeSelReg(uint8_t DviceAddr,uint8_t cmd)
{
	uint8_t cmd_ctrl = cmd & 0x7f;
	return ReadRegData(DviceAddr,cmd_ctrl);
}

#else 


/// @brief ��ȡ�豸ID
/// @param addr READ:0x41  WRITE:0x40
/// @param 0XF8 ��ȡID
void ReadDeviceID(void)
{
	uint8_t pData[3];
	uint16_t mfgname;
	uint8_t revision;
	uint16_t devicecode;
	if(HAL_I2C_Mem_Read(&hi2c,0xF8,0x40,I2C_MEMADD_SIZE_8BIT,pData,3,100) != HAL_OK)
	{
			printf("PCA9698 READ ERROE\n");
	}
	
	mfgname = pData[0] << 4 | (pData[1] &0xF0);
	devicecode = pData[1] << 5 | (pData[2] &0xF8);
	revision = pData[2] & 0x07;
	
	printf("mfgname:%d  devicecode:%d   revision:%d \n",mfgname,devicecode,revision);
}



/** @defgroup PCA ͨ��ʱ����
  *  @brief   ���ֽ�д�����ֽڶ������ֽ�д�����ֽڶ�
  *
@verbatim
 ===============================================================================
                       ##### Communication timing functions #####
 ===============================================================================
@endverbatim
  * @{
  */

/// @brief ��ȡ����IO REG����
/// @param regaddr
/// @param Data[] 
/// @param size 
uint8_t ReadMoreByteForReg(uint8_t regaddr, uint8_t Data[],uint8_t size)
{
	uint8_t *pData = Data;
	uint8_t temp = regaddr | AUTO_INCREMENT;
	return HAL_I2C_Mem_Read(&hi2c,NXP_9868_ADDR,temp,I2C_MEMADD_SIZE_8BIT,pData,size,100);
}

/// @brief ��ȡ����IO REG����
/// @param regaddr
/// @param Data 
uint8_t ReadByteForReg(uint8_t regaddr,uint8_t *Data)
{
	uint8_t temp = regaddr;
	return HAL_I2C_Mem_Read(&hi2c,NXP_9868_ADDR,temp,I2C_MEMADD_SIZE_8BIT,Data,1,100);
}

/// @brief д�����IO REG����
/// @param regaddr
/// @param Data[] 
/// @param size 
uint8_t WireMoreByteToReg(uint8_t regaddr, uint8_t Data[],uint8_t size)
{
	uint8_t *pData = Data;
	uint8_t temp = regaddr | AUTO_INCREMENT;
	return HAL_I2C_Mem_Write(&hi2c, NXP_9868_ADDR,temp, I2C_MEMADD_SIZE_8BIT, pData, size, 100);
}

/// @brief д�뵥��IO REG����
/// @param regaddr
/// @param Data[] 
uint8_t WireByteToReg(uint8_t regaddr,uint8_t Data)
{
	uint8_t temp = regaddr;
	return HAL_I2C_Mem_Write(&hi2c, NXP_9868_ADDR,temp, I2C_MEMADD_SIZE_8BIT, &Data, 1, 100);
}



/** @defgroup PCA_GPIO_Exported_Functions IO operation functions 
  *  @brief   GPIO Read and Write
  *
@verbatim
 ===============================================================================
                       ##### IO operation functions #####
 ===============================================================================

@endverbatim
  * @{
  */
/// @brief GPIO DIR����
/// @param GPIOx
/// @param GPIO_Pin 
/// @param GPIO_Dir
uint8_t PCA_GPIO_DirConfig(CMD_IOCTypeDef GPIOx,uint8_t GPIO_Pin,PCA_PIN_Dir GPIO_Dir)
{
	uint8_t dir;
	if(ReadByteForReg(GPIOx,&dir))
	{
		return 1;
	}
	else
		{
		if(GPIO_Dir == 0x01)
			dir |= (0x01 << GPIO_Pin);  //����ָ��λ
		else if(GPIO_Dir == 0x00)
			dir &= ~(0x01 <<GPIO_Pin);  //����ָ��λ
		
		if(WireByteToReg(GPIOx,dir))
			return 1;
	}
	return 0;
}

/// @brief GPIO д����
/// @param GPIOx
/// @param GPIO_Pin 
/// @param PinState
uint8_t PCA_GPIO_WritePin(CMD_OPTypeDef GPIOx,uint8_t GPIO_Pin,PCA_PIN_State PinState)
{
	uint8_t dir;
	if(ReadByteForReg(GPIOx,&dir))
	{
		return 1;
	}
	else
		{
		if(PinState == 0x01)
			dir |= (0x01 << GPIO_Pin);  //����ָ��λ
		else if(PinState == 0x00)
			dir &= ~(0x01 <<GPIO_Pin);  //����ָ��λ
		
		if(WireByteToReg(GPIOx,dir))
			return 1;
	}
	return 0;
}

/// @brief GPIO ������
/// @param GPIOx
/// @param GPIO_Pin 
uint8_t PCA_GPIO_ReadPin(CMD_IPTypeDef GPIOx,uint8_t GPIO_Pin)
{
	uint8_t value;
	ReadByteForReg(GPIOx,&value);
	return (value & (1 << GPIO_Pin)) ? 1 : 0;
}

/// @brief GPIO �ж�config
/// @param GPIOx
/// @param GPIO_Pin 
/// @param PinMask
uint8_t PCA_GPIO_Pin_Mask(CMD_MASKTypeDef GPIOx,uint8_t GPIO_Pin,PCA_PIN_Mask PinMask)
{
	uint8_t dir;
	if(ReadByteForReg(GPIOx,&dir))
	{
		return 1;
	}
	else
		{
		if(PinMask == 0x01)
			dir |= (0x01 << GPIO_Pin);  //����ָ��λ
		else if(PinMask == 0x00)
			dir &= ~(0x01 <<GPIO_Pin);  //����ָ��λ
		
		if(WireByteToReg(GPIOx,dir))
			return 1;
	}
	return 0;
}

/// @brief GPIO_PIN TOGGLE
/// @param GPIOx
/// @param GPIO_Pin 
uint8_t PCA_GPIO_Pin_Toggle(CMD_PITypeDef GPIOx,uint8_t GPIO_Pin)
{
	uint8_t dir;
	if(ReadByteForReg(GPIOx,&dir))
	{
		return 1;
	}
	else
	{
		
		dir |= (0x01 << GPIO_Pin);  //����ָ��λ		
		if(WireByteToReg(GPIOx,dir))
			return 1;
	}
	return 0;
}



/// @brief GPIO_PIN MODE config
/// @param GPIOx
/// @param Pin_Mode
/// @notice  BANK0�ܿ������飻BANK1~BANK4ֻ��ͬʱ���ư˸�����
uint8_t PCA_GPIO_PinModeCtrl(PCA_PIN_Mode Pin_Mode)
{
	uint8_t mode;
	if(ReadByteForReg(OUTCONF_CMD,&mode))
	{
		return 1;
	}
	else 
	{
		if(Pin_Mode)
			WireByteToReg(OUTCONF_CMD,0xff);	//����BANK������λ�������
		else 
			WireByteToReg(OUTCONF_CMD,0x00);	//����BANK������λ��©���
	}
	return 0;	
}

/// @brief ALL BANK CTRL
/// @param BankState
/// @notice ֻ�ܿ�����������Ϊ���������
uint8_t PCA_AllBANK_Ctrl(uint8_t BankState)
{
	if(!BankState)
	{
		WireByteToReg(ALLBANK_CMD,0x7f);  //������Ҫ�ر�BANK CONCTRL REG �����λ :BSEL=0
	}
	else 
		WireByteToReg(ALLBANK_CMD,0xff);  //������Ҫ��BANK CONCTRL REG �����λ :BSEL=1
	return 0;
}

/// @brief PCA9698 MODE config
/// @param  
/// @return 
uint8_t PCA_MODE_Config(void)
{
	uint8_t commd = MODESEL_OE_L|MODESEL_OCH_ASK|MODESEL_IOAC_NOCALL|MODESEL_SMBA_ASK;
	if(WireByteToReg(MODESEL_CMD,commd))
		return 1;
	return 0;
}

/// @brief READ_TwoPin
/// @param GPIO_Pin1
/// @param GPIO_Pin2
uint8_t READ_TwoPin(CMD_IPTypeDef GPIOx,uint8_t GPIO_Pin1,uint8_t GPIO_Pin2)
{
	uint8_t value;
	ReadByteForReg(GPIOx,&value);
	if(((1<<GPIO_Pin1)&value) == 0 && ((1<<GPIO_Pin2)&value) == 0)
		return 0;
	else 
		return 1;
}
#endif









