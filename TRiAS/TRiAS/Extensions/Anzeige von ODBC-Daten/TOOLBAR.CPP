/*
	File: TOOLBAR.CPP
*/

#include "pheader.h"
#include "odbcext.hr"			// IDM_DISABLE

#include <hpp/toolbar.hpp>			// zugeh. Header

#ifdef WIN32
BEGIN_MESSAGE_MAP(CToolBarEx, CToolBar)
	ON_MESSAGE (IDM_DISABLE, OnDisable)
END_MESSAGE_MAP()
#endif

void CToolBarEx :: Disable (uint nIndex)
{ 
#ifdef WIN32
	UINT nID, nStyle;
	int iImage;
	GetButtonInfo (nIndex, nID, nStyle, iImage);
	if (nStyle == TBBS_DISABLED)
		return;

	if (nStyle == TBBS_PRESSED)
		PostMessage (IDM_DISABLE, nIndex, 0);
	else
		SetButtonInfo (nIndex, nID, TBBS_DISABLED, iImage);
#else
	_SetButtonStyle (nIndex, TBBS_DISABLED); 
#endif
}	

void CToolBarEx :: Enable (uint nIndex)  
{ 
#ifdef WIN32
	UINT nID, nStyle;
	int iImage;
	GetButtonInfo (nIndex, nID, nStyle, iImage);
	if (nStyle != TBBS_BUTTON)
		SetButtonInfo (nIndex, nID, TBBS_BUTTON, iImage);
#else
	_SetButtonStyle (nIndex, TBBS_BUTTON); 
#endif
} 

#ifdef WIN32
afx_msg LONG CToolBarEx :: OnDisable (UINT iIndex, LONG)
{
	Disable (iIndex);		
	return TRUE;
}
#endif
