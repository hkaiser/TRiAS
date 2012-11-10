/* $Header:   G:/cv.win/pvcs/commonvu/src/_runtime.cxv   3.0.1.0   14 Jul 1992 11:56:06   RONAN  $
 *
 *	_ r u n t i m e . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods log:
 *	0.1	ferg	29sep88	Pick Low order word of lParam as HWND to search for.
 *	0.0 ferg	05oct88	------- Milestone 2. Beta 2 Shipped ---------
 *	0.2	ferg	26oct88	added pWindow parameter to CV_RunTime::AppWindow_Show
 *						for correct handling of children.
 *	0.3	ferg	08nov88	WndSize and WndPosition were being passed to wrong
 *						args of CreateWindow.
 *	0.4	jk		15nov88	from jk 24oct88. Added CV_Runtime::Bitmap__ctor, for 
 *						resource files.
 *  0.5 rs		15Nov88 Added CV_RunTime::ScrollEvt_SetScrollBar(...)
 *	0.6 ferg	21nov88	removed code from Control::Show made control
 *						show virtual.
 *	0.7	ferg	22nov88	AppWndBackground is superceded by WndBackground.
 *	0.8	ferg	23nov88	CV_Runtime::Control_Show .. moved to _control.cxx
 *	0.9	jk		29nov88	------ Milestone 2A. Beta 2A shipped ------
 *	0.10 jk		02dec88	Fast Compile defines added.
 *  0.11 rs     22feb89 Map mode compatibility for PM
 *  0.12 rs     Usage of AppWndPointer is redundant - use WndPointer instead
 * 	0.13 rs		Changes to position window from bottomleft not topleft
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *	1.1 rs		29jun89 Added in code to insert object information on
 *						property list
 *  1.2	rs		07jul89 -------Release 1.0a ship date ---------------
 *	1.3 rs		28aug89	Out of memory error boxes should use style
 *								MB_SYSTEMMODAL | MB_ICONHAND
 *	1.4	rs		06oct89	Allow for minimized and maximised styles in show.
 *	1.5 rs		15Nov89	remove sCmd and CmdLine from App
 *	1.6 rs		05Dec89	remove temporal dependencies in System Menus
 *  1.7 rs		07Dec89 SystemMenu support - CV_RunTime :: SysMenu_retrieve.
 *	1.8 rs		11Dec89	Changes to Font__init to support new Font constructor.
 *	1.9 hl		21Dec89 remove - 1 from DevToLog & LogToDev Functions
 *						and in create window.
 *	1.10 rs		02jan90	Provision of correct dereferencing and cleanup of
 *						strings used by CA-CommonView programs.
 *	1.11 rs		08jan90 CV_RunTime::Window_EnsureCaption()
 *						This function ensures that a caption is provided in the
 *						window for usage of MinBoxes etc.
 *
 *	1.12 hl		29jan90 CV_RunTime::ScrollEvt_GetScrollBar(..)
 *						simplification.
 *	1.13 rs		06feb90	From Ferg (PM version) 
 *						Implementation of Find_EC to simplify dispatch code
 *	1.14 rs		20feb90 Simplified 1.13 and moved it inline for efficiency.
 *	1.15 rs		21feb90 Moved caption into Window.
 *	1.16 rs		27feb90	CV_RunTime :: Window_InitSize 
 *	1.17 hl		28feb90 In MenuInitEvt_Menu need to use high word of lParam
 *						in cases of WM_MENUSELECT
 *	2.0	rs		20Jun90 Changes to runtime for hiding.
 *						Where possible pApp_Imp is used instead of pApp.
 *	2.1 rs		05Apr91 Safe copy of captions
 */

#include "tfrmpre.hxx"
#include	<_Link.hxx>   
														// * 0.5 Begin *

void CV_RunTime::  ScrollEvt_SetScrollBar(pApp_Imp AppImpInst, pScrollEvt me, 
					  pAWind_Imp pWnd)
{
HWND hScroll = GET_WM_HSCROLL_HWND(me -> wParam, me -> lParam);

    	if (!hScroll) {
		if (me -> wMsg == WM_HSCROLL)
			me -> EvtExtra =  pWnd -> AppWndHorz;
		else
			me -> EvtExtra =  pWnd -> AppWndVert;
		return;
    	}
	else {
	pControl_Imp pci = (pScrollB_Imp)( AppImpInst->ControlList()->Find ((HANDLE)hScroll));
	
		if (pci)
			me->EvtExtra = Control_Requestor(pci);
		else
			me->EvtExtra = 0;
	}
}
        
													// * 0.5 End *


pControl CV_RunTime:: ControlEvt_GetControl (pApp_Imp AppImpInst, pControlEvt me)
{
pControl_Imp pci = (pControl_Imp)
		(AppImpInst->ControlList()->Find (
			(HANDLE)GET_WM_COMMAND_HWND(me -> wParam, me -> lParam))
		);

	if (pci)
		return Control_Requestor(pci);
	else
		return 0;
								// * 0.1 line above *
}	// End of "CV_RunTime" FUNCTION "ControlEvt_GetControl"

