#include "stdafx.h"
#include "GameObject.h"
// GameObject.cpp : ʵ���ļ�

//��ʼ����Ϸ����λ��
CGameObject::CGameObject(int x, int y) :mPoint(x, y) {}

CGameObject::~CGameObject(){}

CPoint CGameObject::GetPoint() {
	return mPoint;
}

void CGameObject::SetPoint(int x, int y)
{
	mPoint.x = x;
	mPoint.y = y;
}

BOOL CGameObject::LoadImage(CImageList& images, UINT bmpID, COLORREF crMask, int cx, int cy, int nInitial)
{
	//������Ϸ�����ͼ�����
	CBitmap bmp;
	if (!bmp.LoadBitmapW(bmpID))
		return FALSE;

	//����CImageList����
	if (!images.Create(cx, cy, ILC_COLOR24 | ILC_MASK, nInitial, 0))//nInitial��ʼ����
		return FALSE;//cx,cy ͼƬ�Ŀ��

	//ͼ�������м�������Ӧ��ͼ�����֮��ֱ��ͨ�����������ͼ�����
	images.Add(&bmp, crMask);

	return TRUE;
}