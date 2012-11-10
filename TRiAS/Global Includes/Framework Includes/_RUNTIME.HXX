/* $Header:   G:/cv.win/pvcs/commonvu/include/_runtime.hxv   3.0.1.0   14 Jul 1992 11:57:34   RONAN  $
 *
 *	_ R u n t i m e. h x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 */
#ifndef _RUNTIME_HXX
#define _RUNTIME_HXX 1

#ifndef _CONTEXT_CXX
#ifndef NOEVENT
#ifndef NOAPP
#include <_dsfix.hxx>

class DispatchWindow : public Window
{
public:
	void   	_WindowInit ( Event e ) 		{ /*DS_fixup AppFixUp;*/ WindowInit ( e );		}
	void   	_MouseButtonDn ( MouseEvt e )		{ /*DS_fixup AppFixUp;*/ MouseButtonDn ( e );	}
	void   	_MouseButtonUp ( MouseEvt e )		{ /*DS_fixup AppFixUp;*/ MouseButtonUp ( e );	}
	void   	_MouseButtonDblClk ( MouseEvt e )	{ /*DS_fixup AppFixUp;*/ MouseButtonDblClk(e);	}
	void   	_MouseMove ( MouseEvt e )		{ /*DS_fixup AppFixUp;*/ MouseMove ( e );		}
	void   	_MouseDrag ( MouseEvt e )		{ /*DS_fixup AppFixUp;*/ MouseDrag ( e );		}
	void   	_KeyDown ( KeyEvt e )			{ /*DS_fixup AppFixUp;*/ KeyDown ( e );		}
	void   	_KeyUp ( KeyEvt e )			{ /*DS_fixup AppFixUp;*/ KeyUp ( e );			}
	void   	_Activate ( Event e )			{ /*DS_fixup AppFixUp;*/ Activate ( e );		}
	void   	_DeActivate ( Event e )			{ /*DS_fixup AppFixUp;*/ DeActivate ( e );		}
	void   	_FocusChange ( FocusChangeEvt e )	{ /*DS_fixup AppFixUp;*/ FocusChange ( e );	}
	void   	_ReSize ( ReSizeEvt e )			{ /*DS_fixup AppFixUp;*/ ReSize ( e );			}
	void   	_Move ( MoveEvt e )			{ /*DS_fixup AppFixUp;*/ Move ( e );			}
	void   	_Expose ( ExposeEvt e )			{ /*DS_fixup AppFixUp;*/ Expose ( e );			}
	BOOL   	_QueryClose ( Event e )			{ /*DS_fixup AppFixUp;*/ return QueryClose(e);	}
	void   	_Close ( Event e )			{ /*DS_fixup AppFixUp;*/ Close ( e );			}
	void   	_MenuInit ( MenuInitEvt e )		{ /*DS_fixup AppFixUp;*/ MenuInit ( e );		}
	void   	_MenuSelect ( MenuSelectEvt e )		{ /*DS_fixup AppFixUp;*/ MenuSelect ( e );		}
	void   	_MenuCommand ( MenuCommandEvt e )	{ /*DS_fixup AppFixUp;*/ MenuCommand ( e );	}
	void   	_VertScroll ( ScrollEvt e )		{ /*DS_fixup AppFixUp;*/ VertScroll ( e );		}
	void   	_HorizScroll ( ScrollEvt e )		{ /*DS_fixup AppFixUp;*/ HorizScroll ( e );	}
	void   	_ButtonClick ( ControlEvt e )		{ /*DS_fixup AppFixUp;*/ ButtonClick ( e );	}
	void   	_ButtonDblClk ( ControlEvt e )		{ /*DS_fixup AppFixUp;*/ ButtonDblClk ( e );	}
	void   	_EditChange ( ControlEvt e )		{ /*DS_fixup AppFixUp;*/ EditChange ( e );		}
	void   	_EditScroll ( ControlEvt e )		{ /*DS_fixup AppFixUp;*/ EditScroll ( e );		}
	void   	_EditFocusChg ( EditFocusChgEvt e )	{ /*DS_fixup AppFixUp;*/ EditFocusChg ( e );	}
	void   	_ListBoxClk ( ControlEvt e )		{ /*DS_fixup AppFixUp;*/ ListBoxClk ( e );		}
	void   	_ListBoxSel ( ControlEvt e )		{ /*DS_fixup AppFixUp;*/ ListBoxSel ( e );		}
	void   	_HelpRequest ( HelpRequestEvt e )	{ /*DS_fixup AppFixUp;*/ HelpRequest ( e );		}
	void  	_Default ( Event e )			{ /*DS_fixup AppFixUp;*/ Default ( e );		}
	long  	_Dispatch ( Event e )			{ return Dispatch ( e ); }																		
	HWND 	_Handle () 				{ return Handle () ;    }
	void  	_Show ( ShowState s = Normal )  	{ Show ( s ) ;   	    }

#if defined(WIN32)
	BOOL 	_MeasureItem (MeasureItemEvt e)		{ /*DS_fixup AppFixUp;*/ return MeasureItem ( e );		}
	BOOL 	_DrawEntireItem (DrawItemEvt e)		{ /*DS_fixup AppFixUp;*/ return DrawEntireItem ( e );	}
	BOOL 	_DrawItemFocus (DrawItemEvt e)		{ /*DS_fixup AppFixUp;*/ return DrawItemFocus ( e );	}
	BOOL 	_DrawItemSelect (DrawItemEvt e)		{ /*DS_fixup AppFixUp;*/ return DrawItemSelect ( e );	}
	BOOL 	_DeleteItem (DeleteItemEvt e)		{ /*DS_fixup AppFixUp;*/ return DeleteItem ( e );		}
	int 	_CompareItem (OwnerDrawEvt e, void *p1, void *p2)	{ /*DS_fixup AppFixUp;*/ return CompareItem (e, p1, p2);		}
	void 	_Strobe (StrobeEvt e)			{ /*DS_fixup AppFixUp;*/ Strobe ( e );		}
	void 	_PaletteChange (PaletteChangeEvt e)	{ /*DS_fixup AppFixUp;*/ PaletteChange ( e );	}

