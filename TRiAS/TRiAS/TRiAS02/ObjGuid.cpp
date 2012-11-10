// Verwaltung von ObjektGUID's
// File: OBJGUID.CPP

#include "trias02p.hxx"

#include <Com/PropertyHelper.h>
#include <Com/SafeArray.h>
#include <Atl/Ciid.h>

#include <dbmsg.hmc>

#include "Strings.h"
#include "MapCaches.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif // _DEBUG

#define GUID_CCH	39	// Characters in string form of guid, including '\0'

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASDatabase);		// WTRiASDatabase
DefineSmartInterface(TRiASObjectHandleMap);	// WTRiASObjectHandleMap
DefineSmartInterface(TRiASObject);			// WTRiASObject
DefineSmartInterface(TRiASObjects);			// WTRiASObjects
DefineSmartInterface(TRiASFeature);			// WTRiASFeature
DefineSmartInterface(TRiASObjectsOperations);	// WTRiASObjectsOperations
DefineSmartInterface(EnumVARIANT);			// WEnumVARIANT

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

bool WriteTextMerkmal (short iTTyp, long lTarget, long lMCode, const char *pText, short iFlags = 0)
{
TARGETMERKMALEX gm;

	INITSTRUCT(gm, TARGETMERKMALEX);
	gm.lTarget = (LPARAM)lTarget;
	gm.lMCode = lMCode;
	gm.imaxLen = pText != NULL ? strlen (pText) : 0;
	gm.pMText = const_cast<char *>(pText);
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
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
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
	} else
#endif // _FORCE_LEGACY_CODE
	{
	HRESULT hr = HRESULT_FROM_ERRCODE(WC_NOTFOUND);

		TX_ASSERT(IsTRiASDBBased());
		COM_TRY {
		WTRiASObjectHandleMap ObjMap; // (CLSID_TRiASObjectsHandleMap);
		WTRiASObject Obj;

			THROW_FAILED_HRESULT(GetObjectMap(ObjMap.ppi()));

		HOBJECTS hObjs = NULL;		// zugehörige Objektklasse
			
		// wiederauffinden des Objects-Objektes
			TX_ASSERT(ObjMap.IsValid());
			THROW_FAILED_HRESULT(ObjMap -> GetObject(lONr, Obj.ppu()));
			THROW_FAILED_HRESULT(Obj -> get_ObjectsHandle ((INT_PTR *)&hObjs));

		WTRiASObjectHandleMap ObjsMap; // (CLSID_TRiASObjectsHandleMap);
		WTRiASObjects Objs;

			THROW_FAILED_HRESULT(GetObjectsMap(ObjsMap.ppi()));

		WTRiASFeature Feat;

			TX_ASSERT(ObjsMap.IsValid());
			THROW_FAILED_HRESULT(ObjsMap -> GetObject((INT_PTR)hObjs, Objs.ppu()));
			if (SUCCEEDED(hr = Objs -> get_Feature (CComVariant(g_cbPrimaryKey), VARIANT_FALSE, CComBSTR(g_cbNil), Feat.ppi()))) {
			CComVariant vVal;

				THROW_FAILED_HRESULT(Feat -> Eval (Obj, &vVal));
				THROW_FAILED_HRESULT(vVal.ChangeType (VT_BSTR));

			CIID Guid (V_BSTR(&vVal));

				*pGuid = Guid;
				hr = !Guid ? E_FAIL : S_OK;		// no Guid, no fun
			}

		} COM_CATCH;
		return hr;
	}
}

#if defined(_FORCE_LEGACY_CODE)
HRESULT GeoDB::GetObjectGUIDFeature (LONG lONr, LONG lMCode, struct _GUID *pGuid)
{
	TX_ASSERT(IsTRiASDBBased() || VERSION0500000E > GetDBVersion());
	TX_ASSERT(0L != lMCode);
	TX_ASSERT(NULL != pGuid);

	USES_CONVERSION;

HRESULT hr = S_FALSE;
char cbBuffer[GUID_CCH];

	if (ReadTextMerkmal (TT_Objekt, lONr, lMCode, cbBuffer+1, sizeof(cbBuffer))) {

		cbBuffer[0] = '{';
		cbBuffer[37] = '}';
		cbBuffer[38] = '\0';
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
#endif // _FORCE_LEGACY_CODE

HRESULT GeoDB::SetObjectGUID (LONG lONr, const _GUID &rGuid)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
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
	} else
#endif // _FORCE_LEGACY_CODE
	{
	HRESULT hr = HRESULT_FROM_ERRCODE(WC_NOTFOUND);

		TX_ASSERT(IsTRiASDBBased());
		COM_TRY {
		WTRiASObjectHandleMap ObjMap; // (CLSID_TRiASObjectsHandleMap);
		WTRiASObject Obj;

			THROW_FAILED_HRESULT(GetObjectMap(ObjMap.ppi()));

		HOBJECTS hObjs = NULL;		// zugehörige Objektklasse
			
		// wiederauffinden des Objects-Objektes
			TX_ASSERT(ObjMap.IsValid());
			THROW_FAILED_HRESULT(ObjMap -> GetObject(lONr, Obj.ppu()));
			THROW_FAILED_HRESULT(Obj -> get_ObjectsHandle ((INT_PTR *)&hObjs));

		WTRiASObjectHandleMap ObjsMap; // (CLSID_TRiASObjectsHandleMap);
		WTRiASObjects Objs;

			THROW_FAILED_HRESULT(GetObjectsMap(ObjsMap.ppi()));

		WTRiASFeature Feat;

			TX_ASSERT(ObjsMap.IsValid());
			THROW_FAILED_HRESULT(ObjsMap -> GetObject((INT_PTR)hObjs, Objs.ppu()));
			if (SUCCEEDED(hr = Objs -> get_Feature (CComVariant(g_cbPrimaryKey), VARIANT_FALSE, CComBSTR(g_cbNil), Feat.ppi()))) {
			CIID Guid (rGuid);
			CComVariant vGuid (os_string(Guid).c_str());

				THROW_FAILED_HRESULT(Feat -> Update (Obj, vGuid));
			}

		} COM_CATCH;
		return hr;
	}
}

