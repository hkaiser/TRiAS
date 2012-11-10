///////////////////////////////////////////////////////////////////////////////
// @doc 
// @module NativeIdent.cpp | Declaration of <CNativeIdent> class

#include "trias01p.hxx"
#include "Pragmas.h"

#include <ospace/std/set>
#include <ospace/com/iterenum.h>

#include <Atl/Ciid.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#include "resource.h"

#include <ActDB.h>
#include <switchkc.h>
#include <ErrInst.hxx>
#include <NativeIdent.h>
#include <NativeMerkmal.h>
#include <NativeObject.h>
#include <NativePbd.h>
#include <OKSHeader.h>
#include <ObjGuidHeader.h>
#include <UniqueHeader.h>

#include <Com/ComBool.h>

#import "tlb/TRiASMDS.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids 

#include "syncdb.hxx"
#include "strings.h"
#include "ConnectFilterWrappers.h"

extern "C" HINSTANCE g_hInstance;

/////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(TRiASMDSMap);
DefineSmartInterface(TRiASMDSStringColl);
DefineSmartInterface(EnumVARIANT);

/////////////////////////////////////////////////////////////////////////////
// globale Funktionen
BOOL IDLRecHasObjects (HPROJECT hPr, struct idl *pIdl);
BOOL IDLRecIsEmpty (HPROJECT hPr, struct idl *pIdl);

/////////////////////////////////////////////////////////////////////////////
// Wrapperfunktionen für den Umgang mit den globalen Maps
namespace trias_nativeident_map {

	HRESULT InsertEntry (ITRiASMDSMap *pIMap, LONG lIdent, BSTR bstrName, 
		BSTR bstrShort, BSTR bstrLong, DWORD dwTypes, bool fNocase)
	{
		_ASSERTE(NULL != pIMap);

	wchar_t cbBuffer[100];
	CComBSTR bstrId (_ltow (lIdent, cbBuffer, 10));
	bool fModified = false;

		if (NULL != bstrShort && ::SysStringLen (bstrShort) > 0) {
		WTRiASMDSStringColl Coll;
		CComBSTR bstr (bstrShort);
		int iCnt = 1;
		long lSearchMode = mdsSM_Compare|mdsSM_SrchShort;

			if (fNocase)
				lSearchMode |= mdsSM_NoCase;	// ggf. ohne Unterscheidung

			while (S_OK == pIMap -> Search (bstr, lSearchMode, Coll.ppi())) {
			wchar_t cbCnt[32];

				bstr = bstrShort;
				bstr += L" (";
				bstr += _ltow (iCnt++, cbCnt, 10);
				bstr += L")";

				fModified = true;
			} 
			if (fModified)
				bstrShort = bstr;
		}

	// auf doppelte OKS testen und ggf. behandeln
	CComBSTR bstrBuff (bstrShort);

		if (NULL != bstrName && ::SysStringLen(bstrName) > 0) {
		WTRiASMDSStringColl Coll;
		CComBSTR bstr (bstrName);

			if (S_OK == pIMap -> Search (bstr, mdsSM_Compare|mdsSM_SrchName, Coll.ppi())) {
				bstrBuff.LoadString (IDS_DUPLICATEOKS);
				bstrBuff += g_cbLeftBracket;
				bstrBuff += bstrName;
				bstrBuff += g_cbRightBracket;
				bstrName = NULL;
			}
		} 
		RETURN_FAILED_HRESULT(pIMap -> SetAt (bstrId, bstrName, bstrBuff, bstrLong, CComVariant(dwTypes, VT_I4)));
		return S_OK;
	}

	inline 
	HRESULT RetrieveEntry (ITRiASMDSMap *pIMap, LONG lIdent, 
		BSTR *pbstrName = NULL, BSTR *pbstrShort = NULL, BSTR *pbstrLong = NULL, DWORD *pdwTypes = NULL)
	{
		_ASSERTE(NULL != pIMap);
		_ASSERTE(NULL != pbstrName || NULL != pbstrShort || NULL != pbstrLong || NULL != pdwTypes);	// sonst ist's sinnlos

	wchar_t cbBuffer[64];
	CComBSTR bstrId (_ltow (lIdent, cbBuffer, 10));
	CComVariant v;
	HRESULT hr = E_FAIL;
	CComBSTR bstrName, bstrShort, bstrLong;

		if (SUCCEEDED(hr = pIMap -> GetAt (bstrId, pbstrName ? pbstrName : &bstrName, pbstrShort ? pbstrShort : &bstrShort, pbstrLong ? pbstrLong : &bstrLong, &v))) {
			if (NULL != pdwTypes && SUCCEEDED(v.ChangeType (VT_I4)))
				*pdwTypes = V_I4(&v);
			return S_OK;
		}
		return hr;
	}

	inline
	HRESULT RemoveEntry (ITRiASMDSMap *pIMap, LONG lIdent)
	{
		_ASSERTE(NULL != pIMap);

	wchar_t cbBuffer[64];
	CComBSTR bstrId (_ltow (lIdent, cbBuffer, 10));

		return pIMap -> RemoveAt (bstrId);
	}

	inline
	HRESULT ReplaceOKS (ITRiASMDSMap *pIMap, LONG lIdent, BSTR bstrName, trias_nativeident::CNativeIdent *pIdent)
	{
		_ASSERTE(NULL != pIMap);

	wchar_t wcbBuffer[64];
	CComBSTR bstrId (_ltow (lIdent, wcbBuffer, 10));
	CComBSTR bstrNameOld, bstrShort, bstrLong;
	CComVariant v;

		if (SUCCEEDED(pIMap -> GetAt (bstrId, &bstrNameOld, &bstrShort, &bstrLong, &v)))
			pIMap -> RemoveAt (bstrId);

		return pIMap -> SetAt (bstrId, bstrName, bstrShort, bstrLong, v);
	}

	inline
	HRESULT ReplaceShort (ITRiASMDSMap *pIMap, LONG lIdent, BSTR bstrShort)
	{
		_ASSERTE(NULL != pIMap);

	wchar_t cbBuffer[64];
	CComBSTR bstrId (_ltow (lIdent, cbBuffer, 10));
	CComBSTR bstrName, bstrShortOld, bstrLong;
	CComVariant v;

		if (SUCCEEDED(pIMap -> GetAt (bstrId, &bstrName, &bstrShortOld, &bstrLong, &v)))
			pIMap -> RemoveAt (bstrId);
		return pIMap -> SetAt (bstrId, bstrName, bstrShort, bstrLong, v);
	}

	inline
	HRESULT ReplaceLong (ITRiASMDSMap *pIMap, LONG lIdent, BSTR bstrLong)
	{
		_ASSERTE(NULL != pIMap);

	wchar_t cbBuffer[64];
	CComBSTR bstrId (_ltow (lIdent, cbBuffer, 10));
	CComBSTR bstrName, bstrShort, bstrLongOld;
	CComVariant v;

		if (SUCCEEDED(pIMap -> GetAt (bstrId, &bstrName, &bstrShort, &bstrLongOld, &v)))
			pIMap -> RemoveAt (bstrId);
		return pIMap -> SetAt (bstrId, bstrName, bstrShort, bstrLong, v);
	}

	inline
	HRESULT ReplaceTypes (ITRiASMDSMap *pIMap, LONG lIdent, DWORD dwTypes)
	{
		_ASSERTE(NULL != pIMap);

	wchar_t cbBuffer[64];
	CComBSTR bstrId (_ltow (lIdent, cbBuffer, 10));
	CComBSTR bstrName, bstrShort, bstrLong;
	CComVariant v (dwTypes, VT_I4);
	CComVariant vTypesOld;

		if (SUCCEEDED(pIMap -> GetAt (bstrId, &bstrName, &bstrShort, &bstrLong, &vTypesOld)))
			pIMap -> RemoveAt (bstrId);
		return pIMap -> SetAt (bstrId, bstrName, bstrShort, bstrLong, v);
	}

	inline
	HRESULT FindFromName (ITRiASMDSMap *pIMap, BSTR bstrName, bool fCaseSensitive = true, INT_PTR *plIdent = NULL)
	{
	// Kurztext wiederfinden
		if (NULL == bstrName || 0 == ::SysStringLen(bstrName)) 
			return E_UNEXPECTED;

	WTRiASMDSStringColl Coll;
	long lSearchMode = mdsSM_Compare|mdsSM_SrchShort;

		if (!fCaseSensitive)
			lSearchMode |= mdsSM_NoCase;	// Groß-/Kleinschreibung ignorieren

		if (S_OK == pIMap -> Search (bstrName, lSearchMode, Coll.ppi())) {
		WUnknown UnkEnum;
		CComVariant v[2];
		ULONG ulCnt = 0;

			RETURN_FAILED_HRESULT(Coll -> _NewEnum(UnkEnum.ppi()));

		WEnumVARIANT Enum (UnkEnum);

			RETURN_FAILED_HRESULT(Enum -> Reset());
			if (FAILED(Enum -> Next(2, v, &ulCnt)) || 0 == ulCnt)
				return HRESULT_FROM_ERRCODE(WC_NOTFOUND);

			_ASSERTE(ulCnt == 1);		// genau einer muß existieren (nicht mehr)
			_ASSERTE(VT_BSTR == V_VT(&v[0]));
			if (NULL != plIdent)
				*plIdent = _wtol(V_BSTR(&v[0]));
			return S_OK;
		}
		return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
	}
}