	void	_NfyBeginDrag (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ OnBeginDrag (e); }
	void	_NfyBeginRDrag (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ OnBeginRDrag (e); }
	void	_NfyEndDrag (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ OnEndDrag (e); }
	BOOL	_NfyBeginLabelEdit (NotifyEvt e)	{ /*DS_fixup AppFixUp;*/ return OnBeginLabelEdit (e); }
	void	_NfyEndLabelEdit (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ OnEndLabelEdit (e); }
	BOOL	_NfyQueryInsert (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ return OnQueryInsert (e); }
	void	_NfyInsertItem (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ OnInsertItem (e); }
	BOOL	_NfyQueryDelete (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ return OnQueryDelete (e); }
	void	_NfyDeleteItem (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ OnDeleteItem (e); }
	void	_NfyDeleteAllItems (NotifyEvt e)	{ /*DS_fixup AppFixUp;*/ OnDeleteAllItems (e); }
	void	_NfyGetDispInfo (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ OnGetDispInfo (e); }
	void	_NfySetDispInfo (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ OnSetDispInfo (e); }
	BOOL	_NfyItemChanging (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ return OnItemChanging (e); }
	void	_NfyItemChanged (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ OnItemChanged (e); }
	BOOL	_NfyItemExpanding (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ return OnItemExpanding (e); }
	void	_NfyItemExpanded (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ OnItemExpanded (e); }
	BOOL	_NfySelChanging (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ return OnSelChanging (e); }
	void	_NfySelChanged (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ OnSelChanged (e); }
	void	_NfyClick (NotifyEvt e)			{ /*DS_fixup AppFixUp;*/ OnClick (e); }
	void	_NfyDblClick (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ OnDblClick (e); }
	void	_NfyKeyDown (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ OnKeyDown (e); }
	void	_NfyColumnClick (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ OnColumnClick (e); }
	void	_NfyReset (NotifyEvt e)			{ /*DS_fixup AppFixUp;*/ OnReset (e); }
	void	_NfyBeginAdjust (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ OnBeginAdjust (e); }
	void	_NfyEndAdjust (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ OnEndAdjust (e); }
	void	_NfyCustHelp (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ OnCustHelp (e); }
	BOOL	_NfyGetButtonInfo (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ return OnGetButtonInfo (e); }
	void	_NfyToolBarChange (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ OnToolBarChange (e); }

