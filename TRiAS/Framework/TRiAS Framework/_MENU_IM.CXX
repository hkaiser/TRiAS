/* $Header:   G:/cv.win/pvcs/commonvu/src/_menu_im.cxv   1.6.1.0   14 Jul 1992 11:55:50   RONAN  $
 *
 *	_ m e n u . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods log:
 *	0.0	ferg	05oct88	-------- Milestone 2 Beta 2 .. shipped. --------
 *	0.1 ferg	02nov88	Menu::Menu()'s and Menu::~Menu() moved here from 
 *						app.cxx + minor changes to get App pointer from DLL 
 *						dataseg and Show flag from App. menu.cxx now defunct.
 *	0.2	jk		15nov88	from jk 24oct88. Destroymenu called in Menu dtor.
 *	0.3	ferg	16nov88	SysMenu dtor introduced to avoid invoking DestroyMenu
 *						for the windows system menu.
 *	0.4	jk		29nov88	------ Milestone 2A. Beta 2A shipped ------
 *	0.5 jk		02dec88	Fast Compile defines added.
 *  0.6 rs      09mar89 Submenus
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1	rs		07jul89 -------Release 1.0a ship date ---------------
 *	1.2 rs		05Dec89	Lines deleted in SysMenu ctor. 
 *						Uneccessary as temporal dependency removed.
 *	1.3 rs		07Dec89 Support for the showing of menu bar items.
 *	1.4 rs		17Dec89	Null menu constructor.
 *	1.5 rs		04Jan90 Addition of isChanged flag.
 *						This is tagged whenever a menu is changed.
 *						If the menu is changed it will be redrawn by event handler
 *	2.0 rs		19Jun90 rs from nc Apr90 - Hiding
 *	2.1 hl		22jun90 use MF_BYPOSITION to delete a popup menu in
 *				DeleteItem						
 *	2.2 rs		25Jul90 Remove C++ sub menus before destroying menus, as their
 *						menu destructors will destroy them later.
 */

//  09.06.93 A.D. uve Potsdam: Menu_Imp und ~Menu_Imp so geaendert, dass keine App
//                             gefunden werden muss (Verwendung der DLL auch mit
//                             'fremden' EXE'en

#include "tfrmpre.hxx"
#include	<_Link.hxx>   

													// * 0.1 Begin *
Menu_Imp::  Menu_Imp	( )
{
	m_fAutoDetach = false;
		hMenu	= 0;
		hMenuParent = 0;
		autopos = 0;
}	// End of "Menu_Imp" CONSTRUCTOR "(BOOL)"


Menu_Imp::  Menu_Imp (ResID RscName , pMenu pRequestor)
{
pApp_Imp AppImpInst = _AppImpFind();

	m_fAutoDetach = false;
	hMenuParent = 0;
	if (hMenu = ((uint)RscName) ?
		LoadMenu (CV_RunTime :: ResID_handle (RscName, AppImpInst, RT_MENU), 
			  (char*)((ulong)((uint)RscName)))
	      : CreateMenu())
//	AppImpInst -> MenuList() -> Insert (hMenu, pRequestor );
	if (AppImpInst) 
		AppImpInst -> MenuList() -> Insert ((HANDLE)hMenu, pRequestor);
	autopos = 0;  // kleines zusaetzliches if... fuer den Fall, das 
                      // keine App.. zu finden ist (A.D. 09.06.93)
}	// End of "Menu_Imp" CONSTRUCTOR "(const char*)"


Menu_Imp::  Menu_Imp (pMenu pRequestor)		// * 1.4 * start
{
pApp_Imp AppImpInst = _AppImpFind();

	m_fAutoDetach = false;
	hMenuParent = 0;
	if (hMenu = CreateMenu ())
		AppImpInst -> MenuList() -> Insert ((HANDLE)hMenu, pRequestor );
}						// * 1.4 * end


Menu_Imp::  Menu_Imp (HMENU hM, pMenu pRequestor, BOOL fAutoDetach)		// * 1.4 * start
{
pApp_Imp AppImpInst = _AppImpFind();

	m_fAutoDetach = fAutoDetach;
	hMenuParent = 0;
	if (hMenu = hM)
		AppImpInst -> MenuList() -> Insert ((HANDLE)hMenu, pRequestor );
}						// * 1.4 * end

