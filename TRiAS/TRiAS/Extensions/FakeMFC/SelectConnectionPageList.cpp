// SelectConnectionPage.cpp : implementation file
//

#include "fakemfcp.hxx"
#include "fakemfc.h"

#include <Registrx.hxx>
#include <toolguid.h>
#include <itoolbar.h>

#include "Strings.h"
#include "FakeMfc.hxx"
#include "OpenNewPropertySheet.h"
#include "SelectConnectionPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// 
#define SHORT_COLUMN	0
#define LONG_COLUMN		1

#define MINCOLWIDTH		10

///////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(CatInformation);
DefineSmartInterface(EnumGUID);
DefineSmartInterface(EnumString);

///////////////////////////////////////////////////////////////////////////////
// ComponentCategory
const CATID CATID_TRiASDBEngine = {0x079639C6,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};

/////////////////////////////////////////////////////////////////////////////
// CSelectConnectionPage property page

IMPLEMENT_DYNCREATE(CSelectConnectionPage, CPropertyPage)

CSelectConnectionPage::CSelectConnectionPage() 
	: CPropertyPage(CSelectConnectionPage::IDD),
	  m_pParams(NULL), m_fNotEmpty(FALSE)
{
	//{{AFX_DATA_INIT(CSelectConnectionPage)
	//}}AFX_DATA_INIT
	m_rgDatasourceMode = DATASOURCEMODE_Unknown;

// Caption den aktuellen Erfordernissen anpassen
	TRY {
	CString strOrgCap;

		VERIFY(strOrgCap.LoadString (IDS_CREATENEWWIZARD));
		m_strCaption.Format (strOrgCap, g_cbTRiAS);
		m_psp.pszTitle = m_strCaption;
		m_psp.dwFlags |= PSP_USETITLE;

	} CATCH (CMemoryException, e) {
		TRACE("Couldn't change caption for CSelectConnectionPage\r\n");
	} END_CATCH;
}

CSelectConnectionPage::~CSelectConnectionPage()
{
}

void CSelectConnectionPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectConnectionPage)
	DDX_Control(pDX, IDC_DESCTEXT, m_ftDescription);
	DDX_Control(pDX, IDC_CONNECTIONS, m_lvConnections);
	DDX_Control(pDX, IDC_CONNECT_DESCRIPTION, m_ftConnection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectConnectionPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSelectConnectionPage)
	ON_NOTIFY(NM_DBLCLK, IDC_CONNECTIONS, OnDblclkConnections)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// sonstige Funktionen
BOOL CSelectConnectionPage::InitDataServersFromRegistry (void)
{
BOOL fNotEmpty = FALSE;

// für alle Fälle alles bisherige löschen
	m_lvConnections.DeleteAllItems();

// DBEngines über CATID enumerieren
	try {
	WEnumGUID EnumGuids;		// Enumerator der DBEngine-Objekte
	WCatInformation CatInfo (CLSID_CatSimpleCache);	// throws hr
	GUID guidImpl[1]; 

		guidImpl[0] = CATID_TRiASDBEngine;
		THROW_FAILED_HRESULT(CatInfo -> EnumClassesOfCategories (1, guidImpl, 0, NULL, EnumGuids.ppi()));

	GUID guid;

		for (EnumGuids -> Reset(); S_OK == EnumGuids -> Next (1, &guid, NULL); /**/)
		{
			if (SUCCEEDED(InitDataServers (guid)))
				fNotEmpty = TRUE;
		}

	} catch (_com_error &) {
		ASSERT(FALSE);
		return FALSE;
	}
	
	return fNotEmpty;
}

