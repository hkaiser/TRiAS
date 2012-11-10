  //	Usage: #include <CommonVu.hxx>
//
//	Public interface to CA-CommonView 3.1, 
//
//	Computer Associates Portable Windows Application Framework
//
//  Copyright (c) 1992 Trischford Limited 
//  (A wholly owned subsidary of Computer Associates International, Inc)
//  All Rights Reserved
//
//	Version 3.1			Nov 1992
//
//	Tab stops in this file are at	4 * n + 1
//
//-------------------------------------------------------------------------
#ifndef	_COMMONVU_HXX
#define	_COMMONVU_HXX

#if !defined(STRICT)
#define STRICT	1
#endif

#if !defined(MSWIND)
#define MSWIND	1
#endif

#if !defined(WIN32)
#include <print.h>
#else
#include <commctrl.h>		// für neue Controls
#endif

#include <stdlib.h>

#include <cxxtypes.hxx>
#include <cv_types.hxx>
#include <cv_defs.h>

class _TF_ENTRY32 Pair
{
protected:
	CoOrd		a;
	CoOrd		b;

	Pair (void);
	Pair (CoOrd, CoOrd);
};

class _TF_ENTRY32 Point : public Pair
{
public:
	Point (void);
	Point (CoOrd x, CoOrd y);

CoOrd &		X (void);
CoOrd &		Y (void);

CoOrd GetX (void) const;
CoOrd GetY (void) const;
};


class _TF_ENTRY32 Dimension : public Pair
{
public:
	Dimension (void);
	Dimension (CoOrd width, CoOrd height);

CoOrd &		Width (void);
CoOrd &		Height (void);
};


class _TF_ENTRY32 Range : public Pair
{
public:
	Range (void);
	Range (CoOrd minimum, CoOrd maximum);

CoOrd &		Min (void);
CoOrd &		Max (void);
};


class _TF_ENTRY32 Selection : public Pair
{
public:
	Selection (void);
	Selection (CoOrd start, CoOrd end);

CoOrd &		Start (void);
CoOrd &		End (void);
};


class _TF_ENTRY32 Rectangle
{
#ifdef MSWIND
	CoOrd		left;
	CoOrd		top;
	CoOrd		right;
	CoOrd		bottom;
#elif PM
	CoOrd		left;
	CoOrd		bottom;
	CoOrd		right;
	CoOrd		top;
#endif

public:
	Rectangle (void);
	Rectangle (Point topleft, Point bottomright);
	Rectangle (CoOrd t, CoOrd l, CoOrd b, CoOrd r);
	Rectangle (Point topleft, Dimension size);

Point		UpperLeft (void);
Point		LowerRight (void);
CoOrd &		Left (void);
CoOrd &		Right (void);
CoOrd &		Top (void);
CoOrd &		Bottom (void);

CoOrd 		Width (void);		// #HK971112
CoOrd 		Height (void);

Rectangle	Union (rRectangle);
BOOL		PtInRect (Point);
};

class _TF_ENTRY32 ResourceFile
{
private:
friend class CV_RunTime;
	ResFile_Imp	*resFile_Imp;

public:
	ResourceFile (const char *, BOOL fInsert = false);
	~ResourceFile (void);

};

class _TF_ENTRY32 CvID
{
	uint 		id;
	const char *str;

friend BOOL operator==(uint n, CvID id);
friend BOOL operator==(const char*s, CvID id);

public:
	CvID(uint);
	CvID(const char *);

operator	uint(void);
operator 	const char *(void);
BOOL operator==(uint);
BOOL operator==(const char*);
BOOL operator==(CvID &);
};

class _TF_ENTRY32 ResID : public CvID
{
friend class CV_RunTime;
	HINSTANCE		src;
	
public:
	ResID (uint);
	ResID (uint , ResourceFile *);
	ResID (const char *, ResourceFile * = 0);

	HINSTANCE Handle (void) { return src; }
};


#ifndef NORESSTRING

class _TF_ENTRY32 ResString
{
	int		length;
	char *		string;

public:
	ResString (ResID, uint len);
	ResString(const ResString&);

ResString&	operator=(const ResString&);
const char *	Addr (void);
int		Len (void);
operator 	const char* (void);

	~ResString (void);
};

#endif // NORESSTRING

#ifndef NOACCEL
class _TF_ENTRY32 Accel
{
	Accel_Imp *	accel_Imp;

public:
		Accel (ResID);
		Accel (HACCEL);

HACCEL		Handle (Service = 0);

		~Accel (void);
};

#endif // NOACCEL
#ifndef NOCOLOR

class _TF_ENTRY32 Color
{
#ifdef MSWIND
	ColorVal		R;
	ColorVal		G;
	ColorVal		B;
#elif PM
	ColorVal		B;
	ColorVal		G;
	ColorVal		R;
#endif
	ColorVal		_reserved;

public:
	Color (void);
	Color (Colors);
	Color (ColorVal r, ColorVal g, ColorVal b);

	ColorVal &	Red (void);
	ColorVal &	Green (void);
	ColorVal &	Blue (void);
	ColorVal &	Reserved (void) { return _reserved; }	// #HK920730
};

#endif // NOCOLOR
#ifndef NOAPP

class CFreeStore;

class App {
friend class CV_RunTime;
protected:
	App_Imp *	app_Imp;

	_TF_ENTRY32 	App (void);
public:
static 	_TF_ENTRY32 HINSTANCE	Handle (Service = 0);
static	int		Exec (ExecType = ExecNormal);
static	_TF_ENTRY32 int	Exec (ExecType et, BOOL **ppac);
	void		Idle (InvokeStatus);
static 	_TF_ENTRY32 void		Quit (void);

	void	Start (void);
	void	Start (const int argc, const char *argv[]);

static 	_TF_ENTRY32 long	Run (const char *);
	
	CFreeStore *InitApp (CFreeStore *pFS);		// #HK931205
	void DeInitApp (void);
	
	_TF_ENTRY32 ~App (void);

#if defined(WIN32)
// #HK960214: Einbinden der MFC-Hierarchie
	_TF_ENTRY32 PRETRANSLATEPROC AttachPreTranslateProc (PRETRANSLATEPROC pFcn);
	_TF_ENTRY32 PRETRANSLATEPROC DetachPreTranslateProc (void);
	_TF_ENTRY32 IDLEPROC AttachIdleProc (IDLEPROC pF);
	_TF_ENTRY32 IDLEPROC DetachIdleProc (void);

	_TF_ENTRY32 BOOL QuitOnLast (void);
	_TF_ENTRY32 void SetQuitOnLast (BOOL fFlag = true);
#endif // WIN32
};

#ifdef MSCC8
_TF_ENTRY32 int _DLLENTRY CallAppExec (ExecType et);
#endif

#endif // NOAPP
#ifndef NOCURSOR

class _TF_ENTRY32 Cursor
{
	pCursor_Imp	cursor_Imp;

public:
	Cursor (pWindow, Dimension, BOOL greyed);
	Cursor (pWindow, pBitmap);

HWND		Handle (Service = 0);
void		Show (void);
void		Hide (void);
Point		GetPos (void);
void		ChangePos (Point);
uint		GetBlinkTime (void);
void		ChangeBlinkTime (uint mSecs);

	~Cursor (void);
};

#endif // NOCURSOR
#ifndef NOPOINTER

class _TF_ENTRY32 Pointer
{
	pPointer_Imp pointr_Imp;

public:
	Pointer (StdPointer = Arrow);
	Pointer (ResID);
	Pointer (HCURSOR);
	Pointer (LPCSTR pcCursor, StdPointer = Arrow);
	Pointer (HCURSOR, BOOL);		// #HK970824

HCURSOR		Detach (void);			// #HK970824
HCURSOR		Handle (Service = 0);
void		Show (void);
void		Hide (void);
Point		GetPos (void);
void		ChangePos (Point);
void		Confine (Rectangle);

	~Pointer (void);
};

#endif // NOPOINTER
#ifndef NOBRUSH

class _TF_ENTRY32 Brush
{
	pBrush_Imp	brush_Imp;

public:
	Brush (StdBrush = WhiteBrush);
	Brush (Color, StdHatchStyle = SolidHatch);
	Brush (pBitmap);
	Brush (HBRUSH);
	Brush (HBRUSH hBr, BOOL fAutoDetach);

HBRUSH	Detach (void);
HBRUSH	Handle (Service = 0);

	~Brush (void);
};

#endif // NOBRUSH
#ifndef NOBITMAP

class _TF_ENTRY32 Bitmap
{
friend class CV_RunTime;
	pBitmap_Imp	bitmap_Imp ;

public:
	Bitmap (ResID);
	Bitmap (ResID, LPCOLORMAP pMap, int iMapSize, UINT uiFlags = 0);
	Bitmap (Dimension, BOOL mono = true, pushort bits = 0);
	Bitmap (HBITMAP);
	Bitmap (HBITMAP, BOOL fAutoDetach);

HBITMAP		Detach (void);
HBITMAP		Handle (Service = 0);
ulong		GetBits (ulong nBytes, pushort bits);
ulong		SetBits (ulong nBytes, pushort bits);
Dimension	GetSize (void);
void		SetSize (Dimension);

	~Bitmap (void);
};

#endif // NOBITMAP
#ifndef NOPEN

class _TF_ENTRY32 Pen
{
	pPen_Imp	pen_Imp;

public:
	Pen (StdLineStyle, uint width, Color);
	Pen (HPEN);
	Pen (HPEN, BOOL fAutoDetach);

HPEN		Detach (void);
HPEN		Handle (Service = 0);

