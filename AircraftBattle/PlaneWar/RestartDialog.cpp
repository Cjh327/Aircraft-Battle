// RestartDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AircraftBattle.h"
#include "RestartDialog.h"
#include "afxdialogex.h"


// CRestartDialog �Ի���

IMPLEMENT_DYNAMIC(CRestartDialog, CDialogEx)

CRestartDialog::CRestartDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_RESTART, pParent)
{

}

CRestartDialog::~CRestartDialog()
{
}

void CRestartDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRestartDialog, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CRestartDialog::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CRestartDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CRestartDialog ��Ϣ�������


void CRestartDialog::OnBnClickedCancel()
{
	//��ʾ��ϸ��Ϣ���������˳�
	MyDialog  aboutDlg;

	CDialogEx::OnCancel();
	aboutDlg.DoModal();
}


void CRestartDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
	
}
