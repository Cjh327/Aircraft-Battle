//������
#pragma once
#include <atlimage.h>
#include <Mmsystem.h>
#pragma comment(lib, "Winmm.lib")

class CScene
{
	//��Ա����
private:
	CImage	images[8];//��������,0λΪ��ʼͼƬ��1-7Ϊ���Ų�ͬ�ı���
	int		beginY;//������Y����

	bool	isStart;//�Ƿ�ʼ

//��Ա����
public:
	bool InitScene();//��ʼ������
	void MoveBg();//�ƶ�����
				  ////���Ƴ���(ע������bufferDC�����ò���)
	void StickScene(CDC* pDC, int index, CRect rClient);//����index-1��ʾ�����ʼͼƬ
	void ReleaseScene();//�ͷ��ڴ���Դ

};


