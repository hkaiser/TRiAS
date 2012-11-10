//	Usage:	#include <CV_IMP.hxx>
//
//	Implementor interface to CA-CommonView release 3.1, 
//
//  Copyright (c) 1992 Trischford Limited 
//  ( A wholly owned subsidary of Computer Associates International, Inc)
//  All Rights Reserved
//
//	Version 3.1			Nov 1992
//
//	Tab stops in this file are at	4 * n + 1
//
//	-------------------------------------------------------------------------

//
//	Have we already included commonvu.hxx ?

#ifndef	_CV_IMP_HXX
#define	_CV_IMP_HXX	1

#include	<cxxtypes.hxx>
#include	<CV_types.hxx>
#include	<CV_defs.h>

class ResFile_Imp {
private:
	HINSTANCE hLib;
	ResourceFile *m_pReq;		// Rückverweis

public:
	HINSTANCE Handle (void) { return hLib; }
	ResFile_Imp (const char *, ResourceFile *pReq);
	~ResFile_Imp (void);
};

class HelpDisp_Imp {
private:
	char * helpfile;
	HWND 	helpwnd;
	HdError error;

	BOOL	VerifyHelp();

public:
		HelpDisp_Imp ( const char * );

	BOOL	Show( const char * );
	BOOL	Show( ulong );
	HdError	HelpError();

		~HelpDisp_Imp();
};

#ifndef	NOAPP				// Put all your App functions in one module
class	App_Imp
{
friend	class	    CV_RunTime;

enum 	IdleState { IdleFirstTime, IdlePresent, IdleNotPresent };

	IdleState			IdleStatus;

	short				status;
	short 				WindowCount;
	void				(App :: * IdleFunc)( int);
	uint				DS_segment;
	HINSTANCE			hApp;
	HINSTANCE			hPrevInst;
	HWND				LastDlgHandle;
	HWND				MDIClientHandle;
	FARPROC				DlgDispatch;
	FARPROC				EvtDispatch;
	char *				Commandl;
	char **				argv;
	int 				argc;
	App*				pRequestor;

	CVLinked_List		List_of_EventContexts;
	CVLinked_List		List_of_Menus;
	CVLinked_List		List_of_Controls;
	CVLinked_List		List_of_Printers;
	CVLinked_List		List_of_Resources;
#if defined(WIN32)
	CVLinked_List		List_of_ImageLists;

	BOOL				m_fQuitOnLast;

	CONTINUEMODALPROC	m_pCM;
	DWORD				m_dwDataCM;
#endif // // WIN32

	CVTable  			List_of_RegClasses;

	Dimension			AppScreenSize;	//	Size of screen in pixels

// Help support data
	HACCEL				hHelpAccel;		// Accelerator for current help wind
	HWND				hHelpWnd;		// Window currently handling help

	HACCEL 			hWndAccel;
	HWND			hAccelRecv; 


	void			ParseArgs();

// Control Color Management
	HBRUSH			DefBackBrush;
	COLORREF		BackColor;
	COLORREF		TextColor;

public:
	void			InitColors (void);
	HBRUSH			GetDefBackBrush (void) 	{ return DefBackBrush; }
	COLORREF		GetBackColor (void) { return BackColor; }
	COLORREF		GetTextColor (void) 	{ return TextColor; }

	HINSTANCE 		FindResourceModule (ResID &resID, LPCSTR lpszType);	

public:
		App_Imp (App *, uint, HINSTANCE, HINSTANCE, const char*, int );

	int				Exec (BOOL **, ExecType = ExecNormal, CONTINUEMODALPROC pCM = NULL, DWORD dwDataCM = 0L);
	HINSTANCE			Handle (Service = 0);
	int				ArgC (void) { return argc; }
	char**				ArgV (void) { return argv; }
	void				SetClient (HWND h) { MDIClientHandle = h; }
	void				SetActiveDialog (HWND h) { LastDlgHandle = h; }
	HWND				GetClient (void) { return MDIClientHandle; }
	HWND				GetActiveDialog (void) { return LastDlgHandle; }

	void				Start (void);
	void				Idle (InvokeStatus status);
	unsigned short			DS (void);

	void				SetHelpWind (HWND hw, uint mode);
	void				SetAccelWind (HACCEL hacc, HWND receiver);
	
	CVLinked_List*      	ControlList (void);
	CVLinked_List*      	ContextList (void);
	CVLinked_List*      	MenuList (void);
	CVLinked_List*		PrinterList (void);
	CVLinked_List*		ResourceList (void);
	CVLinked_List*		ImagesList (void);
	CVTable*      		RegClassList (void);

static 	void			Quit (void);

		~App_Imp (void);		// * NEW *

protected:
	PRETRANSLATEPROC	m_pPreTranslateMsgProc;
	IDLEPROC			m_pIdleProc;

public:
	PRETRANSLATEPROC	AttachPreTranslateMsgProc (PRETRANSLATEPROC pFcn);
	PRETRANSLATEPROC	DetachPreTranslateMsgProc (void);
	IDLEPROC			AttachIdleProc (IDLEPROC pFcn);
	IDLEPROC			DetachIdleProc (void);

// #HK960229 Erweiterung der Messagebehandlung für MFC
private:
	POINT				m_ptCursorLast;		// letzte CursorPos
	UINT				m_nMsgLast;			// letzte Message

public:
	BOOL IsIdleMessage (MSG *pMsg);
	BOOL PumpMessage (ExecType et, MSG *pMsg);

	BOOL QuitOnLast (void) { return m_fQuitOnLast ? true : false; }
	void SetQuitOnLast (BOOL fFlag = true) { m_fQuitOnLast = fFlag; }

	BOOL PreTranslateMsgExt (MSG *pMsg);	// Wrapper für externe PTM's
	BOOL PreTranslateMessage (MSG *pMsg);	// #HK970116
};
#endif	// NOAPP


#ifndef	NOACCEL
class	Accel_Imp
{
friend	class	CV_RunTime;

	HACCEL			hAccel;

public:
	HACCEL	Handle (Service = 0);

			Accel_Imp (ResID);
			Accel_Imp (HACCEL);
};
#endif  // NOACCEL

#ifndef	NOBITMAP
class	Bitmap_Imp
{
friend	class	CV_RunTime;

	HBITMAP			hBitmap;
	BOOL			DeviceDependent;
	short			ColorPlanes;
	short 			BitsPerPixel;
	BOOL			m_fAutoDetach;

public:
	HBITMAP				Handle (Service = 0);
	HBITMAP				Detach (void);

			Bitmap_Imp (Dimension,BOOL monochrome ,pushort BitString );
			Bitmap_Imp (ResID);
			Bitmap_Imp (ResID uiRes, LPCOLORMAP pMap, int iMapSize, UINT uiFlags);
			Bitmap_Imp (HBITMAP, BOOL fAutoDetach = false);

	ulong				GetBits ( ulong nBits, pushort BitString );
	ulong				SetBits ( ulong nBits, pushort BitString );
	Dimension			GetSize (void);
	void				SetSize ( Dimension );

			~Bitmap_Imp (void);
};
#endif // NOBITMAP

#ifndef	NOBRUSH
/* Logical Brush */
class LogicalBrush {
protected:
	unsigned short lbStyle;
	COLORREF lbColor;
	short lbHatch;
    
public:
		LogicalBrush (pBrush);
		LogicalBrush (HBRUSH);

	COLORREF GetColor (void)	{ return lbColor; }
	short HatchType (void)		{ return lbHatch; }
	unsigned short	GetType (void)	{ return lbStyle; }
};

