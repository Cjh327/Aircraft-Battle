
// AircraftBattleView.cpp : CAircraftBattleView ���ʵ��
//

#include "stdafx.h"
#include <mmsystem.h>
#include <iostream>
#pragma comment(lib, "WINMM.LIB")
#include <MMSYSTEM.H>
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
#include <cassert>


// CAircraftBattleView

IMPLEMENT_DYNCREATE(CAircraftBattleView, CView)

BEGIN_MESSAGE_MAP(CAircraftBattleView, CView)
	// ��׼��ӡ����
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

// CAircraftBattleView ����/����

CAircraftBattleView::CAircraftBattleView()
{
	//Ĭ��ս�������ٶȡ�ս������ֵ��ս���÷֡��ؿ����Ƿ���ء��Ƿ���ͣ

	// TODO: �ڴ˴���ӹ������
}

CAircraftBattleView::~CAircraftBattleView()
{
}

BOOL CAircraftBattleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CAircraftBattleView ����
void CAircraftBattleView::OnDraw(CDC* pDC)
{
	CAircraftBattleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

// CAircraftBattleView ��ӡ

void CAircraftBattleView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CAircraftBattleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CAircraftBattleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CAircraftBattleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CAircraftBattleView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// CAircraftBattleView ���

#ifdef _DEBUG
void CAircraftBattleView::AssertValid() const
{
	CView::AssertValid();
}

void CAircraftBattleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAircraftBattleDoc* CAircraftBattleView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAircraftBattleDoc)));
	return (CAircraftBattleDoc*)m_pDocument;
}
#endif //_DEBUG

//��дʵ��

// CAircraftBattleView ��Ϣ�������
//��ͼ��������
int CAircraftBattleView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	//-----------��ʼ������------------
	//������Ϸ����ͼƬ
	CMyPlane::LoadImage();
	CMyPlane::LoadImageProtect();
	CEnemy::LoadImage();
	CBullet::LoadImage();
	//���ر���ͼƬ
	CBitmap startbmp;
	startbmp.LoadBitmapW(IDB_BMP_TITLE);
	startIMG.Create(346, 96, ILC_COLOR24 | ILC_MASK, 1, 0);
	startIMG.Add(&startbmp, RGB(0, 0, 0));

	//������ʼ��ʧ��
	if (!scene.InitScene()) {
		AfxMessageBox(L"ͼƬ��Դ����ʧ��");
		exit(0);
	}

	//������ʼ��
	myplane = new CMyPlane(false);
	isStarted = false;
	isPause = false;
	isOver = false;
	myScore = 0;

	SetTimer(4, 40, NULL);//����������ʱ��
	SetMyTimer();
	return 0;
}

