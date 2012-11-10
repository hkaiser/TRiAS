// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 24.04.2002 12:30:37 
//
// @doc
// @module AssociateLayersToClasses.h | Declaration of the <c CAssociateLayersToClasses> class

#if !defined(_ASSOCIATELAYERSTOCLASSES_H__DB6F1E17_4600_4A25_9130_E0843736FB0D__INCLUDED_)
#define _ASSOCIATELAYERSTOCLASSES_H__DB6F1E17_4600_4A25_9130_E0843736FB0D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"
#include "relkey.hxx"

///////////////////////////////////////////////////////////////////////////////
// Spaltennummern und BildNummern
#define PICTURE_COLUMN		0
#define LAYER_COLUMN		1
#define CHECK_COLUMN		2
#define CLASS_COLUMN		3

#define MINCOLWIDTH			10

#define IMAGE_POINT			1
#define IMAGE_LINE			2
#define IMAGE_AREA			3
#define IMAGE_TEXT			4

#define IMAGE_UNCHECKED		5
#define IMAGE_CHECKED		6

///////////////////////////////////////////////////////////////////////////////
// eigene Messages
extern const UINT WM_SHOWCOMBO;
extern const UINT WM_DESTROYCOMBO;
extern const UINT WM_ITEMSELECTED;
extern const UINT WM_ADDNEWENTRY;
extern const UINT WM_COPYBNAENTRY;

///////////////////////////////////////////////////////////////////////////////
// ListView für Gegenüberstellung von Layern und Objektklassen
class CAssociateLayersToClasses :
	public ControlWindow
{
public:
	CAssociateLayersToClasses(DialogWindow *pW, UINT uiID);
	~CAssociateLayersToClasses();

	BOOL FInit(TR_LayerTree *pOKSTree, HPROJECT hPr, bool fGcoProduction);
	BOOL AddObjType (int &riCnt, TR_Layer *pLayer, DWORD dwType);

	void OnEndLabelEdit (NMHDR *pNMHDR, LRESULT *plResult);
	void OnClick (NMHDR *pNMHDR, LRESULT *plResult);

// Liefert Nutzerauswahl
	string GetLayerName(int iIndex = -1);
	string GetClassName(int iIndex = -1);
	DWORD GetObjType(int iIndex = -1);
	bool GetDoImport(int iIndex = -1);

	bool SetClassText (int iIndex, LPCSTR pcNewClass);
	bool SetClassText (LPCSTR pcNewClass)
	{
		return SetClassText(GetFocusItem(), pcNewClass);
	}
	void SetCheckState(bool fCheck)
	{
		SetCheckState(GetFocusItem(), fCheck);
	}

	int GetItemCount()
	{
		return GetListView()->GetItemCount();
	}
	int GetFirstSelected()
	{
		m_iCurrItem = -1;				// aufsteigend
		return GetNextSelected();
	}
	int GetNextSelected()
	{
		return (m_iCurrItem = GetListView()->GetNextItem(m_iCurrItem, LVNI_ALL|LVNI_SELECTED));
	}
	int GetFocusItem()
	{
		return GetListView()->GetNextItem(-1, LVNI_ALL|LVNI_FOCUSED);
	}

protected:
// MessageHandling
	LRESULT Dispatch (Event e);
	void MouseButtonDn (MouseEvt e);
	void MouseButtonDblClk (MouseEvt e);
	void FocusChange (FocusChangeEvt e);
	void HorizScroll (ScrollEvt e);
	void VertScroll (ScrollEvt e);

	int HitTestEx (POINT point, int *col);
	BOOL OnShowCombo (int index, int colnum);
	void OnItemSelected (int index, int colnum);
	void OnCloseUp (UINT uiID);
	ComboBox* ShowInPlaceList(int nItem, int nCol, CStringList &lstItems, 
		int nSel, LPCSTR pcInitEntry);
	void ResetClassText(int iIndex);
	bool GetCheckState(int iIndex);
	void SetCheckState (int iIndex, bool fCheck);

// Wrapper Funktionen
	void FitColumn (int iCol, bool fAccountForHeader = true);
	int InsertColumn (int nCol, LPCSTR lpszColumnHeading, 
		int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1)
	{
		return GetListView() -> InsertColumn(nCol, lpszColumnHeading, nFormat, 
			nWidth, nSubItem);
	}
	void SetRedraw (BOOL fRedraw)
	{
		SendMessage(Handle(), WM_SETREDRAW, fRedraw, 0);
	}
	int GetColumnCount(void)
	{
	HWND hCtrl = GetDlgItem (Handle(), 0);

		_ASSERTE(::IsWindow(hCtrl));
		return Header_GetItemCount (hCtrl);
	}
	BOOL SetColumnWidth (int nCol, int cx)
	{
		return GetListView()->SetColumnWidth(nCol, cx);
	}
	int GetColumnWidth (int nCol)
	{
		return GetListView()->GetColumnWidth(nCol);
	}
	CImageList* SetImageList (CImageList* pImageList, int nImageListType)
	{
		return GetListView()->SetImageList (pImageList, nImageListType);
	}
	DWORD GetStyle() 
	{ 
		return (DWORD)::GetWindowLong (Handle(), GWL_STYLE); 
	}

	CListViewCtrl *GetListView() 
	{ 
		_ASSERTE(NULL != GetControl()); 
		return (CListViewCtrl *)GetControl(); 
	}

private:
	CInPlaceCombo *m_pList;
	UINT m_uiID;
	int m_iCurrItem;

	CImageList m_ilType;		// Bildchen für ListView (Objekttypen)
	CImageList m_ilState;		// (Checkmarks)

	typedef vector<int> CSelectedItems;
	CSelectedItems m_vecItems;

	HPROJECT m_hPr;
	bool m_fGcoProduction;
};

#endif // !defined(_ASSOCIATELAYERSTOCLASSES_H__DB6F1E17_4600_4A25_9130_E0843736FB0D__INCLUDED_)
