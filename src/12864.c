/*****************************************************************************
  /12864Һ����������,
  /
/*****************************************************************************/
#include "12864.h"
#include "xos.h"
#define DATA_PARALLEL	1
#define DATA_SERIAL		0
#define DATA_MODE	1	
#ifdef BOARD	
sbit RS=P2^2;
sbit RW=P2^1;
sbit EN=P2^0;
sbit RST=P3^1;
sbit PSB=P3^0;
sbit cbusy=P1^7;
#define data0 P1

#else
sbit RS = P2 ^ 0;
sbit RW = P2 ^ 1;
sbit EN = P3 ^ 2;
sbit RST = P3 ^ 5;
sbit PSB = P3 ^ 3;

sbit CS = P2^0;
sbit SID = P2^1;
sbit SCLK = P3^2;

sbit cbusy = P0 ^ 7;
#define data0 P0
#endif /* BOARD */

sbit ACC7 = ACC^7;
sbit ACC6 = ACC^6;
sbit ACC5 = ACC^5;
sbit ACC4 = ACC^4;
sbit ACC3 = ACC^3;
sbit ACC2 = ACC^2;
sbit ACC1 = ACC^1;
sbit ACC0 = ACC^0;

#define RW_WR	0
#define RW_RD	1
#define RS_CMD	0
#define RS_DATA	1
#define SET_CS()	CS = 1
#define CLR_CS()	CS = 0
#define SET_CLKH()		SCLK = 1
#define SET_CLKL()		SCLK = 0
#define SET_WRITE()	SID = RW_WR
#define SET_READ()	SID = RW_RD
#define SET_CMD()	SID = RS_CMD
#define SET_DATA()	SID = RS_DATA

/* Serial timing */
#if (CPU_T == CPU_1T)

#define TCLK_WH(n)	\
	do {	\
		_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();	\
	} while (0)
#define TCLK_WL(n)	\
	do {	\
		_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();	\
	} while (0)
#define TCLK_SETUP(n)	\
	do {	\
		_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();	\
	} while (0)
#define TDATA_SETUP()	\
	do {	\
		_nop_();_nop_();	\
	} while (0)
#define TDATA_HOLD()	\
	do {	\
		_nop_();_nop_();   \
	} while (0)

#else

#define TCLK_WH()	\
	do {	\
		_nop_();	\
	} while (0)
#define TCLK_WL()	\
	do {	\
		_nop_();	\
	} while (0)
#define TCLK_SETUP()	\
	do {	\
		_nop_();	\
	} while (0)
#define TDATA_SETUP()	\
	do {	\
	} while (0)
#define TDATA_HOLD()	\
	do {	\
		_nop_();_nop_();  \
	} while (0)

#endif /* CPU_T == CPU_1T */

/* Serial macro */
#define rise_clk_setup()	do {SET_CLKH(); TCLK_SETUP();} while (0)
#define rise_clk_hold()		do {SET_CLKH(); TCLK_SETUP(); TCLK_WH();} while (0)
#define rise_clk()			SET_CLKH()
#define set_slcd_sid(n)		SID = n
#define set_slcd_data(n)	do {SID = n; TDATA_SETUP();} while (0)
#define set_slcd_data_hold(n)	do {set_slcd_data(n); TDATA_HOLD();} while (0)
#define get_slcd_sid()		SID
#define	fall_clk()			SET_CLKL()
#define fall_clk_hold()		do {fall_clk(); TCLK_WL(); } while (0)
/*
#define quit_serial(n)	\
		syn_bit_str(n);	\
		SID = 1;	\
		CLR_CS();
*/
#define write_serial_bit(n)	\
	do {	\
		fall_clk();	\
		TCLK_SETUP();	\
		set_slcd_sid(n);	\
		TDATA_SETUP();	\
		rise_clk();	\
		TCLK_WH();	\
	} while (0)
#define read_serial_bit(n)	\
	do {	\
		fall_clk();	\
		TCLK_SETUP();	\
		TDATA_SETUP();	\
		n = get_slcd_sid();	\
		rise_clk();	\
	} while (0)

#define set_12864_rwrs(rw, rs)	\
	do {	\
		write_serial_bit(rw);	\
		write_serial_bit(rs);	\
	} while (0);
#define write_serial_sam(t, n, b)	\
		do {	\
			t = n;	\
			while (t){ \
				write_serial_bit(b);	\
				--t;	\
			}	\
		} while (0)
#define read_serial_dis(t, n)	\
		do {	\
			t = n;	\
			while (t) {	\
				fall_clk();	\
				TCLK_SETUP();	\
				TDATA_SETUP();	\
				--t;	\
				rise_clk();	\
				TCLK_WH();	\
			}	\
		} while (0)

