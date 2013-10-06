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
	DDX_Control(pDX, IDC_BUTTON_OPENHIDE, m_btnOpenHideWindow);
	DDX_Control(pDX, IDC_BUTTON_CLOSEHIDE, 	m_btnCloseHideWindow);
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
	m_btnOpenHideWindow.SetIcon(IDI_ICON5);
	m_btnOpenHideWindow.SetFlat(FALSE);
	m_btnCloseHideWindow.SetIcon(IDI_ICON6);
	m_btnCloseHideWindow.SetFlat(FALSE);
     
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CHideToolDlg::OnBnClickedButtonOpenhide()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
      WinExec(CW2A(_T("systemopen.bat")),SW_HIDE); 
	  Sleep(1000);
	  MessageBox(_T("����Է������˽���ļ���"),_T("��ϲ"),MB_OK);
	  ShellExecute(NULL,_T("open"),_T("k://"),NULL,NULL,SW_SHOW);
	
}

void CHideToolDlg::OnBnClickedButtonClosehide()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	WinExec(CW2A(_T("systemclose.bat")),SW_HIDE);
}
