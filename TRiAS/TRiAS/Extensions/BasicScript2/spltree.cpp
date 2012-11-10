/////////////////////////////////////////////////////////////////////////////
// spltree.cpp : implementation file
//

#include "bscriptp.hxx"
#include "bscript.h"

#include <new>
#include <iobjman.h>
#include "macrguid.h"

#include "conststr.h"
#include "iscrprop.h"
#include "toolbarx.h"
#include "relscrpt.h"
#include "DebCtrl.h"
#include "spltree.h"
#include "splitter.h"
#include "split.h"
#include "projscr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define AFX_WNDCOMMCTLS_REG     (0x0010)
#define AfxDeferRegisterClass(fClass) \
	((afxRegisteredClasses & fClass) ? TRUE : AfxEndDeferRegisterClass(fClass))

#define OS_NO_STREAM_SUPPORT

#define MAX_MACRO_CNT 200

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100

DefineEnumerator2(os_wstring, IID_IEnumos_wstring);
DefineSmartEnumerator2(os_wstring, IID_IEnumos_wstring);

////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(StreamInfo);
DefineSmartInterface(TreeItem);
DefineSmartInterface(ObjManHelper);
DefineSmartInterface(Persist);
DefineSmartInterface(BSProperty);

/////////////////////////////////////////////////////////////////////////////
// globale Funktionsdeklarationen
BOOL	LoadString(CString & str, int IDS);
CString		GetDefaultName(int IDS);
HRESULT FileName(LPCSTR pPathName, LPSTR pNameToUse);
BOOL GetStringTypeFromWType(ebWORD wType, LPSTR lpstr, UINT uiLen);
BOOL ModifyName(LPSTR lpstr);
BOOL FindFirstDefaultString(IObjectManagement *pIObjMan, LPSTR lpstrDef);
CString GetFileName (CString &rPath, BOOL fExt);
extern BOOL AFXAPI AfxEndDeferRegisterClass(short fClass);

/////////////////////////////////////////////////////////////////////////////
// CRelMacroTreeBox

IMPLEMENT_DYNCREATE ( CRelMacroTreeBox, CTreeCtrl )

CRelMacroTreeBox::CRelMacroTreeBox()
{
	m_htreeCurrentMacroRoot = NULL;
	m_pMainFrame = NULL;
	m_hAccel = NULL;
	m_pImageList = NULL;
	m_fNotExpand = false;
	m_fTreeMenu = false;
}

CRelMacroTreeBox::~CRelMacroTreeBox()
{
}


BEGIN_MESSAGE_MAP(CRelMacroTreeBox, CTreeCtrl)
	//{{AFX_MSG_MAP(CRelMacroTreeBox)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, OnBeginlabeledit)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(TVN_DELETEITEM, OnDeleteitem)
	ON_COMMAND(ID_DEBUG_OPEN, OnOpen)
	ON_COMMAND(ID_DEBUG_SAVE, OnSave)
	ON_COMMAND(ID_DEBUG_REMOVE, OnRemove)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpanded)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_COMMAND(ID_DEBUG_IMPORT, OnImport)
	ON_COMMAND(ID_DEBUG_NEWFILE, OnNew)
	ON_COMMAND(ID_DEBUG_SAVEAS, OnSaveas)
	ON_WM_RBUTTONDOWN()
	ON_UPDATE_COMMAND_UI(ID_DEBUG_IMPORT, OnUpdateDebugImport)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_SAVE, OnUpdateDebugSave)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_SAVEAS, OnUpdateDebugSaveas)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_OPEN, OnUpdateDebugOpen)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_NEWFILE, OnUpdateDebugNewfile)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_REMOVE, OnUpdateDebugRemove)
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(ID_DEBUG_INSERT, OnInsert)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_INSERT, OnUpdateDebugInsert)
	ON_COMMAND(ID_DEBUG_CLOSEIMAGE, CloseFoldersImage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrl message handlers

// Need this because this class is tagged DYNCREATE
void CRelMacroTreeBox::PostNcDestroy() 
{
//	delete this;
}

void CRelMacroTreeBox::OnDestroy() 
{
	DeleteAll();
	DeleteAllItems();

	if (m_pImageList && m_pImageList -> DeleteImageList())
	{
		delete m_pImageList; m_pImageList = NULL;
	}

	CTreeCtrl::OnDestroy();
}

void CRelMacroTreeBox::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	CTreeCtrl::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	// Vom Mainframe als Verschicker rufen	
	GetMainFrame() -> OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	SetRBTreeMenu(false);
}

///////////////////////////////////////////////////////////
// Inits
HRESULT CRelMacroTreeBox::InitFirstScript(LPCSTR lpcstrScriptName)
{
	HRESULT hr = S_OK;
	HTREEITEM hItem = NULL;
	// Erst nach Initialisierung des Trees anwenden !
	if (lpcstrScriptName)  
	{// ScriptName wurde explizit übergeben
		hItem = IsItemAllreadyInsert(m_htreeCurrentMacroRoot, lpcstrScriptName);
		if (hItem)
		{		// Item gefunden
			Expand(GetParentItem(hItem), TVE_EXPAND);
			SelectItem(hItem);
		}
		else
		{	// nicht gefunden, NEUES kreieren
			hr = InsertInitItem(m_htreeCurrentMacroRoot, lpcstrScriptName);
		}
	}
	else
	{// Da ItemName nicht vorhanden, "Default" initialisieren
		if (!InitGeneralTree())
		// leerer Baum !!!
			hr = S_FALSE;
	}
	if (S_OK == hr) 
		SetFocus();
	return hr;
}


HRESULT CRelMacroTreeBox::Init(CSplit *pMainFrame)
{
	ASSERT(pMainFrame);
	if (NULL == pMainFrame) return E_POINTER;
	m_pMainFrame = pMainFrame;

	try
	{
		if (!GetAccelerator()) _com_issue_error (E_HANDLE);

		if (m_pImageList && m_pImageList -> DeleteImageList())
		{
			DELETE_OBJ(m_pImageList);
		}
		m_pImageList = new CImageList();
		if (NULL == m_pImageList) _com_issue_error (E_POINTER);

		if (!m_pImageList -> Create(IDR_TREEIMAGES, 16, 0, RGB(128, 0, 128)))
			_com_issue_error (E_FAIL); 

		SetImageList(m_pImageList, TVSIL_NORMAL);
		EnableWindow(false);
	}
	catch(_com_error& e)
	{
		DELETE_OBJ(m_pImageList);
		return _COM_ERROR(e);
	}
	catch (bad_alloc) 
	{
		DELETE_OBJ(m_pImageList);
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

BOOL CRelMacroTreeBox::GetAccelerator()
{
	ASSERT(g_hInstance);
	// free automaticly
	m_hAccel = LoadAccelerators(g_hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR_TREECTRL));
	ASSERT(NULL != m_hAccel);
	if (NULL != m_hAccel) return true;

	return false;
}

BOOL CRelMacroTreeBox::PreTranslateMessage(MSG* pMsg) 
{
	ASSERT(m_hAccel);

	if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		// finally, translate the message
		if (NULL != m_hAccel && ::TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
			return true;
	}
	return CTreeCtrl::PreTranslateMessage(pMsg);
}

void CRelMacroTreeBox::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	WTreeItem IT;
	HTREEITEM hItem = pNMTreeView -> itemNew.hItem;

	if (hItem && SUCCEEDED(GetProjectScript(hItem, IT.ppi())))
	{
		GetMainFrame() -> SetSelectedItem(IT);
		// Damit öffnen immer erlaubt ist für FunktionItems
		*pResult = 0;
		return;
	}

	*pResult = 1;
}

void CRelMacroTreeBox::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	HTREEITEM hItem = pNMTreeView -> itemNew.hItem;

	*pResult = 0;

	if (NULL == hItem || !AdjustImage (hItem))
	{
		*pResult = 1;
		return;
	}

	if (S_OK == IsScriptLevel(hItem) && m_fNotExpand)
		*pResult = 1; // nicht expandieren

	if ( ! ( GetItemState (hItem, TVIS_EXPANDED) & TVIS_EXPANDED ) ) // ist gerade zuammengezogen
	{// Nur beim Expandieren notwendig
		if (FAILED(EnumFunctions(hItem))/* || !SortChildren(hItem)*/)// Nach Anfangsbuchstaben sortieren
			*pResult = 1;
	}

	m_fNotExpand = false;
}	

void CRelMacroTreeBox::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	HTREEITEM hItem = pNMTreeView -> itemNew.hItem;
	UINT uiAction = pNMTreeView -> action;

	*pResult = 1;
	
	if (NULL != hItem && AdjustImage (hItem))
	{
		BOOL f = true;
		if (S_OK == IsScriptLevel (hItem)) f = SortChildren(hItem);			
		if (f) *pResult = 0;
	}		
}


void CRelMacroTreeBox::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult) 
{	
NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
WTreeItem IT;
HTREEITEM hItem = pNMTreeView -> itemOld.hItem;
	
	ASSERT(NULL != hItem);
	try
	{
		THROW_FAILED_HRESULT(GetProjectScript(hItem, IT.ppi()));

	// Closeimage einstellen
		PostMessage(WM_COMMAND, ID_DEBUG_CLOSEIMAGE);

	// Alle Funktionen löschen
		THROW_FAILED_HRESULT(DeleteFunctionItems(hItem));

	// Löschen des Items an sich
	WObjManHelper IOMH = IT;

		THROW_FAILED_HRESULT(IOMH -> Delete());

	// Diesmal übernimmt die Speicherung der Tree, da Parent gespeichert wewrden muss, 
	// der nicht in CSplit (MainFrame) bekannt ist
		if (S_OK == IsScriptLevel(hItem)) 
			OnDebugSaveRelated(hItem, GetItemText(hItem)); 		
	}
	catch(_com_error& e)
	{
		if (FAILED(_COM_ERROR(e)))
			*pResult = 1;
	}
	*pResult = 0;
}

void CRelMacroTreeBox::OnRButtonDown(UINT nFlags, CPoint point) 
{
	RightButtonDown(point);	
	CTreeCtrl::OnRButtonDown(nFlags, point);
}

void CRelMacroTreeBox::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	*pResult = 0;
	// Nach Doppelklick ist jeweiliges Item selektiert
	if (S_OK == IsScriptLevel(GetSelectedItem())) m_fNotExpand = true;
	OnOpen();
}

void CRelMacroTreeBox::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;

	if (OnOpenBeginLabelEdit(pTVDispInfo))
		*pResult = 0;
	else
		*pResult = 1;
}

BOOL CRelMacroTreeBox::OnOpenBeginLabelEdit(TV_DISPINFO* pTVDispInfo)
{
	HTREEITEM hItem = pTVDispInfo -> item.hItem;
	LPSTR lpstrText = pTVDispInfo -> item.pszText;
	HRESULT hr = NOERROR;

	if (NULL == hItem) return false;

	WTreeItem IT;
	hr = GetProjectScript(hItem, IT.ppi());
	if (FAILED(hr)) return false;

	if (NULL != lpstrText && (IT -> CanLabelEdit() || IT -> IsJustInsert()))
	{// Labeleditzustand merken
		IT -> SetLabelEdit(true);	// Soll gerade editiert werden
		return true;
	}	
	return false;
}

