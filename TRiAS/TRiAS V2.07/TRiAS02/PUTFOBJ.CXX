// Generieren eines FlaechenObjektes 
// File: PUTFOBJ.C

#include "trias02p.hxx"

// Generiert ein neues Flächenobjekt ------------------------------------------
extern "C" 
long EXPORT02 FUNCTYPE PutAreaObject (HPROJECT hPr, long *pOBL, long Ident, long *pX, long *pY, 
				      long *pK, long lCnt, short iKCnt) 
{
struct obl OBLSatz;
DB_ADDR_OBL dbaOBL(hPr);
ErrCode RC;                 // FehlerVariable
long newON = -1L;

	DEX_SetDirtyGeoDB (true);

// Objektsatz generieren
//	dbaOBL.file_no = OBL;
	if (*pOBL <= 0) {
	// ObjektSatz neu erzeugen
		memset (&OBLSatz, '\0', sizeof (OBLSatz));

		if (VERSION0500000E <= GetDBVersion (hPr))	// evtl. GUID generieren
			CoCreateGuid (&OBLSatz.guid);

		__New (dbaOBL, OBLSatz);
		newON = dbaOBL.rec_no;
	
	// Identifikator bei Bedarf in IDL eintragen
		DBASSERT (PutIdent (hPr, newON, Ident, TPFlaeche, &OBLSatz.zoid));
	} else {
	// bestehenden ObjektSatz lesen
		newON = dbaOBL.rec_no = *pOBL;
		__Read (dbaOBL, OBLSatz);

	// IdentifikatorSatz richten
		DBASSERT(VerifyIdent(hPr, newON, OBLSatz.zoid, TPFlaeche));

	// evtl. existierende FlächenGeometrie löschen
		if (OBLSatz.zovoma) {
			DBASSERT (delgif (hPr, *pOBL));
			OBLSatz.zovoma = 0;
		}
	}

// neuen KoordinatenSatz generieren
	DBASSERT (PutMasche (hPr, pX, pY, pK, lCnt, iKCnt, &OBLSatz.zovoma));
	DBASSERT (LinkMasche (hPr, newON, OBLSatz.zovoma));

	__Write (dbaOBL, OBLSatz);	// ObjektSatz nochmal wegschreiben

// ObjektNummer liefern
	*pOBL = newON;

return S_OKAY;
}


long FUNCTYPE PutMasche (HPROJECT hPr, long *pX, long *pY, long *pK, 
			 long lCnt, short iKCnt, long *pzvoma)
{
ErrCode RC;
struct mal MALSatz;
DB_ADDR dbaMAL(hPr);
short i;
long j = 0;

// neuen MaschenSatz erzeugen
	dbaMAL.file_no = MAL;
	memset (&MALSatz, '\0', sizeof (struct mal));

// Bearbeiten der einzelnen Konturen
	for (i = 0; i < iKCnt; i++) {
	long lKNr = 0;
	struct kcont *pCont = (struct kcont *)&MALSatz.mcont;

		DBASSERT (PutKante (hPr, &pX[j], &pY[j], pK[i], &lKNr, i ? NULL : pCont));
		DBASSERT (PutChainEnd (hPr, KFM, &MALSatz.zmkfm, lKNr));
		j += pK[i];
	}
	__New (dbaMAL, MALSatz);

// MaschenSatzNummer liefern
	*pzvoma = dbaMAL.rec_no;

return S_OKAY;
}


// Generierung der Verkettung zum und vom Objekt zur Masche -------------------
long FUNCTYPE LinkMasche (HPROJECT hPr, long lONr, long lMasche)
{
long RC;
struct mal MALSatz;
DB_ADDR dbaMAL(hPr);

// Verkettung von Masche zu Objekt eintragen
	dbaMAL.file_no = MAL;
	dbaMAL.rec_no = lMasche;
	__Read (dbaMAL, MALSatz);

	MALSatz.zmvgo = lONr;
	__Write (dbaMAL, MALSatz);

// Rückverkettung Kanten zu Objekt eintragen
	DBASSERT (LinkKanteM (hPr, lMasche, MALSatz.zmkfm));

return S_OKAY;
}

// Rückverkettung aller Kanten zum MaschenObjekt ------------------------------
long FUNCTYPE LinkKanteM (HPROJECT hPr, long lMasche, long lKFM)
{
long RC;
struct kfm KFMSatz; 
struct kal KALSatz;
DB_ADDR dbaKFM(hPr);
DB_ADDR dbaKAL(hPr);
short iFirst = TRUE;

	dbaKFM.file_no = KFM;
	dbaKAL.file_no = KAL;
	while (lKFM) {
	// VerbindungsSatz lesen
		dbaKFM.rec_no = lKFM;
		__Read (dbaKFM, KFMSatz);
		lKFM = KFMSatz.znkfm;

	// KantenSatz lesen
		dbaKAL.rec_no = KFMSatz.zkfmk;
		__Read (dbaKAL, KALSatz);

	// Rückverkettung eintragen
		if (iFirst) {
		// äußere Kontur positiv, alles andere negativ
			DBASSERT (PutLink (hPr, VZO, &KALSatz.zlm, lMasche));
			iFirst = FALSE;
		} else {
			DBASSERT (PutLink (hPr, VZO, &KALSatz.zrm, lMasche));
		}

	// Kantensatz wieder wegschreiben
		__Write (dbaKAL, KALSatz);
	}

return S_OKAY;
}
