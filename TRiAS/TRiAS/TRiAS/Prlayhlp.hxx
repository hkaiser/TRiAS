// Helperklasse für LegendenLayout --------------------------------------------
// File: PRLAYHLP.HXX

#if !defined(_PRLAYHLP_HXX)
#define _PRLAYHLP_HXX

#include "prlaytyp.hxx"

#define A4_WIDTH	19000L
#define A4_HEIGHT	27700L
#define A0_WIDTH	82100L
#define A0_HEIGHT	116900L

typedef double (GETKOEFFPROC)(long);

GETKOEFFPROC FKoeffX;
GETKOEFFPROC FKoeffY;

class CPrintLegLayout {
private:
	string m_strFile;
	string m_strPrjFile;
	string m_strBuffer;
	LEGLAYOUT_FORMAT m_rgFormat;	// Papierformat
	GETKOEFFPROC *m_pFKoeffX;
	GETKOEFFPROC *m_pFKoeffY;

	PrinterPars &m_rPP;
	DoublePair m_dimDots;
		
	bool ReadString (string &strkey);
	bool ReadLongs (string &strKey, long &rlA4, long &rlA0);
	pFont MakeFont (int iFam, LPCSTR pcName, long lSize,
			bool fBold, bool fItalic, bool fUnderline);

protected:
	bool ReadLongsX (string &strKey, long &rlA4, long &rlA0);
	bool ReadLongsY (string &strKey, long &rlA4, long &rlA0);
	bool ReadValue (string &strKey, long &rlValue);
	
	long Height (void);
	long Width (void);

public:
		CPrintLegLayout (PrinterPars &rPP);
		~CPrintLegLayout (void);

static CPrintLegLayout *CreateInstance (PrinterPars &rPP);

	bool FInit (void);

	bool GetFont (long lBase, LEGLAYOUT_ITEM rgItem, 
		      int &iFam, string &strName, int &iSizeY,	// liefert Fontparameter
		      bool &fBold, bool &fItalic, bool &fUnderline,
		      int iCnt = 0);

	long GetValueXMM (long lDefault, long lBase, LEGLAYOUT_ITEM rgItem,
			  LEGLAYOUT_POSITION rgPos = LL_POSITION_None, 
			  LEGLAYOUT_ATTRIBUTE rgAttr = LL_ATTRIBUTE_Breite,
			  int iCnt = 0);
	long GetValueX (long lDefault, long lBase, LEGLAYOUT_ITEM rgItem, 		// liefert Breite
			LEGLAYOUT_POSITION rgPos = LL_POSITION_None, 
			LEGLAYOUT_ATTRIBUTE rgAttr = LL_ATTRIBUTE_Breite, 
			int iCnt = 0);
	long GetValueYMM (long lDefault, long lBase, LEGLAYOUT_ITEM rgItem,
			  LEGLAYOUT_POSITION rgPos = LL_POSITION_None, 
			  LEGLAYOUT_ATTRIBUTE rgAttr = LL_ATTRIBUTE_Hoehe,
			  int iCnt = 0);
	long GetValueYAbs (long lDefault, long lBase, LEGLAYOUT_ITEM rgItem, 
			   LEGLAYOUT_POSITION rgPos, LEGLAYOUT_ATTRIBUTE rgAttr);
	long GetValueY (long lDefault, long lBase, LEGLAYOUT_ITEM rgItem, 		// liefert Höhe
			LEGLAYOUT_POSITION rgPos = LL_POSITION_None, 
			LEGLAYOUT_ATTRIBUTE rgAttr = LL_ATTRIBUTE_Breite,
			int iCnt = 0);

	bool GetString (string &rstr, LEGLAYOUT_ITEM rgItem,
			LEGLAYOUT_POSITION rgPos = LL_POSITION_None, 
			LEGLAYOUT_ATTRIBUTE rgAttr = LL_ATTRIBUTE_None,
			int iCnt = 0);

	long GetSingleValue (long lDefault, LEGLAYOUT_ITEM rgItem,
			LEGLAYOUT_POSITION rgPos = LL_POSITION_None, 
			LEGLAYOUT_ATTRIBUTE rgAttr = LL_ATTRIBUTE_None,
			int iCnt = 0);

// spezielle, nicht dokumentierte Einträge 
	bool NoTRiASLogo (void);

// sonstige HilfsFunktionen
	bool Refresh (void);
#if defined(_DEBUG)
	double kX (long lBase);
	double kY (long lBase);
#else
	double kX (long lBase) { return (*m_pFKoeffX)(lBase); }
	double kY (long lBase) { return (*m_pFKoeffY)(lBase); }
#endif // _DEBUG
};

#endif // _PRLAYHLP_HXX