HMENU Menu_Imp::Detach (void)
{
HMENU hM = hMenu;

	hMenu = NULL;
	return hM;
}

/*  Urspruenglicher Destruktor
Menu_Imp::  ~Menu_Imp	()
{
	pApp_Imp AppImpInst = _AppImpFind();								// * 0.1 *

	if ( hMenu )											// * 0.3 *
	{
		AppImpInst -> MenuList() -> Delete ( hMenu);
		if (AppImpInst -> MenuList() -> First())
		{	
		// Are we a submenu

		if (hMenuParent)
			{
			for( uint i = 0; i < GetMenuItemCount( hMenuParent); i++)		 
				if (GetSubMenu(hMenuParent,i ) == hMenu)
					{
					RemoveMenu	(	hMenuParent, i, MF_BYPOSITION );
					hMenuParent = 0;
					break;
					}
			}

		// There may be sub menus
		for( uint i = 0; i < GetMenuItemCount( hMenu); i++)		 // * 2.2 start *
			{
			HANDLE hSubMenu;
			Menu * prq;
			if( (hSubMenu = GetSubMenu( hMenu, i)) &&
				(prq = (Menu*)AppImpInst -> MenuList()-> TaskFind(hSubMenu)))
					{
					CV_RunTime :: Menu_SethMenuParent(prq, 0);					
					RemoveMenu	(	hMenu, i, MF_BYPOSITION );
					}
			}
		}
	DestroyMenu ( hMenu );
	}

}	// End of "Menu_Imp" DESTRUCTOR
*/
// fuer den Fall das wir keine App.. finden koennen, muessen wir da
// etwas anders machen   (A.D. 09.06.93)
Menu_Imp::  ~Menu_Imp	()
{
    pApp_Imp AppImpInst = _AppImpFind();								// * 0.1 *

	if (hMenu) {										// * 0.3 *
		if (AppImpInst) 
			AppImpInst -> MenuList() -> Delete ((HANDLE)hMenu);
	
	// Are we a submenu
		if (hMenuParent) {
		    	for (int i = 0; i < GetMenuItemCount (hMenuParent); i++) {
				if (GetSubMenu (hMenuParent, i) == hMenu) {
					RemoveMenu (hMenuParent, i, MF_BYPOSITION);
					hMenuParent = 0;
					break;
				}
			}
		}
	
	// There may be sub menus
		for (int i = 0; i < GetMenuItemCount (hMenu); i++) {		 // * 2.2 start *
		HMENU hSubMenu;
		Menu * prq;
		
			if (AppImpInst) {
				if ((hSubMenu = GetSubMenu (hMenu, i)) &&
			    	     (prq = (Menu*)AppImpInst -> MenuList() -> TaskFind ((HANDLE)hSubMenu)))
				{
					CV_RunTime :: Menu_SethMenuParent (prq, 0);		
			    		RemoveMenu (hMenu, i, MF_BYPOSITION);
				}
			} else {
				if (GetSubMenu (hMenu, i)) // SubMenu's herauslösen
					RemoveMenu (hMenu, i, MF_BYPOSITION);
			}
		}	        // Sicherheitshalber
		if (m_fAutoDetach)
			Detach();
		else
			DestroyMenu (hMenu);
	}   
}	// End of "Menu_Imp" DESTRUCTOR
		  
SysMenu_Imp::  SysMenu_Imp	( pWind_Imp parent , pMenu pRequestor)
{	
	pApp_Imp AppImpInst = _AppImpFind();
	if (CV_RunTime :: Window_Handle(parent ))
		{
		HMENU h;
		CV_RunTime :: MenuImp_hMenu (  this ) = 
			h = GetSystemMenu( CV_RunTime :: Window_Handle(parent), FALSE);
		AppImpInst -> MenuList() -> Insert ((HANDLE)h, pRequestor );
		}
}	// End of "SysMenu_Imp" CONSTRUCTOR

													// * 0.1 End *

