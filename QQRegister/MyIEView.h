//Download by http://www.NewXing.com
// MyIEView.h : CMyIEView ��Ľӿ�
//


#pragma once


class CMyIEView : public CHtmlView
{
protected: // �������л�����
	CMyIEView();
	DECLARE_DYNCREATE(CMyIEView)

// ����
public:
	CQQRegDoc* GetDocument() const;

// ����
public:

// ��д
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CMyIEView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	void fill();
	int time;
public:
	afx_msg void OnFill();
	afx_msg void OnFileNew();
	int SaveBitmapToFile(HBITMAP hBitmap, LPTSTR lpFileName) /*hBitmap Ϊ�ղŵ���??ͼ��� */;
	HBITMAP CopyScreenToBitmap(LPRECT lpRect) /*lpRect ����ѡ������ */;
};

#ifndef _DEBUG  // MyIEView.cpp �ĵ��԰汾
inline CQQRegDoc* CMyIEView::GetDocument() const
   { return reinterpret_cast<CQQRegDoc*>(m_pDocument); }
#endif

