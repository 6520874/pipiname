// CheckPasswdDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CheckPasswdDlg.h"


// CCheckPasswdDlg 对话框

IMPLEMENT_DYNAMIC(CCheckPasswdDlg, CDialog)

CCheckPasswdDlg::CCheckPasswdDlg(CWnd* pParent /*=NULL*/)
: CDialog(CCheckPasswdDlg::IDD, pParent)
 {
 }

CCheckPasswdDlg::~CCheckPasswdDlg()
 {
 }


void CCheckPasswdDlg::DoDataExchange(CDataExchange* pDX)
 {
 CDialog::DoDataExchange(pDX);
 }


BEGIN_MESSAGE_MAP(CCheckPasswdDlg, CDialog)
 ON_BN_CLICKED(IDOK, &CCheckPasswdDlg::OnBnClickedOk)
 ON_BN_CLICKED(IDCANCEL, &CCheckPasswdDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCheckPasswdDlg 消息处理程序
void CCheckPasswdDlg::Init(CPasswdDlg *dlg)
 {
 m_passwdDlg = dlg; 
 }
void CCheckPasswdDlg::OnBnClickedOk()
 {
 // TODO: 在此添加控件通知处理程序代码

 GetDlgItemText(IDC_EDIT1,m_CsCheckPasswd);
 if(m_passwdDlg->m_csPasswd  == m_CsCheckPasswd)
  {
  AfxMessageBox(_T("输入正确"));
  m_bPasswdSame = true;
  OnOK();
  }
 else
  {
  AfxMessageBox(_T("密码错误，请重心输入哟"));
  m_bPasswdSame = false;
  }

 }

void CCheckPasswdDlg::OnBnClickedCancel()
 {
 // TODO: 在此添加控件通知处理程序代码
 OnCancel();
 }
