#include "stdafx.h"
#include "CEnemy.h"
#include "resource.h"

//��̬ͼ���б�
CImageList CEnemy::enemyImages;

CEnemy::CEnemy(int window_width, int window_height) : CPlane(ENEMY_HP, ENEMY_DAMAGE, ENEMY_SPEED) {
	mPoint.x = rand() % window_width;
	mPoint.y = 0;
	score = ENEMY_SCORE;
}

int CEnemy::getScore() const {
	return score;
}

//���Ƶ�ǰ�л�λ��
BOOL CEnemy::Draw(CDC* pDC, int passNum, BOOL bPause) {
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

BOOL CEnemy::Draw(CDC* pDC, BOOL bPause) {
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
BOOL CEnemy::LoadImage() {
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

CRect CEnemy::GetRect() {
	return CRect(mPoint, CPoint(mPoint.x + ENEMY_WIDTH, mPoint.y + ENEMY_HEIGHT));
}