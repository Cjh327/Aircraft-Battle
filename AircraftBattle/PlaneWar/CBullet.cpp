#include "stdafx.h"
#include "CBullet.h"
#include "resource.h"

CImageList CBullet::myBulletImages;		// 战机子弹图像
CImageList CBullet::enemyBulletImages;	// 敌机子弹图像

CBullet::CBullet(int x, int y, int _damage, int _speedX, int _speedY, bool _fromMe, int _index) {
	mPoint.x = x;
	mPoint.y = y;
	speedX = _speedX;
	speedY = _speedY;
	damage = _damage;
	fromMe = _fromMe;
	index = _index;
}

bool CBullet::getFromMe() const {
	return fromMe;
}

int CBullet::getSpeedX() const {
	return speedX;
}

int CBullet::getSpeedY() const {
	return speedY;
}

int CBullet::getDamage() const {
	return damage;
}

CRect CBullet::GetRect() {
	return CRect(mPoint, CPoint(mPoint.x + BULLET_WIDTH, mPoint.y + BULLET_HEIGHT));
}

//绘制
BOOL CBullet::Draw(CDC* pDC, BOOL bPause) {
	if (bPause == 0) {
		mPoint.y -= speedY;
		mPoint.x -= speedX;
		if (fromMe) {
			return myBulletImages.Draw(pDC, index, mPoint, ILD_TRANSPARENT);
		}
		else {
			return enemyBulletImages.Draw(pDC, index, mPoint, ILD_TRANSPARENT);
		}
	}
	else {
		return FALSE;
	}
}

//加载敌机图像
BOOL CBullet::LoadImage() {
	CGameObject::LoadImage(myBulletImages, IDB_BMP_BOMB1, RGB(0, 0, 0), BULLET_WIDTH, BULLET_WIDTH, 15);
	CGameObject::LoadImage(enemyBulletImages, IDB_BMP_BALLDOWN, RGB(0, 0, 0), 15, 40, 5);
	return TRUE;
}
