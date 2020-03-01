#pragma once
#include <windows.h>
#include <process.h>
//#include "afxmt.h"

//信号量实现
class semaphore {
private:
	CONDITION_VARIABLE Condition_Var;  //条件变量
	SRWLOCK mutex_lock;  
	// SRW锁 实现原子性操作 相当于互斥锁身份 出现无法wake bug
	CRITICAL_SECTION cs; //使用EnterCriticalSection()函数实现资源的锁定
	int count;       //用来同步多模拟进程

public:
	semaphore(int value = 1) { count = value; }
	int getCount();
	void wait();
	void signal();
};