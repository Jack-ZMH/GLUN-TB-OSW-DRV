#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK STM32F429������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.csom
//�޸�����:2015/6/23
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//********************************************************************************
//V1.0�޸�˵�� 
////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
extern UART_HandleTypeDef UART1_Handler; //UART���

#define RXBUFFERSIZE   1 //�����С
extern u8 aRxBuffer[RXBUFFERSIZE];//HAL��USART����Buffer

//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
void uart2_init(u32 bound);

extern uint8_t Cmd_flag ;
extern uint8_t CmdBuffer[256];

#endif