namespace trias_nativeident {

using namespace trias_nativepbd;
using namespace trias_nativeheader;
using namespace trias_nativemerkmal;
 
///////////////////////////////////////////////////////////////////////////////
// Konstruktor
CNativeIdent::CNativeIdent (HPROJECT hPr, LONG lIdent, DWORD dwTypes, BOOL fCreate)
	: m_hPr(hPr), m_lRecNo(0L), m_lIdent(lIdent), m_dwTypes(dwTypes)
{
// Feststellen, ob Ident bereits existiert
	m_fReportPbdErrors = true;		// default: alle Fehler melden

	if (0 == m_lIdent && fCreate)	// ggf. neuen Ident geben lassen
		m_lIdent = CUniqueHeader(m_hPr).GetNextUniqueCode(CUniqueHeader::UNIQUETYPE_ICODE);
	
	if (0 != m_lIdent) {
		_ASSERTE(NULL != m_hPr);
		SYNC_DBACCESS (g_pDbMutex, m_hPr);

	CActDB ActDB(m_hPr);
	DB_ADDR_IDL dbaIDL (m_hPr);			// gesuchte DatenBankadresse

//		dbaIDL.file_no = IDL;

	ErrInstall EI (WC_NOTFOUND);
	ErrCode RC = (ErrCode)z_keyfind (&dbaIDL, IDN_OLD, (LPVOID)&m_lIdent);

		if (EC_OKAY == RC)
			m_lRecNo = dbaIDL.rec_no;			// gesuchter Satz
		else if (WC_NOTFOUND == RC && fCreate) {
		// neuen IDL-Satz anlegen
		struct idl IDLSatz;

			IDLSatz.idn = m_lIdent;
			if (EC_OKAY == IDLSatz.FillNewRecord(&dbaIDL))
				m_lRecNo = dbaIDL.rec_no;		// neuer Satz
		} 
	}
}

///////////////////////////////////////////////////////////////////////////////
// Liefert alle Identifikatoren dieser Datenbank
/*static*/
HRESULT CNativeIdent::EnumIdents (HPROJECT hPr, 
	HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData)
{
	_ASSERTE(NULL != hPr);
//	SYNC_DBACCESS (g_pDbMutex, hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (hPr, &hPrPbd))			// keine Pbd zugeordnet
		return E_UNEXPECTED;

WTRiASMDSMap Map;
CComBSTR bstr;

	USES_CONVERSION;
	RETURN_FAILED_HRESULT(GetIdentMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));

WUnknown UnkEnum;
CComVariant v;
bool iRC = true;

	RETURN_FAILED_HRESULT(Map -> _NewEnum (UnkEnum.ppi()));

WEnumVARIANT Enum(UnkEnum);

	for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
	CComVariant vTypes;
	DWORD dwTypes = 0;
	CComBSTR bstrName, bstrShort, bstrLong;

		vTypes.vt = VT_I4;
		if (FAILED(v.ChangeType (VT_BSTR)) || FAILED(Map -> GetAt (V_BSTR(&v), &bstrName, &bstrShort, &bstrLong, &vTypes)))
		{
			_ASSERTE(FALSE);
			continue;
		}
		if (SUCCEEDED(vTypes.ChangeType (VT_I4)))
			dwTypes = V_I4(&vTypes) & ~CNativePbdIdent::PBDIDENTTYPE_Mask;		// zusätzliche Flags ausblenden

	// Callback aufrufen
		_ASSERTE(0 != _wtol (V_BSTR(&v)));
		iRC = SUCCEEDED(pFcn (_wtol (V_BSTR(&v)), dwTypes, dwData)) ? true : false;
		if (!iRC) break;
	}
	return iRC ? S_OK : S_FALSE;
}

/*static*/
HRESULT CNativeIdent::EnumIdentsDB (HPROJECT hPr, 
	HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData)
{
	_ASSERTE(NULL != hPr);
	SYNC_DBACCESS (g_pDbMutex, hPr);

CActDB ActDB(hPr);
DB_ADDR_IDL dbaIDL (hPr);
ErrInstall EI (WC_NOTFOUND);	// Fehler WC_NOTFOUND ignorieren

// ersten ID suchen
HRESULT hr = S_OK;
ErrCode RC = (ErrCode)z_keyfirst (&dbaIDL, IDN_OLD);

	if (RC != EC_OKAY) {
	// Fehler aufgetreten
		if (RC == WC_NOTFOUND) 
			return S_FALSE;					// nichts gefunden: OK
		return HRESULT_FROM_ERRCODE(RC);	// sonstiger Fehler
	}

// für alle weiteren ID's
bool iNext = true;
bool iRC = true;

	while (iNext && iRC) {
	long lIdent = 0;
	DWORD dwTypes = 0;

	// ID aus Schlüsseldatei lesen
		RC = (ErrCode)z_keyread (hPr, &lIdent);
		if (RC != EC_OKAY) break;

	// nächsten Schlüssel suchen
		RC = (ErrCode)z_keynext (&dbaIDL, IDN_OLD);
		if (RC != EC_OKAY)
			iNext = false;

		{
		CKeyContext keyCtx;

		// ObjektTypen dieses Idents feststellen
		CNativeIdent HelperIdent (hPr, lIdent, OTPunkt|OTLinie|OTFlaeche|OTText);

			hr = HelperIdent.GetObjectTypesAndCounts (LOOKUPSPEED_INFINITE, dwTypes, NULL);
			if (FAILED(hr)) return hr;

		// Callback aufrufen
			{
				UNLOCK_DBACCESS(&__Sync, hPr);		// __Sync is defined by SYNC_DBACCESS()
				iRC = SUCCEEDED(pFcn (lIdent, dwTypes, dwData)) ? true : false;
				ActDB.ReActivate();
			}
		}
	}
	if (RC == WC_NOTFOUND) 
		RC = EC_OKAY;           // nichts mehr gefunden: OK

	return (EC_OKAY == RC) ? (iRC ? S_OK : S_FALSE) : HRESULT_FROM_ERRCODE(RC);
}

///////////////////////////////////////////////////////////////////////////////
// Liefert alle Merkmale, die an Objekten dieses Identifikators hängen können
/*static*/
HRESULT CNativeIdent::StorePBDMCodes (INT_PTR lMCode, UINT_PTR dwData)
{
	reinterpret_cast<set<LONG> *>(dwData) -> insert (lMCode);
	return S_OK;
}

/*static*/
HRESULT CNativeIdent::EnumRelatedMCodes (
	HPROJECT hPr, HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData)
{
	_ASSERTE(NULL != hPr);
	SYNC_DBACCESS (g_pDbMutex, hPr);

// zuerst PBD enumerieren, um alle dort definierten MCodes zu haben
HPROJECT hPrPbd = NULL;
set<LONG> mapMCodes;

	if (!GetRelatedProject (hPr, &hPrPbd)) 
		return E_UNEXPECTED;
	RETURN_FAILED_HRESULT(CNativePbdMerkmal::EnumPBDData (hPrPbd, StorePBDMCodes, reinterpret_cast<UINT_PTR>(&mapMCodes)));

// zur Zeit haben alle Idents den gleichen MerkmalsSatz
CActDB ActDB(hPr);
DB_ADDR dba(hPr);

// Fehler WC_NOTFOUND ignorieren
ErrInstall EI (WC_NOTFOUND);
ErrCode EC = (ErrCode)z_keyfirst (&dba, MK);	// ersten MerkmalsCode suchen

	if (EC_OKAY != EC) {
	// Fehler aufgetreten
		if (WC_NOTFOUND == EC) 
			return S_OK;					// nichts gefunden: OK
		return HRESULT_FROM_ERRCODE(EC);	// sonstiger Fehler
	}

// für alle weiteren Merkmale
bool iRC = false;

// hier alle Merkmale enumerieren, die wirklich in der GeoDB vertreten sind
	do {
	long lMCode = 0L;

	// MerkmalsCode aus Schlüsseldatei lesen
		EC = (ErrCode)z_keyread (hPr, &lMCode);
		if (EC_OKAY != EC) break;

	// Callback aufrufen
		{
		CKeyContext keyCtx;
		CNativeMerkmal Merkmal(hPr, lMCode); 
		DWORD dwType = Merkmal.GetFullType();

			mapMCodes.erase(lMCode);		// dieser wird nicht mehr gebraucht
			iRC = SUCCEEDED(pFcn (lMCode, dwType, dwData)) ? true : false;
			ActDB.ReActivate();
		}

		if (!iRC) break;

	// nächsten Schlüssel suchen
		EC = (ErrCode)z_keynext (&dba, MK);

	} while (EC_OKAY == EC);
	
	if (WC_NOTFOUND != EC && EC_OKAY != EC)
		return HRESULT_FROM_ERRCODE(EC);	// Fehler
	if (!iRC) return S_FALSE;				// abgebrochen

// und jetzt noch alle restlichen PbdEinträge nachreichen
	for (set<LONG>::iterator it = mapMCodes.begin(); it != mapMCodes.end(); ++it) {
	CNativeMerkmal Merkmal(hPr, *it); 
	DWORD dwType = Merkmal.GetFullType() | CNativePbdMerkmal::PBDFEATURETYPE_PbdOnly;

		iRC = SUCCEEDED(pFcn (*it, dwType, dwData)) ? true : false;
		if (!iRC) break;
	}

	if (WC_NOTFOUND == EC || EC_OKAY == EC) 
		return iRC ? S_OK : S_FALSE;			// nichts mehr gefunden oder OK

	return HRESULT_FROM_ERRCODE(EC);
}

///////////////////////////////////////////////////////////////////////////////
// liefert alle Objektnummern der Objekte der vorgegebenen Typen

