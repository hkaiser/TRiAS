// Funktionen für allgemeinen Geometriefehler
// File: GEOFEHL.CXX
// W. Mörtl


#include "GeoReinP.hxx"



//-------------------------------------------------------------------------------------------------
GeoFehler :: GeoFehler (EObjekt& GO)
		   : _GO (GO)	// Initialisierung des Datenelements _GO, das den Verweis auf
						// das aufrufenden EObjekt liefert (s. geofehl.hxx)
{
	_isCorrected = false;	// Fehler ist noch nicht bereinigt
}


//-------------------------------------------------------------------------------------------------
GeoFehler :: GeoFehler (EObjekt& GO, bool isCorrected)
		   : _GO (GO)
{
	_isCorrected = isCorrected;
}


//-------------------------------------------------------------------------------------------------
GeoFehler :: GeoFehler (GeoFehler& GF)
		   : _GO (GF._GO) 
{
	_isCorrected = GF._isCorrected;
}


//-------------------------------------------------------------------------------------------------
GeoFehler :: ~GeoFehler (void) 
{
}
