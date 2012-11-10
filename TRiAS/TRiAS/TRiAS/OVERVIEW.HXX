// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.03.2001 19:45:59 
//
// @doc
// @module OVERVIEW.HXX | Declaration of the <c COverView> and <c COverViewClient> classes

#if !defined(_OVERVIEW_HXX__79F1E5B7_525B_433C_8896_D83258A24378__INCLUDED_)
#define _OVERVIEW_HXX__79F1E5B7_525B_433C_8896_D83258A24378__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Event für WM_WINDOWPOSCHANGEGING 
#include <WindowPosEvent.h>

///////////////////////////////////////////////////////////////////////////////
// 
#define ID_OVERVIEW_CLIENT	0xE901			// AFX_IDW_PANE_FIRST

class SelectionObject;
class COverView;

class COverViewClientWindow :
	public ChildAppWindow
{
private:
	HENHMETAFILE m_hMF;
	HPALETTE m_hPal;

	RECTL m_ocDB;			// aktueller Gesamt-GeoDBContainer
	double m_dAspect;	
	long m_dDBx;			// aktueller Ausschnitt
	long m_dDBy; 

	CoOrd m_dX;				// durch das aktuelle Metafile genutzter Bereich
	CoOrd m_dY;				// 
	CoOrd m_dX0;			// ZentrierungsOffset
	CoOrd m_dY0;

	RECT *m_prcActVP;		// aktueller Bildausschnitt
	
	CoOrd m_ixExt;			// MetaFileExtend
	CoOrd m_iyExt;

	Brush *m_pBr;			// HinterGrundbrush
	SelectionObject *m_prcSel;	// SelektionsObjekt
	Pointer *m_pOldPointer;
	Pointer *m_pMove;
	Pointer *m_pLupe;	
	Icon *m_pTabIcon;
	COverView *m_pParent;
	os_string m_strViewName;

	HMENU m_hSubMenu;		// RightButtonMenu

	unsigned int m_fBrushChanged : 1;
	unsigned int m_fLeftBttnSem : 1;
	unsigned int m_fPointerChanged : 1;
	unsigned int m_fIsDirty : 1;

	Point m_ptAspect;
	double m_dRatio;
	DatenBasisObjekt &m_rDBO;

protected:
	void Expose (ExposeEvt);	// neu zeichnen
	void MouseButtonUp (MouseEvt);
	void MouseButtonDn (MouseEvt);
	void MouseDrag (MouseEvt);
	void MouseMove (MouseEvt);

	void ReSize (ReSizeEvt);

// RightButtonMenu
	void MenuCommand (MenuCommandEvt);
	void MenuInit (MenuInitEvt);
	void MenuSelect (MenuSelectEvt);

	bool TrackOverviewMenu (Point pt);
	bool OnResetRect (void);
	bool OnActView (void);
	bool OnHideWindow (void);

	void EnsureScaleKoeffs();
	double CalculateScaleKoeffs(Rectangle &rrc);

	void SetActVP (ObjContainer &ocNewVP);
	void ResetActVP (BOOL fFreeSel = TRUE);

public:
		COverViewClientWindow (Point ptAspect, double dRatio, DatenBasisObjekt &rDBO, COverView *pParent = NULL);
		~COverViewClientWindow (void);

static COverViewClientWindow *CreateInstance(ObjContainer &ocDB, bool fInitNew, Point ptAspect, double dRatio, DatenBasisObjekt &rDBO);

	BOOL FInit (ObjContainer &ocDB, bool fInitNew);
	void FInitCursor (void);			// nur Cursor wechseln
	bool ReShow();						// wieder anzeigen

	CComVariant GetIcon();
	double GetAspect() { return m_dAspect; }
	COverView *GetParentWindow() { return m_pParent; }

	void SetActVP (Rectangle rcC);

///////////////////////////////////////////////////////////////////////////////
// MetaFile speichern/einlesen
	HRESULT LoadEnhMetaFile (LPCSTR pcName, LPSTR pBuffer, int iLen);
	HRESULT SaveEnhMetaFile (LPCSTR pcName);
	bool RetrieveActViewMetaFile (Rectangle *prcC = NULL);
	bool SaveOverview (LPCSTR pcName = NULL);

///////////////////////////////////////////////////////////////////////////////
// inlines
	inline CoOrd xDBtoCV (long xOC);
	inline CoOrd yDBtoCV (long yOC);
	inline long xCVtoDB (CoOrd xCV);
	inline long yCVtoDB (CoOrd yCV);

	inline bool fToDelete (void);

	ObjContainer GetActDBRect() { return ObjContainer(m_ocDB.left, m_ocDB.right, m_ocDB.bottom, m_ocDB.top); }
};

