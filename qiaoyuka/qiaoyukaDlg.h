
// qiaoyukaDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "hyperlink.h"

// CqiaoyukaDlg �Ի���
class CqiaoyukaDlg : public CDialog
{
// ����
public:
	CqiaoyukaDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_QIAOYUKA_DIALOG };

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
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	static BOOL CALLBACK OEnumWindowsProc( HWND hwnd, LPARAM lParam );
private:
	CHyperLink m_Static_DiaoSiNiXi;
	CEdit m_EClickTime;
};
