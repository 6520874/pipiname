#pragma once
#include "resource.h"
#include "BtnST.h"
// CHide 对话框

class CHideToolDlg : public CDialog
{
	DECLARE_DYNAMIC(CHideToolDlg)

public:
	CHideToolDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHideToolDlg();

// 对话框数据
	enum { IDD = IDD_HIDE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOpenhide();
	afx_msg void OnBnClickedButtonClosehide();
	CButtonST	m_btnOpenHideWindow;
	CButtonST	m_btnCloseHideWindow;
};
