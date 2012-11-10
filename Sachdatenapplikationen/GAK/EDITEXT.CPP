// editext.cpp : implementation of the CEditExt class
//

#include "stdafx.h"			//	prec. Header
#include "res.h"			//	Resource-Konstanten	
#include "editext.h"		//	zugeh. Header
              
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CEditExt, CEdit)
	//{{AFX_MSG_MAP(CEditExt)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CEditExt::OnRButtonDown(UINT nFlags, CPoint point)
{
	CMenu menu;	
	VERIFY(menu.LoadMenu(IDM_POPUP));	
	                                                
//	Menü einstellen	                                                
	if (!CanUndo ())	    
		menu.EnableMenuItem (IDM_BACK, MF_GRAYED);
		
	BOOL bIsSel = GetSel () > 0;
	if (!bIsSel)
	{
		menu.EnableMenuItem (IDM_CUT, MF_GRAYED);		
		menu.EnableMenuItem (IDM_COPY, MF_GRAYED);		
		menu.EnableMenuItem (IDM_DELETE, MF_GRAYED);		
	}
	
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	                          
	CWnd* pWndPopupOwner = this;
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();
		        
	CPoint NewPoint;		        
	GetCursorPos (&NewPoint);		
                                     
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, NewPoint.x, NewPoint.y,
    					   pWndPopupOwner);
// 	CWnd::OnRButtonDown(nFlags, point);
}   


