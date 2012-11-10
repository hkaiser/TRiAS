// Einlesen der BeschreibungsInformation fuer einen MerkmalsCode
// File: MGETKM.C

#include "trias02p.hxx"

#include <ctype.h>
#include <idtdb.h>

extern "C" 
long FUNCTYPE mgetkm (HPROJECT hPr, long Satz, long *pMCode, short *pMTyp, 
		      long *pWF, long *pVon, long *pBis, long *pNext) 
{
DB_ADDR dbaMMK (hPr);
long RC;
long PBDVersion = GetDBVersion (hPr);

	dbaMMK.file_no = MMK;
	dbaMMK.rec_no = Satz;

	if (PBDVersion <= PBD030000001) {
	struct mmk_001 MMK001Satz;

		__Read (dbaMMK, MMK001Satz);

	// Beschreiben der geforderten Parameter (Resultat)
		if (pMTyp) *pMTyp = (char)MMK001Satz.mtyp[0];
		if (pWF) *pWF = MMK001Satz.wfakm;
		if (pMCode) *pMCode = MMK001Satz.mks;
		if (pVon) memcpy (pVon, &MMK001Satz.wvon, sizeof(long)*2);
		if (pBis) memcpy (pBis, &MMK001Satz.wbis, sizeof(long)*2);
		if (pNext) {
			if (tolower(MMK001Satz.mtyp[0]) != 'f') 
				*pNext = MMK001Satz.wbis.iwbis[1];
			else
				*pNext = 0;	// kein FolgeSatz
		}
	} else if (PBDVersion >= PBD030000002) {
	struct mmk MMKSatz;

		__Read (dbaMMK, MMKSatz);

	// Beschreiben der geforderten Parameter (Resultat)
		if (pMTyp) memcpy (pMTyp, MMKSatz.mtyp, sizeof(short));
		if (pWF) *pWF = MMKSatz.wfakm;
		if (pMCode) *pMCode = MMKSatz.mks;
		if (pVon) memcpy (pVon, &MMKSatz.wvon, sizeof(long)*2);
		if (pBis) memcpy (pBis, &MMKSatz.wbis, sizeof(long)*2);
		if (pNext) {
			if (tolower(MMKSatz.mtyp[0]) != 'f') 
				*pNext = MMKSatz.wbis.iwbis[1];
			else
				*pNext = 0;	// kein FolgeSatz
		}
	}

return S_OKAY;
}


