#include "StdAfx.h"
#include "UpdateSoft.h"


CUpdateSoft::CUpdateSoft(void)
{
	m_bMax = TRUE;
}

void CUpdateSoft::InitFire( CPictureHolder *myTmpPicture,int iWidth,int iHeight )
{
    
	m_iHeight = iHeight;
	m_iWeight = iWidth;
	m_bmpRenderSource.Create32BitFromPicture(myTmpPicture,iWidth,iHeight);
	m_bmpRenderTarget.Create32BitFromPicture(myTmpPicture,iWidth,iHeight);

	//创建水纹对象
	m_myWater.Create(iHeight,iWidth);
	//创建火焰对象
	m_myFire.m_iAlpha = 30;		// 渐变 30% alpha
	m_myFire.m_iHeight = iHeight;
	m_myFire.m_iWidth = iWidth;
	m_myFire.InitFire();
}

void CUpdateSoft::StartFire(CWnd *lp)
{
	if(m_bMax)
	{
		m_myFire.m_iAlpha ++;
	}
	else
	{
		m_myFire.m_iAlpha--;
	}

	if(m_myFire.m_iAlpha>=200)
	{
		m_bMax = FALSE;
	}
	if(m_myFire.m_iAlpha <= 1)
	{
		m_bMax = TRUE;
	}

	m_myWater.FlattenWater();  //浮动它，以便消失

	m_myWater.Render((DWORD*)m_bmpRenderSource.GetDIBits(),(DWORD*)m_bmpRenderTarget.GetDIBits());

	m_myFire.Render((DWORD*)m_bmpRenderTarget.GetDIBits(),m_iWeight,m_iHeight);

	CClientDC dc(lp);
	CPoint ptOrigin(15,20);
	m_bmpRenderTarget.Draw(&dc,ptOrigin);
}

CUpdateSoft::~CUpdateSoft( void )
{

}
