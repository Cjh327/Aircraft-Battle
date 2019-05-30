#pragma once
#include "GameObject.h"

#define BULLET_HEIGHT 60	//战机子弹高都为20
#define BULLET_WIDTH 30		//战机子弹宽
#define BULLET_SPEED 30		//子弹飞行速度

class CBullet :	public CGameObject
{
private:
	int speed;
	int damage;

protected:
	static CImageList bulletImages; // 子弹图像
	
public:
	CBullet(int x, int y, int _damage, int _speed = BULLET_SPEED);
	int getSpeed() const;
	int getDamage() const;

	CRect GetRect();

	//绘制
	BOOL Draw(CDC* pDC, BOOL bPause);

	//加载敌机图像
	static BOOL LoadImage();

};

