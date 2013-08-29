// ShowImageDlg.h : header file
//

#if !defined(AFX_SHOWIMAGEDLG_H__CDE28BA0_4456_4062_A794_455B5C44EBF0__INCLUDED_)
#define AFX_SHOWIMAGEDLG_H__CDE28BA0_4456_4062_A794_455B5C44EBF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CShowImageDlg dialog

class CShowImageDlg : public CDialog
{
// Construction
public:
	
	CShowImageDlg(CWnd* pParent = NULL);	// standard constructor
	CString	GetExePath();
	void	DownURLImage();
	void	ShowImage();
protected:
	RECT	m_pRectLink;		// 用于保存静态文本框的矩形区域
	RECT	m_PicRect;			// 保存图片验证码矩形区域
public:
	int SendForm();
	
// Dialog Data
	//{{AFX_DATA(CShowImageDlg)
	enum { IDD = IDD_SHOWIMAGE_DIALOG };
	CStatic	m_StaticText;
	CString	m_strUser;
	CString	m_strPassword;
	CString	m_strCode;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowImageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CShowImageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnLogin();
	afx_msg void OnBtnExit();
	afx_msg void OnClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWIMAGEDLG_H__CDE28BA0_4456_4062_A794_455B5C44EBF0__INCLUDED_)
