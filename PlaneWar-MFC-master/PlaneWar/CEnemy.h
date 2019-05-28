#pragma once
#include "GameObject.h"
class CEnemy : public CGameObject
{
private:
	int hp;
	int speed;

protected:
	static CImageList enemyImages; //�л�ͼ��

public:
	CEnemy(int window_width, int window_heigh);
	int getHp() const;
	bool isAlive() const;
	void setHp(int _hp);

	CRect GetRect();

	//����
	BOOL Draw(CDC* pDC, BOOL bPause);
	BOOL Draw(CDC* pDC, int passNum, BOOL bPause);

	//���صл�ͼ��
	static BOOL LoadImage();
};

