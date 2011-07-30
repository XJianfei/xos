#ifndef _12864_H_
#define _12864_H_

#include <intrins.h>
#include <reg52.h>
#include "type.h"
//#define _nop_() ;
#define SHOW_PIC	0
#define DISPLAY_STR	0
/************************��������******************************/
extern void init_12864(void); /*��ʼ��LCD*/
#if DISPLAY_STR
void printstr(register u8_t  x, register u8_t y, unsigned char n, unsigned char *chi); /*��X,Y����ʾһ��(16*16)����*/
#endif /* DISPLAY_STR */
extern void clear_lcd(void);  				/*����,ȫ��Ϊ��*/
extern void clear_12864(void);
extern void reverse(unsigned char line);
void draw_point(register u8_t  x, register u8_t  y, register u8_t  b);
//void draw_hline(register u8_t x, register u8_t y, register u8_t l);
//void draw_vline(register u8_t x, register u8_t y, register u8_t l);
void draw_line(u8_t data x1, u8_t data y1,u8_t data x2,u8_t data y2, u8_t b);
#endif
