// ShowImageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShowImage.h"
#include "ShowImageDlg.h"

#include <windows.h>
#include <afxinet.h>

#include "winsock2.h"   

#pragma   comment(lib,"ws2_32.lib")   
#define   winsock_version   0x0101 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

IStream		* pStream  = NULL;
IPicture	* pPicture = NULL;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowImageDlg dialog

CShowImageDlg::CShowImageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowImageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowImageDlg)
	m_strUser = _T("pengfeicfan");
	m_strPassword = _T("6112495qq");
	m_strCode = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShowImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowImageDlg)
	DDX_Control(pDX, IDC_STATIC1, m_StaticText);
	DDX_Text(pDX, IDC_EDIT_USER, m_strUser);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_CODE, m_strCode);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShowImageDlg, CDialog)
	//{{AFX_MSG_MAP(CShowImageDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOGIN, OnBtnLogin)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_WM_CLOSE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowImageDlg message handlers

/************************************************************************/     
/* ����˵������ȡӦ�ó���ǰĿ¼                                         
/* ��    ������                                     
/* �� �� ֵ������Ŀ¼·����CString�����ַ���      
/* By:Koma   2009.10.13 11:23                                 
/************************************************************************/     
CString CShowImageDlg::GetExePath()   
{   
    char pathbuf[260];      
    int  pathlen = ::GetModuleFileName(NULL,pathbuf,260);      
	
    // �滻������   
    while(TRUE)      
    {      
        if(pathbuf[pathlen--]=='\\')      
            break;      
    }      
    pathbuf[++pathlen]=   0x0;      
    CString  fname = pathbuf;      
    return   fname;      
}  

/************************************************************************/     
/* ����˵����������֤��ͼƬ                                         
/* ��    ������                                     
/* �� �� ֵ����      
/* By:Koma   2009.10.13 11:50                                  
/************************************************************************/ 
void CShowImageDlg::DownURLImage()
{
	CInternetSession	session;
	CString		strUrl;
	CFile		*pFile,out; 
	char		buff[512];
	CString		strPath;
	
	// ������λ������������֤��
	int			nRand1 = rand()%100000+10000;
	int			nRand2 = rand()%200000+10000;

	strUrl.Format("http://passport.csdn.net/ShowExPwd.aspx?temp=%d%d",nRand1,nRand2);
	strPath = GetExePath() + "\\test.tmp";
	pFile = session.OpenURL(strUrl); 
	out.Open(strPath, CFile::modeCreate | CFile::modeWrite); 
	while(pFile->Read(buff,512)){ 
		out.Write(buff,512); 
	} 
	out.Flush();
	out.Close(); 
}

/************************************************************************/     
/* ����˵������ʾ��֤��ͼƬ                                         
/* ��    ������                                     
/* �� �� ֵ����      
/* By:Koma   2009.10.13 13:12                                 
/************************************************************************/ 
void CShowImageDlg::ShowImage()
{
	::CoInitialize(NULL);			// ��ʼ��COM 
	HRESULT	hr; 
	CFile	file;
	CString	strPath;
	CPaintDC dc(this);
	
	strPath = GetExePath() + "\\test.tmp";
	file.Open(strPath, CFile::modeRead | CFile::shareDenyNone);

	DWORD	dwSize = file.GetLength(); 
	HGLOBAL hMem = ::GlobalAlloc( GMEM_MOVEABLE, dwSize ); 
	LPVOID	lpBuf = ::GlobalLock( hMem ); 

	file.Read( lpBuf, dwSize ); 
	file.Close(); 
	::GlobalUnlock( hMem ); 
	
	// ��HGLOBAL�õ�IStream������TRUE ��ʾ�ͷ�IStream��ͬʱ���ͷ��ڴ� 
	hr = ::CreateStreamOnHGlobal(hMem,TRUE,&pStream ); 
	ASSERT(SUCCEEDED(hr)); 
	
	hr = ::OleLoadPicture(pStream, dwSize, TRUE, IID_IPicture,(LPVOID *)&pPicture); 
	ASSERT(hr==S_OK); 
	
	long nWidth,nHeight;				// ��� MM_HIMETRICģʽ����λ��0.01���� 
	pPicture->get_Width( &nWidth );		// �� 
	pPicture->get_Height( &nHeight );	// �� 

	CSize sz(nWidth,nHeight);			// ԭ����ʾ
	dc.HIMETRICtoDP(&sz);				// ת��MM_HIMETRICģʽ��λΪMM_TEXT���ص�λ 
	
	pPicture->Render(dc.m_hDC,10,100,sz.cx,sz.cy,0,nHeight,nWidth,-nHeight,NULL); 
	CRect rect(10,100,sz.cx + 10,sz.cy + 100);

	// ��ͼƬ���򱣴棬�Ա����ֻˢ��ͼƬ����
	m_PicRect = rect;
	if(pPicture)						// �ͷ�IPictureָ��
		pPicture->Release();
	if(pStream)							// �ͷ�IStreamָ�룬ͬʱ�ͷ�hMem
		pStream->Release();
	::CoUninitialize();
}