#ifndef NOEVENT
class LogBackBrush {
protected:
	unsigned short lbStyle;
	COLORREF lbColor;
	short lbHatch;

public:
	COLORREF GetColor (void) { return lbColor; }
	unsigned short GetType (void) { return lbStyle; }
	public:
			LogBackBrush( Wind_Imp* pw);
};
#endif // NOEVENT

class	Brush_Imp
{
friend	class	CV_RunTime;
	HBRUSH	  hBrush;
	BOOL	  isStock;
	BOOL	m_fAutoDetach;
		
public:
	HBRUSH	Handle (Service = 0);
	HBRUSH	Detach (void);

		Brush_Imp (StdBrush);			// stock item
		Brush_Imp (Color, StdHatchStyle);	// hatched
		Brush_Imp (pBitmap);								// pattern
		Brush_Imp (HBRUSH hBr, BOOL fAutoDetach = false);
		
		~Brush_Imp (void);
};
#endif // NOBRUSH


#ifndef	NOCURSOR
class	Cursor_Imp
{
	pWind_Imp		pWin;
	Dimension		size;
	Point			where;
	Bitmap_Imp		*bitmap;
	unsigned char	greyed : 1;
	unsigned char	created : 1;
	unsigned char	visible : 1;
	unsigned char	spare : 5;

public :

	HWND			Handle (Service = 0);

			Cursor_Imp ( pWind_Imp, Dimension, BOOL Greyed );
			Cursor_Imp ( pWind_Imp, pBitmap );

	void			Hide (void);
	void			Show (void);
	Point			GetPos (void);
	void			ChangePos (Point);
	uint			GetBlinkTime (void);
	void			ChangeBlinkTime (uint MSecs);

	void 			Update (BOOL creating);

			~Cursor_Imp(void);
};
#endif // NOCURSOR

#ifndef	NOFONT
class	LogFont {
public:
#if !defined(WIN32)
	short				lfHeight;
	short				lfWidth;
	short				lfEscapement;
	short				lfOrientation;
	short				lfWeight;
#else
	LONG				lfHeight;
	LONG				lfWidth;
	LONG				lfEscapement;
	LONG				lfOrientation;
	LONG				lfWeight;
#endif
	uchar				lfItalic;
	uchar				lfUnderline;
	uchar				lfStrikeOut;
	uchar				lfCharSet;
	uchar				lfOutPrecision;
	uchar				lfClipPrecision;
	uchar				lfQuality;
	uchar				lfPitchAndFamily;
	char				lfFaceName[ 32 ];

	LogFont (int = 0 , int = 0, const char * = (char*)0);
	LogFont (const LogFont &);
	LogFont (HFONT h);
			
	operator LOGFONT * (void) const { return (LOGFONT *)this; }

	void	Copy (LOGFONT *);
	void	CopyWOAttributes (LOGFONT *);
#ifdef BETA
	void 	Describe (void);
#endif // BETA
};

class	Font_Imp
{
friend	class		CV_RunTime;

	HFONT			hFont;
	Dimension		FntSize;
	unsigned char 		IsStdFont : 1;
	unsigned char		StdFontType : 7;
	unsigned char		FntChanged : 4;
	unsigned char		FntTmpLft : 4;
	LOGFONT*		lft;
	BOOL m_fAutoDetach;

public:
	HFONT			Handle (Service = 0); 
	HFONT			Detach (void);
	BOOL			isLight ();
	BOOL			isNormal ();			
	BOOL			isBold ();			

	BOOL			isItalic ();			
	BOOL			isUnderline ();		
	BOOL			isStrikethru ();		

	BOOL			isPitchFixed ();		
	BOOL			isPitchVariable ();	

	void			 SetLight ();
	void			 SetNormal ();
	void			 SetBold ();
	void			 SetItalic ();
	void			 SetUnderline ();
	void			 SetStrikethru ();
	void			 SetFixedPitch ();
	void			 SetVariablePitch ();

#if !defined(WIN32)
	short 			SetEscapement (short);
	short			SetOrientation (short);	// #HK920824
#else
	LONG 			SetEscapement (short);
	LONG			SetOrientation (short);	// #HK920824
#endif

	BOOL			GetLogFont (LOGFONT **ppLogFont);

			Font_Imp (StdFamily, Dimension, const char *);
#if _MSC_VER < 1100
			Font_Imp (StdFont);
#else
			Font_Imp (StdFonts);
#endif // _MSC_VER < 1100
			Font_Imp (HFONT, BOOL fAutoDetach = false);
			
			~Font_Imp (void);

	// Internal use only
void    	Init (LOGFONT **arr, HDC hdc = 0);
};														 
#endif //  NOFONT


#ifndef	NOICON
class	Icon_Imp
{

friend	class	CV_RunTime;
	HICON			hIcon;
	BOOL	m_fAutoDetach;

public:
	HICON	Handle (Service  = 0);
	HICON	Detach (void);

			Icon_Imp (StdIcon);	
			Icon_Imp (ResID);		
			Icon_Imp (HICON, BOOL fAutoDetach = false);
	
		~Icon_Imp (void);
};
#endif // NOICON


#ifndef  NOPEN
/* Logical Pen */
class LogicalPen {
private:
	unsigned short lopnStyle;
	Point lopnWidth;
	COLORREF lopnColor;

public:
	LogicalPen (pPen);
	LogicalPen (HPEN);

	COLORREF GetColor (void)		{ return lopnColor; }
	CoOrd GetWidth (void)			{ return lopnWidth.X(); }
	unsigned short GetType (void)	 	{ return lopnStyle; }
};

class	Pen_Imp
{
friend	class	CV_RunTime;
	HPEN		hPen;
	BOOL		m_fAutoDetach;

public:
	HPEN			Handle (Service = 0);
	HPEN			Detach (void);

			Pen_Imp (StdLineStyle, uint Width, Color);
			Pen_Imp (HPEN, BOOL fAutoDetach = false);
			
			~Pen_Imp (void);

	Color GetColor();
	CoOrd GetWidth();
	StdLineStyle GetStyle();
};
#endif // NOPEN

#ifndef	NOPOINTER
class	Pointer_Imp
{
friend class CV_RunTime;
friend class Pointer;

	HCURSOR		hPointer;
	BOOL		m_fAutoDetach;			// #HK970824

protected:
	BOOL LoadStockPointer (StdPointer Stock = Arrow);

public:
	HCURSOR		Handle(Service = 0);

		Pointer_Imp (StdPointer);	
		Pointer_Imp (ResID);
		Pointer_Imp (HCURSOR, BOOL fAutoDetach = false);
		Pointer_Imp (LPCSTR pcCursor);		// #HK970121

	HCURSOR Detach (void);
	Point	GetPos (void);
	void	ChangePos (Point);
	void	Hide (void);
	void	Show (void);
	void	Confine (Rectangle);	
		
		~Pointer_Imp (void);
};
#endif // NOPOINTER

#ifndef	NOMENU
class	Menu_Imp
{
friend	class	CV_RunTime;
	HMENU				hMenu;
	HMENU				hMenuParent;
	uint				MenuID;
	BOOL				isChanged;
	uint				autopos;
	BOOL				m_fAutoDetach;

protected:
	HMENU  RecursiveCopy (HMENU hCopyMenu);

public:
			Menu_Imp (ResID,pMenu);	// Load a resource menu
			Menu_Imp (pMenu);
			Menu_Imp (const Menu_Imp&, pMenu); // Copy constructor
			Menu_Imp (HMENU, pMenu, BOOL fAutoDetach = false);
			Menu_Imp (void);

