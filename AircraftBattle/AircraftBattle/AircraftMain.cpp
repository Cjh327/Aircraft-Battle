// AircraftMain.cpp: 实现文件
//

#include "pch.h"
#include "AircraftBattle.h"
#include "AircraftMain.h"
#include "afxdialogex.h"


// AircraftMain 对话框

IMPLEMENT_DYNAMIC(AircraftMain, CDialogEx)

AircraftMain::AircraftMain(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

AircraftMain::~AircraftMain()
{
}

void AircraftMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BOOL AircraftMain::OnInitDialog()
{
	CRect temprect(0, 0, 1500, 1000);
	CWnd::SetWindowPos(NULL, 0, 0, temprect.Width(), temprect.Height(), SWP_NOZORDER | SWP_NOMOVE);
	CenterWindow();
	return TRUE;
}

BEGIN_MESSAGE_MAP(AircraftMain, CDialogEx)
END_MESSAGE_MAP()


// AircraftMain 消息处理程序
