// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/02/1998 09:38:41 PM
//
// @doc
// @module JumpTable.cpp | Sprungverteilertablle für TRiAS-DEX_... commands

#include "fakemfcp.hxx"
#include "fakemfc.h"		// ResourceKonstanten

#include <ospace/file/path.h>
#include <toolguid.h>
#include <itoolbar.h>
#include <AniWaitCursor.h>
#include <ScopeVar.h>
#include <Esnecil.h>

#include "ThisDLL.h"
#include "fakemfc.hxx"		// die Erweiterung selbst
#include "Strings.h"
#include "JumpTable.h"
#include "mainfrm.h"
#include "LicenseMsg.h"
#include "CreateConnectfilter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if defined(_DEBUG)
extern "C" bool g_fGlobalLic;
#else
#define g_fGlobalLic false
#endif // defined(_DEBUG)

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASProject);
DefineSmartInterface(TRiASConnection);

///////////////////////////////////////////////////////////////////////////////
// alle möglichen Windows-Messages hier vorbeischicken
STDMETHODIMP_(LRESULT) CFakeMFCExtension::WindowsNotification (
	UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	if (__DexCmd == wMsg)
		return FullFillWill (wParam, lParam);		// evtl. hier verarbeiten
	return FALSE;		// alles andere normalerweise weiterleiten
}

