// PopupMenü für TRiAS-Hauptmenü
// File: PopupMenu.cxx
// H. Kaiser


#include "GeometrP.hxx"

#include "PopupMenu.hxx"



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


///////////////////////////////////////////////////////////////////////////////////////////////
BOOL _GEOMETR_EXPORT InstallPopupMenu (HDEX hDex, Menu* pPopupMenu)
{
#if _TRiAS_VER >= 0x0300
	_ASSERTE (NULL != pPopupMenu);

	if (! pPopupMenu) return FALSE;

INSTALLMENUITEMEX imi;

	INITSTRUCT(imi, INSTALLMENUITEMEX);
	imi.hDex = hDex;
	imi.iMenuID = -1;
	imi.iFlag = IMINormalMenu;
	imi.iMenuNum = EXTRA_MENU_POS;
	imi.iMenuPos = -1;

// PopUpMenu und MenuText holen
char cbBuffer[64];

	imi.hMenu = GetSubMenu (pPopupMenu -> Handle(API_MENU_HMENU), 0);

	_ASSERTE (NULL != imi.hMenu);

	GetMenuString (pPopupMenu -> Handle(API_MENU_HMENU), 0, cbBuffer, sizeof(cbBuffer), MF_BYPOSITION);

	imi.pMenuText = cbBuffer;
	return (NULL != DEX_InstallMenuItem (imi)) ? TRUE : FALSE;
#else
	_ASSERTE (_TRiAS_VER >= 0x0300);

	return FALSE;
#endif // _TRiAS_VER >= 0x0300
}


// --------------------------------------------------------------------------------------------
void _GEOMETR_EXPORT RemovePopupMenu (HDEX hDex)
{
#if _TRiAS_VER >= 0x0300
REMOVEMENUITEMEX rmi;

	INITSTRUCT(rmi, REMOVEMENUITEMEX);
	rmi.hDex = hDex;
	rmi.iMenuID = -1;
	rmi.iMenuNum = EXTRA_MENU_POS;
	rmi.iFlag = IMINormalMenu;
	rmi.iMenuPos = -1;
	DEX_RemoveMenuItem (rmi);
#else
	_ASSERTE (_TRiAS_VER >= 0x0300);
#endif // _TRiAS_VER >= 0x0300
}