///////////////////////////////////////////////////////////////////////////////
// Rahmenfenster für die 'alte' (nicht angedockkte Version)
class COverView : 
	public DialogWindow 
{
public:
	friend class COverViewClientWindow;

	COverView(Window *pW);
	~COverView();

static HRESULT RegisterTabWindow();
static COverViewClientWindow *CreateOverView (pWindow pW, ObjContainer &ocDB, bool fInitNew, Point ptAspect, double dRatio, DatenBasisObjekt &rDBO);
static void DeleteInstance(COverViewClientWindow *& pOverView);

	BOOL FInit(ObjContainer &ocDB, bool fInitNew, COverViewClientWindow *pClient);

protected:
	virtual void WindowPosChanging (WindowPosEvt);

	void ReSize (ReSizeEvt evt);
	long Dispatch (Event);
	Bool QueryClose (Event);

	BOOL fToDelete (void) { return m_fToDelete; }

private:
	COverViewClientWindow *m_pOverView;
	Dimension m_dimWnd;     // aktuelle FensterGröße (WindowRect)
	bool m_fToDelete;
};

///////////////////////////////////////////////////////////////////////////////
// allgemeine Funktionsprototypen 
HENHMETAFILE RetrieveMetaFile (HWND, Rectangle &Rc, RECTL &rclDB, UINT uiMapMode);

///////////////////////////////////////////////////////////////////////////////
// Inline-Funktionen 

inline CoOrd COverViewClientWindow::xDBtoCV (long xOC)
{
	return MulDiv(m_dX, xOC-m_ocDB.left, m_ocDB.right-m_ocDB.left) + m_dX0;
}

inline CoOrd COverViewClientWindow::yDBtoCV (long yOC)
{
	return m_dY - (CoOrd(MulDiv (m_dY, yOC-m_ocDB.bottom, m_ocDB.top-m_ocDB.bottom)) - m_dY0);
}

inline long COverViewClientWindow::xCVtoDB (CoOrd xCV)
{
	return MulDiv(xCV - m_dX0, m_ocDB.right-m_ocDB.left, m_dX) + m_ocDB.left;
}

inline long COverViewClientWindow::yCVtoDB (CoOrd yCV)
{
	return MulDiv(m_dY - (yCV - m_dY0), m_ocDB.top-m_ocDB.bottom, m_dY) + m_ocDB.bottom;
}

inline bool COverViewClientWindow::fToDelete (void)
{ 
	return (NULL != m_pParent) ? m_pParent -> fToDelete() : false; 
}

///////////////////////////////////////////////////////////////////////////////
// Stream Konstanten
const DWORD METAFILE_SIGNATURE = 0x4154454DL;		// "META"
const DWORD METAFILE_VERSION_MINOR_MASK = 0xff;
const DWORD METAFILE_VERSION_100 = 0x0100L;
const DWORD METAFILE_LASTKNOWN_VERSION = METAFILE_VERSION_100;

#endif // !defined(_OVERVIEW_HXX__79F1E5B7_525B_433C_8896_D83258A24378__INCLUDED_)
