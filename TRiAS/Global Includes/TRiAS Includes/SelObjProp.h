// Ein TreeViewCtrl, mit welchem Objekteigenschaften ausgewählt werden können -
// File: SELOBJPROP.H

#if !defined(_SELOBJPROP_H)
#define _SELOBJPROP_H

#pragma warning (disable: 4786)		// too long identifiers

#include <ospace/std/map>
#include <ospace/std/list>

#include <CheckTreeView.h>
#include <ObjPropImageList.h>

#if !defined(_DEFINED_OBJECTPROPS)
DefineSmartInterface(ObjectProperty);
DefineSmartInterface(ObjectProps);
#define _DEFINED_OBJECTPROPS
#endif // _DEFINED_OBJECTPROPS

// StandardFunktion für Einfügen eines Items in Baum (alles außer Interaktiv)
typedef bool(*INCLUDEOBJPROP)(DWORD);

inline bool IncludeObjProp (DWORD dwFlags)
{
	return !(dwFlags & (PROPCAPS_INTERACTIVE|PROPCAPS_INTERACTIVE_INIT));
}
inline bool IncludeWritable (DWORD dwFlags)
{
	return IncludeObjProp(dwFlags) && (dwFlags & PROPCAPS_NOTREADONLY);
}
inline bool IncludeAll (DWORD dwFlags)
{
	return true;		// _alle_ eischließen
}

///////////////////////////////////////////////////////////////////////////////
// 
class _TRIAS03_ENTRY CSelObjPropTree : 
	public CCheckTreeView
{
private:
	WObjectProps m_Props;	// hält IObjectProps fest

	typedef map<os_string, HTREEITEM, less<os_string> > CItemMap;
	CItemMap m_Items;
	CObjPropImageList m_ilProps;

	INCLUDEOBJPROP m_pFcn;
	DWORD m_dwRequired;
	bool m_fHasSelectedItem;
	bool m_fIsPopUp;
	
protected:
	HTREEITEM CalcSubGroupItem (HTREEITEM hParent, LPCSTR pcSubGroup);
	HTREEITEM CalcParentItem (LPCSTR pcGroup);

	void MouseButtonUp (MouseEvt);
	void MouseButtonDn (MouseEvt);
	void FocusChange (FocusChangeEvt e);

	void AdjustParentImage (HTREEITEM hItem);

	HRESULT GetSelectedObjProps (HTREEITEM hItem, list<os_string> &rlstObjProps);
	HRESULT GetObjPropName (HTREEITEM hItem, string &rStrSelected, string *pStrFull);

public:
// Konstruktor/Destruktor/Initialisierung
		CSelObjPropTree (pDialogWindow pW, ResID uiRes, IObjectProps *pIProps, 
			INCLUDEOBJPROP pFcn = IncludeObjProp, bool fIsPopUp = true, 
			bool fCheckMarks = false, bool fPartialCheckMarks = false);
		~CSelObjPropTree (void);
		
	bool InitControl (os_string &rStr);
	bool InitControl (list<os_string> &rStrs);

// MessageReflection
	void OnItemExpanded (NotifyEvt);
	void OnSelChanged (NotifyEvt);

	void SetHasSelectedItem (bool fFlag) { m_fHasSelectedItem = fFlag; }
	bool GetHasSelectedItem (void) { return m_fHasSelectedItem; }

	HRESULT GetSelectedObjProps (list<os_string> &rlstObjProps);
	HRESULT GetSelectedObjProp (string &rStrSelected, string *pStrFull);
	bool SelectObjProp (LPCSTR pcObjProp);

	int CountSelectedItems (HTREEITEM hItem = TVI_ROOT, int iCnt = 0);

	IObjectProps *GetObjectProps() { return m_Props; }
	void SetObjectProps(IObjectProps *pIProps) { m_Props = pIProps; }
};

#define WM_ITEMSELECTED	(WM_USER+2345)
#define WM_CANCELDIALOG	(WM_USER+2346)

#endif // _SELOBJPROP_H