	~Pen (void);

	Color GetColor();
	CoOrd GetWidth();
	StdLineStyle GetStyle();
};

#endif // NOPEN
#ifndef NOFONT

#if !defined(_TRIAS_OLDIMPLEMENTATION2)
class _TF_ENTRY32 CVFont
#else 
class _TF_ENTRY32 Font
#endif // _TRIAS_OLDIMPLEMENTATION2
{
protected:
	pFont_Imp	font_Imp;

public:
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
	CVFont (StdFamily, Dimension, const char * = 0);
#if _MSC_VER >= 1100
	CVFont (StdFonts);
#else
	CVFont (StdFont);
#endif
	CVFont (HFONT);
	CVFont (HFONT, BOOL fAutoDetach);
   	~CVFont (void); 
#else 
	Font (StdFamily, Dimension, const char * = 0);
#if _MSC_VER >= 1100
	Font (StdFonts);
#else
	Font (StdFont);
#endif
	Font (HFONT);
	Font (HFONT, BOOL fAutoDetach);
   	~Font (void); 
#endif // _TRIAS_OLDIMPLEMENTATION2

void 		Init (void);
HFONT		Handle (Service = 0);
HFONT		Detach (void);

BOOL		isLight (void);
BOOL		isNormal (void);
BOOL		isBold (void);
   
BOOL		isItalic (void);
BOOL		isUnderline (void);
BOOL		isStrikethru (void);
   
BOOL		isPitchFixed (void);
BOOL		isPitchVariable (void);

void		SetLight (void);
void		SetNormal (void);
void		SetBold (void);

void		SetItalic (void);
void		SetUnderline (void);
void		SetStrikethru (void);

void		SetFixedPitch (void);
void		SetVariablePitch (void);

short 		SetOrientation (short newOr);
short 		SetEscapement (short newEsc);

	BOOL	GetLogFont (LOGFONT **ppLogFont);
}; 

#endif // NOFONT
#ifndef NOICON

class _TF_ENTRY32 Icon
{
	pIcon_Imp	icon_Imp;

public:
	Icon (StdIcon = StandardIcon);
	Icon (ResID);
	Icon (HICON);
	Icon (HICON, BOOL fAutoDeatch);

HICON		Handle (Service = 0);
HICON		Detach (void);

	~Icon (void);
};

#endif // NOICON
#ifndef NOMESSBOX

class _TF_ENTRY32 MessBox
{
protected:
	pMessBox_Imp 	messBox_Imp;

	MessBox (void);

public:
	MessBox (const char * caption, const char *text, pWindow parent);

HWND		Handle (Service = 0);

StdMessBox	GetType (void);
void		SetType (StdMessBox);
StdMessBoxReply	Show (void);

	~MessBox (void);
};


class _TF_ENTRY32 ErrorBox : public MessBox
{
public:
	ErrorBox (const char * text, pWindow parent);
};

class _TF_ENTRY32 InfoBox : public MessBox
{
public:
	InfoBox (const char* caption, const char* text, pWindow parent);
};

class _TF_ENTRY32 WarningBox : public MessBox
{
public:
	WarningBox (const char* caption, const char* text, pWindow parent);
};

#endif // NOMESSBOX

#ifndef NOMENU

class _TF_ENTRY32 Menu
{
protected:
	pMenu_Imp	menu_Imp;

	Menu (void *new_menu);

public:
	Menu (ResID);
	Menu (HMENU);
	Menu (void);
	Menu (HMENU, BOOL fAutoDetach);

HMENU		Handle (Service = 0);
HMENU		Detach (void);

BOOL		AppendItem (uint itemID, const char * newItem);
BOOL		AppendItem (uint itemID, pBitmap newItem);
BOOL		AppendItem (pMenu subMenu, const char * menuHeader);

BOOL		InsertItem (uint itemID, const char * newItem, uint where); 
BOOL		InsertItem (uint itemID, pBitmap newItem, uint where);
BOOL		InsertItem (pMenu subMenu, const char * menuHeader, uint where);

BOOL		DeleteItem (uint which);
BOOL		DeleteItem (pMenu);

BOOL		AppendSeparator (void);
BOOL		InsertSeparator (uint where);
BOOL		CheckItem (uint which);
BOOL		unCheckItem (uint which);
BOOL		EnableItem (uint which);
BOOL		DisableItem (uint which);

void		SetAutoUpdate (uint menu);

	~Menu (void);
};

class _TF_ENTRY32 SysMenu : public Menu
{
protected:
	SysMenu (pWindow parent);

public:
	~SysMenu (void);
};

#endif // NOMENU
#ifndef NOEVENT

class _TF_ENTRY32 Event
{
friend class CV_RunTime;
protected:
	UINT		wMsg;	// the message type
#ifdef MSWIND
	WPARAM		wParam;
	LPARAM		lParam;
#elif PM
	ulong		lParam1;
	ulong		lParam2;
#endif
	void *		EvtExtra;

public:		// added following functions: #HK960913
	UINT &Msg (void);
	WPARAM &WParam (void);
	LPARAM &LParam (void);

// ADDED: #HK970809
	Event (void);
	Event (UINT WMsg, WPARAM WParam = 0, LPARAM LParam = 0, void *pExtra = NULL);
};

class _TF_ENTRY32 MouseEvt : public Event
{
public:
BOOL		isLeftButton (void);
BOOL		isMiddleButton (void);
BOOL		isRightButton (void);
BOOL		isShiftButton (void);
BOOL		isControlButton (void);

Buttons		ButtonID (void);
Point		Where (void);
};	

class _TF_ENTRY32 ReSizeEvt : public Event
{
public:
CoOrd		GetNewHeight (void);
CoOrd		GetNewWidth (void);
Dimension	GetNewSize (void);
};


class _TF_ENTRY32 MoveEvt : public Event
{
public:
Point		NewOrigin (void);
};

class _TF_ENTRY32 FocusChangeEvt : public Event
{
public:
BOOL		gotFocus (void);
};

class _TF_ENTRY32 KeyEvt : public Event
{
public:
BOOL		isSystem (void);
short		Keycode (void);
short		Repeat (void);
char		ASCIIChar (void);
};


class _TF_ENTRY32 ExposeEvt : public Event
{
public:
Rectangle	GetExposedArea (void);
};

class _TF_ENTRY32 MenuInitEvt : public Event
{
public:
pMenu		GetMenu (void);
};

class _TF_ENTRY32 MenuSelectEvt : public Event
{
public:
pMenu		GetMenu (void);
uint		GetItemID (void);
char*      	GetString(char*, int);
};

class _TF_ENTRY32 MenuCommandEvt : public Event
{
public:
pMenu		GetMenu (void);
uint		GetItemID (void);
char*       	GetString(char*, int);
};

class _TF_ENTRY32 ScrollEvt : public Event
{
public:
pScrollBar	GetScrollBar (void);
ScrollType	GetScrollType (void);
int		GetPos (void);
int		GetOldPos (void);
BOOL		isWindowScroll (void);
};

class _TF_ENTRY32 ControlEvt : public Event
{
public:
pControl	GetControl (void);
CvID		GetControlID (void);
};

class _TF_ENTRY32 EditFocusChgEvt : public ControlEvt
{
public:
BOOL		gotFocus (void);
};

class _TF_ENTRY32 ComboFocusChgEvt : public ControlEvt
{
public:
BOOL		gotFocus (void);
};

class _TF_ENTRY32 HelpRequestEvt : public Event
{
public:
HelpType	RequestType(void);
uint 		GetItemID(void);
Point		Where(void);
WindowArea	GetWindowArea(void);
#if defined(WIN32)
const HELPINFO *GetHelpInfo (void);
#endif
};

#ifndef NOPRINTER

class _TF_ENTRY32 PrinterExposeEvt : public Event {
public:
Rectangle	GetExposedArea (void);
int		GetPageNumber(void);
};

class _TF_ENTRY32 PrinterErrorEvt : public Event {
public:
enum ErrorType { FatalDeviceError,
		 UserAbort,
		 NoDiskSpace,
		 NoMemSpace,
		 GeneralError };

ErrorType	GetErrorType(void);
};
#endif

// #HK940119
class _TF_ENTRY32 CDCExposeEvt : public Event {
public:
Rectangle	GetExposedArea (void);
};

#if defined(WIN32)
class _TF_ENTRY32 OwnerDrawEvt : public ControlEvt {
public:
	enum OwnerDrawControl {
		OwnerDrawButton = ODT_BUTTON,
		OwnerDrawComboBox = ODT_COMBOBOX,
		OwnerDrawListBox = ODT_LISTBOX,
		OwnerDrawMenu = ODT_MENU,
	};
	OwnerDrawControl ItemType (void);
};

class _TF_ENTRY32 DeleteItemEvt : public OwnerDrawEvt {
public:
	void *GetItemData (void);	// zugehörige Daten lesen
	int GetItemID (void);		// ItemID
};

class _TF_ENTRY32 MeasureItemEvt : public OwnerDrawEvt {
public: 
	void SetItemHeight (CoOrd);	// Größe des Items setzen
	void SetItemWidth (CoOrd);
	void *GetItemData (void);	// zugehörige Daten lesen
	HWND Handle (Service);
	int GetItemID (void);		// ItemID
};

