
// PlaneWarView.h : CPlaneWarView ��Ľӿ�
//

#pragma once

#include "MyPlane.h"
#include "GameObject.h"
#include "Scene.h"
#include "MyDialog.h"
#include "RestartDialog.h"

//Ĭ��ս���ٶ�
#define DEFAULT_SPEED 30
//Ĭ��ս������
#define DEFAULT_LIFE 10
//Ĭ��ս��������
#define DEFAULT_LIFE_COUNT 3
//Ĭ�Ϲؿ�
#define DEFAULT_PASS 1
//����ս���ӵ����
#define BOMB_DISTANCE 35
//���������
#define STEP 30
//���ص÷���
#define PASS_SCORE 20
//���λ
#define FLAG_RESTART 2
#define FLAG_STOP 3


//��Ϸ��ͼ������
class CPlaneWarView : public CView
{
protected: // �������л�����
	CPlaneWarView();
	DECLARE_DYNCREATE(CPlaneWarView)

// ����
public:
	CPlaneWarDoc* GetDocument() const;

	CScene	scene;//����

	//��������Ϸ����
	CMyPlane *myplane;

	//�����洢��Ϸ����Ķ�������
	CObList enemyList;
	CObList meList;
	CObList bombList;
	CObList ballList;
	CObList explosionList;
	CObList bloodList;

	CRect rect;//������Ļ����

	int speed;//ս�����ٶȣ����������
	int myLife;//Ϊս����������ֵ
	int lifeNum;//ս��������
	int myScore;//ս���ĵ÷�
	int passScore;//��ǰ�ؿ��÷���
	int lifeCount;//Ѫ���������Ʋ���
	BOOL bloodExist;//�����Ļ���Ƿ����Ѫ��
	int magicCount;//ħ��ֵ�������ܷ񷢴���
	int bossBlood;//BossѪ��

	int passNum;//��¼��ǰ�ؿ�
	int isPass;//�Ƿ�ͨ�صı�־
	int isPause;//�Ƿ���ͣ
	BOOL isBoss;//����Ƿ����Boss
	BOOL bossLoaded;//���Boss�������
	BOOL isProtect;//����Ƿ���������
	BOOL isUpdate;//���ս���Ƿ�����
	BOOL test;//�޵�ģʽ����
	BOOL isStop;//�����Ϸֹͣ
	BOOL isStarted;//��ǻ�ӭ�����Ƿ�������
	CImageList startIMG;

// ����
public:
	//��ȡս���ٶ�
	int GetSpeed();
	//����ս���ٶ�
	void SetSpeed(int speed);
	//��Ϸ��ͣ
	void Pause();
	//��Ϸ���¿�ʼ
	void Restart();

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CPlaneWarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	// ����ֵ���㣬��Ϸ����
	void gameOver(CDC* pDC,  CDC& cdc,  CBitmap* cacheBitmap);
	//���ü�ʱ��
	void SetMyTimer();
	//afx_msg void OnClose();
};

#ifndef _DEBUG  // PlaneWarView.cpp �еĵ��԰汾
inline CPlaneWarDoc* CPlaneWarView::GetDocument() const
   { return reinterpret_cast<CPlaneWarDoc*>(m_pDocument); }
#endif

