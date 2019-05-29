#pragma once
#include "GameObject.h"

//ս���ӵ��߶�Ϊ20
#define BULLET_HEIGHT 60

//ս���ӵ���
#define BULLET_WIDTH 30

//�ӵ������ٶ�
#define BULLET_SPEED 30

class CBullet :	public CGameObject
{
private:
	int speed;

protected:
	static CImageList bulletImages; // �ӵ�ͼ��
	
public:
	CBullet(int x = 0, int y = 0, int _speed = BULLET_SPEED);
	int getSpeed() const;

	CRect GetRect();

	//����
	BOOL Draw(CDC* pDC, BOOL bPause);

	//���صл�ͼ��
	static BOOL LoadImage();

};

