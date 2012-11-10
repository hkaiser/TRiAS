///////////////////////////////////////////////////////////////////////////
// @doc 
// @module SelOPrpTree.h | Ein TreeViewCtrl, mit welchem Objekteigenschaften 
// ausgewählt werden können

#if !defined(_SELOPRPTREE_H__8FB5DAD5_E4BD_11D1_8610_00600875138A__INCLUDED_)
#define _SELOPRPTREE_H__8FB5DAD5_E4BD_11D1_8610_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
#if !defined(_DEFINED_OBJECTPROPS)
DefineSmartInterface(ObjectProperty);
DefineSmartInterface(ObjectProps);
#define _DEFINED_OBJECTPROPS
#endif // _DEFINED_OBJECTPROPS

/////////////////////////////////////////////////////////////////////////////
// 
class CSelectObjectPropTree : 
	public CTreeViewCtrl 
{
private:
	WObjectProps m_Props;	// hält IObjectProps fest

	typedef map<os_string, HTREEITEM, less<os_string> > CItemMap;
	CItemMap m_Items;
	CImageList m_ilProps;

protected:
	HTREEITEM CalcSubGroupItem (HTREEITEM hParent, LPCSTR pSubGroup);
	HTREEITEM CalcParentItem (string &strGroup);

	HTREEITEM FindItem (HTREEITEM hItem, LPCSTR pcItem);
	HTREEITEM FindString (LPCSTR pcItem);

	int GetImageIndex (DWORD dwFlags);

public:
// Konstruktor/Destruktor/Initialisierung
		CSelectObjectPropTree (pDialogWindow pW, ResID uiRes, 
				 ResourceFile &rRF, IObjectProps *pIProps);
		~CSelectObjectPropTree (void);
		
	bool InitControl (void);
	bool SelectObjProp (LPCSTR pcObjProp);
};

#endif // !defined(_SELOPRPTREE_H__8FB5DAD5_E4BD_11D1_8610_00600875138A__INCLUDED_)
