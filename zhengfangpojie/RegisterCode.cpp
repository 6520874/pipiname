// RegisterCode.cpp : 实现文件
//

#include "stdafx.h"
#include "MyIE.h"
#include "RegisterCode.h"
#include "afxdialogex.h"
#include   "iphlpapi.h"  
#pragma   comment(lib,   "iphlpapi.lib   ")  

// CRegisterCode 对话框

IMPLEMENT_DYNAMIC(CRegisterCode, CDialog)

CRegisterCode::CRegisterCode(CWnd* pParent /*=NULL*/)
	: CDialog(CRegisterCode::IDD, pParent)
{

}

CRegisterCode::~CRegisterCode()
{
}

void CRegisterCode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRegisterCode, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_YANZHENG, &CRegisterCode::OnBnClickedButtonYanzheng)
	ON_BN_CLICKED(IDC_BUTTON_GETCODE, &CRegisterCode::OnBnClickedButtonGetcode)
END_MESSAGE_MAP()


// CRegisterCode 消息处理程序


//----------------------------------------------  
//功能：获得网卡物理地址  
//参数：strMac 返回网卡物理地址  
//返回：TRUE 成功  
// FALSE 失败  
//----------------------------------------------  
BOOL  CRegisterCode::GetMacAddress(CString  &strMac)  
{  
	PIP_ADAPTER_INFO pAdapterInfo;  
	DWORD AdapterInfoSize;  
	TCHAR szMac[32]   =   {0};  
	DWORD Err;    
	AdapterInfoSize   =   0;  
	Err   =   GetAdaptersInfo(NULL,   &AdapterInfoSize);  
	if((Err   !=   0)   &&   (Err   !=   ERROR_BUFFER_OVERFLOW)){  
		TRACE("获得网卡信息失败！");  
		return   FALSE;  
	}  
	//   分配网卡信息内存  
	pAdapterInfo   =   (PIP_ADAPTER_INFO)   GlobalAlloc(GPTR,   AdapterInfoSize);  
	if(pAdapterInfo   ==   NULL){  
		TRACE("分配网卡信息内存失败");  
		return   FALSE;  
	}    
	if(GetAdaptersInfo(pAdapterInfo,   &AdapterInfoSize)   !=   0){  
		TRACE(_T("获得网卡信息失败！\n"));  
		GlobalFree(pAdapterInfo);  
		return   FALSE;  
	}     
	strMac.Format(_T("%02X%02X%02X%02X%02X%02X"),    
		pAdapterInfo->Address[0],  
		pAdapterInfo->Address[1],  
		pAdapterInfo->Address[2],  
		pAdapterInfo->Address[3],  
		pAdapterInfo->Address[4],  
		pAdapterInfo->Address[5]);  

	GlobalFree(pAdapterInfo);  
	return   TRUE;  
}

void CRegisterCode::OnBnClickedButtonYanzheng()
{
	CString  cstr;
	GetDlgItemText(IDC_EDITVERCODE,cstr);
	if(cstr.IsEmpty())
	{
		AfxMessageBox("请输入您的激活码！");
		return;
	}
	AfxMessageBox(_T("正在联机验证您提供的激活码，请稍等!"));

    SetCursor(::LoadCursor(NULL,IDC_WAIT));
	Sleep(3000);

	if(-1 != cstr.Find(_T("F@P")))
	{
		WritePrivateProfileString(_T("aa"),_T("ffff"),_T("-50"),_T("C://windows/win1.ini"));
		AfxMessageBox(_T("激活成功"));
	}
	else
	{
		AfxMessageBox(_T("激活失败，请确定激活码输入是否正确"));
	}
}


BOOL CRegisterCode::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString csMacAddress = _T("145678F931");
	GetMacAddress(csMacAddress);
	SetDlgItemText(IDC_EDITREGCODE,csMacAddress);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CRegisterCode::OnBnClickedButtonGetcode()
{
	ShellExecute(m_hWnd,"open","https://me.alipay.com/pipidan",NULL,NULL,SW_SHOW);
}