#if defined(_FORCE_LEGACY_CODE)
HRESULT GeoDB::SetObjectGUIDFeature (LONG lONr, const _GUID &rGuid, LONG lMCode)
{
	TX_ASSERT(IsTRiASDBBased() || VERSION0500000E > GetDBVersion());

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
#endif // _FORCE_LEGACY_CODE

// Erzeugen und initialisieren eines neuen TRiASObjects- Objektes
namespace {
	HRESULT MakeNewObjects (
		IDispatch *pIParent, BSTR bstrName, REFCLSID rClsId, 
		OBJECTSCOLLECTIONTYPE rgType, ITRiASObjects **ppIObjs) throw(_com_error)
	{
	WTRiASObjectsOperations ObjOper (CLSID_TRiASObjectsOperations);		// throws hr

		return ObjOper -> MakeNewObjects(pIParent, bstrName, CComBSTR(CIID(rClsId).ProgID().c_str()), rgType, ppIObjs);
	}

	HRESULT GetResultHandle (ITRiASObjects *pIObjs, INT_PTR *plONr)
	{
		COM_TRY {
		WEnumVARIANT Enum;
		CComVariant v;

			THROW_FAILED_HRESULT(pIObjs -> _NewEnum (Enum.ppu()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
				TX_ASSERT(SUCCEEDED(v.ChangeType (VT_DISPATCH)));

			WTRiASObject Obj (V_DISPATCH(&v));
			INT_PTR hObj = NULL;

				THROW_FAILED_HRESULT(Obj -> get_Handle (&hObj));
				*plONr = hObj;
				return S_OK;
			}

		} COM_CATCH;
		return TRIASDB_I_NO_OBJECTS_FOUND;
	}

} // namespace

HRESULT GeoDB::FindObjectFromGUID (const _GUID &rGuid, LONG *plONr)
{
HRESULT hr = TRIASDB_I_NO_OBJECTS_FOUND;

	TX_ASSERT(IsTRiASDBBased());
	COM_TRY {
	// Rechercheparameter zusammenbauen
	CSafeArray sa (VT_VARIANT, 2);

		{
		CSafeArrayLock<VARIANT> lock (sa);
		CIID Guid (rGuid);
		CComVariant v(os_string(Guid).c_str());
		CComVariant vName (g_cbPrimaryKey);

			v.Detach(&lock[0]);		// Suchtext
			vName.Detach(&lock[1]);	// Name des Attributes
		}

	// jetzt kommt eigentliche Recherche
	WTRiASObjects Objs;		// Resultatmenge

		THROW_FAILED_HRESULT(MakeNewObjects (m_Conn, CComBSTR("Test"), CLSID_TRiASObjects, OBJECTSCOLLECTIONTYPE_Temporary, Objs.ppi()));
		hr = SearchObjects (CComBSTR(SEARCHCOMMAND_MatchComplete), Objs, sa);

	// es darf genau ein Objekt gefunden worden sein
		if (S_OK == hr)
			hr = GetResultHandle (Objs, plONr);

	} COM_CATCH;
	return (S_OK == hr) ? S_OK : E_FAIL;
}

#if defined(_FORCE_LEGACY_CODE)
extern "C"
BOOL CALLBACK FindObjFromGuid (LONG lONr, BOOL, void *pData)
{
	*(LONG *)pData = lONr;		// der erste gilt (muß unique sein)
	return FALSE;
}

HRESULT GeoDB::FindObjectFromGUIDFeature (const _GUID &rGuid, LONG lMCode, LONG *plONr)
{
	TX_ASSERT(IsTRiASDBBased() || VERSION0500000E > GetDBVersion());
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
#endif // _FORCE_LEGACY_CODE

