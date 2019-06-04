#include "StdAfx.h"
#include "MyPlane.h"
#include "Resource.h"
#include <iostream>

//战机类实现

//静态图像链表
CImageList CMyPlane::images;
CImageList CMyPlane::images1;
CImageList CMyPlane::imagespro;

CMyPlane::CMyPlane(bool isUpdate) : CPlane(PLANE_HP, PLANE_DAMAGE, 0, 0) {
	index = isUpdate ? 1 : 0;
	mPoint.x = PLANE_X;
	mPoint.y = PLANE_Y;
	progress = 0;
}

CMyPlane::~CMyPlane(void) {}


//绘制战机
BOOL CMyPlane::Draw(CDC* pDC, BOOL bPause, BOOL isProtect) {
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

//加载战机图像
BOOL CMyPlane::LoadImage() {
	//加载游戏对象的图标对象
	CBitmap me;//升级战机图像
	if (!me.LoadBitmapW(IDB_BMP_ME))
		return FALSE;
	CBitmap me1;//未升级战机图像
	if (!me1.LoadBitmapW(IDB_BMP_ME1))
		return FALSE;
	//创建CImageList对象
	if (!images.Create(PLANE_WIDTH, PLANE_HEIGHT, ILC_COLOR24 | ILC_MASK, 14, 0))//nInitial初始个数
		return FALSE;//cx,cy 图片的宽度
	if (!images1.Create(PLANE1_WIDTH, PLANE1_HEIGHT, ILC_COLOR24 | ILC_MASK, 4, 0))//nInitial初始个数
		return FALSE;//cx,cy 图片的宽度

	//图像链表中加入对象对应的图标对象，之后直接通过该链表访问图标对象
	images.Add(&me, RGB(0, 0, 0));

	images1.Add(&me1, RGB(0, 0, 0));
	return TRUE;
}