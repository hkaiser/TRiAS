// Finden aller Objekte innerhalb eines Geometriefensters (Window's)
// Filtern aller Objekte nach gewünschten Identifikatoren
// File: GIWINDOW.CXX

#include "trias02p.hxx"

#include <funcs02.h>
#include <dcreator.hxx>
#include <deltree.hxx>

#if defined(_FORCE_LEGACY_CODE)
#include <ident.hxx>
#endif // defined(_FORCE_LEGACY_CODE)
#include <objliste.hxx>

#include <dbmsg.hmc>			// TRIASDB_S_...

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASDatabase);			// WTRiASDatabase
DefineSmartInterface(TRiASAccessDatabase);		// WTRiASAccessDatabase
DefineSmartInterface(TRiASSearchObjects);		// WTRiASSearchObjects
DefineSmartInterface(TRiASObjectsCollection);	// WTRiASObjectsCollection

#if defined(_USE_LEGACY_CODE)
// Größe des Objektfeldes
const long OBJNUM = 300L;

// GeoDB :: GIWindow untersucht einen durch ein Fenster vorgegebenen Ausschnitt
// einer Geo-Datenbasis und liefert alle Objekte (Objektnummern), die innerhalb
// dieses Fensters liegen in einem vorzugebenden ArrayContainer
ErrCode GeoDB :: GIWindow (ObjContainer &OC, ObjFeld &ObjektFeld, Bool Flag) 
{
// überprüfen, ob DB eröffnet ist
	if (!isOpened()) 
		return (ErrCode)db_error ((int)EC_NOOPEN, (int)RC_GIWindow);

long NachLaden = 0;     // NachLadeparameter
ErrCode EC;             // FehlerStatus
long Objekte[OBJNUM+2];
ObjNummerCreator ONC (ObjektFeld);              // Creator
long Cont[5];           // SuchContainer

// ObjektNummern anfordern
ErrInstall EI (WC_NOTFOUND);	
CActDB ActDB (*this);		// DB aktivieren

// SuchContainer zusammenstellen
	*(ObjContainer *)Cont = OC;
	Cont[4] = Flag;
	do {
		Objekte[0] = OBJNUM;    // max. mögliche Objekt-Anzahl
		Objekte[1] = 0;         // Feld ist leer
		EC = (ErrCode)fndgi (DBDesc(), &NachLaden, Cont, Objekte);
		if (EC != EC_OKAY && EC != WC_WDHLG) 
			return EC;	// Fehler

	// erst mal fragen, was Windows dazu sagt
		App :: Exec (ExecWhileEvent);
		ActDB.ReActivate();	// DB wieder aktivieren

	// Objektnummern in ArrayContainer abspeichern
		for (register int i = 0; i < Objekte[1]; i++)
			ObjektFeld.NewObj (ONC, Objekte[i+2]);
	} while (NachLaden);

	return EC_OKAY;
}
#endif // USE_LEGACY_CODE

///////////////////////////////////////////////////////////////////////////////
// eine Recherche in der DatenBank durchführen
HRESULT GeoDB::SearchObjects (BSTR bstrCommand, ITRiASObjects *pIObjs, SAFEARRAY *pParams)
{
	TX_ASSERT(IsTRiASDBBased());

WTRiASDatabase DBase;

	RETURN_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));

WTRiASSearchObjects SearchObjs;
HRESULT hr = DBase.QueryInterface(SearchObjs);

	if (FAILED(hr)) return TRIASDB_S_SEARCH_NOT_SUPPORTED;		// DataBase kann keine Recherchen

	hr = SearchObjs -> ConsiderSearch (bstrCommand, pParams);
	if (S_OK != hr) return hr;		// Diese Recherche nicht unterstützt oder nicht zu empfehlen

	return SearchObjs -> SearchObjects (bstrCommand, pIObjs, pParams);
}

// eine Recherche in der DatenBank durchführen (objektklassenweise)
HRESULT GeoDB::SearchObjectsSeparate (BSTR bstrCommand, ITRiASObjects *pIObjs, SAFEARRAY *pParams)
{
	TX_ASSERT(IsTRiASDBBased());

WTRiASDatabase DBase;
WTRiASObjectsCollection ObjsDefs;

	RETURN_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));
	RETURN_FAILED_HRESULT(WTRiASAccessDatabase(DBase) -> get_ObjectsDefs (ObjsDefs.ppi()));

