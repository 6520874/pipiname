// ºÍÐ³Éç»áDlg.h : header file
//

#if !defined(AFX_DLG_H__D1D71371_14FA_41D0_B05A_298EEBB737EB__INCLUDED_)
#define AFX_DLG_H__D1D71371_14FA_41D0_B05A_298EEBB737EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define  MAX_SWORDLEN  256
//#define  MGCTEXT  "c:\\minganci\\text"
////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog


#include "HyperLinker.h"
#include "afxwin.h"

class CMyDlg : public CDialog
{
	// Construction
public:
    int couttime;
	CMyDlg(CWnd* pParent = NULL);	// standard constructor
	char directoryname[MAX_SWORDLEN];
	int SaveBitmapToFile(HBITMAP hBitmap, LPSTR lpFileName);
	HBITMAP CopyScreenToBitmap(LPRECT lpRect);
	static  DWORD WINAPI Replacestr(LPVOID lparameter);
	// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MY_DIALOG };
	CEdit	m_filterafter;
	CEdit	m_filterbefore;
	CEdit	m_hexiehou;
	CEdit	m_hexieqian;
	CEdit	m_random;
	CHyperLinker	m_callus;
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	HICON m_hIcon;
	
	// Generated message map functions
	//{{AFX_MSG(CMyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClear();
	afx_msg void OnHEXIE();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnOpenText();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCancelMode();
	afx_msg void OnRandom();
	afx_msg void OnWTI();
	afx_msg void OnReplaceStart();
	afx_msg void OnText_typeset();
	afx_msg void OnChangeEdithexie();
	afx_msg void OnMenuAbout();
	afx_msg void Oncontraction();
	afx_msg void OnContraction();
	afx_msg void OnClipboard();
	afx_msg void OnMenuitem32772();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonweibo();
private:
	CButton m_buttonWeibo;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton9();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_H__D1D71371_14FA_41D0_B05A_298EEBB737EB__INCLUDED_)
