
// MyIEView.cpp : CMyIEView 类的实现
//

#include "stdafx.h"
#include "MyIE.h"

#include "MyIEDoc.h"
#include "MyIEView.h"
#include ".\myieview.h"
#include "SearchDlg.h"
#include "RegisterCode.h"

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
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_32774, &CMyIEView::OnUpdateThunderVip)
	ON_UPDATE_COMMAND_UI(ID_CALLME, &CMyIEView::OnUpdateCallme)
	ON_UPDATE_COMMAND_UI(ID_StartShare, &CMyIEView::OnUpdateStartshare)
	ON_UPDATE_COMMAND_UI(ID_NOWWEB, &CMyIEView::OnUpdateNowweb)
	ON_UPDATE_COMMAND_UI(ID_ZHUCEMA, &CMyIEView::OnUpdateZhucema)
END_MESSAGE_MAP()

// CMyIEView 构造/析构

CMyIEView::CMyIEView()
{
	// TODO: 在此处添加构造代码
	m_pHTMLDocument2 = NULL;
	m_bFirst = false;
}

CMyIEView::~CMyIEView()
{
}

BOOL CMyIEView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	m_csAccount = _T("请输入你的学号密码");
	m_csPasswd = _T("123");
	return CHtmlView::PreCreateWindow(cs);
}

void CMyIEView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	ShellExecute(NULL,"open","使用说明.txt",NULL,NULL,SW_SHOW);
	CString   csDeaultWebSite = _T("http://jw.usx.edu.cn/default2.aspx");
	TCHAR  sz[256] ={0};
	CString csCurrentPath = GetCurrentPath();
	GetPrivateProfileString(_T("web"),_T("website"),csDeaultWebSite,sz,256,csCurrentPath+_T("\\setjw.ini"));
	m_csWebSite  = sz;
	Navigate2(m_csWebSite,navNoHistory,NULL);
	WritePrivateProfileString(_T("web"),_T("website"),m_csWebSite,csCurrentPath+_T("\\setjw.ini"));
	SetTimer(0,1000,0);
} 


#ifdef _DEBUG
void CMyIEView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CMyIEView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

#endif
CString CMyIEView::GetWebStieHtml(CString  strUrl)
{
	CInternetSession mySession(NULL,0);  
	CHttpFile* myHttpFile = NULL;
	myHttpFile = (CHttpFile*)mySession.OpenURL(strUrl);//str是要打开的地址
	CString myData;
	CString  m_csHtmlContent;
	while(myHttpFile->ReadString(myData)) 
	{
		m_csHtmlContent += myData; 
	}

	return m_csHtmlContent;
}

void CMyIEView::fill(int n)
{
	IHTMLDocument2 * pHTMLDocument2=(IHTMLDocument2*)(this->GetHtmlDocument());
	m_pHTMLDocument2 = pHTMLDocument2;
	//pHTMLDocument2->clear();
	IHTMLElementCollection* pColl;
	IHTMLWindow2 *win;
	IHTMLFormElement *form;
	HRESULT hr;
	hr=pHTMLDocument2->get_links(&pColl);
	
	BSTR cst1;
	pHTMLDocument2->get_URL(&cst1);
	CString css1 = COLE2CT(cst1);

	if(css1!=m_csWebSite)
	{
		 int n = css1.ReverseFind('/');
		 CString cstr = css1.Mid(0,n+1);

		 //CString csnewweb = cstr+
	}
	if(hr==S_OK)
	{
		LONG celem;
		hr=pColl->get_length(&celem);
		if(celem>=20)
		{
			return;
		}

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
					if(u=="http://www.youku.com/user_login/")
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
							if(ts=="TextBox1"&&!m_bFirst)
							{
								input->put_value(m_csAccount.AllocSysString());
								m_bFirst = true;
								TRACE("---------NICKName\n");
								
							}
							else if(ts=="TextBox2")
							{
								//input->put_value(m_csPasswd.AllocSysString());
								TRACE("-------------Age\n");
		                         /*input->get_value(&csAccount);
								 input->get_value(&csPasswd);
								 CString css1 = COLE2CT(csAccount);
								 CString css2 = COLE2CT(csPasswd);
								 if(!css1.IsEmpty() &&!css2.IsEmpty())
								 {
									 CString sq1,sq2;
									 sq1="goApply()";
									 sq2="javascript";
									 {
										 pHTMLDocument2->get_parentWindow(&win);
										 win->execScript(sq1.AllocSysString(),sq2.AllocSysString(),&var2);
									 }
									 form->submit();
								 }*/
							}
						}
					}
				}
				
			}
		}
		}
	
						


}

