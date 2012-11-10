///////////////////////////////////////////////////////////////////////////////
// @doc
// @module GeoDBCom.cpp | TRiASDB Spezifika in der Klasse <c GeoDB>

#include "trias02p.hxx"
#include "trias02.h"

#include <DbMsg.hmc>
#include <HdrEntry.hxx>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASDatabase);
DefineSmartInterface(TRiASProperty);

HRESULT GeoDB::AttachConnection (ITRiASConnection *pIConn, ITRiASConnection **ppIConn)
{
	try {
	// Database speichern
	WTRiASConnection Conn (m_Conn);

		m_Conn = pIConn;			// throws hr
		if (NULL != ppIConn)
			*ppIConn = Conn.detach();

		if (!m_Conn)		// Detach
			return S_OK;

	// als erstes das DBHandle++ abfragen
		{
		WTRiASDatabase DBase;

			THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));
			TX_ASSERT(sizeof(LONG) == sizeof(HPROJECT));
			THROW_FAILED_HRESULT(DBase -> get_Handle ((LONG *)&_DBDesc));

		VARIANT_BOOL fCopy = VARIANT_FALSE;

			THROW_FAILED_HRESULT(DBase -> get_OpenedAsCopy (&fCopy));
			SetCopy (fCopy ? TRUE : FALSE);
		}

	// alle notwendigen Properties der Database abfragen
		if (!ReReadHeader())
			return E_FAIL;

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
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
	TX_ASSERT(NULL != (IDispatch *)m_Conn);
	USES_CONVERSION;

	try {
	WTRiASDatabase DBase;

		THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));

	WTRiASProperty Prop;
	CComBSTR vProp (PrepareKey(pHE -> hdrKey));
	CComVariant vVal;

		THROW_FAILED_HRESULT(DBase -> get_Property (vProp, Prop.ppi()));
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

// nichts gefunden oder sonstiger Fehler
	*pHE -> lphdrText = '\0';
	return WC_NOTFOUND;
}

ErrCode GeoDB::SetHeaderEntry (GEODBHDRENTRY *pHE)
{
	TX_ASSERT(NULL != (IDispatch *)m_Conn);

	try {
	WTRiASDatabase DBase;

		THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));

	WTRiASProperty Prop;
	CComBSTR vProp (PrepareKey(pHE -> hdrKey));
	HRESULT hr = DBase -> get_Property (vProp, Prop.ppi());

		if (FAILED(hr)) {
			if (TRIASDB_E_UNKNOWN_PROPERTY == hr) {
				THROW_FAILED_HRESULT(DBase -> CreateProperty (vProp, Prop.ppi()));
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
	return EC_OKAY;
}

ErrCode GeoDB::DeleteHeaderEntry (GEODBHDRENTRY *pHE)
{
	TX_ASSERT(NULL != (IDispatch *)m_Conn);

	try {
	WTRiASDatabase DBase;

		THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));

	WTRiASProperty Prop;
	CComBSTR vProp (PrepareKey(pHE -> hdrKey));
	HRESULT hr = DBase -> get_Property (vProp, Prop.ppi());

		if (SUCCEEDED(hr)) {
			THROW_FAILED_HRESULT(DBase -> RemoveProperty (vProp));
		} else
			return WC_NOTFOUND;

	} catch (_com_error &) {
		return EC_FAIL;
	}
}

BOOL GeoDB::EnumHeaderData (ENUMNOKEYCALLBACK pFcn, void *pData)
{
	TX_ASSERT(NULL != (IDispatch *)m_Conn);
	USES_CONVERSION;
		
	try {
	WTRiASDatabase DBase;

		THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));

	WTRiASProperties Props;
	WTRiASProperty Prop;

		THROW_FAILED_HRESULT(DBase -> get_Properties (Props.ppi()));

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
	return TRUE;
}



