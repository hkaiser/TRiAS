// Farb-DialogFensterKlasse ---------------------------------------------------
// File: PALWIND.HXX

#if !defined(_PALWIND_HXX)
#define _PALWIND_HXX

#include "UpDnEdit.h"

// DialogfensterKlassen für die Einstellung de Darstellungsparameter ----------
class PaletteWindow : public OwnerDrawDialogWindow {
protected:
	ColorScrollBar RedScrollBar;		// Rollbalken ROT
	ColorScrollBar GreenScrollBar;		// RollBalken GRÜN
	ColorScrollBar BlueScrollBar;		// RollBalken BLAU
	FixedText m_ftRed;
	FixedText m_ftGreen;
	FixedText m_ftBlue;
	
	DatenBasisObjekt &m_rDBO;

	unsigned short m_fHSB : 1;

// OwnerDraw EventHandler
	BOOL EXPORTTRIAS DeleteItem (DeleteItemEvt);	// ODItem wird gelöscht
	BOOL EXPORTTRIAS DrawEntireItem (DrawItemEvt);	// ZeichenFunktionen
	BOOL EXPORTTRIAS DrawItemFocus (DrawItemEvt);
	BOOL EXPORTTRIAS DrawItemSelect (DrawItemEvt);

	int EXPORTTRIAS CompareItem (OwnerDrawEvt, void *, void *);	// Vergleichsfunktion
	BOOL EXPORTTRIAS MeasureItem (MeasureItemEvt);

	ColorListBox QueryColor;		// OwnerDrawComboBox mit Farben

private:
	PushButton OKButton, CancelButton;	// Buttons

//protected:	// müssen in APALWIND ausgeblendet werden
//	PushButton NewButton, DelButton;

private:
#if defined(WIN16)
	PushButton HelpButton;
#endif

	void HelpShow (void);

protected:
// Memberdaten
	Color _oldColor;		// alte Farbe

	void ButtonClick (ControlEvt);		// ButtonClick

	void HorizScroll (ScrollEvt);		// ScrollBalken
	void ListBoxSel (ControlEvt);		// ListBoxSel
	void ListBoxClk (ControlEvt);		// DoppelClick

	void EditFocusChg (EditFocusChgEvt);	// Focus loosed/gained to Edit

	long EXPORTTRIAS Dispatch (Event);			// eigener Dispatcher

virtual	Color ModColor (Color * = NULL);	// liefert aktuell geregelte Farbe
virtual ColorBox &CBox (void) = 0;		// liefert embedded ColorBox

public:
// Konstruktor
		PaletteWindow (uint rsc, pWindow, DatenBasisObjekt &, Color, BOOL fHSB = false);

// Memberfunktionen
	Color &GetMainColor (void);	// liefert Resultat

// Destruktor
		~PaletteWindow (void);

	HWND Handle (Service s) { return Window :: Handle (s); }
};

// PaletteWindow für Flächenobjekte -------------------------------------------
class AreaPaletteWindow : public PaletteWindow {
private:
	AreaColorBox ShowArea;		// Rechteck für aktuelle Farbanzeige
	RadioButton FirstColor, SecondColor;	// Umschalter Rand- / Füllfarbe
	CSpinControl LineWidth;
	CheckBox _Transparent;
	CheckBox m_cbBkConture;
	
protected:
	void Expose (ExposeEvt);
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void ListBoxClk (ControlEvt);
	void VertScroll (ScrollEvt);
	void EditFocusChg (EditFocusChgEvt);

#if !defined(WIN16)
	void HelpRequest (HelpRequestEvt e);
#endif
// OwnerDraw EventHandler
	BOOL EXPORTTRIAS DeleteItem (DeleteItemEvt);	// ODItem wird gelöscht
	BOOL EXPORTTRIAS DrawEntireItem (DrawItemEvt);	// ZeichenFunktionen
	int EXPORTTRIAS CompareItem (OwnerDrawEvt, void *, void *);	// Vergleichsfunktion

	Color _oldSecC;			// alte/neue Attribute
	short _oldStyle;
	short _oldBkMode;
#if !defined(OLDVISINFO)
	short m_iOldWidth;		// KonturDicke
	bool m_fOldBkConture;		// Kontur mit Hintergrundfarbe
#endif // OLDVISINFO
	
	FillStyleComboBox FillStyles;	// FüllModeAuswahl

