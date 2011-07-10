#ifndef SEM_H
#define SEM_H
#include "xos.h"
#ifdef SEMPHORE

typedef struct {
	u8 count;		// ������
	u8 wait_task;	// �ȴ����ź��������񣬡�XOS���������Ϊ8,  
					// ����0~7,1bit��Ӧһ������.
}semphore;

extern void sem_down(semphore *sem);
extern void sem_up(semphore *sem, unsigned char n);
extern u8 sem_try_down(semphore *sem);

#endif //SEMPHORE
#endif /* SEM_H*/
