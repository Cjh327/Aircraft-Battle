#pragma once
#include "GameObject.h"
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
	bool isAlive() const;
	void setHp(int _hp);

	CRect GetRect();

	//绘制
	BOOL Draw(CDC* pDC, BOOL bPause);
	BOOL Draw(CDC* pDC, int passNum, BOOL bPause);

	//加载敌机图像
	static BOOL LoadImage();
};

