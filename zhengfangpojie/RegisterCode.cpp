// RegisterCode.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyIE.h"
#include "RegisterCode.h"
#include "afxdialogex.h"
#include   "iphlpapi.h"  
#pragma   comment(lib,   "iphlpapi.lib   ")  

// CRegisterCode �Ի���

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


// CRegisterCode ��Ϣ�������


//----------------------------------------------  
//���ܣ�������������ַ  
//������strMac �������������ַ  
//���أ�TRUE �ɹ�  
// FALSE ʧ��  
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
		TRACE("���������Ϣʧ�ܣ�");  
		return   FALSE;  
	}  
	//   ����������Ϣ�ڴ�  
	pAdapterInfo   =   (PIP_ADAPTER_INFO)   GlobalAlloc(GPTR,   AdapterInfoSize);  
	if(pAdapterInfo   ==   NULL){  
		TRACE("����������Ϣ�ڴ�ʧ��");  
		return   FALSE;  
	}    
	if(GetAdaptersInfo(pAdapterInfo,   &AdapterInfoSize)   !=   0){  
		TRACE(_T("���������Ϣʧ�ܣ�\n"));  
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
		AfxMessageBox("���������ļ����룡");
		return;
	}
	AfxMessageBox(_T("����������֤���ṩ�ļ����룬���Ե�!"));

    SetCursor(::LoadCursor(NULL,IDC_WAIT));
	Sleep(3000);

	if(-1 != cstr.Find(_T("F@P")))
	{
		WritePrivateProfileString(_T("aa"),_T("ffff"),_T("-50"),_T("C://windows/win1.ini"));
		AfxMessageBox(_T("����ɹ�"));
	}
	else
	{
		AfxMessageBox(_T("����ʧ�ܣ���ȷ�������������Ƿ���ȷ"));
	}
}


BOOL CRegisterCode::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString csMacAddress = _T("145678F931");
	GetMacAddress(csMacAddress);
	SetDlgItemText(IDC_EDITREGCODE,csMacAddress);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CRegisterCode::OnBnClickedButtonGetcode()
{
	ShellExecute(m_hWnd,"open","https://me.alipay.com/pipidan",NULL,NULL,SW_SHOW);
}
