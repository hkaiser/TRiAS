// Einlesen der BeschreibungsInformationen zu einer Relationsbeschreibung 
// File: MGETKR.C

#include "trias02p.hxx"

#include <idtdb.h>

extern "C" 
long FUNCTYPE mgetkr (HPROJECT hPr, long Satz, long *pRCode, short *pRTyp) 
{
DB_ADDR dbaMRL (hPr);
long RC;
long PBDVersion = GetDBVersion (hPr);

// gesuchten Satz einlesen
	dbaMRL.file_no = MRL;
	dbaMRL.rec_no = Satz;

	if (PBDVersion <= PBD030000001) {
	struct mrl_001 MRL001Satz;

		__Read (dbaMRL, MRL001Satz);

	// Daten kopieren
		if (pRCode) *pRCode = MRL001Satz.prirel;
		if (pRTyp) *pRTyp = MRL001Satz.reltyp;
	} else if (PBDVersion >= PBD030000002) {
	struct mrl MRLSatz;

		__Read (dbaMRL, MRLSatz);

	// Daten kopieren
		if (pRCode) *pRCode = MRLSatz.prirel;
		if (pRTyp) *pRTyp = MRLSatz.reltyp;
	}

return S_OKAY;
} 
