// Ein TreeViewCtrl, mit welchem Objekteigenschaften ausgewählt werden können -
// File: SELOPRPTREE.CPP

#include "trias03p.hxx"
#include "trias03.h"

#include <eieruhr.hxx>

#include "propname.hxx"
#include "SelObjProp.h"		// ImageListIndizies
#include "SelOPrpTree.h"

extern char g_pDLLName[_MAX_PATH];

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(EnumObjProps);			// WEnumObjProps

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CSelectObjectPropTree::CSelectObjectPropTree (
	pDialogWindow pW, ResID uiRes, ResourceFile &rRF, IObjectProps *pIProps)
		 : CTreeViewCtrl (pW, uiRes), m_Props(pIProps)
{
}

CSelectObjectPropTree::~CSelectObjectPropTree (void)
{
// ImageList wird vom Destruktor ~CImageList freigegeben, hier 
// doppeltes Freigeben verhindern
CImageList *pIL = SetImageList (NULL, TVSIL_NORMAL);
	
	if (pIL) delete pIL;
}

bool CSelectObjectPropTree::InitControl (void)
{
	if (!Control::FInit()) return false;		// Initialisieren

ResourceFile RF (g_pDLLName);

	m_ilProps.CreateList (ResID(IDB_OBJPROPTYPES, &RF), 16, 0, RGB(255, 0, 255));
	m_Items.erase();

// ImageList zuweisen
CImageList *pIL = SetImageList (&m_ilProps, TVSIL_NORMAL);
	
	if (pIL) delete pIL;
	m_Items.erase();

// Objekteigenschaften in Gruppen sortiert im Baum einhängen
CEierUhr Wait (GetParent());
HRESULT hr = m_Props -> OnNewReferenceObject (0L);	// alle ObjProps installieren

	if (FAILED(hr)) return false;
	DEX_SetMustInitOPFs(FALSE);

WEnumObjProps Enum;

	hr = m_Props -> EnumObjectProps (Enum.ppi());
	if (FAILED(hr)) return hr;

// Objekteigenschaften durchgehen
WObjectProperty Prop;
char cbPropInfo[_MAX_PATH];

	for (Enum -> Reset(); 
	     S_OK == Enum -> Next (1, Prop.ppu(), NULL); /**/)
	{
	// vollständigen Namen geben lassen
	DWORD dwFlags = 0L;

		hr = Prop -> GetPropInfo (cbPropInfo, sizeof(cbPropInfo), &dwFlags);
		if (FAILED(hr) || dwFlags & PROPCAPS_INTERACTIVE)
			continue;		// keine interaktive ObjProps anzeigen

	// ParentItem der Property aus dem Baum besorgen
	CPropertyName PropName (cbPropInfo);
	HTREEITEM hParent = CalcParentItem (PropName.GetGroup());
	string rstr = PropName.GetSubGroup();
	HTREEITEM hNewItem = NULL;

		if (0 != rstr.length()) {
		HTREEITEM hSubGroup = CalcSubGroupItem (hParent, rstr.c_str());

			if (NULL != hSubGroup)
				hNewItem = InsertItem (PropName.GetName().c_str(), hSubGroup);
			else 
				hNewItem = InsertItem (PropName.GetName().c_str(), hParent);
		} else 
			hNewItem = InsertItem (PropName.GetName().c_str(), hParent);

	int iIndex = GetImageIndex (dwFlags);

		SetItemImage (hNewItem, iIndex, iIndex);
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Index im ImageList aus Flags herausfinden
int CSelectObjectPropTree::GetImageIndex (DWORD dwFlags)
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

// Finden des ParentItems im Control, ansonsten TVI_ROOT liefern --------------
HTREEITEM CSelectObjectPropTree::CalcParentItem (string &strGroup)
{
HTREEITEM hItem;
CItemMap::const_iterator it = m_Items.find (strGroup.c_str());

	if (it == m_Items.end()) {
	// erstes mal
		hItem = InsertItem (strGroup.c_str(), TVI_ROOT);
		m_Items.insert (make_pair(os_string(strGroup.c_str()), hItem));
	} else
		hItem = (*it).second;

	return hItem;
}

// Finden bzw. hinzufügen eines GruppenItems zu einem Parent ------------------
HTREEITEM CSelectObjectPropTree::CalcSubGroupItem (HTREEITEM hParent, LPCSTR pcSubGroup)
{
HTREEITEM hChild = GetChildItem (hParent);

	while (NULL != hChild) {
	string str = GetItemText (hChild);

		if (str == pcSubGroup) 
			return hChild;		// SubGroup gibt es schon

		hChild = GetNextItem (hChild, TVGN_NEXT);
	}

// nichts gefunden, also neue SubGroup einfügen
	return InsertItem (pcSubGroup, hParent);
}

// Eine bestimmte Objekteigenschaft vorselektieren
bool CSelectObjectPropTree::SelectObjProp (LPCSTR pcObjProp)
{
HTREEITEM hItem = FindString (pcObjProp);

	if (NULL == hItem)
		return false;

	SelectSetFirstVisible (hItem);
	SelectItem (hItem);
	return true;
}

HTREEITEM CSelectObjectPropTree::FindItem (HTREEITEM hItem, LPCSTR pcItem)
{
	if (NULL == hItem) return NULL;

// wenn's das RootItem ist, dann erstes Child geben lassen
HTREEITEM hChildItem = NULL;

	if (TVI_ROOT == hItem)
		hChildItem = GetNextItem (NULL, TVGN_CHILD);
	else {
	// zuerst dieses Item testen (die Root kann's nicht sein)
	string strItem = GetItemText (hItem);

		if (strItem == pcItem)
			return hItem;

		hChildItem = GetChildItem (hItem);
	}

// anschließen alle Childs abtesten
	while (NULL != hChildItem) {
	HTREEITEM hReturn = FindItem (hChildItem, pcItem);

		if (NULL != hReturn)
			return hReturn;
		hChildItem = GetNextItem (hChildItem, TVGN_NEXT);
	}
	return NULL;	// nichts gefunden
}

HTREEITEM CSelectObjectPropTree::FindString (LPCSTR pcItem)
{
	return FindItem (TVI_ROOT, pcItem);
}

