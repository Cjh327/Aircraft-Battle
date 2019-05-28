
// PlaneWarView.cpp : CPlaneWarView ���ʵ��
//

#include "stdafx.h"
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
#include <MMSYSTEM.H>
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "PlaneWar.h"
#endif
   
#include "PlaneWarDoc.h"
#include "PlaneWarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneWarView

IMPLEMENT_DYNCREATE(CPlaneWarView, CView)

BEGIN_MESSAGE_MAP(CPlaneWarView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPlaneWarView::OnFilePrintPreview)
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

// CPlaneWarView ����/����

CPlaneWarView::CPlaneWarView()
{
	//Ĭ��ս�������ٶȡ�ս������ֵ��ս���÷֡��ؿ����Ƿ���ء��Ƿ���ͣ

    // TODO: �ڴ˴���ӹ������
}

CPlaneWarView::~CPlaneWarView()
{
}

BOOL CPlaneWarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPlaneWarView ����
void CPlaneWarView::OnDraw(CDC* pDC)
{
	CPlaneWarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

// CPlaneWarView ��ӡ

void CPlaneWarView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPlaneWarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPlaneWarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPlaneWarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CPlaneWarView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// CPlaneWarView ���

#ifdef _DEBUG
void CPlaneWarView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneWarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneWarDoc* CPlaneWarView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneWarDoc)));
	return (CPlaneWarDoc*)m_pDocument;
}
#endif //_DEBUG

//��дʵ��
//����ٶ�
int CPlaneWarView::GetSpeed()
{
	return this->speed;
}
//�����ٶ�
void CPlaneWarView::SetSpeed(int speed)
{
	this->speed = speed;
}

// CPlaneWarView ��Ϣ�������
//��ͼ��������
int CPlaneWarView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	//-----------��ʼ������------------
	//������Ϸ����ͼƬ
	CMyPlane::LoadImage();
	CMyPlane::LoadImageProtect();
	//���ر���ͼƬ
	CBitmap startbmp;
	startbmp.LoadBitmapW(IDB_BMP_TITLE);
	startIMG.Create(346, 96, ILC_COLOR24 | ILC_MASK, 1, 0);
	startIMG.Add(&startbmp, RGB(0, 0, 0));
	
	//������ʼ��ʧ��
	if (!scene.InitScene())
	{
		AfxMessageBox(L"ͼƬ��Դ����ʧ��");
		exit(0);
	}

	//������ʼ��
	myplane = new CMyPlane(FALSE);
	isBoss = FALSE;
	speed = DEFAULT_SPEED;
	myLife = DEFAULT_LIFE;
	lifeNum = DEFAULT_LIFE_COUNT;
	lifeCount = 1;
	passScore = 0;
	myScore=0;
	bossLoaded = TRUE;
	passNum = DEFAULT_PASS;
	isPass = 0;
	isPause = FALSE;
	magicCount = 0;
	bloodExist = FALSE;
	isProtect = FALSE;
	isUpdate = FALSE;
	test = FALSE;
	isStop = FALSE;
	isStarted = FALSE;

	SetTimer(4, 40, NULL);//����������ʱ��
	SetMyTimer();
	return 0;
}

//��ʱ������
void CPlaneWarView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//˫����
	CDC *pDC = GetDC();
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
	CBitmap *pOldBit = cdc.SelectObject(cacheBitmap);

	//�������
	if (isStarted == FALSE)
		scene.StickScene(&cdc, -1, rect);
	else
		scene.StickScene(&cdc, passNum, rect);
	if (nIDEvent == 4) {
		//��������
		scene.MoveBg();
	}
	//��ӭ����
	if (isStarted == FALSE) {
		startIMG.Draw(&cdc, 0, CPoint(rect.right/2-173, 100), ILD_TRANSPARENT);
		HFONT textFont;
		textFont = CreateFont(12, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(textFont);
		cdc.SetTextColor(RGB(128, 128, 0));
		//����͸������
		cdc.SetBkMode(TRANSPARENT);
		cdc.TextOutW(rect.right/2-120, 210, _T("������ƣ��������ASDW�����"));
		cdc.TextOutW(rect.right/ 2 - 120, 225, _T("������ո����������"));
		cdc.TextOutW(rect.right / 2 - 120, 240, _T("��ͣ��Z��"));
		cdc.TextOutW(rect.right / 2 - 120, 255, _T("���У�X��"));
		cdc.TextOutW(rect.right / 2 - 120, 270, _T("�����֣�C��"));
		cdc.TextOutW(rect.right / 2 - 120, 285, _T("ս��������V��"));
		cdc.TextOutW(rect.right / 2 - 120, 300, _T("�޵�ģʽ��Y��"));
		cdc.TextOutW(rect.right / 2 - 120, 315, _T("��ʼ����ֵ��10"));
		cdc.TextOutW(rect.right / 2 - 120, 330, _T("��ʼħ��ֵ��0"));
		cdc.TextOutW(rect.right / 2 - 120, 345, _T("�л�����ֵ��2"));
		cdc.TextOutW(rect.right / 2 - 120, 360, _T("����һ���л���1�֣���������ﵽҪ�󼴿ɽ���Bossģʽ����ӮBoss���ɽ�����һ�ء�"));
		cdc.TextOutW(rect.right / 2 - 120, 375, _T("ħ��ֵ������Ϸ�������ӣ���ͨ��ʹ��ħ��ֵʹ�÷����֡�ս��������ս�����е�ʹ�á�"));
		cdc.TextOutW(rect.right / 2 - 120, 390, _T("��Ϸ�����л���һ���̶ȵ�Ѫ�������Իָ�����ֵ��"));
		cdc.TextOutW(rect.right / 2 - 120, 405, _T("���Źؿ����࣬�л����ڵ��ٶȺ����������ӣ�ͨ��10�ؼ���ͨ�أ�"));
		HFONT tipFont;
		tipFont = CreateFont(24, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(tipFont);
		cdc.SetTextColor(RGB(255, 0, 0));
		cdc.TextOutW(rect.right / 2 - 120, 420, _T("�����������ո����ʼ��Ϸ"));
		//����������cdc�е��������͵�һ��������pDC�У����������Ļ��
		pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &cdc, 0, 0, SRCCOPY);
		//�ͷŶ���cdc
		cdc.DeleteDC();
		//�ͷŻ���λͼ
		cacheBitmap->DeleteObject();
		//�ͷ�һ��pDC
		ReleaseDC(pDC);
		CView::OnTimer(nIDEvent);
		return;
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
void CPlaneWarView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//���ո������Ϸ
	if (isStarted == FALSE && (GetKeyState(VK_SPACE) < 0)) {
		isStarted = TRUE;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//����ƶ�����������ս��λ��
void CPlaneWarView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (myplane!=NULL && isPause == 0 ) {
		//��������Ϸ����
		myplane->SetPoint(point.x,point.y);
	}
	CView::OnMouseMove(nFlags, point);
}

//��������������
void CPlaneWarView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (isStarted == FALSE) {
		isStarted = TRUE;
	}

	CView::OnLButtonDown(nFlags, point);
}

//����Ҽ�����
void CPlaneWarView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
}

