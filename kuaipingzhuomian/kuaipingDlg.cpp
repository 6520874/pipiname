
// kuaipingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "kuaiping.h"
#include "kuaipingDlg.h"
#include "PasswdDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define WM_SHOWTASK  WM_USER+10
NOTIFYICONDATA m_nid;
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


// CkuaipingDlg 对话框

CkuaipingDlg::CkuaipingDlg(CWnd* pParent /*=NULL*/)
: CDialog(CkuaipingDlg::IDD, pParent)
 {
 m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
 }

void CkuaipingDlg::DoDataExchange(CDataExchange* pDX)
 {
 CDialog::DoDataExchange(pDX);
 DDX_Control(pDX, IDC_TAB1, m_tabctr);
 }

BEGIN_MESSAGE_MAP(CkuaipingDlg, CDialog)
 ON_WM_SYSCOMMAND()
 ON_WM_PAINT()
 ON_WM_QUERYDRAGICON()
 //}}AFX_MSG_MAP
 ON_EN_CHANGE(IDC_EDIT2, &CkuaipingDlg::OnEnChangeEdit2)
 ON_WM_DROPFILES()
 ON_MESSAGE(WM_SHOWTASK,OnShowTask)
 ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CkuaipingDlg::OnTcnSelchangingTab1)
 ON_UPDATE_COMMAND_UI(ID_PASSWD, &CkuaipingDlg::OnUpdatePasswd)
END_MESSAGE_MAP()


// CkuaipingDlg 消息处理程序

BOOL CkuaipingDlg::OnInitDialog()
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
 SetWindowText(_T("屁屁桌面管理"));
 // TODO: 在此添加控件通知处理程序代码
 //---------------------------托盘显示---------------------------------//
 m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);

 m_nid.hWnd = this->m_hWnd;

 m_nid.uID = IDR_MAINFRAME;

 m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP ;

 m_nid.uCallbackMessage = WM_SHOWTASK; // 自定义的消息名称

 m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));

 _tcscpy(m_nid.szTip, L"屁屁桌面管理"); 

 Shell_NotifyIcon(NIM_ADD, &m_nid); // 在托盘区添加图标

 TCITEM item;
 RECT      rc;
 item.mask = TCIF_TEXT;
 item.pszText = L"常用软件";
 item.cchTextMax = 100;
 m_para1.Create (IDD_FILE_DIALOG,&m_tabctr);
 m_tabctr.InsertItem(0,item.pszText);

 item.pszText = L"文件管理";
 m_para2.Create (IDD_SYSTEM_DIALOG,&m_tabctr);
 m_tabctr.InsertItem (1,item.pszText);

 item.pszText = L"私人空间";
 m_para3.Create (IDD_HIDE_DIALOG,&m_tabctr);
 m_tabctr.InsertItem (2,item.pszText);
 GetClientRect(&rc);
 rc.top += 25;
 rc.left += 1;
 rc.right -=1;
 rc.bottom -=2;
 m_para1.SetWindowPos (NULL,10,30,rc.right-20,rc.bottom-40,SWP_SHOWWINDOW);


 //m_para2.SetWindowPos(NULL,rc.left,rc.top,rc.right,rc.bottom,SWP_HIDEWINDOW);
 //m_para3.SetWindowPos(NULL,rc.left,rc.top,rc.right,rc.bottom,SWP_HIDEWINDOW);
 // TODO: 在此添加额外的初始化代码
 return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
 }


void CkuaipingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CkuaipingDlg::OnPaint()
 {
 //添加背景
 CPaintDC dc(this); 
 CBitmap   bitmap; 
 bitmap.LoadBitmap(IDB_BITMAP1);    //这个IDB_BITMAP1要自己添加 
 CBrush   brush; 
 brush.CreatePatternBrush(&bitmap); 
 CBrush*   pOldBrush   =   dc.SelectObject(&brush); 
 dc.Rectangle(0,0,800,600);   // 这些参数可以调整图片添加位置和大小 
 dc.SelectObject(pOldBrush); 

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
HCURSOR CkuaipingDlg::OnQueryDragIcon()
 {
 return static_cast<HCURSOR>(m_hIcon);
 }



void CkuaipingDlg::OnEnChangeEdit2()
 {
 // TODO:  如果该控件是 RICHEDIT 控件，它将不
 // 发送此通知，除非重写 CDialog::OnInitDialog()
 // 函数并调用 CRichEditCtrl().SetEventMask()，
 // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

 // TODO:  在此添加控件通知处理程序代码
 }

void CkuaipingDlg::OnDropFiles(HDROP hDropInfo)
 {
 // TODO: 在此添加消息处理程序代码和/或调用默认值
 int fcount = ::DragQueryFile(hDropInfo,-1,NULL,NULL);
 for(int i=0; i<fcount; i++)	
  {
  int fsize = ::DragQueryFile(hDropInfo,i,NULL,NULL);	
  HANDLE hHeap = ::GetProcessHeap();
  TCHAR *fname = (TCHAR *)::HeapAlloc(hHeap,HEAP_ZERO_MEMORY,fsize++);
  ::DragQueryFile(hDropInfo,i,fname,fsize);
  this->SetWindowText(fname);
  ::HeapFree(hDropInfo,HEAP_ZERO_MEMORY,fname);	
  }	

 CDialog::OnDropFiles(hDropInfo);
 }

void CkuaipingDlg::OnTcnSelchangingTab1(NMHDR *pNMHDR, LRESULT *pResult)
 {
 // TODO: 在此添加控件通知处理程序代码

 CRect r;
 m_tabctr.GetClientRect (&r);

 switch(m_tabctr.GetCurSel())
  {
  case 0:
   m_para1.SetWindowPos (NULL,10,30,r.right-20,r.bottom-40,SWP_SHOWWINDOW);
   m_para2.SetWindowPos (NULL,10,30,r.right-20,r.bottom-40,SWP_HIDEWINDOW);
   m_para3.SetWindowPos(NULL,10,30,r.right-20,r.bottom-40,SWP_HIDEWINDOW);
   break;

  case 1:
   m_para1.SetWindowPos (NULL,10,30,r.right-20,r.bottom -40,SWP_HIDEWINDOW);
   m_para2.SetWindowPos (NULL,10,30,r.right-20,r.bottom -40,SWP_SHOWWINDOW);
   m_para3.SetWindowPos(NULL,10,30,r.right-20,r.bottom -40,SWP_HIDEWINDOW);

   break;
  case 2:
   m_para1.SetWindowPos (NULL,10,30,r.right-20,r.bottom -40,SWP_HIDEWINDOW);
   m_para2.SetWindowPos (NULL,10,30,r.right-20,r.bottom -40,SWP_HIDEWINDOW);
   m_para3.SetWindowPos(NULL,10,30,r.right-20,r.bottom-40,SWP_SHOWWINDOW);
   break;
  }

 *pResult = 0;
 }

void CkuaipingDlg::OnUpdatePasswd(CCmdUI *pCmdUI)
 {
 // TODO: 在此添加命令更新用户界面处理程序代码

 m_CreatePasswddlg.DoModal();
 ShowWindow(SW_MINIMIZE);
 }

LRESULT CkuaipingDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
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
   menu.AppendMenu(MF_STRING, WM_DESTROY, L"关闭屁屁");
   menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);
   HMENU hmenu = menu.Detach();
   menu.DestroyMenu();
   delete lpoint;
   }

   break;

  case WM_LBUTTONDBLCLK: // 双击左键的处理
   {
   if(m_CreatePasswddlg.IsSetPasswd())
	{   
	m_CheckPasswdDlg.Init(&m_CreatePasswddlg);
	m_CheckPasswdDlg.DoModal();

	if(m_CheckPasswdDlg.m_bPasswdSame)
	 {
	 this->ShowWindow(SW_SHOWNORMAL); // 显示主窗口
	 SetForegroundWindow();
	 }
	} 
   else
	{
	this->ShowWindow(SW_SHOWNORMAL); // 显示主窗口
	SetForegroundWindow();
	}

   }

   break;

  }

 return 0;


 }