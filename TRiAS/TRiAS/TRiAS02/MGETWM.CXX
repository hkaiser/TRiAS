// Einlesen der BeschreibungsInformationen zu einem Merkmalsfolgesatz 
// File: MGETWM.C

#include "trias02p.hxx"

#include <ctype.h>
#include <idtdb.h>

extern "C" 
long FUNCTYPE mgetwm (HPROJECT hPr, long Satz, long *pMWert, long *pNext) 
{
DB_ADDR dbaMMW (hPr);
long RC;
long PBDVersion = GetDBVersion (hPr);

// gesuchten Satz einlesen
	dbaMMW.file_no = MMW;
	dbaMMW.rec_no = Satz;

	if (PBDVersion <= PBDVERSION03000001) {
	struct mmw_001 MMW001Satz;

		__Read (dbaMMW, MMW001Satz);

	// Daten kopieren
		if (pMWert) *pMWert = MMW001Satz.wkode;
		if (pNext) *pNext = MMW001Satz.znwert;
	} else if (PBDVersion >= PBDVERSION03000002) {
	struct mmw MMWSatz;

		__Read (dbaMMW, MMWSatz);

	// Daten kopieren
		if (pMWert) *pMWert = MMWSatz.wkode;
		if (pNext) *pNext = MMWSatz.znwert;
	}

return S_OKAY;
} 
