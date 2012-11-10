// Lesen der Geometrie eines DB-Objektes --------------------------------------
// File: DBOGETGI.CXX

#include "triaspre.hxx"

#include "drw_obj1.hxx"
#include "schrift.hxx"
#include "relobj.hxx"
#include "minitpbd.hxx"

#include "triasres.h"

extern HPALETTE hPalette;				// derzeit aktive Palette des IrisWind

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// DatenBasisObjekt :: GetGI liest die Geometrie eines DB-Objektes und
// übergibt dem rufenden Programm einen Pointer auf ein 
// DrawObject (PunktObjekt, KantenObjekt, MaschenObjekt oder SchriftObjekt). 
// Bei KomplexObjekten wird die ObjektListe gelesen.
ErrCode DatenBasisObjekt :: GetGI (long ObjNr, 
				   ExtShapeObjectDCreator &DOC,
				   ExtShapeObject ** ppDO,
				   ObjContainer *pOC) 
{
GeoObjekt *pDBO = NULL;
ErrCode EC;

	if ((EC = DB().GetGI (ObjNr, &pDBO, pOC)) != EC_OKAY) {
		DELETE (pDBO);
		*ppDO = NULL;
		return EC;
	}

// DrawObject bilden
	switch (pDBO -> isA ()) {
	case OT_PUNKT:
		*ppDO = ContCreate (DOC, PunktObjekt) ((GeoPunkt &)(*(GeoPunkt *)pDBO), _MarkerTyp);
		break;

	case OT_KANTE:
		*ppDO = ContCreate (DOC, KantenObjekt) ((GeoKante &)(*(GeoKante *)pDBO));
		break;

	case OT_FLAECHE:
		*ppDO = ContCreate (DOC, MaschenObjekt) ((GeoFlaeche &)(*(GeoFlaeche *)pDBO));
		break;

	case OT_LABEL:
	case OT_TEXT:
		*ppDO = ContCreate (DOC, SchriftObjekt) ((BasicGeoText &)(*(BasicGeoText *)pDBO));
		break;

	case OT_KREIS:
		break;

	case OT_KO:
		*ppDO = ContCreate (DOC, RelationsObjekt) ((KomplexObjekt &)(*(KomplexObjekt *)pDBO));
		if (*ppDO != NULL) // alle Objekte des KomplexObjektes einlesen
			KOGetGI (*(KomplexObjekt *)pDBO, DOC);	
		break;

	case OT_UNKNOWN:
	default:
		break;          // do nothing
	}

return EC_OKAY;
}

// Liefert GeoObjekt zu einer vorgegeben ON -----------------------------------
GeoObjekt *DatenBasisObjekt :: GetGeoObj (long ON) 
{
	TX_ASSERT(IsValidONr(DB().DBDesc(), ON));

CTable t(Shapes().ObjNumTree()); // Navigator für alle Objekte
GeoObjekt *pGO = NULL;

	if (t.Find (&ON)) {
	ExtShapeObjectLock l(t);

		TX_ASSERT(NULL != (ExtShapeObject *)l);
		
		pGO = l -> operator GeoObjekt *();
		
		switch (pGO -> isA()) {
		case OT_PUNKT:   return new GeoPunkt (*(GeoPunkt*)pGO);
		case OT_KANTE:   return new GeoKante (*(GeoKante*)pGO);
		case OT_FLAECHE: return new GeoFlaeche (*(GeoFlaeche*)pGO);
		case OT_LABEL:
		case OT_TEXT:
			{
			TextObjTyp ToTyp = ((BasicGeoText *)pGO) -> isText();

				if (TOT_TEXT == ToTyp)
					return new GeoText (*(GeoText *)pGO);
				else if (TOT_TEXTIND == ToTyp)
					return new GeoTextInd (*(GeoTextInd *)pGO);
				else {
					TX_ASSERT(TOT_TEXTINDOBJPROP == ToTyp);
					return new GeoTextIndOP (*(GeoTextIndOP *)pGO);
				}
			}

		case OT_KREIS:	return new GeoKreis (*(GeoKreis *)pGO);
		case OT_KO:	return new KomplexObjekt (*(KomplexObjekt *)pGO);
		case OT_UNKNOWN:
		default:
			TX_ASSERT(false);
			return NULL;
		}
	} else 
		DB().GetGI (ON, &pGO);

return pGO;
}

// liefert Container zu einer vorgegeben ObjektNummer -------------------------
bool DatenBasisObjekt :: GetObjContainer (long lONr, ObjContainer &OC) 
{
CTable t(Shapes().ObjNumTree()); // Navigator für alle Objekte
bool fLoaded = false;
GeoObjekt *pGO = NULL;

	if (!t.Find (&lONr)) {		// Objekt suchen
	// nicht gefunden, Objekt ist offensichtlich nicht geladen
	ErrCode RC;

		if (((RC = DB().GetGI (lONr, &pGO)) != EC_OKAY) || pGO == NULL)
			return false;

		fLoaded = true;
	} else {
	ExtShapeObjectLock l(t);	// Objekt ist geladen

		if (!l) return false;
		
		pGO = l -> operator GeoObjekt *();
		if ((pGO -> isA() == OT_TEXT || pGO -> isA() == OT_LABEL) && l -> isVisible()) {
		// Texte sofort behandeln, wenn sie angezeigt sind
		Rectangle rcR = l -> BoundingBox();

			OC = rcR;
			return true;
		}
	}
	
// ObjektContainer bestimmen
	switch (pGO -> isA()) {
	case OT_PUNKT:   
	case OT_KANTE:   
	case OT_FLAECHE: 
	case OT_TEXT:		// #HK960116
	case OT_LABEL:		// #HK980602
	case OT_KO:
	case OT_KREIS:
		{
		bool fResult = ::GetObjContainer (pGO, OC);

			if (fLoaded) DELETE (pGO);
			return fResult;
		}

	default:
//	case OT_TEXT:		// #HK960116
	case OT_UNKNOWN:
		break;
	}

// evtl. aufräumen
	if (fLoaded) DELETE (pGO);
	
return false;
}

// Einlesen der Geometrien aller Objekte des Komplexobjektes ------------------
// (insbesondere der Objekte, die nicht zur aktuellen Sicht gehören)
ErrCode DatenBasisObjekt :: KOGetGI (KomplexObjekt &KO, 
				     ExtShapeObjectDCreator &DOC)
{
ObjektListeIterator KOI (KO.OL()); 
CTable t (Idents().IdentTree());
long ONr = KOI.FirstONr();
ErrCode RC;
ExtShapeObject *pESO;

	while (ONr != -1L) {
	long Ident = RetrieveIdent (ONr);	// Ident besorgen

		if (t.Find (&Ident)) {
		CIdentifikatorLock l(t);

			if (l && !(l -> toPaint() & l -> GetOTypes())) {
			// wenn Ident normalerweise nicht geladen werden soll

				DBASSERT (GetGI (ONr, DOC, &pESO));
			}
		}
		ONr = KOI.NextONr();	// nächstes Objekt holen
	}

return EC_OKAY;
}

