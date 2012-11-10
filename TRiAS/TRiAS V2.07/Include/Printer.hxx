// Klassendefinitionen für Druckerausgabe -------------------------------------
// File: PRINTER.HXX

#if !defined(_PRINTER_HXX)
#define _PRINTER_HXX

#if !defined(LAYOUTSTYLES)
#define LAYOUTSTYLES

#define MAX_LOGOFELD	4		// Anzahl der FirmenLogoBereiche

enum FrameStyle {
	FSNoFrame,		// kein Rahmen
	FSSimpleFrame,		// einfache dünne Linie
	FSThickFrame,		// einfache dicke Linie
	FSDoubleFrame,		// innen dünn außen dick
	FSTripleFrame,		// dünn-dick-dünn
};

enum LegendStyle {
	LSNoLegend,		// keine Legende
	LSSimpleLegend,		// normale Legende
};

enum MasstabStyle {
	MSNoMasstab,		// keine Maástabsausgabe
	MSSimpleMasstab,	// einfaches ZahlenFormat
};
#endif

#include <dblpair.hxx>

#if !defined(_PRNTPARS_HXX)
#include <prntpars.hxx>
#endif 

// Druckerfenster -------------------------------------------------------------
#if !defined(NOIRISPRINTER)
class PrinterErrorEvt;		// nur Deklarieren
class PrinterExposeEvt;
class PrintLayout;
class PrinterPars;
class CLegSizeCache;

class IrisPrinter : public BandingPrinter {
private:
	PrinterPars &m_rPD;
	DatenBasisObjekt &m_rDBO;
	CIdTree &m_Idents;
	PBD_DB &m_pbdDB;

// FormatierungsDaten
	DoublePair m_DotsPerMM;
	Point m_Aspect;

// AusgabeLayout
	Rectangle m_ActRect;
	ObjContainer m_Extend;
	Rectangle m_RcLegende, m_RcMasstab, m_RcFrame, m_RcHeadLine;
	FrameStyle m_fsFrame;
	LegendStyle m_lsLegende;
	MasstabStyle m_msMasstab;
	char *m_lpHeadLine;
	long m_lMasstab;

	Rectangle m_rcPageSize;		// gesamter Druckbereich
	Rectangle m_rcPageBase;		// BezugsMaße (gesamtes Papier)

	Rectangle m_rcLogo;		// LogoBereich (Überschrift)

	Rectangle m_rcFirmLogos[MAX_LOGOFELD];	// FirmenLogos (unten)
	bool m_fLogos[MAX_LOGOFELD];

	unsigned short m_iHeadLine : 1;
	unsigned short m_fLogo : 1;
	unsigned short m_fRounded : 1;
	unsigned short m_fLegendOnly : 1;

protected:
	bool PrinterError (PrinterErrorEvt);
	bool PrinterExpose (PrinterExposeEvt);

	bool CalcLinksObenRect (CLegSizeCache &rCache, Rectangle &rRc, int iCnt, Rectangle *prc);
	bool CalcRechtsObenRect (CLegSizeCache &rCache, Rectangle &rRc, int iCnt, Rectangle *prc);
	bool CalcLinksUntenRect (CLegSizeCache &rCache, Rectangle &rRc, int iCnt, Rectangle *prc);
	bool CalcRechtsUntenRect (CLegSizeCache &rCache, Rectangle &rRc, int iCnt, Rectangle *prc);

	bool PaintTextRect (LPCSTR pcText, int rgPos,
			Rectangle &rRc, int iFamily, LPCSTR pcFont, int iSizeY, 
			bool fBold, bool fItalic, bool fUnderline, bool fOpaque);

public:
// Konstruktor
		IrisPrinter (char *jobName, PrintLayout *, 
			DatenBasisObjekt &rDBO, PrinterPars &rPD);

// Memberfunktionen
	const char *DeviceName (void) { return m_rPD.DeviceName(); }
	const char *DriverName (void) { return m_rPD.DriverName(); }
	const char *PortName (void) { return m_rPD.PortName(); }
	PrinterPars & Pars (void) { return m_rPD; }

	HDC Handle (Service s) { return BandingPrinter :: Handle (s); }

// Druckfunktionen
	Point PrintLegend (IrisWind *pW, Rectangle &R, DoublePair &D, int i);
	void PrintMasstab (Rectangle &, DoublePair &, Point &);
	void PrintRefPoint (Punkt &P, DoublePair &D) const;
	char *CnvrtOCtoRC (char *Str, int Len, KoOrd X, KoOrd Y);
	void PaintHeadLine (Rectangle &, LPCSTR pText);
	void PaintMasstab (CLegSizeCache &rCache);
	void PaintRahmen (Rectangle &rRC, int iWidth);	// Breite in 1/100 mm
	void FillRahmen (Rectangle &rRC);
	void PaintEdges (Rectangle &rRC);
	void PaintMeander (HDC hDC, int iTyp, Point pt, int dX, int dY, int iWidth, long lMax, int iZ, int iLine);
	void PaintFirmLogo (CLegSizeCache &rCache, Rectangle &rc, int iCnt);
	bool PaintFirmLogoFeld (CLegSizeCache &rCache, Rectangle &rRc, 
				int rgPos, int iCnt, bool fOpaque);
	void PaintTRiASLogo (Rectangle &rRC);

// sonstige Member
//	Window *m_oldCurrActW;
	class PrintAbort *m_pABox;
	class CLegendeObjekt *m_pLO;

// Destruktor
		~IrisPrinter (void);
};
#endif // NORIRISPRINTER

#endif // _PRINTER_HXX