//��ʱ������
void CAircraftBattleView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//˫����
	CDC* pDC = GetDC();
	if (pDC == NULL) {
		CView::OnTimer(nIDEvent);
		return;
	}
	//��ÿͻ�����������
	GetClientRect(&rect);
	//�ڴ滺��CDC
	CDC cdc;

	//�ڴ��г�����ʱͼ��Ļ���λͼ
	CBitmap* cacheBitmap = new CBitmap;
	//�õ�ǰ�豸CDC��ʼ������CDC
	cdc.CreateCompatibleDC(pDC);
	//��pDC�ͻ���λͼ�Ĺ�ϵ��cdc�����������λͼ�У�������֮����һ���Խ�����λͼ�������Ļ
	cacheBitmap->CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	//�滻cdcԭ���Ļ�����Ϊ����λͼ������cdc��������ݾ�д���˻���λͼ��
	CBitmap* pOldBit = cdc.SelectObject(cacheBitmap);

	if (!isStarted && !isOver) {
		//��ӭ����
		scene.StickScene(&cdc, 0, rect);
		startIMG.Draw(&cdc, 0, CPoint(rect.right / 2 - 173, 100), ILD_TRANSPARENT);
		//����͸������
		cdc.SetBkMode(TRANSPARENT);
		HFONT tipFont;
		tipFont = CreateFont(30, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(tipFont);
		cdc.SetTextColor(RGB(0, 0, 0));
		cdc.TextOutW(rect.right / 2 - 200, 210, _T("�����������ո����ʼ��Ϸ"));
		HFONT textFont;
		textFont = CreateFont(18, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(textFont);
		cdc.SetTextColor(RGB(128, 128, 0));
		const int space = 30, off = 180;
		cdc.TextOutW(rect.right / 2 - off, 210 + space, _T("������ƣ��������ASDW�����"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 2 * space, _T("������ո����������"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 3 * space, _T("��ͣ��Q��"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 4 * space, _T("ս��������V��"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 5 * space, _T("�޵�ģʽ��Y��"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 6 * space, _T("��ʼ����ֵ��10"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 7 * space, _T("�л�����ֵ��2"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 11 * space, _T("����һ���л���1�֣���������ﵽҪ�󼴿ɽ���Bossģʽ����ӮBoss���ɽ�����һ�ء�"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 12 * space, _T("ħ��ֵ������Ϸ�������ӣ���ͨ��ʹ��ħ��ֵʹ�÷����֡�ս��������ս�����е�ʹ�á�"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 13 * space, _T("��Ϸ�����л���һ���̶ȵ�Ѫ�������Իָ�����ֵ��"));
		cdc.TextOutW(rect.right / 2 - off, 210 + 14 * space, _T("���Źؿ����࣬�л����ڵ��ٶȺ����������ӣ�ͨ��10�ؼ���ͨ�أ�"));
	}
	else if (isStarted && !isOver) {
		// ��Ϸ����
		scene.StickScene(&cdc, 1, rect);
		if (nIDEvent == 4) {
			//��������
			scene.MoveBg();
		}
		// ˢ����ʾս��
		if (myplane != NULL) {
			myplane->Draw(&cdc, FALSE, FALSE);
		}
		// �����ӵл�,�л��������ը��
		if (myplane != NULL && !isPause) {
			// �л�������ʱ������
			if (nIDEvent == 2) {
				CEnemy* enemy = new CEnemy(rect.right, rect.bottom);
				enemyList.AddTail(enemy);	//��������л�
			}
		}

		// �����߽�ĵл���������
		POSITION stPos = NULL, tPos = NULL;
		stPos = enemyList.GetHeadPosition();
		while (stPos != NULL) {
			tPos = stPos;
			CEnemy* enemy = (CEnemy*)enemyList.GetNext(stPos);
			// �жϵл��Ƿ����
			if (enemy->GetPoint().x < rect.left || enemy->GetPoint().x > rect.right
				|| enemy->GetPoint().y < rect.top || enemy->GetPoint().y > rect.bottom) {
				enemyList.RemoveAt(tPos);
				delete enemy;
			}
			else {
				//û���磬����
				enemy->Draw(&cdc, 1, FALSE);
				if (nIDEvent == 3) {
					CBullet* bullet = new CBullet(enemy->GetPoint().x + ENEMY_WIDTH / 2 - BULLET_WIDTH / 2, enemy->GetPoint().y + ENEMY_HEIGHT, enemy->getDamage(), 0, -5, false);
					bulletList.AddTail(bullet);	//��������ӵ�
				}
			}
		}

		// ս�������ӵ��������߽���ӵ���������
		stPos = NULL, tPos = NULL;
		stPos = bulletList.GetHeadPosition();
		while (stPos != NULL) {
			tPos = stPos;
			CBullet* bullet = (CBullet*)bulletList.GetNext(stPos);
			// �ж��ӵ��Ƿ����
			if (bullet->GetPoint().x < rect.left || bullet->GetPoint().x > rect.right
				|| bullet->GetPoint().y < rect.top || bullet->GetPoint().y > rect.bottom) {
				bulletList.RemoveAt(tPos);
				delete bullet;
			}
			else {
				// û���磬����
				bullet->Draw(&cdc, FALSE);
			}
		}


		// �ӵ����зɻ�
		POSITION bulletPos = bulletList.GetHeadPosition(), tmpBulletPos = bulletPos;
		while (bulletPos != NULL) {
			tmpBulletPos = bulletPos;
			CBullet* bullet = (CBullet*)bulletList.GetNext(bulletPos);
			if (bullet->getFromMe()) {
				POSITION enemyPos = enemyList.GetHeadPosition(), tmpEnemyPos = enemyPos;
				while (enemyPos != NULL) {
					tmpEnemyPos = enemyPos;
					CEnemy* enemy = (CEnemy*)enemyList.GetNext(enemyPos);
					CRect tmpRect;
					if (tmpRect.IntersectRect(&(bullet->GetRect()), &(enemy->GetRect()))) {
						// ս���ӵ��͵л��������غϣ���ս���ӵ����ел�
						bulletList.RemoveAt(tmpBulletPos);
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
			else {
				CRect tmpRect;
				if (tmpRect.IntersectRect(&(bullet->GetRect()), &(myplane->GetRect()))) {
					// �л��ӵ���ս���������غϣ����л��ӵ�����ս��
					bulletList.RemoveAt(tmpBulletPos);
					myplane->decreaseHp(bullet->getDamage());
					delete bullet;
					bullet = NULL;
				}

			}
		}

		// ս��ײ���л�
		POSITION enemyPos = enemyList.GetHeadPosition(), tmpEnemyPos = enemyPos;
		while (enemyPos != NULL) {
			tmpEnemyPos = enemyPos;
			CEnemy* enemy = (CEnemy*)enemyList.GetNext(enemyPos);
			CRect tmpRect;
			if (tmpRect.IntersectRect(&(myplane->GetRect()), &(enemy->GetRect()))) {
				// ս���͵л��������غϣ���ս��ײ���л�
				myplane->decreaseHp(2 * enemy->getDamage());
				myScore += enemy->getScore();
				enemyList.RemoveAt(tmpEnemyPos);
				delete enemy;
				enemy = NULL;
				break;
			}
		}

		//��Ϸ�����������Ϸ��ǰ��Ϣ
		if (myplane != NULL)
		{
			HFONT font;
			font = CreateFont(20, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
			cdc.SelectObject(font);
			CString str;
			cdc.SetTextColor(RGB(255, 0, 0));
			//����͸������
			cdc.SetBkMode(TRANSPARENT);

			cdc.SelectObject(font);
			cdc.SetTextColor(RGB(255, 0, 0));
			cdc.TextOutW(rect.right - 12 * PLANE_HP - 60, 0, _T("Ѫ����"));
			str.Format(_T("�÷֣�%d"), myScore);
			cdc.TextOutW(rect.right - 12 * PLANE_HP - 60, 20, str);
			//���Ѫ��
			CBrush brush;
			brush.CreateSolidBrush(RGB(255, 0, 0));
			CBrush* oldBrush = cdc.SelectObject(&brush);
			int leftPos, topPos = 0, rightPos, buttomPos = 12;
			leftPos = rect.right - 12 * PLANE_HP;
			rightPos = leftPos + 12 * myplane->getHp();
			cdc.Rectangle(leftPos, topPos, rightPos, buttomPos);
			brush.DeleteObject();

			//���Ѫ���е���ϸѪֵ
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
		// ��Ϸ����
		HFONT textFont;
		textFont = CreateFont(18, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(textFont);
		//����͸������
		cdc.SetBkMode(TRANSPARENT);
		cdc.SetTextColor(RGB(255, 255, 255));
		//��ʾ�����
		CString str;
		cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2 - 30, _T("GAME OVER��"));
		str.Format(_T("���ĵ÷�Ϊ��%d"), myScore);
		cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2 - 5, str);
		cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2 + 30, _T("��Ҫ���ģ�����һ�Σ�"));
		cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2 + 55, _T("�Ƿ����¿�ʼ��Y/N"));
	}

	//����������cdc�е��������͵�һ��������pDC�У����������Ļ��
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &cdc, 0, 0, SRCCOPY);
	//�ͷŶ���cdc
	cdc.DeleteDC();
	//�ͷŻ���λͼ
	cacheBitmap->DeleteObject();
	//�ͷ�һ��pDC
	ReleaseDC(pDC);
	CView::OnTimer(nIDEvent);
}

//���̰��¼���
void CAircraftBattleView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//���ո������Ϸ
	if (!isStarted) {
		if (GetKeyState(VK_SPACE) < 0) {
			isStarted = true;
		}
	}
	else if (!isOver) {
		if (myplane != NULL && GetKeyState(VK_SPACE) < 0) {
			// ���ո�������ӵ�
			CBullet* bullet1, * bullet2, * bullet3;
			bullet1 = bullet2 = bullet3 = nullptr;
			if (myScore < 100) {
				bullet1 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2, myplane->GetPoint().y, myplane->getDamage(), 0, 30, true);
				bulletList.AddTail(bullet1);
			}
			else if (myScore < 300) {
				bullet1 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2 - 15, myplane->GetPoint().y, myplane->getDamage(), 0, 30, true);
				bullet2 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2 + 15, myplane->GetPoint().y, myplane->getDamage(), 0, 30, true);
				bulletList.AddTail(bullet1);
				bulletList.AddTail(bullet2);
			}
			else {
				bullet1 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2, myplane->GetPoint().y, myplane->getDamage(), 0, 30, true);
				bullet2 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2 - 10, myplane->GetPoint().y, myplane->getDamage(), 10, 30, true);
				bullet3 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2 + 10, myplane->GetPoint().y, myplane->getDamage(), -10, 30, true);
				bulletList.AddTail(bullet1);
				bulletList.AddTail(bullet2);
				bulletList.AddTail(bullet3);
			}
		}
	}
	else {
		assert(isOver);
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

//����ƶ�����������ս��λ��
void CAircraftBattleView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (myplane != NULL && isPause == 0) {
		//��������Ϸ����
		myplane->SetPoint(point.x - PLANE1_WIDTH / 2, point.y - PLANE1_HEIGHT / 2);
	}
	CView::OnMouseMove(nFlags, point);
}

//��������������
void CAircraftBattleView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (isStarted == FALSE) {
		isStarted = TRUE;
	}
	else if (myplane != NULL) {
		// �������������ӵ�
		CBullet* bullet1, * bullet2, * bullet3;
		bullet1 = bullet2 = bullet3 = nullptr;
		if (myScore < 100) {
			bullet1 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2, myplane->GetPoint().y, myplane->getDamage(), 0, 30, true);
			bulletList.AddTail(bullet1);
		}
		else if (myScore < 300) {
			bullet1 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2 - 15, myplane->GetPoint().y, myplane->getDamage(), 0, 30, true);
			bullet2 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2 + 15, myplane->GetPoint().y, myplane->getDamage(), 0, 30, true);
			bulletList.AddTail(bullet1);
			bulletList.AddTail(bullet2);
		}
		else {
			bullet1 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2, myplane->GetPoint().y, myplane->getDamage(), 0, 30, true);
			bullet2 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2 - 10, myplane->GetPoint().y, myplane->getDamage(), 10, 30, true);
			bullet3 = new CBullet(myplane->GetPoint().x + PLANE_WIDTH / 2 - BULLET_WIDTH / 2 + 10, myplane->GetPoint().y, myplane->getDamage(), -10, 30, true);
			bulletList.AddTail(bullet1);
			bulletList.AddTail(bullet2);
			bulletList.AddTail(bullet3);
		}
	}

	CView::OnLButtonDown(nFlags, point);
}