class _TF_ENTRY32 DrawItemEvt : public OwnerDrawEvt {
public:
	Rectangle ItemSize (void);	// Größe holen
	BOOL isDisabled (void);		// Item ist disabled
	BOOL hasFocus (void);		// Item hat Focus
	BOOL isSelected (void);		// Item ist selektiert
	void *GetItemData (void);	// zugehörige Daten lesen
	HANDLE Handle (Service);	// hDC/hWnd holen
	int GetItemID (void);		// ItemID
	int GetCtrlID (void);		// ControlID
};


class StrobeEvt : public Event {
public:
	uint GetStrobeID (void) { return wParam; }
};

class Timer {
private:
	uint millisecs;
	uint timerID;

public:
		Timer (uint msecs, uint ID = 1) 
			{ millisecs = msecs; timerID = ID; }
	uint ID (void) { return timerID; }
	uint Interval (void) { return millisecs; }
};
typedef Timer * pTimer;

class PaletteChangeEvt : public Event {
public:
	enum PalAction { 
		PaletteIsChanging = WM_PALETTEISCHANGING,
		PaletteChanged = WM_PALETTECHANGED,
		QueryNewPalette = WM_QUERYNEWPALETTE,
	};

	PalAction GetPalAction (void) { return (PalAction)wMsg; }
	HWND hPalChgWnd (void) { return (HWND)wParam; }
};

class _TF_ENTRY32 NotifyEvt : public Event {
public:
	pControl GetControl (void);
	CvID GetControlID (void);
	NMHDR *GetNotifyInfo (void);
};

class _TF_ENTRY32 ToolTipEvt : public NotifyEvt {
public:
	UINT GetToolTipID (void);
};

#endif // WIN32

class _TF_ENTRY32 EventContext
{
friend class CV_RunTime;
protected:
	EC_Imp *	ec_Imp;

	EventContext (void);

virtual long Dispatch (Event);
virtual void Default (Event);

	HWND Handle (Service s = 0);
	HWND SetHandle (Service s = 0, HANDLE hH = NULL);
	 
virtual		~EventContext (void);
public:

};

class _TF_ENTRY32 Window : public EventContext
{
protected:
	Window (void);

virtual void		WindowInit (Event);
virtual void		MouseButtonDn (MouseEvt);
virtual void		MouseButtonUp (MouseEvt);
virtual void		MouseButtonDblClk (MouseEvt);
virtual void		MouseMove (MouseEvt);
virtual void		MouseDrag (MouseEvt);
virtual void		KeyDown (KeyEvt);
virtual void		KeyUp (KeyEvt);
virtual void		Activate (Event);
virtual void		DeActivate (Event);
virtual void		FocusChange (FocusChangeEvt);
virtual void		ReSize (ReSizeEvt);
virtual void		Move (MoveEvt);
virtual void		Expose (ExposeEvt);
virtual BOOL		QueryClose (Event);
virtual void		Close (Event);
virtual void		MenuInit (MenuInitEvt);
virtual void		MenuSelect (MenuSelectEvt);
virtual void		MenuCommand (MenuCommandEvt);
virtual void		VertScroll (ScrollEvt);
virtual void		HorizScroll (ScrollEvt);
virtual void		ButtonClick (ControlEvt);
virtual void		ButtonDblClk (ControlEvt);
virtual void		EditChange (ControlEvt);
virtual void		EditScroll (ControlEvt);
virtual void		EditFocusChg (EditFocusChgEvt);
virtual void		ListBoxClk (ControlEvt);
virtual void		ListBoxSel (ControlEvt);
virtual void		HelpRequest(HelpRequestEvt);
#if defined(WIN32)
// OwnerDrawEvents ------------------------------------------------------------
virtual BOOL 		MeasureItem (MeasureItemEvt);	// Größe eines Elements bestimmen
virtual BOOL 		DrawEntireItem (DrawItemEvt);	// Element vollständig malen
virtual BOOL 		DrawItemFocus (DrawItemEvt);	// Element mit Focus zeichnen
virtual BOOL 		DrawItemSelect (DrawItemEvt);	// Element ausgewählt zeichnen
virtual BOOL 		DeleteItem (DeleteItemEvt);		// Element ist gelöscht
virtual int 		CompareItem (OwnerDrawEvt, void *, void *);	// Vergleich zweier Einträge

virtual void 		Strobe (StrobeEvt);		// TimerMsg (WM_TIMER)
virtual void 		PaletteChange (PaletteChangeEvt);	// div. PalettenMsgs

// CommonControl notifications ------------------------------------------------
// -->> return true to cancel operation, false to allow it !!
virtual void 		OnClick (NotifyEvt);		// für alle Ctrls
virtual void 		OnDblClick (NotifyEvt);		//

virtual void		OnBeginDrag (NotifyEvt);	// TreeView, ListView, Toolbar
virtual void		OnBeginRDrag (NotifyEvt);	// TreeView, ListView
virtual void		OnEndDrag (NotifyEvt);		// Toolbar
virtual BOOL		OnBeginLabelEdit (NotifyEvt);	// TreeView, ListView
virtual	void		OnEndLabelEdit (NotifyEvt);	// TreeView, ListView
virtual BOOL		OnQueryInsert (NotifyEvt);	// Toolbar
virtual void		OnInsertItem (NotifyEvt);	// ListView
virtual BOOL		OnQueryDelete (NotifyEvt);	// Toolbar
virtual void		OnDeleteItem (NotifyEvt);	// TreeView, ListView
virtual void		OnDeleteAllItems (NotifyEvt);	// ListView
virtual void		OnGetDispInfo (NotifyEvt);	// TreeView, ListView
virtual void		OnSetDispInfo (NotifyEvt);	// TreeView, ListView
virtual void		OnItemChanged (NotifyEvt);	// ListView
virtual BOOL		OnItemChanging (NotifyEvt);	// ListView
virtual void		OnItemExpanded (NotifyEvt);	// TreeView
virtual BOOL		OnItemExpanding (NotifyEvt);	// TreeView
virtual void		OnSelChanged (NotifyEvt);	// TreeView
virtual BOOL		OnSelChanging (NotifyEvt);	// TreeView
virtual void 		OnColumnClick (NotifyEvt);	// ListView
virtual void 		OnKeyDown (NotifyEvt);		// TreeView, ListView
virtual void 		OnReset (NotifyEvt);		// Toolbar
virtual void 		OnBeginAdjust (NotifyEvt);	// Toolbar
virtual void 		OnEndAdjust (NotifyEvt);	// Toolbar
virtual void 		OnCustHelp (NotifyEvt);		// Toolbar
virtual void 		OnToolBarChange (NotifyEvt);	// Toolbar
virtual BOOL		OnGetButtonInfo (NotifyEvt);	// Toolbar, true == ok !

// spezielle ToolTipNotifikationen
virtual void 		OnNeedText (ToolTipEvt);
virtual void 		OnHidingTip (ToolTipEvt);
virtual void 		OnShowingTip (ToolTipEvt);

virtual BOOL		OnDeltaPos (NotifyEvt);		// SpinButton

#endif // WIN32

public:
HWND		Handle (Service = 0);
HWND		SetHandle (Service s = 0, HANDLE hH = NULL);		// #HK980424
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
void		SetStyle (ulong, CVOnOff = CVOn);
#else
void		SetStyle (ulong, OnOff = On);
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)

	Window (HWND hWnd);		// #HK940119


virtual void		Show (ShowState = Normal);
void		Hide (void);
void		Enable (void);
void		Disable (void);

void		SetCaption (const char *);
void		UpdateCaption (const char *);
void		Update (void); 
void		RePaint (void);
void		RePaintRect (Rectangle region);
Point		ChangePosition (Point);
Dimension		ChangeSize (Dimension);
void		CanvasErase (void);
void		CanvasErase (Rectangle &rRc);
void		SetFocus (void);
void		ToTop (void);
Rectangle		CanvasRect (void);
Rectangle		WindowRect (void);
Dimension		TextSize (const char *);
BOOL		isIconic (void);
BOOL		isVisible (void);
BOOL		isZoomed (void);
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
void		MouseTrap (CVOnOff = CVOn);
#else
void		MouseTrap (OnOff = On);
#endif // _TRIAS_OLDIMPLEMENTATION2

// Painting and drawing functions
void		TextPrint (const char *, Point);
void		TextPrintf (Point, const char *, ...);
void		TextPrintf ( const char *, ...);
Point		MoveTo (Point);
void		LineTo (Point);
void		PaintRectangle (Rectangle, PaintMode = Fill);
void		Draw (pDrawObject);
void		DrawEx (pDrawObject, DWORD);	// #HK940121
void    	Scroll (Dimension offset, Rectangle, BOOL clip = true);

// Selection functions
pAccel		ChangeAccel (pAccel);
pBrush		ChangeBackground (pBrush);
pBrush		ChangeBrush (pBrush);
pFont		ChangeFont (pFont);
pMenu		ChangeMenu (pMenu);
pPen		ChangePen (pPen);
pPointer	ChangePointer (pPointer);

// Query functions
pWindow		GetParent(void);
Point		GetPosition (void);
Dimension	GetSize (void);
char *		GetCaption (char *, int);
pAccel		GetAccel (void);
pBrush		GetBackground (void);
pBrush		GetBrush (void);
pFont		GetFont (void);
pMenu		GetMenu (void);
pPen		GetPen (void);
pPointer	GetPointer (void);

void		EnableHelp(BOOL = true, HelpDisplay * AutoHelp = 0);

