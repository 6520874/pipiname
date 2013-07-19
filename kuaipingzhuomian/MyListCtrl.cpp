#include "StdAfx.h"
#include "MyListCtrl.h"
#include "FileTool.h"

CMyListCtrl::CMyListCtrl(void)
{
}

CMyListCtrl::~CMyListCtrl(void)
{
}
BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	ON_WM_DROPFILES()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

void CMyListCtrl::OnDropFiles(HDROP hDrop)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
    /// TODO: 在此添加消息处理程序代码和/或调用默认值
	SHFILEINFO  info = {0};
	// 定义一个缓冲区来存放读取的文件名信息
	TCHAR szFileName[MAX_PATH + 1] = {0};
	// 通过设置iFiles参数为0xFFFFFFFF,可以取得当前拖动的文件数量，
	// 当设置为0xFFFFFFFF,函数间忽略后面连个参数。
	UINT nFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);

	// 通过循环依次取得拖动文件的File Name信息，并把它添加到ListBox中
	for(UINT i=0; i<nFiles; i++)
	{
		DragQueryFile(hDrop,i,szFileName,sizeof(szFileName));

		SHFILEINFO info;
		memset((char*)&info,0,sizeof(info));
		SHGetFileInfo(szFileName,0,&info,sizeof(info),SHGFI_ICON | SHGFI_USEFILEATTRIBUTES );

		i = m_dlg->m_ImageList.Add(info.hIcon);
		CString strsz  = T2CW(szFileName);
		int pos= strsz.ReverseFind(_T('\\'));
		strsz  = strsz.Right(strsz.GetLength()-pos-1);

		int index = m_dlg->m_listctrl.InsertItem(i,CW2W(strsz),i);
		m_dlg->m_listctrl.SetItemText(i,1,szFileName);
		//m_listbox.AddString(szFileName);
	}
	// 结束此次拖拽操作，并释放分配的资源
	DragFinish( hDrop);
	CListCtrl::OnDropFiles(hDrop);
}


void CMyListCtrl::Init(CFileToolDlg *plg)
{
	this->m_dlg = plg;
}