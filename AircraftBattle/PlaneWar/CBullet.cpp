#include "stdafx.h"
#include "CBullet.h"
#include "resource.h"

CImageList CBullet::bulletImages; // ×Óµ¯Í¼Ïñ

CBullet::CBullet(int x, int y, int _damage, int _speedX, int _speedY, bool _fromMe) {
	mPoint.x = x;
	mPoint.y = y;
	speedX = _speedX;
	speedY = _speedY;
	damage = _damage;
	fromMe = _fromMe;
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

//»æÖÆ
BOOL CBullet::Draw(CDC* pDC, BOOL bPause) {
	if (bPause == 0) {
		mPoint.y -= speedY;
		mPoint.x -= speedX;
		//int index = rand() % 15;
		return bulletImages.Draw(pDC, 2, mPoint, ILD_TRANSPARENT);
	}
	else {
		return FALSE;
	}
}

//¼ÓÔØµÐ»úÍ¼Ïñ
BOOL CBullet::LoadImage() {
	CGameObject::LoadImage(bulletImages, IDB_BMP_BOMB1, RGB(0, 0, 0), BULLET_WIDTH, BULLET_WIDTH, 15);
	return TRUE;
}
