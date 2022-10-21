#define _CRT_SECURE_NO_WARNINGS
#include <easyx.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>
const int WIDTH = 640, HEIGHT = 480;
const double pi = 3.1415926;

//����
void dial()
{
	//��������
	setbkcolor(0xe6cdb4);
	cleardevice();

	//��ɫԲ��
	const int R = 170;//���뾶
	setlinestyle(PS_SOLID, 10);//�߿�Ϊʮ������
	setlinecolor(YELLOW);//����
	setfillcolor(WHITE);//��ɫ���
	fillcircle(WIDTH / 2, HEIGHT / 2, R);
	
	//������ɫ
	int r = 150;
	setlinestyle(PS_SOLID, 2);//�߿�Ϊʮ������
	for (int n = 0; n < 10; ++n)
	{
		// �����Ӱ�����α���������
		POINT pts[13];				// �������飬��ʼ�㡢���Ƶ� 1�����Ƶ� 2���յ㣨��㣩�����Ƶ� 1�����Ƶ� 2���յ㣨��㣩����
		double a = 2 * pi * n / 10;	// ���Ӱ껡��
		pts[0].x = int(r / 8 * cos(a + 2 * pi / 22)) + WIDTH / 2;
		pts[0].y = int(r / 8 * sin(a + 2 * pi / 22)) + HEIGHT / 2;	pts[12] = pts[11] = pts[0];
		pts[1].x = int(r / 12 * cos(a + 2 * pi / 22)) + WIDTH / 2;	pts[2].x = int(r / 12 * cos(a - 2 * pi / 22)) + WIDTH / 2;
		pts[1].y = int(r / 12 * sin(a + 2 * pi / 22)) + HEIGHT / 2;	pts[2].y = int(r / 12 * sin(a - 2 * pi / 22)) + HEIGHT / 2;
		pts[3].x = int(r / 8 * cos(a - 2 * pi / 22)) + WIDTH / 2;
		pts[3].y = int(r / 8 * sin(a - 2 * pi / 22)) + HEIGHT / 2;	pts[4] = pts[3];
		pts[5].x = int(r * cos(a - 2 * pi / 22) + WIDTH / 2);
		pts[5].y = int(r * sin(a - 2 * pi / 22)) + HEIGHT / 2;		pts[6] = pts[5];
		pts[9].x = int(r * cos(a + 2 * pi / 22)) + WIDTH / 2;
		pts[9].y = int(r * sin(a + 2 * pi / 22)) + HEIGHT / 2;		pts[10] = pts[9];
		pts[7].x = int(r * 1.1 * cos(a - 2 * pi / 30)) + WIDTH / 2;	pts[8].x = int(r * 1.1 * cos(a + 2 * pi / 30)) + WIDTH / 2;
		pts[7].y = int(r * 1.1 * sin(a - 2 * pi / 30)) + HEIGHT / 2;	pts[8].y = int(r * 1.1 * sin(a + 2 * pi / 30)) + HEIGHT / 2;

		int c = HSLtoRGB(36.0f * n, 0.8f, 0.8f);				// ���òʺ�ɫ
		setlinecolor(c);										// ���û�����ɫΪ�ʺ�ɫ
		polybezier(pts, 13);									// �����α���������	

		setfillcolor(c);										// �������ɫΪ�ʺ�ɫ
		floodfill(int(r / 2 * cos(a)) + WIDTH / 2, int(r / 2 * sin(a)) + HEIGHT / 2, c);	// ������Ӱ�
	}
	//���̶̿�
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	const double angle1 = 2 * pi / 12, angle2 = 2 * pi / 4;
	for (int i = 0; i < 12; ++i)
	{
		setfillcolor(BLACK);
		//���
		r = 145;

		//���Ǻ������ȵ�
		solidcircle(int(r * cos(i * angle1)) + WIDTH / 2,
			-int(r * sin(i * angle1)) + HEIGHT / 2, 2);
		solidcircle(int(r * cos(i * angle2)) + WIDTH / 2,
			-int(r * sin(i * angle2)) + HEIGHT / 2, 4);
		
		
		//����
		r = 125;
		char temp[5] = "";
		sprintf(temp, "%d", 12 - i);
		if (i % 3 == 0)
			settextstyle(48, 0, "Broadway");
		else
			settextstyle(24, 0, "Broadway");


		//����
		int w, h;
		w = textwidth(temp);
		h = textheight(temp);
		outtextxy(int(r * cos(i * angle1 + pi / 2) - w / 2 ) + WIDTH / 2,
			-int(r * sin(i * angle1 + pi / 2) + h / 2 ) + HEIGHT / 2 ,
			temp);
		
	}
}
void digital(int h, int m, int s)
{
	setlinecolor(LIGHTGRAY);
	setfillcolor(WHITE);
	//���߿�
	int W = 50, H = 40, gap = 5;
	fillrectangle(WIDTH / 2 - W - W / 2 - gap, 
		HEIGHT / 2 + H, 
		WIDTH / 2 - W / 2 - gap, 
		HEIGHT / 2 + H + H);
	fillrectangle(WIDTH / 2  - W / 2,    
		HEIGHT / 2 + H, 
		WIDTH / 2 + W / 2 , 
		HEIGHT / 2 + H + H);
	fillrectangle(WIDTH / 2 + W / 2 + gap,     
		HEIGHT / 2 + H, 
		WIDTH / 2 + W + W / 2 + gap, 
		HEIGHT / 2 + H + H);

	//����ʱ�䣬�ڿ���м�
	settextstyle(30, 0, "Broadway");
	char temp[5];
	int width;
	sprintf(temp, "%d", h);
	width = textwidth(temp);
	outtextxy(WIDTH / 2 - W - W / 2 - gap + (W - width) / 2,
		HEIGHT / 2 + H + gap, temp);

	sprintf(temp, "%d", m);
	width = textwidth(temp);
	outtextxy(WIDTH / 2 - W / 2 + (W - width) / 2,
		HEIGHT / 2 + H + gap, temp);

	sprintf(temp, "%d", s);
	width = textwidth(temp);
	outtextxy(WIDTH / 2 + W / 2 + gap + (W - width) / 2,
		HEIGHT / 2 + H + gap, temp);


}
void needles(int h, int m, int s)
{
	//���ڻ���
	double a = pi / 2 - (2 * pi * h / 12 + 2 * pi * 1 / 12 * m / 60);	
	double b = pi / 2 - (2 * pi * m / 60 + 2 * pi * 1 / 60 * s / 60);	
	double c = pi / 2 - 2 * pi * s / 60;								
	int r;
	setlinecolor(BLACK);												
	// �����߿�Ϊ������
	setlinestyle(PS_SOLID, 9);
	//��ʱ��뾶Ϊ50
	r = 50;
	line(WIDTH / 2, HEIGHT / 2, 
		int(r * cos(a)) + WIDTH / 2, int(-r * sin(a)) + HEIGHT / 2);					
	// �����߿�Ϊ������
	setlinestyle(PS_SOLID, 6);
	// ������뾶100
	r = 100;
	line(WIDTH / 2, HEIGHT / 2,
		int(r * cos(b)) + WIDTH / 2, int(-r * sin(b)) + HEIGHT / 2);					
	// ���û�����ɫΪ��ɫ
	setlinecolor(RED);													
	setlinestyle(PS_SOLID, 3);			
	int r2 = 25;
	r = 130;
	line( WIDTH / 2 - int(r2 * cos(c)),  HEIGHT / 2 + int(r2 * sin(c)),
		int(r * cos(c)) + WIDTH / 2, -int(r * sin(c)) + HEIGHT / 2); // ������
}
int main() {
	initgraph(WIDTH, HEIGHT);
	BeginBatchDraw();
	SYSTEMTIME sys;
	while (1)
	{
		cleardevice();

		GetLocalTime(&sys);
		dial();
		digital(sys.wHour, sys.wMinute, sys.wSecond);
		needles(sys.wHour, sys.wMinute, sys.wSecond);
		FlushBatchDraw();
		Sleep(1000);
		
		if (_kbhit())
			break;
	}
	

	EndBatchDraw();
	closegraph();
	return 0;
}