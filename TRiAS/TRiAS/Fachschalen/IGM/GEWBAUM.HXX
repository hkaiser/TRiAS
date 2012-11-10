// Klassendefinitionen fuer Identifikator-Baum ------------------------------------------
// File: GEWBAUM.HXX

#if !defined(_GEWBAUM_HXX)
#define _GEWBAUM_HXX

class TR_OCL {			// In Trias definierte Gew.Klassen
private:
	long _lIdent;
	long _lMCode;
	short _isValid;
	short _iDefine;
	class TR_OBJTree *_pOBJ;

public:
// Konstruktor/Destruktor
		TR_OCL (long Ident, long MCode ,short isValid, TR_OBJTree *pOBJ);

		~TR_OCL (void);

// ZugriffsFunktionen für IDBaum
friend void _XTENSN_EXPORT *GetID (void *pObj);
friend int _XTENSN_EXPORT CmpIDs (void *pObj1, void *pObj2);

	long &Ident ( void ) { return _lIdent; };
	long &MCode ( void ) { return _lMCode; };
	TR_OBJTree *OBJ ( void ) { return _pOBJ; };
	void StoreObj ( TR_OBJTree *pObj );
	void DeleteObj(void);
	short &Define ( void ) { return _iDefine; }
	short &isValid ( void ) { return _isValid; }
	void StoreValidation ( short isValid ) { _isValid = isValid; }
	void StoreDefinition ( short iDefine ) { _iDefine = iDefine; }

};

class TR_OCLTree : public CTree {
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
		TR_OCLTree (void);
		~TR_OCLTree (void);
};
DeclareLock (TR_OCLTree, TR_OCL);		// notwendige Klassendefinitionen

//-------------------------Objekte --------------------------------
//-----------------------------------------------------------------
class TR_OBJ {				// TRiAS - Objekte
private:
	long _lObject;
	char *_pGewNr;
	char *_pGewName;
	char *_pBez;
	long _lLaenge;
	long _lVon;
	long _lBis;
	long _lRechts;
	long _lHoch;
	long _lObjectIdent;
	short _iTyp;
	
public:
// Konstruktor/Destruktor
		TR_OBJ (long Object, char *pGewNr, short iTyp = 0);

		~TR_OBJ (void);

// ZugriffsFunktionen für OBJBaum
friend void _XTENSN_EXPORT *GetObject (void *pObj);
friend int _XTENSN_EXPORT CmpObjects (void *pObj1, void *pObj2);

	long &Object ( void ) { return _lObject; };
	long &ObjectIdent ( void ) { return _lObjectIdent; };
	long &Laenge ( void ) { return _lLaenge; };
	long &Von ( void ) { return _lVon; };
	long &Bis ( void ) { return _lBis; };
	long &Rechts ( void ) { return _lRechts; };
	long &Hoch ( void ) { return _lHoch; };
	short &Typ (void) { return _iTyp;};
	char *GewNr ( void ) { return _pGewNr; };
	char *GewName ( void ) { return _pGewName; };
	char *Bez ( void ) { return _pBez; };
	void StoreObjLaenge ( long lLen );
	void SetObjectIdent (long);
	void SetTyp( short iTyp) { _iTyp = iTyp;};
	void SpeichernGewaesserNummer ( char *);
	void SpeichernGewaesserName ( char *);
	void SpeichernBezeichnung ( char *);
	void SetIntervall ( long, long );
	void SetKoordinate ( long, long );
	bool GetIntervall ( long *, long *);
};

class TR_OBJTree : public CTree {
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
		TR_OBJTree (void);
		~TR_OBJTree (void);
};
DeclareLock (TR_OBJTree, TR_OBJ);		// notwendige Klassendefinitionen

/////////////////////////////////////////////////////////////////

//-------------------------Text/Symbol-Objekte --------------------------------
//-----------------------------------------------------------------
class TS_OBJ {				// TRiAS - Objekte
private:
	long _lObject;
	long _lStart;
	long _lEnde;
	short _iTyp;
	
public:
// Konstruktor/Destruktor
		TS_OBJ (long Object, long lStart, long lEnde);

		~TS_OBJ (void);

// ZugriffsFunktionen für OBJBaum
friend void _XTENSN_EXPORT *GetTObject (void *pObj);
friend int _XTENSN_EXPORT CmpTObjects (void *pObj1, void *pObj2);

