// ExportDialog in neuer Fassung ueber COMMDLG.DLL ----------------------------
// File: EXPDLG.CXX

#include "triaspre.hxx"

#if defined(WIN32)
// STL-related stuff ----------------------------------------------------------
#define NOMINMAX
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)		// debug info truncated
#include <ospace/std/list>
#include <ospace/std/string>

#include <shlobj.h>

#include <xtsnguid.h>
#include <funcs03.h>
#include <dirisole.h>
#include <regprop.hxx>

#include "strings.h"
#include "cordprop.hxx"

#else // WIN32
#include <toolhelp.h>
#endif

#include <windowsx.h>

#include <impexp.hxx>
#include "extmain3.hxx"
#include "expdlg.hxx"           
#include "triasres.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern HINSTANCE hInstance;
#if !defined(WIN32)
bool IsWin40 (void);
#endif

// Konstruktor/Destruktor -----------------------------------------------------
ExportDlg :: ExportDlg (pWindow pW, CoordTrans *pCTF, bool fProject)
	   : CSaveAsDialog (pW, RetrieveAvailExportFormats()),
	     m_pCTF(pCTF), m_pW(pW)
{
	m_pOutFile = NULL;
	m_pInitPath = NULL;
	m_fPos = false;
	m_fAppend = false;
#if defined(WIN32)
	m_fProject = fProject;
	m_fAllObjects = false;

char cbView[64];

	if (NULL !=  DEX_GetActiveSight (cbView)) 
		m_fEnableActView = true;
	else {
		m_fEnableActView = false;
		m_fAllObjects = true;
	}
#endif

// FileTypes wird in RetrieveAvailExportFormats initialisiert
	m_fValid = (m_pFileTypes != NULL) ? true : false;
	if (!m_fValid) return;

#if defined(WIN32)
	if (IsWin40()) {
		AddFlags (OFN_EXPLORER|OFN_LONGNAMES);
		SetHookFcn ((HOOKFCN)ExportFmt40HookFcn);
		if (m_fProject) 
			SetTemplate (hInstance, MAKEINTRESOURCE(EXPORTFMT40SUBDLG));
		else
			SetTemplate (hInstance, MAKEINTRESOURCE(EXPORTFMT40SUBDLGOBJ));
	} else
#endif
	{
	// SonderWünsche einstellen
		if (IsWinNT()) AddFlags (OFN_LONGNAMES);
		SetHookFcn ((HOOKFCN)ExportFmtHookFcn);
		SetTemplate (hInstance, MAKEINTRESOURCE(EXPORTFMTDLG));
	}
	SetCustomData ((DWORD)(void *)this);
	SetCaption (ResString (IDS_EXPORTFMTDLGCAP, 80));

// AnfangsVerzeichnis auf das aktuelle Projektverzeichnis setzen
	m_pInitPath = new char [_MAX_PATH];
	if (m_pInitPath && DEX_GetActiveProject (m_pInitPath) != NULL) {
	char *pPath = new char [_MAX_PATH];
	char *pDrive = new char [_MAX_DRIVE];

		_splitpath (m_pInitPath, pDrive, pPath, NULL, NULL);
		_makepath (m_pInitPath, pDrive, pPath, "", "");
		SetInitialDir (m_pInitPath);
		DELETE_VEC (pPath);
		DELETE_VEC (pDrive);
	}
}


ExportDlg :: ~ExportDlg (void)
{
	DELETE_VEC (m_pOutFile);  
	DELETE_VEC (m_pFileTypes);
	DELETE_VEC (m_pInitPath);

	if (m_iNumFilters > 0) {
		for (int i = 0; i < m_iNumFilters; i++) {
			DELETE_VEC (m_pFilterInfo[i].m_pDLLName);
		}
		DELETE_VEC (m_pFilterInfo[0].m_pFilterName);
	}
	DELETE_VEC (m_pFilterInfo);
}


