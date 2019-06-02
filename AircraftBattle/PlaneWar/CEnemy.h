#pragma once
#include "GameObject.h"
#include "CPlane.h"

#define ENEMY_HEIGHT	90		// �л��ĸ߶�
#define ENEMY_WIDTH		120		// �л��Ŀ��
#define ENEMY_SPEED		3		// �л������ٶ�
#define ENEMY_HP		1		// �л�Ѫ��
#define ENEMY_DAMAGE	1		// �л��˺�
#define ENEMY_SCORE		10		// �л�����

class CEnemy : public CPlane
{
private:
	int score;
protected:
	static CImageList enemyImages; //�л�ͼ��

public:
	CEnemy(int window_width, int window_heigh);
	int getScore() const;

	CRect GetRect();

	//����
	BOOL Draw(CDC* pDC, BOOL bPause);
	BOOL Draw(CDC* pDC, int passNum, BOOL bPause);

	//���صл�ͼ��
	static BOOL LoadImage();
};