	long &Object ( void ) { return _lObject; };
	long &Start ( void ) { return _lStart; };
	long &Ende ( void ) { return _lEnde; };
	void SetTextInformation(long, long);
	short &Typ (void) { return _iTyp;};
};

class TS_OBJTree : public CTree {
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
		TS_OBJTree (void);
		~TS_OBJTree (void);
};
DeclareLock (TS_OBJTree, TS_OBJ);		// notwendige Klassendefinitionen

/////////////////////////////////////////////////////////////////
//----------------------------------------------------------------
class KP_GEW {			// Kompakt-Gewaesser
private:
	LPSTR _pGewNr;
	LPSTR _pGewName;
	short _iHerkunft;
	short _iZuordnung;
	long _lONr;
	long _lCount;
	long _lCountKompakt;
	long _lBeginn;
	long _lEnde;
	long _lBeginnKompakt;
	long _lEndeKompakt;
	class KP_LATree *_pLA; 
	class KP_LATree *_pPA; 
	class TR_OBJTree *_pOBJ;
//-------Hilfsgroesse
	short _iPos;			// n-tes Objekt gleicher GewNr
	
public:
// Konstruktor/Destruktor
		KP_GEW ( GEWAESSER *l, KP_LATree *pLA);
		~KP_GEW (void);

// ZugriffsFunktionen für GEW_Baum
friend void _XTENSN_EXPORT *GetIdent (void *pObj);
friend int _XTENSN_EXPORT CmpIdents (void *pObj1, void *pObj2);

	char *GewNr (void) { return _pGewNr; };
	char *GewName (void) { return _pGewName; };
	short &GetPosition ( void ) { return _iPos;};
	void SetPosition ( short);
	long &Beginn (void) { return _lBeginn; };
	long &Ende (void ) { return _lEnde; };
	long &BeginnKompakt (void) { return _lBeginnKompakt; };
	long &EndeKompakt (void ) { return _lEndeKompakt; };
	long &Count (void) { return _lCount; };
	long &CountKompakt (void ) { return _lCountKompakt; };
	void AddCount (void ) { _lCount++; };
	void AddCountKompakt (void ) { _lCountKompakt++; };
	void TauscheZuKompakt (void );
	void TauscheZuTRiAS (void );
	void TRiASKompaktAbgleich (void );
	void KompaktTRiASAbgleich (void );
	void StoreCountKompakt ( long lCount ) { _lCountKompakt = lCount; };
	void StoreCount ( long lCount ) { _lCount = lCount; };
	void StoreBeginnKompakt ( long lBeginn ) { _lBeginnKompakt = lBeginn; };
	void StoreEndeKompakt ( long lEnde ) { _lEndeKompakt = lEnde; };
	void SetKompaktLen ( long lLen );
	void SetStartEndPunkt ( long,long);
	void StoreGewName ( char *);
	long &Objekt (void ) { return _lONr; };
	KP_LATree *LA ( void ) { return _pLA; };
	KP_LATree *PA ( void ) { return _pPA; };
	TR_OBJTree *GetOBJ ( void ) { return _pOBJ; };
	void SpeichereLeistung ( KP_LATree * pLA);
	void SpeicherePunkt ( KP_LATree * pPA);
	void SetOBJ ( TR_OBJTree *pOBJ);
	void SpeichereObjekt ( long lONr);
	void SpeichereObjektLaenge ( long lLen);
	void SetObjekt ( long lONr);
//---------------------------------------------------------------
};

class KPTree : public CTree {
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
		KPTree (void);
		~KPTree (void);
};
DeclareLock (KPTree, KP_GEW);		// notwendige Klassendefinitionen

/////////////////////////////////////////////////////////////////
//----------------------------------------------------------------
class KP_GEB {			// Kompakt-GewaesserBereiche
private:
	LPSTR _pGewNr;
	LPSTR _pObjKlasse;
	LPSTR _pObjBez;
	short _iIdentNr;
	short _iLRBeide;
	long _lONr;
	long _lPos;
	long _lBeginn;
	long _lEnde;
	double _dFlaeche;	
public:
// Konstruktor/Destruktor
		KP_GEB ( long lPos, long lONr, FLAECHENANABSCHNITTEN *l);
		~KP_GEB (void);

// ZugriffsFunktionen für GEB_Baum
friend void _XTENSN_EXPORT *GetArea (void *pObj);
friend int _XTENSN_EXPORT CmpAreas (void *pObj1, void *pObj2);