//����Ҽ�����
void CAircraftBattleView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	if (isStarted == TRUE && myplane != NULL) {
		// ������Ҽ������ڵ�
		// MyTODO
	}
}

//��������

//��������
void CAircraftBattleView::OnDestroy()
{
	// ����ָ����Դ
	if (myplane != NULL)
		delete myplane;

	//�ͷ��ڴ���Դ
	scene.ReleaseScene();

	CView::OnDestroy();
}

//��Ϸ���¿�ʼ
void CAircraftBattleView::Restart()
{
	// TODO: �ڴ˴������Ϸ���¿�ʼ��ʼ������
	//ս�����¼���
	myplane = new CMyPlane(FALSE);

	//��յл�����
	if (enemyList.GetCount() > 0)
		enemyList.RemoveAll();
	//���ս���ӵ�����
	if (bulletList.GetCount() > 0)
		bulletList.RemoveAll();

	//�������³�ʼ��
	isPause = false;
	isOver = false;
	myScore = 0;
	//isStarted = FALSE;
	SetMyTimer();
}

//��Ϸ��ͣ
void CAircraftBattleView::Pause()
{
	// TODO: �ڴ˴������Ϸ��ͣ����
	isPause = TRUE;
	Sleep(1000);
}

// ����ֵ���㣬��Ϸ����
void CAircraftBattleView::gameOver(CDC* pDC, CDC& cdc, CBitmap* cacheBitmap)
{
	//������Ϸ����
	//�ͷż�ʱ��
	KillTimer(1);
	KillTimer(2);
	KillTimer(3);
	//KillTimer(4);
	KillTimer(5);
	//������Ϸ��������
	PlaySound((LPCTSTR)IDR_WAV_GAMEOVER, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
	//����
	CBitmap* tCache = cacheBitmap;
	cacheBitmap = new CBitmap;
	cacheBitmap->CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	cdc.SelectObject(cacheBitmap);
	//�ڴ��г�����ʱͼ��Ļ���λͼ
	delete tCache;
	//isStop = FLAG_STOP;
}

//���ü�ʱ��
void CAircraftBattleView::SetMyTimer()
{
	SetTimer(1, 17, NULL);//ˢ�½��涨ʱ��
	SetTimer(2, 400 - 1 * 30, NULL);//�����л���ʱ��
	SetTimer(3, 2000 - 2 * 100, NULL);//�����л��ڵ�Ƶ��

	SetTimer(5, 2000, NULL);//����ħ��ֵ�仯Ƶ��
}

//void CAircraftBattleView::OnClose()
//{
//	isPause = TRUE;
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	KillTimer(1);
//	KillTimer(2);
//	KillTimer(3);
//	KillTimer(4);
//	KillTimer(5 );
//	CView::OnClose();
//}
