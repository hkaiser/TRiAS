// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.10.2000 13:16:07 
//
// @doc
// @module SelObjPropList.h | Declaration of the <c CSelObjPropList> class

#if !defined(_SELOBJPROPLIST_H__9881E241_81CF_4021_B11A_1AB90CA12D79__INCLUDED_)
#define _SELOBJPROPLIST_H__9881E241_81CF_4021_B11A_1AB90CA12D79__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ObjPropImageList.h>

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ObjectProps);

///////////////////////////////////////////////////////////////////////////////
// 
class CSelObjPropList :
	public CListViewCtrl
{
public:
	CSelObjPropList(pDialogWindow pW, ResID uiRes);
	~CSelObjPropList();

	bool InitControl(IObjectProps *pIProps);

	bool MoveItemUp(void);
	bool MoveItemDown(void);
	
	int GetItemFocus (void);
	
	int GetFirstSelected(void);
	int GetLastSelected(void);
	int GetNextSelected(void);
	int GetPrevSelected(void);
	bool IsItemSelected(int iIndex);

	bool GetObjectProperties(list<os_string> &rProps);
	bool FillWithItems(list<os_string> &rLstProps);

protected:
	bool SwapItems (int iIndexO, int iIndexN);
	void FitColumns (int iColMin = 0, int iColMax = -1);
	int GetColumnCount (void);

private:
	CObjPropImageList m_ilProps;
	WObjectProps m_Props;
	int m_iCurrItem;
	bool m_fUp;
	bool m_fDown;
};

#endif // !defined(_SELOBJPROPLIST_H__9881E241_81CF_4021_B11A_1AB90CA12D79__INCLUDED_)
