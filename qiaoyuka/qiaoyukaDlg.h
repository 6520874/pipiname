
// qiaoyukaDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "hyperlink.h"

// CqiaoyukaDlg 对话框
class CqiaoyukaDlg : public CDialog
{
// 构造
public:
	CqiaoyukaDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_QIAOYUKA_DIALOG };

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
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	CEdit m_Edit_QiaoyukaExe;
	HWND  m_hQyk;
	CHyperLink m_hyperlink;
public:
	afx_msg void OnBnClickedButtonSend();
private:
	CBrush   m_brush; 
	HWND     m_hTalk;
	BOOL     m_bfirst;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	static BOOL CALLBACK OEnumWindowsProc( HWND hwnd, LPARAM lParam );
	static BOOL CALLBACK OnSubWinow(HWND hwnd, LPARAM lParam);
private:
	CHyperLink m_Static_DiaoSiNiXi;
	CEdit m_EClickTime;
public:
	afx_msg void OnBnClickedButtonbug();
};
CString GetProcessNameFromId(int pid);