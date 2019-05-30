#pragma once
#include "GameObject.h"

#define BULLET_HEIGHT 60	//ս���ӵ��߶�Ϊ20
#define BULLET_WIDTH 30		//ս���ӵ���
#define BULLET_SPEED 30		//�ӵ������ٶ�

class CBullet :	public CGameObject
{
private:
	int speed;
	int damage;

protected:
	static CImageList bulletImages; // �ӵ�ͼ��
	
public:
	CBullet(int x, int y, int _damage, int _speed = BULLET_SPEED);
	int getSpeed() const;
	int getDamage() const;

	CRect GetRect();

	//����
	BOOL Draw(CDC* pDC, BOOL bPause);

	//���صл�ͼ��
	static BOOL LoadImage();

};

