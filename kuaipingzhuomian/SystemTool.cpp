// SystemTool.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "kuaiping.h"
#include "SystemTool.h"


// CSystemTool �Ի���

IMPLEMENT_DYNAMIC(CSystemToolDlg, CDialog)

CSystemToolDlg::CSystemToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSystemToolDlg::IDD, pParent)
{

}

CSystemToolDlg::~CSystemToolDlg()
{
}

void CSystemToolDlg::DoDataExchange(CDataExchange* pDX)
{
CDialog::DoDataExchange(pDX);
DDX_Control(pDX, IDC_LIST1, m_listctrl);
 }


BEGIN_MESSAGE_MAP(CSystemToolDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CSystemToolDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSystemTool ��Ϣ�������

void CSystemToolDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
}

BOOL CSystemToolDlg::OnInitDialog()
 {
 CDialog::OnInitDialog();

 m_ImageList.Create(32, 32, ILC_COLOR24|ILC_MASK, 1, 0);
 m_listctrl.SetImageList(&m_ImageList, LVSIL_NORMAL);
 m_listctrl.InsertColumn( 0, _T("ID"), LVCFMT_LEFT, 40 );//������
 m_listctrl.InsertColumn( 1, _T("NAME"), LVCFMT_LEFT, 50 );
 m_listctrl.InsertColumn( 2, _T("path"), LVCFMT_LEFT, 50 );

 TCHAR m_lpszDefaultDir[MAX_PATH] = {L"d://BigFoot.exe"};
 /*TCHAR  szDocument[MAX_PATH]={0};   
 memset(m_lpszDefaultDir,0,_MAX_PATH); 

 LPITEMIDLIST pidl=NULL;   
 SHGetSpecialFolderLocation(NULL,   CSIDL_PERSONAL,   &pidl);   
 if (pidl   &&   SHGetPathFromIDList(pidl,   szDocument))   
  {   
  GetShortPathName(szDocument,m_lpszDefaultDir,_MAX_PATH);   
  }
  */  

 SHFILEINFO info;
 memset((char*)&info,0,sizeof(info));
 SHGetFileInfo(m_lpszDefaultDir,0,&info,sizeof(info),SHGFI_ICON | SHGFI_USEFILEATTRIBUTES );
 int i = m_ImageList.Add(info.hIcon);
 int index = m_listctrl.InsertItem(0,m_lpszDefaultDir,0);
 m_listctrl.SetItemText(index,1,m_lpszDefaultDir);

  //m_listctrl.InsertColumn()
 //m_list.
 return TRUE;  // return TRUE unless you set the focus to a control
 // �쳣: OCX ����ҳӦ���� FALSE
 }
