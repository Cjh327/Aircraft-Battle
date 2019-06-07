#include "StdAfx.h"
#include "MyPlane.h"
#include "Resource.h"
#include <iostream>

/* 静态图像链表 */
CImageList CMyPlane::images;

/* 构造函数 */
CMyPlane::CMyPlane() : CPlane(PLANE_HP, PLANE_DAMAGE, 0, 0) {
	mPoint.x = PLANE_X;
	mPoint.y = PLANE_Y;
}

/* 绘制战机 */
BOOL CMyPlane::Draw(CDC* pDC, BOOL bPause) {
	if (bPause == 0) {
		return images.Draw(pDC, 0, mPoint, ILD_TRANSPARENT);
	}
	return FALSE;
}

/* 加载战机图像 */
BOOL CMyPlane::LoadImage() {
	CBitmap me1;
	if (!me1.LoadBitmapW(IDB_BMP_ME1))
		return FALSE;
	if (!images.Create(PLANE_WIDTH, PLANE_HEIGHT, ILC_COLOR24 | ILC_MASK, 4, 0))
		return FALSE;
	
	images.Add(&me1, RGB(0, 0, 0));
	return TRUE;
}

/* 获取矩形区域 */
CRect CMyPlane::GetRect() {
	return CRect(mPoint, CPoint(mPoint.x + PLANE_WIDTH, mPoint.y + PLANE_HEIGHT));
}