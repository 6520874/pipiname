// Hide.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Hide.h"


// CHide �Ի���

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


// CHide ��Ϣ�������

BOOL CHideToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
   
     
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CHideToolDlg::OnBnClickedButtonOpenhide()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
      WinExec(CW2A(_T("systemopen.bat")),SW_HIDE); 
	  Sleep(1000);
	  ShellExecute(NULL,_T("open"),_T("k://"),NULL,NULL,SW_SHOW);
	  MessageBox(_T("����Է������˽���ļ���",_T("��ϲ"),MB_OK));
}

void CHideToolDlg::OnBnClickedButtonClosehide()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	WinExec(CW2A(_T("systemclose.bat")),SW_HIDE);
}
