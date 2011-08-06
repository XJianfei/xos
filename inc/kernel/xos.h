/**
 * xos API
 * */
/**
 * v0.1~
 * ���Ż�,С�޸�.
 * */
#ifndef XOS_H
#define XOS_H
#include "type.h"
#include "xos_opt.h"
#include MCU_H
#include <intrins.h>


/* ������������Ԫ�ص��ڴ�ƫ��ֵ,, �Ѳ�ʹ�ã����ýṹ��ʵ����*/
#define STACT_BOTTOM 0
#define ID_TIMESLICE 1
#define TASK_STATUS	2
#define SLEEP_TIME 3
#define SEM_COUNT 5
extern u8_t data current; 			/* ��ǰ����*/
//extern u8_t data _irq;
extern u8_t data stack_bottom[NR_TASK];
extern u8_t data id_timeslice[NR_TASK];
extern u8_t data task_status[NR_TASK];
extern u16_t data sleep_time[NR_TASK];
//extern _u8 data sem_count[NR_TASK];

/* ����״̬��־λ*/
/** ����ȴ��ź��� */
#define TASK_SEM_WAIT (1 << 4)
/** ����˯���� */
#define TASK_SLEEP (1 << 5)
/** ����������������� */
#define TASK_OVER (1 << 7)
/*
typedef struct {
	u8 stack_bottom;		// ��ջ��
	u8 id_timeslice;		// id �� ʱ��Ƭ
	/**
	 * id_timeslice:
	 * [0:3]-id	, ����id
	 * [4~7]-timeslice ,		ʱ��Ƭ
	 *
	u8 task_status;		// ״̬
	u16 sleep_time;			// sleep ���õ�˯��ʱ��. ��λΪHZ.
	u8	sem_count;		// �ڵȴ��ź����ĸ���.
}task_desc;/**/

/**
 * ��������ӵ�XOS.
 * func: ����ĺ�����ַ
 * */
extern void add_task(unsigned int func);
/**
 * XOS��ʼ��,��main������,
 * ���������, ��ʼ������Ĺ��������.
 * */
extern void xos_init();

/* ����ĺ���������ں�, ����Ĵ�����ջ*/
extern void sleep(unsigned int n);
extern void schedule();
#define is_kernel() (PCON &= 0x04)
#define set_os()   	(PCON |= 0x04)
#define clr_os()	(PCON &= ~0x04)

#define disable_tick() 	TRN = 0
#define enable_tick()	TRN = 1

#define disable_irq()	do{\
			EA = 0;	\
			TRN	= 0;	\
		}while(0)

#define enable_irq()do{	\
			EA = 1;	\
			TRN = 1;	\
		}while(0)

#define disable_irq_save() do{ \
			EA = 0;	\
		}while(0)

#define enable_irq_restore() do {\
			EA = 1;				 \
		}while(0)

#define rand()	TLN
//#define 
#endif /* XOS_H*/