// Liefern einiger Objekteigenschaften über die Schnittstelle -----------------
bool DatenBasisObjekt :: QueryObjStatistik (OBJSTATISTIK *pSt)
{
CTable t (Shapes().ObjNumTree());
GeoObjekt *pGO = NULL;
bool iLoaded = false;

	if (!t.Find (&pSt -> lONr)) {	// Objekt suchen
	// nicht gefunden, Objekt ist offensichtlich nicht geladen
	ErrCode RC;

		if ((RC = DB().GetGI (pSt -> lONr, &pGO)) != EC_OKAY)
			return false;
		if (pGO == NULL) 
			return false;
		pSt -> lIdent = pGO -> Id();
		iLoaded = true;
	} else {	// Objekt suchen
	// Objekt ist derzeit geladen
	ExtShapeObjectLock l(t);

		if (!l) return false;
		pSt -> lIdent = l -> Id();	// Identifikator

		pGO = l -> operator GeoObjekt *();
	}

	pSt -> lCnt = 0;
	pSt -> iKCnt = 0;

	switch (pSt -> iObjTyp = pGO -> isA()) {
	case OT_PUNKT:
	// nur eine Koordinate
		pSt -> lCnt = 1;
		break;

	case OT_LABEL:
	case OT_TEXT:
	// nur eine Koordinate
		pSt -> lCnt = 1;
		pSt -> iKCnt = strlen (((BasicGeoText *)pGO) -> TextBase()) +1;
		break;

	case OT_KANTE:
	// Anzahl der Stützpunkte
		pSt -> lCnt = ((GeoKante *)pGO) -> ASP();
		break;

	case OT_FLAECHE:
	// Anzahl der Konturen
		pSt -> iKCnt = ((GeoFlaeche *)pGO) -> KantenAnz();
	// Gesamtanzahl der Stützpunkte
		pSt -> lCnt = ((GeoFlaeche *)pGO) -> ASP();
		break;

	case OT_KREIS:
		pSt -> lCnt = 2;
		break;

	case OT_KO:
	// Anzahl der Teilobjekte liefern
		pSt -> lCnt = (long)((KomplexObjekt *)pGO) -> OL().Count();
		break;

	case OT_UNKNOWN:
	default:
		if (iLoaded) DELETE (pGO);
	        return false;
	}

// Aufräumarbeiten
	if (iLoaded) DELETE (pGO);

return true;
}

// Geometrie über Schnittstelle liefern ---------------------------------------
bool DatenBasisObjekt :: QueryObjGeometrie (OBJGEOMETRIE *pGS)
{
CTable t (Shapes().ObjNumTree());

	if (!t.Find (&pGS -> lONr)) {	// Objekt suchen
	// nicht gefunden, Objekt ist offensichtlich nicht geladen
	GeoObjekt *pGO;
	ErrCode RC;

		if ((RC = DB().GetGI (pGS -> lONr, &pGO)) != EC_OKAY)
			return false;
		RC = (ErrCode)pGO -> RetrieveGeometrie (pGS, pCT());
		if ((pGS -> dwSize == sizeof(TEXTGEOMETRIE) || pGS -> dwSize == sizeof(TEXTGEOMETRIEEX)) && 
			(pGS -> iObjTyp == OT_TEXT || pGS -> iObjTyp == OT_LABEL))
		{
		// Text mit kopieren
		char *pDest = ((TEXTGEOMETRIE *)pGS) -> pText;
		short iLen = pGS -> iKCnt;
			
			if (iLen > 0 && pDest) {
				strncpy (pDest, ((BasicGeoText *)pGO) -> TextBase(), iLen);
				pDest[iLen-1] = '\0';
			}
			if (pGS -> dwSize == sizeof(TEXTGEOMETRIEEX))
				((TEXTGEOMETRIEEX *)pGS) -> fIndObjProp = (pGS -> iObjTyp == OT_LABEL) ? TRUE : FALSE;
		}
		DELETE (pGO);
		return RC;
	} else {
	// Objekt ist derzeit geladen
	ExtShapeObjectLock l(t);

		if (l) {
		GeoObjekt *pGO = l -> operator GeoObjekt *();
		bool iResult = pGO -> RetrieveGeometrie (pGS, pCT());
		
			if ((pGS -> dwSize == sizeof(TEXTGEOMETRIE) || pGS -> dwSize == sizeof(TEXTGEOMETRIEEX)) && 
				(pGS -> iObjTyp == OT_TEXT || pGS -> iObjTyp == OT_LABEL))
			{
			// Text mit kopieren
			char *pDest = ((TEXTGEOMETRIE *)pGS) -> pText;
			short iLen = pGS -> iKCnt;
			
				if (iLen > 0 && pDest) {
					strncpy (pDest, ((BasicGeoText *)pGO) -> TextBase(), iLen);
					pDest[iLen-1] = '\0';
				}
				if (pGS -> dwSize == sizeof(TEXTGEOMETRIEEX))
					((TEXTGEOMETRIEEX *)pGS) -> fIndObjProp = (pGS -> iObjTyp == OT_LABEL) ? TRUE : FALSE;
			}
			return iResult;
		}
	}

return false;
}

bool ConvertCoords (long *, long *, OBJGEOMETRIE *, CoordTrans *, bool = true);
bool CopyCoords (long *, long *, OBJGEOMETRIE *, bool = true);

bool GeoObjekt::RetrieveGeometrie (OBJGEOMETRIE *pGS, CoordTrans *pCT)
{
bool iRC = false;
long *x = NULL, *y = NULL;
long *KCnt = NULL;

	pGS -> lIdent = Id();
	pGS -> lONr = ObjNr();

	if (!RetrievePureGeometrie (&x, &y, &KCnt)) {
	// Speicher wieder freigeben
		DELETE (x);
		DELETE (y);
		DELETE (KCnt);
		return false;
	}

	if ((pGS -> iObjTyp = isA()) == OT_FLAECHE) {
		for (long i = 0; i < pGS -> iKCnt; i++)
			pGS -> plCnt[i] = KCnt[i];
	}

// Geometrie konvertieren
	if (pGS -> iFlags & OGConverted)	// konvertierte doubleKoordinaten 
		iRC = ConvertCoords (x, y, pGS, pCT);
	else			// !konvertierte longKoordinaten
		iRC = CopyCoords (x, y, pGS);

// Speicher wieder freigeben
	DELETE (x);
	DELETE (y);
	DELETE (KCnt);

return iRC;
}

// Konvertieren eines Koordinatenfeldes ---------------------------------------
#if defined(WIN32)
inline bool ConvertRCToOCEx (
	CoordTrans *pCT, double dX, double dY, long &rlX, long &rlY, LPVOID pData)
{
	if (!pCT -> InvTransformEx (&dX, &dY, pData)) 
		return false;

	return pCT -> Scale (dX, dY, &rlX, &rlY);
}

inline bool ConvertOCToRCEx (
	CoordTrans *pCT, long lX, long lY, double &rdX, double &rdY, LPVOID pData)
{
	if (!pCT -> UnScale (lX, lY, &rdX, &rdY))
		return false;

	return pCT -> TransformEx (&rdX, &rdY, pData);
}
#endif // WIN32

