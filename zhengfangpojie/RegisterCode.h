#pragma once


// CRegisterCode 对话框

class CRegisterCode : public CDialog
{
	DECLARE_DYNAMIC(CRegisterCode)

public:
	CRegisterCode(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRegisterCode();

// 对话框数据
	enum { IDD = IDD_DIALOGZHUCEMA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonYanzheng();
	BOOL GetMacAddress(CString  &strMac);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonGetcode();
};
