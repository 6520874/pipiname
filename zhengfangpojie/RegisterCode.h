#pragma once


// CRegisterCode �Ի���

class CRegisterCode : public CDialog
{
	DECLARE_DYNAMIC(CRegisterCode)

public:
	CRegisterCode(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegisterCode();

// �Ի�������
	enum { IDD = IDD_DIALOGZHUCEMA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonYanzheng();
	BOOL GetMacAddress(CString  &strMac);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonGetcode();
};
