// Klassendefinitionen fuer OwnerDraw ComboBox --------------------------------
// File: OWNCOMBO.HXX


#if !defined(_OWNCOMBO_HXX)
#define _OWNCOMBO_HXX

#include <palchevt.hxx>		// PalettenHandling

class _TRIAS03_ENTRY OwnerDrawComboBox : public ControlWindow {
public:
	enum OwnerDrawStyle {
		HasStrings = CBS_HASSTRINGS,
		FixedHeight = CBS_OWNERDRAWFIXED,
		VariableHeight = CBS_OWNERDRAWVARIABLE,
	};

// Konstruktor/Destruktor
	EXPORT03 OwnerDrawComboBox (pDialogWindow pW, ResID rsc);
	EXPORT03 ~OwnerDrawComboBox (void);

protected:
// EventHandler 
	long EXPORT03 Dispatch (Event);
	void EXPORT03 Activate (Event);

virtual void EXPORT03 PaletteChange (PaletteChangeEvt);

#if !defined(WIN16)	// __CVNEW__
virtual BOOL EXPORT03 MeasureItem (MeasureItemEvt);
virtual BOOL EXPORT03 DrawEntireItem (DrawItemEvt);
virtual BOOL EXPORT03 DrawItemFocus (DrawItemEvt);
virtual BOOL EXPORT03 DrawItemSelect (DrawItemEvt);
virtual BOOL EXPORT03 DeleteItem (DeleteItemEvt);
virtual int EXPORT03 CompareItem (OwnerDrawEvt, void *, void *);
#endif 

// sonstige Memberfunktionen
	HWND GetHandle (void) { return GetControl() -> Handle (API_CONTROL_HCONTROL); }

public:
	ComboBox *LocControl (void) { return (ComboBox *)GetControl(); }

	long EXPORT03 AddItem (void *, int Index = -1);	// Eintrag hinzufügen
	void * EXPORT03 GetItem (int Index = -1);		// Eintrag lesen
	long EXPORT03 DelItem (int Index = -1);		// Eintrag löschen
	long EXPORT03 SetItem (void *, int Index = -1);	// Daten neu setzen
	long EXPORT03 FindItem (void *);			// Einrag suchen
};

#endif // _OWNCOMBO_HXX
