
// kuaipingDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "FileTool.h"
#include "SystemTool.h"
#include "Hide.h"
// CkuaipingDlg 对话框
class CkuaipingDlg : public CDialog
{
// 构造
public:
	CkuaipingDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_KUAIPING_DIALOG };

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
	afx_msg void OnEnChangeEdit2();
    CFileToolDlg 	   m_para1;
	CSystemToolDlg     m_para2;
	CHideToolDlg       m_para3;
    CTabCtrl m_tabctr;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnTcnSelchangingTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
