// FileTool.cpp : 实现文件
//

#include "stdafx.h"
#include "kuaiping.h"
#include "FileTool.h"

#define ALLOC_SIZE 200
// CFileTool 对话框

IMPLEMENT_DYNAMIC(CFileToolDlg, CDialog)

CFileToolDlg::CFileToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileToolDlg::IDD, pParent)
{

}

CFileToolDlg::~CFileToolDlg()
{
}

void CFileToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listctrl);
}


BEGIN_MESSAGE_MAP(CFileToolDlg, CDialog)

	ON_UPDATE_COMMAND_UI(ID_DA_32771, &CFileToolDlg::OnUpdateDaOpen)
	ON_UPDATE_COMMAND_UI(ID_DA_32772, &CFileToolDlg::OnUpdateDaLocateFile)
	ON_UPDATE_COMMAND_UI(ID_DA_32773, &CFileToolDlg::OnUpdateDaDeleteFile)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CFileToolDlg::OnNMRClickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CFileToolDlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// CFileTool 消息处理程序



BOOL CFileToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_ImageList.Create(32, 32, ILC_COLOR24|ILC_MASK, 1, 0);
	m_listctrl.SetImageList(&m_ImageList, LVSIL_NORMAL);
	m_listctrl.InsertColumn( 0, _T("ID"), LVCFMT_LEFT, 40 );//插入列
	m_listctrl.InsertColumn( 1, _T("NAME"), LVCFMT_LEFT, 50 );
	m_listctrl.Init(this);
    EnumDesktopLnkPath();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// 枚举桌面上应用程序的lnk路径
void  CFileToolDlg::EnumDesktopLnkPath()
{
	WCHAR szPath[MAX_PATH] = {0};
	SHGetSpecialFolderPathW(NULL, szPath, CSIDL_DESKTOPDIRECTORY, 0);
	IShellFolder* pShell = NULL;

	if(FAILED(SHGetDesktopFolder(&pShell)))
	{
		return ;
	}

	IShellFolder* pFolder = NULL;
	ITEMIDLIST* pItem = NULL;
	
	if(FAILED(pShell->ParseDisplayName(NULL, NULL, szPath, NULL, &pItem, NULL)))
	{
		return;
	}

	if(FAILED(pShell->BindToObject(pItem, NULL, IID_IShellFolder, (LPVOID*)&pFolder)))
	{
		return ;
	}
	pShell->Release();

	if(NULL == pFolder)
	{
		return ;
	}

	IEnumIDList* pEnum = NULL;
	
	if(FAILED(pFolder->EnumObjects(NULL, SHCONTF_NONFOLDERS, &pEnum)))
	{
		return ;
	}

	pItem = NULL;
	ULONG ulFetched = 0;
	WCHAR szLnkPath[MAX_PATH] = {0};
	LPCWSTR pszLnkName(L".exe");
	WIN32_FIND_DATAW fd = {0};
	SHFILEINFO info;
	memset((char*)&info,0,sizeof(info));
    int  i = 0;

	while(S_OK == pEnum->Next(1, &pItem, &ulFetched))
	{
		SHGetDataFromIDListW(pFolder, pItem, SHGDFIL_FINDDATA, &fd, sizeof(fd));
		swprintf(szLnkPath, L"%s\\%s", szPath, fd.cFileName);
		CString strFileName = fd.cFileName;
		if(-1 != strFileName.Find(_T(".exe")))
		{
			SHGetFileInfo(szLnkPath,0,&info,sizeof(info),SHGFI_ICON | SHGFI_USEFILEATTRIBUTES );
			i = m_ImageList.Add(info.hIcon);
			int index = m_listctrl.InsertItem(i,fd.cFileName,i);
            m_listctrl.SetItemText(index,1,szLnkPath);
		    i++;
		}
	}
	pEnum->Release();
	pFolder->Release();
	HICON   hIcon   =   AfxGetApp()-> LoadIcon(IDI_ICON1); 
	m_ImageList.Add(hIcon); 
	 m_listctrl.InsertItem(i,L"可拖拽显示",i);

}

void CFileToolDlg::OnUpdateDaOpen(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	int i= m_listctrl.GetSelectionMark();
	CString strPath = m_listctrl.GetItemText(i,1);

	CString  strFilepath =  ReadShortcut(strPath);

	if(strFilepath == _T(""))
	{
		strFilepath = strPath;
	}
	ShellExecute(m_hWnd,L"open",strFilepath,NULL,NULL,SW_SHOWNORMAL);	

}

void CFileToolDlg::OnUpdateDaLocateFile(CCmdUI *pCmdUI)
{
	TCHAR  strPath[MAX_PATH] = {0};
	TCHAR szPath[MAX_PATH] = {0};
	int index = m_listctrl.GetSelectionMark();
	m_listctrl.GetItemText(index, 1, szPath, MAX_PATH);
	wsprintfW(strPath,L"Explorer /select, %s", szPath);
	USES_CONVERSION;
	WinExec(W2A(strPath), SW_SHOWNORMAL);	
}

void CFileToolDlg::OnUpdateDaDeleteFile(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	int i= m_listctrl.GetSelectionMark();
	m_listctrl.DeleteItem(i);

}

void CFileToolDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CPoint point;	::GetCursorPos(&point);
	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	CMenu* pPopup = menu.GetSubMenu(0);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,this);
	*pResult = 0;
}

void CFileToolDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	int i= m_listctrl.GetSelectionMark();
	CString strPath = m_listctrl.GetItemText(i,1);
	CString  strFilepath =  ReadShortcut(strPath);
	if(strFilepath == _T(""))
	{
		strFilepath = strPath;
	}
	ShellExecute(m_hWnd,L"open",strFilepath,NULL,NULL,SW_SHOWNORMAL);	
	*pResult = 0;
}

CString CFileToolDlg::ReadShortcut(CString lpwLnkFile)
{
	bool bReturn = true;
	TCHAR lpDescFile[MAX_PATH]  = {0};
	IShellLink *pShellLink =NULL;

	if(bReturn)
	{
		bReturn = (CoInitialize(NULL) == S_OK);

		if(bReturn)
		{
			bReturn = CoCreateInstance (CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
				IID_IShellLink, (void **)&pShellLink) >= 0;

			if(bReturn)
			{
				IPersistFile *ppf =NULL;
				bReturn = pShellLink->QueryInterface(IID_IPersistFile, (void **)&ppf) >= 0;
				if(bReturn)
				{
					bReturn = ppf->Load(lpwLnkFile, TRUE) >= 0;
					if(bReturn)
					{
						pShellLink->GetPath(lpDescFile, MAX_PATH, NULL, 0);
					}
					ppf->Release ();
				}
				pShellLink->Release ();
			}
			CoUninitialize();
		}
	}
	return lpDescFile;
}