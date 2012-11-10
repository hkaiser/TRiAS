// Funktionen für das Zeichnen einer Linie
// File: DRAGLINE.CXX
// H. Kaiser, W. Mörtl


#include "geoeditp.hxx"

#include <stdio.h>		// sprintf() für OutputDebugString

#include "editguid.h"	// CLSID_GeometrieEditierung in geoedit.hxx
#include "geoedit.hxx"



#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif




// --------------------------------------------------------------------------------------------------
// linke bzw. rechte Maustaste für Neueditierung bzw. bei Aufbau eiens "Messers" für Flächenteilung
// gedrückt
void GeoEditExtension :: LRMouseButtonDn (Point& Pt)
{
	DELETE (_DRO);
	_DRO = new DragLineObject (Pt);	// Pt ist der Anfangspunkt des Linienobjektes

	if (! _DRO)
	{
		DEX_Error (RC_dragline_edit, EC_NOMEMORY);
		return;
	}
	_DRO -> ChangeRop (ROP_Invert);	// das von _DRO überzeichnete Gebiet wird invertiert
} // LRMouseButtonDn


// --------------------------------------------------------------------------------------------------
// linke Maustaste freigegeben
void GeoEditExtension :: LMouseButtonUp (void)
{
	if (_DRO == NULL) return;
}


// --------------------------------------------------------------------------------------------------
// Maus bewegen, nachdem linke Maustaste gedrückt und eventl. wieder losgelassen wurde
void GeoEditExtension :: LMouseDrag (Point& Pt)
{
	if (_DRO == NULL || m_bHgrZeichnen1 || m_bHgrZeichnen2) return;

	MVWind() -> Draw (_DRO);	// alte Lage der aktuellen Strecke löschen durch invertiertes Neuzeichnen
	_DRO -> Process (Pt);		// Pt ist der Endpunkt der zu zeichnenden Linie (Anfangspunkt wurde
								// bei "new" vereinbart)
	MVWind() -> Draw (_DRO);	// Linie zeichnen
} // LMouseDrag


// --------------------------------------------------------------------------------------------------
// rechte Maustaste drücken
void GeoEditExtension :: RMouseButtonDn (void)
{
	if (_DRO == NULL) return;

	DELETE (_DRO);          // DrawObject freigeben
}


// --------------------------------------------------------------------------------------------------
// linke Maustaste für Verschiebung eines Stützpunktes gedrückt
void GeoEditExtension :: BandingStart (bool bVor, bool bNach)
{
	TX_ASSERT (m_pIOG);

short iOT;

	m_pIOG->GetObjTyp (&iOT);

	if (iOT != OT_KANTE || bVor)	// wird bei Anfangspunkt einer Kante übergangen
	{
		DELETE (_DRO1);
		_DRO1 = new DragLineObject (_PV);	// _PV ist der Anfangspunkt des Linienobjektes
		if (! _DRO1)
		{
			DEX_Error (RC_dragline_edit, EC_NOMEMORY);
			return;
		}
		_DRO1 -> ChangeRop (ROP_Invert);	// das von _DRO1 überzeichnete Gebiet wird invertiert
	}
	else
		_DRO1 = NULL;
		
	if (iOT != OT_KANTE || bNach)	// wird bei Endpunkt einer Kante übergangen
	{
		DELETE (_DRO2);
		_DRO2 = new DragLineObject (_PN);	// _PN ist der Anfangspunkt des Linienobjektes
		if (! _DRO2)
		{
			DEX_Error (RC_dragline_edit, EC_NOMEMORY);
			return;
		}
		_DRO2 -> ChangeRop (ROP_Invert);	// das von _DRO2 überzeichnete Gebiet wird invertiert
	}
	else
		_DRO2 = NULL;
} // BandingStart


// --------------------------------------------------------------------------------------------------
// die beiden angrenzenden (bzw. die eine angrenzende) Strecke mitziehen, wenn ein Stützpunkt
// verschoben wird
void GeoEditExtension :: Banding (Point& Pt)
{
	if (_DRO1)
	{
		MVWind() -> Draw (_DRO1);	// alte Lage der aktuellen Strecke löschen durch invertiertes Neuzeichnen
		_DRO1 -> Process (Pt);		// Pt ist der Endpunkt der zu zeichnenden Linie (Anfangspunkt wurde bei
									// "new" vereinbart)
		MVWind() -> Draw (_DRO1);	// Linie zeichnen
	}
	if (_DRO2)
	{
		MVWind() -> Draw (_DRO2);
		_DRO2 -> Process (Pt);
		MVWind() -> Draw (_DRO2);
	}
} // Banding


// --------------------------------------------------------------------------------------------------
// rechte Maustaste drücken
void GeoEditExtension :: BandingStop (void)
{
	DELETE (_DRO1);          // DrawObject freigeben
	DELETE (_DRO2);
}
