// SystemTool.cpp : 实现文件
//

#include "stdafx.h"
#include "kuaiping.h"
#include "SystemTool.h"


// CSystemTool 对话框

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
}


BEGIN_MESSAGE_MAP(CSystemToolDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CSystemToolDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSystemTool 消息处理程序

void CSystemToolDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxMessageBox(L"saasdads");
}
