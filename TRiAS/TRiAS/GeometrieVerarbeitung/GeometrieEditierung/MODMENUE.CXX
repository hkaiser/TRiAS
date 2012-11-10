// Menü bei Modifizierung einer vorhandenen Geometrie und Druck auf rechte Maustaste
// File: MODMENUE.CXX
// H. Kaiser, W. Mörtl


#include "geoeditp.hxx"

#include "spmoddlg.hxx"	// VertexModifyDlg

#include "editguid.h"	// CLSID_GeometrieEditierung in geoedit.hxx
#include "geoedit.hxx"


// externe Variable
extern ResourceFile* pRF;




static void AddMenuOffset (HMENU hMenu, short iOffset);


// ------------------------------------------------------------------------------------------------
// Menü generieren
void GeoEditExtension :: ObjectModifyMenu (pWindow pW, Point Pt, uint resID)
{
Menu ModifyMenu (ResID (resID, pRF));
HMENU hMenu = ModifyMenu.Handle (API_MENU_HMENU);

	if (hMenu == NULL) return;	// Ressource nicht gefunden
	
// Menü generieren / Offsets addieren
	m_hSubMenu = GetSubMenu (hMenu, 0);		// SubMenu holen

	AddMenuOffset (m_hSubMenu, MenuOffset());

	ClientToScreen (MVWind() -> Handle (API_CLIENT_HWND), (LPPOINT)&Pt);
	TrackPopupMenu (m_hSubMenu, 0, Pt.X(), Pt.Y(), 0, pW -> Handle (API_CLIENT_HWND), NULL);
} // ObjectModifyMenu


// ------------------------------------------------------------------------------------------------
// Modifikation eines Menü's (addieren des Menüoffsets)
static void AddMenuOffset (HMENU hMenu, short iOffset)
{
	if (hMenu == 0) return;		// nur für gültige Menü's

int nCount = GetMenuItemCount (hMenu);
char MenuEntry[DEX_MENUNAMELEN+1];

	for (int wItem = 0; wItem < nCount; wItem++)
	{
	UINT MenuState = GetMenuState (hMenu, wItem, MF_BYPOSITION);
	UINT MenuID = GetMenuItemID (hMenu, wItem);

		if (MenuID == -1)		// PopUpMenu
		{
			AddMenuOffset (GetSubMenu (hMenu, wItem), iOffset);	
			continue;
		}
		if (MenuState & (MF_MENUBARBREAK | MF_MENUBREAK | MF_SEPARATOR))
			continue;
		GetMenuString (hMenu, wItem, MenuEntry, DEX_MENUNAMELEN, MF_BYPOSITION);
		ModifyMenu (hMenu, wItem, MF_BYPOSITION | MenuState, MenuID+iOffset, MenuEntry);
	}
} // AddMenuOffset


// --------------------------------------------------------------------------------------------
// Editieren der Koordinaten des lInd-Stützpunktes im pIOG-Objekt
void GeoEditExtension :: EditVertex (IObjektGeometrie* pIOG, long lInd)
{
// "Visible" ist bei dem nachfolgenden Dialog NICHT angekreuzt, damit dieser erst bei Show()
// angezeigt wird
VertexModifyDlg* pVMDlg = new VertexModifyDlg (MVWind(), pIOG, lInd);
		
	if (! pVMDlg)
	{                                                                      
		DEX_Error (RC_modmenue, EC_NOMEMORY);
		return;
	}

short iMarkGr = GroesseMarkQuadrat ();
Point Pt;	// linke untere Ecke des pVMDlg-Dialogs
Dimension dimDlgGr = pVMDlg -> GetSize();	// Größe des Dialogs in Pixel
Rectangle CRc = MVWind() -> CanvasRect();
CoOrd BSB = CRc.Right() - CRc.Left();	// Bildschirmbreite

	Pt.X() = _ptRM.X() + iMarkGr;
	Pt.Y() = _ptRM.Y() - iMarkGr - dimDlgGr.Height();

	// Korrektur, falls Dialog rechts bzw. unten über Bildschirmrand hinausreicht
	if (Pt.X() + dimDlgGr.Width() > BSB)	// Dialog ragt über den rechten Bildschirmrand hinaus
		Pt.X() = BSB - dimDlgGr.Width();
	if (Pt.Y() < 0)							// Dialog ragt über den unteren Bildschirmrand hinaus
		Pt.Y() = 0;

	pVMDlg -> ChangePosition (Pt);

	pVMDlg -> Show();

AktNeu Erg = (AktNeu) pVMDlg -> Result (); // Rückgabewert der Aktion im pVMDlg-DialogFenster

/*										     
	switch (Erg)
	{                                                                                     
// nach Stützpunkt modifizieren bzw. Stützpunkt löschen Geometrie wegspeichern und Bereich neu
// zeichnen; siehe dazu StuetzpunktVerschieben() in geomodif.cxx
	}
*/

	DELETE (pVMDlg);
} // EditVertex