inline bool ConvertRCToOC (
	CoordTrans *pCT, double dX, double dY, long &rlX, long &rlY)
{
	if (!pCT -> InvTransform (&dX, &dY)) 
		return false;

return pCT -> Scale (dX, dY, &rlX, &rlY);
}

inline bool ConvertOCToRC (
	CoordTrans *pCT, long lX, long lY, double &rdX, double &rdY)
{
	if (!pCT -> UnScale (lX, lY, &rdX, &rdY))
		return false;

	return pCT -> Transform (&rdX, &rdY);
}

#if defined(WIN32)
bool ConvertCoords (long *x, long *y, OBJGEOMETRIE *pGS, CoordTrans *pCT, bool iFlag)
{
// jede Koordinate konvertieren
	TX_ASSERT(pGS -> lCnt > 0);

LPVOID pData = NULL;
bool fResult = true;

	if (iFlag) {
		if (!pCT -> UnScale (x[0], y[0], (double *)(pGS -> pdblX), (double *)(pGS -> pdblY)))
			return false;

		pCT -> GetTransformParam (*(double *)(pGS -> pdblX), *(double *)(pGS -> pdblY), &pData);
		if (!pCT -> TransformEx ((double *)(pGS -> pdblX), (double *)(pGS -> pdblY), pData)) 
		{
			if (NULL != pData) CoTaskMemFree (pData);
			return false;
		}

		for (long i = 1; i < pGS -> lCnt; i++) {
			if (!ConvertOCToRCEx (pCT, x[i], y[i], ((double *)(pGS -> pdblX))[i], ((double *)(pGS -> pdblY))[i], pData)) 
			{
				fResult = false;
				break;
			}
		}
	} else {
		pCT -> GetInvTransformParam (*(double *)(pGS -> pdblX), *(double *)(pGS -> pdblY), &pData);
		for (long i = 0; i < pGS -> lCnt; i++) {
			if (!ConvertRCToOCEx (pCT, ((double *)(pGS -> pdblX))[i], ((double *)(pGS -> pdblY))[i], x[i], y[i], pData))
			{
				fResult = false;
				break;
			}
		}
	}
	if (NULL != pData) CoTaskMemFree (pData);

return fResult;
}
#else
bool ConvertCoords (long *x, long *y, OBJGEOMETRIE *pGS, CoordTrans *pCT, bool iFlag)
{
// jede Koordinate konvertieren
	TX_ASSERT(pGS -> lCnt > 0);

	if (iFlag) {
		for (long i = 0; i < pGS -> lCnt; i++) {
			if (!ConvertOCToRC (pCT, x[i], y[i], ((double *)(pGS -> pdblX))[i], ((double *)(pGS -> pdblY))[i]))
				return false;
		}
	} else {
		for (long i = 0; i < pGS -> lCnt; i++) {
			if (!ConvertRCToOC (pCT, ((double *)(pGS -> pdblX))[i], ((double *)(pGS -> pdblY))[i], x[i], y[i]))
				return false;
		}
	}

return true;
}
#endif // WIN32

bool CopyCoords (long *x, long *y, OBJGEOMETRIE *pGS, bool iFlag)
{
// Koordinaten lediglich umkonvertieren
	if (iFlag) {
		for (long i = 0; i < pGS -> lCnt; i++) {
			((long *)(pGS -> pdblX))[i] = x[i];
			((long *)(pGS -> pdblY))[i] = y[i];
		}
	} else {
		for (long i = 0; i < pGS -> lCnt; i++) {
			x[i] = ((long *)(pGS -> pdblX))[i];
			y[i] = ((long *)(pGS -> pdblY))[i];
		}
	}

return true;
}

#if defined(WIN32)
//////////////////////////////////////////////////////////////////////////////
// Koordinatentransformationen
bool DatenBasisObjekt::ConvertRCToOC (double dX, double dY, long &rlX, long &rlY)
{
	return ::ConvertRCToOC (pCT(), dX, dY, rlX, rlY);
}

bool DatenBasisObjekt::ConvertOCToRC (long lX, long lY, double &rdX, double &rdY)
{
	return ::ConvertOCToRC (pCT(), lX, lY, rdX, rdY);
}
#endif // WIN32

//////////////////////////////////////////////////////////////////////////////
// Löschen eines Objektes mit angehängtem Textobjekt aus Speicher und DB 
bool DatenBasisObjekt::DeleteObjekt (long lONr, bool fUndo)
{
	TX_ASSERT(IsValidONr(DB().DBDesc(), lONr));

// wenn ein Textobjekt dranhängt, dann dieses ebenfalls löschen
CActDB ActDB (DB());	// DB aktivieren
long AssocTextObj = -1L;
bool fDelAssoc = false;
bool fDelObj = !DEXN_DeletingObject (lONr);
short iObjStatus = DEX_GetObjectStatus (lONr);
long lIdent = RetrieveIdent (lONr);
HPROJECT hDB = DB().DBDesc();
ObjTyp rgOTyp = Shapes().RetrieveObjTyp (lONr);

	TX_ASSERT(OT_UNKNOWN != rgOTyp);
#if !defined(_DEBUG)
	if (OT_UNKNOWN == rgOTyp) return false;		// Objekt ist bereits gelöscht
#endif // !_DEBUG

	if (iObjStatus == -1 || !(iObjStatus & OS_Temp)) {
	// Objekte bearbeiten wenn nicht geladen oder nicht temporär
		AssocTextObj = AssociatedTextObjekt (hDB, lONr);

	// eigentliches löschen
		if (AssocTextObj != -1) {
			fDelAssoc = true;
			if (DEXN_DeletingObject (AssocTextObj))
				fDelAssoc = false;
		}

	// GeoDB für alle Fälle als modifiziert markieren
		DB().SetDirty (true);

	// jetzt allen sagen, daß es wirklich gelöscht wird
		if (fDelObj)
			DEXN_ObjectToDelete(lONr);

	// wenn nur Objekt gelöscht werden soll, dann Relation lösen
		if (fDelObj && !fDelAssoc && AssocTextObj != -1L) {
			if ((ErrCode)DelRelation (hDB, lONr, AssocTextObj, 0, BRELA) != EC_OKAY)
				return false;
		}

	// Objekt löschen
		if (fDelObj) {
			if (fUndo) {
				DeleteFeatures (lONr);	// Merkmale mit Undo/Redo löschen
				DeleteRelations (lONr);	// Relationen mit Undo/Redo löschen
			}
			if (((ErrCode)del (hDB, lONr) != EC_OKAY)) 
				return false;
			DecrementObjectCount();		// ein Objekt weniger
		}

	// nur abh. Textobjekt löschen
		if (!fDelObj && fDelAssoc) {
			DEXN_ObjectToDelete(AssocTextObj);
			if (fUndo) {
				DeleteFeatures (AssocTextObj);	// Merkmale mit Undo/Redo löschen
				DeleteRelations (AssocTextObj);	// Relationen mit Undo/Redo löschen
			}
			if (((ErrCode)del (hDB, AssocTextObj) != EC_OKAY))
				return false;
			DecrementObjectCount();		// ein Objekt weniger
		}
	}

// Objekt(e) aus ObjektBaum und IdentBaum löschen
CTable t (Shapes().ObjIdTree());
bool fResult = false;

	if (fDelObj) {
		Shapes().DeleteObjekt (lONr);					// keinen Fehler auswerten
		
		if (0 == Idents().DecrementObjectCount (DB(), lIdent, rgOTyp, lONr)) {	// war's der letzte mit diesem Ident (im Speicher)
		short iOTypes = 0;

			if (!Idents().FindId (DB(), lIdent, NULL, &iOTypes) || 
				0 == (iOTypes & OTypToBits(rgOTyp)))
			{
				Idents().DeleteIdent (lIdent, OTypToVTyp(rgOTyp));
			}
		}
		DEXN_ObjectDeleted (lONr);
		fResult = true;
	}

	if (fDelAssoc && AssocTextObj != -1L) {
	long lAssocId = RetrieveIdent (AssocTextObj);
	
		Shapes().DeleteObjekt (AssocTextObj);
		
		if (0 == Idents().DecrementObjectCount (DB(), lIdent, OT_TEXT, AssocTextObj)) 
		{
		short iOTypes = 0;

			if (!Idents().FindId (DB(), lAssocId, NULL, &iOTypes) || 
				0 == (iOTypes & TPText))
			{
				Idents().DeleteIdent (lAssocId, VT_Text);
			}
		}
		DEXN_ObjectDeleted (AssocTextObj);
		fResult = true;
	}

return fResult;
}