/* 													// * 0.3 Begin *
 * 	Set handle to NULL so that Menu dtor wont attempt to delete it.
 */
SysMenu_Imp::  ~SysMenu_Imp ()
{
	HMENU h;
	pApp_Imp AppImpInst = _AppImpFind();
	if ( h = CV_RunTime :: MenuImp_hMenu( this))											// * 0.3 *
		AppImpInst -> MenuList() -> Delete ((HANDLE)h );
	CV_RunTime :: MenuImp_hMenu ( (pMenu_Imp) this ) = NULL;
}
													// * 0.3 End *
				 									// * 1.3 Start *
BOOL	Menu_Imp::  AppendItem	( uint ID, const char* New )
{
	BOOL result = AppendMenu(hMenu, MF_BYCOMMAND | MF_STRING | MF_ENABLED,
								ID,	New);
	return result;

}	// End of "Menu" FUNCTION "AppendItem(uint,const char*)"

BOOL	Menu_Imp::  AppendItem	(pMenu SubMenu, const char* Header)  // * 0.6 start *
{
	CV_RunTime :: Menu_SethMenuParent(SubMenu, hMenu);					

	BOOL result = AppendMenu(hMenu, MF_BYCOMMAND | MF_POPUP | MF_ENABLED,
				 (UINT)CV_RunTime :: Menu_hMenu(SubMenu), 
				 Header);
	return result;

}	// End of "Menu_Imp" FUNCTION "AppendItem(uint,const char*)" * 0.6 end
	
BOOL	Menu_Imp::  AppendItem	( uint ID, pBitmap New )
{

// ZORTECH
// cast of uint to char far * not allowed directly, cast to long added

	BOOL result = AppendMenu(hMenu, MF_BYCOMMAND | MF_BITMAP | MF_ENABLED ,
				 ID, 
				 (pchar)((long)(HANDLE)CV_RunTime :: Bitmap_hBitmap ( New )) );
	return result;

}	// End of "Menu" FUNCTION "AppendItem(uint,pBitmap)"

	
BOOL	Menu_Imp::  InsertItem	( uint ID, const char* New, uint where )
{
	BOOL result = InsertMenu(hMenu, where, MF_BYCOMMAND | MF_STRING | MF_ENABLED,
								ID,	New);
	return result;

}	// End of "Menu" FUNCTION "InsertItem(uint,const char*,uint)"

	
BOOL	Menu_Imp::  InsertItem	( pMenu SubMenu, const char* Header, uint where)  // * 0.6 start *
{
	CV_RunTime :: Menu_SethMenuParent(SubMenu, hMenu);					
	BOOL result = InsertMenu(hMenu, where, MF_BYCOMMAND | MF_POPUP | MF_ENABLED,
				 (UINT)CV_RunTime :: Menu_hMenu(SubMenu), Header);
	return result;

}	// End of "Menu" FUNCTION "AppendItem(uint,const char*)" * 0.6 end

BOOL	Menu_Imp::  InsertItem	( uint ID, pBitmap New, uint where )
{
// ZORTECH
// cast of uint to char far * not allowed directly, cast to long added

	BOOL result = InsertMenu(hMenu, where, MF_BYCOMMAND | MF_BITMAP | MF_ENABLED,
				 ID, (pchar)((long)(HANDLE)CV_RunTime :: Bitmap_hBitmap ( New )) );
	return result;

}	// End of "Menu" FUNCTION "InsertItem(uint,pBitmap,uint)"

	
BOOL	Menu_Imp::  DeleteItem	( uint where )
{
	BOOL result =	RemoveMenu	(	hMenu, where, MF_BYCOMMAND);
	return result;


}	// End of "Menu" FUNCTION "DeleteItem"

BOOL	Menu_Imp::  DeleteItem	( pMenu SubMenu )
{
	for( int i = 0; i < GetMenuItemCount( hMenu); i++)	// * 2.1 *
	{
		if( GetSubMenu( hMenu, i) == CV_RunTime :: Menu_hMenu(SubMenu))
		{
		BOOL result =	RemoveMenu	(	hMenu, i, MF_BYPOSITION );
		CV_RunTime :: Menu_SethMenuParent(SubMenu, 0);					
			return result;
		}
	}
	return FALSE;

}	// End of "Menu" FUNCTION "DeleteItem"