// Memberfunktionen -----------------------------------------------------------
int ExportDlg :: ReadFileName (void)
{
int iCurrLen = GetFileNameLen();

	if (iCurrLen <= 0) return 0;

	if (m_pOutFile == NULL) {
		m_pOutFile = new char [iCurrLen+1];
		if (m_pOutFile == NULL) return 0;
	}
	GetFileName (m_pOutFile, iCurrLen);

return iCurrLen;
}


int ExportDlg :: FindFilterExt (void)
{
// Alle Dateien ausgewählt: über Dateierweiterung suchen
	if (ReadFileName() == 0) return m_iNumFilters;

char *pExt = new char [_MAX_EXT];

	_splitpath (m_pOutFile, NULL, NULL, NULL, pExt);
	strlwr (pExt);

// Erweiterung in der Liste der Filter suchen
int iIndex = 0;

	for (; iIndex < m_iNumFilters; iIndex++) {
		if (!strcmp (strlwr (m_pFilterInfo[iIndex].m_pFilterExt)+1, pExt))
			break;
	}
	DELETE (pExt);

return iIndex;
}

char *ExportDlg :: GetFileSpec (char *pc, short iLen)
{
int iCurrLen = ReadFileName();

	if (iCurrLen == 0 || pc == NULL) return m_pOutFile;

int iMinLen = min ((int)iLen, iCurrLen);

	strncpy (pc, m_pOutFile, iMinLen);
	pc[iMinLen-1] = '\0';
	
return pc;
}
	
char *ExportDlg :: GetDLLName (char *pc, short iLen)
{
int iIndex = GetFilterIndex() -1;	// fängt bei '1' an

	if (iIndex < 0 || iIndex > m_iNumFilters)
		return NULL;	// Fehler
	
	if (iIndex == m_iNumFilters) {
		iIndex = FindFilterExt();
		if (iIndex >= m_iNumFilters) return NULL; // nichts gefunden
	}

	if (pc == NULL) return m_pFilterInfo[iIndex].m_pDLLName;
	
	strncpy (pc, m_pFilterInfo[iIndex].m_pDLLName, iLen);
	pc[iLen-1] = '\0';
	
return pc;
}


char *ExportDlg :: GetShortName (char *pc, short iLen)
{
int iIndex = GetFilterIndex() -1;	// fängt bei '1' an

	if (iIndex < 0 || iIndex > m_iNumFilters)
		return NULL;	// Fehler
	
	if (iIndex == m_iNumFilters) {
		iIndex = FindFilterExt();
		if (iIndex >= m_iNumFilters) return NULL; // nichts gefunden
	}

	if (pc == NULL) return m_pFilterInfo[iIndex].m_pShortName;
	
	strncpy (pc, m_pFilterInfo[iIndex].m_pShortName, iLen);
	pc[iLen-1] = '\0';
	
return pc;
}

// dieser neue Dialog liefert immer den Namen der aktuellen Sicht -------------
char *ExportDlg :: GetSight (char *cptr, short len)
{
static char cbView[80];

	if (NULL != DEX_GetActiveSight (cbView))
		return cbView;

return "";
}

