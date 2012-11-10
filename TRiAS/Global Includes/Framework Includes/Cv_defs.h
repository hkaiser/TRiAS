//	CommonView also requires a few enumerated types which are listed below.
//	#define's are used, but the intended representations are enum's.

#ifndef	_CV_DEFS_HXX
#define	_CV_DEFS_HXX

enum Colors { BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE };

enum StdPointer
{
	CrossHairs,		
	IBeam,			
	Icon_Pointer,	
	FourPointArrow,	
	UpArrow,			
	HourGlass,		
	Arrow			
};

enum StdBrush		// The list of standard brushes
{
	DarkBrush =	1,
	MediumBrush =	2,
	LightBrush =	3,
	WhiteBrush =	4,
	HollowBrush =	5,
	ClearBrush =	6,
	BlackBrush =	7	
};

enum StdHatchStyle	// The list of standard hatch styles
{
	SolidHatch, 				
	Diagonal_45, 				
	VerticalHatch, 			
	Diagonal_135, 			
	HorizontalHatch, 			
	OrthogonalCrossHatch, 	
	DiagonalCrossHatch		
};

enum StdLineStyle	// The list of standard line styles
{
	SolidLine, 		
	Dashed, 			
	Dotted, 			
	Dash_Dot, 		
	Dash_Dot_Dot, 	
	ClearLine,		
	InsideFrameLine
};

enum StdFamily		// The list of standard font families
{
	Decorative, 		
	Any, 				
	Modern, 			
	Roman, 			
	Script, 			
	Swiss			
};

#if _MSC_VER >= 1100
enum StdFonts		// The list of standard fonts
#else
enum StdFont		// The list of standard fonts
#endif
{
	Modern8, 		
	Modern10, 	
	Modern12, 	

	Roman8,   	
	Roman10, 		
	Roman12, 		
	Roman14, 		
	Roman18, 		
	Roman24, 		

	Swiss8, 		
	Swiss10, 		
	Swiss12, 		
	Swiss14, 		
	Swiss18, 		
	Swiss24, 		

	SystemFont8
};


enum StdIcon		// The list of standard icons
{
	Hand			= 1,
	QuestionMark	= 2,
	Exclamation		= 3,
	Asterisk		= 4,
	StandardIcon	= 5
};

//	enum	StdMessBox		// The list of standard message boxes
#define	StdMessBox int

	// NB :-	you may combine one item from each group
	// Group 1 :-	the standard button combinations

#ifdef MSWIND
	#define	OkayButton				0
	#define	OkayCancelButtons		1
	#define	AbortRetryIgnoreButtons	2
	#define	YesNoCancelButtons		3
	#define	YesNoButtons			4
	#define	RetryCancel				5
#elif PM
	#define	OkayButton				0
	#define	OkayCancelButtons		1
	#define	AbortRetryIgnoreButtons	3
	#define	YesNoCancelButtons		5
	#define	YesNoButtons			4
	#define	RetryCancel				2
#endif

	// Group 2 :-	the standard icons allowed
#ifdef MSWIND
	#define	HandIcon			0x10
	#define	QuestionMarkIcon	0x20
	#define	ExclamationIcon		0x30
	#define	AsteriskIcon		0x40
	#define SetForeground		MB_SETFOREGROUND
	#define SystemModal			MB_SYSTEMMODAL
#elif PM
	#define	HandIcon			0x40
	#define	QuestionMarkIcon	0x10
	#define	ExclamationIcon		0x20
	#define	AsteriskIcon		0x30
#endif

enum StdMessBoxReply	// The list of standard message box replies
{
	AbortReply, 	   
	CancelReply, 	   
	IgnoreReply, 	   
	NoReply, 		   
	OkayReply, 	   
	RetryReply, 	   
	YesReply
};

enum Buttons		// The list of standard mouse buttons
{
	LeftButton		= 1,
	RightButton		= 2, 
	ShiftButton		= 4, 
	ControlButton	= 8, 
	MiddleButton	= 16
};

