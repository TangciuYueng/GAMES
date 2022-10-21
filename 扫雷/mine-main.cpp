#include "mine.h"
int main()
{
	const int a = 500, b = 550;//初始界面窗口的大小
	bool initClose = false;//启动游戏前关闭初始界面，记录是否关闭
	initgraph(a, b, NOMINIMIZE);//打开初始界面
	while (1)
	{
		if (initClose)//启动了游戏关闭了原来的初始界面，循环后直接打开
		{
			initgraph(a, b, NOMINIMIZE);
			initClose = false;
		}
		int choice = titleScreen();//初始界面，返回值代表点击的按钮
		if (choice == 1)//选择开始游戏
		{
			while (1)
			{
				int selection = selectDfct();//选择难度界面，返回值代表点击不同难度按钮
				
				if (selection == 1)//默认初级难度
				{
					closegraph();//关掉了一开始界面
					initClose = true;
					myMine tempGame;
					tempGame.game();
				}
				else if (selection == 2)//中级难度
				{
					closegraph();//关掉了一开始界面
					initClose = true;
					myMine tempGame(16, 16, 40, 30);
					tempGame.game();
				}
				else if (selection == 3)//高级难度
				{
					closegraph();//关掉了一开始界面
					initClose = true;
					myMine tempGame(16, 40, 99, 25);
					tempGame.game();
				}
				else if (selection == 4)//自定义难度
				{
					int n = 0, m = 0, num = 0;//记录输入的长宽和雷数
					bool noInput = false;//记录是否没有输入
					while (1)
					{
						n = 0, m = 0, num = 0;
						char indexes[20] = "";
						int k = 0;
						InputBox(indexes, 20, "请输入高度、宽度、雷数(空格间隔)", "扫雷,范围[1,60],[1,60]", 0, 0, 0, 0);
						if (strlen(indexes) == 0)//没有输入
						{
							noInput = true;
							break;
						}
						for (int i = 0; i < 20; )//获得输入的数据
						{
							if (isdigit(indexes[i]))
							{
								while (isdigit(indexes[i]))
								{
									if (k == 0)
									{
										n = n * 10 + indexes[i] - '0';
									}
									else if (k == 1)
									{
										m = m * 10 + indexes[i] - '0';
									}
									else if (k == 2)
									{
										num = num * 10 + indexes[i] - '0';
									}
									++i;
								}
								++k;
							}
							else
								++i;
						}
						if (n >= 1 && m >= 1 && n <= 60 && m <= 60 && num < n * m)//保证输入的数据合理
							break;
					}
					if (noInput == false)//有输入了才能启动游戏
					{
						myMine tempGame(n, m, num, 25);
						tempGame.game();
					}
				}
				if (selection)//如果有选择就可以结束选择难度的姐买你
					break;
			}
			
		}
		else if (choice == 2)//进入排行榜界面
			board();
		else if (choice == 3)//退出程序
			break;
	}
	closegraph();
	return 0;;
}