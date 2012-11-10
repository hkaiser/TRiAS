// @doc
// @module DBProject.cpp | Routinen der Klasse <c DatenBasisObjekt>, welche 
// über alle geöffneten Connections arbeiten

#include "TriasPre.hxx"

#include <dbmsg.hmc>
#include <HeaderEntry.h>

#include <Com/PropertyHelper.h>
#include <Com/ComBool.h>

#include "Strings.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

using namespace trias_nativeheader;

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASProperty);
DefineSmartInterface(TRiASProperties);
DefineSmartInterface(TRiASObjectsCollection);
DefineSmartInterface(EnumVARIANT);

///////////////////////////////////////////////////////////////////////////////
// Alle Identifikatoren aller GeoDB's enumerieren
namespace {
	inline BOOL EnumIdentsCallback (
		BOOL (*pFcn)(long, BOOL, void *), INT_PTR Id, BOOL iNext, void *pData) 
	{
		return ((ENUMNOKEYLONGCALLBACK)pFcn)(Id, iNext, pData);
	}
	inline BOOL EnumIdentsCallbackEx (
		BOOL (*pFcn)(long, DWORD, void *), INT_PTR Id, DWORD eData, void *pData) 
	{
		return ((ENUMNOKEYLONGEXCALLBACK)pFcn)(Id, eData, pData);
	}

	int BitsFromOBJECTTYPE (OBJECTTYPE rgType)
	{
	int iBits = 0;

		if (OBJECTTYPE_Point & rgType)
			iBits |= OTPunkt;
		if (OBJECTTYPE_Line & rgType)
			iBits |= OTLinie;
		if (OBJECTTYPE_Area & rgType)
			iBits |= OTFlaeche;
		if (OBJECTTYPE_Text & rgType)
			iBits |= OTText;

		return iBits;
	}
}

BOOL DatenBasisObjekt::EnumIdents (HPROJECT hPr, ENUMNOKEYLONGPROC pFcn, void *pData)
{
	TX_ASSERT(NULL != m_pGeoDBs);

// Projektbezogene Objektklassen durchgehen (z.B. Zuordnungsobjektklassen)
BOOL iRC = TRUE;

	COM_TRY {
	WTRiASObjectsCollection ObjsColl;

		THROW_FAILED_HRESULT(m_Prj -> get_ObjectsDefs (ObjsColl.ppi()));

	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(ObjsColl -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
			if (FAILED(v.ChangeType (VT_DISPATCH)))
				continue;

		WTRiASObjects Objs (V_DISPATCH(&v));
		INT_PTR lHandle = NULL;

			if (SUCCEEDED(Objs -> get_Handle (&lHandle))) {
				iRC = EnumIdentsCallback (pFcn, lHandle, TRUE, pData);
				if (!iRC) break;	// Enumeration abgebrochen
			}
		}

	} COM_CATCH_RETURN(FALSE);
	if (!iRC)
		return FALSE;

	if (HACTPROJECT == hPr)
		return S_OK;			// nur projektbezogene Objektklassen liefern

// alle Datenquellen durchgehen
CRing r (*m_pGeoDBs);

	for (r.First(); r.Valid(); r.Next()) {
	GeoDBLock l(r);

		TX_ASSERT(NULL != (GeoDB *)l);
		if (l -> isOpened()) {
		// wenn es nicht die geforderte Datenquelle ist, dann übergehen
			if (HACTCONNECTION != hPr && l -> DBDesc() != hPr)
				continue;

		// jetzt enumerieren
			if (!l -> EnumIdents (pFcn, pData))
				return FALSE;
		}
	}
	return TRUE;
}