// Feststellen des Objekttyps eines Objektes ----------------------------------
ObjTyp DatenBasisObjekt :: RetrieveObjTyp (long lONr)
{
	TX_ASSERT(IsValidONr(DB().DBDesc(), lONr));
	return Shapes().RetrieveObjTyp (lONr);
}

// Temporäres Einfügen eines Objektes in den Objektbaum -----------------------
long DatenBasisObjekt::PutGeoObj (GeoObjekt *pGO, short iFlags)
{
// DrawObject bilden
ExtShapeObjectDCreator DOC (Shapes());
ExtShapeObject *pESO = NULL;
short iTemp = 0;

	if (iFlags & OGTempObject) iTemp |= ANI_Temp;
	if (iFlags & OGAddToView) iTemp |= ANI_AddToView;

	switch (pGO -> isA()) {
	case OT_PUNKT:
		Idents().AddNewIdent (pGO -> Id(), hPalette, iTemp, MODIDENT_PUNKT);	
		pESO = ContCreate (DOC, PunktObjekt) (*(GeoPunkt *)pGO, _MarkerTyp);
		break;

	case OT_KANTE:
		Idents().AddNewIdent (pGO -> Id(), hPalette, iTemp, MODIDENT_LINIE);	
		pESO = ContCreate (DOC, KantenObjekt) (*(GeoKante *)pGO);
		break;

	case OT_FLAECHE:
		Idents().AddNewIdent (pGO -> Id(), hPalette, iTemp, MODIDENT_FLAECHE);	
		pESO = ContCreate (DOC, MaschenObjekt) (*(GeoFlaeche *)pGO);
		break;

	case OT_LABEL:
	case OT_TEXT:
		{
		TextObjTyp ToTyp = ((BasicGeoText *)pGO) -> isText();

			Idents().AddNewIdent (pGO -> Id(), hPalette, iTemp, MODIDENT_TEXT);	
			if (TOT_TEXT == ToTyp)
				pESO = ContCreate (DOC, SchriftObjekt) (*(GeoText *)pGO);
			else if (TOT_TEXTIND == ToTyp)
				pESO = ContCreate (DOC, SchriftObjekt) (*(GeoTextInd *)pGO);
			else {
				TX_ASSERT(TOT_TEXTINDOBJPROP == ToTyp);
				pESO = ContCreate (DOC, SchriftObjekt) (*(GeoTextIndOP *)pGO);
			}
		}
		break;

	case OT_KREIS:
		Idents().AddNewIdent (pGO -> Id(), hPalette, iTemp, MODIDENT_FLAECHE);	
		pESO = ContCreate (DOC, KreisObjekt) (*(GeoKreis *)pGO);
		break;

	case OT_KO:
	case OT_UNKNOWN:
	default:
		TX_ASSERT(false);
		break;          // do nothing
	}

	if (pESO == NULL) {
		db_error (EC_NOMEMORY, RC_PutGeoObj);
		return -1L;
	}

// Objekt ist temporär
	if (iTemp & ANI_Temp) pESO -> Status() = OS_Temp;

// Einfügen und evtl. Baum Optimieren
	Shapes().CondOptimize (Shapes().TimedInsert(DOC, pGO -> isA()));
	Idents().IncrementObjectCount (DB(), pGO -> Id(), pGO -> isA(), pGO -> ObjNr());
	return pGO -> ObjNr();
}

