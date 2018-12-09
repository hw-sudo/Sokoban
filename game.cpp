#include"founction.h"

void game_face(int level, int step_num, int restep_num);
void pause();
void lastlevel();
void passlevel(int step_num);


int gameloop(int level)
{
	mciSendString(TEXT("open Boxmove.wav alias Boxmove"), NULL, 0, NULL);

	PIMAGE pimg_wall = newimage();
	PIMAGE pimg_land = newimage();
	PIMAGE pimg_BoxYellow = newimage();
	PIMAGE pimg_BoxRed = newimage();
	PIMAGE pimg_aim = newimage();
	PIMAGE pimg_ManUP1 = newimage();
	PIMAGE pimg_ManUP2 = newimage();
	PIMAGE pimg_ManDOWN1 = newimage();
	PIMAGE pimg_ManDOWN2 = newimage();
	PIMAGE pimg_ManRIGHT1 = newimage();
	PIMAGE pimg_ManRIGHT2 = newimage();
	PIMAGE pimg_ManLEFT1 = newimage();
	PIMAGE pimg_ManLEFT2 = newimage();
	PIMAGE pimg_black = newimage();

	getimage(pimg_wall, "resources\\image\\wall.jpg", 0, 0);
	getimage(pimg_land, "resources\\image\\land.jpg", 0, 0);
	getimage(pimg_BoxYellow, "resources\\image\\BoxYellow.jpg", 0, 0);
	getimage(pimg_BoxRed, "resources\\image\\BoxRed.jpg", 0, 0);
	getimage(pimg_aim, "resources\\image\\aim.jpg", 0, 0);
	getimage(pimg_ManUP1, "resources\\image\\ManUP1.jpg", 0, 0);
	getimage(pimg_ManUP2, "resources\\image\\ManUP2.jpg", 0, 0);
	getimage(pimg_ManDOWN1, "resources\\image\\ManDOWN1.jpg", 0, 0);
	getimage(pimg_ManDOWN2, "resources\\image\\ManDOWN2.jpg", 0, 0);
	getimage(pimg_ManRIGHT1, "resources\\image\\ManRIGHT1.jpg", 0, 0);
	getimage(pimg_ManRIGHT2, "resources\\image\\ManRIGHT2.jpg", 0, 0);
	getimage(pimg_ManLEFT1, "resources\\image\\ManLEFT1.jpg", 0, 0);
	getimage(pimg_ManLEFT2, "resources\\image\\ManLEFT2.jpg", 0, 0);
	getimage(pimg_black, "resources\\image\\black.jpg", 0, 0);
	
	//��������

	int x, y;//x ������, y ������
	int wide;//��ͼ����ƫ�ƿ��
	int high;//��ͼ����ƫ�Ƹ߶�
	int count;//������
	char option;//��Ϸ�����ж�ȡ������Ϣ
	int scenes;//��ǰ����
	int isEnd;//�����жϱ���
	int reValue;//����ֵ�������泡��

				//������Ϸ��ͼ
	char map[50][50] = { 0 };

	//���������飬��¼�յ�����
	int aim_x[50] = { 0 }, aim_y[50] = { 0 }, xnum, ynum;

	int restep_num;//��¼ʣ�೷������
	int step_num;//��¼�����ܲ���
	int isUndo;//��¼�Ƿ�����
	int lastStep_num;//��¼��һ��������ǰ���ߵĲ���
	int box_x, box_y;//��¼��һ��������ǰ�������
	int box_nx, box_ny;//��¼��һ�������Ӻ��������
	int last_x, last_y;//��¼��һ��������ǰ��ɫ������

					   //��Ϸ��ʼ��

					   //��ʼ������
	count = 0;
	wide = 0;
	step_num = 0;
	restep_num = 3;
	option = NULL;
	xnum = ynum = 0;
	isUndo = 0;
	scenes = 0;
	reValue = 0;
	isEnd = 0;

	//�������ֶ���
	MUSIC mus;
	mus.OpenFile("resources\\music\\Boxmove.wav"); // ���ļ�

	//��ȡ��ͼ
	LoadMap(level,map);

	//�����ͼ���
	wide = strlen(map[0]);

	//��ʼ����ʼλ��
	for (int i = 0; i < 20; i++) {
		for (int t = 0; map[i][t] != '\0'; t++)
			if (map[i][t] == '@') {
				x = i;
				y = t;
				i = 99;
				break;
			}
	}

	//Ѱ���յ�����
	for (int i = 2; i < 20; i++) {
		for (int t = 2; map[i][t] != '\0'; t++) {
			if (map[i][t] == 'X' || map[i][t] == 'Q') {
				aim_x[xnum] = i;
				aim_y[ynum] = t;
				xnum++;
				ynum++;
			}
			if (map[i][1] == '|') {
				high = i;
				i = 99;
				break;
			}
		}
	}

	//�����ͼ����ƫ����
	high = (13 - high) / 2;
	wide = (16 - strlen(map[0])) / 2;

	//��Ϸ��ѭ��
	for (; is_run(); delay_fps(60)) {

		//ÿ����һ֡������������1��ÿ������60����
		if (count > 60)
			count = 0;
		count+=2;
		
		//�����ӡ
		switch (scenes) {
		case 0:
			//��Ϸ����
			game_face(level, step_num,restep_num);

			for (int i = 1; i <= 17; i++)
			{
				for (int t = 0; t < strlen(map[0]); t++)
				{
					if (map[i][t] == '|' || map[i][t] == '=')
						putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_black);
					if (map[i][t] == ' ')
						putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_land);
					if (map[i][t] == 'O')
						putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_BoxYellow);
					if (map[i][t] == 'Q')
						putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_BoxRed);
					if (map[i][t] == '#')
						putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_wall);
					if (map[i][t] == 'X')
						putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_aim);
					if (map[i][t] == '@')
						if (option == 'd' )
						{
							if (count > 30 )
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManRIGHT1);
							else
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManRIGHT2);
						}
						else if (option == 'a' )
						{
							if (count > 30)
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManLEFT1);
							else
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManLEFT2);
						}
						else if (option == 'w')
						{
							if (count > 30)
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManUP1);
							else
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManUP2);
						}
						else
						{
							if (count > 30)
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManDOWN1);
							else
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManDOWN2);
						}
				}
				if (map[i][1] == '|')
					break;
			}
			break;
		case 1:
			//��ͣ����
			pause();
			break;
		case 2:
			//���ؽ���
			if(level==maps_num-1)
				lastlevel();
			else
				passlevel(step_num);
			break;
		default:
			break;
		}

		if (kbhit()) {
			//��������
			option = getch();//��ȡ��������
			option = tolower(option);//�����������ĸ���ΪСд

									 //�¼��ж�
			switch (scenes) {
			case 0:
				if (option == 's') {//�����ƶ�
									//��ǰ���ǿյػ��߿�Ŀ�ĵ�ʱ�����ƶ���ȥ
					if (map[x + 1][y] == ' ' || map[x + 1][y] == 'X') {
						map[x][y] = ' ';//����ɫ��ǰλ�ø���Ϊ�յأ������λ��Ӧ��ΪĿ�ĵ����ǽ��ں���������д���
						x++;//���½�ɫλ��
						map[x][y] = '@';//���µ�λ�ø���Ϊ��ɫ
						step_num++;//�ƶ�������1
					}
					//���ǰ����������������ͬ�������һλ�ò�Ϊǽ��������ʱ�����Խ���ǰ�����ƶ���ȥ
					else if ((map[x + 1][y] == 'O' || map[x + 1][y] == 'Q') && map[x + 2][y] != 'O' && map[x + 2][y] != 'Q' && map[x + 2][y] != '#') {
						map[x][y] = ' ';

						//��¼�ƶ�����ǰ��ɫ������
						last_x = x;
						last_y = y;

						x++;

						//��¼�ƶ�����ǰ���ӵ�����
						box_nx = x;
						box_ny = y;

						map[x][y] = '@';
						map[x + 1][y] = 'O';//�ڽ�ɫ�ƶ��������һλ�ϸ���Ϊ���ӣ������λ��ΪĿ�ĵأ���������ʾ��̬���ǽ��ں���������д���
						isUndo = 1;//�������жϱ�������Ϊ1��true����ʾ��ǰ����λ��Ϊ�ƶ����λ�ã�������

								   //��¼���һ�α��ƶ����ӵ�����
						box_x = x + 1;
						box_y = y;

						lastStep_num = step_num;//��¼��һ��������ǰ���ߵĲ���
						step_num++;

						mus.Play(0);//�����ƶ����ӵ���Ƶ
					}
				}
				else if (option == 'w') {//�����ƶ�
					if (map[x - 1][y] == ' ' || map[x - 1][y] == 'X') {
						map[x][y] = ' ';
						x--;
						map[x][y] = '@';
						step_num++;
					}
					else if ((map[x - 1][y] == 'O' || map[x - 1][y] == 'Q') && map[x - 2][y] != 'O' && map[x - 2][y] != 'Q' && map[x - 2][y] != '#') {
						map[x][y] = ' ';

						//��¼�ƶ�����ǰ��ɫ������
						last_x = x;
						last_y = y;

						x--;

						//��¼�ƶ�����ǰ���ӵ�����
						box_nx = x;
						box_ny = y;

						map[x][y] = '@';
						map[x - 1][y] = 'O';//�ڽ�ɫ�ƶ��������һλ�ϸ���Ϊ���ӣ������λ��ΪĿ�ĵأ���������ʾ��̬���ǽ��ں���������д���
						isUndo = 1;//�������жϱ�������Ϊ1��true����ʾ��ǰ����λ��Ϊ�ƶ����λ�ã�������

								   //��¼���һ�α��ƶ����ӵ�����
						box_x = x - 1;
						box_y = y;

						lastStep_num = step_num;//��¼��һ��������ǰ���ߵĲ���
						step_num++;

						mus.Play(0);//�����ƶ����ӵ���Ƶ
					}
				}
				else if (option == 'a') {//�����ƶ�
					if (map[x][y - 1] == ' ' || map[x][y - 1] == 'X') {
						map[x][y] = ' ';
						y--;
						map[x][y] = '@';
						step_num++;
					}
					else if ((map[x][y - 1] == 'O' || map[x][y - 1] == 'Q') && map[x][y - 2] != 'O' && map[x][y - 2] != 'Q' && map[x][y - 2] != '#') {
						map[x][y] = ' ';

						//��¼�ƶ�����ǰ��ɫ������
						last_x = x;
						last_y = y;

						y--;

						//��¼�ƶ�����ǰ���ӵ�����
						box_nx = x;
						box_ny = y;

						map[x][y] = '@';
						map[x][y - 1] = 'O';//�ڽ�ɫ�ƶ��������һλ�ϸ���Ϊ���ӣ������λ��ΪĿ�ĵأ���������ʾ��̬���ǽ��ں���������д���
						isUndo = 1;//�������жϱ�������Ϊ1��true����ʾ��ǰ����λ��Ϊ�ƶ����λ�ã�������

								   //��¼���һ�α��ƶ����ӵ�����
						box_x = x;
						box_y = y - 1;

						lastStep_num = step_num;//��¼��һ��������ǰ���ߵĲ���
						step_num++;

						mus.Play(0);//�����ƶ����ӵ���Ƶ
					}
					break;
				}
				else if (option == 'd') {//�����ƶ�
					if (map[x][y + 1] == ' ' || map[x][y + 1] == 'X') {
						map[x][y] = ' ';
						y++;
						map[x][y] = '@';
						step_num++;
					}
					else if ((map[x][y + 1] == 'O' || map[x][y + 1] == 'Q') && map[x][y + 2] != 'O' && map[x][y + 2] != 'Q'&&map[x][y + 2] != '#') {
						map[x][y] = ' ';

						//��¼�ƶ�����ǰ��ɫ������
						last_x = x;
						last_y = y;

						y++;

						//��¼�ƶ�����ǰ���ӵ�����
						box_nx = x;
						box_ny = y;

						map[x][y] = '@';
						map[x][y + 1] = 'O';//�ڽ�ɫ�ƶ��������һλ�ϸ���Ϊ���ӣ������λ��ΪĿ�ĵأ���������ʾ��̬���ǽ��ں���������д���
						isUndo = 1;//�������жϱ�������Ϊ1��true����ʾ��ǰ����λ��Ϊ�ƶ����λ�ã�������

								   //��¼���һ�α��ƶ����ӵ�����
						box_x = x;
						box_y = y + 1;

						lastStep_num = step_num;//��¼��һ��������ǰ���ߵĲ���
						step_num++;

						mus.Play(0);//�����ƶ����ӵ���Ƶ
					}
				}
				else if (option == 'u') {
					//����һ��
					if (isUndo && restep_num > 0) {

						map[x][y] = ' ';//����ɫ��ǰλ�ø���Ϊ�յأ������λ��Ӧ��ΪĿ�ĵ����ǽ��ں���������д���
										//����ɫλ�ø���Ϊ֮ǰ�洢��λ��
						x = last_x;
						y = last_y;
						map[x][y] = '@';//����ɫ��ԭ����λ�ø���Ϊ@

										//ͬ��������ӵ�λ��
						map[box_x][box_y] = ' ';
						map[box_nx][box_ny] = 'O';

						step_num = lastStep_num;//��ԭ֮ǰ���ߵĲ���

						isUndo = 0;//�������жϱ�������Ϊ0��false����ʾ��ǰ����λ��Ϊ�������λ�ã���ֹ�ٴγ���
						restep_num--;//ʣ��ɳ���������1
					}
				}
				else if (option == 'q') {//���ñ�����Ϸ
					reValue = 4;
					isEnd = 1;
				}
				else if (option == 27) {//����ͣ�˵�
					scenes = 1;
				}
				break;
			case 1:
				if (option == 'r' || option == 27) {//������Ϸ
					scenes = 0;
				}
				else if (option == 'x') {//���뵽�ؿ�ѡ����棬����;�Ƴ��ؿ�ѡ��Ļ����������ǰ��Ϸ����ص����˵�
					reValue = 2;
					isEnd = 1;
				}
				else if (option == 'q') {
					reValue = 4;
					isEnd = 1;
				}
				else if (option == 'n' && level != maps_num - 1) {//�����ǰ�������һ�أ��������һ��
					reValue = 5;
					isEnd = 1;
				}
				else if (option == 'm') {//�������˵�
					reValue = 1;
					isEnd = 1;
				}
				break;
			case 2:
				if (option == 'x') {
					reValue = 2;
					isEnd = 1;
				}
				else if (option == 'q') {
					reValue = 4;
					isEnd = 1;
				}
				else if (option == 'n'&&level != maps_num - 1) {
					reValue = 5;
					isEnd = 1;
				}
				else if (option == 'm') {
					reValue = 1;
					isEnd = 1;
				}
				break;
			default:
				break;
			}
		}

		//�߼�����

		//��ԭ�յ���,����֮ǰû�д��������,�û���һ��Ҫ��ͨ�������ж�֮ǰ���в�����ȷ�ж��Ƿ����
		for (int i = 0; aim_x[i] != 0; i++) {//���μ���յ�����
			if (map[aim_x[i]][aim_y[i]] == ' ')//���Ϊ' '�����Ϊ'X'
				map[aim_x[i]][aim_y[i]] = 'X';
			if (map[aim_x[i]][aim_y[i]] == 'O')//���Ϊ'O'�����Ϊ'Q'
				map[aim_x[i]][aim_y[i]] = 'Q';
		}

		//ͨ�������ж�
		int count = 0;//��¼��ǰ�ж��ٸ����ӵ����յ�����
		for (int i = 0; aim_x[i] != 0; i++) {//���μ���յ�����
			if (map[aim_x[i]][aim_y[i]] == 'Q')//�����λ��Ϊ����
				count++;//��������1
		}
		if (count == xnum) {//���count�����յ�������Ŀ�����ʾͨ��
			scenes = 2;
		}

		if (isEnd)
			break;
	}

	mus.Close(); // �ر���Ƶ�ļ�

	delimage(pimg_wall);
	delimage(pimg_land);
	delimage(pimg_BoxYellow);
	delimage(pimg_BoxRed);
	delimage(pimg_aim);
	delimage(pimg_ManUP1);
	delimage(pimg_ManUP2);
	delimage(pimg_ManDOWN1);
	delimage(pimg_ManDOWN2);
	delimage(pimg_ManRIGHT1);
	delimage(pimg_ManRIGHT2);
	delimage(pimg_ManLEFT1);
	delimage(pimg_ManLEFT2);
	delimage(pimg_black);
	return reValue;
}

