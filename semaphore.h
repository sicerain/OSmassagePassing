#pragma once
#include <windows.h>
#include <process.h>
//#include "afxmt.h"

//�ź���ʵ��
class semaphore {
private:
	CONDITION_VARIABLE Condition_Var;  //��������
	SRWLOCK mutex_lock;  
	// SRW�� ʵ��ԭ���Բ��� �൱�ڻ�������� �����޷�wake bug
	CRITICAL_SECTION cs; //ʹ��EnterCriticalSection()����ʵ����Դ������
	int count;       //����ͬ����ģ�����

public:
	semaphore(int value = 1) { count = value; }
	int getCount();
	void wait();
	void signal();
};