WTRiASSearchObjects SearchObjs;
HRESULT hr = ObjsDefs.QueryInterface(SearchObjs);

	if (FAILED(hr)) return TRIASDB_S_SEARCH_NOT_SUPPORTED;		// DataBase kann keine Recherchen

	hr = SearchObjs -> ConsiderSearch (bstrCommand, pParams);
	if (S_OK != hr) return hr;		// Diese Recherche nicht unterstützt oder nicht zu empfehlen

	return SearchObjs -> SearchObjects (bstrCommand, pIObjs, pParams);
}

///////////////////////////////////////////////////////////////////////////////
// Vergleicht GeoTyp mit VisTyp 
VisType EXPORT02 OTypToVTyp (ObjTyp iOTyp) 
{
	switch (iOTyp) {
	case OT_PUNKT:	return VT_Punkt;
	case OT_KANTE:	return VT_Linie;
	case OT_FLAECHE:
	case OT_KREIS:	return VT_Flaeche;
	case OT_LABEL:
	case OT_TEXT:	return VT_Text;
	case OT_KO:
	case OT_UNKNOWN:
	default:
		break;
	}

return VT_Default;
}

short OTypToVMsk (ObjTyp iOTyp) 
{
	switch (iOTyp) {
	case OT_PUNKT:	return TPPunkt;
	case OT_KANTE:	return TPLinie;
	case OT_FLAECHE:
	case OT_KREIS:	return TPFlaeche;
	case OT_LABEL:
	case OT_TEXT:	return TPText;
	case OT_KO:	return TPAll;
	case OT_UNKNOWN:
	default:
		break;
	}

return 0;
}

ObjTyp EXPORT02 VTypToOTyp (VisType iVTyp)
{
	switch (iVTyp) {
	case VT_Punkt:		return OT_PUNKT;
	case VT_Linie:		return OT_KANTE;
	case VT_Flaeche:	return OT_FLAECHE;
	case VT_Text:		return OT_TEXT;
	case VT_Default:
	default:
		break;
	}

return OT_UNKNOWN;
}

#if defined(_FORCE_LEGACY_CODE)
// Identifikator, wenn ON nicht existiert
const long IDENTFORBADON = -1L;

// Herausfiltern der Objekte, die nicht gewünschten Identifikator/Typ haben --
ErrCode GeoDB :: IdFilter (ObjFeld &Obj, CIdTree &Idents) 
{
// überprüfen, ob DB eröffnet ist
	if (!isOpened()) 
		return (ErrCode)db_error ((int)EC_NOOPEN, (int)RC_IdFilter);

// DB aktivieren
CActDB ActDB (*this);
CTable tId(Idents.IdentTree());		// Navigator für Identifikatoren
CRing r(Obj);				// Navigator für Objekte
long locId;

// wenn Idents leer ist, dann alles zeichnen
	if (Idents.IdentTree().Count() == 0) return EC_OKAY;

// für alle Objekte der gegebenen Liste
	for (r.First(); r.Valid(); ) {
	register Bool toDelete = TRUE;          // default: ON löschen
		{
		ObjNummerLock ONLock(r);        // Lock der ObjNummer

			locId = DEX_GetObjIdent (ONLock -> _ON);
		
			if (tId.Find (&locId)) {
			CIdentifikatorLock IdLock(tId);	// Lock des Identifikators
			short iVMsk = OTypToVMsk ((ObjTyp)DEX_GetObjectType (ONLock -> _ON));
			// setzen des Flags, ob ON gelöscht werden soll

				toDelete = !IdLock -> toPaint (iVMsk);
			}
		}

	// ON bei Bedarf löschen
		if (toDelete) {
			if (!r.Delete()) break; // ON löschen
		} else  {
			if (!r.Next()) break;   // ansonsten nächste ON
		}

	// überprüfen, was Windows dazu sagt
		App :: Exec (ExecWhileEvent);
		ActDB.ReActivate();
	}

return EC_OKAY;
}

