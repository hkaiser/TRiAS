// AbfDoc.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp
#include "gaksete.h"	// CDaoRecordsetExt
#include "abfset.h"		// CAbfSet	
#include "documext.h"	// CDocumentExt
#include "AbfDoc.h"		// zug. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "GakSet.h"
extern CGakSet * g_pErzSet;

/////////////////////////////////////////////////////////////////////////////
// CAbfDoc

IMPLEMENT_DYNCREATE(CAbfDoc, CDocument)
CAbfDoc :: CAbfDoc ()
		 : CDocumentExt (IDS_ABFALL_DATEN_CAPT)
{
}

BOOL CAbfDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

BEGIN_MESSAGE_MAP(CAbfDoc, CDocumentExt)
	//{{AFX_MSG_MAP(CAbfDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAbfDoc diagnostics

#ifdef _DEBUG
void CAbfDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAbfDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAbfDoc commands

void CAbfDoc::SetTitle(LPCTSTR) 
{
	ASSERT_VALID (&m_AbfSet);
#pragma MSG("JG SetCaption for invalid Data")
	if (m_AbfSet.IsValid())
	{
		if (!m_AbfSet.m_Nummer.IsEmpty () && !m_AbfSet.m_Abfallnummer.IsEmpty ())
		{
			CString strCaption;
			AfxFormatString2 (strCaption, IDS_ABF_CAPT_FORMAT, m_AbfSet.m_Nummer, m_AbfSet.m_Abfallnummer);						  
			CDocumentExt :: SetTitle (strCaption);
		}
		else
			CDocumentExt :: SetTitle (m_AbfSet.m_Nummer);
	}
	else
	{
		// kein DS selektiert, also leere Überschrift anzeigen
			if (NULL != g_pErzSet)
				CDocumentExt :: SetTitle (g_pErzSet->m_Nummer);
			else
				CDocumentExt :: SetTitle (_T(""));
	}
}

