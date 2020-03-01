#pragma once
#include <Windows.h>
#include "semaphore.h"

#define NUM_OF_MASSAGE 20
const int THREAD_NUM = 5;
unsigned int __stdcall sendProcess(LPVOID para);
unsigned int __stdcall recvProcess(LPVOID para);