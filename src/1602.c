#include <intrins.h>
#include <reg52.h>
#include "xos.h"
#include "1602.h"

#define BUSY_TIME 100
//----------------------------------------------��������
static void write_1602(unsigned char da, unsigned char cmd);
static unsigned char check_busy(void) ;

#define writedata(da) 	write_1602(da, 1)
#define writecmd(da)	write_1602(da, 0)
static unsigned char check_busy(void) //���LCD״̬�������ǲ��ǻ���æ��
{
	unsigned char busy;
	en = 0;
	rs = 0;
	rw = 1;
	_nop_();
	en = 1;
	_nop_();
	busy = L_data & 0x80;
	_nop_();
	en = 0;
	return busy;
}
//----------------------------------------------------д������
static void write_1602(unsigned char da, unsigned char cmd) {
	unsigned int i = BUSY_TIME;
	while (check_busy() || (i-- == 0))
		; //�ȴ�LCDæ��,,..
	en = 0;
	rs = cmd;
	rw = 0;
	L_data = da;
	_nop_();
	en = 1;
	_nop_();
#if CRYSTAL_1602 > 12
	_nop_();
#endif
	en = 0;
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


