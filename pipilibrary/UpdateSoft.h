#pragma once

#ifndef DISPLAYSET
#define  DISPLAYSET_DLL __declspec(dllexport)
#else
#define  DISPLAYSET_DLL __declspec(dllimport)
#endif
#include <string>
#include <afxctl.h>
#include "CFireRoutine.h"
#include "CWaterRoutine.h"
#include "DIBSectionLite.h"
class  DISPLAYSET_DLL CUpdateSoft
{
public:
	CUpdateSoft(void);
	virtual ~CUpdateSoft(void);
	void Apply(CString szUrl,CString szFileName);
	void InitFire(CPictureHolder *myTmpPicture,int iWidth,int iHeight);
	void StartFire(CWnd * lp);
	int  DownCommonFile(CString szUrl,CString szFileName);
	static  UINT __cdecl ThreadDownFile( LPVOID pParam ); 
private:  
	CDIBSectionLite	m_bmpRenderSource;
	CDIBSectionLite m_bmpRenderTarget;
	CFireRoutine	m_myFire;
	CWaterRoutine	m_myWater;
    int  m_iWeight;
	int  m_iHeight;
	BOOL  m_bMax;
};
