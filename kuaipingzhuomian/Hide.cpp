// Hide.cpp : 实现文件
//

#include "stdafx.h"
#include "Hide.h"


// CHide 对话框

IMPLEMENT_DYNAMIC(CHideToolDlg, CDialog)

CHideToolDlg::CHideToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHideToolDlg::IDD, pParent)
{

}

CHideToolDlg::~CHideToolDlg()
{
}

void CHideToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHideToolDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OPENHIDE, &CHideToolDlg::OnBnClickedButtonOpenhide)
	ON_BN_CLICKED(IDC_BUTTON_CLOSEHIDE, &CHideToolDlg::OnBnClickedButtonClosehide)
END_MESSAGE_MAP()


// CHide 消息处理程序

BOOL CHideToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
   
     
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CHideToolDlg::OnBnClickedButtonOpenhide()
{
	// TODO: 在此添加控件通知处理程序代码
      WinExec(CW2A(_T("systemopen.bat")),SW_HIDE); 
	  Sleep(1000);
	  ShellExecute(NULL,_T("open"),_T("k://"),NULL,NULL,SW_SHOW);
	  MessageBox(_T("你可以放入你的私密文件了",_T("恭喜"),MB_OK));
}

void CHideToolDlg::OnBnClickedButtonClosehide()
{
	// TODO: 在此添加控件通知处理程序代码
	WinExec(CW2A(_T("systemclose.bat")),SW_HIDE);
}
