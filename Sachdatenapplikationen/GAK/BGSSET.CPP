// bgsset.cpp : implementation of the CBgsSet class
//

#include "stdafx.h"		//	prec. Header
#include "res.h"		//	Resource-Konstanten	
#include "recset.h"		//	CRecordsetExt
#include "bgsset.h"		//	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBgsSet implementation

IMPLEMENT_DYNAMIC(CBgsSet, CRecordsetExt)

CBgsSet::CBgsSet(CDatabase* pdb)
		: CRecordsetExt(pdb)
{
	//{{AFX_FIELD_INIT(CBgsSet)
	m_strAbfallschluesselnummer = _T("");
	m_bBearbeitet = FALSE;
	m_strBefoerderernummer = _T("");
	m_strEntsorgernummer = _T("");
	m_strEntsorgungsverfahren = _T("");
	m_strErzeugernummer = _T("");
	m_dMenge = 0.0;
	m_dMenge_en = 0.0;
	m_strNachweisnummer = _T("");
	m_strPrioritaet = _T("");
	m_nFields = 10;
	//}}AFX_FIELD_INIT
	              
	m_strErzNrParam = "";	              
	m_strAsnParam = "";
	m_nParams = 2;

	VERIFY (m_strSort.LoadString (IDS_ASN_NR));
	VERIFY (m_strFilter.LoadString (IDS_BGS_ERZ_ASN_FILTER));
}   

CString CBgsSet::GetDefaultConnect()
{
	ASSERT (FALSE);
	return "";
}

CString CBgsSet::GetDefaultSQL()
{                         
	ASSERT (!m_strTableName.IsEmpty ());
	return m_strTableName;
}

void CBgsSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CBgsSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Abfallschluesselnummer]"), m_strAbfallschluesselnummer);
	RFX_Text(pFX, _T("[Befoerderernummer]"), m_strBefoerderernummer);
	RFX_Text(pFX, _T("[Entsorgernummer]"), m_strEntsorgernummer);
	RFX_Text(pFX, _T("[Entsorgungsverfahren]"), m_strEntsorgungsverfahren);
	RFX_Text(pFX, _T("[Erzeugernummer]"), m_strErzeugernummer);
	RFX_Double(pFX, _T("[Menge]"), m_dMenge);
	RFX_Double(pFX, _T("[Menge_en]"), m_dMenge_en);
	RFX_Text(pFX, _T("[Nachweisnummer]"), m_strNachweisnummer);
	RFX_Bool(pFX, _T("[Bearbeitet]"), m_bBearbeitet);
	RFX_Text(pFX, _T("[Prioritaet]"), m_strPrioritaet);

	//}}AFX_FIELD_MAP

	if (m_nParams > 0)
	{	                                                
		pFX->SetFieldType(CFieldExchange::param);	                                                
		RFX_Text(pFX, "Erzeugernummer", m_strErzNrParam, sMaxErzNrLen);

		if (m_nParams > 1)
			RFX_Text(pFX, "Abfallschluesselnummer", m_strAsnParam, sMaxAsnNrLen);
	}		
}
/////////////////////////////////////////////////////////////////////////////
// CBgsSetRed
IMPLEMENT_DYNAMIC(CBgsSetRed, CRecordset)

CBgsSetRed::CBgsSetRed(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CBgsSetRed)
	m_Erzeugernummer = _T("");
	m_Abfallschluesselnummer = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString CBgsSetRed::GetDefaultConnect()
{
	ASSERT (FALSE);
	return "";
}

CString CBgsSetRed::GetDefaultSQL()
{
	ASSERT (FALSE);
	return "";
}

void CBgsSetRed::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CBgsSetRed)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Nummer]"), m_Erzeugernummer);
	RFX_Text(pFX, _T("[Abfallnummer]"), m_Abfallschluesselnummer);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CBgsSetRed diagnostics

#ifdef _DEBUG
void CBgsSetRed::AssertValid() const
{
	CRecordset::AssertValid();
}

void CBgsSetRed::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
