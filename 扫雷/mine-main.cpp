#include "mine.h"
int main()
{
	const int a = 500, b = 550;//��ʼ���洰�ڵĴ�С
	bool initClose = false;//������Ϸǰ�رճ�ʼ���棬��¼�Ƿ�ر�
	initgraph(a, b, NOMINIMIZE);//�򿪳�ʼ����
	while (1)
	{
		if (initClose)//��������Ϸ�ر���ԭ���ĳ�ʼ���棬ѭ����ֱ�Ӵ�
		{
			initgraph(a, b, NOMINIMIZE);
			initClose = false;
		}
		int choice = titleScreen();//��ʼ���棬����ֵ�������İ�ť
		if (choice == 1)//ѡ��ʼ��Ϸ
		{
			while (1)
			{
				int selection = selectDfct();//ѡ���ѶȽ��棬����ֵ��������ͬ�ѶȰ�ť
				
				if (selection == 1)//Ĭ�ϳ����Ѷ�
				{
					closegraph();//�ص���һ��ʼ����
					initClose = true;
					myMine tempGame;
					tempGame.game();
				}
				else if (selection == 2)//�м��Ѷ�
				{
					closegraph();//�ص���һ��ʼ����
					initClose = true;
					myMine tempGame(16, 16, 40, 30);
					tempGame.game();
				}
				else if (selection == 3)//�߼��Ѷ�
				{
					closegraph();//�ص���һ��ʼ����
					initClose = true;
					myMine tempGame(16, 40, 99, 25);
					tempGame.game();
				}
				else if (selection == 4)//�Զ����Ѷ�
				{
					int n = 0, m = 0, num = 0;//��¼����ĳ��������
					bool noInput = false;//��¼�Ƿ�û������
					while (1)
					{
						n = 0, m = 0, num = 0;
						char indexes[20] = "";
						int k = 0;
						InputBox(indexes, 20, "������߶ȡ���ȡ�����(�ո���)", "ɨ��,��Χ[1,60],[1,60]", 0, 0, 0, 0);
						if (strlen(indexes) == 0)//û������
						{
							noInput = true;
							break;
						}
						for (int i = 0; i < 20; )//������������
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
						if (n >= 1 && m >= 1 && n <= 60 && m <= 60 && num < n * m)//��֤��������ݺ���
							break;
					}
					if (noInput == false)//�������˲���������Ϸ
					{
						myMine tempGame(n, m, num, 25);
						tempGame.game();
					}
				}
				if (selection)//�����ѡ��Ϳ��Խ���ѡ���ѶȵĽ�����
					break;
			}
			
		}
		else if (choice == 2)//�������а����
			board();
		else if (choice == 3)//�˳�����
			break;
	}
	closegraph();
	return 0;;
}