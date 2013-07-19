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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    /// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SHFILEINFO  info = {0};
	// ����һ������������Ŷ�ȡ���ļ�����Ϣ
	TCHAR szFileName[MAX_PATH + 1] = {0};
	// ͨ������iFiles����Ϊ0xFFFFFFFF,����ȡ�õ�ǰ�϶����ļ�������
	// ������Ϊ0xFFFFFFFF,��������Ժ�������������
	UINT nFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);

	// ͨ��ѭ������ȡ���϶��ļ���File Name��Ϣ����������ӵ�ListBox��
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
	// �����˴���ק���������ͷŷ������Դ
	DragFinish( hDrop);
	CListCtrl::OnDropFiles(hDrop);
}


void CMyListCtrl::Init(CFileToolDlg *plg)
{
	this->m_dlg = plg;
}