/* $Header:   G:/cv.win/pvcs/commonvu/src/_event.cxv   3.0.1.0   14 Jul 1992 11:55:26   RONAN  $
 *
 *	_ e v e n t . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	0.0	ferg	05oct88	--------- Milestone 2. Beta 2 shipped --------
 *	0.1	ferg	02nov88	code from event.cxx moved here, Event.cxx is now
 *						defunct. Minor changes to code to get AppInst from
 *						DLL.
 *	0.2	rs		17nov88	ferg from rs 27oct 88. Convert ThumbScroll type to 
 *						EndScroll.
 *	0.3	rs		17nov88	ferg from rs 03nov88 and 14nov88 support for window
 *						scroll bars.
 *	0.4	ferg	18nov88 isWindowScroll member of ScrollEvt.
 *	0.5 jk		29nov88	------ Milestone 2A. Beta 2A shipped ------
 *	0.6	jk		02dec88	Fast Compile defines added.
 *  0.7 rs      08feb88 Changes for IsWindowScroll
 *  0.8 rs      Mapping mode compatibility 
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1 rs		23jun89	Exposed area rect returns 0 .. ymax,  not 0 .. ymax -1
 * 						need to cater for this.
 * 	1.2 rs		05jul89	NewOrigin previously returned wrong origin for
 *						child windows.
 *  1.3	rs		07jul89 -------Release 1.0a ship date ----------------
 *	1.4 hlj		19Dec89	rs from hlj - updates to key event handling and 
 *						move event handling.
 *	1.5 rs		21Dec89 GetExposedArea returns wrong rectangle
 *	1.6 hl		16feb90 isShiftButton & isControlButton work for
 *						for all Mouse events						
 *						
 */

#include "tfrmpre.hxX"
#include	<_Link.hxx>   


#define SYSTEM_KEYCODE		0x20000000

static ScrollType ScrollType_Convert (uint scrolltype)
{
	switch (scrolltype) {
	case SB_BOTTOM:		return ToBottomRight;
	case SB_LINEDOWN:	return UnitIncrement;
	case SB_LINEUP:		return UnitDecrement;
	case SB_PAGEDOWN:	return BlockIncrement;
	case SB_PAGEUP:		return BlockDecrement;
	case SB_THUMBPOSITION:	return EndScrollThumb;          					// * 0.2 * 
	case SB_THUMBTRACK:	return ThumbDrag;
	case SB_TOP:		return ToTopLeft;
	default:		return EndScroll;          					// * 0.2 * 
	}

return	EndScroll;
}	// End of FUNCTION "ScrollType_Convert"

														// * 0.1 Begin *
pMenu	_DLLENTRY MenuInitEvt::  GetMenu	()
{
	if ((wMsg == WM_INITMENUPOPUP) && HIWORD (lParam))
		return	(pMenu)(_AppImpFind() -> MenuList() -> Find ((HANDLE)wParam));
	else
	 	return CV_RunTime :: Window_WndMenu ((pWind_Imp)EvtExtra);
}	// End of "MenuInitEvt" FUNCTION "GetMenu"


pMenu	_DLLENTRY MenuSelectEvt::  GetMenu	()
{
#if !defined(WIN32)
	if (lParam & MF_SYSMENU)
		return (pMenu)(_AppImpFind() -> MenuList() -> Find (HIWORD(lParam)));
#else
	if (HIWORD(wParam) & MF_SYSMENU)
		return (pMenu)(_AppImpFind() -> MenuList()  -> Find ((HANDLE)lParam));
#endif
	else
	 	return CV_RunTime :: Window_WndMenu((pWind_Imp)EvtExtra);
}	// End of "MenuSelectEvt" FUNCTION "GetMenu"


pMenu	 _DLLENTRY MenuCommandEvt::  GetMenu	(void)
{
	if (wMsg == WM_SYSCOMMAND)
		return	(pMenu)( _AppImpFind() -> MenuList()
			->Find ((HANDLE)GetSystemMenu (CV_RunTime :: Handle ((pWind_Imp)EvtExtra), false)));
	else
	 	return CV_RunTime :: Window_WndMenu ((pWind_Imp)EvtExtra);

}	

