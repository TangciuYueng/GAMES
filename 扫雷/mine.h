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
	//���캯���������Զ���ɨ�׽���ĳ��������
	myMine(int N, int M, int MINE, int Size = 50);
	myMine();
protected:
	//����֮��
	void afterMine();
	//�ݹ��һϵ�п��Դ򿪵�
	void open(int r, int c);
	//�жϱ�Ƕ������������
	bool check();
	//��ʼ���ײ�����
	void initMap();
	//����������
	void drawMap();
	//������
	void mouseInput();
	void showMap();
	//�����û��������ļ�
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
	//��¼ʱ��ı���
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
//�Ѷ�ѡ�����
int selectDfct();
//���а�Ľ���
void board();
//һ��ʼ�Ľ���
int titleScreen();