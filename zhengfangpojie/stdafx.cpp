// stdafx.cpp : 只包括标准包含文件的源文件
// MyIE.pch 将是预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"


CString GetWebStieHtml(CString  strUrl)
{
	CInternetSession mySession(NULL,0);  
	CHttpFile* myHttpFile = NULL;
	myHttpFile = (CHttpFile*)mySession.OpenURL(strUrl);//str是要打开的地址
	CString myData;
	CString  m_csHtmlContent;
	while(myHttpFile->ReadString(myData)) 
	{
		m_csHtmlContent += myData; 
	}

	return m_csHtmlContent;
}