int CShowImageDlg::SendForm()
{
	// InvalidateRect(&m_PicRect);
	// Code: XA69W
	UpdateData(TRUE);
	CString	str1 = "POST /UserLogin.aspx HTTP/1.1\r\n";
	CString str2 = "Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, application/QVOD, application/QVOD, */*\r\n";
	CString str3 = "Referer: http://passport.csdn.net/UserLogin.aspx\r\n";
	CString str4 = "Accept-Language: zh-cn\r\n";
	CString str5 = "Content-Type: application/x-www-form-urlencoded\r\n";
	CString str6 = "Accept-Encoding: gzip, deflate\r\n";
	CString str7 = "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; POTU(RR:28031409:0:5513822); Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1) ; .NET CLR 2.0.50727; CIBA)\r\n";
	CString str8 = "Host: passport.csdn.net\r\n";
	CString str9 = "Content-Length: 669\r\n";
	CString str10 = "Connection: Keep-Alive\r\n";
	CString str11 = "Cache-Control: no-cache\r\n";

	CString str17 = "Bh97Uk6ofQQady&ctl00%24CPH_Content%24tb_LoginNameOrLoginEmail=" + m_strUser + "&ctl00%24C";
	CString str18 = "PH_Content%24tb_Password=" + m_strPassword +"&ctl00%24CPH_Content%24tb_ExPwd=" + m_strCode + "&ClientKey";

	CString strData = str1+str2+str3+str4+str5+str6+str7+str8+str9+str10+str17+str18;
	SOCKADDR_IN saServer;   
	LPHOSTENT   lphostent;   
	WSADATA		wsadata;   
	SOCKET		hsocket;   
	int			nRet;   
	const char* host_name="passport.csdn.net";   

	if(WSAStartup(winsock_version,&wsadata))   
		MessageBox("��ʼ��SOCKET����");
	
	lphostent=gethostbyname(host_name);   
	if(lphostent==NULL)   
		MessageBox("lphostentΪ�գ�");
	
	hsocket   =   socket(AF_INET,   SOCK_STREAM,   IPPROTO_TCP);   
	saServer.sin_family   =   AF_INET;   
	saServer.sin_port = htons(80);   
	saServer.sin_addr = *((LPIN_ADDR)*lphostent->h_addr_list);   
	nRet = connect(hsocket,(LPSOCKADDR)&saServer,sizeof(SOCKADDR_IN));   
	if(nRet == SOCKET_ERROR)   
	{   
		MessageBox("���ܽ������ӣ�");   
		closesocket(hsocket);   
		return 0;   
	}
	else
		MessageBox("connected with %s\n",host_name);
	
	MessageBox(strData);
	nRet = send(hsocket,strData,strData.GetLength(),0);
	if(nRet==SOCKET_ERROR)
	{
		MessageBox("send() Failed");
		closesocket(hsocket);
	}

	char   dest[1000];
	memset(dest,0,1000);
	nRet=1;   
	while(nRet>0)   
	{   
		nRet=recv(hsocket,(LPSTR)dest,sizeof(dest),0);   
		if(nRet>0)   
			dest[nRet]=0;   
		else   
			dest[0]=0;
		CString strRecv;
		strRecv.Format("\nReceived bytes:%d\nResult:\n%s",nRet,dest);   
		MessageBox(strRecv);
		if(nRet == 171)
			MessageBox("Invalid Header Name.");
	}
	return nRet;
}

BOOL CShowImageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	// ��ȡ��̬�ı��ؼ�����
	GetDlgItem(IDC_STATIC1)->GetWindowRect(&m_pRectLink);
	ScreenToClient(&m_pRectLink);

