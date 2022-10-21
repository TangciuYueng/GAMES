#include <iostream>
#include <Windows.h>
#include "color_ball.h"
#include "cmd_console_tools.h"
bool CMP(node& a, node& b)
{
	return a.SCORE > b.SCORE;
}
void button::print(int x, int y, string& myText)
{
	text = myText;
	cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
	cct_gotoxy(x, y);
	int mid = h / 2 + 1, m = (w - text.length()) / 2;
	for (int i = 1; i <= h; ++i)
	{
		if (i == mid)
		{
			for (int i = 0; i < m; ++i)
				cout << ' ';
			cout << text;
			for (int i = 0; i < m; ++i)
				cout << ' ';
		}
		else
			for (int i = 0; i < w; ++i)
				cout << ' ';
		cct_gotoxy(x, y + i);
	}
	cct_setcolor();
}
color_ball::color_ball() :color_num(6)
{
	score = 0;
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < N; ++j)
		{
			board[i][j] = -1;
			cp[i][j] = false;
		}	
	ball_num = 0;
	music_is_playing = false;
	game_exit = false;
}
void color_ball::init()
{
	score = 0;
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < N; ++j)
		{
			board[i][j] = -1;
			cp[i][j] = false;
		}
	ball_num = 0;
	music_is_playing = false;
	game_exit = false;

	srand((unsigned)time(NULL));
	//初始七个球
	const int init_num = 7;
	ball_num += 7;
	int i = 0;
	while (i < init_num)
	{
		//随机位置0 - (M - 1)，颜色0-5六种颜色
		int x = rand() % M;
		int y = rand() % N;
		int val = rand() % color_num;
		if (cp[x][y] == false)
		{
			++i;
			board[x][y] = val;
			cp[x][y] = true;
		}
	}
}
void color_ball::show()
{
	//在最开始显示
	cct_gotoxy(0, 0);
	cout << ' ';
	for (int i = 0; i < M; ++i)
		cout << "   " << 1 + i;
	cout << endl;
	for (int i = 0; i < M; ++i)
	{
		
		cct_setcolor();
		cout << i + 1 << ' ';
		for (int j = 0; j < N; ++j)
		{
			cct_setcolor();
			cout << ' ';
			if (board[i][j] == -1)
				cct_setcolor(COLOR_HWHITE);
			else
				cct_setcolor(board[i][j] + 1);
			cout << ' ' << ' ' << ' ';
		}
		cout << endl;
		cct_setcolor();
		cout << ' ' << ' ';
		for (int j = 0; j < N; ++j)
		{
			cct_setcolor();
			cout << ' ';
			if (board[i][j] == -1)
				cct_setcolor(COLOR_HWHITE);
			else
				cct_setcolor(board[i][j] + 1);
			cout << ' ' << ' ' << ' ';
		}
		cout << endl << endl;
	}
	cct_setcolor();
}
void color_ball::input_move()
{
	int x1, y1, x2, y2, x, y;
	while (1)
	{
		cout << "请输入坐标[1,9]，第一位代表行，第二位代表列";
		cct_getxy(x, y);
		cct_showch(x, y, ' ', 0, 7, 10);
		cct_gotoxy(x, y);
		cin >> x1 >> y1 >> x2 >> y2;
		--x1;
		--x2;
		--y1;
		--y2;
		if ((x1 >= 0 && y1 >= 0 && x2 >= 0 && y2 >= 0 &&
			x1 < M && y1 < N && x2 < M && y2 < N) && can_move(x1, y1, x2, y2))
		{
			//can_move函数改变cp数组，使用完恢复
			update_cp();
			break;
		}
		else
		{
			//can_move函数改变cp数组，使用完恢复
			update_cp();
			cout << "输入错误，请重新输入" << endl;
		}
		cin.clear();
		cin.ignore(65535, '\n');
	}
	//find_path(x1, y1, x2, y2);
	update_cp();
	move(x1, y1, x2, y2);
}
void color_ball::show_cp()
{
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
			cout << cp[i][j] << ' ';
		cout << endl;
	}
}
bool color_ball::can_move(const int x1, const int y1, const int x2, const int y2)
{
	//该点没有球或目标点有球或同一个点
	if (cp[x1][y1] == false || cp[x2][y2] || (x1 == x2 && y1 == y2))
		return false;
	return dfs(x1, y1, x2, y2, x1 - 1, y1) || dfs(x1, y1, x2, y2, x1 + 1, y1)
		|| dfs(x1, y1, x2, y2, x1, y1 - 1) || dfs(x1, y1, x2, y2, x1, y1 + 1);
	//执行完成恢复cp数组
}
void color_ball::move(const int x1, const int y1, const int x2, const int y2)
{
	board[x2][y2] = board[x1][y1];
	cp[x2][y2] = true;
	board[x1][y1] = -1;
	cp[x1][y1] = false;
}
bool color_ball::dfs(const int x1, const int y1, const int x2, const int y2, const int i, const int j)
{
	if (i < 0 || i >= M || j < 0 || j >= N)
		return false;
	if (cp[i][j])
		return false;
	if (i == x2 && j == y2)
		return true;
	//标记已经遍历过
	cp[i][j] = true;
	return dfs(x1, y1, x2, y2, i + 1,j) || dfs(x1, y1, x2, y2,i - 1,j) ||
		dfs(x1, y1, x2, y2, i, j + 1) || dfs(x1, y1, x2, y2, i, j - 1);
}
void color_ball::update_cp()
{
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < N; ++j)
		{
			if (board[i][j] != -1)
				cp[i][j] = true;
			else
				cp[i][j] = false;
		}			
}
void color_ball::new_color(int val[])
{
	for (int i = 0; i < 3; ++i)
		val[i] = rand() % color_num;
}
void color_ball::new_location(int val[],int num)
{
	int i = 0;
	//剩下的位置少于三个
	while (M * N - ball_num < num)
		--num;
	while (i < num)
	{
		int x = rand() % M;
		int y = rand() % N;
		//上面没有球
		if (!cp[x][y])
		{
			board[x][y] = val[i];
			//新增球的图形函数
			output_cube(x, y, 0);
			cp[x][y] = true;
			++i;
		}
	}
	ball_num += num;
}
void color_ball::show_next_three_ball(int val[])
{
	const int yd = 4, D = 5;
	cct_gotoxy(N * yd + 2 + D, 0);
	cout << "将出现的颜色";
	cct_gotoxy(N * yd + 2 + D + 1, 1);
	for (int i = 0; i < 3; ++i)
	{
		cct_setcolor(val[i] + 1);
		cout << ' ';
		cct_setcolor();
		cout << "   ";
	}

}
bool color_ball::check()
{
	bool is = false;
	for(int i = 0; i < M; ++i)
		for(int j = 0; j < N; ++j)
			if (cp[i][j])
			{
				if (check_five_remove(i, j))
					is = true;
			}
	return is;
}
bool color_ball::check_five_remove(int x0, int y0)
{
	//从某个有球的位置开始
	bool five = false;
	//储存左右、上下、右上斜、左上斜四个方向的结果
	int ans[4]= { 0 };
	int total = 1, color = board[x0][y0], i, j, cnt = 0;
	const int NUM = 5;
	//满足不出界、同样颜色才能记录total
	//上下
	for (i = 1; x0 - i >= 0 && board[x0 - i][y0] == color; ++i)
		++total;
	for (j = 1; x0 + j <= M && board[x0 + j][y0] == color; ++j)
		++total;
	//如果超过五个就记录
	if (total >= NUM)
	{
		++cnt;
		ans[0] = total;
		five = true;
	}	
	//左右
	total = 1;
	for (int i = 1; y0 - i >= 0 && board[x0][y0 - i] == color; ++i)
		++total;
	for (int j = 1; y0 + j < N && board[x0][y0 + j] == color; ++j)
		++total;
	//如果超过五个就记录
	if (total >= NUM)
	{
		++cnt;
		ans[1] = total;
		five = true;
	}
	//右上斜
	total = 1;
	for (i = 1; x0 - i >= 0 && y0 + i < N && board[x0 - i][y0 + i] == color; ++i)
		++total;
	for (j = 1; x0 + j < M && y0 - j >= 0 && board[x0 + j][y0 - j] == color; ++j)
		++total;
	//如果超过五个就记录
	if (total >= NUM)
	{
		++cnt;
		ans[2] = total;
		five = true;
	}
	//左上斜
	total = 1;
	for (i = 1; x0 - i >= 0 && y0 - i >= 0 && board[x0 - i][y0 - i] == color; ++i)
		++total;
	for (j = 1; x0 + j < M && y0 + j < N && board[x0 + j][y0 + j] == color; ++j)
		++total;
	//如果超过五个就记录
	if (total >= NUM)
	{
		++cnt;
		ans[3] = total;
		five = true;
	}
	//开始消去球
	if (five)//有超过五个的
	{
		//先消去x0,y0
		board[x0][y0] = -1;
		cp[x0][y0] = false;
		output_cube(x0, y0, 0);
		ball_num -= 1;
		score += 2;
		//再消去旁边的
		//i从0 到 3，上下，左右，右上斜，左上斜
		for (int i = 0; i < 4; ++i)
		{
			if (ans[i] != 0)
			{
				if (i == 0)
				{
					clear_ball(x0 - 1, y0, color, i);
					clear_ball(x0 + 1, y0, color, i);
				}
				else if (i == 1)
				{
					clear_ball(x0, y0 + 1, color, i);
					clear_ball(x0, y0 - 1, color, i);
				}
				else if (i == 2)
				{
					clear_ball(x0 - 1, y0 + 1, color, i);
					clear_ball(x0 + 1, y0 - 1, color, i);
				}
				else
				{
					clear_ball(x0 + 1, y0 + 1, color, i);
					clear_ball(x0 - 1, y0 - 1, color, i);
				}
				score += 2 * (ans[i] - 1);
				ball_num -= ans[i] - 1;
			}
		}
	}
	return five;
}
void color_ball::clear_ball(const int x, const int y, const int val, int select)
{
	//出界
	if (x < 0 || y < 0 || x >= M || y >= N)
		return;
	//别的颜色
	if (board[x][y] != val)
		return;
	//没有球
	if (cp[x][y] == false)
		return;
	//清除
	cp[x][y] = false;
	board[x][y] = -1;
	//同时恢复背景颜色
	output_cube(x, y, 0);
	if (select == 0)
	{
		clear_ball(x - 1, y, val, select);
		clear_ball(x + 1, y, val, select);
	}
	else if (select == 1)
	{
		clear_ball(x, y - 1, val, select);
		clear_ball(x, y + 1, val, select);
	}
	else if (select == 2)
	{
		clear_ball(x + 1, y - 1, val, select);
		clear_ball(x - 1, y + 1, val, select);
	}
	else
	{
		clear_ball(x - 1, y - 1, val, select);
		clear_ball(x + 1, y + 1, val, select);
	}
}
bool color_ball::is_over()
{
	return M * N == ball_num;
}
void color_ball::mouse_input()
{
	int mx, my, m_action, k1, k2, ret;
	int x1 = -1, x2 = -1, y1 = -1, y2 = -1;
	const int xd = 3, yd = 4, fX = 40, fY = 4, mX = 40, mY = 8;
	const int h = 3, w = 16;
	bool flag = false, have_ball = false;
	cct_enable_mouse();
	cct_setcursor(CURSOR_INVISIBLE);	//关闭光标
	while (1)
	{
		//第一次点击
		while (1)
		{
			ret = cct_read_keyboard_and_mouse(my, mx, m_action, k1, k2);
			//是鼠标操作
			if (ret == CCT_MOUSE_EVENT)
			{
				//出界 或 格子的边界
				if ((my > 2 + yd * N || mx > xd * M) || (mx % xd == 0 || my <= 2 || (my - 2) % yd == 0))
				{
					cct_gotoxy(0, xd * M + 1);
					cout << "起始：当前鼠标坐标非法           ";
					cct_showch(0, xd * M + 2, ' ', 0, 7, 25);
					//音乐按钮
					if (mx >= mY && mx <= mY + h && my >= mX && my <= mX + w)
					{
						cct_gotoxy(0, xd * M + 1);
						cout << "音乐按钮                       ";
						//暂停or播放音乐
						if (m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							if (music_is_playing)
							{
								music(0);
							}
							else
							{
								music(1);
							}
							//重新选择起始位置
							continue;
						}
						int x_tmp, y_tmp;
						ret = cct_read_keyboard_and_mouse(y_tmp, x_tmp, m_action, k1, k2);
						if (x_tmp >= mY && x_tmp <= mY + h && y_tmp >= mX && y_tmp <= mX + w && m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							if (music_is_playing)
							{
								music(0);
							}
							else
							{
								music(1);
							}
							//重新选择起始位置
							continue;
						}
				}
					//结束按钮
					else if (mx >= fY && mx <= fY + h && my >= fX && my <= fX + w)
					{
						cct_gotoxy(0, xd * M + 1);
						cout << "结束本轮按钮                  ";
						if (m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							//结束函数
							music(0);
							game_exit = true;
							return;
						}
						int x_tmp, y_tmp;
						ret = cct_read_keyboard_and_mouse(y_tmp, x_tmp, m_action, k1, k2);
						if (x_tmp >= fY && x_tmp <= fY + h && y_tmp >= fX && y_tmp <= fX + w && m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							//结束函数
							music(0);
							game_exit = true;
							return;
						}
					}
					continue;
				}

				x1 = mx / xd;
				y1 = (my - 2) / yd;
				cct_gotoxy(0, xd * M + 1);
				cout << "起始：当前鼠标坐标[" << x1 + 1 << ',' << y1 + 1 << ']';
				cct_showch(0, xd * M + 2, ' ', 0, 7, 25);
				//在格子内
				if (x1 >= 0 && y1 >= 0 && x1 < M && y1 < N)
				{
					//没有球，不可以点击
					if (cp[x1][y1] == false)
					{
						continue;
					}
						
					//有球，可以点击
					else
					{
						if (m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							//选中函数
							click_on(x1, y1);
							cct_gotoxy(0, xd * M + 1);
							cout << "起始：已选择[" << x1 + 1 << ',' << y1 + 1 << ']' << "       ";
							break;
						}
						int x_tmp, y_tmp;
						ret = cct_read_keyboard_and_mouse(y_tmp,x_tmp, m_action, k1, k2);
						//如果没出格子，是点击
						if (x1 == x_tmp / xd && y1 == (y_tmp - 2) / yd && m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							//选中函数
							click_on(x1, y1);
							cct_gotoxy(0, xd * M + 1);
							cout << "起始：已选择[" << x1 + 1 << ',' << y1 + 1 << ']' << "       ";
							break;
						}
						//重复第一个选择
						else
							continue;
					}
				}
				
			}
			//键盘操作
			else
			{
				//空格，暂停or播放音乐
				if (k1 == 32)
				{
					if (music_is_playing)
					{
						music(0);
					}
					else
					{
						music(1);
					}
					//重新选择起始位置
					continue;
				}
				//按键q
				else if (k1 == 'q' || k1 == 'Q')
				{
					//结束函数
					music(0);
					game_exit = true;
					return;
				}
			}
		}
		//第二次点击
		while (1)
		{
			ret = cct_read_keyboard_and_mouse(my, mx, m_action, k1, k2);
			if (ret == CCT_MOUSE_EVENT)
			{
				//出界 或 格子的边界 若是点击就重复第一个选择
				if ((my > 2 + yd * N || mx > xd * M) || (mx % xd == 0 || my <= 2 || (my - 2) % yd == 0))
				{
					cct_gotoxy(0, xd * M + 2);
					cout << "目标：当前鼠标坐标非法           ";
					//音乐按钮
					if (mx >= mY && mx <= mY + h && my >= mX && my <= mX + w)
					{
						cct_gotoxy(0, xd * M + 1);
						cout << "音乐按钮                       ";
						//暂停or播放音乐
						if (m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							if (music_is_playing)
							{
								music(0);
							}
							else
							{
								music(1);
							}
							//重新选择起始位置
							continue;
						}
						int x_tmp, y_tmp;
						ret = cct_read_keyboard_and_mouse(y_tmp, x_tmp, m_action, k1, k2);
						if (x_tmp >= mY && x_tmp <= mY + h && y_tmp >= mX && y_tmp <= mX + w && m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							if (music_is_playing)
							{
								music(0);
							}
							else
							{
								music(1);
							}
							//重新选择起始位置
							continue;
						}
					}
					//结束按钮
					else if (mx >= fY && mx <= fY + h && my >= fX && my <= fX + w)
					{
						cct_gotoxy(0, xd * M + 1);
						cout << "结束本轮按钮                  ";
						if (m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							//结束函数
							music(0);
							game_exit = true;
							return;
						}
						int x_tmp, y_tmp;
						ret = cct_read_keyboard_and_mouse(y_tmp, x_tmp, m_action, k1, k2);
						if (x_tmp >= fY && x_tmp <= fY + h && y_tmp >= fX && y_tmp <= fX + w && m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							//结束函数
							music(0);
							game_exit = true;
							return;
						}
					}
					else if (m_action == MOUSE_LEFT_BUTTON_CLICK)
						break;
					continue;
				}

				x2 = mx / xd;
				y2 = (my - 2) / yd;
				cct_gotoxy(0, xd * M + 2);
				cout << "目标：当前鼠标坐标[" << x2 + 1 << ',' << y2 + 1 << ']';
				//在格子内
				if (x2 >= 0 && y2 >= 0 && x2 < M && y2 < N)
				{
					//有球，可以点击,点了重新选择
					if (cp[x2][y2] == true)
					{
						if (m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							cct_gotoxy(0, xd* M + 2);
							cout << "目标：这里有球，不能移动        ";
							have_ball = true;
							Sleep(500);
							break;
						}
							
						else
							continue;
					}
					//没有球，可以点击
					else
					{
						if (m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							flag = true;
							break;
						}
						int x_tmp, y_tmp;
						ret = cct_read_keyboard_and_mouse(y_tmp, x_tmp, m_action, k1, k2);
						//如果没出格子，是点击
						if (x2 == x_tmp / xd && y2 == (y_tmp - 2) / yd && m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							flag = true;
							break;
						}
						//重复第一个选择
						else
							continue;
					}
				}
			}
			//键盘操作
			else
			{
				//空格，暂停or播放音乐
				if (k1 == 32)
				{
					if (music_is_playing)
					{
						music(0);
					}
					else
					{
						music(1);
					}
					//重新选择起始位置
					continue;
				}
				//按键q
				else if (k1 == 'q' || k1 == 'Q')
				{
					//结束函数
					music(0);
					game_exit = true;
					return;
				}
			}
		}
		//第二次选择也完成啦
		int res_path = find_path(x1, y1, x2, y2);
		if (res_path == 0 && have_ball == false)
		{
			cct_gotoxy(0, xd* M + 2);
			cout << "目标：这里有阻挡，不能移动         ";
			Sleep(500);
		}
		if (flag && res_path)
			break;
	}
	cct_disable_mouse();	//禁用鼠标
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	show_path(x1, y1, x2, y2);
	move(x1, y1, x2, y2);
}
void color_ball::output_cube(const int x, const int y, bool h)
{
	const int xd = 3, yd = 4, NUM = 3;
	int X = xd * x + 1;
	int Y = yd * y + 3;
	int color;
	if (board[x][y] == -1)
		color = 15;//亮白
	else
		color = board[x][y] + 1;
	if (h)
		cct_setcolor(color + 8);
	else
		cct_setcolor(color);
	cct_gotoxy(Y, X);
	for (int i = 0; i < xd - 1; ++i)
	{
		for (int j = 0; j < yd - 1; ++j)
		{
			cout << ' ';
		}
		cct_gotoxy(Y , X + 1 + i);
	}
	cct_setcolor();
}
void color_ball::click_on(const int x, const int y)
{
	const int xd = 3, yd = 4, NUM = 4;
	int X = xd * x - xd + 1;
	int Y = yd * y + 1;
	bool h = true;
	for (int i = 0; i < NUM; ++i)
	{
		output_cube(x, y, h);
		if (h)
			h = false;
		else
			h = true;
		Sleep(100);
	}

}
void color_ball::score_output(bool is_over)
{
	const int xd = 3;
	cct_gotoxy(0, M * xd + 3);
	if (is_over)
		cout << "您的最终得分为：" << score << "!! EXCELLENT! AMAZING! WONDERFUL!";
	else
		cout << "目前得分为：" << score <<"                                         ";
	cct_gotoxy(0, M * xd + 4);
	cout << "输入q结束游戏                                                          ";
}
void color_ball::music(bool play)
{
	if (play)
	{
		PlaySound(LPCWSTR(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);
		music_is_playing = true;
	}
	else
	{
		PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
		music_is_playing = false;
	}
}
void color_ball::show_path(const int x1, const int y1, const int x2, const int y2)
{
	vector<pair<int, int>> path;
	int x = x2, y = y2;
	path.emplace_back(make_pair(x2, y2));
	while (!(x == x1 && y == y1))
	{
		path.emplace_back(make_pair(path_x[x][y], path_y[x][y]));
		int temp_x = x, temp_y = y;

		x = path_x[temp_x][temp_y];
		y = path_y[temp_x][temp_y];
	}
	path.pop_back();
	reverse(path.begin(), path.end());
	x = x1, y = y1;
 	for (int i = 0; i < path.size(); ++i)
	{
		show_move_once(x, y, path[i].first, path[i].second, board[x1][y1] + 1);
		x = path[i].first;
		y = path[i].second;
	}
}
void color_ball::show_move_once(const int from_x, const int from_y, const int to_x, const int to_y, int color)
{
	cct_setcursor(CURSOR_INVISIBLE);
	//0，1 ，2，3代表上下左右
	int dir;
	if (from_x > to_x)
		dir = 0;
	else if (from_x < to_x)
		dir = 1;
	else if (from_y > to_y)
		dir = 2;
	else
		dir = 3;
	const int time = 10, xd = 3, yd = 4;
	const int X = xd * from_x + 1;
	const int Y = yd * from_y + 3;
	//开始移动
	if (dir == 0)//上
	{
		for (int k = 0; k < xd; ++k)
		{
			//背景白色
			cct_setcolor(15);
			cct_gotoxy(Y, X - k);
			for (int i = 0; i < xd - 1; ++i)
			{
				for (int j = 0; j < yd - 1; ++j)
				{
					cout << ' ';
				}
				cct_gotoxy(Y, X + 1 + i - k);
			}
			
			//色块颜色
			cct_setcolor(color);
			cct_gotoxy(Y, X - k - 1);
			for (int i = 0; i < xd - 1; ++i)
			{
				for (int j = 0; j < yd - 1; ++j)
				{
					cout << ' ';
				}
				cct_gotoxy(Y, X + 1 + i - k - 1);
			}

			Sleep(time);
		}
		cct_setcolor();
		cct_gotoxy(Y, X - 1);
		//三个空格
		cout << "   ";
	}
	else if (dir == 1)//下
	{
		for (int k = 0; k < xd; ++k)
		{
			//背景白色
			cct_setcolor(15);
			cct_gotoxy(Y, X + k);
			for (int i = 0; i < xd - 1; ++i)
			{
				for (int j = 0; j < yd - 1; ++j)
				{
					cout << ' ';
				}
				cct_gotoxy(Y, X + 1 + i + k);
			}

			//色块颜色
			cct_setcolor(color);
			cct_gotoxy(Y, X + k + 1);
			for (int i = 0; i < xd - 1; ++i)
			{
				for (int j = 0; j < yd - 1; ++j)
				{
					cout << ' ';
				}
				cct_gotoxy(Y, X + 1 + i + k + 1);
			}

			Sleep(time);
		}
		cct_setcolor();
		cct_gotoxy(Y, X + xd - 1);
		//三个空格
		cout << "   ";
	}
	else if (dir == 2)//左
	{
		for (int k = 0; k < yd; ++k)
		{
			//背景白色
			cct_setcolor(15);
			cct_gotoxy(Y - k, X );
			for (int i = 0; i < xd - 1; ++i)
			{
				for (int j = 0; j < yd - 1; ++j)
				{
					cout << ' ';
				}
				cct_gotoxy(Y - k, X + 1 + i);
			}

			//色块颜色
			cct_setcolor(color);
			cct_gotoxy(Y - k - 1, X);
			for (int i = 0; i < xd - 1; ++i)
			{
				for (int j = 0; j < yd - 1; ++j)
				{
					cout << ' ';
				}
				cct_gotoxy(Y - k - 1, X + 1 + i );
			}

			Sleep(time);
		}
		cct_setcolor();
		for (int i = 0; i < xd - 1; ++i)
		{
			cct_gotoxy(Y - 1, X + i);
			//竖着两个空格
			cout << ' ';
		}
		
	}
	else//右
	{
		for (int k = 0; k < yd; ++k)
		{
			//背景白色
			cct_setcolor(15);
			cct_gotoxy(Y + k, X);
			for (int i = 0; i < xd - 1; ++i)
			{
				for (int j = 0; j < yd - 1; ++j)
				{
					cout << ' ';
				}
				cct_gotoxy(Y + k, X + 1 + i );
			}

			//色块颜色
			cct_setcolor(color);
			cct_gotoxy(Y + k + 1, X);
			for (int i = 0; i < xd - 1; ++i)
			{
				for (int j = 0; j < yd - 1; ++j)
				{
					cout << ' ';
				}
				cct_gotoxy(Y + k + 1, X + 1 + i);
			}

			Sleep(time);
		}
		cct_setcolor();
		for (int i = 0; i < xd - 1; ++i)
		{
			cct_gotoxy(Y + yd - 1, X + i);
			//竖着两个空格
			cout << ' ';
		}
	}
	//恢复默认颜色
	cct_setcolor();
}
int color_ball::find_path(const int x1, const int y1, const int x2, const int y2)
{
	//清理上一次搜寻痕迹
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < N; ++j)
		{
			path_x[i][j] = 0;
			path_y[i][j] = 0;
		}
	//利用bfs，从[x1, y1]扩散
	int x_dir[4] = { -1, 1, 0, 0 };
	int y_dir[4] = { 0, 0, -1, 1 };
	struct Node {
		int x, y, step;
	};
	queue<Node> q;
	Node cur, temp;
	cur.x = x1;
	cur.y = y1;
	cur.step = 0;

	q.emplace(cur);
	while (!q.empty())
	{
		cur = q.front();
		q.pop();

		//找到目标位置，直接退出，保证是最短路径
		if (cur.x == x2 && cur.y == y2)
		{
			//恢复cp数组
			update_cp();
			return cur.step;
		}
		for (int i = 0; i < 4; ++i)
		{
			temp.x = cur.x + x_dir[i];
			temp.y = cur.y + y_dir[i];
			//没出界，没遍历过，没有球
			if (temp.x >= 0 && temp.y >= 0 && temp.x < M && temp.y < N && cp[temp.x][temp.y] == false)
			{
				temp.step = cur.step + 1;

				path_x[temp.x][temp.y] = cur.x;
				path_y[temp.x][temp.y] = cur.y;
				//标记遍历过
				cp[cur.x][cur.y] = true;
				//下一个结点入队
				q.emplace(temp);
			}
		}
	}
	//恢复cp数组
	update_cp();
	//找不到路径
	return 0;
}
void color_ball::start_game()
{
	cct_setconsoleborder(60, 40);
	button Button;
	while (1)
	{
		const int time = 100;
		bool checkfive = false;
		inputId();
		init();
		cct_setcolor();
		music(1);
		score_output();
		show();
		string text = "退出本轮游戏";
		Button.print(40, 4, text);
		text = "暂停/开始 音乐";
		Button.print(40, 4 + 4, text);
		while (1)
		{

			int val[3];
			//没有连成功，才会将要出来的球
			if (checkfive == false)
			{
				//随机三个颜色
				new_color(val);
				//显示将出现的三个球的颜色
				show_next_three_ball(val);
				//随机出来的球连成五个
				check();
			}
			
			//输出得分
			score_output();
			
			//展示棋盘
			Sleep(time);
			//a.show();
			//输入坐标并移动（找最短路径）/ 鼠标点击
			mouse_input();
			if (game_exit)
				break;
			//最短路径动画
			//判断是否消失条件
			//若可以消失则加分，不显示
			//不可以消失则随机将要出现的位置，三个球出现
			if (check())
			{
				checkfive = true;
			}
			else
			{
				checkfive = false;
				new_location(val);
			}
			Sleep(time);
			//检查是否游戏结束
			if (is_over())
			{
				score_output(true);
				break;
			}
		}
		//一局游戏结束之后
		inputScore();
		//恢复强制退出的，重新选择
		game_exit = false;
		
		char ch;
		while (1)
		{
			cct_gotoxy(0, M * 3 + 4);
			cout << "输入回车开始新一轮游戏，输入q退出,输入c查看分数";
			ch = _getch();
			//回车十进制ascii码
			if (ch == 13)
				break;
			if(ch == 'Q' || ch == 'q')
			{
				game_exit = true;
				break;
			}
			if (ch == 'C' || ch == 'c')
				showScore();
		}
		if (game_exit)
			break;
	}
}
void color_ball::inputScore()
{
	//所有数据存入string
	string tempId, fileData;
	int tempScore = 0;
	bool flag = false;
	ifstream in("score.txt", ios::in);
	if (in)
	{
		
		while (in >> tempId >> tempScore)
		{
			if (tempId != id)
			{
				fileData += tempId;
				fileData += " ";
				fileData += to_string(tempScore);
				fileData += "\n";
			}
			else//相同用户名分数取历史最大值
				score = max(score, tempScore);
		}
		in.close();
	}
	
	//存入完了清空在写进文档
	ofstream out("score.txt", ios::out);
	if (!out)
	{
		cct_gotoxy(0, 0);
		cout << "存档失败";
		return;
	}
		
	out << fileData;
	//最后将本轮游戏的信息写入文档
	out << id << ' ' << score << endl;
}
void color_ball::inputId()
{
	cct_cls();
	cct_gotoxy(0, 0);
	cout << "请输入用户名: ";
	cin >> id;
}
void color_ball::showScore()
{
	vector<node> players;
	
	ifstream in("score.txt", ios::in);
	if (!in)
		return;
	string ID;
	int temp = 0;
	while (in >> ID >> temp)
		players.emplace_back(node{ ID, temp });
	in.close();
	//从大到小排序
	sort(players.begin(), players.end(), CMP);
	cct_cls();
	cout << "得分" << endl;
	for (int i = 0; i < players.size(); ++i)
		cout << players[i].ID << ' '<< players[i].SCORE << endl;
}

int main() {
	color_ball a;
	a.start_game();
	return 0;
}