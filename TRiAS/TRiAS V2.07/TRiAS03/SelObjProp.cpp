// Ein TreeViewCtrl, mit welchem Objekteigenschaften ausgewählt werden können -
// File: SelObjProp.cpp

#include "trias03p.hxx"
#include "trias03.h"

#include <xtsnguid.h>
#include <propname.hxx>
#include <eieruhr.hxx>

#include "SelObjProp.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DefineSmartInterface(EnumObjProps);

extern char g_pDLLName[_MAX_PATH];

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CSelObjPropTree :: CSelObjPropTree (pDialogWindow pW, ResID uiRes, IObjectProps *pIProps)
		 : ControlWindow (new CTreeViewCtrl(pW, uiRes)), m_Props(pIProps)
{
	m_fHasSelectedItem = false;
}

CSelObjPropTree :: ~CSelObjPropTree (void)
{
// ImageList wird vom Destruktor ~CImageList freigegeben, hier 
// doppeltes Freigeben verhindern
CImageList *pIL = GetTree()->SetImageList (NULL, TVSIL_NORMAL);
	
	if (pIL) delete pIL;

	if (NULL != GetControl())
		delete (CTreeViewCtrl *)GetControl();
}

bool CSelObjPropTree::InitControl (string &rStr)
{
	if (NULL == GetControl())
		return false;		// Initialisieren

#if defined(ListView_GetExtendedListViewStyle)
//	SetStyle (TVS_TRACKSELECT, true);
#endif // ListView_GetExtendedListViewStyle
	if (!FInit()) 
		return false;

ResourceFile RF (g_pDLLName);

	m_ilProps.CreateList (ResID(IDB_OBJPROPTYPES, &RF), 16, 0, RGB(255, 0, 255));
	m_Items.erase();

// ImageList zuweisen
CImageList *pIL = GetTree()->SetImageList (&m_ilProps, TVSIL_NORMAL);
	
	if (pIL) delete pIL;

// Objekteigenschaften in Gruppen sortiert im Baum einhängen
CEierUhr Wait(GetParent());
WEnumObjProps IEnum;
HRESULT hr = m_Props -> EnumObjectProps (IEnum.ppi());

	if (FAILED(hr)) return hr;

// Objekteigenschaften durchgehen
WObjectProperty IProp;
char cbPropInfo[_MAX_PATH];
HTREEITEM hToSelect = NULL;

	for (IEnum -> Reset(); 
	     S_OK == IEnum -> Next (1, (IUnknown **)IProp.ppi(), NULL); /**/)
	{
	// vollständigen Namen geben lassen
	DWORD dwFlags = 0L;

		hr = IProp -> GetPropInfo (cbPropInfo, sizeof(cbPropInfo), &dwFlags);
		if (FAILED(hr) || dwFlags & PROPCAPS_INTERACTIVE)
			continue;		// keine interaktive ObjProps anzeigen

	// ParentItem der Property aus dem Baum besorgen
	CPropertyName PropName (cbPropInfo);
	HTREEITEM hParent = CalcParentItem (PropName.GetGroup().c_str());
	string rstr = PropName.GetSubGroup();
	HTREEITEM hNewItem = NULL;

		if (0 != rstr.length()) {
		HTREEITEM hSubGroup = CalcSubGroupItem (hParent, rstr.c_str());

			if (NULL != hSubGroup)
				hNewItem = GetTree()->InsertItem (PropName.GetName().c_str(), hSubGroup);
			else 
				hNewItem = GetTree()->InsertItem (PropName.GetName().c_str(), hParent);
		} else 
			hNewItem = GetTree()->InsertItem (PropName.GetName().c_str(), hParent);

		if (PropName.hasSubGroup()) {
		string strName = PropName.GetSubGroup() + '\\' + PropName.GetName();

			if (strName == rStr)
				hToSelect = hNewItem;
		} else if (PropName.GetName() == rStr)
			hToSelect = hNewItem;

	int iIndex = GetImageIndex (dwFlags);

		GetTree()->SetItemImage (hNewItem, iIndex, iIndex);
	}

	if (NULL != hToSelect) {
		GetTree() -> SelectSetFirstVisible (hToSelect);
		GetTree() -> SelectItem (hToSelect);
		m_fHasSelectedItem = true;
	}

return true;
}

///////////////////////////////////////////////////////////////////////////////
// Index im ImageList aus Flags herausfinden
int CSelObjPropTree::GetImageIndex (DWORD dwFlags)
{
	if (dwFlags & PROPCAPS_OBJPROPTYPE_INTEGER)
		return IMG_INTEGERPROP;
	if (dwFlags & PROPCAPS_OBJPROPTYPE_DOUBLE)
		return IMG_DOUBLEPROP;
	if (dwFlags & PROPCAPS_OBJPROPTYPE_BOOL)
		return IMG_BOOLPROP;
	if (dwFlags & PROPCAPS_OBJPROPTYPE_DATE)
		return IMG_DATUMPROP;

return IMG_TEXTPROP;
}

