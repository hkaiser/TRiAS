// Funktionalität für Topologische Relationen
// File: TopoRelFunctions.h
// W. Mörtl

#if !defined(__TOPORELFUNCTIONS_H_)
#define __TOPORELFUNCTIONS_H_


#include "TopoRelR.h"

#include <ospace/com/iterenum.h>	// IEnum<LONG>
#include <ospace/std/set>			// LONG

#include "TopoRelDlg.h"				// TOPORELRESULT
#include "TopoRelRefDlg.h"			// MULTIREFRESULT


///////////////////////////////////////////////////////////////////////////////////////////////
// Declaration diverser Klassen
#if !defined(_ENUM_LONG_ENUMERATOR_DEFINED)
#define _ENUM_LONG_ENUMERATOR_DEFINED

DefineSortingEnumerator(LONG);		// definiert SEnumLONG
DefineEnumInputIterator(LONG);		// definiert InEnumLONG
DefineEnumOutputIterator(LONG);		// definiert OutEnumLONG 

#endif // _ENUM_LONG_ENUMERATOR_DEFINED



///////////////////////////////////////////////////////////////////////////////////////////////
class TopoRelFunc
{
public:

	// Konstruktor, Destruktor
		TopoRelFunc (void);
		~TopoRelFunc (void);
		
	long GetRefONr (void) const { return m_lRefONr; }

	void SetRefObjectsCount (long lRefObjCount) {m_lRefObjCount = lRefObjCount; }
	HRESULT PrepareAnalysis (InEnumLONG RefObject, TOPORELRESULT caRelationInfo,
							 MULTIREFRESULT caMultiRefInfo, bool bFirstRelObj);
	bool GetObjectRelation (long lONr);
	void CountPackets (long& lPacket);
	void BuildOutputObjects (IEnumLONG* pEnumOut, CComBSTR& bstrCapt, CComBSTR& bstrColor,
								OGCPosit& rgPosition);
	CComBSTR MessageNoObjects (void);
	bool IsObjectInTree (long lONr);


	HRESULT RelationObjObj_ONr (long lONr1, long lONr2, Relat* prTR);
	HRESULT RelationObjObj_Geom (IObjektGeometrie* pIOG1, IObjektGeometrie* pIOG2, Relat* prTR);
	HRESULT RelationObjObj2_ONr (LONG lONr1, LONG lONr2, UINT* puiTR);
	HRESULT RelationObjObj2_Geom (IObjektGeometrie* pIOG1, IObjektGeometrie* pIOG2, UINT* puiTR);
	HRESULT RelatObjekte_ONr (long lONr, Relat relTR, IEnumLONG** ppEnumOut);

private:
	CoordTransX m_CTX;
	ulong m_ulSelRelat;			// Bitmuster für ausgewählte Relationen
	bool m_bSepaWin;			// die Analyseergebnisse in separaten Recherchefenstern (true)
	long m_lRefObjCount;		// Anzahl der Bezugsobjekte
	int m_iReferenceType;		// gewählte Methode bei mehreren Bezugsobjekten
	long m_lLimitCnt;			// Anzahl der Bezugsobjekte für "mindestens", "höchstens" bzw. "exakt"
	EObjekt* m_pRefObj;			// aktuelles Bezugsobjekt
	long m_lRefONr;				// Objektnummer des aktuellen Bezugsobjektes
	ObjTyp m_iRefOT;			// Objekttyp des aktuellen Bezugsobjektes

	OGCPosit m_OGCRelat;		// OGC-Relation eines Objektes zu einem Bezugsobjekt
	ObjRechteck m_RefOC;		// Container des aktuellen Bezugsobjektes
	ObjNrBaum m_ONrWithin;		// Baum für Objektnummern der vollständig innerhalb liegenden,
	ObjNrBaum m_ONrContain;		//  vollständig überdeckenden,
	ObjNrBaum m_ONrOverlap;		//  teilweise überlappenden,
	ObjNrBaum m_ONrEnter;		//  kreuzenden oder hineinragenden,
	ObjNrBaum m_ONrTouch;		//  von außen berührenden,
	ObjNrBaum m_ONrEqual;		//  identischen
	ObjNrBaum m_ONrDisjoint;	//  vollständig außerhalb liegenden Objekte
	ObjNrBaum m_ONrRelat;		// gemeinsamer Baum für alle Nummern der Objekte, die die
								// ausgewählten Relationen erfüllen
	ObjNrBaum m_ONrUnclear;		// Baum für Objekte mit unklarer Relation

	bool m_bFirstRelObj;		// Abarbeitung des 1. Referenzobjektes (true)
	WExtendGeoRein m_wGeoRein;	// Interface für Ankopplung von GeoRein.ext	
	bool m_bGeoRein;			// Ankopplung von GeoRein.ext ist erfolgt (true)


	void SetRefONr (long lRefONr) { m_lRefONr = lRefONr; }

	bool BuildReferenceObject (void);
	void Relations (EObjekt* pEO, Posit& posLage);
	bool IsOutside (EObjekt* pEO, ObjTyp iOT, Posit& posLage);
	void TRiAStoOGCRelations (EObjekt* pEO, Posit posLage);
	Posit OGCtoTRiASRelations (OGCPosit ogsLage);
	void StoreObjectNumber (long lONr);
	bool IsMultiRefCondition (long lFrequencyCnt);
	void TransferResults (int iRel, ObjNrBaum& ONrTree, IEnumLONG* pOutput);
	bool IsTreeContentValid (int iRel, ObjNrBaum& ONrTree);
	bool ProcessCompleteView (ulong ulSelRelat);
	bool OutsideObjects (void);
	HRESULT GeoReinInterface (void);
};

#endif // !defined(__TOPORELFUNCTIONS_H_)
