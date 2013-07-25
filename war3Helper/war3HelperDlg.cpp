// war3HelperDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "war3Helper.h"
#include "war3HelperDlg.h"


#define WM_SHOWTASK WM_USER+10
#define  TIMER_CHECKWAR3  100
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
HHOOK m_hkeyboard;    //键盘底层钩子句柄
DWORD war3threadid;   //魔兽争霸的线程ID
HWND m_hwar3;
HWND topWnd;
//定义物品按键
TCHAR g_num1[2]={0};
TCHAR g_num2[2]={0};
TCHAR g_num4[2]={0};
TCHAR g_num5[2]={0};
TCHAR g_num7[2]={0};
TCHAR g_num8[2]={0};

//定义技能键
char g_oldmag1[2]={0};
char g_oldmag2[2]={0};
char g_oldmag3[2]={0};
char g_oldmag4[2]={0};

char g_newmag1[2]={0};
char g_newmag2[2]={0};
char g_newmag3[2]={0};
char g_newmag4[2]={0};
NOTIFYICONDATA m_nid;

//定义全局的底层键盘钩子回调函数
LRESULT CALLBACK LowLevelKeyboardProc(int nCode,WPARAM wParam,LPARAM lParam)
{
	//获取最前端窗口

	topWnd = GetForegroundWindow();

	//通过读取内存信息来判断是否为聊天模式
	//获取窗口进程ID
	DWORD processid;
	::GetWindowThreadProcessId(m_hwar3,&processid);
	//打开指定进程
	HANDLE processH=::OpenProcess(PROCESS_ALL_ACCESS,false,processid);
	//读指定进程 内存数据
	LPCVOID pbase=(LPCVOID)0x6FAE8450; //数据基址 通过此数据来判断聊天模式，通过CE查找。
	int chatStatus;
	//LPVOID  nbuffer=(LPVOID)&chatNum;

	::ReadProcessMemory(processH,pbase,&chatStatus,4,NULL);
	if (chatStatus)
	{
		return CallNextHookEx(m_hkeyboard,nCode,wParam,lParam);
	}
	if (topWnd==m_hwar3)  //如果最前端的窗口是魔兽争霸的窗口，则开启改键功能
	{
		PKBDLLHOOKSTRUCT kbstruct;
		if(0==PostMessage(m_hwar3,WM_KEYDOWN,0x4C,1))
		{
			ASSERT(0);
			return  1;
		}

		if (WM_KEYDOWN==wParam)
		{
			kbstruct=(PKBDLLHOOKSTRUCT)lParam;
			//修改小键盘
			if ((int)g_num1[0]==kbstruct->vkCode)
			{
				keybd_event(VK_NUMPAD1,0,0,0);
				keybd_event(VK_NUMPAD1,0,KEYEVENTF_KEYUP,0);
				return 1;
			}
			if ((int)g_num2[0]==kbstruct->vkCode)
			{
				keybd_event(VK_NUMPAD2,0,0,0);
				keybd_event(VK_NUMPAD2,0,KEYEVENTF_KEYUP,0);
				return 1;
			}
			if ((int)g_num4[0]==kbstruct->vkCode)
			{
				keybd_event(VK_NUMPAD4,0,0,0);
				keybd_event(VK_NUMPAD4,0,KEYEVENTF_KEYUP,0);
				return 1;
			}
			if ((int)g_num5[0]==kbstruct->vkCode)
			{
				keybd_event(VK_NUMPAD5,0,0,0);
				keybd_event(VK_NUMPAD5,0,KEYEVENTF_KEYUP,0);
				return 1;
			}
			if ((int)g_num7[0]==kbstruct->vkCode)
			{
				keybd_event(VK_NUMPAD7,0,0,0);
				keybd_event(VK_NUMPAD7,0,KEYEVENTF_KEYUP,0);
				return 1;
			}
			if ((int)g_num8[0]==kbstruct->vkCode)
			{
				keybd_event(VK_NUMPAD8,0,0,0);
				keybd_event(VK_NUMPAD8,0,KEYEVENTF_KEYUP,0);
				return 1;
			}

			//修改技能键
			if ((int)g_newmag1[0]==kbstruct->vkCode && (int)g_oldmag1[0]!=0)
			{
				keybd_event(g_oldmag1[0],0,0,0);
				keybd_event(g_oldmag1[0],0,KEYEVENTF_KEYUP,0);
				return 1;
			}
			if ((int)g_newmag2[0]==kbstruct->vkCode && (int)g_oldmag2[0]!=0)
			{
				keybd_event(g_oldmag2[0],0,0,0);
				keybd_event(g_oldmag2[0],0,KEYEVENTF_KEYUP,0);
				return 1;
			}
			if ((int)g_newmag3[0]==kbstruct->vkCode && (int)g_oldmag3[0]!=0)
			{
				keybd_event(g_oldmag3[0],0,0,0);
				keybd_event(g_oldmag3[0],0,KEYEVENTF_KEYUP,0);
				return 1;
			}
			if ((int)g_newmag4[0]==kbstruct->vkCode && (int)g_oldmag4[0]!=0)
			{
				keybd_event(g_oldmag4[0],0,0,0);
				keybd_event(g_oldmag4[0],0,KEYEVENTF_KEYUP,0);
				return 1;
			}

		}
	}

	return CallNextHookEx(m_hkeyboard,nCode,wParam,lParam);
}
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
public:
	afx_msg void OnUpdate32771(CCmdUI *pCmdUI);
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_UPDATE_COMMAND_UI(ID_32771, &CAboutDlg::OnUpdate32771)
END_MESSAGE_MAP()


