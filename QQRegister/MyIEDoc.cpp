//Download by http://www.NewXing.com
// MyIEDoc.cpp :  CMyIEDoc ���ʵ��
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


// CMyIEDoc ����/����

CMyIEDoc::CMyIEDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CMyIEDoc::~CMyIEDoc()
{
}

BOOL CMyIEDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMyIEDoc ���л�

void CMyIEDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CMyIEDoc ���

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


// CMyIEDoc ����
