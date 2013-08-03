// war3Helper.cpp : 定义应用程序的类行为。
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


// Cwar3HelperApp 构造

Cwar3HelperApp::Cwar3HelperApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 Cwar3HelperApp 对象

Cwar3HelperApp theApp;


// Cwar3HelperApp 初始化

BOOL Cwar3HelperApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
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
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}
