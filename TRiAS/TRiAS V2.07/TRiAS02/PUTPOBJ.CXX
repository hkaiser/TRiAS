// Generieren eines PunktObjektes 
// File: PUTPOBJ.C

#include "trias02p.hxx"

// Generiert ein neues Punktobjekt --------------------------------------------
extern "C" long EXPORT02 FUNCTYPE PutPunktObject (HPROJECT hPr, long *pOBL, long Ident, long X, long Y) 
{
struct obl OBLSatz;
DB_ADDR_OBL dbaOBL(hPr);
long RC;                 // FehlerVariable
long newON = -1L;

	DEX_SetDirtyGeoDB (true);

// Objektsatz lesen/generieren
//	dbaOBL.file_no = OBL;
	if (*pOBL <= 0) {
	// neuen ObjektSatz generieren
		memset (&OBLSatz, '\0', sizeof (OBLSatz));

		if (VERSION0500000E <= GetDBVersion (hPr))	// evtl. GUID generieren
			CoCreateGuid (&OBLSatz.guid);

		__New (dbaOBL, OBLSatz);
		newON = dbaOBL.rec_no;

	// Identifikator bei Bedarf in IDL eintragen
		DBASSERT (PutIdent (hPr, newON, Ident, TPPunkt, &OBLSatz.zoid));
	} else {
	// ObjektSatz einlesen
		newON = dbaOBL.rec_no = *pOBL;
		__Read (dbaOBL, OBLSatz);

	// IdentifikatorSatz richten
		DBASSERT(VerifyIdent(hPr, newON, OBLSatz.zoid, TPPunkt));

	// evtl. bestehende Geometrie löschen
		if (OBLSatz.zokp != 0) {
			DBASSERT (delgip (hPr, *pOBL));		
			OBLSatz.zokp = 0;
		}
	}

// neuen KoordinatenSatz generieren
	DBASSERT (PutPunkt (hPr, newON, X, Y, &OBLSatz.zokp));
	__Write (dbaOBL, OBLSatz);	// ObjektSatz nochmal wegschreiben

// ObjektNummer liefern
	*pOBL = newON;

return S_OKAY;
}

