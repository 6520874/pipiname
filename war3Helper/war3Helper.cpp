// war3Helper.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "war3Helper.h"
#include "war3HelperDlg.h"

#include "../pipilibrary/ProcessDlg.h"
#include "../pipilibrary/UpdateSoft.h"
#pragma comment(lib,"pipilibrary.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cwar3HelperApp

BEGIN_MESSAGE_MAP(Cwar3HelperApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Cwar3HelperApp ����

Cwar3HelperApp::Cwar3HelperApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� Cwar3HelperApp ����

Cwar3HelperApp theApp;


// Cwar3HelperApp ��ʼ��

BOOL Cwar3HelperApp::InitInstance()
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

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
       
	 //��exe�����и���
	 WinExec("Update.exe",SW_SHOW);
	 //��Ҫ���¾�ֹͣ������
	  //if(FindWindow())

	HANDLE  hEvent= CreateEvent(NULL,FALSE,FALSE,_T("War3Tool"));
	if (hEvent)
	{
		if (ERROR_ALREADY_EXISTS==GetLastError())
		{
			AfxMessageBox(_T("���Ѿ�������һ��War3Tool,�������̴�"));
			return  -1;
		}
	}
	
	Cwar3HelperDlg dlg;

	m_pMainWnd =  &dlg;
	INT_PTR nResponse = dlg.DoModal();
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

BOOL Cwar3HelperApp::IsUpdate()
{
	TCHAR StrCurrentDir[256] ={0};
	GetCurrentDirectory(256,StrCurrentDir);
	CString warPath(StrCurrentDir);
	TCHAR  szValue[MAX_PATH] = {0};
    GetPrivateProfileString(_T("War3version"),_T("version"),_T("130101"),szValue,MAX_PATH,warPath+_T("//war3set.ini"));
	CString csVerOld(szValue);
    CUpdateSoft cUpdateSDlg;
    cUpdateSDlg.DownCommonFile(_T("http://pipihaha.sinaapp.com/war3set.ini"),_T("war3update.ini"));
    GetPrivateProfileString(_T("War3version"),_T("version"),_T("130812"),szValue,MAX_PATH,warPath+_T("//war3update.ini"));
    CString csVerNew(szValue);

    if(csVerOld == csVerNew)
	{
		return FALSE;
	}
	else
	{
		cUpdateSDlg.Apply(_T("http://pipihaha.sinaapp.com/War3ToolSetup.exe"),_T("war3ToolSetup.exe"));
	
		return TRUE;
	}
}
