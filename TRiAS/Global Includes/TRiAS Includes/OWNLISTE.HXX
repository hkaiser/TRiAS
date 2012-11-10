// Klassendefinitionen fuer OwnerDraw ComboBox --------------------------------
// File: OWNLISTE.HXX


#if !defined(_OWNLISTEX_HXX)
#define _OWNLISTEX_HXX

class _TRIAS03_ENTRY OwnerDrawListBoxEx : public OwnerDrawListBox 
{
#if !defined(WIN16)
private:
	Point m_ptMouseDown;
	BOOL m_fMouseOpPending;
	BOOL m_fCaptured;		// mouse is captured
	BOOL m_fDragDrop;		// Drag'n Drop erlauben
#endif // WIN16

protected:
	void EXPORT03 FocusChange (FocusChangeEvt);

#if !defined(WIN16)
	void MouseButtonDn (MouseEvt);
	void MouseButtonUp (MouseEvt);
	void MouseButtonDblClk (MouseEvt);
	void MouseDrag (MouseEvt);
#endif // WIN16

public:
// Konstruktor/Destruktor
	EXPORT03 OwnerDrawListBoxEx (pDialogWindow pW, ResID rsc);
	EXPORT03 ~OwnerDrawListBoxEx (void);

// sonstige Memberfunktionen
public:
	MultiSelListBox *LocCtrl (void) { return (MultiSelListBox *)GetControl(); }

	int EXPORT03 GetNoSelected (void);
	BOOL EXPORT03 ClearSelected (void);
	int EXPORT03 GetFirstSelected (void);
	int EXPORT03 GetNextSelected (void);
	BOOL EXPORT03 ChangeSelected (int index, BOOL = TRUE);
	BOOL EXPORT03 ChangeSelected (Range, BOOL = TRUE);
	BOOL EXPORT03 GetSelection (int);	
	int EXPORT03 GetCaretIndex (void);
	int EXPORT03 SetCaretIndex (int, BOOL = FALSE);

	HWND Handle (Service s) { return (HWND)LocCtrl() -> Handle (s); }

#if !defined(WIN16)
	BOOL EnableDragDrop (BOOL fDragDrop = true);
	int IndexFromPoint (Point pt, BOOL *pfPastLastEntry = NULL);
#endif // WIN16
};

#if !defined(WIN16)

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

#endif // WIN16

#endif // _OWNLISTEX_HXX
