#pragma once

#include "MyIEView.h"
// CSearchDlg �Ի���

class CSearchDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchDlg)

public:
	CSearchDlg(CMyIEView *dlg,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSearchDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonok();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonrandom();
private:
	CComboBox m_CommboxFenYuan;
	CMyIEView * m_Dlg;
public:
	afx_msg void OnCbnSelchangeComboFenyuan();
	afx_msg void OnBnClickedButtontelephone();
	afx_msg void OnBnClickedButtonJietu();
};
