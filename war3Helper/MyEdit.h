#pragma once
#include "afxwin.h"

class CMyEdit :
	public CEdit
{
public:
	CMyEdit(void);
	~CMyEdit(void);
	 virtual BOOL PreTranslateMessage(MSG* pMsg);

	 void OnEditCommandTab(MSG* pMsg,const TCHAR *sz);
};
