// ImportDialog in neuer Fassung über COMMDLG.DLL -----------------------------
// File: IMPDLG.CXX

#include "triaspre.hxx"

#include <windowsx.h>
#include <dlgs.h>

#if !defined(WIN32)
#include <toolhelp.h>
#endif
#include <registry.hxx>

#include <eieruhr.hxx>
#include <ixtensn.hxx>
#include <xtsnguid.h>

#if defined(WIN32)
#include <dirisole.h>
#include "extmain3.hxx"
#endif

#include "strings.h"
#include "ienumstr.hxx"
#include "impdlg.hxx"           
#include "triasres.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern HINSTANCE hInstance;

#if !defined(WIN32)
bool IsWin40 (void);
bool IsWin32s (void);
#endif

#define MAXFORMATS	32	// maximale dynamische Formatanzahl je Erweiterung

// Aufrufende Funktion --------------------------------------------------------
bool ExtDirisWindow :: doImport (void)
{
#if defined(WIN32)
	if (NULL == m_pView)
		return false;
#endif // WIN32

// Fenster aufmachen
CImportDlg *pIDlg = CImportDlg :: CreateInstance (this, *m_pEL, DBO().pCT());

	if (pIDlg == NULL) return false;	// InitialisierungsFehler
		
	pIDlg -> Show();
	if (pIDlg -> Result()) {
	LPIMPORTGEODATA pIImport = NULL;
	HRESULT hr = pIDlg -> GetImportIF (&pIImport);

		if (SUCCEEDED(hr)) {
		LPENUMSTRING pIStrings = NULL;
		
			hr = pIDlg -> GetStrings (&pIStrings);
			if (SUCCEEDED(hr)) {
			// eigentlicher Import
				pIImport -> ImportData (pIStrings, pIDlg -> GetFlags());
				pIStrings -> Release();
			}
			pIImport -> Release();	// wieder freigeben
		}
	}
	DELETE (pIDlg);		// hier wird die Erweiterung rausgeworfen

return true;
}


// Konstruktor/Destruktor -----------------------------------------------------
CImportDlg :: CImportDlg (pWindow pW, ExtensionList &rEL, CoordTrans *pCTF)
	    : COpenDialog (pW, RetrieveAvailImportFormats (rEL)),
	      m_rEL (rEL), m_fValid(false), m_pParent (pW), m_pCTF(pCTF), m_pW(pW)
{
#if defined(WIN32)
	m_lSem = -1;
#endif // WIN32

	SetGeometry (false);
	SetFeatures (false);
	SetRelations (false);
	SetVisualisation (false);
	SetAnsiOem (false);

	SetCanGeometry (false);
	SetCanFeatures (false);
	SetCanRelations (false);
	SetCanVisualisation (false);
	SetCanAnsiOem (false);

	SetCanConfig (false);
	SetMultiSel (false);

	m_iIndex = -1;
	m_pInFile = NULL;
	m_ppFiles = NULL;
	m_iCnt = 0;
	m_pInitPath = NULL;

	m_pIImport = NULL;
}

CImportDlg *CImportDlg :: CreateInstance (pWindow pW, ExtensionList &rEL, CoordTrans *pCTF)
{
CImportDlg *pDlg = new CImportDlg (pW, rEL, pCTF);

	if (pDlg == NULL || !pDlg -> FInit()) {
		DELETE (pDlg);
		return NULL;
	}

return pDlg;
}

