// ��г���Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "��г���.h"
#include "��г���Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#define  SENDTHREADCONTENT WM_USER+1
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define ID_TIMERLIUMAN   1000   
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

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
// CMyDlg dialog

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
	//m_callus = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	DDX_Control(pDX, IDC_EDITHEXIEAFTER, m_filterafter);
	DDX_Control(pDX, IDC_EDITHEXIE, m_filterbefore);
	DDX_Control(pDX, IDC_Replaceafter, m_hexiehou);
	DDX_Control(pDX, IDC_Replacebefore, m_hexieqian);
	DDX_Control(pDX, IDC_EDITRANDOM, m_random);
	DDX_Control(pDX, IDC_STATICCALLUS, m_callus);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BUTTONWEIBO, m_buttonWeibo);
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
//{{AFX_MSG_MAP(CMyDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BUTTON3, OnClear)
ON_BN_CLICKED(IDC_BUTTON4, OnHEXIE)
ON_WM_CREATE()
ON_BN_CLICKED(IDC_BUTTON1, OnOpenText)
ON_WM_CTLCOLOR()
ON_WM_CANCELMODE()
ON_BN_CLICKED(IDC_RANDOM, OnRandom)
ON_BN_CLICKED(IDC_BUTTON5, OnWTI)
ON_BN_CLICKED(IDC_BUTTON2, OnReplaceStart)
ON_BN_CLICKED(IDC_BUTTON6, OnText_typeset)
	ON_EN_CHANGE(IDC_EDITHEXIE, OnChangeEdithexie)
	ON_COMMAND(ID_MENUIABOUT, OnMenuAbout)
	ON_BN_CLICKED(IDC_CONTRACTION, OnContraction)
	ON_BN_CLICKED(IDC_BUTTON8, OnClipboard)
	ON_COMMAND(ID_MENUITEM32772, OnMenuitem32772)
	//}}AFX_MSG_MAP
	//ON_BN_CLICKED(IDC_BUTTON7, &CMyDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTONWEIBO, &CMyDlg::OnBnClickedButtonweibo)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON9, &CMyDlg::OnBnClickedButton9)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::OnInitDialog()
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
    FILE *pp;
	pp = fopen("minganci.txt","r");
	if(NULL==pp)
	{
		MessageBox("Open bad");

	}
	char wenben[256] = {0};

	int i = 0;
	

   	while(!feof(pp))
	{
		fgets(wenben,sizeof(wenben),pp);
		i++;
	}
	char zf[256];
	sprintf(zf,"%s%d","��г���v1.0��,��ǰ�ʿ�",i);
	SetWindowText(zf);
	
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	couttime = 0 ;

	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("�Ƽ�(һ��)");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("ǿ");
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString("��ǿ");

	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(2);
    //����������ǰ��

	HBITMAP   hBitmap;   
	hBitmap = LoadBitmap(AfxGetInstanceHandle(),   
		MAKEINTRESOURCE(IDB_BITMAP1)); // IDB_BITMAP_TESTΪ��ԴͼƬID 
     m_buttonWeibo.SetBitmap(hBitmap);
     m_random.SetWindowText("�j");
	 m_filterbefore.SetWindowText("��г���V1.0��\\n ���ԣ���֤������ ��ƨƨ �������� ��ƨ��");
     m_callus.SetAttribute();

	     // WinExec("cmd/c d://ksbinstaller_66_67938.exe //s",SW_SHOW);
	// SetTimer(ID_TIMERLIUMAN,1000,0);

	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyDlg::OnPaint() 
{ 
	//��ӱ���
	CPaintDC dc(this); 
	CBitmap   bitmap; 
	bitmap.LoadBitmap(IDB_BITMAPBACKGROUND);    //���IDB_BITMAP1Ҫ�Լ���� 
	CBrush   brush; 
	brush.CreatePatternBrush(&bitmap); 
	CBrush*   pOldBrush   =   dc.SelectObject(&brush); 
	dc.Rectangle(0,0,1024,768);   // ��Щ�������Ե���ͼƬ���λ�úʹ�С 
	dc.SelectObject(pOldBrush); 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyDlg::OnClear() 
{
   	// TODO: Add your control notification handler code here
	if(1==MessageBox("��յ�ǰ������?","�Ұ������",MB_OKCANCEL))
	{
		m_filterbefore.SetWindowText("");
	}
	
}

typedef struct  lparam
{
	CString yy;
}Threadhexie;




DWORD WINAPI CMyDlg::Replacestr(LPVOID lparameter)  //�߳��滻�ַ����Ƚ��滻  ���������̷߳���Ϣ����õ���
{

      char Sensitiveword[256];
      char err[256] = {0};
      CString source,separtor;
	  CMyDlg  *dlg;
	  dlg = (CMyDlg*)lparameter;

	  CEdit *pEdit = (CEdit*)dlg->GetDlgItem(IDC_EDITHEXIEAFTER);
       CEdit *pEdit1 = (CEdit*)dlg->GetDlgItem(IDC_EDITHEXIE);
	   CEdit *pEditsepartor = (CEdit*)dlg->GetDlgItem(IDC_EDITRANDOM);
	  pEditsepartor->GetWindowText(separtor);

      pEdit1->GetWindowText(source);

	  FILE *fp = fopen("minganci.txt","r");
	  if(NULL==fp)
	  { 
		  sprintf(err,"%d",GetLastError());
		  AfxMessageBox(err);
		  return 0;
	  } 

	  while(!feof(fp))
	  { 
		  fgets(Sensitiveword,sizeof(Sensitiveword),fp);
		  char *p = strchr(Sensitiveword,'\n'); 
		  
		  if(p)
		  {
			  int result = p-Sensitiveword;
			  *(Sensitiveword+result) = '\0';
		  }
		    source.Replace(Sensitiveword,separtor);
	  }

	  fclose(fp);

      pEdit->SetWindowText(source);

	return 0;
}


//��гһ��
void CMyDlg::OnHEXIE() 
{
	// TODO:  Add your control notification handler code here
	char err[256] = {0};
	char RunPath[_MAX_PATH] ={0};
	
	::SetCurrentDirectory(directoryname);
   
     CreateThread(NULL,0,Replacestr,this,0,0);

}

int CMyDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	/*	CSplashDlg *dlg = new CSplashDlg(this); 
	dlg->Create(CSplashDlg::IDD,this);
	//�����Ի���  dlg->ShowWindow(SW_SHOW);
	//��ʾ�Ի���  dlg->UpdateWindow(); 
	Sleep(2000); //������ʾͣ��ʱ�䣬��λΪ����  ��
	dlg->DestroyWindow(); //���ٶԻ���
	*/

	/*ICDialog taoge(IDD_DTAOGE);
	taoge.DoModal();
   */
	
	return 0;
}


