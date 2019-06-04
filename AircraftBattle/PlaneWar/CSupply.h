#pragma once
#include "GameObject.h"


#define SUPPLY_WIDTH 60		// 补给包宽度
#define SUPPLY_HEIGHT 60	// 补给包高度

class CSupply : public CGameObject {
private:
	int windowWidth;
	int windowHeight;
	int speedX;
	int speedY;
	int hp;
	static CImageList images;
public:
	CSupply(int WINDOWS_WIDTH, int WINDOWS_HEIGHT);
	BOOL Draw(CDC* pDC, BOOL bPause);
	int getHp() const;
	static BOOL LoadImage();
	CRect GetRect();
};