/*static*/
HRESULT CALLBACK CNativeIdent::StoreObjectsSet (INT_PTR lObject, DWORD dwType, UINT_PTR dwData)
{
CStoreObjectsCallBackSet *pData = reinterpret_cast<CStoreObjectsCallBackSet *>(dwData);

	if (!(pData -> m_dwTypes & dwType))
		return S_OK;	// wird nicht gebraucht, da anderer Datentyp

	if (NULL != pData -> m_pIExpr) {
	CComVariant vValue;

		if (FAILED(pData -> m_pIExpr -> Calculate(reinterpret_cast<INT_PTR>(pData -> m_hPr), lObject, &vValue)) ||
			FAILED(vValue.ChangeType(VT_BOOL)) ||
			V_BOOL(&vValue) != VARIANT_TRUE)
		{
			return S_OK;		// dieses Objekt nicht mitnehmen
		}
	}

	try {
		pData->m_pObjs->insert(lObject);

	} catch (_com_error &e) {
		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	} catch (...) {
		ASSERT(SUCCEEDED(E_OUTOFMEMORY));
		return E_OUTOFMEMORY;
	}

	if (NULL != pData -> m_plCnts) {
		switch (dwType) {
		case OTPunkt:	(pData -> m_plCnts)[0]++; break;
		case OTLinie:	(pData -> m_plCnts)[1]++; break;
		case OTFlaeche:	(pData -> m_plCnts)[2]++; break;
		case OTText:	(pData -> m_plCnts)[3]++; break;
		default:
			break;
		}
	}
	return S_OK;
}

/*static*/
HRESULT CALLBACK CNativeIdent::StoreObjectsSetDesc (INT_PTR lObject, DWORD dwType, UINT_PTR dwData)
{
CStoreObjectsCallBackSetDesc *pData = reinterpret_cast<CStoreObjectsCallBackSetDesc *>(dwData);

	if (!(pData -> m_dwTypes & dwType))
		return S_OK;	// wird nicht gebraucht, da anderer Datentyp

	if (NULL != pData -> m_pIExpr) {
	CComVariant vValue;

		if (FAILED(pData -> m_pIExpr -> Calculate(reinterpret_cast<INT_PTR>(pData -> m_hPr), lObject, &vValue)) ||
			FAILED(vValue.ChangeType(VT_BOOL)) ||
			V_BOOL(&vValue) != VARIANT_TRUE)
		{
			return S_OK;		// dieses Objekt nicht mitnehmen
		}
	}

	try {
		pData->m_pObjs->insert(lObject);

	} catch (_com_error &e) {
		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	} catch (...) {
		ASSERT(SUCCEEDED(E_OUTOFMEMORY));
		return E_OUTOFMEMORY;
	}

	if (NULL != pData -> m_plCnts) {
		switch (dwType) {
		case OTPunkt:	(pData -> m_plCnts)[0]++; break;
		case OTLinie:	(pData -> m_plCnts)[1]++; break;
		case OTFlaeche:	(pData -> m_plCnts)[2]++; break;
		case OTText:	(pData -> m_plCnts)[3]++; break;
		default:
			break;
		}
	}
	return S_OK;
}

