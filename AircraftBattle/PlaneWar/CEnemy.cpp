#include "stdafx.h"
#include "CEnemy.h"
#include "resource.h"

//æ≤Ã¨ÕºœÒ¡–±Ì
CImageList CEnemy::enemyImages;

CEnemy::CEnemy(int window_width, int window_height, int _idx) {
	mPoint.x = rand() % window_width;
	mPoint.y = 0;
	index = _idx;
	if (index == 1) {
		hp = ENEMY_HP;
		damage = ENEMY_DAMAGE;
		speedX = rand() % 3;
		if (rand() % 2 == 0) {
			speedX = -speedX;
		}
		speedY = ENEMY_SPEED;
		score = ENEMY_SCORE;
	}
	else if (index == 2) {
		hp = ENEMY_HP + 1;
		damage = ENEMY_DAMAGE + 1;
		speedX = rand() % 3;
		if (rand() % 2 == 0) {
			speedX = -speedX;
		}
		speedY = ENEMY_SPEED;
		score = ENEMY_SCORE + 10;
	}
	else {
		ASSERT(0);
	}
}

int CEnemy::getScore() const {
	return score;
}

int CEnemy::getIndex() const {
	return index;
}

BOOL CEnemy::Draw(CDC* pDC, BOOL bPause) {
	if (bPause == 0) {
		mPoint.x += speedX;
		mPoint.y += speedY;
		enemyImages.Draw(pDC, index, mPoint, ILD_TRANSPARENT);
		return TRUE;
	}
	else return FALSE;
}

//º”‘ÿÕºœÒ
BOOL CEnemy::LoadImage() {
	CBitmap enemyBmp;
	if (!enemyBmp.LoadBitmapW(IDB_BMP_ENEMYDOWN))
		return FALSE;
	if (!enemyImages.Create(ENEMY_WIDTH, ENEMY_HEIGHT, ILC_COLOR24 | ILC_MASK, 5, 0))
		return FALSE;
	enemyImages.Add(&enemyBmp, RGB(0, 0, 0));

	return TRUE;
}

CRect CEnemy::GetRect() {
	return CRect(mPoint, CPoint(mPoint.x + ENEMY_WIDTH, mPoint.y + ENEMY_HEIGHT));
}