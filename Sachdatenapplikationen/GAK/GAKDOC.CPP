// gakDoc.cpp : implementation of the CGakDoc class
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// Resourcen

#include "gaksete.h"	// CDaoRecordsetExt
#include "gakSet.h"		// CGakSet
#include "documext.h"	// CDocumentExt
#include "gakDoc.h"		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGakDoc

IMPLEMENT_DYNCREATE(CGakDoc, CDocument)

BEGIN_MESSAGE_MAP(CGakDoc, CDocumentExt)
	//{{AFX_MSG_MAP(CGakDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGakDoc
CGakDoc :: CGakDoc ()
		 : CDocumentExt (IDS_EINGABE_STD)
{
}

BOOL CGakDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGakDoc diagnostics

#ifdef _DEBUG
void CGakDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGakDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGakDoc commands

void CGakDoc::SetTitle(LPCTSTR lpszTitle) 
{
//	TODO: Add your specialized code here and/or call the base class
	ASSERT_VALID (&m_gakSet);
	CDocumentExt :: SetTitle (m_gakSet.m_Nummer);
}
