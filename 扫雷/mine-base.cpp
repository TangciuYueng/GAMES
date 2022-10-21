#include "mine.h"
#include "resource.h"
#include "resource1.h"
//��ť���ʵ��
button::button(int X, int Y, char _text[])
{
	this->X = X;
	this->Y = Y;
	for (int i = 0; i < 20; ++i)
		this->text[i] = _text[i];
}
button::button(int X, int Y, char _text[], int w, int h)
{
	this->X = X;
	this->Y = Y;
	for (int i = 0; i < 20; ++i)
		this->text[i] = _text[i];
	this->w = w;
	this->h = h;
}
void button::clickButton()
{
	//������
	COLORREF bkColor = getbkcolor();
	setfillcolor(bkColor);
	solidrectangle(X, Y, X + w, Y + h);
	setfillcolor(RGB(70, 70, 70));
	solidrectangle(X + shadow, Y + shadow, X + shadow + w, Y + shadow + h);
	//��������
	settextstyle(30, 0, "����");
	int x = (w + shadow - textwidth(text)) / 2 + X;
	int y = (h + shadow - textheight(text)) / 2 + Y;
	setbkmode(TRANSPARENT);
	outtextxy(x, y, text);
}
void button::onButton()
{
	//������
	setfillcolor(RGB(120, 120, 120));
	solidrectangle(X + shadow, Y + shadow, X + shadow + w, Y + shadow + h);
	setfillcolor(RGB(70, 70, 70));
	solidrectangle(X, Y, X + w, Y + h);
	//��������
	settextstyle(30, 0, "����");
	int x = (w - textwidth(text)) / 2 + X;
	int y = (h - textheight(text)) / 2 + Y;
	setbkmode(TRANSPARENT);
	outtextxy(x, y, text);
}
void button::drawButton()
{
	//������
	setfillcolor(RGB(134, 134, 134));
	solidrectangle(X + shadow, Y + shadow, X + shadow + w, Y + shadow + h);
	setfillcolor(RGB(160, 160, 160));
	solidrectangle(X, Y, X + w, Y + h);
	//��������
	settextstyle(30, 0, "����");
	int x = (w - textwidth(text)) / 2 + X;
	int y = (h - textheight(text)) / 2 + Y;
	setbkmode(TRANSPARENT);
	outtextxy(x, y, text);
}

