// SearchDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyIE.h"
#include "SearchDlg.h"
#include "afxdialogex.h"


// CSearchDlg �Ի���

IMPLEMENT_DYNAMIC(CSearchDlg, CDialogEx)

CSearchDlg::CSearchDlg(CMyIEView *dlg,CWnd* pParent /*=NULL*/)
	: CDialogEx(CSearchDlg::IDD, pParent)
{
	m_Dlg = dlg;
}

CSearchDlg::~CSearchDlg()
{
}

void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTONOK, &CSearchDlg::OnBnClickedButtonok)
END_MESSAGE_MAP()


// CSearchDlg ��Ϣ�������


void CSearchDlg::OnBnClickedButtonok()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int n = GetPrivateProfileInt(_T("aa"),_T("ffff"),0,_T("C://windows/win1.ini"));

	if(n>10)
	{
		AfxMessageBox(_T("����ʹ�ô����ѵ����뵽ע����˵������˻���лл��"));
	}
	else
	{
		wchar_t strNum[10] = {0};
		n++;
		_itow(n,strNum,10);
			CString cstrNum(strNum);
		WritePrivateProfileString(_T("aa"),_T("ffff"),cstrNum,_T("C://windows/win1.ini"));
		CString CsXueHao;
		GetDlgItemText(IDC_EDIT_XUEHSAO,CsXueHao);
		m_Dlg->Changeweb(CsXueHao);
	}
}


BOOL CSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemText(IDC_EDIT_XUEHSAO,_T("0910750025"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
