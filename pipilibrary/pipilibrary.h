// pipilibrary.h : pipilibrary DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CpipilibraryApp
// �йش���ʵ�ֵ���Ϣ������� pipilibrary.cpp
//

class CpipilibraryApp : public CWinApp
{
public:
	CpipilibraryApp();

// ��д
public:
	virtual BOOL InitInstance();
  

	DECLARE_MESSAGE_MAP()
};
