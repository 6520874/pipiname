
// kuaipingDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "FileTool.h"
#include "SystemTool.h"
#include "Hide.h"
#include "PasswdDlg.h"
#include "CheckPasswdDlg.h"
// CkuaipingDlg �Ի���
class CkuaipingDlg : public CDialog
{
// ����
public:
	CkuaipingDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_KUAIPING_DIALOG };

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
public:
	afx_msg void OnEnChangeEdit2();
    CFileToolDlg 	   m_para1;
	CSystemToolDlg     m_para2;
	CHideToolDlg       m_para3;
    CTabCtrl m_tabctr;
	CImageList    m_ImageTab;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnTcnSelchangingTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnUpdatePasswd(CCmdUI *pCmdUI);
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
private:
	CPasswdDlg m_CreatePasswddlg;
	CCheckPasswdDlg m_CheckPasswdDlg;
	CButtonST    m_BtnStart;
	CButtonST    m_BtnClearDeskTop;
public:
 afx_msg void OnBnClickedButton1();
 afx_msg void OnBnClickedButtonbaidu();
 afx_msg void OnSize(UINT nType, int cx, int cy);
 afx_msg void OnBnClickedButtonstart();
 afx_msg void OnBnClickedButtonClearDesktop();
 static DWORD WINAPI CopyFilePro( void* pArguments);
 CString GetFileNameFromPath(const CString &csSavePath);
};