enum ScrollType
{
	EndScroll, 		
	BlockIncrement, 	
	UnitIncrement, 	
	ThumbDrag, 		
	UnitDecrement, 	
	BlockDecrement, 	
	ToTopLeft, 		
	ToBottomRight,	
	EndScrollThumb, 
};

enum FontWeights	// The list of standard font weights
{
	NormalWeight, 	
	LightWeight, 		
	HeavyWeight		
};

enum PitchTypes		// The list of standard font pitches
{
	FixedPitch	  = 1,
	VariablePitch = 2
};

enum PaintMode		// The list of standard painting modes
{
	Fill, 			
	Invert, 			
	Frame			
};

enum RopType		// The list of standard raster operations
{
	ROP_Overwrite, 		
	ROP_Background, 		
	ROP_Invert, 			
	ROP_XOR		 
};	


// Attributes for FileListBoxes
// These are or'ed together to indicate which types of files should be 
// listed
#define FLB_ReadOnly	0x1
#define FLB_Hidden		0x2
#define FLB_System		0x4
#define FLB_SubDir		0x10
#define FLB_Drives		0x4000
#define FLB_Exclusive	0x8000

enum FlbStatus		// List of error codes for file list boxes
{
	FlbFileOk,        
	FlbFileInvalid,   
	FlbFileNotFound,  
	FlbFileExpanded 
};

enum ShowState { 
	Normal, 
	Zoomed, 
	Iconized, 
	HideWindow, 
	Centre, 
	NoActivate = 0x100, 
	NoQuitOnHide = 0x200,		// internal use only (#HK960821)
	NoParentDisabling = 0x400,	// internal use only (#HK990401)
};
#define SHOWSTATE_STATE	0xff

// enum InvokeStatus
#define InvokeStatus	int
#define IdleInit		TRUE
#define IdleExec		FALSE

// enum OnOff
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
#define	CVOnOff		Bool
#define	CVOn		TRUE
#define	CVOff		FALSE
#else
#define	OnOff		Bool
#define	On			TRUE
#define	Off			FALSE
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)

#ifdef MSWIND
	#define KeyCancel		0x03
	#define KeyBackSpace	0x08
	#define KeyTab			0x09
	#define KeyEnter		0x0D
	#define KeyShift		0x10
	#define KeyCtrl			0x11
	#define KeyAlt			0x12
	#define KeyPause		0x13
	#define KeyCapsLock		0x14
	#define KeyEsc			0x1B
	#define KeySpace		0x20
	#define KeyPageUp		0x21
	#define KeyPageDn		0x22
	#define KeyEnd			0x23
	#define KeyHome			0x24
	#define KeyArrowLt		0x25
	#define KeyArrowUp		0x26
	#define KeyArrowRt		0x27
	#define KeyArrowDn		0x28
	#define KeyPrint		0x2A
	#define KeyInsert		0x2D
	#define KeyDelete		0x2E
	#define KeyNumlock		0x90
	#define KeyF1			0x70
	#define KeyF2			0x71
	#define KeyF3			0x72
	#define KeyF4			0x73
	#define KeyF5			0x74
	#define KeyF6			0x75
	#define KeyF7			0x76
	#define KeyF8			0x77
	#define KeyF9			0x78
	#define KeyF10			0x79
	#define KeyF11			0x7A
	#define KeyF12			0x7B
	#define KeyF13			0x7C
	#define KeyF14			0x7D
	#define KeyF15			0x7E
	#define KeyF16			0x7F
