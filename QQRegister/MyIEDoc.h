//Download by http://www.NewXing.com
// MyIEDoc.h :  CMyIEDoc ��Ľӿ�
//


#pragma once

class CMyIEDoc : public CDocument
{
protected: // �������л�����
	CMyIEDoc();
	DECLARE_DYNCREATE(CMyIEDoc)

// ����
public:

// ����
public:

// ��д
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CMyIEDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


