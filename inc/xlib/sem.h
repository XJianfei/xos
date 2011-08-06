#ifndef SEM_H
#define SEM_H
#include "xos.h"
#ifdef SEMPHORE

/**
 * \brief �ź����ṹ��
 */
typedef struct {
/** count �ź�����ֵ,��\a countΪ0,������������ȡ����ź���,����������� */
	u8_t count;		// ������
/** var wait_task ��־����Щ�����ڵȴ�����ź���,һλ��Ӧһ������ */
	u8_t wait_task;	// �ȴ����ź��������񣬡�XOS���������Ϊ8,  
					// ����0~7,1bit��Ӧһ������.
}semphore;

extern void sem_down(semphore *sem);
extern void sem_up(semphore *sem, u8_t n);
extern u8_t sem_try_down(semphore *sem);

#endif //SEMPHORE
#endif /* SEM_H*/
