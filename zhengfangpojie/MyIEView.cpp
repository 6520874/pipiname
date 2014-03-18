
// MyIEView.cpp : CMyIEView ���ʵ��
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
	// ��׼��ӡ����
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

// CMyIEView ����/����

CMyIEView::CMyIEView()
{
	// TODO: �ڴ˴���ӹ������
	m_pHTMLDocument2 = NULL;
	m_bFirst = false;
}

CMyIEView::~CMyIEView()
{
}

BOOL CMyIEView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	m_csAccount = _T("���������ѧ������");
	m_csPasswd = _T("123");
	return CHtmlView::PreCreateWindow(cs);
}

void CMyIEView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	ShellExecute(NULL,"open","ʹ��˵��.txt",NULL,NULL,SW_SHOW);
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
	myHttpFile = (CHttpFile*)mySession.OpenURL(strUrl);//str��Ҫ�򿪵ĵ�ַ
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

HBITMAP  CMyIEView::CopyScreenToBitmap(LPRECT lpRect) //lpRect ����ѡ������
{
	HDC hScrDC, hMemDC;   
	// ��Ļ���ڴ��豸������
	HBITMAP hBitmap,hOldBitmap;   
	// λͼ���
	int nX, nY, nX2, nY2;   
	// ѡ����������
	int nWidth, nHeight;   
	// λͼ��Ⱥ͸߶�
	int xScrn, yScrn;   
	// ��Ļ�ֱ���
	// ȷ��ѡ������Ϊ�վ���
	if (IsRectEmpty(lpRect))
	{
		return NULL;
	}

	//Ϊ��Ļ�����豸������
	hScrDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	hMemDC = CreateCompatibleDC(hScrDC);
	// ���ѡ����������
	nX  = lpRect->left;
	nY  = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	// �����Ļ�ֱ���
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//ȷ��ѡ�������ǿɼ���
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

	// ����һ������Ļ�豸��������ݵ�λͼ
	hBitmap = CreateCompatibleBitmap(hScrDC,nWidth,nHeight);
	// ����λͼѡ���ڴ��豸��������
	hOldBitmap = (HBITMAP)SelectObject(hMemDC,hBitmap);
	// ����Ļ�豸�����������ڴ��豸��������
	BitBlt(hMemDC,0,0, nWidth,nHeight,hScrDC, nX, nY, SRCCOPY);
	//�õ���Ļλͼ�ľ��
	hBitmap = (HBITMAP)SelectObject(hMemDC,hOldBitmap);
	//���
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	// ����λͼ���
	return hBitmap;
}


