#pragma once
#include <afx.h>
class CGameObject :	public CObject
{
private:
	CPoint point;
public:

protected:
	//���ظ���Ϸ�����Ӧ��ͼ��,ͼ������ǹ������ݣ�ֻ��Ҫ����һ�ݣ�ʹ�þ�̬����
	static BOOL LoadImage(CImageList& imageList, UINT bmpID, COLORREF crMask, int cx, int cy, int nInitial);
};

