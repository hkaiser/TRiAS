// DocumExt.cpp : implementation file
//

#include "stdafx.h"			// prec. Header
#include "gak.h"			// CGakApp
#include "childfrm.h"		// CChildFrame
#include "DocumExt.h"		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDocumentExt

// IMPLEMENT_DYNCREATE(CDocumentExt, CDocument)

BEGIN_MESSAGE_MAP(CDocumentExt, CDocument)
	//{{AFX_MSG_MAP(CDocumentExt)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDocumentExt diagnostics

#ifdef _DEBUG
void CDocumentExt::AssertValid() const
{
	CDocument::AssertValid();
}

void CDocumentExt::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDocumentExt commands
void CDocumentExt::SetTitle(LPCTSTR lpszTitle) 
{
	// TODO: Add your specialized code here and/or call the base class
	ASSERT (NULL != lpszTitle && AfxIsValidString (lpszTitle));

	try
	{
		CString strKeine, strCaption;
		if (!*lpszTitle)
			VERIFY (strKeine.LoadString (IDS_KEINE));

		AfxFormatString1 (strCaption, m_uiCaptionID, strKeine.IsEmpty () ? lpszTitle : strKeine);
		CDocument :: SetTitle (strCaption);
	}
	catch (CMemoryException *me)
	{
		me -> ReportError ();
		me -> Delete ();
	}
}

