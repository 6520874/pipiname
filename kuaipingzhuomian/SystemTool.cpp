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
}


BEGIN_MESSAGE_MAP(CSystemToolDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CSystemToolDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSystemTool ��Ϣ�������

void CSystemToolDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AfxMessageBox(L"saasdads");
}
