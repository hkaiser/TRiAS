// Klassendefinitionen für Druckerausgabe -------------------------------------
// File: PRINTER.HXX

#if !defined(_PRINTER_HXX)
#define _PRINTER_HXX

#include <dblpair.hxx>
#include <prntpars.hxx>

#include "LayoutStyles.h"
#include "PrintBase.h"

///////////////////////////////////////////////////////////////////////////////
// declarations only
class PrinterErrorEvt;
class PrinterExposeEvt;
class PrintLayout;
class PrinterPars;
class CLegSizeCache;
class DatenBasisObjekt;
class IrisWind;

///////////////////////////////////////////////////////////////////////////////
// Druckfenster
class IrisPrinter : 
	public BandingPrinter,
	public CPrintBase
{
private:
	PrinterPars &m_rPD;

protected:
	BOOL PrinterError (PrinterErrorEvt);
	BOOL PrinterExpose (PrinterExposeEvt);

public:
// Konstruktor
		IrisPrinter (char *jobName, PrintLayout *pPL, DatenBasisObjekt &rDBO, PrinterPars &rPD);

// Memberfunktionen
	const char *DeviceName (void) { return m_rPD.DeviceName(); }
	const char *DriverName (void) { return m_rPD.DriverName(); }
	const char *PortName (void) { return m_rPD.PortName(); }
	PrinterPars &Pars (void) { return m_rPD; }

// cross_cast functions
	HDC Handle (Service s) { return BandingPrinter::Handle (s); }
	void DrawEx (DrawObject *pDO, DWORD dwData) { BandingPrinter::DrawEx(pDO, dwData); }
	pFont ChangeFont (pFont pF) { return BandingPrinter::ChangeFont(pF); }
	Rectangle CanvasRect() { return BandingPrinter::CanvasRect(); }
	
// sonstige Member
	class PrintAbort *m_pABox;

// Destruktor
		~IrisPrinter (void);
};

#endif // _PRINTER_HXX
