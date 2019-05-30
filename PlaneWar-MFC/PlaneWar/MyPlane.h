#pragma once
#include "GameObject.h"

#define PLANE_WIDTH 120			// 升级战机图像宽
#define PLANE_HEIGHT 150		// 升级战机图像高
#define PLANE1_WIDTH 120		// 未升级战机图像宽
#define PLANE1_HEIGHT 90		// 未升级战机图像高
#define PLANE_PRO_WIDTH 165		// 保护罩战机图像宽
#define PLANE_PRO_HEIGHT 166	// 保护罩战机图像高
#define PLANE_X 400				// 战机初始位置X
#define PLANE_Y 300				// 战机初始位置Y
//#define PLANE_SPEED 30			// 战机默认速度
#define PLANE_DAMAGE 1			// 战机默认伤害
#define PLANE_HP 10				// 战机默认生命

//战机类
class CMyPlane :public CGameObject
{
private:
	int damage;
	int hp;

public:
	CMyPlane(bool isUpdate = false, int _damage = PLANE_DAMAGE, int _hp = PLANE_HP);
	~CMyPlane(void);

	int getSpeed() const;
	int getDamage() const;

	//绘制
	BOOL Draw(CDC* pDC, BOOL bPause, BOOL isProtect);
	BOOL Draw(CDC* pDC, BOOL bPause);
	//加载战机图像
	static BOOL LoadImage();
	static BOOL LoadImageProtect();
	//得到战机矩形区域
	CRect GetRect()	{
		return CRect(mPoint, CPoint(mPoint.x + PLANE_WIDTH, mPoint.y + PLANE_HEIGHT));
	}

	//设置是否升级
	void SetIsUpdate(BOOL isUpdate);
	BOOL GetIsUpdate();

	//是否可以开火发射导弹
	BOOL isFire();
private:
	static CImageList images;//存储升级战机图片
	static CImageList images1;//存储未升级战机图片
	static CImageList imagespro;//存储防护罩图片
	int index;//标记要显示的战机图片下标索引，和战机是否升级相关
	int progress;
};
