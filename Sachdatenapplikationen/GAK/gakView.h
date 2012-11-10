#ifndef __GAKVIEW_H__FILE
#define __GAKVIEW_H__FILE
// gakView.h : interface of the CGakView class
//
/////////////////////////////////////////////////////////////////////////////


class CGakDoc;

#include "recview.h"

class CGakView : public CDaoRecordViewExt
{
public:
	DECLARE_DYNCREATE(CGakView)
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGakView)
	public:
	virtual CDaoRecordset* OnGetRecordset();
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CGakDoc* GetDocument();

protected:
// Generated message map functions
	//{{AFX_MSG(CGakView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDeleteRekord();
	afx_msg void OnHelpDatabaseErrors();
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void Print (BOOL bOnDrucker);		//	View ausgeben
	virtual BOOL OnMoveExt(UINT nIDMoveCommand);
	virtual void Sync();

public:
	static void ExtSync();
};

#ifndef _DEBUG  // debug version in gakView.cpp
inline CGakDoc* CGakView::GetDocument()
   { return (CGakDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

#endif //__GAKVIEW_H__FILE