// überprüfen, welche der Objekte zur gegebenen Sicht gehören -----------------
ErrCode GeoDB :: IdFilter (ObjFeld &Obj, char *SightName) 
{
// überprüfen, ob DB eröffnet ist
	if (!isOpened()) 
		return (ErrCode)db_error ((int)EC_NOOPEN, (int)RC_IdFilterSicht);

// DB aktivieren
CActDB ActDB (*this);
CRing r(Obj);	// Navigator für Objekte

// Identifkatoren dieser Sicht einlesen
long *IDs;
short numIDs;
Sicht locSight (*this, SightName);

	locSight.GetSightIDs (&IDs, numIDs, /* &pVTypes */ NULL);
	if (numIDs == 0) {
		Obj.EveryDelete();	// alles löschen
		return EC_OKAY;		// Sicht ist leer, nichts übertragen
	}

// für alle Objekte der gegebenen Liste
long locId = -1L;

	for (r.First(); r.Valid(); ) {
	register Bool toDelete = FALSE;

		{
		ObjNummerLock ONLock(r);        // Lock der ObjNummer
	
			locId = DEX_GetObjIdent (ONLock -> _ON);

		// setzen des Flags, ob ON gelöscht werden soll
		short iVMsk = OTypToVMsk ((ObjTyp)DEX_GetObjectType (ONLock -> _ON));
			if (!(locSight.GetTypes (locId) & iVMsk))
				toDelete = TRUE;

		}

	// ON bei Bedarf löschen
		if (toDelete) {
			if (!r.Delete()) break; // ON löschen
		} else  {
			if (!r.Next()) break;   // ansonsten nächste ON
		}

	// überprüfen, was Windows dazu sagt
		App :: Exec (ExecWhileEvent);
		ActDB.ReActivate ();	// sicherheitshalber wieder aktivieren
	}
	DELETE_OBJ (IDs);

return EC_OKAY;
}

// Alle Objekte einer Sicht aufsammeln (vom 'scratch') ------------------------
ErrCode GeoDB :: IdFilterNew (ObjFeld &OF, char *SightName) 
{
// überprüfen, ob DB eröffnet ist
	if (!isOpened()) 
		return (ErrCode)db_error ((int)EC_NOOPEN, (int)RC_IdFilterNew);

// als erstes DB aktivieren
CActDB ActDB (*this);

long lObjNum = LastRec (VERSION0500000E <= GetDBVersion() ? OBL_NEW : OBL_OLD);		// Anzahl der Objektsätze
Sicht locSight (*this, SightName);
short numIDs;
long *IDs;
ObjNummerCreator ONC (OF);
ErrCode EC = EC_OKAY;

// Identifikatoren dieser Sicht lesen
	locSight.GetSightIDs (&IDs, numIDs, NULL);
	if (numIDs == 0) 		// Sicht ist leer --> raus 
		return EC_OKAY;	

long lIdent = -1L;

	for (long i = 1; i < lObjNum; i++) {
	// ObjektInfo besorgen
	short iVMsk = OTypToVMsk ((ObjTyp)DEX_GetObjectType (i));
	
		lIdent = DEX_GetObjIdent (i);
		if (locSight.GetTypes (lIdent) & iVMsk)
			OF.NewObj (ONC, i);

	// überprüfen, was Windows dazu sagt
		App :: Exec (ExecWhileEvent);
		ActDB.ReActivate ();	// sicherheitshalber wieder aktivieren
	}
	DELETE_OBJ (IDs);

return EC;
}

// Alle Objekte der GeoDB aufsammeln (vom 'scratch') ------------------------
ErrCode GeoDB :: IdFilterAll (ObjFeld &OF) 
{
// überprüfen, ob DB eröffnet ist
	if (!isOpened()) 
		return (ErrCode)db_error ((int)EC_NOOPEN, (int)RC_IdFilterNew);

// als erstes DB aktivieren
CActDB ActDB (*this);
long lObjNum = LastRec (VERSION0500000E <= GetDBVersion() ? OBL_NEW : OBL_OLD);		// Anzahl der Objektsätze
ObjNummerCreator ONC (OF);
ErrCode EC = EC_OKAY;
long lIdent = -1L;

	for (long i = 1; i < lObjNum; i++) {
	// ObjektInfo besorgen
	short iVMsk = OTypToVMsk ((ObjTyp)DEX_GetObjectType (i));
	
		lIdent = DEX_GetObjIdent (i);
		if (lIdent != IDENTFORBADON && (iVMsk & TPAll))
			OF.NewObj (ONC, i);

	// überprüfen, was Windows dazu sagt
		App :: Exec (ExecWhileEvent);
		ActDB.ReActivate ();	// sicherheitshalber wieder aktivieren
	}

return EC;
}