// * 0.11 start *
// See also AUX1.CXX

Point CV_RunTime::  LogToDev (pWind_Imp pWnd,  Point p )
{
	if (pWnd)
		p.Y() = pWnd -> WndSize.Height() - p.Y() -1 ;
	else {
	pApp_Imp AppImpInst = _AppImpFind();

		p.Y() = AppImpInst -> AppScreenSize.Height() - 1 - p.Y();
	}

return p;
}

Point CV_RunTime::  DevToLog (pWind_Imp pWnd,  Point p)
{
	if (pWnd)
		p.Y() = pWnd -> WndSize.Height() - p.Y() -1;
	else {
	pApp_Imp AppImpInst = _AppImpFind ();

		p.Y() = AppImpInst -> AppScreenSize.Height() - 1 - p.Y();
	}

return p;
}

// * 0.11 End *
void CV_RunTime ::  Window_EnsureCaption(pWind_Imp pw, uint bits, BOOL Adding)	// * 1.11 start *
{
	if (Adding)
		{
		if (!(pw -> WndFlags & WF_LEVEL3))
		{
			pw -> WndFlags |= WF_SIZE_CHANGED;
			pw -> SetStyle(WS_CAPTION);
		}
		pw -> WndFlags |= bits;
	}
	else {
		pw -> WndFlags &= (~bits);
		if (!(pw -> WndFlags & WF_LEVEL3))
		{
			pw -> SetStyle (WS_CAPTION/*BAR*/,false);
			pw -> WndFlags |= WF_SIZE_CHANGED;
		}
	}
}

void CV_RunTime ::  Window_EnsureBorder(pWind_Imp pw, uint bits, BOOL Adding)	// * 1.11 start *
{
	if (Adding)
	{
		if (!(pw -> WndFlags & WF_LEVEL2))
		{
			pw -> WndFlags |= WF_SIZE_CHANGED;
			pw -> SetStyle(WS_BORDER);
		}
		pw -> WndFlags |= bits;
	}
	else {
		pw -> WndFlags &= (~bits);

		if (!(pw -> WndFlags & (WF_LEVEL3 | WF_LEVEL2)))
		{
			pw -> SetStyle(WS_BORDER,false);
			pw -> WndFlags |= WF_SIZE_CHANGED;
		}

	}
}


void CV_RunTime ::  Window_UpdateFrame(pWind_Imp pw)	// * 1.11 start *
{
	if ( Handle(pw))
	{
		if (pw -> WndFlags & WF_SIZE_CHANGED)
		{
	 		SetWindowPos( Handle(pw), NULL, 0,0,0,0,
					SWP_NOSIZE | SWP_NOZORDER | SWP_NOMOVE 
					| SWP_NOREPOSITION | SWP_NOACTIVATE
					| SWP_DRAWFRAME );

			pw -> WndFlags &= (~(WF_SIZE_CHANGED | WF_MENU_CHANGED));
		}
		else if (pw -> WndFlags & WF_MENU_CHANGED)
		{
			char buffer[255];
			GetWindowText( Handle(pw), buffer , 254);
			SetWindowText(Handle(pw), buffer);
			pw -> WndFlags &= (~ WF_MENU_CHANGED);
		}
	}
	else
		pw -> WndFlags &= (~(WF_SIZE_CHANGED | WF_MENU_CHANGED));
}


void	CV_RunTime::  AppWindow_MoveKids	( pAWind_Imp paw)
{
HWND hpaw = Handle(paw);
HDWP hDefer = 0;

	if ((paw -> WindMgt.Anchoring) && 
		GetWindow( hpaw, GW_CHILD))
		{
		pApp_Imp AppImpInst = _AppImpFind();
		AppImpInst -> ControlList() -> LockOrder (true);
		pCVLink	 head =  AppImpInst -> ControlList() -> First();
		if (head)
		 {
		// Try to use deferred positioning
		if (head -> Item())
			{
			hDefer = BeginDeferWindowPos(10);
			CV_ASSERT_VALID(hDefer);
			}
		while (head)
			{
			pControl_Imp pc = (Control_Imp *) (head -> Item());
			if ((pc -> ControlParent == paw) && (pc -> hControl != hpaw))
					// Excluding windows scroll bars
				{
				hDefer = pc -> RePosition(hDefer);
				CV_ASSERT_VALID(hDefer);
				}
			head = head -> Next();
			}
		if (hDefer)
			EndDeferWindowPos(hDefer);
		else
			InvalidateRect ( hpaw, NULL, true );	
		}
		AppImpInst -> ControlList() -> LockOrder (false);
		}
}

void	CV_RunTime::  AppWindow_EnableAnchor	( pWind_Imp paw, BOOL tf)
{
	if (tf) 
		paw -> WindMgt.Anchoring = true;
	else
		paw -> WindMgt.Anchoring = false;
}
							   
void   EnableAnchoring(pAppWindow paw, BOOL tf)
{
	CV_RunTime :: AppWindow_EnableAnchor(CV_RunTime :: pWindow_to_pImp(paw), tf);
}


