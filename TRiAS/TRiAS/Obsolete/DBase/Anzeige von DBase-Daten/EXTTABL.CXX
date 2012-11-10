/*
File EXTTABL.CXX -
realisiert einen horizontalen Scrollbalken an einer CommonView-TabularListBox.

Erarbeitet: J. Benkenstein						  am: 1. Juni 1992
*/

#include "pheader.h"

#include "exttabl.htp"	 // Selektion der CommonView-Klassen
#include <commonvu.hxx>
#include "exttabl.hxx"	 // zugeh. Header	 

ExtTabularListBox :: ExtTabularListBox (pWindow pW, CvID ID, Point Pt,
					 Dimension Dim, uint no_of_columns)
				   : TabularListBox (pW, ID, Pt, Dim, no_of_columns)
{
	// nothing to do
}

ExtTabularListBox :: ExtTabularListBox (pDialogWindow pDW, ResID ID,
					 uint no_of_columns)
				   : TabularListBox (pDW, ID, no_of_columns)
{
	// nothing to do
}

ExtTabularListBox :: ~ ExtTabularListBox (void)
{
	// nothing to do
}

Bool __export ExtTabularListBox :: SetHorzScroll (short TabCount, short TabPos [])
{
	HWND ListHandle = (HWND) Handle ();
	if (!ListHandle)		// wenn Handle nicht gültig
		return False;

	const short CharInTab = 8;	  // 8 Zeichen pro Tabulator

//  Anzahl der Tabulatoren berechnen
	short TabC = 0;
	for (short Index = 0; Index < TabCount; Index++) {
		TabC += TabPos [Index] / CharInTab;
		if (TabPos [Index] % CharInTab)
			TabC++;
	}
	TabC *= (short) GetDialogBaseUnits () * CharInTab;
	
	SendMessage ((HWND) ListHandle, LB_SETHORIZONTALEXTENT, (WPARAM) TabC, 0L);
	return True;
}

Bool __export ExtTabularListBox :: RemoveHorzScroll (void)
{
	HWND ListHandle = (HWND) Handle ();
	if (!ListHandle)		// wenn Handle nicht gültig
		return False;

	SendMessage ((HWND) ListHandle, LB_SETHORIZONTALEXTENT, (WPARAM) 0, 0L);
	return True;
}