#if defined(WIN32)
BOOL 		SetStrobe (pTimer);
BOOL 		CancelStrobe (pTimer);

BOOL		DestroyWindow (void);					// #HK970824
#endif // WIN32

	~Window(void);

pWndVertScroll		EnableVScroll (BOOL = true);	// #HK940711
pWndHorzScroll		EnableHScroll (BOOL = true);

	HWND Detach (void);
	HDC SetDrawTarget (HDC hDC);
	HDC GetDrawTarget (void);
	LRESULT ForwardEvent (Event e);
	void PostEvent (Event e);						// #HK960915

// #HK970903
	LRESULT ForwardEvent (UINT wMsg, WPARAM wParam = 0, LPARAM lParam = 0);
	void PostEvent (UINT wMsg, WPARAM wParam = 0, LPARAM lParam = 0);

virtual BOOL DrawCallUp (DrawObject *pDO, BOOL fForce);			// #HK960320
virtual BOOL PreTranslateMsg (MSG *pMsg);			// #HK970116
};


class _TF_ENTRY32 AppWindow : public Window
{
protected:
	AppWindow (void);
public:
	enum            BorderType  { NoBorder,  SizingBorder, NonSizingBorder };
	
	void		EnableBorder (BorderType = SizingBorder);
	void		EnableMinBox (BOOL = true);
	void		EnableMaxBox (BOOL = true); 
	pSysMenu	EnableSysMenu (BOOL = true);
	void		SetIcon (pIcon);
	void		SetPointer (pPointer);

	~AppWindow (void);
};

#ifndef NOTOPWIND

class _TF_ENTRY32 TopAppWindow : public AppWindow
{
protected:
	TopAppWindow (pAppWindow copy = 0);
// #HK951225 ------------------------------------------------------------------
	TopAppWindow (long dwExStyle, const char *pClassName = NULL);
// #HK951225 ------------------------------------------------------------------

public:
	~TopAppWindow (void);
};

#endif // NOTOPWIND
#ifndef NOCHILD

#if defined(__WATCOMC__)
// Using default arguments would be overload ambiguous
#pragma warning 249 9;
#endif
class _TF_ENTRY32 ChildAppWindow : public AppWindow
{
protected:
	ChildAppWindow (pWindow parent,  pAppWindow copy = 0, BOOL isManaged = true);
// #HK930803 ------------------------------------------------------------------
	ChildAppWindow (pWindow parent, pchar pWClassName = NULL, long dwExStyle = 0);
	ChildAppWindow (pWindow parent, UINT uiID, pchar pWClassName = NULL, long dwExStyle = 0);
// ----------------------------------------------------------------------------
public:
	~ChildAppWindow (void);
};

#endif // NOCHILD
#ifndef NODIALOG

class _TF_ENTRY32 DialogWindow : public Window
{
protected:
	DialogWindow (void);
	DialogWindow (pWindow, ResID, BOOL = true);

void		EndDlg (int nResult = 0);

public:
HWND		Handle (Service = 0);

pFont       	ChangeFont(pFont , BOOL global=false) ;
int		Result (void);

	~DialogWindow (void);

	BOOL PreTranslateMsg (MSG *pMsg);			// #HK970116
};

class _TF_ENTRY32 ModeLessDialog : public DialogWindow
{
protected:
	ModeLessDialog (pWindow parent, ResID);
public:
	~ModeLessDialog (void);
};

#endif // NODIALOG

#ifndef NOPRINTER

class _TF_ENTRY32 PrintingDevice {
friend class CV_RunTime;

	PrintingDevice_Imp	*pd_Imp;

public:
		PrintingDevice (const char * = NULL);

	BOOL isValid (void);

	const char *DeviceName (void);
	const char *DriverName (void);
	const char *PortName (void);
	const DEVMODE *DeviceMode (void);

// Initialisierungsfunktionen
	BOOL InitFromDefaultPrinter (DVTARGETDEVICE **ppdvt = NULL);
	BOOL InitFromData (DVTARGETDEVICE *pdvt);
	BOOL SetUp (DVTARGETDEVICE **ppdvt = NULL);

		~PrintingDevice (void);
};

class _TF_ENTRY32 Printer : public Window 
{
friend class CV_RunTime;

protected:
		Printer (const char *jobname = 0, PrintingDevice * device = 0);

virtual void 		Idle (void);
virtual	BOOL		PrinterError (PrinterErrorEvt);
virtual BOOL		PrinterExpose (PrinterExposeEvt) = 0;


public:
	HDC		Handle (Service = 0);

	void		Start (void);
	void		Start (Range);

	void		Abort(void);
	
	BOOL		isValid(void);

		~Printer(void);
};

#if !defined(NOBANDINGPRINTER)
class _TF_ENTRY32 BandingPrinter : public Printer 
{
friend class CV_RunTime;
protected:
		BandingPrinter (const char *jobname = 0, PrintingDevice *device = 0);

virtual BOOL PrinterExpose (PrinterExposeEvt) = 0;

public:
	void	StartBanding (void);
	void	StartBanding (Range);

		~BandingPrinter(void);
};
#endif // NOBANDINGPRINTER
#endif // NOPRINTER

#ifndef NOSHELL


#if !defined(NODCWINDOW)

class _TF_ENTRY32 CDCWindow : public Window {		// Fenster nur zum Zeichnen
friend class CV_RunTime;
protected:
	CDCWindow (HDC hDC, Rectangle &Rc, HDC hTargetDC = 0);

virtual BOOL 	DCExpose (CDCExposeEvt) = 0;

public:
	HWND Handle (Service = 0);
	BOOL Render (Rectangle &r);		// eigentliches Zeichnen

		~CDCWindow (void);
};

#endif // NODCWINDOW

#define NOMETAFILE		// noch nicht fertig
#if !defined(NOMETAFILE)

class _TF_ENTRY32 CMetaFile : public CDCWindow {
friend class CV_RunTime;
protected:
	CMetaFile (Rectangle &Rc, char *pFName = NULL);	// NULL: MemoryMetaDC

virtual BOOL 		DCExpose (CDCExposeEvt) = 0;

public:
	~CMetaFile (void);
};

#endif

class _TF_ENTRY32 ShellWindow : public AppWindow
{
protected:
	ShellWindow (void);
		
public:
	enum ArrangeStyle { Icons, Cascade, Tile, TileHorz, TileVert };

HWND		Handle (Service = 0);
void		Arrange (ArrangeStyle);

	~ShellWindow(void);
};

#endif // NOSHELL

#if defined(WIN32) // =========================================================

#if !defined(NOPROPERTSHEET)

class _TF_ENTRY32 CPropertyPage : public DialogWindow {
private:
	void Show (ShowState);		// darf nicht gerufen werden

protected:
		CPropertyPage (void);

// OnCancel: Called by the framework when the Cancel button is clicked.
virtual	void OnCancel (NotifyEvt e);
// OnQueryCancel: Called by Framework to verify the Cancel operation
virtual BOOL OnQueryCancel (NotifyEvt e);	// true allows operation
// OnOK: Called by the framework when the OK, Apply Now, or Close button is clicked.
virtual BOOL OnOK (NotifyEvt e);		// true allows operation
// OnSetActive: Called by the framework when the page is made the active page.
virtual BOOL OnSetActive (NotifyEvt e);
// OnKillActive: Called by the framework when the current page is no longer the active page. Perform data validation here.
virtual BOOL OnKillActive (NotifyEvt e);
// OnHelp: Called, when the HelpButton is pressed
virtual	void OnHelp (NotifyEvt e);

// WizardEvents
virtual int OnWizBack (NotifyEvt e);	// -1:cancel
virtual int OnWizNext (NotifyEvt e);	// -1: cancel
virtual BOOL OnWizFinish (NotifyEvt e);	// true:cancel

	HPROPSHEETPAGE CreatePage (void);	// use only, if you know, what you're doing
	class CPropertySheet *GetPropertySheet (void);	// returns parent, after initialisation

public:
		CPropertyPage (ResID nTemplate, LPCSTR pCaption = NULL);
		~CPropertyPage (void);

	HWND Handle (Service = 0);

// CancelToClose: Changes the Cancel button to read Close after an unrecoverable change in the page of a modal property sheet.
	void CancelToClose (void);
// SetModified: Call to activate or deactivate the Apply Now button.
	void SetModified (BOOL bChanged = true);
// QuerySiblings: send messages to other Pages of our PropertySheet
	LRESULT QuerySiblings (WPARAM wParam, LPARAM lParam);

// Icon in Tablasche setzen
	void SetIcon (ResID resID);
	void SetIcon (pIcon pIcon);

// #HK030116: Wizard97 only: set HeaderTitle and HeaderSubTitle
	void SetHeaderTitle(char const *pcHeaderTitle);
	void SetHeaderSubTitle(char const *pcHeaderSubTitle);

// Direkter Zugriff auf PropertySheetWindow
	void SetSheetWizardButtons (DWORD dwFlags = PSWIZB_NEXT|PSWIZB_BACK|PSWIZB_FINISH);
	void PressSheetButton (DWORD dwFlags = PSBTN_APPLYNOW);
};

