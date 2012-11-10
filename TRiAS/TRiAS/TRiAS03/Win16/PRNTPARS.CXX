// Memberfunktionen für DruckerParameterKlasse --------------------------------
// File: PRNTPARS.CXX

#include "trias03p.hxx"

#include <dblpair.hxx>
#include <prntpars.hxx>

// Informationsfunktionen -----------------------------------------------------
// Feststellen der Anzahl der Dots per mm -------------------------------------
DoublePair PrinterPars :: GetDotsPerMM (void) 
{
// Drucker InformationContext
HDC hDCInfo = CreateIC((LPSTR)DriverName(), (LPSTR)DeviceName(), 
		       (LPSTR)PortName(), DeviceMode());
// Geräteeigenschaften holen
int HorzSize = GetDeviceCaps (hDCInfo, HORZSIZE);       // Breite in mm
int VertSize = GetDeviceCaps (hDCInfo, VERTSIZE);       // Höhe in mm
int HorzRes = GetDeviceCaps (hDCInfo, HORZRES);         // Breite in Dots
int VertRes = GetDeviceCaps (hDCInfo, VERTRES);         // Höhe in Dots

	DeleteDC (hDCInfo);

return DoublePair ((double)HorzRes/(double)HorzSize, 
		   (double)VertRes/(double)VertSize);
}

// ObjektContainer entsprechend der AspectRatio eines Ausgabegerätes korrigieren
Point PrinterPars :: GetAspectRatio (void) 
{
// Drucker InformationContext
HDC hDCInfo = CreateIC((LPSTR)DriverName(), (LPSTR)DeviceName(), 
		       (LPSTR)PortName(), DeviceMode());
// Geräteeigenschaften holen
int LogPixelsX = GetDeviceCaps (hDCInfo, LOGPIXELSX);
int LogPixelsY = GetDeviceCaps (hDCInfo, LOGPIXELSY);

	DeleteDC (hDCInfo);

return Point (LogPixelsX, LogPixelsY);
}


// Liefert Größe der Druckseite in mm -----------------------------------------
Dimension PrinterPars :: GetPageSize (void) 
{
// Drucker InformationContext
HDC hDCInfo = CreateIC((LPSTR)DriverName(), (LPSTR)DeviceName(), 
		       (LPSTR)PortName(), DeviceMode());
// Geräteeigenschaften holen
int HorzSize = GetDeviceCaps (hDCInfo, HORZSIZE);       // Breite in mm
int VertSize = GetDeviceCaps (hDCInfo, VERTSIZE);       // Höhe in mm

	DeleteDC (hDCInfo);

return Dimension (HorzSize, VertSize);
}

