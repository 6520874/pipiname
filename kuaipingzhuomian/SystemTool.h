#pragma once


// CSystemTool �Ի���

class CSystemToolDlg : public CDialog
{
	DECLARE_DYNAMIC(CSystemToolDlg)

public:
	CSystemToolDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSystemToolDlg();

// �Ի�������
	enum { IDD = IDD_SYSTEM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