///////////////////////////////////////////////////////////////////////////////
// Identifikator für ein Objekt aus GeoDB lesen
ErrCode EXPORT02 FindID (HPROJECT hPr, long ON, long *pID) 
{
DB_ADDR_OBL dba(hPr);
struct obl OBLSatz;
ErrCode RC;
ErrInstall EI (EC_DELRECORD);

// Objektsatz laden
//	dba.file_no = OBL;
	dba.rec_no = ON;
	if ((RC = (ErrCode)z_readrec (&dba, &OBLSatz)) != EC_OKAY) {
		*pID = IDENTFORBADON;
		if (RC == EC_DELRECORD) 
			return EC_OKAY;
		return RC;
	}

// Id lesen
struct idl IDLSatz;

	dba.file_no = IDL;
	dba.rec_no = OBLSatz.zoid;
	if ((RC = (ErrCode)z_readrec (&dba, &IDLSatz)) != EC_OKAY) {
		*pID = IDENTFORBADON;
		return RC;
	}
	*pID = IDLSatz.idn;

	return EC_OKAY;
}
#endif // defined(_FORCE_LEGACY_CODE)

/////////////////////////////////////////////////////////////////////////////
// Zugehöriges zugeordnetes Objekt finden 
// diese Funktion liefert die ObjektNummer des abhängigen Objektes 
#if !defined(_FORCE_LEGACY_CODE)
namespace {
	typedef struct tagFINDRELATEDOBJ {
		INT_PTR lONr;
		int iRTyp;
	} FINDRELATEDOBJ;

	BOOL CALLBACK FindLinkedObject (long lONr, long lRCode, short iRTyp, void *pData)
	{
	// angehängtes Textobjekt gefunden
		if (-1 == lRCode || 0 == lRCode) {
		FINDRELATEDOBJ *pRO = reinterpret_cast<FINDRELATEDOBJ *>(pData);

			pRO -> iRTyp = 0;
			if (iRTyp == RTBegleitO) {
				pRO -> lONr = lONr;		// abhängiges TextObjekt
				pRO -> iRTyp = iRTyp;
			} else if (iRTyp == RTBegleitU) {
				pRO -> lONr = lONr;		// übergeordnetes Objekt
				pRO -> iRTyp = iRTyp;
			} else 
				return TRUE;			// weitermachen

			return FALSE;				// Objekt gefunden, Enumeration abbrechen
		}
		return TRUE;
	}
} // namespace
#endif // _FORCE_LEGACY_CODE

// Feststellen, ob Objekt ein TextObjekt ist 
extern "C" 
BOOL EXPORT02 isDBTextObjekt (INT_PTR ON) 
{
ObjTyp rgType = (ObjTyp)DEX_GetObjectType (ON);

	return (OT_TEXT == rgType || OT_LABEL == rgType) ? TRUE : FALSE;
}

// FestStellen, ob TextObjekt ein Begleitobjekt ist 
extern "C" 
BOOL EXPORT02 isDBSubTextObjekt (INT_PTR lONr) 	// einfaches Begleitobjekt
{
ENUMRELATIONOBJS ERO;
FINDRELATEDOBJ FRO;

	FRO.iRTyp = 0;
	FRO.lONr = 0L;

	INITSTRUCT(ERO, ENUMRELATIONOBJS);
	ERO.lONr = lONr;
	ERO.lRCode = -1L;		// Begleitrelation
	ERO.iRTyp = RTBegleitU;
	ERO.eFcn = (ENUMRELOBJPROC)FindLinkedObject;
	ERO.pData = &FRO;

	DEX_EnumRelationObjects (ERO);
	return (0 != FRO.lONr) ? TRUE : FALSE;
}

