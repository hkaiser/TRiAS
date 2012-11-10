// Ein TreeViewCtrl, mit welchem Objekteigenschaften ausgewählt werden können -
// File: SelObjProp.cpp

#include "trias03p.hxx"
#include "trias03.h"

#include <xtsnguid.h>
#include <propname.hxx>
#include <eieruhr.hxx>

#include <SelObjProp.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DefineSmartInterface(EnumObjProps);

extern char g_pDLLName[_MAX_PATH];

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CSelObjPropTree :: CSelObjPropTree (
		pDialogWindow pW, ResID uiRes, IObjectProps *pIProps, 
		INCLUDEOBJPROP pFcn, bool fIsPopUp, bool fCheckMarks, bool fPartialCheckMarks) :
	CCheckTreeView (pW, uiRes, fCheckMarks, fPartialCheckMarks), 
	m_Props(pIProps), m_fIsPopUp(fIsPopUp)
{
	m_fHasSelectedItem = false;
	m_pFcn = pFcn;			// diese Objekteigenschaften nicht anzeigen
}

CSelObjPropTree :: ~CSelObjPropTree (void)
{
// ImageList wird vom Destruktor ~CImageList freigegeben, hier doppeltes Freigeben verhindern
CImageList *pIL = SetImageList (NULL, TVSIL_NORMAL);
	
	DELETE_OBJ(pIL);
}

bool CSelObjPropTree::InitControl (string &rStr)
{
list<os_string> lstT;

	lstT.push_back(rStr);
	return InitControl (lstT);
}

inline 
bool SetContainsString (set<os_string> &rSet, os_string const &rStr)
{
set<os_string>::iterator it = rSet.find(rStr);

	return (it != rSet.end()) ? true : false;
}

bool CSelObjPropTree::InitControl (list<os_string> &rStrs)
{
	if (NULL == GetControl())
		return false;		// Initialisieren

	if (!FInit()) 
		return false;

ResourceFile RF (g_pDLLName);

	m_ilProps.CreateList (ResID(IDB_OBJPROPTYPES, &RF), 16, 0, RGB(255, 0, 255));
	m_Items.erase();

// ImageList zuweisen
CImageList *pIL = SetImageList (&m_ilProps, TVSIL_NORMAL);
	
	DELETE_OBJ(pIL);

// Objekteigenschaften in Gruppen sortiert im Baum einhängen
set<os_string> setStrs;

	copy (rStrs.begin(), rStrs.end(), inserter(setStrs, setStrs.begin()));
	
CEierUhr Wait(GetParent());
WEnumObjProps IEnum;
HRESULT hr = m_Props -> EnumObjectProps (IEnum.ppi());

	if (FAILED(hr)) return hr;

// Objekteigenschaften durchgehen
WObjectProperty IProp;
char cbPropInfo[_MAX_PATH];
HTREEITEM hToSelect = NULL;

	for (IEnum -> Reset(); S_OK == IEnum -> Next (1, (IUnknown **)IProp.ppi(), NULL); /**/)
	{
	// vollständigen Namen geben lassen
	DWORD dwFlags = 0L;

		hr = IProp -> GetPropInfo (cbPropInfo, sizeof(cbPropInfo), &dwFlags);
		if (FAILED(hr) || !m_pFcn(dwFlags))
			continue;		// nur gewünschte ObjProps anzeigen

	// ParentItem der Property aus dem Baum besorgen
	CPropertyName PropName (cbPropInfo);
	HTREEITEM hParent = CalcParentItem (PropName.GetGroup().c_str());
	string rstr (PropName.GetSubGroup());
	HTREEITEM hNewItem = NULL;

		if (0 != rstr.length()) {
		HTREEITEM hSubGroup = CalcSubGroupItem (hParent, rstr.c_str());

			if (NULL != hSubGroup)
				hNewItem = InsertItem (PropName.GetName().c_str(), hSubGroup);
			else 
				hNewItem = InsertItem (PropName.GetName().c_str(), hParent);
		} else 
			hNewItem = InsertItem (PropName.GetName().c_str(), hParent);

	// nachsehen, ob dieses Item vorinitialisiert werden soll
	os_string strFull;

		PropName.GetFullName(strFull);
		if (PropName.hasSubGroup()) {
		string strName (PropName.GetSubGroup() + '\\' + PropName.GetName());

			if (SetContainsString(setStrs, strName) || SetContainsString(setStrs, strFull)) {
				hToSelect = hNewItem;
				if (UseCheckMarks()) 
					SetCheckState(hToSelect, TV_CHECK_ON);
			} else if (UseCheckMarks())
				SetCheckState(hNewItem, TV_CHECK_OFF);
		} 
		else if (SetContainsString(setStrs, PropName.GetName()) || SetContainsString(setStrs, strFull)) {
			hToSelect = hNewItem;
			if (UseCheckMarks()) 
				SetCheckState(hToSelect, TV_CHECK_ON);
		} else if (UseCheckMarks())
			SetCheckState(hNewItem, TV_CHECK_OFF);

	// Images setzen
	int iIndex = m_ilProps.GetImageIndex (dwFlags);

		SetItemImage (hNewItem, iIndex, iIndex);
	}

	if (NULL != hToSelect) {
		SelectSetFirstVisible (hToSelect);
		SelectItem (hToSelect);
		m_fHasSelectedItem = true;
	}
	return true;
}