BOOL DatenBasisObjekt::EnumIdentsEx (HPROJECT hPr, ENUMNOKEYLONGEXPROC pFcn, void *pData, DWORD dwData)
{
	TX_ASSERT(NULL != m_pGeoDBs);

// Projektbezogene Objektklassen durchgehen (z.B. Zuordnungsobjektklassen)
BOOL iRC = TRUE;

	COM_TRY {
	WTRiASObjectsCollection ObjsColl;

		THROW_FAILED_HRESULT(m_Prj -> get_ObjectsDefs (ObjsColl.ppi()));

	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(ObjsColl -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) 
		{
			if (FAILED(v.ChangeType (VT_DISPATCH)))
				continue;

		WTRiASObjects Objs (V_DISPATCH(&v));
		INT_PTR lHandle = 0L;
		OBJECTTYPE rgTypes = OBJECTTYPE_Unknown;

			THROW_FAILED_HRESULT(Objs -> get_Types (&rgTypes));

			if (SUCCEEDED(Objs -> get_Handle (&lHandle))) {
				iRC = EnumIdentsCallbackEx (pFcn, lHandle, DWORD(rgTypes), pData);
				if (!iRC) break;	// Enumeration abgebrochen
			}
		}

	} COM_CATCH_RETURN(FALSE);
	if (!iRC)
		return FALSE;

	if (HACTPROJECT == hPr)
		return S_OK;			// nur projektbezogene Objektklassen liefern

// alle Datenquellen durchgehen
CRing r (*m_pGeoDBs);

	for (r.First(); r.Valid(); r.Next()) {
	GeoDBLock l(r);

		TX_ASSERT(NULL != (GeoDB *)l);
		if (l -> isOpened()) {
		// wenn es nicht die geforderte Datenquelle ist, dann übergehen
			if (HACTCONNECTION != hPr && l -> DBDesc() != hPr)
				continue;

		// jetzt enumerieren
			if (!l -> EnumIdentsEx (pFcn, pData, dwData))
				return FALSE;
		}
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// alle Objekte einer Objektmenge enumerieren
namespace {
	typedef BOOL (CALLBACK *ENUMIDENTOBJECTCALLBACK)(long, short, void *);
	inline BOOL EnumIdentObjectsCallback (
		BOOL (*pFcn)(long, BOOL, void *), long Key, short iOTyp, void *pData)
	{
		return ((ENUMIDENTOBJECTCALLBACK)pFcn)(Key, iOTyp, pData);
	}
	inline BOOL EnumIdentObjectsCallbackEx (
		BOOL (*pFcn)(long, DWORD, void *), long Key, DWORD iOTyp, void *pData)
	{
		return ((ENUMLONGKEYEXCALLBACK)pFcn)(Key, iOTyp, pData);
	}
}

BOOL DatenBasisObjekt::EnumIdentObjects (
	HPROJECT hPr, long lIdent, ENUMLONGKEYPROC pFcn, void *pData)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());

		return (LRESULT)DB().EnumIdentObjects (lIdent, pFcn, pData);
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	BOOL iRC = TRUE;

		hPr = GetIdentDBHandle(lIdent, hPr);
		if (HACTPROJECT == hPr) {
		// Heraussuchen der Objektmenge über ihr Handle
		WTRiASObjects Objs;

			THROW_FAILED_HRESULT(GetObjectsFromMap (lIdent, Objs));

		// enumerieren aller Objekte dieser Objektmenge
		WEnumVARIANT Enum;
		CComVariant v;

			THROW_FAILED_HRESULT(Objs -> _NewEnum (Enum.ppu()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
				if (FAILED(v.ChangeType (VT_UNKNOWN)))
					continue;

			WTRiASObject Obj (V_UNKNOWN(&v));
			INT_PTR lONr = 0L;
			OBJECTTYPE rgType = OBJECTTYPE_Unknown;

				THROW_FAILED_HRESULT(Obj -> get_Handle (&lONr));
				THROW_FAILED_HRESULT(Obj -> get_Type (&rgType));

				try {
					iRC = EnumIdentObjectsCallback (pFcn, lONr, BitsFromOBJECTTYPE(rgType), pData);
					if (!iRC) break;
				} catch (bool fResult) {
				// abbrechen der Enumeration
					iRC = fResult;
					break;
				}
			}
		} else {
		GeoDB &rDB = DB(hPr);

			if (!rDB.isOpened())
				return FALSE;
			return rDB.EnumIdentObjects(lIdent, pFcn, pData);
		}
		return iRC;
	}
}

