/**
 * \file xos_opt.h
 * \brief xos��ϵͳ����, ��ֲʱ������.
 * <p>kernel.c��xos.c Ҫ��ѡGenerate Assembler SRC File �� Assemble SRC File
 * �Ҽ��ļ�->option for file '*.c'
 * 			->Generate Assembler SRC File
 * 			->Assemble SRC File
 * */

#ifndef XOS_OPT_H
#define XOS_OPT_H

#define STC12C5A
#define CPU_1T	1
#define CPU_12T	12
#define CPU_T	CPU_1T
//#define CPU_12T
/** MUC header file */
//#define CPU_12T
#ifdef STC12C5A
#define MCU_H <stc12c5a.h>
#else
#define MCU_H <reg52.h>
#endif


/**
 * ʱ��Ƭ,ϵͳ��ʱ,ʱ����, Ĭ��ʹ�ö�ʱ��0
 * */				 
/* ��ϵͳ���е�������,��ֵ̬. ���Ϊ8, ������Ϊϵͳ����,��Դ������,��ò�����6*/
#define NR_TASK 2	
/** xosϵͳ��ʱ�ж�Ƶ��, 1��ʹ��ʱ��Ƭ�Ĵ���*/
#define HZ 250		
/** һ��ʱ��Ƭ��ʱ��(��λms, ��ϵͳ��ʱ����ʱʱ��)*/
#define TICK_TIME 4		
/** ����ʱ��Ƭ, ���ܴ���15*/
#define TIME_SLICE 15		
// 10ms , 24MHz, 1
/** ����Ƶ��*/
#define FOSC (11.0592)	
#define VFOSC	(12)
#define FOSC12	(1)
/** ϵͳ��ʱ��,������װ��ֵ*/
#define THX 0xF1		
#define TLX 0xC0 							//DC 20
/** ϵͳ��ʱ���õļ������Ĵ���*/
#define THN TH0
#define TLN TL0
#define TRN	TR0
#define ETN	ET0



/** ------------------------------------------------------------- */
/**��ʹ���ź�����Ҫ���������*/
#define SEMPHORE	
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
 * \brief �����ջ
 * STACK_SZ = ((ALL_STACK_SZ) / NR_TASK)
 * �������е�ջ�Ĵ�С, ��Ƭ�������������ջ��С / ������
 * !!!Ҫ��
 * 	����ջ�Ĵ�С����Ҫ:����������ʱ����Ƕ�ײ���*2 + 13(�Ĵ���) +��2(�ں�)
 *  ģ��ջ��С(reentrant�ؼ���): �����뺯����ʹ�ô�С.
 *  �ں�ջ: 6. ������data��ʹ�ô�С, ��ģ��ջ��ʼ��ַ������ջ��ʼ��ַ(û��ģ��ջ)֮��
 * */							
/** ��ջ��ʼ��ַ. Ĭ��Ϊidata��ʼ��ַ*/								 
#define STACK_START	(0x80)		
/** END + 1*/
#define STACK_END	(0x100)		
/** ����PDATA��ջ��С,�Լ�������,���Լӿ��ٶȺͼ��ٴ������*/
#define STACK_SZ	((STACK_END - STACK_START) / NR_TASK)	

/** ------------------------------------------------------------- */
/**
 * ��ζ��������������,���Ե�xos.c�ļ���customize_stack�����������Զ����С������ջ.
 * ֻ����customize_stack������������ջ��ʼ��ַ���.ջ��ַ������0x00~0xff��Χ��.
 * */
//#define CUSTOMIZE_STACK
/** reentrant keyword */
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
 * ���������ں��йصĶ���,,������޸��ں�,���������
 * */

/** XOS���������*/
#define MAX_TASK 8		
/** ������ȱ���ļĴ�����*/
#define SAVE_REG 13		

/** sizeof(task_desc),�����������ṹ���С,�����ýṹ�壬�����Ҳ������ */
#define TASK_SZ 6	

/* ������ */
#define NREG  8
#define USEDREG 1







#endif /* XOS_OPT_H**/
