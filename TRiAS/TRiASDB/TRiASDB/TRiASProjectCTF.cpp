// @doc
// @module TRiASProjectCTF.cpp | Implementation of <c CTRiASCTFProperty>
// @comm Dieses Objekt ist lediglich lokal verfügbar (kein Eintrag in der Registry)

#include "stdafx.h"

#include <comcat.h>
#include <Atl/Ciid.h>
#include <Com/PropertyHelper.h>

#include "TRiASDBGuids.h"
#include "Strings.h"
#include "Wrapper.h"
#include "GlobalVars.h"

#include "TRiASProjectCTF.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASCTFProperty, CTRiASCTFProperty)
RT_OBJECT_ENTRY2(CLSID_TRiASCTFConnection, CTRiASCTFProperty, Connection)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(EnumGUID);
DefineSmartInterface(CatInformation);
DefineSmartInterface(CoordTransformInit);

///////////////////////////////////////////////////////////////////////////////
// Component category: 079639C3-3123-101C-BB62-00AA0018497C	
const CATID CATID_TRiASCoordsystem = {0x079639C3L,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
const CLSID CLSID_CatSimpleCache = {0xEA68A685,0x5166,0x4E55,{0x90,0x62,0x0B,0x13,0x06,0x81,0x33,0x93}};

///////////////////////////////////////////////////////////////////////////////
// gecachete GUIDs
CTRiASCTFProperty::CEnumGuids CTRiASCTFProperty::s_GUIDs;

/////////////////////////////////////////////////////////////////////////////
// CTRiASCTFProperty

/////////////////////////////////////////////////////////////////////////////
// PropertySupport
// Callback-interface, welches für die Konkretheit der Properties zuständig ist

STDMETHODIMP CTRiASCTFProperty::PutValue (BSTR Name, VARIANT Value)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASCTFProperty::GetValue (BSTR Name, VARIANT *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASCTFProperty::GetValue");

	_ASSERTE(!wcscmp (Name, g_cbCTFService));	// muß "CTFService" sein
	if (wcscmp (Name, g_cbCTFService))
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASCTFProperty::GetValue");

	COM_TRY {
		THROW_FAILED_HRESULT(InitCTF());	// CTF garantiert laden

	WCoordTransform CTF (m_CTF);

		V_VT(pVal) = VT_DISPATCH;
		V_DISPATCH(pVal) = CTF.detach();

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASCTFProperty::PutType (BSTR Name, PROPERTY_TYPE Value)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASCTFProperty::GetType (BSTR Name, PROPERTY_TYPE *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASCTFProperty::GetType");

	_ASSERTE(!wcscmp (Name, g_cbCTFService));	// muß "CTFService" sein
	if (wcscmp (Name, g_cbCTFService))
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASCTFProperty::GetValue");

	*pVal = PROPERTY_TYPE(PROPERTY_TYPE_Dynamic|PROPERTY_TYPE_ReadOnly);
	return S_OK;
}

STDMETHODIMP CTRiASCTFProperty::PutValueAndType(BSTR Name, VARIANT Val, PROPERTY_TYPE Type)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASCTFProperty::GetValueAndType(BSTR Name, VARIANT * pVal, PROPERTY_TYPE * pType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal || NULL == pType)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASCTFProperty::GetType");

	_ASSERTE(!wcscmp (Name, g_cbCTFService));	// muß "CTFService" sein
	if (wcscmp (Name, g_cbCTFService))
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASCTFProperty::GetValue");

	COM_TRY {
		THROW_FAILED_HRESULT(InitCTF());	// CTF garantiert laden

	WCoordTransform CTF (m_CTF);

		V_VT(pVal) = VT_DISPATCH;
		V_DISPATCH(pVal) = CTF.detach();

		*pType = PROPERTY_TYPE(PROPERTY_TYPE_Dynamic|PROPERTY_TYPE_ReadOnly);

	} COM_CATCH;

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CTF neu einlesen
STDMETHODIMP CTRiASCTFProperty::Refresh(BSTR bstrName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return TerminateCTF();
}

HRESULT CTRiASCTFProperty::
CEnumGuids::InitGuids (bool fForce)
{
	if (!m_fIsInitialized || fForce) {
		Clear();	// alles bisherige vergessen

	// neu füllen
		COM_TRY {
		WEnumGUID EnumGuids;		// Enumerator der CTFService-Objekte
		WCatInformation CatInfo (CLSID_CatSimpleCache);	// throws hr
		GUID guid, guidImpl[1]; 

			guidImpl[0] = CATID_TRiASCoordsystem;
			THROW_FAILED_HRESULT(CatInfo -> EnumClassesOfCategories (1, guidImpl, 0, NULL, EnumGuids.ppi()));

		// alle Guids umkopieren
			for (EnumGuids -> Reset(); S_OK == EnumGuids -> Next (1, &guid, NULL); /**/)
				THROW_FAILED_HRESULT(AddItem (guid));

		} COM_CATCH;
		m_fIsInitialized = true;
	} 
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Helperroutinen
namespace {
	os_string GetOldName (CRegKey &rkey, CIID &rGuid)
	{
	CRegKey key;
	LONG lRegError = key.Open(rkey, os_string(rGuid).c_str(), KEY_READ);

		if (ERROR_SUCCESS == lRegError) 
			lRegError = key.Open(key, g_cbOldName, KEY_READ);

		_ASSERTE(ERROR_SUCCESS == lRegError);
			
	char cbBuffer[_MAX_PATH];
	DWORD dwCnt = sizeof(cbBuffer);

		if (ERROR_SUCCESS == key.QueryValue (cbBuffer, NULL, &dwCnt))
			return os_string(cbBuffer);

		return os_string(g_cbNil);
	}

	inline BOOL IsCorrectGuid (CRegKey &rkey, CIID &rGuid, LPCSTR pcGivenName)
	{
	os_string str (GetOldName (rkey, rGuid));

		return !stricmp (str.c_str(), pcGivenName);
	}
};

HRESULT CTRiASCTFProperty::InitCTF (void)
{
	if (m_CTF.IsValid()) 
		return S_OK;		// bereits erfolgreich initialisiert

	USES_CONVERSION;
	COM_TRY {
	char cbCTFName[_MAX_PATH];
	CComBSTR bstr (GetPropertyFrom (m_PropBase, g_cbCoordTransform, CComBSTR(g_cbDefault)));

		strcpy (cbCTFName, OLE2A(bstr));
		if (!stricmp (cbCTFName, g_cbDefault)) 
			m_fIsDefault = true;

	CComBSTR bstrGuid (GetPropertyFrom (m_PropBase, g_cbCoordTransGUID, g_bstrNil));
	CIID guid (bstrGuid);
	CRegKey key;

		if (ERROR_SUCCESS != key.Open (HKEY_CLASSES_ROOT, g_cbCLSID, KEY_READ))
			THROW_FAILED_HRESULT(E_UNEXPECTED);			// snh !

	// beim Testen nochmal GUID verifizieren
		if (!guid || !IsCorrectGuid (key, guid, cbCTFName) || FAILED(m_CTF.CreateInstance (guid))) {
		// nicht gegebener oder falscher Guid
		
		// CTFService's über CATID enumerieren, CTFService wiederfinden
			THROW_FAILED_HRESULT(s_GUIDs.InitGuids());

		GUID guidDef;
		bool fFoundDef = false;
		bool fFoundGuid = false;
		bool fNoCSS = true;

			for (s_GUIDs.Reset(); S_OK == s_GUIDs.Next (1, &guid, NULL); /**/)
			{
			CIID guidstr (guid);
			os_string strOldName (GetOldName (key, guidstr));

				if (strOldName.size() > 0) {
				// OldName ist gegeben
					fNoCSS = false;

				// Default gefunden
					if (!stricmp (strOldName.c_str(), g_cbDefault)) {
						fFoundDef = true;
						guidDef = guid;
					}

				// die gesuchte CTF gefunden
					if (!stricmp (strOldName.c_str(), cbCTFName)) {
						fFoundGuid = true;
						m_strCTF = strOldName;
						break;
					}
				}
			}

		// wenn nichts installiert wurde
			if (fNoCSS) {
				THROW_FAILED_HRESULT(REPORT_DBERROR(TRIASDB_E_CSS_NOT_INSTALLED));					// snh!
			}
			if (!fFoundGuid) {
				if (fFoundDef) {
				// Default verwenden, da benötigte nicht installiert ist
					guid = guidDef;
					m_strCTF = g_cbDefault;
				} else
					THROW_FAILED_HRESULT(REPORT_DBERROR(TRIASDB_E_CSS_NOT_INSTALLED));					// snh!
			}

		// jetzt den gefundenen Guid fürs nächste Mal im Header des Targets wegschreiben
		PROPERTY_TYPE rgType = PROPERTY_TYPE(PROPERTY_TYPE_System|PROPERTY_TYPE_ReadOnly);

			SetPropertyAndTypeBy (m_PropBase, g_cbCoordTransGUID, os_string(guid).c_str(), rgType, true);
		}

	// jetzt CoordTransform laden und initialisieren
		if (!m_CTF.IsValid())
		{
			THROW_FAILED_HRESULT(m_CTF.CreateInstance (guid));
		}

	WCoordTransformInit Init (m_CTF);

		THROW_FAILED_HRESULT(Init -> InitCoordTransform(m_PropBase));

	} COM_CATCH_OP(m_CTF.Assign(NULL));

	return S_OK;
}

HRESULT CTRiASCTFProperty::TerminateCTF(void)
{
	if (!m_CTF) 
		return S_OK;		// nothing to do

// noch Bescheid geben, daß jetzt alles freigegeben wird
	COM_TRY {
	WCoordTransformInit Init (m_CTF);		// throws hr (snh)

		THROW_FAILED_HRESULT(Init -> TermCoordTransform());
		m_CTF.Assign(NULL);
	} COM_CATCH;

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IObjectWithSite
STDMETHODIMP CTRiASCTFProperty::SetSite (IUnknown *pISite)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL != pISite)
		return pISite -> QueryInterface(m_PropBase.ppi());
	else {
		m_PropBase.Assign(NULL);
		return S_OK;
	}
}

STDMETHODIMP CTRiASCTFProperty::GetSite (REFIID riid, void **ppvSite)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_PropBase) 
		return REPORT_DBERROR(TRIASDB_E_PROPERTY_NOT_INITIALIZED);
	return m_PropBase -> QueryInterface (riid, ppvSite);
}

