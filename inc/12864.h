#ifndef _12864_H_
#define _12864_H_

#include <intrins.h>
#include <reg52.h>
//#define _nop_() ;
#ifdef BOARD	
sbit rs=P2^2;
sbit rw=P2^1;
sbit en=P2^0;
sbit RST=P3^1;
sbit PSB=P3^0;
sbit cbusy=P1^7;
#define data0 P1

#else
sbit rs = P3 ^ 0;
sbit rw = P3 ^ 1;
sbit en = P3 ^ 2;
sbit RST = P3 ^ 5;
sbit PSB = P3 ^ 3;
sbit cbusy = P0 ^ 7;
#define data0 P0

#endif

#define CMD 0
#define DATA 1
#define disfirst	0xc0
#define sety	0x80	//��һ��.
#define setx	0x80	//�ϰ���
#define setxx	0x88	//�°���
/************************��������******************************/
extern void init_12864(void); /*��ʼ��LCD*/
extern void print(unsigned char x, unsigned char y, unsigned char n, unsigned char *chi); /*��X,Y����ʾһ��(16*16)����*/
//extern void cls(void);  				/*����,ȫ��Ϊ��*/
extern void clear_12864(void);
extern void reverse(unsigned char line);

#endif