#elif PM
	#define KeyCancel		0x04
	#define KeyBackSpace	0x05
	#define KeyTab			0x06
	#define KeyEnter		0x1E
	#define KeyShift		0x09
	#define KeyCtrl			0x0A
	#define KeyAlt			0x0B
	#define KeyPause		0x0D
	#define KeyCapslock		0x0E
	#define KeyEsc			0x0F
	#define KeySpace		0x10
	#define KeyPageUp		0x11
	#define KeyPageDn		0x12
	#define KeyEnd			0x13
	#define KeyHome			0x14
	#define KeyArrowLt		0x15
	#define KeyArrowUp		0x16
	#define KeyArrowRt		0x17
	#define KeyArrowDn		0x18
	#define KeyPrint		0x19
	#define KeyInsert		0x1A
	#define KeyDelete		0x1B
	#define KeyNumlock 		0x1D
	#define KeyF1			0x20
	#define KeyF2			0x21
	#define KeyF3			0x22
	#define KeyF4			0x23
	#define KeyF5			0x24
	#define KeyF6			0x25
	#define KeyF7			0x26
	#define KeyF8			0x27
	#define KeyF9			0x28
	#define KeyF10			0x29
	#define KeyF11			0x2A
	#define KeyF12			0x2B
	#define KeyF13			0x2C
	#define KeyF14			0x2D
	#define KeyF15			0x2E
	#define KeyF16			0x2F
#endif		 										

// API services
#if MSWIND

#define	API_ACCEL_HACCEL		0

#define	API_APP_HAB			0

#define API_APP_HAPP			0
#define	API_APP_HMQ			1
#define	API_APP_HHEAP			2
#define API_APP_COMMANDL		3
#define API_APP_HPREV			4

#define	API_BITMAP_HBITMAP		0

#define	API_CONTROL_HCONTROL		0
#define API_CONTROL_HDC			1		// #HK920503

#define	API_CURSOR_HCURSOR		3

#define	API_ICON_HICON			0
#define	API_MENU_HMENU			0
#define	API_CLIENT_HWND			0
#define API_WINDOW_HWND			0

#define API_DRAWOBJECT_HDC		0		// #HK920128
#define API_TARGET_HDC			1		// #HK940116

#define API_DLGWINDOW_HWND		0		// #HK921107

#define	API_WINDOW_HPS			0
#define	API_FRAME_HWND			1
#define	API_CLIENT_HPS			2
#define	API_WINDOW_HDC			2
#define	API_DIALOG_HMODELESS		3
#define	API_MDICLIENT_HWND		4
#define	API_WINDOW_TARGETHDC		5		// #HK940119
#define API_WINDOW_HPROPSHEETPAGE	6		// #HK951115

#define	API_POINTER_HPOINTER		0
#define API_FONT_HFONT			0
#define API_PEN_HPEN			0

#elif PM
#define	API_ACCEL_HACCEL		0
#define	API_APP_HAB				0
#define	API_APP_HMQ				1
#define	API_APP_HHEAP			2
#define	API_BITMAP_HBITMAP		0
#define	API_CONTROL_HCONTROL	0
#define	API_CURSOR_HCURSOR		3
#define	API_ICON_HICON			0
#define	API_MENU_HMENU			0
#define	API_CLIENT_HWND			0
#define	API_FRAME_HWND			1
#define	API_CLIENT_HPS			2
#define	API_POINTER_HPOINTER	0
#define	API_WINDOW_HPS			0
#endif

enum HdError { HdOk, HdCantOpenFile, HdOutOfMemory, HdInvalidKey, HdUnknown };

enum ExecType { 
	ExecNormal, 
	ExecWhileEvent, 
	ExecWhileEventWithIdle,		// #HK960706
	ExecIdleOnly,
	ExecNormalNoQuitOnHide,		// internal use only (#HK960821)
};

enum WindowArea {
	WindowCanvas = 0, 
	Caption, 
	SizeBox, 
	MinBox, 
	MaxBox, 
	SysMenuBox, 
	Border, 
	UnknownArea, 
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
	CVMenuBar
#else
	MenuBar, 
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
};

enum HelpType { HelpMenu = 0, HelpControl, HelpWindow, HelpWmHelp };

#endif // _CV_DEFS_HXX
