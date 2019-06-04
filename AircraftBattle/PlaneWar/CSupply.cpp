#include "stdafx.h"
#include "CSupply.h"
#include "resource.h"

CImageList CSupply::images;

CSupply::CSupply(int WINDOWS_WIDTH, int WINDOWS_HEIGHT) {
	windowWidth = WINDOWS_WIDTH;
	windowHeight = WINDOWS_HEIGHT;
	mPoint.x = rand() % WINDOWS_WIDTH;
	mPoint.y = 0;
	speedX = rand() % 3;
	if (rand() % 2 == 0) {
		speedX = -speedX;
	}
	speedY = 3;
	hp = 2;
}

int CSupply::getHp() const {
	return hp;
}

BOOL CSupply::Draw(CDC* pDC, BOOL bPause) {
	if (bPause == 0) {
		/* 血包移动 */
		mPoint.x += speedX;
		mPoint.y += speedY;
		/* 边界处理 */
		if (mPoint.y < 0) {
			mPoint.y = 0;
			speedY = -speedY;
		}
		if (mPoint.y > windowHeight - SUPPLY_HEIGHT) {
			mPoint.y = windowHeight - SUPPLY_HEIGHT;
			speedY = -speedY;
		}
		if (mPoint.x < 0) {
			mPoint.x = 0;
			speedX = -speedX;
		}
		if (mPoint.x > windowWidth - SUPPLY_WIDTH) {
			mPoint.x = windowWidth - SUPPLY_WIDTH;
			speedX = -speedX;
		}
		images.Draw(pDC, 3, mPoint, ILD_TRANSPARENT);
		return TRUE;
	}
	else {
		return FALSE;
	}
}

BOOL CSupply::LoadImage() {
	return  CGameObject::LoadImage(images, IDB_BMP_BLOOD, RGB(0, 0, 0), SUPPLY_WIDTH, SUPPLY_HEIGHT, 6);
}

CRect CSupply::GetRect() {
	return CRect(mPoint, CPoint(mPoint.x + SUPPLY_WIDTH, mPoint.y + SUPPLY_HEIGHT));
}