/**
 * \file sem.c
 * \brief �ź���
 * Ϊ�������ͬ���ṩ����
 * */
#include "sem.h"
#ifdef SEMPHORE
/**
 * number of semphore the task wait for.<br>
 * �������ڵȴ����ź����ĸ�,
 * ������ȴ����ź���Ϊ0ʱ�ſ��ܻ��� 
 * */
u8_t data sem_count[NR_TASK];
/**
 * \fn void sem_down(semphore *sem)
 * \brief down \a sem
 * ��ȡ\a sem�ź���, �ź�����Ϊ0��,�ź�����1,��������.<br>
 * ����, sem_count[current]+1,
 * \param sem Ҫ��ȡ���ź���
 * \sa sem_try_down
 */
void sem_down(semphore *sem)
{
	disable_irq();
	if (sem->count == 0) {
		++sem_count[current];
		task_status[current] |= TASK_SEM_WAIT;
		/* �õȴ�����ź����������λ */
		sem->wait_task |= (1 << current);
		enable_irq();
		schedule();
	} else {
		sem->count--;
		enable_irq();
	}
}


/**
 * \brief ���Ի�ȡ�ź���, ����������
 * \param sem Ҫ��ȡ���ź���
 * \return ���ź���Ϊ0,�򷵻�Ϊ-1,��������. ���򷵻�0,���ź�����1
 * \sa sem_down
 */
u8_t sem_try_down(semphore *sem)
{
	u8_t ret = -1;
	disable_irq();
	if (sem->count == 0)
		goto sem_quit;
	sem->count--;
	ret = 0;
sem_quit:
	enable_irq();
	return ret;
}
/**
 * \brief �����ź���\a sem��ֵ\a n
 * �����ӵ�ͬʱ,�������ڵ�����ź���������,sem_count��1,���ź����ĵȴ�λ
 * \param sem Ҫ��ȡ���ź���
 * \param n ���ӵ���ֵ 
 * \sa sem_count, semphore, task_status, TASK_SEM_WAIT
 */
void sem_up(semphore *sem, u8_t n)
{
	u8_t id, s_id;
	if (n == 0)
		return;
	disable_irq();
	sem->count += n;
	if (sem->count < n)
		sem->count = -1;
	if (sem->wait_task != 0) {
		/**
		 * TL0 & 0X7, Ϊ�˲���ÿ��up���Ǵ�0��ʼ,������TL0�����һ�������,��������������
		 * */
		id = (TLN) & 7;
		s_id = id;
		do {
			n = (1 << id);
			if (sem->wait_task & n) {
				sem->wait_task &= ~n;
				sem->count--;
				--sem_count[id];
				if (sem_count[id] == 0) {
					task_status[id] &= (~TASK_SEM_WAIT);
				}
				if (sem->count == 0)
					break;
			}
			id++;
			if (id >= MAX_TASK)
				id = 0;
		} while ((s_id != id) && (sem->wait_task != 0));
	}
	enable_irq();
}

#endif //SEMPHORE
