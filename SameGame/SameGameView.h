// SameGameView.h : interface of the CSameGameView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMEGAMEVIEW_H__C967C030_DBE5_40C7_A619_EBE3CC68B586__INCLUDED_)
#define AFX_SAMEGAMEVIEW_H__C967C030_DBE5_40C7_A619_EBE3CC68B586__INCLUDED_

#include "Same.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSameGameView : public CView
{
protected: // create from serialization only 
	CSameGameView();
	DECLARE_DYNCREATE(CSameGameView)
	CBitmap m_bmpScreen;
	CString m_msg;
// Attributes
public:
	bool m_bGameEnded;
	CSameGameDoc* GetDocument();
	CPoint m_hot;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSameGameView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	CImageList m_images,m_imagesHot;
	CSame *m_samegame;
	virtual ~CSameGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSameGameView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFileNew();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SameGameView.cpp
inline CSameGameDoc* CSameGameView::GetDocument()
   { return (CSameGameDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMEGAMEVIEW_H__C967C030_DBE5_40C7_A619_EBE3CC68B586__INCLUDED_)
