// Schreiben eines neuen PunktSatzes (POL) 
// File: PUTPKT.C

#include "trias02p.hxx"

// Generiert einen neuen singulären Punkt -------------------------------------
extern "C" long EXPORT02 FUNCTYPE PutPunkt (HPROJECT hPr, long ONr, long X, long Y, long *pPOL) 
{
struct pol POLSatz;
DB_ADDR dbaPOL(hPr);
ErrCode RC;                 // FehlerVariable

	DEX_SetDirtyGeoDB (true);

// neuen POLSatz generieren
	dbaPOL.file_no = POL;
	memset (&POLSatz, '\0', sizeof(POLSatz));
	POLSatz.kpkrd.px = X;		// Koordinaten merken
	POLSatz.kpkrd.py = Y;
	__New (dbaPOL, POLSatz);

// Rückverkettung der Geometrie in Objektliste vornehmen
	DBASSERT (PutLink (hPr, VGO, &POLSatz.zpvgo, ONr));
	__Write (dbaPOL, POLSatz);

// SatzNummer liefern
	*pPOL = dbaPOL.rec_no;

return S_OKAY;
}

