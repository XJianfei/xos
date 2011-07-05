/**
 * file: xos_opt.h
 * xos��ϵͳ����, ��ֲʱ������.
 * */
#ifndef XOS_OPT_H
#define XOS_OPT_H
/**
 * kernel.c��xos.c Ҫ��ѡGenerate Assembler SRC File �� Assemble SRC File
 * �Ҽ��ļ�->option for file '*.c'
 * 			->Generate Assembler SRC File
 * 			->Assemble SRC File
 * */

#define INCLUDE_MCU <reg52.h>

/* ��ϵͳ���е�������,��ֵ̬. ���Ϊ8, ������Ϊϵͳ����,��Դ������,��ò�����6*/
#define NR_TASK 4	

/**
 * �����ջ
 * STACK_SZ = ((ALL_STACK_SZ) / NR_TASK)
 * �������е�ջ�Ĵ�С, ��Ƭ�������������ջ��С / ������
 * !!!Ҫ��
 * 	����ջ�Ĵ�С����Ҫ:����������ʱ����Ƕ�ײ���*2 + 13(�Ĵ���) +��2(�ں�)
 *  ģ��ջ��С(reentrant�ؼ���): �����뺯����ʹ�ô�С.
 *  �ں�ջ: 6. ������data��ʹ�ô�С, ��ģ��ջ��ʼ��ַ������ջ��ʼ��ַ(û��ģ��ջ)֮��
 * */															 
#define STACK_START	(0x80)		/* ��ջ��ʼ��ַ. Ĭ��Ϊidata��ʼ��ַ*/
#define STACK_END	(0x100)		/* END + 1*/
/* ����PDATA��ջ��С,�Լ�������,���Լӿ��ٶȺͼ��ٴ������*/
#define STACK_SZ	((STACK_END - STACK_START) / NR_TASK)	

/**
 * ��ζ��������������,���Ե�xos.c�ļ���customize_stack�����������Զ����С������ջ.
 * ֻ����customize_stack������������ջ��ʼ��ַ���.ջ��ַ������0x00~0xff��Χ��.
 * */
//#define CUSTOMIZE_STACK
#define XOS_REENTRANT
#define C_BP ?C_IBP
#define C_BP_SIZE	10
#define C_BP_END	0x80
#define C_BP_START	(C_BP_END - C_BP_SIZE * NR_TASK)
/**
 * ����CUSTOMIZE_C_BP
 * */
//#define CUSTOMIZE_C_BP




/**
 * ʱ��Ƭ,ϵͳ��ʱ,ʱ����, Ĭ��ʹ�ö�ʱ��0
 * */
#define HZ 100		/* xosϵͳ��ʱ�ж�Ƶ��, 1��ʹ��ʱ��Ƭ�Ĵ���*/
#define TICK_TIME 10		/* һ��ʱ��Ƭ��ʱ��(��λms, ��ϵͳ��ʱ����ʱʱ��)*/
#define TIME_SLICE 5		/* ����ʱ��Ƭ, ���ܴ���15*/
// 10ms , 24MHz, 1
#define FOSC 11.0592	/* ����Ƶ��*/
#define TH 0xDC		/* ϵͳ��ʱ��,������װ��ֵ*/
#define TL 0x20 
/* ϵͳ��ʱ���õļ������Ĵ���*/
#define THN TH0
#define TLN TL0
/**
 * �����������ʱ,�Ƿ�������������ʱ���ѵ�������.(sleep(n),n�ѵ�).
 * ���SLEEPED_FIRST ������0, ������
 *
 * ���ú�,��һ�������һ��ʱ��Ƭ�����,���������ʱ���ѵ�,��δ���е�����,
 * ��ʹ��������ʱ��Ƭ,�����ó�CPU������ʱ���ѵ��ĵ�����.
 * ��������Ϊ������ʱ�侫�ȸ���.
 * */
#define SLEEPED_FIRST 5


/**
 * ���������ں��йصĶ���,,������޸��ں�,���������
 * */

#define MAX_TASK 8		/* XOS���������*/
#define SAVE_REG 13		/* ������ȱ���ļĴ�����*/
#define TASK_SZ 6		//sizeof(task_desc),�����������ṹ���С


#define NREG  8
#define USEDREG 1

/* ������������Ԫ�ص��ڴ�ƫ��ֵ*/
#define STACT_BOTTOM 0
#define ID_TIMESLICE 1
#define TASK_STATUS	2
#define SLEEP_TIME 3
#define SEM_COUNT 5

/* ����״̬��־λ*/
#define TASK_SEM_WAIT 0x10
#define TASK_SLEEP 0x20
#define TASK_OVER 0x80


#endif /* XOS_OPT_H**/
