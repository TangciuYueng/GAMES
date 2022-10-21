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
	//���캯��
	color_ball();
	//��ʼ��Ϸ
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
	//DFS���Ƿ��п��Դ�[x1, y1] ��[x2, y2]��·��
	bool dfs(const int x1, const int y1, const int x2, const int y2, const int i, const int j);
	//����cp����
	void update_cp();
	//��ӡcp����
	void show_cp();
	//��ʼ������
	void init();
	//��ӡ����
	void show();
	//�ж��ܷ��ƶ�����
	bool can_move(const int x1, const int y1, const int x2, const int y2);
	//����������
	//�������꺯�����ƶ�
	void input_move();
	//������
	//�ж��Ƿ������ߺ���
	bool check();
	bool check_five_remove(int x0, int y0);
	//�����·������
	int find_path(const int x1, const int y1, const int x2, const int y2);
	//չʾ�ƶ�·��
	void show_path(const int x1, const int y1, const int x2, const int y2);
	//�ƶ�����
	void move(const int x1, const int y1, const int x2, const int y2);
	//ɫ���ƶ�
	void show_move_once(const int from_x, const int from_y, const int to_x, const int to_y, int color);
	//��������������
	void new_color(int val[]);
	void new_location(int val[], int num = 3);
	//�������
	void clear_ball(const int x, const int y, const int val, int select);
	//�������
	void mouse_input();
	//��ʾ�����ֵ���������
	void show_next_three_ball(int val[]);
	//�������
	void output_cube(const int x, const int y, bool h);
	//ѡ��
	void click_on(const int x, const int y);
	//����÷�
	void score_output(bool is_over = false);
	//�ж���Ϸ�Ƿ����
	bool is_over();
	//��������
	void music(bool play);
	//�÷�д���ĵ�
	void inputScore();
	//�������÷�
	void showScore();
	//�����û���
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
