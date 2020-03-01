#include "stdafx.h"
#include "massagebuff.h"
#include "color.h"
#include <iostream>

using namespace std;

extern semaphore cout_mutex;

p_Mas MasBuff::Init(int num, int PID){  //��ʼ������Ϊnum����Ϣ���ζ���
	recvPID = PID;   //��ʼ��PID
	empty = num;     //��ʼ��empty�ź���

	int count = 0;
	p_Mas theader = new Mas();
	p_Mas f = theader;
	/*����n-1����Ϣ����*/
	while (count < num-1) {
		p_Mas p = new Mas();
		f->next = p;
		f = p;
		count++;
	}
	f->next = theader;
	header = theader;
	plast = theader;
	return theader;
}

p_Mas MasBuff::getNextEmptyMas(){
	p_Mas p = header;
	while (p->mas != 0) {
		p = p->next;
	}
	return p;
}


void MasBuff::pop(){
	if (header == plast && header->mas == 0) {
		return;
	}
	else{
		header->mas = 0;
		header->PID = 0;
		if (header != plast) {
			header = header->next;
		}
		return;
	}
}

void MasBuff::push(int mas, int pid){
	if (plast->next == header) {
		return;
	}
	else {
		if (plast->mas == 0) {
			plast->mas = mas;
			plast->PID = pid;
		}
		else {
			plast->next->mas = mas;
			plast->next->PID = pid;
			plast = plast->next;
		}
		return;
	}
}

void MasBuff::print(){
	p_Mas p = header;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | BACKGROUND_GREEN);
	cout << "RMASBUFF_ID : " << recvPID << endl;
	while (p != plast) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | BACKGROUND_RED);
		cout << "  ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | BACKGROUND_GREEN);
		cout << "SPID:" << p->PID << " MAS:" << p->mas;
		p = p->next;
	}
	if(p->mas == 0){
		cout << "no massage" << endl;
		initColor();
		return;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | BACKGROUND_RED);
	cout << "  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | BACKGROUND_GREEN);
	cout << "SPID:" << p->PID << " MAS:" << p->mas <<endl;
	initColor();
}
