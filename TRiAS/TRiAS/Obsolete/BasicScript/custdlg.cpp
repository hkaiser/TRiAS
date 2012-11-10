// custdlg.cpp : implementation file
//
#include "bscriptp.hxx"

#include "bscript.h"

#include "macrguid.h"
#include "imacorg.h"
#include "imacro.h"

#include "custdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MIN_SEPARATORID  0xA000

HRESULT LoadStorageMenuItems(LPUNKNOWN pUnk);
HRESULT LoadStorageMacroScripts(LPUNKNOWN pUnk);

/////////////////////////////////////////////////////////////////////////////
// CCustDlg property page

IMPLEMENT_DYNCREATE(CCustDlg, CPropertyPage)

CCustDlg* CCustDlg::CreateInstance ()
{
	CCustDlg* pCust = new CCustDlg ();
	if (NULL == pCust) return NULL;

return pCust;
}

CCustDlg::CCustDlg() 
	: CPropertyPage(CCustDlg::IDD), 
		m_strOldMenuEntry()
{
	//{{AFX_DATA_INIT(CCustDlg)
	//}}AFX_DATA_INIT
	Reset();
	GetInterfaces();
}

void CCustDlg::GetInterfaces()
{
	m_ISC = ((CMacroScriptExtension *)g_pTE) -> GetMacroScripts();
	m_IA = ((CMacroScriptExtension *)g_pTE) -> GetMacroOrg();
}

CCustDlg::~CCustDlg()
{
}

void CCustDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustDlg)
	DDX_Control(pDX, IDC_MENUTREE, m_trMenuItem);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDC_RECHTS, m_Rechts);
	DDX_Control(pDX, IDC_LOESCHEN, m_Loeschen);
	DDX_Control(pDX, IDC_EINFUEGEN, m_Einfuegen);
	DDX_Control(pDX, IDC_LINKS, m_Links);
	DDX_Control(pDX, IDC_MACROLIST, m_cbProjectMacros);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CCustDlg)
	ON_BN_CLICKED(IDC_EINFUEGEN, OnEinfuegen)
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_MENUTREE, OnBeginlabeleditMenutree)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_MENUTREE, OnEndlabeleditMenutree)
	ON_BN_CLICKED(IDC_LOESCHEN, OnLoeschen)
	ON_CBN_SELCHANGE(IDC_MACROLIST, OnSelChangeMacroList)
	ON_NOTIFY(TVN_SELCHANGED, IDC_MENUTREE, OnSelchangedMenutree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustDlg message handlers

BOOL CCustDlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
HRESULT hr = LoadStorageMacroScripts(m_ISC);
// wenn Storage schon geöffnet	
	if (FAILED(hr) && GetScode(hr) != STG_E_ACCESSDENIED) return false; 

	hr = FillLists();
	if (FAILED(hr)) return false; 

	m_trMenuItem.SelectItem(m_trMenuItem.GetFirstVisibleItem());
	m_trMenuItem.SetFocus();
	m_Einfuegen.EnableWindow(false);

return false;  // return TRUE unless you set the focus to a control
}	              // EXCEPTION: OCX Property Pages should return FALSE

bool CCustDlg::SetMenuEntry(HTREEITEM hItem)
{
ITEMDATA *pID = (ITEMDATA *)m_trMenuItem.GetItemData(hItem);
	if (NULL == pID) return false;

	if (pID -> flags == CUSTFLAGS_EDIT) {
		
	CString str = m_trMenuItem.GetItemText(hItem);
	HRESULT hr = m_IA -> SetNewMenuEntry(pID->uiID, str);
		if (FAILED(hr)) return false;

		m_fSave = true;
	}
	
return true;
}

bool CCustDlg::Delete()
{
vector<int>::iterator it;
	
	for (it = vID.begin(); it != vID.end(); it++) {

	HRESULT hr = m_IA -> DeleteItem(*it);
		if (FAILED(hr)) return false;

		m_fSave = true;	
	}

return true;
}

