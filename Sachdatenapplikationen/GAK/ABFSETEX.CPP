// AbfSetEx.cpp : implementation file
//
#include "stdafx.h"		//	prec. Header
#include "gak.h"		//	CGakApp

#include "AbfSetEx.h"	//	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAbfSetExport

IMPLEMENT_DYNAMIC(CAbfSetExport, CDaoRecordset)

CAbfSetExport::CAbfSetExport(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CAbfSetExport)
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
	m_nFields = 28;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}

CString CAbfSetExport::GetDefaultDBName()
{
	ASSERT (FALSE);
	return _T("C:\\GAK\\WIN32\\DATEN\\Gak.mdb");
}

CString CAbfSetExport::GetDefaultSQL()
{
	return ((CGakApp *)AfxGetApp ()) -> AbfallDefaultSQL ();
}

void CAbfSetExport::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAbfSetExport)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Nummer]"), m_Nummer);
	DFX_Text(pFX, _T("[Abfallnummer]"), m_Abfallnummer);
	DFX_Text(pFX, _T("[Transporteurnummer]"), m_Transporteurnummer);
	DFX_Text(pFX, _T("[Entsorgernummer]"), m_Entsorgernummer);
	DFX_Text(pFX, _T("[Vorbehandlung]"), m_Vorbehandlung);
	DFX_Double(pFX, _T("[Menge_t]"), m_Menge_t);
	DFX_Text(pFX, _T("[Verbringungscode]"), m_Verbringungscode);
	DFX_Text(pFX, _T("[Abfallbezeichnung]"), m_Abfallbezeichnung);
	DFX_Text(pFX, _T("[Betreibernummer]"), m_Betreibernummer);
	DFX_Bool(pFX, _T("[Eigentransport]"), m_Eigentransport);
	DFX_Text(pFX, _T("[Entsorgungsverfahren]"), m_Entsorgungsverfahren);
	DFX_Bool(pFX, _T("[Eigenentsorgung]"), m_Eigenentsorgung);
	DFX_Text(pFX, _T("[Entsorgungspartner]"), m_Entsorgungspartner);
	DFX_Text(pFX, _T("[Entsorgungstelefon]"), m_Entsorgungstelefon);
	DFX_Text(pFX, _T("[Entsorgungstelefax]"), m_Entsorgungstelefax);
	DFX_Bool(pFX, _T("[Entsorgungsfreistellung]"), m_Entsorgungsfreistellung);
	DFX_Text(pFX, _T("[Freistellungsnummer]"), m_Freistellungsnummer);
	DFX_Text(pFX, _T("[Betreiberbemerkungen]"), m_Betreiberbemerkungen);
	DFX_Text(pFX, _T("[Transporteurbemerkungen]"), m_Transporteurbemerkungen);
	DFX_Text(pFX, _T("[Entsorgerbemerkungen]"), m_Entsorgerbemerkungen);
	DFX_Text(pFX, _T("[Bemerkungen]"), m_Bemerkungen);
	DFX_DateTime(pFX, _T("[Erfassungsdatum]"), m_Erfassungsdatum);
	DFX_DateTime(pFX, _T("[Aenderungsdatum]"), m_Aenderungsdatum);
	DFX_Bool(pFX, _T("[ro]"), m_ro);
	DFX_Text(pFX, _T("[user]"), m_user);
	DFX_Text(pFX, _T("[EAKNummer]"), m_EAKNummer);
	DFX_Text(pFX, _T("[Nachweisnummer]"), m_Nachweisnummer);
	DFX_Text(pFX, _T("[Exportiert]"), m_Exportiert);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CAbfSetExport diagnostics

#ifdef _DEBUG
void CAbfSetExport::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CAbfSetExport::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG

BOOL CAbfSetExport::operator = (const CAbfSetExport& InSet)
{                                                       
//	prüfe Parameter
	ASSERT (IsOpen ());
	ASSERT (InSet.IsOpen ());
	
//	Felder kopieren
	m_Nummer = InSet.m_Nummer;
	m_Abfallnummer = InSet.m_Abfallnummer;
	m_Transporteurnummer = InSet.m_Transporteurnummer;
	m_Entsorgernummer = InSet.m_Entsorgernummer;
	m_Vorbehandlung = InSet.m_Vorbehandlung;
	m_Menge_t = InSet.m_Menge_t;
	m_Verbringungscode = InSet.m_Verbringungscode;
	m_Abfallbezeichnung = InSet.m_Abfallbezeichnung;
	m_Betreibernummer = InSet.m_Betreibernummer;
	m_Eigentransport = InSet.m_Eigentransport;
	m_Entsorgungsverfahren = InSet.m_Entsorgungsverfahren;
	m_Eigenentsorgung = InSet.m_Eigenentsorgung;
	m_Entsorgungspartner = InSet.m_Entsorgungspartner;
	m_Entsorgungstelefon = InSet.m_Entsorgungstelefon;
	m_Entsorgungstelefax = InSet.m_Entsorgungstelefax;
	m_Entsorgungsfreistellung = InSet.m_Entsorgungsfreistellung;
	m_Freistellungsnummer = InSet.m_Freistellungsnummer;
	m_Betreiberbemerkungen = InSet.m_Betreiberbemerkungen;
	m_Transporteurbemerkungen = InSet.m_Transporteurbemerkungen;
	m_Entsorgerbemerkungen = InSet.m_Entsorgerbemerkungen;
	m_Bemerkungen = InSet.m_Bemerkungen;
	m_Erfassungsdatum = InSet.m_Erfassungsdatum;
	m_Aenderungsdatum = InSet.m_Aenderungsdatum;
	m_user = InSet.m_user;
	m_ro = FALSE;         
	m_EAKNummer = InSet.m_EAKNummer;
	m_Nachweisnummer = InSet.m_Nachweisnummer;	
	m_Exportiert = InSet.m_Exportiert;
	
	return TRUE;
}
