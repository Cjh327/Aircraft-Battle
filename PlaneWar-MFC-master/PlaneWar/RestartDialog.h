#pragma once
#include"MyDialog.h"

// CRestartDialog �Ի���

class CRestartDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CRestartDialog)

public:
	CRestartDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRestartDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RESTART };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
