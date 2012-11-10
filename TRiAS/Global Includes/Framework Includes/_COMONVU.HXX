/*
 *	_ c o m o n v u . h x x
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods log:
 *	0.1	ferg	26sep88	added Dimension casting operator to Big.
 *	0.2	ferg	27sep88	added Window_Handle member to CV_Runtime.
 *	0.3	ferg	28sep88	added define for GWW_ID
 *	0.0 ferg	05oct88	------- Milestone 2. Beta 2 Shipped ---------
 *	0.4	ferg	26oct88	added pWindow parameter to CV_RunTime::AppWindow_Show
 *						for correct handling of children.
 *	0.5	ferg	02nov88	CV_RunTime::App_new, changes to register App in DLL.
 *	0.6	ferg	03nov88	extern declarations for AppFind etc in _aux2.cxx
 *	0.7	ferg	07nov88	new members for accessing new App data members 
 *						_CVSflg and DlgDispatch.
 *	0.8	ferg	07nov88	typedef for FARPROC moved to CV_TYPES.HXX
 *	0.9	ferg	11nov88	need define for WM_NCDESTROY
 *	0.10 jk		15nov88	Bitmap__ctor added to CV_RunTime and define for
 *						WM_ERASEBKGND.
 *	0.11 ferg	16nov88	CV_RunTime::Menu_hMenu returns a ref.
 *	0.12 rs		17nov88 ferg from 15nov rs. Addition of 
 *						CV_Runtime::ScrollEvt_SetScrollBar(...) Used to 
 *						support windows scroll bars.
 *	0.13 rs		17nov88 ferg from 15nov rs. more defines for GetWindowLong
 *	0.14 ferg	18nov88	some new members of CV_RunTime.
 *	0.15 ferg	18nov88	CV_WindowSB defined.
 *	0.16 ferg	23nov88	typedef for pControlShowProc added , 
 *						CV_RunTime::Control_show and ::WndScrollBar_Show deleted
 *	0.17 ferg	29nov88	Window_hDC.
 *	0.18 jk		29nov88 ------ Milestone 2A. Beta 2A shipped ------
 *	0.19 jk		05dec88 Fast Compile defines added.
 *  0.20 rs     14dec88 Added CV_RunTime::EventContext_Invalidate and 
 *                      CV_RunTime::EventContext_isValid
 *	0.21 ferg	15dec88	EventContext_EvtEnd.
 *  0.22 rs     11jan89 CV_Runtime::Control_hControl()
 *  0.23 rs     16jan89 Added directory separator string 
 *  0.24 rs     24jan89 CV_Runtime::Accel_hRecvr() added
 *  0.25 rs     02feb89 Added CV_Runtime::Pointer_hPointer()
 *  0.26 rs     22feb89 Mapping mode extensions
 *  0.27 rs     24feb89 added CV_RunTime::Control_Parent, CV_RunTime::Window_Parent
 *  0.28 rs     27feb89 Added CV_RunTime::Window_GetDC
 *	0.29 rs		07mar89	Added WndPen and WndBrush to support drawing 
 *						hierachy
 *  0.30 rs     08mar89 Added ResID_Id
 *  0.31 rs		13mar89 Added Window_Draw
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *	1.1	rs		28jun89 Added Window_WndPosition
 *  1.2	rs		29jun89 defines for window type information
 *	1.3	rs		11jul89 added Window_WndFont to support drawing hierarchy.
 *	1.4	rs		12jul89 added CV_RunTime::Dialog_hModeless( pModeLessDialog)
 *	1.5	rs		12jul89	added CV_RunTime::DialogWnd_Result
 *	1.6	rs		12jul89 added psuedo-Window styles for DeleteWindows and
 *					ModeLessDialog.
 * 	1.7	sm		21Sep89 Added Window_WndBackground to support the drawing 
 *					hierarchy.
 * 	1.8	sm		21Sep89 Font_FntSize added to support drawing hierarchy
 * 	1.9	rs		04Oct89 Added ValidateControl to remove temporal dependencies
 *						in Controls and their derivatives.
 * 				05Oct89 Added ValidateWindow to remove temporal dependencies
 *						in Windows and their derivatives.
 *	1.10 rs		24Nov89	Added EventContext_retval, EventContext_Definvoked
 *						to support void return values from Event handlers.
 *	1.12 rs		07Dec89 Added SysMenu_retrieve
 *	1.13 hl		29jan90 Added WndScrollBarDisabled
 *	1.14 rs		06feb90	Added EC_Find
 *	1.15 rs		07feb90 Added App_LastDlgHandle which returns handle of
 *						Last dialog created.
 *
 */

