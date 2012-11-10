// Erweiterte Listbox - Klasendefinitionen etc.
// File: LISTBOX.HXX

#if !defined(_LISTBOX_HXX)
#define _LISTBOX_HXX

extern "C" {
// Windows Definitionen
	#define LBS_MULTIPLESEL		0x0008L
	#define LBS_EXTENDEDSEL		0x0800L
}

// ListBox mit einigen nÅtzlichen zusÑtzlichen Funktionen --------------------
class ExtListBox : public ListBox {
public:
// Konstruktoren
		ExtListBox (pDialogWindow pD, ResID R) : ListBox (pD, R) {}

// zusÑtzliche Memberfunktionen
	HANDLE GetHandle (void) { return Handle (API_CONTROL_HCONTROL); }
	Bool GetSelection (int Index);	// Selektion von Item 'Index' abfragen
	int GetStringLen (int Index);	// liefert LÑnge von Item 'Index'
	int GetString (int Index, char *Buffer);	// liefert Item 'Index'
	void EnableRedraw (void);
	void DisableRedraw (void);
};

// ListBox, die zusÑtzlich Multiple Selections erlaubt -----------------------
class MultipleListBox : public ExtListBox {
public:
// Konstruktor
		MultipleListBox (pDialogWindow pD, ResID R)
			: ExtListBox (pD, R) {
		// MultipleSel und ExtendedSel einschalten
			SetStyle (LBS_MULTIPLESEL | LBS_EXTENDEDSEL);
		}

// Memberfunktionen
	int CountSelected (void);	// Anzahl der ausgewÑhlten Items
	int GetSelectedItems (int MaxItems, int *SelItems);
					// liefert selektierte Items
	Bool ChangeSelection (Bool flag, int First, int Last = -1);
					// selektiert Item(s)
};

#endif // _LISTBOX_HXX