///////////////////////////////////////////////////////////////////////////////
// Mouse wurde geklickt
void CSelObjPropTree::MouseButtonUp (MouseEvt e)
{
	if (e.isLeftButton()) 
		PostMessage (GetParent()->Handle(), WM_ITEMSELECTED, 0, 0);
	ControlWindow::MouseButtonUp(e);
}

void CSelObjPropTree::MouseButtonDn (MouseEvt e)
{
	if (e.isLeftButton()) {
	Point pt = e.Where();
	Rectangle rc = WindowRect();

		if (!rc.PtInRect (pt))
			PostMessage (GetParent()->Handle(), WM_CANCELDIALOG, 0, 0);
		else
			m_fHasSelectedItem = false;
	}
	ControlWindow::MouseButtonDn(e);
}

///////////////////////////////////////////////////////////////////////////////
// Finden des ParentItems im Control, ansonsten TVI_ROOT liefern 
HTREEITEM CSelObjPropTree::CalcParentItem (LPCSTR pcGroup)
{
HTREEITEM hItem;
os_string strGroup (pcGroup);
CItemMap::const_iterator it = m_Items.find (strGroup);

	if (it == m_Items.end()) {
	// erstes mal
		hItem = GetTree()->InsertItem (pcGroup, TVI_ROOT);
		GetTree()->SetItemImage (hItem, IMG_FOLDER, IMG_FOLDER);

		m_Items.insert (make_pair(strGroup, hItem));
	} else
		hItem = (*it).second;

return hItem;
}

// Finden bzw. hinzufügen eines GruppenItems zu einem Parent ------------------
HTREEITEM CSelObjPropTree::CalcSubGroupItem (HTREEITEM hParent, LPCSTR pcSubGroup)
{
HTREEITEM hChild = GetTree()->GetChildItem (hParent);

	while (NULL != hChild) {
	string str = GetTree()->GetItemText (hChild);

		if (str == pcSubGroup) 
			return hChild;		// SubGroup gibt es schon

		hChild = GetTree()->GetNextItem (hChild, TVGN_NEXT);
	}

// nichts gefunden, also neue SubGroup einfügen
HTREEITEM hNewItem = GetTree()->InsertItem (pcSubGroup, hParent);
	
	if (NULL != hNewItem)
		GetTree()->SetItemImage (hNewItem, IMG_FOLDER, IMG_FOLDER);

	return hNewItem;
}

///////////////////////////////////////////////////////////////////////////////
// MessageReflection
void CSelObjPropTree::OnSelChanged (NotifyEvt)
{
}

void CSelObjPropTree::OnItemExpanded (NotifyEvt e)
{
NM_TREEVIEW *pnmtv = (NM_TREEVIEW *)e.GetNotifyInfo();
HTREEITEM hItem = pnmtv -> itemNew.hItem;

	AdjustParentImage (hItem);
}

// Bildchen an Parents richten ------------------------------------------------
void CSelObjPropTree::AdjustParentImage (HTREEITEM hItem)
{
	if (!GetTree()->ItemHasChildren (hItem)) 
		return;		// nur Parents behandeln

	if (GetTree()->GetItemState (hItem, TVIS_EXPANDED) & TVIS_EXPANDED) 
		GetTree()->SetItemImage (hItem, IMG_OPENFOLDER, IMG_OPENFOLDER);	// ist expandiert
	else
		GetTree()->SetItemImage (hItem, IMG_FOLDER, IMG_FOLDER);	// ist collabiert
}

HRESULT CSelObjPropTree::GetSelectedObjProp (string &rStrSelected, string *pStrFull)
{
// neues Item besorgen (vollständigen ObjPropName)
HTREEITEM hItem;
string str;

	hItem = GetTree()->GetSelectedItem();
	if (NULL == hItem) {
		TX_ASSERT(NULL == hItem);
		return E_UNEXPECTED;
	}

// wenn ein hChild da ist, dann einfach weitermachen
HTREEITEM hChild = GetTree()->GetChildItem (hItem);

	if (NULL != hChild) return S_FALSE;

// gültiges Item
HTREEITEM hParent = GetTree()->GetParentItem (hItem);

	if (NULL == hParent) {
		TX_ASSERT(NULL == hItem);
		return E_UNEXPECTED;
	}

int iLoop = 0;
string strSubGroup;

	do {
	string strT = GetTree()->GetItemText (hParent);

		strSubGroup = str;
		str = strT + '\\' + str;
		hParent = GetTree()->GetParentItem (hParent);
		iLoop++;
	} while (NULL != hParent);
	
	if (NULL != pStrFull)
		*pStrFull = "OBJPROP_ROOT\\" + str;
	
	if (iLoop > 1)	// mit subgroup ?
		rStrSelected = strSubGroup + GetTree()->GetItemText (hItem);
	else
		rStrSelected = GetTree()->GetItemText (hItem);

	return S_OK;
}


