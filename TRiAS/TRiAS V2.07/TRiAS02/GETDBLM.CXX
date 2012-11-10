// Einlesen der Merkmalsinformation als DoubleWerteFeld
// File: GETDBLM.C

#include "trias02p.hxx"

#include <idtdb.h>

// GetDoubleMerk liest ein DoubleMerkmalsfeld der Länge Len -------------------
long FUNCTYPE EXPORT02 GetMerkDouble (HPROJECT hPr, long zvommi, double *DFeld, long Len) 
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
		DFeld[i] = *(double *)MISatz.mw;
	} while (i++ < Len);

return S_OKAY;
}
