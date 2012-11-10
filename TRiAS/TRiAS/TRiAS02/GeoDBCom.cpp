///////////////////////////////////////////////////////////////////////////////
// @doc
// @module GeoDBCom.cpp | TRiASDB Spezifika in der Klasse <c GeoDB>

#include "trias02p.hxx"
#include "trias02.h"

#include <ospace/std/set>
#include <Com/PropertyHelper.h>
#include <Com/ComBool.h>

#include <DbMsg.hmc>
#include <HdrEntry.hxx>

#include "Strings.h"
#include "Globalvars.h"
#include "MapCaches.h"

#import "tlb/Helper.tlb"	raw_interfaces_only raw_dispinterfaces no_namespace named_guids	\
	exclude("IParseRegularExpression", "IParseStringPairs", "IComposeStringPairs") \
	exclude("IParseStringPairs2")

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASDatabase);			// WTRiASDatabase
DefineSmartInterface(TRiASProperty);
DefineSmartInterface(TRiASProperties);
DefineSmartInterface(TRiASObjectHandleMap);		// WTRiASObjectHandleMap
DefineSmartInterface(TRiASObjectsCollection);	// WTRiASObjectsCollection
DefineSmartInterface(TRiASSimpleObjects);		// WTRiASSimpleObjects
DefineSmartInterface(TRiASObjects);				// WTRiASObjects
DefineSmartInterface(TRiASAccessDatabase);		// WTRiASAccessDatabase
DefineSmartInterface(EnumVARIANT);				// WEnumVARIANT
DefineSmartInterface(TRiASFeatures);			// WTRiASFeatures
DefineSmartInterface(TRiASFeature);				// WTRiASFeature
DefineSmartInterface(CookieHelper);				// WCookieHelper
DefineSmartInterface(TRiASSimpleFeature);		// WTRiASSimpleFeature
DefineSmartInterface(TRiASSimpleFeatures);		// WTRiASSimpleFeatures
DefineSmartInterface(Dispatch);					// WDispatch

HRESULT GeoDB::AttachConnection (ITRiASConnection *pIConn, ITRiASConnection **ppIConn)
{
	COM_TRY {
	// Database speichern
	WTRiASConnection Conn (m_Conn);

		m_Conn = pIConn;			// throws hr
		if (NULL != ppIConn)
			*ppIConn = Conn.detach();

		if (!m_Conn.IsValid())		// Detach
			return S_OK;

	// nur zu öffnende Connections behandeln
	CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

		THROW_FAILED_HRESULT(m_Conn -> get_Status (&rgStatus));
		if (CONNECTSTATUS_Opened == rgStatus) {
		// als erstes das DBHandle++ abfragen
		WTRiASDatabase DBase;

			THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));
			TX_ASSERT(sizeof(LONG) == sizeof(HPROJECT));
			THROW_FAILED_HRESULT(DBase -> get_Handle ((INT_PTR *)&_DBDesc));

		VARIANT_BOOL fCopy = VARIANT_FALSE;

			THROW_FAILED_HRESULT(DBase -> get_OpenedAsCopy (&fCopy));
			SetCopy (fCopy ? TRUE : FALSE);

		VARIANT_BOOL fRW = VARIANT_FALSE;

			THROW_FAILED_HRESULT(DBase -> get_Updatable (&fRW));
			SetROMode (fRW ? FALSE : TRUE);

// wird später explizit besorgt
//		// alle notwendigen Properties der Database abfragen
//			if (!ReReadHeader())
//				return E_FAIL;
		}
	} COM_CATCH;
	return S_OK;
}

