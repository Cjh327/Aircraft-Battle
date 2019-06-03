#pragma once
#include "GameObject.h"

#define BULLET_HEIGHT 60	//ս���ӵ��߶�Ϊ20
#define BULLET_WIDTH 30		//ս���ӵ���
#define BULLET_SPEED 30		//�ӵ������ٶ�

class CBullet :	public CGameObject
{
private:
	bool fromMe;
	int speedX;
	int speedY;
	int damage;

protected:
	static CImageList bulletImages; // �ӵ�ͼ��
	
public:
	CBullet(int x, int y, int _damage, int _speed, int _speedY, bool _fromMe);
	int getSpeedX() const;
	int getSpeedY() const;
	int getDamage() const;

	CRect GetRect();

	//����
	BOOL Draw(CDC* pDC, BOOL bPause);

	//���صл�ͼ��
	static BOOL LoadImage();

};