#if (DATA_MODE == DATA_SERIAL)
#define enter_serial(n, rw, rs)	\
	do {	\
		SET_CS();	\
		SET_CLKH();	\
		write_serial_sam(n, 5, 1);	\
		set_12864_rwrs(rw, rs);	\
		write_serial_bit(0);	\
	} while (0)
#define exit_serial()	CLR_CS()
#endif


#if (DATA_MODE == DATA_SERIAL)
#else

#endif /* DATA_MODE == DATA_SERIAL */



					  
#define LCD_DATA	1
#define LCD_CMD		0
#define CMD 0
#define DATA 1
#define disfiRSt	0xc0
#define sety	0x80	//��һ��.
#define setx	0x80	//�ϰ���
#define setxx	0x88	//�°���
#define C_BUSY_TIME 50
/*			   
			   TC System cycle time 13,000 ns
			   TAS Address setup time 1500ns
			   TR/TF Enable rise/fall time   25ns
			   TDSW Data setup time 1,000ns 
			   TH Data hold time 20ns 
			   TPW Enable pulsewidth 1,500ns 

			   Data setup time TDDR 1,000ns 
 **/
#if (CPU_T == CPU_1T)
#define TC(n)	\
	do {  \
		_nop_();_nop_();_nop_();_nop_();	\
		_nop_();_nop_();_nop_(); \	 
		_nop_();_nop_();_nop_();_nop_();	\
			_nop_();_nop_();_nop_(); \
			_nop_();_nop_();_nop_();_nop_();	\
			_nop_();_nop_();_nop_(); \
	}while(0)
#define TAS(n)	do {_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_(); \
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();}while(0)
#define TR(n)
#define TDSW(n)	do {_nop_();_nop_();_nop_();_nop_();_nop_(); \
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();}while(0)
#define TH(n)	
#define TPW(n)	do {_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_(); \
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_(); \
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_(); }while(0)

#define TDDR(n)	do {_nop_();_nop_();_nop_();_nop_();_nop_(); \
	_nop_();_nop_();_nop_(); \
	_nop_();}while(0)
#else
#define TC()	\
	do {  \
		_nop_();_nop_();_nop_();_nop_();	\
		_nop_();_nop_();_nop_(); \	 
		_nop_();_nop_();_nop_();_nop_();	\
			_nop_();_nop_();_nop_(); \
			_nop_();_nop_();_nop_();_nop_();	\
			_nop_();_nop_();_nop_(); \
	}while(0)
#define TAS(n)	 _nop_()
#define TR(n)	 
#define TDSW(n)	do {_nop_();}while(0)
#define TH(n)	
#define TPW(n)	do {_nop_();}while(0)	

#define TDDR(n)	do {_nop_();}while(0)


#endif /* STC12C5A*/
/*****************λ����*************************/
/*******************************************/
static void write_data(register u8_t dc,register u8_t dat); //д���ݻ�����
static unsigned char read_data(register u8_t b); //�����ݻ�����
static unsigned char chk_busy(); //���æ״̬
void init_12864(); //��ʼ��12864LCD
//void printsnake(unsigned int x,unit y,unsigned char color);		//��������ʾ
/*******************************************/