	void	_NfyNeedText (ToolTipEvt e)		{ /*DS_fixup AppFixUp;*/ OnNeedText (e); }
	void	_NfyHidingTip (ToolTipEvt e)		{ /*DS_fixup AppFixUp;*/ OnHidingTip (e); }
	void	_NfyShowingTip (ToolTipEvt e)		{ /*DS_fixup AppFixUp;*/ OnShowingTip (e); }

	BOOL	_NfyDeltaPos (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ return OnDeltaPos (e); }
	BOOL	_PreTranslateMsg (MSG *pMsg)	{ /*DS_fixup AppFixUp;*/ return PreTranslateMsg (pMsg); }
#endif

//	inline DispatchWindow (void);
};

//inline DispatchWindow::DispatchWindow() {}

#if defined(WIN32)

class PropertySheetDispatchWindow : public CPropertyPage
{
public:
	BOOL	_NfyApply (NotifyEvt e)			{ /*DS_fixup AppFixUp;*/ return OnOK (e); }
	void	_NfyCancel (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ OnCancel (e); }
	BOOL	_NfyQueryCancel (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ return OnQueryCancel (e); }
	int	_NfySetActive (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ return OnSetActive (e); }
	BOOL	_NfyKillActive (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ return OnKillActive (e); }
	void	_NfyHelp (NotifyEvt e)			{ /*DS_fixup AppFixUp;*/ OnHelp (e); }
	int	_NfyWizBack (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ return OnWizBack (e); }
	int	_NfyWizNext (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ return OnWizNext (e); }
	BOOL	_NfyWizFinish (NotifyEvt e)		{ /*DS_fixup AppFixUp;*/ return OnWizFinish (e); }

//	PropertySheetDispatchWindow (void) {}
};
typedef PropertySheetDispatchWindow *pPDW;
#define PPDW_DEFINED	1

#endif // WIN32

typedef DispatchWindow * pDW;
#define PDW_DEFINED 	1
#endif

#endif 
#endif 

inline uint HiWord( ulong l) { return  ((uint)(((l) >> 16) & 0xFFFF)); }
inline uint LoWord( ulong l) { return  ((uint)(l)); }
inline uchar HiByte( uint w) { return  ((uchar)(((uint)(w) >> 8) & 0xFF)); }
inline uchar LoByte( uint w) { return  ((uchar)w); }
inline long MakeLong(int a, int b)  {return (((long)(((uint)(a)) | ((ulong)((uint)(b))) << 16)));}


