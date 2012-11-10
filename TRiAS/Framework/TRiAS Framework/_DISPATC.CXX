/* $Header:   G:/cv.win/pvcs/commonvu/src/_dispatc.cxv   3.0.1.0   14 Jul 1992 11:49:10   RONAN  $
 *
 *	_ d i s p a t c . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	This Module contains the actual generic EventContext dispatcher for
 *	CA-CommonView. This dispatcher finds and locks the instance of the event
 *	context for whom a message has been received, and then invokes its
 *	specific virtual dispatcher. If no event context exists for this message
 *	then invoke the virtual create function for the pending object if any
 *	exists.
 *
 *	Mods log:
 *	0.0	ferg	05oct88	------ Milestone 2.. Beta 2 ship date. --------
 *	0.1	ferg	14oct88	If Window is closed sucessfully then delete it from 
 *						App list of EventContexts.
 *	0.2	ferg	02nov88	if last window closing one do App->Quit.
 *	0.3	ferg	29nov88	Eleventh hour ... ReleaseDC if not already released.
 *						can leave dangling DC's if user overloads Dispatcher.
 *	0.4 jk		29nov88	------ Milestone 2A. Beta 2A shipped ------
 *	0.5 jk		02dec88	Fast Compile defines added.
 *  0.6 rs      14dec88 altered Dispatch to set Event context handle to zero
 *                      upon the receipt of NC_DESTROY
 *	 0.7 ferg	14dec88	need a virtual clean up after event.
 *  0.8 rs      22feb89 Mapping modes for PM compatibility
 *  1.0 rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1 rs 		29jun89 Move initialisng of size and position to position.cxx
 *  1.2 rs		07jul89 -------Release 1.0a ship date ---------------
 *  1.3 rs		22aug89 Removed unneccessary DefWindowProc 
 *	1.4	rs		12oct89 App Idle call shell
 *	1.5 rs,hlj	17Dec89 Updating of window size is needed during WM_MOVE to
 *						ensure correct mapping of points and sizes.
 *	1.6 rs		03Jan89	Flagging of windows to support correct style updating.
 *						Also WndFlags is now used to indicate whether window
 *						is a ModeLessDialog or a DeleteWindow.
 *	1.7 rs		06feb90	Tidied up dispatch using EC_Find
 *	1.8 rs		08feb90 New code to dispatch a window init event 
 *						the first time a new window is used.
 *	1.9 rs		09feb90 Disable WS_SETVISIBLE style in dialogs from resources
 *	2.0 rs		15may90 ===================================================
 *						Conversion to C++ 2.0 
 *						Incorporated dispatch.cxx and position.cxx into
 *						dll.
 *						===================================================
 *	2.1 rs		16May90 Fixup ds on entry to EventDispatcher
 *	2.2 rs		20Jun90 From nc and own additions - hiding.
 *      ls       4Jul92 Moved call to Wind_Imp::Initialise to Show
 */

#include "tfrmpre.hxx"
#include <_Link.hxx>   

static void  ScreenToParent (HWND hwnd, Point *p)
{
HWND hparent;

#if !defined(WIN32)
	if (hparent = (HWND)GetWindowWord(hwnd, GWW_HWNDPARENT))
#else
	if (hparent = (HWND)GetWindowLong(hwnd, GWL_HWNDPARENT))
#endif
		ScreenToClient (hparent, (POINT *)p);
}
 
static void UpdatePos (pWind_Imp pw, HWND hw)
{
	if (IsWindow(hw)) {
	Rectangle r; 

		GetWindowRect (hw, (RECT *)&r);
		Point p (r.Left(), r.Bottom() - 1);	// r.Bottom is one more than actual 
							// bottom position as we are using 
							// Windows co-ordinates.
		ScreenToParent (hw, &p);
		CV_RunTime :: Window_WndPosition (pw) =
			CV_RunTime :: DevToLog (CV_RunTime :: Window_Parent(pw), p);
	}
}

