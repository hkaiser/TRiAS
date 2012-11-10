// Memberfunktionen fuer KomplexObjekte ---------------------------------------
// File: KOMPLEX.CXX

#include "trias02p.hxx"

#include <objfeld.hxx>
#include <komplex.hxx>

#include "getrcode.hxx"

// Konstruktoren --------------------------------------------------------------
// dieser Konstruktor legt im Speicher ein KomplexObjekt an und liest aus der
// DatenBasis die entsprechenden KO-Informationen ein
KomplexObjekt::KomplexObjekt (GeoDB &rDB, INT_PTR ONr, INT_PTR Id)
	       : GeoObjekt (rDB, ONr, Id)
{
// Variablen initialisieren
	_OCont = NULL;

// ObjFeld aufbauen
	TX_TRY(_pOL = new ObjFeld);
	if (_pOL == NULL) {
		db_error (EC_NOMEMORY, RC_ctKomplexObjekt);
		return;
	}

// Relation dieses Komplexobjektes holen
	if (RetrieveORCode (DB().DBDesc(), ONr, _RCode) != EC_OKAY) return;
	if (_RCode == -1L) {	// Fehler: kein übergeordnetes Objekt
		DELETE_OBJ (_pOL);
		return;
	}

// alle Objekte holen, die zu diesem Komplexobjekt gehören
	GetRelation (DB().DBDesc(), ONr, _RCode, *_pOL);
}


// Dieser Konstruktor legt sowohl im Speicher, als auch in der DatenBasis
// ein KomplexObjekt an
KomplexObjekt::KomplexObjekt (GeoDB &rDB, INT_PTR ONr, INT_PTR Id, INT_PTR RCode)
	: GeoObjekt (rDB, -1L, Id)
{
// Variablen initialisieren
	_OCont = NULL;

// ObjektFeld aufbauen 
	TX_TRY(_pOL = new ObjFeld);
	if (_pOL == NULL) {
		db_error (EC_NOMEMORY, RC_ctKomplexObjekt);
		return;
	}

// RelationsCode setzen
	_RCode = RCode;
	AddObject (ONr);	// Objekt reinhängen
}

// CopyConstructor ------------------------------------------------------------
// Kopiert lediglich ObjektNummer und Identifikator, nicht aber die ObjektListe
KomplexObjekt::KomplexObjekt (KomplexObjekt &KObj)
	       : GeoObjekt (KObj.DB(), KObj.ObjNr(), KObj.Id())
{
	_RCode = KObj._RCode;
	_pOL = NULL;
	_OCont = NULL;
}


KomplexObjekt::~KomplexObjekt (void) 
{
	DELETE_OBJ (_pOL);		// ObjFeld freigeben
	DELETE_OBJ (_OCont);
}


ObjContainer KomplexObjekt::GetCont (void) 
{
	if (_OCont) return *_OCont;
	if (_pOL) {
		TX_TRY(_OCont = new ObjContainer (_pOL -> CalcCont()));
		if (_OCont) 
			return *_OCont;
	}
	return ObjContainer (0, 0, 0, 0);
}

bool KomplexObjekt::GetObjContainer (ObjContainer &rOC)
{
	rOC = GetCont();
	return true;
}

long KomplexObjekt::RetrievePureGeometrie (KoOrd **ppX, KoOrd **ppY, long **ppiKCnt)
{
	return 0L;
}

// Hinzufügen meherer Objekte zu einem KomplexObjekt --------------------------
ErrCode KomplexObjekt::AddObjectsToKO (long lCnt, INT_PTR *plObjs, INT_PTR ONr)
{
ErrCode RC;

	for (long iCnt = 0; iCnt < lCnt; iCnt++) {
	// wenn aktuelles Objekt vorliegt weitermachen
		if (plObjs[iCnt] == ONr) continue;

	// weiteres Objekt hinzufügen
		DBASSERT (AddObject (plObjs[iCnt]));
	}
	return EC_OKAY;
}


// MaintenanceMember für ein Komplexobjekt ------------------------------------
extern "C" 
BOOL CALLBACK AddOneObject (INT_PTR ONr, BOOL, void *pData)
{
	return ((KomplexObjekt *)pData) -> AddObject (ONr) == EC_OKAY;
}