class	CV_RunTime {

/*
 *	This object "The Interface Object" is for internal implementation use only,
 *	and should never be exposed to the client of CA-CommonView. It allows access
 *	to the private members of selected classes so that the internals may work
 *	but the client should not know how. The object is essentially a dummy class
 *	which contains no functionality of it's own, nor any data. A statis instance
 *	of it called "IF" is created wherever it is required, and will take up one
 *	character of space. No constructor or destructor functions exist, so no mxx
 *	phase is required. As it does not have any useful state, it could exist in
 *	the DLL, but it does not matter much, as the functions should all be simple
 *	inline functions anyway.
 *
 *	Do NOT derive, nor modify this object. Nor should you ever let the client
 *	know about it.
 */
public:
    // Mapping functions
static Point       LogToDev (pWind_Imp, Point);    // * 0.26 *
static Point       DevToLog (pWind_Imp, Point);    // * 0.26 *
static HINSTANCE   ResID_src (ResID r)    { return r.src; }
	
static ResFile_Imp* pResFile_to_pImp( ResourceFile * rf)
				{ return (rf ?  rf -> resFile_Imp : NULL); }

#ifndef NOAPP												// * 0.19 *

//	class	App				-->	interface functions
static	HINSTANCE	ResID_handle (ResID r, pApp_Imp p) { return (r.src ? (HINSTANCE)r.src : (HINSTANCE)p -> hApp); }
static	HINSTANCE	ResID_handle (ResID r, pApp_Imp p, LPCSTR lpszType) 
				{ return (r.src ? 
					  (HINSTANCE)r.src : 
					  (HINSTANCE)p -> FindResourceModule (r, lpszType)); }
static	HINSTANCE	App_hApp (pApp_Imp p) { return p ->hApp; }
static 	pApp_Imp  	pApp_to_pImp (pApp p) { return (p ? p -> app_Imp : 0); }
static	uint		App_appDS( pApp_Imp p) { return p -> DS_segment; }
static	short &		App_WindowCount( pApp_Imp p) { return p->WindowCount; }
static	int		App_Scmd( pApp_Imp p) { return p->status; }
static	HWND &		App_LastDlgHandle (pApp_Imp p) { return	p->LastDlgHandle; }
static	FARPROC		App_EvtDispatch (pApp_Imp p ) { return p->EvtDispatch; }
static	FARPROC&	App_DlgDispatch(pApp_Imp p) { return p->DlgDispatch; }
static	void		App_Exec (pApp_Imp p, ExecType et, BOOL **pAC, CONTINUEMODALPROC pCM = NULL, DWORD dwDataCM = 0L) { p -> Exec (pAC, et, pCM, dwDataCM); }
static	void		App_ResetIdle( pApp_Imp p) { p -> IdleStatus = App_Imp :: IdleNotPresent; }
static	pApp		App_new (HINSTANCE a, HINSTANCE b, pchar c, int d);

#endif // NOAPP												// * 0.19 *

//	class	EventContext	--> interface functions
#ifndef NOEVENT												// * 0.19 *

#ifdef	_DYNALINK

static	HWND &		EventContext_hEContext (pEC_Imp p) { return p->hEContext; }
static	long *		EC_pRetval(pEC_Imp p) { return p -> pRetval; }
static	void		EC_SetpRetval(pEC_Imp p, long *pl) {  p -> pRetval = pl; }
static	void		EC_SetRetval(pEC_Imp p, long l)	{ if (p -> pRetval) *(p -> pRetval) = l; }
static	long		EC_GetRetval(pEC_Imp p)	{ return p -> pRetval ? (*(p -> pRetval)) : 0L; }

#ifndef NOPRINTER
static void		PrinterIdle (Printer *pr) { pr -> Idle(); }
static PrintingDevice_Imp* pPrDev_to_pImp( PrintingDevice * p )	{  return (p ? p -> pd_Imp : NULL); }
static BOOL Printer_Error (Printer * p, Event evt) 
			{ /*DS_fixup AppFixUp;*/
				   return p -> PrinterError((PrinterErrorEvt&)evt); 
			}
#endif


#endif

static	void	EventContext_Invalidate (pEC_Imp p) {	p->hEContext = 0; }
static	int		ValidateWindow ( Wind_Imp * pc); 

#if defined(PDW_DEFINED) && !defined(_CONTEXT_CXX)
static	long EventContext_Dispatch (pEC_Imp p, Event e)
			{ /*DS_fixup AppFixUp;*/
				e.EvtExtra = (void  *)p;
				return ((pDW)(p->pRequestor)) -> _Dispatch (e); 
			}

#if defined(WIN32)
// rudimentäres subclassing für controls
static	long ControlContext_Default (pControl_Imp p, Event e)
			{ /*DS_fixup AppFixUp;*/ return p -> Default (e); }
static	long ControlContext_OnDestroy (pControl_Imp p, Event e)
			{ /*DS_fixup AppFixUp;*/ return p -> OnDestroy (e); }

// rudimentäres subclassing für PropertySheets
static	void PropertySheet_SetResult (pWind_Imp p, int iResult)
			{ /*DS_fixup AppFixUp;*/ ((PSheetWind_Imp *)p) -> result = iResult; }
static	LRESULT PropertySheet_CallWindowProc (pWind_Imp p, UINT uiMsg, WPARAM wParam, LPARAM lParam)
			{ /*DS_fixup AppFixUp;*/ return CallWindowProc(((PSheetWind_Imp *)p) -> m_poldProc, ((PSheetWind_Imp *)p) -> hEContext, uiMsg, wParam, lParam); }
// #HK961014
static	void PropertySheet_EndDlg (pWind_Imp p)
			{ /*DS_fixup AppFixUp;*/ ((PSheetWind_Imp *)p) -> EndDlg(((PSheetWind_Imp *)p) -> result); }
static	void PropertySheet_EndDlg (pWind_Imp p, int iResult)
			{ /*DS_fixup AppFixUp;*/ ((PSheetWind_Imp *)p) -> EndDlg(iResult); }
#endif // WIN32

#endif

static	void		EventContext_EvtEnd (pEC_Imp p) { ((pWind_Imp)p)->EvtEnd (); }	// * 0.18 *

// class Window			-->	interface functions

static 	pWind_Imp  	pWindow_to_pImp (EventContext * p) {  return (pWind_Imp)(p ? p ->  ec_Imp : 0); }

static  pWind_Imp	Window_Parent (pWind_Imp pW) { return pW -> WndParent; }
static	pWindow		Wind_Requestor(pWind_Imp pW) { return (pWindow)(pW -> pRequestor); }
static	void		Window_EnsureCaption(pWind_Imp, uint, BOOL);
static	void		Window_EnsureBorder(pWind_Imp, uint, BOOL);
static	void		Window_UpdateFrame(pWind_Imp);
static	HWND &		Window_Handle (pWind_Imp p ) { return  ((pEC_Imp)p)->hEContext;	}	
static	char *		Window_Capt (pWind_Imp p) { return  p->WndCapt; }	
static	HWND		Handle (pWind_Imp p) { return  ((pEC_Imp)p)->hEContext; }	
static	HWND		SetHandle (pWind_Imp p, HANDLE h) { HWND hT = ((pEC_Imp)p)->hEContext; ((pEC_Imp)p)->hEContext = (HWND)h; return hT; } // #HK980424

static	HDC &		Window_hDC (pWind_Imp p) { return p->hDC; }
static	HDC &		Window_hTargetDC (pWind_Imp p) { return p->hTargetDC; }
static	HDC			Window_GetDC (pWind_Imp p) { return p -> GetDC(); }
static	HDC			Window_SetDC (pWind_Imp p, HANDLE h) { return p -> SetDC(h); }	// #HK980424
static	HDC			Window_GetDrawDC (pWind_Imp p)
			{ p -> DCFlags.BrushNeeded = 1; p -> DCFlags.PenNeeded = 1; return p -> GetDC();}
static	HDC			Window_GetTargetDC (pWind_Imp p)		// #HK940119
			{ return p -> GetTargetDC(); }
static	HDC			Window_SetTargetDC (pWind_Imp p, HANDLE h) { return p -> SetTargetDC(h); }	// #HK980424
static	HDC			Window_GetDrawTargetDC (pWind_Imp p)	// #HK940119
			{ p -> DCFlags.BrushNeeded = 1; p -> DCFlags.PenNeeded = 1; return p -> GetTargetDC(); }

static	Dimension &	Window_WndSize (pWind_Imp p) { return p -> WndSize; }        
static	Point &		Window_WndPosition(pWind_Imp p) { return p -> WndPosition; }        
static	pBrush		Window_WndBrush (pWind_Imp p) { return p -> WndBrush; }
static	pFont		Window_WndFont (pWind_Imp p) { return p -> WndFont; }
static	pPointer &	Window_WndPointer (pWind_Imp p)	{ return p -> WndPointer; }
static	pPen		Window_WndPen( pWind_Imp p) { return p -> WndPen; }				// * 0.29 end *
static	pMenu &		Window_WndMenu( pWind_Imp p) { return p -> WndMenu; } 
static	pBrush		Window_WndBackground (pWind_Imp p) { return p -> WndBackground; }		// * 1.7 End
static	void		SetWndBkBrush (pWind_Imp p, pBrush pbr)	{ p -> WndBackground = pbr; }		// * 1.7 End
static	ulong&		Window_WndStyle( pWind_Imp p) { return p->WndStyle; }
static	uint&		Window_WndFlags( pWind_Imp p) { return p->WndFlags; }
static	void		Window_ResetDC( pWind_Imp p) {  p->DCFlags.Initialised = 0; }
static	BOOL		Window_Initialised( pWind_Imp p) { return (BOOL)(p->WindMgt.Initialised); }
static	BOOL		Window_Redrawable( pWind_Imp p) { return (BOOL)(p->WindMgt.NoRedraw); }
static	BOOL		Window_isMDIWindow( pWind_Imp p) { return (BOOL)(p->WindMgt.isMDIWindow); }
static	void		Window_Draw (pDrawObject, pWind_Imp);  // * 0.31 *
static	void		Window_DrawEx (pDrawObject, pWind_Imp, DWORD);  // * 0.31 *

static	HPROPSHEETPAGE	PropPage_GethPage (pWind_Imp p) { return ((PPageWind_Imp *)p) -> m_hPage; }

#ifndef 	NODIALOG
//	class	DialogWindow		-->	interface functions
static	int&		DialogWindow_Result (pDWind_Imp pdw) { return pdw -> result; }
static	HWND &		Dialog_hModeless (pDWind_Imp pdw) { return pdw -> hModeless; }
static	BOOL		Dialog_isModeless (pDWind_Imp pdw) { return !(pdw -> WindMgt.isModal); }
#endif

//	class	AppWindow		-->	interface functions
static	void		AppWindow_MoveKids(pAWind_Imp);
static	void		AppWindow_EnableAnchor(pWind_Imp, BOOL);

#endif // NOEVENT										 	// * 0.19 *

#ifdef	_DYNALINK

//	class	Accel			-->	interface functions
#ifndef NOACCEL												// * 0.19 *
static	HACCEL		Accel_hAccel (pAccel p) { return (*(pAccel_Imp *)p)->hAccel; }	// * 2.0 *
#endif // NOACCEL											// * 0.19 *

//	class	Icon			-->	interface functions
#ifndef NOICON												// * 0.19 *
static	pIcon_Imp	Icon_Imp (pIcon p) { return *(pIcon_Imp *)p; }
static	HICON		Icon_hIcon ( pIcon p ) { return (*(pIcon_Imp *)p)->hIcon; } // * 2.0 *
static HICON		IconImp_hIcon (pIcon_Imp p) { return p -> hIcon; }
#endif // NOICON												// * 0.19 *

#endif	// _DYNALINK

//	class	Pointer			-->	interface functions

#ifdef	_DYNALINK
#ifndef NOPOINTER											// * 0.19 *
static	HCURSOR		Pointer_hPointer (pPointer p) { return (*(pPointer_Imp *)p)->hPointer; }// * 2.0 *
#endif // NOPOINTER											// * 0.19 *

//	class	Brush			-->	interface functions
#ifndef NOBRUSH												// * 0.19 *
static	HBRUSH &	Brush_hBrush ( pBrush p ) { return (*(pBrush_Imp *)p)->hBrush; } // * 2.0 *
static	BOOL		Brush_isStock(pBrush p) { return (*(pBrush_Imp *)p)->isStock; }
#endif // NOBRUSH											// * 0.19 *

//	class	Pen			-->	interface functions
#ifndef NOPEN												// * 0.19 *
static	HPEN		Pen_hPen ( pPen p ) { return (*(pPen_Imp *)p)->hPen; } // * 2.0 *
#endif // NOPEN												// * 0.19 *

//	class	Bitmap			-->	interface functions
#ifndef NOBITMAP											// * 0.19 *
static	HBITMAP	&	Bitmap_hBitmap (pBitmap p) { return (*(pBitmap_Imp *)p)->hBitmap; } // * 2.0 *
static 	Bitmap_Imp* 	pBitmap_to_pImp (pBitmap bm) { return (bm ? bm -> bitmap_Imp : NULL); }
static	BOOL &		Bitmap_DeviceDependency (pBitmap p) { return (*(pBitmap_Imp *)p)->DeviceDependent; } // * 2.0 *
static  HBITMAP		BitmapImp_hBitmap(pBitmap_Imp p) { return p -> hBitmap; }	// #HK030116
#endif // NOBITMAP											// * 0.19 *

//	class	Font			-->	interface functions
#ifndef NOFONT												// * 0.19 *
static	HFONT		Font_hFont ( pFont p ) { return ( * (pFont_Imp *)p)->hFont; } // * 2.0 *
static	pFont_Imp	Font_Imp ( pFont p ) { return ( * (pFont_Imp *)p); } 		// * 2.0 *
#endif // NOFONT											// * 0.19 *

#endif	// _DYNALINK

//	class	Event			-->	interface functions
#ifndef NOEVENT												// * 0.19 *
static	UINT &		Event_wMsg (Event& e) {	return	e.wMsg; }
static	WPARAM &	Event_wParam (Event& e) { return e.wParam; }
static	LPARAM &	Event_lParam (Event& e) { return e.lParam; }
static	void		Event_SetExtra (Event& e, void *pv) { e.EvtExtra = pv; }
#endif // NOEVENT											// * 0.19 *

//	class	Menu			-->	interface functions
#ifndef NOMENU												// * 0.19 *
static	HMENU &		Menu_hMenu (pMenu p) { return (*(pMenu_Imp *)p)->hMenu;	} // *  2.0 *
static	HMENU		Menu_SethMenuParent (Menu *p, HMENU h) { return (*(pMenu_Imp *)p)->hMenuParent = h; } // *  2.0 *
static  int		Menu_autopos ( Menu *p ) { return (*(pMenu_Imp *)p)->autopos; }
static	HMENU &		MenuImp_hMenu (pMenu_Imp p) { return p->hMenu; } // *  2.0 *
#endif // NOMENU											// * 0.19 *

//	class	Control			-->	interface functions
#ifndef NOCONTROL											// * 0.19 *
static	pControl	Control_Requestor (pControl_Imp p) { return p -> pRequestor; }// * 0.22 Begin *
static  HWND &		Control_hControl (pControl_Imp p) { return p -> hControl; }                     // * 0.22 End *
static 	pControl_Imp 	pControl_to_pImp (pControl p) { return ((p)? p -> control_Imp  : NULL); }	// * 0.16 End *
#endif // NOCONTROL											// * 0.19 *

//	class	ControlEvt		-->	interface functions
#ifndef NOEVENT												// * 0.19 *
static	pControl	ControlEvt_GetControl (pApp_Imp, pControlEvt);

//	class	ScrollEvt		--> interface functions
static	pScrollBar	ScrollEvt_GetScrollBar (pScrollEvt me) { return ( (pScrollBar)(me -> EvtExtra)); }
static	void		ScrollEvt_SetScrollBar (pApp_Imp, pScrollEvt, pAWind_Imp); // * 0.12 *
#endif // NOEVENT											// * 0.19 *

