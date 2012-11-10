/* $Header:   G:/cv.win/pvcs/commonvu/src/_service.cxv   3.0.1.0   14 Jul 1992 11:56:08   RONAN  $
 *
 *	_ S E R V I C E . C X X
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 * 
 *	Author : Fergal Dearle.
 *
 *	System Dependant services ie class Handle functions.
 *
 *	Mods Log:
 *	Created 1-9-89	by ferg.
 *	1.0		rs	16Nov89		Modified for MS-Windows implementation
 */

#include "tfrmpre.hxx"

HWND	 _DLLENTRY EventContext::  Handle(Service )
{
	return CV_RunTime::Handle((pWind_Imp)ec_Imp);
}

// #HK980424
HWND _DLLENTRY EventContext::SetHandle (Service s, HANDLE hH)
{
	return CV_RunTime::SetHandle((pWind_Imp)ec_Imp, hH);
}

HWND	 _DLLENTRY Window::Handle ( Service s_ID )
{
	if (NULL == this) return NULL;

	switch ( s_ID )	{
	case API_WINDOW_HWND:
		return CV_RunTime::Handle((pWind_Imp)ec_Imp);

	case API_WINDOW_HDC:
		return (HWND)CV_RunTime::Window_hDC((pWind_Imp)ec_Imp);

	case API_WINDOW_TARGETHDC:		// #HK940119
		return (HWND)CV_RunTime::Window_GetTargetDC ((pWind_Imp)ec_Imp);

	default:
		return 0;
	}
}

// #HK980424
HWND _DLLENTRY Window::SetHandle (Service s_ID, HANDLE hH)
{
	if (NULL == this) return NULL;

	switch ( s_ID )	{
	case API_WINDOW_HWND:
		return CV_RunTime::SetHandle((pWind_Imp)ec_Imp, hH);
	
	case API_WINDOW_HDC:
		return (HWND)CV_RunTime::Window_SetDC((pWind_Imp)ec_Imp, hH);
	
	case API_WINDOW_TARGETHDC:		// #HK940119
		return (HWND)CV_RunTime::Window_SetTargetDC ((pWind_Imp)ec_Imp, hH);
	
	default:
		return 0;
	}
}

HWND	 _DLLENTRY ShellWindow::Handle ( Service s_ID )
{
	if (NULL == this) return NULL;

	switch ( s_ID )	{
	case API_MDICLIENT_HWND:
		return ((ShellWind_Imp*)CV_RunTime::pWindow_to_pImp(this)) -> ClientWindow();
	default:
		return Window::Handle(s_ID);
	}
}

HWND	 _DLLENTRY DialogWindow::  Handle ( Service s_ID )
{
	if (NULL == this) return NULL;

	switch ( s_ID )	{
	case API_WINDOW_HWND:
		return CV_RunTime::Handle((pWind_Imp)ec_Imp);
	case API_WINDOW_HDC:
		return (HWND)CV_RunTime::Window_hDC((pWind_Imp)ec_Imp);
	case API_DIALOG_HMODELESS:
		return CV_RunTime::Dialog_hModeless (  (pDWind_Imp)ec_Imp);
	default:
		return NULL;
	}
}
