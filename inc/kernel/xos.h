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
#include <reg52.h>
#include <intrins.h>


extern u8_t data current; 			/* ��ǰ����*/
extern u8_t data _irq;
extern u8_t data stack_bottom[NR_TASK];
extern u8_t data id_timeslice[NR_TASK];
extern u8_t data task_status[NR_TASK];
extern u16_t data sleep_time[NR_TASK];
//extern _u8 data sem_count[NR_TASK];
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
/**
 * ��������
 * n: ���ߵ�ʱ��, ��λΪHZ,��ϵͳʱ��Ƭ��ʱ��. ���ΪHZ(��)��1��,
 * 		���Ϊ0, �������ٹ���.
 * PS: �������������������ѭ������,��ô���Ӧ�õ���sleep(0),�������ٹ���.����ϵͳ�ܷ�
 * */
extern void sleep(unsigned int n);
/**
 * �����������, �����ó�CPU, �ó�һ����������. time slice ʱ��Ƭ��0
 * */
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

			   /**
			   
			_irq = IE;	\
			TR0 = 0;	\  

			IE = _irq;	\
			TR0 = 0;	\
			   
			   */

#define rand()	TLN
//#define 
#endif /* XOS_H*/
