#include "StdAfx.h"
#include "Scene.h"
//������ʵ��
CScene::CScene(void)
{
}

CScene::~CScene(void)
{
}

//��ʼ������
bool CScene::InitScene()
{
	/*this->images[0].Load(L"image\\background1.bmp");
	this->images[1].Load(L"image\\background2.bmp");
	this->images[2].Load(L"image\\background3.bmp");
*/
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

	//���ű�������
	mciSendString(L"open sound\\background.mp3 alias bgm", NULL, 0, NULL);
	mciSendString(L"play bgm repeat", NULL, 0, NULL);
	return true;
}

//���Ƴ���
void CScene::StickScene(CDC* pDC,int index, CRect rClient)
{
	if (index == -1)
		index = 0;
	else
		index = index % 7 + 1;
	//��������ͼƬ��ģʽΪ:COLORONCOLOR, �����������ص�
	pDC->SetStretchBltMode(COLORONCOLOR);

	//��������±߽�, �ص����
	if (beginY >= rClient.Height())
	{
		beginY = 0;

		if (isStart)
			isStart = false;
	}

	//�ͻ����߶�
	int cltHeight = rClient.Height();

	rClient.bottom = cltHeight + beginY;
	rClient.top = beginY;

	//����ǿ�ʼ�ͻ�����ʼ����
	if (isStart)
	{
		this->images[index].StretchBlt(*pDC, rClient, SRCCOPY);
	}
	//����һ�ű�����Ϊ��ʼ����
	else
	{
		this->images[index].StretchBlt(*pDC, rClient, SRCCOPY);
	}

	//������һ�ű���
	rClient.top -= cltHeight;
	rClient.bottom -= cltHeight;
	images[index].StretchBlt(*pDC, rClient, SRCCOPY);
}

//�ƶ�����
void CScene::MoveBg()
{
	//�ƶ�����
	beginY += 1;
}

//�ͷ��ڴ���Դ
void CScene::ReleaseScene()
{
	for (int i = 0; i <8; i++)
		if (!images[i].IsNull())
			images[i].Destroy();

	mciSendString(L"close bgm", NULL, 0, NULL);
}