	Color ModColor (Color * = NULL);
	ColorBox &CBox (void);

#if defined(OLDVISINFO)
	void AdjustBkMode (short iBkMode);
#else
	void AdjustBkMode (short iBkMode, bool fBkConture);
#endif	

public:
// Konstruktor/Destruktor
#if defined(OLDVISINFO)
		AreaPaletteWindow (pWindow, DatenBasisObjekt &, Color, Color, short Style, 
				   bool fHSB = false);
#else
		AreaPaletteWindow (pWindow, DatenBasisObjekt &, Color, Color, short Style, 
				   short iWidth, BOOL fHSB = false, 
				   BOOL fBkConture = false, BOOL fOpaque = false);
#endif // OLDVISINFO
		~AreaPaletteWindow (void);

// Memberfunktionen
	Color &GetFillColor (void);	// liefert Füllfarbe
	short GetFillStyle (void);	// liefert Füllmode
	void SetFillStyle (short);	// setzt FüllMode
	short GetWidth (void);		// liefert Konturbreite
	void SetWidth (short);		// setzt LinienDicke
	short GetStyle (void) { 
		return short((GetFillStyle() + (GetWidth() * 100)) | GetBkMode()); 
	}
	short GetBkMode (void);
#if !defined(OLDVISINFO)
	void SetBkConture (bool);
	short GetBkContureMode (void);
#endif
};

// PaletteWindow für Linienobjekte --------------------------------------------
class LinePaletteWindow : public PaletteWindow {
private:
	LineColorBox ShowLine;		// Bereich für aktuelle Linienanzeige
	CSpinControl LineWidth;

protected:
	void Expose (ExposeEvt);
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void ListBoxClk (ControlEvt);
	void VertScroll (ScrollEvt);		// für SpinButton
	void EditFocusChg (EditFocusChgEvt);	// Focus loosed/gained to Edit

// OwnerDraw EventHandler
	BOOL EXPORTTRIAS DeleteItem (DeleteItemEvt);
	BOOL EXPORTTRIAS DrawEntireItem (DrawItemEvt);
	int EXPORTTRIAS CompareItem (OwnerDrawEvt, void *, void *);

	short _oldWidth;	// alte/neue Attribute
	short _oldStyle;

	LineStyleComboBox LineStyles;

	ColorBox &CBox (void);

public:
// Konstruktor/Destruktor
		LinePaletteWindow (pWindow, DatenBasisObjekt &, Color, short Width, 
				   short Style, BOOL fHSB = false);
		~LinePaletteWindow (void);

// Memberfunktionen
	short &GetWidth (void);		// liefert LinienDicke
	short &GetLineStyle (void);	// liefert LinienTyp
};

// PaletteWindow für Punktobjekte ---------------------------------------------
class PointPaletteWindow : public PaletteWindow {
private:
	PointColorBox ShowPoint;	// Bereich für aktuelle Symbolanzeige
	CSpinControl SymbolX;		// SymbolGröße einstellen
	CSpinControl SymbolY;
#if !defined(WIN16)
	CSpinControl *m_pRotation;
	RadioButton *m_pColor1;
	RadioButton *m_pColor2;
#endif // WIN16
	bool m_fObjVis;

protected:
	void Expose (ExposeEvt);
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void ListBoxClk (ControlEvt);
	void VertScroll (ScrollEvt);		// für SpinButton
	void EditFocusChg (EditFocusChgEvt);	// Focus loosed/gained to Edit

// OwnerDraw EventHandler
	BOOL EXPORTTRIAS DeleteItem (DeleteItemEvt);	// ODItem wird gelöscht
	BOOL EXPORTTRIAS DrawEntireItem (DrawItemEvt);	// ZeichenFunktionen
	int EXPORTTRIAS CompareItem (OwnerDrawEvt, void *, void *);	// Vergleichsfunktion

	short _oldSymbol;	// alte/neue Attribute
	Dimension _oldSize;
	short m_iOldRot;
	Color m_SecC;

	PointStyleComboBox PointStyle;

	ColorBox &CBox (void);
#if !defined(WIN16)
	Color ModColor (Color *pC = NULL);
#endif // WIN16

public:
// Konstruktor/Destruktor
#if !defined(WIN16)
		PointPaletteWindow (pWindow, DatenBasisObjekt &, Color, 
				    Dimension Size, short Style, BOOL fHSB = false, 
				    short iRot = 0, Color SecC = DEF_SECCOLOR,
				    BOOL fObjVis = false);
#else
		PointPaletteWindow (pWindow, DatenBasisObjekt &, Color, 
				    Dimension Size, short Style, bool fHSB = false, 
				    short iRot = 0, Color SecC = DEF_SECCOLOR);
#endif
		~PointPaletteWindow (void);

// Memberfunktionen
	Dimension &GetSize (void);	// liefert PunktGröße
	short &GetPointSymbol (void);	// liefert PunktSymbol
	short &GetRotation (void);
	Color &Get2ndColor (void);
};

#endif	// _PALWIND_HXX