	HMENU				Handle (Service = 0);
	HMENU				Detach (void);
	BOOL				AppendItem (uint ItemID, const char* NewItem );
	BOOL				AppendItem (uint ItemID, pBitmap NewItem );
	BOOL				AppendItem (pMenu SubMenu, const char* MenuHeader );
	BOOL				InsertItem (uint ItemID, const char *NewItem, uint Where ); 
  	BOOL				InsertItem (uint ItemID, pBitmap NewItem, uint Where );
	BOOL				InsertItem (pMenu SubMenu, const char* MenuHeader, uint Where );
	BOOL				DeleteItem (uint Which );
	BOOL				DeleteItem (pMenu );
	BOOL				AppendSeparator (void);
	BOOL				InsertSeparator (uint Where );
	BOOL				CheckItem (uint Which );
	BOOL				unCheckItem (uint Which );
	BOOL				EnableItem (uint Which );
	BOOL				DisableItem (uint Which );
	
	void				SetAutoUpdate (uint pos);
						~Menu_Imp (void);
};


class	SysMenu_Imp			: public	Menu_Imp
{
public:	
			SysMenu_Imp (pWind_Imp, pMenu);
			~SysMenu_Imp (void);
};
#endif // NOMENU

#ifndef NOCONTROL
class	Control_Imp
{
friend	class	CV_RunTime;

protected:
	uint				Type : 8;
	uint				SubType : 8;
	uint				fDialogChild : 1;
	uint 				fAttached : 1;
	uint				fInitialized : 1;

	CvID				ControlID;
	ulong				ControlStyle;
	Dimension			ControlSize;
	Point				ControlWhere;
	char *				ControlName;
	Brush *				ControlBackground;

	char *				WindowName;

	HWND				hControl;
	pWind_Imp			ControlParent;
	pControl			pRequestor;

private:	
	void				ProcessRegClassStr(const char *);

public:
		Control_Imp (pControl, pDWind_Imp, ResID,const char *RegClass  );
		Control_Imp (pControl, pWind_Imp, CvID UsrID, Point, Dimension, const char *RegClass, ulong InitStyle);
		Control_Imp (pControl, pWind_Imp, HWND hWnd);

	ulong               GetStyle()	{ return ControlStyle; }
	const char *        GetRegClassName() 	{ return ControlName; }

	BOOL				Valid();
	HWND				Handle (Service = 0);

	void       	        SetStyle ( ulong );

virtual void    	Show ( BOOL );	// displays/hides control 
virtual void		Create (void) ;
virtual	void		Enable (BOOL = TRUE);
virtual HDWP		RePosition (HDWP = 0, BOOL ReSize = FALSE, BOOL ReDraw = FALSE);
virtual void		Erase();
virtual HBRUSH		SetColors (HDC, uint);

	CvID		    	GetID (void);

	void		    	SetFocus (void);

	Point		    	ChangePosition (Point);
	Dimension	    	ChangeSize (Dimension );
	Point				GetPosition (void);
	Dimension		GetSize (void);
	pWindow			GetParent(void);
	Wind_Imp*           	GetParentImp (void)	{ return ControlParent; }

	int ValidateControl (void) ;

	void	SetControlWhere (Point p) { ControlWhere = p; }
	void	SetControlSize(Dimension d) { ControlSize = d; }
	BOOL	bManageBackground() 	{ return (ControlBackground != 0); }

	pBrush		ChangeBackground (pBrush);

#if defined(WIN32)
// rudimentäres subclassing für alle Controls
private:
	WNDPROC				poldproc;

public:
virtual LRESULT Default (Event e);	// für subclassing
virtual LRESULT OnDestroy (Event e);
#endif // WIN32

virtual		~Control_Imp (void);

#if defined(WIN32)
protected:
virtual	void DestroyControl (void);	// 'OnDestroy' geht aus dem Destruktor nicht mehr
#endif // WIN32
};

#if defined(WIN32)

class	CTreeViewCtrl_Imp : public Control_Imp {
friend	class	CV_RunTime;
public:
		CTreeViewCtrl_Imp (pControl, pWind_Imp, CvID, Point, Dimension, DWORD);
		CTreeViewCtrl_Imp (pControl, pDWind_Imp, ResID);
		~CTreeViewCtrl_Imp (void);

	LRESULT OnDestroy (Event e);
	void RemoveImageList(int nImageList);
};

class	CListViewCtrl_Imp : public Control_Imp {
friend	class	CV_RunTime;
public:
		CListViewCtrl_Imp (pControl, pWind_Imp, CvID, Point, Dimension, DWORD);
		CListViewCtrl_Imp (pControl, pDWind_Imp, ResID);
		~CListViewCtrl_Imp (void);

	LRESULT OnDestroy (Event e);
	void RemoveImageList(int nImageList);
};

class	CToolTipCtrl_Imp : public Control_Imp {
friend	class	CV_RunTime;
public:
		CToolTipCtrl_Imp (pControl, pWind_Imp);
		~CToolTipCtrl_Imp (void);

	void Create (void);
};

class	CToolBarCtrl_Imp : public Control_Imp {
friend	class	CV_RunTime;
public:
		CToolBarCtrl_Imp (pControl, pWind_Imp, CvID, Point, Dimension, DWORD);
		CToolBarCtrl_Imp (pControl, pDWind_Imp, ResID);
		~CToolBarCtrl_Imp (void);

	void Create (void);
};

class	CStatusBarCtrl_Imp : public Control_Imp {
friend	class	CV_RunTime;
public:
		CStatusBarCtrl_Imp (pControl, pWind_Imp, CvID, Point, Dimension, DWORD);
		CStatusBarCtrl_Imp (pControl, pDWind_Imp, ResID);
		~CStatusBarCtrl_Imp (void);
};

class	CSpinButtonCtrl_Imp : public Control_Imp {
friend	class	CV_RunTime;
protected:		// für Kompatibilität mit ScrollBars, da WM_HSCROLL/WM_VSCROLL
				// Messages verabeitet werden, die auf diese Variablen zugreifen
	uint SBType : 14;
	uint SBDisabled : 1;
	uint SBIgnoreEndScroll : 1;
	uint SBBlock;
	uint SBUnit;

public:
		CSpinButtonCtrl_Imp (pControl, pWind_Imp, CvID, Point, Dimension, DWORD);
		CSpinButtonCtrl_Imp (pControl, pDWind_Imp, ResID);
		~CSpinButtonCtrl_Imp (void);
};

class	CProgressCtrl_Imp : public Control_Imp {
friend	class	CV_RunTime;
public:
		CProgressCtrl_Imp (pControl, pWind_Imp, CvID, Point, Dimension, DWORD);
		CProgressCtrl_Imp (pControl, pDWind_Imp, ResID);
		~CProgressCtrl_Imp (void);
};

class CAnimateCtrl_Imp : public Control_Imp {
// Constructors
public:
		CAnimateCtrl_Imp (pControl, pDWind_Imp, ResID);
		CAnimateCtrl_Imp (pControl, pWind_Imp, CvID, Point, Dimension, DWORD);
		~CAnimateCtrl_Imp (void);
};

class CHotKeyCtrl_Imp : public Control_Imp {
// Constructors
public:
		CHotKeyCtrl_Imp (pControl, pDWind_Imp, ResID);
		CHotKeyCtrl_Imp (pControl, pWind_Imp, CvID, Point, Dimension, DWORD);
		~CHotKeyCtrl_Imp (void);
};

#endif // WIN32

class	FixedIcon_Imp		: public	Control_Imp
{
friend	class	CV_RunTime;

public:
		FixedIcon_Imp (pControl req, pDWind_Imp pDW, ResID id): Control_Imp(req, pDW, id,0) {}
	    	FixedIcon_Imp ( pControl req , pWind_Imp, CvID UsrId, Point, ResID id);

