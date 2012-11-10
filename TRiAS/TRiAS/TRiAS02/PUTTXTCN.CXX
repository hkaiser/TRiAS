/* Fuellen Textfeld(Merkmalsinformation)                                */
/* File: PUTTXTC.CXX							*/

#include "trias02p.hxx"

// PUTTXT schreibt einen gegebenen Text in die GeoDB als DBT-Satz (-Sätze) weg.
extern "C" 
long FUNCTYPE EXPORT02 PutTextEx (HPROJECT hPr, const char *pMText, short wf, long *madr, 
				  long zvom, BOOL fIndText)
{
// GeoDB Version abfragen
	if (GetDBVersion(hPr) < VERSION0500000B)
		return PutText (hPr, pMText, wf, madr);

// neue Variante --------------------------------------------------------------
// 1. Satz bearbeiten
	{
	struct kdbt KDBTSatz;
	DB_ADDR dbaDBT(hPr);
	long lLen = sizeof(long)*wf;	// wf enthält die Anzahl der longs
	short iCurrLen = (short)(sizeof(KDBTSatz.info) < lLen ? sizeof(KDBTSatz.info) : lLen);
	long RC = S_OKAY;
	struct fdbt FDBTSatz;
	DB_ADDR dbaFDBT(hPr);
	
		dbaDBT.file_no = KDBT;
		memset (&KDBTSatz, '\0', sizeof(KDBTSatz));
	
	// ersten Satz füllen
		KDBTSatz.llen = fIndText ? -wf : wf;	// Gesamtlänge des Textmerkmales
		KDBTSatz.zmivom = zvom;						// Rückverweis zum VOMSatz
		if (lLen == -1L) {
		// kein Text gegeben, MText zeigt auf long mit MerkmalsKode
		// unter dem im Bezugsobjekt der Text abgespeichert ist
			((INT *)KDBTSatz.info)[0] = *(INT *)pMText;
		} else
			strncpy (KDBTSatz.info, pMText, iCurrLen);
		__New (dbaDBT, KDBTSatz);	// wegschreiben
		
		*madr = dbaDBT.rec_no;
		lLen -= iCurrLen;	// restliche Zeichenkette
		pMText += iCurrLen;
		
	// bei Bedarf weitere Datensätze generieren	
		dbaFDBT.file_no = FDBT;	// FolgeSatz
	
		while (lLen > 0) {
		// FolgeSatz anlegen
			iCurrLen = (short)(sizeof(FDBTSatz.infof) < lLen ? 
					sizeof(FDBTSatz.infof) : lLen);
			memset (&FDBTSatz, '\0', sizeof(FDBTSatz));		// initialisieren
			strncpy (FDBTSatz.infof, pMText, iCurrLen);
			__New (dbaFDBT, FDBTSatz);
			
		// vorhergehenden Satz korrigieren
			__Read (dbaDBT, FDBTSatz);
			FDBTSatz.zndbtf = dbaFDBT.rec_no;
			__Write (dbaDBT, FDBTSatz);
			
		// nächste Runde vorbereiten
			dbaDBT = dbaFDBT;	// vorhergehende Adresse merken
			lLen -= iCurrLen;	// restliche Zeichenkette
			pMText += iCurrLen;
		}
	}
		 
	if (fIndText && VERSION0500000B == ::GetDBVersion (hPr)) 
		::ModifyDBVersion (hPr, VERSION0500000C);	// Version hochsetzen

	return S_OKAY;
}