bool CImportDlg :: FInit (void)
{
// FileTypes wird in RetrieveAvailImportFormats initialisiert
ResString resCaption (IDS_IMPORTFMTDLGCAP, 80);

	m_fValid = (m_pFileTypes != NULL) ? true : false;
	if (!m_fValid) {	// kein Importfilter installiert
		VMessageBox (m_pParent, IDS_IMPORTFMTDLGCAP, 
					ExclamationIcon|OkayButton, IDS_NOIMPORTFILTERS);
		return false;
	}

#if defined(WIN32)
	if (IsWin40()) {
		AddFlags (OFN_EXPLORER|OFN_LONGNAMES|OFN_ALLOWMULTISELECT);
		SetHookFcn ((HOOKFCN)ImportFmt40HookFcn);
		SetTemplate (hInstance, MAKEINTRESOURCE(IMPORTFMT40SUBDLG));
	} else
#endif
	{	// SonderWünsche einstellen
		if (IsWinNT()) 
			AddFlags (OFN_LONGNAMES);
		m_iFileOKMessage = RegisterWindowMessage (FILEOKSTRING);
		SetHookFcn ((HOOKFCN)ImportFmtHookFcn);
		SetTemplate (hInstance, MAKEINTRESOURCE(IMPORTFMTDLG));
	}
	SetCustomData ((DWORD)(void *)this);
	SetCaption (resCaption);
	SetFilterIndex (1);
	AddFlags (OFN_HIDEREADONLY);

// AnfangsVerzeichnis auf das aktuelle Projektverzeichnis setzen
	m_pInitPath = new char [_MAX_PATH];
	if (m_pInitPath && DEX_GetActiveProject (m_pInitPath) != NULL) {
	char *pPath = new char [_MAX_PATH];
	char *pDrive = new char [_MAX_DRIVE];

		_splitpath (m_pInitPath, pDrive, pPath, NULL, NULL);
		_makepath (m_pInitPath, pDrive, pPath, g_cbNil, g_cbNil);
		SetInitialDir (m_pInitPath);
		DELETE_VEC (pPath);
		DELETE_VEC (pDrive);
	}

return true;
}


CImportDlg :: ~CImportDlg (void)
{
	UnLoadExtension();

	DELETE_VEC (m_pFileTypes);
	DELETE_VEC (m_pInitPath);
	DELETE_VEC (m_pInFile);
	DELETE_VEC (m_pFilterInfo);

	if (m_ppFiles) {
		DELETE(m_ppFiles[0]);
	}
	DELETE_VEC(m_ppFiles);
}


// Memberfunktionen -----------------------------------------------------------
bool CImportDlg :: ReadFileName (void)
{
	if (m_pInFile != NULL) return true;	// bereits abgefragt

int iCurrLen = GetFileNameLen();

	if (iCurrLen <= 0) return false;

// einlesen der Dateinamen
LPSTR pTemp = new char [iCurrLen+1];

	if (NULL == pTemp) return false;

	m_pInFile = new char [iCurrLen+1];
	if (NULL == m_pInFile) return false;

	GetFileName (pTemp, iCurrLen);

// Analyse des Strings, evtl. zerlegen und generieren des ersten Namens
int i = 0;
LPSTR pT = pTemp;

#if defined(WIN32)
	m_iCnt = 0;
	do {
	int iLen = strlen (pT) +1;

		pT += iLen;
		i += iLen;
		++m_iCnt;
	} while (i <= iCurrLen && '\0' != *pT);
#else          
	m_iCnt = 1;
#endif // WIN32

	strcpy (m_pInFile, pTemp);

// wenn Multisel, dann in m_pInFile ersten Dateinamen zusammenbauen
	if (m_iCnt > 1) {
		m_ppFiles = new char * [m_iCnt];		// Dateinamen
		if (NULL == m_ppFiles) {
			DELETE (pTemp);
			return false;
		}
		
	// Parsen der Eingabe und zerlegen in ein Pointerfeld
		pT = pTemp;
		i = 0;
		do {
		int iLen = strlen (pT) +1;

			m_ppFiles[i++] = pT;
			pT += iLen;
		} while (i < m_iCnt);

		strcpy (m_pInFile, pTemp);
		if (m_pInFile[strlen(m_pInFile)-1] != '\\')
			strcat (m_pInFile, "\\");
		strcat (m_pInFile, m_ppFiles[1]);

	// m_ppFiles[0] hat pTemp übernommen --> wird im dtor freigegeben
	} else {
		DELETE (pTemp);
	}

return true;
}

// Alle Dateien ausgewählt: über Dateierweiterung suchen ----------------------
int CImportDlg :: FindFilterExt (void)
{
	if (!ReadFileName()) return m_iNumFilters;

char cbExt[_MAX_EXT];

	_splitpath (m_pInFile, NULL, NULL, NULL, cbExt);
	strlwr (cbExt);

// Erweiterung in der Liste der Filter suchen
	for (int iIndex = 0; iIndex < m_iNumFilters; iIndex++) {
		if (!strcmp (m_pFilterInfo[iIndex].m_strFilterExt.c_str()+1, cbExt))
			break;
	}

return iIndex;
}

HRESULT CImportDlg :: GetImportIF (LPIMPORTGEODATA *pIImport)
{
	if (m_pIImport == NULL) return ResultFromScode (E_FAIL);

return m_pIImport -> QueryInterface (IID_IImportGeoData, (LPVOID *)pIImport);
}

