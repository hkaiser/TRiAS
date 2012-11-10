// Fenster, welches Legende beherbergt ----------------------------------------
// File: LEGWIND.HXX

#if !defined(_LEGWIND_HXX)
#define _LEGWIND_HXX

#if !defined(NOLEGENDEWINDOW)
// LegendeFenster, welches eingeblendet werden kann ---------------------------
class CLegendeObjekt;

class CLegendeWindow : public DialogWindow {
private:
	DatenBasisObjekt &m_rDBO;
//	PBD_DB &m_PBD;
//	CIdTree &m_IDs;

	Menu m_LMenu;		// Menu dieses Fensters
	Dimension m_Dim;
	class CLegendeObjekt *m_pLO;

	WndVertScrollBar *m_pVertSB;	// vertikaler ScroolBalken
	WndHorzScrollBar *m_pHorzSB;	// horizontaler ScrollBalken

	unsigned int m_fFitFont : 1;			// Font anpassen
	unsigned int m_fSetScrollBars : 1;	// HilfsFlag
	unsigned int m_fPainting : 1;			// Semaphore für Zeichnen
	unsigned int m_fShowMenu : 1;			// PopupMenu aktiv	
	unsigned int m_fShowAllEntries : 1;	// alles anzeigen
	unsigned int m_fSelRect : 1;			// Rechteck ist angezeigt
	unsigned int m_fPendingReSel : 1;		// Selektion muß gelöscht werden
	unsigned int m_fBrushToDelete : 1;	// m_hBr ist freizugeben
	unsigned int m_fIsDropSource : 1;		// wir sind derzeit DropSource
	unsigned int m_fNeedsCalculation : 1;	// Fontgröße muß berechnet werden
					
	HMENU m_hMenu;				// PopupMenuHandle
	WORD m_iActSelection;			// aktuelle Selektion
		
// DragDropSupport
	UINT m_cf;				// ClipboardFormat für DragDrop
	short m_iDropPos;			// Position der aktuellen DropSelektion
	WORD m_iDropOrder;			// Stelle, an der eingefügt werden soll
	HBRUSH m_hBr;				// Brush für Selektion
	class CLegWindDropTarget *m_pDropTgt;	// DropTarget für dieses Fenster
	WORD m_iClipOrder;			// Position, wo der Eintrag vorher war

	UINT m_uiScrollInset;			// InsetRegion for Scrolling
	UINT m_uiScrollDelay;			// ScrollDelay in InsetRegion
	UINT m_uiHorzScrollCode;		// Scrollen notwendig
	UINT m_uiVertScrollCode;
	UINT m_uiLastTest;
	DWORD m_dwTimeLast;			// letzter TimerTick
	HWND m_hWnd;				// unser FensterHandle
		
#if defined(WIN32)
	HACCEL m_hAccel;		// Acceleratoren für dieses Fenster
#endif // WIN32

	void SetScrollRanges (void);
	Rectangle RealCanvasRect (void);
	bool HideSelection (WORD iOrder);	// Selektion verwalten
	bool ShowSelection (WORD iOrder, bool fForce = false);
	void PaintSelection (Rectangle &rRc);
	bool ResetSelection (void);

	void ShowMenu (short X, short Y);	// PopupMenu anzeigen
	WORD FindEntry (Point &pt);		// Eintrag über Koordinate finden
	
// MenuHandler
	void HandleVisParams (void);
	void HandleEditText (void);

protected:
	void Expose (ExposeEvt e);
	bool QueryClose (Event);
	void MouseButtonDn (MouseEvt);
	void MouseButtonUp (MouseEvt);
	void MouseDrag (MouseEvt);
	void MouseButtonDblClk (MouseEvt);
	void ReSize (ReSizeEvt);
	void MenuCommand (MenuCommandEvt);
	void MenuInit (MenuInitEvt);
	void HorizScroll (ScrollEvt e);
	void VertScroll (ScrollEvt e);
//	void KeyDown (KeyEvt e);
	LRESULT Dispatch (Event e);
#if defined(WIN32)
	bool PreTranslateMsg (MSG *pMsg);		// Accels bearbeiten
#endif // WIN32

public:
// Konstruktor/Destruktor
		CLegendeWindow (pWindow pParent, char* szCaption, 
				DatenBasisObjekt &rDBO);
		~CLegendeWindow (void);

static CLegendeWindow *CreateInstance (pWindow pParent, char *pCaption,
				       DatenBasisObjekt &rDBO);

	bool FInit (void);
	
// sonstige Memberfunktionen
	CIdTree &SetIdTree (CIdTree &newIDs);
	HWND Handle (Service s) { return Window :: Handle (s); }
	bool RefreshLegend (void);
	bool SaveLegend (void);
	bool ResetLegend (void);
	bool AddObject (long lONr);

// DragDropSupport
private:
	LPDATAOBJECT TransferObjectCreate (WORD iOrder);
	bool DrawDropSelection (Rectangle &rc);
	bool FClipEntry (WORD iOrder);

public:
	bool DropSelectTargetWindow (POINTL *pptl, bool fRemove = false, bool fpaint = true);
	bool FQueryPasteFromData (LPDATAOBJECT);	// Daten für uns dabei ?
	bool FPasteFromData (LPDATAOBJECT);		// Daten einfügen
	UINT UTestDroppablePoint (POINTL *pptl);
inline	bool FQueryDrop (void) { return !(m_iClipOrder == m_iDropOrder); }
inline	bool IsDropSource (void) { return m_fIsDropSource; }

inline	PBD_DB &PbdDB (void) { return m_rDBO.PbdDB(); }
inline	CIdTree & IDs (void) { return m_rDBO.Idents(); }

friend class CLegWindDropTarget;
};

// sonstige Funktionen --------------------------------------------------------
bool DefineNewIdentVisInfo (long lIdent, short iVTyp, bool fHSB);
HANDLEVISINFO *GetIdentVisInfo (long lIdent, short iVTyp, char *pView);
HANDLEVISINFO *ctHANDLEVISINFO (short iVTyp);
void dtHANDLEVISINFO (HANDLEVISINFO *& pHVI);

HBRUSH PASCAL CreateInvBrush (void);

#endif // NOLEGENDEWINDOW

#endif // _LEGWIND_HXX

