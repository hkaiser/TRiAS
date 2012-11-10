// Klassendefinitionen fuer OwnerDraw ComboBox --------------------------------
// File: OWNLISTE.HXX


#if !defined(_OWNLISTEX_HXX)
#define _OWNLISTEX_HXX

class _TRIAS03_ENTRY OwnerDrawListBoxEx : public OwnerDrawListBox 
{
#if defined(WIN32)
private:
	Point m_ptMouseDown;
	bool m_fMouseOpPending;
	bool m_fCaptured;		// mouse is captured
	bool m_fDragDrop;		// Drag'n Drop erlauben
#endif // WIN32

protected:
	void EXPORT03 FocusChange (FocusChangeEvt);

#if defined(WIN32)
	void MouseButtonDn (MouseEvt);
	void MouseButtonUp (MouseEvt);
	void MouseDrag (MouseEvt);
#endif // WIN32

public:
// Konstruktor/Destruktor
	EXPORT03 OwnerDrawListBoxEx (pDialogWindow pW, ResID rsc);
	EXPORT03 ~OwnerDrawListBoxEx (void);

// sonstige Memberfunktionen
public:
	MultiSelListBox *LocCtrl (void) { return (MultiSelListBox *)GetControl(); }

	int EXPORT03 GetNoSelected (void);
	Bool EXPORT03 ClearSelected (void);
	int EXPORT03 GetFirstSelected (void);
	int EXPORT03 GetNextSelected (void);
	Bool EXPORT03 ChangeSelected (int index, Bool = TRUE);
	Bool EXPORT03 ChangeSelected (Range, Bool = TRUE);
	Bool EXPORT03 GetSelection (short);	
	int EXPORT03 GetCaretIndex (void);
	int EXPORT03 SetCaretIndex (int, Bool = FALSE);

	HWND Handle (Service s) { return (HWND)LocCtrl() -> Handle (s); }

#if defined(WIN32)
	bool EnableDragDrop (bool fDragDrop = true);
	int IndexFromPoint (Point pt, bool *pfPastLastEntry = NULL);
#endif // WIN32
};

#if defined(WIN32)

#define WM_FAKENOTIFYFORWIN95	(WM_USER+1234)

// Datenstruktur, die als LPARAM verschickt wird, wenn Drag'n Drop
// anfängt
typedef struct tagNM_LISTBOX {
	NMHDR hdr;
	int iItem;
	POINT ptDrag;
	DWORD dwFlags;
} NM_LISTBOX;

#define LBN_BEGINDRAG	1000
#define LBN_BEGINRDRAG	1001

#endif // WIN32

#endif // _OWNLISTEX_HXX