HRESULT CImportDlg :: GetStrings (LPENUMSTRING *pIStrings)
{
// DateiNamen abfragen
	if (!ReadFileName()) return ResultFromScode (E_FAIL);

// Enumerator anlegen
CImpIEnumStrings *pEnum = CImpIEnumStrings :: CreateInstance();

	if (pEnum == NULL) return ResultFromScode(E_OUTOFMEMORY);

// Dateinamen in Enumerator reinbefördern (z.Zt. nur eine Datei)
	if (FMultiSel() && m_iCnt > 1) {
		TX_ASSERT(NULL != m_ppFiles);

	string str;
	int i = 1;

		while (i < m_iCnt) {
			str = m_ppFiles[0];
			if (str.rfind ('\\') != str.length())
				str += '\\';
			str += m_ppFiles[i++];
			pEnum -> AddString (str.c_str());	// eingelesener DateiName
		}
	} 
	else {
#if defined(WIN32)
		if (!FMultiSel() && m_iCnt > 1) {
		// Warnung, wenn nicht MultiSel aber mehrere Dateien ausgewählt
			VMessageBox (m_pParent, IDS_IMPORTFMTDLGCAP, 
						ExclamationIcon|OkayButton, 
						IDS_IMPORTNOMULTISEL, m_pInFile);
		}
#endif
	// nur eine Datei gegeben oder nicht MultiSel
		TX_ASSERT(NULL != m_pInFile);

		pEnum -> AddString (m_pInFile);		// eingelesener DateiName
	}

// Interface abfragen
HRESULT hr = pEnum -> QueryInterface (IID_IEnumString, (LPVOID *)pIStrings);

	pEnum -> Release();		// wird nicht mehr gebraucht

return hr;
}


// ImportOptionen abholen -----------------------------------------------------
DWORD CImportDlg :: GetFlags (void)
{
DWORD rgFlags = FImportGeometry() ? TOIMPORT_GEOMETRY : 0;	// Geometrie importieren

	if (FImportFeatures()) 
		rgFlags |= TOIMPORT_FEATURES;		// Merkmale importieren
	if (FImportRelations()) 
		rgFlags |= TOIMPORT_RELATIONS;		// Relationen importieren
	if (FImportVisualisation()) 
		rgFlags |= TOIMPORT_VISUALISATION;	// Visualisierung importieren
	if (FImportAnsiOem()) 
		rgFlags |= TOIMPORT_ANSIOEM;		// explizit in ANSI konvertieren

return rgFlags;
}

void CImportDlg :: SetFlags (DWORD rgFlags)
{
	SetGeometry ((rgFlags & IMPORTCAPS_CANIMPORTGEOMETRY) ? true : false);
	SetFeatures ((rgFlags & IMPORTCAPS_CANIMPORTFEATURES) ? true : false);
	SetRelations ((rgFlags & IMPORTCAPS_CANIMPORTRELATIONS) ? true : false);
	SetVisualisation ((rgFlags & IMPORTCAPS_CANIMPORTVISUALISATION) ? true : false);
	SetAnsiOem ((rgFlags & IMPORTCAPS_CANIMPORTANSIOEM) ? true : false);

	SetCanGeometry ((rgFlags & IMPORTCAPS_OPTIMPORTGEOMETRY) ? true : false);
	SetCanFeatures ((rgFlags & IMPORTCAPS_OPTIMPORTFEATURES) ? true : false);
	SetCanRelations ((rgFlags & IMPORTCAPS_OPTIMPORTRELATIONS) ? true : false);
	SetCanVisualisation ((rgFlags & IMPORTCAPS_OPTIMPORTVISUALISATION) ? true : false);
	SetCanAnsiOem ((rgFlags & IMPORTCAPS_OPTIMPORTANSIOEM) ? true : false);

	SetCanConfig ((rgFlags & IMPORTCAPS_SHOULDCONFIG) ? true : false);
	SetMultiSel ((rgFlags & IMPORTCAPS_MULTIPLEFILES) ? true : false);
}