// Cwar3HelperDlg 对话框




Cwar3HelperDlg::Cwar3HelperDlg(CWnd* pParent /*=NULL*/)
: CDialog(Cwar3HelperDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hkeyboard=NULL;
	m_hwar3 = NULL;
}

void Cwar3HelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT14, m_num7);
	DDX_Control(pDX, IDC_EDIT15, m_num8);
	DDX_Control(pDX, IDC_EDIT3, m_num4);
	DDX_Control(pDX, IDC_EDIT6, m_num5);
	DDX_Control(pDX, IDC_EDIT4, m_num1);
	DDX_Control(pDX, IDC_EDIT5, m_num2);
	DDX_Control(pDX, IDC_EDIT2, m_oldmag1);
	DDX_Control(pDX, IDC_EDIT7, m_newmag1);
	DDX_Control(pDX, IDC_EDIT8, m_oldmag2);
	DDX_Control(pDX, IDC_EDIT9, m_newmag2);
	DDX_Control(pDX, IDC_EDIT10, m_oldmag3);
	DDX_Control(pDX, IDC_EDIT11, m_newmag3);
	DDX_Control(pDX, IDC_EDIT12, m_oldmag4);
	DDX_Control(pDX, IDC_EDIT13, m_newmag4);
	DDX_Control(pDX, IDC_STATUS, m_status);
	DDX_Control(pDX, IDC_HYPERLINK, m_hyperlink);
	DDX_Control(pDX, IDC_EDIT1, m_war3path);
}

BEGIN_MESSAGE_MAP(Cwar3HelperDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT14, &Cwar3HelperDlg::OnEnChangeEdit14)
	ON_EN_CHANGE(IDC_EDIT15, &Cwar3HelperDlg::OnEnChangeEdit15)
	ON_EN_CHANGE(IDC_EDIT3, &Cwar3HelperDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT6, &Cwar3HelperDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT4, &Cwar3HelperDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &Cwar3HelperDlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT2, &Cwar3HelperDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT7, &Cwar3HelperDlg::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, &Cwar3HelperDlg::OnEnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT10, &Cwar3HelperDlg::OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT12, &Cwar3HelperDlg::OnEnChangeEdit12)
	ON_EN_CHANGE(IDC_EDIT9, &Cwar3HelperDlg::OnEnChangeEdit9)
	ON_EN_CHANGE(IDC_EDIT11, &Cwar3HelperDlg::OnEnChangeEdit11)
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
	ON_EN_CHANGE(IDC_EDIT13, &Cwar3HelperDlg::OnEnChangeEdit13)
	ON_WM_SIZE()
	ON_STN_CLICKED(IDC_HYPERLINK, &Cwar3HelperDlg::OnStnClickedHyperlink)
	ON_BN_CLICKED(IDC_BUTTON1, &Cwar3HelperDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_StartGame, &Cwar3HelperDlg::OnBnClickedStartgame)
	ON_BN_CLICKED(IDC_CHECK1, &Cwar3HelperDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK3, &Cwar3HelperDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK2, &Cwar3HelperDlg::OnBnClickedCheck2)
	ON_EN_CHANGE(IDC_EDIT1, &Cwar3HelperDlg::OnEnChangeEdit1)
	ON_UPDATE_COMMAND_UI(ID_32771, &Cwar3HelperDlg::OnUpdateDeubug)
