/*
 * File      : bluetooth.h
 * This file is ef comp
 * COPYRIGHT (C) 2017,
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at my addr
 *
 *
 * Change Logs:
 * Date           Author       ZAM
 * 2017-09-26     Bernard      the first version
 */
#include "bluetooth.h"
#include "usart.h"

/*******************************************************************************
�� �� ����void Ble_Bluetooth_Init(void)
���������� ������ʼ���˿�
��ڲ�����							
���ز�����
����ʱ��: 2017-11-02 by zam
********************************************************************************/
void Ble_Bluetooth_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(BLUETOOTH_CONTRO_SEND_RCC | BLUETOOTH_SET_RCC | BLUETOOTH_CMD_RCC |BLUETOOTH_CTS_RCC,ENABLE);
	GPIO_InitStructure.GPIO_Pin=BLUETOOTH_CONTRO_SEND_GPIO;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(BLUETOOTH_CONTRO_SEND_PORT,&GPIO_InitStructure);
	BLUETOOTH_CONTRO_SEND_OFF;//��ʱ׼����������

	GPIO_InitStructure.GPIO_Pin=BLUETOOTH_SET_GPIO;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(BLUETOOTH_SET_PORT,&GPIO_InitStructure);
	BLUETOOTH_SET_ON; //����Ϊ��

	GPIO_InitStructure.GPIO_Pin=BLUETOOTH_CMD_GPIO;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(BLUETOOTH_CMD_PORT,&GPIO_InitStructure);
	BLUETOOTH_CMD_ON; //����Ϊ�� ���ݴ���

	GPIO_InitStructure.GPIO_Pin=BLUETOOTH_CTS_GPIO;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(BLUETOOTH_CTS_PORT,&GPIO_InitStructure);
	#ifdef DEBUG_PERPH
	printf("bluetooth open!\r\n");
	#endif
}
/*******************************************************************************
�� �� ����void Send_DataViaBt(char *buf,int len)
������������������
��ڲ�����	buf ����   len:����						
���ز�����
����ʱ��: 2017-11-02 by zam
********************************************************************************/
void Send_DataViaBt(char *buf,int len)
{
	len++;
	while(len--)
	{
		USART_SendData(BLUETOOTH_USART,*buf);
		while(USART_GetFlagStatus(BLUETOOTH_USART, USART_FLAG_TC) == RESET);
		buf++;
	}
}
/*******************************************************************************
�� �� ����void Sendble_Str(char *buf)
������������������
��ڲ�����	buf ���� 				
���ز�����
����ʱ��: 2017-11-02 by zam
********************************************************************************/
void Sendble_Str(char *buf)
{
	while(*buf!='\0')
	{
		USART_SendData(BLUETOOTH_USART,*buf);
		while(USART_GetFlagStatus(BLUETOOTH_USART, USART_FLAG_TC) == RESET);
		buf++;
	}
}





