//Download by http://www.NewXing.com
// MyIEView.h : CMyIEView 类的接口
//


#pragma once


class CMyIEView : public CHtmlView
{
protected: // 仅从序列化创建
	CMyIEView();
	DECLARE_DYNCREATE(CMyIEView)

// 操作
public:

// 重写
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
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

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	void fill(int n =0);
	int m_time;
	bool  m_bstartyanzhi;
public:
	afx_msg void OnFill();
	afx_msg void OnFileNew();
	int SaveBitmapToFile(HBITMAP hBitmap, LPTSTR lpFileName) /*hBitmap 为刚才的屏??图句柄 */;
	HBITMAP CopyScreenToBitmap(LPRECT lpRect) /*lpRect 代表选定区域 */;
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


