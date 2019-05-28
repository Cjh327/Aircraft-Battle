
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
	ON_WM_TIMER()
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
	
	//参数初始化
	//myplane = new CMyplane(FALSE);
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
	//bossBlood = BOSS_LIFE;
	isProtect = FALSE;
	isUpdate = FALSE;
	test = FALSE;
	isStop = FALSE;
	//boss = NULL;
	isStarted = FALSE;
	
	//SetTimer(4, 40, NULL);//背景滚动定时器
	//SetMyTimer();
	return 0;
}


//设置计时器
void CMFCApplication4View::SetMyTimer()
{
	SetTimer(1, 17, NULL);//刷新界面定时器
	SetTimer(2, 400 - passNum * 30, NULL);//产生敌机定时器
	SetTimer(3, 2000 - passNum * 100, NULL);//产生敌机炮弹频率

	SetTimer(5, 2000, NULL);//控制魔法值变化频率
}



void CMFCApplication4View::OnTimer(UINT_PTR nIDEvent)
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

	//输出背景
	if (isStarted == FALSE)
		scene.StickScene(&cdc, -1, rect);
	else
		scene.StickScene(&cdc, passNum, rect);
	if (nIDEvent == 4) {
		//滚动背景
		scene.MoveBg();
	}
	//欢迎界面
	if (isStarted == FALSE) {
		startIMG.Draw(&cdc, 0, CPoint(rect.right / 2/* - 173*/, 100), ILD_TRANSPARENT);
		HFONT textFont;
		textFont = CreateFont(12, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(textFont);
		cdc.SetTextColor(RGB(128, 128, 0));
		//设置透明背景
		cdc.SetBkMode(TRANSPARENT);
		cdc.TextOutW(rect.right / 2 - 120, 210, _T("方向控制：方向键、ASDW、鼠标"));
		cdc.TextOutW(rect.right / 2 - 120, 225, _T("射击：空格键、鼠标左键"));
		cdc.TextOutW(rect.right / 2 - 120, 240, _T("暂停：Z键"));
		cdc.TextOutW(rect.right / 2 - 120, 255, _T("大招：X键"));
		cdc.TextOutW(rect.right / 2 - 120, 270, _T("防护罩：C键"));
		cdc.TextOutW(rect.right / 2 - 120, 285, _T("战机升级：V键"));
		cdc.TextOutW(rect.right / 2 - 120, 300, _T("无敌模式：Y键"));
		cdc.TextOutW(rect.right / 2 - 120, 315, _T("初始生命值：10"));
		cdc.TextOutW(rect.right / 2 - 120, 330, _T("初始魔法值：0"));
		cdc.TextOutW(rect.right / 2 - 120, 345, _T("敌机生命值：2"));
		cdc.TextOutW(rect.right / 2 - 120, 360, _T("消灭一个敌机加1分，如果分数达到要求即可进入Boss模式，打赢Boss即可进入下一关。"));
		cdc.TextOutW(rect.right / 2 - 120, 375, _T("魔法值随着游戏进程增加，可通过使用魔法值使用防护罩、战机升级、战机大招的使用。"));
		cdc.TextOutW(rect.right / 2 - 120, 390, _T("游戏过程中会有一定程度的血包出现以恢复生命值。"));
		cdc.TextOutW(rect.right / 2 - 120, 405, _T("随着关卡增多，敌机、炮弹速度和数量均增加，通过10关即可通关！"));
		HFONT tipFont;
		tipFont = CreateFont(24, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(tipFont);
		cdc.SetTextColor(RGB(255, 0, 0));
		cdc.TextOutW(rect.right / 2 - 120, 420, _T("点击鼠标左键或空格键开始游戏"));
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
	//显示暂停信息
	if (myplane != NULL && isPause == TRUE && isStop == FALSE) {
		HFONT textFont;
		textFont = CreateFont(24, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(textFont);
		cdc.SetTextColor(RGB(255, 0, 0));
		//设置透明背景
		cdc.SetBkMode(TRANSPARENT);
		cdc.TextOutW(rect.right / 2 - 10, 150, _T("暂停"));
		////将二级缓冲cdc中的数据推送到一级级缓冲pDC中，即输出到屏幕中
		//pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &cdc, 0, 0, SRCCOPY);
		////释放二级cdc
		//cdc.DeleteDC();
		////释放缓冲位图
		//cacheBitmap->DeleteObject();
		////释放一级pDC
		//ReleaseDC(pDC);
		//CView::OnTimer(nIDEvent);
		//return;
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
