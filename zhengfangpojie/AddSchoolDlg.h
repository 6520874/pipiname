#pragma once


// CAddSchoolDlg 对话框

class CAddSchoolDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddSchoolDlg)

public:
	CAddSchoolDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddSchoolDlg();

// 对话框数据
	enum { IDD = IDD_DIALOGADDSCHOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddok();
	virtual BOOL OnInitDialog();
};
