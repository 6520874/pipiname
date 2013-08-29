// ShowImage.h : main header file for the SHOWIMAGE application
//

#if !defined(AFX_SHOWIMAGE_H__786D0363_64EE_4279_8945_0EC41EAFF5F0__INCLUDED_)
#define AFX_SHOWIMAGE_H__786D0363_64EE_4279_8945_0EC41EAFF5F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CShowImageApp:
// See ShowImage.cpp for the implementation of this class
//

class CShowImageApp : public CWinApp
{
public:
	CShowImageApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowImageApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CShowImageApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWIMAGE_H__786D0363_64EE_4279_8945_0EC41EAFF5F0__INCLUDED_)
