#include "stdafx.h"
#include "produce_consumer.h"
#include <iostream>
using namespace std;

//生产者
unsigned int __stdcall Producer(LPVOID para) {
	int a = 12;
	while (true) {
		int item = rand();
		                          //cout << "empt ";
		empt.wait();
		                          //cout << "mutex ";
		                          //cout << "a";
		mutex.wait();
		                          //cout << "enter Athread";
		itemBag.push(item);
		cout << "producer produce item is " << item << endl;
		a++;
		                          //cout << "mutex ";
		mutex.signal();
		                          //cout << "full ";
		full.signal();
		                          //cout << "producer unlock\n\n" << endl ;
		if (a == 100) break;
	}
	return 1;
}

//消费者
unsigned int __stdcall Consumer(LPVOID para) {
	int a = 0;
	int item;
	while (true) {
		                           //Sleep(50);
		                           //cout << "full ";
		full.wait();
		                           //cout << "mutex ";
		                           //cout << "b";
		mutex.wait();
		                           //cout << "enter Bthread";
		item = itemBag.top();
		itemBag.pop();
		                           //cout << "mutex ";
		mutex.signal();
		                           //cout << "empt ";
		empt.signal();
		cout << "consumer get item  " << item << endl << endl << endl;
	}
	return 1;
}

void operating() {
	HANDLE thread1 = (HANDLE)_beginthreadex(NULL, 0, Producer, NULL, 0, NULL);
	HANDLE thread2 = (HANDLE)_beginthreadex(NULL, 0, Consumer, NULL, 0, NULL);
	WaitForSingleObject(thread1, INFINITE);
	WaitForSingleObject(thread2, INFINITE);
}