#pragma once

#include "MyIEView.h"
// CSearchDlg �Ի���

class CSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSearchDlg)

public:
	CSearchDlg(CMyIEView *dlg,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSearchDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonok();
	CMyIEView * m_Dlg;
	virtual BOOL OnInitDialog();
};
