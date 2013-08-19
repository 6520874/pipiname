//Download by http://www.NewXing.com
// MyIEDoc.cpp :  CMyIEDoc 类的实现
//

#include "stdafx.h"
#include "MyIE.h"

#include "MyIEDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyIEDoc

IMPLEMENT_DYNCREATE(CMyIEDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyIEDoc, CDocument)
END_MESSAGE_MAP()


// CMyIEDoc 构造/析构

CMyIEDoc::CMyIEDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMyIEDoc::~CMyIEDoc()
{
}

BOOL CMyIEDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMyIEDoc 序列化

void CMyIEDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CMyIEDoc 诊断

#ifdef _DEBUG
void CMyIEDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyIEDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyIEDoc 命令
