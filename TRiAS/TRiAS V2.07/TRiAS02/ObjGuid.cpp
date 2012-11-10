// Verwaltung von ObjektGUID's
// File: OBJGUID.CPP

#include "trias02p.hxx"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif // _DEBUG

#define GUID_CCH	39	// Characters in string form of guid, including '\0'

///////////////////////////////////////////////////////////////////////////////
// Schreiben/Lesen eines Merkmales
bool ReadTextMerkmal (short iTTyp, DWORD lTarget, long lMCode, char *pText, short iLen)
{
TARGETMERKMAL gm;

	INITSTRUCT(gm, TARGETMERKMAL);
	gm.lTarget = (LPARAM)lTarget;
	gm.lMCode = lMCode;
	gm.imaxLen = pText != NULL ? iLen : 0;
	gm.pMText = pText;
	gm.iTTyp = iTTyp;
	if (DEX_GetTextMerkmal (gm) == NULL)
		return false;

	return true;
}

bool WriteTextMerkmal (short iTTyp, long lTarget, long lMCode, char *pText, short iFlags = 0)
{
TARGETMERKMALEX gm;

	INITSTRUCT(gm, TARGETMERKMALEX);
	gm.lTarget = (LPARAM)lTarget;
	gm.lMCode = lMCode;
	gm.imaxLen = pText != NULL ? strlen (pText) : 0;
	gm.pMText = pText;
	gm.iTTyp = iTTyp;
	gm.iFlags = iFlags;
	if (DEX_ModTextMerkmal (gm) != EC_OKAY)
		return false;

	return true;
}

///////////////////////////////////////////////////////////////////////////////
// eigentliche Funktionen
HRESULT GeoDB::GetObjectGUID (LONG lONr, struct _GUID *pGuid)
{
	TX_ASSERT(VERSION0500000E <= GetDBVersion());
	TX_ASSERT(NULL != pGuid);

struct obl OBLSatz;
DB_ADDR_OBL dbaOBL(DBDesc());
ErrCode RC = EC_OKAY;

//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = lONr;
	__ReadHR (dbaOBL, OBLSatz);
	
	*pGuid = OBLSatz.guid;
	return S_OK;
}

HRESULT GeoDB::GetObjectGUIDFeature (LONG lONr, LONG lMCode, struct _GUID *pGuid)
{
	TX_ASSERT(VERSION0500000E > GetDBVersion());
	TX_ASSERT(0L != lMCode);
	TX_ASSERT(NULL != pGuid);

	USES_CONVERSION;

HRESULT hr = S_FALSE;
char cbBuffer[GUID_CCH];

	if (ReadTextMerkmal (TT_Objekt, lONr, lMCode, cbBuffer+1, sizeof(cbBuffer))) {

		cbBuffer[0] = '{';
		cbBuffer[37] = '}';
		return CLSIDFromString(A2OLE(cbBuffer), pGuid);

	} else {
	OLECHAR coleBuffer[GUID_CCH];

		hr = CoCreateGuid (pGuid);
		if (FAILED(hr)) return hr;
	
		hr = StringFromGUID2 (*pGuid, coleBuffer, GUID_CCH);
		if (FAILED(hr)) return hr;

	// '{' und '}' entfernen, damit es genau 36 Zeichen werden (kein FolgeSatz in der DB)
		strcpy (cbBuffer, OLE2A(coleBuffer+1));
		cbBuffer[36] = '\0';

		if (!WriteTextMerkmal (TT_Objekt, lONr, lMCode, cbBuffer))
			return E_FAIL;
	}
	return hr;
}

