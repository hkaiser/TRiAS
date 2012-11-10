// Bestimmen der Dimension eines Long-/DoubleWerteFeldes (MerkmalsWerte)
// File: GETMERKL.C

#include "trias02p.hxx"

// GetMerkLen bestimmt die Größe eines Long- oder DoubleMerkmalsFeldes --------
long FUNCTYPE GetMerkLen (HPROJECT hPr, long zvommi, long *Len) 
{
struct mi MISatz;
DB_ADDR dbaMI(hPr);
long MICnt = 0;

long RC;	// FehlerCode

	dbaMI.file_no = MI;
	MISatz.znmi = zvommi;		// erster Satz
	do {
		if ((dbaMI.rec_no = MISatz.znmi) == 0) 
			break;		// Ende der MerkmalsWerte
		__Read (dbaMI, MISatz);	// Satz einlesen
		MICnt++;		// Sätze zählen
	} while (true);

	*Len = MICnt;		// Ergebnis setzen

return S_OKAY;
}

