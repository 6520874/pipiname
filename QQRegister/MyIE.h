//Download by http://www.NewXing.com
// MyIE.h : MyIE Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CMyIEApp:
// �йش����ʵ�֣������ MyIE.cpp
//

class CMyIEApp : public CWinApp
{
public:
	CMyIEApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyIEApp theApp;
