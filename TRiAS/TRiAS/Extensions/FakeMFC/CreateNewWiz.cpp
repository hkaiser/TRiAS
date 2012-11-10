// CreateNewWiz.cpp : implementation file
//

#include "fakemfcp.hxx"

#include <xtensnn.h>
#include <registrx.hxx>
#include <hdrentrx.hxx>
#include <AniWaitCursor.h>
#include <ScopeVar.h>

#include "fakemfc.h"
#include <dirisole.h>
#include <xtsnguid.h>
#include <toolguid.h>
#include <itoolbar.h>
#include "fmfcguid.h"

#include "fakemfc.hxx"		// die Erweiterung selbst
#include "Strings.h"

#include "OpenNewPropertySheet.h"
#include "WelcomePage.h"
#include "CreateNewWiz.h"
//#include "CreateNewParamWiz.h"
#include "SelectConnectionPage.h"
#include "SelectConnectParams.h"
#include "SelectConnectionOpenNew.h"
#include "ManageConnections.h"

#include "CoordSysKeys.h"
#include "AttachNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASMainDBEngine);
DefineSmartInterface(TRiASProjects);
DefineSmartInterface(TRiASProject);
DefineSmartInterface(TRiASConnections);
DefineSmartInterface(TRiASConnection);
DefineSmartInterface(EnumVARIANT);

