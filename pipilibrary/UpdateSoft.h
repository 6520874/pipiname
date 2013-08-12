#pragma once

#ifndef DISPLAYSET
#define  DISPLAYSET_DLL __declspec(dllexport)
#else
#define  DISPLAYSET_DLL __declspec(dllimport)
#endif
#include <string>
class  DISPLAYSET_DLL CUpdateSoft
{
public:
	CUpdateSoft(void);
	virtual ~CUpdateSoft(void);
	void Apply(CString szUrl,CString szFileName);
	
	int  DownCommonFile(CString szUrl,CString szFileName);
	static  UINT __cdecl ThreadDownFile( LPVOID pParam ); 
private:  

};
