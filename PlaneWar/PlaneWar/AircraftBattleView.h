
// AircraftBattleView.h : CAircraftBattleView ��Ľӿ�
//

#pragma once

#include "MyPlane.h"
#include "GameObject.h"
#include "Scene.h"
#include "MyDialog.h"
#include "RestartDialog.h"

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
class CAircraftBattleView : public CView
{
protected: // �������л�����
	CAircraftBattleView();
	DECLARE_DYNCREATE(CAircraftBattleView)

// ����
public:
	CAircraftBattleDoc* GetDocument() const;

	CScene	scene;//����

	//��������Ϸ����
	CMyPlane *myplane;

	//�����洢��Ϸ����Ķ�������
	CObList enemyList;
	CObList meList;
	CObList bulletList;
	CObList ballList;
	CObList explosionList;
	CObList bloodList;

	CRect rect;//������Ļ����

	bool isStarted; // ��ǻ�ӭ�����Ƿ�������
	bool isPause;   // �Ƿ���ͣ
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
	virtual ~CAircraftBattleView();
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

#ifndef _DEBUG  // AircraftBattleView.cpp �еĵ��԰汾
inline CAircraftBattleDoc* CAircraftBattleView::GetDocument() const
   { return reinterpret_cast<CAircraftBattleDoc*>(m_pDocument); }
#endif