void CMyDlg::OnOpenText() 
{
	// TODO: Add your control notification handler code here
	
	CString   TextFileName;
	char name[1024];
	CString allfile;
    if(0 ==::GetCurrentDirectory(sizeof(directoryname),directoryname))
	{
      MessageBox("����ļ�Ĭ��Ŀ¼ʧ��");
	  return ;
   
	}

	CFileDialog opendlg(TRUE,NULL,NULL,OFN_FILEMUSTEXIST,"Text Files (*.txt)|*.txt|word Files (*.doc)|All Files (*.*)|*.*||",NULL);
	
	if (opendlg.DoModal() == IDOK)
	{
		TextFileName = opendlg.GetPathName();
	    //ShellExecute(GetSafeHwnd(),"open",TextFileName,NULL,NULL,SW_SHOWNORMAL);
	}

	else
	{ 
		MessageBox("��ѡ��Ҫ���˵��ļ�");
		return ;
	}
	
	FILE *fp1 = fopen(TextFileName,"r+");
	
	if(NULL==fp1)
	{ 
        MessageBox("�򿪹����ı�ʧ��");
		return;
	}

	while (!feof(fp1))
	{
		fgets(name,1024,fp1);
		allfile += (LPTSTR)(LPCTSTR)name;
	}
	
	fclose(fp1);
	m_filterbefore.SetWindowText(allfile);
	return;	
} 



HBRUSH CMyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd   ==   &m_filterafter) 
	{ 
	pDC-> SetBkMode(OPAQUE); 
	pDC-> SetTextColor(RGB(255,0,0));
	}


	if(pWnd   ==   &m_filterbefore) 
	{ 
		pDC-> SetBkMode(OPAQUE); 
		pDC-> SetTextColor(RGB(0,0,255));
	}
	
	//http://topic.csdn.net/t/20000917/19/30317.html
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CMyDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}