// Einspeichern eines Objektes aus übergebenen Feldern ------------------------
bool DatenBasisObjekt :: ModObjGeometrie (OBJGEOMETRIE *pGS)
{
GeoObjekt *pGO = NULL;	// Daten konvertieren
ErrCode RC;
bool fRc = true;

// wenn lediglich template erzeugt werden soll
	if (pGS -> dwSize == sizeof(OBJCREATE)) {
		if (!(pGS -> iFlags & OGTempObject)) {
			if (pGS -> lIdent == 0L) {
				pGS -> lIdent = DEX_GetUnknownIdent();
				if (pGS -> lIdent == 0L)
					return false;
			}
			if (pGS -> lONr > 0) {
			// bestehendes Objekt löschen und wiederverwenden
				if (!DeleteObjekt (pGS -> lONr))
					return false;
			}
			pGS -> lONr = DB().CreateObjTemplate (
					pGS -> lIdent, pGS -> iObjTyp);

			if (pGS -> lONr == -1L) return false;
		
		// neues Objekt im Speicher erzeugen/Ident registrieren
			if (!Idents().AddNewIdent (pGS -> lIdent, hPalette, false, MODIDENT_TYP))
				return false;

			IncrementObjectCount();		// ein Objekt mehr
			DB().SetDirty();
			return true;
		} else 
			return true;	// so tun als ob's ok wäre
	}

//
// 1. Schritt: Geometrie des neuen Objektes besorgen
//
	if (pGS -> iFlags & OGIgnoreGeometry)
		return false;		// jemand war vor uns da

	if (!(pGS -> iFlags & OGModObject)) 
		pGS -> lONr = -1L;	// ObjektNummer muß neu vergeben werden

	if (pGS -> iFlags & OGOverlay) {
	// wenn ObjektGeometrie von einem anderen Objekt übernommen werden soll
	CTable t (Shapes().ObjNumTree());
	COPYGEOMETRIE *pCG = (COPYGEOMETRIE *)pGS;

		if (!t.Find (&pCG -> lTargetONr)) {	// Objekt suchen
		// nicht gefunden, Objekt ist offensichtlich nicht geladen
			if ((RC = DB().GetGI (pCG -> lTargetONr, &pGO)) != EC_OKAY)
				return false;
		} else 
		// Objekt ist derzeit geladen
			pGO = GetGeoObj (pCG -> lTargetONr);
	} else {
#if !defined(WIN32)
	// wenn das Objekt zu groß ist, dann abweisen
		if (pGS -> iObjTyp == OGLinie || pGS -> iObjTyp == OGFlaeche) {
			if (pGS -> lCnt > 16000L)
				return false;
		}
#endif // WIN32
		
	// wenn ObjektGeometrie gegeben ist
		if (pGS -> iFlags & OGConverted) {	// konvertierte doubleKoordinaten 
		long *x = NULL, *y = NULL;

			x = new long [pGS -> lCnt];
			y = new long [pGS -> lCnt];
			if (x == NULL || y == NULL) {
				DELETE (x);
				return false;
			}

		// GeoObjekt bilden
			if ((fRc = ConvertCoords (x, y, pGS, pCT(), false)) != false) 
				pGO = MakeGI (pGS, x, y);

		// Speicher wieder freigeben
			DELETE (x);
			DELETE (y);
		} else 				// !konvertierte longKoordinaten
			pGO = MakeGI (pGS, (long *)pGS -> pdblX, (long *)pGS -> pdblY);
	}

	if (pGO == NULL) return false;
	if (pGS -> lIdent != 0 && pGS -> lIdent != -1L)
		pGO -> Id() = pGS -> lIdent;	// Ident korrigieren
	else if (pGS -> lONr > 0)		// ObjektNummer bekannt
		pGO -> Id() = RetrieveIdent (pGS -> lONr);
	else			// Ident und ObjektNummer sind unbekannt
		pGO -> Id() = DEX_GetUnknownIdent();

	if (pGO -> Id() == 0L || pGO -> Id() == -1L)
		return false;

//
// 2. Schritt: Objekt in die GeoDB wegschreiben 
// 	       (wenn nicht TempObjekt gefordert ist)

	if (pGS -> iFlags & OGTempObject) 
	// ObjektNummer generieren
		 pGO -> ObjNr() = DB().GetUniqueTempONr();
	else {
	// Geometrie testen, ob Koordinaten innerhalb DBCont liegen
		if (!(pGS -> iFlags & OGForceGeometry) &&
		    !DB().VerifyGI (pGO)) 
		{
		    DELETE (pGO);
		    return false;
		}

	// neue Geometrie schreiben
		DB().SetDirty();
	
		if (pGS -> iFlags & OGOverlay) {
		// Geometrie in der DB überlagern
		COPYGEOMETRIE *pCG = (COPYGEOMETRIE *)pGS;

			pGO -> ObjNr() = pGS -> lONr;
			if (DB().OverlayGI (pCG -> lTargetONr, pGO) != EC_OKAY) {
				DELETE (pGO);
				return false;
			}
		} else {
		// bisherige Geometrie rauslöschen, wenn modifiziert werden soll
			if (pGS	-> iFlags & OGModObject) {
			// bei allen nachfragen, ob geändert werden soll
				if (DEXN_ChangingObject (pGS -> lONr))
					return false;		// jemand hat was dagegen

			// Geometrie löchen
				if (DB().DelGI (pGO -> ObjNr()) != EC_OKAY) {
					DELETE (pGO);
					return false;
				}
			}

		// Objekt/Geometrie neu speichern
			if (DB().PutGI (pGO) != EC_OKAY) {
				DELETE (pGO);
				return false;
			}
		}
	}

//
// Schritt 3: GeoObjekt im Speicher aufbauen
//
	if ((pGS -> iFlags & (OGModObject|OGOverlay)) && (pGO -> ObjNr() != -1L))
	// bisheriges Objekt löschen
		Shapes().DeleteObjekt (pGO -> ObjNr());
	else
		IncrementObjectCount();		// ein Objekt mehr

// neues Objekt im Speicher erzeugen
	if (!(pGS -> iFlags & OGNoMemoryObject)) {
		if (PutGeoObj (pGO, pGS -> iFlags) == -1L) {
			DELETE (pGO);
			return false;
		}
		pGS -> lONr = pGO -> ObjNr();	// neue ObjektNummer
	} else {
		pGS -> lONr = pGO -> ObjNr();	// neue ObjektNummer
		DELETE (pGO);
	}
	DEXN_ObjectChanged (pGS -> lONr);
			
return true;
}

inline double sqr (long x) { return (double(x)*double(x)); }

// DatenBasisObjekt :: MakeGI bildet DB-Objekte und übergibt einen
// Pointer auf ein GeoObjekt (GeoPunkt, GeoKante oder GeoMasche)
GeoObjekt *DatenBasisObjekt :: MakeGI (OBJGEOMETRIE *pGS, long *x, long *y) 
{
// Geometrie anfordern
GeoObjekt *pGO = NULL;           // Anfangswert

// zu Zeit nur Elementarobjekte 
	switch (pGS -> iObjTyp) {
	case OT_PUNKT:         // PunktObjekt
		pGO = new GeoPunkt (DB(), pGS -> lONr, pGS -> lIdent, 
					      Punkt (x[0], y[0]));
		break;

	case OT_KANTE:         // KantenObjekt
		pGO = new GeoKante (DB(), pGS -> lONr, pGS -> lIdent, 
					      x, y, pGS -> lCnt);
		break;

	case OT_FLAECHE:         // Flächenobjekt
		{
		for (short i = 0; i < pGS -> iKCnt; i++) {
		long lUsedLen = pGS -> plCnt[i];

			if (pGO == NULL) {
			// erste Geometrieportion       
				pGO = new GeoFlaeche (DB(), pGS -> lONr, 
						      pGS -> lIdent, 
						      x, y, lUsedLen
						     );
			} else { 
				((GeoFlaeche *)(pGO)) -> AddKante (
						x, y, lUsedLen, -1
				);
			}
			x += lUsedLen;		// auf nächste Kontur stellen
			y += lUsedLen;
		}
		}
		break;

	case OT_KREIS:
		{
		long lRadius = (long)sqrt (sqr(x[0]-x[1])+sqr(y[0]-y[1]));
		Punkt Pt (x[0], y[0]);

			pGO = new GeoKreis (DB(), pGS -> lONr, pGS -> lIdent, 
					    Pt, lRadius);
		}
		break;

	case OT_LABEL:
	case OT_TEXT:		// TextObjekt
		{
		BOOL fIndObjProp = (OT_LABEL == pGS -> iObjTyp) ? TRUE : FALSE;

			if (pGS -> dwSize == sizeof(TEXTGEOMETRIEEX))
				fIndObjProp = ((TEXTGEOMETRIEEX *)pGS) -> fIndObjProp;

			if (!fIndObjProp) {
				pGO = new GeoText (DB(), pGS -> lONr, pGS -> lIdent, 
						   Punkt (x[0], y[0]), 
						   ((TEXTGEOMETRIE *)pGS) -> pText);
			} else {
				pGO = new GeoTextIndOP (DB(), pGS -> lONr, pGS -> lIdent, 
						   Punkt (x[0], y[0]), 
						   ((TEXTGEOMETRIE *)pGS) -> pText);
			}
		}
		break;

	default:
		pGO = NULL;
		break;
	}

// Fehler aufgetreten         
	if (pGO == NULL) return NULL;

return pGO;
}