///////////////////////////////////////////////////////////////////////////////
// FensterProcedure
LRESULT WINAPI _DISPATCH_ENTRY
EventDispatcher	( HWND hEContext, UINT ecMsg, WPARAM wParam, LPARAM lParam )
{
	CV_ASSERT_DLLDS();

long retval = 0;
pApp_Imp AppImpInst = _AppImpFind();
Event e;
pWind_Imp pWI;
 	
	CV_RunTime :: Event_wMsg (e)	= ecMsg;
	CV_RunTime :: Event_wParam (e)	= wParam;
	CV_RunTime :: Event_lParam (e)	= lParam;
	if ( (AppImpInst -> ContextList() -> First()) &&
		 (pWI = (pWind_Imp)(AppImpInst -> ContextList() 
		   			->Find ((HANDLE)hEContext ))))
	{	
	// * 0.1  Begin *
		if (ecMsg == WM_SIZE) {
		Dimension dimLoc (LOWORD(lParam), HIWORD(lParam));

			CV_RunTime :: Window_WndSize (pWI) = dimLoc;
			UpdatePos( pWI, hEContext); 			// * 1.1 *
			CV_RunTime :: EventContext_EvtEnd (pWI);	// * 0.7 *		
		} 
		else if (ecMsg == WM_MOVE) {
			UpdatePos (pWI, hEContext);
	    	CV_RunTime :: EventContext_EvtEnd (pWI);
		}				// * 1.5 end *
		retval = CV_RunTime :: EventContext_Dispatch (pWI, e);

	// refind pointer in case of deleteion during Event handler
		if (!(pWI = (pWind_Imp)(AppImpInst -> ContextList() 
					->Find ((HANDLE)hEContext))))
			return retval;

		CV_RunTime :: EventContext_EvtEnd (pWI);

		if (ecMsg == WM_NCDESTROY) {                                           // * 0.6 Start *
	   		AppImpInst -> ContextList() -> Delete((HANDLE)hEContext);
			if (!(AppImpInst -> ContextList()-> First()) && AppImpInst -> QuitOnLast())
				AppImpInst->Quit();			  // * 0.2 *
			CV_RunTime :: Window_Handle( pWI) = 0;
		}                                           // * 0.6 End *
	}										  // * 0.1 End *
	else {
		if (ecMsg == WM_MEASUREITEM && IsWinNT()) {
		// NT versendet WM_MEASUREITEM für ComboBoxen VOR WM_INITDIALOG,
		// also hier Standard verarbeiten
		TEXTMETRIC tm;
		HDC hDC = GetDC (hEContext);
		MEASUREITEMSTRUCT *pMI = (MEASUREITEMSTRUCT *)lParam;

			GetTextMetrics (hDC, &tm);
			if (pMI -> itemHeight < (UINT)tm.tmHeight)
				pMI -> itemHeight = tm.tmHeight;
			ReleaseDC (hEContext, hDC);
			return true;
		}
		if (ecMsg == WM_INITDIALOG) {
			CV_RunTime :: App_LastDlgHandle(AppImpInst) = hEContext;
			SetWindowLong (hEContext, GWL_STYLE, 
					((~WS_VISIBLE) & GetWindowLong (hEContext, GWL_STYLE)));
			return false;	
		}
		else {
		FARPROC fp = (FARPROC)GetWindowLong(hEContext, GWL_WNDPROC);
		
			if (fp == CV_RunTime :: App_EvtDispatch(AppImpInst))
				return DefWindowProc(hEContext, ecMsg, wParam, lParam);
			else {
				return false;	
			}
		}
	}
	
	return	retval;
}	// End of FUNCTION "EventDispatcher"


//	The emitted 'C' must be patched to have '_export' placed before this


/*
 *	Unfortunately, due to inconsistancies in the design of MS-Windows, it is
 *	not possible to use just the generic dispatcher, as the return type for
 *	the dialog dispatcher is not the same. IE :- int versus long. Sorry, however
 *	it is just a trivial instance of a function.
 */


LRESULT WINAPI _DISPATCH_ENTRY
DialogDispatcher(HWND hDialog, UINT dlgMsg, WPARAM dlgwParam, LPARAM dlglParam)
{
	CV_ASSERT_DLLDS();
#if defined(WIN32)
LRESULT lResult = EventDispatcher (hDialog, dlgMsg, dlgwParam, dlglParam);

	SetWindowLong (hDialog, DWL_MSGRESULT, lResult);
	return lResult;
#else
	return (bool)EventDispatcher (hDialog, dlgMsg, dlgwParam, dlglParam);
#endif // WIN32
}	// End of FUNCTION "DialogDispatcher"




