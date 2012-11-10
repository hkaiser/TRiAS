// @doc
// @module DBProject.cpp | Routinen der Klasse <c DatenBasisObjekt>, welche 
// über alle geöffneten Connections arbeiten

#include "TriasPre.hxx"

#include <dbmsg.hmc>
#include <HeaderEntry.h>

#include "Strings.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASProperty);

///////////////////////////////////////////////////////////////////////////////
// Alle Identifikatoren aller GeoDB's enumerieren
BOOL DatenBasisObjekt::EnumIdents (ENUMNOKEYLONGPROC pFcn, void *pData)
{
	TX_ASSERT(NULL != m_pGeoDBs);

CRing r (*m_pGeoDBs);

	for (r.First(); r.Valid(); r.Next()) {
	GeoDBLock l(r);

		TX_ASSERT(NULL != (GeoDB *)l);
		if (l -> isOpened() && !l -> EnumIdents (pFcn, pData))
			return FALSE;
	}
	return TRUE;
}

BOOL DatenBasisObjekt::EnumIdentsEx (ENUMNOKEYLONGEXPROC pFcn, void *pData, DWORD dwData)
{
	TX_ASSERT(NULL != m_pGeoDBs);

CRing r (*m_pGeoDBs);

	for (r.First(); r.Valid(); r.Next()) {
	GeoDBLock l(r);

		TX_ASSERT(NULL != (GeoDB *)l);
		if (l -> isOpened() && !l -> EnumIdentsEx (pFcn, pData, dwData))
			return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Berechnet den umschließenden Container aller Connections
ObjContainer DatenBasisObjekt::DBCont (bool fReRead)
{
ObjContainer OC (MAXKOORD, 0, MAXKOORD, 0);
CRing r (*m_pGeoDBs);
bool fFound = false;

	for (r.First(); r.Valid(); r.Next()) {
	GeoDBLock l(r);

		TX_ASSERT(NULL != (GeoDB *)l);
		if (l -> isOpened()) {
			OC += l -> DBCont (fReRead);
			fFound = true;
		}
	}
	if (!fFound) {
		OC = ObjContainer(0, 0, 0, 0);
		Transformation::SetValid (false);		// T-Parameter sind jetzt gültig
	}
	return OC;
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
#if defined(_USE_LEGACY_CODE)
	if (NULL == (IDispatch *)m_Prj) {
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
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(NULL != (IDispatch *)m_Prj);
		USES_CONVERSION;

		if (NULL == hPr) {
		// ProjektHeader 
			try {
			WTRiASProperty Prop;
			CComBSTR vProp (PrepareKey(pHE -> hdrKey));
			CComVariant vVal;

				THROW_FAILED_HRESULT(m_Prj -> get_Property (vProp, Prop.ppi()));
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
		int iItem = m_pGeoDBs -> FFindItem (hPr);

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
#if defined(_USE_LEGACY_CODE)
	if (NULL == (IDispatch *)m_Prj) {
	CActDB ActDB (DB());
	CDBHeader HE (DB().DBDesc(), pHE -> hdrKey);
	long lFlags = 0;

		if (sizeof(GEODBHDRENTRYEX) == pHE -> dwSize)
			lFlags = ((GEODBHDRENTRYEX *)pHE) -> dwFlags;

	HRESULT hr = HE.PutHeaderEntry (pHE -> lphdrText, strlen(pHE -> lphdrText), lFlags);

		DEX_SetDirtyGeoDB(true);
		return SUCCEEDED(hr) ? EC_OKAY : ERRCODE_FROM_HRESULT(hr);
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(NULL != (IDispatch *)m_Prj);

		if (NULL == hPr) {
		// ProjektHeader 
			try {
			WTRiASProperty Prop;
			CComBSTR vProp (PrepareKey(pHE -> hdrKey));
			HRESULT hr = m_Prj -> get_Property (vProp, Prop.ppi());

				if (FAILED(hr)) {
					if (TRIASDB_E_UNKNOWN_PROPERTY == hr) {
						THROW_FAILED_HRESULT(m_Prj -> CreateProperty (vProp, Prop.ppi()));
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
#if defined(_USE_LEGACY_CODE)
	if (NULL == (IDispatch *)m_Prj) {
	CActDB ActDB (DB());
	CDBHeader HE (DB().DBDesc(), pHE -> hdrKey);
	HRESULT hr = HE.DeleteHeaderEntry();

		DEX_SetDirtyGeoDB(true);
		return SUCCEEDED(hr) ? EC_OKAY : ERRCODE_FROM_HRESULT(hr);
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(NULL != (IDispatch *)m_Prj);

		if (NULL == hPr) {
		// ProjektHeader 
			try {
			WTRiASProperty Prop;
			CComBSTR vProp (PrepareKey(pHE -> hdrKey));
			HRESULT hr = m_Prj -> get_Property (vProp, Prop.ppi());

				if (SUCCEEDED(hr)) {
					THROW_FAILED_HRESULT(m_Prj -> RemoveProperty (vProp));
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
#if defined(_USE_LEGACY_CODE)
	if (NULL == (IDispatch *)m_Prj) {
	CActDB ActDB (DB());

		return DB().EnumHdrData ((ENUMNOKEYPROC)pFcn, pData);
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(NULL != (IDispatch *)m_Prj);
		USES_CONVERSION;
		
		if (NULL == hPr) {
		// ProjektHeader 
			try {
			WTRiASProperties Props;
			WTRiASProperty Prop;

				THROW_FAILED_HRESULT(m_Prj -> get_Properties (Props.ppi()));

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
