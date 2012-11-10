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

bool PrinterPars::InitFromDefaultPrinter (void)
{
	Tidy();
	return PrintingDevice::InitFromDefaultPrinter (&m_ptd); 
}

/*
 * TargetDeviceCopy
 *
 * Purpose:
 *  Duplicate a DVTARGETDEVICE structure, allocating new memory
 *  for the copy which the caller must free with CoTaskMemFree.
 *
 * Parameters:
 *  ptdSrc          DVTARGETDEVICE * to copy
 *
 * Return Value:
 *  DVTARGETDEVICE * to the copy, NULL if copy fails or ptdSrc
 *                  is NULL.
 */

DVTARGETDEVICE *TargetDeviceCopy (DVTARGETDEVICE *ptdSrc)
{
DVTARGETDEVICE *ptdDest = NULL;

    if (NULL == ptdSrc)
	    return NULL;

    ptdDest = (DVTARGETDEVICE *)CoTaskMemAlloc (ptdSrc->tdSize);
    if (NULL != ptdDest)
        memcpy (ptdDest, ptdSrc, (size_t)ptdSrc->tdSize);

	return ptdDest;
}

bool PrinterPars::InitFromData (DVTARGETDEVICE *pdvt)
{
	Tidy();
	m_ptd = TargetDeviceCopy (pdvt);
	return PrintingDevice::InitFromData (m_ptd);
}

bool PrinterPars::SetUp (void)
{
	Tidy();
	return PrintingDevice::SetUp (&m_ptd);
}

