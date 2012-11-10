// Uebersichtsanzeige der aktuellen Datenbank ---------------------------------
// File: OVERVIEW.HXX


#if !defined(_OVERVIEW_HXX)
#define _OVERVIEW_HXX

// Event für WM_WINDOWPOSCHANGEGING -------------------------------------------
class WindowPosEvt : 
	public Event 
{
public:
	void GetWindowSize (Dimension &);
	void SetWindowSize (Dimension);
	BOOL SizeIsChanging (void);
};

class SelectionObject;

class COverView : 
	public DialogWindow 
{
private:
#if defined(WIN32)
	HENHMETAFILE m_hMF;
	HPALETTE m_hPal;
#else
	HMETAFILE m_hMF;	// angezeigtes MetaFile
#endif // WIN32

	RECTL m_ocDB;		// aktueller Gesamt-GeoDBContainer
	double m_dAspect;
	long m_dDBx;		// aktueller Ausschnitt
	long m_dDBy; 
	
	Dimension m_dimWnd;     // aktuelle FensterGröße (WindowRect)
	CoOrd m_dX;		// CanvasBreite	(CanvasRect)
	CoOrd m_dY;		// CanvasHöhe
	
	RECT *m_prcActVP;	// aktueller Bildausschnitt
	
	CoOrd m_ixExt;		// MetaFileExtend
	CoOrd m_iyExt;

	Brush *m_pBr;			// HinterGrundbrush
	class SelectionObject *m_prcSel;	// SelektionsObjekt
	Pointer *m_pOldPointer;
	Pointer *m_pMove;
	Pointer *m_pLupe;	
	
	HMENU m_hSubMenu;		// RightButtonMenu

	unsigned int m_fBrushChanged : 1;
	unsigned int m_fLeftBttnSem : 1;
	unsigned int m_fPointerChanged : 1;
	unsigned int m_fToDelete : 1;
	unsigned int m_fIsDirty : 1;

	Point m_ptAspect;
	double m_dRatio;
		
protected:
virtual void WindowPosChanging (WindowPosEvt);

	long Dispatch (Event);

	void Expose (ExposeEvt);	// neu zeichnen
	void MouseButtonUp (MouseEvt);
	void MouseButtonDn (MouseEvt);
	void MouseDrag (MouseEvt);
	void MouseMove (MouseEvt);

	void ReSize (ReSizeEvt);
	Bool QueryClose (Event);

// RightButtonMenu
	void MenuCommand (MenuCommandEvt);
	void MenuInit (MenuInitEvt);
	void MenuSelect (MenuSelectEvt);

	bool TrackOverviewMenu (Point pt);
	bool OnResetRect (void);
	bool OnActView (void);
	bool OnHideWindow (void);

public:
		COverView (pWindow pW, Point ptAspect, double dRatio);
		~COverView (void);
		
	BOOL FInit (ObjContainer &ocDB, bool fInitNew);
	void FInitCursor (void);			// nur Cursor wechseln
	
	void SetActVP (ObjContainer &ocNewVP);
	void ResetActVP (BOOL fFreeSel = TRUE);

///////////////////////////////////////////////////////////////////////////////
// MetaFile speichern/einlesen
	HRESULT LoadEnhMetaFile (LPCSTR pcName);
	HRESULT SaveEnhMetaFile (LPCSTR pcName);
	bool RetrieveActViewMetaFile (Rectangle &rcC);
	bool SaveOverview (LPCSTR pcName = NULL);

///////////////////////////////////////////////////////////////////////////////
// inlines
inline CoOrd xDBtoCV (long xOC);
inline CoOrd yDBtoCV (long yOC);
inline long xCVtoDB (CoOrd xCV);
inline long yCVtoDB (CoOrd yCV);
	
	BOOL fToDelete (void) { return m_fToDelete; }

static 	COverView *CreateOverView (pWindow pW, ObjContainer &ocDB, bool fInitNew, Point ptAspect, double dRatio);
};

// allgemeine Funktionsprototypen ---------------------------------------------
#if !defined(WIN32)
HGLOBAL RetrieveMetaFile (HWND, Rectangle &Rc, RECTL &rclDB, UINT uiMapMode);
#else
HENHMETAFILE RetrieveMetaFile (HWND, Rectangle &Rc, RECTL &rclDB, UINT uiMapMode);
#endif // WIN32

// Inline-Funktionen ----------------------------------------------------------
inline long MulDivL (CoOrd x, long y, long z)
{
	return (y/(z/long(x)));
}

#if defined(__WATCOMC__)
#pragma warning 604 5;		// lookahead required
#pragma warning 595 5;		// resoveld as an expression
#endif

inline long DivMulL (CoOrd x, long y, long z)
{
	return (long(x)*(y/z));
}

inline CoOrd COverView :: xDBtoCV (long xOC)
{
	return short(MulDivL (m_dX, xOC-m_ocDB.left, m_ocDB.right-m_ocDB.left));
}

inline CoOrd COverView :: yDBtoCV (long yOC)
{
	return m_dY - CoOrd(MulDivL (m_dY, yOC-m_ocDB.bottom, m_ocDB.top-m_ocDB.bottom));
}

inline long COverView :: xCVtoDB (CoOrd xCV)
{
	return DivMulL (xCV, m_ocDB.right-m_ocDB.left, m_dX) + m_ocDB.left;
}

inline long COverView :: yCVtoDB (CoOrd yCV)
{
	return DivMulL (m_dY - yCV, m_ocDB.top-m_ocDB.bottom, m_dY) + m_ocDB.bottom;
}


#endif // _OVERVIEW_HXX