HRESULT GeoDB::GetConnection (ITRiASConnection **ppIConn)
{
	if (NULL == ppIConn) 
		return E_POINTER;
	
WTRiASConnection Conn (m_Conn);

	*ppIConn = Conn.detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ProjektHeaderFunktionen
inline CComBSTR PrepareKey (LPSTR pKey)
{
char cbBuffer[HDRKEYLENGTH+1];

	strncpy (cbBuffer, pKey, HDRKEYLENGTH);
	cbBuffer[HDRKEYLENGTH] = '\0';

LPSTR pT = strrlchr (cbBuffer, TEXT(' '));

	if (NULL != pT)
		 *pT = '\0';
	return CComBSTR(cbBuffer);
}

ErrCode GeoDB::GetHeaderEntry (GEODBHDRENTRY *pHE)
{
	TX_ASSERT(IsTRiASDBBased());
	USES_CONVERSION;

	COM_TRY {
	WTRiASDatabase DBase;

		THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));

	WTRiASProperty Prop;
	CComBSTR vProp (PrepareKey(pHE -> hdrKey));
	CComVariant vVal;

		THROW_FAILED_HRESULT(WTRiASPropertyBase(DBase) -> get_Property (vProp, Prop.ppi()));
		if (SUCCEEDED(Prop -> get_Value (&vVal)) && SUCCEEDED(vVal.ChangeType (VT_BSTR)))
		{
			strncpy (pHE -> lphdrText, OLE2A(V_BSTR(&vVal)), pHE -> hdrTextLen);
			pHE -> lphdrText[pHE -> hdrTextLen -1] = '\0';
			if (sizeof(GEODBHDRENTRYEX) == pHE -> dwSize) {
			LONG lType = 0L;

				THROW_FAILED_HRESULT(Prop -> get_Type ((PROPERTY_TYPE *)&lType));
				((GEODBHDRENTRYEX *)pHE) -> dwFlags = lType;
			}
			return EC_OKAY;
		}
	} COM_CATCH_IGNORE;

// nichts gefunden oder sonstiger Fehler
	*pHE -> lphdrText = '\0';
	return WC_NOTFOUND;
}

ErrCode GeoDB::SetHeaderEntry (GEODBHDRENTRY *pHE)
{
	TX_ASSERT(IsTRiASDBBased());

	COM_TRY {
	WTRiASDatabase DBase;

		THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));

	WTRiASProperty Prop;
	CComBSTR vProp (PrepareKey(pHE -> hdrKey));
	WTRiASPropertyBase Propbase(DBase);
	HRESULT hr = Propbase -> get_Property (vProp, Prop.ppi());

		if (FAILED(hr)) {
			if (TRIASDB_E_UNKNOWN_PROPERTY == hr) {
				THROW_FAILED_HRESULT(Propbase -> CreateProperty (vProp, Prop.ppi()));
			} else
				THROW_FAILED_HRESULT(hr);
		}

	// Wert bzw. Typ setzen
	CComVariant vVal (pHE -> lphdrText);

		if (sizeof(GEODBHDRENTRYEX) == pHE -> dwSize)
		{
		LONG lType = ((GEODBHDRENTRYEX *)pHE) -> dwFlags;

			THROW_FAILED_HRESULT(Prop -> SetValueAndType (vVal, (PROPERTY_TYPE)lType));
		} else {
			THROW_FAILED_HRESULT(Prop -> put_Value (vVal));
		}

	} COM_CATCH_RETURN(EC_FAIL);

	return EC_OKAY;
}

ErrCode GeoDB::DeleteHeaderEntry (GEODBHDRENTRY *pHE)
{
	TX_ASSERT(IsTRiASDBBased());

	COM_TRY {
	WTRiASDatabase DBase;

		THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));

	WTRiASProperty Prop;
	CComBSTR vProp (PrepareKey(pHE -> hdrKey));
	WTRiASPropertyBase Propbase(DBase);
	HRESULT hr = Propbase -> get_Property (vProp, Prop.ppi());

		if (SUCCEEDED(hr)) {
			THROW_FAILED_HRESULT(Propbase -> RemoveProperty (vProp));
		} else
			return WC_NOTFOUND;

	} COM_CATCH_RETURN(EC_FAIL);
	return EC_OKAY;
}

BOOL GeoDB::EnumHeaderData (ENUMNOKEYCALLBACK pFcn, void *pData)
{
	TX_ASSERT(IsTRiASDBBased());
	USES_CONVERSION;
		
	COM_TRY {
	WTRiASDatabase DBase;

		THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));

	WTRiASProperties Props;
	WTRiASProperty Prop;

		THROW_FAILED_HRESULT(WTRiASPropertyBase(DBase) -> get_Properties (Props.ppi()));

	long lCnt = 0;

		THROW_FAILED_HRESULT(Props -> get_Count (&lCnt));
		for (long i = 1; i <= lCnt; i++) {
		CComVariant vIndex (i, VT_I4);

			if (FAILED(Props -> Item (vIndex, Prop.ppi())))
				continue;		// irgend ein Fehler

		// CallBack rufen
		CComBSTR Val;

			THROW_FAILED_HRESULT(Prop -> get_Name (&Val));

			if (!pFcn (OLE2A(Val), i < lCnt, pData))
				return FALSE;
		}

	} COM_CATCH_RETURN(FALSE);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// MetaDatenZugriff