/////////////////////////////////////////////////////////////////////////////
// CreateNewProjectWizard: bei TRiAS-Start anzeigen
bool CFakeMFCExtension::ShowProjectWizard (void)
{
COpenNewPropertySheet Wiz (g_cbNil, MWind());
CWelcomePage Welcome;
CCreateNewWiz AskForCoordSystem;
CSelectConnectionOpenNew DataSourceOpenNew;
CSelectConnectionPage WhichConnection;
CSelectConnectParams ConnectParams (CSelectConnectParams::IDD);
CSelectConnectParams ConnectParamsDbms (CSelectConnectParams::IDD_DBMS, TRUE);
//CCreateNewParamWiz AskForParams;

	ConnectParams.AssocCoordSysWiz(CCreateNewWiz::IDD_CAPTION_NEW);
	ConnectParamsDbms.AssocCoordSysWiz(CCreateNewWiz::IDD_CAPTION_NEW);

	Wiz.AddPage (&Welcome);
	Wiz.AddPage (&AskForCoordSystem);
	Wiz.AddPage (&DataSourceOpenNew);
	if (TRIASMODE_GDO & g_dwHookFlags) 		// TRiAS läuft auf GDO
		Wiz.AddPage (&WhichConnection);
	Wiz.AddPage (&ConnectParams);
	Wiz.AddPage (&ConnectParamsDbms);
//	Wiz.AddPage (&AskForParams);

// Wizard anzeigen
	Wiz.SetWizardMode();
	if (IDCANCEL == Wiz.DoModal())
		return false;

CAniWaitCursor Wait(ANICURSOR_LOAD);

	MWind() -> UpdateWindow();				// UI richten
	Wiz.HandleConnectString();				// ConnectString auslesen und umhängen

// jetzt alle Infos entsprechend auswerten und gewünschte Aktion ausführen
#if defined(_BLOCK_CLOSING_DURING_OPENING)
CScopeVar<LONG> fOpening (m_ulOpenSem, 1L);

	if (!fOpening) {
	// nicht ein 2. mal Öffnen
		ASSERT(FALSE);
		return TRUE;
	}
#endif // defined(_BLOCK_CLOSING_DURING_OPENING)

// jetzt gehts weiter
	switch (Wiz.GetOpenMode()) {
	case PROJECTOPENMODE_CreateNew:	// neu Erzeugen eines Projektes
		{
		WTRiASProject Prj;
		HRESULT hr = S_OK;
		CSelectConnectParams *pConnectParams = &ConnectParams;

			if (Wiz.GetConnectParams() -> GetDbmsMode()) {
				if (ConnectParamsDbms.ShouldPrepareResults())
					ConnectParamsDbms.PrepareResults(true);

				pConnectParams = &ConnectParamsDbms;
				Wiz.HandleConnectString();			// ConnectString auslesen und umhängen
			}

			if (DATASOURCEMODE_CreateNew == Wiz.GetDatasourceMode()) {
			// neues Projekt und neue Datenquelle erzeugen
				hr = CreateNewProjectNewDatasource (Wiz.GetConnectParams(), 
					pConnectParams -> GetFiles(), pConnectParams -> m_strConnectName,
					pConnectParams -> m_strConnectDesc, AskForCoordSystem, Prj.ppi());
			} 
			else if (DATASOURCEMODE_OpenExistend == Wiz.GetDatasourceMode()) {
			// neues Projekt mit Verweis auf existierende Datenquelle erzeugen
				hr = CreateNewProjectOpenDatasource (Wiz.GetConnectParams(), 
					pConnectParams -> GetFiles(), pConnectParams -> m_strConnectName,
					pConnectParams -> m_strConnectDesc, AskForCoordSystem, Prj.ppi());
			} 
			else {
				ASSERT(DATASOURCEMODE_OpenExistend == Wiz.GetDatasourceMode() ||
					   DATASOURCEMODE_CreateNew == Wiz.GetDatasourceMode());
			}

		// nur was machen, wenn kein Fehler aufgetreten ist
			if (SUCCEEDED(hr)) {
			// Eintragungen aus Registry in Projekt wegschreiben
//				AskForCoordSystem.RegisterEntries(HACTPROJECT);
//				AskForParams.RegisterEntries();

				DEX_KickIdle();

			// evtl. Import anschieben
				if (CREATEMODE_ImportData == Wiz.GetCreateMode())
					MWind() -> PostMessage (WM_COMMAND, IDM_IMPORT);
			} 
		}
/*		{
		// Projekt erzeugen, dazu StandardBefehl auslösen
			pWnd -> SendMessage (WM_COMMAND, IDM_NEWDB, AskForParams.GetCompatibilityMode());

		// Eintragungen aus Registry in GeoDB wegschreiben
			AskForParams.RegisterEntries();
			AskForCoordSystem.RegisterEntries();
			DEX_KickIdle();	// UI richten

		}
*/		break;
		
	case PROJECTOPENMODE_OpenExistend:	// existierendes Projekt öffnen
		ShowOpenprojectCommand();
		break;

	case PROJECTOPENMODE_OpenMRU:		// zuletzt benutztes Projekt öffnen
		OpenLastMRUProject();
		break;
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// CreateNewProjectWizard: bei 'Projekt Neu ...' anzeigen
bool CFakeMFCExtension::ShowNewprojectCommand (void)
{
// evtl. geöffnetes Projekt schließen
HPROJECT hPr = NULL;	//DEX_GetActiveProjectHandle();

	if (!DEX_CloseProject(hPr))
		return false;		// Projekt wurde nicht geschlossen

// jetzt wirklich neues Projekt erzeugen
COpenNewPropertySheet Wiz (g_cbNil, MWind());
CCreateNewWiz AskForCoordSystem;
CSelectConnectionOpenNew DataSourceOpenNew;
CSelectConnectionPage WhichConnection;
CSelectConnectParams ConnectParams (CSelectConnectParams::IDD);
CSelectConnectParams ConnectParamsDbms (CSelectConnectParams::IDD_DBMS, TRUE);
//CCreateNewParamWiz AskForParams;

	AskForCoordSystem.SetStandAlone();

	ConnectParams.AssocCoordSysWiz(CCreateNewWiz::IDD_CAPTION_NEW);
	ConnectParamsDbms.AssocCoordSysWiz(CCreateNewWiz::IDD_CAPTION_NEW);

	Wiz.AddPage (&AskForCoordSystem);
	Wiz.AddPage (&DataSourceOpenNew);
	if (TRIASMODE_GDO & g_dwHookFlags) 		// TRiAS läuft auf GDO
		Wiz.AddPage (&WhichConnection);
	Wiz.AddPage (&ConnectParams);
	Wiz.AddPage (&ConnectParamsDbms);
//	Wiz.AddPage (&AskForParams);

// Wizard anzeigen
	Wiz.SetWizardMode();
	if (IDCANCEL == Wiz.DoModal())
		return false;

CAniWaitCursor Wait(ANICURSOR_LOAD);

	MWind() -> UpdateWindow();				// UI richten
	Wiz.HandleConnectString();				// ConnectString auslesen und umhängen

// jetzt alle Infos entsprechend auswerten und gewünschte Aktion ausführen
#if defined(_BLOCK_CLOSING_DURING_OPENING)
CScopeVar<LONG> fOpening (m_ulOpenSem, 1L);

	if (!fOpening) {
	// nicht ein 2. mal Öffnen
		ASSERT(FALSE);
		return TRUE;
	}
#endif // defined(_BLOCK_CLOSING_DURING_OPENING)

// jetzt gehts weiter
WTRiASProject Prj;
HRESULT hr = S_OK;
CSelectConnectParams *pConnectParams = &ConnectParams;

	if (Wiz.GetConnectParams() -> GetDbmsMode()) {
		if (ConnectParamsDbms.ShouldPrepareResults()) 
			ConnectParamsDbms.PrepareResults(true);

		Wiz.HandleConnectString();			// ConnectString auslesen und umhängen
		pConnectParams = &ConnectParamsDbms;
	}

	if (DATASOURCEMODE_CreateNew == Wiz.GetDatasourceMode()) {
	// neues Projekt und neue Datenquelle erzeugen
		hr = CreateNewProjectNewDatasource (Wiz.GetConnectParams(), 
			pConnectParams -> GetFiles(), pConnectParams -> m_strConnectName,
			pConnectParams -> m_strConnectDesc, AskForCoordSystem, Prj.ppi());
	} 
	else if (DATASOURCEMODE_OpenExistend == Wiz.GetDatasourceMode()) {
	// neues Projekt mit Verweis auf existierende Datenquelle erzeugen
		hr = CreateNewProjectOpenDatasource (Wiz.GetConnectParams(), 
			pConnectParams -> GetFiles(), pConnectParams -> m_strConnectName,
			pConnectParams -> m_strConnectDesc, AskForCoordSystem, Prj.ppi());
	} 
	else {
		ASSERT(DATASOURCEMODE_OpenExistend == Wiz.GetDatasourceMode() ||
			   DATASOURCEMODE_CreateNew == Wiz.GetDatasourceMode());
	}

// nur was machen, wenn kein Fehler aufgetreten ist
	if (SUCCEEDED(hr)) {
	// Eintragungen aus Registry in Projekt wegschreiben
//		AskForCoordSystem.RegisterEntries(HACTPROJECT);
		DEX_KickIdle();	// UI richten

	// evtl. Import anschieben
		if (CREATEMODE_ImportData == Wiz.GetCreateMode())
			MWind() -> PostMessage (WM_COMMAND, IDM_IMPORT);
	}
/*
// GeoDB erzeugen, dazu StandardBefehl auslösen
	MWind() -> SendMessage (WM_COMMAND, IDM_NEWDB, AskForParams.GetCompatibilityMode());

// Eintragungen aus Registry in GeoDB wegschreiben
	AskForParams.RegisterEntries();
	AskForCoordSystem.RegisterEntries();
	DEX_KickIdle();		// UI richten
*/
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// CreateNewProjectWizard: bei 'Projekt Neu ...' anzeigen
HRESULT CFakeMFCExtension::ShowAddConnectionCommand (CWnd *pWnd, BOOL fShowError)
{
COpenNewPropertySheet Wiz (IDS_ADDDATASOURCE, NULL == pWnd ? MWind() : pWnd);
CSelectConnectionOpenNew DataSourceOpenNew (CSelectConnectionOpenNew::IDD_ADD, CSelectConnectionOpenNew::IDD_CAPTION_ADD);
CSelectConnectionPage WhichConnection (CSelectConnectionPage::IDD_CAPTION_ADD);
CSelectConnectParams ConnectParams (CSelectConnectParams::IDD, FALSE, CSelectConnectParams::IDD_CAPTION_ADD);
CSelectConnectParams ConnectParamsDbms (CSelectConnectParams::IDD_DBMS, TRUE, CSelectConnectParams::IDD_CAPTION_ADD);
//CCreateNewParamWiz AskForParams;

	DataSourceOpenNew.SetStandAlone();

	ConnectParams.AssocCoordSysWiz(CCreateNewWiz::IDD_CAPTION_ADD);
	ConnectParamsDbms.AssocCoordSysWiz(CCreateNewWiz::IDD_CAPTION_ADD);

	Wiz.AddPage (&DataSourceOpenNew);
	if (TRIASMODE_GDO & g_dwHookFlags) 		// TRiAS läuft auf GDO
		Wiz.AddPage (&WhichConnection);
	Wiz.AddPage (&ConnectParams);
	Wiz.AddPage (&ConnectParamsDbms);
//	Wiz.AddPage (&AskForParams);

// Wizard anzeigen
	Wiz.SetWizardMode();
	if (IDCANCEL == Wiz.DoModal())
		return S_FALSE;

CAniWaitCursor Wait(ANICURSOR_LOAD);

	if (NULL != pWnd) 
		pWnd -> UpdateWindow();
	if (pWnd != MWind())
		MWind() -> UpdateWindow();

	Wiz.HandleConnectString();		// ConnectString auslesen und umhängen

// jetzt alle Infos entsprechend auswerten und gewünschte Aktion ausführen
#if defined(_BLOCK_CLOSING_DURING_OPENING)
CScopeVar<LONG> fOpening (m_ulOpenSem, 1L);

	if (!fOpening) {
	// nicht ein 2. mal Öffnen
		ASSERT(FALSE);
		return S_FALSE;
	}
#endif // defined(_BLOCK_CLOSING_DURING_OPENING)

// jetzt gehts weiter
HRESULT hr = S_OK;
CSelectConnectParams *pConnectParams = &ConnectParams;

	if (Wiz.GetConnectParams() -> GetDbmsMode()) {
		if (ConnectParamsDbms.ShouldPrepareResults()) 
			ConnectParamsDbms.PrepareResults(true);

		Wiz.HandleConnectString();			// ConnectString auslesen und umhängen
		pConnectParams = &ConnectParamsDbms;
	}

	if (DATASOURCEMODE_CreateNew == Wiz.GetDatasourceMode()) {
	// neues Projekt und neue Datenquelle erzeugen
		hr = AddNewDatasource (Wiz.GetConnectParams(), 
			pConnectParams -> GetFiles(), pConnectParams -> m_strConnectName,
			pConnectParams -> m_strConnectDesc);
	} 
	else if (DATASOURCEMODE_OpenExistend == Wiz.GetDatasourceMode()) {
	// neues Projekt mit Verweis auf existierende Datenquelle erzeugen
		hr = AddOpenDatasource (Wiz.GetConnectParams(), 
			pConnectParams -> GetFiles(), pConnectParams -> m_strConnectName,
			pConnectParams -> m_strConnectDesc);
	} 
	else {
		ASSERT(DATASOURCEMODE_OpenExistend == Wiz.GetDatasourceMode() ||
			   DATASOURCEMODE_CreateNew == Wiz.GetDatasourceMode());
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Eindeutigkeit des Namens der Connection sicherstellen
CString CFakeMFCExtension::EnsureUniqueConnectionName (
	CWnd *pWnd, LPCSTR pcOrigName, LPCSTR pcFileName, BOOL *pfCorrected)
{
	_ASSERTE(NULL != pcOrigName);
	_ASSERTE(NULL != pfCorrected);

CString strName (pcOrigName);

	*pfCorrected = FALSE;
	while (S_OK == FindConnection (strName) || 
		   S_OK == ToDeleteConnection (strName)) {
	// eine Connection mit diesem Namen gibt es schon
	CAttachNumber AN;

		if (AN.HasNumbering (strName)) 
			strName = AN.CorrectNumbering (strName);
		else 
			strName += " (1)";

		if (!*pfCorrected) {
		// Meldung nur einmal anzeigen
			VMessageBox (pWnd, FakeTRiASName(IDS_DATASOURCEERROR_CAP, g_cbTRiAS).c_str(), 
				MB_OK|MB_ICONSTOP, IDS_CONNECTNAMEISNOTUNIQUE, pcOrigName, pcFileName,
				(LPCSTR)strName);
		}
		*pfCorrected = TRUE;
	}
	return strName;
}

///////////////////////////////////////////////////////////////////////////////
// Überprüfen, ob in einem evtl. aktiven CManageConnectiondlg die neue
// Connection gelöscht wurde
HRESULT CFakeMFCExtension::ToDeleteConnection(LPCSTR pToSearch)
{
	if (NULL == m_pManageConnections)
		return S_FALSE;		// nichts zu löschen ist da

	return m_pManageConnections->IsConnectionDeleted(CComBSTR(pToSearch)) ? S_OK : S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Überprüfen, ob eine gegebene Connection bereits existiert
HRESULT CFakeMFCExtension::FindConnection (LPCSTR pcToSearch)
{
	_ASSERTE(NULL != pcToSearch);

CComBSTR bstrToSearch (pcToSearch);
char cbBuffer[_MAX_PATH];

	if (NULL == DEX_GetActiveProject(cbBuffer))
		return S_FALSE;		// neu angelegtes Projekt mit erster Datenquelle

	try {
	WTRiASMainDBEngine Main;
	WTRiASProjects Prjs;

		THROW_FAILED_HRESULT(GetMainDBEngine (Main.ppi()));
		THROW_FAILED_HRESULT(Main -> get_Projects (Prjs.ppi()));

	// aktuelles Projekt wiederfinden
	WTRiASProject Prj;

		THROW_FAILED_HRESULT(Prjs -> Item(CComVariant(cbBuffer), Prj.ppi()));

	// alle Connections des Projektes durchgehen
	WTRiASConnections Conns;

		THROW_FAILED_HRESULT(Prj -> get_Connections (Conns.ppi()));

	WEnumVARIANT Enum;
	CComVariant v;
	
		THROW_FAILED_HRESULT(Conns -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &v, NULL); /**/) 
		{
			THROW_FAILED_HRESULT(v.ChangeType(VT_UNKNOWN));

		// Bezeichner vergleichen
		WTRiASConnection Conn (V_UNKNOWN(&v));
		CComBSTR bstrDesc;

			THROW_FAILED_HRESULT(Conn -> get_Name(CLEARED(&bstrDesc)));
			if (!wcscmp (bstrToSearch, bstrDesc))
				return S_OK;	// gefunden
		}
	} COM_CATCH;
	return S_FALSE;		// nichts gefunden
}

/////////////////////////////////////////////////////////////////////////////
// DataItem, welches in Tree hängt

CCoordSystemItem::CCoordSystemItem (LPCSTR pcRegKey, LPCSTR pcSubKey)
{
	m_strRegKey = pcRegKey;
	m_strRegKey += g_cbDel;
	m_strRegKey += pcSubKey;

CCurrentUser regKey (KEY_READ, pcRegKey);
char cbBuffer[_MAX_PATH];
LONG lLen = sizeof(cbBuffer);

	if (regKey.GetSZ (pcSubKey, cbBuffer, lLen))
		m_strFullDesc = cbBuffer;

CCurrentUser regTcf (KEY_READ, m_strRegKey);

	lLen = sizeof(cbBuffer);
	if (regTcf.GetSubSZ ("CoordTcfName", cbBuffer, (ULONG &)lLen))
		m_strTcfName = cbBuffer;
}


/////////////////////////////////////////////////////////////////////////////
// CCreateNewWiz property page

IMPLEMENT_DYNCREATE(CCreateNewWiz, CPropertyPage)

CCreateNewWiz::CCreateNewWiz(BOOL fCoordSysForPrj, UINT uiCapID) 
	: CPropertyPage(IDD)
{
	//{{AFX_DATA_INIT(CCreateNewWiz)
	//}}AFX_DATA_INIT
	m_fStandAlone = FALSE;
	if (0 == uiCapID)
		uiCapID = IDS_CREATENEWWIZARD;

	m_fCoordSysForPrj = fCoordSysForPrj;
	m_uiPrompt = fCoordSysForPrj ? IDS_COORDSYS_PRJ : IDD_PROMPT_DS;
	m_fIsLast = false;

// Caption den aktuellen Erfordernissen anpassen
	TRY {
	CString strOrgCap;

		VERIFY(strOrgCap.LoadString (uiCapID));
		m_strCaption.Format (strOrgCap, g_cbTRiAS);
		m_psp.pszTitle = m_strCaption;
		m_psp.dwFlags |= PSP_USETITLE;

	} CATCH (CMemoryException, e) {
		TRACE("Couldn't change caption for CCreateNewWiz\r\n");
	} END_CATCH;
}

CCreateNewWiz::~CCreateNewWiz()
{
}

void CCreateNewWiz::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateNewWiz)
	DDX_Control(pDX, IDC_DESCTEXT, m_ftDescText);
	DDX_Control(pDX, IDC_COORDDESCRIPTION, m_ftDescription);
	DDX_Control(pDX, IDC_COORDSYSTEMS, m_tvCoordSystems);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCreateNewWiz, CPropertyPage)
	//{{AFX_MSG_MAP(CCreateNewWiz)
	ON_NOTIFY(NM_DBLCLK, IDC_COORDSYSTEMS, OnDblclkCoordSystems)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// sonstige Funktionen
bool CCreateNewWiz::InitCoordSystemsFromRegistry (void)
{
CCurrentUser regCoords (KEY_READ, g_cbCoordSystems);

	if (!regCoords.isValid()) return false;

DWORD i = 0;
char cbEnumKey[_MAX_PATH];
bool fNotEmpty = false;

	while (RegEnumKey (regCoords, i, cbEnumKey, _MAX_PATH) == ERROR_SUCCESS) {
		if (InitCoordSystem (regCoords, TVI_ROOT, g_cbCoordSystems, cbEnumKey))
			fNotEmpty = true;
		i++;
	}
	return fNotEmpty;
}

bool CCreateNewWiz::InitCoordSystem (CRegistry &rCurr, HTREEITEM hParent, LPCSTR pcFullKey, LPCSTR pcKey)
{
char cbBuffer[_MAX_PATH];
LONG lLen = sizeof(cbBuffer);

	if (!rCurr.GetSZ (pcKey, cbBuffer, lLen))		// Beschreibung der Klasse lesen
		return false;

CString strFullKey (pcFullKey);

	strFullKey += g_cbDel;
	strFullKey += pcKey;

HTREEITEM hItemParent = m_tvCoordSystems.InsertItem (cbBuffer, IMG_COORDFOLDER, IMG_COORDFOLDER, hParent);
DWORD i = 0;
char cbEnumKey[_MAX_PATH];
CRegistry regEntries (rCurr, KEY_READ, pcKey);
DWORD dwPos = 0;
bool fNotEmpty = false;

	if (!regEntries.GetDWORD (g_cbToolbar32, dwPos)) {
	// ZwischenÜberschrift, weiter in die Rekursion
		while (RegEnumKey (regEntries, i, cbEnumKey, _MAX_PATH) == ERROR_SUCCESS) {
			if (InitCoordSystem (regEntries, hItemParent, strFullKey, cbEnumKey))
				fNotEmpty = true;
			i++;
		}
	} else {
	// eigentliche Koordinatensysteme
		ASSERT(0 <= dwPos && dwPos <= (DWORD)(m_tvCoordSystems.GetImageCount()-1));

		while (RegEnumKey (regEntries, i, cbEnumKey, _MAX_PATH) == ERROR_SUCCESS) {
		CString strCSKey = strFullKey + '\\' + cbEnumKey;
		CCurrentUser regCS (KEY_READ, strCSKey);
		DWORD dwData = 0;

		// nur für Datenquelle, aber Projektfenster
			if (regCS.GetDWORD ("DataSourceOnly", dwData)) {
				if (0 != dwData && m_fCoordSysForPrj) {
					++i;
					continue;
				}
			}

		// nur für Projekt aber Datenquellenfenster
			dwData = 0;
			if (regCS.GetDWORD ("ProjectOnly", dwData)) {
				if (0 != dwData && !m_fCoordSysForPrj) {
					++i;
					continue;
				}
			}

			if (InitCoordSystemEntry (regEntries, hItemParent, strFullKey, cbEnumKey, dwPos))
				fNotEmpty = true;
			i++;
		}
	}
	if (!fNotEmpty)
		m_tvCoordSystems.DeleteItem (hItemParent);
	return fNotEmpty;
}

bool CCreateNewWiz::InitCoordSystemEntry (CRegistry &rCurr, HTREEITEM hParent, 
						LPCSTR pcFullKey, LPCSTR pcSubKey, DWORD dwPos)
{
HTREEITEM hItem = m_tvCoordSystems.InsertItem (pcSubKey, dwPos, dwPos, hParent);

	if (NULL != hItem) {
	CCoordSystemItem *pNewItem = new CCoordSystemItem (pcFullKey, pcSubKey);

		if (!m_tvCoordSystems.SetItemData (hItem, (DWORD)pNewItem)) {
			TRACE0("Could not set item data\n");
			delete pNewItem;
		}
		return true;
	}
	return false;
}

void CCreateNewWiz::SetDescription (HTREEITEM hItem)
{
	if (NULL == hItem)
		hItem = m_tvCoordSystems.GetSelectedItem();
	ASSERT(!m_fNotEmpty || NULL != hItem);

	if (NULL != hItem) {
	CCoordSystemItem *pItemData = (CCoordSystemItem *)m_tvCoordSystems.GetItemData (hItem);

		if (NULL == pItemData) 
			m_ftDescription.SetWindowText (g_cbNil);
		else 
			m_ftDescription.SetWindowText (pItemData -> GetDesc());
	} 
	AdjustButtons(hItem);
}

/////////////////////////////////////////////////////////////////////////////
// CCreateNewWiz message handlers

LRESULT CCreateNewWiz::OnWizardBack() 
{
	ASSERT(!m_fStandAlone);
	return CPropertyPage::OnWizardBack();
}

LRESULT CCreateNewWiz::OnWizardNext() 
{
	ASSERT(!m_fIsLast);			// darf nicht letztes Fenster sein

// Selektierten Eintrag holen
HTREEITEM hItem = m_tvCoordSystems.GetSelectedItem();

	if (NULL == hItem || m_tvCoordSystems.ItemHasChildren (hItem)) 
		return 0;		// nur Childs behandeln

CCoordSystemItem *pItemData = 
	(CCoordSystemItem *)m_tvCoordSystems.GetItemData (hItem);

	if (NULL == pItemData) 
		return 0;

	m_strSelKey = pItemData -> GetRegKey();
	HandleConnectString();

	return CPropertyPage::OnWizardNext();
}

BOOL CCreateNewWiz::OnWizardFinish() 
{
	_ASSERTE(m_fIsLast);			// muß letztes Fenster sein

// Selektierten Eintrag holen
HTREEITEM hItem = m_tvCoordSystems.GetSelectedItem();

	if (NULL == hItem || m_tvCoordSystems.ItemHasChildren (hItem)) 
		return TRUE;		// nur Childs behandeln

CCoordSystemItem *pItemData = 
	(CCoordSystemItem *)m_tvCoordSystems.GetItemData (hItem);

	if (NULL == pItemData) 
		return TRUE;

	m_strSelKey = pItemData -> GetRegKey();
	HandleConnectString();

	return CPropertyPage::OnWizardFinish();
}

BOOL CCreateNewWiz::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
// TreeControl/Imagelist initialisieren
	m_tvCoordSystems.InitTreeCrtl (this);

// Koordinatensysteme einlesen
	m_fNotEmpty = InitCoordSystemsFromRegistry();
	m_tvCoordSystems.SetFocus();

	SetDescription();

// Im Beschreibungstext TRiAS setzen
CString str;
CString strTempl;

	str.Format (m_uiPrompt, g_cbTRiAS);
	m_ftDescText.SetWindowText (str);
	UpdateData (FALSE);

	AdjustButtons();
	return false;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCreateNewWiz::AdjustButtons(HTREEITEM hItem)
{
CPropertySheet *pSheet = (CPropertySheet *)GetParent();
DWORD dwBttns = 0;

	ASSERT(NULL != pSheet);
	if (NULL != hItem) {
	CCoordSystemItem *pItemData = (CCoordSystemItem *)m_tvCoordSystems.GetItemData (hItem);

		if (!m_fStandAlone)
			dwBttns = PSWIZB_BACK;

		if (NULL != pItemData) {
			if (!m_fIsLast)
				dwBttns |= PSWIZB_NEXT;
			else
				dwBttns |= PSWIZB_FINISH;
		}
		else if (m_fIsLast)
			dwBttns |= PSWIZB_DISABLEDFINISH;
	} 
	else if (m_fIsLast)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	pSheet -> SetWizardButtons (dwBttns);
}

BOOL CCreateNewWiz::OnSetActive() 
{
	PresetCS();
	SetDescription();
	return CPropertyPage::OnSetActive();
}

void CCreateNewWiz::OnDblclkCoordSystems(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

HTREEITEM hItem = m_tvCoordSystems.GetSelectedItem();

	if (NULL != hItem) {
	CCoordSystemItem *pItemData = (CCoordSystemItem *)m_tvCoordSystems.GetItemData (hItem);

		if (NULL != pItemData) {
		// nur, wenn leaf selektiert wurde
		CPropertySheet *pSheet = (CPropertySheet *)GetParent();

			ASSERT(NULL != pSheet);
			pSheet -> PressButton (m_fIsLast ? PSBTN_FINISH : PSBTN_NEXT);
		}
	}
}

void CCreateNewWiz::PresetCS()
{
	if (m_strTcfName.GetLength() > 0) {
	HTREEITEM hSelItem = FindTcfName(m_strTcfName);

		if (NULL != hSelItem) {
		HTREEITEM hParent = m_tvCoordSystems.GetParentItem(hSelItem);
		HTREEITEM hParentParent = NULL;

			if (NULL != hParent) 
				hParentParent = m_tvCoordSystems.GetParentItem(hParent);

			if (NULL != hParentParent)
				m_tvCoordSystems.SelectSetFirstVisible(hParentParent);
			else if (NULL != hParent)
				m_tvCoordSystems.SelectSetFirstVisible(hParent);
			else
				m_tvCoordSystems.SelectSetFirstVisible(hSelItem);

			m_tvCoordSystems.SelectItem(hSelItem);
		}
	}
}

HTREEITEM CCreateNewWiz::FindTcfName (LPCSTR pcTcfName, HTREEITEM hParent)
{
HTREEITEM hChild = NULL;

	if (TVI_ROOT == hParent)
		hChild = m_tvCoordSystems.GetNextItem (NULL, TVGN_CHILD);
	else
		hChild = m_tvCoordSystems.GetChildItem (hParent);

	while (NULL != hChild) {
	// diesen Node testen
	CCoordSystemItem *pItemData = (CCoordSystemItem *)m_tvCoordSystems.GetItemData (hChild);

		if (NULL != pItemData && pItemData->GetTcfName() == pcTcfName)
			return hChild;		// gefunden

// anschließend alle Childs abtesten
	HTREEITEM hFoundItem = FindTcfName (pcTcfName, hChild);

		if (NULL != hFoundItem) 
			return hFoundItem;
		hChild = m_tvCoordSystems.GetNextItem (hChild, TVGN_NEXT);
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
bool CCreateNewWiz::RegisterEntries (HPROJECT hPr)
{
	return RegisterEntries (hPr, m_strSelKey);
}

/*static*/
bool CCreateNewWiz::RegisterEntries (HPROJECT hPr, LPCSTR pcRegKey)
{
CCurrentUser regEntry (KEY_READ, pcRegKey);

	for (int i = 0; i < _countof(g_cbCoordSysKeys); i++)
		RegisterEntry (regEntry, g_cbCoordSysKeys[i].m_pKey, g_cbCoordSysKeys[i].m_dwMode, hPr);

	DEXN_ReReadHeader();	// an alle: Header neu lesen
	DEXN_ReScale();
	return true;
}

/*static*/
bool CCreateNewWiz::RegisterEntry (
	CRegistry &rCurr, LPCSTR pcDataName, DWORD dwMode, HPROJECT hPr)
{
// entweder der Eintrag ist vom TYP REG_SZ
char cbBuffer[1024];
DWORD dwLen = sizeof(cbBuffer);

	if (rCurr.GetSubSZ (pcDataName, cbBuffer, dwLen)) {
	HeaderEntryX HE (pcDataName, cbBuffer, dwMode, hPr);
	
		return (EC_OKAY == HE.WriteBack()) ? true : false;	
	}

// oder eben vom Typ REG_DWORD
DWORD dwData = 0;

	if (rCurr.GetDWORD (pcDataName, dwData)) {
		ultoa (dwData, cbBuffer, 10);

	HeaderEntryX HE (pcDataName, cbBuffer, dwMode, hPr);

		return (EC_OKAY == HE.WriteBack()) ? true : false;	
	}
	return false;
}

HRESULT CCreateNewWiz::HandleConnectString()
{
CCurrentUser reg (KEY_READ, m_strSelKey);
char cbBuffer[_MAX_PATH] = { '\0' };
DWORD dwLen = sizeof(cbBuffer);

	if (reg.GetSubSZ("CoordTcfName", cbBuffer, dwLen)) 
	{
	// Namen der CoordSysDatei am Connectstring speichern
		if (m_Pairs.IsValid()) {
			RETURN_FAILED_HRESULT(m_Pairs->SetValue(CComBSTR("COORDSYS"), 
				CComBSTR(cbBuffer), VARIANT_TRUE));
		}
		m_strTcfName = cbBuffer;
	}

// auch noch im DialogKontext ablegen
	if (IsWindow(m_hWnd)) {
		GetPropSheet()->GetConnectParams()->m_strCoordsKey = m_strSelKey;
		if ('\0' != cbBuffer[0])		
			GetPropSheet()->GetConnectParams()->m_strTcfName = cbBuffer;		
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CCoordSystemTree

CCoordSystemTree::CCoordSystemTree()
{
	m_pPage = NULL;
}

CCoordSystemTree::~CCoordSystemTree()
{
}

BEGIN_MESSAGE_MAP(CCoordSystemTree, CTreeCtrl)
	//{{AFX_MSG_MAP(CCoordSystemTree)
	ON_NOTIFY_REFLECT(TVN_DELETEITEM, OnDeleteCoordSystemItem)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemExpanded)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CCoordSystemTree::InitTreeCrtl (CCreateNewWiz *pPage)
{
	m_pPage = pPage;
	if (!m_ilImages.Create (IDB_COORDSYSTEM, 16, 16, RGB(255,0,255))) {
		TRACE0("Could not create imagelist for CoordsystemTree\r\n");
	} else 
		SetImageList(&m_ilImages, TVSIL_NORMAL);
}

/////////////////////////////////////////////////////////////////////////////
// CCoordSystemTree message handlers

void CCoordSystemTree::OnDeleteCoordSystemItem(NMHDR* pNMHDR, LRESULT* pResult) 
{
NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
CCoordSystemItem *pOldItem = (CCoordSystemItem *)pNMTreeView -> itemOld.lParam;

	if (NULL != pOldItem)
		delete pOldItem;
	
	*pResult = 0;
}

void CCoordSystemTree::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
HTREEITEM hItem = pNMTreeView -> itemNew.hItem;

	ASSERT(NULL != hItem);

	if (pNMTreeView -> itemNew.state & TVIS_SELECTED) {
		ASSERT(NULL != m_pPage);
		m_pPage -> SetDescription (hItem);
	}

	AdjustImage (hItem);
}

void CCoordSystemTree::OnItemExpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
HTREEITEM hItem = pNMTreeView -> itemNew.hItem;

	ASSERT(NULL != hItem);
	AdjustImage (hItem);
	*pResult = 0;
}

void CCoordSystemTree::AdjustImage (HTREEITEM hItem)
{
	if (!ItemHasChildren (hItem)) 
		return;		// nur Parents behandeln

	if (GetItemState (hItem, TVIS_EXPANDED) & TVIS_EXPANDED) 
		SetItemImage (hItem, IMG_COORDOPENFOLDER, IMG_COORDOPENFOLDER);	// ist expandiert
	else
		SetItemImage (hItem, IMG_COORDFOLDER, IMG_COORDFOLDER);			// ist collabiert
}