/********************д���ݻ�ָ��(dc==1Ϊ����)*********************/
static void write_data(register u8_t dc,register u8_t dat) {
#if (DATA_MODE == DATA_PARALLEL)
	register u8_t i = C_BUSY_TIME;
	while ((i != 0) && chk_busy())
		--i;
	RS = dc;
	RW = 0;	
	TAS(i);
	EN = 1;	  
	data0 = dat;
	TPW(i);
	TH(i);
	EN = 0;
#else 
	register u8_t circle, i;
	/* first byte 11111AB0 */
	enter_serial(i, RW_WR, dc);
	circle = 0x80;
	/* high 4 bit DDDD0000*/
	/*
	while (circle != (1 << 3)) {
		write_serial_bit(circle & dat);
		circle >>= 1;
	}*/
	ACC = dat;
	write_serial_bit(ACC7);
	write_serial_bit(ACC6);
	write_serial_bit(ACC5);
	write_serial_bit(ACC4);
	write_serial_sam(i, 4, 0);
	/* low 4 bit 0000DDDD */
	write_serial_bit(ACC3);
	write_serial_bit(ACC2);
	write_serial_bit(ACC1);
	write_serial_bit(ACC0);
/*
	while (circle) {
		write_serial_bit(circle & dat);
		circle >>= 1;
	}*/
	write_serial_sam(i, 4, 0);
	exit_serial();
#endif 
}
/*******************������.״̬.1Ϊ����**************************************/
static unsigned char read_data(register u8_t b) {
#if (DATA_MODE == DATA_PARALLEL)
	register u8_t da;
	register u8_t i = C_BUSY_TIME;
	while ((i != 0) && chk_busy())
		--i;
	RS = b;
	RW = 1;		
	TAS(i);  
	data0 = 0xff;
	EN = 1;	   
	TDDR(i);
	da = data0;
	TPW(i);
	TH(i);
	EN = 0;
	return da;
#else 
	register u8_t dat;
	enter_serial(dat, RW_RD, b);
	dat = 0;
	b = 0;
	read_serial_bit(b);
	dat |= (b << 7);
	read_serial_bit(b);
	dat |= (b << 6);
	read_serial_bit(b);
	dat |= (b << 5);
	read_serial_bit(b);
	dat |= (b << 4);
	read_serial_dis(dat, 4);
	read_serial_bit(b);
	dat |= (b << 3);
	read_serial_bit(b);
	dat |= (b << 2);
	read_serial_bit(b);
	dat |= (b << 1);
	read_serial_bit(b);
	dat |= (b << 0);
	read_serial_dis(dat, 4);
	exit_serial();
	return dat;
#endif
}
/*********************æ״̬���***************************/
static unsigned char chk_busy() {
#if (DATA_MODE == DATA_PARALLEL)
	register unsigned char  busy;
	register unsigned char k;
	EN = 0;
	for (k = 0; k < 2; k++) {
		RS = 0;
		RW = 1;
		TAS(busy);
		data0 = 0xff;  
		EN = 1;	   	
		TR(busy);
		busy = (data0 & 0x80);
		TPW(busy);
		EN = 0;
	}
	return busy;
#else
	register u8_t dat;
	enter_serial(dat, RW_RD, RS_CMD);
	dat = 0;
	read_serial_bit(dat);
	return (dat);
#endif
}

/********************��ʼ��LCD***************************************/
void init_12864() {
	PSB = DATA_MODE;
	RST = 1;
	sleep(HZ / 25);
	disable_irq();
	write_data(0, 0x30); //����ָ��
	_nop_();
	write_data(0, 0x0c); //����ʾ
	_nop_();
	write_data(0, 0x01); //����
	_nop_();
	write_data(0, 0x06); //�����ƶ�����
	enable_irq();
	
}

//����,ȫ��Ϊ��
/*********************************************************/
void clear_lcd(void)
{
	u8_t i,j;
	for(j=0;j<32;j++)
	{
		for(i=0;i<8;i++)
		{
			write_data(0,0x34);
			write_data(0,0x80+j);
			write_data(0,0x80+i);
			write_data(0,0x30);
			write_data(1,0);
			write_data(1,0);

			
			write_data(0,0x34);
			write_data(0,0x80+j);
			write_data(0,0x88+i);
			write_data(0,0x30);	  
			write_data(1,0);
			write_data(1,0);
		}
	}
	write_data (0,0x36);
}
/****************��X,Y����ʾһ��(16*16)����****************/
/*				0<=x<8,0<=y<4	   					*******/
#if DISPLAY_STR
void printstr(register u8_t x, register u8_t  y, register u8_t n, unsigned char *chi) {	
	disable_irq();
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
	write_data(RS_CMD, 0x34);
	enable_irq();
}
#endif /* DISPLAY_STR */
void reverse(unsigned char line) {
	disable_irq();
	write_data(CMD, 0x34);
	write_data(CMD, 4 + line);
	write_data(CMD, 0x30);
	enable_irq();
}

void clear_12864() {
	disable_irq();
	write_data(0, 0x01); //����
	enable_irq();
}

/****************************************************
 ********************Щ�ı���Ҫ��12864���.ֱ��,
 ********************Horizontal/Vertical line
 ****************************************************/
/********************************************/

