#pragma once

#include "MyIEView.h"
// CSearchDlg 对话框

class CSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchDlg)

public:
	CSearchDlg(CMyIEView *dlg,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSearchDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonok();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonrandom();
private:
	CComboBox m_CommboxFenYuan;
	CMyIEView * m_Dlg;
public:
	afx_msg void OnCbnSelchangeComboFenyuan();
	afx_msg void OnBnClickedButtontelephone();
	afx_msg void OnBnClickedButtonJietu();
};
