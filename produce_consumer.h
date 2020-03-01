#pragma once
#include <windows.h>
#include "semaphore.h"
#include <stack>
#define N 10

using namespace std;
SRWLOCK mutex_lock;    //SRW锁实现互斥
semaphore mutex = 1;   //信号量实现互斥
semaphore empt = N;
semaphore full = 0;
stack<int> itemBag;

unsigned int __stdcall Producer(LPVOID para);
unsigned int __stdcall Consumer(LPVOID para);

void operating();
