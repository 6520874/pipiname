//Download by http://www.NewXing.com
// MyIEDoc.h :  CQQRegDoc��Ľӿ�
//


#pragma once

class CQQRegDoc : public CDocument
{
protected: // �������л�����
	CQQRegDoc();
	DECLARE_DYNCREATE(CQQRegDoc)

// ����
public:

// ����
public:

// ��д
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	void  CQQRegDoc::SetTitle(LPCTSTR lpszTitle)
	{
		CDocument::SetTitle(_T("У԰��facebook"));
	}
// ʵ��
public:
	virtual ~CQQRegDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