/*static*/
HRESULT CALLBACK CNativeIdent::StoreObjectsVector (INT_PTR lObject, DWORD dwType, UINT_PTR dwData)
{
CStoreObjectsCallBackVector *pData = reinterpret_cast<CStoreObjectsCallBackVector *>(dwData);

	if (!(pData -> m_dwTypes & dwType))
		return S_OK;	// wird nicht gebraucht, da anderer Datentyp

	if (NULL != pData -> m_pIExpr) {
	CComVariant vValue;

		if (FAILED(pData -> m_pIExpr -> Calculate(reinterpret_cast<INT_PTR>(pData -> m_hPr), lObject, &vValue)) ||
			FAILED(vValue.ChangeType(VT_BOOL)) ||
			V_BOOL(&vValue) != VARIANT_TRUE)
		{
			return S_OK;		// dieses Objekt nicht mitnehmen
		}
	}

	try {
		pData->m_pObjs->push_back(lObject);

	} catch (_com_error &e) {
		ASSERT(SUCCEEDED(_COM_ERROR(e)));
		return _COM_ERROR(e);
	} catch (...) {
		ASSERT(SUCCEEDED(E_OUTOFMEMORY));
		return E_OUTOFMEMORY;
	}

	if (NULL != pData -> m_plCnts) {
		switch (dwType) {
		case OTPunkt:	(pData -> m_plCnts)[0]++; break;
		case OTLinie:	(pData -> m_plCnts)[1]++; break;
		case OTFlaeche:	(pData -> m_plCnts)[2]++; break;
		case OTText:	(pData -> m_plCnts)[3]++; break;
		default:
			break;
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert alle Objekte einer Objektklasse
HRESULT CNativeIdent::GetObjects (
	DWORD dwTypes, vector<INT_PTR> &rObjs, long *plObjCnts, ITRiASExpression *pIExpr)
{
	_ASSERTE(NULL != m_hPr);
	_ASSERTE(NULL == plObjCnts || !IsBadWritePtr (plObjCnts, 4*sizeof(long)));

	SYNC_DBACCESS (g_pDbMutex, m_hPr);
	if (NULL != plObjCnts)
		memset (plObjCnts, '\0', 4*sizeof(long));		// Zähler rücksetzen

CStoreObjectsCallBackVector CallBackData;

	CallBackData.m_dwTypes = dwTypes;
	CallBackData.m_pObjs = &rObjs;
	CallBackData.m_plCnts = plObjCnts;
	CallBackData.m_hPr = m_hPr;
	CallBackData.m_pIExpr = pIExpr;

	return EnumObjects (StoreObjectsVector, (UINT_PTR)&CallBackData);
}

HRESULT CNativeIdent::GetObjects (
	DWORD dwTypes, set<INT_PTR> &rObjs, long *plObjCnts, ITRiASExpression *pIExpr)
{
	_ASSERTE(NULL != m_hPr);
	_ASSERTE(NULL == plObjCnts || !IsBadWritePtr (plObjCnts, 4*sizeof(long)));

	SYNC_DBACCESS (g_pDbMutex, m_hPr);
	if (NULL != plObjCnts)
		memset (plObjCnts, '\0', 4*sizeof(long));		// Zähler rücksetzen

CStoreObjectsCallBackSet CallBackData;

	CallBackData.m_dwTypes = dwTypes;
	CallBackData.m_pObjs = &rObjs;
	CallBackData.m_plCnts = plObjCnts;
	CallBackData.m_hPr = m_hPr;
	CallBackData.m_pIExpr = pIExpr;

	return EnumObjects (StoreObjectsSet, (UINT_PTR)&CallBackData);
}

HRESULT CNativeIdent::GetObjects (
	DWORD dwTypes, set<INT_PTR, greater<INT_PTR> > &rObjs, long *plObjCnts, ITRiASExpression *pIExpr)
{
	_ASSERTE(NULL != m_hPr);
	_ASSERTE(NULL == plObjCnts || !IsBadWritePtr (plObjCnts, 4*sizeof(long)));

	SYNC_DBACCESS (g_pDbMutex, m_hPr);
	if (NULL != plObjCnts)
		memset (plObjCnts, '\0', 4*sizeof(long));		// Zähler rücksetzen

CStoreObjectsCallBackSetDesc CallBackData;

	CallBackData.m_dwTypes = dwTypes;
	CallBackData.m_pObjs = &rObjs;
	CallBackData.m_plCnts = plObjCnts;
	CallBackData.m_hPr = m_hPr;
	CallBackData.m_pIExpr = pIExpr;

	return EnumObjects (StoreObjectsSetDesc, (UINT_PTR)&CallBackData);
}

///////////////////////////////////////////////////////////////////////////////
// Objekte in der Reihenfolge ihrer Guids liefern
HRESULT CNativeIdent::GetObjectsFromGuid (
	DWORD dwTypes, vector<INT_PTR> &rObjs, long *plObjCnts, ITRiASExpression *pIExpr)
{
	_ASSERTE(NULL != m_hPr);
	_ASSERTE(NULL == plObjCnts || !IsBadWritePtr (plObjCnts, 4*sizeof(long)));

	SYNC_DBACCESS (g_pDbMutex, m_hPr);
	if (NULL != plObjCnts)
		memset (plObjCnts, '\0', 4*sizeof(long));		// Zähler rücksetzen

CActDB ActDB (m_hPr);
CStoreObjectsCallBackVector CallBackData;

	CallBackData.m_dwTypes = dwTypes;
	CallBackData.m_pObjs = &rObjs;
	CallBackData.m_plCnts = plObjCnts;
	CallBackData.m_hPr = m_hPr;
	CallBackData.m_pIExpr = pIExpr;

	if (VERSION0500000E > LocGetDBVersion(m_hPr)) {
	// Guid ist normales Merkmal
	CObjGuidHeader GuidHdr (m_hPr);
	CNativeMerkmal Attrib (m_hPr, GuidHdr.GetObjGuidCode());

		return Attrib.EnumObjects(StoreObjectsVector, (UINT_PTR)&CallBackData, m_lIdent);
	}

// Guid ist eigener Key
	return EnumObjectsFromGuid (StoreObjectsVector, (UINT_PTR)&CallBackData);
}

///////////////////////////////////////////////////////////////////////////////
// ObjektType eines Idents bestimmen und gleichzeitig existierende Objete zählen

/*static*/
HRESULT CALLBACK CNativeIdent::CountObjects (INT_PTR lObject, DWORD dwType, UINT_PTR dwData)
{
CCountObjectsCallBack *pData = reinterpret_cast<CCountObjectsCallBack *>(dwData);

	if (NULL != pData -> m_pdwTypes)	// ObjektTyp liefern
		*(pData -> m_pdwTypes) |= dwType;

	if (NULL != pData -> m_plCnts) {
		switch (dwType) {
		case OTPunkt:	(pData -> m_plCnts)[0]++; break;
		case OTLinie:	(pData -> m_plCnts)[1]++; break;
		case OTFlaeche:	(pData -> m_plCnts)[2]++; break;
		case OTText:	(pData -> m_plCnts)[3]++; break;
		default:
			break;
		}
	}
	return S_OK;
}

HRESULT CNativeIdent::GetObjectTypesAndCounts (LOOKUPSPEED rgSpeed, DWORD &rdwTypes, long *plObjCnts)
{
	_ASSERTE(NULL != m_hPr);
	_ASSERTE(NULL == plObjCnts || !IsBadWritePtr (plObjCnts, 4*sizeof(ULONG)));

	if (NULL != plObjCnts)
		memset (plObjCnts, '\0', 4*sizeof(ULONG));		// Zähler rücksetzen

CActDB ActDB (m_hPr);

	if (VERSION0500000E <= ::LocGetDBVersion(m_hPr) && 
		(NULL == plObjCnts || FAILED(::GetConnectFilter(m_hPr, NULL))))
	{
	// neue GeoDB und (_kein_ Connectfilter gesetzt oder Objektzähler nicht gefragt)
		SYNC_DBACCESS (g_pDbMutex, m_hPr);

	// bei diesen GeoDB's steht die Anzahl mit in der Datenbank (IDLSatz)
	DB_ADDR_IDL dbaIDL (m_hPr);
	struct idl IDLSatz;
	ErrCode RC;

		if (0 == m_lIdent || 0 == m_lRecNo)
			return E_UNEXPECTED;

	// IdentSatz lesen
//		dbaIDL.file_no = IDL;
		dbaIDL.rec_no = m_lRecNo;
		__ReadHR (dbaIDL, IDLSatz);

		if (0 == IDLSatz.zvio) {
		// nur, wenn keine Objekte ohne Typ vorhanden sind, sonst geht's so doch nicht
		// Zähler kopieren
			if (0 != IDLSatz.lpvio)
				rdwTypes |= OTPunkt;
			if (0 != IDLSatz.llvio)
				rdwTypes |= OTLinie;
			if (0 != IDLSatz.lfvio)
				rdwTypes |= OTFlaeche;
			if (0 != IDLSatz.ltvio)
				rdwTypes |= OTText;

			if (NULL != plObjCnts) {
				plObjCnts[0] = IDLSatz.lpvio;
				plObjCnts[1] = IDLSatz.llvio;
				plObjCnts[2] = IDLSatz.lfvio;
				plObjCnts[3] = IDLSatz.ltvio;
			}
			return S_OK;
		}
	} 

	if (LOOKUPSPEED_IMMEDIATE == rgSpeed)
		return E_FAIL;		// geht nicht schnell genug

// bei älteren GeoDB's müssen alle Objekte durchgegangen werden
CCountObjectsCallBack CallBackData;

	CallBackData.m_pdwTypes = &rdwTypes;
	CallBackData.m_plCnts = plObjCnts;

	return EnumObjects (CountObjects, (UINT_PTR)&CallBackData);
}

///////////////////////////////////////////////////////////////////////////////
// Enumerieren aller Objekte eines Idents in der Reihenfolge ihrer Guids
HRESULT CNativeIdent::ObjectHasIdent (INT_PTR lONr)
{
trias_nativeobject::CNativeObject Obj (m_hPr, lONr);
INT_PTR lObjIdent = 0;

	if (!Obj) return E_INVALIDARG;
	RETURN_FAILED_HRESULT(Obj.GetIdent(&lObjIdent))
	return (m_lIdent == lObjIdent) ? S_OK : S_FALSE;
}

DWORD CNativeIdent::GetObjectType (INT_PTR lONr)
{
DB_ADDR_OBL dbaOBL (m_hPr, lONr);
struct obl OBLSatz;

	if (EC_OKAY != z_readrec(&dbaOBL, &OBLSatz))
		return 0;		// Error, unlknown object type

	if (OBLSatz.status & (SB_TEXTOBJ|SB_TEXTOBJIND)) 
		return OTText;
	if (OBLSatz.status & SB_SACHOBJ) 
		return OTSachObjekt;
	if (OBLSatz.rmaske & OREL) 
		return OTKO;

	if (OBLSatz.zokp) 
		return OTPunkt;
	if (OBLSatz.zovol) 
		return OTLinie;
	if (OBLSatz.zovoma) 
		return OTFlaeche;

	return 0;
}

HRESULT CNativeIdent::EnumObjectsFromGuid (
	HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData)
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (0 == m_lIdent || 0 == m_lRecNo)
		return E_FAIL;

CActDB ActDB(m_hPr);
ErrCode RC;
ErrInstall EI(WC_NOTFOUND);
DB_ADDR_OBL dbaOBL (m_hPr);

	if (EC_OKAY != (RC = (ErrCode)z_keyfirst(&dbaOBL, GUIDKEY)))
		return HRESULT_FROM_ERRCODE(RC);

	do {
		if (S_OK == ObjectHasIdent (dbaOBL.rec_no)) {
		// dieses Objekt gehört zur Ergebnismenge
		CKeyContext keyCtx;
		HRESULT hr = trias_connectfilter::EnumObjectsWrapper(m_hPr, dbaOBL.rec_no, 
			GetObjectType(dbaOBL.rec_no), pFcn, dwData);

			if (S_OK != hr) return hr;
			ActDB.ReActivate();
		}

	// nächstes Objekt suchen
		if ((RC = (ErrCode)z_keynext (&dbaOBL, GUIDKEY)) != EC_OKAY) {
			if (RC == WC_NOTFOUND) 
				return S_OK;
			return HRESULT_FROM_ERRCODE(RC);
		}

	} while (true);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Enumerieren aller Objekte eines Idents mit ObjekttypAuswahl 
HRESULT CNativeIdent::EnumObjects (
	HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData)
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (0 == m_lIdent || 0 == m_lRecNo)
		return E_FAIL;

// zugehörigen IdentSatz einlesen
CActDB ActDB(m_hPr);
ErrCode RC;
struct idl IDLSatz;
DB_ADDR_IDL dbaIDL (m_hPr);

//	dbaIDL.file_no = IDL;
	dbaIDL.rec_no = m_lRecNo;
	__ReadHR (dbaIDL, IDLSatz);

// über Verbindungsliste VIO alle Objekte holen
HRESULT hr = S_OK;

	if (VERSION0500000E <= ::LocGetDBVersion(m_hPr)) {
	// EinzelListen durchgehen
		if (m_dwTypes & OTPunkt) {
			hr = EnumObjectsIdlEx (m_hPr, m_lIdent, IDLSatz.zpvio, OTPunkt, pFcn, dwData);
			if (S_OK != hr) return hr;
		}
		if (m_dwTypes & OTLinie) {
			hr = EnumObjectsIdlEx (m_hPr, m_lIdent, IDLSatz.zlvio, OTLinie, pFcn, dwData);
			if (S_OK != hr) return hr;
		}
		if (m_dwTypes & OTFlaeche) {
			hr = EnumObjectsIdlEx (m_hPr, m_lIdent, IDLSatz.zfvio, OTFlaeche, pFcn, dwData);
			if (S_OK != hr) return hr;
		}
		if (m_dwTypes & OTText) {
			hr = EnumObjectsIdlEx (m_hPr, m_lIdent, IDLSatz.ztvio, OTText, pFcn, dwData);
			if (S_OK != hr) return hr;
		}
		if (m_dwTypes & OTKO) {
			hr = EnumObjectsIdlEx (m_hPr, m_lIdent, IDLSatz.zkvio, OTKO, pFcn, dwData);
			if (S_OK != hr) return hr;
		}

	} else {
	// Hauptliste durchgehen
		hr = EnumObjectsIdlEx (m_hPr, m_lIdent, IDLSatz.zvio, m_dwTypes, pFcn, dwData, TRUE);
		if (S_OK != hr) return hr;
	}
	return S_OK;
}

// KurzText (Bezeichner) lesen
HRESULT CNativeIdent::GetName (LPSTR pBuffer, int iLen)				// KurzText liefern
{
	_ASSERTE(NULL != pBuffer && iLen > 0);
	_ASSERTE(NULL != m_hPr);

//	SYNC_DBACCESS (g_pDbMutex, m_hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))			// keine Pbd zugeordnet
		return MakeDefaultName (pBuffer, iLen);

WTRiASMDSMap Map;
CComBSTR bstr;

	RETURN_FAILED_HRESULT(GetIdentMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));

HRESULT hr = trias_nativeident_map::RetrieveEntry (Map, m_lIdent, NULL, &bstr);

	if (SUCCEEDED(hr) && NULL != bstr.m_str && bstr.Length() > 0) {
		USES_CONVERSION;
		_ASSERTE(TIsValidAddress(pBuffer, iLen));

		strncpy (pBuffer, OLE2A(bstr), iLen-1);
		pBuffer[iLen-1] = '\0';
		return S_OK;
	}
	return MakeDefaultName (pBuffer, iLen);
}

HRESULT CNativeIdent::GetNameDB (LPSTR pBuffer, int iLen, BOOL fMakeDefault, BOOL fCorrectName)
{
	_ASSERTE(NULL != pBuffer && iLen > 0);
	_ASSERTE(NULL != m_hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))			// keine Pbd zugeordnet
		return fMakeDefault ? MakeDefaultName (pBuffer, iLen) : E_UNEXPECTED;

	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CNativePbdIdent Ident (hPrPbd, m_lIdent, NULL, GetReportPbdErrors(), fCorrectName);

	if (!Ident) 
		return fMakeDefault ? MakeDefaultName (pBuffer, iLen) : HRESULT_FROM_ERRCODE(WC_NOTFOUND);

LPCSTR pcKText = Ident.GetKurzText();

	if (NULL != pcKText && strlen(pcKText) > 0) {
		_ASSERTE(TIsValidAddress(pBuffer, iLen));
		strncpy (pBuffer, pcKText, iLen-1);
		pBuffer[iLen-1] = '\0';
		return S_OK;
	}
	return fMakeDefault ? MakeDefaultName (pBuffer, iLen) : HRESULT_FROM_ERRCODE(WC_NOTFOUND);
}

