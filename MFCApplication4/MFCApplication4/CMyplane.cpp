#include "pch.h"
#include "CMyplane.h"
#include "resource.h"

//��̬ͼ������
CImageList CMyplane::images;
CImageList CMyplane::images1;
CImageList CMyplane::imagespro;

//����ս��ͼ��
BOOL CMyplane::LoadImage()
{
	//������Ϸ�����ͼ�����
	CBitmap me;//����ս��ͼ��
	if (!me.LoadBitmapW(IDB_BITMAP_ME))
		return FALSE;
	CBitmap me1;//δ����ս��ͼ��
	if (!me1.LoadBitmapW(IDB_BITMAP_ME1))
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