// Binden der ImportErweiterung, abfragen der Caps etc. -----------------------
bool CImportDlg :: UpdateControls (int iIndex)
{
	if (iIndex < 0 || iIndex > m_iNumFilters)
		return false;

	if (iIndex == m_iNumFilters) 	// Alle Dateien (*.*) gewählt
		return false;

	if (iIndex == m_iIndex)	return true;	// alles ok

IMPORTFILTERINFO *pFI = &m_pFilterInfo[iIndex];

	if (0 <= m_iIndex) {
	IMPORTFILTERINFO *pFIAct = &m_pFilterInfo[m_iIndex];
	
		if (pFIAct -> m_strProgID == pFI -> m_strProgID)
			return true;	// immer noch die gleiche Erweiterung
	}

#if defined(WIN32)
	if (piInterlockedIncrement(&m_lSem) > 0) {
		piInterlockedDecrement(&m_lSem);
		return true;	// nicht verschachteln
	}
#endif // WIN32

COleExtension *pExt = LoadExtension (pFI -> m_strProgID, pFI -> m_strFilterName);

#if defined(WIN32)
	piInterlockedDecrement (&m_lSem);	// Semaphore freigeben
#endif // WIN32

	if (NULL == pExt) return false;

	if (m_iIndex >= 0) 	// vorhergehende Erweiterung freigeben
		UnLoadExtension();	

	if (FAILED(pExt -> GetImportIF (&m_pIImport)))
		return false;

	SetFlags (m_pIImport -> Capabilities());
	m_iIndex = iIndex;

return true;
}

COleExtension *CImportDlg :: LoadExtension (string &rstrProgID, string &rstrName)
{
CEierUhr Wait (m_pParent);

// Erweiterung, die zur aktuellen Auswahl paßt, laden
LOADEXTENSIONEX LE;

	LE.m_pDesc = (char *)rstrName.c_str();
	LE.m_pName = (char *)rstrProgID.c_str();
	LE.m_iMode = LEInitOnly;		// nur initialisieren
	LE.m_fGlobal = true;

HDEX hDex = DEX_ExternalLoadExtensionEx (LE);
COleExtension *pExt = NULL;

	if (hDex == NULL) return NULL;

return (COleExtension *)m_rEL.FindExt (hDex);
}

void CImportDlg :: UnLoadExtension (void)
{
	if (m_iIndex < 0 || m_iIndex >= m_iNumFilters) 
		return;		// nichts geladen

	if (m_pIImport) {
		m_pIImport -> Release();
		m_pIImport = NULL;
	}

	UnLoadExtension (m_pFilterInfo[m_iIndex].m_strProgID, m_pFilterInfo[m_iIndex].m_strFilterName);
}

void CImportDlg :: UnLoadExtension (string &rstrProgID, string &rstrName)
{
LOADEXTENSIONEX LE;

	LE.m_pDesc = (char *)rstrName.c_str();
	LE.m_pName = (char *)rstrProgID.c_str();
	LE.m_iMode = LENoLoad;		// wirklich rauswerfen
	LE.m_fGlobal = true;
	DEX_ExternalUnLoadExtensionEx (LE);
	m_iIndex = -1;
}

void CImportDlg :: InitControls (HWND hDlg)
{
	SendDlgItemMessage (hDlg, IDC_IMPORTGEOMETRY, BM_SETCHECK, FImportGeometry(), 0);
	SendDlgItemMessage (hDlg, IDC_IMPORTFEATURES, BM_SETCHECK, FImportFeatures(), 0);
	SendDlgItemMessage (hDlg, IDC_IMPORTRELATIONS, BM_SETCHECK, FImportRelations(), 0);
	SendDlgItemMessage (hDlg, IDC_IMPORTVISUALISATION, BM_SETCHECK, FImportVisualisation(), 0);
	SendDlgItemMessage (hDlg, IDC_IMPORTANSIOEM, BM_SETCHECK, FImportAnsiOem(), 0);

	EnableWindow (GetDlgItem (hDlg, IDC_IMPORTGEOMETRY), FCanGeometry());
	EnableWindow (GetDlgItem (hDlg, IDC_IMPORTFEATURES), FCanFeatures());
	EnableWindow (GetDlgItem (hDlg, IDC_IMPORTRELATIONS), FCanRelations());
	EnableWindow (GetDlgItem (hDlg, IDC_IMPORTVISUALISATION), FCanVisualisation());
	EnableWindow (GetDlgItem (hDlg, IDC_IMPORTANSIOEM), FCanAnsiOem());

	EnableWindow (GetDlgItem (hDlg, IDB_CONFIG), FCanConfig());
}