BOOL	Menu_Imp::  AppendSeparator	()
{
	BOOL result = AppendMenu(hMenu, MF_BYCOMMAND | MF_SEPARATOR , 0,0);
	return result;

}	// End of "Menu" FUNCTION "AppendSeparator"


BOOL	Menu_Imp::  InsertSeparator	( uint where )
{
	BOOL result = InsertMenu(hMenu, where, MF_BYCOMMAND | MF_SEPARATOR , 0,0);
	return result;

}	// End of "Menu" FUNCTION "InsertSeparator"


BOOL	Menu_Imp::  CheckItem	( uint where )
{
    BOOL result =	CheckMenuItem ( hMenu, where, ( MF_CHECKED | MF_BYCOMMAND ));
	return result;

}	// End of "Menu" FUNCTION "CheckItem"


BOOL	Menu_Imp::  unCheckItem	( uint where )
{
    BOOL result =	CheckMenuItem ( hMenu, where, ( MF_UNCHECKED | MF_BYCOMMAND ));
	return result;

}	// End of "Menu" FUNCTION "unCheckItem"


BOOL	Menu_Imp::  EnableItem	( uint where )
{
    BOOL result =	EnableMenuItem ( hMenu, where, ( MF_ENABLED | MF_BYCOMMAND ));
	return result;

}	// End of "Menu" FUNCTION "EnableItem"


BOOL	Menu_Imp::  DisableItem	( uint where )
{
    BOOL result =	EnableMenuItem ( hMenu, where, ( MF_DISABLED | MF_GRAYED | MF_BYCOMMAND ));
	return result;

}	// End of "Menu" FUNCTION "DisableItem"
	// * 1.3 end *

void Menu_Imp :: SetAutoUpdate ( uint pos )
{
	autopos = pos;
}

HMENU Menu_Imp :: RecursiveCopy (HMENU hCopyMenu)
{
	HMENU hRetval = 0;

	if (hCopyMenu)
		{
		hRetval = CreateMenu();
		int itemCount = GetMenuItemCount(hCopyMenu);
		for (int i = 0; i < itemCount; i++)
			{
			int id  = GetMenuItemID(hCopyMenu, i);
			uint flags = GetMenuState(hCopyMenu, i, MF_BYPOSITION);
			HMENU hnewitem = 0;
			uint newflags = (flags & 
				(MF_MENUBARBREAK | MF_DISABLED 
				| MF_ENABLED | MF_GRAYED | MF_CHECKED 
				| MF_MENUBREAK | MF_UNCHECKED));
			char buffer[61];

		// Get Text of item

			if (flags & MF_BITMAP)
				lstrcpy(buffer, "[Bitmap]");
			else
			if (flags & MF_OWNERDRAW)
				lstrcpy(buffer, "[OwnerDraw]");
			else
				GetMenuString(hCopyMenu, i, buffer, 59, MF_BYPOSITION);

			// is it a separator
			if (flags & MF_SEPARATOR)
				AppendMenu( hRetval, newflags | MF_SEPARATOR, 0,0);
 			else
			// is it a popup menu
			if ((flags & MF_POPUP) && (id == (-1)) && 
					(hnewitem = RecursiveCopy(GetSubMenu(hCopyMenu, i))))
					AppendMenu(hRetval, newflags | MF_POPUP, (UINT)hnewitem, buffer);
			else
			// Presume its a string
					AppendMenu(hRetval, newflags , id, buffer);
			}
		}
	return hRetval;
}

Menu_Imp :: Menu_Imp  ( const Menu_Imp & copyFrom, pMenu pRequestor) {

	hMenu	= RecursiveCopy(copyFrom.hMenu);
	hMenuParent = 0;
	autopos = 0;
	pApp_Imp AppImpInst = _AppImpFind();
	AppImpInst -> MenuList() -> Insert ((HANDLE)hMenu, pRequestor );
}
