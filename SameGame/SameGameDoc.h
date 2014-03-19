// SameGameDoc.h : interface of the CSameGameDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMEGAMEDOC_H__2C0ABB2C_6BE4_4971_A131_0FEF2818A405__INCLUDED_)
#define AFX_SAMEGAMEDOC_H__2C0ABB2C_6BE4_4971_A131_0FEF2818A405__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSameGameDoc : public CDocument
{
protected: // create from serialization only
	CSameGameDoc();
	DECLARE_DYNCREATE(CSameGameDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSameGameDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSameGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSameGameDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMEGAMEDOC_H__2C0ABB2C_6BE4_4971_A131_0FEF2818A405__INCLUDED_)