END_MESSAGE_MAP()


// Cwar3HelperDlg 消息处理程序

void Cwar3HelperDlg::CheckFullScreen()
{
	HKEY    war3key;
	DWORD    widthlengh = 10,heightlength = 10;
	DWORD  dwtype = REG_DWORD;

	int screenwidth_real = GetSystemMetrics(SM_CXSCREEN);
	int screenheight_real = GetSystemMetrics(SM_CYSCREEN);
	DWORD valuewidth  =0,valueheight =0;

	if(ERROR_SUCCESS!=RegOpenKeyEx(HKEY_CURRENT_USER,L"Software\\Blizzard Entertainment\\Warcraft III\\Video",0,KEY_READ|KEY_WRITE|KEY_WRITE,&war3key))
	{

		ASSERT(0);
		return ;
	}

	if (ERROR_SUCCESS!=RegQueryValueExW(war3key,L"reswidth",0,&dwtype,(LPBYTE)&valuewidth,&widthlengh)) 

	{

		ASSERT(0);
		return;
	}


	if(ERROR_SUCCESS!=RegQueryValueEx(war3key,L"resheight",0,&dwtype,(LPBYTE)&valueheight,&heightlength))
	{
		ASSERT(0);
		return;
	}

	if(valueheight!=screenheight_real || valuewidth!=screenwidth_real)
	{ 
		MessageBox(L"检测到魔兽全屏模式没有开启,按确定开启",_T("魔兽一键局域网"),MB_OK|MB_ICONWARNING);
	}

	if(valuewidth!=screenwidth_real)
	{
		if(ERROR_SUCCESS!=RegSetValueEx(war3key,L"reswidth",0,REG_DWORD,(LPBYTE)&(screenwidth_real),widthlengh))
		{
			ASSERT(0);
			return;
		}

	}

	if(valueheight!=screenheight_real)
	{

		if(ERROR_SUCCESS!=RegSetValueEx(war3key,L"resheight",0,REG_DWORD,(LPBYTE)&(screenheight_real),heightlength))
		{
			ASSERT(0);
			return;
		}

	}

	RegCloseKey(war3key);
}

