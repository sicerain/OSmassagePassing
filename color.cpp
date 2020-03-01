

/*
颜色函数SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),前景色 | 背景色 | 前景加强 | 背景加强);
	前景色：数字0-15 或 FOREGROUND_XXX 表示	（其中XXX可用BLUE、RED、GREEN表示）
	前景加强：数字8 或 FOREGROUND_INTENSITY 表示
	背景色：数字16 32 64 或 BACKGROUND_XXX 三种颜色表示
	背景加强： 数字128 或 BACKGROUND_INTENSITY 表示
主要应用：改变指定区域字体与背景的颜色
前景颜色对应值：
　　0=黑色                8=灰色　　
  　1=蓝色                9=淡蓝色        十六进制        　　
　　2=绿色                10=淡绿色       0xa        　　
　　3=湖蓝色              11=淡浅绿色     0xb　
　　4=红色                12=淡红色       0xc　　
　　5=紫色                13=淡紫色       0xd        　　
　　6=黄色                14=淡黄色       0xe        　　
　　7=白色                15=亮白色       0xf
　　也可以把这些值设置成常量。
*/
#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>

void color(short x)	//自定义函根据参数改变颜色 
{
	if (x >= 0 && x <= 15)//参数在0-15的范围颜色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	//只有一个参数，改变字体颜色 
	else//默认的颜色白色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void initColor() { //初始化背景
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}