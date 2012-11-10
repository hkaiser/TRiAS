// Klassendefintionen fuer HashTabellen, die ElementNummern der uebersetzten
// Elemente enthalten
// File: HASHTABS.HXX

#if !defined(_HASHTABS_HXX)
#define _HASHTABS_HXX

const int HASHSIZE = 5003;	// Größe der HashTabelle

// speichert die ElementNummer übersetzter GDB-Elemente
class GDBElement {
protected:
	long _Nr;	// ElementNummer
	long _Nr2;

	DGeoObj *_pDGO;	// bereits ausgegebener Punkt

public:
// Konstruktor
		GDBElement (long Nr, long Nr2, DGeoObj * = NULL);
		~GDBElement (void);

	long &GDBNr (void) { return _Nr; }
	long GDBNr2 (void) { return _Nr2; }
	DGeoObj *CopyDGeoObj (void);
};

// HashTabellen für übersetzte GDB-Elemente
class GDBElementTab : public CHashTable {
protected:
	void UserDelete (void *);

public:
// Konstruktor
		GDBElementTab (void);
		~GDBElementTab (void);

// sonstige Member
	Bool FindOrEnter (long Nr, long Nr2, DGeoObj * = NULL);	
					// sucht und fügt ggf. ein
	DGeoObj *GetDGeoObj (long Nr, long Nr2); 
					// liefert Geometrie des Elementes

friend uint LongPairHash (void *pObj);
friend void *GetLongPairKey (void *pObj);
friend int LongPairCmp (void *PrimKey, void *SecKey);
};
DeclareLock (GDBElementTab, GDBElement);

#endif // _HASHTABS_HXX

