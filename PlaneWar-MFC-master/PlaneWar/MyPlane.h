#pragma once
#include "GameObject.h"

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

//ս����
class CMyPlane :public CGameObject
{
public:
	CMyPlane(BOOL isUpdate);
	~CMyPlane(void);
	//����
	BOOL Draw(CDC* pDC, BOOL bPause, BOOL isProtect);
	BOOL Draw(CDC* pDC, BOOL bPause);
	//����ս��ͼ��
	static BOOL LoadImage();
	static BOOL LoadImageProtect();
	//�õ�ս����������
	CRect GetRect()
	{
		return CRect(mPoint, CPoint(mPoint.x + PLANE_WIDTH, mPoint.y + PLANE_HEIGHT));
	}

	//�����Ƿ�����
	void SetIsUpdate(BOOL isUpdate);
	BOOL GetIsUpdate();

	//�Ƿ���Կ����䵼��
	BOOL isFire();
private:
	static CImageList images;//�洢����ս��ͼƬ
	static CImageList images1;//�洢δ����ս��ͼƬ
	static CImageList imagespro;//�洢������ͼƬ
	int index;//���Ҫ��ʾ��ս��ͼƬ�±���������ս���Ƿ��������
	int progress;
};
