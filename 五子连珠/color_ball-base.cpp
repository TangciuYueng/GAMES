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
	//��ʼ�߸���
	const int init_num = 7;
	ball_num += 7;
	int i = 0;
	while (i < init_num)
	{
		//���λ��0 - (M - 1)����ɫ0-5������ɫ
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
	//���ʼ��ʾ
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
		cout << "����������[1,9]����һλ�����У��ڶ�λ������";
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
			//can_move�����ı�cp���飬ʹ����ָ�
			update_cp();
			break;
		}
		else
		{
			//can_move�����ı�cp���飬ʹ����ָ�
			update_cp();
			cout << "�����������������" << endl;
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
	//�õ�û�����Ŀ��������ͬһ����
	if (cp[x1][y1] == false || cp[x2][y2] || (x1 == x2 && y1 == y2))
		return false;
	return dfs(x1, y1, x2, y2, x1 - 1, y1) || dfs(x1, y1, x2, y2, x1 + 1, y1)
		|| dfs(x1, y1, x2, y2, x1, y1 - 1) || dfs(x1, y1, x2, y2, x1, y1 + 1);
	//ִ����ɻָ�cp����
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
	//����Ѿ�������
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
	//ʣ�µ�λ����������
	while (M * N - ball_num < num)
		--num;
	while (i < num)
	{
		int x = rand() % M;
		int y = rand() % N;
		//����û����
		if (!cp[x][y])
		{
			board[x][y] = val[i];
			//�������ͼ�κ���
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
	cout << "�����ֵ���ɫ";
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
	//��ĳ�������λ�ÿ�ʼ
	bool five = false;
	//�������ҡ����¡�����б������б�ĸ�����Ľ��
	int ans[4]= { 0 };
	int total = 1, color = board[x0][y0], i, j, cnt = 0;
	const int NUM = 5;
	//���㲻���硢ͬ����ɫ���ܼ�¼total
	//����
	for (i = 1; x0 - i >= 0 && board[x0 - i][y0] == color; ++i)
		++total;
	for (j = 1; x0 + j <= M && board[x0 + j][y0] == color; ++j)
		++total;
	//�����������ͼ�¼
	if (total >= NUM)
	{
		++cnt;
		ans[0] = total;
		five = true;
	}	
	//����
	total = 1;
	for (int i = 1; y0 - i >= 0 && board[x0][y0 - i] == color; ++i)
		++total;
	for (int j = 1; y0 + j < N && board[x0][y0 + j] == color; ++j)
		++total;
	//�����������ͼ�¼
	if (total >= NUM)
	{
		++cnt;
		ans[1] = total;
		five = true;
	}
	//����б
	total = 1;
	for (i = 1; x0 - i >= 0 && y0 + i < N && board[x0 - i][y0 + i] == color; ++i)
		++total;
	for (j = 1; x0 + j < M && y0 - j >= 0 && board[x0 + j][y0 - j] == color; ++j)
		++total;
	//�����������ͼ�¼
	if (total >= NUM)
	{
		++cnt;
		ans[2] = total;
		five = true;
	}
	//����б
	total = 1;
	for (i = 1; x0 - i >= 0 && y0 - i >= 0 && board[x0 - i][y0 - i] == color; ++i)
		++total;
	for (j = 1; x0 + j < M && y0 + j < N && board[x0 + j][y0 + j] == color; ++j)
		++total;
	//�����������ͼ�¼
	if (total >= NUM)
	{
		++cnt;
		ans[3] = total;
		five = true;
	}
	//��ʼ��ȥ��
	if (five)//�г��������
	{
		//����ȥx0,y0
		board[x0][y0] = -1;
		cp[x0][y0] = false;
		output_cube(x0, y0, 0);
		ball_num -= 1;
		score += 2;
		//����ȥ�Աߵ�
		//i��0 �� 3�����£����ң�����б������б
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
	//����
	if (x < 0 || y < 0 || x >= M || y >= N)
		return;
	//�����ɫ
	if (board[x][y] != val)
		return;
	//û����
	if (cp[x][y] == false)
		return;
	//���
	cp[x][y] = false;
	board[x][y] = -1;
	//ͬʱ�ָ�������ɫ
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
	cct_setcursor(CURSOR_INVISIBLE);	//�رչ��
	while (1)
	{
		//��һ�ε��
		while (1)
		{
			ret = cct_read_keyboard_and_mouse(my, mx, m_action, k1, k2);
			//��������
			if (ret == CCT_MOUSE_EVENT)
			{
				//���� �� ���ӵı߽�
				if ((my > 2 + yd * N || mx > xd * M) || (mx % xd == 0 || my <= 2 || (my - 2) % yd == 0))
				{
					cct_gotoxy(0, xd * M + 1);
					cout << "��ʼ����ǰ�������Ƿ�           ";
					cct_showch(0, xd * M + 2, ' ', 0, 7, 25);
					//���ְ�ť
					if (mx >= mY && mx <= mY + h && my >= mX && my <= mX + w)
					{
						cct_gotoxy(0, xd * M + 1);
						cout << "���ְ�ť                       ";
						//��ͣor��������
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
							//����ѡ����ʼλ��
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
							//����ѡ����ʼλ��
							continue;
						}
				}
					//������ť
					else if (mx >= fY && mx <= fY + h && my >= fX && my <= fX + w)
					{
						cct_gotoxy(0, xd * M + 1);
						cout << "�������ְ�ť                  ";
						if (m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							//��������
							music(0);
							game_exit = true;
							return;
						}
						int x_tmp, y_tmp;
						ret = cct_read_keyboard_and_mouse(y_tmp, x_tmp, m_action, k1, k2);
						if (x_tmp >= fY && x_tmp <= fY + h && y_tmp >= fX && y_tmp <= fX + w && m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							//��������
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
				cout << "��ʼ����ǰ�������[" << x1 + 1 << ',' << y1 + 1 << ']';
				cct_showch(0, xd * M + 2, ' ', 0, 7, 25);
				//�ڸ�����
				if (x1 >= 0 && y1 >= 0 && x1 < M && y1 < N)
				{
					//û���򣬲����Ե��
					if (cp[x1][y1] == false)
					{
						continue;
					}
						
					//���򣬿��Ե��
					else
					{
						if (m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							//ѡ�к���
							click_on(x1, y1);
							cct_gotoxy(0, xd * M + 1);
							cout << "��ʼ����ѡ��[" << x1 + 1 << ',' << y1 + 1 << ']' << "       ";
							break;
						}
						int x_tmp, y_tmp;
						ret = cct_read_keyboard_and_mouse(y_tmp,x_tmp, m_action, k1, k2);
						//���û�����ӣ��ǵ��
						if (x1 == x_tmp / xd && y1 == (y_tmp - 2) / yd && m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							//ѡ�к���
							click_on(x1, y1);
							cct_gotoxy(0, xd * M + 1);
							cout << "��ʼ����ѡ��[" << x1 + 1 << ',' << y1 + 1 << ']' << "       ";
							break;
						}
						//�ظ���һ��ѡ��
						else
							continue;
					}
				}
				
			}
			//���̲���
			else
			{
				//�ո���ͣor��������
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
					//����ѡ����ʼλ��
					continue;
				}
				//����q
				else if (k1 == 'q' || k1 == 'Q')
				{
					//��������
					music(0);
					game_exit = true;
					return;
				}
			}
		}
		//�ڶ��ε��
		while (1)
		{
			ret = cct_read_keyboard_and_mouse(my, mx, m_action, k1, k2);
			if (ret == CCT_MOUSE_EVENT)
			{
				//���� �� ���ӵı߽� ���ǵ�����ظ���һ��ѡ��
				if ((my > 2 + yd * N || mx > xd * M) || (mx % xd == 0 || my <= 2 || (my - 2) % yd == 0))
				{
					cct_gotoxy(0, xd * M + 2);
					cout << "Ŀ�꣺��ǰ�������Ƿ�           ";
					//���ְ�ť
					if (mx >= mY && mx <= mY + h && my >= mX && my <= mX + w)
					{
						cct_gotoxy(0, xd * M + 1);
						cout << "���ְ�ť                       ";
						//��ͣor��������
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
							//����ѡ����ʼλ��
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
							//����ѡ����ʼλ��
							continue;
						}
					}
					//������ť
					else if (mx >= fY && mx <= fY + h && my >= fX && my <= fX + w)
					{
						cct_gotoxy(0, xd * M + 1);
						cout << "�������ְ�ť                  ";
						if (m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							//��������
							music(0);
							game_exit = true;
							return;
						}
						int x_tmp, y_tmp;
						ret = cct_read_keyboard_and_mouse(y_tmp, x_tmp, m_action, k1, k2);
						if (x_tmp >= fY && x_tmp <= fY + h && y_tmp >= fX && y_tmp <= fX + w && m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							//��������
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
				cout << "Ŀ�꣺��ǰ�������[" << x2 + 1 << ',' << y2 + 1 << ']';
				//�ڸ�����
				if (x2 >= 0 && y2 >= 0 && x2 < M && y2 < N)
				{
					//���򣬿��Ե��,��������ѡ��
					if (cp[x2][y2] == true)
					{
						if (m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							cct_gotoxy(0, xd* M + 2);
							cout << "Ŀ�꣺�������򣬲����ƶ�        ";
							have_ball = true;
							Sleep(500);
							break;
						}
							
						else
							continue;
					}
					//û���򣬿��Ե��
					else
					{
						if (m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							flag = true;
							break;
						}
						int x_tmp, y_tmp;
						ret = cct_read_keyboard_and_mouse(y_tmp, x_tmp, m_action, k1, k2);
						//���û�����ӣ��ǵ��
						if (x2 == x_tmp / xd && y2 == (y_tmp - 2) / yd && m_action == MOUSE_LEFT_BUTTON_CLICK)
						{
							flag = true;
							break;
						}
						//�ظ���һ��ѡ��
						else
							continue;
					}
				}
			}
			//���̲���
			else
			{
				//�ո���ͣor��������
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
					//����ѡ����ʼλ��
					continue;
				}
				//����q
				else if (k1 == 'q' || k1 == 'Q')
				{
					//��������
					music(0);
					game_exit = true;
					return;
				}
			}
		}
		//�ڶ���ѡ��Ҳ�����
		int res_path = find_path(x1, y1, x2, y2);
		if (res_path == 0 && have_ball == false)
		{
			cct_gotoxy(0, xd* M + 2);
			cout << "Ŀ�꣺�������赲�������ƶ�         ";
			Sleep(500);
		}
		if (flag && res_path)
			break;
	}
	cct_disable_mouse();	//�������
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
		color = 15;//����
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
		cout << "�������յ÷�Ϊ��" << score << "!! EXCELLENT! AMAZING! WONDERFUL!";
	else
		cout << "Ŀǰ�÷�Ϊ��" << score <<"                                         ";
	cct_gotoxy(0, M * xd + 4);
	cout << "����q������Ϸ                                                          ";
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
	//0��1 ��2��3������������
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
	//��ʼ�ƶ�
	if (dir == 0)//��
	{
		for (int k = 0; k < xd; ++k)
		{
			//������ɫ
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
			
			//ɫ����ɫ
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
		//�����ո�
		cout << "   ";
	}
	else if (dir == 1)//��
	{
		for (int k = 0; k < xd; ++k)
		{
			//������ɫ
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

			//ɫ����ɫ
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
		//�����ո�
		cout << "   ";
	}
	else if (dir == 2)//��
	{
		for (int k = 0; k < yd; ++k)
		{
			//������ɫ
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

			//ɫ����ɫ
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
			//���������ո�
			cout << ' ';
		}
		
	}
	else//��
	{
		for (int k = 0; k < yd; ++k)
		{
			//������ɫ
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

			//ɫ����ɫ
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
			//���������ո�
			cout << ' ';
		}
	}
	//�ָ�Ĭ����ɫ
	cct_setcolor();
}
int color_ball::find_path(const int x1, const int y1, const int x2, const int y2)
{
	//������һ����Ѱ�ۼ�
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < N; ++j)
		{
			path_x[i][j] = 0;
			path_y[i][j] = 0;
		}
	//����bfs����[x1, y1]��ɢ
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

		//�ҵ�Ŀ��λ�ã�ֱ���˳�����֤�����·��
		if (cur.x == x2 && cur.y == y2)
		{
			//�ָ�cp����
			update_cp();
			return cur.step;
		}
		for (int i = 0; i < 4; ++i)
		{
			temp.x = cur.x + x_dir[i];
			temp.y = cur.y + y_dir[i];
			//û���磬û��������û����
			if (temp.x >= 0 && temp.y >= 0 && temp.x < M && temp.y < N && cp[temp.x][temp.y] == false)
			{
				temp.step = cur.step + 1;

				path_x[temp.x][temp.y] = cur.x;
				path_y[temp.x][temp.y] = cur.y;
				//��Ǳ�����
				cp[cur.x][cur.y] = true;
				//��һ��������
				q.emplace(temp);
			}
		}
	}
	//�ָ�cp����
	update_cp();
	//�Ҳ���·��
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
		string text = "�˳�������Ϸ";
		Button.print(40, 4, text);
		text = "��ͣ/��ʼ ����";
		Button.print(40, 4 + 4, text);
		while (1)
		{

			int val[3];
			//û�����ɹ����ŻὫҪ��������
			if (checkfive == false)
			{
				//���������ɫ
				new_color(val);
				//��ʾ�����ֵ����������ɫ
				show_next_three_ball(val);
				//������������������
				check();
			}
			
			//����÷�
			score_output();
			
			//չʾ����
			Sleep(time);
			//a.show();
			//�������겢�ƶ��������·����/ �����
			mouse_input();
			if (game_exit)
				break;
			//���·������
			//�ж��Ƿ���ʧ����
			//��������ʧ��ӷ֣�����ʾ
			//��������ʧ�������Ҫ���ֵ�λ�ã����������
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
			//����Ƿ���Ϸ����
			if (is_over())
			{
				score_output(true);
				break;
			}
		}
		//һ����Ϸ����֮��
		inputScore();
		//�ָ�ǿ���˳��ģ�����ѡ��
		game_exit = false;
		
		char ch;
		while (1)
		{
			cct_gotoxy(0, M * 3 + 4);
			cout << "����س���ʼ��һ����Ϸ������q�˳�,����c�鿴����";
			ch = _getch();
			//�س�ʮ����ascii��
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
	//�������ݴ���string
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
			else//��ͬ�û�������ȡ��ʷ���ֵ
				score = max(score, tempScore);
		}
		in.close();
	}
	
	//�������������д���ĵ�
	ofstream out("score.txt", ios::out);
	if (!out)
	{
		cct_gotoxy(0, 0);
		cout << "�浵ʧ��";
		return;
	}
		
	out << fileData;
	//��󽫱�����Ϸ����Ϣд���ĵ�
	out << id << ' ' << score << endl;
}
void color_ball::inputId()
{
	cct_cls();
	cct_gotoxy(0, 0);
	cout << "�������û���: ";
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
	//�Ӵ�С����
	sort(players.begin(), players.end(), CMP);
	cct_cls();
	cout << "�÷�" << endl;
	for (int i = 0; i < players.size(); ++i)
		cout << players[i].ID << ' '<< players[i].SCORE << endl;
}

int main() {
	color_ball a;
	a.start_game();
	return 0;
}