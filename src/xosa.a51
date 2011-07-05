/**
 * XOS �ں�.
 * �ں˻����Ҫ����ʵ��
 **/
;��ʼ��XOS��������ݽṹ
;#include "XOS.H"
#include "xos_opt.h"



; r0~r7,�û�ģʽ addr:0x00~0x07
UR0	data 0x00
UR1	data 0x01
UR2	data 0x02
UR3	data 0x03
UR4	data 0x04
UR5	data 0x05
UR6	data 0x06
UR7	data 0x07

;task_desc 

	NAME XOSA
_xos bit	0xd0.5	;PSW.F0

	extrn code 	(find_next)
	extrn code 	(decreas_sleep_time)
	extrn code 	(do_schedule)
	extrn code 	(xos_init)

	extrn data 	(stack_bottom)
	extrn data 	(current)
	extrn data 	(os_sp)


/**
CSEG	AT	0000BH
	LJMP	kernel_tick
;Os using USEDREG
; kernel_tick() interrupt 1, timer 0
	using 0
kernel_tick:
	setb EA		
	push DPH	
	push DPL
	push PSW
	push B
	push ACC	
	setb _xos	
	mov os_sp, SP
	call irq_back	; �˳��ж�״̬,,reti,���ж�
	lcall decreas_sleep_time
	mov TH0, #TH
	mov TL0, #TL
	ljmp do_schedule
irq_back:
	reti
	 	
; END OF kernel_tick
/**/


END