int  CMyIEView::SaveBitmapToFile(HBITMAP hBitmap, LPTSTR lpFileName) //hBitmap Ϊ�ղŵ���Ļλͼ���
{ //lpFileName Ϊλͼ�ļ���
	HDC hDC;   
	//�豸������
	int iBits;   
	//��ǰ��ʾ�ֱ�����ÿ��������ռ�ֽ���

	WORD wBitCount;   
	//λͼ��ÿ��������ռ�ֽ���
	//�����ɫ���С�� λͼ�������ֽڴ�С �� λͼ�ļ���С �� д���ļ��ֽ���
	DWORD dwPaletteSize=0,dwBmBitsSize,dwDIBSize, dwWritten;
	BITMAP Bitmap;   
	//λͼ���Խṹ
	BITMAPFILEHEADER bmfHdr;   
	//λͼ�ļ�ͷ�ṹ
	BITMAPINFOHEADER bi;   
	//λͼ��Ϣͷ�ṹ
	LPBITMAPINFOHEADER lpbi;   
	//ָ��λͼ��Ϣͷ�ṹ
	HANDLE fh, hDib, hPal;
	HPALETTE hOldPal=NULL;
	//�����ļ��������ڴ�������ɫ����

	//����λͼ�ļ�ÿ��������ռ�ֽ���
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
	//�����ɫ���С
	if (wBitCount <= 8)
		dwPaletteSize=(1<<wBitCount)*sizeof(RGBQUAD);

	//����λͼ��Ϣͷ�ṹ
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
	//Ϊλͼ���ݷ����ڴ�
	/*xxxxxxxx����λͼ��С�ֽ�һ��(����һ����������)xxxxxxxxxxxxxxxxxxxx  
	//ÿ��ɨ������ռ���ֽ���Ӧ��Ϊ4���������������㷨Ϊ:
	int biWidth = (Bitmap.bmWidth*wBitCount) / 32;
	if((Bitmap.bmWidth*wBitCount) % 32)
	biWidth++; //�����������ļ�1
	biWidth *= 4;//���������õ���Ϊÿ��ɨ���е��ֽ�����
	dwBmBitsSize = biWidth * Bitmap.bmHeight;//�õ���С
	xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
   

	hDib = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;
	// �����ɫ��   
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal=SelectPalette(hDC,(HPALETTE)hPal,FALSE);
		RealizePalette(hDC);
	}
	// ��ȡ�õ�ɫ�����µ�����ֵ
	GetDIBits(hDC,hBitmap,0,(UINT)Bitmap.bmHeight,(LPSTR)lpbi+sizeof(BITMAPINFOHEADER)+dwPaletteSize, (BITMAPINFO *)lpbi,DIB_RGB_COLORS);
	//�ָ���ɫ��   
	if (hOldPal)
	{
		SelectPalette(hDC, hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}
	//����λͼ�ļ�   
	fh=CreateFile(lpFileName, GENERIC_WRITE,0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (fh==INVALID_HANDLE_VALUE)
		return FALSE;
	// ����λͼ�ļ�ͷ
	bmfHdr.bfType = 0x4D42; // "BM"
	dwDIBSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize;  
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;
	// д��λͼ�ļ�ͷ
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	// д��λͼ�ļ���������
	WriteFile(fh, (LPSTR)lpbi, sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize , &dwWritten, NULL);
	//���   
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);
	return TRUE;
}

// CMyIEView ��Ϣ�������

void Screen(char filename[])
{
	CDC *pDC;//��ĻDC
	pDC = CDC::FromHandle(GetDC(NULL));//��ȡ��ǰ������ĻDC
	int BitPerPixel = pDC->GetDeviceCaps(BITSPIXEL);//�����ɫģʽ
	int Width = pDC->GetDeviceCaps(HORZRES);
	int Height = pDC->GetDeviceCaps(VERTRES);

	CDC memDC;//�ڴ�DC
	memDC.CreateCompatibleDC(pDC);

	CBitmap memBitmap, *oldmemBitmap;//��������Ļ���ݵ�bitmap
	memBitmap.CreateCompatibleBitmap(pDC, Width, Height);

	oldmemBitmap = memDC.SelectObject(&memBitmap);//��memBitmapѡ���ڴ�DC
	memDC.BitBlt(0, 0, Width, Height, pDC, 0, 0, SRCCOPY);//������Ļͼ���ڴ�DC

	//���´��뱣��memDC�е�λͼ���ļ�
	BITMAP bmp;
	memBitmap.GetBitmap(&bmp);//���λͼ��Ϣ

	FILE *fp = fopen(filename, "w+b");

	BITMAPINFOHEADER bih = {0};//λͼ��Ϣͷ
	bih.biBitCount = bmp.bmBitsPixel;//ÿ�������ֽڴ�С
	bih.biCompression = BI_RGB;
	bih.biHeight = bmp.bmHeight;//�߶�
	bih.biPlanes = 1;
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;//ͼ�����ݴ�С
	bih.biWidth = bmp.bmWidth;//���

	BITMAPFILEHEADER bfh = {0};//λͼ�ļ�ͷ
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//��λͼ���ݵ�ƫ����
	bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;//�ļ��ܵĴ�С
	bfh.bfType = (WORD)0x4d42;
	fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);//д��λͼ�ļ�ͷ 
	fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);//д��λͼ��Ϣͷ
	byte * p = new byte[bmp.bmWidthBytes * bmp.bmHeight];//�����ڴ汣��λͼ����
	GetDIBits(memDC.m_hDC, (HBITMAP) memBitmap.m_hObject, 0, Height, p,
		(LPBITMAPINFO) &bih, DIB_RGB_COLORS);//��ȡλͼ����
	fwrite(p, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);//д��λͼ����
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
	// TODO: �ڴ���������������
// fill();
	
}

void CMyIEView::OnFileNew()
{
	// TODO: �ڴ���������������
	
}

void CMyIEView::OnTimer(UINT_PTR nIDEvent)
{
	fill();
	CHtmlView::OnTimer(nIDEvent);
}

int i = 1;
void CMyIEView::OnUpdateThunderVip(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	//Ѹ�׻�Ա��¼
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
									//AfxMessageBox("�鷳��������֤�룬�����������Զ�����س�");

								BSTR  cs;
								input->get_value(&cs);
								CString s = COLE2CT(cs); //��BSTRת��ΪLPCTSTR������ʹ��OLE2CT
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
			AfxMessageBox(_T("�����������ѧ�����룬�����¼,��¼�ɹ����Կ�ʼ��ѯ"));
		}
	}
}


void CMyIEView::OnUpdateZhucema(CCmdUI *pCmdUI)
{
	CRegisterCode   dlg;
	dlg.DoModal();
}