		~FixedIcon_Imp (void);
};


class	ScrollB_Imp		: public	Control_Imp
{
public:
friend	class	CV_RunTime;

protected:

	uint				SBType : 14;
	uint				SBDisabled : 1;
	uint				SBIgnoreEndScroll : 1;
	uint				SBBlock;
	uint				SBUnit;


public:
	    	ScrollB_Imp ( pControl, pDWind_Imp, ResID );
	    	ScrollB_Imp (  pControl, pWind_Imp, CvID , Point, Dimension);

	HBRUSH		SetColors (HDC, uint);

	void 				Show ( BOOL ) ;

	int		    		GetThumbPos ( );
	void		    	SetThumbPos (  int );
	Range		    	GetRange ( );
	void		    	SetRange ( Range );
	uint				GetBlock ();
	void				SetBlock ( uint b );
	uint				GetUnit  ();
	void				SetUnit  ( uint u );

	uint				GetPageSize (void);		// #HK960411
	int					SetPageSize (uint, BOOL);
	int					GetTrackPos (void);

	    	~ScrollB_Imp ();
};


class	VScrollB_Imp	: public	ScrollB_Imp
{
public:
		VScrollB_Imp ( pControl , pDWind_Imp , ResID );
	    	VScrollB_Imp (  pControl, pWind_Imp, CvID, Point, Dimension);
		~VScrollB_Imp();
};

class	HScrollB_Imp	: public	ScrollB_Imp
{
public:
		HScrollB_Imp ( pControl, pDWind_Imp, ResID);
	    	HScrollB_Imp (  pControl, pWind_Imp, CvID, Point, Dimension);
		~HScrollB_Imp();
};

class WndScrollB_Imp : public ScrollB_Imp {
friend	class	CV_RunTime;
public:
			    	WndScrollB_Imp( pControl, pWind_Imp);

	HDWP		RePosition (HDWP, BOOL, BOOL);
    	void		Enable ( BOOL = TRUE);
        void		Show ( BOOL ) ;

		~WndScrollB_Imp();

};


class  WndVScrollB_Imp  : public WndScrollB_Imp
{
public:
		WndVScrollB_Imp( pControl, pWind_Imp);
		~WndVScrollB_Imp();

};

class WndHScrollB_Imp  : public WndScrollB_Imp
{
public:
		WndHScrollB_Imp(  pControl, pWind_Imp);
		~WndHScrollB_Imp();
};

class	TextControl_Imp		: public	Control_Imp
{
friend	class	CV_RunTime;

	int Xchars;
	int Ychars;
	pFont txtCtrlFont;
	COLORREF txtColor;
	uchar ManageColor;

	void InitTextMetrics();

protected:
    void        Create (void) ;
	
public:
		TextControl_Imp ( pControl req, pDWind_Imp parent, ResID id);
		TextControl_Imp ( pControl, pWind_Imp parent, CvID UsrId, Point where, Dimension size, const char *);
		TextControl_Imp ( pControl, pWind_Imp parent, HWND hWnd);

	HBRUSH				SetColors (HDC, uint);
	pFont	  			ChangeFont (pFont font, BOOL rescale);  
	Color	  			ChangeTextColor (Color);  

	void		    	SetText (const char* buffer );
	void		    	GetText (pchar buffer, uint maxlen );
	uint		    	GetTextLen (void);

	BOOL			bManageColor (void) 	{ return ManageColor ? true : false; }

						~TextControl_Imp();
};


class GaugeBox_Imp : public TextControl_Imp {
friend	class	CV_RunTime;
public:
		GaugeBox_Imp (pControl req, pDWind_Imp parent, ResID id);
		GaugeBox_Imp (pControl req, pWind_Imp parent, CvID UsrID, Point where, Dimension size, const char *pIniText);

	void	SetRange (short);
	void	SetPosition (short);
	void	SetOrientation (short);
	void	SetDeltaPos (short);
	void	SetFColor (Color);
	void	SetBkColor (Color);
	void 	Set3DWidth (short);
	void 	SetBezelFace (short);
	
	short	GetRange (void);
	short	GetPosition (void);
	short	GetOrientation (void);
	Color	GetFColor (void);
	Color	GetBkColor (void);
	short	Get3DWidth (void);
	short	GetBezelFace (void);
};

class	Button_Imp			: public	TextControl_Imp
{
public:
      Button_Imp ( pControl, pDWind_Imp parent, ResID );
      Button_Imp ( pControl, pWind_Imp, CvID UsrId, Point, Dimension, const char *);

		HBRUSH		SetColors(HDC, uint);

      ~Button_Imp();
};

class	RadioButton_Imp		: public	Button_Imp
{
public:
   	RadioButton_Imp (  pControl, pWind_Imp, CvID UsrId, Point, Dimension , const char *);
	RadioButton_Imp ( pControl req, pDWind_Imp parent, ResID id ) :	Button_Imp(req, parent, id ) {}

	BOOL   	GetState ( );
	void  	SetState (  BOOL onoff );

		   ~RadioButton_Imp();
};

class	PushButton_Imp	: public	Button_Imp
{
public:
	    	PushButton_Imp ( pControl ,pWind_Imp, CvID UsrId, Point, Dimension, const char * );
			PushButton_Imp ( pControl req, pDWind_Imp parent, ResID id ) :	Button_Imp(req, parent, id ) {}
    		~PushButton_Imp();

	HBRUSH		SetColors(HDC, uint);
	HBITMAP		SetImage (HBITMAP hNewBmp);
	HBITMAP		GetImage (void);
};

class	CheckBox_Imp	: public	Button_Imp
{
public:
	    	CheckBox_Imp (  pControl, pWind_Imp, CvID UsrId, Point, Dimension, const char* InitText );
		CheckBox_Imp ( pControl req, pDWind_Imp parent, ResID id) :	Button_Imp( req, parent, id ) {}


	BOOL		    	isChecked ();
	void		    	SetChecked ( BOOL Checked );
		~CheckBox_Imp();
};


#ifndef NOLISTBOX
class	ListBox_Imp			: public	TextControl_Imp
{
protected:
	int 		MessageSet;
    BOOL      SortDescending;

    void        Create (void) ;

protected:
      int  GetInsertPos( const char *);

public:
    	ListBox_Imp ( pControl, pDWind_Imp parent, ResID );
	ListBox_Imp (  pControl, pWind_Imp, CvID UsrId, Point, Dimension );

	HBRUSH		SetColors (HDC, uint);

 // The Following are in _flb_im.cxx
        int NoCols;
        int *TabStop;
        int lastchar;
        void SetTabStops (void);
        BOOL TabsSet;

        int  AddRow ( int , char*) ; // returns inserted strings position in listbox
        BOOL GetRow (int , char*);
        BOOL SetColWidth (uint col, uint width);

virtual int		GetCurrentIndex (void);
	int		AddString (  const char* Str, int position = -1 );	// adds string to list
	BOOL 		DelString (  int StrIndex = -1 );
	int		FindString (const char *, BOOL);
   	BOOL    	GetString (pchar buffer, int index, int length );
	int  		GetLineLen (int);

	int		GetCount (void);
	void	Clear (void);

#if _MSC_VER >= 1200	// #HK990130
	DWORD GetItemData (int iIndex);
	int SetItemData (int iIndex, DWORD dwData);
// #HK990130
#endif // _MSC_VER >= 1200

virtual void    SetTop (int );
virtual void    SetStdStyle (int) ;

