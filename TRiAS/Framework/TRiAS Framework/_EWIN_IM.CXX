/* $Header:   G:/cv.win/pvcs/commonvu/src/_ewin_im.cxv   3.0.1.0   14 Jul 1992 11:55:30   RONAN  $
 *
 *	_ e d i t w n d . c x x 
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	0.0	rs      16jan89 Initial development
 *  0.1 rs      24feb89 Due to mapping  considerations it was necessary to
 *                      amalgamate references to a parent window for child
 *                      and dialog windows into a Parent pointer in the general
 *                      Window class and change uses of ChildWindow, etc to
 *                      reflect this.
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1	rs		07jul89 -------Release 1.0a ship date ---------------
 *	1.2 rs		24Nov89	Long -> Void event handlers
 *	1.3	rs		14Jan89 Moved ControlWindow::Show from ctrlwnd.cxx
 *	1.4 rs		07feb90	Use GetCurrentTask instead of _AppFind if only
 *						Handle to App is required.
 *	1.5 rs		27feb90	initialise window size after creation.
 *	1.6 rs		20Mar90	Code to hook in control window correctly.
 *
 *	1.7 hl		22May90 do not call Window::Dispatch for WM_HSCROLL 
 *				& WM_VSCROLL
 *
 *	1.8	rs		Generate dummy scrollbar objects for scrollbars in order
 *				to allow manipulation of range, position etc.
 *
 *	1.9 rs		Allow control windows to recieve and manage all key events.
 *	2.0	pc	11Jun92		Add WM_CTLCOLOR handling to Dispatch, to allow
 *					users to subclass ComboBox, and change its background
 *					and text color.
 *
 */

#include "tfrmpre.hxx"
#include <_Link.hxx>
#include 	<_dsfix.hxx>

class ControlWndVSB : public WndVertScrollBar
{
	public:

	ControlWndVSB(pWindow pw) : WndVertScrollBar(pw) {}
	~ControlWndVSB() { CV_RunTime :: Control_hControl(CV_RunTime :: pControl_to_pImp(this)) = 0; }
};

class ControlWndHSB : public WndHorzScrollBar
{
	public:

	ControlWndHSB(pWindow pw) : WndHorzScrollBar(pw) {}
	~ControlWndHSB() { CV_RunTime :: Control_hControl(CV_RunTime :: pControl_to_pImp(this)) = 0; }
};

CWind_Imp:: CWind_Imp(Window * req, pControl pcc) 
		  : Wind_Imp(req), m_fInitialized(false)
{
pControl_Imp pc = CV_RunTime :: pControl_to_pImp(pcc);

	pctrl = pcc;
	WndParent =  CV_RunTime :: pWindow_to_pImp(pc -> GetParent());  // * 0.1 *

	FInit();
}

BOOL CWind_Imp::FInit (void)
{
	if (m_fInitialized) return true;

pApp_Imp AppImpInst = _AppImpFind();
pControl_Imp pc = CV_RunTime :: pControl_to_pImp(pctrl);

	pc -> ValidateControl();

	hEContext = CV_RunTime :: Control_hControl(pc);
	if (NULL != hEContext) {
	// Stitch up control to include dispatcher
		poldproc = (WNDPROC)SetWindowLong(hEContext, GWL_WNDPROC,
					 (long)EventDispatcher);

	// Insert Window in list of Event Contexts
		AppImpInst -> ContextList() -> Insert((HANDLE)hEContext, this);
		InitSize();

		m_fInitialized = true;
	} else
		return false;	// noch nicht initialisiert

return true;
}

void CWind_Imp::  Default( Event e)
{
	CV_RunTime :: EC_SetRetval(this, 
		CallWindowProc( (WNDPROC)poldproc, CV_RunTime :: Handle (this),
					CV_RunTime :: Event_wMsg (e),
					CV_RunTime :: Event_wParam (e),
					CV_RunTime :: Event_lParam (e)
				));
}

void CWind_Imp::  Expose( ExposeEvt e)
{
	paintflag = true;
	Default((Event&) e);
}

/* *****************************************  */
/*  This window init is called with a         */
/*  mocked up window init event - hence       */
/*  it should Not default to the old dispatch */
/*  procedure which has already been called   */
/* *****************************************  */
void CWind_Imp::  Show(ShowState)	// * 1.13 *
{
	pctrl -> Show();
}									// * 1.13 *