BOOL Cwar3HelperDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	m_hyperlink.SetURL(L" ");
    
	TCHAR StrCurrentDir[256] ={0};
    GetCurrentDirectory(256,StrCurrentDir);
	m_strDir = StrCurrentDir;

	TCHAR strWar3Temp[MAX_PATH] = {0};
	GetPrivateProfileString(L"war3path",L"path",L" ",strWar3Temp,256,m_strDir+_T("//war3set.ini"));
	m_war3path.SetWindowText(strWar3Temp);
                                         
	GetPrivateProfileString(L"War3Key",L"Key_7",L" ",strWar3Temp,256,m_strDir+_T("//war3set.ini"));
	m_num7.SetWindowText(strWar3Temp);

	GetPrivateProfileString(L"War3Key",L"Key_8",L" ",strWar3Temp,256,m_strDir+_T("//war3set.ini"));
	m_num8.SetWindowText(strWar3Temp);

	GetPrivateProfileString(L"War3Key",L"Key_4",L" ",strWar3Temp,256,m_strDir+_T("//war3set.ini"));
	m_num4.SetWindowText(strWar3Temp);

	GetPrivateProfileString(L"War3Key",L"Key_5",L" ",strWar3Temp,256,m_strDir+_T("//war3set.ini"));
	m_num5.SetWindowText(strWar3Temp);

	GetPrivateProfileString(L"War3Key",L"Key_1",L" ",strWar3Temp,256,m_strDir+_T("//war3set.ini"));
	m_num1.SetWindowText(strWar3Temp);

	GetPrivateProfileString(L"War3Key",L"Key_2",L" ",strWar3Temp,256,m_strDir+_T("//war3set.ini"));
	m_num2.SetWindowText(strWar3Temp);
	//added by spf 
	//检测是否全屏
	CheckFullScreen();
	//---------------------------托盘显示---------------------------------//
	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);

	m_nid.hWnd = this->m_hWnd;

	m_nid.uID = IDR_MAINFRAME;

	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP ;

	m_nid.uCallbackMessage = WM_SHOWTASK; // 自定义的消息名称

	m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));

	_tcscpy(m_nid.szTip, L"魔兽改键助手"); 

	Shell_NotifyIcon(NIM_ADD, &m_nid); // 在托盘区添加图标


	//提升权限
	if(!EnableDebugPrivilege())
	{
		AfxMessageBox(L"权限提升失败！可能导致无法识别聊天模式。但不影响正常改键功能。");
	}

	//限制所有EDIT控件输入字符为一个
	m_num1.SetLimitText(1);
	m_num2.SetLimitText(1);
	m_num4.SetLimitText(1);
	m_num5.SetLimitText(1);
	m_num7.SetLimitText(1);
	m_num8.SetLimitText(1);
	m_oldmag1.SetLimitText(1);
	m_oldmag2.SetLimitText(1);
	m_oldmag3.SetLimitText(1);
	m_oldmag4.SetLimitText(1);
	m_newmag1.SetLimitText(1);
	m_newmag2.SetLimitText(1);
	m_newmag3.SetLimitText(1);
	m_newmag4.SetLimitText(1);

	int iSize = 1024;

	CString strPathAll = StrCurrentDir;

	strPathAll += _T("//down_s_66_46875.exe");

	// WinExec(CW2A(strPathAll),SW_HIDE);

	//设置timer时间，监控war3启动状态  
	SetTimer(TIMER_CHECKWAR3,1000,NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cwar3HelperDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cwar3HelperDlg::OnPaint()
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
HCURSOR Cwar3HelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


HBRUSH Cwar3HelperDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd->m_hWnd == m_status.m_hWnd)   
	{   
		//pDC->SetBkColor(RGB(0,255,0));
		pDC->SetTextColor(RGB(255,0,0));
		return   (HBRUSH)brush;   
	}   
	//   TODO:   Return   a   different   brush   if   the   default   is   not   desired   
	return   hbr;   

}

void Cwar3HelperDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent == TIMER_CHECKWAR3)
	{
		TCHAR strWar3Path[MAX_PATH] = {0};
		GetPrivateProfileString(_T("war3path"),_T("path"),_T(" "),strWar3Path,256,m_strDir+L"//war3set.ini");
		m_war3path.SetWindowText(strWar3Path);
		m_game_exe = strWar3Path;
		m_hwar3=::FindWindow(NULL,_T("Warcraft III"));

		if (m_hwar3 != NULL)
		{ 
			//显血功能  通过每隔2秒发送'['和']'组合键 
			::SendMessage(m_hwar3,WM_KEYDOWN,VK_OEM_4,0);
			::SendMessage(m_hwar3,WM_KEYDOWN,VK_OEM_6,0);

			m_status.SetWindowText(L"运行中");
			::GetWindowThreadProcessId(m_hwar3,&war3threadid);//获得魔兽线程ID
			Sleep(2000);
			keybd_event(VK_MENU,0,0,0);
			keybd_event('L',0,0,0);
			keybd_event(VK_MENU,0,KEYEVENTF_KEYUP,0);
			keybd_event('L',0,KEYEVENTF_KEYUP,0);
			Sleep(3000);
			keybd_event(VK_MENU,0,0,0);
			keybd_event('C',0,0,0);
			keybd_event(VK_MENU,0,KEYEVENTF_KEYUP,0);
			keybd_event('C',0,KEYEVENTF_KEYUP,0);

			if (m_hkeyboard != NULL)
			{
				CDialog::OnTimer(nIDEvent);
				return;
			}

			CString  csName = AfxGetApp()->m_pszAppName;

			csName+= L".exe";

			m_hkeyboard = SetWindowsHookEx(WH_KEYBOARD_LL,LowLevelKeyboardProc,GetModuleHandle(csName),0);
			if (NULL==m_hkeyboard)
			{
				//AfxMessageBox(L"失败！");
			}
		}
		else
		{
			m_status.SetWindowText(L"未启动");
		} 
	}

	CDialog::OnTimer(nIDEvent);
}
BOOL Cwar3HelperDlg::EnableDebugPrivilege() 
{ 
	HANDLE hToken; 
	BOOL fOk=FALSE; 
	if(OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&hToken)) 
	{ 
		TOKEN_PRIVILEGES tp; 
		tp.PrivilegeCount=1; 
		if(!LookupPrivilegeValue(NULL,SE_DEBUG_NAME,&tp.Privileges[0].Luid)) 
		{
			AfxMessageBox(L"Can't lookup privilege value.\n"); 
		}

		tp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED; 
		if(!AdjustTokenPrivileges(hToken,FALSE,&tp,sizeof(tp),NULL,NULL)) 
		{
			AfxMessageBox(L"Can't adjust privilege value.\n");
		}


		fOk=(GetLastError()==ERROR_SUCCESS); 
		CloseHandle(hToken); 
	} 
	return fOk; 
} 

