// $Header: /TRiAS/TRiAS/TRiAS03/ImportDataDlg.cpp 5     4.06.98 9:51 Hartmut Kaiser $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 05/27/1998 11:33:53 AM
//
// @doc
// @module ImportDataDlg.cpp | PropertyActionDlg für Datenimport

#include "trias03p.hxx"
#include "trias03.h"

#include <StdDlg.hxx>

#include <xtsnguid.h>
#include <eonrguid.h>
#include <eieruhr.hxx>
#include <registry.hxx>

#include "strings.h"
#include "ImportDataDlg.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(EnumString);		// WEnumString
DefineSmartInterface(ImportGeoDataWithResult);		// WImportGeoDataWithResult

/////////////////////////////////////////////////////////////////////////////
// externes
extern char g_pDLLName[_MAX_PATH];

StdMessBoxReply VMessageBox (
	Window *pW, UINT uiCaption, StdMessBox rgType, UINT uiText, ...)
{
ResourceFile RF (g_pDLLName);
ResString resCaption (ResID(uiCaption, &RF), _MAX_PATH);
ResString resFormat (ResID(uiText, &RF), 2*_MAX_PATH); 
va_list params;
char cbOut[4*_MAX_PATH];

	va_start (params, uiText);
	wvsprintf (cbOut, resFormat, params);
	va_end (params);

MessBox mb (resCaption, cbOut, pW);

	mb.SetType (rgType);
	return mb.Show();
}

/////////////////////////////////////////////////////////////////////////////
// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CImportDataDlg::CImportDataDlg (ResID uiDlg, LPCSTR pcCaption)
	      : CPropertyPage (uiDlg, pcCaption), 
		    m_dwFlags(0L), 
			m_cbDataFormat (this, IDC_IMPORTFORMATS),
			m_sleFileName (this, IDC_IMPORTFILES),
			m_pbSelectFile (this, IDC_SELECTIMPORTFILES),
			m_cbOemToAnsi (this, IDC_IMPORTANSIOEM),
			m_cbGeometry (this, IDC_IMPORTGEOMETRY),
			m_cbRelations (this, IDC_IMPORTRELATIONS),
			m_cbObjProps (this, IDC_IMPORTFEATURES),
			m_cbVisInfo (this, IDC_IMPORTVISUALISATION),
			m_pbCoordSystem (this, IDC_COORDSYS),
			m_pbConfig (this, IDB_CONFIG)
{
	m_fWndExists = false;
	m_fHasImportData = false;
	SetImportFlags (0L);
}

#pragma warning (default: 4355)

CImportDataDlg::~CImportDataDlg (void)
{
}

CImportDataDlg *CImportDataDlg::CreateInstance (
	UINT uiDlg, LPCSTR pcCaption, ResourceFile &rRF)
{
	try {
	CImportDataDlg *pDlg = NULL;
	
		pDlg = new CImportDataDlg (ResID (uiDlg, &rRF), pcCaption);
		if (pDlg == NULL || !pDlg -> FInit (rRF)) {
			DELETE_OBJ (pDlg);
			return NULL;
		}
		return pDlg;

	} catch (...) {
		return NULL;
	}
}

namespace {
	BOOL CALLBACK EnumExtensionProc (char *pDLLName, BOOL, void *pData)
	{
	EXTENSIONINFO EI;
	char cbBuffer[_MAX_PATH];

		INITSTRUCT(EI, EXTENSIONINFO);
		EI.pcDLLName = pDLLName;
		EI.pName = cbBuffer;
		EI.iLen = sizeof(cbBuffer);
		if (DEX_GetExtensionInfo (EI)) {
		CImportDataDlg *pDlg = (CImportDataDlg *)pData;

			if (EI.rgFlags & EF_CanImport)
				pDlg -> AddImportExtension (cbBuffer, pDLLName);
		}	
		return TRUE;	// auf jeden Fall weitermachen
	} 
} // namespace

