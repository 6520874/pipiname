
// kuaiping.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CkuaipingApp:
// �йش����ʵ�֣������ kuaiping.cpp
//

class CkuaipingApp : public CWinAppEx
{
public:
	CkuaipingApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CkuaipingApp theApp;