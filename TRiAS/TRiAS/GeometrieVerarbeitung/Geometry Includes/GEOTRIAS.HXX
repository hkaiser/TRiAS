// Funktionen für Übertragung der Objektgeometrien von und zu TRiAS
// File: GeoTrias.hxx
// W. Mörtl

#if !defined(_GEOTRIAS_HXX)
#define _GEOTRIAS_HXX

#if _TRiAS_VER < 0x0300
class CoordTransX;
#endif // _TRiAS_VER < 0x0300

// Anzahl der selektierten (markierten) Objekte in allen geöffneten Recherchefenstern
_GEOMETR_ENTRY BOOL _GEOMETR_EXPORT FAR PASCAL AnzSelektObjekte (long, BOOL, void* Anz);

// Fläche bilden
_GEOMETR_ENTRY EFlaeche* EFlaecheErzeugen (int iKCnt, KoOrd* pdblX, KoOrd* pdblY,
										   long* plCnt);

// Elementarobjekt erzeugen
_GEOMETR_ENTRY bool EObjektErzeugen (long lONr, EObjekt*& pEO, CoordTransX* pCT);

// Aus IObjektGeometrie ein Elementarobjekt (EPunkt, EKante, EFlaeche) rekonstruieren
_GEOMETR_ENTRY bool IObjGeometrieInEObj (IObjektGeometrie* pIOG, EObjekt*& pEO,
										 CoordTransX* pCT);

// Aus OBJGEOMETRIE ein Elementarobjekt (EPunkt, EKante, EFlaeche) rekonstruieren
_GEOMETR_ENTRY bool OBJGEOMETRIEinEObj (OBJGEOMETRIE* pOG, EObjekt*& pEO, CoordTransX* pCT, 
	IUnknown *pICS = NULL);

// Hilfsroutine für OBJGEOMETRIEinEObj() und IObjGeometrieInEObj()
bool KonvertierungInEObj (short iOTyp, short& iFlags, long lCnt, short iKCnt, void* pdblX,
	void* pdblY, long* plCnt, EObjekt*& pEO, CoordTransX* pCT, IUnknown *pICS = NULL);

// Geometrie eines Elementarobjektes (EPunkt, EKante, EFlaeche) in das Interface
// IObjektGeometrie einer ObjektGeometrie einspeichern
_GEOMETR_ENTRY bool EObjInIObjGeometrie (EObjekt* pEO, IObjektGeometrie* pIOG);

// Geometrie eines Elementarobjektes (EPunkt, EKante, EFlaeche) in Struktur OBJGEOMETRIE
// einspeichern
_GEOMETR_ENTRY bool EObjInOBJGEOMETRIE (EObjekt* pEO, int iObjTyp, OBJGEOMETRIE* pOG,
										bool bDblCoord);

// OBJGEOMETRIE eines GeoObjektes an TRiAS zurückgeben
_GEOMETR_ENTRY bool GeometrieAnTRIAS (GeoObjekt* pGO, SpForm sfSForm, long& lNeuONr,
									  CoordTransX* pCT = 0);
_GEOMETR_ENTRY bool GeometrieAnTRIASEx (HPROJECT hPr, GeoObjekt* pGO, SpForm sfSForm,
										long& lNeuONr, CoordTransX* pCT = 0);

// Test, ob Container des lONr-Objektes mit dem Container der aktuellen Sicht bzw. des
// Ausschnitts mindestens einen Punkt gemeinsam hat
bool ObjektInAusschnitt (long lONr);

#endif  // _GEOTRIAS_HXX
