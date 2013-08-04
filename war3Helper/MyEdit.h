#pragma once
#include "afxwin.h"
class  Cwar3HelperDlg;
class CMyEdit :
	public CEdit
{
private:
	Cwar3HelperDlg * m_Pdlg;
public:
	CMyEdit(void);
	~CMyEdit(void);
	 virtual BOOL PreTranslateMessage(MSG* pMsg);
     void InitDlg(Cwar3HelperDlg *dlg);
	 void OnEditCommandTab(MSG* pMsg,const TCHAR *sz);

};
