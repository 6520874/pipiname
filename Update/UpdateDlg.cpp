
// UpdateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Update.h"
#include "UpdateDlg.h"
#include <Wininet.h>
#include <Mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CUpdateDlg �Ի���




CUpdateDlg::CUpdateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_process);
}

BEGIN_MESSAGE_MAP(CUpdateDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CUpdateDlg ��Ϣ�������






BOOL CUpdateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
    WinExec("kill.bat",SW_HIDE);
    InternetGetFile(_T("http://pipihaha.sinaapp.com/War3ToolSetup.exe"),_T("war3ToolSetup.exe"));
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


BOOL CUpdateDlg::IsUpdate()
{
	TCHAR StrCurrentDir[256] ={0};
	GetCurrentDirectory(256,StrCurrentDir);
	CString warPath(StrCurrentDir);
	TCHAR  szValue[MAX_PATH] = {0};
	GetPrivateProfileString(_T("War3version"),_T("version"),_T("130101"),szValue,MAX_PATH,warPath+_T("//war3set.ini"));
	CString csVerOld(szValue);

//	cUpdateSDlg.DownCommonFile(_T("http://pipihaha.sinaapp.com/war3set.ini"),_T("war3update.ini"));
	GetPrivateProfileString(_T("War3version"),_T("version"),_T("130812"),szValue,MAX_PATH,warPath+_T("//war3update.ini"));
	CString csVerNew(szValue);

	if(csVerOld == csVerNew)
	{
		return FALSE;
	}
	else
	{
		//cUpdateSDlg.Apply(_T("http://pipihaha.sinaapp.com/War3ToolSetup.exe"),_T("war3ToolSetup.exe"));

		return TRUE;
	}
}

void CUpdateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUpdateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CUpdateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CUpdateDlg::InternetGetFile(CString szUrl,CString szFileName)
{	
	if(szUrl.IsEmpty() ||szFileName.IsEmpty())
	{
		return -1;
	}

	DWORD dwFlags;
     ShowWindow(SW_SHOW);
    m_process.SetRange(0,743138);
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
	if ( !(hConnect = InternetOpenUrlA ( hOpen,szUrl,szHead,
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
		m_process.SetPos(dwBytes);
		//dwn = dwBytes;

	}while (TRUE);
    

	file.Close();
	InternetCloseHandle(hOpen);
	WinExec("war3ToolSetup.exe",SW_SHOW);
	SendMessage(WM_CLOSE,0,0);
	return 0;
}