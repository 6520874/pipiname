#include "StdAfx.h"
#include "MyEdit.h"
#include "war3HelperDlg.h"
CMyEdit::CMyEdit(void)
{
}

CMyEdit::~CMyEdit(void)
{
}

void CMyEdit::OnEditCommandTab(MSG* pMsg,const TCHAR * sz)
{ 
  
	//GetWar3Dlg().m_num7.GetWindowText(sz);
	if(pMsg->hwnd == m_Pdlg->m_num7.GetSafeHwnd())
	{
		m_Pdlg->m_num7.SetWindowText(sz);
	}
	else if(pMsg->hwnd == m_Pdlg->m_num8.GetSafeHwnd())
	{
		m_Pdlg->m_num8.SetWindowText(sz);
	}
	else if(pMsg->hwnd == m_Pdlg->m_num4.GetSafeHwnd())
		m_Pdlg->m_num4.SetWindowText(sz);
	else if(pMsg->hwnd == m_Pdlg->m_num5.GetSafeHwnd())
		m_Pdlg->m_num5.SetWindowText(sz);
	else if(pMsg->hwnd == m_Pdlg->m_num1.GetSafeHwnd())
		m_Pdlg->m_num1.SetWindowText(sz);
	else if(pMsg->hwnd == m_Pdlg->m_num2.GetSafeHwnd())
		m_Pdlg->m_num2.SetWindowText(sz);
  
}
BOOL CMyEdit::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
    if(pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_TAB:OnEditCommandTab(pMsg,_T("Tab"));break;
		case VK_SPACE: OnEditCommandTab(pMsg,_T("Space"));break;
		case VK_CAPITAL:OnEditCommandTab(pMsg,_T("Caps"));;break;
		default:break;
		}
		
	}
	return CEdit::PreTranslateMessage(pMsg);
}

void CMyEdit::InitDlg( Cwar3HelperDlg *dlg )
{
    m_Pdlg = dlg;
}
