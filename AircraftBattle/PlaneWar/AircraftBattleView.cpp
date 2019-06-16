
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
#include "CSupply.h"

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
	maxScore = pDoc->getMaxScore();

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
	CEnemy::LoadImage();
	CBullet::LoadImage();
	CSupply::LoadImage();
	//加载标题图片
	CBitmap startbmp;
	startbmp.LoadBitmapW(IDB_BMP_TITLE);
	startIMG.Create(346, 96, ILC_COLOR24 | ILC_MASK, 1, 0);
	startIMG.Add(&startbmp, RGB(0, 0, 0));

	//场景初始化失败
	if (!scene.InitScene()) {
		AfxMessageBox(L"图片资源加载失败");
		exit(0);
	}

	//参数初始化
	myplane = new CMyPlane();
	isStarted = false;
	isPause = false;
	isOver = false;
	myScore = 0;

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

	if (!isStarted && !isOver) {
		//欢迎界面
		scene.StickScene(&cdc, 0, rect);
		startIMG.Draw(&cdc, 0, CPoint(rect.right / 2 - 173, 100), ILD_TRANSPARENT);
		//设置透明背景
		cdc.SetBkMode(TRANSPARENT);
		HFONT tipFont;
		tipFont = CreateFont(30, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(tipFont);
		cdc.SetTextColor(RGB(0, 0, 0));
		cdc.TextOutW(rect.right / 2 - 200, 220, _T("点击鼠标左键或空格键开始游戏"));
		cdc.SetTextColor(RGB(0, 0, 255));
		CString str;
		str.Format(_T("最高纪录：%d"), maxScore);
		cdc.TextOutW(rect.right / 2 - 100, 270, str);
		HFONT textFont;
		textFont = CreateFont(24, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(textFont);
		cdc.SetTextColor(RGB(255, 255, 0));
		const int space = 30, off = 200;
		cdc.TextOutW(rect.right / 2 - off, 400, _T("方向控制：鼠标"));
		cdc.TextOutW(rect.right / 2 - off, 400 + 1 * space, _T("射击：空格键、鼠标左键"));
	}
	else if (isStarted && !isOver) {
		// 游戏界面
		scene.StickScene(&cdc, 1, rect);
		if (nIDEvent == 4) {
			//滚动背景
			scene.MoveBg();
		}
		// 刷新显示战机
		if (myplane != NULL) {
			myplane->Draw(&cdc, FALSE);
		}
		// 随机产生敌机和补给包
		if (myplane != NULL && !isPause) {
			// 敌机产生定时器触发
			if (nIDEvent == 2) {
				// 随机产生普通敌机
				CEnemy* enemy = new CEnemy(rect.right, rect.bottom, 1);
				enemyList.AddTail(enemy);
			}
			if (nIDEvent == 5) {
				// 随机产生高级敌机
				CEnemy* enemy = new CEnemy(rect.right, rect.bottom, 2);
				enemyList.AddTail(enemy);
			}
			if (nIDEvent == 6) {
				// 随机产生补给包
				CSupply* supply = new CSupply(rect.right, rect.bottom);
				supplyList.AddTail(supply);
			}
		}

		if (myplane != NULL && !isPause) {
			// 绘制补给包
			POSITION supplyPos = supplyList.GetHeadPosition(), tmpSupplyPos;
			while (supplyPos != NULL) {
				CSupply* supply = (CSupply*)supplyList.GetNext(supplyPos);
				supply->Draw(&cdc, FALSE);
			}

			// 超出边界的敌机进行销毁
			POSITION stPos = NULL, tPos = NULL;
			stPos = enemyList.GetHeadPosition();
			while (stPos != NULL) {
				tPos = stPos;
				CEnemy* enemy = (CEnemy*)enemyList.GetNext(stPos);
				// 判断敌机是否出界
				if (enemy->GetPoint().x < rect.left || enemy->GetPoint().x > rect.right
					|| enemy->GetPoint().y < rect.top || enemy->GetPoint().y > rect.bottom) {
					enemyList.RemoveAt(tPos);
					delete enemy;
				}
				else {
					// 没出界则绘制
					enemy->Draw(&cdc, FALSE);
					if (nIDEvent == 3) {
						CBullet* bullet = new CBullet(enemy->GetPoint().x + ENEMY_WIDTH / 2 - BULLET_WIDTH / 2, enemy->GetPoint().y + ENEMY_HEIGHT, enemy->getDamage(), 0, -5, false, enemy->getIndex());
						enemyBulletList.AddTail(bullet);
					}
				}
			}

			// 发射子弹，超出边界的子弹进行销毁
			stPos = NULL, tPos = NULL;
			stPos = enemyBulletList.GetHeadPosition();
			while (stPos != NULL) {
				tPos = stPos;
				CBullet* bullet = (CBullet*)enemyBulletList.GetNext(stPos);
				// 判断子弹是否出界
				if (bullet->GetPoint().x < rect.left || bullet->GetPoint().x > rect.right
					|| bullet->GetPoint().y < rect.top || bullet->GetPoint().y > rect.bottom) {
					enemyBulletList.RemoveAt(tPos);
					delete bullet;
				}
				else {
					// 没出界，绘制
					bullet->Draw(&cdc, FALSE);
				}
			}
			stPos = NULL, tPos = NULL;
			stPos = myBulletList.GetHeadPosition();
			while (stPos != NULL) {
				tPos = stPos;
				CBullet* bullet = (CBullet*)myBulletList.GetNext(stPos);
				// 判断子弹是否出界
				if (bullet->GetPoint().x < rect.left || bullet->GetPoint().x > rect.right
					|| bullet->GetPoint().y < rect.top || bullet->GetPoint().y > rect.bottom) {
					myBulletList.RemoveAt(tPos);
					delete bullet;
				}
				else {
					// 没出界，绘制
					bullet->Draw(&cdc, FALSE);
				}
			}

			// 战机子弹打中敌机
			POSITION bulletPos = myBulletList.GetHeadPosition(), tmpBulletPos = bulletPos;
			while (bulletPos != NULL) {
				tmpBulletPos = bulletPos;
				CBullet* bullet = (CBullet*)myBulletList.GetNext(bulletPos);
				ASSERT(bullet->getFromMe());
				POSITION enemyPos = enemyList.GetHeadPosition(), tmpEnemyPos = enemyPos;
				while (enemyPos != NULL) {
					tmpEnemyPos = enemyPos;
					CEnemy* enemy = (CEnemy*)enemyList.GetNext(enemyPos);
					CRect tmpRect;
					if (tmpRect.IntersectRect(&(bullet->GetRect()), &(enemy->GetRect()))) {
						// 战机子弹和敌机区域有重合，即战机子弹打中敌机
						myBulletList.RemoveAt(tmpBulletPos);
						enemy->decreaseHp(bullet->getDamage());
						delete bullet;
						bullet = NULL;
						if (!enemy->isAlive()) {
							myScore += enemy->getScore();
							enemyList.RemoveAt(tmpEnemyPos);
							delete enemy;
							enemy = NULL;
						}
						break;
					}
				}
			}

			// 敌机子弹打中战机
			bulletPos = enemyBulletList.GetHeadPosition(), tmpBulletPos = bulletPos;
			while (bulletPos != NULL) {
				tmpBulletPos = bulletPos;
				CBullet* bullet = (CBullet*)enemyBulletList.GetNext(bulletPos);
				ASSERT(!bullet->getFromMe());
				CRect tmpRect;
				if (tmpRect.IntersectRect(&(bullet->GetRect()), &(myplane->GetRect()))) {
					// 敌机子弹和战机区域有重合，即敌机子弹打中战机
					enemyBulletList.RemoveAt(tmpBulletPos);
					myplane->decreaseHp(bullet->getDamage());
					delete bullet;
					bullet = NULL;
				}
			}

			// 子弹打中子弹
			bulletPos = myBulletList.GetHeadPosition(), tmpBulletPos = bulletPos;
			while (bulletPos != NULL) {
				tmpBulletPos = bulletPos;
				CBullet* myBullet = (CBullet*)myBulletList.GetNext(bulletPos);
				POSITION bulletPos1 = enemyBulletList.GetHeadPosition(), tmpBulletPos1 = bulletPos1;
				while (bulletPos1 != NULL) {
					tmpBulletPos1 = bulletPos1;
					CBullet* enemyBullet = (CBullet*)enemyBulletList.GetNext(bulletPos1);
					ASSERT(myBullet->getFromMe() != enemyBullet->getFromMe());
					CRect tmpRect;
					if (tmpRect.IntersectRect(&(myBullet->GetRect()), &(enemyBullet->GetRect()))) {
						// 战机子弹和敌机子弹有重合，即战机子弹打中敌机子弹
						myBulletList.RemoveAt(tmpBulletPos);
						enemyBulletList.RemoveAt(tmpBulletPos1);
						delete myBullet;
						delete enemyBullet;
						myBullet = enemyBullet = NULL;
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
					myplane->decreaseHp(2 * enemy->getDamage());
					myScore += enemy->getScore();
					enemyList.RemoveAt(tmpEnemyPos);
					delete enemy;
					enemy = NULL;
					break;
				}
			}

			// 战机吃到补给包
			supplyPos = supplyList.GetHeadPosition(), tmpSupplyPos = supplyPos;
			while (supplyPos != NULL) {
				tmpSupplyPos = supplyPos;
				CSupply* supply = (CSupply*)supplyList.GetNext(supplyPos);
				CRect tmpRect;
				if (tmpRect.IntersectRect(&(myplane->GetRect()), &(supply->GetRect()))) {
					// 战机和补给包区域有重合，即战机吃到补给包
					myplane->increaseHp(supply->getHp());
					supplyList.RemoveAt(tmpSupplyPos);
					delete supply;
					supply = NULL;
					break;
				}
			}
		}

		// 游戏界面输出该游戏当前信息
		if (myplane != NULL) {
			HFONT font;
			font = CreateFont(20, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
			cdc.SelectObject(font);
			CString str;
			cdc.SetTextColor(RGB(255, 0, 0));
			// 设置透明背景
			cdc.SetBkMode(TRANSPARENT);
			cdc.SelectObject(font);
			cdc.SetTextColor(RGB(255, 0, 0));
			cdc.TextOutW(rect.right - 12 * PLANE_HP - 80, 0, _T("血量："));
			str.Format(_T("当前得分：%d"), myScore);
			cdc.TextOutW(rect.right - 12 * PLANE_HP - 80, 20, str);
			str.Format(_T("历史最高得分：%d"), maxScore);
			cdc.TextOutW(rect.right - 12 * PLANE_HP - 80, 40, str);
			// 输出血条
			CBrush brush;
			brush.CreateSolidBrush(RGB(255, 0, 0));
			CBrush* oldBrush = cdc.SelectObject(&brush);
			int leftPos, topPos = 0, rightPos, buttomPos = 12;
			leftPos = rect.right - 12 * PLANE_HP;
			rightPos = leftPos + 12 * myplane->getHp();
			cdc.Rectangle(leftPos, topPos, rightPos, buttomPos);
			brush.DeleteObject();

			// 输出血条中的详细血值
			HFONT textFont;
			textFont = CreateFont(12, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
			cdc.SelectObject(textFont);
			cdc.SetTextColor(RGB(255, 255, 255));
			str.Format(_T("%d/%d"), myplane->getHp(), PLANE_HP);
			cdc.TextOutW(rect.right - 12 * PLANE_HP + 12 * 4, 0, str);
		}

		if (myplane != NULL && !myplane->isAlive()) {
			gameOver(pDC, cdc, cacheBitmap);
			isOver = true;
		}
	}
	else if (isOver) {
		// 游戏结束
		HFONT textFont;
		textFont = CreateFont(18, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(textFont);
		// 设置透明背景
		cdc.SetBkMode(TRANSPARENT);
		cdc.SetTextColor(RGB(255, 255, 255));
		// 显示最后结果
		CString str;
		cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2 - 60, _T("GAME OVER"));
		if (myScore > maxScore) {
			cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2 - 30, _T("太棒了！新的得分纪录！"));
			str.Format(_T("您的得分为：%d"), myScore);
			cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2, str);
			cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2 + 30, _T("再接再厉！"));
			cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2 + 60, _T("是否重新开始？Y/N"));
			maxScore = myScore;
			CAircraftBattleDoc* pDoc = GetDocument();
			ASSERT_VALID(pDoc);
			if (!pDoc)
				return;
			pDoc->setMaxScore(maxScore);
		}
		else {
			str.Format(_T("您的得分为：%d"), myScore);
			cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2 - 30, str);
			cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2, _T("不要灰心！再来一次！"));
			cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2 + 30, _T("是否重新开始？Y/N"));
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
	if (!isStarted) {
		if (GetKeyState(VK_SPACE) < 0) {
			isStarted = true;
		}
	}
	else if (!isOver) {
		if (myplane != NULL && GetKeyState(VK_SPACE) < 0) {
			// 按空格键发射子弹
			CBullet* bullet1, * bullet2, * bullet3;
			bullet1 = bullet2 = bullet3 = nullptr;
			if (myScore < 100) {
				bullet1 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2, myplane->GetPoint().y, myplane->getDamage(), 0, 30, true, 2);
				myBulletList.AddTail(bullet1);
			}
			else if (myScore < 300) {
				bullet1 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2 - 15, myplane->GetPoint().y, myplane->getDamage(), 0, 30, true, 2);
				bullet2 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2 + 15, myplane->GetPoint().y, myplane->getDamage(), 0, 30, true, 2);
				myBulletList.AddTail(bullet1);
				myBulletList.AddTail(bullet2);
			}
			else {
				bullet1 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2, myplane->GetPoint().y, myplane->getDamage(), 0, 30, true, 2);
				bullet2 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2 - 10, myplane->GetPoint().y, myplane->getDamage(), 10, 30, true, 2);
				bullet3 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2 + 10, myplane->GetPoint().y, myplane->getDamage(), -10, 30, true, 2);
				myBulletList.AddTail(bullet1);
				myBulletList.AddTail(bullet2);
				myBulletList.AddTail(bullet3);
			}
		}
	}
	else {
		ASSERT(isOver);
		if (GetKeyState('Y') < 0) {
			isOver = false;
			Restart();
		}
		else if (GetKeyState('N') < 0) {
			MyDialog dlg;
			dlg.DoModal();
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
		myplane->SetPoint(point.x - PLANE_WIDTH / 2, point.y - PLANE_HEIGHT / 2);
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
		CBullet* bullet1, * bullet2, * bullet3;
		bullet1 = bullet2 = bullet3 = nullptr;
		if (myScore < 100) {
			bullet1 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2, myplane->GetPoint().y, myplane->getDamage(), 0, 30, true, 2);
			myBulletList.AddTail(bullet1);
		}
		else if (myScore < 300) {
			bullet1 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2 - 15, myplane->GetPoint().y, myplane->getDamage(), 0, 30, true, 2);
			bullet2 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2 + 15, myplane->GetPoint().y, myplane->getDamage(), 0, 30, true, 2);
			myBulletList.AddTail(bullet1);
			myBulletList.AddTail(bullet2);
		}
		else {
			bullet1 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2, myplane->GetPoint().y, myplane->getDamage(), 0, 30, true, 2);
			bullet2 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2 - 10, myplane->GetPoint().y, myplane->getDamage(), 10, 30, true, 2);
			bullet3 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2 + 10, myplane->GetPoint().y, myplane->getDamage(), -10, 30, true, 2);
			myBulletList.AddTail(bullet1);
			myBulletList.AddTail(bullet2);
			myBulletList.AddTail(bullet3);
		}
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
	// 重新加载战机
	myplane = new CMyPlane();

	// 清空敌机链表
	if (enemyList.GetCount() > 0)
		enemyList.RemoveAll();
	// 清空战机子弹链表
	if (myBulletList.GetCount() > 0)
		myBulletList.RemoveAll();
	// 清空敌机子弹列表
	if (enemyBulletList.GetCount() > 0)
		enemyBulletList.RemoveAll();

	//参数重新初始化
	isPause = false;
	isOver = false;
	myScore = 0;
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
	KillTimer(5);
	KillTimer(6);
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
	SetTimer(1, 17, NULL);		//刷新界面定时器
	SetTimer(2, 600, NULL);		//产生敌机定时器
	SetTimer(3, 2000, NULL);	//产生敌机子弹定时器
	SetTimer(5, 1200, NULL);	//产生高级敌机定时器
	SetTimer(6, 5000, NULL);	//产生补给包敌机定时器
}
