#pragma once


// CSystemTool 对话框

class CSystemToolDlg : public CDialog
{
	DECLARE_DYNAMIC(CSystemToolDlg)

public:
	CSystemToolDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSystemToolDlg();

// 对话框数据
	enum { IDD = IDD_SYSTEM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