//void Hline(u8_t x,u8_t y,u8_t L);	//��ֱ�ߺ���,��(x,y)����ʼ,����ΪL
//void Vline(u8_t x,u8_t y,u8_t L);	//��ֱ�ߺ���,��(x,y)����ʼ,����ΪL
/******************����ʵ��****************/
/****************д�㺯��ʵ��,��(x,y)������ʾ��*************/
//bΪ���û��㻹�������.1Ϊ��.0Ϊ��
/***********************************************************/
void draw_point(register u8_t  x,register u8_t  y,register u8_t  b)
{
	u8_t xtemp= x & 0xf;
	u8_t ch1=0,ch2=0;
	u16_t ch=0;
	if(y<=31) {	//���ϰ���
		x=0x80+(x >> 4);
	} else {	   //���°���
		y=y-32;
		x=0x88+(x >> 4);
	}
	disable_irq();
	write_data(0,y+0x80);
	write_data(0,x);
#if (DATA_MODE == DATA_PARALLEL)
	read_data(LCD_DATA);
#endif
	ch1=read_data(LCD_DATA);		 //�ϰ�λ
	ch2=read_data(LCD_DATA);		 //�°�λ
	ch=(ch1<<8)+ch2;
	if(b)					//�����ǻ�������
		ch|=(0x8000>>xtemp);
	else
		ch&=(~(0x8000>>xtemp));
	//�����ǻ滭���ܲ���		
	write_data(0,0x34);
	write_data(0,y+0x80);
	write_data(0,x);
	write_data(0,0x30);
	write_data(1,ch>>8);
	write_data(1,ch&0x00ff);
	write_data(0,0x36);	
	enable_irq();
}
/***************��ֱ�ߺ���,��(x,y)����ʼ,����ΪL********************
void draw_hline(register u8_t x, register u8_t y, register u8_t l)
{
	register u8_t i = 0;
	while (i < l) {
		draw_point(x + i, y, 1);	
		++i;
	}		
}

/***************��ֱ�ߺ���,��(x,y)����ʼ,����ΪL********************
void draw_vline(register u8_t x, register u8_t y, register u8_t l)
{
	register u8_t i=0;
	while (i < l) {
		draw_point(x,y+i,1);	
		++i;
	}
}
/********************************************************************/
//����б��,���ⷽ��ֱ��,����,������(x1,y1)��(x2,y2),��С��������
/********************************************************************/
void draw_line(u8_t data x1, u8_t data y1,u8_t data x2,u8_t data y2, u8_t b)
{
	u8_t idata temp,sx,sy,slope=0;
	register u8_t y = y1, x = x1,i = x1,j = 0, xx=0,yy=0;
	s8_t idata p;
	//XX,YY��š�X��Y,x,y���ֱ������,sx,sy����Ǽ�һ���Ǽ�һ,
	//slope��ʾ�Ƿ�б�ʴ���1.i,j������ѭ������
	if(x2>x1)
		xx=x2-x1;
	else
		xx=x1-x2;
	if(y2>y1)
		yy=y2-y1;		
	else
		yy=y1-y2;
	j=x2;			//��ʼ��Ϊ�Ƶ�x2��/

	if(yy <= xx){ 		//б��С��1��X����.����1��Y����
		i=x1; j=x2;
	} else {
		i=y1; j=y2;
	}

	if(yy>xx) {		//�ж�б�ʴ���1,����1�򲽽�Y,С��1�򲽽�X
		temp=xx;		//
		xx=yy;		//
		yy=temp;		//xx.yy�Ե�
		slope=1;		//
	}

	if(y2>y1)			//����ֱ�������»�������
		sy=1;		//����
	else
		sy=-1;		//�ݼ�

	if(x2>x1)			//����ֱ��������������
		sx=1;		//����
	else
		sx=-1;		//�ݼ�
	p = (yy << 1) - xx;		//��ʼP,������Ӧ����ʾƫ�ϻ���ƫ��

	if(i>j) {		//����i,j�Ĵ�С
		temp=i;
		i=j;
		j=temp;
	}

	while (i <= j){
		draw_point(x,y,b);		//��ʾ��
		if(p>=0) {
			if(!slope)			//б��С��1�����.
				y+=sy;
			else
				x+=sx;		//б�ʴ���1
			p = p - (xx << 1);			//��Ĳ���
		}
		if(slope)				//��������
			y+=sy;
		else
			x+=sx;
		p = p + (yy << 1);
		++i;
	}
}

#if SHOW_PIC
void pps(u8_t *img)
{

	u8_t i,j;
	for(j=0;j<32;j++)
	{
		for(i=0;i<8;i++)
		{
			write_data(0,0x34);
			write_data(0,0x80+j);
			write_data(0,0x80+i);
			write_data(0,0x30);
			write_data(1,img[j*16+i*2]);
			write_data(1,img[j*16+i*2+1]);
		}
	}
	for(j=32;j<64;j++)
	{
		for(i=0;i<8;i++)
		{
			write_data(0,0x34);
			write_data(0,0x80+j-32);
			write_data(0,0x88+i);
			write_data(0,0x30);
			write_data(1,img[j*16+i*2]);
			write_data(1,img[j*16+i*2+1]);
		}
	}
	write_data (0,0x36);
}
#endif