// Initialisieren der zusätzlichen Controls -----------------------------------
LRESULT ExportDlg :: OnWmInitDialog (HWND hDlg, HWND hDlgP)
{
	SendDlgItemMessage (hDlg, IDR_EXPORTOVERWRITE, BM_SETCHECK, true, 0);
	SendDlgItemMessage (hDlg, IDR_EXPORTCONCAT, BM_SETCHECK, false, 0);
	SendDlgItemMessage (hDlg, IDR_EXPORTPOSITION, BM_SETCHECK, false, 0);

#if defined(WIN32)
	EnableWindow (GetDlgItem (hDlg, IDC_OPTIONS), false);	// erstmal falsch

// nicht ganz genau in die Mitte, damit KoordinatenFenster besser zu erkennen ist
RECT rc;

	if (IsWin40()) {
		CentreWindow (::GetParent (hDlgP), hDlgP);

		GetWindowRect (hDlgP, &rc);
		SetWindowPos (hDlgP, NULL, max(rc.left-40, 0), max(rc.top-40, 0), 0, 0, 
					  SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOZORDER);

		if (m_fProject) {
			if (m_fEnableActView) {
				SendDlgItemMessage (hDlg, IDR_EXPORTACTVIEW, BM_SETCHECK, true, 0);
				SendDlgItemMessage (hDlg, IDR_EXPORTALLOBJECTS, BM_SETCHECK, false, 0);
			} else {
				EnableWindow (GetDlgItem (hDlg, IDR_EXPORTACTVIEW), false);
				SendDlgItemMessage (hDlg, IDR_EXPORTACTVIEW, BM_SETCHECK, false, 0);
				SendDlgItemMessage (hDlg, IDR_EXPORTALLOBJECTS, BM_SETCHECK, true, 0);
			}
		}
	} else {
	// Win32s
		CentreWindow (hDlgP, hDlg);

		GetWindowRect (hDlg, &rc);
		SetWindowPos (hDlg, NULL, max(rc.left-40, 0), max(rc.top-40, 0), 0, 0, 
					  SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOZORDER);
	}
#else
// KoordinatenSystem ist konfigurierbar
	EnableWindow (GetDlgItem (hDlg, IDC_COORDSYS), m_pCTF -> CanConfig());
#endif

return true;
}


// WM_COMMAND geschickt, drückt Nutzer Knöpfchen? -----------------------------
LRESULT ExportDlg :: OnWmCommand (HWND hDlg, WPARAM wParam, LPARAM lParam)
{
UINT uiID = GET_WM_COMMAND_ID (wParam, lParam);
HWND hCntrl = GET_WM_COMMAND_HWND (wParam, lParam);
UINT uiCmd = GET_WM_COMMAND_CMD (wParam, lParam);

	if (uiCmd == BN_CLICKED) switch (uiID) {
	case IDR_EXPORTOVERWRITE:
		if (SendDlgItemMessage (hDlg, uiID, BM_GETCHECK, 0, 0))
			m_fAppend = false;
		else
			m_fAppend = true;
		return true;

	case IDR_EXPORTCONCAT:
		if (SendDlgItemMessage (hDlg, uiID, BM_GETCHECK, 0, 0))
			m_fAppend = true;
		else
			m_fAppend = false;
		return true;

	case IDC_COORDSYS:	// Auswahl der Koordinatensystemparameter 
		return SelectCoordSysParams (GetParent(), IDS_EXPORTFMTDLGCAP, m_pCTF);

	case IDR_EXPORTPOSITION:
		m_fPos = SendDlgItemMessage (hDlg, uiID, BM_GETCHECK, 0, 0) ? true : false;
		return true;

#if defined(WIN32)
	case IDR_EXPORTALLOBJECTS:
		if (!IsWin40() || !m_fProject) break;

		if (SendDlgItemMessage (hDlg, uiID, BM_GETCHECK, 0, 0))
			m_fAllObjects = true;
		else
			m_fAllObjects = false;
		return true;

	case IDR_EXPORTACTVIEW:
		if (!IsWin40() || !m_fProject) break;

		if (SendDlgItemMessage (hDlg, uiID, BM_GETCHECK, 0, 0))
			m_fAllObjects = false;
		else
			m_fAllObjects = true;
		return true;

	case IDC_OPTIONS:		// Auswahl der zu exportierenden Objekteigenschaften
		if (IsWin40()) 
			return GetObjPropsForExport();
		break;
#endif //WIN32

	default:
		break;
	}

return false;
}


// HookFunktion ---------------------------------------------------------------
extern bool g_fCtl3dInit;
static ExportDlg *s_pDlg = NULL;

