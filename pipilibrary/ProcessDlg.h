

#pragma once
#include "afxcmn.h"
#include "resource.h"
#include "Wininet.h"
#include <Mmsystem.h>
#pragma comment(lib,"Winmm.lib")

// CProcessDlg �Ի���

class    CProcessDlg : public CDialog
{
	DECLARE_DYNAMIC(CProcessDlg)

public:
	CProcessDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProcessDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