HRESULT GeoDB::SetObjectGUID (LONG lONr, const _GUID &rGuid)
{
	TX_ASSERT(VERSION0500000E <= GetDBVersion());

LONG lTarget = 0L;
HRESULT hr = FindObjectFromGUID (rGuid, &lTarget);

	if (SUCCEEDED(hr)) 
		return (lTarget == lONr) ? S_OK : HRESULT_FROM_ERRCODE(S_DUPLICATE);

struct obl OBLSatz;
DB_ADDR_OBL dbaOBL(DBDesc());
ErrCode RC = EC_OKAY;

//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = lONr;
	__ReadHR (dbaOBL, OBLSatz);
	
ErrInstall Duplicate (WC_DUPLICATE);		// GUID muß unique sein

	OBLSatz.guid = rGuid;
	__WriteHR(dbaOBL, OBLSatz);
	
	return S_OK;
}

HRESULT GeoDB::SetObjectGUIDFeature (LONG lONr, const _GUID &rGuid, LONG lMCode)
{
	TX_ASSERT(VERSION0500000E > GetDBVersion());

// erstmal feststellen, on dieser Guid noch nicht vertreten ist
LONG lTarget = 0L;
HRESULT hr = FindObjectFromGUIDFeature (rGuid, lMCode, &lTarget);

	if (SUCCEEDED(hr)) 
		return (lTarget == lONr) ? S_OK : HRESULT_FROM_ERRCODE(WC_DUPLICATE);

// jetzt wirklich schreiben
OLECHAR coleBuffer[GUID_CCH];

	hr = StringFromGUID2 (rGuid, coleBuffer, GUID_CCH);
	if (FAILED(hr)) return hr;

// '{' und '}' entfernen, damit es genau 36 Zeichen werden (kein FolgeSatz in der DB)
	USES_CONVERSION;

char cbBuffer[GUID_CCH];

	strcpy (cbBuffer, OLE2A(coleBuffer+1));
	cbBuffer[36] = '\0';

	if (!WriteTextMerkmal (TT_Objekt, lONr, lMCode, cbBuffer))
		return E_FAIL;

	return S_OK;
}

HRESULT GeoDB::FindObjectFromGUID (const _GUID &rGuid, LONG *plONr)
{
	TX_ASSERT(VERSION0500000E <= GetDBVersion());
	TX_ASSERT(NULL != plONr);

//struct obl OBLSatz;
DB_ADDR_OBL dbaOBL(DBDesc());
ErrCode RC = EC_OKAY;

//	dbaOBL.file_no = OBL;

ErrInstall EI (WC_NOTFOUND);

	DBASSERTHR(z_keyfind (&dbaOBL, GUIDKEY, (LPVOID)&rGuid));

	*plONr = dbaOBL.rec_no;
	return S_OK;
}

extern "C"
BOOL CALLBACK FindObjFromGuid (LONG lONr, BOOL, void *pData)
{
	*(LONG *)pData = lONr;		// der erste gilt (muß unique sein)
	return FALSE;
}

HRESULT GeoDB::FindObjectFromGUIDFeature (const _GUID &rGuid, LONG lMCode, LONG *plONr)
{
	TX_ASSERT(VERSION0500000E > GetDBVersion());
	TX_ASSERT(0L != lMCode);

OLECHAR coleBuffer[GUID_CCH];
HRESULT hr = StringFromGUID2 (rGuid, coleBuffer, GUID_CCH);

	if (FAILED(hr)) return hr;

// '{' und '}' entfernen, damit es genau 36 Zeichen werden (kein FolgeSatz in der DB)
	USES_CONVERSION;

char cbBuffer[GUID_CCH];

	strcpy (cbBuffer, OLE2A(coleBuffer+1));
	cbBuffer[36] = '\0';

ENUMRECHTEXTMERKMAL ERM;

	INITSTRUCT(ERM, ENUMRECHTEXTMERKMAL);
	ERM.lMCode = lMCode;
	ERM.pMWert = cbBuffer;
	ERM.iMode = SMExactMatch;
	ERM.eFcn = (RECHTEXTMERKMALCALLBACK)FindObjFromGuid;
	ERM.pData = plONr;

	*plONr = 0L;	
	DEX_EnumRechTextMerkmal(ERM);
	if (0 == *plONr)
		return E_FAIL;
	return S_OK;
}

