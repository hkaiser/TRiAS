// ListCtrlObjects.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ListCtrlObjects.h"
#include "MetaData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlObjects

CListCtrlObjects::CListCtrlObjects()
{
	tLButtonDownCatched = false;
}

CListCtrlObjects::~CListCtrlObjects()
{
}


BEGIN_MESSAGE_MAP(CListCtrlObjects, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlObjects)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CListCtrlObjects 

void CListCtrlObjects::OnLButtonDown(UINT nFlags, CPoint point) 
{
	LV_HITTESTINFO	lvhti;

	SetFocus();
	lvhti.pt = point;
	if( -1 != SubItemHitTest(&lvhti) ) {
		if( lvhti.iSubItem == 0 && (lvhti.flags & LVHT_ONITEMICON) ) {
			tLButtonDownCatched = true;
		}
		else if( lvhti.iSubItem == 1 && (lvhti.flags & LVHT_ONITEMICON) ) {
			tLButtonDownCatched = true;
		}
		else {
			tLButtonDownCatched = false;
			CListCtrl::OnLButtonDown(nFlags, point);
		}
	}
	else {
		tLButtonDownCatched = false;
		CListCtrl::OnLButtonDown(nFlags, point);
	}
}

void CListCtrlObjects::OnLButtonUp(UINT nFlags, CPoint point) 
{
	LVITEM			lvi;
	LV_HITTESTINFO	lvhti;

	lvhti.pt = point;
	if( -1 != SubItemHitTest(&lvhti) ) {
		CString strLayer;
		CRule_Layer	*pRule_Layer;
		bool tSelect;
		int iNumItems;
		int iItem;
		if( tLButtonDownCatched && lvhti.iSubItem == 0 && (lvhti.flags & LVHT_ONITEMICON) ) {
			tLButtonDownCatched = false;

			lvi.mask = LVIF_STATE | LVIF_IMAGE;
			lvi.iItem = lvhti.iItem;
			lvi.iSubItem = 0;
			lvi.stateMask = LVIS_SELECTED;
			GetItem(&lvi);
			if( 4 == lvi.iImage ) {
				tSelect = true;
			}
			else {
				tSelect = false;
			}
			if( lvi.state & LVIS_SELECTED ) {
				iNumItems = GetItemCount();
				for( iItem = 0; iItem < iNumItems; iItem++ ) {
					lvi.mask = LVIF_STATE;
					lvi.iItem = iItem;
					lvi.iSubItem = 0;
					lvi.stateMask = LVIS_SELECTED;
					GetItem(&lvi);
					
					if( lvi.state & LVIS_SELECTED ) {
						lvi.mask = LVIF_IMAGE;
						lvi.iItem = iItem;
						lvi.iSubItem = 0;
						strLayer = GetItemText(iItem, 0);
						pRule_Layer = g_pMetaData->GetRule_Layer(strLayer);
						if( tSelect ) {
							pRule_Layer->ImportMode() = EDBS_IMPORTALWAYS;
							lvi.iImage = 5;
						}
						else {
							pRule_Layer->ImportMode() = EDBS_IMPORTNEVER;
							lvi.iImage = 4;
						}
						SetItem(&lvi);
					}
				}	
			}
			else {
				lvi.mask = LVIF_IMAGE;
				lvi.iItem = lvhti.iItem;
				lvi.iSubItem = 0;
				strLayer = GetItemText(lvhti.iItem, 0);
				pRule_Layer = g_pMetaData->GetRule_Layer(strLayer);
				if( tSelect ) {
					pRule_Layer->ImportMode() = EDBS_IMPORTALWAYS;
					lvi.iImage = 5;
				}
				else {
					pRule_Layer->ImportMode() = EDBS_IMPORTNEVER;
					lvi.iImage = 4;
				}
				SetItem(&lvi);
			}
		}
		else if( tLButtonDownCatched && lvhti.iSubItem == 1 && (lvhti.flags & LVHT_ONITEMICON) ) {
			tLButtonDownCatched = false;

			lvi.mask = LVIF_STATE | LVIF_IMAGE;
			lvi.iItem = lvhti.iItem;
			lvi.iSubItem = 1;
			lvi.stateMask = LVIS_SELECTED;
			GetItem(&lvi);
			if( 1 == lvi.iImage ) {
				tSelect = true;
			}
			else {
				tSelect = false;
			}
			if( lvi.state & LVIS_SELECTED ) {
				iNumItems = GetItemCount();
				for( iItem = 0; iItem < iNumItems; iItem++ ) {
					lvi.mask = LVIF_STATE;
					lvi.iItem = iItem;
					lvi.iSubItem = 1;
					lvi.stateMask = LVIS_SELECTED;
					GetItem(&lvi);
					
					if( lvi.state & LVIS_SELECTED ) {
						lvi.mask = LVIF_IMAGE;
						lvi.iItem = iItem;
						lvi.iSubItem = 1;
						strLayer = GetItemText(iItem, 0);
						pRule_Layer = g_pMetaData->GetRule_Layer(strLayer);
						if( tSelect ) {
							pRule_Layer->Resolve(true);
							lvi.iImage = 2;
						}
						else {
							pRule_Layer->Resolve(false);
							lvi.iImage = 1;
						}
						SetItem(&lvi);
					}
				}	
			}
			else {
				lvi.mask = LVIF_IMAGE;
				lvi.iItem = lvhti.iItem;
				lvi.iSubItem = 1;
				strLayer = GetItemText(lvhti.iItem, 0);
				pRule_Layer = g_pMetaData->GetRule_Layer(strLayer);
				if( tSelect ) {
					pRule_Layer->Resolve(true);
					lvi.iImage = 2;
				}
				else {
					pRule_Layer->Resolve(false);
					lvi.iImage = 1;
				}
				SetItem(&lvi);
			}
		}	
		else {
			tLButtonDownCatched = false;
			CListCtrl::OnLButtonUp(nFlags, point);
		}
	}
	else {
		CListCtrl::OnLButtonUp(nFlags, point);
	}
}
