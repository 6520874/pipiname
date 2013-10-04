
// kuaipingDlg.cpp : ʵ���ļ�
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


// CkuaipingDlg �Ի���

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


// CkuaipingDlg ��Ϣ�������

BOOL CkuaipingDlg::OnInitDialog()
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
 SetWindowText(_T("ƨƨ�������"));
 // TODO: �ڴ���ӿؼ�֪ͨ����������
 //---------------------------������ʾ---------------------------------//
 m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);

 m_nid.hWnd = this->m_hWnd;

 m_nid.uID = IDR_MAINFRAME;

 m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP ;

 m_nid.uCallbackMessage = WM_SHOWTASK; // �Զ������Ϣ����

 m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));

 _tcscpy(m_nid.szTip, L"ƨƨ�������"); 

 Shell_NotifyIcon(NIM_ADD, &m_nid); // �����������ͼ��

 TCITEM item;
 RECT      rc;
 item.mask = TCIF_TEXT;
 item.pszText = L"�������";
 item.cchTextMax = 100;
 m_para1.Create (IDD_FILE_DIALOG,&m_tabctr);
 m_tabctr.InsertItem(0,item.pszText);

 item.pszText = L"�ļ�����";
 m_para2.Create (IDD_SYSTEM_DIALOG,&m_tabctr);
 m_tabctr.InsertItem (1,item.pszText);

 item.pszText = L"˽�˿ռ�";
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
 // TODO: �ڴ���Ӷ���ĳ�ʼ������
 return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CkuaipingDlg::OnPaint()
 {
 //��ӱ���
 CPaintDC dc(this); 
 CBitmap   bitmap; 
 bitmap.LoadBitmap(IDB_BITMAP1);    //���IDB_BITMAP1Ҫ�Լ���� 
 CBrush   brush; 
 brush.CreatePatternBrush(&bitmap); 
 CBrush*   pOldBrush   =   dc.SelectObject(&brush); 
 dc.Rectangle(0,0,800,600);   // ��Щ�������Ե���ͼƬ���λ�úʹ�С 
 dc.SelectObject(pOldBrush); 

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
HCURSOR CkuaipingDlg::OnQueryDragIcon()
 {
 return static_cast<HCURSOR>(m_hIcon);
 }



void CkuaipingDlg::OnEnChangeEdit2()
 {
 // TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
 // ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
 // ���������� CRichEditCtrl().SetEventMask()��
 // ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

 // TODO:  �ڴ���ӿؼ�֪ͨ����������
 }

void CkuaipingDlg::OnDropFiles(HDROP hDropInfo)
 {
 // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
 // TODO: �ڴ���ӿؼ�֪ͨ����������

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
 // TODO: �ڴ������������û����洦��������

 m_CreatePasswddlg.DoModal();
 ShowWindow(SW_MINIMIZE);
 }

LRESULT CkuaipingDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
 {

 if(wParam != IDR_MAINFRAME)

  return 1;

 switch(lParam)

  {
  case WM_RBUTTONUP: // �Ҽ�����ʱ�����˵�
   {
   LPPOINT lpoint = new tagPOINT;
   ::GetCursorPos(lpoint); // �õ����λ��
   CMenu menu;
   menu.CreatePopupMenu(); // ����һ������ʽ�˵�
   menu.AppendMenu(MF_STRING, WM_DESTROY, L"�ر�ƨƨ");
   menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);
   HMENU hmenu = menu.Detach();
   menu.DestroyMenu();
   delete lpoint;
   }

   break;

  case WM_LBUTTONDBLCLK: // ˫������Ĵ���
   {
   if(m_CreatePasswddlg.IsSetPasswd())
	{   
	m_CheckPasswdDlg.Init(&m_CreatePasswddlg);
	m_CheckPasswdDlg.DoModal();

	if(m_CheckPasswdDlg.m_bPasswdSame)
	 {
	 this->ShowWindow(SW_SHOWNORMAL); // ��ʾ������
	 SetForegroundWindow();
	 }
	} 
   else
	{
	this->ShowWindow(SW_SHOWNORMAL); // ��ʾ������
	SetForegroundWindow();
	}

   }

   break;

  }

 return 0;


 }