class _TF_ENTRY32 CPropertySheet : public DialogWindow {
public:
		CPropertySheet (LPCSTR pszCaption, Window *pParentWnd = NULL, 
				DWORD = PSH_DEFAULT, UINT iSelectPage = 0);
		~CPropertySheet (void);

// handle PSM_ISDIALOGMESSAGE
	BOOL PreTranslateMsg (MSG *pMsg);			// #HK990623

// GetPageCount: Retrieves the number of pages in the property sheet.
	int GetPageCount (void);

// GetPage: Retrieves a pointer to the specified page.
	CPropertyPage* GetPage (UINT nPage) const;

// Show: Displays a modal property sheet.
	void Show (ShowState = Normal);

// AddPage: Adds a page to the property sheet.
	UINT AddPage (CPropertyPage *pPage);
	UINT AddPage (HPROPSHEETPAGE hPage);

// RemovePage: Removes a page from the property sheet.
	BOOL RemovePage (CPropertyPage *pPage);
	BOOL RemovePage (HPROPSHEETPAGE hPage);
	BOOL RemovePage (UINT nPage);

// EndDialog: Terminates the property sheet.
	void EndDialog (int nEndID = 0);

// SetCurSel: Aktivieren einer Seite
	BOOL SetCurSel (CPropertyPage *pPage);
	BOOL SetCurSel (HPROPSHEETPAGE hPage);
	BOOL SetCurSel (UINT nPage);

// PressButton: drückt programmtechnisch den angegebenen Knopf
	void PressButton (DWORD dwFlags = PSBTN_APPLYNOW);

// SetWizardButtons: aktiviert/deaktiviert angegebene WizardButtons
	void SetWizardButtons (DWORD dwFlags = PSWIZB_NEXT|PSWIZB_BACK|PSWIZB_FINISH);

// Icon in Caption setzen
	void SetIcon (ResID resID);
	void SetIcon (pIcon pIcon);

// #HK030116: Wizard97: Headerbitmap und Watermark setzen
	void SetHeaderBitmap (ResID resID);
	void SetHeaderBitmap (pBitmap pBitmap);
	void SetWatermark (ResID resID);
	void SetWatermark (pBitmap pBitmap);
};

#endif // NOPROPERTSHEET
#endif // WIN32 ===============================================================

#endif // NOEVENT

#ifndef NOCONTROL

class _TF_ENTRY32 Control
{
friend class CV_RunTime;
protected:
	pControl_Imp control_Imp;

	Control (void);
	Control (pDialogWindow, ResID, const char *RegClass  = 0);
	Control (pWindow, CvID id, Point, Dimension, const char *RegClass = 0, ulong InitStyle = 0);

public:
HWND		Handle (Service = 0);
void       	SetStyle (ulong);
void		Show (void);
void		Hide (void);
void		Enable (void);
void		Disable (void);
CvID		GetID (void);
void		SetFocus (void);
pWindow     	GetParent(void);
Point		GetPosition (void);
Point		ChangePosition (Point);
Dimension	GetSize (void);
Dimension	ChangeSize (Dimension);
pBrush		ChangeBackground(pBrush);
LRESULT		ForwardEvent (Event e);
void		PostEvent (Event e);

// #HK970903
LRESULT ForwardEvent (UINT wMsg, WPARAM wParam = 0, LPARAM lParam = 0);
void PostEvent (UINT wMsg, WPARAM wParam = 0, LPARAM lParam = 0);

	~Control (void);

#if defined(WIN32)		// Nachinitialisierung für PropSheets
	BOOL 	FInit (void);
#endif // WIn32
};

#ifndef NOFIXEDICON

class _TF_ENTRY32 FixedIcon : public Control
{
public:
	FixedIcon (pDialogWindow parent, ResID id);
	FixedIcon (pWindow, CvID id, Point, ResID iconid);
};

#endif // NOFIXEDICON
#ifndef NOSCROLLBAR

class _TF_ENTRY32 ScrollBar : public Control
{
protected:
	ScrollBar (void);

public:
	ScrollBar (pDialogWindow parent, ResID);
	ScrollBar (pWindow, CvID id, Point, Dimension);

int			GetThumbPos (void);
void		SetThumbPos (int);
Range		GetRange (void);
void		SetRange (Range);
uint		GetBlock (void);
void		SetBlock (uint);
uint		GetUnit (void);
void		SetUnit (uint);

uint		GetPageSize (void);		// #HK960411
int			SetPageSize (uint uiSize, BOOL fRedraw = true);
int			GetTrackPos (void);

	~ScrollBar (void);
};

#ifndef NOVERTBAR

class _TF_ENTRY32 VertScrollBar : public ScrollBar
{
public:
	VertScrollBar (pDialogWindow parent, ResID);
	VertScrollBar (pWindow, CvID id, Point, Dimension);
};

class _TF_ENTRY32 WndVertScrollBar : public ScrollBar
{
public:
	WndVertScrollBar (pWindow);
};

#endif // NOVERTBAR
#ifndef NOHORBAR

class _TF_ENTRY32 HorizScrollBar : public ScrollBar
{
public:
	HorizScrollBar (pDialogWindow parent, ResID);
	HorizScrollBar (pWindow, CvID id, Point, Dimension);
};

class _TF_ENTRY32 WndHorzScrollBar : public ScrollBar
{
public:
	WndHorzScrollBar (pWindow);
};

#endif // NOHORBAR
#endif // NOSCROLLBAR
#ifndef NOTEXTCONTROL

class _TF_ENTRY32 TextControl : public Control
{
protected:
	TextControl (void);
	TextControl (pDialogWindow parent, ResID);
	TextControl (pWindow, CvID id, Point, Dimension);

public:
void		SetText (const char * buffer);
void		GetText (char * buffer, uint maxlen);
uint		GetTextLen (void);

pFont		ChangeFont (pFont font, BOOL rescale = false);  
Color		ChangeTextColor (Color c);
};


#if defined(WIN32)

#if !defined(NOWIN95CONTROLS)
#if !defined(NOTREELIST)

class CImageList;

