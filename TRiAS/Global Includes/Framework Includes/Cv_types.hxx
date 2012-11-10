//	Protect against multiple inclusions

#ifndef	_CV_TYPES_HXX
#define	_CV_TYPES_HXX

#if !defined(_TF_ENTRY32)

#if defined(WIN32)
#undef _DLLENTRY
#define _DLLENTRY

#if defined(__TFDLL__)
#define _TF_ENTRY32 __declspec(dllexport)
#else

#if !defined(__TFLIB__)
#define _TF_ENTRY32 __declspec(dllimport)
#else
#define _TF_ENTRY32
#endif // __TFLIB__

#endif // __TFDLL__

#else
#define _TF_ENTRY32
#endif // WIN32

#endif // _TF_ENTRY32

#ifdef PM
	#define	HANDLE	void *
#elif MSWIND
#if defined(__WATCOMC__) && defined(__386__)
	#define HANDLE 	unsigned short
#else
#if !defined(WIN32)
	#define	HANDLE	unsigned int
#else
	#define HANDLE	LPVOID
#endif
#endif
#endif

//	Types required by CommonView
//	The primitive types :-

#ifdef PM
	typedef	long		CoOrd;
#elif MSWIND
#if defined (__WATCOMC__) && defined(__386__)
	typedef short int	CoOrd;
#else
#if !defined(WIN32)
	typedef	short int	CoOrd;
#else
	typedef LONG		CoOrd;
#endif
#endif
#endif

typedef unsigned char 		ColorVal;
typedef	unsigned short *	pushort;
typedef	unsigned short 		ushort;

typedef	unsigned short		Service;

//	The classes required by CommonView :-
//	Indentation indicates relative position in the inheritance hierarchy

//		RunTime Support types :-
class	CV_RunTime;

//		Ordered pairs :-
class	Pair;
class		Point;
class		Dimension;
class		Range;
class		Selection;

//		General Support Types :-
class	ResID;
class	Rectangle;
class	ResString;
class	Accel;
class	Color;

typedef Rectangle * pRectangle;

//		The Application Type :-
class	App;

//		The Tools :-
class	Cursor;
class	Pointer;
class	Brush;
class	Bitmap;
class	Pen;
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
class	CVFont;
#else 
class	Font;
#endif // _TRIAS_OLDIMPLEMENTATION2
class	Icon;
class	DrawObject;

class	MessBox;
class		ErrorBox;

class	Menu;
class		SysMenu;

//		The Types of Events :-
class	Event;
class		MouseEvt;
class		ReSizeEvt;
class		MoveEvt;
class		FocusChangeEvt;
class		KeyEvt;
class		ExposeEvt;
class		MenuInitEvt;
class		MenuSelectEvt;
class		MenuCommandEvt;
class		ScrollEvt;
class		ControlEvt;

//		The Contexts within which Events can occur :-
class	EventContext;
class		Window;
class			AppWindow;
class				TopAppWindow;
class				ChildAppWindow;
class				ShellWindow;
class	PrintingDevice;
class 			Printer;
class			DialogWindow;
class				ModeLessDialog;

//		Control Types used by Event Contexts :-
class	Control;
class		FixedIcon;
class		ScrollBar;
class			VertScrollBar;
class			WndVertScrollBar;
class			HorizScrollBar;
class			WndHorzScrollBar;
class		TextControl;
class			Button;
class				RadioButton;
class				PushButton;
class				CheckBox;
class			ListBox;
class			Edit;
class				MultiLineEdit;
class				SingleLineEdit;
class			FixedText;

// Miscellaneous

class	HelpDisplay;

//	Pointers to many of these types are required, so ...
typedef	Point &		rPoint;
typedef	Rectangle &	rRectangle;

typedef	App				 *	pApp;
typedef	Accel			 *	pAccel;

typedef	Pointer			 *	pPointer;
typedef	Brush			 *	pBrush;
typedef	Bitmap			 *	pBitmap;
typedef	Pen				 *	pPen;
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
typedef	CVFont			 *	pFont;
#else 
typedef	Font			 *	pFont;
#endif // _TRIAS_OLDIMPLEMENTATION2
typedef	Icon			 *	pIcon;
typedef DrawObject		 *	pDrawObject;

typedef	Menu			 *	pMenu;
typedef SysMenu			 *	pSysMenu;

typedef	EventContext	 *	pEventContext;
typedef	Window			 *	pWindow;
typedef	AppWindow		 *	pAppWindow;
typedef	DialogWindow	 *	pDialogWindow;
typedef	ModeLessDialog	 *	pModeLessDialog;