bool CCustDlg::SetNewMenu(HTREEITEM hItem)
{	
ITEMDATA *pID = (ITEMDATA *)m_trMenuItem.GetItemData(hItem);	
	if (NULL == pID) return false;

	if (pID -> flags == CUSTFLAGS_NEWMACRO) {

	CString str = m_trMenuItem.GetItemText(hItem); 
	UINT uiPreID = 0, uiSucID = 0, uiNewID = 0;

		if (!GetEnvItems(uiPreID, uiSucID, hItem)) return false;

	HRESULT hr = m_IA -> SetNewMenu(	uiPreID, uiSucID, uiNewID, 
										pID -> strMacroText, str,
										true);
		if (FAILED (hr) || 0==uiNewID) return false;
		
		pID -> uiID = uiNewID;
		m_trMenuItem.SetItemData(hItem, (DWORD)pID);

		m_fSave = true;
	}

return true;
}

bool CCustDlg::CustomizeMenu(HTREEITEM hItem)
{
	while (hItem) { 
	
	HTREEITEM hItemChild = NULL;
		if (hItemChild = m_trMenuItem.GetChildItem(hItem)) {
			if ( ! CustomizeMenu(hItemChild) ) return false;
		}

		if ( ! SetNewMenu(hItem) /*|| ! Delete(hItem) */|| ! SetMenuEntry(hItem) ) 
			return false;

		hItem = m_trMenuItem.GetNextSiblingItem(hItem);
	}  
return true;
}

bool CCustDlg::ResetItems(HTREEITEM hItem)
{
	while (hItem) { 
	
	HTREEITEM hItemChild = NULL;
		if (hItemChild = m_trMenuItem.GetChildItem(hItem)) {
			if ( ! ResetItems(hItemChild) ) return false;
		}

	ITEMDATA *pID = (ITEMDATA *)m_trMenuItem.GetItemData(hItem);
		if (pID) delete pID;		

		hItem = m_trMenuItem.GetNextSiblingItem(hItem);
	}  
return true;
}

bool CCustDlg::Save()
{
	try {
	WSave ISv(m_IA);
	HRESULT hr = NOERROR;
	LPSTORAGE pIS = NULL;
		
		if(NULL == DEX_GetProjectStorage(pIS)) {
			hr = ISv -> SaveFile();
			if (FAILED(hr)) return false;
		}
		else {
			pIS -> Release();
			hr = ISv -> SaveToStorage(true);
			// für späteres Commit()		
			if (FAILED(hr)) return false;
			DEX_SetDirtyGeoDB(1);
		}
	} catch (HRESULT) {
		return false; 
	}

return true;
}

void CCustDlg::OnOK() 
{
HTREEITEM hItem = m_trMenuItem.GetRootItem();

	if (!Delete()) return; 		

	if (!m_trMenuItem.ItemHasChildren(hItem) || ! CustomizeMenu(hItem) || ! ResetItems(hItem) )
		return; 
  	
	if (m_fSave) {
// Menüitems Storage laden	
	HRESULT hr = LoadStorageMenuItems(m_IA);

		if (FAILED(hr) && GetScode(hr) != STG_E_ACCESSDENIED && GetScode(hr) != E_UNEXPECTED) 
			return; 

		if (!Save()) return;
	}

	Reset();

	CPropertyPage::OnOK();
}

void CCustDlg::Reset()
{
	m_strOldMenuEntry.Empty();
	m_fSave = false; 
}

void CCustDlg::OnCancel() 
{
HTREEITEM hItem = m_trMenuItem.GetRootItem();
	if ( ! m_trMenuItem.ItemHasChildren(hItem) ) return;
	if ( ! ResetItems(hItem) ) return;
	Reset();
	CPropertyPage::OnCancel();
}

DWORD  CCustDlg::GetDataSelectedItem()
{
return m_trMenuItem.GetItemData(m_trMenuItem.GetSelectedItem());
}

