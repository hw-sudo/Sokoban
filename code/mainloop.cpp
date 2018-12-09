#include"founction.h"

void mainloop()
{

	int level;//��ǰ�ؿ�
	int level_option;//ѡ��Ĺؿ�
	int scenes;//����
	char option;//����ָ��
	int isEnd;//�Ƿ����

			  //��ʼ������
	level = 0;//��ʼ����ǰ�ؿ�Ϊ��һ�أ���0���𣬷�ΧΪ0-maps_num��
	level_option = 1;//��ʼ��ѡ��ؿ�Ϊ��һ�أ���1����
	scenes = 0;//��ʼ������Ϊ������
	isEnd = 0;//��ʼ�������жϱ���Ϊ0��false��

	//��ʼ��Ϣѭ��
	while (is_run()) {//ֻҪ����û�йرգ�����ѭ��

			   //�����ӡ
		switch (scenes) {
		case 0:
			//��ӡ������
			main_interface1();
			break;
		case 1:
			//��ӡ���˵�2
			main_interface2();
			break;
		case 2:
			selectLevel(level_option);
			break;
		default:
			break;
		}

		//��������
		if (scenes < 3) {
			option = getch();//��ȡ��������
			option = tolower(option);//�����������ĸ���ΪСд
		}

		//�¼��ж�
		switch (scenes) {
		case 0://�������¼��ж�
			if (option == 's')//�������Ϊ's',��������˵�2
				scenes = 1;
			else if (option == 27) {//�������Ϊesc��27�������˳���Ϸ
				isEnd = 1;
			}
			break;
		case 1://���˵�2�¼��ж�
			if (option == 'r' || option == 27)//�����ϼ��˵�
				scenes = 0;
			else if (option == 'a') {//�ӵ�һ�ؿ�ʼ��Ϸ
				scenes = 3;
			}
			else if (option == 'x') {//����ؿ�ѡ�����
				scenes = 2;
			}
			break;
		case 2://�ؿ�ѡ������¼��ж�
			   //���level_option����1���С1�����level_optionС��maps_num������1��������ж��Է�ֹԽ��
			if ((option == 'a') && level_option > 1)
				level_option--;
			else if ((option == 'd') && level_option < maps_num)
				level_option++;
			else if ((option == 13 || option == 32)) {//�������Ϊ�ո�32����س���13�������ѡ��Ĺؿ�
				level = level_option - 1;//����ǰ�ؿ�����Ϊѡ��Ĺؿ������Ӧ��ϵΪ level = level_option - 1
				scenes = 4;
			}
			else if (option == 27)
				scenes = 1;
			break;
		case 3://��ͷ��ʼ
			level = 0;
			scenes = gameloop(level);//������Ϸ
			break;
		case 4://��ʼ��ǰ�ؿ�
			scenes = gameloop(level);
			break;
		case 5://������һ��
			level++;
			scenes = 4;
			break;
		case 6://ͨ����������
			scenes = 0;
			level = 0;
			break;
		default:
			break;
		}

		if (isEnd)//��������жϱ���Ϊ1��true��������ѭ�������˳���Ϸ
			break;
	}

}

void main_interface1()
{
	PIMAGE pimg_logo = newimage();
	getimage(pimg_logo, "resources\\image\\logo.jpg", 0, 0);

	//����
	cleardevice();

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfillcolor(WHITE);
	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	//���ֱ���ɫ��ע��setbkcolor����Ҳ��ͬʱ�ı����ֱ���ɫ��
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

	setbkmode(TRANSPARENT);
	putimage(280, 50, pimg_logo);
	setfont(48, 0, "����");
	outtextxy(400, 300, "��ʼ(S)");
	outtextxy(380, 400, "�˳�(ESC)");

	delimage(pimg_logo);
}

void main_interface2()
{
	PIMAGE pimg_logo = newimage();
	getimage(pimg_logo, "resources\\image\\logo.jpg", 0, 0);
	//����
	cleardevice();

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfillcolor(WHITE);
	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	//���ֱ���ɫ��ע��setbkcolor����Ҳ��ͬʱ�ı����ֱ���ɫ��
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

	//�������壬��һ������������ĸ߶ȣ����أ����ڶ�������������Ŀ�ȣ��ڶ����������Ϊ0����ʹ��Ĭ�ϱ���ֵ
	setfont(80, 0, "����");

	//Ҫʹ�������ʽ���ַ�����outtextrect
	//�������ֱ�����䷽ʽΪ͸����Ĭ��ΪOPAQUE��͸��
	setbkmode(TRANSPARENT);
	putimage(280, 50, pimg_logo);

	setfont(48, 0, "����");
	outtextxy(360, 300, "��ͷ��ʼ(A)");
	outtextxy(400, 350, "ѡ��(X)");
	outtextxy(400, 400, "����(R)");

	delimage(pimg_logo);
}

void selectLevel(int level)
{
	//����
	cleardevice();

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfillcolor(WHITE);
	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	//���ֱ���ɫ��ע��setbkcolor����Ҳ��ͬʱ�ı����ֱ���ɫ��
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

	//�������壬��һ������������ĸ߶ȣ����أ����ڶ�������������Ŀ�ȣ��ڶ����������Ϊ0����ʹ��Ĭ�ϱ���ֵ
	//����߶�Ϊ12�����൱��С����֣�����9���֣�ʵ�ʵĻ�����Լ���ɰ�
	setfont(48, 0, "����");

	//д���֣�ע�⣺outtextxy��֧��\t \n�����ʽ���õ������ַ��������ַ��ᱻ����
	//Ҫʹ�������ʽ���ַ�����outtextrect
	//�������ֱ�����䷽ʽΪ͸����Ĭ��ΪOPAQUE��͸��
	setbkmode(TRANSPARENT);
	outtextxy(340, 200, "��A��D��ѡ��");
	char str[20];
	sprintf(str, "�ؿ�:%d", level);
	outtextxy(400, 300, str);
	outtextxy(400, 400, "����(ESC)");
}