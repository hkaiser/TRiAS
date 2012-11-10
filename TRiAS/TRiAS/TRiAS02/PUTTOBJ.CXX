// Schreiben eines TextObjektes -----------------------------------------------
// File: PUTTOBJ.CXX

#include "trias02p.hxx"

// Generiert ein neues Textobjekt ---------------------------------------------
extern "C" 
long EXPORT02 FUNCTYPE PutTextObject (
	HPROJECT hPr, long *pOBL, long Ident, long MCode, 
	long X, long Y, char *pText, BOOL fIndObjProp) 
{
struct obl OBLSatz;
DB_ADDR_OBL dbaOBL(hPr);
ErrCode RC;                 // FehlerVariable
long newON = -1L;

	DEX_SetDirtyGeoDB (true);

//	dbaOBL.file_no = OBL;
	if (*pOBL <= 0) {
	// Objektsatz generieren
		memset (&OBLSatz, '\0', sizeof (OBLSatz));

		if (VERSION0500000E <= GetDBVersion (hPr))	// evtl. GUID generieren
			CoCreateGuid (&OBLSatz.guid);

		__New (dbaOBL, OBLSatz);
		newON = dbaOBL.rec_no;

	// Identifikator bei Bedarf in IDL eintragen
		DBASSERT (PutIdent (hPr, newON, Ident, TPText, &OBLSatz.zoid));
	} else {
	// ObjektSatz einlesen
		newON = dbaOBL.rec_no = *pOBL;
		__Read (dbaOBL, OBLSatz);

	// IdentifikatorSatz richten
		DBASSERT(VerifyIdent(hPr, newON, OBLSatz.zoid, TPText));

	// evtl. bestehende Geometrie löschen
		if (OBLSatz.zokp != 0) {
			DBASSERT (delgip (hPr, *pOBL));		
			OBLSatz.zokp = 0;
		}
	}

// neuen KoordinatenSatz generieren
	DBASSERT (PutPunkt (hPr, newON, X, Y, &OBLSatz.zokp));

	OBLSatz.status |= SB_TEXTOBJ;	// Objekt ist TextObjekt
	if (fIndObjProp)
		OBLSatz.status |= SB_TEXTOBJIND;	// Objekt ist indirektes TextObjekt
	__Write (dbaOBL, OBLSatz);	// ObjektSatz wegschreiben

// Text wegschreiben
ErrInstall EI (WC_MCODEEXISTS);

	if (pText == NULL) {
		if (GetDBVersion(hPr) < VERSION05000008) {
			DBASSERT (PutText (hPr, " ", 1, &OBLSatz.zovom));
			__Write (dbaOBL, OBLSatz);	// ObjektSatz wegschreiben
		} else {
			if ((RC = (ErrCode)PutMiText (hPr, MCode, newON, OBL_OLD, " ", TRUE)) != EC_OKAY &&
			    RC != WC_MCODEEXISTS)
				return RC;
		}
	} else {
		if (GetDBVersion(hPr) < VERSION05000008) {
			DBASSERT (PutText (hPr, pText, (strlen (pText) + 3)/4, &OBLSatz.zovom));
			__Write (dbaOBL, OBLSatz);	// ObjektSatz wegschreiben
		} else {
		char *pT = new char [strlen(pText)+1];

			if (pT) AnsiToOem (pText, pT);
			RC = (ErrCode)PutMiText (hPr, MCode, newON, OBL_OLD, pT ? pT : pText, TRUE);
			DELETE_OBJ(pT);
			if (RC != EC_OKAY && RC != WC_MCODEEXISTS)
				return RC;
		}
	}

// ObjektNummer liefern
	*pOBL = newON;

return EC_OKAY;
}