HRESULT CNativeIdent::SetName (LPCSTR pcNewName)
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))
		return E_UNEXPECTED;		// keine Pbd zugeordnet

CNativePbdIdent Ident (hPrPbd, m_lIdent, NULL, FALSE);

	RETURN_FAILED_HRESULT(Ident.SetKurzText (pcNewName));
	RETURN_FAILED_HRESULT(Ident.SaveInPBD());

WTRiASMDSMap Map;

	RETURN_FAILED_HRESULT(GetIdentMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));
	RETURN_FAILED_HRESULT(trias_nativeident_map::ReplaceShort (Map, m_lIdent, CComBSTR(pcNewName)));

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Langtext lesen
HRESULT CNativeIdent::GetDescription (LPSTR pBuffer, int iLen)		// LangText liefern
{
	_ASSERTE(NULL != pBuffer && iLen > 0);
	_ASSERTE(NULL != m_hPr);

//	SYNC_DBACCESS (g_pDbMutex, m_hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))			// keine Pbd zugeordnet
		return E_UNEXPECTED;

WTRiASMDSMap Map;
CComBSTR bstr;

	USES_CONVERSION;
	RETURN_FAILED_HRESULT(GetIdentMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));

HRESULT hr = trias_nativeident_map::RetrieveEntry (Map, m_lIdent, NULL, NULL, &bstr);

	if (SUCCEEDED(hr) && NULL != bstr.m_str && bstr.Length() > 0) {
		_ASSERTE(TIsValidAddress(pBuffer, iLen));
		strncpy (pBuffer, OLE2A(bstr), iLen-1);
		pBuffer[iLen-1] = '\0';
		return S_OK;
	}
	return MakeDefaultName (pBuffer, iLen);
}

HRESULT CNativeIdent::GetDescriptionDB (LPSTR pBuffer, int iLen, BOOL fMakeDefault, BOOL fCorrectName)
{
	_ASSERTE(NULL != pBuffer && iLen > 0);
	_ASSERTE(NULL != m_hPr);

	SYNC_DBACCESS (g_pDbMutex, m_hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))
		return E_UNEXPECTED;		// keine Pbd zugeordnet

CNativePbdIdent Ident (hPrPbd, m_lIdent, NULL, GetReportPbdErrors(), fCorrectName);

	if (!Ident)
		return fMakeDefault ? MakeDefaultName (pBuffer, iLen) : HRESULT_FROM_ERRCODE(WC_NOTFOUND);

	if (NULL == Ident.GetLangText (pBuffer, iLen))
		return fMakeDefault ? MakeDefaultName (pBuffer, iLen) : ::GetLastError();
	return S_OK;
}

HRESULT CNativeIdent::SetDescription (LPCSTR pcNewDesc)
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))
		return E_UNEXPECTED;		// keine Pbd zugeordnet

CNativePbdIdent Ident (hPrPbd, m_lIdent, NULL, FALSE);

	RETURN_FAILED_HRESULT(Ident.SetLangText (pcNewDesc));
	RETURN_FAILED_HRESULT(Ident.SaveInPBD());

WTRiASMDSMap Map;

	RETURN_FAILED_HRESULT(GetIdentMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));
	RETURN_FAILED_HRESULT(trias_nativeident_map::ReplaceLong (Map, m_lIdent, CComBSTR(pcNewDesc)));
	return S_OK;
}

// DefaultKText erzeugen
HRESULT CNativeIdent::MakeDefaultName (LPSTR pBuffer, int iLen)				// KurzText liefern
{
	_ASSERTE(NULL != pBuffer && iLen > 0);

char cbBuffer[TEXTLEN+1];
char cbOut[_MAX_PATH];
char cbOKS[65];

	if (SUCCEEDED(GetOKS (cbOKS, sizeof(cbOKS)))) {
		if (!::LoadString (g_hInstance, IDS_DEFAULTOKSKTEXT, cbBuffer, sizeof(cbBuffer)))
			return E_UNEXPECTED;
		wsprintf (cbOut, cbBuffer, cbOKS);
	} else {
		if (!::LoadString (g_hInstance, IDS_DEFAULTIDENTKTEXT, cbBuffer, sizeof(cbBuffer)))
			return E_UNEXPECTED;
		wsprintf (cbOut, cbBuffer, m_lIdent);
	}

	_ASSERTE(TIsValidAddress(pBuffer, iLen));
	_ASSERTE(iLen <= sizeof(cbOut));

	strncpy (pBuffer, cbOut, iLen-1);
	pBuffer[iLen-1] = '\0';
	return S_FALSE;		// kein Beschreibungstext vorhanden
}

/////////////////////////////////////////////////////////////////////////////
// Objektklassenschlüssel besorgen/setzen
HRESULT CNativeIdent::GetOKS (LPSTR pBuffer, int iLen)
{
	_ASSERTE(NULL != pBuffer && iLen > 0);
	_ASSERTE(NULL != m_hPr);

//	SYNC_DBACCESS (g_pDbMutex, m_hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))			// keine Pbd zugeordnet
		return E_UNEXPECTED;

WTRiASMDSMap Map;
CComBSTR bstr;

	USES_CONVERSION;
	RETURN_FAILED_HRESULT(GetIdentMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));

HRESULT hr = trias_nativeident_map::RetrieveEntry (Map, m_lIdent, &bstr);

	if (FAILED(hr) || NULL == bstr.m_str || bstr.Length() == 0) 
		return HRESULT_FROM_ERRCODE(WC_NOTFOUND);

// Resultat als OKS umkopieren
int iToCopy = min ((size_t)(iLen-3), bstr.Length());		// '[' und ']' einrechnen

	pBuffer[0] = '[';
	strncpy (pBuffer+1, OLE2A(bstr), iToCopy);
	pBuffer[iToCopy+1] = ']';
	pBuffer[iToCopy+2] = '\0';
	return S_OK;
}

HRESULT CNativeIdent::GetOKSDB (LPSTR pBuffer, int iLen)
{
	_ASSERTE(NULL != pBuffer && iLen > 0);

	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

// MerkmalsCode der OKS's aus Header lesen
COKSHeader Hdr (m_hPr);
long lMCode = Hdr.GetOKSMCode();

	if (0L == lMCode)
		return E_UNEXPECTED;

// OKS selbst vom Ident besorgen
os_string str;
HRESULT hr = GetTextMerkmal (lMCode, str);

	if (FAILED(hr)) return hr;

// Resultat als OKS umkopieren
int iToCopy = min ((size_t)(iLen-1), str.size());

	strncpy (pBuffer, str.c_str(), iToCopy);
	pBuffer[iToCopy] = '\0';
	return S_OK;
}

HRESULT CNativeIdent::SetOKS (LPCSTR pcNewOKS)
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

// MerkmalsCode der OKS's aus Header lesen
COKSHeader Hdr (m_hPr);
long lMCode = Hdr.GetOKSMCode();

	if (0L == lMCode)
		return E_UNEXPECTED;

