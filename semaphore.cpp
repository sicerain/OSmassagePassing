#pragma once
#include "stdafx.h"
#include "semaphore.h"
#include <windows.h>
#include <iostream>

using namespace std;

/*�����ź���ʵ�ֶ�ģ����̵�ͬ��*/

int semaphore::getCount(){
	return count;
}

void semaphore::wait() {                //�ź�����P����

	AcquireSRWLockShared(&mutex_lock);  //���SRW��
	                                    //����ʹ��EnterCriticalSection(&cs);�����ٽ���

	/*���ź���ֵ�ĸ���Ϊԭ�Ӳ��� Ӧ�����´�����Ϊ�ٽ�����������������*/
	
	if (--count < 0) {                  //InterlockedDecrement((LPLONG)count)
		                               // cout << "sleep!" << endl;
										//cout << "the count is" << count << endl;
		                                //SleepConditionVariableCS(&Condition_Var, &cs, 0); 

		/*˯��֮ǰӦ�ͷ����������޷���singal�н����ٽ������份��*/

		SleepConditionVariableSRW(&Condition_Var, &mutex_lock, INFINITE, CONDITION_VARIABLE_LOCKMODE_SHARED);
		                                //cout << "i wake up!!" << endl;
		//������������ȡ��˯�߸�ģ�����
	}
	ReleaseSRWLockShared(&mutex_lock);  //LeaveCriticalSection(&cs); 
	//cout << "leave lock" << endl;
	                                   // cout << "the count is" << count << endl;
}

void semaphore::signal() {                   //�ź�����V����

	AcquireSRWLockShared(&mutex_lock);    //���SRW�� ��ʹ��AcquireSRWLockExclusive��������������޷������ٽ���
	                                         //EnterCriticalSection(&cs);
	if (++count <= 0) {                      //InterlockedIncrement((LPLONG)&count)
		                                     //cout << "wake up!" ;
		WakeConditionVariable(&Condition_Var);
		/*��˯�ߵ�ģ����̻���*/
	}

	ReleaseSRWLockShared(&mutex_lock);    //LeaveCriticalSection(&cs);ReleaseSRWLockExclusive
	   
	                                          //cout << "the count is" << count << endl;
}

/*����˵����
	����������������
	AcquireSRWLockShared �� AcquireSRWLockExclusive����
*/