void CRelMacroTreeBox::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;

	if (SUCCEEDED(OnOpenEndLabelEdit(pTVDispInfo)))
	{
		*pResult = 0;
	}
	else
		*pResult = 1;
}

HRESULT CRelMacroTreeBox::GetProjectScript(HTREEITEM hItem, ITreeItem **ppIT)
{
	*ppIT = (ITreeItem *) GetItemData(hItem);

	if (*ppIT)
	{
		(*ppIT) -> AddRef();
		return NOERROR;
	}

	return E_FAIL;
}

HRESULT CRelMacroTreeBox::GetObjFeatScripts(IObjectManagement **ppIObj)
{
	return GetMainFrame() -> GetObjFeatScripts(ppIObj);
}
HRESULT CRelMacroTreeBox::GetInfoObjFeatScripts(IStreamInfo **ppISI)
{
	return GetMainFrame() -> GetInfoObjFeatScripts(ppISI);
}
HRESULT CRelMacroTreeBox::GetGeneralScripts(IObjectManagement **ppIObj)
{
	return GetMainFrame() -> GetGeneralScripts(ppIObj);
}
HRESULT CRelMacroTreeBox::GetInfoGeneralScripts(IStreamInfo **ppISI)
{
	return GetMainFrame() -> GetInfoGeneralScripts(ppISI);
}
HRESULT CRelMacroTreeBox::GetFilterScripts(IObjectManagement **ppIObj)
{
	return GetMainFrame() -> GetFilterScripts(ppIObj);
}
HRESULT CRelMacroTreeBox::GetInfoFilterScripts(IStreamInfo **ppISI)
{
	return GetMainFrame() -> GetInfoFilterScripts(ppISI);
}

/////////////////////////////////////////////////////////////////////////////
// Speicheroperationen
/////////////////////////////////////////////////////////////////////////////
// Neues File EINFÜGEN
BOOL CRelMacroTreeBox::OnDebugInsert() 
{
	HTREEITEM hItem = GetSelectedItem();
	if (NULL == hItem) return false;
	// Ein Projekt selektiert
	return FindRightInsertItem(hItem, m_htreeCurrentMacroRoot);
}
/////////////////////////////////////////////////////////////////////////////
// Neues File EINFÜGEN, aus externer Datei als Verknüpfung laden
BOOL CRelMacroTreeBox::OnDebugImport(LPCSTR lpcstrFileName) 
{
	return ImportFile(lpcstrFileName);
}
/////////////////////////////////////////////////////////////////////////////
// Neues File EINFÜGEN, aus externer Datei laden
BOOL CRelMacroTreeBox::OnDebugImportInProject(LPCSTR lpcstrFileName) 
{
	return Import(lpcstrFileName);
}

BOOL CRelMacroTreeBox::Import (LPCSTR lpcstrFileName)
{	
	HTREEITEM hItem = GetSelectedItem();
	if (NULL == hItem) return false;
	if (InsertFileOnImport(CLSID_Script, lpcstrFileName, false, hItem))
		return true;
	return false;
}
/////////////////////////////////////////////////////////////////////////////
// Neues File EINFÜGEN, aus externer Datei ganzes Projekt ladenladen
BOOL CRelMacroTreeBox::OnDebugImportAllInProject(LPCSTR lpcstrFileName) 
{
	return ImportAll(lpcstrFileName);
}

BOOL CRelMacroTreeBox::ImportAll (LPCSTR lpcstrFileName)
{	
	if (InsertFileOnImport(CLSID_Script, lpcstrFileName, false, m_htreeCurrentMacroRoot))
		return true;
	return false;
}
BOOL CRelMacroTreeBox::ImportFile (LPCSTR lpcstrFileName)
{	
	HTREEITEM hItem = GetSelectedItem();
	if (NULL == hItem) return false;

	if (InsertFileOnImport(CLSID_FileScript, lpcstrFileName, false, hItem))
		return true;
	return false;
}
/////////////////////////////////////////////////////////////////////////////
// anderes ÖFFNEN
BOOL CRelMacroTreeBox::OnDebugOpen(BOOL fSet) 
{
	m_htreeLoadedItem = NULL;

	if (false == fSet) return true; // extern
	if (NULL == GetSelectedItem()) return false;	

	m_htreeLoadedItem = GetSelectedItem();

	// Parent Opened-Image einstellen
	// Nach IMPORT, OPEN
	OpenFoldersImage(m_htreeLoadedItem);

	return true;
}