// Eine bestimmte Objekteigenschaft vorselektieren
bool CSelObjPropTree::SelectObjProp (LPCSTR pcObjProp)
{
HTREEITEM hItem = FindString (pcObjProp);

	if (NULL == hItem)
		return false;

	SelectSetFirstVisible (hItem);
	SelectItem (hItem);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Mouse wurde geklickt
void CSelObjPropTree::MouseButtonUp (MouseEvt e)
{
	if (m_fIsPopUp && e.isLeftButton()) 
		GetParent()->PostEvent (WM_ITEMSELECTED);
	CCheckTreeView::MouseButtonUp(e);
}

void CSelObjPropTree::MouseButtonDn (MouseEvt e)
{
	if (m_fIsPopUp && e.isLeftButton()) {
	Point pt = e.Where();
	Rectangle rc = WindowRect();

		if (!rc.PtInRect (pt))
			GetParent()->PostEvent (WM_CANCELDIALOG);
		else
			m_fHasSelectedItem = false;
	}
	CCheckTreeView::MouseButtonDn(e);
}

void CSelObjPropTree::FocusChange (FocusChangeEvt e)
{
	if (m_fIsPopUp && !e.gotFocus())
		GetParent()->PostEvent (WM_CANCELDIALOG);
	CCheckTreeView::FocusChange(e);
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
		hItem = InsertItem (pcGroup, TVI_ROOT);
		SetItemImage (hItem, IMG_FOLDER, IMG_FOLDER);

		m_Items.insert (make_pair(strGroup, hItem));

		if (UseCheckMarks()) {
			if (UsePartialCheckMarks()) 
				SetCheckState(hItem, TV_CHECK_OFF);
			else
				HideStateImage(hItem);
		}

	} else
		hItem = (*it).second;

	return hItem;
}

// Finden bzw. hinzufügen eines GruppenItems zu einem Parent ------------------
HTREEITEM CSelObjPropTree::CalcSubGroupItem (HTREEITEM hParent, LPCSTR pcSubGroup)
{
HTREEITEM hChild = GetChildItem (hParent);

	while (NULL != hChild) {
	string str (GetItemText (hChild));

		if (str == pcSubGroup) 
			return hChild;		// SubGroup gibt es schon

		hChild = GetNextItem (hChild, TVGN_NEXT);
	}

// nichts gefunden, also neue SubGroup einfügen
HTREEITEM hNewItem = InsertItem (pcSubGroup, hParent);
	
	if (NULL != hNewItem)
		SetItemImage (hNewItem, IMG_FOLDER, IMG_FOLDER);

//	if (UseCheckMarks()) 
//		HideStateImage(hNewItem);

	return hNewItem;
}

///////////////////////////////////////////////////////////////////////////////
// MessageReflection
void CSelObjPropTree::OnSelChanged (NotifyEvt)
{
HTREEITEM hItem = GetSelectedItem();

	if (NULL != hItem && UseCheckMarks()) {
	TV_HITTESTINFO ht;

		GetCursorPos(&ht.pt);
		ScreenToClient(Handle(), &ht.pt);

	HTREEITEM hNewTarget = HitTest (&ht);

		if ((GetItemState (hItem, TVIS_SELECTED) & TVIS_SELECTED) &&
			(hItem == hNewTarget) && !(ht.flags & TVHT_ONITEMSTATEICON))
		{
			SetCheckState(hItem, TV_CHECK_ON);
		}
	}
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
	if (!ItemHasChildren (hItem)) 
		return;		// nur Parents behandeln

	if (GetItemState (hItem, TVIS_EXPANDED) & TVIS_EXPANDED) 
		SetItemImage (hItem, IMG_OPENFOLDER, IMG_OPENFOLDER);	// ist expandiert
	else
		SetItemImage (hItem, IMG_FOLDER, IMG_FOLDER);	// ist collabiert
}

