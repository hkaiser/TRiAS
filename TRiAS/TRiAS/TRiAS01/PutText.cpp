// @doc
// @module PutText.cpp | Füllen Textfeld(Merkmalsinformation)

#include "trias01p.hxx"

/////////////////////////////////////////////////////////////////////////////
// PUTTXT schreibt einen gegebenen Text in die GeoDB als DBT-Satz (-Sätze) weg.
HRESULT PutTextToDBTOld (HPROJECT hPr, const char *MText, short wf, long *madr) 
{
long satznr;
DB_ADDR dba (hPr);
struct fdbt dbt_satz;    /* Satz der Datei '.dbt' */
register int flag = FALSE;
int RC;
long *mi = (long *)MText;

	dba.file_no = FDBT;
	if (wf >= 0) {		// erlauben von Merkmalen mit 0 Zeichen
	// Text ist gegeben
		dba.rec_no = 0L;
		do {
			DBASSERTHR (DBPageZeroAlloc(hPr, RecordTable(hPr, FDBT) -> rt_file, &satznr));
			if (dba.rec_no != 0) {
				dbt_satz.zndbtf = satznr;
				__WriteHR (dba, dbt_satz);
			} else 
				*madr = satznr;
			dba.rec_no = satznr;
			__ReadHR (dba, dbt_satz);

			if (flag == FALSE) *((INT *)(&dbt_satz.infof[0])) = wf;
			else {
				*((INT *)(&dbt_satz.infof[0])) = *mi++;
				--wf;
			}
                        
			for (int i = 1; i < 10; ++i) {
				if (--wf < 0) break;
				*((INT *)(&dbt_satz.infof[i*sizeof(INT)])) = *mi++;
			}
			flag = TRUE;
		} while (wf > 0);
		dbt_satz.zndbtf = 0L;
		__WriteHR (dba, dbt_satz);
	} else {
	// kein Text gegeben, MText zeigt auf long mit MerkmalsKode
	// unter dem im Bezugsobjekt der Text abgespeichert ist

		DBASSERTHR (DBPageZeroAlloc(hPr, RecordTable(hPr, FDBT) -> rt_file, &satznr));
		*madr = satznr;
		dba.rec_no = satznr;
		__ReadHR (dba, dbt_satz);
		((INT *)dbt_satz.infof)[0] = -1L;	// Kennung für MCode
		((INT *)dbt_satz.infof)[1] = *mi;	// MCode
		dbt_satz.zndbtf = 0;			// kein Folgesatz
		__WriteHR (dba, dbt_satz);
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// 
HRESULT PutTextToDBT (HPROJECT hPr, const char *pMText, short wf, long *madr, long zvom, BOOL fIndText)
{
// GeoDB Version abfragen
	if (LocGetDBVersion(hPr) < VERSION0500000B)
		return PutTextToDBTOld (hPr, pMText, wf, madr);

// neue Variante 
// 1. Satz bearbeiten
	{
	struct kdbt KDBTSatz;
	DB_ADDR dbaDBT(hPr);
	long lLen = sizeof(long)*wf;	// wf enthält die Anzahl der longs
	int iCurrLen = (int)(sizeof(KDBTSatz.info) < lLen ? sizeof(KDBTSatz.info) : lLen);
	long RC = S_OK;
	struct fdbt FDBTSatz;
	DB_ADDR dbaFDBT(hPr);
	
		dbaDBT.file_no = KDBT;
	
	// ersten Satz füllen
		KDBTSatz.llen = fIndText ? -wf : wf;	// Gesamtlänge des Textmerkmales
		KDBTSatz.zmivom = zvom;						// Rückverweis zum VOMSatz
		if (lLen == -1L) {
		// kein Text gegeben, MText zeigt auf long mit MerkmalsKode
		// unter dem im Bezugsobjekt der Text abgespeichert ist
			((INT *)KDBTSatz.info)[0] = *(INT *)pMText;
		} else
			strncpy (KDBTSatz.info, pMText, iCurrLen);
		__NewHR (dbaDBT, KDBTSatz);	// wegschreiben
		
		*madr = dbaDBT.rec_no;
		lLen -= iCurrLen;	// restliche Zeichenkette
		pMText += iCurrLen;
		
	// bei Bedarf weitere Datensätze generieren	
		dbaFDBT.file_no = FDBT;	// FolgeSatz
		dbaDBT.file_no = FDBT;	// FolgeSatz
	
		while (lLen > 0) {
		// FolgeSatz anlegen
			iCurrLen = (short)(sizeof(FDBTSatz.infof) < lLen ? 
					sizeof(FDBTSatz.infof) : lLen);
			memset (&FDBTSatz, '\0', sizeof(FDBTSatz));		// initialisieren
			strncpy (FDBTSatz.infof, pMText, iCurrLen);
			__NewHR (dbaFDBT, FDBTSatz);
			
		// vorhergehenden Satz korrigieren
			__ReadHR (dbaDBT, FDBTSatz);
			FDBTSatz.zndbtf = dbaFDBT.rec_no;
			__WriteHR (dbaDBT, FDBTSatz);
			
		// nächste Runde vorbereiten
			dbaDBT = dbaFDBT;	// vorhergehende Adresse merken
			lLen -= iCurrLen;	// restliche Zeichenkette
			pMText += iCurrLen;
		}
	}
	if (fIndText && VERSION0500000B == ::LocGetDBVersion (hPr)) 
		::ModifyDBVersion (hPr, VERSION0500000C);	// Version hochsetzen
	return S_OK;
}

