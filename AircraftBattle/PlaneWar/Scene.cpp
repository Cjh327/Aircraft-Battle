#include "StdAfx.h"
#include "Scene.h"

//��ʼ������
bool CScene::InitScene() {
	//���ؿ�ʼͼƬ
	this->images[0].Load(_T("image\\start.bmp"));
	CString str;
	//�������ʧ��, ����false
	for (int i = 1; i <= 7; i++) {
		str.Format(_T("image\\background%d.bmp"), i);
		this->images[i].Load(str);
		if (images[i].IsNull())
			return false;
	}

	//��ʼΪ��, ������ʼ����Ϊ0
	this->isStart = true;
	this->beginY = 0;

	return true;
}

//���Ƴ���
void CScene::StickScene(CDC* pDC, int index, CRect rClient) {
	//��������ͼƬ��ģʽΪ:COLORONCOLOR, �����������ص�
	pDC->SetStretchBltMode(COLORONCOLOR);

	//��������±߽�, �ص����
	if (beginY >= rClient.Height())	{
		beginY = 0;
		isStart = false;
	}

	//�ͻ����߶�
	int cHeight = rClient.Height();

	rClient.bottom = cHeight + beginY;
	rClient.top = beginY;

	//����ǿ�ʼ�ͻ�����ʼ����
	if (isStart) {
		this->images[index].StretchBlt(*pDC, rClient, SRCCOPY);
	}
	//����һ�ű�����Ϊ��ʼ����
	else {
		this->images[index].StretchBlt(*pDC, rClient, SRCCOPY);
	}

	//������һ�ű���
	rClient.top -= cHeight;
	rClient.bottom -= cHeight;
	images[index].StretchBlt(*pDC, rClient, SRCCOPY);
}

//�ƶ�����
void CScene::MoveBg() {
	//�ƶ�����
	beginY += 1;
}

//�ͷ��ڴ���Դ
void CScene::ReleaseScene() {
	for (int i = 0; i < 8; i++)
		if (!images[i].IsNull())
			images[i].Destroy();

	mciSendString(L"close bgm", NULL, 0, NULL);
}