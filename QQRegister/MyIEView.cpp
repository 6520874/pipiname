//Download by http://www.NewXing.com
// MyIEView.cpp : CMyIEView 类的实现
//

#include "stdafx.h"
#include "MyIE.h"

#include "MyIEDoc.h"
#include "MyIEView.h"
#include ".\myieview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "comutil.h"

// CMyIEView

IMPLEMENT_DYNCREATE(CMyIEView, CHtmlView)

BEGIN_MESSAGE_MAP(CMyIEView, CHtmlView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
	ON_COMMAND(ID_Fill, OnFill)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
END_MESSAGE_MAP()

// CMyIEView 构造/析构

CMyIEView::CMyIEView()
{
	// TODO: 在此处添加构造代码

}

CMyIEView::~CMyIEView()
{
}

BOOL CMyIEView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CHtmlView::PreCreateWindow(cs);
}

void CMyIEView::OnInitialUpdate()
{
	
	time=0;
	
	CHtmlView::OnInitialUpdate();/*http://211.87.237.80/untitled-1.htm*/
	Navigate2(_T("http://freeqq2.qq.com/1.shtml"),navNoHistory|navNoWriteToCache,NULL);

}


// CMyIEView 打印



// CMyIEView 诊断

#ifdef _DEBUG
void CMyIEView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CMyIEView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CQQRegDoc* CMyIEView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CQQRegDoc)));
	return (CQQRegDoc*)m_pDocument;
}
#endif //_DEBUG

void CMyIEView::fill()
{

	IHTMLDocument2*pHTMLDocument2=(IHTMLDocument2*)(this->GetHtmlDocument());
	//pHTMLDocument2->clear();
	IHTMLElementCollection* pColl;
	IHTMLWindow2 *win;
	IHTMLFormElement *form;
	HRESULT hr;
	hr=pHTMLDocument2->get_links(&pColl);
	
	if(hr==S_OK)
	{
		LONG celem;
		hr=pColl->get_length(&celem);
		if(hr==S_OK)
		{
			VARIANT varIndex,var2;
			for(int i=0;i<celem;i++)
			{
				varIndex.vt=VT_UINT;
				varIndex.lVal=i;
				VariantInit(&var2);
				IDispatch* pDisp;
				hr=pColl->item(varIndex,var2,&pDisp);
				if(hr==S_OK)
				{
					BSTR bs;
					IHTMLAnchorElement*pa;
					hr=pDisp->QueryInterface(IID_IHTMLAnchorElement,(void**)&pa);
					pa->get_href(&bs);
					TRACE(bs);
					CString u(bs);
					if(u=="http://freeqq2.qq.com/2.shtml")
					{
						Navigate2(u,NULL,NULL);
					}
				}
			}
		}
	}
	hr=pHTMLDocument2->get_all(&pColl);
	if(hr==S_OK)
	{
		LONG celem;
		hr=pColl->get_length(&celem);
		if(hr==S_OK)
		{
			VARIANT varIndex,var2;
			for(int i=0;i<celem;i++)
			{
				varIndex.vt=VT_UINT;
				varIndex.lVal=i;
				VariantInit(&var2);
				IDispatch* pDisp;
				hr=pColl->item(varIndex,var2,&pDisp);

				if(hr==S_OK)
				{
					IHTMLElement*pElem;
					hr=pDisp->QueryInterface(IID_IHTMLElement,(void**)&pElem);
					if(hr==S_OK)
					{
						///time+=1;
						CString ts,ts1,tss;
						tss="";
						BSTR bs;
						pElem->get_tagName(&bs);
						ts=CString(bs);
						if(ts=="SELECT")
						{
							IHTMLSelectElement *pp;
							hr=pDisp->QueryInterface(IID_IHTMLSelectElement,(void**)&pp);
							pp->get_name(&bs);
							ts=CString(bs);
							if(ts=="sltCountry")
								pp->put_selectedIndex(0);
							if(ts=="sltProvinceId")
							{
								pp->put_selectedIndex(1);
								pHTMLDocument2->get_parentWindow(&win);
								CString sq1,sq2;
								sq1="SelectProvice()";
								sq2="javascript";
								hr=win->execScript(sq1.AllocSysString(),sq2.AllocSysString(),&var2);
								if(hr!=S_OK)
									MessageBox("error");

							}
							if(ts=="sltAllLocId")
							{
								pp->put_selectedIndex(0);

							}
						}
						if(ts=="FORM")
						{
							hr=pDisp->QueryInterface(IID_IHTMLFormElement,(void**)&form);
							if(hr!=S_OK)
								MessageBox("error form");
						continue;

						}
						if(ts=="INPUT")
						{
							IHTMLInputElement* input;
							hr=pDisp->QueryInterface(IID_IHTMLInputElement,(void**)&input);
							input->get_name(&bs);
							ts=CString(bs);
							if(ts=="Nickname")
							{
								ts1="123";
								input->put_value(ts1.AllocSysString());
								TRACE("---------NICKName\n");
							}
							if(ts=="Age")
							{
								ts1="20";
								input->put_value(ts1.AllocSysString());
								TRACE("-------------Age\n");
							}
							if((ts=="Passwd")||(ts=="Passwd1"))
							{

								ts1="123456";
								input->put_value(ts1.AllocSysString());
								TRACE("-----------------password\n");
							}
							if((ts=="Validatecode"))
							{
								time=(++time)%2;
								input->get_value(&bs);
								tss=CString(bs);
								TRACE("%s\n",tss);
								if(tss!="")
								{
										CString sq1,sq2;
										sq1="goApply()";
										sq2="javascript";
									/*MessageBox("ok");
									if(time==1)
									{
									pHTMLDocument2->get_parentWindow(&win);
									win->execScript(sq1.AllocSysString(),sq2.AllocSysString(),&var2);
									}
									form->submit();*/
								}
									
							}
							if(ts=="Email")
							{
								input->select();
								MessageBox("ok");
							}
							
						}
						TRACE("%d:%s\n",i,ts);
					}
				}
			}
		}
	}


}
// CMyIEView 消息处理程序

void CMyIEView::OnFill()
{
	// TODO: 在此添加命令处理程序代码
	AfxMessageBox(_T("QQ2013将开始自动分析验证码，此过程可能需要等待一段时间"));
	fill();
}

void CMyIEView::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
	
	time=0;
	BSTR bs;
	CString ts="";
	IHTMLDocument2*pHTMLDocument3=(IHTMLDocument2*)(this->GetHtmlDocument());
	pHTMLDocument3->get_cookie(&bs);
	TRACE("------------------------777777777777777777------------------\n");
	TRACE(bs);
	TRACE("\n");
	pHTMLDocument3->put_cookie(ts.AllocSysString());
	pHTMLDocument3->clear();
	pHTMLDocument3->get_cookie(&bs);
	TRACE("-----------------------88888888888888888------------------\n");
	TRACE(bs);
	TRACE("\n");
	Navigate2(_T("http://freeqq2.qq.com/1.shtml"),0x4,NULL);
}