BOOL DatenBasisObjekt::EnumIdentObjectsEx (
	HPROJECT hPr, long lIdent, ENUMLONGKEYEXPROC pFcn, void *pData, DWORD dwData)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());

		return DB().EnumIdentObjectsEx (lIdent, pFcn, pData, dwData);
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	BOOL iRC = TRUE;

		hPr = GetIdentDBHandle(lIdent, hPr);
		if (HACTPROJECT == hPr) {
		// Heraussuchen der Objektmenge über ihr Handle
		WTRiASObjects Objs;

			THROW_FAILED_HRESULT(GetObjectsFromMap (lIdent, Objs));

		// enumerieren aller Objekte dieser Objektmenge
		WEnumVARIANT Enum;
		CComVariant v;

			THROW_FAILED_HRESULT(Objs -> _NewEnum (Enum.ppu()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
				if (FAILED(v.ChangeType (VT_UNKNOWN)))
					continue;

			WTRiASObject Obj (V_UNKNOWN(&v));
			INT_PTR lONr = 0L;
			OBJECTTYPE rgType = OBJECTTYPE_Unknown;

				THROW_FAILED_HRESULT(Obj -> get_Handle (&lONr));
				THROW_FAILED_HRESULT(Obj -> get_Type (&rgType));

				try {
				DWORD dwToEnum = BitsFromOBJECTTYPE(rgType);

					if (dwData & dwToEnum) {	// nur enumerieren, wenn gefordert
						iRC = EnumIdentObjectsCallbackEx (pFcn, lONr, dwToEnum, pData);
						if (!iRC) break;
					}

				} catch (bool fResult) {
				// abbrechen der Enumeration
					iRC = fResult;
					break;
				}
			}

		} else {
		GeoDB &rDB = DB(hPr);

			if (!rDB.isOpened())
				return FALSE;
			return rDB.EnumIdentObjectsEx(lIdent, pFcn, pData, dwData);
		}
		return iRC;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Berechnet den umschließenden Container aller Connections
ObjContainer DatenBasisObjekt::DBCont (bool fReRead)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		return DB().DBCont (fReRead);
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		TX_ASSERT(NULL != pCT());

	CRing r (*m_pGeoDBs);
	bool fFound = false;
	bool fFoundCS = false;
	W_DGMRectangleGeometry rc;
	CCSRectangleGeometry Rect (MAXKOORD, MAXKOORD, -MAXKOORD, -MAXKOORD);
	CCSRectangleGeometry RectCS (MAXKOORD, MAXKOORD, -MAXKOORD, -MAXKOORD);

		for (r.First(); r.Valid(); r.Next()) {
		GeoDBLock l(r);

			TX_ASSERT(NULL != (GeoDB *)l);

			if (l -> isOpened()) {
			HRESULT hr = l -> DBCont (rc.ppi(), fReRead);

				if (S_OK == hr) {	// S_FALSE: no objects 
				// gemeinsames Rechteck berechnen (Vereinigung)
					Rect = Rect + CCSRectangleGeometry(rc);
					fFound = true;
				}
				else if (S_FALSE == hr) {
				// gemeinsames Rechteck berechnen (Vereinigung)
					RectCS = RectCS + CCSRectangleGeometry(rc);
					fFoundCS = true;
				}
			}
		}

	ObjContainer OC;
	double dXMin, dYMin, dXMax, dYMax;

		if (fFound) {
			THROW_FAILED_HRESULT(Rect.get_XMin (&dXMin));
			THROW_FAILED_HRESULT(Rect.get_YMin (&dYMin));
			THROW_FAILED_HRESULT(Rect.get_XMax (&dXMax));
			THROW_FAILED_HRESULT(Rect.get_YMax (&dYMax));
		}
		else if (fFoundCS) {
			THROW_FAILED_HRESULT(RectCS.get_XMin (&dXMin));
			THROW_FAILED_HRESULT(RectCS.get_YMin (&dYMin));
			THROW_FAILED_HRESULT(RectCS.get_XMax (&dXMax));
			THROW_FAILED_HRESULT(RectCS.get_YMax (&dYMax));
		}

		if (fFound || fFoundCS) {
		// über Workspace-CS wieder rückrechnen
#if defined(_KOORD_ISDOUBLE)
			OC.SetXMin(dXMin);
			OC.SetYMin(dYMin);
			OC.SetXMax(dXMax);
			OC.SetYMax(dYMax);
#else
		KoOrd x, y;

			pCT() -> Scale (dXMin, dYMin, &x, &y);
			OC.SetXMin(x);
			OC.SetYMin(y);

			pCT() -> Scale (dXMax, dYMax, &x, &y);
			OC.SetXMax(x);
			OC.SetYMax(y);
#endif // _KOORD_ISDOUBLE
		}

		if ((!fFound && !fFoundCS) || !OC.isValid()) {
			OC = ObjContainer(0, 0, 0, 0);
			Transformation::SetValid (false);		// T-Parameter sind jetzt nicht mehr gültig
		}
		return OC;
	}
}

///////////////////////////////////////////////////////////////////////////////
// ProjektHeader Lesen/Schreiben/Löschen
inline CComBSTR PrepareKey (LPSTR pKey)
{
char cbBuffer[HDRKEYLENGTH+1];

	strncpy (cbBuffer, pKey, HDRKEYLENGTH);
	cbBuffer[HDRKEYLENGTH] = '\0';

LPSTR pT = strrlchr (cbBuffer, *g_cbSpace);

	if (NULL != pT)
		 *pT = '\0';
	return CComBSTR(cbBuffer);
}