WTRiASMDSMap Map;
HPROJECT hPrPbd = NULL;

	USES_CONVERSION;
	if (!GetRelatedProject (m_hPr, &hPrPbd))
		return E_UNEXPECTED;		// keine Pbd zugeordnet
	RETURN_FAILED_HRESULT(GetIdentMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));

	if (pcNewOKS[0] == '[') {
	// OKS ist als solcher gegeben
	string str (pcNewOKS + 1);
	size_t iLast = str.find_last_of("]");

		if (os_npos != iLast)
			str = str.substr(1, iLast-1);
		RETURN_FAILED_HRESULT(PutTextMerkmal (lMCode, str.c_str()));
		RETURN_FAILED_HRESULT(trias_nativeident_map::ReplaceOKS (Map, m_lIdent, CComBSTR(str.c_str()), this));
	} else {
	// OKS direkt wegschreiben
		RETURN_FAILED_HRESULT(PutTextMerkmal (lMCode, pcNewOKS));
		RETURN_FAILED_HRESULT(trias_nativeident_map::ReplaceOKS (Map, m_lIdent, CComBSTR(pcNewOKS), this));
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Textmerkmal eines Identifikators lesen
HRESULT CNativeIdent::GetTextMerkmal (long lMCode, os_string &rStr)
{
CActDB ActDB(m_hPr);
long lTarget = ::GetMerkmalTarget (m_hPr, (void *)m_lIdent, TT_Identifikator);

	if (-1 == lTarget) return E_UNEXPECTED;

char *pT = NULL;

	try {
		THROW_FAILED_HRESULT(::GetTextMerkmal (m_hPr, lMCode, lTarget, TT_Identifikator, &pT));
		rStr = pT;

	} catch (_com_error &e) {
		DELETE_VEC(pT);
		return _COM_ERROR(e);
	} catch (...) {
		DELETE_VEC(pT);
		return E_OUTOFMEMORY;
	}

	DELETE_VEC(pT);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Neues Textmerkmal erzeugen
HRESULT CNativeIdent::PutTextMerkmal (long lMCode, LPCSTR pcNewText)
{
CActDB ActDB(m_hPr);
long lTarget = ::GetMerkmalTarget (m_hPr, (void *)m_lIdent, TT_Identifikator);
ErrInstall EI (WC_NOTFOUND);

	if (-1 == lTarget) {
		RETURN_FAILED_HRESULT(::CreateMerkmalTarget (m_hPr, TT_Identifikator, m_lIdent, &lTarget));
		return ::PutTextMerkmal (m_hPr, lMCode, lTarget, TT_Identifikator, pcNewText);
	} else {
		::DeleteTextMerkmal (m_hPr, lMCode, lTarget, TT_Identifikator);

	// DeleteTextMerkmal gibt IdentSatz evtl. frei		
		lTarget = ::GetMerkmalTarget (m_hPr, (void *)m_lIdent, TT_Identifikator);
		if (-1 == lTarget) 
			RETURN_FAILED_HRESULT(::CreateMerkmalTarget (m_hPr, TT_Identifikator, m_lIdent, &lTarget));
		return ::PutTextMerkmal (m_hPr, lMCode, lTarget, TT_Identifikator, pcNewText);
	}
}

/////////////////////////////////////////////////////////////////////////////
// Textmerkmal löschen
HRESULT CNativeIdent::DeleteTextMerkmal (long lMCode)
{
CActDB ActDB(m_hPr);
long lTarget = ::GetMerkmalTarget (m_hPr, (void *)m_lIdent, TT_Identifikator);

	if (-1 == lTarget) 
		return E_UNEXPECTED;

ErrInstall EI (WC_NOTFOUND);

	return ::DeleteTextMerkmal (m_hPr, lMCode, lTarget, TT_Identifikator);
}

///////////////////////////////////////////////////////////////////////////////
// Festellen eines Objettypes an Hand des ObjektSatzes
/*static*/
DWORD CNativeIdent::GetObjectType (struct obl &rOBLSatz)
{
	if (rOBLSatz.status & (SB_TEXTOBJ|SB_TEXTOBJIND)) 
		return OTText;
	if (rOBLSatz.status & SB_SACHOBJ) 
		return OTSachObjekt;
	if (rOBLSatz.rmaske & OREL) 
		return OTKO;

	if (rOBLSatz.zokp) 
		return OTPunkt;
	if (rOBLSatz.zovol) 
		return OTLinie;
	if (rOBLSatz.zovoma) 
		return OTFlaeche;

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Enumeration aller Objekte eines IdentifikatorSatzes mit vorgebbaren Objekttypen

/*static*/
HRESULT CNativeIdent::EnumObjectsIdlEx (
	HPROJECT hPr, LONG lIdent, LONG lRecNo, DWORD dwTypes,
	HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData, 
	BOOL fVerifyType)
{
// DatenBasis aktivieren
CActDB ActDB (hPr);
DB_ADDR dbaVIO (hPr);
bool iRC = true;
HRESULT hr;
ErrCode RC;
long lVersion = ::LocGetDBVersion(hPr);

	if (VERSION0500000F <= lVersion) {
	long lNextVIO = 0L;
	long lIdLink = 0L;

		dbaVIO.file_no = VIO_NEW;
		dbaVIO.rec_no = lRecNo;
		while (iRC && dbaVIO.rec_no != 0) {
			if (VERSION05000011 <= lVersion) {
			// Elemente des Keys jetzt getauscht
			struct identx VIOSatz;

			// lfd. VIOSatz lesen
				__ReadHR(dbaVIO, VIOSatz);
				_ASSERTE(lIdent == VIOSatz.identxkey.identx);

				lIdLink = LINKTOLINK(VIOSatz.identxkey.zvioox);
				lNextVIO = VIOSatz.zvionk;

			} else {
			// bisherige Variante
			struct identb VIOSatz;

			// lfd. VIOSatz lesen
				__ReadHR(dbaVIO, VIOSatz);
				_ASSERTE(lIdent == VIOSatz.identbkey.identk);

				lIdLink = LINKTOLINK(VIOSatz.identbkey.zviook);
				lNextVIO = VIOSatz.zvionk;
			}

		// ObjektSatz nur auswerten, wenn _DEBUG, oder wenn wirklich notwendig

	#if defined(_DEBUG)
		// ObjektSatz lesen, Typ feststellen
		struct obl OBLSatz;
		DB_ADDR_OBL dbaOBL (hPr);

			dbaOBL.rec_no = lIdLink;
			__ReadHR (dbaOBL, OBLSatz);

		// Objekttypen liefern
		DWORD dwOTyp = GetObjectType (OBLSatz);
			
		// ObjektTyp muß eindeutig sein, oder alle Objekttypen behandeln
			_ASSERTE(fVerifyType || dwOTyp == dwTypes);
			if (dwTypes & dwOTyp) {	// nur wenn dieser Objekttyp gefordert ist
				try {
					hr = trias_connectfilter::EnumObjectsWrapper (hPr, lIdLink, 
						dwOTyp, pFcn, dwData);
					if (S_OK != hr) return hr;
					
				} catch (bool fResult) {
				// abbrechen der Enumeration
					iRC = fResult;
					break;		// bei neuen GeoDB's hier aufhören
				}
			}
	#else
			if (fVerifyType) {
			// ObjektSatz lesen, Typ feststellen
			struct obl OBLSatz;
			DB_ADDR_OBL dbaOBL (hPr);

				dbaOBL.rec_no = lIdLink;
				__ReadHR (dbaOBL, OBLSatz);

			// Objekttypen liefern
			DWORD dwOTyp = GetObjectType (OBLSatz);
				
				if (dwTypes & dwOTyp) {	// nur wenn dieser Objekttyp gefordert ist
					try {
						hr = trias_connectfilter::EnumObjectsWrapper (hPr, lIdLink, 
							dwOTyp, pFcn, dwData);
						if (S_OK != hr)	return hr;
						
					} catch (bool fResult) {
					// abbrechen der Enumeration
						iRC = fResult;
						break;		// bei neuen GeoDB's hier aufhören
					}
				} 
			} 
			else {
				try {
					hr = trias_connectfilter::EnumObjectsWrapper (hPr, lIdLink, 
						dwTypes, pFcn, dwData);
					if (S_OK != hr) return hr;
					
				} catch (bool fResult) {
				// abbrechen der Enumeration
					iRC = fResult;
					break;		// bei neuen GeoDB's hier aufhören
				}
			}
	#endif // _DEBUG

			ActDB.ReActivate();	// für alle Fälle wieder aktivieren
			dbaVIO.rec_no = lNextVIO;
		}
		return iRC ? S_OK : S_FALSE;
	}

// hier wieder alles beim Alten (Version <= VERSION0500000F)
struct vio VIOSatz;

	dbaVIO.file_no = VIO_OLD;
	dbaVIO.rec_no = lRecNo;
	while (iRC && dbaVIO.rec_no != 0) {
	// lfd. VIOSatz lesen
		__ReadHR(dbaVIO, VIOSatz);

	// ObjektSatz nur auswerten, wenn _DEBUG, oder wenn wirklich notwendig

#if defined(_DEBUG)
	// ObjektSatz lesen, Typ feststellen
	struct obl OBLSatz;
	DB_ADDR_OBL dbaOBL (hPr);

		dbaOBL.rec_no = VIOSatz.zvioo;
		__ReadHR(dbaOBL, OBLSatz);

	DWORD dwOTyp = GetObjectType (OBLSatz);
		
	// ObjektTyp muß eindeutig sein, oder alle Objekttypen behandeln
		_ASSERTE(fVerifyType || dwOTyp == dwTypes);
		if (dwTypes & dwOTyp) {	// nur wenn dieser Objekttyp gefordert ist
			try {
				hr = trias_connectfilter::EnumObjectsWrapper (hPr, 
					VIOSatz.zvioo, dwOTyp, pFcn, dwData);
				if (S_OK != hr) return hr;
				
			} catch (bool fResult) {
			// abbrechen der Enumeration
				iRC = fResult;
				if (VERSION0500000E <= lVersion)
					break;		// beí neueren GeoDB's hier aufhören
			}
		}
#else
		if (fVerifyType) {
		// ObjektSatz lesen, Typ feststellen
		struct obl OBLSatz;
		DB_ADDR_OBL dbaOBL (hPr);

			dbaOBL.rec_no = VIOSatz.zvioo;
			__ReadHR(dbaOBL, OBLSatz);

		DWORD dwOTyp = GetObjectType (OBLSatz);
			
			if (dwTypes & dwOTyp)	{	// nur wenn dieser Objekttyp gefordert ist
				try {
					hr = trias_connectfilter::EnumObjectsWrapper (hPr, 
						VIOSatz.zvioo, dwOTyp, pFcn, dwData);
					if (S_OK != hr) return hr;
					
				} catch (bool fResult) {
				// abbrechen der Enumeration
					iRC = fResult;
					if (VERSION0500000E <= lVersion)
						break;		// beí neueren GeoDB's hier aufhören
				}
			} 
		} 
		else {
			try {
				hr = trias_connectfilter::EnumObjectsWrapper (hPr, 
					VIOSatz.zvioo, dwTypes, pFcn, dwData);
				if (S_OK != hr) return hr;
				
			} catch (bool fResult) {
			// abbrechen der Enumeration
				iRC = fResult;
				if (VERSION0500000E <= lVersion)
					break;		// beí neueren GeoDB's hier aufhören
			}
		}
#endif // _DEBUG

		ActDB.ReActivate();	// für alle Fälle wieder aktivieren
		dbaVIO.rec_no = VIOSatz.znvio;
	}
	return iRC ? S_OK : S_FALSE;
}

HRESULT CNativeIdent::HasObjects()
{
// Feststellen, ob Ident bereits existiert
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (0 != m_lRecNo) {
	CActDB ActDB (m_hPr);
	struct idl IDLSatz;
	DB_ADDR_IDL dbaIDL (m_hPr, m_lRecNo);
	ErrCode RC;

		__ReadHR(dbaIDL, IDLSatz);
		return IDLRecHasObjects (m_hPr, &IDLSatz) ? S_FALSE : S_OK;
	} 
	return S_FALSE;	// no Ident, no Objects
}

HRESULT CNativeIdent::Delete(bool fDeleteAllObjects)
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

// IDLSatz aus DB herauslöschen
	if (0 != m_lRecNo) {
	CActDB ActDB (m_hPr);
	struct idl IDLSatz;
	DB_ADDR_IDL dbaIDL (m_hPr, m_lRecNo);
	ErrCode RC;

		__ReadHR(dbaIDL, IDLSatz);

	HRESULT hr = IDLRecHasObjects (m_hPr, &IDLSatz);

		if (S_OK == hr && !fDeleteAllObjects)
			hr = E_UNEXPECTED;
		if (FAILED(hr))
			return hr;		// Fehler oder noch Objekte vorhanden

	// ggf. alle Objekte löschen
		if (fDeleteAllObjects) {
		vector<INT_PTR> Objs;

			if (SUCCEEDED(GetObjects(OTAll, Objs))) {
				for (vector<INT_PTR>::iterator it = Objs.begin(); it != Objs.end(); ++it) {
				trias_nativeobject::CNativeObject Obj (m_hPr, *it);

					Obj.Delete(FALSE);		// Fehler nicht auswerten
				}
			}
		}

		while (S_OK == (hr = DeleteTextMerkmal(-1L)))		// alle noch existierenden Merkmale löschen
			;

	// der IDLSatz darf nicht mehr existieren
	ErrInstall E1(EC_INVADDR);
	ErrInstall E2(EC_DELRECORD);
		
		RC = (ErrCode)z_dispose(&dbaIDL);
		_ASSERTE(EC_INVADDR == RC || EC_DELRECORD == RC || EC_OKAY == RC);
	}

// nun auch aus Pbd herauslöschen
HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))
		return S_OK;		// keine Pbd zugeordnet

CNativePbdIdent Ident (hPrPbd, m_lIdent, NULL, FALSE);

	RETURN_FAILED_HRESULT(Ident.DeleteInPBD());

WTRiASMDSMap Map;

	RETURN_FAILED_HRESULT(GetIdentMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));
	RETURN_FAILED_HRESULT(trias_nativeident_map::RemoveEntry (Map, m_lIdent));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IdentMap mit allen derzeit existierenden Idents füllen
