#pragma once
#include "semaphore.h"


typedef struct Mas {        //消息节点
	int mas = 0;        //消息信息
	int PID = 0;        //发送者的模拟进程号
	Mas* next;     //下一节点
}*p_Mas;

typedef struct MasBuff {         //链式缓冲区 在接收模拟进程中缓冲已发送但未被接收的消息
	p_Mas header;
	p_Mas plast;        //队尾元素
	int recvPID;         //该缓冲区所有者
	semaphore mutex = 1; //互斥访问信号量 （互斥量）
	semaphore full = 0;  //同步访问信号量
	semaphore empty;
	p_Mas Init(int num , int PID);  //获取并初始化该链式缓冲区 返回header
	p_Mas getNextEmptyMas();  //获取下一个空位
	void pop();        //取出队首数据不返回
	void push(int mas, int pid); //向队尾写入数据

	void print();        //打印缓冲区
}*p_MasBuff;

//struct MasBuffList {      //消息链缓冲区 
//
//};