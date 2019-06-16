
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
#include "CSupply.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
	maxScore = pDoc->getMaxScore();

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
	CEnemy::LoadImage();
	CBullet::LoadImage();
	CSupply::LoadImage();
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
	myplane = new CMyPlane();
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
		cdc.TextOutW(rect.right / 2 - 200, 220, _T("�����������ո����ʼ��Ϸ"));
		cdc.SetTextColor(RGB(0, 0, 255));
		CString str;
		str.Format(_T("��߼�¼��%d"), maxScore);
		cdc.TextOutW(rect.right / 2 - 100, 270, str);
		HFONT textFont;
		textFont = CreateFont(24, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(textFont);
		cdc.SetTextColor(RGB(255, 255, 0));
		const int space = 30, off = 200;
		cdc.TextOutW(rect.right / 2 - off, 400, _T("������ƣ����"));
		cdc.TextOutW(rect.right / 2 - off, 400 + 1 * space, _T("������ո����������"));
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
			myplane->Draw(&cdc, FALSE);
		}
		// ��������л��Ͳ�����
		if (myplane != NULL && !isPause) {
			// �л�������ʱ������
			if (nIDEvent == 2) {
				// ���������ͨ�л�
				CEnemy* enemy = new CEnemy(rect.right, rect.bottom, 1);
				enemyList.AddTail(enemy);
			}
			if (nIDEvent == 5) {
				// ��������߼��л�
				CEnemy* enemy = new CEnemy(rect.right, rect.bottom, 2);
				enemyList.AddTail(enemy);
			}
			if (nIDEvent == 6) {
				// �������������
				CSupply* supply = new CSupply(rect.right, rect.bottom);
				supplyList.AddTail(supply);
			}
		}

		if (myplane != NULL && !isPause) {
			// ���Ʋ�����
			POSITION supplyPos = supplyList.GetHeadPosition(), tmpSupplyPos;
			while (supplyPos != NULL) {
				CSupply* supply = (CSupply*)supplyList.GetNext(supplyPos);
				supply->Draw(&cdc, FALSE);
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
					// û���������
					enemy->Draw(&cdc, FALSE);
					if (nIDEvent == 3) {
						CBullet* bullet = new CBullet(enemy->GetPoint().x + ENEMY_WIDTH / 2 - BULLET_WIDTH / 2, enemy->GetPoint().y + ENEMY_HEIGHT, enemy->getDamage(), 0, -5, false, enemy->getIndex());
						enemyBulletList.AddTail(bullet);
					}
				}
			}

			// �����ӵ��������߽���ӵ���������
			stPos = NULL, tPos = NULL;
			stPos = enemyBulletList.GetHeadPosition();
			while (stPos != NULL) {
				tPos = stPos;
				CBullet* bullet = (CBullet*)enemyBulletList.GetNext(stPos);
				// �ж��ӵ��Ƿ����
				if (bullet->GetPoint().x < rect.left || bullet->GetPoint().x > rect.right
					|| bullet->GetPoint().y < rect.top || bullet->GetPoint().y > rect.bottom) {
					enemyBulletList.RemoveAt(tPos);
					delete bullet;
				}
				else {
					// û���磬����
					bullet->Draw(&cdc, FALSE);
				}
			}
			stPos = NULL, tPos = NULL;
			stPos = myBulletList.GetHeadPosition();
			while (stPos != NULL) {
				tPos = stPos;
				CBullet* bullet = (CBullet*)myBulletList.GetNext(stPos);
				// �ж��ӵ��Ƿ����
				if (bullet->GetPoint().x < rect.left || bullet->GetPoint().x > rect.right
					|| bullet->GetPoint().y < rect.top || bullet->GetPoint().y > rect.bottom) {
					myBulletList.RemoveAt(tPos);
					delete bullet;
				}
				else {
					// û���磬����
					bullet->Draw(&cdc, FALSE);
				}
			}

			// ս���ӵ����ел�
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
						// ս���ӵ��͵л��������غϣ���ս���ӵ����ел�
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

			// �л��ӵ�����ս��
			bulletPos = enemyBulletList.GetHeadPosition(), tmpBulletPos = bulletPos;
			while (bulletPos != NULL) {
				tmpBulletPos = bulletPos;
				CBullet* bullet = (CBullet*)enemyBulletList.GetNext(bulletPos);
				ASSERT(!bullet->getFromMe());
				CRect tmpRect;
				if (tmpRect.IntersectRect(&(bullet->GetRect()), &(myplane->GetRect()))) {
					// �л��ӵ���ս���������غϣ����л��ӵ�����ս��
					enemyBulletList.RemoveAt(tmpBulletPos);
					myplane->decreaseHp(bullet->getDamage());
					delete bullet;
					bullet = NULL;
				}
			}

			// �ӵ������ӵ�
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
						// ս���ӵ��͵л��ӵ����غϣ���ս���ӵ����ел��ӵ�
						myBulletList.RemoveAt(tmpBulletPos);
						enemyBulletList.RemoveAt(tmpBulletPos1);
						delete myBullet;
						delete enemyBullet;
						myBullet = enemyBullet = NULL;
						break;
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

			// ս���Ե�������
			supplyPos = supplyList.GetHeadPosition(), tmpSupplyPos = supplyPos;
			while (supplyPos != NULL) {
				tmpSupplyPos = supplyPos;
				CSupply* supply = (CSupply*)supplyList.GetNext(supplyPos);
				CRect tmpRect;
				if (tmpRect.IntersectRect(&(myplane->GetRect()), &(supply->GetRect()))) {
					// ս���Ͳ������������غϣ���ս���Ե�������
					myplane->increaseHp(supply->getHp());
					supplyList.RemoveAt(tmpSupplyPos);
					delete supply;
					supply = NULL;
					break;
				}
			}
		}

		// ��Ϸ�����������Ϸ��ǰ��Ϣ
		if (myplane != NULL) {
			HFONT font;
			font = CreateFont(20, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
			cdc.SelectObject(font);
			CString str;
			cdc.SetTextColor(RGB(255, 0, 0));
			// ����͸������
			cdc.SetBkMode(TRANSPARENT);
			cdc.SelectObject(font);
			cdc.SetTextColor(RGB(255, 0, 0));
			cdc.TextOutW(rect.right - 12 * PLANE_HP - 80, 0, _T("Ѫ����"));
			str.Format(_T("��ǰ�÷֣�%d"), myScore);
			cdc.TextOutW(rect.right - 12 * PLANE_HP - 80, 20, str);
			str.Format(_T("��ʷ��ߵ÷֣�%d"), maxScore);
			cdc.TextOutW(rect.right - 12 * PLANE_HP - 80, 40, str);
			// ���Ѫ��
			CBrush brush;
			brush.CreateSolidBrush(RGB(255, 0, 0));
			CBrush* oldBrush = cdc.SelectObject(&brush);
			int leftPos, topPos = 0, rightPos, buttomPos = 12;
			leftPos = rect.right - 12 * PLANE_HP;
			rightPos = leftPos + 12 * myplane->getHp();
			cdc.Rectangle(leftPos, topPos, rightPos, buttomPos);
			brush.DeleteObject();

			// ���Ѫ���е���ϸѪֵ
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
		// ����͸������
		cdc.SetBkMode(TRANSPARENT);
		cdc.SetTextColor(RGB(255, 255, 255));
		// ��ʾ�����
		CString str;
		cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2 - 60, _T("GAME OVER"));
		if (myScore > maxScore) {
			cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2 - 30, _T("̫���ˣ��µĵ÷ּ�¼��"));
			str.Format(_T("���ĵ÷�Ϊ��%d"), myScore);
			cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2, str);
			cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2 + 30, _T("�ٽ�������"));
			cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2 + 60, _T("�Ƿ����¿�ʼ��Y/N"));
			maxScore = myScore;
			CAircraftBattleDoc* pDoc = GetDocument();
			ASSERT_VALID(pDoc);
			if (!pDoc)
				return;
			pDoc->setMaxScore(maxScore);
		}
		else {
			str.Format(_T("���ĵ÷�Ϊ��%d"), myScore);
			cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2 - 30, str);
			cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2, _T("��Ҫ���ģ�����һ�Σ�"));
			cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2 + 30, _T("�Ƿ����¿�ʼ��Y/N"));
		}
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

//����ƶ�����������ս��λ��
void CAircraftBattleView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (myplane != NULL && isPause == 0) {
		//��������Ϸ����
		myplane->SetPoint(point.x - PLANE_WIDTH / 2, point.y - PLANE_HEIGHT / 2);
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
	// ���¼���ս��
	myplane = new CMyPlane();

	// ��յл�����
	if (enemyList.GetCount() > 0)
		enemyList.RemoveAll();
	// ���ս���ӵ�����
	if (myBulletList.GetCount() > 0)
		myBulletList.RemoveAll();
	// ��յл��ӵ��б�
	if (enemyBulletList.GetCount() > 0)
		enemyBulletList.RemoveAll();

	//�������³�ʼ��
	isPause = false;
	isOver = false;
	myScore = 0;
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
	KillTimer(5);
	KillTimer(6);
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
	SetTimer(1, 17, NULL);		//ˢ�½��涨ʱ��
	SetTimer(2, 600, NULL);		//�����л���ʱ��
	SetTimer(3, 2000, NULL);	//�����л��ӵ���ʱ��
	SetTimer(5, 1200, NULL);	//�����߼��л���ʱ��
	SetTimer(6, 5000, NULL);	//�����������л���ʱ��
}