#ifndef	__COMONVU_HXX
#define	__COMONVU_HXX	1

// Define for Windows version number 30a = Win 3.1
#ifndef WINVER
#define WINVER  0x030a
#endif 	// WINVER

#if _MSC_VER >= 800
#define MSCC8			1
#define MSWIND			1
//#define STRICT			1
#define _DYNALINK		1
#endif

#include <cxxtypes.hxx>
#include <cvresid.h>

// entry point types

#if !defined(WIN32)

#if defined(__BCPLUSPLUS__)

#define _DLLENTRY		_export
#define	_DLLENTRY_NODATA    	_export
#define _DISPATCH_ENTRY		_export
#define	PASCAL_FUNC		_pascal
#define	PASCAL_FUNC_DECL	

#elif defined(MSCC8)

#define _DLLENTRY		__export
#define	_DLLENTRY_NODATA    	__export
#define _DISPATCH_ENTRY		__export
#define	PASCAL_FUNC		__pascal
#define	PASCAL_FUNC_DECL	__pascal
#define _TF_ENTRY32

#else

#define _DLLENTRY
#define	_DLLENTRY_NODATA
#define _DISPATCH_ENTRY		_loadds
#define	PASCAL_FUNC
#define	PASCAL_FUNC_DECL	

#endif

#else // WIN32

#define _DLLENTRY		
#define	_DLLENTRY_NODATA    	
#define _DISPATCH_ENTRY		
#define	PASCAL_FUNC		
#define	PASCAL_FUNC_DECL	

#endif // WIN32

#define START_C_FUNCTIONS	extern "C" {
#define END_C_FUNCTIONS		}

// START_C_FUNCTIONS
// typedef	int	(far pascal * FARPROC)();
// END_C_FUNCTIONS


class			CVLink;
class			CVLinked_List;
class			CV_RunTime;
typedef	CVLink			*	pCVLink;
typedef	CVLinked_List	*	pCVLinked_List;

#include 	<_link.hxx>
#include	<CommonVu.hxx>

#include 	<messages.h>
#include 	<cv_imp.hxx>

// #ifdef __ZTC__
// #include 	<_zortech.hxx>
// #endif

#define RNAME_LEN 	30

//	Further #define's required for the implementation

#define	elif	else if

#define GWW_HWNDTEXT	-10

#define GW_HWNDFIRST 0
#define GW_HWNDLAST  1
#define GW_HWNDNEXT  2
#define GW_HWNDPREV  3
#define GW_OWNER     4
#define GW_CHILD     5

#define SC_MASK		0xFFF0
#define SC_SIZE		0xF000
#define SC_MOVE		0xF010
#define SC_MINIMIZE	0xF020
#define SC_MAXIMIZE	0xF030
#define SC_NEXTWINDOW	0xF040
#define SC_PREVWINDOW	0xF050
#define SC_CLOSE	0xF060
#define SC_VSCROLL	0xF070
#define SC_HSCROLL	0xF080
#define SC_MOUSEMENU	0xF090
#define SC_KEYMENU	0xF100
#define SC_ARRANGE	0xF110
#define SC_RESTORE	0xF120
#define SC_ICON		SC_MINIMIZE
#define SC_ZOOM		SC_MAXIMIZE

#define MA_ACTIVATE	    1
#define MA_ACTIVATEANDEAT   2
#define MA_NOACTIVATE	    3

