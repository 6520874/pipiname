// SearchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyIE.h"
#include "SearchDlg.h"
#include "afxdialogex.h"
#

// CSearchDlg 对话框

IMPLEMENT_DYNAMIC(CSearchDlg, CDialogEx)

CSearchDlg::CSearchDlg(CMyIEView *dlg,CWnd* pParent /*=NULL*/)
	: CDialogEx(CSearchDlg::IDD, pParent)
{
	m_Dlg = dlg;
}

CSearchDlg::~CSearchDlg()
{
}

void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FENYUAN, m_CommboxFenYuan);
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTONOK, &CSearchDlg::OnBnClickedButtonok)
	ON_BN_CLICKED(IDC_BUTTONRANDOM, &CSearchDlg::OnBnClickedButtonrandom)
END_MESSAGE_MAP()


// CSearchDlg 消息处理程序


void CSearchDlg::OnBnClickedButtonok()
{
	// TODO: 在此添加控件通知处理程序代码
	int n = GetPrivateProfileInt(_T("aa"),_T("ffff"),0,_T("C://windows/win1.ini"));

	if(n>3)
	{
		AfxMessageBox(_T("您3次使用次数已到，请到注册码菜单激活账户，谢谢！"));
	}
	else
	{
		wchar_t strNum[10] = {0};
		n++;
		_itow(n,strNum,10);
		CString cstrNum(strNum);
		WritePrivateProfileString(_T("aa"),_T("ffff"),cstrNum,_T("C://windows/win1.ini"));
		CString CsXueHao;
		GetDlgItemText(IDC_EDIT_XUEHSAO,CsXueHao);
		m_Dlg->Changeweb(CsXueHao);
	}
}


BOOL CSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemText(IDC_EDIT_XUEHSAO,_T("11052107"));

	TCHAR *sz[] ={_T("法学"),_T("公共事业管理"),_T("行政管理"),_T("纺织工程"),_T("服务"),
		_T("艺术设计"),_T("工程管理"),_T("机械设计制造及其自动化")
		,_T("计算机科学与技术"),_T("英语"),_T("音乐"),_T("日语"),_T("护理学")};


	for(int i=0;i<10;i++)
	m_CommboxFenYuan.InsertString(i,sz[i]);
	m_CommboxFenYuan.SetCurSel(9);
  
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSearchDlg::OnBnClickedButtonrandom()
{  
	srand( (unsigned)time( NULL ) );
	 int n  = rand()%10;
	 int n1 = rand()%10;
	 int n2 = rand()%10;
	 int n3=   rand()%10;

	 CString cstr;

	 switch(n)
	 {
	 case 0: cstr = _T("12092227");break;
	 case 1: cstr = _T("12092228");break;
	 case 2: cstr = _T("10051330");break;
	 case 3: cstr = _T("11095115");break;
	 case 4: cstr = _T("10051328");break;
	 case 5: cstr = _T("11052107");break;
	 case 6: cstr = _T("12073209");break;
	 case 7: cstr.Format(_T("1209%d%d%d%d"),n,n1,n2,n3);break;
	 case 8: cstr.Format(_T("1105%d%d%d%d"),n,n1,n2,n3);break;
     case 9: cstr.Format(_T("1105%d%d%d%d"),n,n1,n2,n3);break;
	 }
	 	m_Dlg->Changeweb(cstr);
}