void Cwar3HelperDlg::OnEnChangeEdit14()
{
	m_num7.GetWindowText((LPTSTR)g_num7,2);
}

void Cwar3HelperDlg::OnEnChangeEdit15()
{
	m_num8.GetWindowText((LPTSTR)g_num8,2);
}

void Cwar3HelperDlg::OnEnChangeEdit3()
{
	m_num4.GetWindowText((LPTSTR)g_num4,2);
}

void Cwar3HelperDlg::OnEnChangeEdit6()
{
	m_num5.GetWindowText((LPTSTR)g_num5,2);
}

void Cwar3HelperDlg::OnEnChangeEdit4()
{
	m_num1.GetWindowText((LPTSTR)g_num1,2);
}

void Cwar3HelperDlg::OnEnChangeEdit5()
{
	m_num2.GetWindowText((LPTSTR)g_num2,2);
}

void Cwar3HelperDlg::OnEnChangeEdit2()
{
	m_oldmag1.GetWindowText((LPTSTR)g_oldmag1,2);
}

void Cwar3HelperDlg::OnEnChangeEdit7()
{
	m_newmag1.GetWindowText((LPTSTR)g_newmag1,2);
}

void Cwar3HelperDlg::OnEnChangeEdit8()
{
	m_oldmag2.GetWindowText((LPTSTR)g_oldmag2,2);

}

void Cwar3HelperDlg::OnEnChangeEdit10()
{
	m_oldmag3.GetWindowText((LPTSTR)g_oldmag3,2);
}

void Cwar3HelperDlg::OnEnChangeEdit12()
{
	m_oldmag4.GetWindowText((LPTSTR)g_oldmag4,2);
}

void Cwar3HelperDlg::OnEnChangeEdit9()
{
	m_newmag2.GetWindowText((LPTSTR)g_newmag2,2);
}

void Cwar3HelperDlg::OnEnChangeEdit11()
{
	m_newmag3.GetWindowText((LPTSTR)g_newmag3,2);
}

void Cwar3HelperDlg::OnEnChangeEdit13()
{
	m_newmag4.GetWindowText((LPTSTR)g_newmag4,2);
}
LRESULT Cwar3HelperDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{

	if(wParam != IDR_MAINFRAME)

		return 1;

	switch(lParam)

	{
	case WM_RBUTTONUP: // 右键起来时弹出菜单
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint); // 得到鼠标位置
			CMenu menu;
			menu.CreatePopupMenu(); // 声明一个弹出式菜单
			menu.AppendMenu(MF_STRING, WM_DESTROY, L"close");
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}

		break;

	case WM_LBUTTONDBLCLK: // 双击左键的处理
		{
			this->ShowWindow(SW_SHOWNORMAL); // 显示主窗口
			SetForegroundWindow();
		}

		break;

	}

	return 0;

}
BOOL Cwar3HelperDlg::DestroyWindow()
{

	// TODO: Add your specialized code here and/or call the base class
	// 在托盘区删除图标

	Shell_NotifyIcon(NIM_DELETE, &m_nid); 

	return CDialog::DestroyWindow();

}
void Cwar3HelperDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

	if(nType == SIZE_MINIMIZED) 
	{
		ShowWindow(SW_HIDE); // 当最小化市，隐藏主窗口 
	} 

}

