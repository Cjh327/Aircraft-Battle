#pragma once
#include "GameObject.h"

//战机子弹高都为20
#define BULLET_HEIGHT 60

//战机子弹宽
#define BULLET_WIDTH 30

//子弹飞行速度
#define BULLET_SPEED 30

class CBullet :	public CGameObject
{
private:
	int speed;

protected:
	static CImageList bulletImages; // 子弹图像
	
public:
	CBullet(int x = 0, int y = 0, int _speed = BULLET_SPEED);
	int getSpeed() const;

	CRect GetRect();

	//绘制
	BOOL Draw(CDC* pDC, BOOL bPause);

	//加载敌机图像
	static BOOL LoadImage();

};

