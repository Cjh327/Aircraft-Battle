
// MFCApplication4View.cpp: CMFCApplication4View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication4.h"
#endif

#include "MFCApplication4Doc.h"
#include "MFCApplication4View.h"

#include "CMyplane.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication4View

IMPLEMENT_DYNCREATE(CMFCApplication4View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication4View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMFCApplication4View 构造/析构

CMFCApplication4View::CMFCApplication4View() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCApplication4View::~CMFCApplication4View()
{
}

BOOL CMFCApplication4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCApplication4View 绘图

void CMFCApplication4View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCApplication4View 打印

BOOL CMFCApplication4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplication4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCApplication4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCApplication4View 诊断

#ifdef _DEBUG
void CMFCApplication4View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication4Doc* CMFCApplication4View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication4Doc)));
	return (CMFCApplication4Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication4View 消息处理程序

//视图创建监听
int CMFCApplication4View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	//-----------初始化工作------------
	//加载游戏对象图片
	
	CMyplane::LoadImage();
	/*CMyPlane::LoadImageProtect();
	CEnemy::LoadImage();
	CBoss::LoadImage();
	CBall::LoadImageUp();
	CBall::LoadImageDown();
	CBomb::LoadImage();
	CExplosion::LoadImage();
	CBlood::LoadImage();
	//加载标题图片
	CBitmap startbmp;
	startbmp.LoadBitmapW(IDB_BMP_TITLE);
	startIMG.Create(346, 96, ILC_COLOR24 | ILC_MASK, 1, 0);
	startIMG.Add(&startbmp, RGB(0, 0, 0));
	*/
	//场景初始化失败
	if (!scene.InitScene())
	{
		AfxMessageBox(L"图片资源加载失败");
		exit(0);
	}
	/*
	//参数初始化
	myplane = new CMyPlane(FALSE);
	isBoss = FALSE;
	speed = DEFAULT_SPEED;
	myLife = DEFAULT_LIFE;
	lifeNum = DEFAULT_LIFE_COUNT;
	lifeCount = 1;
	passScore = 0;
	myScore = 0;
	bossLoaded = TRUE;
	passNum = DEFAULT_PASS;
	isPass = 0;
	isPause = FALSE;
	magicCount = 0;
	bloodExist = FALSE;
	bossBlood = BOSS_LIFE;
	isProtect = FALSE;
	isUpdate = FALSE;
	test = FALSE;
	isStop = FALSE;
	boss = NULL;
	isStarted = FALSE;

	SetTimer(4, 40, NULL);//背景滚动定时器
	SetMyTimer();
	*/
	return 0;
	return 0;
}