// testet, ob wenigstens eine Option aktiv ist --------------------------------
bool CImportDlg :: FlagsInvalid (void)
{
	if (m_pIImport == NULL) return true;	// nichts ausgewählt

return !(m_pIImport -> Capabilities() & GetFlags());
}


// Initialisieren der zusätzlichen Controls -----------------------------------
LRESULT CImportDlg :: OnWmInitDialog (HWND hDlg, HWND hDlgP)
{
#if defined(WIN32)
// nicht ganz genau in die Mitte, damit KoordinatenFenster besser zu erkennen ist
RECT rc;

	if (IsWin40()) {
		CentreWindow (::GetParent (hDlgP), hDlgP);	// zentrieren
		GetWindowRect (hDlgP, &rc);
		SetWindowPos (hDlgP, NULL, max(rc.left-40, 0), max(rc.top-40, 0), 0, 0, 
					  SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOZORDER);
	} else {
	// Win32s
		CentreWindow (hDlgP, hDlg);	// zentrieren
		GetWindowRect (hDlg, &rc);
		SetWindowPos (hDlg, NULL, max(rc.left-40, 0), max(rc.top-40, 0), 0, 0, 
					  SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOZORDER);
	}
#else
// KoordinatenSystem ist konfigurierbar
	EnableWindow (GetDlgItem (hDlg, IDC_COORDSYS), m_pCTF -> CanConfig());
#endif // WIN32
//	InitControls (hDlg);	// Controls initialisieren

return true;
}

// WM_COMMAND geschickt, drückt Nutzer Knöpfchen? -----------------------------
LRESULT CImportDlg :: OnWmCommand (HWND hDlg, WPARAM wParam, LPARAM lParam)
{
UINT uiID = GET_WM_COMMAND_ID (wParam, lParam);
HWND hCntrl = GET_WM_COMMAND_HWND (wParam, lParam);
UINT uiCmd = GET_WM_COMMAND_CMD (wParam, lParam);

	if (uiCmd == BN_CLICKED) switch (uiID) {
	case IDC_IMPORTGEOMETRY:
		SetGeometry (SendDlgItemMessage (hDlg, uiID, BM_GETCHECK, 0, 0) ? true : false);
		return true;

	case IDC_IMPORTFEATURES:
		SetFeatures (SendDlgItemMessage (hDlg, uiID, BM_GETCHECK, 0, 0) ? true : false);
		return true;

	case IDC_IMPORTRELATIONS:
		SetRelations (SendDlgItemMessage (hDlg, uiID, BM_GETCHECK, 0, 0) ? true : false);
		return true;

	case IDC_IMPORTVISUALISATION:
		SetVisualisation (SendDlgItemMessage (hDlg, uiID, BM_GETCHECK, 0, 0) ? true : false);
		return true;

	case IDC_IMPORTANSIOEM:
		SetAnsiOem (SendDlgItemMessage (hDlg, uiID, BM_GETCHECK, 0, 0) ? true : false);
		return true;

	case IDB_CONFIG:
		if (m_pIImport && SUCCEEDED(m_pIImport -> Configure(hDlg)))
			return true;
		return false;

	case IDC_COORDSYS:
		return SelectCoordSysParams (GetParent(), IDS_IMPORTFMTDLGCAP, m_pCTF);

	default:
		break;
	}

	if (!IsWin40() && CBN_SELCHANGE == uiCmd && cmb1 == uiID) {	// neuer Dateityp ausgewählt
	int iIndex = (int)SendDlgItemMessage (hDlg, cmb1, CB_GETCURSEL, 0, 0);
	
	// Controls entsprechend ImportFilter setzen
		if (LB_ERR != iIndex) {
			if (UpdateControls (iIndex))
				InitControls (hDlg);
			else if (0 != iIndex) {
				MessageBeep (MB_OK);
				SendDlgItemMessage (hDlg, cmb1, CB_SETCURSEL, 0, 0);
			}
		}
	}

return false;
}


// HookFunktion ---------------------------------------------------------------
extern bool g_fCtl3dInit;
static CImportDlg *s_pDlg = NULL;

