// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 23.08.2002 09:00:34 
//
// @doc
// @module ObjPropTree.h | Declaration of the <c CObjPropTree> class

#if !defined(_OBJPROPTREE_H__7EF942F3_0404_4A96_A7AB_9ED8D7603A82__INCLUDED_)
#define _OBJPROPTREE_H__7EF942F3_0404_4A96_A7AB_9ED8D7603A82__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/map>

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(EnumObjProps);
DefineSmartInterface(ObjectProperty);
DefineSmartInterface(ObjectProps);

/////////////////////////////////////////////////////////////////////////////
// special support for CheckBox's in TreeCtrl's
#define TV_CHECK_NOCHANGE	(UINT)(-1)
#define TV_CHECK_NOMARK		(INDEXTOSTATEIMAGEMASK(0))
#define TV_CHECK_OFF		(INDEXTOSTATEIMAGEMASK(1))
#define TV_CHECK_ON			(INDEXTOSTATEIMAGEMASK(2))
#define TV_CHECK_PASSIVE	(INDEXTOSTATEIMAGEMASK(3))
#define TV_CHECK_PARTIAL_ON	(INDEXTOSTATEIMAGEMASK(4))

#define TVN_CHECKSTATECHANGED	(WM_USER+4321)
#define TVN_CHANGINGCHECKSTATE	(WM_USER+4322)

typedef struct tagNMTREEVIEWCHECK {
    NMHDR hdr;
    UINT action;
    HTREEITEM hItem;
	UINT state;
} NM_TREEVIEWCHECK;

///////////////////////////////////////////////////////////////////////////////
// Indizies in Imagelist (IDB_OBJPROPTYPES)
#define IMG_FOLDER		1
#define IMG_OPENFOLDER	2
#define IMG_TEXTPROP	3
#define IMG_BOOLPROP	4
#define IMG_DATUMPROP	8
#define IMG_INTEGERPROP	9
#define IMG_UNKNOWNPROP	10
#define IMG_DOUBLEPROP	11

///////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////
// CObjPropTree window

class CObjPropTree : public CTreeCtrl
{
// Construction
public:
	typedef map<os_string, HTREEITEM, less<os_string> > CItemMap;

	CObjPropTree(INCLUDEOBJPROP pFcn = IncludeAll, bool fUseCheckMarks = true, 
		bool fUsePartialCheckMarks = false);

// Attributes
public:

// Operations
public:
// Initialisierung
	BOOL Init(IObjectProps *pIProps, LPCSTR pcToSelect = NULL)
	{
	list<os_string> listStr;

		if (NULL != pcToSelect) {
			ATLTRY(listStr.push_back(pcToSelect));
		}
		return Init (pIProps, listStr);
	}
	BOOL Init(IObjectProps *pIProps, list<os_string> &rStrs);

#if defined(_USE_CHECKMARK_OBJPROPTREE)
// CheckStuff
	void SetCheckStateEx (HTREEITEM hItem, UINT uiState, 
		bool fPropagateUp = true, bool fPropagateDown = true);
	int GetCheckState(HTREEITEM hItem) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return GetItemState(hItem, TVIS_STATEIMAGEMASK) & TVIS_STATEIMAGEMASK;
	}
	void HideStateImage(HTREEITEM hItem)
	{
		SetCheckState(hItem, TV_CHECK_NOMARK);
	}
	bool ToggleCheckMark (HTREEITEM hItem);

// Resultate abfragen
	HRESULT GetSelectedObjProps (list<os_string> &rlstObjProps, HTREEITEM hItem = TVI_ROOT);
#endif // defined(_USE_CHECKMARK_OBJPROPTREE)

	int CountSelectedItems (HTREEITEM hItem = TVI_ROOT, int iCnt = 0);
	HRESULT GetSelectedObjProp (CString &rStrSelected, CString *pStrFull);
	HRESULT GetObjPropName(HTREEITEM hItem, CString &rStrSelected, CString *pStrFull);
	HRESULT GetSelectObject (IUnknown **ppIUnk);
	static HRESULT GetObjectProp (LPCSTR pcObjProp, IObjectProps *pIProps, IObjectProperty **ppIObjProp);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjPropTree)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CObjPropTree();

	IObjectProps *GetObjectProps() { return m_Props; }

	// Generated message map functions
protected:
	//{{AFX_MSG(CObjPropTree)
	afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);

protected:
	HTREEITEM CalcSubGroupItem (HTREEITEM hParent, LPCSTR pcSubGroup);
	HTREEITEM CalcParentItem (CItemMap &rItems, LPCSTR pcGroup);

#if defined(_USE_CHECKMARK_OBJPROPTREE)
	bool UseCheckMarks() { return m_fUseCheckMarks; }
	bool UsePartialCheckMarks() { return m_fUsePartialCheckMarks; }
	UINT CalcParentCheckState (HTREEITEM hItem);
	void HandleCheckMark(CPoint point, UINT uiMsg);

	void NotifyChecked (HTREEITEM hNewTarget, UINT uiMsg, UINT uiCheckState);
	UINT ChangingCheckState (HTREEITEM hNewTarget, UINT uiMsg);

public:
	void SetLimitCount(long lLimitCnt) { m_lLimitCnt = lLimitCnt; }
#endif // defined(_USE_CHECKMARK_OBJPROPTREE)

protected:
	void SetCheckState (HTREEITEM hItem, UINT uiState)
	{
		SetItemState(hItem, uiState, TVIS_STATEIMAGEMASK);
	}

	void AdjustParentImage (HTREEITEM hItem)
	{
		if (ItemHasChildren (hItem)) {
		// nur Parents behandeln
			if (GetItemState (hItem, TVIS_EXPANDED) & TVIS_EXPANDED) 
				SetItemImage (hItem, IMG_OPENFOLDER, IMG_OPENFOLDER);	// ist expandiert
			else
				SetItemImage (hItem, IMG_FOLDER, IMG_FOLDER);	// ist collabiert
		}
	}

private:
	INCLUDEOBJPROP m_pFcn;
	bool m_fHasSelectedItem;
	CImageList m_imgList;
	WObjectProps m_Props;	// hält IObjectProps fest

#if defined(_USE_CHECKMARK_OBJPROPTREE)
	CImageList m_imgListCk;
	bool m_fUseCheckMarks;
	bool m_fUsePartialCheckMarks;
	long m_lLimitCnt;
	bool m_fShowLimitWarning;
#endif // defined(_USE_CHECKMARK_OBJPROPTREE)
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_OBJPROPTREE_H__7EF942F3_0404_4A96_A7AB_9ED8D7603A82__INCLUDED_)