	HDWP    RePosition (HDWP, BOOL, BOOL);
        	~ListBox_Imp(void);
};

class SingleSelListBox_Imp : public ListBox_Imp
{
public:
			SingleSelListBox_Imp ( pControl, pDWind_Imp parent, ResID );
			SingleSelListBox_Imp (  pControl, pWind_Imp, CvID UsrID, Point, Dimension );

	int		GetCurrentIndex (void);
	BOOL	ChangeCurrentIndex (int index);

	~SingleSelListBox_Imp (void);
};


class MultiSelListBox_Imp : public ListBox_Imp
{
private:
      int       SelectNo;

public:
				MultiSelListBox_Imp (pControl, pDWind_Imp parent, ResID );
				MultiSelListBox_Imp (pControl, pWind_Imp, CvID UsrID, Point, Dimension );

    int         GetNoSelected ();
    BOOL        ClearSelected ();
    int         GetFirstSelected ();
    int         GetNextSelected ();
    BOOL        ChangeSelected ( int index, BOOL = True );
    BOOL        ChangeSelected (Range, BOOL = True );
	short 	GetCaretIndex (void);
	BOOL 	SetCaretIndex (short iIndex, BOOL fScroll);
	BOOL 	GetSelection (short iIndex);
	int		FindString (const char *str, BOOL fWhole = false, int iStart = -1);

				~MultiSelListBox_Imp (void);
};

class	ComboBox_Imp	: public SingleSelListBox_Imp
{

protected:
    void        Create (void);

public:
   	ComboBox_Imp (pControl, pWind_Imp, CvID UsrId, Point, Dimension, int );
   	ComboBox_Imp (pControl req, pDWind_Imp parent, ResID id );

   	void	   SetTop (int);

   	HDWP RePosition (HDWP, BOOL, BOOL);
   	void Erase();
	void SetStdStyle(int);

// ADDED: #HK961031
	Selection	GetEditSelection (BOOL toClipBoard = false);
	Selection	GetEditSelection (char *, int TextLen = -1);
	void ChangeEditSelection (Selection);
	void DeleteEditSelected (BOOL toClipBoard = false);

	~ComboBox_Imp (void);
};

// BEGIN: #HK030317
class ComboBoxEx_Imp 
:	public ComboBox_Imp 
{
public:
   	ComboBoxEx_Imp (pControl, pWind_Imp, CvID UsrId, Point, Dimension, int);
   	ComboBoxEx_Imp (pControl req, pDWind_Imp parent, ResID id);
	~ComboBoxEx_Imp ();

	int DeleteItem(int iIndex);
	BOOL GetItem(COMBOBOXEXITEM* pCBItem);
	int InsertItem(const COMBOBOXEXITEM* pCBItem);
	BOOL SetItem(const COMBOBOXEXITEM* pCBItem);
};
// END: #HK030317

class FileListBox_Imp   :   public SingleSelListBox_Imp
{
friend	class	CV_RunTime;

	char				DefExt[5];
	char				FileSpec[120];
	uint				attrib;
	CvID				idpath;
public:
				    	FileListBox_Imp (pControl, pDWind_Imp, ResID ListBoxId, ResID PathId  );
                       
	BOOL		    	List ( const char* Path, uint Attributes );
	BOOL		    	GetCurrentFile ( pchar FileName, int len = 120 );
	FlbStatus	    	Validate ( pchar FileName, int len = 120 );

					~FileListBox_Imp(void);
};

class TLBox_Imp : public SingleSelListBox_Imp {
public :
        TLBox_Imp (pControl req, pDWind_Imp, ResID, int);
        TLBox_Imp (pControl req, pWind_Imp, CvID, Point, Dimension, int);
};


class TLMultiBox_Imp : public MultiSelListBox_Imp {

public :
        TLMultiBox_Imp (pControl req, pDWind_Imp, ResID, int);
        TLMultiBox_Imp (pControl req, pWind_Imp, CvID, Point, Dimension, int);

};
#endif // NOLISTBOX

class	Edit_Imp		: public	TextControl_Imp
{
public:
	    	Edit_Imp ( pControl, pDWind_Imp parent, ResID );
	    	Edit_Imp ( pControl, pWind_Imp, CvID UsrId, Point, Dimension );
	    	Edit_Imp (pControl, pWind_Imp, HWND);

	HBRUSH		SetColors(HDC, uint);

	BOOL		    	isModified (void);
	void			SetModified( BOOL ModSet = TRUE );
	Selection	    	GetSelection (BOOL toClipBoard = FALSE );
	Selection	    	GetSelection (pchar , int TxtLen = -1);

	void		    	ChangeSelection (Selection);
	void		    	SetTextLimit (uint nChars);
	BOOL		    	ReplaceSelected (const char* Text );
	void		    	DeleteSelected (BOOL toClipBoard = FALSE );
	BOOL		    	Undo (void);
	BOOL		    	CanUndo (void);
	void			SetTabStop (uint);
	uint			GetTabStop (void);
	void			SetStdStyle (int);

		~Edit_Imp (void);
};



class	MultiLineEdit_Imp	: public	Edit_Imp
{
public:
	    	MultiLineEdit_Imp (  pControl , pWind_Imp, CvID UsrId, Point, Dimension);
	    	MultiLineEdit_Imp ( pControl req, pDWind_Imp parent, ResID id );

	uint		    	GetLineLength ( int Index = -1 ); // this inserted here because it must be accessed by the public class
	uint		    	GetLine (  int Index, pchar Buffer, uint nChars );
	uint		    	GetNumLines ( );
	void		    	ScrollVertical (  int nLines );
	void		    	ScrollHoriz (  int nChars );
	void		    	PageUp ( );
	void		    	PageDown ( );
	void		    	LineUp ();
	void		    	LineDown ();
	void			SetMultiStyle( int );
		~MultiLineEdit_Imp();
};


class	SingleLineEdit_Imp	: public	Edit_Imp
{
public:
	    	SingleLineEdit_Imp (  pControl, pWind_Imp, CvID UsrId, Point, Dimension );
	    	SingleLineEdit_Imp ( pControl req, pDWind_Imp parent, ResID id );
	    	SingleLineEdit_Imp ( pControl req, pWind_Imp parent, HWND hWnd );
		~SingleLineEdit_Imp();
};

class	FixedText_Imp		: public	TextControl_Imp
{
friend	class	CV_RunTime;

public:
	    	FixedText_Imp (  pControl ,pWind_Imp, CvID UsrId, Point, Dimension, const char* Text );
	    	FixedText_Imp ( pControl req, pDWind_Imp parent, ResID id );

    void    SetStdStyle(int);

		~FixedText_Imp();
};

class GroupBox_Imp : public TextControl_Imp
{
public:
		    GroupBox_Imp (pControl, pWind_Imp, CvID, Point, Dimension, const char *text);
		    GroupBox_Imp (pControl, pDWind_Imp, ResID);
protected:
	 	HDWP		RePosition (HDWP, BOOL, BOOL);
	 	void		Erase (void);
};
#endif // NOCONTROL

#ifndef	NOEVENT
class	EC_Imp			// * CURRENT *
{
friend	class	CV_RunTime;

protected:
	HWND				hEContext;
	long*				pRetval;

	EventContext*	pRequestor;

public:
virtual	long		Dispatch (Event) = 0;
virtual	void		Default (Event) = 0;

	EventContext *	GetRequestor (void) { return pRequestor; }
	HWND		 Handle ( Service = 0 ) { return hEContext; }

			EC_Imp (EventContext *);
virtual			~EC_Imp (void);
};

enum CloseStyle { ChQuery, ChClose, ChCloseAndTidy };

