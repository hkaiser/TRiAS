// CreateNewWiz.cpp : implementation file
//

#include "fakemfcp.hxx"

#include <xtensnn.h>
#include <registrx.hxx>
#include <hdrentrx.hxx>

#include "fakemfc.h"
#include <dirisole.h>
#include <xtsnguid.h>
#include <toolguid.h>
#include <itoolbar.h>
#include "fmfcguid.h"

#include "fakemfc.hxx"		// die Erweiterung selbst
#include "Strings.h"

#include "WelcomePage.h"
#include "CreateNewWiz.h"
#include "CreateNewParamWiz.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CreateNewProjectWizard: bei TRiAS-Start anzeigen
bool CFakeMFCExtension::ShowProjectWizard (void)
{
	if (TOTD_ForceNoWizard & m_dwTOTD) 
		return true;

CPropertySheet Wiz (g_cbNil, MWind());
CWelcomePage Welcome;
CCreateNewWiz AskForCoordSystem;
CCreateNewParamWiz AskForParams;

	Wiz.AddPage (&Welcome);
	Wiz.AddPage (&AskForCoordSystem);
	Wiz.AddPage (&AskForParams);
	Wiz.SetWizardMode();
	if (IDCANCEL == Wiz.DoModal())
		return false;

// GeoDB erzeugen, dazu StandardBefehl auslˆsen
	if (CWelcomePage::OPENMODE_CreateNew == Welcome.GetOpenMode()) {
		MWind() -> SendMessage (WM_COMMAND, IDM_NEWDB, AskForParams.GetCompatibilityMode());

	// Eintragungen aus Registry in GeoDB wegschreiben
		AskForParams.RegisterEntries();
		AskForCoordSystem.RegisterEntries();
		DEX_KickIdle();	// UI richten

	// evtl. Import anschieben
		if (CCreateNewParamWiz::CREATEMODE_ImportData == AskForParams.GetCreateMode())
			MWind() -> PostMessage (WM_COMMAND, IDM_IMPORT);
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// CreateNewProjectWizard: bei 'Projekt Neu ...' anzeigen
bool CFakeMFCExtension::ShowNewprojectCommand (void)
{
// evtl. geˆffnetes Projekt schlieﬂen
HPROJECT hPr = NULL;	//DEX_GetActiveProjectHandle();

	if (!DEX_CloseProject(hPr))
		return false;		// Projekt wurde nicht geschlossen

// jetzt wirklich neues Projekt erzeugen
CPropertySheet Wiz (g_cbNil, MWind());
CCreateNewWiz AskForCoordSystem(true);
CCreateNewParamWiz AskForParams;

	Wiz.AddPage (&AskForCoordSystem);
	Wiz.AddPage (&AskForParams);
	Wiz.SetWizardMode();
	if (IDCANCEL == Wiz.DoModal())
		return false;

// GeoDB erzeugen, dazu StandardBefehl auslˆsen
	MWind() -> SendMessage (WM_COMMAND, IDM_NEWDB, AskForParams.GetCompatibilityMode());

// Eintragungen aus Registry in GeoDB wegschreiben
	AskForParams.RegisterEntries();
	AskForCoordSystem.RegisterEntries();
	DEX_KickIdle();		// UI richten

// evtl. Import anschieben
	if (CCreateNewParamWiz::CREATEMODE_ImportData == AskForParams.GetCreateMode())
		MWind() -> PostMessage (WM_COMMAND, IDM_IMPORT);
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// DataItem, welches in Tree h‰ngt

CCoordSystemItem::CCoordSystemItem (LPCSTR pcRegKey, LPCSTR pcSubKey)
{
	m_strRegKey = pcRegKey;
	m_strRegKey += g_cbDel;
	m_strRegKey += pcSubKey;

CCurrentUser regKey (pcRegKey);
char cbBuffer[_MAX_PATH];
LONG lLen = sizeof(cbBuffer);

	if (regKey.GetSZ (pcSubKey, cbBuffer, lLen))
		m_strFullDesc = cbBuffer;
}


/////////////////////////////////////////////////////////////////////////////
// CCreateNewWiz property page

IMPLEMENT_DYNCREATE(CCreateNewWiz, CPropertyPage)

CCreateNewWiz::CCreateNewWiz (bool fStandAlone) 
	: CPropertyPage(CCreateNewWiz::IDD)
{
	//{{AFX_DATA_INIT(CCreateNewWiz)
	//}}AFX_DATA_INIT
	m_fStandAlone = fStandAlone;

// Caption den aktuellen Erfordernissen anpassen
	TRY {
	CString strOrgCap;

		VERIFY(strOrgCap.LoadString (IDS_CREATENEWWIZARD));
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// sonstige Funktionen
bool CCreateNewWiz::InitCoordSystemsFromRegistry (void)
{
CCurrentUser regCoords (g_cbCoordSystems);

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

HTREEITEM hItemParent = m_tvCoordSystems.InsertItem (cbBuffer, IMG_FOLDER, IMG_FOLDER, hParent);
DWORD i = 0;
char cbEnumKey[_MAX_PATH];
CRegistry regEntries (rCurr, pcKey);
DWORD dwPos = 0;

	if (!regEntries.GetDWORD (g_cbToolbar32, dwPos)) {
	// Zwischen‹berschrift, weiter in die Rekursion
	bool fNotEmpty = false;

		while (RegEnumKey (regEntries, i, cbEnumKey, _MAX_PATH) == ERROR_SUCCESS) {
			if (InitCoordSystem (regEntries, hItemParent, strFullKey, cbEnumKey))
				fNotEmpty = true;
			i++;
		}
		return fNotEmpty;
	} else {
	// eigentliche Koordinatensysteme
		ASSERT(0 <= dwPos && dwPos <= m_tvCoordSystems.GetImageCount()-1);

		while (RegEnumKey (regEntries, i, cbEnumKey, _MAX_PATH) == ERROR_SUCCESS) {
			InitCoordSystemEntry (regEntries, hItemParent, strFullKey, cbEnumKey, dwPos);
			i++;
		}
	}

return NULL != hItemParent;
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

CPropertySheet *pSheet = (CPropertySheet *)GetParent();
DWORD dwBttns = 0;

	ASSERT(NULL != pSheet);
	ASSERT(!m_fNotEmpty || NULL != hItem);

	if (NULL != hItem) {
	CCoordSystemItem *pItemData = (CCoordSystemItem *)m_tvCoordSystems.GetItemData (hItem);

		if (!m_fStandAlone)
			dwBttns = PSWIZB_BACK;

		if (NULL == pItemData) {
			m_ftDescription.SetWindowText (g_cbNil);
//			dwBttns |= PSWIZB_DISABLEDFINISH;
		} else {
			m_ftDescription.SetWindowText (pItemData -> GetDesc());
			dwBttns |= PSWIZB_NEXT;
		}
	} 
//	else
//		dwBttns = PSWIZB_DISABLEDFINISH;

	pSheet -> SetWizardButtons (dwBttns);
}

/////////////////////////////////////////////////////////////////////////////
// CCreateNewWiz message handlers

LRESULT CCreateNewWiz::OnWizardNext() 
{
// Selektierten Eintrag holen
HTREEITEM hItem = m_tvCoordSystems.GetSelectedItem();

	if (NULL == hItem || m_tvCoordSystems.ItemHasChildren (hItem)) 
		return 0;		// nur Childs behandeln

CCoordSystemItem *pItemData = (CCoordSystemItem *)m_tvCoordSystems.GetItemData (hItem);

	if (NULL == pItemData) return 0;

	m_strSelKey = pItemData -> GetRegKey();
	return CPropertyPage::OnWizardNext();
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

	m_ftDescText.GetWindowText (strTempl);
	str.Format (strTempl, g_cbTRiAS);
	m_ftDescText.SetWindowText (str);
	UpdateData (FALSE);
	return false;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CCreateNewWiz::OnSetActive() 
{
	SetDescription();
	return CPropertyPage::OnSetActive();
}

///////////////////////////////////////////////////////////////////////////////
// Bekannte RegistryKeys
typedef struct tagCOORDSYSKEY {
	TCHAR *m_pKey;
	DWORD m_dwMode;
} COORDSYSKEY;

const COORDSYSKEY g_cbCoordSysKeys[] = {
	{ TEXT("CoordTransform"), HEADER_SYSTEMRO, },
	{ TEXT("CoordMeridian"), HEADER_SYSTEMRO },
	{ TEXT("CoordStrBreite"), HEADER_SYSTEMRO },
	{ TEXT("CoordPrecision"), HEADER_SYSTEM },
	{ TEXT("CoordScaling"), HEADER_SYSTEMRO },
	{ TEXT("ShowGKCoords"), HEADER_SYSTEMRO },
	{ TEXT("CoordMeridianV"), HEADER_SYSTEMRO },
	{ TEXT("OffsetX"), HEADER_SYSTEMRO },
	{ TEXT("OffsetY"), HEADER_SYSTEMRO },
	{ TEXT("Koeff11"), HEADER_SYSTEMRO },
	{ TEXT("Koeff12"), HEADER_SYSTEMRO },
	{ TEXT("Koeff21"), HEADER_SYSTEMRO },
	{ TEXT("Koeff22"), HEADER_SYSTEMRO },
};

#define _countof(array) (sizeof(array)/sizeof(array[0]))

bool CCreateNewWiz::RegisterEntries (void)
{
CCurrentUser regEntry (m_strSelKey);

	for (int i = 0; i < _countof(g_cbCoordSysKeys); i++)
		RegisterEntry (regEntry, g_cbCoordSysKeys[i].m_pKey, g_cbCoordSysKeys[i].m_dwMode);

	DEXN_ReReadHeader();	// an alle: Header neu lesen
	DEXN_ReScale();

return true;
}

bool CCreateNewWiz::RegisterEntry (CRegistry &rCurr, LPCSTR pcDataName, DWORD dwMode)
{
char cbBuffer[_MAX_PATH];
DWORD dwLen = sizeof(cbBuffer);

	if (rCurr.GetSubSZ (pcDataName, cbBuffer, dwLen)) {
	HeaderEntryX HE (pcDataName, cbBuffer, dwMode);
	
		return (EC_OKAY == HE.WriteBack()) ? true : false;	
	}

DWORD dwData = 0;

	if (rCurr.GetDWORD (pcDataName, dwData)) {
		ultoa (dwData, cbBuffer, 10);

	HeaderEntryX HE (pcDataName, cbBuffer, HEADER_SYSTEMRO);

		return (EC_OKAY == HE.WriteBack()) ? true : false;	
	}

return false;
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
		SetItemImage (hItem, IMG_OPENFOLDER, IMG_OPENFOLDER);	// ist expandiert
	else
		SetItemImage (hItem, IMG_FOLDER, IMG_FOLDER);			// ist collabiert
}


