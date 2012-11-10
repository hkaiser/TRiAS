// Schreiben eines KomplexObjektes 
// File: PUTKOBJ.C

#include "trias02p.hxx"

// Generiert ein neues KomplexObjekt ------------------------------------------
extern "C" long EXPORT02 FUNCTYPE PutKomplexObject (HPROJECT hPr, 
			long *pOBL, long Ident, long RCode, 
			short iRTyp, short iCnt, long *pObjs) 
{
struct obl OBLSatz;
DB_ADDR_OBL dbaOBL(hPr);
ErrCode RC;                 // FehlerVariable
long newON = -1L;
short i;

	DEX_SetDirtyGeoDB (true);

// neuen Objektsatz generieren
//	dbaOBL.file_no = OBL;
//	memset (&OBLSatz, '\0', sizeof (OBLSatz));

	if (VERSION0500000E <= GetDBVersion (hPr))	// evtl. GUID generieren
		CoCreateGuid (&OBLSatz.guid);

	__New (dbaOBL, OBLSatz);
	newON = dbaOBL.rec_no;

// Identifikator bei Bedarf in IDL eintragen
	DBASSERT (PutIdent (hPr, newON, Ident, TPKO, &OBLSatz.zoid));

	__Write (dbaOBL, OBLSatz);	// ObjektSatz schreiben

// neue Relationen generieren
	for (i = 0; i < iCnt; i++) {
	// für jedes gegebene Objekt
		DBASSERT (PutRelation (hPr, newON, pObjs[i], RCode, iRTyp));
	}

// ObjektNummer liefern
	*pOBL = newON;

return S_OKAY;
}

