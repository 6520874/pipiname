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

// ��д
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CMyIEView();
	void Changeweb(CString csXuehao)
	{
		if(m_pHTMLDocument2!=NULL)
		{
			BSTR cst1;
		m_pHTMLDocument2->get_URL(&cst1);
		CString css1 = COLE2CT(cst1);
		int n = css1.ReverseFind('/');
		CString cstr = css1.Mid(0,n+1);
		CString csNew = cstr+_T("readimagexs.aspx?xh=")+csXuehao;
		Navigate2(csNew,navNoHistory,NULL);
		}
	}

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	void fill(int n =0);
	int m_time;
	bool  m_bstartyanzhi;
public:
	afx_msg void OnFill();
	afx_msg void OnFileNew();
	int SaveBitmapToFile(HBITMAP hBitmap, LPTSTR lpFileName) /*hBitmap Ϊ�ղŵ���??ͼ��� */;
	HBITMAP CopyScreenToBitmap(LPRECT lpRect) /*lpRect ����ѡ������ */;
	UINT  static __cdecl MyControllingFunction( LPVOID pParam );
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnUpdateThunderVip(CCmdUI *pCmdUI);
	void FillWeb(CString csWebSite,CString csAccountname,CString csPasswdName);
	CString GetWebStieHtml(CString  strUrl);
private:
	CString m_csAccount;
	CString m_csPasswd;
	IHTMLDocument2 * m_pHTMLDocument2;
	bool    m_bFirst;
public:
	afx_msg void OnUpdateCallme(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStartshare(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNowweb(CCmdUI *pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnUpdateZhucema(CCmdUI *pCmdUI);
};


