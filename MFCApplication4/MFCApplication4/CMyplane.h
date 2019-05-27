#pragma once
#include "CGameObject.h"

//升级战机图像宽
#define PLANE_WIDTH 120
//升级战机图像高
#define PLANE_HEIGHT 150
//未升级战机图像宽
#define PLANE1_WIDTH 120
//未升级战机图像高
#define PLANE1_HEIGHT 90
//保护罩战机图像宽
#define PLANE_PRO_WIDTH 165
//保护罩战机图像高
#define PLANE_PRO_HEIGHT 166
//战机初始位置X
#define PLANE_X 400
//战机初始位置Y
#define PLANE_Y 300

class CMyplane : public CGameObject
{
private:
	static CImageList images;//存储升级战机图片
	static CImageList images1;//存储未升级战机图片
	static CImageList imagespro;//存储防护罩图片
	int index;//标记要显示的战机图片下标索引，和战机是否升级相关
	int progress;

public:
	//加载战机图像
	static BOOL LoadImage();
};

