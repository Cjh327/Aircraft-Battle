#include "stdafx.h"
#include "CEnemy.h"
#include "resource.h"


//�л��ĸ߶�
#define ENEMY_HEIGHT 90
//�л��Ŀ��
#define ENEMY_WIDTH 120
//�л������ٶ�
#define ENEMY_SPEED 3
//�л�Ѫ��
#define ENEMY_HP 2


//��̬ͼ���б�
CImageList CEnemy::enemyImages;

CEnemy::CEnemy(int window_width, int window_height) : hp(ENEMY_HP), speed(ENEMY_SPEED) {
	mPoint.x = rand() % window_width;
	mPoint.y = 0;
}

int CEnemy::getHp() const {
	return hp;
}

bool CEnemy::isAlive() const {
	return hp > 0;
}

void CEnemy::setHp(int _hp) {
	hp = _hp;
}

//���Ƶ�ǰ�л�λ��
BOOL CEnemy::Draw(CDC* pDC, int passNum, BOOL bPause)
{
	if (bPause == 0) {
		int index = passNum % 5;
		//�л�λ������仯,ֻ�ı������꣬�����Ϊ���õл������ٷ���
		//+ rand() % 10
		mPoint.y += speed;
		enemyImages.Draw(pDC, index, mPoint, ILD_TRANSPARENT);
		return TRUE;
	}
	else return FALSE;
}

BOOL CEnemy::Draw(CDC* pDC, BOOL bPause)
{
	if (bPause == 0) {
		//�л�λ������仯,ֻ�ı������꣬�����Ϊ���õл������ٷ���
		//+ rand() % 10
		mPoint.y += speed;
		enemyImages.Draw(pDC, 0, mPoint, ILD_TRANSPARENT);
		return TRUE;
	}
	else return FALSE;
}

//����ͼ��
BOOL CEnemy::LoadImage()
{
	//������Ϸ�����ͼ�����
	CBitmap enemyBmp;
	if (!enemyBmp.LoadBitmapW(IDB_BMP_ENEMYDOWN))
		return FALSE;
	//����CImageList����
	if (!enemyImages.Create(ENEMY_WIDTH, ENEMY_HEIGHT, ILC_COLOR24 | ILC_MASK, 5, 0))//nInitial��ʼ����
		return FALSE;//cx,cy ͼƬ�Ŀ��
	//ͼ�������м�������Ӧ��ͼ�����֮��ֱ��ͨ�����������ͼ�����
	enemyImages.Add(&enemyBmp, RGB(0, 0, 0));

	return TRUE;
}

CRect CEnemy::GetRect()
{
	return CRect(mPoint, CPoint(mPoint.x + ENEMY_HEIGHT, mPoint.y + ENEMY_HEIGHT));
}