// war3HelperDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "hyperlink.h"


// Cwar3HelperDlg 对话框
class Cwar3HelperDlg : public CDialog
{
// 构造
public:
	Cwar3HelperDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_WAR3HELPER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	BOOL EnableDebugPrivilege();
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
	BOOL DestroyWindow();
public:
	CEdit m_num7;
	CEdit m_num8;
	CEdit m_num4;
	CEdit m_num5;
	CEdit m_num1;
	CEdit m_num2;
	CEdit m_oldmag1;
	CEdit m_newmag1;
	CEdit m_oldmag2;
	CEdit m_newmag2;
	CEdit m_oldmag3;
	CEdit m_newmag3;
	CEdit m_oldmag4;
	CEdit m_newmag4;
	CBrush   brush; 
	CStatic m_status;
	CHyperLink m_hyperlink;
    CEdit m_war3path;
    CString m_game_exe;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeEdit14();
	afx_msg void OnEnChangeEdit15();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnEnChangeEdit12();
	afx_msg void OnEnChangeEdit9();
	afx_msg void OnEnChangeEdit11();
	afx_msg void OnEnChangeEdit13();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnStnClickedHyperlink();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedStartgame();
	afx_msg void OnBnClickedCheck1();
	void CheckFullScreen();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnEnChangeEdit1();
private:
	CString m_strDir;
public:
	afx_msg void OnUpdateDeubug(CCmdUI *pCmdUI);
};