ErrCode GeoDB::ModPBDDataIdent (PBDDATA *pData)
{
	TX_ASSERT(IsTRiASDBBased());

ErrCode RC = EC_OKAY;

	USES_CONVERSION;
	COM_TRY {
	WTRiASDatabase DBase;

		THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));

	WTRiASObjectHandleMap Map; // (CLSID_TRiASObjectsHandleMap);
	WTRiASObjects Objs;

		if (FAILED(GetObjectsMap(Map.ppi())))
			return WC_NOTFOUND;

	// wiederauffinden des Objects-Objektes
		if (FAILED(Map -> GetObject(pData -> pbdCode, Objs.ppu()))) {
			TX_ASSERT(pData -> pbdKTextLen > 0 && NULL != pData -> pbdKText);	// KurzText muß gegeben sein

		// Objektmenge (Tabelle) muß neu angelegt werden
		WTRiASObjectsCollection ObjsDefs;
		char cbBuffer[64] = { '\0' };

#pragma MESSAGE("Was tun, wenn IdentBase nicht übereinstimmt?")

			_ultoa (pData -> pbdCode, cbBuffer, m_iIdentBase);
			THROW_FAILED_HRESULT(WTRiASAccessDatabase(DBase) -> get_ObjectsDefs (ObjsDefs.ppi()));
			THROW_FAILED_HRESULT(ObjsDefs -> Add (CComBSTR(cbBuffer), g_bstrNil, Objs.ppi()));

			if (pData -> pbdKTextLen > 0 && NULL != pData -> pbdKText)
				THROW_FAILED_HRESULT(Objs -> put_Name(CComBSTR(pData -> pbdKText)));

		// reales, vergebenes Handle zurückliefern
		LONG lHandle = 0;

			THROW_FAILED_HRESULT(Objs -> get_Handle ((INT_PTR *)&lHandle));
			if (lHandle != pData -> pbdCode) {
				TX_TRACE2("TRiAS: ModPbdDataIdent: Changed IdentHandle %lx -> %lx !", pData -> pbdCode, lHandle);
				pData -> pbdCode = lHandle;
				RC = WC_RETURN;
			}

		} else {
		// hier nur neuen KurzText (Namen) einstellen
			if (pData -> pbdKTextLen > 0 && NULL != pData -> pbdKText)
				THROW_FAILED_HRESULT(Objs -> put_Name (CComBSTR(pData -> pbdKText)));
		}
	
	// LangText (BeschreibungsInfo) einstellen
		if (pData -> pbdLTextLen > 0 && NULL != pData -> pbdLText) 
			THROW_FAILED_HRESULT(Objs -> put_Description (CComBSTR(pData -> pbdLText)));

	} COM_CATCH_RETURN(EC_FAIL);
	return RC;
}

ErrCode GeoDB::ModPBDDataMerkmal (PBDDATA *pData)
{
	TX_ASSERT(IsTRiASDBBased());
	return EC_OKAY;
}

ErrCode GeoDB::DelPBDDataIdent (PBDDATA *pData)
{
	TX_ASSERT(IsTRiASDBBased());
	COM_TRY {
	WTRiASDatabase DBase;

		THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));

	WTRiASObjectHandleMap Map; // (CLSID_TRiASObjectsHandleMap);
	WTRiASObjects Objs;

		if (FAILED(GetObjectsMap(Map.ppi())))
			return WC_NOTFOUND;

	// wiederauffinden des Objects-Objektes (selbiges muß existieren)
	LONG lCnt = 0;

		THROW_FAILED_HRESULT(Map -> GetObject(pData -> pbdCode, Objs.ppu()));
		THROW_FAILED_HRESULT(Objs  -> get_Count (&lCnt));
		if (lCnt != 0)
			return EC_FAIL;		// darf nur leere Objektklassen löschen

	// Objektmenge (Tabelle) soll gelöscht werden (DROP TABLE)
	WTRiASObjectsCollection ObjsDefs;

		THROW_FAILED_HRESULT(WTRiASAccessDatabase(DBase) -> get_ObjectsDefs (ObjsDefs.ppi()));
		THROW_FAILED_HRESULT(ObjsDefs -> Remove (CComVariant(Objs)));

	} COM_CATCH_RETURN(EC_FAIL);
	return EC_OKAY;
}

