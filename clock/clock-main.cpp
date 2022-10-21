#define _CRT_SECURE_NO_WARNINGS
#include <easyx.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>
const int WIDTH = 640, HEIGHT = 480;
const double pi = 3.1415926;

//表盘
void dial()
{
	//灰蓝背景
	setbkcolor(0xe6cdb4);
	cleardevice();

	//黄色圆盘
	const int R = 170;//最大半径
	setlinestyle(PS_SOLID, 10);//线宽为十个像素
	setlinecolor(YELLOW);//黄线
	setfillcolor(WHITE);//白色填充
	fillcircle(WIDTH / 2, HEIGHT / 2, R);
	
	//扇形颜色
	int r = 150;
	setlinestyle(PS_SOLID, 2);//线宽为十个像素
	for (int n = 0; n < 10; ++n)
	{
		// 画橘子瓣的三次贝塞尔曲线
		POINT pts[13];				// 定义数组，起始点、控制点 1、控制点 2、终点（起点）、控制点 1、控制点 2、终点（起点）……
		double a = 2 * pi * n / 10;	// 橘子瓣弧度
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

		int c = HSLtoRGB(36.0f * n, 0.8f, 0.8f);				// 设置彩虹色
		setlinecolor(c);										// 设置画线颜色为彩虹色
		polybezier(pts, 13);									// 画三次贝塞尔曲线	

		setfillcolor(c);										// 设置填充色为彩虹色
		floodfill(int(r / 2 * cos(a)) + WIDTH / 2, int(r / 2 * sin(a)) + HEIGHT / 2, c);	// 填充橘子瓣
	}
	//表盘刻度
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	const double angle1 = 2 * pi / 12, angle2 = 2 * pi / 4;
	for (int i = 0; i < 12; ++i)
	{
		setfillcolor(BLACK);
		//点点
		r = 145;

		//三角函数弧度的
		solidcircle(int(r * cos(i * angle1)) + WIDTH / 2,
			-int(r * sin(i * angle1)) + HEIGHT / 2, 2);
		solidcircle(int(r * cos(i * angle2)) + WIDTH / 2,
			-int(r * sin(i * angle2)) + HEIGHT / 2, 4);
		
		
		//数字
		r = 125;
		char temp[5] = "";
		sprintf(temp, "%d", 12 - i);
		if (i % 3 == 0)
			settextstyle(48, 0, "Broadway");
		else
			settextstyle(24, 0, "Broadway");


		//居中
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
	//画边框
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

	//数字时间，在框框中间
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
	//所在弧度
	double a = pi / 2 - (2 * pi * h / 12 + 2 * pi * 1 / 12 * m / 60);	
	double b = pi / 2 - (2 * pi * m / 60 + 2 * pi * 1 / 60 * s / 60);	
	double c = pi / 2 - 2 * pi * s / 60;								
	int r;
	setlinecolor(BLACK);												
	// 设置线宽为九像素
	setlinestyle(PS_SOLID, 9);
	//画时针半径为50
	r = 50;
	line(WIDTH / 2, HEIGHT / 2, 
		int(r * cos(a)) + WIDTH / 2, int(-r * sin(a)) + HEIGHT / 2);					
	// 设置线宽为六像素
	setlinestyle(PS_SOLID, 6);
	// 画分针半径100
	r = 100;
	line(WIDTH / 2, HEIGHT / 2,
		int(r * cos(b)) + WIDTH / 2, int(-r * sin(b)) + HEIGHT / 2);					
	// 设置画线颜色为红色
	setlinecolor(RED);													
	setlinestyle(PS_SOLID, 3);			
	int r2 = 25;
	r = 130;
	line( WIDTH / 2 - int(r2 * cos(c)),  HEIGHT / 2 + int(r2 * sin(c)),
		int(r * cos(c)) + WIDTH / 2, -int(r * sin(c)) + HEIGHT / 2); // 画秒针
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