namespace {
	typedef struct tagFILLIDENTSDATA {
		HPROJECT m_hPr;
		ITRiASMDSMap *m_pIMap;
		set<INT_PTR> *m_pIdents;
		bool m_fFillMap;
		bool m_fNoCase;
	} FILLIDENTSDATA;
};

/*static*/
HRESULT CALLBACK CNativeIdent::StorePBDIdents (INT_PTR lIdent, UINT_PTR dwData)
{
	return StorePBDIdentsEx (lIdent, DWORD(-1L), dwData);
}

/*static*/
HRESULT CALLBACK CNativeIdent::StorePBDIdentsEx (INT_PTR lIdent, DWORD dwTypes, UINT_PTR dwData)
{
FILLIDENTSDATA *pFID = reinterpret_cast<FILLIDENTSDATA *>(dwData);
WTRiASMDSMap Map (pFID -> m_pIMap);

	if (!pFID -> m_fFillMap) {
	// jetzt nur noch nicht dagewesene Idents durchlassen
		if (pFID -> m_pIdents -> find(lIdent) != pFID -> m_pIdents -> end())
			return S_FALSE;	// den hatten wir schon
	}

// alle dagewesenen aufsammeln
	pFID -> m_pIdents -> insert (lIdent);

CComBSTR bstrOKS;
CComBSTR bstrShort;
CComBSTR bstrLong;
char cbBuffer[_MAX_PATH];

CNativeIdent Ident (pFID -> m_hPr, lIdent, OTPunkt|OTLinie|OTFlaeche|OTText);

	Ident.ReportPbdErrors (FALSE);
	if (SUCCEEDED(Ident.GetOKSDB (cbBuffer, sizeof(cbBuffer))))
		bstrOKS = cbBuffer;			// evtl. ist OKS vorhanden
	
	if (SUCCEEDED(Ident.GetNameDB (cbBuffer, sizeof(cbBuffer), FALSE, FALSE)))
		bstrShort = cbBuffer;		// Kurztext (unverfälscht)

	if (SUCCEEDED(Ident.GetDescriptionDB (cbBuffer, sizeof(cbBuffer), FALSE, FALSE)))
		bstrLong = cbBuffer;		// Langtext (unverfälscht)

// existierende Objekttypen laden
HRESULT hr = S_OK;

	if (DWORD(-1) == dwTypes)
		hr = Ident.GetObjectTypesAndCounts (LOOKUPSPEED_INFINITE, dwTypes, NULL);

	if (SUCCEEDED(hr)) {
		dwTypes |= Ident.GetFullTypeDB();
		hr = trias_nativeident_map::InsertEntry (Map, lIdent, bstrOKS, bstrShort, bstrLong, dwTypes, pFID -> m_fNoCase);
	}
	return hr;
}

/*static*/
HRESULT CNativeIdent::FillWithIdents (HPROJECT hPr, ITRiASMDSMap *pIMap, bool fNoCase)
{
	_ASSERTE(NULL != hPr);
	SYNC_DBACCESS (g_pDbMutex, hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (hPr, &hPrPbd))			// keine Pbd zugeordnet
		return E_UNEXPECTED;
		
FILLIDENTSDATA FID;
set<INT_PTR> Idents;

	FID.m_hPr = hPr;
	FID.m_pIMap = pIMap;
	FID.m_pIdents = &Idents;
	FID.m_fFillMap = true;
	FID.m_fNoCase = fNoCase;

HRESULT hr = EnumIdentsDB (hPr, StorePBDIdentsEx, reinterpret_cast<UINT_PTR>(&FID));

	if (FAILED(hr))
		return hr;

	FID.m_fFillMap = false;
	return CNativePbdIdent::EnumPBDData(hPrPbd, StorePBDIdents, reinterpret_cast<UINT_PTR>(&FID));
}

///////////////////////////////////////////////////////////////////////////////
// zusätzliche Flags des identifikators behandeln
HRESULT CNativeIdent::GetReadOnly (BOOL *pfReadOnly)
{
	_ASSERTE(NULL != m_hPr);
	if (NULL == pfReadOnly)
		return E_POINTER;

HPROJECT hPrPbd = NULL;
WTRiASMDSMap Map;

	if (!GetRelatedProject (m_hPr, &hPrPbd))			// keine Pbd zugeordnet
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(GetIdentMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));

DWORD dwTypes = 0;
HRESULT hr = trias_nativeident_map::RetrieveEntry (Map, m_lIdent, NULL, NULL, NULL, &dwTypes);

	*pfReadOnly = dwTypes & CNativePbdIdent::PBDIDENTTYPE_ReadOnly;
	return S_OK;
}

HRESULT CNativeIdent::GetSystem (BOOL *pfSystem)
{
	_ASSERTE(NULL != m_hPr);
	if (NULL == pfSystem)
		return E_POINTER;

HPROJECT hPrPbd = NULL;
WTRiASMDSMap Map;

	if (!GetRelatedProject (m_hPr, &hPrPbd))			// keine Pbd zugeordnet
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(GetIdentMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));

DWORD dwTypes = 0;
HRESULT hr = trias_nativeident_map::RetrieveEntry (Map, m_lIdent, NULL, NULL, NULL, &dwTypes);

	*pfSystem = dwTypes & CNativePbdIdent::PBDIDENTTYPE_System;
	return S_OK;
}

HRESULT CNativeIdent::GetFullType(DWORD *pdwTypes)
{
	_ASSERTE(NULL != m_hPr);
	if (NULL == pdwTypes)
		return E_POINTER;

HPROJECT hPrPbd = NULL;
WTRiASMDSMap Map;

	if (!GetRelatedProject (m_hPr, &hPrPbd))			// keine Pbd zugeordnet
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(GetIdentMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));
	return trias_nativeident_map::RetrieveEntry (Map, m_lIdent, NULL, NULL, NULL, pdwTypes);
}

HRESULT CNativeIdent::SetReadOnly (BOOL fReadOnly)
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))			// keine Pbd zugeordnet
		return E_UNEXPECTED;

// in Pbd nachführen
CNativePbdIdent Ident (hPrPbd, m_lIdent, NULL, FALSE);

	Ident.SetReadOnly (fReadOnly);
	RETURN_FAILED_HRESULT(Ident.SaveInPBD());

