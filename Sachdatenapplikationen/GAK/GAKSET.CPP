// gakSet.cpp : implementation of the CGakSet class
//

#include "stdafx.h"			// prec. Header
#include "gak.h"			// Resourcekonstanten
#include "gaksete.h"		// CDaoRecordsetExt
#include "gakSet.h"			// zugeh. Header
#include "gakview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// globale Variablen
CGakSet *g_pErzSet = NULL;

//	globale Funktionen (ohne TRY/CATCH)
void CALLBACK SetBranchenNummer (LPARAM lParam)
{
	ASSERT (NULL != g_pErzSet);
	g_pErzSet -> m_Branchennummer = (const char *) lParam;
}

/////////////////////////////////////////////////////////////////////////////
// CGakSet implementation
IMPLEMENT_DYNAMIC(CGakSet, CDaoRecordsetExt)

CGakSet::CGakSet(CDaoDatabase* pdb)
	    : CDaoRecordsetExt(IDS_ERZ_PRIM_INDEX,
						  ((CGakApp *) AfxGetApp ()) -> ErzeugerDefaultSQL (), pdb)
{
	//{{AFX_FIELD_INIT(CGakSet)
	m_Anfallstelle = _T("");
	m_Ansprechpartner = _T("");
	m_Antragsnummer = _T("");
	m_Anzeigenachweisverordnung = FALSE;
	m_Bemerkungen = _T("");
	m_Betreibernummer = _T("");
	m_Betriebsbeauftragtennummer = 0;
	m_Betriebsbeauftragtentelefax = _T("");
	m_Betriebsbeauftragtentelefon = _T("");
	m_Betriebsbeauftragter = _T("");
	m_Betriebsstaette = _T("");
	m_Bilanznummer = _T("");
	m_Bimschgenehmigungsnummer = _T("");
	m_Bimschnummer = _T("");
	m_Bimschspalte = _T("");
	m_Branchennummer = _T("");
	m_Firmenansprechpartner = _T("");
	m_Partnerfunktion = _T("");
	m_Firmenhausnummer = _T("");
	m_Firmenname = _T("");
	m_Firmenortsname = _T("");
	m_Firmenpostleitzahl = _T("");
	m_Firmenstrasse = _T("");
	m_Firmentelefax = _T("");
	m_Firmentelefon = _T("");
	m_Gemeindekennzahl = _T("");
	m_Hausnummer = _T("");
	m_Ortsname = _T("");
	m_Partnertelefax = _T("");
	m_Partnertelefon = _T("");
	m_Postleitzahl = _T("");
	m_Strasse = _T("");
	m_Exportiert = _T("");
	m_EDV = _T("");
	m_EDVSonstige = _T("");
	m_Unterschrift = FALSE;
	//}}AFX_FIELD_INIT
	m_nFields += 36;
	
	g_pErzSet = this;						// globale Variable setzen
}

CGakSet::~CGakSet (void)
{
	g_pErzSet = NULL;

	// die Views synchronisieren
	CGakView::ExtSync();
}

void CGakSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CGakSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Anfallstelle]"), m_Anfallstelle);
	DFX_Text(pFX, _T("[Ansprechpartner]"), m_Ansprechpartner);
	DFX_Text(pFX, _T("[Antragsnummer]"), m_Antragsnummer);
	DFX_Bool(pFX, _T("[Anzeigenachweisverordnung]"), m_Anzeigenachweisverordnung);
	DFX_Text(pFX, _T("[Bemerkungen]"), m_Bemerkungen);
	DFX_Text(pFX, _T("[Betreibernummer]"), m_Betreibernummer);
	DFX_Long(pFX, _T("[Betriebsbeauftragtennummer]"), m_Betriebsbeauftragtennummer);
	DFX_Text(pFX, _T("[Betriebsbeauftragtentelefax]"), m_Betriebsbeauftragtentelefax);
	DFX_Text(pFX, _T("[Betriebsbeauftragtentelefon]"), m_Betriebsbeauftragtentelefon);
	DFX_Text(pFX, _T("[Betriebsbeauftragter]"), m_Betriebsbeauftragter);
	DFX_Text(pFX, _T("[Betriebsstaette]"), m_Betriebsstaette);
	DFX_Text(pFX, _T("[Bilanznummer]"), m_Bilanznummer);
	DFX_Text(pFX, _T("[Bimschgenehmigungsnummer]"), m_Bimschgenehmigungsnummer);
	DFX_Text(pFX, _T("[Bimschnummer]"), m_Bimschnummer);
	DFX_Text(pFX, _T("[Bimschspalte]"), m_Bimschspalte);
	DFX_Text(pFX, _T("[Branchennummer]"), m_Branchennummer);
	DFX_Text(pFX, _T("[Firmenansprechpartner]"), m_Firmenansprechpartner);
	DFX_Text(pFX, _T("[Partnerfunktion]"), m_Partnerfunktion);
	DFX_Text(pFX, _T("[Firmenhausnummer]"), m_Firmenhausnummer);
	DFX_Text(pFX, _T("[Firmenname]"), m_Firmenname);
	DFX_Text(pFX, _T("[Firmenortsname]"), m_Firmenortsname);
	DFX_Text(pFX, _T("[Firmenpostleitzahl]"), m_Firmenpostleitzahl);
	DFX_Text(pFX, _T("[Firmenstrasse]"), m_Firmenstrasse);
	DFX_Text(pFX, _T("[Firmentelefax]"), m_Firmentelefax);
	DFX_Text(pFX, _T("[Firmentelefon]"), m_Firmentelefon);
	DFX_Text(pFX, _T("[Gemeindekennzahl]"), m_Gemeindekennzahl);
	DFX_Text(pFX, _T("[Hausnummer]"), m_Hausnummer);
	DFX_Text(pFX, _T("[Ortsname]"), m_Ortsname);
	DFX_Text(pFX, _T("[Partnertelefax]"), m_Partnertelefax);
	DFX_Text(pFX, _T("[Partnertelefon]"), m_Partnertelefon);
	DFX_Text(pFX, _T("[Postleitzahl]"), m_Postleitzahl);
	DFX_Text(pFX, _T("[Strasse]"), m_Strasse);
	DFX_Text(pFX, _T("[Exportiert]"), m_Exportiert);
	DFX_Text(pFX, _T("[EDV]"), m_EDV);
	DFX_Text(pFX, _T("[EDVsonstige]"), m_EDVSonstige);
	DFX_Bool(pFX, _T("[Unterschrift]"), m_Unterschrift);
	//}}AFX_FIELD_MAP

