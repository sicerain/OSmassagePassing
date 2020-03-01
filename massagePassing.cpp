// massagePassing.cpp: 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include "semaphore.h"
#include "send_recv.h"
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <stack>
#include <process.h>

using namespace std;

extern void operating();

int main (){
	int x[THREAD_NUM] = { 0,1,2,3,4 };
	HANDLE thread_p[THREAD_NUM];
	cout << "massage buff init..." << endl;
	HANDLE thread_r[THREAD_NUM];
	for (int j = 0; j < THREAD_NUM;j++) {
		thread_r[j] = (HANDLE)_beginthreadex(NULL, 0, recvProcess, (LPVOID)&x[j], 0, NULL);
		Sleep(1000); 
	}
	for (int j = 0; j < THREAD_NUM;j++) {
		thread_p[j] = (HANDLE)_beginthreadex(NULL, 0, sendProcess,NULL, 0, NULL);
	}
	WaitForMultipleObjects(THREAD_NUM, thread_p, TRUE, INFINITE);
	WaitForMultipleObjects(THREAD_NUM, thread_r, TRUE, INFINITE);
	return 0;
}

//LINK2005错误
