#pragma once
#include "stdafx.h"
#include "semaphore.h"
#include <windows.h>
#include <iostream>

using namespace std;

/*构造信号量实现多模拟进程的同步*/

int semaphore::getCount(){
	return count;
}

void semaphore::wait() {                //信号量的P操作

	AcquireSRWLockShared(&mutex_lock);  //获得SRW锁
	                                    //或者使用EnterCriticalSection(&cs);进入临界区

	/*对信号量值的更改为原子操作 应将以下代码视为临界区利用锁保护起来*/
	
	if (--count < 0) {                  //InterlockedDecrement((LPLONG)count)
		                               // cout << "sleep!" << endl;
										//cout << "the count is" << count << endl;
		                                //SleepConditionVariableCS(&Condition_Var, &cs, 0); 

		/*睡眠之前应释放锁，否则无法在singal中进入临界区将其唤醒*/

		SleepConditionVariableSRW(&Condition_Var, &mutex_lock, INFINITE, CONDITION_VARIABLE_LOCKMODE_SHARED);
		                                //cout << "i wake up!!" << endl;
		//缓冲区数据已取空睡眠该模拟进程
	}
	ReleaseSRWLockShared(&mutex_lock);  //LeaveCriticalSection(&cs); 
	//cout << "leave lock" << endl;
	                                   // cout << "the count is" << count << endl;
}

void semaphore::signal() {                   //信号量的V操作

	AcquireSRWLockShared(&mutex_lock);    //获得SRW锁 若使用AcquireSRWLockExclusive函数获得锁导致无法访问临界区
	                                         //EnterCriticalSection(&cs);
	if (++count <= 0) {                      //InterlockedIncrement((LPLONG)&count)
		                                     //cout << "wake up!" ;
		WakeConditionVariable(&Condition_Var);
		/*将睡眠的模拟进程唤醒*/
	}

	ReleaseSRWLockShared(&mutex_lock);    //LeaveCriticalSection(&cs);ReleaseSRWLockExclusive
	   
	                                          //cout << "the count is" << count << endl;
}

/*补充说明：
	条件变量参数问题
	AcquireSRWLockShared 与 AcquireSRWLockExclusive问题
*/