#pragma once
#include <windows.h>
#include "semaphore.h"
#include <stack>
#define N 10

using namespace std;
SRWLOCK mutex_lock;    //SRW��ʵ�ֻ���
semaphore mutex = 1;   //�ź���ʵ�ֻ���
semaphore empt = N;
semaphore full = 0;
stack<int> itemBag;

unsigned int __stdcall Producer(LPVOID para);
unsigned int __stdcall Consumer(LPVOID para);

void operating();