///////////////////////////////////////////////////////////////////////////////
// Sprungverteilertabelle initialisieren
bool CFakeMFCExtension::InitJumpTable()
{
// größten und kleinsten MessageID suchen
unsigned int iFirst = UINT_MAX;
unsigned int iLast = 0;
const DEXMESSAGEENTRY *pDME = DexMessageEntries;

	for (int i = 0; i < _countof(DexMessageEntries); i++, pDME++) {
	UINT uiMsg = pDME -> m_uiMsg;
	
		if (iFirst > uiMsg) iFirst = uiMsg;
		if (iLast < uiMsg) iLast = uiMsg;
	}
	if (iFirst == USHRT_MAX || iLast == 0)
		return false;
	
	m_iDexProcsNum = iLast-iFirst+1;
	m_i1stDexProc = iFirst;

	ASSERT(m_iDexProcsNum >= 1);
					
// Tabelle anlegen und initialisieren
	ATLTRY(m_cbDexProcs = new DEXMESSAGEPROC [m_iDexProcsNum]);
	if (NULL == m_cbDexProcs) return false;

	for (unsigned short j = 0; j < m_iDexProcsNum; j++) 
		 m_cbDexProcs[j] = NULL;

// Funktionen eintragen
	pDME = DexMessageEntries;
	for (i = 0; i < _countof(DexMessageEntries); i++, pDME++) {
	// erste Zuweisung ?
		ASSERT(NULL == m_cbDexProcs[(pDME -> m_uiMsg) - iFirst]);
		m_cbDexProcs[(pDME -> m_uiMsg) - iFirst] = pDME -> m_pProc;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Sprungverteilertabelle freigeben
void CFakeMFCExtension::FreeJumpTable()
{
	DELETE_VEC(m_cbDexProcs);
}

///////////////////////////////////////////////////////////////////////////////
// DEX_Commands abarbeiten
LRESULT CFakeMFCExtension::FullFillWill (WPARAM wParam, LPARAM lParam)
{
	ASSERT (NULL != m_cbDexProcs);	// über Sprungverteiler abwickeln

register unsigned int uiMsg = wParam-m_i1stDexProc;
	
	if (uiMsg >= 0 && uiMsg < m_iDexProcsNum && NULL != m_cbDexProcs[uiMsg])
		return (this ->* m_cbDexProcs[uiMsg])(DEX_GetContextDataSource(), lParam);

// alle, die nicht implementiert sind, weiterleiten
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// DEX_... command handler

// DEX_CREATENEWGEODB
LRESULT CFakeMFCExtension::OnCreateProject (HPROJECT hPr, LPARAM lParam)
{
CREATEDB *pCD = reinterpret_cast<CREATEDB *>(lParam);

#if defined(_DEBUG)
	ASSERT_POINTER(pCD, DWORD);
	if (sizeof(CREATEDBEX) == pCD -> dwSize)
		ASSERT_POINTER(pCD, CREATEDBEX);
	else {
		ASSERT(sizeof(CREATEDB) == pCD -> dwSize);
		ASSERT_POINTER(pCD, CREATEDB);
	}
	ASSERT(AfxIsValidString(pCD -> m_pName));
	ASSERT(NULL == pCD -> m_pUser || AfxIsValidString(pCD -> m_pUser));
	ASSERT(NULL == pCD -> m_pPassWd || AfxIsValidString(pCD -> m_pPassWd));
#endif // _DEBUG

	if (sizeof(CREATEDBEX) == pCD -> dwSize) {
	// in Storage erzeugen
	CREATEDBEX *pCDEx = reinterpret_cast<CREATEDBEX *>(pCD);
	WTRiASProject Prj;
	HRESULT hr = S_OK;

		if (OPENMODE_CreateInternalDatasource & pCDEx -> m_iMode) {
		// Projekt mit neuer interner datenquelle erzeugen
		OPENMODE rgMode = (OPENMODE)(pCDEx -> m_iMode & ~OPENMODE_CreateInternalDatasource);

			hr = CreateNewProject (pCDEx -> m_pIStorage, pCDEx -> m_pName, rgMode, Prj.ppi());
			if (FAILED(hr))	return ERRCODE_FROM_HRESULT(hr);

		DWORD dwPos = 0;
		CConnectParams Item;
		HRESULT hr = TxGetExtension() -> ReadDataServerParams (dwPos, &Item, g_cbInternalDataBase);
		CFiles Files;
		CString strConnName, strConnDesc;

			strConnName.Format (IDS_CONNECTNAME_DBMS, Item.m_strShortName, 1);		// es ist immer die erste interne Datenquelle
			strConnDesc.Format (IDS_CONNECTDESCRIPTION_DBMS, Item.m_strShortName, 1, Item.m_strFileDesc);

		CString strTemplate;

			VERIFY(strTemplate.LoadString (IDS_FILENAMETEMPLATE_DBMS));
			Files.insert (os_string(strTemplate));
			hr = CreateNewDataSource (Prj, Item.m_ClsId, Files, strConnName, Item.m_strProgID, Item.m_strConnect, true);
			if (FAILED(hr))	return ERRCODE_FROM_HRESULT(hr);

		// DataSource öffnen und ankoppeln
		WTRiASConnection Conn;
		CONNECTMODE rgConnMode = Item.m_fIsReadWrite ? 
					CONNECTMODE(CONNECTMODE_OpenAutoResolution|CONNECTMODE_CloseAutoResolution|CONNECTMODE_OpenReadWrite) : 
					CONNECTMODE_OpenReadOnly;

			THROW_FAILED_HRESULT(OpenDataSource (Prj, Item.m_ClsId, Files, strConnName, 
				strConnDesc, rgConnMode, Item.m_strProgID, Item.m_strConnect, true, false, Conn.ppi()));

		// Koordinatensystem des Projektes erstmal in Datenquelle übernehmen
		BOOL fReReadHeader = FALSE;

			THROW_FAILED_HRESULT(CopyPropertiesToDatasource (Prj, Conn, NULL, &fReReadHeader));

		// Header neu einlesen
			if (fReReadHeader) {
				DEXN_ReReadHeader();	// an alle: Header neu lesen
				DEXN_ReScale();
				DEXN_ReReadContainer();
			}
		} else {
			hr = CreateNewProject (pCDEx -> m_pIStorage, pCDEx -> m_pName, (OPENMODE)pCDEx -> m_iMode, Prj.ppi());
			if (FAILED(hr)) return ERRCODE_FROM_HRESULT(hr);
		}
	}
	else {
	// in Datei erzeugen, Nutzername und PassWord (erstmal) ignorieren
	WTRiASProject Prj;
	HRESULT hr = CreateNewProject (pCD -> m_pName, true, (OPENMODE)pCD -> m_iMode, Prj.ppi());

		if (FAILED(hr))
			return ERRCODE_FROM_HRESULT(hr);
	}
	return WC_RETURN;		// ok, aber keine 0
}

// DEX_PROJECTOPEN oder DEX_PROJECTOPENEX
LRESULT CFakeMFCExtension::OnOpenProject (HPROJECT hPr, LPARAM lParam)
{
#if defined(_BLOCK_CLOSING_DURING_OPENING)
CScopeVar<LONG> fOpening (m_ulOpenSem, 1L);

	if (!fOpening) {
	// nur einmal gleichzeitig öffnen
		ASSERT(FALSE);
		return EC_NOOPEN;
	}
#endif // defined(_BLOCK_CLOSING_DURING_OPENING)

TRIAS_OPEN *pTO = reinterpret_cast<TRIAS_OPEN *>(lParam);

	ASSERT_POINTER(pTO, TRIAS_OPENSTG);		// ist die kleinste Struktur
	ASSERT(sizeof(TRIAS_OPEN) == pTO -> dwSize || sizeof(TRIAS_OPENEX) == pTO -> dwSize || sizeof(TRIAS_OPENSTG) == pTO -> dwSize);
	ASSERT(AfxIsValidString(pTO -> lpProject));

	if (sizeof(TRIAS_OPENSTG) == pTO -> dwSize) {
	// Storagebasiertes Projekt
	CAniWaitCursor Wait(ANICURSOR_LOAD);
	TRIAS_OPENSTG *pTOS = reinterpret_cast<TRIAS_OPENSTG *>(pTO);

		if (S_OK == OpenExistingProject (pTOS -> m_pIStorage, (pTOS -> iMode & OM_RO) ? true : false, pTOS -> pcProject))
		{
		// Projekt neu zeichnen
			if (NULL != m_pViewWnd)
				m_pViewWnd -> InvalidateRect(NULL);
			return WC_RETURN;
		}

	} else {
	// Dateibasiertes Projekt
		ASSERT(NULL == pTO -> lpUser || AfxIsValidString(pTO -> lpUser));
		ASSERT(NULL == pTO -> lpPassWord || AfxIsValidString(pTO -> lpPassWord));

	os_path path = os_string(pTO -> lpProject);

		if (!stricmp (path.extension().c_str(), g_cbRis+1)) {
		// TRiAS-Datenquelle öffnen und implizit konvertieren
		CAniWaitCursor Wait(ANICURSOR_LOAD);

			if (SUCCEEDED(CreateNewProjectOpenAndConvertDatasource (pTO -> lpProject, (pTO -> iMode & OM_RO) ? true : false)))
			{
			// Projekt neu zeichnen
				if (NULL != m_pViewWnd)
					m_pViewWnd -> InvalidateRect(NULL);
				return WC_RETURN;
			}

		} else {
		// versuchen, als TRiAS Workspace eröffnen
		CAniWaitCursor Wait(ANICURSOR_LOAD);

			if (S_OK == OpenExistingProject (pTO -> lpProject, (pTO -> iMode & OM_RO) ? true : false))
			{
			// Projekt neu zeichnen
				if (NULL != m_pViewWnd)
					m_pViewWnd -> InvalidateRect(NULL);
				return WC_RETURN;
			}
		}
	} 
	return EC_NOOPEN;		// nicht weiterleiten, Fehler melden
}

// DEX_PROJECTCLOSE oder DEX_PROJECTCLOSEEX
LRESULT CFakeMFCExtension::OnCloseProject (HPROJECT hPr, LPARAM lParam)
{
#if defined(_BLOCK_CLOSING_DURING_OPENING)
CScopeVar<LONG> fOpening (m_ulOpenSem, 1L);

	if (!fOpening) {
	// nicht während Öffnen schließen
		ASSERT(FALSE);
		return TRUE;
	}
#endif // defined(_BLOCK_CLOSING_DURING_OPENING)
	return FALSE;		// erstmal weiterleiten
}

// DEX_UPDATESTATUSBAR
LRESULT CFakeMFCExtension::OnUpdateStatusBar (HPROJECT hPr, LPARAM lParam)
{
// MainToolbar erzeugen
CMainFrame *pFrame = (CMainFrame *)MWind();

	ASSERT(NULL != pFrame);
	pFrame -> UpdateStatusBar (lParam ? TRUE : FALSE);
	return TRUE;		// nicht weiterleiten
}

// #HK000713: Druckerdaten synchronisieren
// DEX_UPDATEPRINTERSELECTION
LRESULT CFakeMFCExtension::OnUpdatePrinterSelection (HPROJECT hPr, LPARAM lParam)
{
DVTARGETDEVICE *ptd = reinterpret_cast<DVTARGETDEVICE *>(lParam);

	((CThisDLL *)AfxGetApp()) -> UpdatePrinterSelection(ptd);
	return TRUE;		// nicht weiterleiten
}

///////////////////////////////////////////////////////////////////////////////
// DEX_SHOWSTARTUPDIALOG
LRESULT CFakeMFCExtension::OnShowStartupDialog (HPROJECT hPr, LPARAM lParam)
{
// es darf kein Projekt geöffnet sein
	if (NULL != DEX_GetActiveProjectHandle())
		return FALSE;				// TRiAS liefert auch nur FALSE
		
// Dialog anzeigen und auswerten
	return ShowProjectWizard();
}

///////////////////////////////////////////////////////////////////////////////
// #HK001114
// DEX_VERIFYLICLEVEL
LRESULT CFakeMFCExtension::OnVerifyLicenseLevel (HPROJECT hPr, LPARAM lParam)
{
VERIFYLICENSE *pVL = reinterpret_cast<VERIFYLICENSE *>(lParam);

	ASSERT_POINTER(pVL, VERIFYLICENSE);
	ASSERT(sizeof(VERIFYLICENSE) == pVL -> dwSize ||
		sizeof(VERIFYLICENSEEX) == pVL -> dwSize);
	ASSERT(NULL == pVL -> pcCaption || AfxIsValidString(pVL -> pcCaption));
	ASSERT(sizeof(VERIFYLICENSE) == pVL -> dwSize ||
		NULL == reinterpret_cast<VERIFYLICENSEEX *>(pVL) -> pcLicText || 
		AfxIsValidString(reinterpret_cast<VERIFYLICENSEEX *>(pVL) -> pcLicText));

	switch (pVL -> iMode & ~VERIFYMODE_DontShowDialog) {
	case VERIFYMODE_Equal:
		{
			if (!g_fGlobalLic && m_esnecil.IsLevelEqual(pVL -> lLevelOrOption)) {
				if (pVL ->iMode & VERIFYMODE_DontShowDialog)
					return FALSE;

				DEX_ShowLicenseDenyDialog(*pVL);
				return FALSE;
			}
		}
		break;

	case VERIFYMODE_LessOrEqual:
		{
			if (!g_fGlobalLic && !m_esnecil.VerifyLevel(pVL -> lLevelOrOption)) {
				if (pVL ->iMode & VERIFYMODE_DontShowDialog)
					return FALSE;

				DEX_ShowLicenseDenyDialog(*pVL);
				return FALSE;
			}
		}
		break;

	default:
		return FALSE;
	}
	return TRUE;
}

// DEX_VERIFYLICOPTION
LRESULT CFakeMFCExtension::OnVerifyLicenseOption (HPROJECT hPr, LPARAM lParam)
{
VERIFYLICENSE *pVL = reinterpret_cast<VERIFYLICENSE *>(lParam);

	ASSERT_POINTER(pVL, VERIFYLICENSE);
	ASSERT(sizeof(VERIFYLICENSE) == pVL -> dwSize ||
		sizeof(VERIFYLICENSEEX) == pVL -> dwSize);
	ASSERT(NULL == pVL -> pcCaption || AfxIsValidString(pVL -> pcCaption));
	ASSERT(sizeof(VERIFYLICENSE) == pVL -> dwSize ||
		NULL == reinterpret_cast<VERIFYLICENSEEX *>(pVL) -> pcLicText || 
		AfxIsValidString(reinterpret_cast<VERIFYLICENSEEX *>(pVL) -> pcLicText));

	if (!g_fGlobalLic && !m_esnecil.VerifyOptions(pVL -> lLevelOrOption)) {
		if (pVL -> iMode & VERIFYMODE_DontShowDialog)
			return FALSE;

		DEX_ShowLicenseDenyDialog(*pVL);
		return FALSE;
	}
	return TRUE;	
}

// DEX_SHOWDENYLICDLG
LRESULT CFakeMFCExtension::OnShowLicenseDialog (HPROJECT hPr, LPARAM lParam)
{
VERIFYLICENSE *pVL = reinterpret_cast<VERIFYLICENSE *>(lParam);

	ASSERT_POINTER(pVL, VERIFYLICENSE);
	ASSERT(sizeof(VERIFYLICENSE) == pVL -> dwSize ||
		sizeof(VERIFYLICENSEEX) == pVL -> dwSize);
	ASSERT(NULL == pVL -> pcCaption || AfxIsValidString(pVL -> pcCaption));
	ASSERT(sizeof(VERIFYLICENSE) == pVL -> dwSize ||
		NULL == reinterpret_cast<VERIFYLICENSEEX *>(pVL) -> pcLicText || 
		AfxIsValidString(reinterpret_cast<VERIFYLICENSEEX *>(pVL) -> pcLicText));

	if (sizeof(VERIFYLICENSEEX) == pVL -> dwSize)
		m_vLic = *reinterpret_cast<VERIFYLICENSEEX *>(pVL);
	else
		m_vLic = *pVL;

	if (pVL -> iMode & VERIFYMODE_ShowDialogSync)
		return OnShowLicenseDialogPost (hPr, lParam);

// Dialog asynchron anzeigen (wenn mal Zeit dazu ist)
	PostMessage(__hWndM, __DexCmd, WM_SHOWDENYLICENSEDIALOG, 0);
	return TRUE;
}

// WM_SHOWDENYLICENSEDIALOG
LRESULT CFakeMFCExtension::OnShowLicenseDialogPost (HPROJECT hPr, LPARAM lParam)
{
CWnd *pWnd = (NULL != m_vLic.hWndParent) ? CWnd::FromHandle(m_vLic.hWndParent) : MWind();

	if (NULL == pWnd || pWnd -> IsWindowVisible()) {
	CLicenseMsg Dlg (pWnd, m_vLic.pcCaption, m_vLic.pcLicText);

		Dlg.DoModal();	
	}
	return TRUE;	// niemals weiterleiten
}

///////////////////////////////////////////////////////////////////////////////
// ProjectBar angezeigt
// WM_QUERYPROJECTBARACTIVE
LRESULT CFakeMFCExtension::OnQueryProjectBarActive(HPROJECT hPr, LPARAM lParam)
{
	_ASSERTE(0 != lParam);
#if defined(_USE_DOCKEDTABWINDOW)
	*reinterpret_cast<BOOL *>(lParam) = ((CMainFrame *)AfxGetMainWnd()) -> ProjectBarIsVisible();
#else
	*reinterpret_cast<BOOL *>(lParam) = TRUE;
#endif // defined(_USE_DOCKEDTABWINDOW)
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// OverViewBar angezeigt
// WM_QUERYOVERVIEWBARACTIVE
LRESULT CFakeMFCExtension::OnQueryOverViewBarActive(HPROJECT hPr, LPARAM lParam)
{
	_ASSERTE(0 != lParam);
#if defined(_USE_DOCKEDTABWINDOW)
	*reinterpret_cast<BOOL *>(lParam) = ((CMainFrame *)AfxGetMainWnd()) -> OverviewBarIsVisible();
#else
	*reinterpret_cast<BOOL *>(lParam) = TRUE;
#endif // defined(_USE_DOCKEDTABWINDOW)
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// OverViewBar angezeigt
// WM_QUERYSABiSBARACTIVE
LRESULT CFakeMFCExtension::OnQuerySABiSBarActive(HPROJECT hPr, LPARAM lParam)
{
	_ASSERTE(0 != lParam);
#if defined(_USE_DOCKEDTABWINDOW)
	*reinterpret_cast<BOOL *>(lParam) = ((CMainFrame *)AfxGetMainWnd()) -> SABiSBarIsVisible();
#else
	*reinterpret_cast<BOOL *>(lParam) = TRUE;
#endif // defined(_USE_DOCKEDTABWINDOW)
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// GenricBar angezeigt
// WM_QUERYGENERICBARACTIVE
LRESULT CFakeMFCExtension::OnQueryGenericBarActive(HPROJECT hPr, LPARAM lParam)
{
	_ASSERTE(0 != lParam);
#if defined(_USE_DOCKEDTABWINDOW)
GENERICBARINFO *pGBI = reinterpret_cast<GENERICBARINFO *>(lParam);

	_ASSERTE(!IsBadReadPtr(pGBI, sizeof(GENERICBARINFO)));
	_ASSERTE(sizeof(GENERICBARINFO) == pGBI -> dwSize);
	pGBI -> fVisible = ((CMainFrame *)AfxGetMainWnd()) -> GenericBarIsVisible(pGBI -> guidSid);
#else
	pGBI -> fVisible = TRUE;
#endif // defined(_USE_DOCKEDTABWINDOW)
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// #HK021219
// DEX_CREATECONNECTIONFILTER_DLG 
LRESULT CFakeMFCExtension::OnShowCreateConnectionFilterDlg (HPROJECT hPr, LPARAM lParam)	
{
#if _TRiAS_VER < 0x0510
extern DWORD g_dwVer51;

	if (0 == g_dwVer51)
		return FALSE;		// not supported (yet)
#endif // _TRiAS_VER < 0x0510

CREATECONNECTIONFILTER *pCCF = reinterpret_cast<CREATECONNECTIONFILTER *>(lParam);

	_ASSERTE(!IsBadReadPtr(pCCF, sizeof(CREATECONNECTIONFILTER)));
	_ASSERTE(sizeof(CREATECONNECTIONFILTER) == pCCF -> dwSize);
	_ASSERTE(NULL == pCCF -> pName || !IsBadWritePtr(pCCF -> pName, pCCF -> iLen));
	_ASSERTE(NULL == pCCF -> hWndParent || ::IsWindow(pCCF -> hWndParent));
	_ASSERTE(!(pCCF -> fShowPropertiesOnly && 
		(NULL == pCCF -> pName || '\0' == pCCF -> pName[0])));

// Dialog erzeugen, Voreinstellungen machen und anzeigen
UINT uiResId = (pCCF -> fShowApplyAllConnections) ? 
	CCreateConnectfilter::IDD : CCreateConnectfilter::IDD_NOAPPLY;
CWnd *pwndParent = CWnd::FromHandle(pCCF -> hWndParent);
CCreateConnectfilter Dlg (uiResId, pwndParent);

	Dlg.SetApplyToAllConnections(pCCF -> fApplyAllConnections);
	Dlg.SetEditMode(pCCF -> fShowPropertiesOnly);
	if (NULL != pCCF -> pName && '\0' != pCCF -> pName[0])
		Dlg.SetFilterName(pCCF -> pName);
	Dlg.SetTargetObject(pCCF -> hTargetONr);
	Dlg.SetFilterTyp (pCCF -> iMode);

int iResult = Dlg.DoModal();

	if (IDCANCEL != iResult) {
	// Ok gedrückt, also Einstellungen zurückkopieren
		if (NULL != pCCF -> pName) {
		CString strFilterName(Dlg.GetFilterName());
		int iToCopy = min(pCCF -> iLen-1, strFilterName.GetLength());

			strncpy (pCCF -> pName, strFilterName, iToCopy);
			pCCF -> pName[iToCopy] = '\0';
		}
		pCCF -> fApplyAllConnections = Dlg.GetApplyToAllConnections();
		pCCF -> fNameIsNew = Dlg.GetNameIsNew();
		pCCF -> iMode = Dlg.GetFilterTyp();

	// ggf. auch das gewünschte durchführen
		Dlg.ApplySettings(pCCF -> fApplySettings);
	}
	pCCF -> iRetVal = iResult;
	return TRUE;	// immer TRUE, da sonst TRiAS gerufen wird
}

///////////////////////////////////////////////////////////////////////////////
// #HK030107
// DEX_SHOWCONNECTFILTERS 
LRESULT CFakeMFCExtension::OnShowConnectionFilters (HPROJECT hPr, LPARAM lParam)	
{
// es muß ein Projekt geöffnet sein
	if (NULL == DEX_GetActiveProjectHandle())
		return TRUE;

#if _TRiAS_VER < 0x0510
extern DWORD g_dwVer51;

	if (0 == g_dwVer51)
		return TRUE;		// not supported (yet)
#endif // _TRiAS_VER < 0x0510

CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
CTRiASView *pView = (CTRiASView *)pFrame->GetActiveView();

	if (NULL == pView)
		return TRUE;		// noch nichtfertig initialisiert

	ASSERT_KINDOF(CTRiASView, pView);
	pView -> m_fPaintConnectFilters = lParam ? TRUE : FALSE;

	return TRUE;	// immer TRUE, da sonst TRiAS gerufen wird
}

// DEX_CONNECTFILTERSSHOWN 
LRESULT CFakeMFCExtension::OnConnectionFiltersShown (HPROJECT hPr, LPARAM lParam)	
{
BOOL *pResult = reinterpret_cast<BOOL *>(lParam);

	_ASSERTE(!IsBadWritePtr(pResult, sizeof(BOOL)));
	*pResult = FALSE;

// es muß ein Projekt geöffnet sein
	if (NULL == DEX_GetActiveProjectHandle())
		return TRUE;

#if _TRiAS_VER < 0x0510
extern DWORD g_dwVer51;

	if (0 == g_dwVer51)
		return TRUE;		// not supported (yet)
#endif // _TRiAS_VER < 0x0510

CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
CTRiASView *pView = (CTRiASView *)pFrame->GetActiveView();

	if (NULL == pView)
		return TRUE;		// noch nichtfertig initialisiert

	ASSERT_KINDOF(CTRiASView, pView);
	*pResult = pView -> m_fPaintConnectFilters;

	return TRUE;	// immer TRUE, da sonst TRiAS gerufen wird
}

