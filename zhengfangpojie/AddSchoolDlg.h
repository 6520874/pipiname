#pragma once


// CAddSchoolDlg �Ի���

class CAddSchoolDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddSchoolDlg)

public:
	CAddSchoolDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddSchoolDlg();

// �Ի�������
	enum { IDD = IDD_DIALOGADDSCHOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddok();
	virtual BOOL OnInitDialog();
};