//	Invalidate();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CShowImageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CShowImageDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//DownURLImage();		// �������ػ�ʱ����������֤��
		//Sleep(50);			// ����50����
		//ShowImage();		// ������ʾ��֤��
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CShowImageDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CShowImageDlg::OnBtnLogin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_strUser.IsEmpty())
	{
		MessageBox("�û�������Ϊ�գ�","��ʾ",MB_ICONERROR | MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_USER)->SetFocus(); 
		return;
	}
	if( m_strPassword.IsEmpty())
	{
		MessageBox("���벻��Ϊ�գ�","��ʾ",MB_ICONERROR | MB_OK);
		(CEdit*)GetDlgItem(IDC_EDIT_PASSWORD)->SetFocus(); 
		return;
	}

	// ֮ǰ������SOCKET���ͱ������������û���ҳ�ԭ����λ�ֵܰ�æ����
	// SendForm();

	//���ò�����
	CInternetSession m_InetSession(_T("session"),0,INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,INTERNET_FLAG_DONT_CACHE);     
	
	UpdateData(TRUE);
	CHttpConnection	* pServer = NULL;	// Server
	CHttpFile		* pFile = NULL;		// HTTP File
	CString			strHtml = "";		// Recv Data

	CString strHeaders = "POST /userlogin.aspx HTTP/1.0\r\nAccept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/vnd.ms-excel, application/msword, application/vnd.ms-powerpoint, */*\r\nAccept-Language: en-us\r\nAccept-Encoding: gzip, deflate\r\nUser-Agent: Mozilla/4.0\r\nContent-Length: 708\r\nContent-Length: 708\r\nContent-Length: 708\r\nHost: PASSPORT.CSDN.NET\r\n";
	CString strRequest = "__EVENTTARGET=&__EVENTARGUMENT=&__VIEWSTATE=%2FwEPDwULLTEyMzU0NzEzNDkPFgIeCkZpbmlzaFN0YXlnFgJmD2QWBAIBDxYCHgRUZXh0BQznlKjmiLfnmbvlvZVkAgIPZBYCAgMPZBYCAgEPFgIeB1Zpc2libGVoZBgBBR5fX0NvbnRyb2xzUmVxdWlyZVBvc3RCYWNrS2V5X18WAgUeY3RsMDAkQ1BIX0NvbnRlbnQkY2JfU2F2ZVN0YXRlBR1jdGwwMCRDUEhfQ29udGVudCRJbWFnZV9Mb2dpbjFp31Bt8XH%2B3e%2Bh97Uk6ofQQady&ctl00%24CPH_Content%24tb_LoginNameOrLoginEmail="+ m_strUser +"&ctl00%24CPH_Content%24tb_Password="+ m_strPassword +"&ctl00%24CPH_Content%24tb_ExPwd="+ m_strCode +"&ClientKey=a667fbdd-3fc7-42bf-bd83-9f16b8330b26&ctl00%24CPH_Content%24cb_SaveState=on&from=http%3A%2F%2Fhi.csdn.net%2F&MailParameters=&PrePage=&MailParameters=&ctl00%24CPH_Content%24Image_Login.x=21&ctl00%24CPH_Content%24Image_Login.y=14";
	try{
		INTERNET_PORT nPort;
		nPort=80;
		pServer = m_InetSession.GetHttpConnection("passport.csdn.net", nPort);
		pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_POST,"/");
		pFile->AddRequestHeaders(strHeaders);
		pFile->SendRequestEx(strRequest.GetLength()+1);
		pFile->WriteString(strRequest);
		pFile->EndRequest();
		
		DWORD	dwRet;
		int		nRead = 0;
		CString strLine;
		pFile->QueryInfoStatusCode(dwRet);
		if(dwRet == HTTP_STATUS_OK)
		{
			while ((nRead = pFile->ReadString(strLine))>0)
			{
				strHtml += strLine;
			}
		}
		// ����һЩ������û�ٷ����ˣ���λ����Ը������ɰɣ�
		// MessageBox(strHtml);
		// CFile       file("3.html",CFile::modeCreate | CFile::modeWrite);   
		// file.Write(strHtml,strHtml.GetLength());   
		// file.Flush();   
		// file.Close(); 
		// delete pFile;
		// delete pServer;
	}
	catch (CInternetException* e){
		e->m_dwContext;
	}
}

void CShowImageDlg::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_CLOSE);
}

void CShowImageDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	// ɾ����֤�����ʱ�ļ�
	CString strPath;
	strPath = GetExePath() + "\\test.tmp";
	DeleteFile(strPath);

	CDialog::OnClose();
}

void CShowImageDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (point.x>m_pRectLink.left&&point.x<m_pRectLink.right&&point.y>m_pRectLink.top&&point.y<m_pRectLink.bottom)
	{
		if (nFlags==MK_LBUTTON)	// �����̬����,������֤��
		{
			//InvalidateRect(&m_PicRect);
			Invalidate();
		}
	}
	if (point.x>m_PicRect.left&&point.x<m_PicRect.right&&point.y>m_PicRect.top&&point.y<m_PicRect.bottom)
	{
		if (nFlags==MK_LBUTTON)	// ���ͼƬ,������֤��
		{
			//InvalidateRect(&m_PicRect);
			Invalidate();
		}
	}
	CDialog::OnLButtonDown(nFlags, point);
}