long CWind_Imp::  Dispatch (Event e)
{
LRESULT		retval = 0;
LRESULT	*	oldptr = CV_RunTime :: EC_pRetval(this);
uint ControlType = 0;
	
	CV_RunTime :: EC_SetpRetval(this, &retval);

	switch	( CV_RunTime :: Event_wMsg ( e )) {
	case WM_PAINT: 
	        {
			paintflag = false;
			Report(this, CVEVT_Expose, e );
			((pDW)pRequestor) -> _Expose((ExposeEvt&)e);
			if (!paintflag) {
			Rectangle r;
			
				paintflag = true;
				if (GetUpdateRect(hEContext, (RECT *)&r, false))
				ValidateRect(hEContext, (RECT *)&r);
			}
	        }
	        break;

	case WM_HSCROLL:
		{
		ScrollEvt& k = (ScrollEvt&) (Event&)e;
		ControlWndHSB whsb (CV_RunTime :: Wind_Requestor(this));

			CV_RunTime :: Event_SetExtra (e, (void *)&whsb);
			Report(this, CVEVT_HorizScroll, e);
			((pDW)pRequestor) -> _HorizScroll (k);
		}
		break;

	case WM_VSCROLL:
		{
		ScrollEvt& k = (ScrollEvt&) e;
		ControlWndVSB wvsb (CV_RunTime :: Wind_Requestor(this));

			CV_RunTime :: Event_SetExtra(e, (void*)&wvsb);
			Report(this, CVEVT_VertScroll, e);
			((pDW)pRequestor) -> _VertScroll (k);
		}
		break;

//************************************************************************
// Due to improvements in the keyboard interface, the following section of 
// code appears to be unneccessary.
//************************************************************************
/* 
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		{
		Report(this, CVEVT_KeyDown, e );
		((pDW)pRequestor) -> _KeyDown ((KeyEvt&)e );	
		}
		break;
*/

/*The handling of WM_CTLCOLOR was inserted here to allow the users to change
  the background and text color for combo boxes.  This is because a combobox
  is really three windows : an edit/static, and a list box, both of which are
  children of an ComboBox window. The comboBox window must be subclassed by
  putting it in a ControlWindow to intercept the WM_CTLCOLOR messages.
*/
#if !defined(WIN32)
	case WM_CTLCOLOR:		
		{
			ControlType = HiWord (CV_RunTime::Event_lParam (e));

			switch(ControlType) {
			case CTLCOLOR_EDIT:		
			case CTLCOLOR_LISTBOX:	
			case CTLCOLOR_STATIC:		
				{
				const int  ClassNameLength = 10;
				char ClassName[ClassNameLength];
				HBRUSH hBrush;
				ComboBox_Imp *pCCI;

					GetClassName(hEContext, ClassName, ClassNameLength);

					if ((lstrcmpi (ClassName, "ComboBox") == 0) &&
					    (pCCI = (ComboBox_Imp*)(CV_RunTime :: pControl_to_pImp(pctrl))) &&
					    ( ((TextControl_Imp*)pCCI) -> bManageColor() || pCCI -> bManageBackground() ))
					{
						hBrush = pCCI -> SetColors((HDC)CV_RunTime::Event_wParam(e), ControlType);
						CV_RunTime::EC_SetRetval (this, retval = (LRESULT)(HANDLE)hBrush);
						return (LRESULT)(HANDLE)hBrush;
					}
					else
						((pDW)pRequestor) -> _Default(e);
				}
				break;
			
			default:
				((pDW)pRequestor) -> _Default( e);
				break;
			}
		}
		break;
#else
	case WM_CTLCOLOREDIT:
		ControlType = CTLCOLOR_EDIT;
	//durchfallen
	
	case WM_CTLCOLORLISTBOX:
		ControlType = CTLCOLOR_LISTBOX;
	//durchfallen
	
	case WM_CTLCOLORSTATIC:
		ControlType = CTLCOLOR_STATIC;

		{
		const int  ClassNameLength = 30;
		char ClassName[ClassNameLength];
		HBRUSH hBrush;
		ComboBox_Imp *pCCI;

			GetClassName(hEContext, ClassName, ClassNameLength);

			if ((lstrcmpi (ClassName, "ComboBox") == 0) &&
			    (pCCI = (ComboBox_Imp*)(CV_RunTime :: pControl_to_pImp (pctrl))) &&
			    ( ((TextControl_Imp*)pCCI) -> bManageColor() || pCCI -> bManageBackground() ))
			{
				hBrush = pCCI -> SetColors ((HDC)CV_RunTime::Event_wParam(e), ControlType);
				CV_RunTime::EC_SetRetval (this, retval = (LRESULT)(HANDLE)hBrush);
				return (LRESULT)(HANDLE)hBrush;
			}
			else
				((pDW)pRequestor) -> _Default(e);
		}
		break;

	case WM_HELP:		// an parent weiterleiten
	case WM_CTLCOLORMSGBOX:
	case WM_CTLCOLORBTN:
	case WM_CTLCOLORDLG:
	case WM_CTLCOLORSCROLLBAR:
		((pDW)pRequestor) -> _Default( e);
		break;
#endif

	default:
		Wind_Imp::Dispatch(e);
		break;
	}

	CV_RunTime :: EC_SetpRetval(this, oldptr);

return retval;
}

