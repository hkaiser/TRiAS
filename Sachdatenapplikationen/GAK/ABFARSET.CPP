// AbfArSet.cpp : implementation file
//

#include "stdafx.h"			// prec. Header
#include "gak.h"			// CGakApp u. Ressourcen
#include "selset.h"			// CSelectSet
#include "AbfArSet.h"		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAbfArtSet
IMPLEMENT_DYNAMIC(CAbfArtSet, CDaoRecordset)

CAbfArtSet :: CAbfArtSet (CDaoDatabase* pdb, const char *pTableName)
		    : CSelectSet (pdb, pTableName)
{
	//{{AFX_FIELD_INIT(CAbfArtSet)
	m_Sonderabfall = FALSE;
	m_Dichte = 0.0f;
	//}}AFX_FIELD_INIT
	m_nFields += 2;
}

CString CAbfArtSet::GetDefaultSQL()
{
	// return _T("[Abfallarten]");
	ASSERT (!m_strTableName.IsEmpty ());
	CString strSel;
	AfxFormatString1 (strSel, IDS_SEL_ABF_ARTEN, m_strTableName);
	return strSel;
}

void CAbfArtSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAbfArtSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Bool(pFX, _T("[Sonderabfall]"), m_Sonderabfall);
	DFX_Single(pFX, _T("[Dichte]"), m_Dichte);
	//}}AFX_FIELD_MAP
	CSelectSet :: DoFieldExchange(pFX);	// Basisklasse rufen
}

/////////////////////////////////////////////////////////////////////////////
// CAbfArtSet diagnostics

#ifdef _DEBUG
void CAbfArtSet::AssertValid() const
{
	CSelectSet::AssertValid();
}

void CAbfArtSet::Dump(CDumpContext& dc) const
{
	CSelectSet::Dump(dc);
}
#endif //_DEBUG


