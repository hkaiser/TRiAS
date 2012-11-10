// Profile-Routinen, die intelligent die Maße des Drucklayouts berechnen ------
// File: PRLAYOUT.HXX

#if !defined(_PRLAYOUT_HXX)
#define _PRLAYOUT_HXX

#include "prlaytyp.hxx"

class CLegSizeCache {		// Cache für LegendenGrößen
private:
	unsigned int m_fIsPrinter : 1;	// ist eine DruckLegende
	class CPrintLegLayout *m_pPrLayout;

	long m_lBaseX;
	long m_lBaseY;

public:
		CLegSizeCache (void);
		~CLegSizeCache (void);

	bool FInit (PrinterPars &rPP);	// für DruckLegende rufen, sonst nicht
	bool Refresh (void);
	void SetBaseValues (long lBaseX, long lBaseY);

///////////////////////////////////////////////////////////////////////////////
// Zugriff auf Größen innerhalb der Legende (alle fürs Layout in mm)
	long LegendeBreite (long lDefault, long lBase);		// in mm !!
	long MasstabHoehe (long lDefault, long lBase);		// in mm !!
	long UeberschriftBreite (long lDefault, long lBase);	// in mm !!
	long UeberschriftHoehe (long lDefault, long lBase);	// in mm !!
	long LogoHoehe (long lDefault, long lBase, int iCnt);	// in mm !!

///////////////////////////////////////////////////////////////////////////////
// Zugriff auf sonstige Attribute innerhab einer Legende (alle in Pixel - devicedependent)
	long UeberschriftTyp (long lDefault);
	bool LogoText (string &str);

	long LegendeVorHoehe (long lDefault);		// in pix !!
	long LegendeNachHoehe (long lDefault);		// in pix !!

	long LegendeKopfVorHoehe (long lDefault);	// in pix !!
	long LegendeKopfNachHoehe (long lDefault);	// in pix !!
	bool LegendeKopfFont (int &iFam, string &strName, int &iSizeY, 
			      bool &fB, bool &fI, bool &fU);

// ein LegendenEintrag
	bool KastenFont (int &iFam, string &strName, int &iSizeY, 
			 bool &fB, bool &fI, bool &fU);
	long KastenVorBreite (long lDefault);		// in Pixel
	long KastenNachBreite (long lDefault);		// in Pixel
	long KastenVorHoehe (long lDefault);		// in Pixel
	long KastenNachHoehe (long lDefault);		// in Pixel

	long LeerzeileHoehe (long lDefault);		// in Pixel

// Maßstabsbereich	
	bool MasstabFont (int &iFam, string &strName, int &iSizeY, 
			  bool &fB, bool &fI, bool &fU);
	bool MasstabDesc (string &rstr);
	long MeanderDicke (long lDefault);		// StrichDicke in 0.01mm
	long MasstabVorHoehe (long lDefault);		// in pix !!
	long MasstabZwischenHoehe (long lDefault);	// in pix !!
	long MasstabNachHoehe (long lDefault);		// in pix !!

// FirmenLogos (bis zu MAX_LOGOFELD Bereiche am unteren LegendenRand)
	long LogoFeldHoehe (long lDefault, LEGLAYOUT_SUB_ITEM rgPos, int iCnt);
	long LogoFeldBreite (long lDefault, LEGLAYOUT_SUB_ITEM rgPos, int iCnt);
	bool LogoFeldFont (int &iFam, string &strName, int &iSizeY, 
			   bool &fB, bool &fI, bool &fU, 
			   LEGLAYOUT_SUB_ITEM rgPos, int iCnt);
	bool LogoFeldDesc (string &rstr, LEGLAYOUT_SUB_ITEM rgPos, int iCnt);
	bool LogoFeldOpaque (int iCnt);

	long LogoVorBreite (long lDefault);
	long LogoZwischenBreite (long lDefault);
	long LogoNachBreite (long lDefault);
	long LogoVorHoehe (long lDefault);
	long LogoZwischenHoehe (long lDefault);
	long LogoNachHoehe (long lDefault);

// workaround für internal compiler error
	long KastenBreite (long lDefault);		// in Pixel
	long KastenZwischenBreite (long lDefault);	// in Pixel
	long KastenHoehe (long lDefault);		// in %

// spezielle, nicht dokumentierte Einträge
	bool NoTRiASLogo (void);
};

#endif // _PRLAYOUT_HXX
