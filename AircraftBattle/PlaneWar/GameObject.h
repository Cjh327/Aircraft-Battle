#pragma once
#include "afx.h"

// ��Ϸ����ĸ��࣬������Ϸ���󶼼̳�����
class CGameObject : public CObject
{
public:
	CGameObject(int x = 0, int y = 0);
	virtual ~CGameObject();

	// ���ƶ���
	virtual BOOL Draw(CDC* pDC, BOOL bPause) = 0;

	// ��þ�������
	virtual CRect GetRect() = 0;

	// ������Ͻ�����
	CPoint GetPoint();

	// ��������
	void SetPoint(int x, int y);

protected:
	//���ظ���Ϸ�����Ӧ��ͼ��,ͼ������ǹ������ݣ�ֻ��Ҫ����һ�ݣ�ʹ�þ�̬����
	static BOOL LoadImage(CImageList& imageList, UINT bmpID, COLORREF crMask, int cx, int cy, int nInitial);
protected:
	//��Ϸ�����λ��
	CPoint  mPoint;
};