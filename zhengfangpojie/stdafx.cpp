// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// MyIE.pch ����Ԥ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"


CString GetWebStieHtml(CString  strUrl)
{
	CInternetSession mySession(NULL,0);  
	CHttpFile* myHttpFile = NULL;
	myHttpFile = (CHttpFile*)mySession.OpenURL(strUrl);//str��Ҫ�򿪵ĵ�ַ
	CString myData;
	CString  m_csHtmlContent;
	while(myHttpFile->ReadString(myData)) 
	{
		m_csHtmlContent += myData; 
	}

	return m_csHtmlContent;
}

CString  GetCurrentPath()  
{   
	CString    sPath;   
	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);   
	sPath.ReleaseBuffer    ();   
	int    nPos;   
	nPos=sPath.ReverseFind('\\');   
	sPath=sPath.Left(nPos);   
	return    sPath;   
}