	// class Scroll bar functions			  					
#ifndef NOSCROLLBAR											// * 0.19 *
															// * 0.14 Begin *
static	pScrollBar	WndVertScrollBar__ctor (pWindow pW) { return new WndVertScrollBar (pW); }
static	pScrollBar	WndHorzScrollBar__ctor (pWindow pW) { return new WndHorzScrollBar (pW);	}
static	void		WndVertScrollBar__dtor (pScrollBar pS) { delete (WndVertScrollBar *) pS; }
static	void		WndHorzScrollBar__dtor (pScrollBar pS) { delete ( WndHorzScrollBar  * ) pS; }
static	uint		ScrollBar_SBType (pScrollB_Imp p) { return p->SBType; }
static	void		ScrollBar_SetSBType (pScrollB_Imp p, uint stype) { p->SBType = stype; }
static	void		ScrollBar_SetIgnore (pScrollB_Imp p, uint val) { p->SBIgnoreEndScroll = val; }
static	int		ScrollBar_GetIgnore (pScrollB_Imp p) { return (int)p->SBIgnoreEndScroll; }
static	BOOL		WndScrollBarDisabled( pScrollB_Imp p ) { return (p -> SBDisabled); }	// * 1.13 *
static	pScrollB_Imp	GetScrollImp (ScrollEvt *p) { return  (* ((pScrollB_Imp *)(p -> EvtExtra) )); }	// * 0.14 End *
#endif // NOSCROLLBAR										// * 0.19 *

#ifndef NOHELP
static HelpDisp_Imp*	pHD_to_pImp (HelpDisplay* p) { return (p ? p -> hd_imp : NULL); }
#endif
};


#endif
