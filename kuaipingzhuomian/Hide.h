#pragma once
#include "resource.h"

// CHide �Ի���

class CHideToolDlg : public CDialog
{
	DECLARE_DYNAMIC(CHideToolDlg)

public:
	CHideToolDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHideToolDlg();

// �Ի�������
	enum { IDD = IDD_HIDE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOpenhide();
	afx_msg void OnBnClickedButtonClosehide();
};
