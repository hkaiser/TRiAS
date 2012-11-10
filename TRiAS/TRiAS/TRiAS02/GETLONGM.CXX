// Einlesen der Merkmalsinformation als LongWerteFeld
// File: GETLONGM.C

#include "trias02p.hxx"

// GetLongMerk liest ein LongMerkmalsfeld der Länge Len ein -------------------
long FUNCTYPE EXPORT02 GetMerkLong (HPROJECT hPr, long zvommi, long *LFeld, long Len) 
{
struct mi MISatz;
DB_ADDR dbaMI(hPr);
long i = 0;

long RC;	// FehlerCode

	dbaMI.file_no = MI;
	MISatz.znmi = zvommi;
	do {
	// Satz einlesen
		if ((dbaMI.rec_no = MISatz.znmi) == 0)
			break;		// Ende der Kette
		__Read (dbaMI, MISatz);

	// MerkmalsWert umkopieren
		LFeld[i] = MISatz.mw[0];
	} while (i++ < Len);

return S_OKAY;
}
