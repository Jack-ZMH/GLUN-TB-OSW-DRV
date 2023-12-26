#include "bsp_ad5175.h"




void ad5175_Init(void)
{
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	//��©�����û�����������衢����ٶ�
	GPIO_InitStruct.Pin = AD5175_eRST;							
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;				
	GPIO_InitStruct.Pull = GPIO_PULLUP;								
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(AD5175_GPIO_PORT, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(AD5175_GPIO_PORT,AD5175_eRST,GPIO_PIN_RESET);
	delay_ms(100);
	HAL_GPIO_WritePin(AD5175_GPIO_PORT,AD5175_eRST,GPIO_PIN_SET);
	
	//AD5175_RESET();
	AD5175_SoftwareRest();
}


//����2�ֽ�
uint8_t AD5175_WriteByte(uint8_t * pucByte) 
{
    uint8_t Ask = NULL;
	i2c_start();	//��ʼ�ź�
    i2c_write_byte(AD5175_WIRE_ADDR); //���͵�ַ

	Ask = i2c_wait_ask(); //�ȴ�ADK
	if(Ask)return 1;  
		
    i2c_write_byte(*(pucByte ++)); //���͸�8λ
    Ask = i2c_wait_ask();
	if(Ask)return 2;
		
    i2c_write_byte(*pucByte);//���͵�8λ
    Ask = i2c_wait_ask();
	if(Ask)return 3;  
		
    i2c_stop();
    return 0; 
}

//��ȡ2�ֽ�
uint16_t AD5175_ReadByte(uint8_t * pucByte) 
{
    i2c_start();
    i2c_write_byte(AD5175_READ_ADDR);
    if(i2c_wait_ask()) return 1;
    
    *(pucByte++) = i2c_read_byte(); //��ȡ��8λ
    i2c_ask(); //����Ӧ��
	
    *pucByte = i2c_read_byte();//��ȡ��8λ
    i2c_nask(); //���ͷ�Ӧ��
	
    i2c_stop();//����ͨ��
    return *pucByte;    
}

//д������
uint8_t AD5175_WriteCmd(uint8_t ucCmd, uint16_t nData) 
{
    uint8_t ucData[2];
    
    ucData[0] = (uint8_t)((ucCmd << 2) | (nData >> 8));
    ucData[1] = (uint8_t)(nData & 0xff);
    
    return AD5175_WriteByte(ucData);
}

//��ȡ16BIT�Ĵ���
uint16_t AD5175_Read16Bit(void) 
{
    uint8_t ucData[2];
   	uint16_t nNumber;
    
    AD5175_ReadByte(ucData);
    nNumber = ucData[0] & 0x3;
    nNumber = (nNumber << 8) + ucData[1];
    return nNumber; 
}



//д��RDAC����
void AD5175_WriteRDAC(uint16_t nRDAC) 
{
    AD5175_WriteCmd(COMMAND_W_RDAC, nRDAC);
}

//��ȡRDAC����
uint16_t AD5175_ReadRDAC(void) 
{
    AD5175_WriteCmd(COMMAND_R_RDAC, 0x00);
    return AD5175_Read16Bit();
}

//��RDAC����д��50-Tp��
void AD5175_WriteRadcTo50tp(void)
{
	AD5175_WriteCmd(COMMAND_STORE_RDAC_50TP,0x00);
	delay_ms(500);  //д��50TP��Ҫ�ȴ�350ms����
}

//�����λ
void AD5175_SoftwareRest(void)
{
	AD5175_WriteCmd(COMMAND_SOFTWARE_RESET,0x00);
	delay_ms(1000); //�����λ֮�󣬵ȴ�100MS
}

//��ȡ50TP�е�����
uint16_t AD5175_Read50TP(uint8_t _50TpAddr)
{
    AD5175_WriteCmd(COMMAND_R_50TP_NEXT_FRAME, _50TpAddr);
    return AD5175_Read16Bit();
}

//��ȡ50TP��ַ
uint16_t AD5175_Read50TPAddress(void) 
{
    AD5175_WriteCmd(COMMAND_R_LAST_50TP_LOCATION, 0x00);
    return AD5175_Read16Bit();
}

//д���ƼĴ���
void AD5175_WriteControl(uint8_t nData)
{
	AD5175_WriteCmd(COMMAND_W_CONTROL,nData);
}
//�����ƼĴ���
uint16_t AD5175_ReadControl(void)
{
	AD5175_WriteCmd(COMMAND_R_CONTROL,0x00);
	return AD5175_Read16Bit();
}

//�������
void AD5175_SoftwareSwitch(uint8_t nData)
{
	AD5175_WriteCmd(COMMAND_SOFTWARE_SHUTDOWN,nData);
}