extern "C"
UINT EXPORTTRIAS CALLBACK ImportFmtHookFcn (HWND hDlg, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	switch (wMsg) {
	case WM_INITDIALOG:		// Pointer auf CImportDlg holen
		{
			if (g_fCtl3dInit) 
				Ctl3dSubclassDlg (hDlg, CTL3D_ALL);
			s_pDlg = (CImportDlg *) (((OPENFILENAME *)lParam) -> lCustData);
			s_pDlg -> OnWmInitDialog (hDlg, hDlg);

			if (s_pDlg -> UpdateControls (0)) {
				s_pDlg -> InitControls (hDlg);
				return true;
			}
			return false;
		}
		
	case WM_DESTROY:	// letzte Message an uns
		s_pDlg = NULL;		// AusgangsZustand wieder herstellen
		break;

	case WM_COMMAND:
		return s_pDlg ? (UINT)s_pDlg -> OnWmCommand (hDlg, wParam, lParam) : false;

	default:
		if (NULL != s_pDlg && wMsg == s_pDlg -> m_iFileOKMessage) 
			return s_pDlg -> FlagsInvalid();	// evtl. Fehler, nicht schließen
		break;
	}

return false;
}


#if defined(WIN32)

// Diese Funktion wird nur unter 40 installiert und gerufen -------------------
extern "C" 
UINT EXPORTTRIAS APIENTRY ImportFmt40HookFcn (HWND hDlg, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	switch (wMsg) {
	case WM_NOTIFY:
		{
		LPOFNOTIFY pofn = (LPOFNOTIFY)lParam;

			switch (pofn->hdr.code) {
			case CDN_INITDONE:
				s_pDlg = (CImportDlg *)(pofn -> lpOFN -> lCustData);
				s_pDlg -> OnWmInitDialog (hDlg, ::GetParent (hDlg));

				if (s_pDlg -> UpdateControls (0)) {
					s_pDlg -> InitControls (hDlg);
					return true;
				}
				return false;

			case CDN_TYPECHANGE:
				return s_pDlg -> OnCdnTypeChange (hDlg);

			case CDN_FILEOK:	// user has pressed OK
				SetWindowLong (hDlg, DWL_MSGRESULT, s_pDlg -> FlagsInvalid());
				return true;	// evtl. nicht schließen !
				
			default:
				break;
			}
		}
		break;

	case WM_DESTROY:
		s_pDlg = NULL;
		break;

	case WM_COMMAND:
		return s_pDlg ? s_pDlg -> OnWmCommand (hDlg, wParam, lParam) : false;

	default:		// no actions
		break;
	}
			
return FALSE;	// erstmal alles weiterleiten
}

LRESULT CImportDlg :: OnCdnTypeChange (HWND hDlg)
{
int iIndex = SendDlgItemMessage (::GetParent(hDlg), cmb1, CB_GETCURSEL, 0, 0);

	if (iIndex == LB_ERR)	return false;

	if (UpdateControls (iIndex))	// Controls entsprechend ImportFilter setzen
		InitControls (hDlg);
	else if (m_iIndex != 0) {
		MessageBeep (MB_OK);
		SendDlgItemMessage (::GetParent(hDlg), cmb1, CB_SETCURSEL, 0, 0);
	}

return true;
}

#endif // WIN32

// Bilden der Dateibeschreibungen für Dateitypauswahl im Dialog -----------------
inline char *EOS (char *pStr) { return &pStr[strlen(pStr)]; }

char *CImportDlg :: RetrieveAvailImportFormats (ExtensionList &rEL)
{
// registrierte Filter einlesen
	m_pFileTypes = NULL;
	m_pFilterInfo = NULL;
	m_iNumFilters = 0;

	if (!ReadFormats (rEL)) return (char *)g_cbNil;

	m_pFileTypes = new char [m_iNumFilters * _MAX_PATH];
	if (m_pFileTypes == NULL) return (char *)g_cbNil;

// Dateibeschreibungsstring zusammenbauen
	*m_pFileTypes = '\0';
	for (int i = 0; i < m_iNumFilters; i++) {
		wsprintf (EOS(m_pFileTypes), TEXT("%s (%s)|%s|"), 
			  m_pFilterInfo[i].m_strShortName.c_str(), 
			  m_pFilterInfo[i].m_strFilterExt.c_str(),
			  m_pFilterInfo[i].m_strFilterExt.c_str());
	}
	*(EOS(m_pFileTypes)-1) = '\0';	// letztes '|' weglöschen

return m_pFileTypes;
}
 
