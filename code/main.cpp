//==========================
//�������ƣ���Ģ��
//�汾�ţ�1.0
//�����ˣ�Howard
//==========================
#include"founction.h"

//���ڳߴ�
#define Win_L 1000
#define Win_H 600

int main(void)
{
	ege::setinitmode(ege::INIT_ANIMATION);
	// ͼ�γ�ʼ��
	ege::initgraph(Win_L, Win_H);
	setcaption("��Ģ��"); //�޸Ĵ�������
	// �������ʼ���������Ҫʹ��������Ļ�
	ege::randomize();
	// ������ѭ��
	mainloop();
	// �رջ�ͼ�豸
	ege::closegraph();
	return 0;
}

