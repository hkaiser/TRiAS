// Funktionsdefinitionen fuer OwnerDrawComboBox -------------------------------
// File: OWNCOMBO.CXX

#include "trias03p.hxx"

#include <owncombo.hxx>

// Konstruktoren --------------------------------------------------------------
OwnerDrawComboBox :: OwnerDrawComboBox (pDialogWindow pDW, ResID rsc) 
		   : ControlWindow (new ComboBox (pDW, rsc))
{
	if (LocControl() == NULL)
		db_error (EC_NOMEMORY, RC_ctOwnerDrawComboBox);
}

OwnerDrawComboBox :: ~OwnerDrawComboBox (void) 
{
	if (LocControl()) delete LocControl();
}


// Memberfunktionen -----------------------------------------------------------
// Funktionen zum Handling der einzelnen Einträge -----------------------------
long OwnerDrawComboBox :: AddItem (void *pData, WORD Index) 
{
// wenn Objekt ungültig ist
	if (LocControl() == NULL) return CB_ERR;

	if (Index == -1) 
	// normales Insert (ans Ende oder sortiert)
		return ComboBox_AddString (GetHandle(), pData);
//		return SendMessage (GetHandle(), CB_ADDSTRING, 0, (LPARAM)pData);
	else
	// platziertes Insert
		return ComboBox_InsertString (GetHandle(), Index, pData);
//		return SendMessage (GetHandle(), CB_INSERTSTRING, Index, (LPARAM)pData);
}

void *OwnerDrawComboBox :: GetItem (WORD Index) 
{
// wenn Objekt ungültig ist, dann wieder raus
	if (LocControl() == NULL) return NULL;

	if (Index == -1)
	// aktuellen Eintrag lesen
		Index = ComboBox_GetCurSel (GetHandle());
//		Index = (WORD)SendMessage (GetHandle(), CB_GETCURSEL, 0, 0L);

// Daten zu Eintrag anfordern
	if (Index != CB_ERR) {
	long Data = ComboBox_GetItemData (GetHandle(), Index);
//	long Data = SendMessage (GetHandle(), CB_GETITEMDATA, Index, 0L);

		if (Data == CB_ERR)
			return NULL;
		else
			return (void *)Data;
	} else
		return NULL;
}

// liefert Anzahl der in der ListBox der ComboBox verbleibenden Items
long OwnerDrawComboBox :: DelItem (WORD Index) 
{
// wenn Objekt ungültig ist, dann wieder raus
	if (LocControl() == NULL) return CB_ERR;

	if (Index == -1) 	
	// aktuellen Eintrag löschen
		Index = ComboBox_GetCurSel (GetHandle());
//		Index = (WORD)SendMessage (GetHandle(), CB_GETCURSEL, 0, 0L);

// Eintrag löschen
	if (Index != CB_ERR)
		return ComboBox_DeleteString (GetHandle(), Index);
//		return SendMessage (GetHandle(), CB_DELETESTRING, Index, 0L);
	else
	// Fehler: kein Eintrag selektiert und kein Index gegeben
		return CB_ERR;
}

long OwnerDrawComboBox :: SetItem (void *pData, WORD Index) 
{
// wenn Objekt ungültig ist, dann wieder raus
	if (LocControl() == NULL) return CB_ERR;

	if (Index == -1)
	// aktuellen Eintrag behandeln
		Index = ComboBox_GetCurSel (GetHandle());
//		Index = (WORD)SendMessage (GetHandle(), CB_GETCURSEL, 0, 0L);

// Daten zu Eintrag hinzufügen
	if (Index != CB_ERR)
		return ComboBox_SetItemData (GetHandle(), Index, pData);
//		return SendMessage (GetHandle(), CB_SETITEMDATA, Index, (LPARAM)pData);
	else
	// Fehler - kein Eintrag selektiert und kein Index gegeben
		return CB_ERR;
}

long OwnerDrawComboBox :: FindItem (void *pData) 
{
	if (LocControl() == NULL) return CB_ERR;

//	return SendMessage (GetHandle(), CB_FINDSTRING, 0, (LPARAM)pData);
	return ComboBox_FindString (GetHandle(), 0, pData);
}

// neuer Dispatcher -----------------------------------------------------------
#if !defined(NAKEDEVT)
#define NAKEDEVT
class NakedEvt : public Event {
public:
	uint &wmsg (void) { return wMsg; }
	uint wparam (void) { return wParam; }
};
#endif

long OwnerDrawComboBox :: Dispatch (Event e) 
{
	switch (((NakedEvt &)e).wmsg()) {
	case WM_PALETTEISCHANGING:
	case WM_PALETTECHANGED:
	case WM_QUERYNEWPALETTE:
		PaletteChange ((PaletteChangeEvt &)e);
		return TRUE;

	default:
		return ControlWindow :: Dispatch (e);
	}

return TRUE;
}


// EventHandler ---------------------------------------------------------------
void OwnerDrawComboBox :: PaletteChange (PaletteChangeEvt e) 
{
	Default ((Event &)e);
}

void OwnerDrawComboBox :: Activate (Event e) 
{
	if (((NakedEvt &)e).wparam()) {
		((NakedEvt &)e).wmsg() = WM_QUERYNEWPALETTE;
		PaletteChange ((PaletteChangeEvt &)e);	// Palette behandeln
	}
	((NakedEvt &)e).wmsg() = WM_ACTIVATE;
	ControlWindow :: Activate (e);
}

#if defined(WIN32)	// __CVNEW__
// DrawItemEvts kommen jetzt aus der Window-Klasse ----------------------------
bool EXPORT03 OwnerDrawComboBox :: MeasureItem (MeasureItemEvt e)
{
        Default ((Event &)e);
        return false;           // keine Behandlung
}

bool EXPORT03 OwnerDrawComboBox :: DrawEntireItem (DrawItemEvt e)
{
        Default ((Event &)e);
        return false;           // keine Behandlung
}

bool EXPORT03 OwnerDrawComboBox :: DrawItemFocus (DrawItemEvt e)
{
        Default ((Event &)e);
        return false;           // keine Behandlung
}

bool EXPORT03 OwnerDrawComboBox :: DrawItemSelect (DrawItemEvt e)
{
        Default ((Event &)e);
        return false;           // keine Behandlung
}

bool EXPORT03 OwnerDrawComboBox :: DeleteItem (DeleteItemEvt e)
{
        Default ((Event &)e);
        return false;           // keine Behandlung
}

int EXPORT03 OwnerDrawComboBox :: CompareItem (OwnerDrawEvt e, void *, void *)
{
        Default ((Event &)e);
        return 0;           // keine Behandlung
}


#endif // WIN32
