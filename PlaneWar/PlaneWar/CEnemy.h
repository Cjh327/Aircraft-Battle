#pragma once
#include "GameObject.h"

//�л��ĸ߶�
#define ENEMY_HEIGHT 90
//�л��Ŀ��
#define ENEMY_WIDTH 120
//�л������ٶ�
#define ENEMY_SPEED 3
//�л�Ѫ��
#define ENEMY_HP 1

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
	void decreaseHp(int x);
	bool isAlive() const;
	void setHp(int _hp);

	CRect GetRect();

	//����
	BOOL Draw(CDC* pDC, BOOL bPause);
	BOOL Draw(CDC* pDC, int passNum, BOOL bPause);

	//���صл�ͼ��
	static BOOL LoadImage();
};