HRESULT CSelectConnectionPage::InitDataServers (REFGUID rGuid)
{
LPOLESTR poleStr = NULL;

	USES_CONVERSION;

	m_lCnt = 0L;		// Zähler der Einträge
	try {
	// DBEngine instantiieren und nach EnumString fragen
	WTRiASDBEngine DBEng (rGuid);	// throws hr
	WUnknown Unk;
	WEnumString EnumStr;
	HRESULT hr = S_OK, hr_global = HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	bool fFound = false;

		THROW_FAILED_HRESULT(DBEng -> EnumDataBaseTypes (Unk.ppi()));
		EnumStr = Unk;				// throws hr

		for (EnumStr -> Reset(); S_OK == EnumStr -> Next (1, &poleStr, NULL); /**/)
		{
			hr = InitDataServer(OLE2A(poleStr));		// Fehler führt nicht zum Abbruch
			if (SUCCEEDED(hr))
				fFound = true;
			else
				hr_global = hr;

			CoTaskMemFree (poleStr);
			poleStr = NULL;
		}

	// wenn nicht wenigstens einer gültig ist, dann mit Fehler raus
		if (!fFound) 
			return hr_global;		// liefert den letzten der FehlerCodes

	} catch (_com_error &e) {
		if (poleStr)
			CoTaskMemFree (poleStr);
		return _COM_ERROR(e);
	}

	m_lvConnections.FitColumn();	// Fit all Columns
	return S_OK;
}

