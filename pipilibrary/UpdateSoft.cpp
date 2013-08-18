#include "StdAfx.h"
#include "UpdateSoft.h"
#include "ProcessDlg.h"


CUpdateSoft::CUpdateSoft(void)
{
	m_bMax = TRUE;
}

CUpdateSoft::~CUpdateSoft(void)
{
}

UINT __cdecl  CUpdateSoft::ThreadDownFile( LPVOID pParam )
{
    
   //CUpdateSoft *dlg = (CUpdateSoft *)pParam;
   //GetProcessDlg().InternetGetFile(_T("http://pipihaha.sinaapp.com/War3ToolSetup.exe"),_T("war3ToolSetup.exe"));

	return 0;
    
}
void CUpdateSoft::Apply(CString szUrl,CString szFileName)
{

  GetProcessDlg().SetUrlFileName(szUrl,szFileName);
	
}

int CUpdateSoft::DownCommonFile(CString szUrl,CString szFileName)
{ 
  DWORD dwFlags;

 	InternetGetConnectedState(&dwFlags, 0);
	CHAR strAgent[64];
	sprintf(strAgent, "Agent%ld", timeGetTime());
	HINTERNET hOpen;
	if(!(dwFlags & INTERNET_CONNECTION_PROXY))
		hOpen = InternetOpenA(strAgent, INTERNET_OPEN_TYPE_PRECONFIG_WITH_NO_AUTOPROXY, NULL, NULL, 0);
	else
		hOpen = InternetOpenA(strAgent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if(!hOpen)
	{
		//AfxMessageBox("Internet连接错误!");
		return -1;
	}

	DWORD dwSize;
	CHAR   szHead[] = "Accept: */*\r\n\r\n";
	VOID* szTemp[16384];
	HINTERNET  hConnect;
	CFile file;
 
	USES_CONVERSION;
	if ( !(hConnect = InternetOpenUrlA ( hOpen,CW2A(szUrl), szHead,
		 lstrlenA (szHead), INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_RELOAD, 0)))
	{
	  // AfxMessageBox("不能打开该URL!");
	   return -1;
	}

	if  (file.Open(szFileName,CFile::modeWrite|CFile::modeCreate)==FALSE )
	{
	   //AfxMessageBox("不能打开本地的文件!");
	  return -1;
	}

	DWORD dwByteToRead = 0;
	DWORD dwSizeOfRq = 4;
	DWORD dwBytes = 0;

    if (!HttpQueryInfo(hConnect, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, 
                  (LPVOID)&dwByteToRead, &dwSizeOfRq, NULL))
	{
		dwByteToRead = 0;
	}


	do
	{
		if (!InternetReadFile (hConnect, szTemp, 16384,  &dwSize))
		{
			//AfxMessageBox("读文件出错!");
			file.Close();
			return -1;
		}
		if (dwSize==0)
			break;
		else
			file.Write(szTemp,dwSize);
		dwBytes+=dwSize;

	}while (TRUE);
    

	file.Close();
	InternetCloseHandle(hOpen);
	return 0;
    
}

void CUpdateSoft::InitFire( CPictureHolder *myTmpPicture,int iWidth,int iHeight )
{
    
	m_iHeight = iHeight;
	m_iWeight = iWidth;
	m_bmpRenderSource.Create32BitFromPicture(myTmpPicture,iWidth,iHeight);
	m_bmpRenderTarget.Create32BitFromPicture(myTmpPicture,iWidth,iHeight);

	//创建水纹对象
	m_myWater.Create(iHeight,iWidth);
	//创建火焰对象
	m_myFire.m_iAlpha = 30;		// 渐变 30% alpha
	m_myFire.m_iHeight = iHeight;
	m_myFire.m_iWidth = iWidth;
	m_myFire.InitFire();
}

void CUpdateSoft::StartFire(CWnd *lp)
{
	if(m_bMax)
	{
		m_myFire.m_iAlpha ++;
	}
	else
	{
		m_myFire.m_iAlpha--;
	}

	if(m_myFire.m_iAlpha>=200)
	{
		m_bMax = FALSE;
	}
	if(m_myFire.m_iAlpha <= 1)
	{
		m_bMax = TRUE;
	}

	m_myWater.FlattenWater();  //浮动它，以便消失

	m_myWater.Render((DWORD*)m_bmpRenderSource.GetDIBits(),(DWORD*)m_bmpRenderTarget.GetDIBits());

	m_myFire.Render((DWORD*)m_bmpRenderTarget.GetDIBits(),m_iWeight,m_iHeight);

	CClientDC dc(lp);
	CPoint ptOrigin(15,20);
	m_bmpRenderTarget.Draw(&dc,ptOrigin);
}