// * 0.13 End *

#define	CV_CTRL_Mask		0xE000

#define	CV_Button		0x2000
#define	CV_ListBox		0x4000
#define	CV_ScrollBar		0x6000
#define	CV_Edit			0x8000
#define	CV_Static		0xA000
#define	CV_WindowSB		0xC000
#define	CV_ComboBox		0xE000

#define	CV4_Button		0x0200
#define	CV4_ListBox		0x0400
#define	CV4_ScrollBar		0x0600
#define	CV4_Edit		0x0800
#define	CV4_Static		0x0A00
#define	CV4_WindowSB		0x0C00
#define	CV4_ComboBox		0x0E00


#define	CTRL_Static		1
#define	CTRL_ScrollBar		2
#define	CTRL_Button		3
#define	CTRL_ListBox		4
#define	CTRL_Edit		5
#define CTRL_ComboBox		6
//#define CTRL_GroupBox   7
#define CTRL_Gauge		7
#if defined(WIN32)
#define CTRL_CTreeListCtrl	8
#define CTRL_CListViewCtrl	9
#define CTRL_ToolTipCtrl	10
#define CTRL_ToolBarCtrl	11
#define CTRL_StatusBarCtrl	12
#define CTRL_SpinButtonCtrl	13
#define CTRL_ProgressBarCtrl	14
#define CTRL_AnimateCtrl	15
#define CTRL_HotkeyCtrl		16
#define CTRL_ComboBoxEx		17
#endif // WIN32

// * required to distinguish Window scrolls from other scrolls * 0.16 *
#define	CTRL_WndScroll		20

// And only related in that they are stored in the same space are ...
// * 0.23 * Directory separator string 

// * 1.2 * window type defines
#define WT_WinType 		1
#define WT_CtrlType		2

//	Further types required for the implementation
typedef	ControlEvt	 *	pControlEvt;
typedef	MenuInitEvt	 *	pMenuInitEvt;
typedef	ScrollEvt	 *	pScrollEvt;
typedef	MessBox		 *	pMessBox;

typedef	void		 *	pvoid;
typedef	void		 *	npvoid;

START_C_FUNCTIONS
extern 	_TF_ENTRY32 pApp_Imp	PASCAL_FUNC _AppFind ( );			// * 0.6 *
extern	_TF_ENTRY32 void	PASCAL_FUNC _AppInsert ( pApp );		// * 0.6 *
extern	_TF_ENTRY32 void	PASCAL_FUNC _AppDelete ( );			// * 0.6 *
extern 	_TF_ENTRY32 pApp_Imp	PASCAL_FUNC _AppImpFind ( );		// * 0.6 *
END_C_FUNCTIONS

// Common windows housekeeping calls

typedef	int		*	pint;
typedef	Point		*	pPoint;
typedef	FixedIcon	*	pFixedIcon;
typedef	FixedText	*	pFixedText;

class	PaintStruct
{
public:
	HDC				hdc;
	bool				fErase;
	Rectangle			rcPaint;
	bool				fRestore;
	bool				fIncUpdate;
	uchar				rgbReserved[ 16 ];
};

typedef	PaintStruct	 *	pPaintStruct;
typedef	WNDCLASS	 *	pWNDCLASS;

/*
 *	The HouseKeeping Data declarations :-
 */
#ifndef	_DYNALINK

extern	bool		 	__CV_Show_Flag;
extern	pApp		 	AppInst;	// The Application Instance Pointer

#else

