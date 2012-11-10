// Kompakt-Header
// File KOMPHEAD.HXX

#if !defined(_KOMPHEAD_HXX)
#define _KOMPHEAD_HXX

class KompaktHeader {
protected:
	short _isValid;
//-----GewaesserDaten--------------------------------------
	TR_OCLTree *_pGewClass;
	ulong _MCGewNr;
	ulong _MCGewKl;
	ulong _MCGewName;
	long _lProzentL;
// KK010809
	long _lSchrittweite;
	long _lPuffer;


	bool _iProzFlag;
//------ReferenzDaten
	ulong _RFGewNr;
	ulong _RFGewName;

//-----BauwerksDaten--------------------------------------
	TR_OCLTree *_pBauwClass;
	ulong _MCBauwNr;
	ulong _MCBauwKl;
	ulong _MCBauwName;
	ulong _MCBauwAnfStat;
	ulong _MCBauwEndStat;
	ulong _MCBauwAnlNr;
	ulong _MCBauwBez;
	ulong _MCBauwStauziel;
	ulong _MCBauwWasserSp;
	ulong _MCBauwSensib;
	ulong _MCBauwArt;
	ulong _MCBauwLeist;

//------ReferenzDaten
	ulong _RFBauwNr;
	ulong _RFBauwName;

//------Einzugsgebiete/Hydraulik---------------------------
	TR_OCLTree *_pHydrClass;
	ulong _MCHydrHoehe;
	ulong _MCHydrKl;
	ulong _MCHydrWert;

//------ReferenzDaten
	ulong _RFHydrHoehe;
	ulong _RFHydrWert;


//------Flaechendaten--------------------------------------
	TR_OCLTree *_pFlaClass;
	ulong _MCFlaKl;

//--------Counter-----------------------------------------
	long _lGewCount;
	long _lBWCount;

	ResourceFile *_pResTarget;

	char * _pLocProt;

#if _MSC_VER >= 1100
	HPROJECT _hPr;
#endif

public:
		KompaktHeader ( ResourceFile *pResTarget);
		~KompaktHeader (void);

//Member
	short isValid ( void ) { return _isValid; };
	void SetValidation ( char * );

#if _MSC_VER >= 1100
	HPROJECT HKompaktProject( void ) { return _hPr; };
	void SetKompaktProject( HPROJECT hPr ) { _hPr = hPr; };
#endif

	void CleanOKS(void);
	void OKSCleaner ( ulong, ulong);

	void Aktualisieren (short);
	bool GetHeaderInformation ( void );
	bool GetHeaderClassInformation ( void );
	bool GetHeaderTypInformation ( short );
	char *GetHeaderTypEintrag ( short );
	bool SetHeaderInformation ( void );
	bool SetHeaderClassInformation ( void );
	bool SetHeaderTypInformation ( short );
	bool ErfasseAltInformationen(short);
	void AktualisiereIdentMerkmal (long,ulong,char*);
/////////////////////////////////////////////////////////////
	bool Name ( char *, short lLen);
	long GewaesserCount ( void );
	long BauwerkeCount ( void );
/////////////////////////////////////////////////////////////
	bool ClassHeaderAnalyse(ulong*,ulong*,ulong*,ulong*,char *);
	bool AktualisiereHeaderParameter(ulong*,ulong*,ulong*,ulong*);
	ulong GetHeaderMCode ( char *);

#if _MSC_VER >= 1100
	long KP_GetUniqueSysMCodeEx ( HPROJECT hPr);
#endif

	void SetPBDMCode ( long , ResString ,short);
	void SetPBDIDCode ( short, long );
	void SetPBDObjectCode (short );
	void LadeObjektCode ( short);
	void LadeObjektMCode ( short);
	char *HoleIdentMerkmal ( long, ulong);
	void BestimmeMerkmalsKode ( short, char *);
	bool BestimmeAltMerkmalsKode ( short, char *);
	void TauscheMerkmal ( short );
	void BestimmeBauwerke ( char *);
	TR_OCLTree *LadeKompaktKlassen ( ulong, short);
//---GewaesserDaten--------------------------------------
	TR_OCLTree * GewClass ( void ) { return _pGewClass; }
	ulong &CodeGewNr (void) { return _MCGewNr; }
	ulong &CodeGewKl (void) { return _MCGewKl; }
	ulong &CodeGewName (void) { return _MCGewName; }
	long &GewDiffLaenge (void) { return  _lProzentL; }
// KK010726
	bool &GewDiffProzent (void) { return  _iProzFlag; }
	void SetGewDiffProzent (bool iFlag) { _iProzFlag = iFlag; }
// KK010809
	long &GewSchrittweite (void) { return  _lSchrittweite; }
	long &GewPuffer (void) { return  _lPuffer; }
	void SetGewSchrittweite (long lWert) { _lSchrittweite = lWert; }
	void SetGewPuffer (long lWert) { _lPuffer = lWert; }

