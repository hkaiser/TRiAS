/* $Header:   G:/cv.win/pvcs/commonvu/src/_menu.cxv   3.0   25 Mar 1992 15:21:00   RONAN  $
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
 *	1.0	jf	dec89	Created a new as the source for the public interface class
 */

#include "tfrmpre.hxx"
#include	<_Link.hxx>   

_DLLENTRY Menu:: ~Menu	()
{
	if ( menu_Imp )
		delete menu_Imp;
	menu_Imp = NULL;
}


_DLLENTRY Menu:: Menu	( ResID RscID )
{
	menu_Imp = new Menu_Imp(RscID, this);
}

_DLLENTRY Menu:: Menu	()
{
	menu_Imp = new Menu_Imp(this);
}


_DLLENTRY Menu:: Menu	(HMENU hMenu)
{
	menu_Imp = new Menu_Imp (hMenu, this);
}

_DLLENTRY Menu:: Menu	(HMENU hMenu, BOOL fAutoDetach)
{
	menu_Imp = new Menu_Imp (hMenu, this, fAutoDetach);
}

_DLLENTRY Menu:: Menu	( void* )
{

}	// End of "Menu" CONSTRUCTOR "(bool)"

HMENU _DLLENTRY Menu::Detach (void)
{
	return menu_Imp -> Detach();
}
		  
_DLLENTRY SysMenu:: SysMenu	( pWindow parent ) : Menu( (void*)0 )
{
	menu_Imp = new SysMenu_Imp( CV_RunTime :: pWindow_to_pImp(parent), this );
}

_DLLENTRY SysMenu:: ~SysMenu	()
{
	if ( menu_Imp )
		delete ((SysMenu_Imp*)menu_Imp);
	menu_Imp = NULL;
}

BOOL	 _DLLENTRY Menu:: AppendItem	( uint ID, const char* New )
{
	return	menu_Imp->AppendItem(ID, New);
}

	
BOOL	 _DLLENTRY Menu:: AppendItem	( uint ID, pBitmap New )
{
	return menu_Imp->AppendItem(ID, New);
}

BOOL	 _DLLENTRY Menu:: AppendItem	( pMenu SubMenu, const char* Header )
{
	return menu_Imp->AppendItem(SubMenu, Header);
}
	
BOOL	 _DLLENTRY Menu:: InsertItem	( uint ID, const char* New, uint where )
{
	return	menu_Imp->InsertItem(ID, New, where);
}

	
BOOL	 _DLLENTRY Menu:: InsertItem	( uint ID, pBitmap New, uint where )
{
	return	menu_Imp->InsertItem(ID, New, where);
}

BOOL	 _DLLENTRY Menu:: InsertItem	( pMenu SubMenu, const char* Header, uint where )
{
	return	menu_Imp->InsertItem(SubMenu, Header, where);
}
	
BOOL	 _DLLENTRY Menu:: DeleteItem	( uint which )
{
	return	menu_Imp->DeleteItem(which);
}

BOOL  _DLLENTRY Menu ::  DeleteItem ( pMenu Popup )
{
	return	menu_Imp->DeleteItem(Popup);
}

BOOL	 _DLLENTRY Menu:: AppendSeparator	()
{
	return	menu_Imp->AppendSeparator();
}


BOOL	 _DLLENTRY Menu:: InsertSeparator	( uint where )
{
	return	menu_Imp->InsertSeparator(where);
}


BOOL	 _DLLENTRY Menu:: CheckItem	( uint which )
{
	return	menu_Imp->CheckItem(which);
}


BOOL	 _DLLENTRY Menu:: unCheckItem	( uint which )
{
	return	menu_Imp->unCheckItem(which);
}


BOOL	 _DLLENTRY Menu:: EnableItem	( uint which )
{
	return	menu_Imp->EnableItem(which);
}


BOOL	 _DLLENTRY Menu:: DisableItem	( uint which )
{
	return	menu_Imp->DisableItem(which);
}


HMENU	 _DLLENTRY Menu::  Handle ( Service s_ID )
{
	if ( s_ID == API_MENU_HMENU )
		return menu_Imp -> Handle(s_ID);
	else
		return NULL;
} 

void _DLLENTRY Menu :: SetAutoUpdate ( uint pos )
{
	menu_Imp->SetAutoUpdate(pos);
}

/*
Menu :: Menu ( const Menu& copyFrom)
{
	menu_Imp = new Menu_Imp (*(copyFrom.menu_Imp), this);
}

Menu & Menu :: operator = ( const Menu & copyFrom)
{
	if ( menu_Imp )
		delete menu_Imp;
	menu_Imp = new Menu_Imp (*(copyFrom.menu_Imp), this);
	return *this;
}

*/