LRESULT WINAPI _DISPATCH_ENTRY
CvMdiFrameDispatcher (HWND hEContext, UINT ecMsg, WPARAM wParam, LPARAM lParam)
{
	CV_ASSERT_DLLDS();

pApp_Imp AppImpInst = _AppImpFind();
Event e;				  
long retval = 0;
pWind_Imp pWI;

	CV_RunTime :: Event_wMsg (e)	= ecMsg;
	CV_RunTime :: Event_wParam (e)	= wParam;
	CV_RunTime :: Event_lParam (e)	= lParam;
	if ( (AppImpInst -> ContextList() -> First()) &&
		   (pWI = (pWind_Imp)(AppImpInst -> ContextList() 
		   			-> Find ((HANDLE)hEContext))))
	{	
		if (ecMsg == WM_SIZE) {
		Dimension dimLoc (LOWORD(lParam), HIWORD(lParam));

			CV_RunTime :: Window_WndSize (pWI) = dimLoc;
			UpdatePos (pWI, hEContext); // * 1.1 *
    			CV_RunTime :: EventContext_EvtEnd ( pWI );				// * 0.7 *		
		}
		else if (ecMsg == WM_MOVE) {
			UpdatePos( pWI, hEContext);
			CV_RunTime :: EventContext_EvtEnd (pWI);
		}				// * 1.5 end *
 
		retval = CV_RunTime :: EventContext_Dispatch (pWI, e);

	// refind pointer in case of deleteion during Event handler
		if (!(pWI = (pWind_Imp)(AppImpInst -> ContextList() 
					->Find ((HANDLE)hEContext))))
			return retval;

		CV_RunTime :: EventContext_EvtEnd (pWI);

		if (ecMsg == WM_NCDESTROY) {                                           // * 0.6 Start *
			AppImpInst -> ContextList() -> Delete ((HANDLE)hEContext);
			if (!(AppImpInst -> ContextList()-> First()) && AppImpInst -> QuitOnLast())
				AppImpInst->Quit( );			  // * 0.2 *
			CV_RunTime :: Window_Handle (pWI) = 0;
		}                                           // * 0.6 End *
	} else	
		return DefFrameProc(hEContext, GetWindow (hEContext, GW_CHILD), ecMsg, wParam, lParam);

return retval;
}

LRESULT WINAPI _DISPATCH_ENTRY
CvMdiChildDispatcher( HWND hEContext, UINT ecMsg, WPARAM wParam, LPARAM lParam )
{
	CV_ASSERT_DLLDS();
	
pApp_Imp AppImpInst = _AppImpFind();
Event e;				  
long retval = 0;
pWind_Imp pWI;
 	
	CV_RunTime :: Event_wMsg (e)	= ecMsg;
	CV_RunTime :: Event_wParam (e)	= wParam;
	CV_RunTime :: Event_lParam (e)	= lParam;
	if ((AppImpInst -> ContextList() -> First()) &&
	    (pWI = (pWind_Imp)(AppImpInst -> ContextList() 
	   			-> Find ((HANDLE)hEContext))))
	{	
		if (ecMsg == WM_SIZE) {
		Dimension dimLoc (LOWORD(lParam), HIWORD(lParam));

			CV_RunTime :: Window_WndSize (pWI) = dimLoc;
			UpdatePos( pWI, hEContext); 			// * 1.1 *
			CV_RunTime :: EventContext_EvtEnd (pWI);	// * 0.7 *		
		} else if (ecMsg == WM_MOVE) {
			UpdatePos( pWI, hEContext);
			CV_RunTime :: EventContext_EvtEnd ( pWI );
		}				// * 1.5 end *
 		retval = CV_RunTime :: EventContext_Dispatch (pWI, e);

	// refind pointer in case of deleteion during Event handler
		if (!(pWI = (pWind_Imp)(AppImpInst -> ContextList() 
					->Find ((HANDLE)hEContext))))
			return retval;

		CV_RunTime :: EventContext_EvtEnd (pWI);

		if(ecMsg == WM_NCDESTROY) {                                           // * 0.6 Start *
			AppImpInst -> ContextList() -> Delete((HANDLE)hEContext);
			if (!(AppImpInst -> ContextList()-> First()) && AppImpInst -> QuitOnLast())
				AppImpInst->Quit( );			  // * 0.2 *
			CV_RunTime :: Window_Handle( pWI) = 0;
		}                                           // * 0.6 End *
	} else	
		return DefMDIChildProc(hEContext, ecMsg, wParam, lParam);

return	retval;
}

#if defined(WIN32)
LRESULT WINAPI _DISPATCH_ENTRY
ControlDispatcher (HWND hEContext, UINT ecMsg, WPARAM wParam, LPARAM lParam)
{
	CV_ASSERT_DLLDS();

long retval = 0;
pApp_Imp AppImpInst = _AppImpFind();
Event e;
pControl_Imp pCI;
 	
	if ( (AppImpInst -> ControlList() -> First()) &&
		 (pCI = (pControl_Imp)(AppImpInst -> ControlList() -> Find ((HANDLE)hEContext))))
	{	
	CV_RunTime :: Event_wMsg (e)	= ecMsg;
	CV_RunTime :: Event_wParam (e)	= wParam;
	CV_RunTime :: Event_lParam (e)	= lParam;

        if (ecMsg == WM_DESTROY)
			return CV_RunTime::ControlContext_OnDestroy (pCI, e);

		return CV_RunTime::ControlContext_Default (pCI, e);
	}										  // * 0.1 End *
	return	retval;
}
#endif // WIN32
