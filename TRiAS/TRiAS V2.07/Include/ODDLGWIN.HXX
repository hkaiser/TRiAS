// Klassendefinition fuer Dialogfenster-Erweiterungen (OwnerDraw und Custom)
// File: ODDLGWIN.HXX

#if !defined(_ODDLGWIN_HXX)
#define _ODDLGWIN_HXX

#if !defined(WIN32)

#if !defined(NAKEDEVT)
// entblößter Event
class NakedEvt : public Event {
public:
	uint &wmsg (void) { return wMsg; }
	uint wparam (void) { return wParam; }
	ulong lparam (void) { return lParam; }
	void *lpExtra (void *pExtra = NULL) {
	void *poldExtra = EvtExtra;

		if (pExtra != NULL) EvtExtra = pExtra;
		return poldExtra;
	}
};
#define NAKEDEVT
#endif // NAKEDEVT

// EventKlassen für die OwnerDraw Controls ------------------------------------
class _TRIAS03_ENTRY OwnerDrawEvt : public ControlEvt {
public:
	enum OwnerDrawControl {
		OwnerDrawButton = ODT_BUTTON,
		OwnerDrawComboBox = ODT_COMBOBOX,
		OwnerDrawListBox = ODT_LISTBOX,
		OwnerDrawMenu = ODT_MENU,
	};
	OwnerDrawControl EXPORT03 ItemType (void);
};

class _TRIAS03_ENTRY DeleteItemEvt : public OwnerDrawEvt {
public:
	void * EXPORT03 GetItemData (void);	// zugehörige Daten lesen
	int EXPORT03 GetItemID (void);		// ItemID
};

class _TRIAS03_ENTRY MeasureItemEvt : public OwnerDrawEvt {
public: 
	void EXPORT03 SetItemHeight (CoOrd);	// Größe des Items setzen
	void EXPORT03 SetItemWidth (CoOrd);
	void * EXPORT03 GetItemData (void);	// zugehörige Daten lesen
	HWND EXPORT03 Handle (Service);
	int EXPORT03 GetItemID (void);		// ItemID
};

class _TRIAS03_ENTRY DrawItemEvt : public OwnerDrawEvt {
public:
	Rectangle EXPORT03 ItemSize (void);	// Größe holen
	Bool EXPORT03 isDisabled (void);	// Item ist disabled
	Bool EXPORT03 hasFocus (void);		// Item hat Focus
	Bool EXPORT03 isSelected (void);	// Item ist selektiert
	void * EXPORT03 GetItemData (void);	// zugehörige Daten lesen
	HANDLE EXPORT03 Handle (Service);	// hDC/hWnd holen
	int EXPORT03 GetItemID (void);		// ItemID
};

// erweiterte Dialogfensterklasse, die für OwnerDraw - Controls geeignet ist --
class _TRIAS03_ENTRY OwnerDrawDialogWindow : public DialogWindow {
protected:
// neue EventHandlerFunktionen
virtual Bool EXPORT03 MeasureItem (MeasureItemEvt);	// Größe eines Elements bestimmen
virtual Bool EXPORT03 DrawEntireItem (DrawItemEvt);	// Element vollständig malen
virtual Bool EXPORT03 DrawItemFocus (DrawItemEvt);	// Element mit Focus zeichnen
virtual Bool EXPORT03 DrawItemSelect (DrawItemEvt);	// Element ausgewählt zeichnen
virtual Bool EXPORT03 DeleteItem (DeleteItemEvt);	// Element ist gelöscht
virtual int EXPORT03 CompareItem (OwnerDrawEvt, void *, void *);	// Vergleich zweier Einträge

// der neue EventDispatcher
	long EXPORT03 Dispatch (Event e);

public:
// Konstruktor/Destruktor
	EXPORT03 OwnerDrawDialogWindow (pWindow pW, ResID rsc, Bool isModal = TRUE);
	EXPORT03 ~OwnerDrawDialogWindow (void);
};

#else

typedef DialogWindow OwnerDrawDialogWindow;

#endif // WIN32

#endif // _ODDLGWIN_HXX
