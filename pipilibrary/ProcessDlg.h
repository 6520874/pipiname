

#pragma once
#include "afxcmn.h"
#include "resource.h"
#include "Wininet.h"
#include <Mmsystem.h>
#pragma comment(lib,"Winmm.lib")

// CProcessDlg 对话框

class    CProcessDlg : public CDialog
{
	DECLARE_DYNAMIC(CProcessDlg)

public:
	CProcessDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProcessDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CProgressCtrl m_progress;
public:
	virtual BOOL OnInitDialog();
	int InternetGetFile(CString szUrl,CString szFileName);
	afx_msg void OnBnClickedButton1();
	void SetUrlFileName(CString szUrl,CString szFileName);
private:
	CString m_csUrl;
	CString m_csFileName;
};


CProcessDlg   &  GetProcessDlg();