class _TF_ENTRY32 CTreeViewCtrl : public Control {
protected:
	void RemoveImageList(int nImageList);

public:
		CTreeViewCtrl (pDialogWindow parent, ResID id);
		CTreeViewCtrl (pWindow, CvID id, Point, Dimension, DWORD dwInitStyle = 0);
		~CTreeViewCtrl (void);

// Attributes
	BOOL GetItemRect (HTREEITEM hItem, Rectangle *lpRect, BOOL bTextOnly);
	UINT GetCount (void);
	UINT GetIndent (void);
	void SetIndent (UINT nIndent);
	CImageList *GetImageList (UINT nImageList);
	CImageList *SetImageList (CImageList *pImageList, int nImageListType);
	HTREEITEM GetNextItem (HTREEITEM hItem, UINT nCode);
	HTREEITEM GetChildItem (HTREEITEM hItem);
	HTREEITEM GetNextSiblingItem (HTREEITEM hItem);
	HTREEITEM GetPrevSiblingItem (HTREEITEM hItem);
	HTREEITEM GetParentItem (HTREEITEM hItem);
	HTREEITEM GetFirstVisibleItem (void);
	HTREEITEM GetNextVisibleItem (HTREEITEM hItem);
	HTREEITEM GetPrevVisibleItem (HTREEITEM hItem);
	HTREEITEM GetSelectedItem (void);
	HTREEITEM GetDropHilightItem (void);
	HTREEITEM GetRootItem (void);
	BOOL GetItem (TV_ITEM *pItem);
	string GetItemText (HTREEITEM hItem);
	BOOL GetItemImage (HTREEITEM hItem, int& nImage, int& nSelectedImage);
	UINT GetItemState (HTREEITEM hItem, UINT nStateMask);
	DWORD GetItemData (HTREEITEM hItem);
	BOOL SetItem (const TV_ITEM *pItem);
	BOOL SetItem (HTREEITEM hItem, UINT nMask, LPCSTR lpszItem, int nImage, 
		      int nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam);
	BOOL SetItemText (HTREEITEM hItem, LPCSTR lpszItem);
	BOOL SetItemImage (HTREEITEM hItem, int nImage, int nSelectedImage);
	BOOL SetItemState (HTREEITEM hItem, UINT nState, UINT nStateMask);
	BOOL SetItemData (HTREEITEM hItem, DWORD dwData);
	BOOL ItemHasChildren (HTREEITEM hItem);
	SingleLineEdit *GetEditControl (void);
	UINT GetVisibleCount (void);

// Operations
	HTREEITEM InsertItem (const TV_INSERTSTRUCT *lpInsertStruct);
	HTREEITEM InsertItem (UINT nMask, LPCSTR lpszItem, int nImage, 
		int nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam, 
		HTREEITEM hParent, HTREEITEM hInsertAfter);
	HTREEITEM InsertItem (LPCSTR lpszItem, HTREEITEM hParent = TVI_ROOT, 
		HTREEITEM hInsertAfter = TVI_LAST);
	HTREEITEM InsertItem (LPCSTR lpszItem, int nImage, int nSelectedImage,
		HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
	BOOL DeleteItem (HTREEITEM hItem);
	BOOL DeleteAllItems (void);
	BOOL Expand (HTREEITEM hItem, UINT nCode);
	HTREEITEM Select (HTREEITEM hItem, UINT nCode);
	HTREEITEM SelectItem (HTREEITEM hItem);
	HTREEITEM SelectDropTarget (HTREEITEM hItem);
	HTREEITEM SelectSetFirstVisible (HTREEITEM hItem);
	SingleLineEdit *EditLabel (HTREEITEM hItem);
	HTREEITEM HitTest (Point pt, UINT *pFlags = NULL);
	HTREEITEM HitTest (TV_HITTESTINFO *pHitTestInfo);
	CImageList *CreateDragImage (HTREEITEM hItem);
	BOOL SortChildren (HTREEITEM hItem);
	BOOL EnsureVisible (HTREEITEM hItem);
	BOOL SortChildrenCB (TV_SORTCB *pSort);
};

#endif // NOTREELIST

#if !defined(NOLISTVIEW)

class _TF_ENTRY32 CListViewCtrl : public Control {
protected:
	void RemoveImageList (int nImageList);

public:
// Constructors
		CListViewCtrl (pDialogWindow parent, ResID id);
		CListViewCtrl (pWindow, CvID id, Point, Dimension, DWORD dwInitStyle = 0);
		~CListViewCtrl (void);

// Attributes
	COLORREF GetBkColor (void);
	BOOL SetBkColor (COLORREF cr);
	CImageList* GetImageList (int nImageList);
	CImageList* SetImageList (CImageList* pImageList, int nImageListType);
	int GetItemCount (void);
	BOOL GetItem (LV_ITEM *pItem);
	BOOL SetItem (const LV_ITEM *pItem);
	BOOL SetItem (int nItem, int nSubItem, UINT nMask, LPCSTR lpszItem,
		      int nImage, UINT nState, UINT nStateMask, LPARAM lParam);
	UINT GetCallbackMask (void);
	BOOL SetCallbackMask (UINT nMask);
	int GetNextItem (int nItem, int nFlags);
	BOOL GetItemRect (int nItem, LPRECT lpRect, UINT nCode);
	int GetStringWidth (LPCSTR lpsz);
	SingleLineEdit *GetEditControl (void);
	BOOL GetColumn (int nCol, LV_COLUMN *pColumn);
	BOOL SetColumn (int nCol, const LV_COLUMN *pColumn);
	int GetColumnWidth (int nCol);
	BOOL SetColumnWidth (int nCol, int cx);
	BOOL GetViewRect (LPRECT lpRect);
	COLORREF GetTextColor (void);
	BOOL SetTextColor (COLORREF cr);
	COLORREF GetTextBkColor (void);
	BOOL SetTextBkColor (COLORREF cr);
	int GetTopIndex (void);
	int GetCountPerPage (void);
	BOOL GetOrigin (LPPOINT lpPoint);
	BOOL SetItemState (int nItem, LV_ITEM* pItem);
	BOOL SetItemState (int nItem, UINT nState, UINT nMask);
	UINT GetItemState (int nItem, UINT nMask);
	string GetItemText (int nItem, int nSubItem);
	int GetItemText (int nItem, int nSubItem, LPSTR lpszText, int nLen);
	BOOL SetItemText (int nItem, int nSubItem, LPSTR lpszText);
	void SetItemCount (int nItems);
	BOOL SetItemData (int nItem, DWORD dwData);
	DWORD GetItemData (int nItem);
	UINT GetSelectedCount (void);

// Operations
	int InsertItem (const LV_ITEM *pItem);
	int InsertItem (int nItem, LPCSTR lpszItem);
	int InsertItem (int nItem, LPCSTR lpszItem, int nImage);
	BOOL DeleteItem (int nItem);
	BOOL DeleteAllItems (void);
	int FindItem (LV_FINDINFO *pFindInfo, int nStart = -1);
	int HitTest (LV_HITTESTINFO *pHitTestInfo);
	int HitTest (Point pt, UINT *pFlags = NULL);
	BOOL EnsureVisible (int nItem, BOOL bPartialOK);
	BOOL Scroll (Dimension size);
	BOOL RedrawItems (int nFirst, int nLast);
	BOOL Arrange (UINT nCode);
	SingleLineEdit *EditLabel (int nItem);
	int InsertColumn (int nCol, const LV_COLUMN* pColumn);
	int InsertColumn (int nCol, LPCSTR lpszColumnHeading,
			 int nFormat = LVCFMT_LEFT, int nWidth = -1, 
			 int nSubItem = -1);
	BOOL DeleteColumn (int nCol);
	CImageList *CreateDragImage (int nItem, LPPOINT lpPoint);
	BOOL Update (int nItem);
	BOOL SortItems (PFNLVCOMPARE pfnCompare, DWORD dwData);

// New functions for 'Nashville' (#HK960823)
	DWORD GetExtendedStyle (void);
	DWORD SetExtendedStyle (DWORD dwStyleEx);
	BOOL GetSubItemRect (int iItem, int iSubItem, int iCode, LPRECT lpRc);
	int SubItemHitTest (LV_HITTESTINFO *pHitTestInfo);
	BOOL SetColumnOrderArray (int iCount, int *piCols);
	BOOL GetColumnOrderArray (int iCount, int *piCols);
	int SetHotItem (int iItem);
	int GetHotItem (void);
	HCURSOR SetHotCursor (HCURSOR hCursor);
	HCURSOR GetHotCursor (void);
	DWORD ApproximateViewRect (int iWidth, int iHeight, int iCount);

// Implementation
	int InsertItem (UINT nMask, int nItem, LPCSTR lpszItem, UINT nState,
			UINT nStateMask, int nImage, LPARAM lParam);
};

#endif // NOLISTVIEW

#if !defined(NOTOOLTIP)

class _TF_ENTRY32 CToolTipCtrl : public Control {
public:
// Constructors
		CToolTipCtrl (pWindow parent);
		~CToolTipCtrl (void);

// Attributes
	void GetText (string& str, pWindow pWnd, UINT nIDTool = 0);
	BOOL GetToolInfo (LPTOOLINFO lpToolInfo, pWindow pWnd, UINT nIDTool = 0);
	void SetToolInfo (LPTOOLINFO lpToolInfo);
	void SetToolRect (pWindow pWnd, UINT nIDTool, LPCRECT lpRect);
	int GetToolCount (void);

// Operations
	void Activate (BOOL bActivate);

	BOOL AddTool (pWindow pWnd, ResID nIDText, LPCRECT lpRectTool = NULL, 
		      UINT nIDTool = 0);
	BOOL AddTool (pWindow pWnd, LPCTSTR lpszText = LPSTR_TEXTCALLBACK, 
		      LPCRECT lpRectTool = NULL, UINT nIDTool = 0);

	void DelTool (pWindow pWnd, UINT nIDTool = 0);

	BOOL HitTest (pWindow pWnd, Point pt, LPTOOLINFO lpToolInfo);
	void RelayEvent (LPMSG lpMsg);
	void SetDelayTime (UINT nDelay);
	void UpdateTipText (LPCTSTR lpszText, pWindow pWnd, UINT nIDTool = 0);
	void UpdateTipText (ResID nIDText, pWindow pWnd, UINT nIDTool = 0);

// Implementation
public:
	void FillInToolInfo (TOOLINFO& ti, pWindow pWnd, UINT nIDTool);
};

#endif // NOTOOLTIP

#if !defined(NOTOOLBAR)

class _TF_ENTRY32 CToolBarCtrl : public Control {
public:
// Construction
		CToolBarCtrl (pDialogWindow parent, ResID id);
		CToolBarCtrl (pWindow, CvID id, Point, Dimension, DWORD dwInitStyle = 0);
		~CToolBarCtrl (void);

// Attributes
public:
	BOOL IsButtonEnabled (int nID);
	BOOL IsButtonChecked (int nID);
	BOOL IsButtonPressed (int nID);
	BOOL IsButtonHidden (int nID);
	BOOL IsButtonIndeterminate (int nID);
	BOOL SetState (int nID, UINT nState);
	int GetState (int nID);
	BOOL GetButton (int nIndex, LPTBBUTTON lpButton);
	int GetButtonCount (void);
	BOOL GetItemRect (int nIndex, LPRECT lpRect);
	void SetButtonStructSize (int nSize);
	BOOL SetButtonSize (Dimension size);
	BOOL SetBitmapSize(Dimension size);
	CToolTipCtrl *GetToolTips (void);
	void SetToolTips (CToolTipCtrl *pTip);
	void SetOwner (pWindow pWnd);
	void SetRows (int nRows, BOOL bLarger, LPRECT lpRect);
	int GetRows (void);
	BOOL SetCmdID (int nIndex, UINT nID);
	UINT GetBitmapFlags (void);

// Operations
public:
	BOOL EnableButton (int nID, BOOL bEnable = true);
	BOOL CheckButton (int nID, BOOL bCheck = true);
	BOOL PressButton (int nID, BOOL bPress = true);
	BOOL HideButton (int nID, BOOL bHide = true);
	BOOL Indeterminate (int nID, BOOL bIndeterminate = true);
	int AddBitmap (int nNumButtons, ResID nBitmapID);
	int AddBitmap (int nNumButtons, Bitmap *pBitmap);
	BOOL AddButtons (int nNumButtons, LPTBBUTTON lpButtons);
	BOOL InsertButton (int nIndex, LPTBBUTTON lpButton);
	BOOL DeleteButton (int nIndex);
	UINT CommandToIndex (UINT nID);
	void SaveState (HKEY hKeyRoot, LPCSTR lpszSubKey, LPCSTR lpszValueName);
	void RestoreState (HKEY hKeyRoot, LPCSTR lpszSubKey, LPCSTR lpszValueName);

