#pragma once
#include "GameObject.h"
#include "CPlane.h"

#define ENEMY_HEIGHT	90		// 敌机的高度
#define ENEMY_WIDTH		120		// 敌机的宽度
#define ENEMY_SPEED		3		// 敌机飞行速度
#define ENEMY_HP		1		// 敌机血量
#define ENEMY_DAMAGE	1		// 敌机伤害
#define ENEMY_SCORE		10		// 敌机分数

class CEnemy : public CPlane
{
private:
	int score;
protected:
	static CImageList enemyImages; //敌机图像

public:
	CEnemy(int window_width, int window_heigh);
	int getScore() const;

	CRect GetRect();

	//绘制
	BOOL Draw(CDC* pDC, BOOL bPause);
	BOOL Draw(CDC* pDC, int passNum, BOOL bPause);

	//加载敌机图像
	static BOOL LoadImage();
};

