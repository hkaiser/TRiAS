// ImportInterface-Implementation für den Import von PolyGIS-BNA-Daten -----------
// File: BNAIMPIF.CPP

#include "bnaimpp.hpp"

#include <errinstx.hxx>
#include <xtensnn.h>
#include <fnamestr.h>
#include <eonrguid.h>
#include <hdrentrx.hxx>
#include <REGISTRX.HXX>

#include <ospace/std/vector>
#include <ospace/string/tokenize.h>

#include "relkey.hxx"

#include "bnaimp.h"
#include "status.hxx"
#include "result.hxx"
#include "bnaimp.hpp"
#include "bnapars.h"
#include "input.h"

char cbInFile[_MAX_PATH] = "";		// aktuelle EingabeDatei

// Für GeoPunktProduktion
static LPCTSTR g_cbBNA	= TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\%s\\%s");
static LPCTSTR g_cbBNALocal	= TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\%s\\%s\\%s");

static void protocol_open (char const *pFile);
static void make_file (char *pNew, char const *old, char const *ext);
void CountObjects (long lOTyp, bool fIncrement = true);
bool ImportGeometry (HPROJECT hPr, OBJGEOMETRIE *pOG, long sta[], long lIdent, double *gxi, double *gyi, int iFlags, long &rlONr, ULONG &rlIgnore);
ErrCode IdentIsDefined (long lIdent);
HOBJECTS IdentScriptIsDefined (char const *pIdent);
ErrCode MCodeIsDefined (long lMCode, char const *pT);

int end_previous_object (FILE *);	/* Objekt bearbeiten */
void init_new_object (void);	/* Naechstes Objekt initialisieren */
//void EnsureUIdentMCodes(void);
void EnsurePolyMCodes(void);
HFEATURE EnsurePolyMCode(char const *pName);
void DefinePolyMCodes(void);
void SetTextField(char const *pText, HFEATURE lMCode);
void PolyInit(void);
HRESULT RestoreRegistryKey (void);
bool MemoIdentifikator(HOBJECTS lIdent); 
short DatLayer( char const*);

// Informationsfelder ---------------------------------------------------------
LONG on = 0;						// Objektnummer
ULONG id;							// Identifikator

long sta[2] = { E_OBJEKT, 0 };		// Status
long mi[MAXMI] = { MAXMI, 0, };		// Merkmalsinformation

#if defined(_NO_CONVERSION_BNA)
long gxi[MAXGI];					// Geometrieinformation
long gyi[MAXGI];
#else
double gxi[MAXGI];					// Geometrieinformation
double gyi[MAXGI];
#endif // _NO_CONVERSION_BNA

long lgi = -1;						// Anzahl der Koordinatenpaare
long maxgi = MAXGI;

long *curr_mi = &mi[-1];			// Merkmalsfeldzeiger 
char *curr_mi_text = (char *)&mi[5];	// Merkmalsfeldzeiger fuer Text

int mi_count = 3;					// Zähler der I*4 Merkmalsfelder

// sonstige Variablen ---------------------------------------------------------
long koord_paare = 0;	// Anzahl der einzulesenden Koordinatenpaare
int mi_werte = 0;		// Anzahl der einzulesenden Merkmalswerte
int mi_length;			// Laenge der Merkmalswerte
int satz_nr;			// Nummer des Objektes im ASCII-File
int objekt_nr = 0;		// Nummer des Satzes im ASCII-File

// globale Daten --------------------------------------------------------------
long lTextObjMCode;		// MerkmalsCode, an dem bei Textobjekten der Text hängt

bool r_flag = true;		// Relationen ignorieren
bool d_flag = true;		// Identifikator dezimal/hexadezimal
bool md_flag = true;		// Merkmale dezimal/hexadezimal
bool g_flag = true;		// Geometrie immer importieren
bool m_flag = true;		// Merkmale importieren

// TransformationsParameter ---------------------------------------------------
double Koeff11 = 1.0;
double Koeff12 = 0.0;
double Koeff21 = 0.0;
double Koeff22 = 1.0;
double OffsetX = 0.0;
double OffsetY = 0.0;

FILE *fpProt = NULL;		// Protokolldatei

// lokale Daten ---------------------------------------------------------------
static char comment[STRINGLEN+1];
static char header[STRINGLEN+1];

// Schlüssel für DB-Header (Leerzeichen sind signifikant !) -------------------
char Koeff11Key[17] = 	"Koeff11         ";
char Koeff12Key[17] = 	"Koeff12         ";
char Koeff21Key[17] = 	"Koeff21         ";
char Koeff22Key[17] = 	"Koeff22         ";
char OffsetXKey[17] = 	"OffsetX         ";
char OffsetYKey[17] = 	"OffsetY         ";
char PbdNameKey[17] = 	"PBD-NAME        ";
char VerschnittKey[17] = 	"Verschnitt      ";
char ZeitKey[17] = 	"Erstellungsdatum";
char DBStatusKey[17] = 	"DB-STATUS       ";
char ScaleKey[17] =   	"Scale           ";
char OffsetKey[17] =  	"Offset          ";
char ObjVisInfoMCode[17] =	"ObjVisInfoMCode ";
char TextObjMCode[17] = "TextObjMCode    ";
char IdentBase[17] =	"IdentBase       ";
char MCodeBase[17] = 	"MCodeBase       ";
char UniqueIdent[17] =	"Unique Ident    ";
char OldUniqueIdent[17] =	"Old Unique Ident";

bool fFirstIdent = true;
bool fFirstMCode = true;

// Scale/Offset verwalten
static bool fWasScaleProject = false;
static bool fWasOffsetProject = false;
static bool fWriteOffsetProject = false;
static bool fWriteScaleProject = false;	

static bool fWasScale = false;
static bool fWasOffset = false;
static bool fWriteOffset = false;
static bool fWriteScale = false;	

// ZählerVariablen ------------------------------------------------------------
long g_lPoints = 0;
long g_lLines = 0;
long g_lAreas = 0;
long g_lTexts = 0;
long g_lKomplex = 0;

long g_lWithErrors = 0;
long g_lNotImported = 0;
long g_lTime = 0;

// Verwalten der Koordinatenparameter ---------------------------------
double g_dOffsetX = 0.0;
double g_dOffsetY = 0.0;
double g_dScaling = 1.0;

// Verwalten des lIdent für PolyGIS-Klassen ---------------------------------
unsigned long g_ulPolyId = 0L;
unsigned long g_ulPolyIdTyp = 0L;

// Verwalten des MCodes für den Unique Ident ---------------------------------
unsigned long g_ulUniqueId = 0L;
unsigned long g_ulOrgUniqueId = 0L;
unsigned long g_ulOldUniqueId = 0L;


// Verwalten des MCodes für den PolyGIS-BNA ---------------------------------
unsigned long g_ulName1 = 0L;
unsigned long g_ulName2 = 0L;
unsigned long g_ulID = 0L;

unsigned long g_ulMemo = 0L;
unsigned long g_ulOrdnung = 0L;

// DAT-Struktur
char g_cKey01[BNAKEYLEN];
char g_cKey02[BNAKEYLEN];
char g_cKey03[BNAKEYLEN];
char g_cKey01P[BNAKEYLEN];
char g_cKey02P[BNAKEYLEN];
char g_cKey03P[BNAKEYLEN];


char g_cName1Buff[BNAKEYLEN];
char g_cName2Buff[BNAKEYLEN];
char g_cIDBuff[BNAKEYLEN];
char g_cSuffix[BNAKEYLEN];
char g_cMemo[BNAKEYLEN];
char g_cOrdnung[BNAKEYLEN];

char g_cBNALayer[_MAX_PATH];
char g_cMemoKlasse[_MAX_PATH];
char g_cMemoKlasseReplace[_MAX_PATH];
char g_cMemoRef[_MAX_PATH];

//////////////////////////////////////////////////////////////////////////////
// MerkmalsCodes für Objektklassenabgleich
bool g_fImportObj = true;				// Objekt vollständig importieren (default)

bool g_fAbglGeom = false;				// Geometrie abgleichen
bool g_fAbglAttr = false;				// Attribute abgleichen

bool g_fAbglOks = false;				// Objektklasse abgleichen
unsigned long g_ulOksFromAttr = 0L;		// Objektklasse hier entnehmen

unsigned long g_ulOksToAttr = 0L;		// bisherige Oks hier ablegen

int yylineno;		/* Zeilennummer */

///////////////////////////////////////////////////////////////////////////////
// aktuelle Datenquelle
HPROJECT g_hPr = NULL;

typedef struct tagBNAID {
    ULONG lIdent;
    char const *pBeschreibung;
	HPROJECT hPr;
} BNAID;

///////////////////////////////////////////////////////////////////////////////
// BNA-Felddefinitionen
int BNALayer[5] = { POLYBNANAME1, POLYBNANAME2, POLYBNAID, POLYBNALAYER, POLYBNAKOORD };

TR_OBJTree *g_MemoTree = NULL;
TR_OKSTree *g_BNAKey = NULL;
TR_LayerTree *g_OKSTree = NULL;		// Baum der OKS

//////////////////////////////////////////////////////////////////////////////
///////////////// Import-Modi ///////////////////////////////////////////////

short m_iMode = 0;


/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineEnumIIDWrapper(LONG);
DefineSmartEnumerator(LONG);

/////////////////////////////////////////////////////////////////////////////
// Globale Variablen
time_t g_lFullTime = 0L;
CStatusDlg *g_pDlg = NULL;
WEnumLONG g_Enum;
bool g_fReReadHeader = false;

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// *** IImportGeoData methods -------------------------------------------------
// Abfrage der Eigenschaften und Möglichkkeiten des ImportModuls (siehe Flags
// in File IXTENSN.HXX IMPORTCAPS_...
STDMETHODIMP_(DWORD) CImpBnaExtension::Capabilities (void)
{
	ResetKeyTree ();		// Baum leeren 
	return IMPORTCAPS_CANIMPORTGEOMETRY  | IMPORTCAPS_OPTIMPORTFEATURES |
	       IMPORTCAPS_OPTIMPORTGEOMETRY  | IMPORTCAPS_CANIMPORTFEATURES |
		   IMPORTCAPS_MULTIPLEFILES |
		   IMPORTCAPS_OPTIMPORTANSIOEM;
}

STDMETHODIMP CImpBnaExtension::GetConfigInfo (IEnumString **ppEnumCfg, DWORD dwReserved)
{
	return E_NOTIMPL;
}

// Diese Funktion wird nur dann gerufen, wenn 'Capabilities' das Flag
// IMPORTCAPS_SHOULDCONFIGURE geliefert hat. Im dieser Funktion sollte die
// Konfiguration des Modules für den nächsten Import durchgeführt werden.
STDMETHODIMP CImpBnaExtension::Configure (HWND hWnd)
{
	return E_NOTIMPL;
}

// Das ist die eigentliche ImportFunktion, die einmal gerufen wird und dann alles
// machen muß, was sie für richtig hält. 
// Der Enumerator pEnumFiles liefert die Dateinamen der zu importierenden Datei(en)
// (ACHTUNG: UNICODE!!! und OLE-TaskAllocator)
STDMETHODIMP CImpBnaExtension::ImportData (IEnumString *pEnumFiles, DWORD dwFlags)
{
	return ImportDataWithResult (pEnumFiles, dwFlags, NULL, NULL);
}

// Übergabe des zu verwendenden Koodinatensystemes
STDMETHODIMP CImpBnaExtension::put_CS (IUnknown *pICS)
{
	m_CS = pICS;
	return S_OK;
}

