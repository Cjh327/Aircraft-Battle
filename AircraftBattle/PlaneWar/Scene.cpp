#include "StdAfx.h"
#include "Scene.h"

//初始化场景
bool CScene::InitScene() {
	//加载开始图片
	this->images[0].Load(_T("image\\start.bmp"));
	CString str;
	//如果加载失败, 返回false
	for (int i = 1; i <= 7; i++) {
		str.Format(_T("image\\background%d.bmp"), i);
		this->images[i].Load(str);
		if (images[i].IsNull())
			return false;
	}

	//开始为真, 背景起始坐标为0
	this->isStart = true;
	this->beginY = 0;

	return true;
}

//绘制场景
void CScene::StickScene(CDC* pDC, int index, CRect rClient) {
	//设置缩放图片的模式为:COLORONCOLOR, 以消除像素重叠
	pDC->SetStretchBltMode(COLORONCOLOR);

	//如果到了下边界, 回到起点
	if (beginY >= rClient.Height())	{
		beginY = 0;
		isStart = false;
	}

	//客户区高度
	int cHeight = rClient.Height();

	rClient.bottom = cHeight + beginY;
	rClient.top = beginY;

	//如果是开始就绘制起始背景
	if (isStart) {
		this->images[index].StretchBlt(*pDC, rClient, SRCCOPY);
	}
	//将下一张背景作为起始背景
	else {
		this->images[index].StretchBlt(*pDC, rClient, SRCCOPY);
	}

	//绘制下一张背景
	rClient.top -= cHeight;
	rClient.bottom -= cHeight;
	images[index].StretchBlt(*pDC, rClient, SRCCOPY);
}

//移动背景
void CScene::MoveBg() {
	//移动背景
	beginY += 1;
}

//释放内存资源
void CScene::ReleaseScene() {
	for (int i = 0; i < 8; i++)
		if (!images[i].IsNull())
			images[i].Destroy();

	mciSendString(L"close bgm", NULL, 0, NULL);
}