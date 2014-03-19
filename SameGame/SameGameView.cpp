// SameGameView.cpp : implementation of the CSameGameView class
//

#include "stdafx.h"
#include "SameGame.h"
#include "math.h"

#include "SameGameDoc.h"
#include "SameGameView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSameGameView

IMPLEMENT_DYNCREATE(CSameGameView, CView)

BEGIN_MESSAGE_MAP(CSameGameView, CView)
	//{{AFX_MSG_MAP(CSameGameView)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSameGameView construction/destruction

CSameGameView::CSameGameView()
{
	m_samegame = NULL;

	m_bGameEnded = false;
	CBitmap bmp1,bmp2;
	bmp1.LoadBitmap(IDB_SAME);
	bmp2.LoadBitmap(IDB_SAMEHOT);
	m_images.Create(22, 22, ILC_MASK | ILC_COLOR32, 0, 0);
	m_images.Add(&bmp1, RGB(255,255,255));

	m_imagesHot.Create(22, 22, ILC_MASK | ILC_COLOR32, 0, 0);
	m_imagesHot.Add(&bmp2, RGB(255,255,255));
}

CSameGameView::~CSameGameView()
{
	if(m_bmpScreen.m_hObject != NULL) {
		m_bmpScreen.DeleteObject();
		m_bmpScreen.m_hObject = NULL;
	}
	if(m_samegame)
	{
		delete m_samegame;
	}
	m_imagesHot.DeleteImageList();
	m_images.DeleteImageList();
}

BOOL CSameGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSameGameView drawing

void CSameGameView::OnDraw(CDC* pDC)
{
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDC imageDC;
	imageDC.CreateCompatibleDC(pDC);

	CBitmap* pOldMemDCBitmap = NULL;

	CRect rect; //(0,0,22*15+15, 22*10+10);
	GetClientRect(&rect);

	if(m_bmpScreen.m_hObject == NULL) 
		m_bmpScreen.CreateCompatibleBitmap( pDC, rect.Width(), rect.Height());

	pOldMemDCBitmap = (CBitmap*)imageDC.SelectObject(&m_bmpScreen);
	
	imageDC.FillSolidRect(rect,RGB(255,255,255));

	if(m_samegame)
	{
		m_samegame->Draw(&imageDC,&m_images);
		if(m_hot.x >=0 && m_hot.y >= 0)
		{
			m_samegame->Zero();
			m_samegame->DrawHot(&imageDC,m_hot.y,m_hot.x,&m_imagesHot);
		}
	}

	pDC->BitBlt( rect.left , rect.top , rect.Width(), rect.Height(), 
					&imageDC, 0, 0, SRCCOPY );


	imageDC.SelectObject(pOldMemDCBitmap);
}

/////////////////////////////////////////////////////////////////////////////
// CSameGameView diagnostics

#ifdef _DEBUG
void CSameGameView::AssertValid() const
{
	CView::AssertValid();
}

void CSameGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSameGameDoc* CSameGameView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSameGameDoc)));
	return (CSameGameDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSameGameView message handlers

BOOL CSameGameView::OnEraseBkgnd(CDC* pDC) 
{
	
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}

void CSameGameView::OnFileNew() 
{
	m_bGameEnded = false;
	if(m_samegame)
	{
		delete m_samegame;
	}

	m_samegame = new CSame(10,15);
	Invalidate();
}

void CSameGameView::OnInitialUpdate() 
{
	OnFileNew();

	CView::OnInitialUpdate();
}

void CSameGameView::OnMouseMove(UINT nFlags, CPoint point) 
{
	static CPoint hot;

	point.x = point.x/23;
	point.y = point.y/23;
	if(point != hot)
	{
		hot = point;
	}
	else
	{
		return;
	}
	
	if((point.x != m_hot.x)  || (point.y != m_hot.y))
	{
		
		if((point.x >=0 && point.y >= 0) && (point.x <15 && point.y < 10 ))
		{
			if(m_hot.y >= 0 && m_hot.x >= 0)
				if(m_samegame->pCells[point.y][point.x].color == m_samegame->pCells[m_hot.y][m_hot.x].color)
					return;

			int c = 0;
			m_samegame->Zero();
			m_samegame->Find(point.y,point.x,c);
			
			if(c <= 1 )
			{
				point.x = -1;
				point.y = -1;
			}
			m_hot = point;
			Invalidate();
		}
		else
		{
			if(m_hot.y >= 0 && m_hot.x >= 0)
			{
				m_hot.x = -1;
				m_hot.y = -1;
				Invalidate();
			}
		}	
	}
}

void CSameGameView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	point.x = point.x/23;
	point.y = point.y/23;

	if((point.x >=0 && point.y >= 0) && (point.x <15 && point.y < 10 ))
	{
		int c = 0;
		m_samegame->Zero();
		m_samegame->Find(point.y,point.x,c);

		if(c > 1 )
		{
			//TODO: Queda por hacer la animacion de la eliminacion
			m_samegame->Delete(point.y,point.x,c);
			m_samegame->ReorganizeV();
			m_samegame->ReorganizeH();
			m_samegame->points += (int)pow((c-2),2);

			if(m_hot.y >= 0 && m_hot.x >= 0)
			{
				
				m_samegame->Zero();
				m_samegame->Find(m_hot.y,m_hot.x,c);

				if(c <= 1)
				{
					m_hot.x = -1;
					m_hot.y = -1;
				}

				m_samegame->Find(c);
				if(c <= 1)
				{
					if(c == 0)
					{
						m_samegame->points += 1000;
					}
					m_bGameEnded = true;
					MessageBox("Game Over!");
				}
				CMainFrame *wnd = (CMainFrame *)AfxGetMainWnd();
				m_msg.Format("Score : %d",m_samegame->points);
				wnd->m_wndStatusBar.SetPaneText(0,m_msg);

			}
			Invalidate();
		}
	}	
}
