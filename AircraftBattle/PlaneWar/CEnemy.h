#pragma once
#include "GameObject.h"
#include "CPlane.h"

#define ENEMY_HEIGHT	90		// �л��ĸ߶�
#define ENEMY_WIDTH		120		// �л��Ŀ��
#define ENEMY_SPEED		3		// �л������ٶ�
#define ENEMY_HP		2		// �л�Ѫ��
#define ENEMY_DAMAGE	1		// �л��˺�
#define ENEMY_SCORE		10		// �л�����

class CEnemy : public CPlane {
private:
	int score;
	int index;
protected:
	static CImageList enemyImages; //�л�ͼ��

public:
	CEnemy(int window_width, int window_heigh, int _idx);
	int getScore() const;
	int getIndex() const;

	CRect GetRect();

	//����
	BOOL Draw(CDC* pDC, BOOL bPause);
	//BOOL Draw(CDC* pDC, int index, BOOL bPause);

	//���صл�ͼ��
	static BOOL LoadImage();
};