ErrCode GeoDB::DelPBDDataMerkmal (PBDDATA *pData)
{
	TX_ASSERT(IsTRiASDBBased());
	return EC_OKAY;
}

namespace {
	inline BOOL EnumIdentsCallback (
		BOOL (*pFcn)(long, BOOL, void *), long Id, BOOL fNotLast, void *pData) 
	{
		return ((ENUMNOKEYLONGCALLBACK)pFcn)(Id, fNotLast, pData);
	}
}

BOOL GeoDB::EnumPBDDataIdent (ENUMLONGKEYPROC pFcn, void *pData)
{
	TX_ASSERT(IsTRiASDBBased());

BOOL iRC = TRUE;		// wenn keine Idents vorhanden sind, dann weitermachen

	COM_TRY {
	WTRiASDatabase DBase;

		THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));

	// Objektmengen (Tabellen) enumerieren
	WTRiASObjectsCollection ObjsDefs;

		THROW_FAILED_HRESULT(WTRiASAccessDatabase(DBase) -> get_ObjectsDefs (ObjsDefs.ppi()));

	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(ObjsDefs -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) 
		{
			if (FAILED(v.ChangeType (VT_DISPATCH)))
				continue;

		WTRiASObjects Item (V_DISPATCH(&v));
		LONG lHandle = 0L;

			if (SUCCEEDED(Item -> get_Handle ((INT_PTR *)&lHandle))) {
				iRC = EnumIdentsCallback (pFcn, lHandle, TRUE, pData);
				if (!iRC) break;	// Enumeration abgebrochen
			}
		}

	} COM_CATCH_RETURN(FALSE);
	return iRC;
}

BOOL GeoDB::EnumPBDDataMerkmal (ENUMLONGKEYPROC pFcn, void *pData)
{
	TX_ASSERT(IsTRiASDBBased());
	TX_ASSERT(SUCCEEDED(E_NOTIMPL));
	return TRUE;
}

HRESULT GeoDB::GetObjectsDef (
	ULONG ulIdent, VARIANT vItem, VARIANT_BOOL fCreate, BSTR bstrType, 
	ITRiASObjects **ppIObjs)
{
	TX_ASSERT(IsTRiASDBBased());
	if (NULL == ppIObjs)
		return E_POINTER;

	COM_TRY {
	WTRiASDatabase DBase;

		THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));

	// aus Database-Tabelle entfernen
	WTRiASObjectHandleMap Map; // (CLSID_TRiASObjectsHandleMap);
	WTRiASObjects Objs;

		if (FAILED(GetObjectsMap(Map.ppi())))
			return WC_NOTFOUND;
	
	// wiederauffinden des Objects-Objektes
		if (0 == ulIdent || FAILED(Map -> GetObject(ulIdent, Objs.ppu()))) {
			if (VT_ERROR == V_VT(&vItem))	// nichts gefunden
				return HRESULT_FROM_ERRCODE(WC_NOTFOUND);

			THROW_FAILED_HRESULT(WTRiASAccessDatabase(DBase) -> get_ObjectsDef (vItem, fCreate, bstrType, Objs.ppi()));
			if (0 != ulIdent)
				THROW_FAILED_HRESULT(Objs -> put_Handle (ulIdent));
		}
		*ppIObjs = Objs.detach();

	} COM_CATCH;
	return S_OK;
}

namespace {
	inline BOOL EnumFeatsCallback (
		BOOL (*pFcn)(long, BOOL, void *), INT_PTR lMCode, BOOL fNotLast, void *pData) 
	{
		return ((ENUMNOKEYLONGCALLBACK)pFcn)(lMCode, fNotLast, pData);
	}
}