//��������

//��������
void CPlaneWarView::OnDestroy()
{
	// ����ָ����Դ
	if (myplane != NULL)
		delete myplane;

		//�ͷ��ڴ���Դ
	scene.ReleaseScene();

	CView::OnDestroy();
}

//��Ϸ���¿�ʼ
void CPlaneWarView::Restart()
{
	// TODO: �ڴ˴������Ϸ���¿�ʼ��ʼ������
	//ս�����¼���
	myplane = new CMyPlane(FALSE);

	//��յл�����
	if (enemyList.GetCount() > 0)
		enemyList.RemoveAll();
	//���ս������
	if (meList.GetCount() > 0)
		meList.RemoveAll();
	//���ս���ӵ�����
	if (bombList.GetCount() > 0)
		bombList.RemoveAll();
	//��յл�ը������
	if (ballList.GetCount() > 0)
		ballList.RemoveAll();
	//��ձ�ը����
	if (explosionList.GetCount() > 0)
		explosionList.RemoveAll();
	//���Ѫ���б�
	if (bloodList.GetCount() > 0)
		bloodList.RemoveAll();

	//�������³�ʼ��
	myLife = DEFAULT_LIFE;
	lifeNum = DEFAULT_LIFE_COUNT;
	myScore = 0;
	passScore = 0;
	passNum = DEFAULT_PASS;
	isPass = 0;
	isPause = 0;
	lifeCount = 1;
	magicCount = 0;
	bloodExist = FALSE;
	isBoss = FALSE;
	bossLoaded = TRUE;
	isProtect = FALSE;
	isUpdate = FALSE;
	test = FALSE;
	//isStarted = FALSE;
	SetMyTimer();
}

//��Ϸ��ͣ
void CPlaneWarView::Pause()
{
	// TODO: �ڴ˴������Ϸ��ͣ����
	isPause = TRUE;
	Sleep(1000);
}

// ����ֵ���㣬��Ϸ����
void CPlaneWarView::gameOver(CDC* pDC,CDC& cdc,CBitmap* cacheBitmap)
{
	//������Ϸ����
	//�ͷż�ʱ��
	KillTimer(1);
	KillTimer(2);
	KillTimer(3);
	//KillTimer(4);
	KillTimer(5);
	//�������÷�
	myScore += passScore;
	//������Ϸ��������
	PlaySound((LPCTSTR)IDR_WAV_GAMEOVER, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
	//����
	CBitmap* tCache = cacheBitmap;
	cacheBitmap = new CBitmap;
	cacheBitmap->CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	cdc.SelectObject(cacheBitmap);
	//�ڴ��г�����ʱͼ��Ļ���λͼ
	delete tCache;
	isStop = FLAG_STOP;
}

//���ü�ʱ��
void CPlaneWarView::SetMyTimer()
{
	SetTimer(1, 17, NULL);//ˢ�½��涨ʱ��
	SetTimer(2, 400-passNum*30, NULL);//�����л���ʱ��
	SetTimer(3, 2000- passNum * 100, NULL);//�����л��ڵ�Ƶ��
	
	SetTimer(5, 2000, NULL);//����ħ��ֵ�仯Ƶ��
}

//void CPlaneWarView::OnClose()
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
