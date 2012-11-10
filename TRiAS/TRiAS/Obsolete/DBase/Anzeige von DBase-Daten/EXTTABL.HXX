/*
File EXTTABL.HXX -
realisiert einen horizontalen Scrollbalken an einer CommonView-TabularListBox.

Erarbeitet: J. Benkenstein							am: 1. Juni 1992
*/

#ifndef EXTTABL_HXX
#define EXTTABL_HXX

#ifndef NOLISTBOX
class ExtTabularListBox : public TabularListBox
{

// Konstruktoren/Destruktoren
// übergeben nur die notwendigen Parameter an Basisklasse
public:
	ExtTabularListBox (pWindow pW, CvID ID, Point Pt, Dimension Dim,
					   uint no_of_columns);
	ExtTabularListBox (pDialogWindow pDW, ResID ID, uint no_of_columns );
	~ ExtTabularListBox (void);

// sonstige Member
	Bool SetHorzScroll (short TabCount, short TabPos []); /* horiz. Scrollbalken
		auf Basis der Tabulator-Positionen berechnen und aktivieren,
		False, wenn Handle der Listbox ungültig, sonst True,
		Hinweis: Handle ist nach dem 1. AddRow auf jeden Fall gültig */

	Bool RemoveHorzScroll (void); /* horiz. Scrollbalken entfernen,
		False, wenn Handle der Listbox ungültig, sonst True */
};
#endif   // NOLISTBOX

#endif			// EXTTABL_HXX