BOOL GeoDB::EnumAllFeatures (ENUMNOKEYLONGPROC pFcn, void *pData)
{
	TX_ASSERT(IsTRiASDBBased());
	COM_TRY {
	WTRiASDatabase DBase;

		THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));

	// alle Objektklassen enumerieren
	WTRiASObjectsCollection ObjsDef;

		THROW_FAILED_HRESULT(WTRiASAccessDatabase(DBase) -> get_ObjectsDefs (ObjsDef.ppi()));

	WEnumVARIANT Enum;
	CComVariant v;
	BOOL iRC = TRUE;
	set<INT_PTR> setIdents;

		THROW_FAILED_HRESULT(ObjsDef -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); iRC && S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) 
		{
			if (FAILED(v.ChangeType (VT_DISPATCH)))
				continue;

		// alle Attribute dieser Objektklasse enumerieren
		WTRiASObjects Objs (V_DISPATCH(&v));
		WTRiASFeatures Feats;

			THROW_FAILED_HRESULT(Objs -> get_Features (Feats.ppi()));

		WEnumVARIANT EnumFeats;
		CComVariant vFeat;

			THROW_FAILED_HRESULT(Feats -> _NewEnum (EnumFeats.ppu()));
			for (EnumFeats -> Reset(); S_OK == EnumFeats -> Next (1, CLEARED(&vFeat), NULL); /**/) 
			{
				if (FAILED(v.ChangeType (VT_DISPATCH)))
					continue;

			WTRiASFeature Item (V_DISPATCH(&vFeat));
			INT_PTR lHandle = 0L;

				if (SUCCEEDED(Item -> get_Handle (&lHandle))) {
				set<INT_PTR>::iterator it = setIdents.find (lHandle);

					if (it == setIdents.end()) {
					// erstes Vorkommen
						setIdents.insert(lHandle);
						iRC = EnumFeatsCallback (pFcn, lHandle, TRUE, pData);
						if (!iRC) break;	// Enumeration abgebrochen
					}
				}
			}
		}
	} COM_CATCH_RETURN(FALSE);
	return TRUE;
}

namespace {
	inline BOOL EnumFeatsCallbackEx (
		BOOL (*pFcn)(long, DWORD, void *), INT_PTR lMCode, DWORD eData, void *pData) 
	{
		return ((ENUMNOKEYLONGEXCALLBACK)pFcn)(lMCode, eData, pData);
	}
}

BOOL GeoDB::EnumAllFeaturesEx (
	ENUMNOKEYLONGEXPROC pFcn, FEATURETYPE rgTypeToEnum, void *pData, bool fListAllClasses)
{
	TX_ASSERT(IsTRiASDBBased());

BOOL iRC = TRUE;

	COM_TRY {
	WTRiASDatabase DBase;

		THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));

	// alle Objektklassen enumerieren
	WTRiASObjectsCollection ObjsDef;

		THROW_FAILED_HRESULT(WTRiASAccessDatabase(DBase) -> get_ObjectsDefs (ObjsDef.ppi()));

	WEnumVARIANT Enum;
	CComVariant v;
	set<HFEATURE, less<HFEATURE> > setMCodes;

		THROW_FAILED_HRESULT(ObjsDef -> _NewEnum (Enum.ppu()));

		if (NULL == pData && fListAllClasses) {
		// Wenn keine Daten gegeben sind und das Flag fListAllClasses, dann für TRiAS-Datenquellen
		// jeden MCode nur einmal enumerieren und als Daten alle zugehörigen Identifikatoren 
		// durchreichen (als vector<HOBJECTS> *).

			if (IsTRiASDataSource()) {
			// alle Idents dieser Datenquelle aufsammeln
			WTRiASObjects Objs;
			vector<HOBJECTS> Idents;

				for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
					if (FAILED(v.ChangeType (VT_DISPATCH)))
						continue;

				// alle Attribute dieser Objektklasse enumerieren
				HOBJECTS hObjs = NULL;

					Objs = V_DISPATCH(&v);
					THROW_FAILED_HRESULT(Objs -> get_Handle (&hObjs));
					Idents.push_back(hObjs);
				}

			// jetzt genau einmal enumerieren (mit der letzten Objektklasse)
				if (Idents.size() > 0) 
					iRC = EnumAllFeaturesObjsEx (Objs, pFcn, rgTypeToEnum, &Idents, &setMCodes);
			}
			else {
			// einfach jeden Ident einzeln behandeln
			vector<HOBJECTS> Idents(1);

				for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
					if (FAILED(v.ChangeType (VT_DISPATCH)))
						continue;

				// alle Attribute dieser Objektklasse enumerieren
				WTRiASObjects Objs (V_DISPATCH(&v));
				HOBJECTS hObjs = NULL;

					THROW_FAILED_HRESULT(Objs -> get_Handle (&hObjs));
					Idents[0] = hObjs;

					iRC = EnumAllFeaturesObjsEx (Objs, pFcn, rgTypeToEnum, &Idents, &setMCodes);
					if (!iRC) break;
				}
			}

		}
		else {
		// 'normale' Enumeration
			for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) 
			{
				if (FAILED(v.ChangeType (VT_DISPATCH)))
					continue;

			// alle Attribute dieser Objektklasse enumerieren
			WTRiASObjects Objs (V_DISPATCH(&v));

				iRC = EnumAllFeaturesObjsEx (Objs, pFcn, rgTypeToEnum, pData, &setMCodes);
				if (!iRC) break;
			}
		}

	} COM_CATCH_RETURN(FALSE);
	return iRC;
}