	char *GewNr (void) { return _pGewNr; };
	char *ObjKlasse (void) { return _pObjKlasse; };
	char *ObjBez (void) { return _pObjBez; };
	short &IdentNr (void) { return _iIdentNr; };
	short &LRBeide (void ) { return _iLRBeide; };
	long &Beginn (void) { return _lBeginn; };
	long &Ende (void ) { return _lEnde; };
	long &Pos (void) { return _lPos; };
	long &ONr (void) { return _lONr; };
	double &Flaeche (void) { return _dFlaeche; };

//---------------------------------------------------------------
};

class KPBTree : public CTree {
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
		KPBTree (void);
		~KPBTree (void);
};
DeclareLock (KPBTree, KP_GEB);		// notwendige Klassendefinitionen

//------------------------------------------------------------------
//----------------------LeistungsArten------------------------------
//------------------------------------------------------------------

class KP_LA {		// Klasse der KompaktDaten(Leistungen/Bauwerke)
private:
	long _lCount;		// Zaehler in der Kette
	LPSTR _pGewNr;
	LPSTR _pLeistung;
	LPSTR _pZuordnung;
	short _iHerkunft;
	short _iZuordnung;
	short _iLinksRechtsMitte;
	long _lBeginn;
	long _lEnde;
	long _lMeterOffen;
	long _lObjectIdent;
	double _dKostet;
	short _iRechnNr;
	long _lONr;
	double _dHoehe;
	LPSTR _pKurzText;
	LPSTR _pLangText;
	LPSTR _pComment;

// BauwerkeTeil
	LPSTR _pBauwBez;
	LPSTR _pBez1;
	LPSTR _pBez2;
	long _lHoch;
	long _lRechts;
	long _lAnlageNr;
	double _dBauwHoehe;
	double _dWasserSpDiff;
public:
// Konstruktor/Destruktor
		KP_LA ( long, KOMPAKTDATEN *);
		~KP_LA (void);

// ZugriffsFunktionen für IDBaum
friend void _XTENSN_EXPORT *GetArt (void *pObj);
friend int _XTENSN_EXPORT CmpArts (void *pObj1, void *pObj2);

	long &Count ( void ) { return _lCount; };
	char *Leistung (void) { return _pLeistung; };
	long &Beginn (void) { return _lBeginn; };
	long &Ende (void) { return _lEnde; };
	long &MeterOffen (void) { return _lMeterOffen; };
	long &ObjectIdent (void) { return _lObjectIdent; };
	short &RechnungsNr (void) {return _iRechnNr; };
	double &Hoehe ( void ) { return _dHoehe;};
	double &Kosten ( void ) { return _dKostet;};
	void SpeichereHoehe ( double dHoehe) { _dHoehe = dHoehe; };
	short &Herkunft (void) { return _iHerkunft; };
	short &Zuordnung (void) { return _iZuordnung; };
	void SpeichereObjekt (long lONr);
	long &Objekt(void) { return _lONr; };
//	Links/Rechts/Mitte
	short LinksRechtsMitte (void) { return _iLinksRechtsMitte; };
	void SetLinksRechtsMitte ( short);

//------BauwerksTeil---------------------------------
	char *BauwerksBez (void) { return _pBauwBez; };
	char *Bezeichner1 (void) { return _pBez1; };
	char *Bezeichner2 (void) { return _pBez2; };
	long &HochWert (void) { return _lHoch; };
	long &RechtsWert (void) { return _lRechts; };
	long &AnlageNr (void) { return _lAnlageNr; };
	double &BauwerksHoehe (void) { return _dBauwHoehe; };
	double &WasserSpiegelDiff ( void ) { return _dWasserSpDiff; };
	

};

class KP_LATree : public CTree {
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
		KP_LATree (void);
		~KP_LATree (void);
};
DeclareLock (KP_LATree, KP_LA);		// notwendige Klassendefinitionen

//------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////

class TR_IDM {			// In Trias definierte F.Klassen
private:
	long _lIdent;
	short _iTyp;
	class TR_IDOTree *_pOBJP;
	class TR_IDOTree *_pOBJLI;
	class TR_IDOTree *_pOBJLIA;
	class TR_IDOTree *_pOBJFI;
	class TR_IDOTree *_pOBJFIA;

public:
// Konstruktor/Destruktor
		TR_IDM (long Ident, short iTyp);

