#include "stdafx.h"
#include "CEnemy.h"
#include "resource.h"

//静态图像列表
CImageList CEnemy::enemyImages;

CEnemy::CEnemy(int window_width, int window_height) : CPlane(ENEMY_HP, ENEMY_DAMAGE, ENEMY_SPEED) {
	mPoint.x = rand() % window_width;
	mPoint.y = 0;
	score = ENEMY_SCORE;
}

int CEnemy::getScore() const {
	return score;
}

//绘制当前敌机位置
BOOL CEnemy::Draw(CDC* pDC, int passNum, BOOL bPause) {
	if (bPause == 0) {
		int index = passNum % 5;
		//敌机位置随机变化,只改变纵坐标，随机数为了让敌机不匀速飞行
		//+ rand() % 10
		mPoint.y += speed;
		enemyImages.Draw(pDC, index, mPoint, ILD_TRANSPARENT);
		return TRUE;
	}
	else return FALSE;
}

BOOL CEnemy::Draw(CDC* pDC, BOOL bPause) {
	if (bPause == 0) {
		//敌机位置随机变化,只改变纵坐标，随机数为了让敌机不匀速飞行
		//+ rand() % 10
		mPoint.y += speed;
		enemyImages.Draw(pDC, 0, mPoint, ILD_TRANSPARENT);
		return TRUE;
	}
	else return FALSE;
}

//加载图像
BOOL CEnemy::LoadImage() {
	//加载游戏对象的图标对象
	CBitmap enemyBmp;
	if (!enemyBmp.LoadBitmapW(IDB_BMP_ENEMYDOWN))
		return FALSE;
	//创建CImageList对象
	if (!enemyImages.Create(ENEMY_WIDTH, ENEMY_HEIGHT, ILC_COLOR24 | ILC_MASK, 5, 0))//nInitial初始个数
		return FALSE;//cx,cy 图片的宽度
	//图像链表中加入对象对应的图标对象，之后直接通过该链表访问图标对象
	enemyImages.Add(&enemyBmp, RGB(0, 0, 0));

	return TRUE;
}

CRect CEnemy::GetRect() {
	return CRect(mPoint, CPoint(mPoint.x + ENEMY_WIDTH, mPoint.y + ENEMY_HEIGHT));
}