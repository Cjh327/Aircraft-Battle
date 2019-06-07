#pragma once
#include "GameObject.h"
#include "CPlane.h"

#define PLANE_WIDTH			120		// δ����ս��ͼ���
#define PLANE_HEIGHT		90		// δ����ս��ͼ���
#define PLANE_X				400		// ս����ʼλ��X
#define PLANE_Y				300		// ս����ʼλ��Y
#define PLANE_SPEED			30		// ս��Ĭ���ٶ�
#define PLANE_DAMAGE		1		// ս��Ĭ���˺�
#define PLANE_HP			10		// ս��Ĭ������

//ս����
class CMyPlane :public CPlane {
private:
	static CImageList images;
public:
	CMyPlane();							// ���캯��
	BOOL Draw(CDC* pDC, BOOL bPause);	// ���ƺ���
	static BOOL LoadImage();			// ����ͼ��
	CRect GetRect();					// ��д��ȡ��������
};
