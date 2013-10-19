#pragma once
#include "mylistctrl.h"
#include "resource.h"
#include <vector>
// CFileTool 对话框

class CFileToolDlg : public CDialog
{
	DECLARE_DYNAMIC(CFileToolDlg)

public:
	CFileToolDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFileToolDlg();

// 对话框数据
	enum { IDD = IDD_FILE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:


	virtual BOOL OnInitDialog();
	CMyListCtrl m_listctrl;
	CImageList  m_ImageList;
	afx_msg void OnUpdateDaOpen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDaLocateFile(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDaDeleteFile(CCmdUI *pCmdUI);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	CString ReadShortcut(CString lpwLnkFile);
	void GetDeskIco();
	void EnumDesktopLnkPath();
	afx_msg void OnUpdateDaDesktoplink(CCmdUI *pCmdUI);
	void CreateDesktopShort(CString cspath,CString csSavePath);
	std::vector<CString>  m_LinkExepath;
 };
