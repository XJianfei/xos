/*! 
 * \file kernel.c
 * \brief �ں˴���, �������, ʱ��Ƭ��˯�ߴ���,
 * @author xjf cexowginui@163.com
 */
#include "xos.h"
#include "kernel.h"

#ifdef XOS_REENTRANT

	/* ����ջ��ָ�� */
	u8_t data bp[NR_TASK];  
	#pragma ASM
		extrn data (?C_IBP) /*  */
	#pragma ENDASM

#endif 
/*
#pragma ASM

#pragma ENDASM		
*/
/**
 * 
 */
unsigned char xpcon;	/* ����ʱ,PCON�Ḵλ,����Ҫ���� */
/**
 * �������, �ҳ���������ʱ��Ƭ����������,û�п����е�������<br>
 * ��������״̬,ֱ����һ��ʱ��Ƭ�����������ж�.
 */
void do_schedule()
{
	//_u8 id;
TRY_AGAIN:
	//id = find_next();
	if (find_next() == NR_TASK) {
		SP = os_sp;
		EA = 1;
		xpcon = PCON;
		PCON |= 1;			//���ߡ�
		PCON = xpcon;
		goto TRY_AGAIN;
	}
	//quit_os(id);	

#ifdef XOS_REENTRANT	
#pragma ASM	
		// if (current != findnext()) //r7 = findnext();  {
		MOV  	A,current
		XRL  	A,r7
		JZ   	POPREGS

		// bp[current] = C_BP
		mov a, #bp
		add a, current
		mov r0, a
		mov @r0, C_BP 
		// C_BP = bp[r7] // 
		mov a, #bp
		add a, r7
		mov r0, a
		mov C_BP, @r0
		// }  
POPREGS:
#pragma ENDASM

#endif /* XOS_REENTRANT*/

	//current = find_next();
	
#pragma ASM		
	mov current, r7	
#pragma ENDASM 
	SP = stack_bottom[current];
#pragma ASM
		pop ar7;
		pop ar6;
		pop ar5;
		pop ar4;
		pop ar3;
		pop ar2;
		pop ar1;
		pop ar0;
#pragma ENDASM	 
	_pop_(PSW);    
	_pop_(DPL);
	_pop_(DPH);	  
	_pop_(B);	
	_pop_(ACC); 
	clr_os();
}




/**
 * ������һ����Ҫִ�е�����
 * @return��һ��Ҫִ�е�����, �������NR_TASK,��ȫ�������߻������������е�״̬.
 */
u8_t find_next()
{
	u8_t id, tmp;
	if (id_timeslice[current] != 0)
		id_timeslice[current]--;
#if (SLEEPED_FIRST != 0)
	//��������ʱ�����������, sleeped_taskÿһλ����һ������
	//�������ߣ�����Ӧ��sleeped_taskλ��λ
	if (sleeped_task != 0) {
		for (id = 0; id < NR_TASK; id++) {
			tmp = (1 << id);
			if (sleeped_task & tmp) {
				sleeped_task &= tmp;
				if (task_status[id] == 0) {
					goto retback;	 
				}
			}
		}		
	}
#endif /* SLEEPED_FIRST*/
	id = current;
	while ((id_timeslice[id] & 0xf) == 0
		|| (task_status[id] != 0)) {	
		if (++id == NR_TASK) {
			id = 0;		
		}
		/* ���������ʱ��Ƭ������, ʱ��Ƭ+5, ���¿�ʼ*/
		if (id == current) {
			for (id = 0; id < NR_TASK; id++) {
				id_timeslice[id] &= 0xf0;
				id_timeslice[id] += TIME_SLICE;
			}				 
			id = 0;
			while (task_status[id] != 0) {
				id++;
				if (id == NR_TASK)
					goto retback;//return id;
			}
			break;
		}
	}
retback:
	return id;
}

/**
 * ��������ʱ��ݼ�
 * */
static void decreas_sleep_time()
{
	u8_t i = 0;
	for (; i < NR_TASK; i++) {
		if (sleep_time[i] != 0) {
			sleep_time[i]--;
			if (sleep_time[i] == 0) {
				task_status[i] &= (~TASK_SLEEP);
#if (SLEEPED_FIRST != 0)
				sleeped_task |= (1 << i);
#endif // SLEEPED_FIRST
			}
		}
	}
}

/**
 * ϵͳ��ʱ���жϺ���<br>
 * ���˶�ʱ��1, ���������¼�,����
 * @see do_schedule()
 * @see find_next()
 * */
void kernel_tick() interrupt 1
{	 
	THN = THX;
	TLN = TLX;
	if (!is_kernel())
		stack_bottom[current] = SP;
	SP = os_sp;
	set_os();
/* ���ж�״̬*/
#pragma ASM
	call irq_back
#pragma ENDASM
	decreas_sleep_time();
	do_schedule();

#pragma ASM
irq_back:
	reti
#pragma ENDASM	
}
/**/