START_C_FUNCTIONS
enum RegClassString { Rcs_MdiFrame,Rcs_AppWindow,Rcs_MdiChild, Rcs_MdiDefChild   };
extern	pchar	 PASCAL_FUNC	CV_strncpy ( char*, const char *, uint );
extern	pchar	 PASCAL_FUNC	CV_strchr ( const char * , char);
extern 	uint	 PASCAL_FUNC	_GetStringValue ( const char * );
extern 	const char  *	 PASCAL_FUNC _GetString ( uint );
extern 	char  * GetRegClassString ( RegClassString );
extern	int 	 PASCAL_FUNC	IsWin31();
#if defined(WIN32)
extern	bool IsWin40 (void);		// #HK950105
extern	bool IsWin32s (void);		// #HK950705
extern	bool IsWinNT (void);		// #HK950705
#endif 
extern	int 	 PASCAL_FUNC	IsTrueTypeEnabled();
extern	int 	 PASCAL_FUNC	UseTrueTypeOnly();
extern	int 	 PASCAL_FUNC	UsePrivateDC();

// ZORTECH
#if defined(__ZTC__)
extern uint  _getDS();
extern uint  _loadds GetDLLDS();
extern uint  cdecl _setDS(uint); 
extern void  * cdecl getPtrDS();
extern void  * cdecl setPtrDS( void  *);
#endif

END_C_FUNCTIONS

#endif		// _DYNALINK

START_C_FUNCTIONS
extern  uint  cdecl _getDS();
extern	char *	CV_strdup ( const char * );
END_C_FUNCTIONS

/*
 *	Some declarations etc have to be borrowed from 'windows.h'
 */

#define MM_TEXT		    1
#define MM_LOMETRIC	    2
#define MM_HIMETRIC	    3
#define MM_LOENGLISH	    4
#define MM_HIENGLISH	    5
#define MM_TWIPS	    6
#define MM_ISOTROPIC	    7
#define MM_ANISOTROPIC	    8

// #define	MAKEINTRESOURCE(i)	((pchar)((ulong)((uint)(i))))

/* Predefined Resource Types */
#define RT_CURSOR	    MAKEINTRESOURCE(1)
#define RT_BITMAP	    MAKEINTRESOURCE(2)
#define RT_ICON 	    MAKEINTRESOURCE(3)
#define RT_MENU 	    MAKEINTRESOURCE(4)
#define RT_DIALOG	    MAKEINTRESOURCE(5)
#define RT_STRING	    MAKEINTRESOURCE(6)
#define RT_FONTDIR	    MAKEINTRESOURCE(7)
#define RT_FONT 	    MAKEINTRESOURCE(8)
#define RT_ACCELERATOR	    MAKEINTRESOURCE(9)
#define RT_RCDATA	    MAKEINTRESOURCE(10)


#define	BN_CLICKED			0
//#define	BN_DOUBLECLICKED	5

// for Windows 3.1 only
//#define ES_READONLY	    0x00000800L


#define	MK_MASK				0x001F

#ifdef MSCC8
#define MDIS_ALLCHILDSTYLES 0x0001
#define MDITILE_VERTICAL	0x0000
#define MDITILE_HORIZONTAL	0x0001
#define MDITILE_SKIPDISABLED	0x0002
#endif

//
// Values for WndFlags 
// Necessary for correct updating of windows etc.
//

#define WF_IS_DELETE		0x4000
#define	WF_IS_SHOWN			0x2000
#define WF_IS_CHILD			0x1000

#define	WF_SIZE_CHANGED		0x0400
#define WF_MENU_CHANGED		0x0200

#define WF_HAS_CAPTION		0x0080
#define WF_HAS_BORDER		0x0040
#define WF_HAS_MENU			0x0020
#define	WF_HORZSCROLL		0x0010

#define WF_MINBOX			0x0008
#define WF_MAXBOX			0x0004
#define WF_SYSMENU			0x0002
#define	WF_VERTSCROLL		0x0001

#define WF_LEVEL3		( WF_HAS_CAPTION | WF_HAS_MENU | WF_MINBOX | WF_MAXBOX | WF_SYSMENU)
#define	WF_LEVEL2		( WF_HAS_CAPTION | WF_HAS_BORDER | WF_VERTSCROLL | WF_HORZSCROLL)
#define WF_NEED_UPDATE		( WF_SIZE_CHANGED | WF_MENU_CHANGED)

