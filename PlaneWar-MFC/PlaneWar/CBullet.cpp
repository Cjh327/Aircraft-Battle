#include "stdafx.h"
#include "CBullet.h"
#include "resource.h"

CImageList CBullet::bulletImages; // ×Óµ¯Í¼Ïñ

CBullet::CBullet(int x, int y, int _speed) {
	mPoint.x = x;
	mPoint.y = y;
	speed = _speed;
}

int CBullet::getSpeed() const {
	return speed;
}

CRect CBullet::GetRect() {
	return CRect(mPoint, CPoint(mPoint.x + BULLET_WIDTH, mPoint.y + BULLET_HEIGHT));
}

//»æÖÆ
BOOL CBullet::Draw(CDC* pDC, BOOL bPause) {
	if (bPause == 0) {
		mPoint.y -= speed;
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
