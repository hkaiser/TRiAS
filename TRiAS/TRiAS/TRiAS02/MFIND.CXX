// Suchen eines gegebenen Beschreibungssatzes in der PBD
// File: MFIND.C

#include "trias02p.hxx"

#include <ctype.h>
#include <idtdb.h>

// allgemeine Routine zum Auffinden eines Beschreibungssatzes -----------------
extern "C" 
long FUNCTYPE mfind (HPROJECT hPr, short Typ, long Code, long *pSatz) 
{
	switch (tolower (Typ)) {
	case 'i':
		return mfindi (hPr, Code, pSatz);
	case 'm':
		return mfindm (hPr, Code, pSatz);
	case 'r':
		return mfindr (hPr, Code, pSatz);
	default:
		return db_error (S_BADTYP, RC_MFIND);
	}
}


// Finden des Beschreibungssatzes für einen Identifikator ---------------------
long FUNCTYPE mfindi (HPROJECT hPr, long Ident, long *pSatz) 
{
DB_ADDR dbaIDL (hPr);
long RC;

	dbaIDL.file_no = MID;
	DBASSERT (z_keyfind (&dbaIDL, IDS, &Ident));
	*pSatz = dbaIDL.rec_no;

return S_OKAY;
}

// Finden des Beschreibungssatzes für einen MerkmalsCode ----------------------
long FUNCTYPE mfindm (HPROJECT hPr, long MCode, long *pSatz) 
{
DB_ADDR dbaMMK (hPr);
long RC; 

	dbaMMK.file_no = MMK;
	DBASSERT (z_keyfind (&dbaMMK, MKS, &MCode));
	*pSatz = dbaMMK.rec_no;

return S_OKAY;
}

// Finden des Beschreibungssatzes für eine Relation ---------------------------
long FUNCTYPE mfindr (HPROJECT hPr, long RCode, long *pSatz) 
{
DB_ADDR dbaMRL (hPr);
long RC;

	dbaMRL.file_no = MRL;
	DBASSERT (z_keyfind (&dbaMRL, PRIREL, &RCode));
	*pSatz = dbaMRL.rec_no;

return S_OKAY;
}