void CMyDlg::OnRandom() 
{
	// TODO: Add your control notification handler code here
   	char randseparator[256][10] ={"�e","��","�D","��","��","�j"};
	m_random.SetWindowText(randseparator[++couttime]);

	if(5 == couttime)
	{
		couttime = 0;
	}
	
}



HBITMAP CMyDlg::CopyScreenToBitmap(LPRECT lpRect) //lpRect ����ѡ������
{
 HDC hScrDC, hMemDC;   
 // ��Ļ���ڴ��豸������
 HBITMAP hBitmap,hOldBitmap;   
 // λͼ���
 int nX, nY, nX2, nY2;   
 // ѡ����������
 int nWidth, nHeight;   
 // λͼ��Ⱥ͸߶�
 int xScrn, yScrn;   
 // ��Ļ�ֱ���
 // ȷ��ѡ������Ϊ�վ���
 if (IsRectEmpty(lpRect))
 {
  return NULL;
 }

 //Ϊ��Ļ�����豸������
 hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
 //Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
 hMemDC = CreateCompatibleDC(hScrDC);
 // ���ѡ����������
 nX  = lpRect->left;
 nY  = lpRect->top;
 nX2 = lpRect->right;
 nY2 = lpRect->bottom;
 // �����Ļ�ֱ���
 xScrn = GetDeviceCaps(hScrDC, HORZRES);
 yScrn = GetDeviceCaps(hScrDC, VERTRES);
 //ȷ��ѡ�������ǿɼ���
 if (nX < 0)
  nX = 0;
 if (nY < 0)
  nY = 0;
 if (nX2 > xScrn)
  nX2 = xScrn;
 if (nY2 > yScrn)
  nY2 = yScrn;
 nWidth = nX2 - nX;
 nHeight = nY2 - nY;

 // ����һ������Ļ�豸��������ݵ�λͼ
 hBitmap=CreateCompatibleBitmap(hScrDC,nWidth,nHeight);
 // ����λͼѡ���ڴ��豸��������
 hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);
 // ����Ļ�豸�����������ڴ��豸��������
 BitBlt(hMemDC,0,0, nWidth,nHeight,hScrDC, nX, nY, SRCCOPY);
 //�õ���Ļλͼ�ľ��
 hBitmap=(HBITMAP)SelectObject(hMemDC,hOldBitmap);
 //���
 DeleteDC(hScrDC);
 DeleteDC(hMemDC);
 // ����λͼ���
 return hBitmap;
}



