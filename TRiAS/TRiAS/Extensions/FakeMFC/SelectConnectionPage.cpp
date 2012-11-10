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

#define IMG_FOLDER_CLOSED	8
#define IMG_FOLDER_OPEN		9

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

CSelectConnectionPage::CSelectConnectionPage(UINT uiIDCap) 
	: CPropertyPage(CSelectConnectionPage::IDD),
	  m_pParams(NULL), m_fNotEmpty(FALSE)
{
	//{{AFX_DATA_INIT(CSelectConnectionPage)
	//}}AFX_DATA_INIT
	m_rgDatasourceMode = DATASOURCEMODE_Unknown;

// Caption den aktuellen Erfordernissen anpassen
	TRY {
	CString strOrgCap;

		VERIFY(strOrgCap.LoadString (uiIDCap));
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
	DDX_Control(pDX, IDC_SELECTCONNECTIONTREE, m_lvConnections);
	DDX_Control(pDX, IDC_CONNECT_DESCRIPTION, m_ftConnection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectConnectionPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSelectConnectionPage)
	ON_NOTIFY(NM_DBLCLK, IDC_SELECTCONNECTIONTREE, OnDblclkConnections)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_SELECTCONNECTIONTREE, OnListGetDispInfo)
	ON_NOTIFY(NM_RETURN, IDC_SELECTCONNECTIONTREE, OnListCRPressed)
	ON_WM_DESTROY()
	ON_WM_CANCELMODE()
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
//	WEnumGUID EnumGuids;		// Enumerator der RegisterTRiASExtension-Objekte
//	WCatInformation CatInfo (CLSID_StdComponentCategoriesMgr);	// throws hr
//	GUID guidImpl[1]; 
//
//		guidImpl[0] = CATID_TRiASDBEngine;
//		THROW_FAILED_HRESULT(CatInfo -> EnumClassesOfCategories (1, guidImpl, 0, NULL, EnumGuids.ppi()));

	// gecachte GUID's verwenden
	GUID guid;

		_ASSERTE(CFakeMFCExtension::s_DBEngineGUIDs.IsValid());
		for (CFakeMFCExtension::s_DBEngineGUIDs.Reset(); S_OK == CFakeMFCExtension::s_DBEngineGUIDs.Next (1, &guid, NULL); /**/)
		{
		HRESULT hr = InitDataServers (guid);

			if (SUCCEEDED(hr))
				fNotEmpty = TRUE;
			else if (CLASS_E_NOTLICENSED == hr)
				CFakeMFCExtension::s_DBEngineGUIDs.RemoveActiveItem();
		}
	
	// alles, was nicht (wirklich) gebraucht wird, wieder rauswerfen
		::CoFreeUnusedLibraries();

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
	WTRiASDBEngine DBEng; 
	WUnknown Unk;
	WEnumString EnumStr;
	HRESULT hr = S_OK, hr_global = HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	bool fFound = false;
	
		hr = DBEng.CreateInstance(rGuid);
		if (FAILED(hr)) 
			return hr;		// ggf. nicht instantiierbar (z.B. lizensiert)

	// jede DBEngine ist ein eigener SubBaum
	CComBSTR bstrDesc;

		THROW_FAILED_HRESULT(DBEng -> get_Description (CLEARED(&bstrDesc)));
	
	HTREEITEM hItem = m_lvConnections.InsertItem (OLE2A(bstrDesc), IMG_FOLDER_CLOSED, IMG_FOLDER_CLOSED, TVI_ROOT, TVI_LAST);

		if (NULL == hItem)
			return E_OUTOFMEMORY;

	// jetzt eigentliche Dataserver einfügen
		THROW_FAILED_HRESULT(DBEng -> EnumDataBaseTypes (Unk.ppi()));
		EnumStr = Unk;				// throws hr

		for (EnumStr -> Reset(); S_OK == EnumStr -> Next (1, &poleStr, NULL); /**/)
		{
			hr = InitDataServer(hItem, OLE2A(poleStr));		// Fehler führt nicht zum Abbruch
			if (S_OK == hr)
				fFound = true;
			else
				hr_global = hr;

			CoTaskMemFree (poleStr);
			poleStr = NULL;
		}

	// wenn nicht wenigstens einer gültig ist, dann mit Fehler raus
		if (!fFound) {
			m_lvConnections.DeleteItem (hItem);		// leere Items rausnehmen
			return hr_global;		// liefert den letzten der FehlerCodes
		}

	} catch (_com_error &e) {
		if (poleStr)
			CoTaskMemFree (poleStr);
		return _COM_ERROR(e);
	}

	m_lvConnections.FitColumn();	// Fit all Columns
	return S_OK;
}

