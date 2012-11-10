// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 02.03.2001 10:20:22 
//
// @doc
// @module LEGWIND.HXX | Fenster, welches Legende beherbergt

#if !defined(_LEGWIND_HXX__413DD00F_47C2_4FA1_BF9E_FA037A63F2F6__INCLUDED_)
#define _LEGWIND_HXX__413DD00F_47C2_4FA1_BF9E_FA037A63F2F6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "LegDInfo.hxx"
#include "Legende.hxx"

///////////////////////////////////////////////////////////////////////////////
// Fenster welches die eigentliche Legende enthält
#define ID_LEGEND_CLIENT	0xE901			// AFX_IDW_PANE_FIRST

class CLegendeWindow;
class CLegendeObjekt;
class CLegWindDropTarget;

class CLegendeClientWindow :
	public ChildAppWindow
{
	friend class CLegWindDropTarget;

public:
// ctor/dtor/Initialisiertung
	CLegendeClientWindow(DatenBasisObjekt &rDBO, CLegendeWindow *pParent = NULL);
	~CLegendeClientWindow();

static CLegendeClientWindow *CreateInstance (DatenBasisObjekt &rDBO, CLegendeWindow *pParent = NULL);

	bool FInit (Rectangle *prc = NULL, Dimension *pDim = NULL);
	bool ReShow();

// Methoden
	bool RefreshLegend (void);
	bool SaveLegend (void);
	bool ResetLegend (void);
	bool AddObject (long lONr);
	bool ViewSelected (LPCSTR pcView);

	bool GetFitFont() { return m_fFitFont; }
	bool GetShowAll() { return m_pLO -> ShowAll(); }
	bool GetShowAreaOnly() { return m_pLO -> ShowAreaOnly(); }
	bool GetScaleMode() { return m_pLO -> GetScaleMode(); }
	WORD GetActSelection() { return m_iActSelection; }

	bool GetIsShown(WORD iActSel) { return m_pLO -> isShown (iActSel); }
	bool GetHasSpace(WORD iActSel) { return m_pLO -> hasSpace (iActSel); }
	LEGENTRYTYPE GetIsA(WORD iActSel) { return m_pLO -> isA(iActSel); }
	bool GetCustomizedText(WORD iActSel) { return m_pLO -> CustomizedText (iActSel); }
	bool GetIsFirstEntry(WORD iActSel) { return m_pLO -> isFirstEntry (iActSel); }
	bool GetIsLastEntry(WORD iActSel) { return m_pLO -> isLastEntry (iActSel); }

// DragDropSupport
private:
	LPDATAOBJECT TransferObjectCreate (WORD iOrder);
	bool DrawDropSelection (Rectangle &rc);
	bool FClipEntry (WORD iOrder);

public:
	bool DropSelectTargetWindow (POINTL *pptl, bool fRemove = false, bool fpaint = true);
	bool FQueryPasteFromData (LPDATAOBJECT);	// Daten für uns dabei ?
	bool FPasteFromData (LPDATAOBJECT);			// Daten einfügen
	UINT UTestDroppablePoint (POINTL *pptl);
	bool FQueryDrop (void) { return !(m_iClipOrder == m_iDropOrder); }
	bool IsDropSource (void) { return m_fIsDropSource; }

	CIdTree &IDs (void) { return m_rDBO.Idents(); }
	CLegendeWindow *GetParentWindow() { return m_pParent; }
	CComVariant GetIcon();

	void MenuCommand (MenuCommandEvt);
	void MenuInit(MenuInitEvt e);

	bool ResetSelection (void);

protected:
	void Expose (ExposeEvt e);
	BOOL QueryClose (Event);
	void MouseButtonDn (MouseEvt);
	void MouseButtonUp (MouseEvt);
	void MouseDrag (MouseEvt);
	void MouseButtonDblClk (MouseEvt);
	void ReSize (ReSizeEvt);
	void HorizScroll (ScrollEvt e);
	void VertScroll (ScrollEvt e);
	LRESULT Dispatch (Event e);
	BOOL PreTranslateMsg (MSG *pMsg);		// Accels bearbeiten
	void KeyDown (KeyEvt e);

private:		
	void SetScrollRanges (void);
	Rectangle RealCanvasRect (void);
	bool HideSelection (WORD iOrder);		// Selektion verwalten
	bool ShowSelection (WORD iOrder, bool fForce = false);
	void PaintSelection (Rectangle &rRc);

	void ShowMenu (WORD wOrder, int X, int Y);		// PopupMenu anzeigen
	WORD FindEntry (Point &pt);				// Eintrag über Koordinate finden
	
// MenuHandler
	bool FitLegendEntries();
	bool SizesLikeScaling();
	bool ShowAllEntries();
	bool LegendReset();

	bool HandleShowEntry();
	bool HandleVisParams();
	bool HandleEditText();
	bool HandleInsertHeadLine();
	bool HandleResetText();
	bool HandleMoveUp();
	bool HandleMoveDown();
	bool HandleSelectAusschnitt();

	bool HandleInsertSpaceLine();
	bool HandleRemoveSpaceLine();
	bool HandleRemoveEntry();

private:
	DatenBasisObjekt &m_rDBO;
	CLegendeObjekt *m_pLO;
	CLegendeWindow *m_pParent;		// != NULL, wenn im 'alten' Anzeigerahmen
	Brush *m_pbkBrush;				// Hintergrundpinsel

	Dimension m_Dim;

	WndVertScrollBar *m_pVertSB;	// vertikaler ScroolBalken
	WndHorzScrollBar *m_pHorzSB;	// horizontaler ScrollBalken

	unsigned int m_fFitFont : 1;			// Font anpassen
	unsigned int m_fSetScrollBars : 1;		// HilfsFlag
	unsigned int m_fPainting : 1;			// Semaphore für Zeichnen
	unsigned int m_fShowMenu : 1;			// PopupMenu aktiv	
	unsigned int m_fShowAllEntries : 1;		// alles anzeigen
	unsigned int m_fSelRect : 1;			// Rechteck ist angezeigt
	unsigned int m_fPendingReSel : 1;		// Selektion muß gelöscht werden
	unsigned int m_fBrushToDelete : 1;		// m_hBr ist freizugeben
	unsigned int m_fIsDropSource : 1;		// wir sind derzeit DropSource
	unsigned int m_fNeedsCalculation : 1;	// Fontgröße muß berechnet werden
					
	HMENU m_hMenu;							// PopupMenuHandle
	WORD m_iActSelection;					// aktuelle Selektion

// DragDropSupport
	UINT m_cf;								// ClipboardFormat für DragDrop
	short m_iDropPos;						// Position der aktuellen DropSelektion
	WORD m_iDropOrder;						// Stelle, an der eingefügt werden soll
	HBRUSH m_hBr;							// Brush für Selektion
	CLegWindDropTarget *m_pDropTgt;			// DropTarget für dieses Fenster
	WORD m_iClipOrder;						// Position, wo der Eintrag vorher war

	UINT m_uiScrollInset;					// InsetRegion for Scrolling
	UINT m_uiScrollDelay;					// ScrollDelay in InsetRegion
	UINT m_uiHorzScrollCode;				// Scrollen notwendig
	UINT m_uiVertScrollCode;
	UINT m_uiLastTest;
	DWORD m_dwTimeLast;						// letzter TimerTick
	HWND m_hWnd;							// unser FensterHandle
	HACCEL m_hAccel;						// Acceleratoren für dieses Fenster
	Icon *m_pTabIcon;						// angezeigtes Bildchen
};

