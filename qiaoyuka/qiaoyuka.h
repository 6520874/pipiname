
// qiaoyuka.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CqiaoyukaApp:
// �йش����ʵ�֣������ qiaoyuka.cpp
//

class CqiaoyukaApp : public CWinAppEx
{
public:
	CqiaoyukaApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CqiaoyukaApp theApp;