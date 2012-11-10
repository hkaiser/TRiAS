// abfalset.cpp : implementation of the CAbfallSet class
//

#include "stdafx.h"		//	prec. Header
#include "res.h"		//	Resource-Konstanten	
#include "recset.h"		//	CRecordsetExt
#include "abfalset.h"	// 	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAbfallSet implementation

IMPLEMENT_DYNAMIC(CAbfallSet, CRecordsetExt)

CAbfallSet::CAbfallSet(CDatabase* pdb)
		   :CRecordsetExt(pdb)
{
	//{{AFX_FIELD_INIT(CAbfallSet)
	m_strNummer = _T("");
	m_strAbfallnummer = _T("");
	m_strTransporteurnummer = _T("");
	m_strEntsorgernummer = _T("");
	m_dMenge_t = 0.0;
	m_strEntsorgungsverfahren = _T("");
	m_strNachweisnummer = _T("");
	m_strPrioritaet = _T("");
	m_bBearbeitet = FALSE;
	m_strEntsorgerBemerkung = _T("");
	m_strTransportBemerkung = _T("");;

	m_nFields = 11;
	//}}AFX_FIELD_INIT
	              
	m_strErzNrParam = "";	              
	m_strAsnParam = "";
	m_nParams = 2;

	VERIFY (m_strSort.LoadString (IDS_ABF_NR));
	VERIFY (m_strFilter.LoadString (IDS_ERZ_ASN_FILTER));
}

CString CAbfallSet::GetDefaultConnect()
{
	ASSERT (FALSE);
	return "";
}

CString CAbfallSet::GetDefaultSQL()
{      
	ASSERT (!m_strTableName.IsEmpty ());
	CString strSelect;
	AfxFormatString1 (strSelect, IDS_ERZEUGER_SELECT, m_strTableName);
	return strSelect;
}

void CAbfallSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAbfallSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Nummer]"), m_strNummer);
	RFX_Text(pFX, _T("[Abfallnummer]"), m_strAbfallnummer);
	RFX_Text(pFX, _T("[Transporteurnummer]"), m_strTransporteurnummer);
	RFX_Text(pFX, _T("[Entsorgernummer]"), m_strEntsorgernummer);
	RFX_Double(pFX, _T("[Menge_t]"), m_dMenge_t);
	RFX_Text(pFX, _T("[Entsorgungsverfahren]"), m_strEntsorgungsverfahren);
	RFX_Text(pFX, _T("[Nachweisnummer]"), m_strNachweisnummer);
	RFX_Text(pFX, _T("[Prioritaet]"), m_strPrioritaet);
	RFX_Bool(pFX, _T("[Bearbeitet]"), m_bBearbeitet);
	RFX_Text(pFX, _T("[Transporteurbemerkungen]"), m_strTransportBemerkung);
	RFX_Text(pFX, _T("[Entsorgerbemerkungen]"), m_strEntsorgerBemerkung);
	//}}AFX_FIELD_MAP

	if (m_nParams > 0)
	{	                    
		pFX->SetFieldType(CFieldExchange::param);
		RFX_Text(pFX, "Nummer", m_strErzNrParam, sMaxErzNrLen);

		if (m_nParams > 1)
			RFX_Text(pFX, "Abfallnummer", m_strAsnParam, sMaxAsnNrLen);
	}
}
