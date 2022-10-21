#pragma once
#include <vector>
#include <queue>
#include <mmsystem.h>
#include <algorithm>
#include <conio.h>
#include <fstream>
#include <string>
#include "resource.h"
#pragma comment(lib, "winmm.lib")
using namespace std;
const int M = 9, N = 9; 
class color_ball {
public:
	//构造函数
	color_ball();
	//开始游戏
	void start_game();
private:
	int score;
	string id;
	int shortest_size;
	int board[M][N];
	bool cp[M][N];
	int path_x[M][N] = { 0 };
	int path_y[M][N] = { 0 };
	bool music_is_playing, game_exit;
	int ball_num;
	const int color_num;
	//DFS找是否有可以从[x1, y1] 到[x2, y2]的路径
	bool dfs(const int x1, const int y1, const int x2, const int y2, const int i, const int j);
	//更新cp数组
	void update_cp();
	//打印cp数组
	void show_cp();
	//初始化函数
	void init();
	//打印数组
	void show();
	//判断能否移动函数
	bool can_move(const int x1, const int y1, const int x2, const int y2);
	//画背景函数
	//输入坐标函数并移动
	void input_move();
	//画球函数
	//判断是否连成线函数
	bool check();
	bool check_five_remove(int x0, int y0);
	//找最短路径函数
	int find_path(const int x1, const int y1, const int x2, const int y2);
	//展示移动路径
	void show_path(const int x1, const int y1, const int x2, const int y2);
	//移动函数
	void move(const int x1, const int y1, const int x2, const int y2);
	//色块移动
	void show_move_once(const int from_x, const int from_y, const int to_x, const int to_y, int color);
	//新生成三个球函数
	void new_color(int val[]);
	void new_location(int val[], int num = 3);
	//清除球函数
	void clear_ball(const int x, const int y, const int val, int select);
	//点击函数
	void mouse_input();
	//显示将出现的三个方块
	void show_next_three_ball(int val[]);
	//输出方块
	void output_cube(const int x, const int y, bool h);
	//选中
	void click_on(const int x, const int y);
	//输出得分
	void score_output(bool is_over = false);
	//判断游戏是否结束
	bool is_over();
	//背景音乐
	void music(bool play);
	//得分写入文档
	void inputScore();
	//读出来得分
	void showScore();
	//输入用户名
	void inputId();
};
struct node
{
	string ID;
	int SCORE;
};
struct button {
	int x, y, h = 3, w = 16;
	string text;
	void print(int x, int y, string& myText);
};
