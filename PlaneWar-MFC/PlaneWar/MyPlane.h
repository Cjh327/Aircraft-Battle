#pragma once
#include "GameObject.h"

#define PLANE_WIDTH 120			// ����ս��ͼ���
#define PLANE_HEIGHT 150		// ����ս��ͼ���
#define PLANE1_WIDTH 120		// δ����ս��ͼ���
#define PLANE1_HEIGHT 90		// δ����ս��ͼ���
#define PLANE_PRO_WIDTH 165		// ������ս��ͼ���
#define PLANE_PRO_HEIGHT 166	// ������ս��ͼ���
#define PLANE_X 400				// ս����ʼλ��X
#define PLANE_Y 300				// ս����ʼλ��Y
//#define PLANE_SPEED 30			// ս��Ĭ���ٶ�
#define PLANE_DAMAGE 1			// ս��Ĭ���˺�
#define PLANE_HP 10				// ս��Ĭ������

//ս����
class CMyPlane :public CGameObject
{
private:
	int damage;
	int hp;

public:
	CMyPlane(bool isUpdate = false, int _damage = PLANE_DAMAGE, int _hp = PLANE_HP);
	~CMyPlane(void);

	int getSpeed() const;
	int getDamage() const;

	//����
	BOOL Draw(CDC* pDC, BOOL bPause, BOOL isProtect);
	BOOL Draw(CDC* pDC, BOOL bPause);
	//����ս��ͼ��
	static BOOL LoadImage();
	static BOOL LoadImageProtect();
	//�õ�ս����������
	CRect GetRect()	{
		return CRect(mPoint, CPoint(mPoint.x + PLANE_WIDTH, mPoint.y + PLANE_HEIGHT));
	}

	//�����Ƿ�����
	void SetIsUpdate(BOOL isUpdate);
	BOOL GetIsUpdate();

	//�Ƿ���Կ����䵼��
	BOOL isFire();
private:
	static CImageList images;//�洢����ս��ͼƬ
	static CImageList images1;//�洢δ����ս��ͼƬ
	static CImageList imagespro;//�洢������ͼƬ
	int index;//���Ҫ��ʾ��ս��ͼƬ�±���������ս���Ƿ��������
	int progress;
};
