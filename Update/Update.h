
// Update.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUpdateApp:
// �йش����ʵ�֣������ Update.cpp
//

class CUpdateApp : public CWinAppEx
{
public:
	CUpdateApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	BOOL IsUpdate();
	CString GetWebStieHtml(CString strUrl);
};

extern CUpdateApp theApp;