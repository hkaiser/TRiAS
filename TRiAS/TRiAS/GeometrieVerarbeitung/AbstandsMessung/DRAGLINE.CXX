// Funktionen für das Nachführen einer Linie
// File: DRAGLINE.CXX
// H. Kaiser


#include "abstandp.hxx"

#include "abstguid.h"	// CLSID_Abstand
#include "abstand.hxx"	// AbstandExtension


//-------------------------------------------------------------------------------------------------
// linke Maustaste drücken
void AbstandExtension :: LMouseButtonDn (Point& Pt)
{
	MVWind() -> MouseTrap (TRUE);	// alle MausEvt's an dieses Fenster
	if (_DRO != NULL)
		MVWind() -> Draw (_DRO);	// letzte Lage evtl. noch löschen
	DELETE_OBJ (_DRO);
	_DRO = new DragLineObject (Pt);
	if (! _DRO)
	{
		DEX_Error (RC_dragline_abst, EC_NOMEMORY);
		return;
	}
	_DRO -> ChangeRop (ROP_Invert);
}


//-------------------------------------------------------------------------------------------------
// Maus bei gedrückter linker Maustaste bewegt
void AbstandExtension :: LMouseDrag (Point& Pt)
{
	if (_DRO == NULL) return;

// DragRechteck neu dimensionieren und neu zeichen
	MVWind() -> Draw (_DRO); // alte Lage löschen
	_DRO -> Process (Pt);
	MVWind() -> Draw (_DRO);
}


//-------------------------------------------------------------------------------------------------
// linke Maustaste freigegeben
void AbstandExtension :: LMouseButtonUp (void)
{
	if (_DRO == NULL) return;

	MVWind() -> MouseTrap (FALSE);	// MausEvents wieder freigeben
}


//-------------------------------------------------------------------------------------------------
// rechte Maustaste drücken
void AbstandExtension :: RMouseButtonDn (void)
{
	if (_DRO == NULL) return;

	MVWind() -> Draw (_DRO);	// letzte Lage auch noch löschen
	DELETE_OBJ (_DRO);          // DrawObject freigeben
}