// Funktionen zur Verwaltung von SichtContainern ------------------------------
ErrCode DatenBasisObjekt :: SetActSichtCont (ObjContainer &OC)
{
// VersionsKontrolle
	if (DB().GetDBVersion() < VERSION05000008) return EC_OKAY;

// Eintrag in Header und Pbd generieren
	MainInitPbd (DB(), IDS_HDRSICHTCONTAINER, true);

// MCode aus Header holen
HeaderEntry HE (DB(), IDS_HDRSICHTCONTAINER);
long lMCode = HE.EntryLong (-1L);

	if (lMCode == -1L) return WC_NOTFOUND;	// Fehler

// Container als Merkmal an aktueller Sicht wegschreiben
char *pBuffer = new char [SIGHTMENUITEM +1];

	if (pBuffer == NULL) return EC_OKAY;
	GetActiveSightName (pBuffer, SIGHTMENUITEM +1);
	if (pBuffer[0] == '\0') {
		DELETE (pBuffer);
		return EC_OKAY;		// keine aktive Sicht
	}

CActDB ActDB (DB());		// #ActDB
ErrInstall EI (WC_NOTFOUND);
Sicht S (DB(), pBuffer);
ErrCode RC;

	wsprintf (pBuffer, "0,%ld,%ld,%ld,%ld", OC.XMin(), OC.YMin(), OC.XMax(), OC.YMax());
	RC = S.PutMiText (lMCode, pBuffer);
	DELETE (pBuffer);

return RC;
}


ErrCode DatenBasisObjekt :: DelActSichtCont (void)
{
// VersionsKontrolle
	if (DB().GetDBVersion() < VERSION05000008) return EC_OKAY;

// MCode aus Header holen
HeaderEntry HE (DB(), IDS_HDRSICHTCONTAINER);
long lMCode = HE.EntryLong (-1L);

	if (lMCode == -1L) return EC_OKAY;	// kein MCode gegeben

// Container als Merkmal an aktueller Sicht wegschreiben
char *pBuffer = new char [SIGHTMENUITEM +1];

	if (pBuffer == NULL) return EC_OKAY;
	GetActiveSightName (pBuffer, SIGHTMENUITEM +1);
	if (pBuffer[0] == '\0') {
		DELETE (pBuffer);
		return EC_OKAY;		// keine aktive Sicht
	}

// Merkmal in Sicht löschen
CActDB ActDB (DB());		// #ActDB
ErrInstall EI (WC_NOTFOUND);
Sicht S (DB(), pBuffer);

	DELETE (pBuffer);

return S.DelMiText (lMCode);
}


ErrCode DatenBasisObjekt :: GetActSichtCont (ObjContainer *pOC, char *pView)
{
// VersionsKontrolle
	if (DB().GetDBVersion() < VERSION05000008) return WC_RETURN;

// MCode aus Header holen
HeaderEntry HE (DB(), IDS_HDRSICHTCONTAINER);
long lMCode = HE.EntryLong (-1L);

	if (lMCode == -1L) return WC_RETURN;	// kein MCode gegeben

// Container als Merkmal an aktueller Sicht wegschreiben
bool fDelete = false;

	if (pView == NULL) {
		pView = new char [SIGHTMENUITEM +1];
		if (pView == NULL)
			return WC_RETURN;
		GetActiveSightName (pView, SIGHTMENUITEM +1);
		fDelete = true;
	}
	if (pView[0] == '\0') {
		if (fDelete) DELETE (pView);
		return WC_RETURN;		// keine aktive Sicht
	}

// Merkmal in Sicht löschen
char *pBuffer = NULL;

	{
	CActDB ActDB (DB());		// #ActDB
	ErrInstall EI (WC_NOTFOUND);
	Sicht S (DB(), pView);
	ErrCode RC;

		if (fDelete) {
			DELETE (pView);
		}
		if ((RC = S.GetMiText (lMCode, &pBuffer)) != EC_OKAY) {
			DELETE (pBuffer);
			return RC;
		}
	}
	if (pOC == NULL) {
		DELETE (pBuffer);
		return EC_OKAY;	// nur testen, ob Merkmal existiert
	}

// ObjContainer neu aufbauen
char *cptr;

	strtok (pBuffer, ",");		// erste Zahl überspringen
	cptr = strtok (NULL, ",");
	if (cptr) pOC -> XMin() = atol (cptr);
	else {
		DELETE (pBuffer);
		return WC_RETURN;
	}

	cptr = strtok (NULL, ",");
	if (cptr) pOC -> YMin() = atol (cptr);
	else {
		DELETE (pBuffer);
		return WC_RETURN;
	}

	cptr = strtok (NULL, ",");
	if (cptr) pOC -> XMax() = atol (cptr);
	else {
		DELETE (pBuffer);
		return WC_RETURN;
	}

	cptr = strtok (NULL, ",");
	if (cptr) pOC -> YMax() = atol (cptr);
	else {
		DELETE (pBuffer);
		return WC_RETURN;
	}
	DELETE (pBuffer);

return EC_OKAY;
}


bool DatenBasisObjekt :: hasSichtCont (void)
{
	return GetActSichtCont () == EC_OKAY;
}

// Recherche nach Textmerkmal, Enumeration der gefundenen Objekte -------------
bool DatenBasisObjekt :: EnumRechTextMerkmal (ENUMRECHTEXTMERKMAL *pERTM)
{
// als erstes Textrecherche selbst durchführen
ObjFeld Objekte;	// Feld welches ObjektNummern aufnehmen soll
char *pText = pERTM -> pMWert;

	if (SMExistanceOnly == pERTM -> iMode & ~SMActViewOnly) {
	// NULL-Text vortäuschen
		pText = NULL;
		pERTM -> iMode = SMExactMatch | (pERTM -> iMode & SMActViewOnly);
	}

ErrCode RC = DB().FindText (pERTM -> lMCode, pERTM -> iMode & ~SMActViewOnly, 
			    pText, Objekte);

	if (RC == WC_NOTFOUND) return true;	// nichts gefunden
	if (RC != EC_OKAY) return false;	// Fehler

	if (pERTM -> iMode & SMActViewOnly) {
	// nach Identifikatoren (über aktuelle Sicht) filtern
		if (DB().IdFilter (Objekte, Idents()) != EC_OKAY)
			return false;
	} else if (pERTM -> pView != NULL) {
	// nach Identifikatoren (über gegebebene Sicht) filtern
		if (DB().IdFilter (Objekte, pERTM -> pView) != EC_OKAY)
			return false;
	}

// gefundene Objekte enumerieren
return Objekte.Enumerate ((bool (*)(long, bool, void *))pERTM -> eFcn, pERTM -> pData);
}