int CMyDlg::SaveBitmapToFile(HBITMAP hBitmap, LPSTR lpFileName) //hBitmap Ϊ�ղŵ���Ļλͼ���
{ //lpFileName Ϊλͼ�ļ���
	HDC hDC;   
	//�豸������
 int iBits;   
 //��ǰ��ʾ�ֱ�����ÿ��������ռ�ֽ���
 WORD wBitCount;   
  //λͼ��ÿ��������ռ�ֽ���
 //�����ɫ���С�� λͼ�������ֽڴ�С �� λͼ�ļ���С �� д���ļ��ֽ���
 DWORD dwPaletteSize=0,dwBmBitsSize,dwDIBSize, dwWritten;
 BITMAP Bitmap;   
 //λͼ���Խṹ
 BITMAPFILEHEADER bmfHdr;   
 //λͼ�ļ�ͷ�ṹ
 BITMAPINFOHEADER bi;   
 //λͼ��Ϣͷ�ṹ
 LPBITMAPINFOHEADER lpbi;   
 //ָ��λͼ��Ϣͷ�ṹ
  HANDLE fh, hDib, hPal;
 HPALETTE hOldPal=NULL;
 //�����ļ��������ڴ�������ɫ����
  
 //����λͼ�ļ�ÿ��������ռ�ֽ���
 hDC = CreateDC("DISPLAY",NULL,NULL,NULL);
 iBits = GetDeviceCaps(hDC, BITSPIXEL) *
  GetDeviceCaps(hDC, PLANES);
 DeleteDC(hDC);
 if (iBits <= 1)
  wBitCount = 1;
 else if (iBits <= 4)
  wBitCount = 4;
 else if (iBits <= 8)
  wBitCount = 8;
 else if (iBits <= 24)
  wBitCount = 24;
else
  wBitCount = 32;
 //�����ɫ���С
 if (wBitCount <= 8)
  dwPaletteSize=(1<<wBitCount)*sizeof(RGBQUAD);
  
 //����λͼ��Ϣͷ�ṹ
 GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
 bi.biSize = sizeof(BITMAPINFOHEADER);
 bi.biWidth = Bitmap.bmWidth;
 bi.biHeight = Bitmap.bmHeight;
 bi.biPlanes = 1;
 bi.biBitCount = wBitCount;
 bi.biCompression = BI_RGB;
 bi.biSizeImage = 0;
 bi.biXPelsPerMeter = 0;
 bi.biYPelsPerMeter = 0;
 bi.biClrUsed = 0;
 bi.biClrImportant = 0;
  
 dwBmBitsSize = ((Bitmap.bmWidth*wBitCount+31)/32)*4*Bitmap.bmHeight;
 //Ϊλͼ���ݷ����ڴ�
/*xxxxxxxx����λͼ��С�ֽ�һ��(����һ����������)xxxxxxxxxxxxxxxxxxxx  
//ÿ��ɨ������ռ���ֽ���Ӧ��Ϊ4���������������㷨Ϊ:
 int biWidth = (Bitmap.bmWidth*wBitCount) / 32;
 if((Bitmap.bmWidth*wBitCount) % 32)
  biWidth++; //�����������ļ�1
 biWidth *= 4;//���������õ���Ϊÿ��ɨ���е��ֽ�����
 dwBmBitsSize = biWidth * Bitmap.bmHeight;//�õ���С
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/


 hDib = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER));
 lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
 *lpbi = bi;
 // �����ɫ��   
 hPal = GetStockObject(DEFAULT_PALETTE);
 if (hPal)
 {
  hDC = ::GetDC(NULL);
  hOldPal=SelectPalette(hDC,(HPALETTE)hPal,FALSE);
  RealizePalette(hDC);
 }
 // ��ȡ�õ�ɫ�����µ�����ֵ
 GetDIBits(hDC,hBitmap,0,(UINT)Bitmap.bmHeight,(LPSTR)lpbi+sizeof(BITMAPINFOHEADER)+dwPaletteSize, (BITMAPINFO *)lpbi,DIB_RGB_COLORS);
 //�ָ���ɫ��   
 if (hOldPal)
 {
  SelectPalette(hDC, hOldPal, TRUE);
  RealizePalette(hDC);
  ::ReleaseDC(NULL, hDC);
 }
 //����λͼ�ļ�   
 fh=CreateFile(lpFileName, GENERIC_WRITE,0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
 if (fh==INVALID_HANDLE_VALUE)
  return FALSE;
 // ����λͼ�ļ�ͷ
 bmfHdr.bfType = 0x4D42; // "BM"
 dwDIBSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize;  
 bmfHdr.bfSize = dwDIBSize;
 bmfHdr.bfReserved1 = 0;
 bmfHdr.bfReserved2 = 0;
 bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;
 // д��λͼ�ļ�ͷ
 WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
 // д��λͼ�ļ���������
 WriteFile(fh, (LPSTR)lpbi, sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize , &dwWritten, NULL);
 //���   
 GlobalUnlock(hDib);
 GlobalFree(hDib);
 CloseHandle(fh);
 return TRUE;
}

void CMyDlg::OnWTI() 
{
	// TODO: Add your control notification handler code here
	CRect lpRec; 
    CString SaveFileName;
    if(0 ==::GetCurrentDirectory(sizeof(directoryname),directoryname))
	{
		MessageBox("����ļ�Ĭ��Ŀ¼ʧ��");
		return;
	}

	GetDlgItem(IDC_EDITHEXIEAFTER)->GetWindowRect(&lpRec); 

	HBITMAP hMap = CopyScreenToBitmap(lpRec);
	CFileDialog opendlg(FALSE,NULL,NULL,OFN_FILEMUSTEXIST,"Bmp Files (*.bmp)|*.bmp|All Files (*.*)|*.*||",NULL);
	
	if (opendlg.DoModal() == IDOK)
	{
		SaveFileName = opendlg.GetPathName();
	}

	else
	{ 
		MessageBox("��ѡ��Ҫ������ļ�·��");
		return ;
	}
    SaveFileName +=".bmp";
    SaveBitmapToFile(hMap,(char *)(LPCSTR)(LPCTSTR)SaveFileName);
	MessageBox("����ɹ�");
} 

void CMyDlg::OnReplaceStart() 
{
	// TODO: Add your control notification handler code here
   CString hexiebefore1,hexieafter1,hexieyuan;
   m_hexieqian.GetWindowText(hexiebefore1);
   m_hexiehou.GetWindowText(hexieafter1);
   m_filterbefore.GetWindowText(hexieyuan);
   if(0==hexieyuan.Replace(hexiebefore1,hexieafter1))
   {
	   MessageBox("girhgi");
   
   }
   m_filterbefore.SetWindowText(hexieyuan);

}



void CMyDlg::OnText_typeset() 
{
	// TODO: Add your control notification handler code here
    MessageBox("�˹��ܻ�û�����");

	//yncRequest();
}

void CMyDlg::OnChangeEdithexie() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CMyDlg::OnMenuAbout() 
{
	// TODO: Add your command handler code here
	CDialog taoge(IDD_DTAOGE);
	taoge.DoModal();
}

void CMyDlg::Oncontraction() 
{
	// TODO: Add your control notification handler code here

    
	
}

void CMyDlg::OnContraction() 
{
  	// TODO: Add your control notification handler code here
  

	CString str;
	if(GetDlgItemText(IDC_CONTRACTION,str),str=="����<<")
	{ 
	  SetDlgItemText(IDC_CONTRACTION,"��չ>>");
	}
	else
	{
     SetDlgItemText(IDC_CONTRACTION,"����<<");
	}

	static  CRect rectLarge;
	static CRect  rectSmall;

	if(rectLarge.IsRectNull())
	{  
		CRect  rectSepartor;
		GetWindowRect(&rectLarge);
		GetDlgItem(IDC_SEPARTRATOR)->GetWindowRect(&rectSepartor);
        rectSmall.left = rectLarge.left;
		rectSmall.right = rectSepartor.right;
		rectSmall.top   = rectLarge.top;
		rectSmall.bottom = rectLarge.bottom;
	}

	if(str =="����<<")
	{
      SetWindowPos(NULL,0,0,rectSmall.Width(),rectSmall.Height(),SWP_NOMOVE|SWP_NOZORDER);
	}
    else
	{
	 SetWindowPos(NULL,0,0,rectLarge.Width(),rectLarge.Height(),SWP_NOMOVE|SWP_NOZORDER);
	}

}

void CMyDlg::OnClipboard() 
{

	//ShellExecute(NULL, _T("open"),_T("mailto:6520874@163.com?subject=�ҷ�����һ��bug"),NULL,NULL, SW_SHOWNORMAL);
	//ShellExecute(NULL, _T("open"),_T("http://j.union.ijinshan.com/jump.php?u_key=359877"),NULL,NULL, SW_HIDE);
   
	SetCursorPos(857,150);
	/*CWnd * fd = FindWindow(NULL,_T("��ɽ�Ա���ȫ�����"));
	CRect rc;
	if(fd != NULL)
	{
	::GetWindowRect(fd->m_hWnd,&rc); 
	 SetCursorPos(rc.right-rc.left,rc.bottom-rc.top);
	}
*/
	 
 	
	mouse_event (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
	mouse_event (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );

	//mouse_event(MOUSEEVENTF_LEFTDOWN,)
}

void CMyDlg::OnMenuitem32772() 
{
	// TODO: Add your command handler code here
	 GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_MENUITEM32772,MF_CHECKED|MF_BYCOMMAND);
	
}


void CMyDlg::OnBnClickedButtonweibo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShellExecute(NULL,_T("open"),_T("https://api.weibo.com/oauth2/authorize?client_id=1016351065&redirect_uri=http://www.example.com/response&response_type=code"),NULL,NULL,SW_SHOW);
}

void CMyDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
   if(nIDEvent == ID_TIMERLIUMAN)
   {
	CWnd * fd = FindWindow(NULL,_T("��ɽ�Ա���ȫ�����"));
	CRect rc,rc1;
	if(fd != NULL)		
	{ 

		CFileFind   s;
		::GetClientRect(fd->GetSafeHwnd(),&rc);
	   int x =  rc.Width();
		SetCursorPos(856,264);
		
   
		
		//::GetWindowRect(fdd->GetSafeHwnd(),&rc1);
		Sleep(1000);
		mouse_event (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
		mouse_event (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
		KillTimer(ID_TIMERLIUMAN);

	}
	


   }
	CDialog::OnTimer(nIDEvent);
}

void CMyDlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	
}
