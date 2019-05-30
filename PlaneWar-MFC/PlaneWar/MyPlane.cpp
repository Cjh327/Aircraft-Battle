#include "StdAfx.h"
#include "MyPlane.h"
#include "Resource.h"
#include <iostream>

//ս����ʵ��

//��̬ͼ������
CImageList CMyPlane::images;
CImageList CMyPlane::images1;
CImageList CMyPlane::imagespro;

CMyPlane::CMyPlane(bool isUpdate, int _damage, int _hp) {
	index = isUpdate ? 1 : 0;
	mPoint.x = PLANE_X;
	mPoint.y = PLANE_Y;
	progress = 0;
	damage = _damage;
	hp = _hp;
}

CMyPlane::~CMyPlane(void) {}

int CMyPlane::getDamage() const {
	return damage;
}

//����ս��
BOOL CMyPlane::Draw(CDC* pDC, BOOL bPause, BOOL isProtect)
{
	if (bPause == 0) {
		if (isProtect == TRUE) {
			CPoint point;
			point.x = mPoint.x - 25;
			point.y = mPoint.y - 30;
			imagespro.Draw(pDC, 0, point, ILD_TRANSPARENT);
		}
		if (index == 1) {
			if (progress < 14) {
				images.Draw(pDC, progress, mPoint, ILD_TRANSPARENT);
				progress++;
			}
			else {
				progress = 0;
				images.Draw(pDC, progress, mPoint, ILD_TRANSPARENT);
			}
		}
		else {
			images1.Draw(pDC, 3, mPoint, ILD_TRANSPARENT);
		}
		return TRUE;
	}
	return FALSE;
}
BOOL CMyPlane::Draw(CDC* pDC, BOOL bPause) {
	if (bPause == 0) {
		return images.Draw(pDC, index, mPoint, ILD_TRANSPARENT);
	}
	return FALSE;
}
//����ս��ͼ��
BOOL CMyPlane::LoadImage()
{
	//������Ϸ�����ͼ�����
	CBitmap me;//����ս��ͼ��
	if (!me.LoadBitmapW(IDB_BMP_ME))
		return FALSE;
	CBitmap me1;//δ����ս��ͼ��
	if (!me1.LoadBitmapW(IDB_BMP_ME1))
		return FALSE;
	//����CImageList����
	if (!images.Create(PLANE_WIDTH, PLANE_HEIGHT, ILC_COLOR24 | ILC_MASK, 14, 0))//nInitial��ʼ����
		return FALSE;//cx,cy ͼƬ�Ŀ��
	if (!images1.Create(PLANE1_WIDTH, PLANE1_HEIGHT, ILC_COLOR24 | ILC_MASK, 4, 0))//nInitial��ʼ����
		return FALSE;//cx,cy ͼƬ�Ŀ��

	//ͼ�������м�������Ӧ��ͼ�����֮��ֱ��ͨ�����������ͼ�����
	images.Add(&me, RGB(0, 0, 0));

	images1.Add(&me1, RGB(0, 0, 0));
	return TRUE;
}
//���ر�����ս��ͼ��
BOOL CMyPlane::LoadImageProtect() {
	//������Ϸ�����ͼ�����
	CBitmap protect;
	if (!protect.LoadBitmapW(IDB_BMP_PROTECT))
		return FALSE;
	//CBitmap protectme2;
	//if (!protectme2.LoadBitmapW(IDB_BMP_PROTECTME2))
	//	return FALSE;
	//����CImageList����
	if (!imagespro.Create(PLANE_PRO_WIDTH, PLANE_PRO_HEIGHT, ILC_COLOR24 | ILC_MASK, 1, 0))//nInitial��ʼ����
		return FALSE;//cx,cy ͼƬ�Ŀ��

	//ͼ�������м�������Ӧ��ͼ�����֮��ֱ��ͨ�����������ͼ�����
	imagespro.Add(&protect, RGB(255, 255, 255));
	//imagespro.Add(&protectme2, RGB(255, 255, 255));
	return TRUE;
}

BOOL CMyPlane::isFire()//�Ƿ���Է��䵼��
{
	return TRUE;
}

void CMyPlane::SetIsUpdate(BOOL isUpdate) {
	this->index = isUpdate;
}
BOOL CMyPlane::GetIsUpdate() {
	return index;
}
