// war3Helper.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "war3Helper.h"
#include "war3HelperDlg.h"

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
	HANDLE  g_hEvent= CreateEvent(NULL,FALSE,FALSE,_T("War3Tool"));
	if (g_hEvent)
	{
		if (ERROR_ALREADY_EXISTS==GetLastError())
		{
			//cout<<"only one instance is running"<<endl;
			return  -1;
		}
	}
	
	//Cwar3HelperDlg dlg;
	//CPDlg.
	m_pMainWnd =  &GetWar3Dlg();
	INT_PTR nResponse = GetWar3Dlg().DoModal();
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
