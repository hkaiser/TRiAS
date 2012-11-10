// OwnerDraw - DialogFensterKlasse --------------------------------------------
// File: EXDLGWIN.CXX

#include "trias03p.hxx"

// Konstruktor ----------------------------------------------------------------
EXPORT03  OwnerDrawDialogWindow :: OwnerDrawDialogWindow (pWindow pW, ResID rsc, Bool isModal)
		       : DialogWindow (pW, rsc, isModal)
{
	// sonst nichts weiter
}

EXPORT03  OwnerDrawDialogWindow :: ~OwnerDrawDialogWindow (void) 
{
	// nichts weiter
}

// Memberfunktionen -----------------------------------------------------------
long EXPORT03  OwnerDrawDialogWindow :: Dispatch (Event e) 
{
uint Message = ((NakedEvt &)e).wmsg();
uint wParam = ((NakedEvt &)e).wparam();
ulong lParam = ((NakedEvt &)e).lparam();

	switch (Message) {
	case WM_COMMAND:
//		switch (HIWORD(lParam)) {
//		default:
			return DialogWindow :: Dispatch (e);
//		}

	// OwnerDraw Messages
	case WM_COMPAREITEM:	// Vergleich zweier Einträge (Items)
		return CompareItem ((OwnerDrawEvt &)e,
				    (void *)(((COMPAREITEMSTRUCT *)lParam) -> itemData1),
				    (void *)(((COMPAREITEMSTRUCT *)lParam) -> itemData2));

	case WM_DELETEITEM:	// Item wird gelöscht
		return DeleteItem ((DeleteItemEvt &)e);

	case WM_DRAWITEM:	// Item neu zeichnen 
		{
		DRAWITEMSTRUCT *pDI = (DRAWITEMSTRUCT *)lParam;

			if (pDI -> itemID == -1) {
			// keine Elemente in ComboBox
				return DrawItemFocus ((DrawItemEvt &)e);
			} else switch (pDI -> itemAction) {
			// Element normal behandeln
			case ODA_DRAWENTIRE:
				{
					DrawEntireItem ((DrawItemEvt &)e);
//					if (((DrawItemEvt &)e).isSelected())
//						DrawItemSelect ((DrawItemEvt &)e);
//					if (((DrawItemEvt &)e).hasFocus())
//						DrawItemFocus ((DrawItemEvt &)e);
				}
				return TRUE;

			case ODA_SELECT:
				return DrawItemSelect ((DrawItemEvt &)e);

			case ODA_FOCUS:
				return DrawItemFocus ((DrawItemEvt &)e);
	
			default:
				return DialogWindow :: Dispatch (e);
			}
		}
		break;

	case WM_MEASUREITEM:	// Größe eines Items bestimmen
		{
		HWND hWnd = Handle (API_WINDOW_HWND);	// Handle des DialogFensters

			((NakedEvt &)e).lpExtra ((void *)&hWnd);	// HWND merken			
			return MeasureItem ((MeasureItemEvt &)e);
		}

	default:
		return DialogWindow :: Dispatch (e);
	}
}

// Neue Events sowie ihre Memberfunktionen ------------------------------------
// allgemeiner OwnerDrawEvent
OwnerDrawEvt::OwnerDrawControl EXPORT03  OwnerDrawEvt :: ItemType (void) 
{
	return (OwnerDrawEvt::OwnerDrawControl)((DRAWITEMSTRUCT *)lParam) -> CtlType;	
	// bei allen an der gleichen Position in der Struktur
}

// Event, wenn ein Item aus List-/ComboBox gelöscht wird ----------------------
void *EXPORT03  DeleteItemEvt :: GetItemData (void) 
{
	return (void *)(((DELETEITEMSTRUCT *)lParam) -> itemData);
}

int EXPORT03  DeleteItemEvt :: GetItemID (void) 
{
	return ((DELETEITEMSTRUCT *)lParam) -> itemID;
}

// Event, wenn ein Item neu gezeichnet werden muß -----------------------------
void *EXPORT03  DrawItemEvt :: GetItemData (void) 
{
	return (void *)(((DRAWITEMSTRUCT *)lParam) -> itemData);
}

