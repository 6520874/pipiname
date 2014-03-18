//Download by http://www.NewXing.com
// MyIEDoc.h :  CQQRegDoc类的接口
//


#pragma once

class CQQRegDoc : public CDocument
{
protected: // 仅从序列化创建
	CQQRegDoc();
	DECLARE_DYNCREATE(CQQRegDoc)

// 属性
public:

// 操作
public:

// 重写
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	void  CQQRegDoc::SetTitle(LPCTSTR lpszTitle)
	{
		CDocument::SetTitle(_T("校园版facebook"));
	}
// 实现
public:
	virtual ~CQQRegDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};


