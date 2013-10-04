#pragma once
#include "resource.h"

#include "PasswdDlg.h"
class CCheckPasswdDlg : public CDialog
{
	DECLARE_DYNAMIC(CCheckPasswdDlg)

public:
	CCheckPasswdDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCheckPasswdDlg();

// 对话框数据
	enum { IDD = IDD_DIALOGCHECKPASSWD };
	
	CPasswdDlg  *m_passwdDlg;

   bool  m_bPasswdSame;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
  public:
   afx_msg void OnBnClickedOk();
   afx_msg void OnBnClickedCancel();
   void Init(CPasswdDlg *dlg);
  private:
 CString m_CsCheckPasswd;
 };
