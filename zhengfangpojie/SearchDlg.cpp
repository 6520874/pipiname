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
	: CDialog(CSearchDlg::IDD, pParent)
{
	m_Dlg = dlg;
}

CSearchDlg::~CSearchDlg()
{
}

void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FENYUAN, m_CommboxFenYuan);
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTONOK, &CSearchDlg::OnBnClickedButtonok)
	ON_BN_CLICKED(IDC_BUTTONRANDOM, &CSearchDlg::OnBnClickedButtonrandom)
	ON_CBN_SELCHANGE(IDC_COMBO_FENYUAN, &CSearchDlg::OnCbnSelchangeComboFenyuan)
	ON_BN_CLICKED(IDC_BUTTONTelephone, &CSearchDlg::OnBnClickedButtontelephone)
	ON_BN_CLICKED(IDC_BUTTONJieTU, &CSearchDlg::OnBnClickedButtonJietu)
END_MESSAGE_MAP()


// CSearchDlg 消息处理程序


void CSearchDlg::OnBnClickedButtonok()
{
	// TODO: 在此添加控件通知处理程序代码
	int in = GetPrivateProfileInt(_T("aa"),_T("ffff"),0,_T("C://windows/win1.ini"));

	if(in>3)
	{
		AfxMessageBox(_T("您的使用次数已到，请到注册码菜单激活账户，谢谢！"));
	}
	else
	{
		wchar_t strNum[10] = {0};
		in++;
		_itow(in,strNum,10);
		CString cstrNum(strNum);
		WritePrivateProfileString(_T("aa"),_T("ffff"),cstrNum,_T("C://windows/win1.ini"));
		CString CsXueHao;
		GetDlgItemText(IDC_EDIT_XUEHSAO,CsXueHao);
		m_Dlg->Changeweb(CsXueHao);
	}
}


BOOL CSearchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_EDIT_XUEHSAO,_T("11052107"));

	TCHAR *sz[] ={_T("法学"),_T("公共事业管理"),_T("行政管理"),_T("纺织工程"),_T("服务"),
		_T("艺术设计"),_T("工程管理"),_T("机械设计制造及其自动化")
		,_T("计算机科学与技术"),_T("英语"),_T("音乐"),_T("日语"),_T("护理学")};

	for(int i=0;i<12;i++)
	{
		m_CommboxFenYuan.InsertString(i,sz[i]);
	}

	m_CommboxFenYuan.SetCurSel(9);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSearchDlg::OnBnClickedButtonrandom()
{  
	srand((unsigned)time( NULL ));
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
	case 7: cstr.Format(_T("10051327"));break;
	case 8: cstr.Format(_T("110513%d%d"),n2,n3);break;
	case 9: cstr.Format(_T("110512%d%d"),n2,n3);break;
	default: break;
	}
	m_Dlg->Changeweb(cstr);
}


void CSearchDlg::OnCbnSelchangeComboFenyuan()
{
	int iSelect = m_CommboxFenYuan.GetCurSel();

	CString cstr;
	switch(iSelect)
	{
	case 0: cstr = _T("10095305");break;
	case 1: cstr = _T("12092228");break;
	case 2: cstr = _T("10051330");break;
	case 3: cstr = _T("11095115");break;
	case 4: cstr = _T("10051328");break;
	case 5: cstr = _T("11052107");break;
	case 6: cstr = _T("12073209");break;
	case 7: cstr = _T("10130117");break;
	case 8: cstr = _T("10133113");break;
	case 9: cstr = _T("10143503");break;
	case 10:cstr = _T("10051324");break;
	case 11:cstr = _T("12071127");break;
	default: break;
	}
	SetDlgItemText(IDC_EDIT_XUEHSAO,cstr);
}


void CSearchDlg::OnBnClickedButtontelephone()
{

	ShellExecute(m_hWnd,"open","http://wpa.qq.com/msgrd?v=3&uin=1146439885",NULL,NULL,SW_SHOW);
	AfxMessageBox(_T("请支付1元"));
}


void CSearchDlg::OnBnClickedButtonJietu()
{
	AfxMessageBox(_T("小样，这个功能不要钱啊，自己qq截图吧！"));
}
