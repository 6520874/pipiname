// CheckPasswdDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CheckPasswdDlg.h"


// CCheckPasswdDlg �Ի���

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


// CCheckPasswdDlg ��Ϣ�������
void CCheckPasswdDlg::Init(CPasswdDlg *dlg)
 {
 m_passwdDlg = dlg; 
 }
void CCheckPasswdDlg::OnBnClickedOk()
 {
 // TODO: �ڴ���ӿؼ�֪ͨ����������

 GetDlgItemText(IDC_EDIT1,m_CsCheckPasswd);
 if(m_passwdDlg->m_csPasswd  == m_CsCheckPasswd)
  {
  AfxMessageBox(_T("������ȷ"));
  m_bPasswdSame = true;
  OnOK();
  }
 else
  {
  AfxMessageBox(_T("�����������������Ӵ"));
  m_bPasswdSame = false;
  }

 }

void CCheckPasswdDlg::OnBnClickedCancel()
 {
 // TODO: �ڴ���ӿؼ�֪ͨ����������
 OnCancel();
 }
