// war3Helper.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cwar3HelperApp:
// �йش����ʵ�֣������ war3Helper.cpp
//

class Cwar3HelperApp : public CWinApp
{
public:
	Cwar3HelperApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cwar3HelperApp theApp;