github: git@github.com:johnnyop/xos.git
git remote add origin git@github.com:johnnyop/xos.git
git push -u origin master
Existing Git Repo?
  cd existing_git_repo
  git remote add origin git@github.com:johnnyop/xos.git
  git push -u origin master
/************************************************************/
PS:ʱ��Ƭѭ���������
1.	�����뺯��, ���ﲻһ���Ǳ�����о���ĺ���������������(WARNING L15: MULTIPLE CALL TO SEGMENT), 
	����KEIL C51�Ժ����Ĳ�����������ջ, �����������������ȫ�ֱ���(!̫���������ָ��,�������ȫ�ֱ���),
	��Ӧ�ô����������, ���жϻ���reentrant�ؼ���(���Լ������ȫ�ֱ�����Ч)
	��������OVERLAY (* ! sfname)��ȫ������NOOVERLAY
2.	C15���(������������), ��ͬһ�ļ��ﲻ�ụ����õĵĺ���, ĳЩ�������ܻṲ�õ�ַ,
	 �ǾͲ�������������"ͬʱ"�����������,
	 ��Ϊ���һ������������������,ͻȻ�����������,ʧȥCPU, 
	 ��һ����������ʱҲ������������Ļ�,���õ�ַ�ı����ᱻ�������е�����ı�
	 ��ֵ, ����Ҫ��ֹ�����������,�������ź���,���ж�(disable_irq),��
3.	���ж�(�����ж����ȼ��Ǹ�)ʱ,Ҫ��is_kernel()ȷ���Ƿ��ں���������ʱ�����,
	�����, ���ڹ��ж��ڼ䲻�ܵ��û�����������,ʧȥCPU��API,����ϵͳ���ܱ���.

4.	���ݸ���.
	While this technique is mostly automatic, there are a few situations that require special attention.
		Indirect Function Calls (Function Pointers). 
		Tables or Arrays of Function Pointers. 
		Recursive Functions (functions that call themselves). 
		Reentrant Functions (functions invoked by more than one thread of execution �� for example, a function called by main and an interrupt service routine. 
	
/************************************************************/


/**/
