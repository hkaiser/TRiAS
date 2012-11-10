// Klassendefintion fuer Komplexobjekte ---------------------------------------
// File: KOMPLEX.HXX

#if !defined(_KOMPLEX_HXX)
#define _KOMPLEX_HXX

#if !defined(NOKOMPLEXOBJEKT)
class KomplexObjekt : public GeoObjekt {
private:
	long _RCode;	// RelationsCode in diesem Komplexobjekt
	ObjFeld *_pOL;	// Liste der ObjektNummern
	ObjContainer *_OCont;	// GesamtContainer dieses Objektes

public:
	_TRIAS02_ENTRY EXPORT02 KomplexObjekt (GeoDB &rDB, long KONr, long Id = 0);	// einlesen der TeilObjekte
	_TRIAS02_ENTRY EXPORT02 KomplexObjekt (GeoDB &rDB, long newONr, long Id, long RCode);
					// neubilden eines KomplexObjektes
	_TRIAS02_ENTRY EXPORT02 KomplexObjekt (KomplexObjekt &);
	_TRIAS02_ENTRY EXPORT02 ~KomplexObjekt (void);

// QueryMember
	long RCode (void) { return _RCode; }
	ObjFeld & OL (void) const { return *_pOL; }

_TRIAS02_ENTRY ObjTyp EXPORT02 isA (void);
_TRIAS02_ENTRY GeoObjekt * EXPORT02 operator +(long);
_TRIAS02_ENTRY ObjContainer EXPORT02 GetCont (void);

// MaintenanceMember
_TRIAS02_ENTRY ErrCode EXPORT02 AddObject (long ONr);	// Hinzufügen eines Objektes
_TRIAS02_ENTRY ErrCode EXPORT02 DeleteObject (long ONr);// Entfernen eines Objektes
_TRIAS02_ENTRY ErrCode AddObjectsToKO (long, long *, long = -1L);
_TRIAS02_ENTRY Bool EnumKObjects (BOOL (*fcn)(long, BOOL, void *), void *);
};
#endif 

#if !defined(NOOBJLISTEITERATOR)
class _TRIAS02_ENTRY ObjektListeIterator {
private:
	CRing *_pR;	// Navigator für ObjFeld in KomplexObjekt

public:
		EXPORT02 ObjektListeIterator (ObjFeld &);
		EXPORT02 ~ObjektListeIterator (void);

	long EXPORT02 FirstONr (void);		// der Reihe nach alle ONr's liefern
	long EXPORT02 NextONr (void);
};
#endif

#endif // _KOMPLEX_HXX

