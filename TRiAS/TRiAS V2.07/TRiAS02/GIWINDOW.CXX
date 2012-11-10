// Finden aller Objekte innerhalb eines Geometriefensters (Window's)
// Filtern aller Objekte nach gewünschten Identifikatoren
// File: GIWINDOW.CXX

#include "trias02p.hxx"

#include <dcreator.hxx>
#include <deltree.hxx>

#include <ident.hxx>
#include <objfeld.hxx>
#include <listobj.hxx>

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


// Vergleicht GeoTyp mit VisTyp ------------------------------------------------
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
	DELETE (IDs);

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
	DELETE (IDs);

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

// Feststellen, ob Objekt ein TextObjekt ist ----------------------------------
extern "C" 
BOOL EXPORT02 isDBTextObjekt (HPROJECT hPr, long ON) 
{
	if (GetDBVersion(hPr) < NEWDBVERSION)
		return FALSE;		// alte DB

ErrCode RC;
DB_ADDR_OBL dbaOBL(hPr);
struct obl OBLSatz;

//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ON;
	if ((RC = (ErrCode)z_readrec (&dbaOBL, &OBLSatz)) != EC_OKAY)
		return FALSE;

return (OBLSatz.status & SB_TEXTOBJ);
}

// FestStellen, ob TextObjekt ein Begleitobjekt ist ---------------------------
extern "C" 
BOOL EXPORT02 isDBSubTextObjekt (HPROJECT hPr, long ON) 	// einfaches Begleitobjekt
{
	if (GetDBVersion(hPr) < NEWDBVERSION)
		return FALSE;		// alte DB

ErrCode RC;
DB_ADDR_OBL dbaOBL(hPr);
struct obl OBLSatz;

//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ON;
	if ((RC = (ErrCode)z_readrec (&dbaOBL, &OBLSatz)) != EC_OKAY)
		return FALSE;

	if (!(OBLSatz.status & SB_TEXTOBJ))
		return FALSE;

return OBLSatz.rmaske & BRELP;	// Testen, ob Begleitobjekt ist
}


extern "C" 
BOOL EXPORT02 isDBSubTextObjektInd (HPROJECT hPr, long ON) 	// indirektes Begleitobjekt
{
	if (GetDBVersion(hPr) < NEWDBVERSION)
		return FALSE;		// alte DB

ErrCode RC;
DB_ADDR_OBL dbaOBL(hPr);
struct obl OBLSatz;

//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ON;
	if ((RC = (ErrCode)z_readrec (&dbaOBL, &OBLSatz)) != EC_OKAY)
		return FALSE;

	if (!((OBLSatz.status & SB_TEXTOBJ) && 
	      (OBLSatz.status & SB_TEXTOBJIND)))
		return FALSE;

return OBLSatz.rmaske & BRELP;	// Testen, ob Begleitobjekt ist
}

extern "C" {

// Liefern der ObjektNummer des zugehörigen TextObjektes ----------------------
long FUNCTYPE EXPORT02 AssociatedTextObjekt (HPROJECT hPr, long ON) 
{
	if (GetDBVersion(hPr) < NEWDBVERSION)
		return -1L;		// alte DB

ErrCode RC;
DB_ADDR_OBL dbaOBL(hPr);
struct obl OBLSatz;

//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ON;
	if ((RC = (ErrCode)z_readrec (&dbaOBL, &OBLSatz)) != EC_OKAY)
		return -1L;

	if (OBLSatz.rmaske & BRELA) {
	// besitzt Begleitobjekt
	DB_ADDR dbaVRT(hPr);
	struct reltyp VRTSatz;

		dbaVRT.file_no = RELTYP;
		dbaVRT.rec_no = OBLSatz.zovor;
		if ((RC = (ErrCode)z_readrec (&dbaVRT, &VRTSatz)) != EC_OKAY)
			return -1L;
		return VRTSatz.zbrela;	// abhängiges TextObjekt
	}

return -1L;
}

// Zugehöriges übergeordnetes Objekt finden -----------------------------------
// liefert 0 bei nicht existierendem Bezugsobjekt,
// negative ObjNummer bei abhängigem Objekt und positive ON bei übergeordnetem
// Objekt
long FUNCTYPE EXPORT02 AssociatedObjekt (HPROJECT hPr, long ON) 
{
	if (GetDBVersion(hPr) < NEWDBVERSION)
		return 0L;		// alte DB

ErrCode RC;
DB_ADDR_OBL dbaOBL(hPr);
struct obl OBLSatz;

//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ON;
	if ((RC = (ErrCode)z_readrec (&dbaOBL, &OBLSatz)) != EC_OKAY)
		return 0L;

	if (OBLSatz.rmaske & (BRELA | BRELP)) {
	// besitzt Begleitobjekt
	DB_ADDR dbaVRT(hPr);
	struct reltyp VRTSatz;

		dbaVRT.file_no = RELTYP;
		dbaVRT.rec_no = OBLSatz.zovor;
		if ((RC = (ErrCode)z_readrec (&dbaVRT, &VRTSatz)) != EC_OKAY)
			return 0L;
		if (OBLSatz.rmaske & BRELA)
			return -VRTSatz.zbrela;	// abhängiges TextObjekt
		else
			return VRTSatz.zbrelp;	// übergeordnetes Objekt
	}

return 0L;
}

}	// extern "C" 

// Finden eines Identifikators im vorgegebenen Feld ---------------------------
extern "C" 
long EXPORT02 FindLong (long *Vals, long numVals, long toSearch) 
{
	for (long i = 0; i < numVals; i++)
		if (Vals[i] == toSearch) return i;

return -1L;
}


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