HTREEITEM CCustDlg::GetParentNextVisible()
{
return m_trMenuItem.GetParentItem((m_trMenuItem.GetNextVisibleItem(m_trMenuItem.GetSelectedItem())));
}

HTREEITEM CCustDlg::GetParentSelectedItem()
{
return m_trMenuItem.GetParentItem(m_trMenuItem.GetSelectedItem());
}

CString CCustDlg :: GetTextSelectedItem()
{
return m_trMenuItem.GetItemText(m_trMenuItem.GetSelectedItem());
}

bool CCustDlg::GetEnvItems(UINT &uiPreID, UINT &uiSucID, HTREEITEM hItemIn)
{
HTREEITEM hItem = m_trMenuItem.GetNextSiblingItem(hItemIn);
ITEMDATA *pID  = NULL;

	while (hItem) {
	
		pID = (ITEMDATA *)m_trMenuItem.GetItemData(hItem);	
		if (pID == NULL) return false;

		if (pID -> flags != CUSTFLAGS_NEWMACRO) {
		
			uiPreID = 0;
			uiSucID = pID -> uiID;
			if (uiSucID > 0) return true;
		}

		hItem = m_trMenuItem.GetNextSiblingItem(hItem);
	}

	hItem = m_trMenuItem.GetPrevSiblingItem(hItemIn);
	
	//letztes Item einer Menüliste eines Levels
	pID = (ITEMDATA *)m_trMenuItem.GetItemData(hItem);	
	if (pID == NULL) return false;

	uiPreID = pID -> uiID;
	uiSucID = 0;

return true;
}

bool CCustDlg::OnEinfuegenInTree()
{
	m_trMenuItem.Expand(m_trMenuItem.GetSelectedItem(), TVE_EXPAND);

TV_INSERTSTRUCT InsertStruct;
	if ( m_trMenuItem.GetSelectedItem() == GetParentNextVisible() ){
		InsertStruct.hParent = m_trMenuItem.GetSelectedItem();
		InsertStruct.hInsertAfter = TVI_FIRST;	
	}
	else {
		InsertStruct.hParent = GetParentSelectedItem();
		InsertStruct.hInsertAfter = m_trMenuItem.GetSelectedItem();	
	}

TV_ITEM   item;
char c[MAXSTRLENGTH];
	m_cbProjectMacros.GetWindowText (c, MAXSTRLENGTH);
	item.mask = TVIF_TEXT ;
	item.pszText = c;
	item.cchTextMax = MAXSTRLENGTH;

	InsertStruct.item = item;

HTREEITEM hItem = m_trMenuItem.InsertItem (&InsertStruct);
	if (NULL == hItem) return false;
	if ( ! m_trMenuItem.SelectItem(hItem) )	return false;

ITEMDATA *pID = new ITEMDATA;
	if (NULL == pID) return false;

		pID -> flags = CUSTFLAGS_NEWMACRO;
		pID -> strMacroText = c;
		pID -> uiID = 0;
	if ( ! m_trMenuItem.SetItemData(hItem, (DWORD)pID) ) return false;

	if(NULL == m_trMenuItem.EditLabel(hItem)) return false;		

return true;
}

void CCustDlg::OnLoeschen() 
{
ITEMDATA *pID = (ITEMDATA *)GetDataSelectedItem();

	ASSERT(pID);

	if (pID -> flags != CUSTFLAGS_NEWMACRO) 
		vID.push_back(pID->uiID);

	m_trMenuItem.DeleteItem(m_trMenuItem.GetSelectedItem());
	m_trMenuItem.SelectItem(m_trMenuItem.GetRootItem()); 
}

void CCustDlg::OnEinfuegen() 
{
	OnEinfuegenInTree();
}			

void CCustDlg::OnBeginlabeleditMenutree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;

