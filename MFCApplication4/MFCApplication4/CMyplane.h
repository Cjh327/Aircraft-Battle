#pragma once
#include "CGameObject.h"

//����ս��ͼ���
#define PLANE_WIDTH 120
//����ս��ͼ���
#define PLANE_HEIGHT 150
//δ����ս��ͼ���
#define PLANE1_WIDTH 120
//δ����ս��ͼ���
#define PLANE1_HEIGHT 90
//������ս��ͼ���
#define PLANE_PRO_WIDTH 165
//������ս��ͼ���
#define PLANE_PRO_HEIGHT 166
//ս����ʼλ��X
#define PLANE_X 400
//ս����ʼλ��Y
#define PLANE_Y 300

class CMyplane : public CGameObject
{
private:
	static CImageList images;//�洢����ս��ͼƬ
	static CImageList images1;//�洢δ����ս��ͼƬ
	static CImageList imagespro;//�洢������ͼƬ
	int index;//���Ҫ��ʾ��ս��ͼƬ�±���������ս���Ƿ��������
	int progress;

public:
	//����ս��ͼ��
	static BOOL LoadImage();
};