BOOL GeoDB::EnumAllFeaturesObjsEx (
	ITRiASObjects *pIObjs, ENUMNOKEYLONGEXPROC pFcn, FEATURETYPE rgTypeToEnum, void *pData,
	set<HFEATURE, less<HFEATURE> > *pMCodes)
{
BOOL iRC = TRUE;

	COM_TRY {
	WTRiASFeatures Feats;
	bool fHacked = false;

		THROW_FAILED_HRESULT(pIObjs -> get_Features (Feats.ppi()));
		if (NULL == pData) {
		// HACK!: wenn keine Daten übergeben werden sollen (NULL == pData), dann als
		// Daten die derzeit behandelte Objektklasse liefern
			THROW_FAILED_HRESULT(pIObjs -> get_Handle (reinterpret_cast<INT_PTR *>(&pData)));
			fHacked = true;
		}

	bool fEnumAll = (rgTypeToEnum & FEATURETYPE_AllFeatures) ? true : false;
	bool fEnumSystem = (rgTypeToEnum & FEATURETYPE_System) ? true : false;
	bool fEnumDefinitionOnly = (rgTypeToEnum & FEATURETYPE_DefinitionOnly) ? true : false;
	FEATURETYPE rgToEnum = FEATURETYPE(rgTypeToEnum & FEATURETYPE_TypeMask);

	WEnumVARIANT EnumFeats;
	CComVariant vFeat;

		THROW_FAILED_HRESULT(Feats -> _NewEnum (EnumFeats.ppu()));
		for (EnumFeats -> Reset(); S_OK == EnumFeats -> Next (1, CLEARED(&vFeat), NULL); /**/) 
		{
			TX_ASSERT(SUCCEEDED(FAILED(vFeat.ChangeType (VT_DISPATCH))));

		WTRiASFeature Item (V_DISPATCH(&vFeat));
		FEATURETYPE rgType = FEATURETYPE_Unknown;

			THROW_FAILED_HRESULT(Item -> get_Type (&rgType));
			if (!fEnumAll && (rgToEnum != FEATURETYPE(rgType & FEATURETYPE_TypeMask)))
				continue;
			if (!fEnumSystem && (rgType & FEATURETYPE_System))
				continue;
			if (!fEnumDefinitionOnly && (rgType & FEATURETYPE_DefinitionOnly))
				continue;		// keine Objekte mit dieser Objekteigenschaft vorhanden

		INT_PTR lHandle = 0L;

			if (SUCCEEDED(Item -> get_Handle (&lHandle))) {
				if (!fHacked && NULL != pMCodes) {
				set<INT_PTR>::iterator it = pMCodes -> find (lHandle);

					if (it != pMCodes -> end())
						continue;		// den haben wir schon
					pMCodes -> insert (lHandle);
				}

			// bei Anwendung des o.g. Hacks werden _alle_ MCodes enumeriert, egal, ob sie für
			// andere Objs schon da waren oder nicht (wichtig bei der Instantiierung der 
			// Objekteigenschaften für TRiAS-Datenbanken)
				iRC = EnumFeatsCallbackEx (pFcn, lHandle, DWORD(rgType), pData);
				if (!iRC) break;	// Enumeration abgebrochen
			}
		}
	} COM_CATCH_RETURN(FALSE);
	return iRC;
}

///////////////////////////////////////////////////////////////////////////////
// ein Objekt aus der Datenbank herauslöschen
HRESULT GeoDB::DeleteObject (INT_PTR lONr)
{
	TX_ASSERT(IsTRiASDBBased());

WTRiASObjects Objs;
INT_PTR lIdent = DEX_GetObjIdent(lONr);

	RETURN_FAILED_HRESULT(GetObjectsDef (lIdent, vtMissing, VARIANT_FALSE, CComBSTR(g_cbNil), Objs.ppi()));
	return Objs -> Delete (CComVariant(lONr));
}

