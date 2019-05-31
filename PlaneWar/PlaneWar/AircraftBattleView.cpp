
// AircraftBattleView.cpp : CAircraftBattleView 类的实现
//

#include "stdafx.h"
#include <mmsystem.h>
#include <iostream>
#pragma comment(lib, "WINMM.LIB")
#include <MMSYSTEM.H>
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "AircraftBattle.h"
#endif

#include "AircraftBattleDoc.h"
#include "AircraftBattleView.h"
#include "CEnemy.h"
#include "MyPlane.h"
#include "CBullet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAircraftBattleView

IMPLEMENT_DYNCREATE(CAircraftBattleView, CView)

BEGIN_MESSAGE_MAP(CAircraftBattleView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CAircraftBattleView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CAircraftBattleView 构造/析构

CAircraftBattleView::CAircraftBattleView()
{
	//默认战机飞行速度、战机生命值、战机得分、关卡、是否过关、是否暂停

	// TODO: 在此处添加构造代码
}

CAircraftBattleView::~CAircraftBattleView()
{
}

BOOL CAircraftBattleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CAircraftBattleView 绘制
void CAircraftBattleView::OnDraw(CDC* pDC)
{
	CAircraftBattleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

// CAircraftBattleView 打印

void CAircraftBattleView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CAircraftBattleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CAircraftBattleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CAircraftBattleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CAircraftBattleView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// CAircraftBattleView 诊断

#ifdef _DEBUG
void CAircraftBattleView::AssertValid() const
{
	CView::AssertValid();
}

void CAircraftBattleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAircraftBattleDoc* CAircraftBattleView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAircraftBattleDoc)));
	return (CAircraftBattleDoc*)m_pDocument;
}
#endif //_DEBUG

//重写实现

// CAircraftBattleView 消息处理程序
//视图创建监听
int CAircraftBattleView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	//-----------初始化工作------------
	//加载游戏对象图片
	CMyPlane::LoadImage();
	CMyPlane::LoadImageProtect();
	CEnemy::LoadImage();
	CBullet::LoadImage();
	//加载标题图片
	CBitmap startbmp;
	startbmp.LoadBitmapW(IDB_BMP_TITLE);
	startIMG.Create(346, 96, ILC_COLOR24 | ILC_MASK, 1, 0);
	startIMG.Add(&startbmp, RGB(0, 0, 0));

	//场景初始化失败
	if (!scene.InitScene())
	{
		AfxMessageBox(L"图片资源加载失败");
		exit(0);
	}

	//参数初始化
	myplane = new CMyPlane(FALSE);
	isStarted = false;
	isPause = false;

	SetTimer(4, 40, NULL);//背景滚动定时器
	SetMyTimer();
	return 0;
}

