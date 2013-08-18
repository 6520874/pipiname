
// Update.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Update.h"
#include "UpdateDlg.h"
#include <afxinet.h>
#pragma  comment(lib,"Winmm.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUpdateApp

BEGIN_MESSAGE_MAP(CUpdateApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CUpdateApp ����

CUpdateApp::CUpdateApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CUpdateApp ����

CUpdateApp theApp;


// CUpdateApp ��ʼ��

BOOL CUpdateApp::IsUpdate()
{
	TCHAR StrCurrentDir[256] ={0};
	GetCurrentDirectory(256,StrCurrentDir);
	CString warPath(StrCurrentDir);
	TCHAR  szValue[MAX_PATH] = {0};
	GetPrivateProfileString(_T("War3version"),_T("version"),_T("130101"),szValue,MAX_PATH,warPath+_T("//war3set.ini"));
	CString csVerOld(szValue);

	CString csVerNew = GetWebStieHtml("http://pipihaha.sinaapp.com/war3/");

	if(csVerOld != csVerNew)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


CString   CUpdateApp::GetWebStieHtml(CString  strUrl)
{
	CInternetSession mySession(NULL,0);  
	CHttpFile* myHttpFile = NULL;
	myHttpFile = (CHttpFile*)mySession.OpenURL(strUrl);//str��Ҫ�򿪵ĵ�ַ
	CString myData;
	CString  csHtmlContent;
	while(myHttpFile->ReadString(myData)) 
	{
		csHtmlContent += myData; 
	}

	return  csHtmlContent;
}

BOOL CUpdateApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
    
	if(IsUpdate())
	{
		return -1;
	}
	CUpdateDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	//ShellExecute()
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