///////////////////////////////////////////////////////////////////////////////
// Irgend was neu einlesen
HRESULT GeoDB::ForceReLoad (RELOADDATABASE rgWhat)
{
	TX_ASSERT(IsTRiASDBBased());

WTRiASDatabase DBase;

	RETURN_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));
	RETURN_FAILED_HRESULT(DBase -> ReLoad (rgWhat));

	return S_OK;
}

HRESULT GeoDB::GetFeature (INT_PTR lIdent, LPCSTR pcName, ITRiASFeature **ppIFeat)
{
WTRiASObjects Objs;
HRESULT hr = GetObjectsDef (lIdent, vtMissing, VARIANT_FALSE, CComBSTR(g_cbNil), Objs.ppi());

	if (FAILED(hr))
		return hr;
			
	return Objs -> get_Feature (CComVariant(pcName), VARIANT_FALSE, CComBSTR(g_cbNil), ppIFeat);
}

///////////////////////////////////////////////////////////////////////////////
// Versuchen das zu einem Merkmalscode dieser GeoDB gehörende Handle zu finden
INT_PTR GeoDB::MapMCodeToHandle (INT_PTR lMCode, BOOL fCreate, BOOL *pfCreated, INT_PTR lIdent)
{
	if (pfCreated)
		*pfCreated = FALSE;

	COM_TRY {
	// wenn gegeben, dann evtl. Objektklasse nach gesuchtem Handle befragen
	INT_PTR lHandle = NULL;

		if (NULL != lIdent) {
		WTRiASObjectHandleMap ClsMap; // (CLSID_TRiASObjectsHandleMap);
		WTRiASObjects Objs;

			THROW_FAILED_HRESULT(GetObjectsMap(ClsMap.ppi()));
			if (SUCCEEDED(ClsMap -> GetObject (lIdent, Objs.ppu()))) {
			WTRiASFeatures Feats;

				if (SUCCEEDED(Objs -> get_Features (Feats.ppi()))) {
				WTRiASSimpleFeatures SimpleFeats;
				WTRiASFeature Feat;

					if (SUCCEEDED(Feats -> QueryInterface (SimpleFeats.ppi())) &&
						SUCCEEDED(SimpleFeats -> get_Feature (lMCode, Feat.ppi())))
					{
						THROW_FAILED_HRESULT(Feat -> get_Handle (&lHandle));
						return lHandle;
					}
				}
			}
		}

	// nur TRiAS-GeoDB's können ohne Objektklasse Merkmale erzeugen
		if (fCreate && (0 != lIdent || IsTRiASDataSource())) {
		// entweder nicht gefunden oder Ident nicht gegeben
		WTRiASDatabase DBase;

			THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));
			THROW_FAILED_HRESULT(DBase -> ReLoad (RELOADDATABASE_EnsureFeatures));	// Features sicherstellen

		WTRiASObjectHandleMap Map (GetPropertyFrom (DBase, g_cbFeatureMap, (IDispatch *)NULL), false);
		WTRiASFeature Feat;

			if (Map.IsValid() && SUCCEEDED(Map -> GetObjectEx (lMCode, OBJECTMAPMODE_GetObjectFromNativeHandle, Feat.ppu()))) 
			{
				THROW_FAILED_HRESULT(Feat -> get_Handle (&lHandle));
				return lHandle;
			}

			THROW_FAILED_HRESULT(CreateFeature (lIdent, CComVariant(lMCode), &lHandle, NULL, DBase));
			lMCode = lHandle;
			if (pfCreated)
				*pfCreated = TRUE;

		} 
		else if (!fCreate && IsTRiASDataSource()) {
		// TRiAS Datenquellen haben immer etwas besonderes
		WTRiASDatabase DBase;

			THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));

		WTRiASObjectHandleMap Map (GetPropertyFrom (DBase, g_cbFeatureMap, (IDispatch *)NULL), false);
		WTRiASFeature Feat;

			if (Map.IsValid() && SUCCEEDED(Map -> GetObjectEx (lMCode, OBJECTMAPMODE_GetObjectFromNativeHandle, Feat.ppu()))) 
			{
				THROW_FAILED_HRESULT(Feat -> get_Handle (&lHandle));
				return lHandle;
			}

		} else
			lMCode = 0L;	// wenn nichts gefunden, dann NULL liefern

	} COM_CATCH_IGNORE;
	return lMCode;
}