extern "C"
UINT EXPORTTRIAS CALLBACK ExportFmtHookFcn (HWND hDlg, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	switch (wMsg) {
	case WM_INITDIALOG:		// Pointer auf ExportDlg holen
		if (g_fCtl3dInit) 
			Ctl3dSubclassDlg (hDlg, CTL3D_ALL);
		s_pDlg = (ExportDlg *) (((OPENFILENAME *)lParam) -> lCustData);
		return (UINT)s_pDlg -> OnWmInitDialog (hDlg, ::GetParent (hDlg));
		
	case WM_DESTROY:	// letzte Message an uns
		s_pDlg = NULL;		// AusgangsZustand wieder herstellen
		break;

	case WM_COMMAND:
		return s_pDlg ? (UINT)s_pDlg -> OnWmCommand (hDlg, wParam, lParam) : false;

	default:
		break;
	}

return false;
}


#if defined(WIN32)

// Diese Funktion wird nur unter 40 installiert und gerufen -------------------
extern "C" 
UINT EXPORTTRIAS APIENTRY ExportFmt40HookFcn (HWND hDlg, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	switch (wMsg) {
	case WM_NOTIFY:
		{
		LPOFNOTIFY pofn = (LPOFNOTIFY)lParam;

			switch (pofn->hdr.code) {
			case CDN_INITDONE:
				s_pDlg = (ExportDlg *)(pofn -> lpOFN -> lCustData);
				return s_pDlg -> OnWmInitDialog (hDlg, ::GetParent(hDlg));

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

#endif // WIN32


// Bilden der Dateibeschreibungen für Dateitypauswahl im Dialog -----------------
inline char *EOS (char *pStr) { return &pStr[strlen(pStr)]; }

char *ExportDlg :: RetrieveAvailExportFormats (void)
{
// registrierte Filter einlesen
	m_pFileTypes = NULL;
	if (!ReadFormats()) return NULL;

	m_pFileTypes = new char [m_iNumFilters * _MAX_PATH];
	if (m_pFileTypes == NULL) return NULL;

// Dateibeschreibungsstring zusammenbauen
	*m_pFileTypes = '\0';
	for (int i = 0; i < m_iNumFilters; i++) {
		strlwr (m_pFilterInfo[i].m_pFilterExt);
		wsprintf (EOS(m_pFileTypes), "%s (%s)|%s|", 
			  m_pFilterInfo[i].m_pFilterName, 
			  m_pFilterInfo[i].m_pFilterExt,
			  m_pFilterInfo[i].m_pFilterExt);
	}
	*(EOS(m_pFileTypes)-1) = '\0';	// letztes '|' weglöschen

return m_pFileTypes;
}
 
// FilterNamen aus TRIAS20.INI einlesen -----------------------------------------
bool ExportDlg :: ReadFormats (void) 
{
ResString rsParams (IDS_IRISPARS, 15);
ResString rsFilters (IDS_FILTERS, 15);
ResString rsProfile (IDS_PROFILE, 15);

	m_iNumFilters = GetPrivateProfileInt (rsParams, 
				ResString(IDS_NUMFILTERS, 15), 0, rsProfile);

char *pFilterNamesStr = NULL;

	if (m_iNumFilters > 0) {
	// wenn Systemfarben gegeben sind
		pFilterNamesStr = new char [m_iNumFilters*_MAX_PATH+1];
		m_pFilterInfo = new FILTERINFO [m_iNumFilters];

		if (pFilterNamesStr == NULL || m_pFilterInfo == NULL) {
			db_error (EC_NOMEMORY, RC_ctExportDlg);
			return false;
		}

		GetPrivateProfileString (rsFilters, NULL, "", pFilterNamesStr, 
					 m_iNumFilters*_MAX_PATH+1, rsProfile);
		m_pFilterInfo[0].m_pFilterName = pFilterNamesStr;

	int len = 0;
	int i;

		for (i = 1; i < m_iNumFilters; i++) 
			m_pFilterInfo[i].m_pFilterName = 
			    &pFilterNamesStr[len += strlen(m_pFilterInfo[i-1].m_pFilterName)+1];
		
		for (i = 0; i < m_iNumFilters; i++) {
		// FilterBeschreibung aus ProfileDatei einlesen
		FILTERINFO *pFI = &m_pFilterInfo[i];

			pFI -> m_pDLLName = new char [_MAX_PATH];
			if (pFI  -> m_pDLLName == NULL)
				return (ErrCode)db_error (EC_NOMEMORY, RC_ctExportDlg);
			GetPrivateProfileString (rsFilters, pFI -> m_pFilterName, 
						 "", pFI -> m_pDLLName, 
						 _MAX_PATH, rsProfile);
			pFI -> m_pDLLName = strtok (pFI -> m_pDLLName, ", "); // FilterFormatName
			pFI -> m_pShortName = strtok (NULL, ", ");         // KurzName
			pFI -> m_pFilterExt = strtok (NULL, ", ");         // Extension
		}
	} else
		return false;

return true;
}

// Auswahl der Koordinatensystemparameter -------------------------------------
#if !defined(WIN32)

LRESULT SelectCoordSysParams (pWindow pW, CoordTrans *pCTF)
{
	return pCTF -> CoordTransMode (pW);
}

#else

// Anzeige und Verarbeitung des Dialoges für die ProjektEigenschaften ---------
LRESULT SelectCoordSysParams (pWindow pW, UINT uiID, CoordTrans *)
{
	TX_ASSERT(NULL != pW);

// Dialogfenster generieren
CEierUhr Wait (pW);
CCoordProperties CoordProps (pW); 

	CoordProps.LoadPages();			// zusätzliche Pages aus Registry laden
	
	if (CoordProps.GetPageCount() == 0) {
		VMessageBox (pW, uiID, OkayButton|ExclamationIcon, IDS_COORDCANTCONFIG);
		return false;
	}

// Dialogfenster anzeigen
	Wait.Hide();
	CoordProps.Show (Centre);	// KoordinatenProps editieren

	CoFreeUnusedLibraries();	// DLL's wieder freigeben

return CoordProps.Result();
}

///////////////////////////////////////////////////////////////////////////////
// PropertySheet --------------------------------------------------------------
CCoordProperties::CCoordProperties (pWindow pWnd)
	: CPropertySheetExt (ResString (IDS_DOCPROPS, 64), pWnd)
{
}

HRESULT CCoordProperties::LoadPages (void)
{
// alle sonstigen Pages aus der Registry laden
WStorage IStg;
WDataObject IDO;

	if (DEX_GetProjectStorage (*IStg.ppv())) 
		CreateDataObject (IStg, IDO);

string strKey (g_cbDocSubKey);

	strKey += string(g_cbDel) + g_cbCoordinates;

return LoadExtPagesFromRegistry (HKEY_CLASSES_ROOT, g_cbDocKey, strKey.c_str(), IDO, NULL);
}

HRESULT CCoordProperties::CreateDataObject (WStorage &rIStg, WDataObject &rIDO)
{ 
// DataObject generieren
HRESULT hr = DataObjectCreateInstance (NULL, IID_IDataObject, rIDO.ppv()); 

	if (FAILED(hr)) return hr;

// Storage im DataObject wegspeichern
STGMEDIUM stm;

	stm.tymed = TYMED_ISTORAGE;
	stm.pstg = rIStg.detach();		// übergibt AddRef()
	stm.pUnkForRelease = NULL;

FORMATETC fe;
UINT uiCf = RegisterClipboardFormat (g_cbDocKey);

	SETDefFormatEtc (fe, uiCf, TYMED_ISTORAGE);

return rIDO -> SetData (&fe, &stm, true);
}

#endif // WIN32
