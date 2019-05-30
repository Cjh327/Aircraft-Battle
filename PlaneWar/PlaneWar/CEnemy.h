#pragma once
#include "GameObject.h"

//敌机的高度
#define ENEMY_HEIGHT 90
//敌机的宽度
#define ENEMY_WIDTH 120
//敌机飞行速度
#define ENEMY_SPEED 3
//敌机血量
#define ENEMY_HP 1

class CEnemy : public CGameObject
{
private:
	int hp;
	int speed;

protected:
	static CImageList enemyImages; //敌机图像

public:
	CEnemy(int window_width, int window_heigh);
	int getHp() const;
	void decreaseHp(int x);
	bool isAlive() const;
	void setHp(int _hp);

	CRect GetRect();

	//绘制
	BOOL Draw(CDC* pDC, BOOL bPause);
	BOOL Draw(CDC* pDC, int passNum, BOOL bPause);

	//加载敌机图像
	static BOOL LoadImage();
};

