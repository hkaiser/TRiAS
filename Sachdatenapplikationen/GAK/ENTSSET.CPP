// EntsSet.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp u. Ressourcen
#include "selset.h"		// CSelectSet: Basisklasse
#include "EntsSet.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEntsorgerSet

IMPLEMENT_DYNAMIC(CEntsorgerSet, CSelectSet)

CEntsorgerSet :: CEntsorgerSet (CDaoDatabase* pdb, const char *pTableName)
			   : CSelectSet (pdb, pTableName)
{
	//{{AFX_FIELD_INIT(CEntsorgerSet)
	m_Anlage = _T("");
	m_Strasse = _T("");
	m_Ortsname = _T("");
	m_Postleitzahl = _T("");
	//}}AFX_FIELD_INIT
	m_nFields += 4;
	m_nDefaultType = dbOpenSnapshot;
}

CString CEntsorgerSet::GetDefaultSQL()
{
	ASSERT (!m_strTableName.IsEmpty ());	
	CString strSQL, strWhere;

//	ggf. Where-Klausel einbauen
	if (((CGakApp*)AfxGetApp ()) -> OnlyValidEntsorger ())
		VERIFY (strWhere.LoadString (IDS_ENTS_WHERE));

	//	SELECT Nummer,Name,Ortsname,Postleitzahl,Strasse,Anlage FROM [%1] %2 ORDER BY Nummer
	AfxFormatString2 (strSQL, IDS_ENTS_SELECT, m_strTableName, strWhere);
	return strSQL;
}

void CEntsorgerSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//	zuerst Basisklasse rufen
	CSelectSet :: DoFieldExchange (pFX);

	//{{AFX_FIELD_MAP(CEntsorgerSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Anlage]"), m_Anlage);
	DFX_Text(pFX, _T("[Strasse]"), m_Strasse);
	DFX_Text(pFX, _T("[Ortsname]"), m_Ortsname);
	DFX_Text(pFX, _T("[Postleitzahl]"), m_Postleitzahl);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CEntsorgerSet diagnostics
#ifdef _DEBUG
void CEntsorgerSet::AssertValid() const
{
	CSelectSet::AssertValid();
}

void CEntsorgerSet::Dump(CDumpContext& dc) const
{
	CSelectSet::Dump(dc);
}
#endif //_DEBUG
