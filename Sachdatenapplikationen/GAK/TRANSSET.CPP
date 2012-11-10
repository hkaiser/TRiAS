// TransSet.cpp : implementation file
//
#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp u. Ressourcen
#include "selset.h"		// CSelectSet: Basisklasse
#include "TransSet.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTranspSet

IMPLEMENT_DYNAMIC(CTranspSet, CSelectSet)

CTranspSet :: CTranspSet (CDaoDatabase* pdb, const char *pTableName)
		    : CSelectSet (pdb, pTableName)
{
	//{{AFX_FIELD_INIT(CTranspSet)
	m_Strasse = _T("");
	m_Ortsname = _T("");
	m_Postleitzahl = _T("");
	//}}AFX_FIELD_INIT
	m_nFields += 3;
	m_nDefaultType = dbOpenSnapshot;
}

void CTranspSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
//	zuerst Basisklasse rufen
	CSelectSet :: DoFieldExchange (pFX);

	//{{AFX_FIELD_MAP(CTranspSet)
	DFX_Text(pFX, _T("[Strasse]"), m_Strasse);
	DFX_Text(pFX, _T("[Ortsname]"), m_Ortsname);
	DFX_Text(pFX, _T("[Postleitzahl]"), m_Postleitzahl);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTranspSet diagnostics

#ifdef _DEBUG
void CTranspSet::AssertValid() const
{
	CSelectSet::AssertValid();
}

void CTranspSet::Dump(CDumpContext& dc) const
{
	CSelectSet::Dump(dc);
}
#endif //_DEBUG

CString CTranspSet::GetDefaultSQL() 
{
// TODO: Add your specialized code here and/or call the base class
	ASSERT (!m_strTableName.IsEmpty ());	
	CString strSQL, strWhere;

//	ggf. Where-Klausel einbauen
	if (((CGakApp *)AfxGetApp ()) -> OnlyValidTransporteure ())
	{
		COleDateTime OleDate (COleDateTime::GetCurrentTime());
		CString strDate (OleDate.Format ((UINT) IDS_DATE_FORMAT));
		AfxFormatString1 (strWhere, IDS_TRANS_WHERE, strDate);
	}

//	SELECT Nummer,Name,Ortsname,Postleitzahl,Strasse FROM [%1] %2 ORDER BY Nummer
	AfxFormatString2 (strSQL, IDS_TRANSP_SELECT, m_strTableName, strWhere);
	return strSQL;
}
