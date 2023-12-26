#ifndef BSP_AD5175_H
#define BSP_AD5175_H
#include "bsp_i2c.h"

/*
* 1��AD5175ʹ��ǰ��Ҫ��C0��C1����λ
*/

#define AD5175_eRST	 				GPIO_PIN_0
#define AD5175_GPIO_PORT            GPIOC

//7λ��ַλ
#define AD5175_ADDR					0x2C	//addr connect VCC
#define AD5175_WIRE_ADDR			(AD5175_ADDR << 1) | 0x00
#define AD5175_READ_ADDR			(AD5175_ADDR << 1) | 0x01

/* ����������� */
#define COMMAND_NOP                     0x00	//NOP
#define COMMAND_W_RDAC                  0x01	//�����мĴ�����������д��RDAC��
#define COMMAND_R_RDAC                  0x02	//��ȡRDAC�α�Ĵ��������ݡ�
#define COMMAND_STORE_RDAC_50TP         0x03	//�洢�α����ã���RDAC���ô洢��50-TP�С�
#define COMMAND_SOFTWARE_RESET          0x04	//�����λ���������һ��50-TP�洢���洢��ֵ��ˢ��RDAC��
#define COMMAND_R_50TP_NEXT_FRAME       0x05	//����һ֡�д�SDO�����ȡ50-TP�����ݡ�
#define COMMAND_R_LAST_50TP_LOCATION    0x06	//��ȡ���һ��50-TP��̴洢��λ�õĵ�ַ��
#define COMMAND_W_CONTROL               0x07	//�����мĴ�����������д����ƼĴ�����
#define COMMAND_R_CONTROL               0x08	//��ȡ���ƼĴ��������ݡ�
#define COMMAND_SOFTWARE_SHUTDOWN       0x09	//����ضϡ�D0 = 0������ģʽ��D0 = 1���ض�ģʽ


//������ƼĴ�������
#define RADC_ENABLE						0x20
#define RADC_DISABL						0x00

#define AD5175_50TP_ENABLE				0x01
#define AD5175_50TP_DISABL				0x00

/* ��������ض�ģʽ */	
#define SOFT_NORMAL_MODE				0x00	//����ģʽ
#define SOFT_SHUTOFF_MODE				0x01	//�ض�ģʽ



void ad5175_Init(void);

uint8_t AD5175_WriteByte(uint8_t * pucByte); /*д�ֽں���*/
uint16_t AD5175_ReadByte(uint8_t * pucByte); /*���ֽں���*/

uint8_t AD5175_WriteCmd(uint8_t ucCmd, uint16_t nData);//д������
uint16_t AD5175_Read16Bit(void);//��ȡ16BIT�Ĵ���

//���ܺ���
void AD5175_WriteRDAC(uint16_t nRDAC);//д��RDAC����
uint16_t AD5175_ReadRDAC(void);//��ȡRDAC����
void AD5175_WriteRadcTo50tp(void);//��RDAC����д��50-Tp��
void AD5175_SoftwareRest(void);//�����λ
uint16_t AD5175_Read50TP(uint8_t _50TpAddr);//��ȡ50TP�е�����
uint16_t AD5175_Read50TPAddress(void);//��ȡ50TP��ַ
void AD5175_WriteControl(uint8_t nData);//д���ƼĴ���
uint16_t AD5175_ReadControl(void);//�����ƼĴ���
void AD5175_SoftwareSwitch(uint8_t nData);//�������

//ʹ�ú���



#endif

