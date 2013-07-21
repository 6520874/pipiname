#if !defined(AFX_HYPERLINKER_H__294375CE_81BF_45A7_812B_705722B344AF__INCLUDED_)
#define AFX_HYPERLINKER_H__294375CE_81BF_45A7_812B_705722B344AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HyperLinker.h : header file
//
// // www.zju.edu.cn

/////////////////////////////////////////////////////////////////////////////
// CHyperLinker window

class CHyperLinker : public CStatic
{
public:
	CHyperLinker();
	virtual ~CHyperLinker();

public:
    COLORREF m_InitColor;							//�ı���ʼ��ɫ
	COLORREF m_VisitedColor;						//�ı������ʹ������ɫ
    COLORREF m_CoverColor;							//����������ı��Ϸ�ʱ����ɫ
    
	BOOL     m_bAboveControl;                        // �Ƿ�����Ƶ��ؼ���
    BOOL     m_bVisited;                            // �Ƿ񱻷���
    BOOL     m_bUnderLine;                          // �Ƿ����»���
    
	CString  m_sURL;								// URL����Ӧ�ó����λ��
    CFont    m_Font;                                // �趨����
    HCURSOR  m_hLinkCursor;                         // ���

public:
	void SetAttribute(CString url="http://pipi.1kapp.com/",COLORREF InitColor=RGB(0,0,255), COLORREF VisitedColor=RGB(255,0,0), 
                    COLORREF CoverColor=RGB(125,125,0),BOOL bUnderLine=TRUE);
	BOOL OpenUsingShellExecute();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHyperLinker)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

protected:
	// Generated message map functions
	//{{AFX_MSG(CHyperLinker)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HYPERLINKER_H__294375CE_81BF_45A7_812B_705722B344AF__INCLUDED_)