// LegendenFenster, welches eingeblendet werden kann 
class CLegendeWindow : 
	public DialogWindow 
{
private:
	Menu m_LMenu;		// Menu dieses Fensters
	CLegendeClientWindow *m_pLegend;

public:
// Konstruktor/Destruktor
	CLegendeWindow (pWindow pParent, char* szCaption);
	~CLegendeWindow (void);

static HRESULT RegisterTabWindow();
static CLegendeClientWindow *CreateInstance (pWindow pParent, char *pCaption, DatenBasisObjekt &rDBO);
static void DeleteInstance(CLegendeClientWindow *& pLegend);

	bool FInit (CLegendeClientWindow *pLegend = NULL);
	
// sonstige Memberfunktionen
	bool RefreshLegend (void) { return m_pLegend -> RefreshLegend(); }
	bool SaveLegend (void) { return m_pLegend -> SaveLegend(); }
	bool ResetLegend (void) { return m_pLegend -> ResetLegend(); }
	bool AddObject (long lONr) { return m_pLegend -> AddObject(lONr); }
	bool ViewSelected (LPCSTR pcView) 
	{ 
		if (NULL != pcView)
			SetCaption (pcView);
		return m_pLegend -> ViewSelected(pcView); 
	}
	bool ResetSelection (void) { return (NULL != m_pLegend) ? m_pLegend -> ResetSelection() : true; }
	CLegendeClientWindow *GetClientWindow() { return m_pLegend; }

protected:
	LRESULT Dispatch (Event e);
	BOOL QueryClose (Event);
	void MenuInit (MenuInitEvt);
	void MenuCommand (MenuCommandEvt);
	void ReSize (ReSizeEvt);
};

///////////////////////////////////////////////////////////////////////////////
// sonstige Funktionen 
bool DefineNewIdentVisInfo (long lIdent, short iVTyp, bool fHSB);
HANDLEVISINFO *GetIdentVisInfo (long lIdent, short iVTyp, char *pView);
HANDLEVISINFO *ctHANDLEVISINFO (short iVTyp);
void dtHANDLEVISINFO (HANDLEVISINFO *& pHVI);

HBRUSH PASCAL CreateInvBrush (void);

#endif // !defined(_LEGWIND_HXX__413DD00F_47C2_4FA1_BF9E_FA037A63F2F6__INCLUDED_)