HBITMAP  CMyIEView::CopyScreenToBitmap(LPRECT lpRect) //lpRect 代表选定区域
{
	HDC hScrDC, hMemDC;   
	// 屏幕和内存设备描述表
	HBITMAP hBitmap,hOldBitmap;   
	// 位图句柄
	int nX, nY, nX2, nY2;   
	// 选定区域坐标
	int nWidth, nHeight;   
	// 位图宽度和高度
	int xScrn, yScrn;   
	// 屏幕分辨率
	// 确保选定区域不为空矩形
	if (IsRectEmpty(lpRect))
	{
		return NULL;
	}

	//为屏幕创建设备描述表
	hScrDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	//为屏幕设备描述表创建兼容的内存设备描述表
	hMemDC = CreateCompatibleDC(hScrDC);
	// 获得选定区域坐标
	nX  = lpRect->left;
	nY  = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	// 获得屏幕分辨率
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//确保选定区域是可见的
	if (nX < 0)
		nX = 0;
	if (nY < 0)
		nY = 0;
	if (nX2 > xScrn)
		nX2 = xScrn;
	if (nY2 > yScrn)
		nY2 = yScrn;
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;

	// 创建一个与屏幕设备描述表兼容的位图
	hBitmap = CreateCompatibleBitmap(hScrDC,nWidth,nHeight);
	// 把新位图选到内存设备描述表中
	hOldBitmap = (HBITMAP)SelectObject(hMemDC,hBitmap);
	// 把屏幕设备描述表拷贝到内存设备描述表中
	BitBlt(hMemDC,0,0, nWidth,nHeight,hScrDC, nX, nY, SRCCOPY);
	//得到屏幕位图的句柄
	hBitmap = (HBITMAP)SelectObject(hMemDC,hOldBitmap);
	//清除
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	// 返回位图句柄
	return hBitmap;
}


