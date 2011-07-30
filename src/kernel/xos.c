/**
 * xos API
 * */
#include "xos.h"
#include "kernel.h"
#include INCLUDE_MCU

u8_t data current = 0; /*��ǰ����*/
u8_t data os_sp;
u8_t data _irq;

u8_t data stack_bottom[NR_TASK];
u8_t data id_timeslice[NR_TASK];						   
u8_t data task_status[NR_TASK];
u16_t data sleep_time[NR_TASK];

#if (SLEEPED_FIRST != 0)   
	//sleeped_taskÿһλ����һ������
	//�������ߣ�����Ӧ��sleeped_taskλ��λ
	u8_t sleeped_task = 0;
#endif /* SLEEPED_FIRST*/	    

#ifdef XOS_REENTRANT  
	extern u8_t data bp[NR_TASK]; 
#pragma ASM		 
	extrn data (?C_IBP)
#pragma ENDASM
#endif 

#ifdef CUSTOMIZE_STACK
static void customize_stack()
{
	stack_bottom[0] = 0x80 + SAVE_REG + 1;
	stack_bottom[1] = 0x90 + SAVE_REG + 1;
	stack_bottom[id] = STACK_START + SAVE_REG + 1;
	/* ... */
}
#endif

#ifdef CUSTOMIZE_C_BP
static void customize_c_bp()
{
	bp[0] = 0x80;
	bp[1] = 0x76;
	/* ... */
}
#endif	/* CUSTOMIZE_C_BP*/

/**
 * xos_init����. ��ʼ��Ƭ���Ĵ���,����
 * */
 /**
 
XOS_INIT:
	mov OS_SP, sp	; ���浱ǰջλ��,,�Ժ����½����ں˶������ջ��ʼ
	lcall _init
	;sp = ����0ջ,��ʼ����0
	mov a, stack_bottom
	clr c
	subb a, #SAVE_REG
	mov sp, a	
	ret
 */
void xos_init()
{
	os_sp = SP;

	THN = THX;
	TLN = TLX;
	TMOD = (TMOD & (~0x0f)) | 0x01;
	IP = 0x02;
	EA = 1;
	TRN = 1;
	ETN = 1;
	current = 0;

#ifdef CUSTOMIZE_STACK
	customize_stack();
#endif


	SP = stack_bottom[0] - SAVE_REG;

#ifdef XOS_REENTRANT 
#ifdef CUSTOMIZE_C_BP
	customize_c_bp();
#endif
#pragma ASM
	mov C_BP, #C_BP_END
#pragma ENDASM
#endif 
}

/**
 * ��������ӵ�XOS.
 * func: ����ĺ�����ַ
 * */
void add_task(unsigned int func) 
{	
	u8_t id = current;	 
	u8_t *p;
	
	current++;
	id_timeslice[id] = (id << 4) + TIME_SLICE;
	task_status[id] = 0x00;
#ifndef CUSTOMIZE_STACK
	stack_bottom[id] = STACK_SZ * id + STACK_START + SAVE_REG + 1;
#endif
	p = (u8_t *)(STACK_SZ * id + STACK_START);
	*p = (func & 0xff);
	p++;
	*p = (func >> 8); 
#ifdef XOS_REENTRANT 
	#ifndef CUSTOMIZE_C_BP
		bp[id] = C_BP_END - (C_BP_SIZE * id);
	#endif
#endif 		
	//return id;
	/**/
}

/**
 * �����������, �����ó�CPU, �ó�һ����������. time slice ʱ��Ƭ��0
 * */
void schedule()
{
#pragma ASM			
	push 	acc
	PUSH 	B	   	
	PUSH 	DPH	   	
	PUSH 	DPL	   	
	PUSH 	PSW	   	
	PUSH 	AR0	   	
	PUSH 	AR1	   	
	PUSH 	AR2	   	
	PUSH 	AR3	   	
	PUSH 	AR4	   	
	PUSH 	AR5	   	
	PUSH 	AR6		
	PUSH 	AR7			 
#pragma ENDASM	
	stack_bottom[current] = SP;
	SP = os_sp;
	set_os();
	id_timeslice[current] &= (~0x0f);
	do_schedule();
}

/**
 * ��������
 * n: ���ߵ�ʱ��, ��λΪHZ,��ϵͳʱ��Ƭ��ʱ��. ���ΪHZ(��)��1��,
 * 		���Ϊ0, �������ٹ���.
 * PS: �������������������ѭ������,��ô���Ӧ�õ���sleep(0),�������ٹ���.����ϵͳ�ܷ�
 * */
void sleep(unsigned int n) 
{	
	u8_t tmp;
#pragma ASM
	push 	acc
	PUSH 	B	   	
	PUSH 	DPH	   	
	PUSH 	DPL	   	
	PUSH 	PSW	   	
	PUSH 	AR0	   	
	PUSH 	AR1	   	
	PUSH 	AR2	   	
	PUSH 	AR3	   	
	PUSH 	AR4	   	
	PUSH 	AR5	   	
	PUSH 	AR6		
	PUSH 	AR7			 
#pragma ENDASM	
	stack_bottom[current] = SP;
	SP = os_sp;
	set_os();
	/* ʱ��Ƭ���ó���һ��*/
	tmp = (0x100 - THN);
	if (tmp > ((0xff - THX) >> 1))
		n++;
	sleep_time[current] = n;
	tmp = 0;
	tmp |= TASK_SLEEP;
	if (tmp == 0) {
		tmp |= TASK_OVER;
	} 
	task_status[current] |= tmp;
	do_schedule();
}

