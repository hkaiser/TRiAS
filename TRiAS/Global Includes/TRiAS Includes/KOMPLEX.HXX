///////////////////////////////////////////////////////////////////////////
// @doc 
// @module KOMPLEX.HXX | Komplexobjekte

#if !defined(_KOMPLEX_HXX__766329D8_0736_11D2_8657_00600875138A__INCLUDED_)
#define _KOMPLEX_HXX__766329D8_0736_11D2_8657_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <objfeld.hxx>

class KomplexObjekt : 
	public GeoObjekt 
{
private:
	INT_PTR _RCode;			// RelationsCode in diesem Komplexobjekt
	ObjFeld *_pOL;			// Liste der ObjektNummern
	ObjContainer *_OCont;	// GesamtContainer dieses Objektes

public:
_TRIAS02_ENTRY KomplexObjekt (GeoDB &rDB, INT_PTR KONr, INT_PTR Id = 0);	// einlesen der TeilObjekte
_TRIAS02_ENTRY KomplexObjekt (GeoDB &rDB, INT_PTR newONr, INT_PTR Id, INT_PTR RCode);
_TRIAS02_ENTRY KomplexObjekt (KomplexObjekt &);
_TRIAS02_ENTRY ~KomplexObjekt (void);

// QueryMember
	INT_PTR RCode (void) { return _RCode; }
	ObjFeld &OL (void) const { return *_pOL; }

_TRIAS02_ENTRY ObjTyp isA (void);
_TRIAS02_ENTRY bool GetObjContainer (ObjContainer &rOC);	// liefert ObjektContainer
_TRIAS02_ENTRY long RetrievePureGeometrie (KoOrd **ppX, KoOrd **ppY, long **ppiKCnt = NULL);

	_DGMGeometry *GetGeometry (bool fAddRef = false) { return NULL; }
	GEOMETRYTYPE GType() { return GEOMETRYTYPE_Unknown; }

_TRIAS02_ENTRY ObjContainer GetCont (void);

// MaintenanceMember
_TRIAS02_ENTRY ErrCode AddObject (INT_PTR ONr);	// Hinzufügen eines Objektes
_TRIAS02_ENTRY ErrCode DeleteObject (INT_PTR ONr);// Entfernen eines Objektes
_TRIAS02_ENTRY ErrCode AddObjectsToKO (long lCnt, INT_PTR *plObjs, INT_PTR lActONr = -1L);
_TRIAS02_ENTRY BOOL EnumKObjects (BOOL (*fcn)(long, BOOL, void *), void *);
};

class _TRIAS02_ENTRY ObjektListeIterator 
{
private:
	CRing *_pR;	// Navigator für ObjFeld in KomplexObjekt

public:


		ObjektListeIterator (ObjFeld &rOF);
		~ObjektListeIterator (void);

	INT_PTR FirstONr (void);		// der Reihe nach alle ONr's liefern
	INT_PTR NextONr (void);
};

#endif // !defined(_KOMPLEX_HXX__766329D8_0736_11D2_8657_00600875138A__INCLUDED_)
