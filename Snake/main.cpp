#include <cstdio>
#include <iostream>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <deque>
using namespace std;
//取出标准输出设备对应句柄
static const HANDLE __hout = GetStdHandle(STD_OUTPUT_HANDLE);		//取标准输出设备对应的句柄
static const HANDLE __hin = GetStdHandle(STD_INPUT_HANDLE);		//取标准输入设备对应的句柄
const int M = 69, N = 17, MAX_LEN = 1000, default_len = 3, target_len = 40;
void cls()
{
	COORD coord = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO binfo;
	DWORD num;
	//取当前缓冲区信息
	GetConsoleScreenBufferInfo(__hout, &binfo);
	//填充字符
	FillConsoleOutputCharacter(__hout, (TCHAR)' ', binfo.dwSize.X * binfo.dwSize.Y, coord, &num);
	//填充属性
	FillConsoleOutputAttribute(__hout, binfo.wAttributes, binfo.dwSize.X * binfo.dwSize.Y, coord, &num);
	//光标回到0，0
	SetConsoleCursorPosition(__hout, coord);
	return;
}
void gotoxy( const int X, const int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(__hout, coord);
}
void showch( const int X, const int Y, const char ch)
{
	gotoxy( X, Y);
	putchar(ch);
}
void init_border(int MM = M, int NN = N)
{
	gotoxy( 0, 0);
	for (int Y = 0; Y <= N + 1; ++Y)
	{
		cout << '*';
		for (int X = 1; X <= M + 1; ++X)
		{
			if (Y == 0 || Y == N + 1)
				cout << '*';
			else
				cout << ' ';
		}
		cout << '*';
		cout << endl;
	}
}
void setcursor(const int options)
{
	CONSOLE_CURSOR_INFO cursor_info;
	if (options == 0)//光标不显示
	{
		cursor_info.bVisible = 0;
		cursor_info.dwSize = 1;
	}
	else//光标恢复
	{
		cursor_info.bVisible = 1;
		cursor_info.dwSize = 25;
	}
	SetConsoleCursorInfo(__hout, &cursor_info);
}
class Snake {
public:
	deque<int> x_coord;
	deque<int> y_coord;
	int max_length;
	int cur_length;
	int food_x = 0, food_y = 0;
	bool flag = false;//判断用否设置食物
	Snake(int _max_length = MAX_LEN):max_length(_max_length) {
		for (int i = 0; i < default_len; ++i)
		{
			x_coord.emplace_back((M + 1) / 2 + i );
			y_coord.emplace_back((N + 1) / 2);
			food_x = 0;
			food_y = 0;
		}
		cur_length = default_len;
	}
	void ini_snake_pos() {
		for (int i = 0; i < cur_length; ++i)
			showch(x_coord[i], y_coord[i], '0');
	}
	void move_once(int x_direction, int y_direction)
	{
		//蛇头+方向
		x_coord.emplace_front(x_coord.front() + x_direction);
		y_coord.emplace_front(y_coord.front() + y_direction);
		
	}
	void move_show_snake() {
		showch(x_coord.front(), y_coord.front(), '0');
		showch(x_coord.back(), y_coord.back(), ' ');
		//去掉蛇尾
		x_coord.pop_back();
		y_coord.pop_back();
	}
	//不出界
	bool is_alive() {
		return x_coord.front() > 0 && x_coord.front() < M + 2
			&& y_coord.front() > 0 && y_coord.front() < N + 1;
	}
	//食物不在身体里
	bool check_food_in_snake(int food_x, int food_y)
	{
		for (int i = 0; i < x_coord.size(); ++i)
			if (x_coord[i] == food_x && y_coord[i] == food_y)
				return true;
		return false;
	}
	//放置食物
	void set_food() {
		do
		{
			srand(time(NULL));
			food_x = rand() % (M - 2) + 1;
			food_y = rand() % (N - 2) + 1;
			//要保证不在蛇身体内部
		} while (check_food_in_snake(food_x, food_y));
		flag = false;
		showch(food_x, food_y, '#');
	}
	//判断是否吃到食物
	bool eaten()
	{
		return x_coord.front() == food_x && y_coord.front() == food_y;
	}
	//变长
	void get_longer()
	{
		++cur_length;
		flag = true;
		show_data();
		x_coord.emplace_front(x_coord.front());
		y_coord.emplace_front(y_coord.front());
	}
	//输出数据
	void show_data()
	{
		gotoxy(0, N + 3);
		cout << "THE LENGTH OF THE SNAKE IS :" << cur_length;
	}
};
void snake(Snake& s) 
{
	init_border();
	setcursor(0);
	char get_key;
	int d = 0;
	int x_direction[4] = { -1,1,0,0 };
	int y_direction[4] = { 0,0,-1,1 };
	//初始蛇位置
	s.ini_snake_pos();
	s.set_food();
	s.show_data();
	while (1) {
		if (s.flag)
			s.set_food();
		Sleep(500 - s.cur_length);
		//非阻塞判断有无输入
		if (_kbhit())
		{
			get_key = _getch();
			if (get_key == 'w' || get_key == 'W' || get_key == 'i' || get_key == 'I')
			{
				if (d != 3)
					d = 2;
			}
			else if (get_key == 's' || get_key == 'S' || get_key == 'k' || get_key == 'K')
			{
				if (d != 2)
					d = 3;
			}
			else if (get_key == 'a' || get_key == 'A' || get_key == 'j' || get_key == 'J')
			{
				if (d != 1)
					d = 0;
			}
			else if ((get_key == 'd' || get_key == 'D' || get_key == 'l' || get_key == 'L'))
			{
				if (d != 0)
					d = 1;
			}
			else if (get_key == 'q' || get_key == 'Q')
				break;
		}
		s.move_once(x_direction[d], y_direction[d]);
		s.move_show_snake();
		//判断有没有吃到
		if (s.eaten())
			s.get_longer();
		//判断有无出界
		if (!s.is_alive() || s.cur_length > MAX_LEN)
			break;
		if (s.cur_length == target_len)
		{
			gotoxy(0, N + 3);
			cout << "HOORAY ! YOU WIN !! CONGRATULATIONS !!" << endl;
			break;
		}
	}
}
int main() {
	
	char ch;
	while (1)
	{
		cls();//清空窗口
		cout << "PLEASE PUT IN ANY KEY TO START YOUR GAME" << endl;
		cout << " \tW                     \tI" << endl;
		cout << "A\tS\tF        J\tK\tL" << endl;
		ch = _getch();
		gotoxy(0, N + 2);
		cout << "INTPUT Q TO END THE GAME";
		
		Snake s;
		
		snake(s);

		gotoxy(0, N + 3);
		cout << "GAME OVER! YOUR LENGTH IS " << s.cur_length << "!!       " << endl;;
		cout << "INPUT Q IF YOU REALLY WANT TO END THE GAME, OR OTHER KEYS FOR ONE MORE TIME" << endl;;
		ch = _getch();
		if (ch == 'q' || ch == 'Q')
			break;
	}
	setcursor(1);
	return 0;
}