#pragma once

#include "afxcmn.h"

class CFileToolDlg;
class CMyListCtrl :
	public CListCtrl
{
public:
	CMyListCtrl(void);
	~CMyListCtrl(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDropFiles(HDROP hDropInfo);

	public:
	void Init(CFileToolDlg *plg);
	CFileToolDlg * m_dlg;

};