//计时器监听
void CAircraftBattleView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//双缓冲
	CDC* pDC = GetDC();
	if (pDC == NULL) {
		CView::OnTimer(nIDEvent);
		return;
	}
	//获得客户区矩形区域
	GetClientRect(&rect);
	//内存缓冲CDC
	CDC cdc;

	//内存中承载临时图像的缓冲位图
	CBitmap* cacheBitmap = new CBitmap;
	//用当前设备CDC初始化缓冲CDC
	cdc.CreateCompatibleDC(pDC);
	//绑定pDC和缓冲位图的关系，cdc先输出到缓冲位图中，输出完毕之后再一次性将缓冲位图输出到屏幕
	cacheBitmap->CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	//替换cdc原本的缓冲区为缓冲位图，这样cdc输出的内容就写到了缓冲位图中
	CBitmap* pOldBit = cdc.SelectObject(cacheBitmap);

	if (isStarted == FALSE) {
		//欢迎界面
		scene.StickScene(&cdc, -1, rect);
		startIMG.Draw(&cdc, 0, CPoint(rect.right / 2 - 173, 100), ILD_TRANSPARENT);
		//设置透明背景
		cdc.SetBkMode(TRANSPARENT);
		HFONT tipFont;
		tipFont = CreateFont(30, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(tipFont);
		cdc.SetTextColor(RGB(0, 0, 0));
		cdc.TextOutW(rect.right / 2 - 200, 210, _T("点击鼠标左键或空格键开始游戏"));
		HFONT textFont;
		textFont = CreateFont(18, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(textFont);
		cdc.SetTextColor(RGB(128, 128, 0));
		const int space = 30, off = 180;
		cdc.TextOutW(rect.right / 2 - off, 210 + space, _T("方向控制：方向键、ASDW、鼠标"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 2 * space, _T("射击：空格键、鼠标左键"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 3 * space, _T("暂停：Z键"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 4 * space, _T("大招：X键"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 5 * space, _T("防护罩：C键"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 6 * space, _T("战机升级：V键"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 7 * space, _T("无敌模式：Y键"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 8 * space, _T("初始生命值：10"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 9 * space, _T("初始魔法值：0"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 10 * space, _T("敌机生命值：2"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 11 * space, _T("消灭一个敌机加1分，如果分数达到要求即可进入Boss模式，打赢Boss即可进入下一关。"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 12 * space, _T("魔法值随着游戏进程增加，可通过使用魔法值使用防护罩、战机升级、战机大招的使用。"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 13 * space, _T("游戏过程中会有一定程度的血包出现以恢复生命值。"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 14 * space, _T("随着关卡增多，敌机、炮弹速度和数量均增加，通过10关即可通关！"));
		//将二级缓冲cdc中的数据推送到一级级缓冲pDC中，即输出到屏幕中
		pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &cdc, 0, 0, SRCCOPY);
		//释放二级cdc
		cdc.DeleteDC();
		//释放缓冲位图
		cacheBitmap->DeleteObject();
		//释放一级pDC
		ReleaseDC(pDC);
		CView::OnTimer(nIDEvent);
		return;
	}
	else {
		// 游戏界面
		scene.StickScene(&cdc, 1, rect);
		if (nIDEvent == 4) {
			//滚动背景
			scene.MoveBg();
		}
		// 刷新显示战机
		if (myplane != NULL) {
			myplane->Draw(&cdc, FALSE, FALSE);
		}
		// 随机添加敌机,敌机随机发射炸弹，此时敌机速度与数量和关卡有关
		if (myplane != NULL && !isPause) {
			// 敌机产生定时器触发
			if (nIDEvent == 2) {
				CEnemy* enemy = new CEnemy(rect.right, rect.bottom);
				enemyList.AddTail(enemy);	//随机产生敌机
			}
		}
		// 超出边界的敌机进行销毁
		POSITION stPos = NULL, tPos = NULL;
		stPos = enemyList.GetHeadPosition();
		while (stPos != NULL) {
			tPos = stPos;
			CEnemy* enemy = (CEnemy*)enemyList.GetNext(stPos);
			// 判断敌机是否出界
			if (enemy->GetPoint().x<rect.left || enemy->GetPoint().x>rect.right
				|| enemy->GetPoint().y<rect.top || enemy->GetPoint().y>rect.bottom) {
				enemyList.RemoveAt(tPos);
				delete enemy;
			}
			else {
				//没出界，绘制
				enemy->Draw(&cdc, 1, FALSE);
			}
		}

		// 发射子弹，超出边界的子弹进行销毁
		stPos = NULL, tPos = NULL;
		stPos = bulletList.GetHeadPosition();
		while (stPos != NULL) {
			tPos = stPos;
			CBullet* bullet = (CBullet*)bulletList.GetNext(stPos);
			// 判断敌机是否出界
			if (bullet->GetPoint().x < rect.left || bullet->GetPoint().x > rect.right
				|| bullet->GetPoint().y < rect.top || bullet->GetPoint().y > rect.bottom) {
				bulletList.RemoveAt(tPos);
				delete bullet;
			}
			else {
				// 没出界，绘制
				bullet->Draw(&cdc, FALSE);
			}
		}

		// 子弹打中敌机
		POSITION bulletPos = bulletList.GetHeadPosition(), tmpBulletPos = bulletPos;
		while (bulletPos != NULL) {
			tmpBulletPos = bulletPos;
			CBullet* bullet = (CBullet*)bulletList.GetNext(bulletPos);
			POSITION enemyPos = enemyList.GetHeadPosition(), tmpEnemyPos = enemyPos;
			while (enemyPos != NULL) {
				tmpEnemyPos = enemyPos;
				CEnemy* enemy = (CEnemy*)enemyList.GetNext(enemyPos);
				CRect tmpRect;
				if (tmpRect.IntersectRect(&(bullet->GetRect()), &(enemy->GetRect()))) {
					// 子弹和敌机区域有重合，即子弹打中敌机
					bulletList.RemoveAt(tmpBulletPos);
					enemy->decreaseHp(bullet->getDamage());
					delete bullet;
					bullet = NULL;
					if (!enemy->isAlive()) {
						enemyList.RemoveAt(tmpEnemyPos);
						delete enemy;
						enemy = NULL;
					}
					break;
				}
			}
		}

		// 战机撞到敌机
		POSITION enemyPos = enemyList.GetHeadPosition(), tmpEnemyPos = enemyPos;
		while (enemyPos != NULL) {
			tmpEnemyPos = enemyPos;
			CEnemy* enemy = (CEnemy*)enemyList.GetNext(enemyPos);
			CRect tmpRect;
			if (tmpRect.IntersectRect(&(myplane->GetRect()), &(enemy->GetRect()))) {
				// 战机和敌机区域有重合，即战机撞到敌机
				myplane->decreaseHp(10 * enemy->getDamage());
				enemyList.RemoveAt(tmpEnemyPos);
				delete enemy;
				enemy = NULL;
				break;
			}
		}
	}

	//将二级缓冲cdc中的数据推送到一级级缓冲pDC中，即输出到屏幕中
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &cdc, 0, 0, SRCCOPY);
	//释放二级cdc
	cdc.DeleteDC();
	//释放缓冲位图
	cacheBitmap->DeleteObject();
	//释放一级pDC
	ReleaseDC(pDC);
	CView::OnTimer(nIDEvent);
}

//键盘按下监听
void CAircraftBattleView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//按空格进入游戏
	if (isStarted == false) {
		if (GetKeyState(VK_SPACE) < 0) {
			isStarted = true;
		}
	}
	else {
		if (myplane != NULL && GetKeyState(VK_SPACE) < 0) {
			// 按空格键发射子弹
			CBullet* bullet = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2, myplane->GetPoint().y, myplane->getDamage());
			bulletList.AddTail(bullet);
		}
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//鼠标移动监听，控制战机位置
void CAircraftBattleView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (myplane != NULL && isPause == 0) {
		//绘制新游戏对象
		myplane->SetPoint(point.x - PLANE1_WIDTH / 2, point.y - PLANE1_HEIGHT / 2);
	}
	CView::OnMouseMove(nFlags, point);
}

//按下鼠标左键监听
void CAircraftBattleView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (isStarted == FALSE) {
		isStarted = TRUE;
	}
	else if (myplane != NULL) {
		// 按鼠标左键发射子弹
		CBullet* bullet = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2, myplane->GetPoint().y, myplane->getDamage());
		bulletList.AddTail(bullet);
	}

	CView::OnLButtonDown(nFlags, point);
}

//鼠标右键监听
void CAircraftBattleView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	if (isStarted == TRUE && myplane != NULL) {
		// 按鼠标右键发射炮弹
		// MyTODO
	}
}

//生命周期

//窗口销毁
void CAircraftBattleView::OnDestroy()
{
	// 销毁指针资源
	if (myplane != NULL)
		delete myplane;

	//释放内存资源
	scene.ReleaseScene();

	CView::OnDestroy();
}

//游戏重新开始
void CAircraftBattleView::Restart()
{
	// TODO: 在此处添加游戏重新开始初始化参数
	//战机重新加载
	myplane = new CMyPlane(FALSE);

	//清空敌机链表
	if (enemyList.GetCount() > 0)
		enemyList.RemoveAll();
	//清空战机链表
	if (meList.GetCount() > 0)
		meList.RemoveAll();
	//清空战机子弹链表
	if (bulletList.GetCount() > 0)
		bulletList.RemoveAll();
	//清空敌机炸弹链表
	if (ballList.GetCount() > 0)
		ballList.RemoveAll();
	//清空爆炸链表
	if (explosionList.GetCount() > 0)
		explosionList.RemoveAll();
	//清空血包列表
	if (bloodList.GetCount() > 0)
		bloodList.RemoveAll();

	//参数重新初始化
	isPause = false;
	//isStarted = FALSE;
	SetMyTimer();
}

//游戏暂停
void CAircraftBattleView::Pause()
{
	// TODO: 在此处添加游戏暂停操作
	isPause = TRUE;
	Sleep(1000);
}

// 生命值归零，游戏结束
void CAircraftBattleView::gameOver(CDC* pDC, CDC& cdc, CBitmap* cacheBitmap)
{
	//结束游戏界面
	//释放计时器
	KillTimer(1);
	KillTimer(2);
	KillTimer(3);
	//KillTimer(4);
	KillTimer(5);
	//计算最后得分
	//播放游戏结束音乐
	PlaySound((LPCTSTR)IDR_WAV_GAMEOVER, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
	//清屏
	CBitmap* tCache = cacheBitmap;
	cacheBitmap = new CBitmap;
	cacheBitmap->CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	cdc.SelectObject(cacheBitmap);
	//内存中承载临时图像的缓冲位图
	delete tCache;
	//isStop = FLAG_STOP;
}

//设置计时器
void CAircraftBattleView::SetMyTimer()
{
	SetTimer(1, 17, NULL);//刷新界面定时器
	SetTimer(2, 400 - 1 * 30, NULL);//产生敌机定时器
	SetTimer(3, 2000 - 1 * 100, NULL);//产生敌机炮弹频率

	SetTimer(5, 2000, NULL);//控制魔法值变化频率
}

//void CAircraftBattleView::OnClose()
//{
//	isPause = TRUE;
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	KillTimer(1);
//	KillTimer(2);
//	KillTimer(3);
//	KillTimer(4);
//	KillTimer(5 );
//	CView::OnClose();
//}
