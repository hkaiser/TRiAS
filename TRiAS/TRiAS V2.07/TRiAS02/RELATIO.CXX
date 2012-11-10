// Zusammenstellen aller Objekte, die in thematischer Relation zu gegebenen
// Objekt stehen
// File: RELATION.CXX

#include "trias02p.hxx"

#include <switchkc.h>
#include <objfeld.hxx>
#include <db.hxx>

#include "relliste.hxx"
#include "getrcode.hxx"

// Diese Funktion untersucht ein vorgegebenes Objekt und liefert alle
// Objektnummern, die mit diesem Objekt in thematischer Relation stehen
ErrCode GeoDB :: RelInfo (long ON, ObjFeld &Objekte) 
{
ErrCode RC;

// überprüfen, ob DB eröffnet ist
	if (!isOpened())
		return (ErrCode)db_error ((int)EC_NOOPEN, (int)RC_RelInfo);

// überprüfen, ob richtige Version der DB vorliegt
	if (GetDBVersion() < NEWDBVERSION) return EC_OKAY;

CActDB ActDB (*this);		// DB aktivieren
RCodes RelC;			// Alle Relationen dieses Objektes finden

	DBASSERT (GetRelationsCodes (DBDesc(), ON, RelC));

// für jede gefundene Relation zugehörige Objekte bestimmen
CTable t(RelC);

	for (t.First(); t.Valid(); t.Next()) {
	RCodeLock l(t);

		if (!l) continue;
		DBASSERT (GetRelation (DBDesc(), ON, l -> RelCode(), Objekte));

	// Windows abfragen
		App :: Exec (ExecWhileEvent);
		ActDB.ReActivate();
	}

return EC_OKAY;
}

// SchnittstellenFunktionen, die Objekte entsprechend lRCode, iRTyp enumerieren
extern "C" {

inline BOOL PASCAL CallRelEnumFunc (ENUMRELOBJPROC pF, long lONr, long lRCode,
				    short iRTyp, void *pD)
{
	return ((ENUMRELOBJCALLBACK)pF)(lONr, lRCode, iRTyp, pD);
}

}

Bool GeoDB :: EnumRelationObjs (ENUMRELATIONOBJS *pERO)
{
	if (pERO -> lONr <= 0) return FALSE;

ObjRelFeld RelC;	// RCodeInfo für ein Objekt
ErrInstall EI (WC_NOTFOUND);

	if (pERO -> lRCode != -1) {
	// nur ein RelationsCode

		if (GetRelation (DBDesc(), pERO -> lONr, pERO -> lRCode, RelC) != EC_OKAY)
			return FALSE;
	} else {
	// alle Relationen

		if (RelInfo (pERO -> lONr, RelC) != EC_OKAY)
			return FALSE;
	}

// eigentliche Enumeration mit RTypMatching
CRing r(RelC);

	for (r.First(); r.Valid(); r.Next()) {
	ObjRelNummerLock l(r);

		if (!l || !(l -> RelTyp() & pERO -> iRTyp)) 
			continue;
		if (CallRelEnumFunc (pERO -> eFcn, l -> _ON, 
				     l -> RelCode(), l -> RelTyp(),
				     pERO -> pData) == FALSE) 
		{
			return FALSE;
		}
	}

return TRUE;
}


// Enumeration aller RCodes einer Datenbasis ----------------------------------
extern "C" {

inline BOOL PASCAL EnumRCodesCallBack (ENUMNOKEYLONGPROC pF, long lRCode, Bool iNext,
				       void *pD)
{
	return ((ENUMNOKEYLONGCALLBACK)pF)(lRCode, iNext, pD);
}

}

Bool GeoDB :: EnumRCodes (ENUMNOKEYLONGPROC pFcn, void *pData)
{
ErrCode EC;
DB_ADDR dba(DBDesc());
KEYCONTEXT KC;
ErrInstall EI (WC_NOTFOUND);	// Fehler WC_NOTFOUND ignorieren

// DatenBasis aktivieren
CActDB ActDB (*this);

// ersten RCode suchen
	EC = (ErrCode)z_keyfirst (&dba, RAT);
	if (EC != EC_OKAY) {
	// Fehler aufgetreten
		if (EC == WC_NOTFOUND) 
			EC = EC_OKAY;         // nichts gefunden: OK
		return EC == EC_OKAY;         // sonstiger Fehler
	}

// für alle weiteren RCodes
Bool iNext = TRUE;
Bool iRC = TRUE;

	while (iNext && iRC) {
	long lRCode;

	// ID aus Schlüsseldatei lesen
		EC = (ErrCode)z_keyread (dba.db_no, &lRCode);
		if (EC != EC_OKAY) break;

	// nächsten Schlüssel suchen
		EC = (ErrCode)z_keynext (&dba, RAT);
		if (EC != EC_OKAY)
			iNext = FALSE;

		GetKeyContext (&KC);
		iRC = EnumRCodesCallBack (pFcn, lRCode, iNext, pData);
		ActDB.ReActivate();		// fär alle Fälle
		SetKeyContext (&KC);
	}
	if (EC == WC_NOTFOUND) 
		EC = EC_OKAY;           // nichts mehr gefunden: OK

return iRC ? EC == EC_OKAY : iRC;
}


