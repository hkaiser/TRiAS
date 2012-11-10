// $Header: /TRiAS/TRiAS/TRiAS03/ImportDataDlg.cpp 5     4.06.98 9:51 Hartmut Kaiser $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 05/27/1998 11:33:53 AM
//
// @doc
// @module ImportDataDlg.cpp | PropertyActionDlg für Datenimport

#include "trias03p.hxx"
#include "trias03.h"

#include <Atl/Ciid.h>
#include <StdDlg.hxx>

#include <shlobj.h>
#include <ixtnext.hxx>

#include <xtsnguid.h>
#include <eonrguid.h>
#include <eieruhr.hxx>
#include <registry.hxx>

#include "strings.h"
#include "SelectCoordSysActionDlg.h"
#include "ImportDataDlg.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(EnumString);			// WEnumString
DefineSmartInterface(ImportGeoDataWithResult);	// WImportGeoDataWithResult
DefineSmartInterface(ImportGeoDataSelectCS);	// WImportGeoDataSelectCS
DefineSmartInterface(TriasPropSheetExt);		// WTriasPropSheetExt
DefineSmartInterface(TRiASProject);			// WTRiASProject
DefineSmartInterface(TRiASConnections);		// WTRiASConnections
DefineSmartInterface(TRiASConnection);		// WTRiASConnection
DefineSmartInterface(TRiASDatabase);		// WTRiASDatabase
DefineSmartInterface(TRiASCS);				// WTRiASCS

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
CImportDataDlg::CImportDataDlg (ResID uiDlg, LPCSTR pcCaption) :
	CPropertyPage (uiDlg, pcCaption), 
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
	m_pbConfig (this, IDB_CONFIG),
	m_cbDataSources (this, IDC_DATASOURCES)
{
	m_fWndExists = false;
	m_fHasImportData = false;
	m_hPr = NULL;
	SetImportFlags (0L);
	m_uiCnt = 0;
	m_fFilesChanged = false;
	m_pSelectCoordSysDlg = NULL;
}

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
// Datenquellen füllen
bool CImportDataDlg::FillDataSources()
{
long lCntOpen = 0;

	USES_CONVERSION;
	COM_TRY {
	// alle Connections durchgehen und feststellen:
	// aktuelle Connection, ob beschreibbare Connection existiert
	WTRiASProject Prj;

		if (!DEX_GetActiveProjectPtr (*Prj.ppi())) 
			_com_issue_error(E_UNEXPECTED);		// snh

	WTRiASConnections Conns;
	long lCnt = 0;

		THROW_FAILED_HRESULT(Prj -> get_Connections (Conns.ppi()));
		THROW_FAILED_HRESULT(Conns -> get_Count(&lCnt));

		for (long i = 1; i <= lCnt; i++) {
		CComVariant vIndex (i);
		WTRiASConnection Conn;

			THROW_FAILED_HRESULT(Conns -> Item (vIndex, Conn.ppi()));

		CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

			THROW_FAILED_HRESULT(Conn -> get_Status (&rgStatus));
			if (CONNECTSTATUS_Opened == rgStatus) {
			VARIANT_BOOL fUpdatable = VARIANT_FALSE;

				THROW_FAILED_HRESULT(Conn -> get_Updatable (&fUpdatable));
				if (fUpdatable) {
				// geöffnet und beschreibbar
				CComBSTR bstrName;

					THROW_FAILED_HRESULT(Conn -> get_Name (CLEARED(&bstrName)));

				int iNew = m_cbDataSources.AddString (OLE2A(bstrName));

				// wenns die aktuelle ist, dann den Index speichern
				WTRiASDatabase DBase;
				LONG lHandle = 0; 

					THROW_FAILED_HRESULT(Conn -> get_Database(DBase.ppi()));
					THROW_FAILED_HRESULT(DBase -> get_Handle ((INT_PTR *)&lHandle));
					if (-1 != iNew) {
						m_cbDataSources.SetItemData (iNew, lHandle);		// ProjectHandle zuordnen
						lCntOpen++;
					}
				}
			}
		}
	} COM_CATCH_RETURN(false);

	if (0 == lCntOpen) {		// keine beschreibbaren Datenquellen vorhanden
		VMessageBox (this, IDS_IMPORTFMTDLGCAP, 
			ExclamationIcon|OkayButton, IDS_NOWRITEABLECONNECTIONS);
		return false;
	}

	if (1 == lCntOpen)			// wenn nur einer da ist, dann diesen voreinstellen
		m_cbDataSources.ChangeCurrentIndex(0);
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

// Datenquellen enumerieren
	FillDataSources();

	AdjustOK();
}

