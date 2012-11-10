// Ein TreeViewCtrl, mit welchem Objekteigenschaften ausgewählt werden können -
// File: SELOBJPROP.H

#if !defined(_SELOBJPROP_H)
#define _SELOBJPROP_H

#pragma warning (disable: 4786)		// too long identifiers
//#pragma optimize ("", off)			// map nicht optimieren
#include <ospace/std/map>

#if !defined(_DEFINED_OBJECTPROPS)
DefineSmartInterface(ObjectProperty);
DefineSmartInterface(ObjectProps);
#define _DEFINED_OBJECTPROPS
#endif // _DEFINED_OBJECTPROPS

class CSelObjPropTree : 
	public ControlWindow
{
private:
	WObjectProps m_Props;	// hält IObjectProps fest

	typedef map<os_string, HTREEITEM, less<os_string> > CItemMap;
	CItemMap m_Items;
	CImageList m_ilProps;

	bool m_fHasSelectedItem;

protected:
	int GetImageIndex (DWORD dwFlags);
	HTREEITEM CalcSubGroupItem (HTREEITEM hParent, LPCSTR pcSubGroup);
	HTREEITEM CalcParentItem (LPCSTR pcGroup);
	CTreeViewCtrl *GetTree() { return (CTreeViewCtrl *)GetControl(); }

	void MouseButtonUp (MouseEvt);
	void MouseButtonDn (MouseEvt);

// MessageReflection
	void OnSelChanged (NotifyEvt);

	void AdjustParentImage (HTREEITEM hItem);

public:
// Konstruktor/Destruktor/Initialisierung
		CSelObjPropTree (pDialogWindow pW, ResID uiRes, IObjectProps *pIProps);
		~CSelObjPropTree (void);
		
	bool InitControl (string &rStr);
	void OnItemExpanded (NotifyEvt);

	CTreeViewCtrl *operator-> () { return GetTree(); }

	void SetHasSelectedItem (bool fFlag) { m_fHasSelectedItem = fFlag; }
	bool GetHasSelectedItem (void) { return m_fHasSelectedItem; }

	HRESULT GetSelectedObjProp (string &rStrSelected, string *pStrFull);
};

#define WM_ITEMSELECTED	(WM_USER+2345)
#define WM_CANCELDIALOG	(WM_USER+2346)

// Indizies in Imagelist
#define IMG_FOLDER		1
#define IMG_OPENFOLDER	2
#define IMG_TEXTPROP	3
#define IMG_BOOLPROP	4
#define IMG_DATUMPROP	8
#define IMG_INTEGERPROP	9
#define IMG_UNKNOWNPROP	10
#define IMG_DOUBLEPROP	11

#endif // _SELOBJPROP_H