//	Basisklasse rufen
	CDaoRecordsetExt :: DoFieldExchange (pFX);
}

/////////////////////////////////////////////////////////////////////////////
// CGakSet diagnostics

#ifdef _DEBUG
void CGakSet::AssertValid() const
{
	CDaoRecordsetExt::AssertValid();
}

void CGakSet::Dump(CDumpContext& dc) const
{
	CDaoRecordsetExt::Dump(dc);
}
#endif //_DEBUG

BOOL CGakSet::operator= (const CGakSet &InSet)
{                      
//	prüfe Parameter
//	ASSERT (InSet.IsOpen ());
//	ASSERT (IsOpen ());
	ASSERT (this != &InSet);
	
//	Parameter kopieren
	m_Anfallstelle = InSet.m_Anfallstelle;
	m_Betriebsstaette = InSet.m_Betriebsstaette;
	m_Strasse = InSet.m_Strasse;
	m_Hausnummer = InSet.m_Hausnummer;
	m_Postleitzahl = InSet.m_Postleitzahl;
	m_Ortsname = InSet.m_Ortsname;
	m_Gemeindekennzahl = InSet.m_Gemeindekennzahl;
	m_Ansprechpartner = InSet.m_Ansprechpartner;
	m_Partnertelefon = InSet.m_Partnertelefon;
	m_Partnertelefax = InSet.m_Partnertelefax;
	m_Branchennummer = InSet.m_Branchennummer;
	m_Firmenname = InSet.m_Firmenname;
	m_Firmenstrasse = InSet.m_Firmenstrasse;
	m_Firmenhausnummer = InSet.m_Firmenhausnummer;
	m_Firmenpostleitzahl = InSet.m_Firmenpostleitzahl;
	m_Firmenortsname = InSet.m_Firmenortsname;
	m_Bimschnummer = InSet.m_Bimschnummer;
	m_Bimschspalte = InSet.m_Bimschspalte;
	m_Bimschgenehmigungsnummer = InSet.m_Bimschgenehmigungsnummer;
	m_Bilanznummer = InSet.m_Bilanznummer;
	m_Betriebsbeauftragter = InSet.m_Betriebsbeauftragter;
	m_Betriebsbeauftragtentelefon = InSet.m_Betriebsbeauftragtentelefon;
	m_Betriebsbeauftragtentelefax = InSet.m_Betriebsbeauftragtentelefax;
	m_Bemerkungen = InSet.m_Bemerkungen;
	m_Nummer = InSet.m_Nummer;
	
	m_Partnerfunktion = InSet.m_Partnerfunktion;
	m_Firmentelefon = InSet.m_Firmentelefon;
	m_Firmentelefax = InSet.m_Firmentelefax;
	m_Firmenansprechpartner = InSet.m_Firmenansprechpartner;
	m_Betreibernummer = InSet.m_Betreibernummer;
	m_Anzeigenachweisverordnung = InSet.m_Anzeigenachweisverordnung;
	m_Antragsnummer = InSet.m_Antragsnummer;
	m_Betriebsbeauftragtennummer = InSet.m_Betriebsbeauftragtennummer;
	m_Exportiert = InSet.m_Exportiert;
	m_EDV = InSet.m_EDV;
	m_EDVSonstige = InSet.m_EDVSonstige;
	m_Unterschrift = InSet.m_Unterschrift;

//	Systemfelder
	m_ro = FALSE;				//	immer zurücksetzen
	m_user = InSet.m_user;                  
	m_Aenderungsdatum = InSet.m_Aenderungsdatum;
	m_Erfassungsdatum = InSet.m_Erfassungsdatum;

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CGakSetRed

IMPLEMENT_DYNAMIC(CGakSetRed, CDaoRecordset)

CGakSetRed::CGakSetRed(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CGakSetRed)
	m_Gemeindekennzahl = _T("");
	m_Nummer = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}

CString CGakSetRed::GetDefaultDBName()
{
//	lese default-DB-Namen
	CGakApp *pApp = (CGakApp *) AfxGetApp ();
	ASSERT (pApp != NULL);
	return pApp -> DatabaseName ();
}

CString CGakSetRed::GetDefaultSQL()
{
	return ((CGakApp *)AfxGetApp ()) -> ErzeugerDefaultSQL ();
}

void CGakSetRed::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CGakSetRed)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Gemeindekennzahl]"), m_Gemeindekennzahl);
	DFX_Text(pFX, _T("[Nummer]"), m_Nummer);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CGakSetRed diagnostics

#ifdef _DEBUG
void CGakSetRed::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CGakSetRed::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
