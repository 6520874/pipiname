
// UpdateDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CUpdateDlg �Ի���
class CUpdateDlg : public CDialog
{
// ����
public:
	CUpdateDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UPDATE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	int InternetGetFile(CString szUrl,CString szFileName);
    static UINT __cdecl UpdateThreadPro( LPVOID pParam);
	CString GetWebStieHtml(CString strUrl);

private:
	CProgressCtrl m_process;
	CString     m_CsExePath;
};
	