// Recherche nach Geometrie (Rechteck), Enumeration der gefundenen Objekte ----
bool DatenBasisObjekt :: EnumRechGeometrie (ENUMRECHGEOMETRIE *pERG)
{
// als erstes Geometrierecherche selbst durchführen
CActDB ActDB (DB());
ObjFeld Objekte;	// Feld für ObjektNummern
ErrCode RC = EC_OKAY;

	if (pERG -> iMode & ERGConverted) {
	long x1, y1, x2, y2;
	double *pC = (double *)pERG -> lCont;

#if defined(WIN32)
	LPVOID pData = NULL;

		pCT() -> GetInvTransformParam (pC[0], pC[2], &pData);
		::ConvertRCToOCEx (pCT(), pC[0], pC[2], x1, y1, pData);
		::ConvertRCToOCEx (pCT(), pC[1], pC[3], x2, y2, pData);
		if (NULL != pData) CoTaskMemFree (pData);
#else
		::ConvertRCToOC (pCT(), pC[0], pC[2], x1, y1);
		::ConvertRCToOC (pCT(), pC[1], pC[3], x2, y2);
#endif // WIN32

	ObjContainer OC (x1, x2, y1, y2);

		RC = DB().GIWindow (OC, Objekte, pERG -> iMode & ERGExact);
	} else {
		RC = DB().GIWindow (*(ObjContainer *)(pERG -> lCont),
							Objekte, pERG -> iMode & ERGExact);
	}

	if (RC != EC_OKAY) return false;

// nach Identifikatoren (über gegebene Sicht) filtern
	if (sizeof(ENUMRECHGEOMETRIEEX) == pERG -> dwSize) {
	ENUMRECHGEOMETRIEEX *pERGEx = (ENUMRECHGEOMETRIEEX *)pERG;

		if (NULL != pERGEx -> m_pView) {
		// nach Identifikatoren (über gegebebene Sicht) filtern
			if (DB().IdFilter (Objekte, (char *)pERGEx -> m_pView) != EC_OKAY)
				return false;
		} else
			pERG -> iMode |= ERGActSight;		// über aktuelle Sicht filtern
	}

// nach Identifikatoren (über aktuelle Sicht) filtern
	if (pERG -> iMode & ERGActSight) {
		if (DB().IdFilter (Objekte, Idents()) != EC_OKAY)
			return false;
	}

// gefundene Objekte enumerieren
return Objekte.Enumerate (pERG -> eFcn, pERG -> pData);
}

// SichtBeschreibungsinfo behandeln -------------------------------------------
bool ReadTextMerkmal (short iTTyp, DWORD lTarget, long lMCode, char *pText, short iLen);
bool WriteTextMerkmal (short iTTyp, long lTarget, long lMCode, char *pText, short iFlags = 0);
long GetHeaderMCode (bool fGenerate, uint resID, LPCSTR = NULL, uint = 0, uint = 0);

char *DatenBasisObjekt :: QueryViewDesc (VIEWDESC *pVD)
{
// MerkmalsCode aus Header lesen
long lMCode = GetHeaderMCode (false, IDS_CAPTIONMCODE);

	if (!IsValidMCode(lMCode)) return NULL;
	
char *pView = pVD -> m_pView;
bool fToDelete = false;

	if (pView == NULL) {	
	// wenn keine Sicht gegeben ist, dann aktuelle benutzen
		pView = new char [SIGHTMENUITEM +1];
		if (pView == NULL) return NULL;
		GetActiveSightName (pView, SIGHTMENUITEM +1);
		if (*pView == '\0') {
			delete [] pView;
			return NULL;
		}
		fToDelete = true;
	}

// SichtMerkmal einlesen
	if (ReadTextMerkmal (TT_Sicht, (long)pView, lMCode, 
			     pVD -> m_pDesc, pVD -> m_iLen))
	{
		if (fToDelete) delete [] pView;
		if (pVD -> m_pDesc) 
			pVD -> m_iLen = strlen (pVD -> m_pDesc);
		else
			pVD -> m_iLen = 0;
		return pVD -> m_pDesc;
	}
	pVD -> m_iLen = 0;
	if (fToDelete) delete [] pView;
	
return NULL;	// nichts vorhanden
}

char *DatenBasisObjekt :: SetViewDesc (VIEWDESC *pVD)
{
// Sicht besorgen
char *pView = pVD -> m_pView;
bool fToDelete = false;

	if (pView == NULL) {	
	// wenn keine Sicht gegeben ist, dann aktuelle benutzen
		pView = new char [SIGHTMENUITEM +1];
		if (pView == NULL) return NULL;
		GetActiveSightName (pView, SIGHTMENUITEM +1);
		if (*pView == '\0') {
			delete [] pView;
			return NULL;
		}
		fToDelete = true;
	}

// MerkmalsCode aus Header lesen, ggf. erzeugen
	// (nur erzeugen, wenn nicht löschen)
long lMCode = GetHeaderMCode (pVD -> m_pDesc != NULL, 
			      IDS_CAPTIONMCODE, (LPCSTR)pView,
			      IDS_CAPTIONMCODEKTEXT,
			      IDS_CAPTIONMCODELTEXT);
// SichtMerkmal schreiben
	if (IsValidMCode(lMCode) && WriteTextMerkmal (TT_Sicht, (long)pView, 
					       lMCode, pVD -> m_pDesc))
	{
		if (fToDelete) delete [] pView;
		return pVD -> m_pDesc;
	}
//	pVD -> m_iLen = 0;		// nicht in Struktur schreiben
	if (fToDelete) delete [] pView;

return NULL;
}

// Eintrag für Ident in PBD generieren ----------------------------------------
static bool SaveICodeInPbd (long lIdent, uint uiResKT, uint uiResLT)
{
// PBDEintrag zusammenstellen
ResString rsKText (uiResKT, 32);
ResString rsLText (uiResLT, 64);
PBDDATA TM;
bool iResult = true;

	INITSTRUCT (TM, PBDDATA);
	TM.pbdTyp = 'i';
	TM.pbdCode = lIdent;
	TM.pbdKText = (char *)rsKText.Addr();
	TM.pbdLText = (char *)rsLText.Addr();	
	TM.pbdKTextLen = strlen (rsKText);
	TM.pbdLTextLen = strlen (rsLText);

	{
	ErrInstall EI (WC_NOIDENT);

		if (DEX_ModPBDData (TM) != EC_OKAY)
			iResult = false;
		else
			DEXN_PBDIdentChanged (lIdent);
	}
	
return iResult; 
}