ErrCode DatenBasisObjekt::GetHeaderEntry (HPROJECT hPr, GEODBHDRENTRY *pHE)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());
	CDBHeader HE (DB().DBDesc(), pHE -> hdrKey);
	long lFlags = 0;
	HRESULT hr = HE.GetHeaderEntry (pHE -> lphdrText, pHE -> hdrTextLen, &lFlags);

		if (SUCCEEDED(hr)) {
			if (sizeof(GEODBHDRENTRYEX) == pHE -> dwSize) 
				((GEODBHDRENTRYEX *)pHE) -> dwFlags = lFlags;
			return EC_OKAY;
		} else {
			*pHE -> lphdrText = '\0';
			return WC_NOTFOUND;
		}
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		USES_CONVERSION;

		if (HACTPROJECT == hPr) {
		// ProjektHeader 
			try {
			WTRiASProperty Prop;
			CComBSTR vProp (PrepareKey(pHE -> hdrKey));
			CComVariant vVal;

				THROW_FAILED_HRESULT(WTRiASPropertyBase(m_Prj) -> get_Property (vProp, Prop.ppi()));
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

			} catch (_com_error &) {
				;
			}
		} else { 
		// Header einer Connection
		int iItem = m_pGeoDBs -> FFindItem (hPr);		// NULL == hPr liefert aktuelles Projekt

			if (-1 == iItem || !DB(hPr).isOpened())
				return EC_FAIL;
			return DB(hPr).GetHeaderEntry (pHE);
		}
	}

// nichts gefunden oder sonstiger Fehler
	*pHE -> lphdrText = '\0';
	return WC_NOTFOUND;
}

ErrCode DatenBasisObjekt::SetHeaderEntry (HPROJECT hPr, GEODBHDRENTRY *pHE)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());
	CDBHeader HE (DB().DBDesc(), pHE -> hdrKey);
	long lFlags = 0;

		if (sizeof(GEODBHDRENTRYEX) == pHE -> dwSize)
			lFlags = ((GEODBHDRENTRYEX *)pHE) -> dwFlags;

	HRESULT hr = HE.PutHeaderEntry (pHE -> lphdrText, strlen(pHE -> lphdrText), lFlags);

		DEX_SetDirtyGeoDB(true);
		return SUCCEEDED(hr) ? EC_OKAY : ERRCODE_FROM_HRESULT(hr);
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

		if (HACTPROJECT == hPr) {
		// ProjektHeader 
			try {
			WTRiASProperty Prop;
			CComBSTR vProp (PrepareKey(pHE -> hdrKey));
			WTRiASPropertyBase Propbase (m_Prj);
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

			} catch (_com_error &) {
				return EC_FAIL;
			}
		} else {
		// Header einer Connection
		int iItem = m_pGeoDBs -> FFindItem (hPr);

			if (-1 == iItem || !DB(hPr).isOpened())
				return EC_FAIL;
			return DB(hPr).SetHeaderEntry (pHE);
		}
	}
	return EC_OKAY;
}

ErrCode DatenBasisObjekt::DeleteHeaderEntry (HPROJECT hPr, GEODBHDRENTRY *pHE)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());
	CDBHeader HE (DB().DBDesc(), pHE -> hdrKey);
	HRESULT hr = HE.DeleteHeaderEntry();

		DEX_SetDirtyGeoDB(true);
		return SUCCEEDED(hr) ? EC_OKAY : ERRCODE_FROM_HRESULT(hr);
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		if (HACTPROJECT == hPr) {
		// ProjektHeader 
			try {
			WTRiASProperty Prop;
			CComBSTR vProp (PrepareKey(pHE -> hdrKey));
			WTRiASPropertyBase Propbase(m_Prj);
			HRESULT hr = Propbase -> get_Property (vProp, Prop.ppi());

				if (SUCCEEDED(hr)) {
					THROW_FAILED_HRESULT(DelPropertyBy (Propbase, vProp));
				} else
					return WC_NOTFOUND;

			} catch (_com_error &) {
				return EC_FAIL;
			}
		} else {
		// Header einer Connection
		int iItem = m_pGeoDBs -> FFindItem (hPr);

			if (-1 == iItem || !DB(hPr).isOpened())
				return EC_FAIL;
			return DB(hPr).DeleteHeaderEntry (pHE);
		}
	}
	return EC_OKAY;
}

