#pragma once
#include <afx.h>
class CGameObject : public CObject
{
protected:
	CPoint point;
public:
	CGameObject(int x, int y);
	//加载该游戏对象对应的图像,图像对象是共有数据，只需要加载一份，使用静态方法
	static BOOL loadImage(CImageList& imageList, UINT bmpID, COLORREF crMask, int cx, int cy, int nInitial);
};