bool CImportDataDlg::FInit (ResourceFile &rRF)
{
// alle verfügbaren ImportErweiterungen heraussuchen
ENUMNOKEY ENK;

	m_Exts.clear();		// alles bisherige löschen
	ENK.eFcn = (ENUMNOKEYPROC)EnumExtensionProc;
	ENK.ePtr = this;
	if (!DEX_EnumExtensions (ENK))
		return false;

	if (0 == m_Exts.size()) {	// kein Importfilter installiert
		VMessageBox (this, IDS_IMPORTFMTDLGCAP, 
			ExclamationIcon|OkayButton, IDS_NOIMPORTFILTERS);
		return false;
	}

	m_it = m_Exts.end();
	for (CExtensions::iterator it = m_Exts.begin(); it != m_Exts.end(); ++it) {
		if (m_strProgID == (*it).first) {
			UpdateControls(it, !m_fHasImportData);						// Erweiterung laden
			break;
		}
	}
	return true;
}
	
///////////////////////////////////////////////////////////////////////////////
// EventHandler 
inline void EnableControl (Control &rCtrl, bool fEnable)
{
	if (fEnable) rCtrl.Enable();
	else		 rCtrl.Disable();
}

void CImportDataDlg::WindowInit (Event)
{
CEierUhr Wait (this);		// danmit es nicht langweilig wird

	m_cbDataFormat.FInit();		// Controls initialisieren
	m_sleFileName.FInit();
	m_pbSelectFile.FInit();

	m_cbOemToAnsi.FInit();
	m_cbGeometry.FInit();
	m_cbRelations.FInit();
	m_cbObjProps.FInit();
	m_cbVisInfo.FInit();
	m_cbOemToAnsi.FInit();

	m_pbCoordSystem.FInit();
	m_pbConfig.FInit();

	m_pbCoordSystem.Disable();		// vorlaufig

// ImportErweiterungen eintragen
bool fLoaded = false;
int i = 0;

	for (CExtensions::iterator it = m_Exts.begin(); it != m_Exts.end(); ++it, ++i) {
		m_cbDataFormat.AddString ((*it).second.c_str());
		if (!fLoaded && m_strProgID == (*it).first) {
			m_cbDataFormat.ChangeCurrentIndex (i);	// Format voreinstellen
			fLoaded = true;
		}
	}

	m_fWndExists = true;
	InitControls();
	AdjustOK();
}

/////////////////////////////////////////////////////////////////////////////
// Datenformat ausgewählt
void CImportDataDlg::ListBoxSel (ControlEvt e)
{
	TX_ASSERT(IDC_IMPORTFORMATS == (UINT)e.GetControlID());

int iIndex = m_cbDataFormat.GetCurrentIndex();

	if (-1 == iIndex)
		return;

// neue Erweiterung laden
int i = 0;

	for (CExtensions::iterator it = m_Exts.begin(); it != m_Exts.end(); ++it, ++i) {
		if (iIndex == i) {
			UpdateControls(it);						// Erweiterung laden
			break;
		}
	}
	m_Names.clear();		// evtl. bisherige Dateien entfernen
	m_sleFileName.SetText(g_cbNil);

	AdjustOK();
}