/////////////////////////////////////////////////////////////////////////////
// Datenformat ausgewählt
void CImportDataDlg::ListBoxSel (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDC_IMPORTFORMATS:
		{
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
		}
		break;

	default:
		break;
	}
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

	case IDC_IMPORTANSIOEM:
		if (FCanAnsiOem()) 
			SetAnsiOem (m_cbOemToAnsi.isChecked());
		break;

	case IDC_IMPORTGEOMETRY:
		if (FCanGeometry()) 
			SetGeometry (m_cbGeometry.isChecked());
		break;

	case IDC_IMPORTRELATIONS:
		if (FCanRelations()) 
			SetRelations (m_cbRelations.isChecked());
		break;

	case IDC_IMPORTFEATURES:
		if (FCanFeatures()) 
			SetFeatures (m_cbObjProps.isChecked());
		break;

	case IDC_IMPORTVISUALISATION:
		if (FCanVisualisation()) 
			SetVisualisation (m_cbVisInfo.isChecked());
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
	m_fFilesChanged = false;
	return 0;
}

int CImportDataDlg::OnWizNext (NotifyEvt)
{
	COM_TRY {
		if (PrepareResult()) {		// Ergebnisse zwischenspeichern
		WTRiASImportWizardPropExt2 Ext2;
		UINT uiNextPage = 0;

			m_pSelectCoordSysDlg->SetNextPageId(0);		// assume no additional pages

			if (m_ExtPages.IsValid() && 
				SUCCEEDED(m_ExtPages->QueryInterface(Ext2.ppi()))) 
			{
				THROW_FAILED_HRESULT(Ext2 -> get_StartPageId(&uiNextPage));
				if (m_fCanCoordSystems) {
				// wenn Koordinatensystem unterstützt werden, ist die
				// entsprechende Seite die Nächste
					m_pSelectCoordSysDlg->SetNextPageId(uiNextPage);
					uiNextPage = IDD_SELECTCOORDSYSACTION_OPTIONS;
				}
			}
			else if (m_fCanCoordSystems) {
				uiNextPage = IDD_SELECTCOORDSYSACTION_OPTIONS;
			}
			return uiNextPage;
		}
	} COM_CATCH;
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
bool fHasDataSource = (-1 != m_cbDataSources.GetCurrentIndex()) ? true : false;

	if (fHasDataFormat && fHasFileName && fHasDataSource) {
		if ((m_dwFlags & ADDPAGES_LASTPAGE) && 0 == m_uiCnt && !m_fCanCoordSystems)
			dwBttns |= PSWIZB_FINISH;
		else
			dwBttns |= PSWIZB_NEXT;
	} else if ((m_dwFlags & ADDPAGES_LASTPAGE) && 0 == m_uiCnt && !m_fCanCoordSystems)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	pSheet -> SetWizardButtons (dwBttns);
}