int  CMyIEView::SaveBitmapToFile(HBITMAP hBitmap, LPTSTR lpFileName) //hBitmap 为刚才的屏幕位图句柄
{ //lpFileName 为位图文件名
	HDC hDC;   
	//设备描述表
	int iBits;   
	//当前显示分辨率下每个像素所占字节数

	WORD wBitCount;   
	//位图中每个像素所占字节数
	//定义调色板大小， 位图中像素字节大小 ， 位图文件大小 ， 写入文件字节数
	DWORD dwPaletteSize=0,dwBmBitsSize,dwDIBSize, dwWritten;
	BITMAP Bitmap;   
	//位图属性结构
	BITMAPFILEHEADER bmfHdr;   
	//位图文件头结构
	BITMAPINFOHEADER bi;   
	//位图信息头结构
	LPBITMAPINFOHEADER lpbi;   
	//指向位图信息头结构
	HANDLE fh, hDib, hPal;
	HPALETTE hOldPal=NULL;
	//定义文件，分配内存句柄，调色板句柄

	//计算位图文件每个像素所占字节数
	hDC = CreateDC(_T("DISPLAY"),NULL,NULL,NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL) *
		GetDeviceCaps(hDC, PLANES);
	DeleteDC(hDC);
	if (iBits <= 1)
		wBitCount = 1;
	else if (iBits <= 4)
		wBitCount = 4;
	else if (iBits <= 8)
		wBitCount = 8;
	else if (iBits <= 24)
		wBitCount = 24;
	else
		wBitCount = 32;
	//计算调色板大小
	if (wBitCount <= 8)
		dwPaletteSize=(1<<wBitCount)*sizeof(RGBQUAD);

	//设置位图信息头结构
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;
	bi.biHeight = Bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0; 
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	dwBmBitsSize = ((Bitmap.bmWidth*wBitCount+31)/32)*4*Bitmap.bmHeight;
	//为位图内容分配内存
	/*xxxxxxxx计算位图大小分解一下(解释一下上面的语句)xxxxxxxxxxxxxxxxxxxx  
	//每个扫描行所占的字节数应该为4的整数倍，具体算法为:
	int biWidth = (Bitmap.bmWidth*wBitCount) / 32;
	if((Bitmap.bmWidth*wBitCount) % 32)
	biWidth++; //不是整数倍的加1
	biWidth *= 4;//到这里，计算得到的为每个扫描行的字节数。
	dwBmBitsSize = biWidth * Bitmap.bmHeight;//得到大小
	xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
   

	hDib = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;
	// 处理调色板   
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal=SelectPalette(hDC,(HPALETTE)hPal,FALSE);
		RealizePalette(hDC);
	}
	// 获取该调色板下新的像素值
	GetDIBits(hDC,hBitmap,0,(UINT)Bitmap.bmHeight,(LPSTR)lpbi+sizeof(BITMAPINFOHEADER)+dwPaletteSize, (BITMAPINFO *)lpbi,DIB_RGB_COLORS);
	//恢复调色板   
	if (hOldPal)
	{
		SelectPalette(hDC, hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}
	//创建位图文件   
	fh=CreateFile(lpFileName, GENERIC_WRITE,0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (fh==INVALID_HANDLE_VALUE)
		return FALSE;
	// 设置位图文件头
	bmfHdr.bfType = 0x4D42; // "BM"
	dwDIBSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize;  
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;
	// 写入位图文件头
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	// 写入位图文件其余内容
	WriteFile(fh, (LPSTR)lpbi, sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize , &dwWritten, NULL);
	//清除   
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);
	return TRUE;
}

// CMyIEView 消息处理程序

void Screen(char filename[])
{
	CDC *pDC;//屏幕DC
	pDC = CDC::FromHandle(GetDC(NULL));//获取当前整个屏幕DC
	int BitPerPixel = pDC->GetDeviceCaps(BITSPIXEL);//获得颜色模式
	int Width = pDC->GetDeviceCaps(HORZRES);
	int Height = pDC->GetDeviceCaps(VERTRES);

	CDC memDC;//内存DC
	memDC.CreateCompatibleDC(pDC);

	CBitmap memBitmap, *oldmemBitmap;//建立和屏幕兼容的bitmap
	memBitmap.CreateCompatibleBitmap(pDC, Width, Height);

	oldmemBitmap = memDC.SelectObject(&memBitmap);//将memBitmap选入内存DC
	memDC.BitBlt(0, 0, Width, Height, pDC, 0, 0, SRCCOPY);//复制屏幕图像到内存DC

	//以下代码保存memDC中的位图到文件
	BITMAP bmp;
	memBitmap.GetBitmap(&bmp);//获得位图信息

	FILE *fp = fopen(filename, "w+b");

	BITMAPINFOHEADER bih = {0};//位图信息头
	bih.biBitCount = bmp.bmBitsPixel;//每个像素字节大小
	bih.biCompression = BI_RGB;
	bih.biHeight = bmp.bmHeight;//高度
	bih.biPlanes = 1;
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;//图像数据大小
	bih.biWidth = bmp.bmWidth;//宽度

	BITMAPFILEHEADER bfh = {0};//位图文件头
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//到位图数据的偏移量
	bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;//文件总的大小
	bfh.bfType = (WORD)0x4d42;
	fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);//写入位图文件头 
	fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);//写入位图信息头
	byte * p = new byte[bmp.bmWidthBytes * bmp.bmHeight];//申请内存保存位图数据
	GetDIBits(memDC.m_hDC, (HBITMAP) memBitmap.m_hObject, 0, Height, p,
		(LPBITMAPINFO) &bih, DIB_RGB_COLORS);//获取位图数据
	fwrite(p, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);//写入位图数据
	delete [] p;
	fclose(fp);
	memDC.SelectObject(oldmemBitmap);
}


UINT __cdecl CMyIEView::MyControllingFunction(LPVOID pParam)
{

	
	return 0;

}
void CMyIEView::OnFill()
{
	// TODO: 在此添加命令处理程序代码
// fill();
	
}

void CMyIEView::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
	
}

void CMyIEView::OnTimer(UINT_PTR nIDEvent)
{
	fill();
	CHtmlView::OnTimer(nIDEvent);
}

int i = 1;
void CMyIEView::OnUpdateThunderVip(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	//迅雷会员登录
	KillTimer(0);
	if(i==1)
	{
		
		Navigate2(_T("http://i.xunlei.com/login.html?redirect_url="),navNoHistory|navNoWriteToCache,NULL);
	}	
}


void  CMyIEView::FillWeb(CString csWebSite,CString csAccountname,CString csPasswdName)
{
	IHTMLDocument2*pHTMLDocument2=(IHTMLDocument2*)(this->GetHtmlDocument());
	////pHTMLDocument2->clear();
	IHTMLElementCollection* pColl;
	IHTMLWindow2 *win;
	IHTMLFormElement *form;
	HRESULT hr;
	hr=pHTMLDocument2->get_links(&pColl);

	if(hr==S_OK)
	{
		LONG celem;
		hr=pColl->get_length(&celem);
		if(celem>=20)
		{
			return;
		}

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
					if(u==csWebSite)
					{
						Navigate2(u,NULL,NULL);
					}
				}
			}
		}
	}
	hr=pHTMLDocument2->get_all(&pColl);
	BSTR s;

	pHTMLDocument2->get_title(&s);

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
							if(ts==csAccountname)
							{
								ts1="123456qq";
								input->put_value(ts1.AllocSysString());
								TRACE("---------NICKName\n");
							}
							if(ts==csPasswdName)
							{
								ts1="6520874@163.com";
								input->put_value(ts1.AllocSysString());
								TRACE("-------------Age\n");
	
							}

							if(ts=="verifycode")
							{ 

								//if(!m_bstartyanzhi)   
									//AfxMessageBox("麻烦您输下验证码，输完后软件会自动点击回车");

								BSTR  cs;
								input->get_value(&cs);
								CString s = COLE2CT(cs); //将BSTR转换为LPCTSTR，不可使用OLE2CT
								if(s.GetLength() >=1)
								{
									m_bstartyanzhi = true;
								}


								if(s.GetLength() >= 4)
								{
									KillTimer(0);
									CString sq1,sq2;
									sq1="goApply()";
									sq2="javascript";
									if(m_time==1)
									{
										pHTMLDocument2->get_parentWindow(&win);
										win->execScript(sq1.AllocSysString(),sq2.AllocSysString(),&var2);
									}
									form->submit();

								}
								if(s.GetLength()<=0)
								{
									m_bstartyanzhi  = false;
								}

							}


						}
						TRACE("%d:%s\n",i,ts);
					}
				}
			}
		}
	}
}


void CMyIEView::OnUpdateCallme(CCmdUI *pCmdUI)
{
   ShellExecute(m_hWnd,"open","http://wpa.qq.com/msgrd?v=3&uin=1146439885",NULL,NULL,SW_SHOW);
}

void CMyIEView::OnUpdateStartshare(CCmdUI *pCmdUI)
{
	ShellExecute(m_hWnd,"open","http://121.199.10.53/Youku/",NULL,NULL,SW_SHOW);
}

void CMyIEView::OnUpdateNowweb(CCmdUI *pCmdUI)
{
	
	BSTR cst1;
	if(m_pHTMLDocument2)
	{
		m_pHTMLDocument2->get_URL(&cst1);
		CString css1 = COLE2CT(cst1);

		if(css1 != m_csWebSite)
		{
			CSearchDlg  dlg(this);
			dlg.DoModal();
		}
		else
		{
			AfxMessageBox(_T("请先输入你的学号密码，点击登录,登录成功可以开始查询"));
		}
	}
}


void CMyIEView::OnUpdateZhucema(CCmdUI *pCmdUI)
{
	CRegisterCode   dlg;
	dlg.DoModal();
}