/* Window Xtra flags - related to enabling , disabling, opening and closing */
#define	WFX_OPENED		0x80
#define WFX_INITIALISED		0x40
#define WFX_VSCR_ENABLED	0x20
#define WFX_HSCR_ENABLED	0x10

#define WFX_ANCHORING		0x01
#define WFX_NOREDRAW		0x02
#define WFX_HELPON			0x04
#define WFX_DESTRUCTOR		0x08

/* Termination flags */
#define CV_QUIT_APP	(1)
#define CV_QUIT_EXEC	(2)
#define CV_QUIT_LOOP	(4)

/* SetWindowPos flags */

/* WINWhere area codes */
#define HTNOWHERE      0
#define HTCLIENT       1
#define HTCAPTION      2
#define HTSYSMENU      3
#define HTMENU	       5
#define HTHSCROLL      6
#define HTVSCROLL      7
#define HTLEFT	       10
#define HTRIGHT	       11
#define HTTOP	       12
#define HTTOPLEFT      13
#define HTTOPRIGHT     14
#define HTBOTTOM       15
#define HTBOTTOMLEFT   16
#define HTBOTTOMRIGHT  17
#define HTSIZEFIRST HTLEFT
#define HTSIZELAST  HTBOTTOMRIGHT

#define SM_CXSCREEN	   0
#define SM_CYSCREEN	   1
#define SM_CXVSCROLL   2
#define SM_CYHSCROLL   3
#define SM_CYCAPTION   4
#define SM_CXBORDER	   5
#define SM_CYBORDER	   6
//#define SM_CXDLGFRAME  7
//#define SM_CYDLGFRAME  8
#define SM_CYVTHUMB	   9
#define SM_CXHTHUMB	  10
#define SM_CXICON	  11
#define SM_CYICON	  12
#define SM_CXCURSOR	  13
#define SM_CYCURSOR	  14
#define SM_CYMENU	  15
#define SM_CXFULLSCREEN	  16
#define SM_CYFULLSCREEN	  17
#define SM_CYKANJIWINDOW  18
#define SM_MOUSEPRESENT	  19
#define SM_CYVSCROLL	  20
#define SM_CXHSCROLL	  21
#define SM_DEBUG	  22
#define SM_SWAPBUTTON	  23
#define SM_RESERVED1	  24
#define SM_RESERVED2	  25
#define SM_RESERVED3	  26	    /* new additions since 2.0 */
#define SM_RESERVED4	  27
#define SM_CXMIN	  28
#define SM_CYMIN	  29
#define SM_CXSIZE	  30
#define SM_CYSIZE	  31
//#define SM_CXFRAME	  32
//#define SM_CYFRAME	  33
#define SM_CXMINTRACK	  34
#define SM_CYMINTRACK	  35
// #define SM_CMETRICS	  36


#ifndef NOMESSBOX
// defines for Message box construction
//#define MB_OK		    0x0000
//#define MB_OKCANCEL	    0x0001
//#define MB_ABORTRETRYIGNORE 0x0002
//#define MB_YESNOCANCEL	    0x0003
//#define MB_YESNO	    0x0004
//#define MB_RETRYCANCEL	    0x0005

//#define MB_ICONHAND	    0x0010
//#define MB_ICONQUESTION	    0x0020
//#define MB_ICONEXCLAMATION  0x0030
//#define MB_ICONASTERISK	    0x0040

//#define MB_DEFBUTTON1	    0x0000
//#define MB_DEFBUTTON2	    0x0100
//#define MB_DEFBUTTON3	    0x0200

//#define MB_APPLMODAL	    0x0000
//#define MB_SYSTEMMODAL	0x1000
//#define MB_TASKMODAL	    0x2000

//#define MB_NOFOCUS	    0x8000
//#define MB_MISCMASK	    0xC000
//#define MB_TYPEMASK	    0x000F
//#define MB_ICONMASK	    0x00F0
//#define MB_DEFMASK	    0x0F00
//#define MB_MODEMASK	    0x3000
#endif