CWind_Imp::  ~CWind_Imp()
{
	pctrl = 0;
}

pControl CWind_Imp ::  GetControl ()
{
	return pctrl;
}

void CWind_Imp :: 	Hide ()
{ pctrl-> Hide(); }

void CWind_Imp :: 	Enable ()
{ pctrl-> Enable(); }

void CWind_Imp :: 	Disable ()
{ pctrl-> Disable(); }

CvID CWind_Imp :: 	GetID()
{ return pctrl-> GetID(); }

void CWind_Imp :: 	SetFocus()	
{ pctrl-> SetFocus(); }

Point CWind_Imp :: 	ChangePosition ( Point p)
{ return pctrl-> ChangePosition(p); }

Dimension CWind_Imp :: 	ChangeSize ( Dimension d)
{ return pctrl-> ChangeSize(d); }

EWind_Imp:: 	EWind_Imp ( pWindow req, pDialogWindow parent, ResID RscID )
: CWind_Imp(req, new MultiLineEdit (  parent,  RscID ))
{
}

EWind_Imp::  EWind_Imp ( pWindow req, pWindow parent, CvID UsrID, Point p, Dimension d)
  : CWind_Imp(req, new MultiLineEdit ( parent, UsrID, p, d ))
{ }

EWind_Imp::  ~EWind_Imp()
{
    if (GetControl())
        delete (MultiLineEdit*)GetControl();
}


void EWind_Imp ::  SetText( const char* Buffer)
{ ((MultiLineEdit*)GetControl())-> SetText( Buffer ); }

void EWind_Imp :: 		GetText( pchar Buffer, uint maxlen)
{ ((MultiLineEdit*)GetControl())-> GetText( Buffer, maxlen); }

uint   EWind_Imp :: 		GetTextLen()
{ return ((MultiLineEdit*)GetControl())-> GetTextLen(); }

BOOL	EWind_Imp ::   	isModified ()
{ return ((MultiLineEdit*)GetControl())->isModified ();	}

Selection  EWind_Imp ::  	GetSelection ()
{ return ((MultiLineEdit*)GetControl())->GetSelection (); }

void	EWind_Imp :: 	   	ChangeSelection ( Selection s )
{ ((MultiLineEdit*)GetControl())-> ChangeSelection ( s );	} 

void	EWind_Imp :: 	   	SetTextLimit ( uint nChars )
{ ((MultiLineEdit*)GetControl())-> SetTextLimit ( nChars ); }

void	EWind_Imp :: 	   	ReplaceSelected ( const char* Text )
{ ((MultiLineEdit*)GetControl())-> ReplaceSelected ( Text ); }

void	EWind_Imp :: 		DeleteSelected ()
{ ((MultiLineEdit*)GetControl())-> DeleteSelected (); }

uint 	EWind_Imp ::  	GetLine ( uint Index, pchar Buffer, uint nChars )
{ return ((MultiLineEdit*)GetControl())-> GetLine (Index, Buffer, nChars ); }

uint	EWind_Imp :: 	GetNumLines ()
{ return ((MultiLineEdit*)GetControl())-> GetNumLines (); }

void	EWind_Imp :: 	ScrollVertical ( uint nLines )
{ ((MultiLineEdit*)GetControl())-> ScrollVertical ( nLines ); }

void	EWind_Imp :: 				ScrollHoriz ( uint nChars )
{ ((MultiLineEdit*)GetControl())-> ScrollHoriz ( nChars ); }

void	EWind_Imp :: 				PageUp ()
{ ((MultiLineEdit*)GetControl())-> PageUp (); }

void	EWind_Imp :: 				PageDown ()
{ ((MultiLineEdit*)GetControl())-> PageDown (); }

void	EWind_Imp :: 				LineUp ()
{ ((MultiLineEdit*)GetControl())-> LineUp (); }

void	EWind_Imp :: 				LineDown ()
{ ((MultiLineEdit*)GetControl())-> LineDown (); }

BOOL	EWind_Imp :: 	Undo ()
{
return ((MultiLineEdit*)GetControl())-> Undo ();
}


