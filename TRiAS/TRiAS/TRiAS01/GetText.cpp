// @doc
// @module GetText.cpp | Lesen der Textinformationen in der *.DBT

#include "trias01p.hxx"

/////////////////////////////////////////////////////////////////////////////
// GetTextMerkmal liest den Text aus den DBT-S‰tzen ein
// ACHTUNG: schlieﬂt eingelesene Zeichenkette nicht unbedingt mit '\0' ab
static HRESULT GetTextFromDBTOld (HPROJECT hPr, long madr, char *mi, long Len) 
{
DB_ADDR dba(hPr);
struct fdbt dbt_satz;		// Satz der Datei '.dbt'
long wf = 0, j;
int flag = FALSE;
long *lpmi = (long *)mi;

// wenn kein TextSatz da ist (Textl‰nge gleich 0)
	if (madr == 0) {
		if (mi) *mi = '\0';
		return S_OK;
	}

	dba.file_no = FDBT;
	dba.rec_no = madr;
	j = 0;
	for (;;) {
	long RC;

		__ReadHR (dba, dbt_satz);
		if (flag == FALSE) {
		// erster Satz: ¸berpr¸fen, ob Text gegeben ist
			wf = ((INT *)(dbt_satz.infof))[0];
			if (-1L == wf) {
				if (Len >= sizeof(INT)) {
				// Text ist im Bezugsobjekt
					*lpmi = ((INT *)(dbt_satz.infof))[1];
					return S_OK;
				} else {
					if (lpmi) *lpmi = -1L;
					return HRESULT_FROM_ERRCODE(S_TEXTTOLONG);
				}
			} 
			if ((size_t)(wf * sizeof(long)) > (size_t)Len) {
				if (mi) 
					*mi = '\0';
				return HRESULT_FROM_ERRCODE(S_TEXTTOLONG);
			}
		} else {
			lpmi[j++] = ((INT *)(dbt_satz.infof))[0];
		}

		for (long i = 1; i < 10; ++i) {
			if (j == wf) break;
			lpmi[j++] = ((INT *)(dbt_satz.infof))[i];
		}
		flag = TRUE;
		if (dbt_satz.zndbtf == 0) 
			break;
		dba.rec_no = dbt_satz.zndbtf;
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Einlesen einer Zeichenkette aus DBT-Satz
HRESULT GetTextFromDBT (HPROJECT hPr, long lAdr, char *pMText, long lLen, BOOL /*fText*/) 
{
// alte Datenbank
	if (LocGetDBVersion(hPr) < VERSION0500000B) 
		return GetTextFromDBTOld (hPr, lAdr, pMText, lLen);
		
// neue Variante 
	{
	DB_ADDR dbaDBT(hPr);
	struct kdbt KDBTSatz;
	int iCurrLen;
	long RC = S_OKAY;
	struct fdbt FDBTSatz;
	DB_ADDR dbaFDBT(hPr);
	
	// wenn kein TextSatz da ist (Textl‰nge gleich 0)
		if (lAdr == 0) {
			if (pMText) *pMText = '\0';
			return S_OK;
		}
	
		dbaDBT.file_no = KDBT;
		dbaDBT.rec_no = lAdr;
		__ReadHR (dbaDBT, KDBTSatz);	// ersten Satz lesen
	
		if (KDBTSatz.llen == -1L) {
		// Text am BezugsObjekt
			if (lLen >= sizeof(INT)) {	// MerkmalsCode lesen
				*(INT *)pMText = ((INT *)(KDBTSatz.info))[0];
				return S_OKAY;
			} else {
				if (pMText) *(INT *)pMText = -1L;
				return HRESULT_FROM_ERRCODE(S_TEXTTOLONG);
			}
		} else if (KDBTSatz.llen < -1L) {
			KDBTSatz.llen = -KDBTSatz.llen;		// #HK980601
		}
		KDBTSatz.llen *= sizeof(long);			// #HK980605
	
	// normaler Text am Textobjekt
		iCurrLen = (sizeof(KDBTSatz.info) < KDBTSatz.llen) ? sizeof(KDBTSatz.info) : KDBTSatz.llen;

		if (iCurrLen > lLen) {
			iCurrLen = (short)lLen;		// TextBuffer zu klein
			RC = HRESULT_FROM_ERRCODE(S_TEXTTOLONG);
		} else
			RC = S_OK;
	
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
			__ReadHR (dbaFDBT, FDBTSatz);	
	
		// TextBuffer sicherstellen
			if (iCurrLen > lLen) {
				iCurrLen = (short)lLen;		// TextBuffer zu klein
				RC = HRESULT_FROM_ERRCODE(S_TEXTTOLONG);
			} else
				RC = S_OK;
	
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
	return S_OK;
}

