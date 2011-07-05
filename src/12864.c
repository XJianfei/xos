/*****************************************************************************
 /12864Һ����������,
 /
 /*****************************************************************************/
#include "12864.h"
#include "xos.h"
#define C_BUSY_TIME 50
/*****************λ����*************************/
/*******************************************/
static void write_data(unsigned char dc, unsigned char dat); //д���ݻ�����
static unsigned char read_data(unsigned char b); //�����ݻ�����
static unsigned char chk_busy(); //���æ״̬
void init_12864(); //��ʼ��12864LCD
void cls(); //ȫ������
void print(unsigned int x, unsigned int y, unsigned char *chi, unsigned char n); //д���ֻ��ַ�
//void printsnake(unsigned int x,unit y,unsigned char color);		//��������ʾ
/*******************************************/

/********************����**************************       
 void delay(unsigned int n)
 {
 int s;
 for(;n>0;n--)
 for(s=124;s>0;s--);
 }
 /*********************æ״̬���***************************/
static unsigned char chk_busy() {
	unsigned char  busy;
	unsigned char k;
	en = 0;
	for (k = 0; k < 2; k++) {
		rs = 0;
		rw = 1;
		en = 1;	   
		data0 = 0xff;
		busy = (data0 & 0x80);
		en = 0;
	}
	return busy;
}
/********************д���ݻ�ָ��(dc==1Ϊ����)*********************/
static void write_data(unsigned char dc, unsigned char dat) {
	//while(chk_busy()){;}
	/**/
	unsigned int i = C_BUSY_TIME;
	while ((i-- == 0) && chk_busy())
		;
	/**/
	rs = dc;
	rw = 0;
	en = 1;
	_nop_();
	data0 = dat;
	en = 0;
}
/*******************������.״̬.1Ϊ����**************************************/
static unsigned char read_data(unsigned char b) {
	unsigned char da;
	unsigned int i = C_BUSY_TIME;
	while ((i-- == 0) && chk_busy())
		;
	rs = b;
	rw = 1;
	en = 1;
	data0 = 0xff;
	da = P0;
	en = 0;
	return da;
}
/********************��ʼ��LCD***************************************/
void init_12864() {
	PSB = 1;
	RST = 1;
	sleep(HZ / 25);
	EA = 0;
	write_data(0, 0x30); //����ָ��
	_nop_();
	write_data(0, 0x0c); //����ʾ
	_nop_();
	write_data(0, 0x01); //����
	_nop_();
	write_data(0, 0x06); //�����ƶ�����
	EA = 1;
}

//����,ȫ��Ϊ��
/*********************************************************
 void cls()
 {
 unsigned char data i,j;
 for(i=0;i<32;i++)
 {
 for(j=0;j<8;j++)
 {
 write_data(0,0x34);		//������չ����ָ��,��Ϊ�ػ滭
 write_data(0,0x80+i);		//дY��ַ
 write_data(0,0x80+j);		//дX��ַ
 write_data(0,0x30);		//���û�������ָ��
 write_data(1,0x00);	 //����д������8λ����.
 write_data(1,0x00);
 }
 }
 for(i=0;i<32;i++)
 {
 for(j=0;j<8;j++)
 {
 write_data(0,0x34);
 write_data(0,0x80+i);
 write_data(0,0x88+j);
 write_data(0,0x30);
 write_data(1,0x00);
 write_data(1,0x00);
 }
 }
 write_data(0,0x36);
 }
 /****************��X,Y����ʾһ��(16*16)����****************/
/*				0<=x<8,0<=y<4	   					*******/
void print(unsigned char x, unsigned char y, unsigned char n, unsigned char *chi) {
	disable_irq_save();
	switch (y) {
	case 0:
		y = 0x80;
		break;
	case 1:
		y = 0x90;
		break;
	case 2:
		y = 0x88;
		break;
	case 3:
		y = 0x98;
		break;
	}
	y += x; //����Ҫ��ʾ��Һ������
	write_data(0, 0x30);
	write_data(0, y);
	if (n == 0)
		n = 16;
	y = 0;
	while (chi[y] != '\0' && n--) {
		write_data(1, chi[y]);
		y++;
	}
	enable_irq_restore();
}

void reverse(unsigned char line) {
	disable_irq_save();
	write_data(CMD, 0x34);
	write_data(CMD, 4 + line);
	write_data(CMD, 0x30);
	enable_irq_restore();
}

void clear_12864() {
	disable_irq_save();
	write_data(0, 0x01); //����
	enable_irq_restore();
}