HRESULT CSelObjPropTree::GetSelectedObjProp (string &rStrSelected, string *pStrFull)
{
// neues Item besorgen (vollständigen ObjPropName)
HTREEITEM hItem;

	hItem = GetSelectedItem();
	if (NULL == hItem) {
		TX_ASSERT(NULL == hItem);
		return E_UNEXPECTED;
	}

// wenn ein hChild da ist, dann einfach weitermachen
HTREEITEM hChild = GetChildItem (hItem);

	if (NULL != hChild) return S_FALSE;

// gültiges Item
HTREEITEM hParent = GetParentItem (hItem);

	if (NULL == hParent) {
		TX_ASSERT(NULL == hItem);
		return E_UNEXPECTED;
	}
	
	return GetObjPropName (hItem, rStrSelected, pStrFull);
}

HRESULT CSelObjPropTree::GetObjPropName(HTREEITEM hItem, os_string &rStrSelected, os_string *pStrFull)
{
int iLoop = 0;
os_string strItem (GetItemText (hItem));
os_string str ("");
os_string strSubGroup ("");

	do {
	os_string strT (GetItemText (hItem));

		strSubGroup = str;
		if (iLoop > 0)
			str = strT + '\\' + str;
		else
			str = strT;

		hItem = GetParentItem (hItem);
		iLoop++;
	} while (NULL != hItem);
	
	if (NULL != pStrFull) {
	os_string strT ("OBJPROP_ROOT\\");

		strT += str;
		*pStrFull = strT;
	}
	if (iLoop > 2)	// mit subgroup ?
		rStrSelected = strSubGroup;
	else
		rStrSelected = strItem;

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// liefert alle angehakten Items
HRESULT CSelObjPropTree::GetSelectedObjProps (list<os_string> &rlstObjProps)
{
	return GetSelectedObjProps (TVI_ROOT, rlstObjProps);
}

HRESULT CSelObjPropTree::GetSelectedObjProps (HTREEITEM hItem, list<os_string> &rlstObjProps)
{
	if (NULL == hItem) 
		return S_OK;

// wenn's das RootItem ist, dann erstes Child geben lassen
HTREEITEM hChildItem = NULL;

	if (TVI_ROOT == hItem)
		hChildItem = GetNextItem (NULL, TVGN_CHILD);
	else {
		if (!ItemHasChildren(hItem)) {
		// keine Childnodes mehr, daher nur hier CheckState auswerten
			if (TV_CHECK_ON == GetCheckState(hItem)) {
			os_string strFull, strName;

				if (SUCCEEDED(GetObjPropName(hItem, strName, &strFull))) 
					rlstObjProps.push_back (strFull);
			}
		} else
			hChildItem = GetChildItem (hItem);
	}

// anschließen alle Childs abtesten
	while (NULL != hChildItem) {
	HRESULT hr = GetSelectedObjProps (hChildItem, rlstObjProps);

		if (FAILED(hr)) 
			return hr;
		hChildItem = GetNextItem (hChildItem, TVGN_NEXT);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// nachsehen, ob was selektiert wurde
int CSelObjPropTree::CountSelectedItems (HTREEITEM hItem, int iCnt)
{
	if (NULL == hItem) 
		return iCnt;

// wenn's das RootItem ist, dann erstes Child geben lassen
HTREEITEM hChildItem = NULL;

	if (TVI_ROOT == hItem)
		hChildItem = GetNextItem (NULL, TVGN_CHILD);
	else {
		if (TV_CHECK_ON == GetCheckState(hItem))
			++iCnt;

		hChildItem = GetChildItem (hItem);
	}

// anschließen alle Childs abtesten
	while (NULL != hChildItem) {
		iCnt = CountSelectedItems (hChildItem, iCnt);
		hChildItem = GetNextItem (hChildItem, TVGN_NEXT);
	}
	return iCnt;
}