#define IDOK	  1
#define IDCANCEL  2
#define IDABORT	  3
#define IDRETRY	  4
#define IDIGNORE  5
#define IDYES	  6
#define IDNO	  7

#ifndef NOAPP
// Class creation styles
#define	CS_VREDRAW		0x0001
#define	CS_HREDRAW		0x0002
#define	CS_DBLCLKS		0x0008
#define CS_BYTEALIGNCLIENT  	0x1000
#define CS_BYTEALIGNWINDOW  	0x2000
#define CS_OWNDC	    	0x0020

#define CS_GLOBALCLASS	    	0x4000    /* Global window class */

class SystemApp : public App
{
public:
	 _TF_ENTRY32 SystemApp (uint, HINSTANCE, HINSTANCE, const char *, int);
};

#endif

#ifndef NOMENU
class SystemMenu : public SysMenu {
public:
	SystemMenu (pWindow pw) : SysMenu (pw) {}
};

#endif

#include	<CVD.hxx>

#ifndef NODEBUGGING
extern 	int			CVDebugging;
extern 	int			CVProfiling;
#endif

//	Font Weight Values :-

#define	LIGHTWEIGHT			200
#define	NORMALWEIGHT			400
#define	HEAVYWEIGHT			700

#include <winfns.h>
#include <cv_impi.hxx>
#include "_runtime.hxx"


// ****************************
// Help system declarations
// ****************************
extern HCURSOR hHelpCursor;

// Help modes
#define HM_GENERAL 	1
#define HM_MOUSE	2
#define HM_NONE		3

// String functions

inline int CV_strcmp ( const char* a, const char* b) { return strcmp(a,b); }
inline uint CV_strlen ( const char* a) { return strlen(a); }
inline char  *CV_strcat(char* a, const char * b) { return strcat(a,b); }
inline char  *CV_strcpy(char* a, const char* b) { return strcpy(a, b); }


// Text alignment tags
// Stock objects
/* Stock Logical Objects */
#define WHITE_BRUSH	    0
#define LTGRAY_BRUSH	    1
#define GRAY_BRUSH	    2
#define DKGRAY_BRUSH	    3
#define BLACK_BRUSH	    4
#define NULL_BRUSH	    5
#define HOLLOW_BRUSH	    NULL_BRUSH
#define WHITE_PEN	    6
#define BLACK_PEN	    7
#define NULL_PEN	    8
#define OEM_FIXED_FONT	    10
#define ANSI_FIXED_FONT     11
#define ANSI_VAR_FONT	    12
#define SYSTEM_FONT	    13
#define DEVICE_DEFAULT_FONT 14
#define DEFAULT_PALETTE     15
#define SYSTEM_FIXED_FONT   16

// Brush Styles
#define BS_SOLID	    0
#define BS_NULL		    1
#define BS_HOLLOW	    BS_NULL
#define BS_HATCHED	    2
#define BS_PATTERN	    3
#define BS_INDEXED	    4
#define	BS_DIBPATTERN	    5

/* Hatch Styles */
#define HS_HORIZONTAL	    0	    /* ----- */
#define HS_VERTICAL	    1	    /* ||||| */
#define HS_FDIAGONAL	    2	    /* \\\\\ */
#define HS_BDIAGONAL	    3	    /* ///// */
#define HS_CROSS	    4	    /* +++++ */
#define HS_DIAGCROSS	    5	    /* xxxxx */

/* Pen Styles */
#define PS_SOLID	    0
#define PS_DASH		    1	    /* -------	*/
#define PS_DOT		    2	    /* .......	*/
#define PS_DASHDOT	    3	    /* _._._._	*/
#define PS_DASHDOTDOT	    4	    /* _.._.._	*/
#define PS_NULL 	    5
#define PS_INSIDEFRAME 	    6

/* Color Types for  Color management*/
#define CTLCOLOR_MSGBOX		0
#define CTLCOLOR_EDIT		1
#define CTLCOLOR_LISTBOX	2
#define CTLCOLOR_BTN		3
#define CTLCOLOR_DLG		4
#define CTLCOLOR_SCROLLBAR	5
#define CTLCOLOR_STATIC		6
//#define CTLCOLOR_MAX		8     /* three bits max */