void CImportDataDlg::ButtonClick (ControlEvt e)
{
	switch ((UINT)e.GetControlID()) {
	case IDC_COORDSYS:		// Koordinatensystem auswählen
		break;

	case IDB_CONFIG:		// ImportFilterKonfiguration
		TX_ASSERT(FCanConfig());
		if (m_ImportExt.IsValid())
			m_ImportExt -> Configure (Handle(API_WINDOW_HWND));
		break;

	case IDC_SELECTIMPORTFILES:
		SelectImportFiles();
		AdjustOK();
		break;

	default:
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
// WizardMessages
void CImportDataDlg::OnSelChanged (NotifyEvt)
{
	AdjustOK();
}

int CImportDataDlg::OnSetActive (NotifyEvt)
{
	AdjustOK();
	return 0;
}

int CImportDataDlg::OnWizNext (NotifyEvt)
{
	if (PrepareResult()) 		// Ergebnisse zwischenspeichern
		return 0;
	return -1;
}

int CImportDataDlg::OnWizFinish (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern
	return 0;
}

void CImportDataDlg::OnCancel (NotifyEvt)
{
	// evtl. Aufräumarbeiten durchführen
}

///////////////////////////////////////////////////////////////////////////////
// HilfsRoutinen --------------------------------------------------------------
void CImportDataDlg::AdjustOK (bool fDisableNext)
{
CPropertySheet *pSheet = GetPropertySheet();

	if (NULL == pSheet) return;

DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns |= PSWIZB_BACK;

// Muß Datenformat und Dateinamen haben
bool fHasDataFormat = (-1 != m_cbDataFormat.GetCurrentIndex()) ? true : false;
bool fHasFileName = (m_sleFileName.GetTextLen() > 0) ? true : false;

	if (fHasDataFormat && fHasFileName) {
		if (m_dwFlags & ADDPAGES_LASTPAGE)
			dwBttns |= PSWIZB_FINISH;
		else
			dwBttns |= PSWIZB_NEXT;
	}
	pSheet -> SetWizardButtons (dwBttns);
}

// Ergebnisdaten aus Controls lesen und zwischenspeichern ---------------------
bool CImportDataDlg::PrepareResult (void)
{
// neue Daten einlesen
	m_dwFlags = GetImportFlags();
	GetFileNames (m_Names);
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// DateiNamen einlesen
bool CImportDataDlg::GetFileNames(list<os_string> &rNames)
{
int iCurrLen = m_sleFileName.GetTextLen();

	if (iCurrLen <= 0) return false;

// einlesen der Dateinamen
LPSTR pTemp = NULL;

	TX_TRY(pTemp = new char [iCurrLen+2]);
	if (NULL == pTemp) return false;

	ZeroMemory (pTemp, iCurrLen+2);
	m_sleFileName.GetText(pTemp, iCurrLen+1);

// Analyse des Strings, evtl. zerlegen und generieren des ersten Namens
int i = 0;
LPSTR pT = pTemp;
int iCnt = 0;

	do {
	int iLen = strlen (pT) +1;

		pT += iLen;
		i += iLen;
		++iCnt;
	} while (i <= iCurrLen && '\0' != *pT);

	rNames.clear();		// alles bisherige vergessen
	if (iCnt > 1) {
	// Parsen der Eingabe und zerlegen in eine list<os_string>
		pT = pTemp;
	
		for (int i = 0; i < iCnt; i++) {
		int iLen = strlen (pT) +1;

			TX_TRY(rNames.push_back (pT));
			pT += iLen;
		} 

	} else {
		TX_TRY(rNames.push_back (pTemp));
	}
	
	DELETE_OBJ(pTemp);
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// ImportOptionen abholen 
DWORD CImportDataDlg::GetImportFlags (void)
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

HRESULT CImportDataDlg::SetImportInfo (IMPORTDATA *pInfo)
{
	COM_TRY {
		m_strProgID = pInfo -> m_strProgID;

	// neue Erweiterung laden
	//fje
		for (CExtensions::iterator it = m_Exts.begin(); it != m_Exts.end(); ++it) {
			if ( m_strProgID == (*it).first) {
				UpdateControls(it);						// Erweiterung laden
				break;
			}
		}

		m_Names = pInfo -> m_listNames;
		m_sleFileName.SetText(g_cbNil);
		m_fShowErrors = pInfo -> m_fShowErrors ? true : false;

		SetImportFlags (pInfo -> m_dwFlags);

		m_fHasImportData = true;
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ImportOptionen initialisieren
void CImportDataDlg::SetImportFlags (DWORD rgFlags, bool fInitActFlags)
{
	if (fInitActFlags) {
		SetGeometry ((rgFlags & IMPORTCAPS_CANIMPORTGEOMETRY) ? true : false);
		SetFeatures ((rgFlags & IMPORTCAPS_CANIMPORTFEATURES) ? true : false);
		SetRelations ((rgFlags & IMPORTCAPS_CANIMPORTRELATIONS) ? true : false);
		SetVisualisation ((rgFlags & IMPORTCAPS_CANIMPORTVISUALISATION) ? true : false);
		SetAnsiOem ((rgFlags & IMPORTCAPS_CANIMPORTANSIOEM) ? true : false);
	}

	SetCanGeometry ((rgFlags & IMPORTCAPS_OPTIMPORTGEOMETRY) ? true : false);
	SetCanFeatures ((rgFlags & IMPORTCAPS_OPTIMPORTFEATURES) ? true : false);
	SetCanRelations ((rgFlags & IMPORTCAPS_OPTIMPORTRELATIONS) ? true : false);
	SetCanVisualisation ((rgFlags & IMPORTCAPS_OPTIMPORTVISUALISATION) ? true : false);
	SetCanAnsiOem ((rgFlags & IMPORTCAPS_OPTIMPORTANSIOEM) ? true : false);

	SetCanConfig ((rgFlags & IMPORTCAPS_SHOULDCONFIG) ? true : false);
	SetMultiSel ((rgFlags & IMPORTCAPS_MULTIPLEFILES) ? true : false);

	InitControls();
}

bool CImportDataDlg::AddImportExtension (LPCSTR pcName, LPCSTR pcDLLName)
{
	m_Exts.push_back (CExtensions::value_type(os_string(pcDLLName), os_string(pcName)));
	return true;
}

// Binden der ImportErweiterung, abfragen der Caps etc. -----------------------
bool CImportDataDlg::UpdateControls (CExtensions::iterator it, bool fInitFlags)
{
	if (it == m_it)	
		return true;	// alles ok, bereits geladen

WImportGeoData Import;

	if (!LoadExtension ((*it).first.c_str(), (*it).second.c_str(), Import.ppi()))
		return false;

	if (m_it != m_Exts.end()) 	// vorhergehende Erweiterung freigeben
		UnLoadExtension((*m_it).first.c_str(), (*m_it).second.c_str());	

	TX_ASSERT(Import.IsValid());
	m_ImportExt = Import;
	SetImportFlags (m_ImportExt -> Capabilities(), fInitFlags);

	m_it = it;
	m_strProgID = (*it).first;
	return true;
}

bool CImportDataDlg::LoadExtension (LPCSTR pcProgID, LPCSTR pcName, IImportGeoData **ppIImport)
{
CEierUhr Wait (this);

// Erweiterung laden, die zur aktuellen Auswahl paßt
LOADEXTENSIONEX LE;

	LE.m_pDesc = (char *)pcName;
	LE.m_pName = (char *)pcProgID;
	LE.m_iMode = LEInitOnly;		// nur initialisieren
	LE.m_fGlobal = true;
	if (NULL != DEX_ExternalLoadExtensionEx(LE)) {
	EXTENSIONPTR EP;
	WUnknown Unk;

		INITSTRUCT(EP, EXTENSIONPTR);
		EP.pcDLLName = pcProgID;
		EP.ppIUnk = Unk.ppu();

		if (!DEX_GetExtensionPtr (EP)) {
			UnLoadExtension (pcProgID, pcName);
			return false;
		}
		return SUCCEEDED(Unk -> QueryInterface (IID_IImportGeoData, (LPVOID *)ppIImport));
	}
	return false;
}

void CImportDataDlg::UnLoadExtension (LPCSTR pcProgID, LPCSTR pcName)
{
	m_ImportExt.Assign(NULL);

LOADEXTENSIONEX LE;

	LE.m_pDesc = (char *)pcName;
	LE.m_pName = (char *)pcProgID;
	LE.m_iMode = LENoLoad;		// wirklich rauswerfen
	LE.m_fGlobal = true;
	DEX_ExternalUnLoadExtensionEx(LE);
	m_it = m_Exts.end();
}

void CImportDataDlg::InitControls()
{
	if (m_fWndExists) {
		m_cbGeometry.SetChecked(FImportGeometry());
		m_cbRelations.SetChecked(FImportRelations());
		m_cbObjProps.SetChecked(FImportFeatures());
		m_cbVisInfo.SetChecked(FImportVisualisation());
		m_cbOemToAnsi.SetChecked(FImportAnsiOem());

		EnableControl (m_cbGeometry, FCanGeometry());
		EnableControl (m_cbObjProps, FCanFeatures());
		EnableControl (m_cbRelations, FCanRelations());
		EnableControl (m_cbVisInfo, FCanVisualisation());
		EnableControl (m_cbOemToAnsi, FCanAnsiOem());

		EnableControl (m_pbConfig, FCanConfig());
	}
}

/////////////////////////////////////////////////////////////////////////////
// DateiDialog anzeigen und Dateinamen einlesen

// Diese Funktion wird nur unter 40 installiert und gerufen 
extern "C" 
UINT CALLBACK ImportFmt40HookFcn (HWND hDlg, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	switch (wMsg) {
	case WM_NOTIFY:
		{
		LPOFNOTIFY pofn = (LPOFNOTIFY)lParam;

			switch (pofn->hdr.code) {
			case CDN_INITDONE:
				((CImportDataDlg *)(pofn -> lpOFN -> lCustData)) -> OnWmInitDialog (hDlg, ::GetParent (hDlg));
				return true;
				
			default:
				break;
			}
		}
		break;

	default:		// no actions
		break;
	}
	return FALSE;	// erstmal alles weiterleiten
}

extern "C"
UINT CALLBACK ImportFmtHookFcn (HWND hDlg, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	switch (wMsg) {
	case WM_INITDIALOG:		// Pointer auf CImportDlg holen
		((CImportDataDlg *)(((OPENFILENAME *)lParam) -> lCustData)) -> OnWmInitDialog (hDlg, hDlg);
		return true;
	
	default:
		break;
	}
	return false;
}

// Initialisieren der zusätzlichen Controls -----------------------------------
LRESULT CImportDataDlg::OnWmInitDialog (HWND hDlg, HWND hDlgP)
{
// zentrieren des Fensters
	if (IsWin40()) 
		::CentreWindow (::GetParent (hDlgP), hDlgP);	
	else
		::CentreWindow (hDlgP, hDlg);		// Win32s etc.
	return true;
}

bool CImportDataDlg::SelectImportFiles()
{
os_string strFilter = GetActualFilterString();
COpenDialog OpenDlg (this, (char *)strFilter.c_str());

	if (IsWin40()) {
		OpenDlg.AddFlags (OFN_EXPLORER|OFN_LONGNAMES|OFN_ALLOWMULTISELECT);
		OpenDlg.SetHookFcn ((HOOKFCN)ImportFmt40HookFcn);
	} else {
		if (IsWinNT()) 
			OpenDlg.AddFlags (OFN_LONGNAMES);
		OpenDlg.SetHookFcn ((HOOKFCN)ImportFmtHookFcn);
	}

ResourceFile RF(g_pDLLName);
ResString resCaption(ResID(IDS_IMPORTFMTDLGCAP, &RF), _MAX_PATH);

	OpenDlg.SetCustomData ((DWORD)(void *)this);
	OpenDlg.SetCaption (resCaption);
	OpenDlg.SetFilterIndex (1);
	OpenDlg.AddFlags (OFN_HIDEREADONLY);

	OpenDlg.SetFileName (m_strInitFile.c_str());
	OpenDlg.SetInitialDir (m_strInitDir.c_str());

	OpenDlg.Show();
	if (!OpenDlg.Result())
		return false;

char cbBuffer[4096];

	OpenDlg.GetFileName(cbBuffer, sizeof(cbBuffer));
	m_sleFileName.SetText (cbBuffer);

// Dateinamen wieder einlesen
	GetFileNames (m_Names);
	if (!FMultiSel() && m_Names.size() > 1) {
	// Warnung, wenn nicht MultiSel aber mehrere Dateien ausgewählt
		VMessageBox (this, IDS_IMPORTFMTDLGCAP, 
					ExclamationIcon|OkayButton, 
					IDS_IMPORTNOMULTISEL, (*m_Names.begin()).c_str());
	}
	return true;
}

os_string CImportDataDlg::GetActualFilterString()
{
os_string strShortName;
os_string strFilterExt;
os_string strKey = os_string(g_cbRegExtensions) + g_cbDel;
	
	strKey += m_strProgID;	// ProgID
	strKey += os_string(g_cbDel) + g_cbImportFormat;

CCurrentUser Reg (strKey.c_str());
char cbKey[_MAX_PATH];

	if (!Reg.isValid()) 
		return g_cbNil;

ULONG lLen = _MAX_PATH;

	if (Reg.GetSubSZ (g_cbDescription, cbKey, lLen)) {
		strShortName = cbKey;			// FilterFormatName

		lLen = _MAX_PATH;
		if (Reg.GetSubSZ (g_cbFileExt, cbKey, lLen)) {
			strFilterExt = TEXT("*.");	// Extension
			strFilterExt += strlwr (cbKey);
		} else
			strFilterExt = TEXT("*.*");
	}
	wsprintf (cbKey, TEXT("%s (%s)|%s"), strShortName.c_str(), strFilterExt.c_str(), strFilterExt.c_str());
	return os_string(cbKey);
}

/////////////////////////////////////////////////////////////////////////////
// Import und Resultate abholen
class CWrapErrMsg 
{
private:
	BOOL m_fFlag;

public:
	CWrapErrMsg(BOOL fFlag) { m_fFlag = ::ShowErrorMessages(fFlag); }
	~CWrapErrMsg() { ::ShowErrorMessages(m_fFlag); }
};

HRESULT CImportDataDlg::GetNextEnumLONG (IEnum<LONG> **ppIEnum)
{
	COM_TRY {
		TX_ASSERT(m_ImportExt.IsValid());

	WEnumString Enum;

		THROW_FAILED_HRESULT(GetNamesAsEnum (Enum.ppi()));

	WImportGeoDataWithResult Import;
	CWrapErrMsg EM (m_fShowErrors ? TRUE : FALSE);		// alle (Datenbank-)Fehler unterdrücken

		if (/*m_dwFlags & ADDPAGES_LASTPROPERTYACTION ||*/
			FAILED(m_ImportExt -> QueryInterface (IID_IImportGeoDataWithResult, Import.ppv())))
		{
		// normalen Import durchführen
			THROW_FAILED_HRESULT(m_ImportExt -> ImportData (Enum, GetImportFlags()));
		} 
		else {
			THROW_FAILED_HRESULT(Import -> ImportDataWithResult (Enum, GetImportFlags(), NULL, (IEnumLONG **)ppIEnum));
		}

	} COM_CATCH;
	return S_OK;
}

HRESULT CImportDataDlg::GetNamesAsEnum (IEnumString **ppIEnum)
{
	if (NULL == ppIEnum) return E_POINTER;

CComObject<CEnumString> *pIEnum = NULL;

	ATLTRY(pIEnum = new CComObject<CEnumString>());
	if (NULL == pIEnum) return E_OUTOFMEMORY;

// Zeiger umkopieren, damit ein zusammenhängender Vektor entsteht,
// dazu auf dem Stack den Speicher anfordern (gibt sich selbst frei!)
LPOLESTR *ppOleStr = (LPOLESTR *)alloca(sizeof(LPOLESTR) * m_Names.size());
int i = 0;

	USES_CONVERSION;
	for (list<os_string>::iterator it = m_Names.begin(); 
		 it != m_Names.end(); ++it)
	{
		ppOleStr[i++] = A2OLE((*it).c_str());	// kein Kopieren hier, sondern in Init
	}

// die Funktion Init des EnumTemplates erwartet die Adressen des ersten und 
// letzten+1 Elementes eines Vektors
HRESULT hr = pIEnum -> Init (&ppOleStr[0], &ppOleStr[m_Names.size()], m_ImportExt, AtlFlagCopy);

	if (SUCCEEDED(hr))
		hr = pIEnum -> QueryInterface(IID_IEnumString, (LPVOID *)ppIEnum);

	if (FAILED(hr))		// bei Fehler alles freigeben
		delete pIEnum;

	return hr;
}