HRESULT CSelectConnectionPage::InitDataServer (HTREEITEM hParent, LPCSTR pcProgID)
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
		return S_FALSE;		// der nächste bitte
	}

// wenn Öffnen und Datenquelle im aktuellen Projekt, dann weiter
	if (DATASOURCEMODE_OpenExistend == GetPropSheet() -> GetDatasourceMode() &&
		pNewItem -> m_fNameIsSubStorage)
	{
		DELETE_OBJ(pNewItem);
		return S_FALSE;		// der nächste bitte
	}

// neues Item erzeugen (erste Spalte ist Bildchen plus Typ)
TV_INSERTSTRUCT tvi;

	memset (&tvi, 0, sizeof(TV_INSERTSTRUCT));
	tvi.hParent = hParent;
	tvi.hInsertAfter = TVI_LAST;

	tvi.item.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM|TVIF_STATE;
//	tvi.item.iItem = m_lCnt++;
//	tvi.item.iSubItem = SHORT_COLUMN;
	tvi.item.pszText = (LPTSTR)(LPCTSTR)pNewItem -> m_strShortName;
	tvi.item.iImage = dwPos;
	tvi.item.iSelectedImage = dwPos;
	tvi.item.lParam = reinterpret_cast<DWORD>(pNewItem);
	tvi.item.stateMask = TVIS_OVERLAYMASK;
	tvi.item.state = INDEXTOOVERLAYMASK(0);

HTREEITEM hItem = m_lvConnections.InsertItem (&tvi);

	if (NULL == hItem) return E_OUTOFMEMORY;

// zweite Spalte enthält den Beschreibung
//LV_ITEM lvi;
//
//	memset (&lvi, 0, sizeof(LV_ITEM));
//	lvi.mask = LVIF_TEXT;
//	lvi.pszText = (LPTSTR)(LPCTSTR)pNewItem -> m_strFileDesc;
//	lvi.iItem = m_lCnt++; //m_lvConnections.GetItemIndex (hItem);		// einfach extern mitzählen
//	lvi.iSubItem = LONG_COLUMN;
//	m_lvConnections.InsertItem (&lvi);
	return S_OK;
}

void CSelectConnectionPage::OnListGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
LV_DISPINFO *lvdi = (LV_DISPINFO *)pNMHDR;

	if (lvdi->item.iSubItem == 1)
	{
	HTREEITEM hItem = m_lvConnections.GetItemAt(lvdi->item.iItem);
	CDataServerItem *pItem = (CDataServerItem *)m_lvConnections.GetItemData(hItem);

		if (NULL != pItem)
			_tcsncpy(lvdi->item.pszText, pItem->m_strFileDesc, lvdi->item.cchTextMax);
		else
			_tcsncpy(lvdi->item.pszText, g_cbSpace, lvdi->item.cchTextMax);
		lvdi->item.mask |= LVIF_DI_SETITEM;  // So we're not asked again
	}
	*pResult = 0;
}

