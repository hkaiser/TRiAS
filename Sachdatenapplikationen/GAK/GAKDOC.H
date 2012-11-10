#ifndef __GAKDOC_H__FILE
#define __GAKDOC_H__FILE
// gakDoc.h : interface of the CGakDoc class
//
/////////////////////////////////////////////////////////////////////////////

#include "GakView.h"

class CGakDoc : public CDocumentExt
{
protected: // create from serialization only
	CGakDoc();
	DECLARE_DYNCREATE(CGakDoc)

// Attributes
public:
	CGakSet m_gakSet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGakDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void SetTitle(LPCTSTR lpszTitle);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGakDoc() 
	{}
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGakDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif //__GAKDOC_H__FILE