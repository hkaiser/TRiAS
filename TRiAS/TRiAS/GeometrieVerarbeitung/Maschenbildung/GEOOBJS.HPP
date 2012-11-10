/*
Datei: GEOOBJS.HPP

Realisiert die Verwaltung der typspezifischen Objektgeometrien.
*/

#ifndef _GEOOBJS_HPP
#define _GEOOBJS_HPP

#ifndef _NO_OBJECT_GEOMETRIE
DefineSmartInterface (ObjektGeometrie);
#endif

class CCompareObjects;
//	CGeometrieObject ----------------------------------------------------------
class CGeometrieObject
{
public:
//	Attribute
	BOOL m_bIsDoppelt;
	WObjektGeometrie m_wIObjGeo;					// Interface-Wrapper
	
//	Konstruktor/Destruktor
	CGeometrieObject ();							//	default Konstruktor
	CGeometrieObject (const CGeometrieObject &);	//	Copy-Konstruktor
	CGeometrieObject (long lObjektNummer);
	
//	allgemeine Funktionen
	HRESULT GetInterface (IObjektGeometrie **ppIOG);
	
//	lese Objektnummer
	long GetObjNummer (void);

//	durch STL geforderte Operatoren
	BOOL operator < (const CGeometrieObject &) const { return FALSE; }

//	durch STL benutzte Operatoren
	BOOL operator = (const CGeometrieObject &);
	BOOL operator == (const CGeometrieObject &) const { return FALSE; }

	friend class CCompareObjects;
};

//	CCompareObjects ------------------------------------------------------------
class CCompareObjects
{
private:
//	Attribute
	BOOL m_bIsFlaeche;
	IEnumObjectsByNumber *m_pIEnumObjs;					//	Objektnummern-Ausgabe-Strom
	long *m_pX;
	long *m_pY;
	long *m_lpCnt;
	long m_lCnt;
	short m_sKCnt;

protected:
	void GetGeometrie (CGeometrieObject &Object, long **ppX, long **ppY, long *lpCnt, 
					   short *spKCnt = NULL, long **lppCnt = NULL);
	
public:
//	Konstruktor/Destruktor
	CCompareObjects (IEnumObjectsByNumber *);

//	Init-Funktion
	void Init (CGeometrieObject &, BOOL bIsFlaeche = FALSE); // lese zu vergleichende Geometrie

//	operator
	void operator ()(CGeometrieObject &);		// Vergleich der Objekte
};

#endif			// _GEOOBJS_HPP

