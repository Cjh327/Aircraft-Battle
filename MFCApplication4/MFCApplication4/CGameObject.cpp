#include "pch.h"
#include "CGameObject.h"

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