	void StoreGewDiffLaenge (long lLen) { _lProzentL = lLen; }
	void StoreCodeGewNr ( ulong lGewNr ) { _MCGewNr = lGewNr; }
	void StoreCodeGewName ( ulong lGewName ) { _MCGewName = lGewName; }
	void StoreGewClass ( TR_OCLTree *);
	void DeleteGewClass ( void );
//----BauwerksDaten--------------------------------------
	TR_OCLTree * BauwClass ( void ) { return _pBauwClass; }
	ulong &CodeBauwNr (void) { return _MCBauwNr; }
	ulong &CodeBauwKl (void) { return _MCBauwKl; }
	ulong &CodeBauwName (void) { return _MCBauwName; }
	ulong &CodeBauwAnfStat (void) { return _MCBauwAnfStat; };
	ulong &CodeBauwEndStat (void) { return _MCBauwEndStat; };
	ulong &CodeBauwAnlNr (void) { return _MCBauwAnlNr; };
	ulong &CodeBauwBez (void) { return _MCBauwBez; };
	ulong &CodeBauwStauziel (void) { return _MCBauwStauziel; };
	ulong &CodeBauwWasserSpiegel (void) { return _MCBauwWasserSp; };
	ulong &CodeBauwSensib (void) { return _MCBauwSensib; };
	ulong &CodeBauwArt (void) { return _MCBauwArt; };
	ulong &CodeBauwLeist (void) { return _MCBauwLeist; };

	void StoreBauwAnfStat (ulong lAnfStat) { _MCBauwAnfStat = lAnfStat; };
	void StoreBauwEndStat (ulong lEndStat) { _MCBauwEndStat = lEndStat; };
	void StoreBauwAnlNr ( ulong lAnlNr) { _MCBauwAnlNr = lAnlNr; };
	void StoreBauwBez (ulong lBez) { _MCBauwBez = lBez; };
	void StoreBauwStauziel (ulong lStau) { _MCBauwStauziel = lStau; };
	void StoreBauwWasserSpiegel (ulong lWasserSp) { _MCBauwWasserSp = lWasserSp; };
	void StoreBauwSensib (ulong lSens) { _MCBauwSensib = lSens; };
	void StoreBauwArt (ulong lArt) { _MCBauwArt = lArt; };

	void StoreCodeBauwNr ( ulong lBauwNr ) { _MCBauwNr = lBauwNr; }
	void StoreCodeBauwName ( ulong lBauwName ) { _MCBauwName = lBauwName; }
	void StoreBauwClass ( TR_OCLTree *);
	void DeleteBauwClass ( void);

	//-----HydraulikDaten---------------------------------------
	TR_OCLTree * HydrClass ( void ) { return _pHydrClass; }
	ulong &CodeHydrWert (void) { return _MCHydrWert; }
	ulong &CodeHydrKl (void) { return _MCHydrKl; }
	ulong &CodeHydrHoehe (void) { return _MCHydrHoehe; }
	void StoreCodeHydrWert ( ulong lHydrWert ) { _MCHydrWert = lHydrWert; }
	void StoreCodeHydrHoehe ( ulong lHydrHoehe ) { _MCHydrHoehe = lHydrHoehe; }
	void StoreHydrClass ( TR_OCLTree *);
	void DeleteHydrClass ( void);

	//-----FlaechenDaten---------------------------------------
	TR_OCLTree * FlaClass ( void ) { return _pFlaClass; }
	ulong &CodeFlaKl (void) { return _MCFlaKl; }
	void StoreFlaClass ( TR_OCLTree *);
	void DeleteFlaClass ( void);


// Bauwerke
	void SetzeBauwerkeKlassen(void);
	void BildeBauwerkeKlassen(short,short);
// Leistungen
	void SetzeLeistungsKlassen(void);
	void SetzeLeistungsEinzelKlasse(short);
	void BildeLeistungsKlassen(short,short);
// Topographie+Schutzgebiete+Grenzen
	void SetzeTopKlassen(void);
	void BildeTopKlassen(char *,char *);
// Gewaesser
	void SetzeGewaesserKlassen(void);
	void BildeGewaesserKlassen(long,char *);
// Hydraulik
	void SetzeHydraulikKlassen(void);
	void BildeHydraulikKlassen(short,short);
//-----------------------------------------------------------
};

#endif 	// _KOMPHEAD_HXX
