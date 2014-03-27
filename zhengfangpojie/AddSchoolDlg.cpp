// AddSchoolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyIE.h"
#include "AddSchoolDlg.h"
#include "afxdialogex.h"

// CAddSchoolDlg �Ի���

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


// CAddSchoolDlg ��Ϣ�������


void CAddSchoolDlg::OnBnClickedButtonAddok()
{
	   CString  csWeb;
	   GetDlgItemText(IDC_EDIT1,csWeb);
	   if(csWeb.IsEmpty())
	   {
		   AfxMessageBox(_T("���벻�ܿ�"));
		   return;
	   }
	   WritePrivateProfileString(_T("web"),_T("website"),csWeb,GetCurrentPath()+_T("\\setjw.ini"));
	   AfxMessageBox("�������������лл��");
}


BOOL CAddSchoolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetDlgItemText(IDC_EDIT1,_T("http://"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