	void Customize (void);
	int AddString (ResID nStringID);
	int AddStrings (LPCSTR lpszStrings);
	void AutoSize (void);
};

#endif // NOTOOLBAR

#if !defined(NOSTATUSBAR)

class _TF_ENTRY32 CStatusBarCtrl : public Control {
public:
// Constructors
		CStatusBarCtrl (pDialogWindow parent, ResID id);
		CStatusBarCtrl (pWindow, CvID id, Point, Dimension, DWORD dwInitStyle = 0);
		~CStatusBarCtrl (void);

// Attributes
	BOOL SetText (LPCSTR lpszText, int nPane, int nType);
	string GetText (int nPane, int *pType = NULL);
	int GetText (LPCSTR lpszText, int nPane, int *pType = NULL);
	int GetTextLength (int nPane, int *pType = NULL);
	BOOL SetParts (int nParts, int *pWidths);
	BOOL SetBorders (int *pBorders);
	BOOL SetBorders (int nHorz, int nVert, int nSpacing);
	int GetParts (int nParts, int *pParts);
	BOOL GetBorders (int *pBorders);
	BOOL GetBorders (int& nHorz, int& nVert, int& nSpacing);
	void SetMinHeight (int nMin);
	BOOL SetSimple (BOOL bSimple = true);
	BOOL GetRect (int nPane, LPRECT lpRect);
};

#endif // NOSTATUSBAR

#if !defined(NOUPDOWN)

class _TF_ENTRY32 CSpinButtonCtrl : public Control {
public:
// Constructors
		CSpinButtonCtrl (pDialogWindow parent, ResID id);
		CSpinButtonCtrl (pWindow, CvID id, Point, Dimension, DWORD dwInitStyle = 0);
		~CSpinButtonCtrl (void);

// Attributes
	BOOL SetAccel (int nAccel, UDACCEL *pAccel);
	UINT GetAccel (int nAccel, UDACCEL *pAccel);
	int SetBase (int nBase);
	UINT GetBase (void);
	pControl SetBuddy (pControl pWndBuddy);
	pControl GetBuddy (void);
	int SetPos (int nPos);
	int GetPos (void);
	void SetRange (int nLower, int nUpper);
	DWORD GetRange (void);
	void GetRange (int &lower, int& upper);
};

#endif // NOUPDOWN

#if !defined(NOPROGRESS)

class _TF_ENTRY32 CProgressCtrl : public Control {
public:
// Constructors
		CProgressCtrl (pDialogWindow parent, ResID id);
		CProgressCtrl (pWindow, CvID id, Point, Dimension, DWORD dwInitStyle = 0);
		~CProgressCtrl (void);

// Attributes
	void SetRange (int nLower, int nUpper);
	int SetPos (int nPos);
	int OffsetPos (int nPos);
	int SetStep (int nStep);

// Operations
	int StepIt (void);
};

#endif // NOPROGRESS

#if !defined(NOANIMATE)

class _TF_ENTRY32 CAnimateCtrl : public Control {
// Constructors
public:
		CAnimateCtrl (pDialogWindow parent, ResID id);
		CAnimateCtrl (pWindow, CvID id, Point, Dimension, DWORD dwInitStyle = 0);
		~CAnimateCtrl (void);

// Operations
	BOOL Open(LPCTSTR lpszFileName);
	BOOL Open(UINT nID);
	BOOL Play(UINT nFrom, UINT nTo, UINT nRep);
	BOOL Stop();
	BOOL Close();
	BOOL Seek(UINT nTo);
};
#endif // NOANIMATE

// BEGIN: #HK001012
class _TF_ENTRY32 CHotKeyCtrl :
	public Control
{
public:
	CHotKeyCtrl (pDialogWindow parent, ResID id);
	CHotKeyCtrl (pWindow, CvID id, Point, Dimension, DWORD dwInitStyle = 0);
	~CHotKeyCtrl();

// Attributes
	void SetHotKey(WORD wVirtualKeyCode, WORD wModifiers);
	DWORD GetHotKey() const;
	void GetHotKey(WORD &wVirtualKeyCode, WORD &wModifiers) const;

// Operations
	void SetRules(WORD wInvalidComb, WORD wModifiers);
};
// END: #HK001012

#endif // NOWIN95CONTROLS
#endif // WIN32

#if !defined(NOGAUGECONTROL)

class _TF_ENTRY32 GaugeBox : public TextControl
{
protected:
	GaugeBox (void);

public:
	GaugeBox (pDialogWindow parent, ResID);
	GaugeBox (pWindow, CvID id, Point, Dimension, const char *pInitText = 0);

void		SetRange (short);
void		SetPosition (short);
void		SetOrientation (short);
void		SetDeltaPos (short);
void		SetFColor (Color);
void		SetBkColor (Color);
void 		Set3DWidth (short);
void 		SetBezelFace (short);
	
short		GetRange (void);
short		GetPosition (void);
short		GetOrientation (void);
Color		GetFColor (void);
Color		GetBkColor (void);
short		Get3DWidth (void);
short		GetBezelFace (void);
};

#endif // NOGAUGECONTROL

#ifndef NOBUTTON

class _TF_ENTRY32 Button : public TextControl
{
protected:
	Button (void);
	Button (pDialogWindow parent, ResID);
	Button (pWindow, CvID id, Point, Dimension, const char * InitText);
};

#ifndef NORADIOBUTTON

class _TF_ENTRY32 RadioButton : public Button
{
public:
	RadioButton (pDialogWindow parent, ResID);
	RadioButton (pWindow, CvID id, Point, Dimension, const char* InitText = 0);

BOOL		GetState (void);
void		SetState (BOOL onoff);
};

#endif // NORADIOBUTTON
#ifndef NOPUSHBUTTON

class _TF_ENTRY32 PushButton : public Button
{
public:
		PushButton (pDialogWindow parent, ResID);
		PushButton (pWindow, CvID id, Point, Dimension, const char * InitText = 0);

	HBITMAP SetImage (HBITMAP);
	HBITMAP GetImage (void);
};

#endif // NOPUSHBUTTON
#ifndef NOCHECKBOX

class _TF_ENTRY32 CheckBox : public Button
{
public:
	CheckBox (pDialogWindow parent, ResID);
	CheckBox (pWindow, CvID id, Point, Dimension, const char * InitText = 0);

BOOL		isChecked (void);
void		SetChecked (BOOL checked);
};

#endif // NOCHECKBOX
#endif // NOBUTTON
#ifndef NOLISTBOX

class _TF_ENTRY32 BaseListBox : public TextControl
{
public:
	BaseListBox (void);
	BaseListBox (pDialogWindow , ResID);
	BaseListBox (pWindow, CvID id, Point, Dimension);

	enum    ListBoxStyle { UnSorted, SortedAscending, SortedDescending };

void    	SetStdStyle (ListBoxStyle);
int		AddString (const char * str, int position = -1);
BOOL	DelString (int strIndex = -1);
int		FindString (const char *, BOOL wholeword =false);
BOOL    	GetString (char* buffer, int index, int length = -1);
int		GetStringLength (int index);
int		GetCount (void);
void    	SetTop (uint index);
void	Clear (void);

#if _MSC_VER >= 1200
	DWORD GetItemData (int iIndex);				// #HK990130
	int SetItemData (int iIndex, DWORD dwData);	// #HK990130

// erstmal einfache Variante für horizontale ScrollBars
	BOOL InitListboxExtents();		// #HK991020
	BOOL FreeListboxExtents();
	void ResetListboxExtents();
	DWORD AddExtentEntry (LPCSTR psz);
	DWORD RemoveExtentEntry (LPCSTR pcText);
#endif // _MSC_VER >= 1200	
};

class _TF_ENTRY32 ListBox : public BaseListBox
{
public:
	ListBox (void);
	ListBox (pWindow, CvID id, Point, Dimension);
	ListBox (pDialogWindow, ResID);

int		GetCurrentIndex (void);
BOOL    	ChangeCurrentIndex (int index);
BOOL    	GetCurrentString   (char* buffer, int len = -1);
};

class _TF_ENTRY32 MultiSelListBox : public BaseListBox 
{
public:
	MultiSelListBox (void);
	MultiSelListBox (pDialogWindow, ResID);
    	MultiSelListBox (pWindow, CvID id, Point, Dimension);

int  		GetNoSelected (void);
BOOL 		ClearSelected (void);
int  		GetFirstSelected (void);
int  		GetNextSelected (void);
BOOL 		ChangeSelected (int index, BOOL = true);
BOOL 		ChangeSelected (Range, BOOL = true);
short 		GetCaretIndex (void);
BOOL 		SetCaretIndex (short iIndex, BOOL fScroll = true);
BOOL 		GetSelection (short iIndex);
int			FindString (const char *pText, BOOL fWhole = false, int iStart = -1);
};

class _TF_ENTRY32 TabularListBox : public ListBox
{
public :
	TabularListBox (pDialogWindow, ResID, uint);
	TabularListBox (pWindow, CvID, Point, Dimension, uint);

int 		AddRow (int , ...); 
BOOL 		GetRow (int , ...);
void 		SetColWidth (uint col, uint width);
};

class _TF_ENTRY32 MultiSelTabularListBox : public MultiSelListBox 
{
public :
	MultiSelTabularListBox (pDialogWindow, ResID, uint);
	MultiSelTabularListBox (pWindow, CvID, Point, Dimension, uint);

int 		AddRow (int , ...); 
BOOL 		GetRow (int , ...);
void 		SetColWidth (uint col, uint width);
};

class _TF_ENTRY32 ComboBox : public ListBox
{
public :
	enum ComboStyle { Simple, DropDown, DropDownList };