// Ergebnisdaten aus Controls lesen und zwischenspeichern ---------------------
bool CImportDataDlg::PrepareResult (void)
{
// neue Daten einlesen
	m_dwFlags = GetImportFlags();

int iIndex = m_cbDataSources.GetCurrentIndex();

	TX_ASSERT(-1 != iIndex);
	m_hPr = reinterpret_cast<HPROJECT>(m_cbDataSources.GetItemData (iIndex));

// zusätzliche Seite(n) von Dateiauswahl informieren
	COM_TRY {
		if (m_ExtPages.IsValid() && m_fFilesChanged) {
		WEnumString Enum;

			THROW_FAILED_HRESULT(GetNamesAsEnum (Enum.ppi()));
			THROW_FAILED_HRESULT(m_ExtPages -> put_SelectedFiles (Enum));

		WTRiASImportWizardPropExt2 Ext2;

			if (SUCCEEDED(m_ExtPages->QueryInterface(Ext2.ppi()))) {
			// ContextHandle und StartPageId mitteilen
				THROW_FAILED_HRESULT(Ext2 -> put_ContextHandle((INT_PTR)m_hPr));
				THROW_FAILED_HRESULT(Ext2 -> put_FirstPageId(
					m_fCanCoordSystems ? IDD_SELECTCOORDSYSACTION_OPTIONS : IDD_IMPORT_WIZ));
				THROW_FAILED_HRESULT(Ext2 -> put_ImportFlags(m_dwFlags));
			}
		}

	} COM_CATCH_RETURN(false);
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// DateiNamen einlesen
bool CImportDataDlg::GetFileNames (list<os_string> &rNames, LPCSTR pcBuffer, int iCurrLen)
{
	if (iCurrLen <= 0)
		iCurrLen = m_sleFileName.GetTextLen();
	if (iCurrLen <= 0) 
		return false;

// einlesen der Dateinamen
LPSTR pTemp = NULL;

	TX_TRY(pTemp = new char [iCurrLen+2]);
	if (NULL == pTemp) return false;

	ZeroMemory (pTemp, iCurrLen+2);
	if (NULL == pcBuffer)
		m_sleFileName.GetText(pTemp, iCurrLen+1);
	else
		memcpy (pTemp, pcBuffer, iCurrLen+1);

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
	os_string strPath (pTemp);

		pT = pTemp;
	
		for (int i = 0; i < iCnt; i++) {
		int iLen = strlen (pT) +1;

			if (i > 0) {
			// vollständigen Dateinamen zusammenbauen
			os_string str (strPath);

				str += '\\';
				str += pT;
				TX_TRY(rNames.push_back (str.c_str()));
			}
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
			if (m_strProgID == (*it).first) {
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
CRegKey regExt;
os_string strName (pcName);
os_string strFileExt;

	if (ERROR_SUCCESS == regExt.Open (HKEY_CURRENT_USER, "Software", KEY_READ) &&
		ERROR_SUCCESS == regExt.Open (regExt, REG_COMPANY_KEY, KEY_READ) &&
		ERROR_SUCCESS == regExt.Open (regExt, REG_PRODUCT_KEY, KEY_READ) &&
		ERROR_SUCCESS == regExt.Open (regExt, "Extensions", KEY_READ) &&
		ERROR_SUCCESS == regExt.Open (regExt, pcDLLName, KEY_READ) &&
		ERROR_SUCCESS == regExt.Open (regExt, g_cbImportFormat, KEY_READ))
	{
	char cbBuffer[_MAX_PATH];
	DWORD dwCnt = sizeof(cbBuffer);

		if (ERROR_SUCCESS == regExt.QueryValue (cbBuffer, g_cbDescription, &dwCnt) && dwCnt > 0)
			strName = cbBuffer;

		dwCnt = sizeof(cbBuffer);
		if (ERROR_SUCCESS == regExt.QueryValue (cbBuffer, g_cbFileExt, &dwCnt) && dwCnt > 0)
			strFileExt = strupr(cbBuffer);
	}
	if (strFileExt.size() > 0) {
		strName += " (";
		strName += strFileExt;
		strName += ")";
	}

	m_Exts.push_back (CExtensions::value_type(os_string(pcDLLName), strName));
	return true;
}

// Binden der ImportErweiterung, abfragen der Caps etc. -----------------------
bool CImportDataDlg::UpdateControls (CExtensions::iterator it, bool fInitFlags)
{
	if (it == m_it)	
		return true;	// alles ok, bereits geladen

// neu ausgewählte Erweiterung laden
WImportGeoData Import;

	if (!LoadExtension ((*it).first.c_str(), (*it).second.c_str(), Import.ppi()))
		return false;

	if (m_it != m_Exts.end()) 	// vorhergehende Erweiterung freigeben
		UnLoadExtension((*m_it).first.c_str(), (*m_it).second.c_str());	

	TX_ASSERT(Import.IsValid());
	m_ImportExt = Import;
	SetImportFlags (m_ImportExt -> Capabilities(), fInitFlags);

// ggf. KoordinatensystemAuswahl anzeigen
WImportGeoDataSelectCS SelectCS;

	if (SUCCEEDED(m_ImportExt->QueryInterface(SelectCS.ppi())))
		m_fCanCoordSystems = true;
	else
		m_fCanCoordSystems = false;

// evtl. zusätzliche Konfigurationsseiten ranhängen
	ResetExtPages();

// aktuellen Stand speichern
	m_it = it;
	m_strProgID = (*it).first;

CIID Guid (GetActualConfigGuid().c_str(), CIID::INITCIID_InitFromGuid);

	if (!!Guid) 
		LoadExtPages(Import, Guid);
	return true;
}

bool CImportDataDlg::LoadExtension (LPCSTR pcProgID, LPCSTR pcName, IImportGeoData **ppIImport)
{
CEierUhr Wait (this);

// Erweiterung laden, die zur aktuellen Auswahl paßt
LOADEXTENSIONEX LE;

	LE.m_pDesc = NULL;		// (char *)pcName;		wird von TRiAS richtig geschrieben
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

#if defined(ENABLE_WIN32S_CODE)
	if (IsWin40()) 
#endif // defined(ENABLE_WIN32S_CODE)
	{
		OpenDlg.AddFlags (OFN_EXPLORER|OFN_LONGNAMES|OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_ALLOWMULTISELECT);
#if defined(OFN_ENABLESIZING)
		if (IsWin41() || (IsWinNT() && IsWin50())) {		// Win98 oder WinNT50
			OpenDlg.AddFlags (OFN_ENABLESIZING);
#if defined(OFN_DONTADDTORECENT)
			OpenDlg.AddFlags (OFN_DONTADDTORECENT);
#endif // OFN_DONTADDTORECENT
		}
#endif // OFN_ENABLESIZING
		OpenDlg.SetHookFcn ((HOOKFCN)ImportFmt40HookFcn);
	} 
#if defined(ENABLE_WIN32S_CODE)
	else {
		if (IsWinNT()) 
			OpenDlg.AddFlags (OFN_LONGNAMES);
		OpenDlg.SetHookFcn ((HOOKFCN)ImportFmtHookFcn);
	}
#endif // defined(ENABLE_WIN32S_CODE)

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

int iLen = OpenDlg.GetFileNameLen();
char cbBuffer[4096];

	TX_ASSERT(iLen < sizeof(cbBuffer));
	OpenDlg.GetFileName(cbBuffer, iLen);

	m_sleFileName.SetText (cbBuffer);

// Dateinamen wieder einlesen
	GetFileNames (m_Names, cbBuffer, iLen);
	if (!FMultiSel() && m_Names.size() > 1) {
	// Warnung, wenn nicht MultiSel aber mehrere Dateien ausgewählt
		VMessageBox (this, IDS_IMPORTFMTDLGCAP, 
					ExclamationIcon|OkayButton, 
					IDS_IMPORTNOMULTISEL, (*m_Names.begin()).c_str());
	}
	m_fFilesChanged  = true;
	return true;
}

os_string CImportDataDlg::GetActualConfigGuid()
{
os_string strGuid(g_cbNil);
os_string strFilterExt;
os_string strKey = os_string(g_cbExtensions) + g_cbDel;
	
	strKey += m_strProgID;	// ProgID
	strKey += os_string(g_cbDel) + g_cbImportFormat;

CCurrentUser Reg (KEY_READ, strKey.c_str());

	if (!Reg.isValid()) 
		return g_cbNil;

ULONG lLen = _MAX_PATH;
char cbKey[_MAX_PATH] = { '\0' };

	if (Reg.GetSubSZ (g_cbConfigPage, cbKey, lLen)) 
		strGuid = cbKey;			// ConfigGUID

	return strGuid;
}

os_string CImportDataDlg::GetActualFilterString()
{
os_string strShortName;
os_string strFilterExt;
os_string strKey = os_string(g_cbExtensions) + g_cbDel;
	
	strKey += m_strProgID;	// ProgID
	strKey += os_string(g_cbDel) + g_cbImportFormat;

CCurrentUser Reg (KEY_READ, strKey.c_str());
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

///////////////////////////////////////////////////////////////////////////////
// Das aktive projekt für die Dauer des Importes einstellen und TRiAS davon
// informieren, daß ein Import läuft
class CActiveProject 
{
public:
	CActiveProject (HPROJECT hPr)
	{
		m_hPr = DEX_GetDataSourceHandle();
		DEX_ImportMode(TRUE);

#if defined(_DEBUG)
	HPROJECT hPrOld = DEX_MakeDataSourceActive(hPr);

		TX_ASSERT(hPrOld == m_hPr);
#else
		DEX_MakeDataSourceActive(hPr);
#endif // defined(_DEBUG)
	}
	~CActiveProject()
	{
		DEX_ImportMode(FALSE);
		DEX_MakeDataSourceActive (m_hPr);
	}

private:
	HPROJECT m_hPr;
};

HRESULT CImportDataDlg::GetNextEnumLONG (IEnum<LONG> **ppIEnum)
{
	COM_TRY {
		TX_ASSERT(m_ImportExt.IsValid());
		TX_ASSERT(NULL != m_hPr);

	WEnumString Enum;

		THROW_FAILED_HRESULT(GetNamesAsEnum (Enum.ppi()));

	// Import starten
	WImportGeoDataWithResult Import;
	CWrapErrMsg EM (m_fShowErrors ? TRUE : FALSE);		// alle (Datenbank-)Fehler unterdrücken
	CActiveProject Prj(m_hPr);							// ZielDatenquelle voreinstellen

	WImportGeoDataSelectCS SelectCS;

		if (SUCCEEDED(m_ImportExt->QueryInterface(SelectCS.ppi()))) {
		WTRiASCS CS;

			THROW_FAILED_HRESULT(m_pSelectCoordSysDlg->GetSelectedCS(CS.ppi()));
			THROW_FAILED_HRESULT(SelectCS->put_CS(CS));
		}

		if (FAILED(m_ImportExt->QueryInterface (Import.ppi()))) {
		// normalen Import durchführen
			THROW_FAILED_HRESULT(m_ImportExt -> ImportData (Enum, GetImportFlags()));
		} 
		else {
			THROW_FAILED_HRESULT(Import -> ImportDataWithResult (Enum, GetImportFlags(), 
				NULL, (IEnumLONG **)ppIEnum));
		}

	} COM_CATCH;
	return S_OK;
}

HRESULT CImportDataDlg::GetNamesAsEnum (IEnumString **ppIEnum)
{
	if (NULL == ppIEnum) 
		return E_POINTER;
	*ppIEnum = NULL;

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

int CImportDataDlg::GetPageIndex (CPropertySheet *pSheet)
{
int iIndex = -1;

	for (int i = 0; i < pSheet -> GetPageCount(); i++) {
		if ((CPropertyPage *)this == pSheet -> GetPage (i)) {
			iIndex = i;
			break;
		}
	}
	return iIndex;
}

HRESULT CImportDataDlg::ResetExtPages()
{
// evtl. alte Pages freigeben
CPropertySheet *pSheet = GetPropertySheet();
int iMyIndex = GetPageIndex (pSheet);

	TX_ASSERT(iMyIndex != -1);

	++iMyIndex;			// Koordinatenseite nicht rauslöschen
	while (m_uiCnt > 0) {
		pSheet -> ForwardEvent (PSM_REMOVEPAGE, iMyIndex+1);
		m_uiCnt--;
	}

// evtl. altes Objekt freigeben
	m_ExtPages.Assign(NULL);
	m_uiCnt = 0;
	return S_OK;
}

BOOL CImportDataDlg::LoadExtPages (IImportGeoData *pIImport, REFGUID rGuid)
{
	USES_CONVERSION;
	COM_TRY {
		ResetExtPages();

	// wenn kein Objekt für diesen DataServer existiert, dann weiter
		if (IsEqualGUID(rGuid, GUID_NULL))
			return FALSE;

	// Objekt für zusätzliche Pages erzeugen und initialisieren
	CPropertySheet *pSheet = GetPropertySheet();
	WTRiASImportWizardPropExt ExtPages (rGuid);	// throws hr
	char cbCaption[_MAX_PATH];

		GetCaption (cbCaption, sizeof(cbCaption));
		THROW_FAILED_HRESULT(ExtPages -> InitForImportDialog (pIImport, A2OLE(cbCaption), m_dwFlags));

	// Pages einhängen
	WTriasPropSheetExt SheetExt (ExtPages);

		THROW_FAILED_HRESULT(SheetExt -> AddPages (AddPropSheetPageProc, reinterpret_cast<LPARAM>(pSheet)));
		THROW_FAILED_HRESULT(ExtPages -> get_PageCount (&m_uiCnt));

		if (0 != m_uiCnt)
			m_ExtPages = ExtPages;

	} COM_CATCH_OP_RETURN (ResetExtPages(), FALSE);
	return TRUE;	// Objekt erfolgreich geladen
}

BOOL CImportDataDlg::AddPropSheetPageProc (HPROPSHEETPAGE hPSP, LPARAM lParam)
{
	return reinterpret_cast<CPropertySheet *>(lParam) -> ForwardEvent(PSM_ADDPAGE, 0, (LPARAM)hPSP);
}


