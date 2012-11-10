// Funktionsdefinitionen fuer OwnerDrawListBox --------------------------------
// File: OWNLIST.CXX

#include "trias03p.hxx"

#include <limits.h>
#include <ownlist.hxx>

// Konstruktoren --------------------------------------------------------------
OwnerDrawListBox :: OwnerDrawListBox (pDialogWindow pDW, ResID rsc) 
		  : ControlWindow (new ListBox (pDW, rsc))
{
	if (LocControl() == NULL)
		db_error (EC_NOMEMORY, RC_ctOwnerDrawListBox);
}

OwnerDrawListBox :: OwnerDrawListBox (Control *pL) 
		  : ControlWindow (pL)
{
	if (LocControl() == NULL)
		db_error (EC_NOMEMORY, RC_ctOwnerDrawListBox);
}

OwnerDrawListBox :: ~OwnerDrawListBox (void) 
{
	if (LocControl()) delete LocControl();
}


// Memberfunktionen -----------------------------------------------------------
// Funktionen zum Handling der einzelnen Einträge -----------------------------
long OwnerDrawListBox :: AddItem (void *pData, int Index) 
{
// wenn Objekt ungültig ist
	if (LocControl() == NULL) return LB_ERR;

	if (Index == UINT_MAX) // normales Insert (ans Ende oder sortiert)
		return ListBox_AddItemData (GetHandle(), pData);
	else		 // platziertes Insert
		return ListBox_InsertItemData (GetHandle(), Index, pData);
}

void *OwnerDrawListBox :: GetItem (int Index) 
{
// wenn Objekt ungültig ist, dann wieder raus
	if (LocControl() == NULL) return NULL;

int iIndex = Index;

	if (Index == UINT_MAX)	// aktuellen Eintrag lesen
		iIndex = ListBox_GetCurSel (GetHandle());

// Daten zu Eintrag anfordern
	if (iIndex != LB_ERR) {
	long lData = ListBox_GetItemData (GetHandle(), iIndex);

		if (lData == LB_ERR)
			return NULL;
		else
			return (void *)lData;
	} else
		return NULL;
}

// liefert Anzahl der in der ListBox der ComboBox verbleibenden Items
long OwnerDrawListBox :: DelItem (int Index) 
{
// wenn Objekt ungültig ist, dann wieder raus
	if (LocControl() == NULL) return LB_ERR;

int iIndex = Index;

	if (Index == UINT_MAX) 	// aktuellen Eintrag löschen
		iIndex = ListBox_GetCurSel (GetHandle());

// Eintrag löschen
	if (iIndex != LB_ERR)
		return ListBox_DeleteString (GetHandle(), iIndex);
	else		// Fehler: kein Eintrag selektiert und kein Index gegeben
		return LB_ERR;
}

long OwnerDrawListBox :: SetItem (void *pData, int Index) 
{
// wenn Objekt ungültig ist, dann wieder raus
	if (LocControl() == NULL) return LB_ERR;

int iIndex = Index;

	if (Index == UINT_MAX)	// aktuellen Eintrag behandeln
		iIndex = ListBox_GetCurSel (GetHandle());

// Daten zu Eintrag hinzufügen
	if (iIndex != LB_ERR)
		return ListBox_SetItemData (GetHandle(), iIndex, pData);
	else	// Fehler - kein Eintrag selektiert und kein Index gegeben
		return LB_ERR;
}

long OwnerDrawListBox :: FindItem (void *pData) 
{
	if (LocControl() == NULL) return LB_ERR;

	return ListBox_FindString (GetHandle(), 0, pData);
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

long OwnerDrawListBox :: Dispatch (Event e) 
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
void OwnerDrawListBox :: PaletteChange (PaletteChangeEvt e) 
{
	Default ((Event &)e);
}

void OwnerDrawListBox :: Activate (Event e) 
{
	if (((NakedEvt &)e).wparam()) {
		((NakedEvt &)e).wmsg() = WM_QUERYNEWPALETTE;
		PaletteChange ((PaletteChangeEvt &)e);	// Palette behandeln
	}
	((NakedEvt &)e).wmsg() = WM_ACTIVATE;
	ControlWindow :: Activate (e);
}
