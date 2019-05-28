
// MFCApplication4View.h: CMFCApplication4View 类的接口
//

#pragma once

#include "Scene.h"
#include "CMyplane.h"

//默认战机速度
#define DEFAULT_SPEED 30
//默认战机生命
#define DEFAULT_LIFE 10
//默认战机命条数
#define DEFAULT_LIFE_COUNT 3
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

class CMFCApplication4View : public CView
{
protected: // 仅从序列化创建
	CMFCApplication4View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication4View)

// 特性
public:
	CMFCApplication4Doc* GetDocument() const;

	Scene scene;	//场景

	//创建各游戏对象
	CMyplane* myplane;
	//CEnemy* enemy;
	//CBoss* boss;
	//CBomb* bomb;
	//CBall* ball;
	//CExplosion* explosion;
	//CBlood* blood;

	//创建存储游戏对象的对象链表
	CObList enemyList;
	CObList meList;
	CObList bombList;
	CObList ballList;
	CObList explosionList;
	CObList bloodList;

	CRect rect;//窗口屏幕矩形

	int speed;//战机的速度，方向键控制
	int myLife;//为战机设置生命值
	int lifeNum;//战机命条数
	int myScore;//战机的得分
	int passScore;//当前关卡得分数
	int lifeCount;//血包产生控制参数
	BOOL bloodExist;//标记屏幕中是否存在血包
	int magicCount;//魔法值，控制能否发大招
	int bossBlood;//Boss血量

	int passNum;//记录当前关卡
	int isPass;//是否通关的标志
	int isPause;//是否暂停
	BOOL isBoss;//标记是否进入Boss
	BOOL bossLoaded;//标记Boss出场完成
	BOOL isProtect;//标记是否开启防护罩
	BOOL isUpdate;//标记战机是否升级
	BOOL test;//无敌模式参数
	BOOL isStop;//标记游戏停止
	BOOL isStarted;//标记欢迎界面是否加载完成
	CImageList startIMG;

// 操作
public:
	//设置计时器
	void SetMyTimer();

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
	virtual ~CMFCApplication4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // MFCApplication4View.cpp 中的调试版本
inline CMFCApplication4Doc* CMFCApplication4View::GetDocument() const
   { return reinterpret_cast<CMFCApplication4Doc*>(m_pDocument); }
#endif

