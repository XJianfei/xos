#include <intrins.h>
#include "xos.h"
#include "1602.h"

#define BUSY_TIME 100 
#define OTHERS_BOARD
/**/
#ifndef OTHERS_BOARD
	#define L_data P0
	sbit rs_1602=P3^0;
	sbit rw_1602=P3^1;
	sbit en_1602=P3^2;
#else
	#define L_data P2
	sbit rs_1602=P1^2;
	sbit rw_1602=P1^1;
	sbit en_1602=P1^0;
#endif
//----------------------------------------------��������
static void write_1602(unsigned char da, unsigned char cmd);
static unsigned char check_busy(void) ;

#define writedata(da) 	write_1602(da, 1)
#define writecmd(da)	write_1602(da, 0)
static unsigned char check_busy(void) //���LCD״̬�������ǲ��ǻ���æ��
{
	unsigned char busy;
	en_1602 = 0;
	rs_1602 = 0;
	rw_1602 = 1;
	_nop_();
	en_1602 = 1;
	_nop_();
	busy = L_data & 0x80;
	_nop_();
	en_1602 = 0;
	return busy;
}
//----------------------------------------------------д������
static void write_1602(unsigned char da, unsigned char cmd) {
	unsigned int i = BUSY_TIME;
	while (check_busy() || (i-- == 0))
		; //�ȴ�LCDæ��,,..
	en_1602 = 0;
	rs_1602 = cmd;
	rw_1602 = 0;
	L_data = da;
	_nop_();
	en_1602 = 1;
	_nop_();
#if CRYSTAL_1602 > 12
	_nop_();
#endif
	en_1602 = 0;
}
//----------------------------------------------------ָ��λ����ʾһ���ַ�
/***************************ָ��λ����ʾһ���ַ�************************************/
void printc(unsigned char x, unsigned char y, unsigned char dat) {
	disable_irq_save();
	if (y > 2 || x > 39)
		return; //��ֹλ�ó���
	if (y == 0) //
		x = 0x80 + x; //��������
	else
		//
		x = 0xc0 + x;
	writecmd(x);
	writedata(dat);
	enable_irq_restore();
}
/****************************************************************************/
//-------------------------------------------------------ָ��λ����ʾһ���ַ�
void prints(unsigned char x, unsigned char y, unsigned char *dat) {
	disable_irq_save();
	if (y > 2 || x > 39)
		return; //��ֹλ�ó���
	if (y != 0)
		x += 0x40;
	x += 0x80; //��������
	y = 0;
	while (dat[y] != '\0') {
		writecmd(x);
		writedata(dat[y]);
		x++;
		y++;
	}
	EA = 1;
	enable_irq_restore();
}
//---------------------------------------------------��ʼ��LCD
void init_1602() {
	sleep(HZ / 100); //
	EA = 0;
	writecmd(0x38); //
	EA = 1;
	sleep(HZ / 100); //����ģʽ��ʾ����
	EA = 0;
	writecmd(0x38); //
	EA = 1;
	sleep(HZ / 100); //
	disable_irq_save();
	writecmd(0x38); //
	writecmd(0x38);
	writecmd(0x08); //�ر���ʾ
	writecmd(0x06); //��ʾ����ƶ�����
	writecmd(0x0c); //����������������
	enable_irq_restore();
}