extern "C" 
BOOL EXPORT02 isDBSubTextObjektInd (INT_PTR ON) 	// indirektes Begleitobjekt
{
ObjTyp rgType = (ObjTyp)DEX_GetObjectType (ON);

	return (OT_LABEL == rgType) ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Liefern der ObjektNummer des zugehörigen TextObjektes 
extern "C" 
long FUNCTYPE EXPORT02 AssociatedTextObjekt (INT_PTR ON) 
{
ENUMRELATIONOBJS ERO;
FINDRELATEDOBJ FRO;

	FRO.iRTyp = 0;
	FRO.lONr = 0L;

	INITSTRUCT(ERO, ENUMRELATIONOBJS);
	ERO.lONr = ON;
	ERO.lRCode = -1L;		// Begleitrelation
	ERO.iRTyp = RTBegleitO;
	ERO.eFcn = (ENUMRELOBJPROC)FindLinkedObject;
	ERO.pData = &FRO;

	DEX_EnumRelationObjects (ERO);
	if (FRO.iRTyp & RTBegleitO)
		return FRO.lONr;
	return -1L;				// wenn nichts gefunden, dann -1L liefern
}

// Zugehöriges zugeordnetes Objekt finden 
// liefert 0 bei nicht existierendem Bezugsobjekt,
// negative ObjNummer bei abhängigem Objekt und positive ON bei übergeordnetem
// Objekt
extern "C" 
long FUNCTYPE EXPORT02 AssociatedObjekt (INT_PTR lONr, bool *pfIsRelated) 
{
ENUMRELATIONOBJS ERO;
FINDRELATEDOBJ FRO;

	FRO.iRTyp = 0;
	FRO.lONr = 0L;

	INITSTRUCT(ERO, ENUMRELATIONOBJS);
	ERO.lONr = lONr;
	ERO.lRCode = -1L;		// Begleitrelation
	ERO.iRTyp = RTBegleitO|RTBegleitU;
	ERO.eFcn = (ENUMRELOBJPROC)FindLinkedObject;
	ERO.pData = &FRO;

	DEX_EnumRelationObjects (ERO);
	if (NULL != pfIsRelated)
		*pfIsRelated = (FRO.iRTyp & RTBegleitO) ? true : false;
	return FRO.lONr;		// wenn nichts gefunden, dann 0L liefern
}

// Finden eines Identifikators im vorgegebenen Feld ---------------------------
extern "C" 
long EXPORT02 FindLong (long *Vals, long numVals, long toSearch) 
{
	for (long i = 0; i < numVals; i++)
		if (Vals[i] == toSearch) return i;
	return -1L;
}

#if defined(_USE_LEGACY_CODE)
// Suchen der Objekte, die ein vorgegebenes Textmerkmal besitzen
ErrCode GeoDB :: FindText (long MCode, int Mode, char *SText, ObjFeld &ObjektFeld) 
{
// überprüfen, ob DB eröffnet ist
	if (!isOpened()) 
		return (ErrCode)db_error ((int)EC_NOOPEN, (int)RC_FindText);

long NachLaden = 0;     // NachLadeparameter
ErrCode EC;             // FehlerStatus
long feObj = 0;
ObjNummerCreator ONC (ObjektFeld);              // Creator
ErrInstall EI (WC_NOTFOUND);
CActDB ActDB (*this);				// DB aktivieren

// ObjektNummern anfordern, die Kriterium genügen
	EC = (ErrCode)::TextFind (DBDesc(), MCode, SText, Mode, OBL_OLD, &feObj);
	if (EC != EC_OKAY && EC != WC_WDHLG) {
		if (feObj) ferel_ (&feObj); 
		return EC;	// Fehler
	}

// Objektnummern in Container abspeichern
long *pObjekte;
long lCnt = 0;
ErrCode RC;
	
	FlexAdr ((short)feObj, &pObjekte);       // Feldadressen holen
	DBASSERT (felen_ (&feObj, &lCnt));
	for (long i = 0; i < lCnt; i++)
		ObjektFeld.NewObj (ONC, pObjekte[i]);

	if (feObj) ferel_ (&feObj); 

return EC_OKAY;
}

// Funktion, die aus der GeoDB den Objekttyp eines Objektes bestimmt ----------
static short GetOT (struct obl *pOBLSatz);

short GetObjTyp (HPROJECT hPr, long lONr)
{
DB_ADDR_OBL dba(hPr);
struct obl OBLSatz;
ErrInstall EI (EC_DELRECORD);

// Objektsatz laden
//	dba.file_no = OBL;
	dba.rec_no = lONr;
	if ((ErrCode)z_readrec (&dba, &OBLSatz) != EC_OKAY)
		return OT_UNKNOWN;

	return GetOT (&OBLSatz);
}


static short GetOT (struct obl *pOBLSatz)
{
	if (pOBLSatz == NULL) return OT_UNKNOWN;

	if (pOBLSatz -> status & SB_TEXTOBJIND) return OT_LABEL;
	if (pOBLSatz -> status & SB_TEXTOBJ) return OT_TEXT;
	if (pOBLSatz -> status & SB_SACHOBJ) return OT_KO;
	if (pOBLSatz -> rmaske & OREL) return OT_KO;

	if (pOBLSatz -> zokp) return OT_PUNKT;
	if (pOBLSatz -> zovol) return OT_KANTE;
	if (pOBLSatz -> zovoma) return OT_FLAECHE;

return OT_UNKNOWN;
}
#endif // _USE_LEGACY_CODE


