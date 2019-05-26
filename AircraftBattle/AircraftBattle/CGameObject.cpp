#include "pch.h"
#include "CGameObject.h"

CGameObject::CGameObject(int x, int y) {
	point.x = x;
	point.y = y;
}

BOOL CGameObject::loadImage(CImageList& images, UINT bmpID, COLORREF crMask, int cx, int cy, int nInitial)
{
	//加载游戏对象的图标对象
	CBitmap bmp;
	if (!bmp.LoadBitmapW(bmpID))
		return FALSE;

	//创建CImageList对象
	if (!images.Create(cx, cy, ILC_COLOR24 | ILC_MASK, nInitial, 0))//nInitial初始个数
		return FALSE;//cx,cy 图片的宽度

	//图像链表中加入对象对应的图标对象，之后直接通过该链表访问图标对象
	images.Add(&bmp, crMask);

	return TRUE;
}