HRESULT GeoDB::CreateFeature (
	INT_PTR lIdent, VARIANT vMCodeOrName, INT_PTR *plMCode, ITRiASFeature **ppIFeat, ITRiASDatabase *pIDB)
{
	COM_TRY {
	// wenn Database nicht gegeben ist, dann eben lokale verwenden
	WTRiASDatabase DBase (pIDB);

		if (!DBase.IsValid())
			THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));

	// neues Handle erzeugen lassen
	WTRiASFeatures Feats (GetPropertyFrom (DBase, TEXT("SimpleFeatures"), (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab
	WTRiASFeature Feat;

		TX_ASSERT(Feats.IsValid() || 0 != lIdent);
		if (!Feats.IsValid()) {
			TX_ASSERT(!IsTRiASDataSource());

		WTRiASObjectHandleMap ClsMap;
		WTRiASObjects Objs;

			THROW_FAILED_HRESULT(GetObjectsMap(ClsMap.ppi()));
			THROW_FAILED_HRESULT(ClsMap -> GetObject (lIdent, Objs.ppu()));
			THROW_FAILED_HRESULT(Objs -> get_Feature (vMCodeOrName, VARIANT_TRUE, CComBSTR(g_cbNil), Feat.ppi()));
		} 
		else {
		FEATURETYPE rgType = FEATURETYPE(DATATYPE_FROM_VT(VT_BSTR) | MPObjectFeature);

			if (IsTRiASDataSource())
				rgType = (FEATURETYPE)(rgType | FEATURETYPE_IsGlobal);

			THROW_FAILED_HRESULT(Feats -> Add (vMCodeOrName, CComBSTR(g_cbNil), rgType, Feat.ppi()));
		}
		THROW_FAILED_HRESULT(Feat -> get_Handle (plMCode));
		if (NULL != ppIFeat)
			*ppIFeat = Feat.detach();

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Versuchen das zu einem Handle ein MCode dieser GeoDB zu finden

// Finden eines besonderen Parents in der Objekthierarchie über einem gegebenen
// Objekt
template<class T>
inline HRESULT FindSpecificParent (T ParentIn, REFIID riid, void **ppIObj)
{
__Interface<IDispatch> Parent(ParentIn);

	while (Parent.IsValid()) {
		if (SUCCEEDED(Parent -> QueryInterface(riid, ppIObj)))
			return S_OK;		// gesuchtes Objekt gefunden

	// eine Etage weiter hoch
	__Interface<ITRiASBase> ParT(Parent);

		RETURN_FAILED_HRESULT(ParT -> get_Parent (Parent.ppi()));
	}
	return E_UNEXPECTED;
}

INT_PTR GeoDB::MapHandleToMCode (INT_PTR lHandle)
{
INT_PTR lMCode = lHandle;

	COM_TRY {
	WTRiASObjectHandleMap Map; // (CLSID_TRiASObjectsHandleMap);
	WTRiASFeature Feat;

		THROW_FAILED_HRESULT(GetFeatureMap(Map.ppi()));
		if (SUCCEEDED(Map -> GetObject (lHandle, Feat.ppu()))) {
		WTRiASSimpleFeature SimpleFeat;

			if (SUCCEEDED(Feat -> QueryInterface (SimpleFeat.ppi()))) {
#if defined(_DEBUG)
			// Datenquellen müssen übereinstimmen
			INT_PTR hPrFeat = NULL;
			WDispatch Parent;

				THROW_FAILED_HRESULT(FindSpecificParent (Feat, IID_ITRiASDatabase, Parent.ppv()));
				THROW_FAILED_HRESULT(WTRiASDatabase(Parent) -> get_Handle (&hPrFeat));
				TX_ASSERT(DBDesc() == reinterpret_cast<HPROJECT>(hPrFeat));
#endif // defined(_DEBUG)

			// nur wenn es aus einer TRiAS-datenquelle kommt
				THROW_FAILED_HRESULT(SimpleFeat -> get_LocalHandle (&lMCode));
			}
		}
	} COM_CATCH_IGNORE;
	return lMCode;
}

// Abfrage, ob Objektklassen/Objekteigenschaften erzeugt bzw. gelöscht werden dürfen
BOOL GeoDB::GetSchemaUpdatable()
{
	TX_ASSERT(IsTRiASDBBased());

CComBool fUpdatable;

	if (FAILED(m_Conn -> get_SchemaUpdatable (&fUpdatable))) 
		return FALSE;		// sicherheitshalber nicht modifizierbar melden

	return fUpdatable;	
}
