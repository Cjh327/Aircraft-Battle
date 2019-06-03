
// AircraftBattleView.h : CAircraftBattleView 类的接口
//

#pragma once

#include "MyPlane.h"
#include "GameObject.h"
#include "Scene.h"
#include "MyDialog.h"
#include "RestartDialog.h"

//默认关卡
#define DEFAULT_PASS 1
//两个战机子弹间隔
#define BOMB_DISTANCE 35
//方向键步长
#define STEP 30
//过关得分数
#define PASS_SCORE 20
//标记位
#define FLAG_RESTART 2
#define FLAG_STOP 3


//游戏视图窗口类
class CAircraftBattleView : public CView
{
protected: // 仅从序列化创建
	CAircraftBattleView();
	DECLARE_DYNCREATE(CAircraftBattleView)

	// 特性
public:
	CAircraftBattleDoc* GetDocument() const;

	CScene	scene;//场景

	//创建各游戏对象
	CMyPlane* myplane;

	//创建存储游戏对象的对象链表
	CObList enemyList;
	CObList myBulletList;
	CObList enemyBulletList;

	CRect rect;//窗口屏幕矩形

	bool isStarted; // 标记欢迎界面是否加载完成
	bool isPause;   // 是否暂停
	bool isOver;	// 是否游戏结束

	int myScore;		// 游戏得分

	CImageList startIMG;

	// 操作
public:
	//游戏暂停
	void Pause();
	//游戏重新开始
	void Restart();

	// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 实现
public:
	virtual ~CAircraftBattleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 生成的消息映射函数
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
	void gameOver(CDC* pDC, CDC& cdc, CBitmap* cacheBitmap);
	void SetMyTimer();
};

#ifndef _DEBUG  // AircraftBattleView.cpp 中的调试版本
inline CAircraftBattleDoc* CAircraftBattleView::GetDocument() const
{
	return reinterpret_cast<CAircraftBattleDoc*>(m_pDocument);
}
#endif

