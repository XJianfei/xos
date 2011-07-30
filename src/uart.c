/*
 * uart.c
 */
/**
 * ��ʼ����ʱ��1�ʹ���ͨѶ
 * 8bit����,����żУ��,1ֹͣλ
 * */
#include "uart.h"
#include <reg52.h>
void init_uart(unsigned char th, unsigned char smod)
{
	TMOD = (TMOD & ~0xf0) | 0x20; //��ʱ��1.������ʽ2
	TH1 = th;
	TL1 = th; //������Ϊ9.6K

	SCON = 0x50; //������ʽ1.�������.SM2=0;
	if (smod)
		PCON |= 0x80;
	else
		PCON &= ~(0x80);

	EA = 1; //ȫ���жϿ�

	TR1 = 1; //������ʱ��1
	ES = 1; //�������ж�
	PS = 1;
}
/**
void com_uart(void) interrupt 4
{
	uchar str;
	ES=0;
	/*			���������ж�						*
	if(RI)
	{
		str=SBUF;
		RI=0;
		P0=str;
	}
	/*          ���������ж�                        *
	if(TI)
	{
		TI=0;
	}
	ES=1;
}
 * */
