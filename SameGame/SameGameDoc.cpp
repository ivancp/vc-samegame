// SameGameDoc.cpp : implementation of the CSameGameDoc class
//

#include "stdafx.h"
#include "SameGame.h"

#include "SameGameDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSameGameDoc

IMPLEMENT_DYNCREATE(CSameGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CSameGameDoc, CDocument)
	//{{AFX_MSG_MAP(CSameGameDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSameGameDoc construction/destruction

CSameGameDoc::CSameGameDoc()
{
	// TODO: add one-time construction code here

}

CSameGameDoc::~CSameGameDoc()
{
}

BOOL CSameGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSameGameDoc serialization

void CSameGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSameGameDoc diagnostics

#ifdef _DEBUG
void CSameGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSameGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSameGameDoc commands