STDMETHODIMP CImpBnaExtension::ImportDataWithResult (
	IEnumString *pEnumFiles, DWORD dwFlags, 
	IProgressIndicator *pIStatus, IEnumLONG **ppIObjs)
{
LPWSTR pFile = NULL;
ULONG ulGot = 0;
HRESULT hr = E_FAIL;

	m_dwFlags = dwFlags;

// ImportModi setzen
	g_flag = (dwFlags & TOIMPORT_GEOMETRY) ? true : false;
	m_flag = (dwFlags & TOIMPORT_FEATURES) ? true : false;


// ZählerVariablen initialisieren
	PolyInit();

	g_lPoints = 0;
	g_lLines = 0;
	g_lAreas = 0;
	g_lTexts = 0;
	g_lKomplex = 0;

	g_lWithErrors = 0;
	g_lNotImported = 0;

	g_fReReadHeader = false;

// eigentlichen Import durchführen
	if (NULL != ppIObjs) {
		COM_TRY { 
			g_Enum = WEnumLONG (CLSID_EnumObjectsByNumber); 
		} COM_CATCH_IGNORE;
	}			

	USES_CONVERSION;
	if (NULL == pIStatus) {
	CStatusDlg SDlg (g_pTE -> MWind());	// StatusDialog
	bool fShown = false;

		g_pDlg = &SDlg;
		g_lFullTime = 0L;		// GesamtZeit

		pEnumFiles -> Reset();
		while (S_OK == pEnumFiles -> Next (1, (LPOLESTR *)&pFile, &ulGot)) {
		// alle Dateien nacheinander abarbeiten
			if (!fShown) {
				SDlg.Show();
				fShown = true;
			}

			InitConfigDataFromRegistry();

			hr = ImportBNA (OLE2A(pFile));
			CoTaskMemFree (pFile);

			if (FAILED(hr))	break;
		}
		g_pDlg = NULL;

	} 
	else {
		g_pDlg = NULL;
		g_lFullTime = 0L;		// GesamtZeit

		pEnumFiles -> Reset();
		while (S_OK == pEnumFiles -> Next (1, (LPOLESTR *)&pFile, &ulGot)) {
		// alle Dateien nacheinander abarbeiten
			InitConfigDataFromRegistry();

			hr = ImportBNA (OLE2A(pFile));
			CoTaskMemFree (pFile);

			if (FAILED(hr))	break;
		}
	}

// evtl. Enumerator liefern
	if (NULL != ppIObjs)
		*ppIObjs = (IEnumLONG *)g_Enum.detach();

// Abschlußdialog nach jedem File - Übergangslösung
// Neues Interface in allen Import-Funktionen nachziehen und Objekt(g_Enum) auswerten
// -> neue Schnittstelle : ImportDataWithResult

	/*if (NULL == ppIObjs) */
	{
		DEX_PostRebuildSight();		// alles neu zeichnen

	// ResultatsDialog anzeigen
	CResultDlg RDlg (g_pTE -> MWind());

		RDlg.SetTexts (g_lTexts);
		RDlg.SetLines (g_lLines);
		RDlg.SetAreas (g_lAreas);
		RDlg.SetPoints (g_lPoints);
		RDlg.SetKomplex (g_lKomplex);
		RDlg.SetWithErrors (g_lWithErrors);
		RDlg.SetNotImported (g_lNotImported);
		RDlg.SetImported (g_lPoints + g_lLines + g_lAreas + g_lTexts + g_lKomplex);
		SetTime (g_lFullTime, RDlg.m_ftTime);

		MessageBeep (MB_ICONASTERISK);		// fertig !!
		RDlg.Show (Centre);
	}

// alles wieder aufräumen
	ResetKeyTree();			// Konf_Daten_Baum wieder raus
	ResetMemoTree();		// MemoKlassen_Baum wieder raus
	ResetOKSTree();			// BNAKlassen_Baum wieder raus
	return hr;
}