void game_face(int level, int step_num, int restep_num)
{
	cleardevice();

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfillcolor(WHITE);
	bar(750, 0, 755, 700);

	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));
	setfont(48, 0, "����");
	setbkmode(TRANSPARENT);
	char str[20];
	sprintf(str, "��%d��", level + 1);
	outtextxy(800, 100, str);
	setfont(24, 0, "����");
	sprintf(str, "������%d", step_num);
	outtextxy(780, 250, str);

	sprintf(str, "ʣ�೷��������%d", restep_num);
	outtextxy(780, 300, str);

	outtextxy(780, 350, "���汾��(Q)");
	outtextxy(780, 400, "����(U)");
	outtextxy(780, 450, "��ͣ(ESC)");
}

void pause()
{
	cleardevice();

	setfillcolor(WHITE);
	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));
	setfont(48, 0, "����");
	setbkmode(TRANSPARENT);
	outtextxy(400, 200, "����(R)");

	setfont(40, 0, "����");
	outtextxy(140, 300, "ѡ��(X)");
	outtextxy(320, 300, "����(Q)");
	outtextxy(480, 300, "��һ��(N)");
	outtextxy(700, 300, "���˵�(M)");
}

void lastlevel()
{
	cleardevice();

	setfillcolor(WHITE);
	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));
	setfont(48, 0, "����");
	setbkmode(TRANSPARENT);
	outtextxy(280, 250, "���Ѿ������һ���ˣ�");
}

void passlevel(int step_num)
{
	cleardevice();

	setfillcolor(WHITE);
	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));
	setfont(60, 0, "����");
	setbkmode(TRANSPARENT);
	outtextxy(420, 150, "���أ�");

	setfont(40, 0, "����");
	char str[20];
	sprintf(str, "�����ܼƲ���:%d", step_num);
	outtextxy(350, 250, str);

	setfont(40, 0, "����");
	outtextxy(140, 350, "ѡ��(X)");
	outtextxy(320, 350, "����(Q)");
	outtextxy(480, 350, "��һ��(N)");
	outtextxy(700, 350, "�˵�(M)");
}

void LoadMap(int level,char (*map)[50])
{
	char buffer[256];
	FILE *fp;
	sprintf(buffer, "resources/map/%d.txt", level+1);
	fp = fopen(buffer,"r");
	for(int i=0;;i++)
	{
		fgets(map[i], 256, fp);
		if (map[i][1] == '|')
			break;
	}
	fclose(fp);
}