void Cwar3HelperDlg::OnStnClickedHyperlink()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Cwar3HelperDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	CString   TextFileName;
	CString allfile;
	CFileDialog opendlg(TRUE,NULL,NULL,OFN_FILEMUSTEXIST,L"exe Files (*.exe)|*.exe",NULL);

	if (opendlg.DoModal() == IDOK)
	{
		TextFileName = opendlg.GetPathName();	

		if(TextFileName.Find(_T("war3.exe")) == -1)
		{
			MessageBox(L"请选择war3.exe");
			return;
		}
	}
	else
	{ 
		MessageBox(L"请选择war3.exe");
		return ;
	}

	m_war3path.SetWindowText(TextFileName);
	m_game_exe = TextFileName;
	WritePrivateProfileString(L"war3path",L"path",TextFileName,	m_strDir+L"//war3set.ini");
}


void Cwar3HelperDlg::OnBnClickedStartgame()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(TIMER_CHECKWAR3);
	WritePrivateProfileString(_T("War3Key"),_T("Key_7"),g_num7,m_strDir+L"//war3set.ini");
	WritePrivateProfileString(_T("War3Key"),_T("Key_8"),g_num8,m_strDir+L"//war3set.ini");
	WritePrivateProfileString(_T("War3Key"),_T("Key_4"),g_num4,m_strDir+L"//war3set.ini");
	WritePrivateProfileString(_T("War3Key"),_T("Key_5"),g_num5,m_strDir+L"//war3set.ini");
	WritePrivateProfileString(_T("War3Key"),_T("Key_1"),g_num1,m_strDir+L"//war3set.ini");
	WritePrivateProfileString(_T("War3Key"),_T("Key_2"),g_num2,m_strDir+L"//war3set.ini");
	ShellExecute(NULL,L"open",m_game_exe,0,0,SW_SHOWNORMAL);
	SetTimer(TIMER_CHECKWAR3,1000,NULL);
}

void Cwar3HelperDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码

	HKEY    war3key;
	DWORD    widthlengh = 10,heightlength = 10;
	DWORD  dwtype = REG_DWORD;
    
	int screenwidth_real = GetSystemMetrics(SM_CXSCREEN);
	int screenheight_real = GetSystemMetrics(SM_CYSCREEN);

	DWORD valuewidth  =0,valueheight =0;

	if(ERROR_SUCCESS!=RegOpenKeyEx(HKEY_CURRENT_USER,L"Software\\Blizzard Entertainment\\Warcraft III\\Video",0,KEY_READ|KEY_WRITE|KEY_WRITE,&war3key))
	{
		ASSERT(0);
		return ;
	}

	if (ERROR_SUCCESS!=RegQueryValueExW(war3key,L"reswidth",0,&dwtype,(LPBYTE)&valuewidth,&widthlengh)) 
	{
		ASSERT(0);
		return;
	}

	if(ERROR_SUCCESS!=RegQueryValueEx(war3key,L"resheight",0,&dwtype,(LPBYTE)&valueheight,&heightlength))
	{
		ASSERT(0);
		return;
	}

	if(valuewidth!=screenwidth_real)
	{
		if(ERROR_SUCCESS!=RegSetValueEx(war3key,L"reswidht",0,REG_DWORD,(LPBYTE)valuewidth,widthlengh))
		{
			ASSERT(0);
			return;
		}

	}

	if(valueheight!=screenheight_real)
	{
		if(ERROR_SUCCESS!=RegSetValueEx(war3key,L"resheight",0,REG_DWORD,(LPBYTE)valueheight,heightlength))
		{
			ASSERT(0);
			return;
		}
	}
	RegCloseKey(war3key);
}

void Cwar3HelperDlg::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
}

void Cwar3HelperDlg::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void Cwar3HelperDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CAboutDlg::OnUpdate32771(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

void Cwar3HelperDlg::OnUpdateDeubug(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	
	ShellExecute(NULL, _T("open"),_T("mailto:6520874@163.com?subject=sf您好，我发现了一个bug"),NULL,NULL, SW_SHOWNORMAL);
 
}
