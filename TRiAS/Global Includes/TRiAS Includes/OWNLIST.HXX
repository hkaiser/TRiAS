// Klassendefinitionen fuer OwnerDraw ComboBox --------------------------------
// File: OWNLIST.HXX


#if !defined(_OWNLIST_HXX)
#define _OWNLIST_HXX

#include <palchevt.hxx>		// PalettenHandling

class _TRIAS03_ENTRY OwnerDrawListBox : public ControlWindow {
public:
	enum OwnerDrawStyle {
		HasStrings = CBS_HASSTRINGS,
		FixedHeight = CBS_OWNERDRAWFIXED,
		VariableHeight = CBS_OWNERDRAWVARIABLE,
	};

// Konstruktor/Destruktor
	EXPORT03 OwnerDrawListBox (pDialogWindow pW, ResID rsc);
	EXPORT03 OwnerDrawListBox (Control *);
	EXPORT03 ~OwnerDrawListBox (void);

protected:
// EventHandler 
	long EXPORT03 Dispatch (Event);
	void EXPORT03 Activate (Event);

virtual void EXPORT03 PaletteChange (PaletteChangeEvt);

public:
// sonstige Memberfunktionen
	HWND GetHandle (void) { return (HWND)GetControl() -> Handle (API_CONTROL_HCONTROL); }

public:
	ListBox *LocControl (void) { return (ListBox *)GetControl(); }

	long EXPORT03 AddItem (void *, int Index = -1);	// Eintrag hinzufügen
	void * EXPORT03 GetItem (int Index = -1);		// Eintrag lesen
	long EXPORT03 DelItem (int Index = -1);		// Eintrag löschen
	long EXPORT03 SetItem (void *, int Index = -1);	// Daten neu setzen
	long EXPORT03 FindItem (void *);			// Einrag suchen
};


#endif // _OWNLIST_HXX
