#pragma once
#include "semaphore.h"


typedef struct Mas {        //��Ϣ�ڵ�
	int mas = 0;        //��Ϣ��Ϣ
	int PID = 0;        //�����ߵ�ģ����̺�
	Mas* next;     //��һ�ڵ�
}*p_Mas;

typedef struct MasBuff {         //��ʽ������ �ڽ���ģ������л����ѷ��͵�δ�����յ���Ϣ
	p_Mas header;
	p_Mas plast;        //��βԪ��
	int recvPID;         //�û�����������
	semaphore mutex = 1; //��������ź��� ����������
	semaphore full = 0;  //ͬ�������ź���
	semaphore empty;
	p_Mas Init(int num , int PID);  //��ȡ����ʼ������ʽ������ ����header
	p_Mas getNextEmptyMas();  //��ȡ��һ����λ
	void pop();        //ȡ���������ݲ�����
	void push(int mas, int pid); //���βд������

	void print();        //��ӡ������
}*p_MasBuff;

//struct MasBuffList {      //��Ϣ�������� 
//
//};