	ComboBox (pDialogWindow parent, ResID);
	ComboBox (pWindow, CvID id, Point, Dimension, ComboStyle = DropDown);

Selection	GetEditSelection (BOOL toClipBoard = false);
Selection	GetEditSelection (char *, int TextLen = -1);
void		ChangeEditSelection (Selection);
void		DeleteEditSelected (BOOL toClipBoard = false);

protected:
	ComboBox();
};

class _TF_ENTRY32 ComboBoxEx : public ComboBox
{
// Constructors
public:
	ComboBoxEx(pDialogWindow parent, ResID);
	ComboBoxEx(pWindow pW, CvID id, Point pt, Dimension dim, 
		ComboStyle = DropDown);
	~ComboBoxEx();

// Operations
	int DeleteItem(int iIndex);
	BOOL GetItem(COMBOBOXEXITEM* pCBItem);
	int InsertItem(const COMBOBOXEXITEM* pCBItem);
	BOOL SetItem(const COMBOBOXEXITEM* pCBItem);

// Attributes
	BOOL HasEditChanged();
	DWORD GetExtendedStyle();
	DWORD SetExtendedStyle(DWORD dwExMask, DWORD dwExStyles);
	SingleLineEdit* GetEditCtrl();
	CImageList* GetImageList();
	CImageList* SetImageList(CImageList* pImageList);
};

class _TF_ENTRY32 FileListBox : public ListBox
{
public:
	FileListBox (pDialogWindow, ResID lbid, ResID pathid);
                        
BOOL		List (const char * path, uint attributes);
BOOL		GetCurrentFile (char * filename, int len = _MAX_PATH);
FlbStatus		Validate (char * filename, int len = _MAX_PATH);
};

#endif // NOLISTBOX
#ifndef NOEDIT

class _TF_ENTRY32 Edit : public TextControl
{
protected:
	Edit (void);
	Edit (pDialogWindow parent, ResID);
	Edit (pWindow, CvID id, Point, Dimension);

public:
	enum EditStyle  { Bordered, UnBordered, PassWord, ReadOnly };

void 		SetStdStyle (EditStyle);
void		SetTextLimit (uint nChars);
BOOL		isModified (void);
void		SetModified(BOOL SetTo = true);

Selection		GetSelection (BOOL toClipBoard = false);
Selection		GetSelection (char *, int TextLen = -1);
void		ChangeSelection (Selection);
BOOL		ReplaceSelected (const char * text = 0);
void		DeleteSelected (BOOL toClipBoard = false);

BOOL		Undo (void);
BOOL		CanUndo (void);
};

class _TF_ENTRY32 MultiLineEdit : public Edit
{
public:
	MultiLineEdit (pDialogWindow parent, ResID);
	MultiLineEdit (pWindow, CvID id, Point, Dimension);

	enum MultiLineStyle  { HScroll, VScroll};

void 		SetMultiStyle (MultiLineStyle);
uint		GetLine (int index, char * buffer, uint nChars);
uint		GetLineLength (int index = -1);

uint		GetNumLines (void);

void		ScrollVertical (int nLines);
void		ScrollHoriz (int nChars);

void		PageUp (void);
void		PageDown (void);

void		LineUp (void);
void		LineDown (void);
};

class _TF_ENTRY32 SingleLineEdit : public Edit
{
public:
	SingleLineEdit (pDialogWindow parent, ResID);
	SingleLineEdit (pWindow, CvID id, Point, Dimension);
#if defined(WIN32)
	SingleLineEdit (pWindow, HWND hWnd);
#endif // WIN32
};

#endif // NOEDIT
#ifndef NOFIXEDTEXT

class _TF_ENTRY32 FixedText : public TextControl
{
public:
        enum FixedTextStyle { LeftAlign, RightAlign, Centered };

	FixedText (pDialogWindow parent, ResID);
	FixedText (pWindow, CvID id, Point, Dimension, const char * text = 0);

void 		SetStdStyle(FixedTextStyle);

	~FixedText (void);
};

#endif // NOFIXEDTEXT
#ifndef NOGROUPBOX

class _TF_ENTRY32 GroupBox : public TextControl
{
public:
	GroupBox (pDialogWindow, ResID);
	GroupBox (pWindow, CvID, Point, Dimension, const char *text=0);
    
};
#endif  // NOGROUPBOX


#endif // NOTEXTCONTROL
#endif // NOCONTROL

#ifndef NOEVENT
#ifndef NOCONTROL

class _TF_ENTRY32 ControlWindow : public Window
{
protected:
	ControlWindow (void);
	ControlWindow (pControl);

void		Expose (ExposeEvt);
#ifdef MSWIND
void		VertScroll (ScrollEvt);
void		HorizScroll (ScrollEvt);
#endif

pControl	GetControl (void);

public:
void		Hide (void);
void		Enable (void);
void		Disable (void);
CvID		GetID (void);
void		SetFocus (void);
Point		ChangePosition (Point);
Dimension	ChangeSize (Dimension);

	~ControlWindow (void);

#if defined(WIN32)		// Nachinitialisierung für PropSheets
	BOOL FInit (void);
#endif // WIN32
};

#ifndef NOTEXTCONTROL
#ifndef NOEDIT

class _TF_ENTRY32 EditWindow : public ControlWindow
{
protected:
	EditWindow (pDialogWindow parent, ResID);
	EditWindow (pWindow, CvID id, Point, Dimension);

public:
void		SetText (const char * buffer);
void		GetText (char * buffer, uint maxlen);
uint		GetTextLen (void);
BOOL		isModified (void);
Selection		GetSelection (void);
void		ChangeSelection (Selection);
void		SetTextLimit (uint nChars);
void		ReplaceSelected (const char * text);
void		DeleteSelected (BOOL toClipBoard = false);

uint		GetLine (uint index, char * buffer, uint nChars);
uint		GetNumLines (void);
void		ScrollVertical (uint nLines);
void		ScrollHoriz (uint nChars);
void		PageUp (void);
void		PageDown (void);
void		LineUp (void);
void		LineDown (void);
BOOL		Undo (void);

	~EditWindow(void);
};

#endif // NOEDIT
#endif // NOTEXTCONTROL
#endif // NOCONTROL
#endif // NOEVENT

#ifndef NOHELP
class _TF_ENTRY32 HelpDisplay
{
friend class CV_RunTime;
	HelpDisp_Imp  *hd_imp;

public:
	HelpDisplay (const char *);

BOOL 		Show (const char *);
BOOL 		Show (ulong);

HdError		HelpError (void);
HANDLE		Handle (Service = 0);

	~HelpDisplay(void);
};
#endif // NOHELP

#if defined(WIN32)

#if !defined(NOWIN95CONTROLS)
#if !defined(NOIMAGEAPIS)

class _TF_ENTRY32 CImageList {
private:
	HIMAGELIST m_hImageList;			// must be first data member
	BOOL m_fAutoDetach;	// lediglich Container für HIMAGELIST

// Constructors
public:
		CImageList (void);
		CImageList (HIMAGELIST hIML, BOOL fAutoDetach = true);

	BOOL CreateList (int cx, int cy, BOOL bMask, int nInitial, int nGrow);
	BOOL CreateList (ResID rscBitmapID, int cx, int nGrow, COLORREF crMask);
	BOOL CreateList (CImageList& imagelist1, int nImage1, CImageList& imagelist2, 
			 int nImage2, int dx, int dy);

// Attributes
	HIMAGELIST Handle (Service s = 0) const;

	BOOL Attach(HIMAGELIST hImageList);
	HIMAGELIST Detach (void);

	int GetImageCount (void);
	COLORREF SetBkColor (COLORREF cr);
	COLORREF GetBkColor (void);
	BOOL GetImageInfo(int nImage, IMAGEINFO* pImageInfo);

// Operations
	BOOL DeleteImageList (void);

	int Add (Bitmap* pbmImage, Bitmap* pbmMask);
	int Add (Bitmap* pbmImage, COLORREF crMask);
	BOOL Remove (int nImage);
	BOOL Replace (int nImage, Bitmap* pbmImage, Bitmap* pbmMask);
	int  Add (Icon *pIcon);
	int  Replace (int nImage, Icon *phIcon);
	HICON ExtractIcon (int nImage);
	BOOL Draw (HDC hDC, int nImage, Point pt, UINT nStyle);
	BOOL SetOverlayImage (int nImage, int nOverlay);

// Drag APIs
	BOOL BeginDrag (int nImage, Point ptHotSpot);
	static void EndDrag (void);
	static BOOL DragMove (Point pt);
	BOOL SetDragCursorImage (int nDrag, Point ptHotSpot);
	static BOOL DragShowNolock (BOOL bShow);
	static CImageList* GetDragImage (Point *lpPoint, Point *lpPointHotSpot);
	static BOOL DragEnter (pWindow pWndLock, Point point);
	static BOOL DragLeave (pWindow pWndLock);

// Implementation
public:
	virtual ~CImageList(void);
};

#endif // NOIMAGEAPIS
#endif // NOWIN95CONTROLS

///////////////////////////////////////////////////////////////////////////////
// MacroDefinitionen für MenuBefehle etc. 
#define BEGIN_COMMANDS(e)			switch (e) {
#define ON_COMMAND_ID(uiID,pFcn)	case (uiID): (pFcn)(); break
#define ON_COMMAND(uiID,pFcn,e)		case (uiID): (pFcn)(e); break
#define DEFAULT_COMMANDS(pFcn, e)	default: (pFcn)(e); break
#define END_COMMANDS				}

#endif // WIN32

#include <cvInline.hxx>

#endif // _COMMONVU_HXX

