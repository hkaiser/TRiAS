// Ein TreeViewCtrl, mit welchem Objekteigenschaften ausgewählt werden können -
// File: SELOPRPT.CXX

#include "featurep.hxx"

#include "propname.hxx"
#include "seloprpt.hxx"

static char s_cbPropInfo[_MAX_PATH];

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CSelObjPropTree :: CSelObjPropTree (pDialogWindow pW, ResID uiRes,
				    ResourceFile &rRF, IObjectProps *pIProps)
		 : CTreeViewCtrl (pW, uiRes), m_Props(pIProps)
{
}

CSelObjPropTree :: ~CSelObjPropTree (void)
{
}

bool CSelObjPropTree :: InitControl (void)
{
	if (!Control::FInit()) return false;		// Initialisieren

	m_Items.erase();

// Objekteigenschaften in Gruppen sortiert im Baum einhängen
HRESULT hr = m_Props -> OnNewReferenceObject (0L);	// alle ObjProps installieren

	if (FAILED(hr)) return hr;

WEnumObjProps IEnum;

	hr = m_Props -> EnumObjectProps (IEnum.ppi());
	if (FAILED(hr)) return hr;

// Objekteigenschaften durchgehen
WObjectProperty IProp;

	for (IEnum -> Reset(); 
	     S_OK == IEnum -> Next (1, (IUnknown **)IProp.ppi(), NULL); /**/)
	{
	// vollständigen Namen geben lassen
		IProp -> GetPropInfo (s_cbPropInfo, sizeof(s_cbPropInfo), NULL);

	// ParentItem der Property aus dem Baum besorgen
	CPropertyName PropName (s_cbPropInfo);
	HTREEITEM hParent = CalcParentItem (PropName.GetGroup());
	os_string rstr = PropName.GetSubGroup();

		if (0 != rstr.size()) {
		HTREEITEM hSubGroup = CalcSubGroupItem (hParent, rstr.c_str());

			if (NULL != hSubGroup)
				InsertItem (PropName.GetName().c_str(), hSubGroup);
			else 
				InsertItem (PropName.GetName().c_str(), hParent);
		} else 
			InsertItem (PropName.GetName().c_str(), hParent);
	}

return true;
}

// Finden des ParentItems im Control, ansonsten TVI_ROOT liefern --------------
HTREEITEM CSelObjPropTree :: CalcParentItem (os_string &strGroup)
{
HTREEITEM hItem;
CItemMap::const_iterator it = m_Items.find (strGroup);

	if (it == m_Items.end()) {
	// erstes mal
		hItem = InsertItem (strGroup.c_str(), TVI_ROOT);
		m_Items.insert (make_pair(strGroup, hItem));
	} else
		hItem = (*it).second;

return hItem;
}

// Finden bzw. hinzufügen eines GruppenItems zu einem Parent ------------------
HTREEITEM CSelObjPropTree::CalcSubGroupItem (HTREEITEM hParent, LPCSTR pcSubGroup)
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
