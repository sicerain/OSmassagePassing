#include "stdafx.h"
#include "send_recv.h"
#include "massagebuff.h"
#include "color.h"
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <list>

using namespace std;

list<MasBuff*> cache;   //��Ϣ��������
MasBuff recvMasBuff[THREAD_NUM];
semaphore cout_mutex = 1;

unsigned int __stdcall sendProcess(LPVOID para) {
	int num = NUM_OF_MASSAGE;   //����ʮ����Ϣ
	while (num != 0) {
		list<MasBuff*>::iterator iter;
		MasBuff* p_recvMasBuff;   //���ս�����Ϣ������
		int i = 0;
		int getid = rand() % THREAD_NUM;
		for (iter = cache.begin(); iter != cache.end();iter++) {
			if (i == getid) {
				break;
			}
			i++;
		}
		(*iter)->empty.wait();
		(*iter)->mutex.wait();
		int mas = rand();
		int id = GetCurrentThreadId();
		(*iter)->push(mas, id);
		cout_mutex.wait();
		cout << "SPID " << id << " send massage: " << mas << " to RPID " << (*iter)->recvPID << endl;
		(*iter)->print();
		Sleep(100);
		cout_mutex.signal();
		(*iter)->mutex.signal();
		(*iter)->full.signal();
		num--;
	}
	return 0;
}

unsigned int __stdcall recvProcess(LPVOID para) {

    //���ս�����Ϣ������
	int a = *(int*)para;
	recvMasBuff[a].Init(NUM_OF_MASSAGE, GetCurrentThreadId()); //*(int*)para
	cout << "RPID " << recvMasBuff[a].recvPID << " massagebuff is ready!" << endl;
	cache.push_back(&recvMasBuff[a]);
	while (true) {
		recvMasBuff[a].full.wait();
		recvMasBuff[a].mutex.wait();
		int mas = recvMasBuff[a].header->mas;
		int PID = recvMasBuff[a].header->PID;
		recvMasBuff[a].pop();
		cout_mutex.wait();
		cout << "RPID " << recvMasBuff[a].recvPID << " recv process recv massage: " << mas << " from SPID " << PID << endl;
		recvMasBuff[a].print();
		Sleep(100);
		cout_mutex.signal();
		recvMasBuff[a].mutex.signal();
		recvMasBuff[a].empty.signal();
	}
	return 0;
}

