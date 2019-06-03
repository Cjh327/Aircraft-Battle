#pragma once
#include "GameObject.h"

#define BULLET_HEIGHT 60	//战机子弹高都为20
#define BULLET_WIDTH 30		//战机子弹宽
#define BULLET_SPEED 30		//子弹飞行速度

class CBullet :	public CGameObject
{
private:
	bool fromMe;
	int speedX;
	int speedY;
	int damage;
	int index;

protected:
	static CImageList myBulletImages;		// 战机子弹图像
	static CImageList enemyBulletImages;	// 敌机子弹图像
	
public:
	CBullet(int x, int y, int _damage, int _speed, int _speedY, bool _fromMe, int _index);
	int getSpeedX() const;
	int getSpeedY() const;
	int getDamage() const;
	bool getFromMe() const;

	CRect GetRect();

	//绘制
	BOOL Draw(CDC* pDC, BOOL bPause);

	//加载敌机图像
	static BOOL LoadImage();

};