long GetHeaderICode (bool fGenerate, uint resID, uint uiResKT, uint uiResLT)
{
GEODBHDRENTRY hdrEntry;
long result = 0L;

	INITSTRUCT (hdrEntry, GEODBHDRENTRY);
	strncpy (hdrEntry.hdrKey, ResString (resID, 17), 16);
	hdrEntry.lphdrText = new char [64 +1];
	hdrEntry.hdrTextLen = 64;

	if (DEX_ReadGeoDBHdrEntry (hdrEntry) == EC_OKAY) {
	// HeaderEintrag existiert
		result = atol (hdrEntry.lphdrText);
	} else if (fGenerate) {
	// bei Bedarf neu generieren
	long lIdent = DEX_GetUniqueICode();	// neuen MCode besorgen
	
		if (lIdent != -1) {		// und wegschreiben
			ltoa (lIdent, hdrEntry.lphdrText, 10);
			if (DEX_WriteGeoDBHdrEntry (hdrEntry) == EC_OKAY)
				result = lIdent;
		// in Pbd eintragen
			SaveICodeInPbd (lIdent, uiResKT, uiResLT);
		}
	}
	DELETE (hdrEntry.lphdrText);

return result;
}

// Liefert den Ident für ein nicht klassifiziertes/nicht klassifizierbares Objekt 
ULONG DatenBasisObjekt :: QueryUnknownIdent (void)
{
CActDB ActDB (DB());

	return GetHeaderICode (true, IDS_HDRUNKNOWNIDENT, 
			       IDS_KTUNKNOWNIDENT, IDS_LTUNKNOWNIDENT);
}

// Liefert ONr zu gegebenem Objektnamen ---------------------------------------
typedef struct tagFINDOBJFROMOBJNAME {
	long m_lONr;
	char *m_pMWert;
} FINDOBJFROMOBJNAME;

extern "C" bool WINAPI EXPORTTRIAS FindObjNameForIdent (long lONr, bool, void *pData)
{
	*(long *)pData = lONr;
	return false;		// nur das erste Objekt interessiert
}

extern "C" bool WINAPI EXPORTTRIAS EnumIdentForObjName (long lIdent, bool, void *pData)
{
ENUMRECHTEXTMERKMAL ERTM;
FINDOBJFROMOBJNAME *pFindObj = (FINDOBJFROMOBJNAME *)pData;

	INITSTRUCT (ERTM, ENUMRECHTEXTMERKMAL);
	ERTM.lMCode = DEX_GetObjNameMCode (lIdent);
	ERTM.pMWert = pFindObj -> m_pMWert;
	ERTM.iMode = SMExactMatch;
	ERTM.eFcn = (RECHTEXTMERKMALCALLBACK)FindObjNameForIdent;
	ERTM.pData = &pFindObj -> m_lONr;

return DEX_EnumRechTextMerkmal (ERTM);	
}


long DatenBasisObjekt :: FindObjFromName (char *pObjName)
{
// alle Identifikatoren Enumerieren, da der MCode identspezifisch ist
ENUMNOKEYLONG ENK;
FINDOBJFROMOBJNAME FOBJ;

	FOBJ.m_lONr = -1L;
	FOBJ.m_pMWert = pObjName;
	
	ENK.eFcn = (ENUMNOKEYLONGPROC)EnumIdentForObjName;
	ENK.ePtr = &FOBJ;
	DEX_EnumIdents (ENK);

	if (FOBJ.m_lONr == -1L) {
	// unter Objektnamen nichts gefunden, das ganze für UniqueIdent wiederholen
	ENUMRECHTEXTMERKMAL ERTM;
	
		INITSTRUCT (ERTM, ENUMRECHTEXTMERKMAL);
		ERTM.lMCode = DEX_GetUniqueIdentMCode();
		ERTM.pMWert = pObjName;
		ERTM.iMode = SMExactMatch;
		ERTM.eFcn = (RECHTEXTMERKMALCALLBACK)FindObjNameForIdent;
		ERTM.pData = &FOBJ.m_lONr;
		DEX_EnumRechTextMerkmal (ERTM);	
	}

return FOBJ.m_lONr;
}


// RückrufFunktion für EnumIdentViewsEx ---------------------------------------
// extern VisType OTypToVTyp (ObjTyp iOTyp);

typedef struct tagENUMVIEWSDATA {
	ENUMLONGKEYEX *pELK;
	GeoDB *pDB;
} ENUMVIEWSDATA;

extern "C" {

inline bool locF (ENUMLONGKEYEXPROC pF, char *pView, DWORD dwData, void *pPtr)
{
	return ((bool (CALLBACK *)(char *, DWORD, void *))pF)(pView, dwData, pPtr);
}

static bool HandleView (Sicht &rS, char *pName, ENUMLONGKEYEX *pELK, short iVTyp)
{
	if (rS.GetIDfromSight (pELK -> eKey, NULL, iVTyp) == EC_OKAY) 
	{
	// eigentliche enumerationsFunktion rufen
		if (!locF(pELK -> eFcn, pName, pELK -> eData, pELK -> ePtr))
			return false;		// abgebrochen
	}

return true;
}

extern "C" bool PASCAL CALLBACK EnumViewForIdent (char *pView, bool, void *pData)
{
ENUMVIEWSDATA *pEVD = ((ENUMVIEWSDATA *)pData);
ENUMLONGKEYEX *pELK = pEVD -> pELK;
ErrInstall EI (WC_NOTFOUND);
Sicht S (*(pEVD -> pDB), pView);
char cbName[64];

	OemToAnsi (S.Name(), cbName);
	if ((pELK -> eData & OTPunkt) && !HandleView (S, cbName, pELK, VT_Punkt)) 
		return false;
	if ((pELK -> eData & OTLinie) && !HandleView (S, cbName, pELK, VT_Linie)) 
		return false;
	if ((pELK -> eData & OTFlaeche) && !HandleView (S, cbName, pELK, VT_Flaeche)) 
		return false;
	if ((pELK -> eData & OTText) && !HandleView (S, cbName, pELK, VT_Text)) 
		return false;

return true; 	// weiter machen
}

} // extern "C"

// Enumeration aller Sichten, zu dem der gegebene Ident gehört ---------------- 
bool DatenBasisObjekt :: EnumIdentViewsEx (ENUMLONGKEYEX *pELK)
{
ENUMNOKEY ENK;
ENUMVIEWSDATA EVD;

	EVD.pELK = pELK;
	EVD.pDB = &DB();
	
	ENK.eFcn = (ENUMNOKEYPROC)EnumViewForIdent;
	ENK.ePtr = &EVD;

return (bool)DEX_EnumSights (ENK);
}


// Identifikator besorgen -----------------------------------------------------
LONG DatenBasisObjekt :: RetrieveIdent (LONG lONr) 
{
	TX_ASSERT(IsValidONr(DB().DBDesc(), lONr));

CTable t(Shapes().ObjNumTree());	// Navigator Objektliste

	if (t.Find (&lONr)) {		// Objekt gefunden
	ExtShapeObjectLock l(t);

		TX_ASSERT(NULL != (ExtShapeObject *)l);
		
		return l -> Id();
	} else {
	// Objekt nicht geladen, ist nicht in aktueller Sicht
	LONG lIdent = 0L;
	CActDB ActDB (DB());

	// in GeoDB nachsehen
		if (FindID (DB().DBDesc(), lONr, &lIdent) == EC_OKAY)
			return lIdent;
	}

return 0L;
}