class	Wind_Imp			: public	EC_Imp
{

friend	class	CV_RunTime;
friend  class 	AWind_Imp;
friend  class 	TAWind_Imp;
friend  class 	CAWind_Imp;
friend  class 	DWind_Imp;
friend  class 	MDWind_Imp;
friend	class	PSheetWind_Imp;
friend  class 	PPageWind_Imp;

private:
	// Canvas related stuff
	HDC				hDC;
	HDC				hTargetDC;	// #HK940119
	HFONT				hFontInUse;

protected:
	pFont				WndFont;	//	font,
	pBrush				WndBrush;	//	brush,
	pPen				WndPen;		//	pen,
	pBrush				WndBackground;	// background brush.

	char *				WndCapt;	// Window caption
	pMenu	 			WndMenu;	// The Window's menu,

private:
	pBitmap				WndBitmap;	//	bitmap,

protected:
	pAccel				WndAccel;	//  accelerator,
	pPointer			WndPointer;	//	pointer,

private:
	pIcon				WndIcon;	//  icon.
	Cursor_Imp*			WndCursor;
	HelpDisp_Imp*			CurrentHelp;
	uint				LastKeyCode;

protected:
virtual HDC				GetDC (void);
virtual HDC				GetTargetDC (void);		// #HK940119
virtual HDC				SetDC (HANDLE H);		// #HK980424
virtual HDC				SetTargetDC (HANDLE h);	// #HK980424

	void				EvtEnd (void);
	void				PaintBackground (HDC, Rectangle *prc = NULL);	// #HK940912

	uint				WndFlags;

// Window flags for DC management

	struct	{
		uchar 	  		FontInUse : 1;
		uchar 	  		PenInUse : 1;
		uchar 	  		BrushInUse : 1;
		uchar 	  		Initialised : 1;
		uchar 	  		FontNeeded : 1;
		uchar 	  		PenNeeded : 1;
		uchar 	  		BrushNeeded : 1;
		uchar 	   		Erasing : 1;
	} DCFlags;

	void	*	PaintInfo;

// Windows Management flags
	struct	{
		uint			Opened : 1;
		uint			Initialised : 1;
		uint			Anchoring : 1;
		uint			NoRedraw : 1;
		uint			Destructor : 1;
		uint			HelpOn : 1;
		uint			HelpCursorOn : 1;
		uint			HelpMenu : 1;
		uint			isMDIWindow : 1;
		uint			isModal : 1;
		uint			isPropPage : 1;
	} WindMgt;

// Flags for Window color management of controls
	struct {
		uchar 	 		TextClr	: 1;
		uchar 	 		TrapCtlColor : 1;
	} ColorMgt;

	uchar 				fAttached : 1;

	Dimension			WndSize;
	Point				WndPosition;
	ulong				WndStyle;
	pWind_Imp			WndParent;

// HouseKeeping functions
	void				InitSize (void);
	BOOL 				HelpFilter (Event e);
	void				HandlePointer (Event e, BOOL isHelp = FALSE, BOOL isClient = FALSE);

// Event Handler functions
public:
enum MhType { MhInit, MhSelect, MhCommand };

virtual	void				MenuHandler ( MhType, Event );
virtual	void				ButtonClick ( ControlEvt );
virtual void				HelpRequest( HelpRequestEvt );


	long				Dispatch ( Event );
	void				Default ( Event );
public:
		Wind_Imp (Window *p); 
		Wind_Imp (Window *p, HWND hWnd);		// #HK940119
		~Wind_Imp (void);						// #HK930316
		
virtual	void				Show ( ShowState = Normal );
virtual void            		Hide (void);
	void				Enable(BOOL);

virtual	void				SetStyle ( ulong , BOOL = TRUE);	// set window style.
	void				SetCaption ( const char*, BOOL fSetText = true);		// Sets up caption bar
	void				Update( ); 
	void				RePaint( );			// Repaint the entire window
	void				RePaintRect( Rectangle region );
	Point				ChangePosition ( Point );
virtual	Dimension			ChangeSize ( Dimension );
	void				SetFocus();
	void				CanvasErase (Rectangle *prc = NULL);

	void				ToTop();
virtual Rectangle			CanvasRect ();		// Returns canvas area rectangle
virtual Rectangle			WindowRect ();		// Returns entire window
	Dimension			TextSize ( const char* );
	BOOL				isIconic ();
	BOOL				isVisible ();
	BOOL				isZoomed ();
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
	void				MouseTrap ( CVOnOff = CVOn );
#else
	void				MouseTrap ( OnOff = On );
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)

//	Painting and drawing functions
	void				TextPrint ( const char*, Point );
	void				TextPrintf ( Point, const char*,  const char * );
	void				TextPrintf ( const char*,  const char * );
	Point				MoveTo ( Point );	// Move pen origin
	void				LineTo ( Point );	// Draw line from current pen
	void				PaintRectangle ( Rectangle, PaintMode = Fill );	// Paint rectangle from current brush
	void				Draw ( pDrawObject );
	void				DrawEx (pDrawObject, DWORD);	// #HK940121
	void			    	Scroll( Dimension, Rectangle, BOOL = TRUE);

//	Selection functions
	pPointer			ChangePointer ( pPointer );
	pBrush				ChangeBackground ( pBrush );
	pBrush				ChangeBrush ( pBrush );
	pFont				ChangeFont ( pFont );
	pMenu				ChangeMenu ( pMenu );
virtual void				AssociateMenu(BOOL ViaPost= FALSE);
virtual void				AssociateAccel(BOOL Set);
	pPen				ChangePen ( pPen );
	pAccel				ChangeAccel ( pAccel );

	HDC 				SetDrawTarget (HDC hTargetDC);
	HDC 				GetDrawTarget (void);
	HWND				Detach (void);
	HWND				Attach (HWND hWnd);		// FensterHandle zuweisen
			
// Help support functions
	void				EnableHelp(BOOL enabled, HelpDisp_Imp*);
	void				EnableHelpCursor (BOOL enabled);
	BOOL				ProcessHelpCursor (HWND hw,  uint area);
	BOOL				FilterHelpCursor(uint area);
   
// Internal support functions
	void				Initialise();
	BOOL				InDestructor() { return WindMgt.Destructor; }
virtual	BOOL				CloseHandler(CloseStyle, Event);

// Query functions
	Point		GetPosition ();
	Dimension	GetSize ( );
	pchar		GetCaption ( pchar, int );
	pAccel		GetAccel ( );
	pBrush		GetBackground ( );
	pBrush		GetBrush (  );
	pFont		GetFont (  );
	pMenu		GetMenu (  );
	pWindow		GetParent() { return (Window*)(WndParent ? (WndParent -> GetRequestor()) : 0); } 
	uint		GetVirtKey() { return LastKeyCode; }
	pPen		GetPen (  );
	pPointer	GetPointer (  );

	Cursor_Imp* 	GetWinCursor() { return WndCursor; }
	void 		SetWinCursor(Cursor_Imp* ci) { WndCursor = ci; }

	void		ManageControlBackground(BOOL);
	void		ManageControlText(BOOL);
	void*		GetPaintInfo() { return PaintInfo; }
	BOOL		InCursorHelpMode() { return WindMgt.HelpOn && WindMgt.HelpCursorOn; }
	BOOL		ToggleClipChildren(BOOL);

virtual pScrollBar 	GetWndScrollBar(uint);

// #HK940711 ------------------------------------------------------------------
protected:		
	pScrollBar			AppWndVert;
	pScrollBar			AppWndHorz;

public:
	pWndVertScroll		EnableVScroll (BOOL = TRUE);
	pWndHorzScroll		EnableHScroll (BOOL = TRUE);
// #HK940711 ------------------------------------------------------------------

// #HK960320 -----------------------------------------------------------------
virtual BOOL			DrawCallUp (DrawObject *, BOOL);

// #HK970116 -----------------------------------------------------------------
virtual	BOOL			PreTranslateMsg (MSG *pMsg);

// #HK970824 -----------------------------------------------------------------
virtual BOOL			DestroyWindow (void);
};


class	AWind_Imp		: public	Wind_Imp
{
friend	class	CV_RunTime;

private:
	pIcon				AppWndIcon;			// The associated icon

public:
	void				Default ( Event );
	long				Dispatch ( Event );
	BOOL				CloseHandler(CloseStyle, Event);

				AWind_Imp (AppWindow * req, pAWind_Imp );

	void				EnableBorder ( int = 0) ;
	void				EnableMinBox (BOOL = TRUE);
	void				EnableMaxBox (BOOL = TRUE); 
	pSysMenu			EnableSysMenu (BOOL = TRUE);
	void				SetIcon ( pIcon );
	void				SetPointer ( pPointer );

			 	~AWind_Imp();

//	pScrollBar GetWndScrollBar(uint );	// #HK940711
};

#ifndef	NOTOPWIND
class	TAWind_Imp	: public	AWind_Imp
{
public:
		TAWind_Imp (AppWindow * req, pAWind_Imp copy_from = 0 );
// #HK951225 ------------------------------------------------------------------
		TAWind_Imp (AppWindow * req, long dwExStyle = 0, char *pClassName = NULL);
// #HK951225 ------------------------------------------------------------------

	void	Show (ShowState s );
};
#endif // NOTOPWND

#ifndef	NOCHILD
class	CAWind_Imp	: public	AWind_Imp
{
protected:
	void  	HelpRequest( HelpRequestEvt );

public:
		CAWind_Imp ( AppWindow * req, pWind_Imp parent, pAWind_Imp copy_from = 0 );
// #HK930803 ------------------------------------------------------------------
// zusätzlicher Konstruktor, um auf eigene FensterKlasse zugreifen zu können
		CAWind_Imp (AppWindow *req, pWind_Imp parent, pchar pClassName, long dwExStyle = 0, UINT uiID = 0);
// ----------------------------------------------------------------------------

	void				Show ( ShowState );
};
#endif // NOCHILD

#ifndef	NODIALOG
class	DWind_Imp	: public	Wind_Imp
{
friend	class	CV_RunTime;

protected:
	CvID			dialogID;
	int				result;
	HWND			hModeless;
	BOOL *			pActiveContext;
	int 			Xbase, Ybase, Xchars, Ychars;
	WNDPROC			m_poldProc;	// evtl. Subclassing

	struct {
		bool		IsShown;
		bool		fParentsDisabled;
	} DlgFlags;
	HWND			m_hWndLast;

public:
//			HANDLE		Handle( Service = 0);

protected:

	long			Dispatch ( Event );
	void			Default ( Event );
	BOOL			CloseHandler(CloseStyle, Event);

public:
				DWind_Imp (DialogWindow * );
				DWind_Imp ( DialogWindow *, pWind_Imp , ResID, BOOL );

	int			Result (void);
		void			Show (ShowState );
#if defined(WIN32)
virtual	void			EndDlg (int nResult = 0);
#else
	void			EndDlg (int nResult = 0);
#endif
	pFont			ChangeFont (pFont, BOOL);

	WNDPROC *	GetSuperClassProc(void);

					~DWind_Imp();
};
#endif // NODIALOG
	
#ifndef NOPRINT
#if !defined(WIN32)
extern "C" int PASCAL __loadds PrinterAbortProc(HDC hPr, int Code);
#else
int CALLBACK PrinterAbortProc (HDC hPr, int Code);
#endif

class PrintingDevice_Imp {
private:
	HGLOBAL	m_hDevMode;
	HGLOBAL m_hDevNames;
	string 	m_strDevice;
	string 	m_strDriver;
	string 	m_strPort;
	DEVMODE *m_pDevMode;

	BOOL	m_fValid;

protected:
	BOOL ParseDevNames (void);
	void Tidy (void);

public:
	static PRINTDLG s_pd;

	BOOL InitFromDefaultPrinter (DVTARGETDEVICE **ppdvt = NULL);
	BOOL InitFromData (DVTARGETDEVICE *pdvt);

public:
		PrintingDevice_Imp (void);
		~PrintingDevice_Imp (void);
	
	BOOL Setup (BOOL fInit = false, DVTARGETDEVICE **ppdvt = NULL);
	BOOL isValid (void) { return m_fValid; }

	const char *Device (void);
	const char *Driver (void);
	const char *Port (void);
	DEVMODE *InitString (void);
};

class PWind_Imp : public Wind_Imp
{
#if !defined(WIN32)
friend int PASCAL __loadds PrinterAbortProc(HDC hPr, int Code);
#else
friend int CALLBACK PrinterAbortProc (HDC hPr, int Code);
#endif

	char * PrStdFonts;

protected:
	BOOL PrValid;
	BOOL PrAbort;
	BOOL PrPage;

public:
		PWind_Imp(Window *,const char*,PrintingDevice_Imp *);
		~PWind_Imp();

	Rectangle	CanvasRect ();		// Returns canvas area rectangle
	Rectangle	WindowRect ();		// Returns entire window
	HDC		GetDC();
	Dimension	ChangeSize ( Dimension size );

	void 	Show(ShowState);
	void	NewPage();
	void	EndPage();
	void	Abort();
	BOOL 	Valid() { return PrValid; }
	BOOL 	Aborted() { return PrAbort; }
};
#endif // NOPRINT

// #HK921029 ------------------------------------------------------------------
class BPWind_Imp : public PWind_Imp
{
public:
		BPWind_Imp (Window *, const char *, PrintingDevice_Imp *);
		~BPWind_Imp (void);

	void	NextBand (Rectangle &, BOOL fFirst = false);
};
// ----------------------------------------------------------------------------

// #HK940119 ------------------------------------------------------------------
#if !defined(NODCWINDOW)

class CDCWind_Imp : public Wind_Imp {
public:
		CDCWind_Imp (Window *pDCWindow, Rectangle &Rc);
		~CDCWind_Imp (void);

	void 	Show (ShowState);

	HDC 	SetDrawDC (HDC hDC);
	HDC	GetDC (void);		// überladene Funktion
	HDC 	DetachDC (void);

	Rectangle CanvasRect (void);
	Rectangle WindowRect (void);
};

#endif // NODCWINDOW

#if !defined(NOMETAFILE)

class CMWind_Imp : public CDCWind_Imp {
public:
		CMWind_Imp (Window *pMetaWind);
		~CMWind_Imp (void);
};

// ----------------------------------------------------------------------------

#endif	// NOMETAFILE


#ifndef NOSHELL
class ShellWind_Imp : public AWind_Imp 
{
friend class CV_RunTime;

	HWND 	hwndClient;
	HMENU	tmpMenu;
	HWND	hDefChild;

// Flags for Shell management of menus
	uchar 	Sf_UsingChildMenu	: 1;
	uchar 	Sf_UsingOwnMenu		: 1;
	uchar 	Sf_UsingDefMenu		: 1;
	uchar 	Sf_HasHandledMenu	: 1;
	uchar 	Sf_padding 		: 4;

	CVLinked_List  List_of_ChildDocs;

public:
	HWND	ClientWindow() { return hwndClient; }

			ShellWind_Imp(AppWindow *);

	void	Show (ShowState s);
	void    Hide ();