char * _DLLENTRY MenuSelectEvt :: GetString (char * buf , int i)
{
#if !defined(WIN32)
	if (lParam & MF_SYSMENU) {
#else
	if (HIWORD(wParam) & MF_SYSMENU) {
#endif
		if ((GetMenuString(GetSystemMenu (
					CV_RunTime :: Handle ((pWind_Imp)EvtExtra), false),
					LOWORD(wParam), buf, i, MF_BYCOMMAND)) != 0)
	        	return buf;
	        else
	        	return (0);
	}
	else {
		if ((GetMenuString (GetMenu()->Handle(),
					LOWORD(wParam), buf, i, MF_BYCOMMAND)) != 0)
			return buf;
		else
			return (0);
	}
}



char * _DLLENTRY MenuCommandEvt :: GetString (char * buf , int i)
{
	if ((GetMenuString(GetMenu()->Handle(),
			LOWORD(wParam), buf, i, MF_BYCOMMAND)) != 0)
		return buf;
	else
		return (0);
}
        
pControl _DLLENTRY ControlEvt::  GetControl	()
{
	return	CV_RunTime :: ControlEvt_GetControl (_AppImpFind(), this ); // * 0.1 *
}	



BOOL	 _DLLENTRY MouseEvt::  isLeftButton	()		// true if left button is pressed.
{
	switch	(wMsg) {
	case WM_LBUTTONUP:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		return	true;

	case WM_MOUSEMOVE:
		return	(( wParam & LeftButton ) == LeftButton );

#if defined(WIN32)
	case WM_NOTIFY:
		return (((LPNMHDR)lParam) -> code == NM_CLICK) || 
		       (((LPNMHDR)lParam) -> code == NM_DBLCLK);
		break;
#endif
	default:
		break;
	}	// End of SWITCH

return	false;
}	// End of "MouseEvt" FUNCTION "isLeftButton"


BOOL	 _DLLENTRY MouseEvt::  isMiddleButton	()	// true if mid button is pressed.
{
	switch	(wMsg) {
	case WM_MBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONDBLCLK:
		return	true;

	case WM_MOUSEMOVE:
		return	(( wParam & MiddleButton ) == MiddleButton );

	default:
		break;
	}	// End of SWITCH

return	false;
}	// End of "MouseEvt" FUNCTION "isMiddleButton"


BOOL	 _DLLENTRY MouseEvt::  isRightButton	()		// true if right button is pressed.
{
	switch	(wMsg) {
	case WM_RBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
		return	true;

	case WM_MOUSEMOVE:
		return	(( wParam & RightButton ) == RightButton );

#if defined(WIN32)
	case WM_NOTIFY:
		return (((LPNMHDR)lParam) -> code == NM_RCLICK) || 
		       (((LPNMHDR)lParam) -> code == NM_RDBLCLK);
		break;
#endif
	default:
		break;
	}	// End of SWITCH

return	false;
}	// End of "MouseEvt" FUNCTION "isRightButton"


BOOL	 _DLLENTRY MouseEvt::  isShiftButton	()		// true if shift is pressed.
{
#if defined(WIN32)
	return	wMsg != WM_NOTIFY && ((wParam & ShiftButton ) == ShiftButton);// * 1.6 *
#else
	return	((wParam & ShiftButton ) == ShiftButton);// * 1.6 *
#endif 
}	// End of "MouseEvt" FUNCTION "isShiftButton"


BOOL	 _DLLENTRY MouseEvt::  isControlButton	()	// true if control is pressed.
{
#if defined(WIN32)
	return wMsg != WM_NOTIFY && ((wParam & ControlButton ) == ControlButton); // * 1.6 *
#else
	return	((wParam & ControlButton ) == ControlButton); // * 1.6 *
#endif 
}	// End of "MouseEvt" FUNCTION "isControlButton"


Buttons	 _DLLENTRY MouseEvt::  ButtonID ()		// returns which button was pressed.
{
	switch	(wMsg) {
	case WM_LBUTTONUP:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		return	LeftButton;

	case WM_MBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONDBLCLK:
		return	MiddleButton;

	case WM_RBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
		return	RightButton;

	case WM_MOUSEMOVE:
		return	((Buttons)(wParam & MK_MASK));

#if defined(WIN32)
	case WM_NOTIFY:
		switch (((LPNMHDR)lParam) -> code) {
		case NM_CLICK:
		case NM_DBLCLK:
			return	LeftButton;

		case NM_RCLICK:
		case NM_RDBLCLK:
			return	RightButton;
		}
		break;
#endif
	}	// End of SWITCH

return	(Buttons)0;	// No Keys
}	// End of "MouseEvt" FUNCTION "ButtonID"


// *****************************************************************************
// * MouseEvt :: Where - returns point at which mouse event took place
// * Mouse events are returned from Windows as screen co-ordinates
// * It is necessary to convert these to Client co-ordinates 
// * relative to the bottom left corner of the client area before 
// * returning the result to the caller.
// *****************************************************************************
Point	 _DLLENTRY MouseEvt::  Where	()			
{
#if defined(WIN32)
	if (wMsg == WM_NOTIFY) return Point(0, 0);
#endif

short x = LOWORD(lParam);
short y = HIWORD(lParam);
Point pt (x, y);
	
	return CV_RunTime ::  DevToLog ( (pWind_Imp)EvtExtra, pt);
}	

CoOrd	 _DLLENTRY ReSizeEvt::  GetNewHeight	()		// returns the new height of the window.
{
short c = HIWORD(lParam);

	return c;
//	return	(*((Dimension*)(&lParam))) . Height ();
}	


CoOrd _DLLENTRY ReSizeEvt::  GetNewWidth ()		// returns the new width of the window.
{
//	return	(*((Dimension*)(&lParam))) . Width ();
short c = LOWORD(lParam);

	return c;
}	// End of "ReSizeEvt" FUNCTION "GetNewWidth"


Dimension _DLLENTRY ReSizeEvt::  GetNewSize ()	// returns the new size of the window.
{
short x = LOWORD(lParam);
short y = HIWORD(lParam);

	return Dimension (x, y);
}	// End of "ReSizeEvt" FUNCTION "GetNewSize"


Point _DLLENTRY MoveEvt::  NewOrigin ()		// returns the new window origin.
{
Point p = CV_RunTime :: Window_WndPosition ((pWind_Imp)EvtExtra);

	return p; 
}


BOOL	 _DLLENTRY FocusChangeEvt::  gotFocus ()	// returns true if the window is
{										// receiving FOCUS.
#if defined(WIN32)
	return ((wMsg == WM_SETFOCUS) || (wMsg == WM_NOTIFY && ((LPNMHDR)lParam) -> code == NM_SETFOCUS));
#else
	return	(wMsg == WM_SETFOCUS);
#endif
}	


BOOL	 _DLLENTRY KeyEvt::  isSystem ()			// returns true if it is a system key.
{
	return	(lParam & SYSTEM_KEYCODE  ? true : false);	// Check if alt key is depressed ?
}


short _DLLENTRY KeyEvt::  Keycode ()			// returns the code of the key pressed
{
	if (wMsg == WM_CHAR) {
	uint retval = ((pWind_Imp)EvtExtra) -> GetVirtKey();

		if (retval == (-1)) {
		uint scancode = (uint)((lParam & 0x00ff0000) >> 16) ;
			
			retval = MapVirtualKey(scancode, 1);
		}
		return retval;
	}
	else
		return	wParam;
}


short	 _DLLENTRY KeyEvt::  Repeat	()		// If the key is held returns the
{											// number of repeats that occured.
	return	LOWORD(lParam);
}


char	 _DLLENTRY KeyEvt::  ASCIIChar	()
{
										// * 1.4 * start
	if( wMsg == WM_CHAR)
		return	(char)(wParam);
	else
//	if ( (((wMsg == WM_KEYUP) || (wMsg == WM_SYSKEYUP))) && 
//		(((wParam >= 0x30) && (wParam < 0x70)) || (wParam == KeySpace)))
		{
		uint scancode = (uint)((lParam & 0x00ff0000) >> 16) ;
		unsigned char keyState[256];
		unsigned char result[5];

			GetKeyboardState(keyState);
#if defined(WIN32)
			if (ToAscii(wParam , scancode, keyState, (LPWORD)result, 1) == 1)
#else
			if (ToAscii(wParam , scancode, keyState, (LPDWORD)result, 1) == 1)
#endif
				return result[0];
		}
	return (char)0;
}	


//
// As CA-CommonView uses a bottom left co-ordinate system, the Exposed area
// returns a rectangle whose bottom-right corner is outside the drawing area.
// Need to offset by 1 to compensate for this.
//
Rectangle	 _DLLENTRY ExposeEvt::  GetExposedArea	()	// returns the area to be repainted.
{
Rectangle r;                                        // * 0.8 start *
Wind_Imp *current_wnd = (Wind_Imp *)EvtExtra;

	if (current_wnd -> GetPaintInfo())
		r = ((pPaintStruct)(current_wnd -> GetPaintInfo()) )->rcPaint;
	else
		GetUpdateRect(CV_RunTime :: Handle(current_wnd), (RECT *)&r, false);
//
// Only transform co-ordinates if Rectangle is not empty
//
	if (r.Top() || r.Bottom() || r.Right() || r.Left()) {
#ifdef RECT_INCLUSIVE
		r.Bottom() = 										// * 1.1 start *
			CV_RunTime :: DevToLog( (pWind_Imp) EvtExtra, r.LowerRight()).Y() + 1;	// * 1.5 *
		r.Top() = 
			CV_RunTime :: DevToLog( (pWind_Imp) EvtExtra, r.UpperLeft()).Y();	// * 1.5 *
														// * 1.1 end *
#else
		r.Bottom() = 										// * 1.1 start *
			CV_RunTime :: DevToLog( (pWind_Imp) EvtExtra, r.LowerRight()).Y() + 1;	// * 1.5 *
		r.Top() = 
			CV_RunTime :: DevToLog( (pWind_Imp) EvtExtra, r.UpperLeft()).Y() + 1;	// * 1.5 *
														// * 1.1 end *
#endif
	}

return r;                                           // * 0.8 end *
}


uint	 _DLLENTRY MenuSelectEvt::  GetItemID	()
{
	return LOWORD(wParam);
}	// End of "MenuSelectEvt" FUNCTION "GetItemID"


uint	 _DLLENTRY MenuCommandEvt::  GetItemID	()
{
	return LOWORD(wParam);
}	// End of "MenuCommandEvt" FUNCTION "GetItemID"


pScrollBar	 _DLLENTRY ScrollEvt::  GetScrollBar	()
{
HWND hWndl = GET_WM_HSCROLL_HWND(wParam, lParam);

	if (!hWndl)
		return ((Wind_Imp*)EvtExtra) -> GetWndScrollBar((wMsg == WM_HSCROLL) ? SB_HORZ : SB_VERT);
	else {
	pControl_Imp pci = (pScrollB_Imp)_AppImpFind()->ControlList()->Find ((HANDLE)hWndl);
	
		return (pci ? ((ScrollBar *) CV_RunTime :: Control_Requestor (pci)) : (ScrollBar*) 0);
	}
}	// End of "ScrollEvt" FUNCTION "GetScrollBar"
															// * 0.1 End *

ScrollType	 _DLLENTRY ScrollEvt::  GetScrollType	()
{
	return ScrollType_Convert (LOWORD(wParam));
}	// End of "ScrollEvt" FUNCTION "GetScrollType"

int	 _DLLENTRY ScrollEvt::  GetPos	()
{
pScrollBar 	pSB = GetScrollBar();

Range 		rng; 
int 	 	retval = GetOldPos();  
uint	  	Block; 
uint	   	Unit; 

	if (pSB) {
		rng = pSB -> GetRange();
		Block = pSB -> GetBlock();
		Unit = pSB -> GetUnit ();
	}
	else {
	// Assume default block and unit
		Block = 1;
		Unit = 1; 

	// Calculate Range
	int rMin, rMax;

	// If no CA-CommonView scroll Bar calculate stats from scratch.
	uint SBType;
	HWND hScroll = GET_WM_HSCROLL_HWND(wParam, lParam);

		if (hScroll)
			SBType = SB_CTL;
		else {
			hScroll = ((Wind_Imp*)EvtExtra) -> Handle();
			SBType = (wMsg == WM_HSCROLL) ? SB_HORZ : SB_VERT;
		}
		GetScrollRange (hScroll, SBType, &rMin, &rMax);
		rng = Range (rMin, rMax);
	}

	switch	(LOWORD(wParam)) {
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		retval = GET_WM_HSCROLL_POS(wParam, lParam);
		break;

	case SB_LINEDOWN:
		retval = ( (retval + ((int)Unit)) > rng.Max()) ? rng.Max() : retval + Unit;
		break;

	case SB_LINEUP:
		retval = ( (retval - ((int)Unit)) < rng.Min()) ? rng.Min() : retval - Unit;
		break;

	case SB_PAGEUP:
		retval = ((retval - ((int)Block)) < rng.Min()) ? rng.Min() : retval - Block;
		break;

	case SB_PAGEDOWN:
		retval = (retval + ((int)Block) > rng.Max()) ? rng.Max() : retval + Block;
	
	default:
		break;
	}	

return	retval;
}	

int	 _DLLENTRY ScrollEvt::  GetOldPos	()
{
pScrollBar pSB;

	if (pSB = GetScrollBar())
		return pSB -> GetThumbPos();
	else {
	// If no CA-CommonView scroll Bar calculate stats from scratch.
	uint SBType;
	HWND hScroll = GET_WM_HSCROLL_HWND(wParam, lParam);

		if (hScroll)
			SBType = SB_CTL;
		else
		{
			hScroll = ((Wind_Imp*)EvtExtra) -> Handle();
			SBType = (wMsg == WM_HSCROLL) ? SB_HORZ : SB_VERT;
		}
	
	return GetScrollPos (hScroll, SBType);
	}
}
															// * 0.3 End *

BOOL  _DLLENTRY ScrollEvt:: 	isWindowScroll ()
{
	return (GET_WM_HSCROLL_HWND(wParam, lParam) != NULL) ? false : true;
}

CvID  _DLLENTRY ControlEvt::  GetControlID	()
{
	return	(CvID(LOWORD(wParam)));
}	

BOOL _DLLENTRY EditFocusChgEvt :: gotFocus()
{
#if !defined(WIN32)
	return (HIWORD(lParam) == EN_SETFOCUS);
#else
	return (HIWORD(wParam) == EN_SETFOCUS);
#endif
}

Rectangle _DLLENTRY PrinterExposeEvt::  GetExposedArea	()	// returns the area to be repainted.
{
	 return *((Rectangle*)EvtExtra);
}

int _DLLENTRY PrinterExposeEvt::  GetPageNumber()
{
	return wParam;
}

// #HK940214 ------------------------------------------------------------------
// ExposeEvt, der an CDCWindows geschickt wird --------------------------------
Rectangle _DLLENTRY CDCExposeEvt :: GetExposedArea (void)
{
	return *((Rectangle*)EvtExtra);
}

BOOL _DLLENTRY ComboFocusChgEvt :: gotFocus()	// #HK940302
{
#if !defined(WIN32)
	return (HIWORD(lParam) == CBN_SETFOCUS);
#else
	return (HIWORD(wParam) == CBN_SETFOCUS);
#endif
}

#if defined(WIN32)
// Neue Events sowie ihre Memberfunktionen ------------------------------------
// allgemeiner OwnerDrawEvent
OwnerDrawEvt::OwnerDrawControl OwnerDrawEvt :: ItemType (void) 
{
	return (OwnerDrawEvt::OwnerDrawControl)((DRAWITEMSTRUCT *)lParam) -> CtlType;	
	// bei allen an der gleichen Position in der Struktur
}

// Event, wenn ein Item aus List-/ComboBox gelöscht wird ----------------------
void *DeleteItemEvt :: GetItemData (void) 
{
	return (void *)(((DELETEITEMSTRUCT *)lParam) -> itemData);
}

int DeleteItemEvt :: GetItemID (void) 
{
	return ((DELETEITEMSTRUCT *)lParam) -> itemID;
}

// Event, wenn ein Item neu gezeichnet werden muß -----------------------------
void *DrawItemEvt :: GetItemData (void) 
{
	return (void *)(((DRAWITEMSTRUCT *)lParam) -> itemData);
}

int DrawItemEvt :: GetItemID (void) 
{
	return ((DRAWITEMSTRUCT *)lParam) -> itemID;
}

int DrawItemEvt::GetCtrlID (void)		// #HK970823
{
	return ((DRAWITEMSTRUCT *)lParam) -> CtlID;
}

HANDLE DrawItemEvt :: Handle (Service s) 
{
	switch (s) {
	case API_CONTROL_HDC:
		return (HANDLE)((DRAWITEMSTRUCT *)lParam) -> hDC;

	case API_CONTROL_HCONTROL:
		return (HANDLE)((DRAWITEMSTRUCT *)lParam) -> hwndItem;

	default:
		return NULL;
	}
}

Rectangle DrawItemEvt :: ItemSize (void) 
{
Rectangle locRc;

	CopyRect ((LPRECT)&locRc, (LPRECT)&((DRAWITEMSTRUCT *)lParam) -> rcItem);

return locRc;
}

BOOL DrawItemEvt :: isDisabled (void) 
{
	return ((DRAWITEMSTRUCT *)lParam) -> itemState & ODS_DISABLED;
}

BOOL DrawItemEvt :: hasFocus (void) 
{
	return ((DRAWITEMSTRUCT *)lParam) -> itemState & ODS_FOCUS;
}

BOOL DrawItemEvt :: isSelected (void) 
{
	return ((DRAWITEMSTRUCT *)lParam) -> itemState & ODS_SELECTED;
}

// Event, wenn Größe eines Items bestimmt werden soll
void *MeasureItemEvt :: GetItemData (void) 
{
	return (void *)(((MEASUREITEMSTRUCT *)lParam) -> itemData);
}

void MeasureItemEvt :: SetItemHeight (CoOrd iH) 
{
	((MEASUREITEMSTRUCT *)lParam) -> itemHeight = iH;
}

void MeasureItemEvt :: SetItemWidth (CoOrd iW) 
{
	((MEASUREITEMSTRUCT *)lParam) -> itemWidth = iW;
}

HWND MeasureItemEvt :: Handle (Service s) 
{
	switch (s) {
	case API_DLGWINDOW_HWND:
	// FensterHandle des DialogFensters liefern
		return *(HWND *)EvtExtra;

	default:
		return 0;
	}
}

int MeasureItemEvt :: GetItemID (void) 
{
	return ((MEASUREITEMSTRUCT *)lParam) -> itemID;
}


// DefaultHandler für die neuen EventHandler ----------------------------------
BOOL Window :: DeleteItem (DeleteItemEvt e) 
{
	Default ((Event &)e);
	return FALSE;		// keine Behandlung
}

BOOL Window :: DrawEntireItem (DrawItemEvt e) 
{
	Default ((Event &)e);
	return FALSE;		// keine Behandlung
}

BOOL Window :: MeasureItem (MeasureItemEvt e) 
{
	Default ((Event &)e);
	return FALSE;
}

BOOL Window :: DrawItemFocus (DrawItemEvt e) 
{
Rectangle Rc = e.ItemSize();			// aktuellen Bereich holen

	DrawFocusRect ((HDC)e.Handle (API_CONTROL_HDC), (RECT *)&Rc);

return TRUE;
}

BOOL Window :: DrawItemSelect (DrawItemEvt e) 
{
Rectangle Rc = e.ItemSize();			// aktuellen Bereich holen

	InvertRect ((HDC)e.Handle (API_CONTROL_HDC), (RECT *)&Rc);

return TRUE;
}

int Window :: CompareItem (OwnerDrawEvt, void *Item1, void *Item2) 
{
	return strcmp ((const char *)Item1, (const char *)Item2);
}

// EventBehandlung für TimerInterrupts ----------------------------------------
void Window :: Strobe (StrobeEvt e) 
{
	Default ((Event &)e);
}

BOOL Window :: SetStrobe (pTimer pt) 
{
	if (Handle())
		return SetTimer (Handle(), pt -> ID(), pt -> Interval(), 0);
	else
        	return FALSE;
}

BOOL Window :: CancelStrobe (pTimer pt) 
{
	if (Handle ())
		return KillTimer (Handle(), pt -> ID());
	else
		return false;
}

// PalettenBehandlung ---------------------------------------------------------
void Window :: PaletteChange (PaletteChangeEvt e) 
{
	Default ((Event &)e);
}

pControl NotifyEvt :: GetControl (void)
{
	return (pControl)CV_RunTime::Wind_Requestor((pWind_Imp)EvtExtra);
}

CvID NotifyEvt :: GetControlID (void)
{
	return ((LPNMHDR)lParam) -> idFrom;
}

NMHDR *NotifyEvt :: GetNotifyInfo (void)
{
	return (LPNMHDR)lParam;
}

UINT ToolTipEvt :: GetToolTipID (void)
{
	return (UINT)wParam;
}

///////////////////////////////////////////////////////////////////////////////
// #HK970116
BOOL Window::PreTranslateMsg (MSG *pMsg)
{
	return false;	// Standard: nicht bearbeitet
}

#endif // WIN32
