#include "pch.h"
#include "CMyplane.h"
#include "resource.h"

//静态图像链表
CImageList CMyplane::images;
CImageList CMyplane::images1;
CImageList CMyplane::imagespro;

//加载战机图像
BOOL CMyplane::LoadImage()
{
	//加载游戏对象的图标对象
	CBitmap me;//升级战机图像
	if (!me.LoadBitmapW(IDB_BITMAP_ME))
		return FALSE;
	CBitmap me1;//未升级战机图像
	if (!me1.LoadBitmapW(IDB_BITMAP_ME1))
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