#define COLOR_SCROLLBAR		0
//#define COLOR_BACKGROUND	1
#define COLOR_ACTIVECAPTION	2
#define COLOR_INACTIVECAPTION	3
#define COLOR_MENU		4
#define COLOR_WINDOW		5
#define COLOR_WINDOWFRAME	6
#define COLOR_MENUTEXT		7
#define COLOR_WINDOWTEXT	8
#define COLOR_CAPTIONTEXT	9
#define COLOR_ACTIVEBORDER	10
#define COLOR_INACTIVEBORDER	11
#define COLOR_APPWORKSPACE	12
#define COLOR_HIGHLIGHT		13
#define COLOR_HIGHLIGHTTEXT	14
//#define COLOR_BTNFACE           15
//#define COLOR_BTNSHADOW         16
#define COLOR_GRAYTEXT          17
#define COLOR_BTNTEXT		18
#define COLOR_ENDCOLORS 	COLOR_BTNTEXT

/* Device Parameters for GetDeviceCaps() */
#define DRIVERVERSION 0     /* Device driver version			*/
#define TECHNOLOGY    2     /* Device classification			*/
#define HORZSIZE      4     /* Horizontal size in millimeters		*/
#define VERTSIZE      6     /* Vertical size in millimeters		*/
#define HORZRES       8     /* Horizontal width in pixels		*/
#define VERTRES       10    /* Vertical width in pixels 		*/
#define BITSPIXEL     12    /* Number of bits per pixel 		*/
#define PLANES	      14    /* Number of planes 			*/
#define NUMBRUSHES    16    /* Number of brushes the device has 	*/
#define NUMPENS       18    /* Number of pens the device has		*/
#define NUMMARKERS    20    /* Number of markers the device has 	*/
#define NUMFONTS      22    /* Number of fonts the device has		*/
#define NUMCOLORS     24    /* Number of colors the device supports	*/
#define PDEVICESIZE   26    /* Size required for device descriptor	*/
#define CURVECAPS     28    /* Curve capabilities			*/
#define LINECAPS      30    /* Line capabilities			*/
#define POLYGONALCAPS 32    /* Polygonal capabilities			*/
#define TEXTCAPS      34    /* Text capabilities			*/
#define CLIPCAPS      36    /* Clipping capabilities			*/
#define RASTERCAPS    38    /* Bitblt capabilities			*/
#define ASPECTX       40    /* Length of the X leg			*/
#define ASPECTY       42    /* Length of the Y leg			*/
#define ASPECTXY      44    /* Length of the hypotenuse 		*/

#define LOGPIXELSX    88    /* Logical pixels/inch in X 		*/
#define LOGPIXELSY    90    /* Logical pixels/inch in Y 		*/

#define SIZEPALETTE  104    /* Number of entries in physical palette	*/
#define NUMRESERVED  106    /* Number of reserved entries in palette	*/
#define COLORRES     108    /* Actual color resolution 			*/

/* Device Capability Masks: */
/* Device Technologies */
#define DT_PLOTTER	    0	/* Vector plotter		    */
#define DT_RASDISPLAY	    1	/* Raster display		    */
#define DT_RASPRINTER	    2	/* Raster printer		    */
#define DT_RASCAMERA	    3	/* Raster camera		    */
#define DT_CHARSTREAM	    4	/* Character-stream, PLP	    */
#define DT_METAFILE	    5	/* Metafile, VDM		    */
#define DT_DISPFILE	    6	/* Display-file 		    */


