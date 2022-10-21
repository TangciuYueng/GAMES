#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <graphics.h>
#include <easyx.h>
#include <time.h>
#include <iostream>
#include <string.h>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <vector>
using namespace std;
#define STOP_TIME 200
class myMine {
public:
	void game();
	//构造函数，可以自定义扫雷界面的长宽和雷数
	myMine(int N, int M, int MINE, int Size = 50);
	myMine();
protected:
	//踩雷之后
	void afterMine();
	//递归打开一系列可以打开的
	void open(int r, int c);
	//判断标记都标记在雷上了
	bool check();
	//初始化底层数据
	void initMap();
	//画整个棋盘
	void drawMap();
	//鼠标操作
	void mouseInput();
	void showMap();
	//输入用户名分数文件
	void intputMsg(char name[], int Time);
private:
	int N = 10, M = 10, MINE = 10;
	int Size = 50;
	const int w = 150, h = 45, shadow = 4;
	const int firstLine = 50;
	vector<vector<int>> map;
	int flag = 0, tag = 0;
	bool gameBegin = false, fail = false, 
		startTime = false, clickMusic = false;
	IMAGE img[12];
	//记录时间的变量
	SYSTEMTIME begTime, endTime;
};
class button {
public:
	button(int X, int Y, char _text[]);
	button(int X, int Y, char _text[], int w, int h);
	
	void drawButton();
	
	void onButton();
	
	void clickButton();
	
	
private:
	int X, Y;
	char text[20];
	int w = 150, h = 45, shadow = 4;
};
struct node {
	string name;
	int Time;
};
bool cmp(node& a, node& b);
//难度选择界面
int selectDfct();
//排行榜的界面
void board();
//一开始的界面
int titleScreen();