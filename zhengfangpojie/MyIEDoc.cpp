

#include "stdafx.h"
#include "MyIE.h"

#include "MyIEDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyIEDoc

IMPLEMENT_DYNCREATE(CQQRegDoc, CDocument)

BEGIN_MESSAGE_MAP(CQQRegDoc, CDocument)
END_MESSAGE_MAP()


// CQQRegDoc����/����

CQQRegDoc::CQQRegDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CQQRegDoc::~CQQRegDoc()
{
}

BOOL CQQRegDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CQQRegDoc���л�

void CQQRegDoc::Serialize(CArchive& ar)
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


// CQQRegDoc���

#ifdef _DEBUG
void CQQRegDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CQQRegDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CQQRegDoc����
