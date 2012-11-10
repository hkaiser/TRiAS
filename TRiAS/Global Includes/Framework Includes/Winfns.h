
extern "C" {

// #define WINAPI _pascal

// extern int _cdecl atoi(const char *);

#ifdef NEWWAVE
Bool   WINAPI NW_MessageFilter ( HANDLE, uint, uint, ulong, long  * );
#endif // NEWWAVE

#ifdef M_I86LM
// void  WINAPI DebugBreak(void);
// long  WINAPI GetWinFlags(void);

#define WF_PMODE	0x0001
#define WF_CPU286	0x0002
#define WF_CPU386	0x0004
#define WF_WIN286	0x0010
#define WF_WIN386	0x0020
#define WF_LARGEFRAME	0x0100
#define WF_SMALLFRAME	0x0200

#endif // M_I86LM

#if !defined(WIN32)
extern pchar  _cdecl StaticPtr(void near *);
#else
#define StaticPtr(x)	(x)
#endif

#if defined(_DYNALINK)
extern void  WINAPI StaticDataInit (HINSTANCE);
#if !defined(WIN32)
extern void  WINAPI _loadds StaticDataCleanup (void);
#else
extern void  WINAPI StaticDataCleanup (void);
#endif
HINSTANCE WINAPI CV_LibHandle(void);
#endif // _DYNALINK

extern _TF_ENTRY32 LRESULT	 WINAPI	_DISPATCH_ENTRY DialogDispatcher (HWND, UINT, WPARAM, LPARAM);
extern _TF_ENTRY32 LRESULT	 WINAPI	_DISPATCH_ENTRY EventDispatcher (HWND, UINT, WPARAM, LPARAM);
#if defined(WIN32)
extern _TF_ENTRY32 LRESULT	 WINAPI	_DISPATCH_ENTRY ControlDispatcher (HWND, UINT, WPARAM, LPARAM);
extern _TF_ENTRY32 LRESULT	 WINAPI	_DISPATCH_ENTRY PropSheetDispatcher (HWND, UINT, WPARAM, LPARAM);
#endif // WIN32
extern _TF_ENTRY32 LRESULT	 WINAPI	_DISPATCH_ENTRY MDIChildDispatcher (HWND, UINT, WPARAM, LPARAM);
extern _TF_ENTRY32 LRESULT	 WINAPI	_DISPATCH_ENTRY CvMdiFrameDispatcher (HWND, UINT, WPARAM, LPARAM);
extern _TF_ENTRY32 LRESULT	 WINAPI	_DISPATCH_ENTRY CvMdiChildDispatcher (HWND, UINT, WPARAM, LPARAM);
extern _TF_ENTRY32 LRESULT	 WINAPI	_DISPATCH_ENTRY CvDesktopDispatcher (HWND, UINT, WPARAM, LPARAM);
extern _TF_ENTRY32 LRESULT	 WINAPI	_DISPATCH_ENTRY MdiDefChildDispatcher (HWND, UINT, WPARAM, LPARAM);

extern int   WINAPI ProfInsChk(void);
extern void  WINAPI ProfSetup(int,int);
extern void  WINAPI ProfSampRate(int,int);
extern void  WINAPI ProfStart(void);
extern void  WINAPI ProfStop(void);
extern void  WINAPI ProfClear(void);
extern void  WINAPI ProfFlush(void);
extern void  WINAPI ProfFinish(void);

#if (WINVER >= 0x030a)

uint    WINAPI GetFreeSystemResources(uint);
#define GFSR_SYSTEMRESOURCES   0x0000
#define GFSR_GDIRESOURCES      0x0001
#define GFSR_USERRESOURCES     0x0002

#define HWND_DESKTOP        ((HWND)0)

// void    WINAPI LogError(uint err, void * lpInfo);
// void    WINAPI LogParamError(uint err, FARPROC lpfn, void * param);

/****** LogParamError/LogError values */

/* Error modifier bits */

#define ERR_WARNING		0x8000
#define ERR_PARAM		0x4000

#define ERR_SIZE_MASK		0x3000
#define ERR_BYTE                0x1000
#define ERR_WORD                0x2000
#define ERR_DWORD               0x3000

/****** LogParamError() values */

/* Generic parameter values */
#define ERR_BAD_VALUE           0x6001
#define ERR_BAD_FLAGS           0x6002
#define ERR_BAD_INDEX           0x6003
#define ERR_BAD_DVALUE		0x7004
#define ERR_BAD_DFLAGS		0x7005
#define ERR_BAD_DINDEX		0x7006
#define ERR_BAD_PTR		0x7007
#define ERR_BAD_FUNC_PTR	0x7008
#define ERR_BAD_SELECTOR        0x6009
#define ERR_BAD_STRING_PTR	0x700a
#define ERR_BAD_HANDLE          0x600b

/* KERNEL parameter errors */
#define ERR_BAD_HINSTANCE       0x6020
#define ERR_BAD_HMODULE         0x6021
#define ERR_BAD_GLOBAL_HANDLE   0x6022
#define ERR_BAD_LOCAL_HANDLE    0x6023
#define ERR_BAD_ATOM            0x6024
#define ERR_BAD_HFILE           0x6025

/* USER parameter errors */
#define ERR_BAD_HWND            0x6040
#define ERR_BAD_HMENU           0x6041
#define ERR_BAD_HCURSOR         0x6042
#define ERR_BAD_HICON           0x6043
#define ERR_BAD_HDWP            0x6044
#define ERR_BAD_CID             0x6045
#define ERR_BAD_HDRVR           0x6046

/* GDI parameter errors */
#define ERR_BAD_COORDS		0x7060
#define ERR_BAD_GDI_OBJECT      0x6061
#define ERR_BAD_HDC             0x6062
#define ERR_BAD_HPEN            0x6063
#define ERR_BAD_HFONT           0x6064
#define ERR_BAD_HBRUSH          0x6065
#define ERR_BAD_HBITMAP         0x6066
#define ERR_BAD_HRGN            0x6067
#define ERR_BAD_HPALETTE        0x6068
#define ERR_BAD_HMETAFILE       0x6069


/**** LogError() values */

/* KERNEL errors */
#define ERR_GALLOC              0x0001
#define ERR_GREALLOC            0x0002
#define ERR_GLOCK               0x0003
#define ERR_LALLOC              0x0004
#define ERR_LREALLOC            0x0005
#define ERR_LLOCK               0x0006
#define ERR_ALLOCRES            0x0007
#define ERR_LOCKRES             0x0008
#define ERR_LOADMODULE          0x0009

/* USER errors */
#define ERR_CREATEDLG           0x0040
#define ERR_CREATEDLG2          0x0041
#define ERR_REGISTERCLASS       0x0042
#define ERR_DCBUSY              0x0043
#define ERR_CREATEWND           0x0044
#define ERR_STRUCEXTRA          0x0045
#define ERR_LOADSTR             0x0046
#define ERR_LOADMENU            0x0047
#define ERR_NESTEDBEGINPAINT    0x0048
#define ERR_BADINDEX            0x0049
#define ERR_CREATEMENU          0x004a

/* GDI errors */
#define ERR_CREATEDC            0x0080
#define ERR_CREATEMETA          0x0081
#define ERR_DELOBJSELECTED      0x0082
#define ERR_SELBITMAP           0x0083

#define WPF_SETMINPOSITION      0x0001
#define WPF_RESTORETOMAXIMIZED  0x0002

#define WM_WINDOWPOSCHANGING 0x0046
#define WM_WINDOWPOSCHANGED 0x0047

#define DCX_WINDOW	    0x00000001L
#define DCX_CACHE	    0x00000002L
#define DCX_CLIPCHILDREN    0x00000008L
#define DCX_CLIPSIBLINGS    0x00000010L
#define DCX_PARENTCLIP	    0x00000020L

#define DCX_EXCLUDERGN	    0x00000040L
#define DCX_INTERSECTRGN    0x00000080L

#define DCX_LOCKWINDOWUPDATE 0x00000400L

#define DCX_USESTYLE	    0x00010000L

#endif

}