HRESULT CImpBnaExtension::InitConfigDataFromRegistry()
{
	RETURN_FAILED_HRESULT(DefineRegistryStandard());
	RETURN_FAILED_HRESULT(ImportRegistry (STANDARD));
	RETURN_FAILED_HRESULT(ImportRegistry (IMPORT));
	RETURN_FAILED_HRESULT(ImportRegistry (IMPORTSTANDARDKLASSEN));
	RETURN_FAILED_HRESULT(ImportRegistry (IMPORTMEMOKLASSEN));
	RETURN_FAILED_HRESULT(RestoreRegistryKey());		// "Verdichtete" Konfigurationsdaten an Referenzfelder
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////
// Datei durchgehen und Objektklassen rausfinden
//HRESULT CImpBnaExtension::TestImportBNA (char *pFile, CStatusDlg *pDlg)
//{
//HRESULT hr = NOERROR;
//FILE *yyin = yyin = fopen (pFile, "r");
//
//	if (yyin == NULL)
//		return ResultFromScode (STG_E_PATHNOTFOUND);
//
//	strcpy (cbInFile, pFile);		// für FehlerMeldung sichern
//	protocol_open (pFile);
//
//	fseek (yyin, 0L, SEEK_END);		// Dateilänge bestimmen
//
//long lLen = ftell (yyin);
//
//	if (lLen > 0) {
//	ErrInstall EI ((ErrCode)ESYNTX, esyntx);
//
//		if (NULL != pDlg) {
//		string strFile = pFile;
//		string str = get_name (strFile) + get_ext(strFile);
//
//			pDlg -> FInit (lLen, str.c_str()); 
//			pDlg -> Update();
//		}
//
//		fseek (yyin, 0L, SEEK_SET);			// wieder am Anfang
//		hr = PolyParseHeader(yyin, pDlg);
//	}
//	fclose (yyin);
//
//// evtl. Protokolldatei schließen
//	if (fpProt) {
//		fclose (fpProt);
//		fpProt = NULL;
//	}
//	return hr;
//}

////////////////////////////////////////////////////////////////////////////////////
// nur Headersätze untersuchen
//HRESULT CImpBnaExtension::PolyParseHeader (FILE *pActFile, CStatusDlg *pDlg)
//{
//	if (pActFile == NULL)
//		return S_FALSE;  
//
//long lIndex = 0L;
//HRESULT hr = E_FAIL;
//
//	yylineno = 0;		/* Zeilennummer */
//
//char cbLine[4*_MAX_PATH];                       // 1 Zeile
//char cbRefPoly[_MAX_PATH];              
//
//	try {
//   	// aktive Datenquelle bsorgen
//      	g_hPr = DEX_GetDataSourceHandle();
//      	_ASSERTE(NULL != g_hPr);
//
//		lIndex = 0;
//		while (fgets (cbLine, sizeof(cbLine)-1, pActFile)) {
//			yylineno++;		/* Zeilennummer */
//
//			if (NULL != pDlg) {
//				pDlg -> SetPos (ftell (pActFile), yylineno);
//				if (pDlg -> Break())
//					return S_OK;
//			}
//
//			if ('"' == cbLine[0]) {		// Headereinträge - Objektdefinition
//			int iPoly = 0;
//
//				cbRefPoly[0] = '\0';
//
//			char *pPoly = strtok(cbLine, ",");
//
//				while(NULL != pPoly) {
//				char *ptr = strchr ( pPoly,'\0');
//
//					if (ptr && '"' == *(ptr-1)) {
//						if (cbRefPoly[0] != '\0' ) {
//							strcat (cbRefPoly, pPoly);
//
//							PolyLayer(BNALayer[iPoly], cbRefPoly);
//
//							iPoly++;
//							cbRefPoly[0] = '\0';
//						} 
//						else {
//							PolyLayer (BNALayer[iPoly], pPoly);
//							iPoly++;
//						}
//					} 
//					else {
//						strcat (cbRefPoly,pPoly);
//					}
//
//				// Get next token
//					pPoly = strtok(NULL, ",");
//				}
//
//				if (cbRefPoly[0] != '\0') 
//					PolyLayer(BNALayer[iPoly], cbRefPoly);
//
//				if (iPoly < 4)
//					MessageBox (0,"Zur Erinnerung : Fehlerhafte Kopfsätze aufbereiten !", "Lesen PolyGIS-BNA-Kopfsatz",MB_OK);
//			}
//		}
//
//		hr = S_OK;
//
//		if (RetrieveAbgleichOKSTree())
//			return hr;
//
//	CClassDlg CDlg (g_pTE -> MWind(),g_OKSTree);
//	
//		CDlg.Show (Centre);
//		if (0 == CDlg.Result()) 
//			return S_FALSE;
//				
//	} 
//	catch(...) {
//		hr = E_UNEXPECTED;
//	}
//	return hr;
//}

//----------------------------------------------------------------------------
//void CImpBnaExtension::PolyLayer (short iPoly, char const *p)
//{
//	if (iPoly == POLYBNALAYER) {
//		if (!p || '\0' == *p)
//			return;
//
//	char cbPoly[_MAX_PATH];
//
//		cbPoly[0] = '\0';
//		strncat (cbPoly, p+1, strlen(p)-2);
//
//	// Ident existiert evtl. bereits in Zuordnungstabelle
//	long lIdent = ClassIsDefined(cbPoly);
//
//		StoreInOKSTree (cbPoly, lIdent);
//	}
//}

/////////////////////////////////////////////////////////////////////////////////////
// Datei importieren
HRESULT CImpBnaExtension::ImportBNA (char const *pFile)
{
HRESULT hr = NOERROR;
FILE *yyin = fopen (pFile, "r");

	if (NULL == yyin)
		return ResultFromScode (STG_E_PATHNOTFOUND);

	m_iMode = 0;

	protocol_open (pFile);
	strcpy (cbInFile, pFile);	// für FehlerMeldung sichern

	fseek (yyin, 0L, SEEK_END);		// Dateilänge bestimmen

	long lLen = ftell (yyin);



////////////////////////////////////////////////////////////////////////////////



	if (lLen > 0) {
		ErrInstall EI ((ErrCode)ESYNTX, esyntx);
		string strFile (pFile);
		string str = get_name (strFile) + get_ext(strFile);


		g_pDlg -> FInit (lLen, str.c_str()); 
		g_pDlg -> Update();

		fseek (yyin, 0L, SEEK_SET);	// wieder am Anfang

		InitAllEnvironment();

		g_lTime = timeGetTime();	// Zeit für diese Datei


	//KK020904-NOT ===========================================================
	m_iMode = DatLayer(pFile);

	if ( m_iMode ) {
			if (m_iMode == DATIMPORT)
				hr = PolyParseDat(yyin);

			if (m_iMode == GPSIMPORT)
				hr = VideoParseDat(yyin,pFile);

			if (m_iMode == GCAIMPORT)
				hr = GCAParseDat(yyin,pFile);

	} else
			hr = PolyParse(yyin);

	//KK020904-NOT ===========================================================


		g_lFullTime += timeGetTime() - g_lTime;
	}
	fclose (yyin);

// evtl. Protokolldatei schließen
	if (fpProt) {
		fclose (fpProt);
		fpProt = NULL;
	}

// GeoDB neu initialisieren
	DEXN_ReScale();
	DEXN_ReReadIdents();
	DEXN_ReReadContainer();

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// 
HRESULT CImpBnaExtension::ImportRegistryType (int iTyp, UINT uiThemaId)
{
	_ASSERTE(NULL != g_pTE);

TCHAR szBNAKey[_MAX_PATH];
ResString Projekt (ResID(IDS_PROJEKTLAYER, &g_pTE->RF()), 80);
ResString Thema (ResID(uiThemaId, &g_pTE->RF()), 80);

	wsprintf(szBNAKey, g_cbBNA, Projekt.Addr(), Thema.Addr());
	return ImportRegistryStandard(iTyp, szBNAKey);
}

HRESULT CImpBnaExtension::ImportRegistryType (int iTyp, UINT uiThemaId, UINT uiDefaultId)
{
	_ASSERTE(NULL != g_pTE);

TCHAR szBNAKey[_MAX_PATH];
ResString Projekt (ResID(IDS_PROJEKTLAYER, &g_pTE->RF()), 80);
ResString Thema (ResID(uiThemaId, &g_pTE->RF()), 80);
ResString Default (ResID(uiDefaultId, &g_pTE->RF()), 80);

	wsprintf(szBNAKey, g_cbBNALocal, Projekt.Addr(), Thema.Addr(), Default.Addr());
	return ImportRegistryStandard(iTyp, szBNAKey);
}

//-------------------------ImportRegistry-------------------------------------
HRESULT CImpBnaExtension::ImportRegistry (int iTyp)
{
// Registry-Einträge
	switch (iTyp) {
	case STANDARD:
		return ImportRegistryType(STANDARD, IDS_STANDARD);
		
	case IMPORT:
		return ImportRegistryType(IMPORT, IDS_IMPORT, IDS_STANDARDDEFINITION);

	case IMPORTSTANDARDKLASSEN:
		return ImportRegistryType(IMPORTSTANDARDKLASSEN, IDS_IMPORT, IDS_STANDARDKLASSEN);

	case IMPORTMEMOKLASSEN:
		return ImportRegistryType(IMPORTMEMOKLASSEN, IDS_IMPORT, IDS_MEMOKLASSEN);


	default:
		_ASSERTE(FALSE);
		break;
	}
	return EC_OKAY;
}

//-------------------------DefineRegistryStandard-------------------------------------
HRESULT CImpBnaExtension::DefineRegistryStandard()
{
// Registry-Einträge
	g_cName1Buff[0] = '\0';
	g_cName2Buff[0] = '\0';
	g_cIDBuff[0] = '\0';
	g_cSuffix[0] = '\0';
	g_cMemo[0] = '\0';
	g_cOrdnung[0] = '\0';

	g_cMemoKlasse[0] = '\0';
	g_cMemoKlasseReplace[0] = '\0';
	g_cBNALayer[0] = '\0';

	_ASSERTE(NULL != g_pTE);

ResString BNAKeyName1 (ResID(IDS_BNAKEYNAME1, &g_pTE->RF()), 80);
ResString BNAKeyName2 (ResID(IDS_BNAKEYNAME2, &g_pTE->RF()), 80);
ResString BNAKeyID (ResID(IDS_BNAKEYID, &g_pTE->RF()), 80);
ResString BNASuffix (ResID(IDS_BNAKEYSUFFIX, &g_pTE->RF()), 80);
ResString MEMO (ResID(IDS_BNAKEYMEMO, &g_pTE->RF()), 80);
ResString ORDNUNG (ResID(IDS_BNAKEYORDNUNG, &g_pTE->RF()), 80);
ResString MEMOKlasse (ResID(IDS_KEYMEMOKLASSE, &g_pTE->RF()), 80);
ResString MEMOKlasseReplace (ResID(IDS_KEYMEMOKLASSEREPLACE, &g_pTE->RF()), 80);
ResString BNALayer (ResID(IDS_BNALAYER, &g_pTE->RF()), 80);

	strcat (g_cName1Buff, ResString (ResID(IDS_POLYNAME1, &g_pTE->RF()), 50).Addr());
	StoreInKeyTree (BNAKeyName1.Addr(), g_cName1Buff);

// Merkmal Name2
	strcat (g_cName2Buff, ResString (ResID(IDS_POLYNAME2, &g_pTE->RF()), 50).Addr());
	StoreInKeyTree (BNAKeyName2.Addr(), g_cName2Buff);

// Merkmal ID
	strcat (g_cIDBuff, ResString (ResID(IDS_POLYID, &g_pTE->RF()), 50).Addr());
	StoreInKeyTree (BNAKeyID.Addr(), g_cIDBuff);

// BNASuffix
	strcat (g_cSuffix, ResString (ResID(IDS_POLYSUFFIX, &g_pTE->RF()), 50).Addr());
	StoreInKeyTree (BNASuffix.Addr(), g_cSuffix);

// Merkmal Memo
	strcat (g_cMemo, ResString (ResID(IDS_BNAMEMO, &g_pTE->RF()), 50).Addr());
	StoreInKeyTree (MEMO.Addr(), g_cMemo);

// Merkmal Strassenordnung
	strcat (g_cOrdnung, ResString (ResID(IDS_STRASSENORDNUNG, &g_pTE->RF()), 50).Addr());
	StoreInKeyTree (ORDNUNG.Addr(), g_cOrdnung);

//  MemoSuffix
	strcat (g_cMemoKlasse, ResString (ResID(IDS_MEMOKLASSE, &g_pTE->RF()), 50).Addr());
	StoreInKeyTree (MEMOKlasse.Addr(), g_cMemoKlasse);

//  MemoSuffixReplace
	StoreInKeyTree (MEMOKlasseReplace.Addr(), g_cMemoKlasseReplace);

//  BNALayer
	strcat (g_cBNALayer, ResString (ResID(IDS_BNALAYER, &g_pTE->RF()), 50).Addr());
	StoreInKeyTree (BNALayer.Addr(), g_cBNALayer);

	return S_OK;
}


//-------------------------ImportRegistryStandard-------------------------------------
HRESULT CImpBnaExtension::ImportRegistryStandard (int iTyp, char const *pcKey)
{
	_ASSERTE(NULL != g_pTE);

// Registry-Einträge
	g_cName1Buff[0] = '\0';
	g_cName2Buff[0] = '\0';
	g_cIDBuff[0] = '\0';
	g_cSuffix[0] = '\0';
	g_cMemo[0] = '\0';
	g_cOrdnung[0] = '\0';

	g_cMemoKlasse[0] = '\0';
	g_cMemoKlasseReplace[0] = '\0';
	g_cBNALayer[0] = '\0';

CCurrentUser rgMass(pcKey, true);
ResString BNAKeyName1 (ResID(IDS_BNAKEYNAME1, &g_pTE->RF()), 80);
ResString BNAKeyName2 (ResID(IDS_BNAKEYNAME2, &g_pTE->RF()), 80);
ResString BNAKeyID (ResID(IDS_BNAKEYID, &g_pTE->RF()), 80);
ResString BNASuffix (ResID(IDS_BNAKEYSUFFIX, &g_pTE->RF()), 80);
ResString MEMO (ResID(IDS_BNAKEYMEMO, &g_pTE->RF()), 80);
ResString ORDNUNG (ResID(IDS_BNAKEYORDNUNG, &g_pTE->RF()), 80);
ResString MEMOKlasse (ResID(IDS_KEYMEMOKLASSE, &g_pTE->RF()), 80);
ResString MEMOKlasseReplace (ResID(IDS_KEYMEMOKLASSEREPLACE, &g_pTE->RF()), 80);
ResString BNALayer (ResID(IDS_BNALAYER, &g_pTE->RF()), 80);

// Merkmal Name1
DWORD dKeyLen = BNAKEYLEN;

	if (rgMass.GetSubSZ (BNAKeyName1.Addr(), (LPTSTR) g_cName1Buff, dKeyLen)) {
		if (0 == dKeyLen)
			g_cName1Buff[0] = 0;
		StoreInKeyTree (BNAKeyName1.Addr(), g_cName1Buff);
	}

// Merkmal Name2
	dKeyLen = BNAKEYLEN;
	if (rgMass.GetSubSZ (BNAKeyName2.Addr(), (LPTSTR) g_cName2Buff, dKeyLen)) {
		if (0 == dKeyLen)
			g_cName2Buff[0] = 0;
		StoreInKeyTree (BNAKeyName2.Addr(), g_cName2Buff);
	}

// Merkmal ID
	dKeyLen = BNAKEYLEN;
	if (rgMass.GetSubSZ (BNAKeyID.Addr(), (LPTSTR) g_cIDBuff, dKeyLen)) {
		if (0 == dKeyLen)
			g_cIDBuff[0] = 0;
		StoreInKeyTree (BNAKeyID.Addr(), g_cIDBuff);
	}

// BNASuffix
	dKeyLen = BNAKEYLEN;
	if (rgMass.GetSubSZ (BNASuffix.Addr(), (LPTSTR) g_cSuffix, dKeyLen)) {
		if (0 == dKeyLen)
			g_cSuffix[0] = 0;
		StoreInKeyTree (BNASuffix.Addr(), g_cSuffix);
	}

// Merkmal Memo
	dKeyLen = BNAKEYLEN;
	if (rgMass.GetSubSZ (MEMO.Addr(), (LPTSTR) g_cMemo, dKeyLen)) {
		if (0 == dKeyLen)
			g_cMemo[0] = 0;
		StoreInKeyTree (MEMO.Addr(), g_cMemo);
	}

// Merkmal Strassenordnung
	dKeyLen = BNAKEYLEN;
	if (rgMass.GetSubSZ (ORDNUNG.Addr(), (LPTSTR) g_cOrdnung, dKeyLen)) {
		if (0 == dKeyLen)
			g_cOrdnung[0] = 0;
		StoreInKeyTree (ORDNUNG.Addr(), g_cOrdnung);
	}

//  MemoSuffix
	dKeyLen = BNAKEYLEN;
	if (rgMass.GetSubSZ (MEMOKlasse.Addr(), (LPTSTR) g_cMemoKlasse, dKeyLen)) {
		if (0 == dKeyLen)
			g_cMemoKlasse[0] = 0;
		StoreInKeyTree (MEMOKlasse.Addr(), g_cMemoKlasse);
	}

//  MemoSuffixReplace
	dKeyLen = BNAKEYLEN;
	if (rgMass.GetSubSZ (MEMOKlasseReplace.Addr(), (LPTSTR)g_cMemoKlasseReplace, dKeyLen)) {
		if (0 == dKeyLen)
			g_cMemoKlasseReplace[0] = 0;
		StoreInKeyTree (MEMOKlasseReplace.Addr(), g_cMemoKlasseReplace);
	}

//  BNALayer
	dKeyLen = BNAKEYLEN;
	if (rgMass.GetSubSZ (BNALayer.Addr(), (LPTSTR) g_cBNALayer, dKeyLen)) {
		if (0 == dKeyLen)
			g_cBNALayer[0] = 0;
		StoreInKeyTree (BNALayer.Addr(), g_cBNALayer);
	}

// MemoKlassen
	if (iTyp == IMPORTMEMOKLASSEN) {
	char tBuff [80];
	char const *dKey = "M%d";
	char tKey[20];
	int j = 1;

		for (int i = 1; i < 100; i++) {
			wsprintf (tKey, dKey, i);
			dKeyLen = BNAKEYLEN;
			if (rgMass.GetSubSZ ((LPCTSTR )tKey, (LPTSTR) tBuff, dKeyLen)) {
//			HOBJECTS lIdent = IdentScriptIsDefined(tBuff);

				j++;
//				if (INVALID_HOBJECTS != lIdent)
					StoreInMemoTree (tBuff);
			}
			if ((i - j) > 2)
				return EC_OKAY;
		}
	}
	return EC_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
// überspringen des aktuellen Objektes im BNA-File
bool CImpBnaExtension::SkipObject(FILE *pFile)
{
long lLastPos = ftell(pFile);
char cbBuffer[4*_MAX_PATH];

	while (fgets (cbBuffer, sizeof(cbBuffer)-1, pFile)) {
		if ('"' == cbBuffer[0]) {		
		// Headereinträge - Objektdefinition
			fseek(pFile, lLastPos, SEEK_SET);
			return true;						// nächstes Objekt gefunden
		}
		yylineno++;
		lLastPos = ftell(pFile);
	}
	return false;		// EOF
}

//--------------------------PolyParsen-----------------------------------------
DWORD GetObjType (string &rStr, long *pulCount = NULL);


///////////////////////////////////////////////////////////////////////////////

HRESULT CImpBnaExtension::PolyParse (FILE *pActFile)
{
	if (pActFile == NULL)
		return S_FALSE;  

long lIndex = 0L;
HRESULT hr = E_FAIL;

char cbLine[4*_MAX_PATH];                       // 1 Zeile
char abLine[4*_MAX_PATH];                       // 1 Zeile

//char cbRefPoly[_MAX_PATH];

	try {
   	// aktive Datenquelle bsorgen
      	g_hPr = DEX_GetDataSourceHandle();
      	_ASSERTE(NULL != g_hPr);
      
	// Flag initialisieren
   		fFirstIdent = true;
   		fFirstMCode = true;

//		EnsureUIdentMCodes();
		EnsurePolyMCodes();

		satz_nr = 0;
		lIndex = 0;

	bool fObjectWasSkipped = false;

		App::Exec(ExecWhileEvent);
		while (fgets (cbLine, sizeof(cbLine)-1, pActFile)) {
			yylineno++;		/* Zeilennummer */

			if ('"' == cbLine[0]) {		// Headereinträge - Objektdefinition
				lIndex = 0;

			//DOS-Flag auswerten
				if (m_dwFlags & TOIMPORT_ANSIOEM ){
					strcpy(abLine,cbLine);
					OemToChar (abLine,cbLine);
				}


  			// Vorhergehendes EO bearbeiten
				if (!fObjectWasSkipped && satz_nr > 0) {
					if (end_previous_object (pActFile))
						return S_OK;
				}

    		// Nächstes Objekt beginnen 
				fObjectWasSkipped = false;
				++satz_nr;
      			init_new_object ();


			// tokenizer zerteilt die Kopfzeile in Tokens:
			// token 0: leer
			// token 1: NAME1
			// token 2: ','
			// token 3: NAME2
			// token 4: ','
			// token 5: ID
			// token 6: ','
			// token 7: LAYER
			// token 8: ",Geometrie" (Anzahl der Stützpunkte)
			os_tokenizer token("\"", true, "", "\n", "", false);
			vector<string> tokens = token.tokenize(cbLine);

				if (9 != tokens.size()) {
					_ASSERTE(9 == tokens.size());
					SkipObject(pActFile);
					fObjectWasSkipped = true;
					continue;		// unerwartetes Eingabeformat
				}

			// Layer behandeln
			CTable t (*g_OKSTree);

				if (!t.Find((void *)tokens[7].c_str())) {
					_ASSERTE(FALSE);		// should exist
					SkipObject(pActFile);
					fObjectWasSkipped = true;
					continue;
				}

			TR_LayerLock l(t);

				if (!l) {
					_ASSERTE(FALSE);		// snh
					SkipObject(pActFile);
					fObjectWasSkipped = true;
					continue;
				}

			// hier ist der neue Ident
				DWORD dwObjTyp = GetObjType(tokens[8], &koord_paare);

			// Objekttyp und Stützpunktanzahl
				if (1 == koord_paare)

					sta[1] = O_PUNKT;

				else if (koord_paare < 0) {

					sta[1] = O_LINIE;
					koord_paare = -koord_paare;

				}

				else {
					_ASSERTE(2 < koord_paare);
					sta[1] = O_FLAECHE;
				}

				ULONG lIdent = l -> Ident(dwObjTyp);

				if (0 == lIdent) {
				// Objekte dieses Layers/Objekttyps sollen nicht importiert werden
					SkipObject(pActFile);
					fObjectWasSkipped = true;
					continue;
				}
				if (lIdent != g_ulPolyId) {
					g_ulPolyId = lIdent;
					DefinePolyMCodes();
				}
	   			id = lIdent;

			// Name1, Name2 und Id behandlen
				if (l -> GetImportAttributes(dwObjTyp)) {
				ResourceFile RF (g_pDLLName);

					if (INVALID_HFEATURE == g_ulName1) {
					ResString resName1 (ResID(IDS_POLYNAME1, &RF), 64);
					HFEATURE hFeat = EnsurePolyMCode(resName1);

						if (INVALID_HFEATURE != hFeat && 
							EC_OKAY == MCodeIsDefined(hFeat, resName1))
						{
							SetTextField(tokens[1].c_str(), hFeat);
						}
					}
					else
						SetTextField(tokens[1].c_str(), g_ulName1);

					if (INVALID_HFEATURE == g_ulName2) {
					ResString resName2 (ResID(IDS_POLYNAME2, &RF), 64);
					HFEATURE hFeat = EnsurePolyMCode(resName2);

						if (INVALID_HFEATURE != hFeat && 
							EC_OKAY == MCodeIsDefined(hFeat, resName2))
						{
							SetTextField(tokens[3].c_str(), hFeat);
						}
					}
					else
			 			SetTextField(tokens[3].c_str(), g_ulName2);

					if (INVALID_HFEATURE == g_ulID) {
					ResString resID (ResID(IDS_POLYID, &RF), 64);
					HFEATURE hFeat = EnsurePolyMCode(resID);

						if (INVALID_HFEATURE != hFeat && 
							EC_OKAY == MCodeIsDefined(hFeat, resID))
						{
							SetTextField(tokens[5].c_str(), hFeat);
						}
					}
					else
						SetTextField(tokens[5].c_str(), g_ulID);
				} 
				else {
					SetTextField(tokens[1].c_str(), g_ulName1);
		 			SetTextField(tokens[3].c_str(), g_ulName2);
					SetTextField(tokens[5].c_str(), g_ulID);
				}
				strcpy (g_cMemoRef, tokens[5].c_str());

			// UniqueIdent
			char cbBuffer[_MAX_PATH];

				wsprintf (cbBuffer, "%s_%ld", tokens[7].c_str(), satz_nr);
				if (MemoIdentifikator(lIdent)) {

					_ASSERTE(0 != g_ulMemo);

					SetTextField(g_cMemoRef, g_ulMemo);
				}

				_ASSERTE(0 != g_ulUniqueId);
				SetTextField(cbBuffer, g_ulUniqueId);
			} 
			else {	
			// Koordinaten !!!
			int irc = 0;
			double xref,yref;

				lgi++;				// Koordinatenanzahl
				irc = sscanf (cbLine, "%lf,%lf", &xref, &yref);

				gxi[lIndex] = (xref + g_dOffsetX) * g_dScaling;
				gyi[lIndex] = (yref + g_dOffsetY) * g_dScaling;

				lIndex++;
			}
		}

	// Vorhergehendes EO bearbeiten
		if (!fObjectWasSkipped && satz_nr > 0) {
			if (end_previous_object (pActFile))
				return S_OK;
		}
		hr = S_FALSE;
	} 
	catch(...) {
		hr = E_UNEXPECTED;
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
void SetTextField (char const *pPoly, HFEATURE lMCode)
{
	if (!pPoly || *pPoly == '\0' || INVALID_HFEATURE == lMCode)
		return;

int Len = strlen (pPoly);
long wf = 0;
      
	curr_mi = &curr_mi[mi_count];
    mi_count = 3;
    curr_mi_text = (char *)&curr_mi[3];
  
	curr_mi[0] = lMCode;	// MerkmalsCode
    curr_mi[1] = M_TEXT;
  
// wie normalen Merkmalswert behandeln
    if (!strncmp (pPoly, "@@", 2)) {
      	Len -= 2;
      	strncpy (curr_mi_text, pPoly+2, 78);
      	curr_mi_text[min(78, Len)] = '\0';
  
	// Status korrigieren
      	sta[1] = O_TEXTOBJIND;
    } else {
      	strncpy (curr_mi_text, pPoly, 78);
      	curr_mi_text[min(78, Len)] = '\0';
    }
  
	curr_mi_text += Len;
    wf = (Len + (sizeof(long)-1))/sizeof(long);
  
	mi[1] += wf + 3;
    curr_mi[2] = wf;		// Wiederholungsfaktor
    mi_count += wf;
}

///////////////////////////////////////////////////////////////////////////////
// nachsehen, ob es diesen MCode schon gibt
ErrCode MCodeIsDefined (long lMCode, char const *rs)
{
ErrInstall EI (WC_NOMERKMAL);
PBDMERKMALEX pbdData;

	INITSTRUCT(pbdData, PBDMERKMALEX);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCode;
	pbdData.pbdKText = NULL;
	pbdData.pbdLText = NULL;
	pbdData.pbdKTextLen = 0;
	pbdData.pbdLTextLen = 0;
	pbdData.lIdent = g_ulPolyId;

// PBD-Info holen
	if (DEX_GetPBDDataEx (g_hPr, pbdData) == EC_OKAY) 
		return EC_OKAY;

char KText[TEXTLEN] = { '\0' };
PBDMERKMALEX pbdData1;

	INITSTRUCT(pbdData1, PBDMERKMALEX);
	pbdData1.pbdTyp = 'm';
	pbdData1.pbdCode = lMCode;
	pbdData1.pbdKTextLen = sizeof(KText) -1;
	pbdData1.pbdLTextLen = 0;

	strcat (KText, rs);

	pbdData1.pbdKText = KText;

	pbdData1.ipbdMTyp = MPObjectFeature;	// so tun, als ob's nur für Objekte wär
	pbdData1.ipbdMLen = 256;
	pbdData1.lIdent = g_ulPolyId;

	if (DEX_ModPBDDataEx (g_hPr, pbdData1) != EC_OKAY)
		return EC_INVPBDNAME;
	else
		DEXN_PBDMCodeChanged (lMCode);

	return EC_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
// nachsehen, ob es diesen Ident schon gibt
ErrCode IdentIsDefined (long lIdent)
{
ErrInstall EI (WC_NOIDENT);
PBDDATA pbdData;

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = NULL;
	pbdData.pbdLText = NULL;
	pbdData.pbdKTextLen = 0;
	pbdData.pbdLTextLen = 0;

// PBD-Info holen
	return DEX_GetPBDDataEx (g_hPr, pbdData);
}

///////////////////////////////////////////////////////////////////////////////
// nachsehen, ob es diese IdentBeschreibung schon gibt
extern "C" 
bool PASCAL OKSBeschreibung (long lIdent, bool, void *pData)
{
	if (DEX_GetObjectsProject(lIdent) != ((BNAID *)pData) -> hPr)
		return true;		// falsche Datenquelle

char cbText[_MAX_PATH];
ErrInstall EI (WC_NOIDENT);
PBDDATA pbdData;		// Nun mit Text definieren

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = cbText;
	pbdData.pbdLText = NULL;
	pbdData.pbdKTextLen = sizeof(cbText)-1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDDataEx (((BNAID *)pData) -> hPr, pbdData);

	if (!strcmp(cbText, ((BNAID *)pData) -> pBeschreibung)) {
		((BNAID *)pData) -> lIdent = lIdent;

	char *cptr = strrchr (cbText, '_');
	
		if (cptr && !strcmp (g_cMemoKlasse, cptr)) 
			StoreInMemoTree (cbText);		// Baumlösung
		return false;		// nicht weiter suchen
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Ident zu einer gegebenen Objektklasse liefern
ULONG ClassIsDefined (char const *pIdent, HPROJECT hPr)
{
	if (NULL == hPr)
		hPr = DEX_GetDataSourceHandle();

BNAID p;

	p.lIdent = 0;
	p.pBeschreibung = pIdent;
	p.hPr = hPr;

//  PBD-Info holen
ENUMLONGKEY ENK;

	ENK.eKey = 'i';
	ENK.eFcn = (ENUMLONGKEYPROC) OKSBeschreibung;
	ENK.ePtr = &p;
	DEX_EnumPBDDataEx (p.hPr, ENK);
	return p.lIdent;
}

///////////////////////////////////////////////////////////////////////////////////////
//
HOBJECTS IdentScriptIsDefined (char const *pIdent)
{
HOBJECTS ulIdent = ClassIsDefined(pIdent, g_hPr);

	if (0L != ulIdent)		// Beschreibung wurde gefunden !
		return ulIdent;

ErrInstall EI (WC_NOIDENT);
PBDDATA pbdData;		// Nun mit Text definieren

	ulIdent = (ULONG)DEX_GetUniqueICodeEx (g_hPr); // neuer Ident von TRIAS

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = ulIdent;
	pbdData.pbdKText = (LPSTR)pIdent;
	pbdData.pbdLText = NULL;
	pbdData.pbdKTextLen = _MAX_PATH;
	pbdData.pbdLTextLen = 0;
	DEX_ModPBDDataEx (g_hPr, pbdData);		// PBD-Info setzen
	return ulIdent;
}


///////////////////////////////////////////////////////////////////////////////
// PolyMCodes sicherstellen
HFEATURE EnsurePolyMCode(char const *pName)
{
	_ASSERTE(NULL != g_hPr);
	if (NULL == pName || '\0' == pName[0])
		return INVALID_HFEATURE;

HFEATURE lMHandle = DEX_GetMCodeFromFeatureNameEx (g_hPr, pName);

	if (INVALID_HFEATURE == lMHandle) 
		lMHandle = DEX_MapHandleToMCode(DEX_GetUniqueMCode());

	_ASSERTE(INVALID_HFEATURE != lMHandle);
	return lMHandle;
}

void EnsurePolyMCodes()
{
	if (INVALID_HFEATURE == g_ulName1) 
		g_ulName1 = EnsurePolyMCode(g_cName1Buff);

	if (INVALID_HFEATURE == g_ulName2) 
		g_ulName2 = EnsurePolyMCode(g_cName2Buff);

	if (INVALID_HFEATURE == g_ulID) 
		g_ulID = EnsurePolyMCode(g_cIDBuff);

	if (INVALID_HFEATURE == g_ulMemo) 
		g_ulMemo = EnsurePolyMCode(g_cMemo);

	if (INVALID_HFEATURE == g_ulOrdnung) 
		g_ulOrdnung = EnsurePolyMCode(g_cOrdnung);

	// UniqueIdent besorgen !!!

	g_ulUniqueId = DEX_GetUniqueIdentMCodeEx(g_hPr);
}

///////////////////////////////////////////////////////////////////////////////
// PolyMCodes in PBD definieren
void DefinePolyMCodes()
{
	if (0L != g_ulName1)
		MCodeIsDefined (g_ulName1, g_cName1Buff);

	if (0L != g_ulName2) 
		MCodeIsDefined (g_ulName2, g_cName2Buff);

	if (0L != g_ulID)
		MCodeIsDefined (g_ulID, g_cIDBuff);

	if (0L != g_ulMemo) 
		MCodeIsDefined (g_ulMemo, g_cMemo);

	if (0L != g_ulOrdnung) 
		MCodeIsDefined (g_ulOrdnung, g_cOrdnung);
}

// Protokolldatei eröffnen ----------------------------------------------------
static void protocol_open (char const *pFile) 
{
char cbProtocol[_MAX_PATH];

	make_file (cbProtocol, pFile, ".lst");

	if (fpProt)
		fclose (fpProt);		// evtl. vorherige Datei schließen

	fpProt = fopen (cbProtocol, "w");
	if (fpProt)
		setvbuf (fpProt, NULL, _IONBF, 0);	// Buffering ausschalten
}


// Neue Extension anhängen ----------------------------------------------------
static void make_file (char *pNew, char const *old, char const *ext) 
{
char *cptr;

	strcpy (pNew, old);
	for (cptr = &pNew[strlen(pNew) -1]; cptr >= pNew; --cptr) {
		if (*cptr == '.') {
			strcpy (cptr, ext);
			break;
		}
		if (*cptr == BACKSLASH || cptr == pNew) {
			strcat (pNew, ext);
			break;
		}
	}
}

// FehlerAusgabeRoutine -------------------------------------------------------
int __cdecl esyntx (int errcode, int routine, ...) 
{
va_list pList;
ERROR_PARAMETER *pErrPar;

	va_start (pList, routine);
	pErrPar = va_arg (pList, ERROR_PARAMETER *);
	va_end (pList);

ResourceFile RF (g_pDLLName);
ResString resErrorCap (ResID (IDS_PARSERERRORCAP, &RF), 64);
ResString resError (ResID (IDS_PARSERERROR, &RF), 256);
char cbBuffer[_MAX_PATH];

	wsprintf (cbBuffer, resError, pErrPar -> pFile, pErrPar -> iLineNumber, pErrPar -> pString);
	MessBox mb (resErrorCap, cbBuffer, g_pTE -> MWind());
	mb.Show();
	return errcode;
}
//------------------------------------------------------------------------------

#define YYACCEPT        return(0)
#define YYABORT         return(1)

void yyerror (char *string) 
{
ERROR_PARAMETER param;

//	param.iLineNumber = yylineno;
	param.pString = string;
	param.pFile = cbInFile;
	db_error (ESYNTX, BNAPARSER, (DWORD)&param);
}

int db_error (int iError, int iRoutine, DWORD dwData)
{
int R = EOKAY;

	DEX_SetError (R, iRoutine, iError, (void *)dwData);
	return R;
}

// Headerverwaltung -----------------------------------------------------------
static 
bool GetAllKoeffs (HPROJECT hPr)
{
	Koeff11 = HeaderEntryX(Koeff11Key, hPr).EntryDouble(1.0);
	Koeff12 = HeaderEntryX(Koeff12Key, hPr).EntryDouble(0.0);
	Koeff21 = HeaderEntryX(Koeff21Key, hPr).EntryDouble(0.0);
	Koeff22 = HeaderEntryX(Koeff22Key, hPr).EntryDouble(1.0);
	OffsetX = HeaderEntryX(OffsetXKey, hPr).EntryDouble(0.0);
	OffsetY = HeaderEntryX(OffsetYKey, hPr).EntryDouble(0.0);

// wieder invertieren
	if (EvalKoeffs (&Koeff11, &Koeff12, &Koeff21, &Koeff22) != EOKAY)
		return false;

	return true;
}

static 
bool toWriteScaleProject ()
{
	if (fWasScaleProject) return false;

	fWasScaleProject = true;

	if (fWasOffsetProject)
		return fWriteScaleProject;
	else {
	double dTmp = 0.0;

		if (!GetHdFloat (HACTPROJECT, Koeff11Key, dTmp))
			fWriteOffsetProject = true;
		else {
			fWriteOffsetProject = false;
			GetAllKoeffs(HACTPROJECT);
		}
		return fWriteOffsetProject;
	}
}

static 
bool toWriteOffsetProject ()
{
	if (fWasOffsetProject) return false;

	fWasOffsetProject = true;

	if (fWasScaleProject)
		return fWriteOffsetProject;
	else {
	double dTmp = 0.0;

		if (!GetHdFloat (HACTPROJECT, Koeff11Key, dTmp))
			fWriteScaleProject = true;
		else {
			fWriteScaleProject = false;
			GetAllKoeffs (HACTPROJECT);
		}
		return fWriteScaleProject;
	}
}

static 
bool toWriteScale ()
{
	if (fWasScale) return false;

	fWasScale = true;

	if (!DEX_GetTRiASDataSourceEx(g_hPr))
		return true;		// keine TRiAS-GeoDB

	if (fWasOffset)
		return fWriteScale;
	else {
	double dTmp = 0.0;

		if (!GetHdFloat (g_hPr, Koeff11Key, dTmp))
			fWriteOffset = true;
		else {
			fWriteOffset = false;
			GetAllKoeffs(g_hPr);
		}
		return fWriteOffset;
	}
}

static 
bool toWriteOffset ()
{
	if (fWasOffset) return false;

	fWasOffset = true;

	if (!DEX_GetTRiASDataSourceEx(g_hPr))
		return true;		// keine TRiAS-GeoDB

	if (fWasScale)
		return fWriteOffset;
	else {
	double dTmp = 0.0;

		if (!GetHdFloat (g_hPr, Koeff11Key, dTmp))
			fWriteScale = true;
		else {
			fWriteScale = false;
			GetAllKoeffs (g_hPr);
		}
		return fWriteScale;
	}
}

void InitAllEnvironment (void)
{
	on = 0;			// Objektnummer
	lgi = -1;		// Anzahl der Koordinatenpaare
	maxgi = MAXGI;

	curr_mi = &mi[-1];	// Merkmalsfeldzeiger */
	curr_mi_text = (char *)&mi[5];	// Merkmalsfeldzeiger fuer Text

	mi_count = 3;		// Zähler der Merkmalsfelder

// sonstige Variablen ---------------------------------------------------------
	mi_werte = 0;		// Anzahl der einzulesenden Merkmalswerte
	objekt_nr = 0;		// Nummer des Satzes im BNA-File

// globale Daten --------------------------------------------------------------
	d_flag = true;		// Identifikator dezimal
	md_flag = true;		// Merkmale dezimal

// Abgleichsparameter
	g_fImportObj = true;		// Objekt standardmäßig vollständig importieren

	g_fAbglGeom = false;		// Geometrie abgleichen
	g_fAbglAttr = false;		// Attribute abgleichen

	g_fAbglOks = false;			// Objektklasse abgleichen
	g_ulOksFromAttr = 0L;		// Objektklasse hier entnehmen

	g_ulOksToAttr = 0L;		// bisherige Oks hier ablegen

// TransformationsParameter ---------------------------------------------------
	Koeff11 = 1.0;
	Koeff12 = 0.0;
	Koeff21 = 0.0;
	Koeff22 = 1.0;
	OffsetX = 0.0;
	OffsetY = 0.0;

	fFirstIdent = true;
	fFirstMCode = true;

// Scale/Offset verwalten
	fWasScaleProject = false;
	fWasOffsetProject = false;
	fWriteOffsetProject = false;
	fWriteScaleProject = false;	

	fWasScale = false;
	fWasOffset = false;
	fWriteOffset = false;
	fWriteScale = false;	

// Unique IdentMCodes rücksetzen
	g_ulOrgUniqueId = g_ulOldUniqueId = g_ulUniqueId = 0L;
}

bool ImportHeader (LPCSTR pcKey, LPCSTR pcData, DWORD dwStyle)
{
char KeyString[17];
int len;

	memset (KeyString, ' ', 16);
	KeyString[16] = '\0';

	strncpy (KeyString, pcKey, 16);
	if ((len = strlen (KeyString)) < 16)
		KeyString[len] = ' ';

	if (!strcmp (KeyString, ScaleKey)) {
	// zuerst in Datenquelle nachsehen
		if (!toWriteScale()) 
			return true;

	// ScaleZeile als Entry
	double f11, f12, f21, f22;

		sscanf (pcData, "%lf%lf%lf%lf", &f11, &f12, &f21, &f22);
		Koeff11 = f11;
		Koeff12 = f12;
		Koeff21 = f21;
		Koeff22 = f22;
		if (EvalKoeffs (&f11, &f12, &f21, &f22) != EOKAY)
			return false;

		if (DEX_GetTRiASDataSourceEx(g_hPr)) {
			PutHdFlt (g_hPr, f11, Koeff11Key, true, HEADER_SYSTEMRO);
			PutHdFlt (g_hPr, f12, Koeff12Key, true, HEADER_SYSTEMRO);
			PutHdFlt (g_hPr, f21, Koeff21Key, true, HEADER_SYSTEMRO);
			PutHdFlt (g_hPr, f22, Koeff22Key, true, HEADER_SYSTEMRO);
		}

	// evtl. auch im Projekt testen
		if (!toWriteScaleProject()) 
			return true;

		PutHdFlt (HACTPROJECT, f11, Koeff11Key, true, HEADER_SYSTEMRO);
		PutHdFlt (HACTPROJECT, f12, Koeff12Key, true, HEADER_SYSTEMRO);
		PutHdFlt (HACTPROJECT, f21, Koeff21Key, true, HEADER_SYSTEMRO);
		PutHdFlt (HACTPROJECT, f22, Koeff22Key, true, HEADER_SYSTEMRO);
		return true;
	} 
	if (!strcmp (KeyString, OffsetKey)) {
	// OffsetZeile als Entry
		if (!toWriteOffset()) 
			return true;

		sscanf (pcData, "%lf%lf", &OffsetX, &OffsetY);

		if (DEX_GetTRiASDataSourceEx(g_hPr)) {
			PutHdFlt (g_hPr, OffsetX, OffsetXKey, true, HEADER_SYSTEMRO);
			PutHdFlt (g_hPr, OffsetY, OffsetYKey, true, HEADER_SYSTEMRO);
		}

	// evtl. auch in Projekt schreiben
		if (!toWriteOffsetProject()) 
			return true;

		PutHdFlt (HACTPROJECT, OffsetX, OffsetXKey, true, HEADER_SYSTEMRO);
		PutHdFlt (HACTPROJECT, OffsetY, OffsetYKey, true, HEADER_SYSTEMRO);
		return true;
	}

// Zahlenbasis für Identifikator einstellen evtl. aus Header
	if (!strcmp (KeyString, IdentBase)) {
	ULONG ulIdBase = 10;

		if (!GetHdULONG (g_hPr, IdentBase, ulIdBase)) 
			d_flag = (atoi (pcData) == 10) ? true : false;
		else
			d_flag = (ulIdBase == 10) ? true : false;
	}

// Zahlenbasis für Merkmale einstellen (Hex hat Vorrang)
	if (md_flag && !strcmp (KeyString, MCodeBase)) 
		md_flag = (atoi (pcData) == 10);

// spezielle Auswertung des UniqueIdents
	if (!strcmp (KeyString, UniqueIdent)) {
		g_ulUniqueId = strtoul (pcData, NULL, 10);

	unsigned long ulVal = 0;

		g_ulOrgUniqueId = g_ulUniqueId;
		if (GetHdULONG (g_hPr, UniqueIdent, ulVal) && 0 != ulVal)
			g_ulOrgUniqueId = ulVal;
	}

// ansonsten normale Behandlung
	PutHdString (g_hPr, (char *)pcData, (char *)pcKey, false, dwStyle);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Objekt neu initialisieren 
void init_new_object (void) 
{
	lgi = -1;			// noch keine Geometrie gelesen
	mi[0] = MAXMI;		// Merkmalsfeldgröße
	mi[1] = 0;			// noch keine Merkmale gelesen
	curr_mi = &mi[-1];	// aktuelle Merkmalswerte
	curr_mi_text = (char *)&curr_mi[3];
	koord_paare = 0;	// Anzahl der Stützpunkte
	mi_count = 3;		// Zaehler der Merkmalswerte
	mi_werte = 0;		// Anzahl der Merkmalswerte
	on = 0;

	sta[0] = E_OBJEKT;	// für alle Fälle wieder auf ElementarObjekt

// RelationsDaten
	ClearList();		// interne Datenstrukturen initialisieren
}

///////////////////////////////////////////////////////////////////////////////
// Objekt bearbeiten 
int end_previous_object (FILE *yyin) 
{
long irc = 0L;

	lgi++;		/* Geometriezaehler korrigieren */
	if (lgi < koord_paare)
		return (db_error (EGCNT, BNAPARSER, yylineno));

// bevor irgend etwas passiert Header neu einlesen
	if (g_fReReadHeader) {
		DEXN_ReReadHeader();
		DEXN_ReScale();
		g_fReReadHeader = false;		// nur einmal
	}

// auswerten ob Komplexobjekt 
	if (lgi == 0) {
		if (RelCount() == 0)
			return db_error (EBADKO, BNAPARSER, yylineno);
		if (!r_flag)
			return EOKAY;	// keine Relationen, keine KomplexObjekte
		sta[0] = K_OBJEKT;	// Status setzen
		sta[1] = 0;		
	}

	if (g_flag) 
		irc = CreateObject (on, id, sta, mi, lgi, gxi, gyi);
	else
		irc = UpdateFeatures (on, id, sta, mi);

// evtl. zur AusgabeObjektmenge hinzufügen
	if (irc && g_Enum.IsValid())
		g_Enum -> AddItem (on);

// Protocoll, Relationen etc.
bool fBreak = false;

	if (NULL != g_pDlg) {
		if (irc) 
			g_pDlg -> SetPos (ftell (yyin), on);
		fBreak = g_pDlg -> Break();
	}

	if (fpProt) 
		fprintf (fpProt, "Satz %5ld, Objekt %5ld: Irc = %3ld\n", satz_nr, on, irc);

	if (irc && r_flag) {
		if (RelCount()) {
		// Relationen aufbauen
		long lONr, lRCode;
		short iRTyp;

			ResetList();
			while (RetrieveNextFromList (&lONr, &lRCode, &iRTyp)) 
				CreateRelation (on, lONr, lRCode, iRTyp);
			ClearList();
		}

	// Zuordnung Objekt <--> SatzNummer für Relationen merken
		StoreInTree (on, satz_nr);
	}
	return fBreak;
}

// Objekt ueberspringen -------------------------------------------------------
//int error_skip_lines (char *pattern, int error_code) 
//{
//// Fehlermeldung ausgeben
//	db_error (error_code, BNAPARSER, yylineno);
////	satz_nr = 0;				// Objekt nicht speichern
////	skip_lines (pattern);		// Satz suchen
//	return (error_code);
//}

// Schreiben von HeaderSätzen in den DB-Header --------------------------------
bool PutHdFlt (HPROJECT hPr, double Val, char *pKey, bool fForce, DWORD dwStyle) 
{
char cbOutBuff[50];

	sprintf (cbOutBuff, "%18.9lf", Val);
	return PutHdString (hPr, cbOutBuff, pKey, fForce, dwStyle);
}

bool PutHdString (HPROJECT hPr, char *pText, char *pKey, bool fForce, DWORD dwStyle) 
{
HeaderEntryX HE (pKey, hPr);

	if (HE.Status() != HE_INVALID && !fForce)
		return true;	// existiert bereits

	HE.SetEntryText (pText);
	HE.Flags() = dwStyle;

	if (EC_OKAY == HE.WriteBack()) {
		g_fReReadHeader = true;
		return true;
	}
	return false;
}

bool GetHdULONG (HPROJECT hPr, const char *pKey, unsigned long &ulVal)
{
HeaderEntryX HE (pKey, hPr);

	if (HE.Status() != HE_INVALID) {
		ulVal = (unsigned long)HE.EntryLong (0);
		return true;
	}
	return false;
}

bool GetHdFloat (HPROJECT hPr, const char *pKey, double &rd)
{
HeaderEntryX HE (pKey, hPr);

	if (HE.Status() != HE_INVALID) {
		rd = HE.EntryDouble (0.0);
		return true;
	}
	return false;
}

// Inverse Matrix für Koordinatentransformation berechnen ---------------------
int EvalKoeffs (double *k11, double *k12, double *k21, double *k22) 
{
double DetA = *k11 * *k22 - *k12 * *k21;

	if (DetA != 0.0) {
	double temp = *k11;

		*k11 = *k22/DetA;
		*k22 = temp/DetA;
		*k12 = -(*k12/DetA);
		*k21 = -(*k21/DetA);
		return EOKAY;
	} 
	else {
		yyerror ("Entartete Transformationsmatrix.");
		return ESYNTX;
	}
}

// Umkonvertieren einer dezimalzahl in eine HexZahl ---------------------------
unsigned long MakeHex (unsigned long lPseudoHex)
{
char pTmp[40];

	ultoa (lPseudoHex, pTmp, 10);
	return strtoul (pTmp, NULL, 16);
}

///////////////////////////////////////////////////////////////////////////////
// Zählen der importierten Objekte
void CountObjects (long lOTyp, bool fIncrement)
{
	switch (lOTyp) {
	case O_PUNKT:
		if (fIncrement)
			g_lPoints++;
		else
			g_lPoints--;
		break;

	case O_LINIE:
		if (fIncrement)
			g_lLines++;
		else
			g_lLines--;
		break;

	case O_FLAECHE:
		if (fIncrement)
			g_lAreas++;
		else
			g_lAreas--;
		break;

	case O_TEXTOBJEKT:
		if (fIncrement)
			g_lTexts++;
		else
			g_lTexts--;
		break;

	case O_TEXTOBJIND:
		if (fIncrement)
			g_lTexts++;
		else
			g_lTexts--;
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Geometrieobjekt erzeugen bzw. Geometrie modifizieren
short GetMOIMode (long sta[])
{
short iMode = 0;

	switch (sta[1]) {
	case O_PUNKT:
		iMode = MODIDENT_PUNKT;
		break;

	case O_LINIE:
		iMode = MODIDENT_LINIE;
		break;

	case O_FLAECHE:
		iMode = MODIDENT_FLAECHE;
		break;

	case O_TEXTOBJEKT:
	case O_TEXTOBJIND:
		iMode = MODIDENT_TEXT;
		break;
	}
	return iMode;
}

bool CreateObject (LONG &rlONr, ULONG lIdent, long sta[], 
		   long mi[], long lgi, double gxi[], double gyi[])
{
HPROJECT hPr = DEX_GetDataSourceHandle();

	_ASSERTE(NULL != hPr);

	if (sta[0] == K_OBJEKT) 
		return r_flag ? CreateKomplexObject (hPr, rlONr, lIdent, mi) : true;

// Objekt erzeugen oder wiederfinden, Geometrie schreiben
long lONr = 0L;
char *pUIdent = NULL;

//	TX_ASSERT(!(g_fAbglGeom && g_fAbglAttr));	// nie gleichzeitig Attribs und Geometrie abgleichen!

	if (!m_flag || g_fAbglOks || g_fAbglGeom || g_fAbglAttr || 0 != g_ulOksToAttr) {
	// versuchen, über Unique Ident zu finden
		if (RetrieveText (g_ulUniqueId, mi, &pUIdent, false, !g_fImportObj) > 0) 
			lONr = FindObject (g_ulUniqueId, pUIdent);
	}
	DELETE_OBJ(pUIdent);

TEXTGEOMETRIEEX TG;
OBJGEOMETRIE *pOG = (OBJGEOMETRIE *)&TG;
ULONG lIgnore = 0L;
int iFlags = OGForceGeometry|OGNoMemoryObject|OGConverted|OGAddToView;
bool fRet = true;

	if (0 == lONr) {	// nicht wiedergefunden
	// Objekt neu erzeugen
		iFlags |= OGNewObject;
		iFlags |= OGAddToView;
		fRet = ImportGeometry (hPr, pOG, sta, lIdent, gxi, gyi, iFlags, rlONr, lIgnore);

		VIEWIDENTOBJECT VI;
		INITSTRUCT(VI,VIEWIDENTOBJECT);
		VI.m_lIdent = lIdent;
	//	VI.m_lONr = rlONr;
		VI.m_iOTyp = OTPunkt | OTLinie | OTFlaeche | OTText;

		DEX_AddIdentToView(VI);

	} else {
	// Abgleich durchführen
		if (g_fAbglGeom) {
		// Geometrie abgleichen
			iFlags |= OGModObject;
			fRet = ImportGeometry (hPr, pOG, sta, lIdent, gxi, gyi, iFlags, rlONr, lIgnore);

		} else { 
		// bisherigen Oks wegschreiben
			if (0 != g_ulOksToAttr) {
			long lOldIdent = DEX_GetObjIdent(lONr);
			char cbOKS[MAX_OKS_LENX+1];
			
				if (S_OK == ClassFromIdentX (lOldIdent, cbOKS)) 
					WriteTextMerkmal (lONr, (ULONG)g_ulOksToAttr, cbOKS, strlen(cbOKS));
			} 
			
		// Oks abgleichen
			if (g_fAbglOks) {
				if (0 == g_ulOksFromAttr) {
				// Oks vom EingabeOks nehmen
				MODOBJIDENT MOI;

					INITSTRUCT(MOI, MODOBJIDENT);
					MOI.lONr = lONr;
					MOI.lNewIdent = lIdent;
					MOI.iMode = GetMOIMode (sta);
					DEX_ModObjectIdent(MOI);
				} 
				else {
				// Oks aus EingabeAttribut verwenden
				char *pOks = NULL;

					if (RetrieveText (g_ulOksFromAttr, mi, &pOks, false, !g_fImportObj) > 0) {
					// Ident über Oks besorgen
					long lNewIdent = 0;
					HRESULT hr = IdentFromClassX (hPr, pOks, (ULONG *)&lNewIdent);

						if (S_FALSE == hr) {
						ErrCode RC = IdentIsDefined(lNewIdent);
						
							if (RC != EC_OKAY && !DEX_isIdentUsedEx(hPr, lNewIdent)) 
							// neu erzeugen, wenn keine Objekte mit diesem Ident existieren
								hr = IdentFromClassX (hPr, pOks, (ULONG *)&lNewIdent, true);
						}

						if (0 != lNewIdent) {
						// jetzt Ident modifizieren
						MODOBJIDENT MOI;

							INITSTRUCT(MOI, MODOBJIDENT);
							MOI.lONr = lONr;
							MOI.lNewIdent = lNewIdent;
							MOI.iMode = GetMOIMode (sta);
							DEX_ModObjectIdent(MOI);

							lIdent = lNewIdent;
						}
					}
					DELETE_OBJ(pOks);
				}
			}

		// evtl. doch noch neues Objekt erzeugen
			if (g_fImportObj) {
				iFlags |= OGNewObject;
				fRet = ImportGeometry (hPr, pOG, sta, lIdent, gxi, gyi, iFlags, rlONr, lIgnore);
			} else
				rlONr = lONr;
		}
	}

	if (!fRet) {
		if (0 == pOG -> lONr) {
			g_lNotImported++;
			return false;
		} else {
			if (pOG -> iFlags & OGObjectHasGeometryErrors)
				g_lWithErrors++;	// mit Fehlern importiert
		}
	} 
	CountObjects (sta[1]);		// Objekte zählen

// Merkmale erzeugen
	if (m_flag || g_fAbglAttr)
		return CreateFeatures (rlONr, mi, lIdent, lIgnore);

	return true;
}

bool ImportGeometry (HPROJECT hPr, 
	OBJGEOMETRIE *pOG, long sta[], long lIdent, double *gxi, double *gyi, 
	int iFlags, long &rlONr, ULONG &lIgnore)
{
	INITSTRUCT (*pOG, OBJGEOMETRIE);
	pOG -> lONr = 0L;
	pOG -> lIdent = lIdent;
	pOG -> iFlags = short(iFlags);
	pOG -> pdblX = gxi;
	pOG -> pdblY = gyi;
	((TEXTGEOMETRIEEX &)pOG).fIndObjProp = FALSE;

	switch (sta[1]) {
	case O_PUNKT:
		pOG -> iObjTyp = OGPunkt;
		break;

	case O_LINIE:
		pOG -> iObjTyp = OGLinie;
		break;

	case O_FLAECHE:
		pOG -> iObjTyp = OGFlaeche;
		pOG -> iKCnt = AnalyzeAreaContures (lgi, gxi, gyi, &pOG -> plCnt);
		break;

	case O_TEXTOBJEKT:
		pOG -> iObjTyp = OGText;
		pOG -> iKCnt = RetrieveText (lTextObjMCode, mi, &((TEXTGEOMETRIE *)pOG) -> pText, true);
		lIgnore = lTextObjMCode;
		break;

	case O_TEXTOBJIND:
		pOG -> dwSize = sizeof(TEXTGEOMETRIEEX);
		pOG -> iObjTyp = OGLabel;
		pOG -> iKCnt = RetrieveText (lTextObjMCode, mi, &((TEXTGEOMETRIE *)pOG) -> pText, true);
		((TEXTGEOMETRIEEX &)pOG).fIndObjProp = TRUE;
		lIgnore = lTextObjMCode;
		break;
	}
	pOG -> lCnt = lgi;

GEOMETRIEWITHCS GCS;

	INITSTRUCT (GCS, GEOMETRIEWITHCS);
	GCS.pOG = pOG;
	GCS.pICS = ((CImpBnaExtension *)g_pTE)->get_CS();

bool fRet = DEX_ModObjGeometrieEx(hPr, GCS);

	DELETE_OBJ(pOG -> plCnt);
	rlONr = pOG -> lONr;		// neue ObjektNummer
	return fRet;
}

// Anzahl der Konturen einer Fläche feststellen ------------------------------
short AnalyzeAreaContures (long &lgi, double gxi[], double gyi[], long **pplCnt)
{
short lCnt = 0;
double lX = gxi[0];
double lY = gyi[0];

// Anzahl der Konturen zählen
long lLast = 0;

	for (long lIndex = 1; lIndex < lgi; lIndex++) {
		if (lX == gxi[lIndex] && lY == gyi[lIndex]) {
			lCnt++;
			lLast = lIndex+1;
			if (++lIndex < lgi) {
				lX = gxi[lIndex];
				lY = gyi[lIndex];
			}
		}
	}

	if (lLast != lgi) // letzte Kontur nicht geschlossen
		lCnt++;		// eine mehr

// Speicher anfordern und Feld füllen
long *plCnt = NULL;

	lLast = 0;
	if (lCnt > 0) {
		plCnt = new long[lCnt];

		lCnt = 0;	// wieder von vorn
		lX = gxi[0];
		lY = gyi[0];

	long lKCnt = 1;

		for (long lIndex = 1; lIndex < lgi; lIndex++) {
			lKCnt++;	// zählt Stützpunkte dieser Kontur
			if (lX == gxi[lIndex] && lY == gyi[lIndex]) {
				plCnt[lCnt++] = lKCnt;
				lLast = lIndex+1;
				if (++lIndex < lgi) {
					lX = gxi[lIndex];
					lY = gyi[lIndex];
				}
				lKCnt = 1;
			}
		}
		if (lLast != lgi)
			plCnt[lCnt++] = lKCnt;
	}

	*pplCnt = plCnt;
	return lCnt;
}

// Geometrie nicht modifizieren, nur Merkmale/Ident korrigieren ---------------
bool UpdateFeatures (LONG &rlONr, ULONG lIdent, long sta[], long mi[])
{
// Objekt wiederfinden
char *pUIdent = NULL;
	
	rlONr = 0L;
	if (RetrieveText (g_ulUniqueId, mi, &pUIdent) > 0) 
		rlONr = FindObject (g_ulUniqueId, pUIdent);

	DELETE_OBJ(pUIdent);
	if (rlONr > 0) {		// Merkmale erzeugen
		if (m_flag && !CreateFeatures (rlONr, mi, lIdent)) {
			g_lWithErrors++;	// mit Fehlern importiert
			return false;
		}

	ULONG lOldId = (ULONG)DEX_GetObjIdent (rlONr);

		if (lIdent != lOldId) {
		MODOBJIDENT MOI;

			INITSTRUCT(MOI, MODOBJIDENT);
			MOI.lONr = rlONr;
			MOI.lNewIdent = lIdent;
			MOI.iMode = 0;
			if (!DEX_ModObjectIdent (MOI)) {
				g_lWithErrors++;	// mit Fehlern importiert
				return false;
			}
		}
		CountObjects (sta[1]);
		return true;
	} else
		g_lNotImported++;		// nicht wiedergefunden

	return false;
}

extern "C" 
bool PASCAL FindObjectCallback (long lONr, bool, void *pData)
{
	*(LONG *)pData = lONr;	// Objektnummer des gesuchten Objektes
	return false;			// ein Objekt genügt
}

long FindObject (LONG lMCode, LPCSTR pcUIdent)
{
long lONr = 0;
ENUMRECHTEXTMERKMAL ERTM;

	INITSTRUCT(ERTM, ENUMRECHTEXTMERKMAL);
	ERTM.lMCode = lMCode;
	ERTM.pMWert = (char *)pcUIdent;
	ERTM.iMode = SMExactMatch;
	ERTM.eFcn = (RECHTEXTMERKMALCALLBACK)FindObjectCallback;
	ERTM.pData = &lONr;
	DEX_EnumRechTextMerkmal(ERTM);
	return lONr;
}

// KomplexObjekt erzeugen -----------------------------------------------------
bool CreateKomplexObject (HPROJECT hPr, LONG &rlONr, ULONG lIdent, long mi[])
{
OBJCREATE OC;

	INITSTRUCT (OC, OBJCREATE);
	OC.lIdent = (long)lIdent;
	OC.iObjTyp = OGKO;
	OC.iFlags = OGNewObject;

	if (DEX_ModObjGeometrieEx (hPr, OC)) {
		g_lKomplex++;
		rlONr = OC.lONr;
		return true;
	}

	rlONr = -1L;
	return false;
}

// Kodiert diverse spezielle Zeichen um ---------------------------------------
char *CodeChars (char *lpRes, const char *lpText, int iBuffLen, int iStrLen = -1)
{
char *lpResult = lpRes;

	if (-1 == iStrLen)
		iStrLen = iBuffLen;

// jetzt umkopieren
	while (*lpText && iBuffLen > 0 && iStrLen > 0) {
		if (*lpText == '\\') {
			switch (*++lpText) {
			case 'n':	// Zeilenumbruch
				*lpResult++ = '\n';
				lpText++;
				iBuffLen--;
				iStrLen--;
				break;
				
			case 't':
				*lpResult++ = '\t';
				lpText++;
				iBuffLen--;
				iStrLen--;
				break;
				
			case '\0':	// Satzende
				*lpResult = '\0';
				return lpRes;
				
			default:	// keine Sonderbedeutung
				*lpResult++ = *lpText++;
				iBuffLen--;
				iStrLen--;
				break;
			}
		} else {
			*lpResult++ = *lpText++;
			iBuffLen--;
			iStrLen--;
		}
	}
	*lpResult = '\0';
	return lpRes;
}

// Merkmale an ein Objekt anhängen --------------------------------------------
bool CreateFeatures (LONG rlONr, long MInfo[], ULONG lIdent, ULONG lMCodeIgnore)
{
long *pMK = &MInfo[2];	// erstes Merkmal
char *pText = NULL;
bool fReturn = TRUE;
HPROJECT hPr = DEX_GetObjectsProject(lIdent);

	while (pMK < &MInfo[MInfo[1] + 2] && fReturn) {	// alle Merkmale ausgeben
		if (pMK[0] != 0 && (ULONG)pMK[0] != lMCodeIgnore) {
		// noch nicht ausgegeben
		int iLen = pMK[2]*sizeof(long);

			try { pText = new char[2*iLen+1]; } catch (...) {}
			if (NULL == pText) return false;

			memset(pText, '\0', 2*iLen);
			CodeChars (pText, (LPCSTR)&pMK[3], 2*iLen, iLen);

		// zugehörigen derzeitigen MCode wiederfinden
		MAPMCODETOHANDLE MMH;
		INT_PTR lMappedMCode = NULL;
		BOOL fCreated = FALSE;
		INT_PTR lMCode = pMK[0];

			INITSTRUCT (MMH, MAPMCODETOHANDLE);
			MMH.lIdent = lIdent;
			MMH.lMCode = lMCode;
			MMH.plHandle = &lMappedMCode;
			MMH.fCreate = FALSE;
			MMH.pfCreated = &fCreated;
			DEX_MapOrCreateMCodeToHandle (hPr, MMH);

			if (NULL != lMappedMCode && (fCreated || lMCode != lMappedMCode))
				lMCode = lMappedMCode;

		// Merkmal schreiben
			if (!WriteTextMerkmal (rlONr, (ULONG)lMCode, pText, strlen(pText)))
				fReturn = FALSE;
			DELETE_OBJ(pText);
		}
		pMK = &pMK[pMK[2] + 3];
	}
	return fReturn;
}


// Schreiben eines Merkmales --------------------------------------------------
bool WriteTextMerkmal (LONG lONr, ULONG lMCode, char cbBuffer[], int iLen)
{

	int iStep = iLen;
	bool iBlank = true;

	while ( iStep > 0) {
		if (cbBuffer[iStep-1] != ' ') {
			iBlank = false;
			break;
		}
		iStep--;
	}

	if(iBlank)
		return true;

	if (lMCode == g_ulID) {	// GCO-Merkmal
		ulong lIdent = DEX_GetObjIdent (lONr);
		if ( MemoIdentifikator(lIdent) ) 
			return true;
	}

TARGETMERKMALEX gm;

	INITSTRUCT (gm, TARGETMERKMALEX);
	gm.lTarget = (LPARAM)lONr;
	gm.lMCode = (long)lMCode;
	gm.imaxLen = iLen;
	gm.pMText = cbBuffer;
	gm.iTTyp = TT_Objekt;
	gm.iFlags = TMNoCaching;

	if (DEX_ModTextMerkmal (gm) != EC_OKAY)
		return false;

	return true;
}


// Text eines Textobjektes aus Merkmalsfeld extrahieren ---------------------
short RetrieveText (ULONG lMCode, long mi[], char **ppText, bool fConvert, bool fMarkAsWritten)
{
short lLen = 0;
char *pText = FindMWert (lMCode, mi, &lLen, fMarkAsWritten);

	if (pText == NULL || lLen == 0)
		return 0;

char *pNewT = new char [2*lLen+1];

	if (pNewT == NULL) return 0;

	if (fConvert) 
		CodeChars (pNewT, pText, 2*lLen, lLen);
	else {
		strncpy (pNewT, pText, lLen);
		pNewT[lLen] = '\0';
	}

	*ppText = pNewT;
	return lLen;
}


// Finden eines Merkmales im MerkmalsFeld -------------------------------------
char *FindMWert (ULONG lMCode, long pMInfo[], short *plLen, bool fMarkAsWritten)
{
	TX_ASSERT (0 != lMCode);

long *pMK = &pMInfo[2];		// erstes Merkmal

	*plLen = 0;
	while (pMK < &pMInfo[pMInfo[1] + 2]) {	// alle Merkmale ausgeben
		if ((ULONG)pMK[0] == lMCode) {	// MCode gefunden
			if (fMarkAsWritten)
				pMK[0] = 0;		// MWert bereits ausgegeben
			*plLen = (pMK[2]*sizeof(long));
			return (char *)&pMK[3];
		}

		if (pMK[2] == -1L) 	// O_TEXTOBJIND
			pMK = &pMK[4];
		else
			pMK = &pMK[pMK[2] + 3];
	}

return NULL;
}

// Aufbauen einer Relation ----------------------------------------------------
bool CreateRelation (LONG lPONr, LONG lSONr, ULONG lRCode, short iRTyp)
{
MODRELATION MR;

	INITSTRUCT (MR, MODRELATION);
	MR.lPONr = lPONr;
	MR.lSONr = lSONr;
	MR.lRCode = (long)lRCode;
	MR.iRTyp = iRTyp;
	return DEX_ModifyRelation (MR);
}

//////////////////////////////////////////////////////////////////////////////////////
//
void PolyInit (void)
{
	fFirstIdent = true;
	fFirstMCode = true;

// Scale/Offset verwalten
	fWasScaleProject = false;
	fWasOffsetProject = false;
	fWriteOffsetProject = false;
	fWriteScaleProject = false;	

	fWasScale = false;
	fWasOffset = false;
	fWriteOffset = false;
	fWriteScale = false;	

// ZählerVariablen ------------------------------------------------------------
	g_lPoints = 0;
	g_lLines = 0;
	g_lAreas = 0;
	g_lTexts = 0;
	g_lKomplex = 0;

	g_lWithErrors = 0;
	g_lNotImported = 0;
	g_lTime = 0;

// Verwalten der Koordinatenparameter ---------------------------------
	g_dOffsetX = 0.0;
	g_dOffsetY = 0.0;
	g_dScaling = 1.0;

// Verwalten des lIdent für PolyGIS-Klassen ---------------------------------
	g_ulPolyId = 0L;
	g_ulPolyIdTyp = 0L;

// Verwalten des MCodes für den Unique Ident ---------------------------------
	g_ulUniqueId = 0L;
	g_ulOrgUniqueId = 0L;
	g_ulOldUniqueId = 0L;


// Verwalten des MCodes für den PolyGIS-BNA ---------------------------------
	g_ulName1 = 0L;
	g_ulName2 = 0L;
	g_ulID = 0L;

	g_ulMemo = 0L;
	g_ulOrdnung = 0L;

}

//----------------------------------------------------------------------------
HRESULT RestoreRegistryKey (void)
{
// Registry-Einträge
ResString BNAKeyName1 (ResID(IDS_BNAKEYNAME1, &g_pTE->RF()), 80);
ResString BNAKeyName2 (ResID(IDS_BNAKEYNAME2, &g_pTE->RF()), 80);
ResString BNAKeyID (ResID(IDS_BNAKEYID, &g_pTE->RF()), 80);
ResString BNASuffix (ResID(IDS_BNAKEYSUFFIX, &g_pTE->RF()), 80);
ResString MEMO (ResID(IDS_BNAKEYMEMO, &g_pTE->RF()), 80);
ResString ORDNUNG (ResID(IDS_BNAKEYORDNUNG, &g_pTE->RF()), 80);
ResString MEMOKlasse (ResID(IDS_KEYMEMOKLASSE, &g_pTE->RF()), 80);
ResString MEMOKlasseReplace (ResID(IDS_KEYMEMOKLASSEREPLACE, &g_pTE->RF()), 80);
ResString BNALayer (ResID(IDS_BNALAYER, &g_pTE->RF()), 80);

	strcpy (g_cName1Buff, RetrieveFromKeyTree(BNAKeyName1));
	strcpy (g_cName2Buff, RetrieveFromKeyTree(BNAKeyName2));
	strcpy (g_cIDBuff, RetrieveFromKeyTree(BNAKeyID));
	strcpy (g_cSuffix, RetrieveFromKeyTree(BNASuffix));
	strcpy (g_cMemo, RetrieveFromKeyTree(MEMO));
	strcpy (g_cOrdnung, RetrieveFromKeyTree(ORDNUNG));
	strcpy (g_cMemoKlasse, RetrieveFromKeyTree(MEMOKlasse));
	strcpy (g_cMemoKlasseReplace, RetrieveFromKeyTree(MEMOKlasseReplace));
	strcpy (g_cBNALayer, RetrieveFromKeyTree(BNALayer));
	return S_OK;
}

//-----------------------------------------------------------------------------
bool MemoIdentifikator(HOBJECTS lIdent)
{
ErrInstall EI (WC_NOIDENT);
PBDDATA pbdData;
char cbKText[34];

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = cbKText;
	pbdData.pbdLText = NULL;
	pbdData.pbdKTextLen = 0;
	pbdData.pbdLTextLen = 0;

// PBD-Info holen
	if (EC_OKAY == DEX_GetPBDDataEx (g_hPr, pbdData))
		return RetrieveFromMemoTree(cbKText);
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Baum der Konfigurationsdaten 
bool StoreInKeyTree (const char *pKey, const char *pWert) 
{
	if (g_BNAKey == NULL) {
	// erstes Element: Baum muß angelegt werden
		g_BNAKey = new TR_OKSTree();
		if (g_BNAKey == NULL) 
			return false;
	}

CTable t (*g_BNAKey);

	if (!t.Find ((void *)pKey)) {
	TR_OKSCreator OSCr (*g_BNAKey);

		return ContCreate(OSCr, TR_OKS)(pKey, pWert) != NULL;
	} 
	else {
	TR_OKSLock l(t);
	
		return l->SetWert(pWert);
	}
}

// Wiederauffinden einer ObjektNummer an Hand einer gegebenen SatzNummer
char const *RetrieveFromKeyTree (const char *pKey) 
{
	if (g_BNAKey == NULL) 
		return NULL;

CTable t (*g_BNAKey);

	if (t.Find ((void *)pKey)) {
	TR_OKSLock l(t);

		if (l) 
			return l -> Wert();
	}

	_ASSERTE(FALSE);		// snh
	return "";
}

// Baum wieder zurücksetzen
void ResetKeyTree (void) 
{
	DELETE_OBJ(g_BNAKey);
}

///////////////////////////////////////////////////////////////////////////////
// Baum der OKSKlassen
int StoreInOKSTree (const char *pBNAText, DWORD dwType, HPROJECT hPr, 
	bool fImportAttributes) 
{
	if (NULL == g_OKSTree) {
	// erstes Element: Baum muß angelegt werden
		g_OKSTree = new TR_LayerTree();
		if (g_OKSTree == NULL) return false;
	}

// Memoklassen müssen ggf. auf andere OKS gematched werden
	char cbText[_MAX_PATH];

	strcpy (cbText, pBNAText);

	bool fModified = false;

	if ('\0' != g_cMemoKlasseReplace[0]) {
	char *cptr = strrchr (cbText, '_');

		if (cptr && !strcmp (g_cMemoKlasse, cptr)) {
			strcpy (cptr, g_cMemoKlasseReplace);	// ggf. Suffix austauschen
			fModified = true;
		}
	}

// Objektklasse zur späteren Verwendung speichern
	HOBJECTS lIdent = ClassIsDefined(cbText, hPr);


// KK021219 - nur für Video
if ( m_iMode == GPSIMPORT ) {
	if ( lIdent == 0 )
		lIdent = IdentScriptIsDefined (cbText);
}


CTable t (*g_OKSTree);

	if (!t.Find((void *)pBNAText)) {
	TR_LayerCreator OSCr (*g_OKSTree);
	TR_Layer *pLayer = ContCreate(OSCr, TR_Layer)(pBNAText, lIdent, dwType, fImportAttributes);

		if (NULL == pLayer)
			return false;
		if (fModified)
			pLayer -> SetKurzText(dwType, cbText, hPr);
	}
	else {
	TR_LayerLock l(t);

		if (l) {
			l -> AddType(lIdent, dwType);
			l -> SetImportAttributes(fImportAttributes, dwType);
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Wiederauffinden BNAText
//int RetrieveFromOKSTree (const char *pBNAText) 
//{
//	if (g_OKSTree == NULL) 
//		return false;
//
//CTable t (*g_OKSTree);
//
//	if (t.Find ((char *)pBNAText)) {
//	TR_LayerLock l(t);
//
//		if (l) 
//			return true;
//	}
//	return false;
//}

// Wiederauffinden AbgleichStatus über BNAText 
//int RetrieveAbgleichFromOKSTree (const char *pBNAText) 
//{
//	if (g_OKSTree == NULL) 
//		return -1;
//
//CTable t (*g_OKSTree);
//
//	if (t.Find ((char *)pBNAText)) {
//	TR_LayerLock l(t);
//
//		if (l) 
//			return l->Abgleich();
//	}
//	return -1;
//}

//--------------------------------------------------------------------------------
// Wiederauffinden AbgleichStatus über BNAText 
//int RetrieveAbgleichOKSTree (void) 
//{
//	if (g_OKSTree == NULL) 
//		return -1;
//
//int iAbgleich = 1;	// alles ok
//CTable t (*g_OKSTree);
//
//	for (t.First(); t.Valid(); t.Next()) {
//	TR_LayerLock l(t);
//
//		if (l) 
//			iAbgleich = l->Abgleich();
//
//		if (0 == iAbgleich)			// Wenigstens einer nicht definiert
//			return iAbgleich;
//	}
//	return iAbgleich;
//}

//--------------------------------------------------------------------------------
// Baum wieder zurücksetzen
void ResetOKSTree (void) 
{
	DELETE_OBJ(g_OKSTree);
}

///////////////////////////////////////////////////////////////////////////////
// Baum der MemoKlassen
int StoreInMemoTree (char const *pWert) 
{
	if (g_MemoTree == NULL) {
	// erstes Element: Baum muß angelegt werden
		g_MemoTree = new TR_OBJTree();
		if (g_MemoTree == NULL) return false;
	}

CTable t (*g_MemoTree);

	if (!t.Find (const_cast<char *>(pWert))) {
	TR_OBJCreator OSCr (*g_MemoTree);

		return ContCreate(OSCr, TR_OBJ)(pWert) != NULL;
	}
	return true;
}

// Wiederauffinden einer ObjektNummer an Hand einer gegebenen SatzNummer
int RetrieveFromMemoTree (char const *pWert) 
{
	if (g_MemoTree == NULL) 
		return false;

CTable t (*g_MemoTree);

	if (t.Find (const_cast<char *>(pWert))) {
	TR_OBJLock l(t);

		if (l) 
			return true;
	}
	return false;
}

// Baum wieder zurücksetzen
void ResetMemoTree (void) 
{
	DELETE_OBJ(g_MemoTree);
}

