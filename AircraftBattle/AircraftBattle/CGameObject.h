#pragma once
#include <afx.h>
class CGameObject : public CObject
{
protected:
	CPoint point;
public:
	CGameObject(int x, int y);
	//���ظ���Ϸ�����Ӧ��ͼ��,ͼ������ǹ������ݣ�ֻ��Ҫ����һ�ݣ�ʹ�þ�̬����
	static BOOL loadImage(CImageList& imageList, UINT bmpID, COLORREF crMask, int cx, int cy, int nInitial);
};