typedef	Control			 *	pControl;
typedef	ScrollBar		 *	pScrollBar;
typedef	WndVertScrollBar *	pWndVertScroll;
typedef	WndHorzScrollBar *	pWndHorzScroll;

class	Accel_Imp;
class	App_Imp;
class	Bitmap_Imp;
class	Icon_Imp;
class	Cursor_Imp;
class	Pointer_Imp;
class	Brush_Imp;
class	Pen_Imp;
class	Font_Imp;
class 	Menu_Imp;

class	Control_Imp;
class	FixedIcon_Imp;
class	ScrollB_Imp;
class	VScrollB_Imp;
class 	WndVScrollB_Imp;
class	HScrollB_Imp;
class 	WndHScrollB_Imp;
class	TextControl_Imp;
class	Button_Imp;
class	RadioButton_Imp;
class	PushButton_Imp;
class	CheckBox_Imp;
class	ListBox_Imp;
class	FileListBox_Imp;
class	Edit_Imp;
class	MultiLineEdit_Imp;
class	SingleLineEdit_Imp;
class	FixedText_Imp;

class	EC_Imp;
class	Wind_Imp;
class 	AWind_Imp;
class 	TAWind_Imp;
class 	CAWind_Imp;
class 	DWind_Imp;
class 	MDWind_Imp;
class	CWind_Imp;
class 	EWind_Imp;
class   ShellWind_Imp;
class 	MessBox_Imp; 
class	ResFile_Imp;
class HelpDisp_Imp;
class PrintingDevice_Imp;
class DispatchWindow;

typedef Control_Imp * pControl_Imp;
typedef FixedIcon_Imp * pFixedIcon_Imp;
typedef ScrollB_Imp * pScrollB_Imp;
typedef VScrollB_Imp * pVScrollB_Imp;
typedef WndVScrollB_Imp * pWndVScrollB_Imp;
typedef HScrollB_Imp * pHScrollB_Imp;
typedef WndHScrollB_Imp * pWndHScrollB_Imp;
typedef TextControl_Imp * pTextControl_Imp;
typedef Button_Imp * pButton_Imp;
typedef RadioButton_Imp * pRadioButton_Imp;
typedef PushButton_Imp * pPushButton_Imp;
typedef CheckBox_Imp * pCheckBox_Imp;
typedef ListBox_Imp * pListBox_Imp;
typedef FileListBox_Imp * pFileListBox_Imp;
typedef Edit_Imp * pEdit_Imp;
typedef MultiLineEdit_Imp * pMultiLineEdit_Imp;
typedef SingleLineEdit_Imp * pSingleLineEdit_Imp;
typedef FixedText_Imp * pFixedText_Imp;

typedef	Accel_Imp		 *	pAccel_Imp;
typedef	App_Imp			 *	pApp_Imp;
typedef	AWind_Imp		 *	pAWind_Imp;
typedef	Bitmap_Imp		 *	pBitmap_Imp;
typedef	CAWind_Imp		 *	pCAWind_Imp;
typedef	CWind_Imp		 *	pCWind_Imp;
typedef	DWind_Imp		 *	pDWind_Imp;
typedef	EC_Imp			 *	pEC_Imp;
typedef	EWind_Imp		 *	pEWind_Imp;
typedef	Icon_Imp		 *	pIcon_Imp;
typedef	TAWind_Imp		 *	pTAWind_Imp;
typedef	Wind_Imp		 *	pWind_Imp;
typedef	Cursor_Imp		 *	pCursor_Imp;
typedef	Pointer_Imp		 *	pPointer_Imp;
typedef	Brush_Imp		 *	pBrush_Imp;
typedef	Pen_Imp			 *	pPen_Imp;
typedef	Font_Imp		 *	pFont_Imp;
typedef	Menu_Imp		 *	pMenu_Imp;
typedef	MessBox_Imp		 *	pMessBox_Imp;

// #HK960214: Stuff zum Einbinden der MFC-Hierarchie
typedef BOOL PRETRANSLATEFUNC (MSG *pMsg);
typedef PRETRANSLATEFUNC *PRETRANSLATEPROC;
typedef BOOL IDLEFUNC (LONG);
typedef IDLEFUNC *IDLEPROC;

// #HK961014: PropertySheets, die 2.
typedef BOOL CONTINUEMODALFUNC (DWORD dwDataCM);
typedef CONTINUEMODALFUNC *CONTINUEMODALPROC;

#endif // _CV_TYPES_HXX