ITEMDATA *pID = (ITEMDATA *)pTVDispInfo -> item.lParam;
CString str = pTVDispInfo -> item.pszText;
	if (str.IsEmpty() || NULL == pID) { *pResult = 1; return; }

	m_strOldMenuEntry = str; 
	
	*pResult = 0; 
}

void CCustDlg::OnEndlabeleditMenutree(NMHDR* pNMHDR, LRESULT* pResult) 
{
TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;

	ASSERT(NULL != pTVDispInfo);
	if (NULL == pTVDispInfo) return; 		
	
CString str = pTVDispInfo -> item.pszText;
	if (str.IsEmpty() || m_strOldMenuEntry == str) return;

ITEMDATA *pID = (ITEMDATA *) pTVDispInfo -> item.lParam;

	ASSERT(NULL != pID);
	if (NULL == pID) return;

	if (! m_trMenuItem.SetItemText(pTVDispInfo -> item.hItem, str) ) {
		*pResult = 1; return; 		
	}

	if (pID -> flags == CUSTFLAGS_NEWMACRO) return; 

	pID -> flags = CUSTFLAGS_EDIT; 

	if (! m_trMenuItem.SetItemData(pTVDispInfo -> item.hItem, (DWORD)pID) ) { 
		*pResult = 1; return; 
	}		


	*pResult = 0;
}

HRESULT CCustDlg::FillLists()
{
HRESULT hr = m_IA -> ReadMenu((CWnd *)&m_trMenuItem);	
	if (FAILED(hr)) return hr;

	hr = Fill((CWnd *)&m_cbProjectMacros, 1, m_ISC);
	if (FAILED(hr)) return hr;

return NOERROR;
}

//////////////////////////////////////////////////////////////////////
// *** global functions:


HRESULT Fill(CWnd *pWnd, bool fCB, IScriptContainer * pISC)
{
IEnumScripts *pEnumScripts;  
// pEnumScripts -> AddRef()
HRESULT hr  = pISC -> GetEnumScripts (&pEnumScripts);  
	if (FAILED(hr)) return hr; 

	pEnumScripts -> Reset();

LPUNKNOWN pUnk = NULL;                                                
	
// Next() macht pUnk -> AddRef()
	while (S_OK == pEnumScripts -> Next (1, &pUnk, NULL)) {
	
	IScript *pIScript = NULL;	
	char cName[MAXSTRLENGTH];
		
		hr = pUnk -> QueryInterface (IID_IScript, (LPVOID *)&pIScript);
//	 von Next() 
		pUnk -> Release();
		if (SUCCEEDED(hr)) {
			hr = pIScript -> GetName (cName, MAXSTRLENGTH);
			pIScript -> Release();

		DWORD dwInfo = 0;
			
			hr = pISC -> GetScriptInfo(cName, &dwInfo);
			if (FAILED(hr)) {
				pEnumScripts -> Release();
				return hr;
			}

			if(fCB) { 
				if (dwInfo & CC_CODE) 
					((CComboBox *)pWnd) -> AddString (cName);
			}
			else 
				((CListBox *)pWnd) -> AddString (cName);
		}
		else {
			pEnumScripts -> Release();
			return ResultFromScode (E_FAIL);
		}
	}	
// von Get(pEnumScripts)
	pEnumScripts -> Release();
		
return NOERROR;
}


void CCustDlg::OnSelChangeMacroList() 
{
CString str;
	m_cbProjectMacros.GetWindowText(str);
	if(str.IsEmpty()) m_Einfuegen.EnableWindow(false);
	else m_Einfuegen.EnableWindow(true);
}

void CCustDlg::OnSelchangedMenutree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

ITEMDATA *pID = (ITEMDATA *)GetDataSelectedItem();
	if(pID == NULL) { *pResult=1; return; }

	if (pID->uiID >= MIN_SEPARATORID) m_Loeschen.EnableWindow(false);
	else m_Loeschen.EnableWindow(true);

	*pResult = 0;
}
