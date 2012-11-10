// Enumeration der Einträge des DBHeaders--------------------------------------
// File: ENUMHDR.CXX

extern "C" {
	#include <windows.h>
	#include <switchkc.h>

	#include <risdb.h>
}

// FunktionsPrototypen --------------------------------------------------------
_TRIAS02_ENTRY bool EnumHdrData (BOOL (*pFcn)(char *, BOOL, void *), void *pData);
bool AnalyzeHdrData (char *pKey, BOOL, void *pData);

// lokale Datenstrukturen -----------------------------------------------------
typedef struct tagENUMHDRDATA {
	long lMCode;		// gesuchter MCode
	char *pHdrKey;		// gefundener Text
	short iLen;		// max. TextBufferLänge
} ENUMHDRDATA;

// wird für jeden HeaderEintrag gerufen ---------------------------------------
BOOL AnalyzeHdrData (char *pKey, BOOL, void *pData)
{
ENUMHDRDATA *pEHD = (ENUMHDRDATA *)pData;
HeaderEntry HE (pKey);

	if (HE.Status() == HE_INVALID) return TRUE;	// weiter
	if (HE.EntryLong (-1) == pEHD -> lMCode) {
		strncpy (pEHD -> pHdrKey, HE.EntryKey(), pEHD -> iLen);
		return FALSE;	// fertig, gefunden, abbrechen
	}

return TRUE;	// nichts gefunden, weitermachen
}

// Wiederaufinden eines Headereintrages anhand des HeaderWertes ---------------
BOOL FindHdrEntry (long lMCode, char *pHdrEntry, short iLen)
{
ENUMHDRDATA EHD;

	EHD.lMCode = lMCode;
	EHD.pHdrKey = pHdrEntry;
	EHD.iLen = iLen;

return !EnumHdrData (AnalyzeHdrData, &EHD);
}


// Aufzählen aller vorhandenen HeaderEinträge ---------------------------------
BOOL EnumHdrData (BOOL (*pFcn)(char *, BOOL, void *), void *pData) 
{
ErrCode RC;
DB_ADDR dba;
KEYCONTEXT KC;
ErrInstall EI (WC_NOTFOUND);

        dba.file_no = HEAD;
	RC = (ErrCode)z_keyfirst (&dba, HDIDN);
	if (RC != EC_OKAY) {
	// Fehler aufgetreten
		if (RC == WC_NOTFOUND) 
			RC = EC_OKAY; // nichts gefunden: OK
		return RC == EC_OKAY;		// sonstiger Fehler
	}

BOOL iNext = TRUE;
char pHdidn[16];		// HeaderSchlüssel

	while (iNext) {
		RC = (ErrCode)z_keyread (pHdidn);
		if (RC != EC_OKAY) break;

	// nächsten Schlüssel suchen
		iNext = ((RC = (ErrCode)z_keynext (&dba, HDIDN)) == EC_OKAY);
		GetKeyContext (&KC);

	// Enumeration
		if ((*pFcn)(pHdidn, iNext, pData) == FALSE) 
			return FALSE;

		SetKeyContext (&KC);
	}

return RC == EC_OKAY;
}
