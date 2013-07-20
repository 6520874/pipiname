#pragma once
#ifndef DISPLAYSET
#define  DISPLAYSET_DLL __declspec(dllexport)
#else
#define  DISPLAYSET_DLL __declspec(dllimport)
#endif


#include "Wininet.h"
#include <Mmsystem.h>
#pragma  comment(lib,"Winmm.lib")

class  DISPLAYSET_DLL CDownFile
{
public:
	CDownFile(void);

	virtual ~CDownFile(void);
	int InternetGetFile(CString szUrl,CString szFileName);
};