//ɨ����Ϸ��ʵ��
myMine::myMine()
{
	map.resize(N, vector<int>(M, 0));
}
myMine::myMine(int N, int M, int  MINE, int Size)
{
	this->N = N;
	this->M = M;
	this->MINE = MINE;
	this->Size = Size;
	map.resize(N, vector<int>(M, 0));

}
void myMine::afterMine()
{
	/*����֮��ÿ�����׵ĵط����Գ���*/
	BeginBatchDraw();
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
		{
			if (map[i][j] == 19)
			{
				map[i][j] -= 20;
				putimage(j * Size, i * Size + firstLine, &img[9]);
				FlushBatchDraw();
				Sleep(STOP_TIME / 4);
			}
			else if (map[i][j] == 39)
			{
				map[i][j] -= 40;
				putimage(j * Size, i * Size + firstLine, &img[9]);
				FlushBatchDraw();
				Sleep(STOP_TIME / 2);
			}
		}
	EndBatchDraw();
}
void myMine::open(int r, int c)
{
	if (map[r][c] == 0)
	{
		for (int m = r - 1; m <= r + 1; ++m)
		{
			for (int n = c - 1; n <= c + 1; ++n)
			{
				//�����磬û�мǺ�
				if (m >= 0 && n >= 0 && m < N && n < M && map[m][n] >= 20 && map[m][n] <= 28)
				{
					map[m][n] -= 20;
					++flag;
					open(m, n);//�ݹ���Χ�ĸ���
				}
			}
		}
	}
}
bool myMine::check()
{
	int sum = 0, sum2 = 0;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
		{
			if (map[i][j] >= 30)//�������
				++sum;
			else if (map[i][j] == 19 + 20)//������׵�����
				++sum2;
		}
	//��ǵ����� ���� ��ǵ��׵�����
	if (sum == sum2 && sum2 == MINE)
		return true;
	else
		return false;
}
void myMine::initMap()
{
	//ÿһ���µ���Ϸ��ʼ������
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			map[i][j] = 0;

	flag = 0;
	fail = false;
	startTime = false;
	tag = 0;
	srand(unsigned(time(NULL)));//���������
	//��������׵�λ��
	for (int i = 0; i < MINE;)
	{
		int r = rand() % N;//���0-9
		int c = rand() % M;
		if (map[r][c] != -1)
		{
			map[r][c] = -1;
			++i;
		}
	}
	//������Χ�������
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			//�������
			if (map[i][j] == -1)
			{
				for (int m = i - 1; m <= i + 1; ++m)
				{
					for (int n = j - 1; n <= j + 1; ++n)
					{
						//���������
						if (m < 0 || n < 0 || m >= N || n >= M || map[m][n] == -1)
							continue;
						++map[m][n];
					}
				}
			}
		}
	}
	//�Ӷ�ʮ���ϸ���
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			map[i][j] += 20;
	//����ͼƬ
	for (int i = 0; i < 12; ++i)
	{
		char temp[50] = "";
		sprintf(temp, "IMG%d", i + 1);
		loadimage(&img[i], "IMAGE", temp, Size, Size);
	}

}
void myMine::drawMap()
{
	cleardevice();//����ϴκۼ�
	//��ʾʣ���׵���Ŀ
	char temp[10] = "";
	sprintf(temp, "%3d", MINE - tag);
	setfillcolor(BLACK);
	solidrectangle(15, 5, 25 + 50, 45);
	settextcolor(RED);
	settextstyle(30, 0, "����");
	setbkmode(TRANSPARENT);
	outtextxy(30, 10, temp);
	//��ͼƬ
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			if (map[i][j] == -1)//��
			{
				putimage(j * Size, i * Size + firstLine, &img[9]);
			}
			else if (map[i][j] == 0)
			{
				putimage(j * Size, i * Size + firstLine, &img[0]);
			}
			else if (map[i][j] > 0 && map[i][j] <= 8)//������
			{
				putimage(j * Size, i * Size + firstLine, &img[map[i][j]]);
			}
			else if (map[i][j] >= 19 && map[i][j] <= 28)//��ס��
			{
				putimage(j * Size, i * Size + firstLine, &img[10]);
			}
			else if (map[i][j] >= 30)//���
			{
				putimage(j * Size, i * Size + firstLine, &img[11]);
			}
		}
	}


}
void myMine::mouseInput()
{
	if (MouseHit())
	{
		if (gameBegin == false)
			gameBegin = true;
		if (startTime == false)
		{
			GetLocalTime(&begTime);
			startTime = true;
		}

		MOUSEMSG msg = GetMouseMsg();
		int r = (msg.y - firstLine) / Size;
		int c = msg.x / Size;
		if (msg.y < firstLine)//������һ�е㲻��
			return;
		if (msg.uMsg == WM_LBUTTONDOWN)//����㿪�и��ӵ�
		{

			if (map[r][c] == 19)//�㿪��
			{
				clickMusic = true;
				map[r][c] -= 20;
				fail = true;//ʧ����
				return;
			}
			if (map[r][c] > 8 && map[r][c] <= 28 && map[r][c] != 19)//�㿪�����׵�λ��
			{
				clickMusic = true;
				map[r][c] -= 20;
				++flag;
				open(r, c);
			}

		}
		else if (msg.uMsg == WM_RBUTTONDOWN)//�Ҽ����
		{

			if (map[r][c] >= 19 && map[r][c] <= 28)//û�㿪�Ĳſɱ��
			{
				clickMusic = true;
				map[r][c] += 20;
				++tag;
			}
			else if (map[r][c] > 30)//����˵�ȡ�����
			{
				clickMusic = true;
				map[r][c] -= 20;
				--tag;
			}
		}

	}
}
void myMine::showMap()
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			printf("%d ", map[i][j]);

		}
		putchar('\n');
	}
}
void myMine::intputMsg(char name[], int Time)
{
	ifstream in("Msg.txt", ios::in);
	string thisName = "";
	thisName += name;
	string tempName, fileData;
	int tempTime = 0;
	if (in)
	{
		while (in >> tempName >> tempTime)
		{
			if (tempName != thisName)
			{
				fileData += tempName;
				fileData += " ";
				fileData += to_string(tempTime);
				fileData += "\n";
			}
			else//��ͬ�û���ȡ��С
				Time = min(Time, tempTime);
		}
		in.close();
	}
	//����fileData���������д���ĵ�
	ofstream out("Msg.txt", ios::out);
	if (!out)
	{
		return;
	}
	out << fileData;
	out << thisName << ' ' << Time << endl;

}
void myMine::game()
{
	initgraph(Size * M, Size * N + 50, NOMINIMIZE);

	bool exitGame = false;
	setbkcolor(RGB(191, 191, 191));
	while (1)
	{
		BeginBatchDraw();

		initMap();
		drawMap();
		while (1)
		{
			mouseInput();
			//�Ȼ�ͼ
			drawMap();
			FlushBatchDraw();
			if (clickMusic)//�����������
			{
				//PlaySound("./image/click.wav", NULL, SND_SYNC | SND_FILENAME);
				PlaySound(LPCSTR(IDR_WAVE2), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC );

				clickMusic = false;
			}
			if (fail)//�ȵ�����
			{
				//PlaySound("./image/boom.wav", NULL, SND_SYNC | SND_FILENAME | SND_LOOP);
				PlaySound(LPCSTR(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC );

				gameBegin = false;
				drawMap();//һ�ֽ����������

				Sleep(STOP_TIME / 4);
				afterMine();
				FlushBatchDraw();

				PlaySound(NULL, NULL, SND_SYNC);
				int is = MessageBox(GetHWnd(), "�����ˣ�����һ����", "��ʾ", MB_OKCANCEL);
				if (is != IDOK)
					exitGame = true;//�����ر�
				break;
			}
			if (flag == N * M - MINE || check())//Ӯ��
			{
				//PlaySound("./image/tada.wav", NULL, SND_SYNC | SND_FILENAME);
				PlaySound(LPCSTR(IDR_WAVE3), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);

				gameBegin = false;
				//Ӯ�˼�¼ʱ��
				GetLocalTime(&endTime);
				
				int Time = (endTime.wHour - begTime.wHour) * 3600
					+ (endTime.wMinute - begTime.wMinute) * 60
					+ (endTime.wSecond - begTime.wSecond);


				drawMap();//һ�ֽ����������
				FlushBatchDraw();

				//��¼�û���
				char name[20] = "";
				InputBox(name, 20, "�������û���", "ɨ��");
				intputMsg(name, Time);//�����ļ�

				int is = MessageBox(GetHWnd(), "����winwinwin�ˣ�����һ����", "��ʾ", MB_OKCANCEL);
				if (is != IDOK)
					exitGame = true;//�����ر�
				break;
			}
		}//end of while
		if (exitGame)
		{
			break;
		}
		EndBatchDraw();

	}//end of while

	closegraph();
}

//�ȽϺ����ͽ�����Ϸ֮ǰ����
bool cmp(node& a, node& b)
{
	if (a.Time == b.Time)
		return a.name < b.name;
	return a.Time < b.Time;
}
int selectDfct()
{
	int N = 10, M = 10, MINE = 10;
	int Size = 50;
	const int w = 150, h = 45, shadow = 4;

	setbkcolor(BLACK);
	settextcolor(WHITE);
	cleardevice();

	const int itv = 75, x1 = (M * Size - w) / 2, y1 = N * Size / 3 + itv,
		x2 = x1, y2 = N * Size / 3 + 2 * itv,
		x3 = x1, y3 = N * Size / 3 + 3 * itv,
		x4 = x1, y4 = N * Size / 3 + 4 * itv,
		x = Size * (M - 3), y = Size * (N - 1);

	int res = 0;
	string text = "����";
	char temp[20] = "";
	strcpy(temp, text.c_str());
	button d1(x1, y1, temp);
	text = "�м�";
	strcpy(temp, text.c_str());
	button d2(x2, y2, temp);
	text = "�߼�";
	strcpy(temp, text.c_str());
	button d3(x3, y3, temp);
	text = "�Զ���";
	strcpy(temp, text.c_str());
	button diy(x4, y4, temp);
	text = "�˳�";
	strcpy(temp, text.c_str());
	button _exit(x, y, temp, 100, 50);

	BeginBatchDraw();
	d1.drawButton();
	d2.drawButton();
	d3.drawButton();
	diy.drawButton();
	_exit.drawButton();

	FlushBatchDraw();
	while (1)
	{
		cleardevice();
		d1.drawButton();
		d2.drawButton();
		d3.drawButton();
		diy.drawButton();
		_exit.drawButton();

		MOUSEMSG msg = GetMouseMsg();
		if (msg.x >= x1 && msg.x <= x1 + w && msg.y >= y1 && msg.y <= y1 + h)
		{
			d1.onButton();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				d1.clickButton();
				FlushBatchDraw();
				Sleep(STOP_TIME);
				res = 1;
				break;
			}
		}
		else if (msg.x >= x2 && msg.x <= x2 + w && msg.y >= y2 && msg.y <= y2 + h)
		{
			d2.onButton();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				d2.clickButton();
				FlushBatchDraw();
				Sleep(STOP_TIME);
				res = 2;
				break;
			}
		}
		else if (msg.x >= x3 && msg.x <= x3 + w && msg.y >= y3 && msg.y <= y3 + h)
		{
			d3.onButton();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				d3.clickButton();
				FlushBatchDraw();
				Sleep(STOP_TIME);
				res = 3;
				break;
			}
		}
		else if (msg.x >= x4 && msg.x <= x4 + w && msg.y >= y4 && msg.y <= y4 + h)
		{
			diy.onButton();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				diy.clickButton();
				FlushBatchDraw();
				Sleep(STOP_TIME);
				res = 4;
				break;
			}
		}
		else if (msg.x >= x && msg.x <= x + w && msg.y >= y && msg.y <= y + h)
		{
			_exit.onButton();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				_exit.clickButton();
				FlushBatchDraw();
				Sleep(STOP_TIME);
				res = 5;
				break;
			}
		}

		FlushBatchDraw();
	}
	EndBatchDraw();
	return res;
}
void board()
{
	int N = 10, M = 10, MINE = 10;
	int Size = 50;
	const int w = 150, h = 45, shadow = 4;

	setbkcolor(BLACK);
	settextcolor(WHITE);
	cleardevice();
	ifstream in("Msg.txt", ios::in);
	char text[] = "���а�";
	settextstyle(100, 0, "����");
	int len = textwidth(text);
	int hei = textheight(text);
	outtextxy((M * Size - len) / 2, Size / 2, text);
	if (!in)
	{
		settextstyle(50, 0, "����");
		char text[] = "��û�����а�";
		int len = textwidth(text), h = textheight(text);
		outtextxy((M * Size - len) / 2, (N * Size - hei) / 2, text);
	}
	else
	{
		vector<node> player;
		string tempName;
		int tempTime;
		while (in >> tempName >> tempTime)
			player.emplace_back(node{ tempName, tempTime });
		sort(player.begin(), player.end(), cmp);
		for (int i = 0; i < player.size(); ++i)
		{
			char msg[30] = "";
			sprintf(msg, "%d %s %ds", i + 1, player[i].name.c_str(), player[i].Time);
			settextstyle(20, 0, "����");

			outtextxy(Size, hei + Size / 2 * (i + 1), msg);
		}
	}
	char text2[] = "�˳�";
	int x = Size * (M - 4), y = Size * (N - 1);
	button _exit(x, y, text2);
	BeginBatchDraw();
	_exit.drawButton();
	FlushBatchDraw();
	while (1)
	{
		_exit.drawButton();

		MOUSEMSG msg = GetMouseMsg();
		if (msg.x >= x && msg.x <= x + w && msg.y >= y && msg.y <= y + h)
		{
			_exit.onButton();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				_exit.clickButton();
				FlushBatchDraw();
				Sleep(STOP_TIME);
				break;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
}
int titleScreen()
{
	int N = 10, M = 10, MINE = 10;
	int Size = 50;
	const int w = 150, h = 45, shadow = 4;

	setbkcolor(BLACK);
	settextcolor(WHITE);
	cleardevice();

	const int itv = 75, x1 = (M * Size - w) / 2, y1 = N * Size / 3 + itv,
		x2 = x1, y2 = N * Size / 3 + 2 * itv,
		x3 = x1, y3 = N * Size / 3 + 3 * itv;
	int res = 0;
	string text = "��ʼ��Ϸ";
	char temp[20] = "";
	strcpy(temp, text.c_str());
	button start(x1, y1, temp);
	text = "���а�";
	strcpy(temp, text.c_str());
	button board(x2, y2, temp);
	text = "�ر�";
	strcpy(temp, text.c_str());
	button _exit(x3, y3, temp);

	BeginBatchDraw();
	start.drawButton();
	board.drawButton();
	_exit.drawButton();
	FlushBatchDraw();
	while (1)
	{
		cleardevice();
		start.drawButton();
		board.drawButton();
		_exit.drawButton();

		MOUSEMSG msg = GetMouseMsg();
		if (msg.x >= x1 && msg.x <= x1 + w && msg.y >= y1 && msg.y <= y1 + h)
		{
			start.onButton();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				start.clickButton();
				FlushBatchDraw();
				Sleep(STOP_TIME);
				res = 1;
				break;
			}
		}
		else if (msg.x >= x2 && msg.x <= x2 + w && msg.y >= y2 && msg.y <= y2 + h)
		{
			board.onButton();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				board.clickButton();
				FlushBatchDraw();
				Sleep(STOP_TIME);
				res = 2;
				break;
			}
		}
		else if (msg.x >= x3 && msg.x <= x3 + w && msg.y >= y3 && msg.y <= y3 + h)
		{
			_exit.onButton();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				_exit.clickButton();
				FlushBatchDraw();
				Sleep(STOP_TIME);
				res = 3;
				break;
			}
		}

		FlushBatchDraw();
	}
	EndBatchDraw();
	return res;
}