HRESULT CSelectConnectionPage::InitDataServer (LPCSTR pcProgID)
{
// Daten an das neue Item dranhängen
CDataServerItem *pNewItem = NULL;

	ATLTRY(pNewItem = new CDataServerItem());
	if (NULL == pNewItem) return E_OUTOFMEMORY;

DWORD dwPos = IMG_GENERAL;
HRESULT hr = TxGetExtension() -> ReadDataServerParams (dwPos, pNewItem, pcProgID);

	if (FAILED(hr)) {
		DELETE_OBJ(pNewItem);
		return hr;
	}

// wenn neu erzeugt werden soll, dann nur writeable DataServer auflisten
	if (DATASOURCEMODE_CreateNew == GetPropSheet() -> GetDatasourceMode() &&
		!pNewItem -> m_fIsReadWrite)
	{
		DELETE_OBJ(pNewItem);
		return S_OK;		// der nächste bitte
	}

// neues Item erzeugen (erste Spalte ist Bildchen plus Typ)
LV_ITEM lvi;

	memset (&lvi, 0, sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM|LVIF_STATE;
	lvi.iItem = m_lCnt++;
	lvi.iSubItem = SHORT_COLUMN;
	lvi.pszText = (LPTSTR)(LPCTSTR)pNewItem -> m_strShortName;
	lvi.iImage = dwPos;
	lvi.lParam = reinterpret_cast<DWORD>(pNewItem);
	lvi.stateMask = LVIS_OVERLAYMASK;
	lvi.state = INDEXTOOVERLAYMASK(0);

int iItem = m_lvConnections.InsertItem (&lvi);

	if (-1 == iItem) return E_OUTOFMEMORY;

// zweite Spalte enthält den Beschreibung
	memset (&lvi, 0, sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT;
	lvi.pszText = (LPTSTR)(LPCTSTR)pNewItem -> m_strFileDesc;
	lvi.iItem = iItem;
	lvi.iSubItem = LONG_COLUMN;
	m_lvConnections.SetItem (&lvi);

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CSelectConnectionPage message handlers

BOOL CSelectConnectionPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_pParams = GetPropSheet() -> GetConnectParams();

// TreeControl/Imagelist initialisieren
	m_lvConnections.InitListCrtl (this);
	
// Datenserver einlesen
	m_fNotEmpty = InitDataServersFromRegistry();
	m_rgDatasourceMode = GetPropSheet() -> GetDatasourceMode();

	SetDescription();
	m_lvConnections.SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectConnectionPage::SetDescription (int iItem)
{
	if (-1 == iItem)
		iItem = m_lvConnections.GetNextItem (-1, LVNI_ALL|LVNI_SELECTED);

CPropertySheet *pSheet = (CPropertySheet *)GetParent();
DWORD dwBttns = PSWIZB_BACK;

	ASSERT(NULL != pSheet);

	if (-1 != iItem) {
	CDataServerItem *pItemData = (CDataServerItem *)m_lvConnections.GetItemData (iItem);

		if (NULL == pItemData) {
			m_ftConnection.SetWindowText (g_cbNil);
		} else {
			m_ftConnection.SetWindowText (pItemData -> GetDesc());
			dwBttns |= PSWIZB_NEXT;
		}
	} 
	pSheet -> SetWizardButtons (dwBttns);
}

LRESULT CSelectConnectionPage::OnWizardNext() 
{
// Selektierten Eintrag holen
int iItem = m_lvConnections.GetNextItem (-1, LVNI_ALL|LVNI_SELECTED);

	if (-1 == iItem) return 0;		// nichts selektiert

CDataServerItem *pItemData = (CDataServerItem *)m_lvConnections.GetItemData (iItem);

	if (NULL == pItemData) return 0;

	ASSERT(NULL != m_pParams);
	*m_pParams = *(CConnectParams *)pItemData;		// Resultate speichern

// beim Neuerzeugen muß DataServer writeable sein
	ASSERT(DATASOURCEMODE_OpenExistend == GetPropSheet() -> GetDatasourceMode() ||
		   m_pParams -> m_fIsReadWrite);
	return CPropertyPage::OnWizardNext();
}

BOOL CSelectConnectionPage::OnSetActive() 
{
	if (m_rgDatasourceMode != GetPropSheet() -> GetDatasourceMode()) {
		m_fNotEmpty = InitDataServersFromRegistry();
		m_rgDatasourceMode = GetPropSheet() -> GetDatasourceMode();
	}

	SetDescription();
	return CPropertyPage::OnSetActive();
}

#if defined(_DEBUG)
BOOL CSelectConnectionPage::OnWizardFinish() 
{
	ASSERT(FALSE);		// darf nicht passieren
	return CPropertyPage::OnWizardFinish();
}
#endif // _DEBUG

void CSelectConnectionPage::OnDblclkConnections(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
int iItem = pNMListView -> iItem;

	if (0 <= iItem) 
	{
	CPropertySheet *pSheet = (CPropertySheet *)GetParent();

		ASSERT(NULL != pSheet);
		pSheet -> PressButton (PSBTN_NEXT);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDataServerList

CDataServerList::CDataServerList()
{
}

CDataServerList::~CDataServerList()
{
}

BEGIN_MESSAGE_MAP(CDataServerList, CListCtrlEx)
	//{{AFX_MSG_MAP(CDataServerList)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_NOTIFY_REFLECT(LVN_DELETEITEM, OnDeleteitem)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDataServerList::InitListCrtl (CSelectConnectionPage *pPage)
{
	m_pPage = pPage;

	ModifyStyle (0L, LVS_SHOWSELALWAYS, 0);
	if (!m_ilImages.Create (IDB_DATASERVER, 16, 16, RGB(255,0,255))) {
		TRACE0("Could not create imagelist for CDataServerList\r\n");
	} else 
		SetImageList(&m_ilImages, LVSIL_SMALL);

	VERIFY(-1 != InsertColumn (SHORT_COLUMN, IDS_SHORTNAMECOLUMN, LVCFMT_LEFT, -1, SHORT_COLUMN));
	VERIFY(-1 != InsertColumn (LONG_COLUMN, IDS_LONGNAMECOLUMN, LVCFMT_LEFT, -1, SHORT_COLUMN));
}

/////////////////////////////////////////////////////////////////////////////
// CDataServerList message handlers

void CDataServerList::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
int iItem = pNMListView -> iItem;

	ASSERT(0 <= iItem);

	if (pNMListView -> uNewState & LVIS_SELECTED) {
		ASSERT(NULL != m_pPage);
		m_pPage -> SetDescription (iItem);
	}
}

void CDataServerList::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult) 
{
NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
CDataServerItem *pOldItem = (CDataServerItem *)pNMListView -> lParam;

	if (NULL != pOldItem)
		delete pOldItem;
	
	*pResult = 0;
}

void CDataServerList::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CListCtrlEx::OnLButtonDown(nFlags, point);

int index = HitTestEx (point, NULL);
	
	if (-1 != index)
	{
		SetItemState (index, LVIS_SELECTED|LVIS_FOCUSED,
					  LVIS_SELECTED | LVIS_FOCUSED);
	}
}