// FilterNamen aus TRIAS20.INI einlesen -----------------------------------------
bool CImportDlg :: ReadFormats (ExtensionList &rEL) 
{
// Feststellen, wieviele Erweiterungen überhaupt importieren können
CTable r(rEL);

// Anzahl der installierten ImportFilter feststellen
	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		TX_ASSERT(NULL != (Extension *)l);
		if (l -> GetFlags() & EF_DynImportCfg) 
			m_iNumFilters += MAXFORMATS;		// maximal 32 Formate je Erweiterung
		else if (l -> GetFlags() & EF_CanImport)
			m_iNumFilters++;
	}

// Daten über Importfilter aus Registry einlesen
	if (m_iNumFilters > 0) {
		m_pFilterInfo = new IMPORTFILTERINFO [m_iNumFilters];
		if (m_pFilterInfo == NULL) return false;

	// Filterbeschreibung aus Registry lesen
	char cbKey[_MAX_PATH];
	ULONG lLen = _MAX_PATH;
	int i = 0;
	string strProgID, strName;
	DWORD dwFlags = 0L;

		for (i = 0, r.First(); r.Valid() && i < m_iNumFilters; r.Next()) {
		IMPORTFILTERINFO *pFI = &m_pFilterInfo[i];

			{
			ExtensionLock l(r);

				TX_ASSERT(NULL != (Extension *)l);
				strName = l -> ExtName();
				strProgID = l -> DLLName();
				dwFlags = l -> GetFlags();
			}

/*
			if (dwFlags & EF_DynImportCfg) {
			// Strings dynamisch von Erweiterung abfragen
			COleExtension *pExt = LoadExtension (strProgID, strName);

				if (NULL != pExt) {
				IEnumString *pIStr = NULL;
				HRESULT hr = pExt -> GetConfigInfo (&pIStr);

					if (SUCCEEDED(hr)) {
					LPWSTR pCfgStr = NULL;
					int iCnt = 0;

						for (pIStr -> Reset();
						     iCnt < MAXFORMATS && 
						     S_OK == pIStr -> Next (1, (LPOLESTR *)&pCfgStr, NULL); 
						     iCnt++)
						{
						string str = AnsiString (pCfgStr);
						int pos = str.find ("|");

							if (NPOS != pos) {
								pFI -> m_strProgID = strProgID;			// ProgID
								pFI -> m_strFilterName = strName;		// Bezeichner
								pFI -> m_strShortName = str.substr (0, pos-1);	// Beschreibung des Dateiformates
								pFI -> m_strFilterExt = str.substr (pos+1);	// default Dateierweiterung
							}
							CoTaskMemFree (pCfgStr);
						}
						pIStr -> Release();
					}

					UnLoadExtension (strProgID, strName);		
				}
			} else 
*/
			if (dwFlags & EF_CanImport) {	
			// Strings in der Registry lesen
			CRegistry *pReg = NULL;
			string strKey;
			
#if defined(WIN32)
#if defined(ENABLE_WIN32S_CODE)
				if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
				{
					strKey = string(g_cbRegExtensions) + g_cbDel;
					strKey += strProgID;	// ProgID
					strKey += string(g_cbDel) + g_cbImportFormat;
					pReg = new CCurrentUser (strKey.c_str());
				} 
#if defined(ENABLE_WIN32S_CODE)
				else
#endif // ENABLE_WIN32S_CODE
#endif // WIN32
#if defined(ENABLE_WIN32S_CODE)
				{
					strKey = strProgID;	// ProgID
					strKey += string(g_cbDel) + g_cbImportFormat;
					pReg = new CClassesRoot (strKey.c_str());
				}
#endif // ENABLE_WIN32S_CODE

				if (pReg && pReg -> isValid()) {
					pFI -> m_strProgID = strProgID;		// ProgID
					pFI -> m_strFilterName = strName;	// Bezeichner

					lLen = _MAX_PATH;
					if (pReg -> GetSubSZ (g_cbDescription, cbKey, lLen)) {
						pFI -> m_strShortName = cbKey; // FilterFormatName

						lLen = _MAX_PATH;
						if (pReg -> GetSubSZ (g_cbFileExt, cbKey, lLen)) {
							pFI -> m_strFilterExt = TEXT("*.");         // Extension
							pFI -> m_strFilterExt += strlwr (cbKey);
						} else
							pFI -> m_strFilterExt = TEXT("*.*");
					
						i++; 	//nächster ImportFilter
					}
				}
				DELETE (pReg);
			}
		}
		m_iNumFilters = i;	// reale Anzahl
	} else
		return false;

return 0 < m_iNumFilters;
}

