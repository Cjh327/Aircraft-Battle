#pragma once
#include "GameObject.h"
#include "CPlane.h"

#define PLANE_WIDTH			120		// 未升级战机图像宽
#define PLANE_HEIGHT		90		// 未升级战机图像高
#define PLANE_X				400		// 战机初始位置X
#define PLANE_Y				300		// 战机初始位置Y
#define PLANE_SPEED			30		// 战机默认速度
#define PLANE_DAMAGE		1		// 战机默认伤害
#define PLANE_HP			10		// 战机默认生命

//战机类
class CMyPlane :public CPlane {
private:
	static CImageList images;
public:
	CMyPlane();							// 构造函数
	BOOL Draw(CDC* pDC, BOOL bPause);	// 绘制函数
	static BOOL LoadImage();			// 加载图像
	CRect GetRect();					// 重写获取矩形区域
};
