// Memberfunktionen für Listboxerweiterungen ----------------------------------
// File: LISTBOX.CXX

#include "trias03p.hxx"

#include <cvext.hxx>
#include "listbox.hxx"

// Memberfunktionen für ExtListBox -------------------------------------------
// liefert den Selektionsstatus des Items mit der Nummer 'Index'
// TRUE: Item ist selektiert, FALSE: Item ist nicht selektiert
bool ExtListBox :: GetSelection (int Index) 
{
	return (SendMessage (GetHandle(), LB_GETSEL, Index, NULL) > 0);
}


// Verhindert Neuzeichnen bei Veränderung
void ExtListBox :: DisableRedraw (void) 
{
	SendMessage (GetHandle(), WM_SETREDRAW, FALSE, NULL);
}

// Ermöglicht Neuzeichnen bei Veränderung
void ExtListBox :: EnableRedraw (void) 
{
	SendMessage (GetHandle(), WM_SETREDRAW, TRUE, NULL);
}


// Memberfunktionen für MultipleSelectionListBox -----------------------------
// liefert die Anzahl der selektiereten Items der ListBox
int MultipleListBox :: CountSelected (void) 
{
	return (int)SendMessage (GetHandle(), LB_GETSELCOUNT, NULL, NULL);
}

// Liefert selektierte Items aus der ListBox (MaxItems in Fels SelItems)
int MultipleListBox :: GetSelectedItems (int MaxItems, int *SelItems) 
{
	return (int)SendMessage (GetHandle(), LB_GETSELITEMS, MaxItems, (unsigned long)SelItems);
}

// Selektiert/UnSelektiert einen Bereich von Items, wenn Last == -1,
// dann nur First
bool MultipleListBox :: ChangeSelection (Bool Flag, int First, int Last) 
{
	if (Last == -1) 	// nur ein Item selektieren
		return (bool)SendMessage (GetHandle(), LB_SELITEMRANGE,
						Flag, MAKELONG(First, First));
	else			// alle von First bis Last selektieren
		return (bool)SendMessage (GetHandle(), LB_SELITEMRANGE,
						Flag, MAKELONG(First, Last));
}

