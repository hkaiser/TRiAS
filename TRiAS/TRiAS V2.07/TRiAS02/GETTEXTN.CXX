/* Lesen der Textinformationen in der *.DBT                             */
/* File: GETTXTC.C              last update: 05. Juni 1990              */

#include "trias02p.hxx"


// GetText liest den Text aus den DBT-S‰tzen ein ------------------------------
// ACHTUNG: schlieﬂt eingelesene Zeichenkette nicht unbedingt mit '\0' ab
extern "C"
long FUNCTYPE EXPORT02 GetText (HPROJECT hPr, long lAdr, char *pMText, long lLen, BOOL /*fText*/) 
{
// alte Datenbank
	if (GetDBVersion(hPr) < VERSION0500000B) 
		return GetTextOld (hPr, lAdr, pMText, lLen);
		
// neue Variante --------------------------------------------------------------
	{
	DB_ADDR dbaDBT(hPr);
	struct kdbt KDBTSatz;
	long iCurrLen;
	long RC = S_OKAY;
	struct fdbt FDBTSatz;
	DB_ADDR dbaFDBT(hPr);
	
	// wenn kein TextSatz da ist (Textl‰nge gleich 0)
		if (lAdr == 0) {
			if (pMText) *pMText = '\0';
			return S_OKAY;
		}
	
		dbaDBT.file_no = KDBT;
		dbaDBT.rec_no = lAdr;
		__Read (dbaDBT, KDBTSatz);	// ersten Satz lesen
	
		if (KDBTSatz.llen == -1L) {
		// Text am BezugsObjekt
			if (lLen >= sizeof(INT)) {	// MerkmalsCode lesen
				*(INT *)pMText = ((INT *)(KDBTSatz.info))[0];
				return S_OKAY;
			} else {
				if (pMText) *(INT *)pMText = -1L;
				return S_TEXTTOLONG;
			}
		} else if (KDBTSatz.llen < -1L) {
			KDBTSatz.llen = -KDBTSatz.llen;		// #HK980601
		}
		KDBTSatz.llen *= sizeof(long);			// #HK980605

	// normaler Text am Textobjekt
		iCurrLen = (sizeof(KDBTSatz.info) < KDBTSatz.llen) ? sizeof(KDBTSatz.info) : KDBTSatz.llen;
		if (iCurrLen > lLen) {
			iCurrLen = lLen;		// TextBuffer zu klein
			RC = S_TEXTTOLONG;
		} else
			RC = S_OKAY;
	
	    strncpy (pMText, KDBTSatz.info, iCurrLen);
	    pMText[iCurrLen] = '\0';		// sicher abschlieﬂen
		pMText += iCurrLen;
		KDBTSatz.llen -= iCurrLen;
		lLen -= iCurrLen;
		if (lLen <= 0) return RC;		// TextBuffer voll
				        
	// bei Bedarf weitere Datens‰tze lesen
		dbaFDBT.file_no = FDBT;			// FolgeSatz
		dbaFDBT.rec_no = KDBTSatz.zndbt;
		while (KDBTSatz.llen > 0 && 0 != dbaFDBT.rec_no) {	// doppelt testen, wegen BUG bis VERSION0500000B
		// MerkmalsSatz einlesen
			iCurrLen = sizeof(FDBTSatz.infof) < KDBTSatz.llen ? sizeof(FDBTSatz.infof) : KDBTSatz.llen;
			__Read (dbaFDBT, FDBTSatz);	
	
		// TextBuffer sicherstellen
			if (iCurrLen > lLen) {
				iCurrLen = lLen;		// TextBuffer zu klein
				RC = S_TEXTTOLONG;
			} else
				RC = S_OKAY;
	
		// Text umkopieren
			strncpy (pMText, FDBTSatz.infof, iCurrLen);
			pMText[iCurrLen] = '\0';
			
			pMText += iCurrLen;
			KDBTSatz.llen -= iCurrLen;
			lLen -= iCurrLen;
			if (lLen <= 0) return RC;		// TextBuffer voll
	
		// n‰chster Satz
			dbaFDBT.rec_no = FDBTSatz.zndbtf;
		}
	}
	return S_OKAY;
}