int EXPORT03  DrawItemEvt :: GetItemID (void) 
{
	return ((DRAWITEMSTRUCT *)lParam) -> itemID;
}

HANDLE EXPORT03  DrawItemEvt :: Handle (Service s) 
{
	switch (s) {
	case API_CONTROL_HDC:
		return (HANDLE)((DRAWITEMSTRUCT *)lParam) -> hDC;

	case API_CONTROL_HCONTROL:
		return (HANDLE)((DRAWITEMSTRUCT *)lParam) -> hwndItem;

	default:
		return NULL;
	}
}

Rectangle EXPORT03  DrawItemEvt :: ItemSize (void) 
{
Rectangle locRc;

	CopyRect ((LPRECT)&locRc, (LPRECT)&((DRAWITEMSTRUCT *)lParam) -> rcItem);

return locRc;
}

Bool EXPORT03  DrawItemEvt :: isDisabled (void) 
{
	return ((DRAWITEMSTRUCT *)lParam) -> itemState & ODS_DISABLED;
}

Bool EXPORT03  DrawItemEvt :: hasFocus (void) 
{
	return ((DRAWITEMSTRUCT *)lParam) -> itemState & ODS_FOCUS;
}

Bool EXPORT03  DrawItemEvt :: isSelected (void) 
{
	return ((DRAWITEMSTRUCT *)lParam) -> itemState & ODS_SELECTED;
}

// Event, wenn Größe eines Items bestimmt werden soll
void *EXPORT03  MeasureItemEvt :: GetItemData (void) 
{
	return (void *)(((MEASUREITEMSTRUCT *)lParam) -> itemData);
}

void EXPORT03  MeasureItemEvt :: SetItemHeight (CoOrd iH) 
{
	((MEASUREITEMSTRUCT *)lParam) -> itemHeight = iH;
}

void EXPORT03  MeasureItemEvt :: SetItemWidth (CoOrd iW) 
{
	((MEASUREITEMSTRUCT *)lParam) -> itemWidth = iW;
}

HWND EXPORT03  MeasureItemEvt :: Handle (Service s) 
{
	switch (s) {
	case API_DLGWINDOW_HWND:
	// FensterHandle des DialogFensters liefern
		return *(HWND *)(((NakedEvt *)this) -> lpExtra());

	default:
		return 0;
	}
}

int EXPORT03  MeasureItemEvt :: GetItemID (void) 
{
	return ((MEASUREITEMSTRUCT *)lParam) -> itemID;
}


// DefaultHandler für die neuen EventHandler ----------------------------------
Bool EXPORT03  OwnerDrawDialogWindow :: DeleteItem (DeleteItemEvt e) 
{
	Default ((Event &)e);
	return FALSE;		// keine Behandlung
}

Bool EXPORT03  OwnerDrawDialogWindow :: DrawEntireItem (DrawItemEvt e) 
{
	Default ((Event &)e);
	return FALSE;		// keine Behandlung
}

Bool EXPORT03  OwnerDrawDialogWindow :: MeasureItem (MeasureItemEvt e) 
{
	Default ((Event &)e);
	return FALSE;
}

Bool EXPORT03  OwnerDrawDialogWindow :: DrawItemFocus (DrawItemEvt e) 
{
Rectangle Rc = e.ItemSize();			// aktuellen Bereich holen

	DrawFocusRect ((HDC)e.Handle (API_CONTROL_HDC), (RECT *)&Rc);

return TRUE;
}

Bool EXPORT03  OwnerDrawDialogWindow :: DrawItemSelect (DrawItemEvt e) 
{
Rectangle Rc = e.ItemSize();			// aktuellen Bereich holen

	InvertRect ((HDC)e.Handle (API_CONTROL_HDC), (RECT *)&Rc);

return TRUE;
}

int EXPORT03  OwnerDrawDialogWindow :: CompareItem (OwnerDrawEvt, void *Item1, void *Item2) 
{
	return strcmp ((const char *)Item1, (const char *)Item2);
}

