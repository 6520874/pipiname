// AddSchoolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyIE.h"
#include "AddSchoolDlg.h"
#include "afxdialogex.h"

// CAddSchoolDlg 对话框

IMPLEMENT_DYNAMIC(CAddSchoolDlg, CDialog)

CAddSchoolDlg::CAddSchoolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddSchoolDlg::IDD, pParent)
{

}

CAddSchoolDlg::~CAddSchoolDlg()
{
}

void CAddSchoolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddSchoolDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADDOK, &CAddSchoolDlg::OnBnClickedButtonAddok)
END_MESSAGE_MAP()


// CAddSchoolDlg 消息处理程序


void CAddSchoolDlg::OnBnClickedButtonAddok()
{
	   CString  csWeb;
	   GetDlgItemText(IDC_EDIT1,csWeb);
	   if(csWeb.IsEmpty())
	   {
		   AfxMessageBox(_T("输入不能空"));
		   return;
	   }
	   WritePrivateProfileString(_T("web"),_T("website"),csWeb,GetCurrentPath()+_T("\\setjw.ini"));
	   AfxMessageBox("请重启本软件，谢谢！");
}


BOOL CAddSchoolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetDlgItemText(IDC_EDIT1,_T("http://"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
