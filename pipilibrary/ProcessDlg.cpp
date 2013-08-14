// ProcessDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "pipilibrary.h"
#include "ProcessDlg.h"


// CProcessDlg �Ի���
CProcessDlg m_Dlg;

IMPLEMENT_DYNAMIC(CProcessDlg, CDialog)

CProcessDlg::CProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessDlg::IDD, pParent)
{

}

CProcessDlg::~CProcessDlg()
{

}

void CProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
}


BEGIN_MESSAGE_MAP(CProcessDlg, CDialog)
END_MESSAGE_MAP()


// CProcessDlg ��Ϣ�������

BOOL CProcessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

	DWORD  dwn = 0;
int CProcessDlg::InternetGetFile(CString szUrl,CString szFileName)
{	
	DWORD dwFlags;
     ShowWindow(SW_SHOW);
    m_progress.SetRange(0,743138);
 	InternetGetConnectedState(&dwFlags, 0);
	CHAR strAgent[64];
	sprintf(strAgent, "Agent%ld", timeGetTime());
	HINTERNET hOpen;
	if(!(dwFlags & INTERNET_CONNECTION_PROXY))
		hOpen = InternetOpenA(strAgent, INTERNET_OPEN_TYPE_PRECONFIG_WITH_NO_AUTOPROXY, NULL, NULL, 0);
	else
		hOpen = InternetOpenA(strAgent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if(!hOpen)
	{
		//AfxMessageBox("Internet���Ӵ���!");
		return -1;
	}
 
	DWORD dwSize;
	CHAR   szHead[] = "Accept: */*\r\n\r\n";
	VOID* szTemp[16384];
	HINTERNET  hConnect;
	CFile file;
 
	USES_CONVERSION;
	if ( !(hConnect = InternetOpenUrlA ( hOpen,CW2A(szUrl), szHead,
		 lstrlenA (szHead), INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_RELOAD, 0)))
	{
	  // AfxMessageBox("���ܴ򿪸�URL!");
	   return -1;
	}

	if  (file.Open(szFileName,CFile::modeWrite|CFile::modeCreate)==FALSE )
	{
	   //AfxMessageBox("���ܴ򿪱��ص��ļ�!");
	  return -1;
	}

	DWORD dwByteToRead = 0;
	DWORD dwSizeOfRq = 4;
	DWORD dwBytes = 0;

    if (!HttpQueryInfo(hConnect, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, 
                  (LPVOID)&dwByteToRead, &dwSizeOfRq, NULL))
	{
		dwByteToRead = 0;
	}


	do
	{
		if (!InternetReadFile (hConnect, szTemp, 16384,  &dwSize))
		{
			//AfxMessageBox("���ļ�����!");
			file.Close();
			return -1;
		}
		if (dwSize==0)
			break;
		else
			file.Write(szTemp,dwSize);
		dwBytes+=dwSize;
		m_progress.SetPos(dwBytes);
		dwn = dwBytes;

	}while (TRUE);
    

	file.Close();
	InternetCloseHandle(hOpen);
	WinExec("war3ToolSetup.exe",SW_SHOW);
	return 0;
}


CProcessDlg &GetProcessDlg()
{  
	return m_Dlg;
}
