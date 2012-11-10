// outset.cpp : implementation of the COutputSet class
//

#include "stdafx.h"		//	prec. Header
#include "res.h"		//	Ressourcen
#include "outset.h"		// 	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputSet implementation

IMPLEMENT_DYNAMIC(COutputSet, CRecordset)

COutputSet :: COutputSet(CDatabase* pdb)
			: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(COutputSet)
	m_strNummer = _T("");
	m_strAbfallnummer = _T("");
	m_strTransporteurnummer = _T("");
	m_strEntsorgernummer = _T("");
	m_dMenge_t = 0.0;
	m_strEntsorgungsverfahren = _T("");
	m_strNachweisnummer = _T("");
	m_strPrioritaet = _T("");
	m_bBearbeitet = FALSE;
	m_nFields = 10;
	//}}AFX_FIELD_INIT                         
	                  
//	aktuelles Eingabedatum setzen	                  
	m_tErfassungsdatum = CTime::GetCurrentTime();
}

COutputSet::~COutputSet (void)
{
	if (IsOpen ())
		Close ();
}	

CString COutputSet::GetDefaultConnect()
{
	ASSERT (FALSE);
	return "";
}

CString COutputSet::GetDefaultSQL()
{      
	ASSERT (!m_strTableName.IsEmpty ());
	CString strS;
	AfxFormatString1 (strS, IDS_OUTPUT_SET, m_strTableName);
	return strS;
}

void COutputSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(COutputSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Nummer]"), m_strNummer);
	RFX_Text(pFX, _T("[Abfallnummer]"), m_strAbfallnummer);
	RFX_Text(pFX, _T("[Transporteurnummer]"), m_strTransporteurnummer);
	RFX_Text(pFX, _T("[Entsorgernummer]"), m_strEntsorgernummer);
	RFX_Double(pFX, _T("[Menge_t]"), m_dMenge_t);
	RFX_Text(pFX, _T("[Entsorgungsverfahren]"), m_strEntsorgungsverfahren);
	RFX_Date(pFX, _T("[Erfassungsdatum]"), m_tErfassungsdatum);
	RFX_Text(pFX, _T("[Nachweisnummer]"), m_strNachweisnummer);
	RFX_Text(pFX, _T("[Prioritaet]"), m_strPrioritaet);
	RFX_Bool(pFX, _T("[Bearbeitet]"), m_bBearbeitet);
	//}}AFX_FIELD_MAP
}
