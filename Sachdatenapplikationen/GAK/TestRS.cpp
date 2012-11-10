// TestRS.cpp : implementation file
//

#include "stdafx.h"
#include "gak.h"
#include "TestRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestRS

IMPLEMENT_DYNAMIC(CTestRS, CRecordset)

CTestRS::CTestRS(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CTestRS)
	m_Prioritaet = _T("");
	m_Bearbeitet = FALSE;
	m_Nummer = _T("");
	m_Abfallnummer = _T("");
	m_Transporteurnummer = _T("");
	m_Entsorgernummer = _T("");
	m_Vorbehandlung = _T("");
	m_Menge_t = 0.0;
	m_Verbringungscode = _T("");
	m_Abfallbezeichnung = _T("");
	m_Betreibernummer = _T("");
	m_Eigentransport = FALSE;
	m_Entsorgungsverfahren = _T("");
	m_Eigenentsorgung = FALSE;
	m_Entsorgungspartner = _T("");
	m_Entsorgungstelefon = _T("");
	m_Entsorgungstelefax = _T("");
	m_Entsorgungsfreistellung = FALSE;
	m_Freistellungsnummer = _T("");
	m_Betreiberbemerkungen = _T("");
	m_Transporteurbemerkungen = _T("");
	m_Entsorgerbemerkungen = _T("");
	m_Bemerkungen = _T("");
	m_ro = FALSE;
	m_user = _T("");
	m_EAKNummer = _T("");
	m_Nachweisnummer = _T("");
	m_Exportiert = _T("");
	m_nFields = 30;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CTestRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=Gak32");
}

CString CTestRS::GetDefaultSQL()
{
	return _T("[Abfaelle]");
}

void CTestRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CTestRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Prioritaet]"), m_Prioritaet);
	RFX_Bool(pFX, _T("[Bearbeitet]"), m_Bearbeitet);
	RFX_Text(pFX, _T("[Nummer]"), m_Nummer);
	RFX_Text(pFX, _T("[Abfallnummer]"), m_Abfallnummer);
	RFX_Text(pFX, _T("[Transporteurnummer]"), m_Transporteurnummer);
	RFX_Text(pFX, _T("[Entsorgernummer]"), m_Entsorgernummer);
	RFX_Text(pFX, _T("[Vorbehandlung]"), m_Vorbehandlung);
	RFX_Double(pFX, _T("[Menge_t]"), m_Menge_t);
	RFX_Text(pFX, _T("[Verbringungscode]"), m_Verbringungscode);
	RFX_Text(pFX, _T("[Abfallbezeichnung]"), m_Abfallbezeichnung);
	RFX_Text(pFX, _T("[Betreibernummer]"), m_Betreibernummer);
	RFX_Bool(pFX, _T("[Eigentransport]"), m_Eigentransport);
	RFX_Text(pFX, _T("[Entsorgungsverfahren]"), m_Entsorgungsverfahren);
	RFX_Bool(pFX, _T("[Eigenentsorgung]"), m_Eigenentsorgung);
	RFX_Text(pFX, _T("[Entsorgungspartner]"), m_Entsorgungspartner);
	RFX_Text(pFX, _T("[Entsorgungstelefon]"), m_Entsorgungstelefon);
	RFX_Text(pFX, _T("[Entsorgungstelefax]"), m_Entsorgungstelefax);
	RFX_Bool(pFX, _T("[Entsorgungsfreistellung]"), m_Entsorgungsfreistellung);
	RFX_Text(pFX, _T("[Freistellungsnummer]"), m_Freistellungsnummer);
	RFX_Text(pFX, _T("[Betreiberbemerkungen]"), m_Betreiberbemerkungen);
	RFX_Text(pFX, _T("[Transporteurbemerkungen]"), m_Transporteurbemerkungen);
	RFX_Text(pFX, _T("[Entsorgerbemerkungen]"), m_Entsorgerbemerkungen);
	RFX_Text(pFX, _T("[Bemerkungen]"), m_Bemerkungen);
	RFX_Date(pFX, _T("[Erfassungsdatum]"), m_Erfassungsdatum);
	RFX_Date(pFX, _T("[Aenderungsdatum]"), m_Aenderungsdatum);
	RFX_Bool(pFX, _T("[ro]"), m_ro);
	RFX_Text(pFX, _T("[user]"), m_user);
	RFX_Text(pFX, _T("[EAKNummer]"), m_EAKNummer);
	RFX_Text(pFX, _T("[Nachweisnummer]"), m_Nachweisnummer);
	RFX_Text(pFX, _T("[Exportiert]"), m_Exportiert);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTestRS diagnostics

#ifdef _DEBUG
void CTestRS::AssertValid() const
{
	CRecordset::AssertValid();
}

void CTestRS::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
