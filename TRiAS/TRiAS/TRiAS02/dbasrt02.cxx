// Diverse Testroutinen -------------------------------------------------------
// File: DBASRT02.CXX

#include "trias02p.hxx"

#include <errfkt.hxx>
#include <objstat.hxx>

bool EXPORT02 IsValidONr (LONG lONr)
{
#if !defined(_FORCE_LEGACY_CODE)
#if defined(_DEBUG)
	return 0L != lONr && -1L != lONr;
#else
	return true;
#endif // _DEBUG
#else
	if (0L >= lONr) return false;	// sowieso Blödsinn

#if defined(_DEBUG) && defined(WIN32)
// DEX_GetObjectStatus ruft ebenfalls IsValidONr !!
static long g_lValidONrSem = -1;

	if (InterlockedIncrement (&g_lValidONrSem) > 0) {
		InterlockedDecrement (&g_lValidONrSem);
		return true;
	}

HPROJECT hOldPr = z_activate (hPr);

	if (OS_Temp == DEX_GetObjectStatus(lONr)) {
		if (NULL != hOldPr) z_activate (hOldPr);
		InterlockedDecrement (&g_lValidONrSem);
		return true;		// temporäres Objekt gilt als gültig
	}
	InterlockedDecrement (&g_lValidONrSem);

struct obl OBLSatz;
DB_ADDR_OBL dbaOBL(hPr);

//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = lONr;

ErrInstall EI1(EC_DELRECORD);
ErrInstall EI2(EC_INVADDR);
ErrCode RC = (ErrCode)z_readrec(&dbaOBL, &OBLSatz);

	if (NULL != hOldPr) z_activate (hOldPr);
	if (EC_OKAY != RC && EMIgnore == err_type (long(RC)))
		RC = EC_OKAY;		// Fehler anderweitig abgefangen

	return (EC_OKAY == RC) ? true : false;
#else
	return true;	// NDEBUG: nicht so genau testen
#endif // WIN32 && _DEBUG
#endif // _!FORCE_LEGACY_CODE
}

bool EXPORT02 IsValidIdent (LONG lIdent)
{
	return 0L != lIdent && -1L != lIdent;
}

bool EXPORT02 IsValidMCode (LONG lMCode)
{
	return 0L != lMCode && -1L != lMCode;
}

bool EXPORT02 IsValidRCode (LONG lRCode)
{
	return 0L != lRCode && -1L != lRCode;
}