ErrCode KomplexObjekt::AddObject (INT_PTR ONr)
{
// weiteres Objekt einhängen
	if (_pOL == NULL) return EC_OKAY;

ObjTyp OTyp = (ObjTyp)DEX_GetObjectType (ONr);	// ObjektTyp des neuen Objektes holen
ErrCode RC;

	if (OTyp != OT_KO && OTyp != OT_UNKNOWN) {
	// neues Objekt ist ElementarObjekt
	CRing r(*_pOL);
	Bool iFound = FALSE;	// ist Objekt bereits in Liste enthalten

		for (r.First(); r.Valid(); r.Next()) {
		ObjNummerLock l(r);

			if (l && l -> _ON == ONr) iFound = TRUE;
		}
		if (iFound) 	// Objekt ist bereits in der Liste
			return EC_OKAY;

	// Objekt in die Liste einspeichern
		{
		ObjNummerCreator Cr (*_pOL);

			if (_pOL -> NewObj (Cr, ONr) == NULL)
				return (ErrCode)db_error (EC_NOMEMORY, RC_AddObject);
		}	// Objekt real in Liste einspeichern, damit Count() stimmt

	// in der DatenBasis nachführen
		DEX_SetDirtyGeoDB (true);
		if (_pOL -> Count() == 1) {
		// Objekt in der DatenBasis erzeugen
			DBASSERT (PutKomplexObject (DB().DBDesc(), (long *)&ObjNr(), Id(), RCode(), OREL, 1, (long *)&ONr));
		} else {
			DBASSERT (PutRelation (DB().DBDesc(), ObjNr(), ONr, RCode(), OREL));
		}
	} else if (OTyp == OT_KO) {
	// neues (hinzuzufügendes) Objekt ist bereits KomplexObjekt

		if (DEX_GetKObjectRCode (ONr) == RCode()) {
		// Relationen sind identisch
		long Result; 

			DEX_EnumKObjects (Result, ONr, 
					  (ENUMLONGKEYPROC)AddOneObject, this);
			if (!Result) 
				return (ErrCode)db_error (WC_CANTCREATEKO, RC_AddObject);
		} else {
		// sorry, not implemented
			return (ErrCode)db_error (WC_BADRCODE, RC_AddObject);
		}
	}
	return EC_OKAY;
}

extern "C" 
inline BOOL EnumKObjectsCallback (BOOL (*pFcn)(long, BOOL, void *), 
				  INT_PTR Key, BOOL iFlag, void *pData)
{
	return ((ENUMLONGKEYCALLBACK)pFcn)(Key, iFlag, pData);
}

// Wird zur Enumeration der EinzelObjekte benötigt ----------------------------
BOOL KomplexObjekt::EnumKObjects (BOOL (*fcn)(long, BOOL, void *), void *pData)
{
	if (_pOL == NULL) return FALSE;

// für alle Objekte dieses Komplexobjektes die gegebene Funtkion rufen
ObjektListeIterator KOI (OL());
INT_PTR ONr = KOI.FirstONr();

	while (ONr != -1L) {
	INT_PTR NextONr = KOI.NextONr();	// nächstes Objekt holen

		if (EnumKObjectsCallback (fcn, ONr, NextONr != -1L, pData) == FALSE) 
			return FALSE;	// abrechen, wenn FALSE geliefert wird
		ONr = NextONr;
	}
	return TRUE;
}


// Löschen eines Objektes aus dem KomplexObject -------------------------------
ErrCode KomplexObjekt::DeleteObject (INT_PTR ONr)
{
// gegebenes Objekt aus KO herauslösen
	if (_pOL == NULL) return EC_OKAY;

CRing r(*_pOL);
ErrCode RC;

	for (r.First(); r.Valid(); ) {
	Bool toDelete = FALSE;

	// Objekt suchen
		{
		ObjNummerLock l(r);

			if (!l) continue;
			if (l -> _ON == ONr) toDelete = TRUE;
		}

	// wenn das Objekt gefunden wurde, dann herauslöschen
		if (toDelete) {
			r.Delete();

		// DatenBasis nachführen
			DEX_SetDirtyGeoDB(true);
			DBASSERT (DelRelation (DB().DBDesc(), ObjNr(), ONr, _RCode, OREL));
			break;
		} else {
			if (!r.Next()) 
				break;
		}
	}
	return EC_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
// IterationsKlasse, um die einzelnen Objekte des Komplexobjektes anzusprechen 
ObjektListeIterator::ObjektListeIterator (ObjFeld &OL)
{
	_pR = new CRing (OL);
	if (_pR == NULL) {
		db_error (EC_NOMEMORY, RC_ctKomplexObjektIterator);
		return;
	}
	_pR -> First();		// an Anfang positionieren
}


ObjektListeIterator::~ObjektListeIterator (void)
{
	DELETE_OBJ (_pR);
}

///////////////////////////////////////////////////////////////////////////////
// sonstige MemberFunktionen 
ObjTyp KomplexObjekt::isA (void) { return OT_KO; }

INT_PTR ObjektListeIterator::FirstONr (void)  
{
INT_PTR ONr = -1L;

	if (_pR && _pR -> First()) {
	ObjNummerLock l(*_pR);

		if (l) ONr = l -> _ON;
		_pR -> Next();		// weiterschalten
	}
	return ONr;	// kein Objekt enthalten
}


INT_PTR ObjektListeIterator::NextONr (void) 
{
INT_PTR ONr = -1L;

	if (_pR && _pR -> Valid()) {
	ObjNummerLock l(*_pR);

		if (l) ONr = l -> _ON;
		_pR -> Next();
	}
	return ONr;
}