/////////////////////////////////////////////////////////////////////////////
// SPEICHERN Related
HRESULT CRelMacroTreeBox::OnDebugSaveRelated(HTREEITEM hItem, LPCSTR lpcstrDeleted) 
{
	HRESULT hr = NOERROR;

	LPSTR *lplpstr = NULL;
	UINT uiCnt = 0;
	try
	{// hier selbst vom Tree übernehmen, weiss, wer Parent (Siehe Delete hier und Import in Split)
		if (NULL == hItem) {// kommt aus Import, Importiertes ist nach Import Geladenes
			hItem = GetLoadedItem();// oder kommt aus OnDeleteItem, Item != NULL
		}
		// z.B. externes Script			// Related auf sich selbst soeichern QUATSCH
		if (NULL == hItem || S_OK == IsSuperItem(hItem)) _com_issue_error(S_FALSE);

		WTreeItem IT;
		HTREEITEM hSuper = GetSuperItem (hItem, IT.ppi()); 
		if (NULL == hSuper) _com_issue_error(S_FALSE);
		// Anzahl der Items enumerieren
		uiCnt = GetCountSuperItem(hSuper, lpcstrDeleted);
		// oberstes MacroScript
		if (uiCnt) 
		{
			lplpstr = (LPSTR *)CoTaskMemAlloc(uiCnt*sizeof(LPSTR));
			if (NULL == lplpstr) _com_issue_error(E_OUTOFMEMORY); 
			GetStringListItems(hSuper, lplpstr, uiCnt, lpcstrDeleted);
		}
		// Wenn uiCnt, dann Save
		WObjManHelper IOMH = IT; // Query...
		hr = IOMH -> Save(NULL, NULL, lplpstr, uiCnt, CC_RELATEDSCRIPTS);
		if (FAILED(hr)) _com_issue_error(hr);
	}
	catch (_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	MEMFREE(lplpstr, uiCnt);
	return hr;
}
/////////////////////////////////////////////////////////////////////////////
// SPEICHERN unter
BOOL CRelMacroTreeBox::OnDebugSaveAs(LPSTR **lplplpstr, UINT & uiCnt) 
{
	// NULL: Extenes Script !!!
	if (NULL == GetLoadedItem()) return true;
	uiCnt = GetCountSuperItem(GetLoadedItem());
	if (0 == uiCnt) return true;
	// oberstes MacroScript
	(*lplplpstr) = (LPSTR *)CoTaskMemAlloc(uiCnt*sizeof(LPSTR));
	if (NULL == *lplplpstr) return false;
		
	if (GetStringListItems(GetLoadedItem(), *lplplpstr, uiCnt)) return true;

	MEMFREE(*lplplpstr, uiCnt);
	return false;
}
/////////////////////////////////////////////////////////////////////////////
// SPEICHERN
BOOL CRelMacroTreeBox::OnDebugSave(LPSTR **lplplpstr, UINT & uiCnt) 
{
	return OnDebugSaveAs(lplplpstr, uiCnt);
}
/////////////////////////////////////////////////////////////////////////////
// LÖSCHEN Selectiertes
BOOL CRelMacroTreeBox::OnDebugRemoveSelected() 
{
	if (!DeleteSuperItem(GetSelectedItem(), false))
		return DeleteSubItem(GetSelectedItem());
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// LÖSCHEN Geladenes
BOOL CRelMacroTreeBox::OnDebugRemoveLoaded() 
{
	if (!DeleteSuperItem(GetLoadedItem(), true))
		return DeleteSubItem(GetLoadedItem());
	return true;
}
//////////////////////////////////////////////////////////////////////////////
// Löschen eines NEUEN
BOOL CRelMacroTreeBox::OnDebugDeleteLoaded() 
{
	HTREEITEM hItem = GetLoadedItem();
	if (NULL == hItem) return false; // EXTERNE Datei

	// Wenn gerade FunktionScript geladen, muss der Parent gelöscht werden
	if (S_OK == IsFunctionLevel(hItem))
		hItem = GetParentItem(hItem);

	if (!DeleteSuperItem(hItem, false)) /* Is from menu*/
		return DeleteSubItem(hItem);
	// Ist schließlich gelöscht
	m_htreeLoadedItem = NULL;
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// Go-Operationen
HRESULT CRelMacroTreeBox::OnDebugGo()
{
	// extern ???, dann nicht in Tree
	if (NULL == m_htreeLoadedItem) return S_OK;
	
	try
	{
		HRESULT hr = IsSuperItem(m_htreeLoadedItem); 
		if (S_FALSE != hr) _com_issue_error(hr);// S_OK, dann Superitem schon geladen oder FAILED
		WTreeItem IT;
		HTREEITEM hSuper = GetSuperItem (NULL, IT.ppi()); 
		if (NULL == hSuper) _com_issue_error(E_HANDLE);
		// Damit dieser geöffnet werden kann
		SetFocus();
		SelectItem(hSuper);
	}
	catch (_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// EndLabelEdit ÖFFNEN
HRESULT CRelMacroTreeBox::OnOpenEndLabelEdit(TV_DISPINFO* pTVDispInfo)
{
	HRESULT hr = NOERROR;
	try
	{
		HTREEITEM hEditItem = pTVDispInfo -> item.hItem;
		if (NULL == hEditItem) _com_issue_error(E_HANDLE); 		
		WTreeItem IT;
		hr = GetProjectScript(hEditItem, IT.ppi());	
		if (FAILED(hr)) _com_issue_error(hr);
		
		LPSTR lpstr = pTVDispInfo -> item.pszText;
		// Name nicht geändert
		if (NULL == lpstr) 
		{
			char str[_MAX_PATH];
			WBSProperty IBSP = IT; // Query...
			IBSP -> GetScriptName(str, _MAX_PATH);
			lpstr = str;
		}
		// Stream darf keine Leerzeichen enthalten und nicht länger als 32 Byte sein, Am Anfang Großbuchstaben
		ModifyName(lpstr);
		// gerade neuer Key: Einfügen, Gibt eigefügtes Item zurück
		HTREEITEM hInsertItem = NULL;
		// S_FALSE == JustInsert
		if (false == IT -> IsJustInsert()) // Schon im Baum: Umbenennen
			hr = RenameItemEndLabelEdit(hEditItem, lpstr, &hInsertItem);
		else // Neuen eventuell einfügen
			hr = InsertItemEndLabelEdit(hEditItem, lpstr, &hInsertItem);
		// Flags zurück
		IT -> SetLabelEdit(false);
		IT -> SetJustInsert(false);	// Key darf danach nicht mehr editiert werden	

		if (FAILED(hr)) _com_issue_error(hr);
		
		SetFocus();	// Damit Selektiertes geöffnet wird.		
		OnOpen();	// Öffnen		
		hr = OnDebugSaveRelated(hInsertItem, NULL); // Related gleich abspeichern
		if (FAILED(hr)) _com_issue_error(hr);
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}		
	return hr;
}

/////////////////////////////////////////////////////////////////////////
// Allgemeines

// Bildchen richten 
void CRelMacroTreeBox::CloseFoldersImage()
{
	if (NULL == m_htreeCurrentMacroRoot) return;
	if ( ! ItemHasChildren(m_htreeCurrentMacroRoot) )
	{
		SetItemImage (m_htreeCurrentMacroRoot, IMAGE_CLOSEMACROS, IMAGE_CLOSEMACROS);	// collabiert
	}
}
void CRelMacroTreeBox::OpenFoldersImage(HTREEITEM hChild)
{
	if (NULL == hChild || NULL == GetParentItem(hChild)) return;

	// Folder öffnen, wenn ein Item eingefügt wird
	if (S_OK == IsFirstLevel(GetParentItem(hChild)))
	{
		SetItemImage (GetParentItem(hChild), IMAGE_OPENMACROS, IMAGE_OPENMACROS);	// ist expandiert
	}

	if (NULL == GetParentItem(GetParentItem(hChild))) return;

	if (S_OK == IsFirstLevel(GetParentItem(GetParentItem(hChild))))
	{
		SetItemImage (GetParentItem(GetParentItem(hChild)), IMAGE_OPENMACROS, IMAGE_OPENMACROS);	// ist expandiert
	}
}

BOOL CRelMacroTreeBox::AdjustImage (HTREEITEM hItem)
{
	if (!(S_OK == IsFirstLevel(hItem))) {
		return true;
	}
	
	if (ItemHasChildren(hItem) && GetItemState (hItem, TVIS_EXPANDED) & TVIS_EXPANDED) 
		SetItemImage (hItem, IMAGE_OPENMACROS, IMAGE_OPENMACROS);	// ist expandiert
	else
		SetItemImage (hItem, IMAGE_CLOSEMACROS, IMAGE_CLOSEMACROS);	// ist collabiert

	return true;
}

HRESULT CRelMacroTreeBox::IsFirstLevel(HTREEITEM hItem)
{
// Root
	// Filter == m_htreeFilterMacros
		//	Keys
			// Scripts == hParent
				//	Functions
	ASSERT(hItem);	
	HRESULT hr = NOERROR;
	try
	{
		WTreeItem IT;
		THROW_FAILED_HRESULT(GetProjectScript(hItem, IT.ppi()));
		hr = IT -> IsFirstLevel();
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	return hr;
}
HRESULT CRelMacroTreeBox::IsKeyLevel(HTREEITEM hItem)
{
	ASSERT(hItem);
	HRESULT hr = NOERROR;
	try
	{
		WTreeItem IT;
		THROW_FAILED_HRESULT(GetProjectScript(hItem, IT.ppi()));

		hr = IT -> IsKeyLevel();
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	
	return hr;
}
HRESULT CRelMacroTreeBox::IsScriptLevel(HTREEITEM hItem)
{
	ASSERT(hItem);	
	HRESULT hr = NOERROR;
	try
	{
		WTreeItem IT;
		THROW_FAILED_HRESULT(GetProjectScript(hItem, IT.ppi()));

		hr = IT -> IsScriptLevel();
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	return hr;
}
HRESULT CRelMacroTreeBox::IsFunctionLevel(HTREEITEM hItem)
{
	ASSERT(hItem);
	HRESULT hr = NOERROR;
	try
	{
		WTreeItem IT;
		THROW_FAILED_HRESULT(GetProjectScript(hItem, IT.ppi()));

		hr = IT -> IsFunctionLevel();
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	return hr;
}

BOOL CRelMacroTreeBox::InitGeneralTree() 
{
	// FÄLLE für Beginn:
	if (NULL == GetChildItem(m_htreeCurrentMacroRoot))
	{// wenn noch kein Macro vorhanden
		if (InsertDefaultItem(m_htreeCurrentMacroRoot))
			return false;
	}
	else 
	{// wenn ein ProjectMacro vorhanden, erstes selectieren
		if (InitItem(m_htreeCurrentMacroRoot))
			return true;
	}
	return false;
}

HRESULT CRelMacroTreeBox::IsSuperItem(HTREEITEM hItem)	
{
	HRESULT hr = NOERROR;
	try
	{
		WTreeItem IT;
		hr = GetProjectScript(hItem, IT.ppi());
		if (FAILED(hr)) _com_issue_error(hr); 
	
		if (IT -> IsSuperItem())
			hr =  S_OK;
		else
			hr =  S_FALSE;
	}
	catch (_com_error& e)
	{	
		hr = _COM_ERROR(e);
	}	
	return hr;
}

BOOL CRelMacroTreeBox::DeleteSuperItem(HTREEITEM hItem, BOOL fIsFromMenu) 
{// externes File
	if (NULL == hItem) return false;
	// RootKeys
	if (!(S_OK == IsFirstLevel(hItem)))
	{// ProjectEintrag
		if (!(S_OK == IsKeyLevel(hItem)))
		{// allein in dieser Projektliste
			if (NULL == GetNextSiblingItem(hItem) && NULL == GetPrevSiblingItem(hItem))
			{// Superitem ohne Schwesteritems
				DeleteItemWithParent(hItem);
				// bei Reaktion auf MenuCommand "Entfernen" eventuell Neues initialisieren
				if (fIsFromMenu)
					InitGeneralTree();
				return true;
			}
		}
	}
	return false;
}

BOOL CRelMacroTreeBox::DeleteSubItem(HTREEITEM hItem) 
{// externes File
	if (NULL == hItem) return false;
	// RootKey
	if (!(S_OK == IsFirstLevel(hItem)))
	{// ProjectEintrag
		if (!(S_OK == IsKeyLevel(hItem)))
		{// SuperItem darf nicht Subitems besitzen
			if (NULL != GetPrevSiblingItem(hItem) || NULL == GetNextSiblingItem(hItem))
			{
				if (DeleteItem(hItem))	
					return true;
			}
		}
	}
	return false;
}

HRESULT CRelMacroTreeBox::ResetIfOnClose(void) 
{ 
	try
	{	// Objekte freigeben
		HRESULT hr = DeleteAll();
		if (FAILED(hr)) _com_issue_error(hr);
		// Items löschen
		if (!DeleteAllItems()) _com_issue_error(E_FAIL);
		// Dummy-Item setzen
		int iImage = IMAGE_CLOSEMACROS;
		CString str = GetDefaultName(IDS_NOPROJECTITEMS);
		if (NULL == InsertKey(str, iImage, NULL)) _com_issue_error(E_HANDLE);
		EnableWindow(false);
	}
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT CRelMacroTreeBox::DeleteAll()
{
	DeleteAllObjects(GetRootItem());
	m_htreeCurrentMacroRoot = NULL;
	return 	S_OK;
}

BOOL CRelMacroTreeBox::DeleteAllObjects(HTREEITEM hItem)
{
	HTREEITEM hChildItem = GetChildItem(hItem);

	while (hChildItem)
	{
		DeleteAllObjects(hChildItem);

		WTreeItem IT;
		HRESULT hr = GetProjectScript(hChildItem, IT.ppi());
		// Parent selbst auch löschen
		if (SUCCEEDED(hr))
		{// Childs löschen
			IT -> Release();
			SetItemData(hChildItem, 0);
		}

		hChildItem = GetNextSiblingItem(hChildItem);
	}
	
	return true;
}

BOOL CRelMacroTreeBox::DeleteItemWithParent(HTREEITEM hItem) 
{
	if (hItem)
	{
		HTREEITEM hParItem = GetParentItem(hItem);

		if (DeleteItem(hItem))
		{// Rückruf OnDelete korrekt
			if (hParItem)
			{// war das letze Item in der Liste
				if (NULL == GetChildItem(hParItem))
				{
					if (DeleteItem(hParItem))
						return true;
				}
			}
		}
	}
	return false;
}


HTREEITEM CRelMacroTreeBox::InitItem(HTREEITEM hItem) 
{
	HTREEITEM hInitItem = NULL;

	if (Expand(hItem, TVE_EXPAND))
	{	// 2. Ebene öffnen, 1. nur Schlüssel
		hInitItem = GetChildItem(GetChildItem(hItem));

		if (hInitItem)
		{
			SelectItem(hInitItem);
		}
	}

	return hInitItem;
}

HTREEITEM CRelMacroTreeBox::FindRightImportItem(REFIID riid, LPCSTR lpcstrFileName, HTREEITEM hSelItem)
{
	// Firstlevel == m_htreeCurrentMacroRoot oder m_htreeFilterMacros oper...
	HTREEITEM hInsertItem = NULL;
	/////////////////////////////////////////////////////
	// erstmal SUB-Items behandeln
	if (GetParentItem(hSelItem) == m_htreeCurrentMacroRoot)
	{// Projekt selektiert, SUB einfügen
		CString strParent;
		GetRightToken(hSelItem, strParent);

		hInsertItem = InsertGeneralItem(
						riid,
						lpcstrFileName,	// Scriptname
						strParent,		// Parentname
						hSelItem,		// Parenthandle
						false,			// Subitem
						true);			// neu
		return hInsertItem;
	}
	else if (GetParentItem(GetParentItem(hSelItem)) == m_htreeCurrentMacroRoot)
	{// drittes Level selektiert, auch SUB eifügen
		CString strParent;
		GetRightToken(GetParentItem(hSelItem), strParent);

		hInsertItem = InsertGeneralItem(
						riid,
						lpcstrFileName,	// Scriptname
						strParent,		// Parentname
						GetParentItem(hSelItem),		// Parenthandle
						false,			// Subitem
						true);			// neu
		return hInsertItem;
	}

	return NULL;
}

BOOL CRelMacroTreeBox::FindRightInsertItem(HTREEITEM hSelItem, HTREEITEM hFirstLevelItem)
{	//m_htreeCurrentMacroRoot == hFirstLevelItem oder m_htreeFilterMacros == hFirstLevelItem
	// oder ...
	if (GetParentItem(hSelItem) == hFirstLevelItem) 
	{
		if (InsertDefaultItem(hSelItem))
			return true;
	}
	else if (GetParentItem(GetParentItem(hSelItem)) == hFirstLevelItem)
	{// Ein Makro aus dritter Ebene selektiert
		if (InsertDefaultItem(GetParentItem(hSelItem)))
			return true;
	}
	else 
	{// Etwas anderes selektiert, Projekt einfügen
		if (InsertDefaultItem(hFirstLevelItem))
			return true;
	}

	return false;
}

BOOL CRelMacroTreeBox::InsertFileOnImport(REFIID riid, LPCSTR lpcstrFileName, BOOL fFirst, HTREEITEM hSelItem) 
{
	ASSERT(lpcstrFileName);
	ASSERT(hSelItem);

	/////////////////////////////////////////////////////
	// erstmal SUB-Items behandeln
	HTREEITEM hInsertItem = FindRightImportItem(riid, lpcstrFileName, hSelItem);
	/////////////////////////////////////////////////////
	// nun SUPER-Items behandeln, wenn kein SUB eingefügt wurde
	if (NULL == hInsertItem)
	{ // irgandwas Anderes selektiert, neues Filterprojekt einfügen
		// erstmal Key
		CString strFileName = GetContainerName(lpcstrFileName);
		HTREEITEM hParent = InsertGenKeyItem(hSelItem, strFileName);

		if (hParent)
		{
			hInsertItem = InsertGeneralItem(
						riid,
						lpcstrFileName, 
						lpcstrFileName, 
						hParent, 
						true, 
						true);
		}
	}

	// Für alle
	if (hInsertItem)
	{
		Expand(GetParentItem(hInsertItem), TVE_EXPAND);
		SelectItem(hInsertItem);
		return true;
	}

	return false;
}

BOOL CRelMacroTreeBox::GetNameEndLabelEdit(LPSTR lpstrDefaultName, UINT uiLen)
{
	ASSERT(uiLen > 0);
	ASSERT(lpstrDefaultName);

	WObjectManagement IObjFeatObjManagement;
	WObjectManagement IObjManagement;
	WObjectManagement IFilterObjManagement;
	CString  strDefault = GetDefaultName(IDS_DEFAULTMACRONAMEWITHCOUNT);
	UINT ui = 1;
	BOOL fResult = false;
	HRESULT hr = NOERROR;
	
	// Alle Container (und noch andere SPÄTER) durchsuchen
	hr = GetFilterScripts(IFilterObjManagement.ppi());
	if (FAILED(hr)) return false;
	hr = GetGeneralScripts(IObjManagement.ppi());
	if (FAILED(hr)) return false;
	hr = GetObjFeatScripts(IObjFeatObjManagement.ppi());
	if (FAILED(hr)) return false;
	// ob z.B. "Makro #1" oder "Makro #100" noch nicht vorhanden ist
	// MAX_MACRO_CNT == 200
	while (ui < MAX_MACRO_CNT && lpstrDefaultName)
	{
		wsprintf(lpstrDefaultName, (LPSTR)(LPCSTR)strDefault, ui); 

		if ( ! FindFirstDefaultString(IObjManagement, lpstrDefaultName) &&
			 ! FindFirstDefaultString(IFilterObjManagement, lpstrDefaultName) &&
			 ! FindFirstDefaultString(IObjFeatObjManagement, lpstrDefaultName))
		{// Nirgendswo dieses Makro gefunden, also gültig
			fResult = true;
			break;			
		}
		ui++;
	}

	return fResult;
}

HRESULT CRelMacroTreeBox::RenameItemEndLabelEdit(HTREEITEM hEditItem, LPCSTR lpcstr, HTREEITEM *phItem)
{
	ASSERT(hEditItem);
	ASSERT(lpcstr);
	ASSERT(phItem);
	if (NULL == lpcstr || NULL == phItem) return E_POINTER;
	if (NULL == hEditItem) return E_HANDLE;

	*phItem = NULL;

	try
	{
		WTreeItem IT;
		HRESULT hr = GetProjectScript(hEditItem, IT.ppi());
		if (FAILED(hr)) _com_issue_error(hr);
		// Umbenennen
		WObjManHelper IOMH = IT;
		hr = IOMH -> Rename(lpcstr);
		if (FAILED(hr)) _com_issue_error(hr);
		// Wird nicht mehr editiert
		// Item selbst umbenennen
		SetItemText(hEditItem, lpcstr);
		// Parent nicht umbenennen
		// Erfolg
		*phItem = hEditItem;
	}

	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return S_OK;
}
HRESULT CRelMacroTreeBox::InsertItemEndLabelEdit(HTREEITEM hEditItem, LPCSTR lpcstr, HTREEITEM *phItem)
{
	ASSERT(hEditItem);
	ASSERT(phItem);
	if (NULL == phItem) return E_POINTER;
	if (NULL == hEditItem) return E_HANDLE;

	HRESULT hr = NOERROR;

	*phItem = NULL;

	try
	{
		HTREEITEM hItem = NULL;
		if (m_htreeCurrentMacroRoot == GetParentItem(hEditItem))
		{
			hItem = InsertGeneralItem(
								CLSID_Script, // CLSID
								lpcstr,		//Name 
								lpcstr,		//Name Parent
								hEditItem,	//Parent 
								true,		//Super
								true);		//InitNew
		}
		// Item musste eingefügt werden
		if (hItem)
		{
			WTreeItem IT;			
			HRESULT hr = GetProjectScript(hItem, IT.ppi());
			if (FAILED(hr)) _com_issue_error(hr);

			SetItemText(hItem, lpcstr);
			// ItemText Key == Parent ändern
			char DefaultName[_MAX_PATH];
			CString str = GetDefaultName(IDS_CONTAINER);			
			wsprintf (DefaultName, str, lpcstr);
			SetItemText(hEditItem, DefaultName);

			Expand(hEditItem, TVE_EXPAND);
			SelectItem(hItem);
			// ERFOLG
			*phItem = hItem;
		}
		else 
		{// editiertes SELBST, d. h., SUBITEM !, Item schon vorhanden		
			WTreeItem IT;			
			HRESULT hr = GetProjectScript(hEditItem, IT.ppi());
			if (FAILED(hr)) _com_issue_error(hr); 
			// Parentname setzen
			CString strParent;
			GetRightToken(GetParentItem(hEditItem), strParent);
			WObjManHelper IOMH = IT;
			IOMH -> SetParentName(strParent);
				// Name Sub wurde editiert
			WBSProperty IP = IT;
			IP -> SetScriptName(lpcstr);
				
			SetItemText(hEditItem, lpcstr);
			SelectItem(hEditItem);
			
			*phItem = hEditItem;
		}
	}
	catch (_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	return hr;
}

BOOL CRelMacroTreeBox::CreateDefaultTree(IObjectManagement *pIOM, IStreamInfo *pISI)
{
	ASSERT(pIOM);
	ASSERT(pISI);
	if (NULL == pIOM || NULL == pISI) return false;

	int iImage = IMAGE_CLOSEMACROS;
	UINT uiID = pISI -> GetManID();
		
	switch (uiID)
	{
	case MANID_GENERAL:
		m_htreeCurrentMacroRoot = InsertGenRootItem(GenerateTreeEntry(IDS_TREEPROJECTMACROS), iImage);
		break;
	case MANID_FILTER:
		m_htreeCurrentMacroRoot = InsertFilterRootItem(GenerateTreeEntry(IDS_TREEFILTERMACROS), iImage);
		break;
	case MANID_OBJFEAT:
		m_htreeCurrentMacroRoot = InsertObjFeatRootItem(GenerateTreeEntry(IDS_TREEOBJFEATMACROS), iImage);
		break;
	}
	if (NULL == m_htreeCurrentMacroRoot) return false;

	if (FillTree(m_htreeCurrentMacroRoot, pIOM, pISI))					
		return true;
	return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// INSERTS
// Bei AnfangsInitialisierung
HRESULT CRelMacroTreeBox::InsertInitItem(HTREEITEM hParent, LPCSTR lpcstr)
{
	ASSERT(lpcstr);

	CString strName = GetContainerName(lpcstr);
	ASSERT(!strName.IsEmpty());
	// KeyItem erzeugen
	HTREEITEM hKeyItem = InsertGenKeyItem(hParent, strName);		
	// Immer Superitem erzeugen
	if (hKeyItem)
	{
		HTREEITEM hSuperItem = InsertGeneralItem(
						CLSID_Script, // CLSID
						lpcstr,		//Name 
						lpcstr,		//Name Parent
						hKeyItem,	//Parent 
						true,		//Super
						true);		//InitNew

		if (hSuperItem)
		{
			Expand(hKeyItem, TVE_EXPAND);
			SelectItem(hSuperItem);
			return S_OK;
		}
	}

	return E_FAIL;  
}

HRESULT CRelMacroTreeBox::Init(
							ITreeItem *pProjScript, 
							int iImage,
							HTREEITEM hParent,
							LPCSTR lpcstrItemEntry, 
							LPCSTR lpcstr,
							LPCSTR lpcstrPar,
							BOOL fJustInsert,
							HTREEITEM *phItem)
{
	ASSERT(pProjScript);
	ASSERT(phItem);
	if (NULL == phItem || NULL == pProjScript) return E_POINTER;
	
	*phItem = NULL;
	try
	{	// Item einfügen
		HTREEITEM hItem = InsertKey(lpcstrItemEntry, iImage, hParent);					
		if (NULL == hItem)	_com_issue_error(E_HANDLE);
		
		WObjManHelper IOMH = pProjScript; 
		WBSProperty IBSP = pProjScript;
		IOMH -> SetParentName(lpcstrPar);// Namen setzen		
		IBSP -> SetScriptName(lpcstr);// ParentNamen setzen
		// gerade eingefügt ?
		pProjScript -> SetJustInsert(fJustInsert);
		pProjScript -> AddRef();
		// TreeItem als Datum hinzufügen
		DWORD dwScript = (DWORD)pProjScript;
		SetItemData(hItem, dwScript);

		*phItem = hItem;
	}
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return S_OK;
}

// Allgemeine Objekte Sub's und Superitems
HTREEITEM CRelMacroTreeBox::InsertGeneralItem(REFIID riid, 
											  LPCSTR lpcstr, 
											  LPCSTR lpcstrPar, 
											  HTREEITEM hParent, 
											  BOOL fSuperItem, 
											  BOOL fInitNew,
											  BOOL fJustInsert)
{
	HTREEITEM hItem = NULL;
	try
	{
		if (IsNew(hParent)) _com_issue_error(E_FAIL); 

		WTreeItem IParent;
		THROW_FAILED_HRESULT(GetProjectScript(hParent, IParent.ppi())); 

		// ProjectScript instanzieren
		WTreeItem IProject;
		THROW_FAILED_HRESULT(IParent -> CreateInsertItem(
										IProject.ppi(), 
										riid,
										NULL,
										NULL,
										NULL,
										NULL,
										NULL,
										fSuperItem));
		// Namen, Parent, Justinsert, Itemdata setzen, ITEM einfügen
		int iImage = IProject -> GetImage();
		THROW_FAILED_HRESULT(Init(
					IProject, 
					iImage,
					hParent,
					lpcstr,		//	ItemEntry
					lpcstr,		//	ScriptName
					lpcstrPar,	//	ParentName
					fJustInsert,//	gerade eingefügt
					&hItem));
	}
	catch(_com_error&)
	{
		return NULL;
	}
	catch (bad_alloc) 
	{
		return NULL;
	}
	return hItem;
}

// RootItems
HTREEITEM CRelMacroTreeBox::InsertGenRootItem(LPCSTR lpcstr, int iImage)
{
	HTREEITEM hItem = NULL;
	ITreeItem *pProjScript = NULL;
	// ProjectScript instanzieren
	try 
	{
		pProjScript = (ITreeItem *) new CComObject<CRootDummyScript>;
		if (NULL == pProjScript) _com_issue_error(E_POINTER);		
		pProjScript -> AddRef();

		hItem = InsertKey(lpcstr, iImage, NULL);
		if (NULL == hItem) _com_issue_error(E_HANDLE);				
		// Diesen DummyScript hinzufügen
		DWORD dwScript = (DWORD)pProjScript;
		SetItemData(hItem, dwScript);
	}
	catch(_com_error&)
	{
		RELEASE(pProjScript);
		return NULL;
	}
	catch (bad_alloc) 
	{
		return NULL;
	}
	return hItem;
}
// RootItems
HTREEITEM CRelMacroTreeBox::InsertFilterRootItem(LPCSTR lpcstr, int iImage)
{
	HTREEITEM hItem = NULL;
	ITreeItem *pProjScript = NULL;
	// ProjectScript instanzieren
	try 
	{
		pProjScript = (ITreeItem *) new CComObject<CRootFilterScript>;
		if (NULL == pProjScript) _com_issue_error(E_POINTER);		
		pProjScript -> AddRef();

		hItem = InsertKey(lpcstr, iImage, NULL);
		if (NULL == hItem) _com_issue_error(E_HANDLE);				
		// Diesen DummyScript hinzufügen
		DWORD dwScript = (DWORD)pProjScript;
		SetItemData(hItem, dwScript);
	}
	catch(_com_error&)
	{
		RELEASE(pProjScript);
		return NULL;
	}
	catch (bad_alloc) 
	{
		return NULL;
	}
	return hItem;
}
// RootItems
HTREEITEM CRelMacroTreeBox::InsertObjFeatRootItem(LPCSTR lpcstr, int iImage)
{
	HTREEITEM hItem = NULL;
	ITreeItem *pProjScript = NULL;
	// ProjectScript instanzieren
	try 
	{
		pProjScript = (ITreeItem *) new CComObject<CRootObjFeatScript>;
		if (NULL == pProjScript) _com_issue_error(E_POINTER);		
		pProjScript -> AddRef();

		hItem = InsertKey(lpcstr, iImage, NULL);
		if (NULL == hItem) _com_issue_error(E_HANDLE);				
		// Diesen DummyScript hinzufügen
		DWORD dwScript = (DWORD)pProjScript;
		SetItemData(hItem, dwScript);
	}
	catch(_com_error&)
	{
		RELEASE(pProjScript);
		return NULL;
	}
	catch (bad_alloc) 
	{
		return NULL;
	}
	return hItem;
}
// KeyItems
HTREEITEM CRelMacroTreeBox::InsertGenKeyItem(HTREEITEM hParent, LPCSTR lpcstr, BOOL fJustInsert)
{
	HTREEITEM hItem = NULL;
	try 
	{// Parent geben lassen
		WTreeItem ITParent; 
		THROW_FAILED_HRESULT(GetProjectScript(hParent, ITParent.ppi()));
		// ProjectScript instanzieren
		WTreeItem IProjScript;
		THROW_FAILED_HRESULT(ITParent -> CreateInsertItem(
												IProjScript.ppi(), 
												CLSID_NULL, 
												NULL, 
												NULL, 
												NULL, 
												NULL, 
												NULL,
												false));		
		int iImage = IProjScript -> GetImage();
		// Namen, Parent, Justinsert, Itemdata setzen, ITEM einfügen
		THROW_FAILED_HRESULT(Init(
					IProjScript, 
					iImage,
					hParent,
					lpcstr,		//	ItemEntry
					lpcstr,
					NULL,
					fJustInsert, // gerade eingefügt
					&hItem));
	}
	catch(_com_error&)
	{
		return NULL;
	}
	catch (bad_alloc) 
	{
		return NULL;
	}
	return hItem;
}
HTREEITEM CRelMacroTreeBox::InsertFunctionItem (
												HTREEITEM hParent, 
												LPCSTR lpcstr, 
												LPCSTR lpcstrDecl, 												
												LPCSTR lpcstrType,
												LPCSTR lpcstrParams,
												LPCSTR lpcstrComment
												)
{
	ASSERT(lpcstr);
	ASSERT(hParent);

	HTREEITEM hItem = NULL;
	try 
	{
		WTreeItem IT;
		THROW_FAILED_HRESULT(GetProjectScript(hParent, IT.ppi()));
		
		WTreeItem IFunction;
		THROW_FAILED_HRESULT(IT -> CreateInsertItem(
											IFunction.ppi(),
											CLSID_NULL, 
											lpcstr, 
											lpcstrDecl, 												
											lpcstrType,
											lpcstrParams,
											lpcstrComment,
											false));		
		// Namen von Script setzen
		char str[_MAX_PATH], strPar[_MAX_PATH];
		WBSProperty IBSP = IT;
		WObjManHelper IOMH = IT;
		IBSP -> GetScriptName(str, _MAX_PATH);
		IOMH -> GetParentName(strPar, _MAX_PATH); // ParentNamen von Script geben lassen
		int iImage = IFunction -> GetImage();
		// Weitere Initialisierungen
		THROW_FAILED_HRESULT(Init(
									IFunction, 
									iImage,
									hParent,
									lpcstr,
									str,
									strPar,
									false,	// Gerade eingefügt
									&hItem));
	}
	catch (_com_error&)
	{
		return NULL;
	}
	catch (bad_alloc)
	{
		return NULL;
	}
	return hItem;
}

// "Neues Macro"
HTREEITEM CRelMacroTreeBox::InsertDefaultItem(HTREEITEM hParent)
{
	ASSERT(hParent);
	if (NULL == hParent) return NULL;

	HTREEITEM hItem = NULL;
	try
	{
		if (IsNew(hParent)) _com_issue_error(E_FAIL);
		// DefaultItem einfügen
		char cs[_MAX_PATH];		
		if (!GetNameEndLabelEdit(cs, _MAX_PATH)) _com_issue_error(E_FAIL);

		if (hParent == m_htreeCurrentMacroRoot)
		{
			hItem = InsertGenKeyItem(hParent, cs, true);
		}
		else if (GetParentItem(hParent) == m_htreeCurrentMacroRoot)
		{
			hItem = InsertGeneralItem(
										CLSID_Script, // CLSID
										cs,		//Name Script
										cs,		//Name Parent
										hParent,	//Parent 
										false,		//Super 
										true);		//InitNew
		}
		if (NULL == hItem) _com_issue_error(E_HANDLE);

		WTreeItem IT;
		THROW_FAILED_HRESULT(GetProjectScript(hItem, IT.ppi()));
		IT -> SetJustInsert(true);	// Darf danach nicht mehr editiert werden		
		// Parent Opened-Image einstellen
		OpenFoldersImage(hItem);

		Expand(hItem, TVE_EXPAND); // bei Wolfgang nich möglich: , Warum ??? 
		SelectItem(hItem); 
		EditLabel(hItem);
	}
	catch (_com_error&)
	{
		return NULL;
	}
	return hItem;
}

HTREEITEM CRelMacroTreeBox::InsertKey(LPCSTR lpcstr, int iImage, HTREEITEM hParent)
{
	// aus einem Path FileNamen herausfiltern
	CString strFileName = lpcstr;
	strFileName = GetFileName(strFileName, false);

	TV_ITEM   item;

	item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	item.iImage = iImage;
	item.iSelectedImage = iImage;
	item.pszText = (LPSTR)(LPCSTR)strFileName;

	TV_INSERTSTRUCT InsertStruct;

	InsertStruct.hParent = hParent;
	InsertStruct.hInsertAfter = TVI_LAST;//fFirst ? TVI_FIRST : TVI_LAST;	
	InsertStruct.item = item;

	HTREEITEM hItem = InsertItem (&InsertStruct);
	ASSERT(hItem);

	return hItem;
}

HRESULT CRelMacroTreeBox::CreateSubItems(LPCSTR lpcstrParentName, REFIID riid)
{
	HTREEITEM hSel = GetSelectedItem();
	if (NULL == hSel) return E_HANDLE;
	HTREEITEM hPar = GetParentItem(hSel);
	if (NULL == hPar) return E_HANDLE;
	
	CString strFileName = lpcstrParentName;
	strFileName = GetFileName(strFileName, false);
	HRESULT hr = SetSubItems(hPar, hSel, strFileName, riid);
	return hr;
}

HRESULT CRelMacroTreeBox::SetSubItems(HTREEITEM hParentItem, HTREEITEM hSuperItem, LPCSTR lpcstrParentName, REFIID riid)
{
	HRESULT hr = NOERROR;
	LPSTR *lplpstrRel = NULL;
	LPSTR lpstrText = NULL;
	ebHCODE hCode = NULL;
	UINT uiCnt = 0;

	LPSTR lpstrTextSub = NULL;
	ebHCODE hCodeSub = NULL;
	LPSTR *lplpstrRelSub = NULL;
	UINT uiCntSub = 0;
	try
	{
		WTreeItem IT;
		THROW_FAILED_HRESULT(GetProjectScript(hSuperItem, IT.ppi()));							
		// Setzen aller SUBS dieses SUPER-Items, vorher wurde Parent-DummyItem erzeugt
		WObjManHelper IOMH = IT; // Query
		THROW_FAILED_HRESULT(IOMH -> Open(&lpstrText, &hCode, &lplpstrRel, uiCnt));

		for (UINT ui = 0; ui < uiCnt; ui++)
		{
			COTASKMEMFREE(lpstrTextSub); 
			COTASKMEMFREE(hCodeSub); 
			MEMFREE(lplpstrRelSub, uiCntSub);

			LPSTR lpstr = lplpstrRel[ui];
			ASSERT(lpstr);
			HTREEITEM hInsert = NULL;
			hInsert = InsertGeneralItem(riid, lpstr, lpcstrParentName, hParentItem, false, false, false/* not just insert */);
			ASSERT(hInsert);
			if (NULL == hInsert) _com_issue_error(E_HANDLE);
			// Code da ?
			WTreeItem ITSub;
			THROW_FAILED_HRESULT(GetProjectScript(hInsert, ITSub.ppi()));							
			// Setzen aller SUBS dieses SUPER-Items, vorher wurde Parent-DummyItem erzeugt
			// Kann eigentlich keine Related besitzen
			WObjManHelper IOMHSub = ITSub; // Query
			THROW_FAILED_HRESULT(IOMHSub -> Open(&lpstrTextSub, &hCodeSub, &lplpstrRelSub, uiCntSub));
			if (NULL == hCodeSub) continue;

			// Funktion nur bei compilierten Code setzen !!!
			if (NULL == hInsert || NULL == InsertDummyFunction(hInsert)) 
			{
				_com_issue_error(E_FAIL); 
				break;
			}
		}
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	COTASKMEMFREE(lpstrText); 
	COTASKMEMFREE(hCode);
	COTASKMEMFREE(lpstrTextSub); 
	COTASKMEMFREE(hCodeSub); 
	MEMFREE(lplpstrRel, uiCnt);
	MEMFREE(lplpstrRelSub, uiCntSub);
	return hr;
}

HTREEITEM CRelMacroTreeBox::SetSuperItem(
										 IObjectManagement *pIObjMan, 
										 IStreamInfo *pIStreamInfo, 
										 HTREEITEM hParItem, 
										 REFIID riid, 
										 LPCSTR lpcstr, 
										 HTREEITEM *phInsertItem
										 )
{
	ASSERT(phInsertItem);
	ASSERT(lpcstr);
	ASSERT(pIStreamInfo);
	if (NULL == lpcstr || NULL == phInsertItem || NULL == pIStreamInfo) return NULL;
	*phInsertItem = NULL;

	CString strFileName = GetContainerName(lpcstr);
	// erstmal Keyitem einfügen
	HTREEITEM hKeyItem = InsertGenKeyItem(hParItem, strFileName);
	if (NULL == hKeyItem) return NULL;
	// Super an sich einfügen
	*phInsertItem = InsertGeneralItem(
							riid,
							lpcstr/*Name*/, 
							lpcstr, 
							hKeyItem/*Parent*/, 
							true/*Super*/, 
							false/*InitNew*/,
							false/* not just insert */);
	if (NULL == *phInsertItem) return NULL; 

	if (GetStreamInfo(pIStreamInfo, lpcstr) & CC_CODE)
	{// Nur bei Code Dummy einfügen
		if (NULL == InsertDummyFunction(*phInsertItem))	return NULL;
	}
	return hKeyItem;
}

DWORD CRelMacroTreeBox::GetStreamInfo(IStreamInfo *pInfo, LPCSTR lpcstr)
{
	DWORD dwInfo = 0;
	USES_CONVERSION;	
	if (SUCCEEDED(pInfo -> Get(A2OLE(lpcstr), &dwInfo)))
		return dwInfo;

	return 0;
}

BOOL CRelMacroTreeBox::FillTree(HTREEITEM hItem, IObjectManagement *pIObjMan, IStreamInfo *pIStreamInfo)
{
	try
	{
		WUnknown IU;
		THROW_FAILED_HRESULT(pIObjMan -> EnumStrings(IU.ppi()));

		WEnumos_wstring IE(IU);
		os_wstring oswstr;
			
		while (S_OK == IE -> Next(1, &oswstr, NULL)) 
		{
			CString str = GetDefaultName(IDS_NEWSTREAMINFO);
			CString strOld = GetDefaultName(IDS_STREAMINFOS);
			USES_CONVERSION;
			LPSTR lpstr = OLE2A(oswstr.c_str());

			if (0 == _stricmp(str, lpstr) || 0 == _stricmp(strOld, lpstr)) continue;

			HTREEITEM hSuperItem = NULL;
			HTREEITEM hParentItem = NULL;
			if (GetStreamInfo(pIStreamInfo, lpstr) & SUPERITEM)
			{// Parent merken
				hParentItem = SetSuperItem(pIObjMan, pIStreamInfo, hItem, CLSID_Script, lpstr, &hSuperItem);
				if (NULL == hParentItem) _com_issue_error(E_HANDLE);
				THROW_FAILED_HRESULT(SetSubItems(hParentItem, hSuperItem, lpstr, CLSID_Script));
			}
			else if (0 == GetStreamInfo(pIStreamInfo, lpstr))
			{// Bei alten Storage_strukturen keine Streaminfo
				hParentItem = SetSuperItem(pIObjMan, pIStreamInfo, hItem, CLSID_Script, lpstr, &hSuperItem);
				if (NULL == hParentItem) _com_issue_error(E_HANDLE);
			}
		}
	}
	catch(_com_error&)
	{
		return false;
	}
	return true;
}


HTREEITEM CRelMacroTreeBox::IsItemAllreadyInsert(HTREEITEM hItem, LPCSTR lpcstr)
{
	ASSERT(lpcstr);

	HTREEITEM hChildItem = GetChildItem(hItem);
	while (hChildItem)
	{
		CString str = GetItemText(hChildItem);
		CString strFileName = lpcstr;
		
		strFileName = GetFileName(strFileName, false);

		if (0 == _stricmp(str, strFileName))
			return hChildItem;

		HTREEITEM hNext = IsItemAllreadyInsert(hChildItem, lpcstr);

		if (NULL != hNext)
			return hNext;

		hChildItem = GetNextSiblingItem(hChildItem);
	}

return NULL;
}

HTREEITEM CRelMacroTreeBox::GetChildItemSel(ITreeItem **ppIT)
{
	HTREEITEM hItem = GetSelectedItem();
//	ASSERT(NULL != hItem);
	if (NULL == hItem) return NULL;

	HTREEITEM hChildItem = GetChildItem(hItem);
	if (NULL == hChildItem) return NULL;
	
	if (FAILED(GetProjectScript(hChildItem, ppIT)))
		return NULL;

	return hChildItem;
}

UINT CRelMacroTreeBox::GetCountSuperItem(HTREEITEM hItem, LPCSTR lpcstrDeleted)
{
	UINT ui = 0;
	try
	{
		if (S_OK == IsFunctionLevel(hItem))
			hItem = GetParentItem(hItem);

		if (NULL == hItem || NULL != GetPrevSiblingItem(hItem))// SuperItem immer an erster Stelle im Tree
			_com_issue_error(E_FAIL);

		while (hItem)
		{
			hItem = GetNextSiblingItem(hItem);
			if (NULL == hItem) break;

			WTreeItem IT;
			HRESULT hr = GetProjectScript(hItem, IT.ppi());
			if (FAILED(hr)) _com_issue_error(hr);

			WObjManHelper IOMH = IT;
			if (IOMH -> GetInitNew())
				continue;
	
			char str[_MAX_PATH];
			WBSProperty IBSP = IT;
			IBSP -> GetScriptName(str, _MAX_PATH);
			if (0 == strlen(str)) _com_issue_error(E_FAIL); // Fehler

			if (lpcstrDeleted && 0 == strcmp(str, lpcstrDeleted)) // Schon Gelöschten nicht mitzählen
				continue;

			ui++;
		}
	}
	catch(_com_error& e)
	{
		if (FAILED(_COM_ERROR(e)))
			ui = 0;
	}
	return ui;
}

BOOL CRelMacroTreeBox::GetStringListItems(HTREEITEM hItem, LPSTR * lplpstr, UINT uiCnt, LPCSTR lpcstrDeleted)
{
	int i = 0;
	try
	{
		if (S_OK == IsFunctionLevel(hItem))		// bei FunctionLevel, Itemliste des Parents, wenn SUPER, durchlaufen
			hItem = GetParentItem(hItem);
		if (NULL == hItem || NULL != GetPrevSiblingItem(hItem))
			_com_issue_error(E_FAIL);// SUPER immer an erster Stelle im Tree

		while (i < uiCnt && hItem != NULL)
		{
			hItem = GetNextSiblingItem(hItem);
			if (NULL == hItem) break;

			WTreeItem IT;
			HRESULT hr = GetProjectScript(hItem, IT.ppi());
			if (FAILED(hr)) _com_issue_error(hr);

			WObjManHelper IOMH = IT;
			if (IOMH -> GetInitNew())
				continue;
			
			char str[_MAX_PATH];
			WBSProperty IBSP = IT;
			IBSP -> GetScriptName(str, _MAX_PATH);
			int iLen = strlen(str);// Ohne '\0' -> uiLen+1
			ASSERT(iLen > 0);
			if (iLen <= 0) _com_issue_error(E_FAIL); // Fehler

			if (lpcstrDeleted && 0 == strcmp(str, lpcstrDeleted))
				continue;// Schon Gelöschten nicht mitzählen

			LPSTR lpstr = (LPSTR)CoTaskMemAlloc(iLen + 1);
			if (NULL == lpstr) _com_issue_error(E_POINTER);

			strcpy(lpstr, str);
			lpstr[iLen] = '\0';

			lplpstr[i] = lpstr;

			i++;
		}
	}
	catch(_com_error& e)
	{
		if (FAILED(_COM_ERROR(e))) {
			MEMFREE(lplpstr, i); // Bis einen zurück freigeben
			return false;
		}
	}
	return true;
}

BOOL CRelMacroTreeBox::GetRightToken(HTREEITEM hItem, CString & str)
{
	CString strContainerText = GetItemText(hItem);
	LPSTR lpstrTok = strtok((LPSTR)(LPCSTR)strContainerText, " ");
	lpstrTok = strtok(NULL, " ");
	str = lpstrTok;
	return lpstrTok ? true : false;
}
					// Applic.,Proj., Script, Dirty
CString CRelMacroTreeBox::GenerateTreeEntry (int IDS)
{
	char Name[_MAX_PATH];
	char ProjectName[_MAX_PATH];
	CString strEntry; 
	LPSTR pEntry = NULL;
	
	strEntry.Empty();

	if (DEX_GetActiveProject(ProjectName))
	{
		HRESULT hr = FileName (ProjectName, Name);
		if(SUCCEEDED(hr))
		{
			TRY 
			{
				pEntry = strEntry.GetBuffer (_MAX_PATH);
				if (pEntry == NULL) return strEntry;
			}
			CATCH (CMemoryException, e) 
			{
				return strEntry;
			}                  
			END_CATCH
			
			wsprintf (pEntry, "%s (%s)", (LPCSTR)GetDefaultName(IDS), (LPCSTR)Name);
			
			strEntry.ReleaseBuffer();
			
			return strEntry;
		}
	}

return strEntry;
}

CString CRelMacroTreeBox::GetContainerName(LPCSTR lpcstrFileName)
{
	ASSERT(lpcstrFileName);

	CString strDefault;
	CString str = GetDefaultName(IDS_CONTAINER);
	CString strFileName = lpcstrFileName;

	strFileName = GetFileName(strFileName, false);

	try {
		LPSTR lpstrDefault = strDefault.GetBuffer(_MAX_PATH);
		wsprintf (lpstrDefault, str, strFileName);
	} catch (bad_alloc) {
		return g_cbNil;
	}

	strDefault.ReleaseBuffer();

	return strDefault;
}

BOOL CRelMacroTreeBox::IsNew (HTREEITEM hItem)
{
	try
	{
		HTREEITEM hChildItem = GetChildItem(hItem);
		if (NULL == hChildItem) _com_issue_error(S_FALSE); 
		// nur einfügen, wenn Superitem schon gespeichert
		WTreeItem IT;
		HRESULT hr = GetProjectScript(hChildItem, IT.ppi());
		if (FAILED(hr)) _com_issue_error(hr);  

		WObjManHelper IOMH = IT;
		if (IOMH -> GetInitNew())
			return true;
	}
	catch(_com_error& e)
	{
		if (FAILED(_COM_ERROR(e)))
			return true;
	}				
	return false;
}

HTREEITEM CRelMacroTreeBox::GetSuperItem (HTREEITEM hSubItem, ITreeItem **ppIT)
{
	ASSERT(ppIT);
	if (NULL == ppIT) return NULL;
	///////////////////////////////////////////////////
	// Gibt SuperItem (Übergeordnetes) eines SUB's zurück
	HTREEITEM hItem = NULL;
	*ppIT = NULL;
	try
	{// Wenn Null übergeben wird, dann das Geladene nehmen
		if (NULL == hSubItem) hSubItem = GetLoadedItem();
		if (NULL == hSubItem) _com_issue_error(E_HANDLE);

		if (S_OK == IsFunctionLevel(hSubItem)) hSubItem = GetParentItem(hSubItem);
		if (NULL == hSubItem) _com_issue_error(E_HANDLE);
		//erst  Parent des SUB's geben lassen, erstes Item (Childitem) des Parent ist gleichzeitíg SUPER
		hItem = GetParentItem(hSubItem); 
		hItem = GetChildItem(hItem);
		if (NULL == hItem) _com_issue_error(E_HANDLE);
		// ItemObjekt des SUPER an sich geben lassen	
		WTreeItem IT;
		HRESULT hr = GetProjectScript(hItem, IT.ppi());
		if (FAILED(hr)) _com_issue_error(hr);
		
		if (S_OK == IsSuperItem(hItem))
			*ppIT = IT.detach();
	}
	catch(_com_error&)
	{
		return NULL;
	}
	return hItem;
}

HRESULT FileName(LPCSTR pPathName, LPSTR pNameToUse)
{
	ASSERT(pPathName);
	ASSERT(pNameToUse);

	char *pDrive = new char [_MAX_DRIVE];
	char *pPath = new char [_MAX_DIR];
	char *pFName = new char [_MAX_FNAME];

	if (pDrive == NULL || pPath == NULL || pFName == NULL) {
		if (pDrive) delete (pDrive);
		if (pPath) delete (pPath);
		if (pFName) delete (pFName);    
		return ResultFromScode (E_OUTOFMEMORY);
	}
	
	// DateiNamen splitten
	_splitpath (pPathName, pDrive, pPath, pFName, NULL);
	// auszugebender Name
	_makepath (pNameToUse, NULL, NULL, pFName, NULL);

	// Speicher freigeben
	delete (pDrive);
	delete (pPath);
	delete (pFName);               
		                        
return NOERROR;		
}

CString GetDefaultName(int IDS)
{
	CString str;
	if (!::LoadString(str, IDS))
	{
		str.Empty();
		return str;
	}

	return str;
}

CString GetFileName (CString &rPath, BOOL fExt)
{// liefert FileName ohne Fileerweiterung/mit Fileerweiterung

	CString strName, strExt;

	try {                                       
		char *pName = strName.GetBuffer (_MAX_PATH);
		char *pExt = strExt.GetBuffer(_MAX_EXT);
		
		_splitpath (rPath, NULL, NULL, pName, pExt);
		_makepath (pName, g_cbNil, g_cbNil, pName, fExt ? pExt : g_cbNil);
	} catch (bad_alloc) {
		AfxMessageBox (IDS_NOMEMORY);
		return g_cbNil;
	}                  

	strName.ReleaseBuffer();

	return strName;
}

CString GetFileExtension (CString &rPath)
{// liefert FileName ohne Fileerweiterung/mit Fileerweiterung

	CString strName, strExt;

	try {                                       
		char *pName = strName.GetBuffer (_MAX_PATH);
		char *pExt = strExt.GetBuffer(_MAX_EXT);
		
		_splitpath (rPath, NULL, NULL, NULL, pExt);
		_makepath (pName, g_cbNil, g_cbNil, g_cbNil, pExt);
	} catch (bad_alloc) {
		AfxMessageBox (IDS_NOMEMORY);
		return g_cbNil;
	}                  

	strName.ReleaseBuffer();

	return strName;
}


HRESULT CRelMacroTreeBox::InsertFunction (HTREEITEM hParent, const ebHCODE hCode)
{
	ASSERT(hParent);
	ASSERT(NULL != hCode);

	if (NULL == hCode || NULL == hParent) return E_HANDLE;

	ebPROCINFO PI;
	ebBOOL fNext = true;
	ebHENUM hEnum = NULL;
	HRESULT hr = NOERROR;
	char strRet[MAXSTRLENGTH];
	HTREEITEM hItem = NULL;

	if (GetChildItem(hParent)) 
	{
		hr = DeleteFunctionItems(hParent);
		if (FAILED(hr) || S_FALSE == hr) return hr; 
	}

	try	{
		// alle Entries enumerieren und in TreeItem erzeugen
		hEnum = ebGetFirstProc(hCode, &PI);
		if (NULL != hEnum) {
			while (fNext) {
				strRet[0] = '\0';

				if (1 == PI.wType)
				{// Function
					GetStringTypeFromWType(PI.wRetType, strRet, MAXSTRLENGTH);
				}

				hItem = InsertFunctionItem (hParent, PI.szName, NULL, strRet, NULL, NULL);
				ASSERT(NULL != hItem);
				fNext = ebGetNextProc(hEnum, &PI);
			}		
		
			ebEnumClose(hEnum);
		}
	}
	catch (_com_error &e)
	{
		if (hEnum)	ebEnumClose(hEnum);
		return _COM_ERROR(e);
	}

	return hr;
}

HTREEITEM CRelMacroTreeBox::InsertDummyFunction (HTREEITEM hParent)
{
	ASSERT(hParent);
	CString strUnt = GetDefaultName(IDS_UNTITLED);
	return 	InsertFunctionItem (hParent, strUnt, NULL, NULL, NULL, NULL);
}

HTREEITEM CRelMacroTreeBox::CountOneLevel(HTREEITEM hParItem, LPCSTR lpcstrItemName, UINT & ui)
{
	ASSERT(hParItem);
	ASSERT(lpcstrItemName);

	CString str;
	HTREEITEM hItem = NULL;
	BOOL fResult = false;

	if (
		NULL == hParItem || 
		NULL == lpcstrItemName ||//Fehler
		! ItemHasChildren(hParItem)// hat gar keine Children
		) 
		return NULL;

	ui = 0;

	hItem = GetChildItem(hParItem);
		
	while (NULL != hItem)
	{
		str = GetItemText(hItem);

		if (str == lpcstrItemName) 
			ui++;
		hItem = GetNextSiblingItem(hItem);
	}
// den jeweils letzten rausreichen
	return hItem;
}

HRESULT CRelMacroTreeBox::InsertFunctionLoadedItem (
	LPCSTR lpcstrName, LPCSTR  lpcstrDecl, LPCSTR lpcstrType, LPCSTR  lpcstrParams, LPCSTR lpcstrComment, LPSTR * lplpstr)
{	// Extern ?
	if (NULL == m_htreeLoadedItem) return E_UNEXPECTED;

	HRESULT hr = NOERROR;
	try
	{
		HTREEITEM hParentItem = NULL;
		// Jeweils gewährleisten, dass Script Parent von Funktion andererseits RAUS
		if (S_OK == IsScriptLevel(m_htreeLoadedItem))
			hParentItem = m_htreeLoadedItem;
		else if (S_OK == IsFunctionLevel(m_htreeLoadedItem)) 
			hParentItem = GetParentItem(m_htreeLoadedItem);
		else // RAUS
			_com_issue_error(E_FAIL); 

		HTREEITEM hFunctionItem = InsertFunctionItem (hParentItem, lpcstrName, lpcstrDecl, lpcstrType, lpcstrParams, lpcstrComment);
		if (NULL == hFunctionItem) _com_issue_error(E_HANDLE);

		WTreeItem IT;
		hr = GetProjectScript(hFunctionItem, IT.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

		WObjManHelper IOMH = IT;
		hr = IOMH -> New(lplpstr);
		if (FAILED(hr)) _com_issue_error(hr);
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}			
	return hr;
}

HRESULT CRelMacroTreeBox::DeleteFunctionItems(HTREEITEM hParent)
{
	HRESULT hr = NOERROR;
	HTREEITEM hChild = GetChildItem(hParent);
	HTREEITEM hNext = NULL;

	if (!(S_OK == IsScriptLevel(hParent)))// nicht 4.Stufe
		return S_FALSE;

	while (hChild)
	{// erst noch Next geben lassen
		hNext = GetNextSiblingItem(hChild);
		DeleteItem(hChild); // dann Delete
		if (NULL == hNext) break;
		hChild = hNext;
	}

	return hr;
}

HRESULT CRelMacroTreeBox::GetItemForExport(ITreeItem **ppIT, DWORD & dwSaveFLag)
{
	ASSERT(ppIT);
	if (NULL == ppIT) return E_POINTER;

	*ppIT = NULL;

	HRESULT hr = S_OK;
	HTREEITEM hSelItem = GetSelectedItem();
	if (NULL == hSelItem) return E_HANDLE;

	if (S_OK == IsScriptLevel(hSelItem))
	{// Nur Stream an sich exportieren
		hr = GetProjectScript(hSelItem, ppIT);
		if (FAILED(hr)) return hr;
	}
	else if (S_OK == IsFunctionLevel(hSelItem))
	{// Nur Item an sich exportieren
		HTREEITEM hItem = GetParentItem(hSelItem);
		
		hr = GetProjectScript(hItem, ppIT);
		if (FAILED(hr)) return hr;
	}
	else if (S_OK == IsFirstLevel(hSelItem))
	{
		HTREEITEM hItem = GetChildItem(hSelItem);
		if (NULL != hItem) 
			hItem = GetChildItem(hItem);
		
		if (NULL == hItem) return E_HANDLE;

		hr = GetProjectScript(hItem, ppIT);
		if (FAILED(hr)) return hr;
		dwSaveFLag |= CC_EXPORTALL;
	}
	else if (S_OK == IsKeyLevel(hSelItem))
	{
		HTREEITEM hItem = GetChildItem(hSelItem);
		if (NULL == hItem) return E_HANDLE;

		hr = GetProjectScript(hItem, ppIT);
		if (FAILED(hr)) return hr;
		dwSaveFLag |= CC_EXPORTALL;
	}
	else
		hr = E_FAIL;

	return S_OK;
}

///////////////////////////////////////////////////////////////////
// Bei COMPILIERUNG im Debugger und EXPAND im Tree
HRESULT CRelMacroTreeBox::EnumFunctions(HTREEITEM hItem)
{
	HRESULT hr = NOERROR;
	ebHCODE hCode = NULL;

	if (NULL == hItem && NULL == m_htreeLoadedItem) return S_FALSE; // externes File

	if (NULL == hItem) // Ruf kommt aus Debugger 
		hItem = m_htreeLoadedItem;// Hier muss gültiges Item vorhanden sein	
	
// Muss Script sein	, if IT -> GetInitNew() ? 
	if (!(S_OK == IsScriptLevel(hItem))) 
		return S_FALSE;

// Wenn der schon Geladene Expanded, dann immer aktuellen Code aus Debugger besorgen
	hr = EnumFunctionsFromDebugger(hItem);
	if (FAILED(hr)) // hCode im Debugger == NULL, wenigstens von Platte besorgen
		hr = EnumFunctionsFromDisk(hItem);

	return hr;
}
HRESULT CRelMacroTreeBox::EnumFunctionsFromDebugger(HTREEITEM hItem)
{
	ASSERT(hItem);

	if (hItem != m_htreeLoadedItem && // FunctionItem
		GetParentItem(m_htreeLoadedItem) != hItem) 
		return E_FAIL;
	// Parent vom Geladenen Functionitem wurde expandiert
	if (GetParentItem(m_htreeLoadedItem) == hItem)
		hItem = GetParentItem(m_htreeLoadedItem);

	ebHCODE hCode = NULL;
	HRESULT hr = NOERROR;

	// Aktuellen Code vom Item besorgen
	hr = GetMainFrame() -> GetCode(&hCode);
	if (SUCCEEDED(hr) && NULL != hCode)// liefert S_FALSE, wenn hCode == NULL
		hr = InsertFunction (hItem, hCode);
	
	if (hCode) {
		CoTaskMemFree(hCode); hCode = NULL;
	} else 
		return E_HANDLE;

	return hr;
}
HRESULT CRelMacroTreeBox::EnumFunctionsFromDisk(HTREEITEM hItem)
{
	ASSERT(hItem);

	LPSTR *lplpstrRel = NULL;
	LPSTR lpstrText = NULL;
	ebHCODE hDiskCode = NULL;
	UINT uiCnt = 0;
	HRESULT hr = NOERROR;
	try
	{
		WTreeItem IT;
		hr = GetProjectScript(hItem, IT.ppi());							
		if (FAILED(hr)) _com_issue_error(hr);  
		// Nicht aktuellen Code von Platte besorgen, wenn EnumFunctionsDebugger() FAIL
		WObjManHelper IOMH = IT;
		hr = IOMH -> Open(&lpstrText, &hDiskCode, &lplpstrRel, uiCnt);	
		if (FAILED(hr)) _com_issue_error(hr);  
		// Unter Umständen nur Text abgespeichert, COMPILE war nicht erfolgreich
		if (NULL == hDiskCode) _com_issue_error(S_FALSE);
		hr = InsertFunction (hItem, hDiskCode);
		if (FAILED(hr)) _com_issue_error(hr);  
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}			
	if (hDiskCode) CoTaskMemFree(hDiskCode);
	if (lpstrText) CoTaskMemFree(lpstrText);
	MEMFREE(lplpstrRel, uiCnt);
	return hr;
}	

HRESULT CRelMacroTreeBox::RightButtonDown(CPoint pt)
{
	HRESULT hr = NOERROR;
	try
	{
		SetRBTreeMenu(true);
		// SubMenue erzeugen
		CMenu Menu;
		ClientToScreen(&pt) ;
		if (false == Menu.LoadMenu(IDR_RBUTTONTREEGENERAL)) _com_issue_error(E_FAIL);
		// Hier nach Selektion entscheiden, welches Menü geladen weren soll
		HTREEITEM hItem = GetSelectedItem();
		if (NULL == hItem) _com_issue_error(E_HANDLE);
		// Selektierten geben lassen
		WTreeItem IT;
		THROW_FAILED_HRESULT(GetProjectScript(hItem, IT.ppi()));
		int iID = IT -> GetPopUpMenuID();
		// Invalid ID ()
		if (iID < 0 || iID > DEBUGGERFOCUSED) _com_issue_error(E_INVALIDARG);
		// Fokus auf Debugger
		if (!GetMainFrame() -> IsTreeFocused())
			iID = DEBUGGERFOCUSED;
		// Richtiges Menü laden
		if (NULL == Menu.GetSubMenu (iID) -> TrackPopupMenu (TPM_LEFTALIGN|TPM_RIGHTBUTTON, pt.x, pt.y, this)) return E_FAIL;
	}
	catch (_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	return hr;
}

BOOL GetStringTypeFromWType(ebWORD wType, LPSTR lpstr, UINT uiLen)
{
	LPSTR lpstrType = NULL;

	switch (wType)
	{
		case TYP_INTEGER:
		{
			lpstrType = "Integer";
			break;
		}
		case TYP_LONG:
		{
			lpstrType = "Long";
			break;
		}
		case TYP_SINGLE:
		{
			lpstrType = "Single";
			break;
		}
		case TYP_DOUBLE:	
		{
			lpstrType = "Double";
			break;
		}
		case TYP_DATE:
		{
			lpstrType = "Date";
			break;
		}
		case TYP_STRING:		
		{
			lpstrType = "String";
			break;
		}
		case TYP_BOOLEAN:		
		{
			lpstrType = "BOOLean";
			break;
		}
		case TYP_VARIANT:		
		{
			lpstrType = "Variant";
			break;
		}
		default:
		{
			return false;
		}
	}

	if (strlen(lpstrType) < uiLen)
		strcpy(lpstr, lpstrType);

	return true;
}

BOOL ModifyName(LPSTR lpstr)
{
	ASSERT(lpstr);
	// Am Anfang Großbuchstaben
	if (__isascii(*lpstr) && islower(*lpstr)) {
		*lpstr = toupper ((int)*lpstr); 
	}	

	UINT ui = strlen(lpstr);
	if (ui >= 32)// Stream darf keine Leerzeichen enthalten und nicht länger als 32 Byte sein
		lpstr[31] = '\0';

	LPSTR lpstrTok = lpstr;

	while (NULL != lpstrTok && '\0' != *lpstrTok)
	{
		if (' ' == *lpstrTok)
			*lpstrTok = '_';
		lpstrTok ++;
	}

	return true;
}
BOOL FindFirstDefaultString(IObjectManagement *pIObjMan, LPSTR lpstrDef)
{
	LPSTR lpstr = NULL;
	WUnknown IU;
	HRESULT hr = pIObjMan -> EnumStrings(IU.ppi());

	USES_CONVERSION;

	if (SUCCEEDED(hr)) 
	{
		WEnumos_wstring IE(IU);
		os_wstring oswstr;

		while (S_OK == IE -> Next(1, &oswstr, NULL)) 
		{
			lpstr = OLE2A(oswstr.c_str());
			ASSERT(lpstr);
			if (0 == _stricmp(lpstrDef, lpstr))
			{// String gefunden, nun mit nächstem lpstrDef (z.B. "Makro #2") weitersuchen
				return  true;
			}
		}
	}

	return false;
}


////////////////////////////////////////////////////////////////////////////
// Commands

// IMPORT 
void CRelMacroTreeBox::OnImport() 
{
	GetMainFrame() -> OnDebugImport();
}	
// Export 
void CRelMacroTreeBox::OnSaveas() 
{
	GetMainFrame() -> OnDebugSaveas();
}
// ÖFFNEN 
void CRelMacroTreeBox::OnOpen()
{
	GetMainFrame() -> OnDebugOpen();
//	GetMainFrame() -> OnDebugSave();
	GetMainFrame() -> PostMessage(WM_SETFOCUS);
}
// SAVE 
void CRelMacroTreeBox::OnSave() 
{
	GetMainFrame() -> OnDebugSave();	
}
// Entfernen 
void CRelMacroTreeBox::OnRemove() 
{
	GetMainFrame() -> OnDebugRemove();	
}
// Neues File anlegen 
void CRelMacroTreeBox::OnNew() 
{
	GetMainFrame() -> OnDebugNewFile();	
}
// Inserts
void CRelMacroTreeBox::OnInsert() 
{
	GetMainFrame() -> OnDebugInsert();	
}

/////////////////////////////////////////////////////////////////////////////
// Updates
/////////////////////////////////////////////////////////////////////////////
void CRelMacroTreeBox::OnUpdateDebugSave(CCmdUI* pCmdUI) 
{
	GetMainFrame() -> OnUpdateDebugSave(pCmdUI);
}

void CRelMacroTreeBox::OnUpdateDebugSaveas(CCmdUI* pCmdUI) 
{
	GetMainFrame() -> OnUpdateDebugSaveas(pCmdUI);
}

void CRelMacroTreeBox::OnUpdateDebugOpen(CCmdUI* pCmdUI) 
{
	GetMainFrame() -> OnUpdateDebugOpen(pCmdUI); 
}

void CRelMacroTreeBox::OnUpdateDebugNewfile(CCmdUI* pCmdUI) 
{
	GetMainFrame() -> OnUpdateDebugNewFile(pCmdUI); 
}

void CRelMacroTreeBox::OnUpdateDebugRemove(CCmdUI* pCmdUI) 
{
	GetMainFrame() -> OnUpdateDebugRemove(pCmdUI);
}

void CRelMacroTreeBox::OnUpdateDebugImport(CCmdUI* pCmdUI) 
{// Hier immer 
	GetMainFrame() -> OnUpdateDebugImport(pCmdUI);
}
void CRelMacroTreeBox::OnUpdateDebugInsert(CCmdUI* pCmdUI) 
{
	GetMainFrame() -> OnUpdateDebugInsert(pCmdUI);	
}

void CRelMacroTreeBox::InitTree(IObjectManagement *pIObjectManagement, IStreamInfo *pISI)
{
	DeleteAll();
	DeleteAllItems();	
	CreateDefaultTree(pIObjectManagement, pISI);
	EnableWindow(true);
}

CString GetDefaultScript()
{
CString strScript;
CString strDel (GetDefaultName (IDS_DELIMITER));
CString strBegin1 (GetDefaultName(IDS_BEGINSCRIPT1));
CString strBegin2 (GetDefaultName(IDS_BEGINSCRIPT2));
CString strMain (GetDefaultName(IDS_MAINSCRIPT1));
CString strEnd1 (GetDefaultName(IDS_ENDSCRIPT1));
CString strEnd2 (GetDefaultName(IDS_ENDSCRIPT2));
CString strToClose1 (GetDefaultName(IDS_DOCTOCLOSE1));
CString strToClose2 (GetDefaultName(IDS_DOCTOCLOSE2));

	strScript.Format (IDS_DEFAULTSCRIPT, 
		(LPCSTR)strDel, (LPCSTR)strBegin1, (LPCSTR)strBegin2, 
		(LPCSTR)strDel, (LPCSTR)strMain, 
		(LPCSTR)strDel, (LPCSTR)strEnd1, (LPCSTR)strEnd2, 
		(LPCSTR)strDel, (LPCSTR)strToClose1, (LPCSTR)strToClose2);
	return strScript;
}

CString GetFilterDefaultScript()
{
CString strScript;
CString strDel (GetDefaultName (IDS_DELIMITER));
CString strBegin1 (GetDefaultName(IDS_BEGINFILTER1));
CString strBegin2 (GetDefaultName(IDS_BEGINFILTER2));
CString strMain1 (GetDefaultName(IDS_MAINFILTER1));
CString strMain2 (GetDefaultName(IDS_MAINFILTER2));
CString strEnd1 (GetDefaultName(IDS_ENDFILTER1));
CString strEnd2 (GetDefaultName(IDS_ENDFILTER2));

	strScript.Format (IDS_FILTERDEFAULTSCRIPT, 
		(LPCSTR)strDel, (LPCSTR)strBegin1, (LPCSTR)strBegin2, 
		(LPCSTR)strDel, (LPCSTR)strMain1,  (LPCSTR)strMain2, 
		(LPCSTR)strDel, (LPCSTR)strEnd1, (LPCSTR)strEnd2); 
	return strScript;
}

CString GetPropertyDefaultScript()
{
CString strScript;
CString strDel (GetDefaultName (IDS_DELIMITER));
CString strBegin1 (GetDefaultName(IDS_BEGINPROP1));
CString strBegin2 (GetDefaultName(IDS_BEGINPROP2));
CString strMain1 (GetDefaultName(IDS_MAINPROP1));
CString strMain2 (GetDefaultName(IDS_MAINPROP2));
CString strCum1 (GetDefaultName(IDS_CUMULATEPROP1));
CString strCum2 (GetDefaultName(IDS_CUMULATEPROP2));

	strScript.Format (IDS_OBJFEATUREDEFAULTSCRIPT, 
		(LPCSTR)strDel, (LPCSTR)strBegin1, (LPCSTR)strBegin2, 
		(LPCSTR)strDel, (LPCSTR)strMain1,  (LPCSTR)strMain2, 
		(LPCSTR)strDel, (LPCSTR)strCum1,  (LPCSTR)strCum2);
	return strScript;
}