		~TR_IDM (void);

// ZugriffsFunktionen für IDBaum
friend void _XTENSN_EXPORT *GetIDM (void *pObj);
friend int _XTENSN_EXPORT CmpIDMs (void *pObj1, void *pObj2);

	long &Ident ( void ) { return _lIdent; };
	short &Typ(void) { return _iTyp; };
	TR_IDOTree *OBJP ( void ) { return _pOBJP; };
	TR_IDOTree *OBJLI ( void ) { return _pOBJLI; };
	TR_IDOTree *OBJLIA ( void ) { return _pOBJLIA; };
	TR_IDOTree *OBJFI ( void ) { return _pOBJFI; };
	TR_IDOTree *OBJFIA ( void ) { return _pOBJFIA; };
	void StoreObject( long,Relat);
	void SetTyp( short);
	void StoreKanteInnen(long);
	void StoreKanteInAus(long);
	void StoreFlaecheInnen(long);
	void StoreFlaecheInAus(long);
	void StorePunktInnen(long);
};

class TR_IDMTree : public CTree {
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
		TR_IDMTree (void);
		~TR_IDMTree (void);
};
DeclareLock (TR_IDMTree, TR_IDM);		// notwendige Klassendefinitionen

//-------------------------IDO-Objekte --------------------------------
//-----------------------------------------------------------------
class TR_IDO {				// TRiAS - Objekte
private:
	long _lObject;
	TR_IDMTree *_pIDM;
	
public:
// Konstruktor/Destruktor
		TR_IDO (long Object);

		~TR_IDO (void);

// ZugriffsFunktionen für OBJBaum
friend void _XTENSN_EXPORT *GetIDO (void *pObj);
friend int _XTENSN_EXPORT CmpIDOs (void *pObj1, void *pObj2);

	long &Object ( void ) { return _lObject; };
	TR_IDMTree *IDM (void) { return _pIDM;};
};

class TR_IDOTree : public CTree {
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
		TR_IDOTree (void);
		~TR_IDOTree (void);
};
DeclareLock (TR_IDOTree, TR_IDO);		// notwendige Klassendefinitionen

/////////////////////////////////////////////////////////////////

//OKSKlassen
//-----------------------------------------------------------------
class TR_OKS {				// TRiAS - Objekte
private:
	char * _pOKS;
	ulong _lIdent1;
	ulong _lIdent2;
	
public:
// Konstruktor/Destruktor
		TR_OKS (char *pOKS, ulong lIdent);

		~TR_OKS (void);

// ZugriffsFunktionen für OBJBaum
friend void _XTENSN_EXPORT *GetOKS (void *pObj);
friend int _XTENSN_EXPORT CmpOKSs (void *pObj1, void *pObj2);

	char *OKS ( void ) { return _pOKS; };
	ulong UIdent1 (void) { return _lIdent1;};
	ulong UIdent2 (void) { return _lIdent2;};
	void StoreSecondIdent ( ulong lIdent ) { _lIdent2 = lIdent;};

};

class TR_OKSTree : public CTree {
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
		TR_OKSTree (void);
		~TR_OKSTree (void);
};
DeclareLock (TR_OKSTree, TR_OKS);		// notwendige Klassendefinitionen

/////////////////////////////////////////////////////////////////


//-------------------------------------------------------------------------
//Datenquellenverwaltung
//-------------------ListContainer------------------------------------------

//  class für ObjClass-ListContainer
class DATACL {
private:
//  Attribute

	short _DATATyp;
	HPROJECT _DATAhPr;
	char _DATALong[128];
	char _DATAShort[128];

public:

//  Konstruktor/Destruktor
	DATACL ( short Typ, char * pLong, char *pShort, HPROJECT hPr);
	~DATACL (void);

//	Member

	char &DATALong ( void ) { return _DATALong[0]; };
	char &DATAShort ( void ) { return _DATAShort[0]; };
	short &DATATyp ( void ) { return _DATATyp; };
	HPROJECT &DATAhPr(void) { return _DATAhPr; };
};

//  Verwaltung einer ObjClass-Liste
class DATACLList : public CListContainer {

protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
//  Konstruktor/Destruktor
	DATACLList (void);
	~ DATACLList (void);
};

DeclareLock (DATACLList, DATACL);

////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
#endif // _GEWBAUM_HXX