// lokal in Map austauschen
WTRiASMDSMap Map;
DWORD dwType = 0;

	RETURN_FAILED_HRESULT(GetIdentMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));

	RETURN_FAILED_HRESULT(trias_nativeident_map::RetrieveEntry (Map, m_lIdent, NULL, NULL, NULL, &dwType));
	dwType = (dwType & ~CNativePbdIdent::PBDIDENTTYPE_ReadOnly) | (fReadOnly ? CNativePbdIdent::PBDIDENTTYPE_ReadOnly: 0);
	RETURN_FAILED_HRESULT(trias_nativeident_map::ReplaceTypes (Map, m_lIdent, dwType));

	return S_OK;
}

HRESULT CNativeIdent::SetSystem (BOOL fSystem)
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))			// keine Pbd zugeordnet
		return E_UNEXPECTED;

// in Pbd nachführen
CNativePbdIdent Ident (hPrPbd, m_lIdent, NULL, FALSE);

	Ident.SetSystem (fSystem);
	RETURN_FAILED_HRESULT(Ident.SaveInPBD());

// lokal in Map austauschen
WTRiASMDSMap Map;
DWORD dwType = 0;

	RETURN_FAILED_HRESULT(GetIdentMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));

	RETURN_FAILED_HRESULT(trias_nativeident_map::RetrieveEntry (Map, m_lIdent, NULL, NULL, NULL, &dwType));
	dwType = (dwType & ~CNativePbdIdent::PBDIDENTTYPE_System) | (fSystem ? CNativePbdIdent::PBDIDENTTYPE_System : 0);
	RETURN_FAILED_HRESULT(trias_nativeident_map::ReplaceTypes (Map, m_lIdent, dwType));

	return S_OK;
}

DWORD CNativeIdent::GetFullTypeDB()
{
HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))			// keine Pbd zugeordnet
		return E_UNEXPECTED;

// in Pbd nachführen
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CNativePbdIdent Ident (hPrPbd, m_lIdent, NULL, FALSE);

	return Ident.GetFullType();
}

/*static*/ 
HRESULT CNativeIdent::FindFromName (HPROJECT hPr, LPCSTR pcName, VARIANT_BOOL fCaseSensitive, INT_PTR *plIdent)
{
	_ASSERTE(NULL != hPr);
	SYNC_DBACCESS (g_pDbMutex, hPr);

HPROJECT hPrPbd = NULL;
WTRiASMDSMap Map;

	if (!GetRelatedProject (hPr, &hPrPbd))			// keine Pbd zugeordnet
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(GetIdentMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));
	return trias_nativeident_map::FindFromName (Map, CComBSTR(pcName), CComBool(fCaseSensitive), plIdent);
}

///////////////////////////////////////////////////////////////////////////////
// IdentGuid behandeln
HRESULT CNativeIdent::GetIdentGUID (struct _GUID *pGuid)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (0 == m_lIdent || 0 == m_lRecNo)
		return E_UNEXPECTED;

CActDB ActDB(m_hPr);

	if (VERSION05000013 <= LocGetDBVersion(m_hPr)) {
	// GUID's sind direkt in der GeoDB gespeichert
	DB_ADDR_IDL dbaIDL (m_hPr, m_lRecNo);
	struct idl IDLSatz;
	ErrCode RC;		// FehlerCode

		__ReadHR (dbaIDL, IDLSatz);
		*pGuid = IDLSatz.idguid;
	} 
	else {
	// GUID's werden als spezielle Merkmale gehalten
	CObjGuidHeader GuidHdr (m_hPr);
	HRESULT hr = S_FALSE;
	os_string str;
	long lMCode = GuidHdr.GetObjGuidCode();

		if (0 == lMCode) 
			return E_UNEXPECTED;

		if (SUCCEEDED(GetTextMerkmal (lMCode, str))) {
		os_string strGuid("{");
		
			strGuid += str;
			strGuid += "}";

		CIID Guid (strGuid.c_str());

			if (!!Guid) {
				*pGuid = Guid;
				return S_OK;
			}
			TX_ASSERT(!!Guid);

		// und durchfallen
		// ...
		} 

	// alle Fehler definiert behandeln
		{
		CIID Guid;		// neuen Guid erzeugen
		os_string subGuid = Guid;

		// '{' und '}' entfernen, damit es genau 36 Zeichen werden (kein FolgeSatz in der DB)
			subGuid = subGuid.substr (1, 36);
			RETURN_FAILED_HRESULT(PutTextMerkmal (lMCode, subGuid.c_str()));

			memcpy (pGuid, &Guid, sizeof(GUID));
		}
	}
	return S_OK;
}

HRESULT CNativeIdent::SetIdentGUID (const _GUID &rGuid)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (0 == m_lIdent || 0 == m_lRecNo)
		return E_UNEXPECTED;

CActDB ActDB(m_hPr);

	if (VERSION05000013 <= LocGetDBVersion(m_hPr)) {
	// GUID's sind direkt in der GeoDB gespeichert
	INT_PTR lTarget = 0L;
	HRESULT hr = FindIdentFromGUID (m_hPr, rGuid, &lTarget);

		if (SUCCEEDED(hr)) 
			return (lTarget == m_lIdent) ? S_OK : HRESULT_FROM_ERRCODE(S_DUPLICATE);

	DB_ADDR_IDL dbaIDL (m_hPr, m_lRecNo);
	struct idl IDLSatz;
	ErrCode RC;		// FehlerCode

		__ReadHR (dbaIDL, IDLSatz);
		
	ErrInstall Duplicate (WC_DUPLICATE);		// GUID muß unique sein

		IDLSatz.idguid = rGuid;
		__WriteHR(dbaIDL, IDLSatz);
	} 
	else {
	// GUID's werden als spezielle Merkmale gehalten
	CObjGuidHeader GuidHdr (m_hPr);
	long lMCode = GuidHdr.GetObjGuidCode();

		if (0 == lMCode) return E_UNEXPECTED;

	// erstmal feststellen, on dieser Guid noch nicht vertreten ist
	INT_PTR lTarget = 0L;
	HRESULT hr = FindIdentFromGUID (m_hPr, rGuid, &lTarget);

		if (SUCCEEDED(hr)) 
			return (lTarget == m_lIdent) ? S_OK : HRESULT_FROM_ERRCODE(WC_DUPLICATE);

	// jetzt wirklich schreiben
	CIID Guid (rGuid);

	// '{' und '}' entfernen, damit es genau 36 Zeichen werden (kein FolgeSatz in der DB)
	os_string subGuid = Guid;

		subGuid = subGuid.substr (1, 36);
		RETURN_FAILED_HRESULT(PutTextMerkmal (lMCode, subGuid.c_str()));
	}
	return S_OK;
}

/*static*/
HRESULT CNativeIdent::FindIdentFromGUID (HPROJECT hPr, const _GUID &rGuid, INT_PTR *plIdent)
{
	TX_ASSERT(NULL != hPr);
	SYNC_DBACCESS (g_pDbMutex, hPr);

CActDB ActDB(hPr);

	if (VERSION05000013 <= LocGetDBVersion(hPr)) {
	// GUID's sind direkt in der GeoDB gespeichert
	DB_ADDR_IDL dbaIDL(hPr);
	ErrInstall EI (WC_NOTFOUND);
	ErrCode RC;
	
		DBASSERTHR(z_keyfind (&dbaIDL, IDGUID, (LPVOID)&rGuid));
		*plIdent = dbaIDL.rec_no;
	} 
	else {
	// GUID's werden als spezielle Merkmale gehalten
	CObjGuidHeader GuidHdr (hPr);
	long lMCode = GuidHdr.GetObjGuidCode();

		if (0 == lMCode) return E_UNEXPECTED;

	vector <unsigned long> Idents;
	CIID Guid (rGuid);
	// '{' und '}' entfernen, damit es genau 36 Zeichen werden (kein FolgeSatz in der DB)
	os_string subGuid = Guid;

		subGuid = subGuid.substr (1, 36);
	
	HRESULT hr = ::FindTextMerkmal (hPr, lMCode, subGuid.c_str(), SMExactMatch, IDL_OLD, Idents);

		if (FAILED(hr)) 
			return hr;

		if (1 != Idents.size())
			return E_UNEXPECTED;
		*plIdent = Idents[0];
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// CreationDate und ModificationDate behandeln
HRESULT CNativeIdent::GetCreationDate(DATE *pdCreate)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (NULL == pdCreate)
		return E_POINTER;
	*pdCreate = 0;

	if (0 == m_lIdent || 0 == m_lRecNo)
		return E_UNEXPECTED;

	if (LocGetDBVersion(m_hPr) < VERSION05000013)
		return S_FALSE;

// IdentSatz lesen
CActDB ActDB(m_hPr);
DB_ADDR_IDL dbaIDL (m_hPr, m_lRecNo);
struct idl IDLSatz;
ErrCode RC;		// FehlerCode

	__ReadHR (dbaIDL, IDLSatz);
	*pdCreate = IDLSatz.idcreate;
	return S_OK;
}

HRESULT CNativeIdent::GetModificationDate(DATE *pdCreate)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (NULL == pdCreate)
		return E_POINTER;
	*pdCreate = 0;

	if (0 == m_lIdent || 0 == m_lRecNo)
		return E_UNEXPECTED;

	if (LocGetDBVersion(m_hPr) < VERSION05000013)
		return S_FALSE;

// IdentSatz lesen
CActDB ActDB(m_hPr);
DB_ADDR_IDL dbaIDL (m_hPr, m_lRecNo);
struct idl IDLSatz;
ErrCode RC;		// FehlerCode

	__ReadHR (dbaIDL, IDLSatz);
	*pdCreate = IDLSatz.idmodify;
	return S_OK;
}

} // namespace trias_nativeident