/* Text Capabilities */
//#define TC_OP_CHARACTER     0x0001  /* Can do OutputPrecision	CHARACTER      */
//#define TC_OP_STROKE	    0x0002  /* Can do OutputPrecision	STROKE	       */
//#define TC_CP_STROKE	    0x0004  /* Can do ClipPrecision	STROKE	       */
//#define TC_CR_90	    0x0008  /* Can do CharRotAbility	90	       */
//#define TC_CR_ANY	    0x0010  /* Can do CharRotAbility	ANY	       */
//#define TC_SF_X_YINDEP	    0x0020  /* Can do ScaleFreedom	X_YINDEPENDENT */
//#define TC_SA_DOUBLE	    0x0040  /* Can do ScaleAbility	DOUBLE	       */
//#define TC_SA_INTEGER	    0x0080  /* Can do ScaleAbility	INTEGER        */
//#define TC_SA_CONTIN	    0x0100  /* Can do ScaleAbility	CONTINUOUS     */
//#define TC_EA_DOUBLE	    0x0200  /* Can do EmboldenAbility	DOUBLE	       */
//#define TC_IA_ABLE	    0x0400  /* Can do ItalisizeAbility	ABLE	       */
//#define TC_UA_ABLE	    0x0800  /* Can do UnderlineAbility	ABLE	       */
//#define TC_SO_ABLE	    0x1000  /* Can do StrikeOutAbility	ABLE	       */
//#define TC_RA_ABLE	    0x2000  /* Can do RasterFontAble	ABLE	       */
//#define TC_VA_ABLE	    0x4000  /* Can do VectorFontAble	ABLE	       */
//#define TC_RESERVED	    0x8000


/* Raster Capabilities */
#define	RC_GDI20_OUTPUT	    0x0010	/* has 2.0 output calls	 	*/
#define	RC_DI_BITMAP	    0x0080	/* supports DIB to memory	*/
#define	RC_PALETTE	    0x0100	/* supports a palette		*/
#define	RC_DIBTODEV	    0x0200	/* supports DIBitsToDevice	*/
#define	RC_BIGFONT	    0x0400	/* supports >64K fonts		*/
#define	RC_STRETCHBLT	    0x0800	/* supports StretchBlt		*/
#define	RC_FLOODFILL	    0x1000	/* supports FloodFill		*/
#define	RC_STRETCHDIB	    0x2000	/* supports StretchDIBits	*/

extern char *InitPrStdFonts (HDC);

#if defined(BETA) || defined(_DEBUG)

#define CV_ASSERT(x) _ASSERTE((x))			// { CVDebug(CVD_Always,"Assertion Failed %s @ %s,%d", #x, __FILE__, __LINE__); DebugBreak(); }
#define CV_ASSERT_VALID(x) _ASSERTE((x))	// { CVDebug(CVD_Always,"Object invalid %s @ %s,%d", #x, __FILE__, __LINE__); DebugBreak(); }
#define CV_NOTE(x) CVDebug(CVD_Always, (x))

#if !defined(WIN32)
#define CV_ASSERT_DLLDS() if (_getDS() != GetDLLDS()) DebugBreak()
#define CV_ASSERT_APPDS() if (_getDS() == GetDLLDS()) DebugBreak()
#else // WIN32
#define CV_ASSERT_DLLDS()
#define CV_ASSERT_APPDS()
#endif // WIN32

#else // !_DEBUG && !BETA
#define CV_ASSERT(x)
#define CV_ASSERT_VALID(x)
#define CV_NOTE(x)
#define CV_ASSERT_DLLDS()
#define CV_ASSERT_APPDS()
#endif


#define RDW_INVALIDATE		0x0001
#define RDW_INTERNALPAINT	0x0002
#define RDW_ERASE		0x0004

#define RDW_VALIDATE		0x0008
#define RDW_NOINTERNALPAINT	0x0010
#define RDW_NOERASE		0x0020

#define RDW_NOCHILDREN		0x0040
#define RDW_ALLCHILDREN 	0x0080

#define RDW_UPDATENOW		0x0100
#define RDW_ERASENOW		0x0200

#define RDW_FRAME               0x0400
#define RDW_NOFRAME             0x0800


#if defined(WIN32)
#define WM_MYMDISETMENU		(WM_USER+0x4444)
#endif

#endif		// __COMONVU_HXX