void CSelectConnectionPage::OnListCRPressed(NMHDR* pNMHDR, LRESULT* pResult) 
{
int nItem = m_lvConnections.GetFocusIndex();

	if (-1 != nItem) {
	HTREEITEM htiSel = m_lvConnections.GetItemAt(nItem);

		if (NULL != htiSel && NULL == m_lvConnections.GetChildItem (htiSel)) 
		// Enter gedrückt, wenn Leaf selektiert ist: Press Key Next
			GetPropSheet() -> PressButton (PSBTN_NEXT);
	}
	*pResult = 0;
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
	if (m_fNotEmpty) {
	HTREEITEM hFirstItem = m_lvConnections.GetNextItem (NULL, TVGN_CHILD);

		m_lvConnections.ExpandCompletely (TVI_ROOT, TVE_EXPAND);
		m_lvConnections.SetItemState (hFirstItem, TVIS_SELECTED, TVIS_SELECTED);
		m_lvConnections.SetListItemState (hFirstItem, LVIS_FOCUSED, LVIS_FOCUSED);
		m_lvConnections.ResizeColumns();
	}
	m_lvConnections.SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectConnectionPage::SetDescription (HTREEITEM hItem)
{
	if (NULL == hItem)
		hItem = m_lvConnections.GetNextItem (NULL, TVGN_CARET);

CPropertySheet *pSheet = (CPropertySheet *)GetParent();
DWORD dwBttns = PSWIZB_BACK;

	ASSERT(NULL != pSheet);

	if (NULL != hItem) {
	CDataServerItem *pItemData = (CDataServerItem *)m_lvConnections.GetItemData (hItem);

		if (NULL == pItemData) {
			m_ftConnection.SetWindowText (g_cbNil);
		} else {
			m_ftConnection.SetWindowText (pItemData -> GetDesc());
			dwBttns |= PSWIZB_NEXT;
		}
	} 
	pSheet -> SetWizardButtons (dwBttns);
}

LRESULT CSelectConnectionPage::OnWizardBack() 
{
// lediglich evtl. Tooltip ausblenden
	m_lvConnections.HideToolTip();
	return CPropertyPage::OnWizardBack();
}

LRESULT CSelectConnectionPage::OnWizardNext() 
{
// Selektierten Eintrag holen
HTREEITEM hItem = m_lvConnections.GetNextItem (NULL, TVGN_CARET);

	if (NULL == hItem) return 0;		// nichts selektiert

CDataServerItem *pItemData = (CDataServerItem *)m_lvConnections.GetItemData (hItem);

	if (NULL == pItemData) return 0;

	ASSERT(NULL != m_pParams);
	*m_pParams = *pItemData;		// Resultate speichern

// beim Neuerzeugen muß DataServer writeable sein
	ASSERT(DATASOURCEMODE_OpenExistend == GetPropSheet() -> GetDatasourceMode() ||
		   m_pParams -> m_fIsReadWrite);

	m_lvConnections.HideToolTip();
	if (m_pParams -> m_fNameIsFile || m_pParams -> m_fNameIsDir) {
		CPropertyPage::OnWizardNext();	
		SetWindowLong (m_hWnd, DWL_MSGRESULT, IDD_CONNECTION_PARAMS);	// 'normale' Seite anzeigen
//		SetWindowLong (GetParent() -> GetSafeHwnd(), DWL_MSGRESULT, IDD_CONNECTION_PARAMS);
		return IDD_CONNECTION_PARAMS;
	}

	CPropertyPage::OnWizardNext();
	SetWindowLong (m_hWnd, DWL_MSGRESULT, IDD_CONNECTION_PARAMS_DBMS);	// DBMS-Seite anzeigen
//	SetWindowLong (GetParent() -> GetSafeHwnd(), DWL_MSGRESULT, IDD_CONNECTION_PARAMS_DBMS);
	return IDD_CONNECTION_PARAMS_DBMS;
}

BOOL CSelectConnectionPage::OnSetActive() 
{
	if (m_rgDatasourceMode != GetPropSheet() -> GetDatasourceMode()) {
		m_fNotEmpty = InitDataServersFromRegistry();
		m_rgDatasourceMode = GetPropSheet() -> GetDatasourceMode();

		if (m_fNotEmpty) {
		HTREEITEM hFirstItem = m_lvConnections.GetNextItem (NULL, TVGN_CHILD);

			m_lvConnections.Expand (hFirstItem, TVE_EXPAND);
			m_lvConnections.SetItemState (hFirstItem, TVIS_SELECTED, TVIS_SELECTED);
			m_lvConnections.SetListItemState (hFirstItem, LVIS_FOCUSED, LVIS_FOCUSED);
			m_lvConnections.ResizeColumns();
		}
	}
	SetDescription();
	m_lvConnections.SetFocus();
	return CPropertyPage::OnSetActive();
}

void CSelectConnectionPage::OnDestroy() 
{
	DlgClosed();
	CPropertyPage::OnDestroy();
}

void CSelectConnectionPage::DlgClosed()
{
	m_lvConnections.SetDeleting();
	m_lvConnections.DeleteAllItems();
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

// weiterschalten, wenn Doppelklick auf Subitem
HTREEITEM hItem = m_lvConnections.GetSelectedItem();

	if (NULL != hItem && NULL == m_lvConnections.GetChildItem (hItem)) {
	CPropertySheet *pSheet = (CPropertySheet *)GetParent();

		ASSERT(NULL != pSheet);
		pSheet -> PressButton (PSBTN_NEXT);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDataServerList

CDataServerList::CDataServerList()
{
	m_fIsDeleting = false;
}

CDataServerList::~CDataServerList()
{
}

BEGIN_MESSAGE_MAP(CDataServerList, CSECTreeCtrlEx)
	//{{AFX_MSG_MAP(CDataServerList)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemExpanded)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelChanged)
	ON_NOTIFY_REFLECT(TVN_DELETEITEM, OnDeleteitem)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDataServerList::InitListCrtl (CSelectConnectionPage *pPage)
{
	m_pPage = pPage;
	m_cyHeader = 16;		// HeaderControl ist nur 16 Pixel hoch

	SubclassTreeCtrlId (IDC_SELECTCONNECTIONTREE, pPage);
	EnableHeaderCtrl (TRUE);
	ModifyListCtrlStyles (0, LVS_NOSORTHEADER, 0, LVXS_HILIGHTSUBITEMS);

CBitmap bmpIcons;
CBitmap bmpMask;

	if (!bmpIcons.LoadBitmap(IDB_DATASERVER) || !bmpMask.LoadBitmap(IDB_DATASERVERMASK)) 
		TRACE0("Could not load bitmaps for CDataServerList\r\n");
	else {
		if (!m_ilImages.Create(16, 16, ILC_COLOR|ILC_MASK, 20, 0) ||
			-1 ==  m_ilImages.Add(&bmpIcons, &bmpMask)) 
		{
			TRACE0("Could not create imagelist for CDataServerList\r\n");
		} else 
			SetImageList(&m_ilImages, TVSIL_NORMAL);
	}

CString str;

	VERIFY(str.LoadString(IDS_SHORTNAMECOLUMN));
	SetColumnHeading (SHORT_COLUMN, str);
	VERIFY(-1 != InsertColumn (LONG_COLUMN, IDS_LONGNAMECOLUMN, LVCFMT_LEFT, -1, LONG_COLUMN));
}

/////////////////////////////////////////////////////////////////////////////
// CDataServerList message handlers

void CDataServerList::OnItemExpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

NM_TREEVIEW *pNMTreeView = (NM_TREEVIEW *)pNMHDR;
HTREEITEM hItem = pNMTreeView -> itemNew.hItem;

	if (NULL == GetParentItem (hItem)) {		// NULL == TVI_ROOT
		if (pNMTreeView -> itemNew.state & TVIS_EXPANDED)
			SetItemImage (hItem, IMG_FOLDER_OPEN, IMG_FOLDER_OPEN);
		else
			SetItemImage (hItem, IMG_FOLDER_CLOSED, IMG_FOLDER_CLOSED);
	}
}

void CDataServerList::OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

NM_TREEVIEW *pNMTreeView = (NM_TREEVIEW *)pNMHDR;

	if (pNMTreeView -> itemNew.state & TVIS_SELECTED) {
		ASSERT(NULL != m_pPage);
		m_pPage -> SetDescription (pNMTreeView -> itemNew.hItem);
	}
}

void CDataServerList::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	if (!m_fIsDeleting) return;

NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW *)pNMHDR;
HTREEITEM hItem = pNMTreeView -> itemOld.hItem;
CDataServerItem *pOldItem = (CDataServerItem *)GetItemData (hItem);

	if (NULL != pOldItem) {
		delete pOldItem;
		SetItemData (hItem, NULL);
	}
}

void CDataServerList::ResizeColumns()
{
CRect rc;

	GetWindowRect (&rc);
	SetColumnWidth (SHORT_COLUMN, (rc.right-rc.left)/2);
	SetColumnWidth (LONG_COLUMN, (rc.right-rc.left)/2 +3);

	ResizeColumnsToFit();
	ReMeasureAllItems();
	Invalidate();
}

void CDataServerList::HideToolTip()
{
	if (NULL != m_pToolTipWnd)
		m_pToolTipWnd->Hide();
}