BOOL DatenBasisObjekt::EnumHeaderData (HPROJECT hPr, ENUMNOKEYCALLBACK pFcn, void *pData)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());

		return DB().EnumHdrData ((ENUMNOKEYPROC)pFcn, pData);
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		USES_CONVERSION;
		
		if (HACTPROJECT == hPr) {
		// ProjektHeader 
			try {
			WTRiASProperties PropsT, Props;
			WTRiASProperty Prop;

				THROW_FAILED_HRESULT(WTRiASPropertyBase(m_Prj) -> get_Properties (PropsT.ppi()));
				THROW_FAILED_HRESULT(PropsT -> _Clone (Props.ppi()));

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

			} catch (_com_error &) {
				return FALSE;
			}
		} else {
		// Header einer Connection
		int iItem = m_pGeoDBs -> FFindItem (hPr);

			if (-1 == iItem || !DB(hPr).isOpened())
				return FALSE;

			return DB(hPr).EnumHeaderData (pFcn, pData);
		}
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Projekt wurde temporär erzeugt
bool DatenBasisObjekt::GetTempMode(void)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		return DB().GetTempMode();
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		try {
		VARIANT_BOOL fValue = VARIANT_FALSE;

			THROW_FAILED_HRESULT(m_Prj -> get_Temporary (&fValue));
			return fValue ? true : false;

		} catch (_com_error &) {
			;
		}
	}

// bei Fehler nicht temporär
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Projekt wurde modifiziert
bool DatenBasisObjekt::isDirty(void)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		return DB().isDirty();
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	CComBool fDirty;

		m_Prj -> get_Dirty(&fDirty);
		if (m_fLastDirty != bool(fDirty)) {
		// Dirtyzustand hat sich seid dem letzten mal geändert
			m_fLastDirty = fDirty;
			DEX_ReReadCaption();		// Caption neu erzeugen
		}
		return fDirty ? true : false;
	}

// bei Fehler nicht modifziert
	return false;
}

void DatenBasisObjekt::SetDirty (bool fFlag)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		DB().SetDirty(fFlag);
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		m_Prj -> put_Dirty(fFlag ? VARIANT_TRUE : VARIANT_FALSE);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Projekt wurde beim Öffnen kopiert
bool DatenBasisObjekt::isCopy(void)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		return DB().isCopy();
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		try {
		VARIANT_BOOL fValue = VARIANT_FALSE;

			THROW_FAILED_HRESULT(m_Prj -> get_OpenedAsCopy (&fValue));
			return fValue ? true : false;

		} catch (_com_error &) {
			;
		}
	}

// bei Fehler nicht modifziert
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert ProjektNamen
LPCSTR DatenBasisObjekt::GetDBName (LPSTR pBuffer)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		return strcpy (pBuffer, DB().GetDBName());
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		USES_CONVERSION;
		try {
		CComBSTR bstr;

			THROW_FAILED_HRESULT(m_Prj -> get_Name(CLEARED(&bstr)));
			strcpy (pBuffer, OLE2T(bstr));
			return pBuffer;

		} catch (_com_error &) {
			pBuffer[0] = '\0';
			return pBuffer;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Projekthandle liefern
HPROJECT DatenBasisObjekt::DBDesc()
{ 
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		return DB().DBDesc(); 
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		try {
		INT_PTR lHandle = NULL;

			THROW_FAILED_HRESULT(m_Prj -> get_Handle (&lHandle));
			return HPROJECT(lHandle);

		} catch (_com_error &) {
			;
		}
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// Ist Projekt RO ?
bool DatenBasisObjekt::GetROMode (void)
{ 
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		return DB().GetROMode() ? true : false; 
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		try {
		VARIANT_BOOL fValue = VARIANT_FALSE;

			THROW_FAILED_HRESULT(m_Prj -> get_Updatable (&fValue));
			return fValue ? false : true;

		} catch (_com_error &) {
			;
		}
	}

// im zweifelsfall ist's RO
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Das Projekt muß wissen, obs das aktive ist
void DatenBasisObjekt::SetActive (bool fFlag)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		m_fIsActiveProject = fFlag; 
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		m_Prj -> put_Activated (fFlag ? VARIANT_TRUE : VARIANT_FALSE);
	}
}

bool DatenBasisObjekt::IsActive (void)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		return m_fIsActiveProject; 
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		try {
		VARIANT_BOOL fValue = VARIANT_FALSE;

			THROW_FAILED_HRESULT(m_Prj -> get_Activated (&fValue));
			return fValue ? false : true;

		} catch (_com_error &) {
			;
		}
	}
	return false;
}