	void	Arrange ( int );
	void	AssociateMenu(BOOL = FALSE);
	void	AssociateAccel(BOOL Set);

	long	Dispatch(Event);
	void	Default(Event);

	void	UseChildMenu(Menu*, BOOL = FALSE);

	void	SetMenuHandler(BOOL tf)	{ Sf_HasHandledMenu = tf; } 
	BOOL  CloseHandler(CloseStyle cs, Event e);

    	CVLinked_List*      ChildDocList()	{ return &List_of_ChildDocs; }

	HWND	DefaultChild()	{ return hDefChild; }

			~ShellWind_Imp();
};

class DocWind_Imp : public AWind_Imp
{
	HWND	hwndClient;

public:
		DocWind_Imp( AppWindow *req, Wind_Imp *parent,pAWind_Imp copy_from = 0);

	void	AssociateMenu(BOOL = FALSE);
	void	AssociateAccel(BOOL Set);

	long	Dispatch(Event);
	void	Default(Event);
	void	MenuHandler ( MhType, Event );
		
	void	Show (ShowState s);
	void    Hide ();

	BOOL  	CloseHandler(CloseStyle cs, Event e);
	void  	HelpRequest( HelpRequestEvt );

		~DocWind_Imp();
};
#endif // NOSHELL

#ifndef NOCONTROL
class CWind_Imp : public Wind_Imp
{
private:
	WNDPROC				poldproc;
	char				paintflag;
	BOOL				m_fInitialized;		// #HK960502

protected:
	pControl			pctrl;

public:
	void				Default ( Event );
	void				Expose ( ExposeEvt );
	long				Dispatch ( Event);

	BOOL				FInit (void);		// #HK960502

public:
				CWind_Imp (Window * req, pControl );

	pControl			GetControl ();
	void				Hide ();
	void				Enable ();
	void 				Disable ();
		
	CvID				GetID();
	void			 	SetFocus();
	Point				ChangePosition ( Point p);
	Dimension			ChangeSize ( Dimension d);

	void				Show(ShowState s);

				~CWind_Imp ();
};


#ifndef NOTEXTCONTROL
#ifndef NOEDIT
class EWind_Imp : public CWind_Imp
{

public:
		EWind_Imp ( pWindow req, pDialogWindow parent, ResID RscID );
		EWind_Imp ( pWindow req,pWindow, CvID UsrId, Point, Dimension );

	void 			SetText( const char* Buffer);
	void			GetText( pchar Buffer, uint maxlen);
	uint			GetTextLen();
	BOOL			isModified ();
	Selection		GetSelection ();
	void			ChangeSelection ( Selection s );
	void			SetTextLimit ( uint nChars );
	void			ReplaceSelected ( const char* Text );
	void			DeleteSelected ();

	uint			GetLine ( uint Index, pchar Buffer, uint nChars );
	uint			GetNumLines ();
	void			ScrollVertical ( uint nLines );
	void			ScrollHoriz ( uint nChars );
	void			PageUp ();
	void			PageDown ();
	void			LineUp ();
	void			LineDown ();
	BOOL			Undo ();
		~EWind_Imp();
};
#endif	// NOEDIT
#endif	// NOTEXTCONTROL
#endif	// NOCONTROL

#endif 	// NOEVENT

#ifndef	NOMESSBOX
class	MessBox_Imp
{
friend	class	CV_RunTime;

	HWND				hMsgBox;

	pWind_Imp			Parent;
	StdMessBox			Type;
	char*				Text;
	char*				Caption;

	BOOL				Beep;

public:
			MessBox_Imp ( const char* Caption, const char* Text, pWind_Imp parent );

	HWND			Handle (Service = 0) { return hMsgBox ; }
	StdMessBox			GetType () { return Type ; }
	void				SetType ( StdMessBox );
	StdMessBoxReply		Show ();	// Returns the name of the button selected

	void             	SetBeep(BOOL);

		 	~MessBox_Imp ();
};

#endif // NOMESSBOX

#if defined(WIN32)
#if !defined(NOPROPERTYSHEET)

extern "C"
LRESULT WINAPI _DISPATCH_ENTRY PropertyPageDispatcher (HWND, UINT, WPARAM, LPARAM);

class PPageWind_Imp : public DWind_Imp 
{
friend	class CV_RunTime;
private:
	PROPSHEETPAGE m_psp;	// Struktur dieser Page
	HPROPSHEETPAGE m_hPage;
	int m_nPage;		// SeitenNummer

// #HK030116
	char const *m_pcHeaderTitle;
	char const *m_pcHeaderSubTitle;

protected:
	LRESULT	Dispatch (Event);
	void Default (Event);

public:
		PPageWind_Imp (CPropertyPage *pPage, ResID RscID, 
			       LPCSTR pCaption = NULL);
		~PPageWind_Imp (void);

	void CancelToClose (void);
	void SetModified (BOOL bChanged = true);
	LRESULT QuerySiblings (WPARAM wParam, LPARAM lParam);

	HPROPSHEETPAGE CreatePage (class PSheetWind_Imp *pSheet);
	int GetPage (void) { return m_nPage; }
	void Setpage (int nPage) { m_nPage = nPage; }

	BOOL FInit (HWND hWnd);

	void SetIcon (ResID resID);
	void SetIcon (Icon_Imp *pIcon);

// #HK030116: Wizard97 only: set HeaderTitle and HeaderSubTitle
	void SetHeaderTitle(char const *pcHeaderTitle);
	void SetHeaderSubTitle(char const *pcHeaderSubTitle);

	class PSheetWind_Imp *GetPSheetImp (void);

	void SetSheetWizardButtons (DWORD dwFlags);
	void PressSheetButton (DWORD dwFlags);
};


class PSheetWind_Imp : public DWind_Imp {
friend	class CV_RunTime;
friend	BOOL ContinueModal (DWORD dwDataCM);

private:
	PROPSHEETHEADER m_psh;

	PPageWind_Imp **m_pPages;
	int m_iSelPage;
	ShowState m_st;		// geforderter ShowState

public:
	void EndDlg (int nEndID = 0);
	void SetStyle (ulong style, BOOL setflag = true);

public:
		PSheetWind_Imp (CPropertySheet *pSheet, LPCSTR pszCaption, 
				Wind_Imp *parent, DWORD, int iSelPage);
		~PSheetWind_Imp (void);

	int GetPageCount (void);
	PPageWind_Imp* GetPage (UINT nPage) const;
	void Show (ShowState);
	UINT AddPage (PPageWind_Imp *pPage);
	UINT AddPage (HPROPSHEETPAGE hPage);
	BOOL RemovePage (PPageWind_Imp *pPage);
	BOOL RemovePage (HPROPSHEETPAGE hPage);
	BOOL RemovePage (UINT nPage);
	void EndDialog (int nEndID = 0);
	BOOL SetCurSel (PPageWind_Imp *pPage);
	BOOL SetCurSel (HPROPSHEETPAGE hPage);
	BOOL SetCurSel (UINT nPage);
	void PressButton (DWORD);
	void SetWizButtons (DWORD);

	BOOL FInit (HWND hWnd);

	void SetIcon (ResID resID);
	void SetIcon (Icon_Imp *pIcon);

// #HK030116: Wizard97: Headerbitmap und Watermark setzen
	void SetHeaderBitmap (ResID resID);
	void SetHeaderBitmap (Bitmap_Imp *pBitmap);
	void SetWatermark (ResID resID);
	void SetWatermark (Bitmap_Imp *pBitmap);
};

#endif // NOPROPERTYSHEET
#endif // WIN32

#endif // _CV_IMP_HXX
