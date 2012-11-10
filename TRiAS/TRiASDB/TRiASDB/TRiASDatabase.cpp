// @doc
// @module TRiASDatabase.cpp | Implementation of the 
// <c CTRiASDatabase>, <c CTRiASCompatibleDatabase> and <c CTRiASDatabaseOnStg> classes

#include "stdafx.h"

#include <ospace/file/path.h>
#include <Atl/Ciid.h>
#include <Com/PropertyHelper.h>
#include <Com/MkHelper.h>

#include <zprotos.h>
#include <dbd.hxx>
#include <ErrInst.hxx>
#include <HeaderEntry.h>

#include "Strings.h"
#include "Wrapper.h"
#include "TRiASDBGuids.h"

#include "CSFactory.h"
#include "TRiASDatabase.h"
#include "TRiASProperty.h"

#include "TRiASSimpleObject.h"

using namespace trias_nativeheader;
using namespace trias_nativeobject;

///////////////////////////////////////////////////////////////////////////////
// Debughilfe für Storage
//#define _DEBUG_ISTORAGE
#if defined(_DEBUG) && defined(_DEBUG_ISTORAGE)
#include <stghelp.hxx>
#endif // defined(_DEBUG) && defined(_DEBUG_ISTORAGE)

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASDatabaseOnFile, CTRiASDatabaseOnFile)
RT_OBJECT_ENTRY(CLSID_TRiASDatabaseOnStg, CTRiASDatabaseOnStg)
RT_OBJECT_ENTRY(CLSID_TRiASCompatibleDatabase, CTRiASCompatibleDatabase)

///////////////////////////////////////////////////////////////////////////////
// {07963822-3123-101C-BB62-00AA0018497C}	
DEFINE_GUID(CLSID_TRiASMetaDocument, 0x07963822L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ParseStringPairs);
DefineSmartInterface(TRiASObjectHandleMap);		// WTRiASObjectHandleMap
DefineSmartInterface(TRiASCS);
DefineSmartInterface(TRiASCSTransform);
DefineSmartInterface(TRiASSimpleFeatures);

DefineSmartInterface(OleItemContainer);

/////////////////////////////////////////////////////////////////////////////
// spezielle RegistryFunktion
static _ATL_REGMAP_ENTRY s_regEntryMap[] = 
{
	{ L"MAINMODULE", NULL },		// REM_MAINMODULE
	{ L"TRIASNAME", NULL },
	{ NULL, NULL },					// EndeKennung
};

HRESULT WINAPI CTRiASDatabaseBase::UpdateRegistry (BOOL bRegister, UINT uiRes)
{
	USES_CONVERSION;
	
HMODULE hTRiAS = GetModuleHandle (NULL);
TCHAR szModule[_MAX_PATH];

	GetModuleFileName (hTRiAS, szModule, _MAX_PATH);

TCHAR szModuleShort[_MAX_PATH];
int cbShortName = GetShortPathName (szModule, szModuleShort, _MAX_PATH);
LPOLESTR pszModule;

	if (cbShortName == _MAX_PATH)
		return E_OUTOFMEMORY;
	pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? T2OLE(szModule) : T2OLE(szModuleShort);

	s_regEntryMap[0].szData = pszModule;
	s_regEntryMap[1].szData = A2OLE(g_cbTRiAS);

	return _Module.UpdateRegistryFromResource(uiRes, bRegister, s_regEntryMap);
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASDatabaseBase

STDMETHODIMP CTRiASDatabaseBase::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASDatabase,
		&IID_ITRiASAccessDatabase,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CTRiASDatabaseBase::FinalConstruct (void)
{
	return S_OK;
}

void CTRiASDatabaseBase::FinalRelease()
{
	_ASSERTE(NULL == m_hPr);		// DB ist noch offen (snh)
	if (NULL != m_hPr)
		Close();
}

/////////////////////////////////////////////////////////////////////////////
// Properties dieses Objektes
STDMETHODIMP CTRiASDatabaseBase::get_Application(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	TEST_OUT_PARAM(pVal);

	*pVal = m_Application;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::put_Application(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Application = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::get_Parent(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	TEST_OUT_PARAM(pVal);

	*pVal = m_Parent;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::put_Parent(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Parent = newVal;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// PropertySupport
// Callback-interface, welches für die Konkretheit der Properties zuständig ist

STDMETHODIMP CTRiASDatabaseBase::CreateProperty (BSTR Name, ITRiASProperty **Property)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(Property);

	COM_TRY {
	// Events vorher
	VARIANT_BOOL fVal = VARIANT_FALSE;
		
		THROW_FAILED_HRESULT(Fire_CreatingProperty (Name, &fVal)); 
		if (VARIANT_TRUE == fVal)
			return S_FALSE;
		THROW_FAILED_HRESULT(Fire_PropertyToCreate (Name));

	// eigentliche Aktion
	CComObject<CTRiASProperty> *pNew = NULL;

		THROW_FAILED_HRESULT(CComObject<CTRiASProperty>::CreateInstance (&pNew));

	WTRiASProperty Prop (pNew);		// required AddRef;
	WTRiASPropertyCallback Supp;

		THROW_FAILED_HRESULT(pNew -> put_Name (Name));
		THROW_FAILED_HRESULT(GetPropertySupportSite (Name, GetUnknown(), this, Supp.ppi()));
		THROW_FAILED_HRESULT(pNew -> SetSite (Supp));	// using IObjectWithSite

	// Events hinterher
		THROW_FAILED_HRESULT(Fire_PropertyCreated (Prop));
		*Property = Prop.detach();

	} COM_CATCH;
	return S_OK;
}

// Einlesen aller Eigenschaften der Database und aller lokaler Props des
// Objektes.
// Die Eigenschaften einer TRiAS-Database sind im sog. Header gespeichert.

// Props zeigt auf einen bereits existierenden Enumerator und wird durch 
// diese Funktion lediglich mit allen Properties gefüllt.
STDMETHODIMP CTRiASDatabaseBase::FillWithProperties (IUnknown **Props)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);

// zuerst die feststehenden Properties hinzufügen
	RETURN_FAILED_HRESULT(CManagePropertySupport<CTRiASDatabaseBase>::FillWithProperties(Props));

// danach die im Projekt enthaltenen
CActDB ActDB (m_hPr);
CDBHeader DBProp (m_hPr);
CEnumPropertyCallback CallBackData;

	CallBackData.m_pTarget = this;
	CallBackData.m_Enum = *Props;	// throws hr

	RETURN_FAILED_HRESULT(DBProp.EnumHeaderData (RefreshCallBack, (UINT_PTR)&CallBackData)); 
	
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::RemoveProperty (BSTR Name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == Name)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDatabaseBase::RemoveProperty");

	USES_CONVERSION;

// evtl. abschließende Leerzeichen abschneiden
CComBSTR bstrName (TrimRight (Name));

// Events vorher
VARIANT_BOOL fVal = VARIANT_FALSE;
	
	RETURN_FAILED_HRESULT(Fire_DeletingProperty (bstrName, &fVal)); 
	if (VARIANT_TRUE == fVal)
		return S_FALSE;
	RETURN_FAILED_HRESULT(Fire_PropertyToDelete (bstrName));

// nur im Header löschen, wenn's keine vordefinierte Property ist
HRESULT hr = S_OK;

	if (S_OK != PropertyIsPredefined (bstrName)) {
	// eigentliche Aktion
	CActDB ActDB (m_hPr);
	CDBHeader DBProp (m_hPr, OLE2A(bstrName));

		RETURN_FAILED_HRESULT(DBProp.DeleteHeaderEntry()); 

	// ggf. zuständiges Objekt freigeben, S_FALSE (nicht gefunden) darf vorkommen
		RETURN_FAILED_HRESULT(ReleasePropertySupportSite (bstrName));
	}
	else
		RETURN_FAILED_HRESULT(hr = ReleasePropertySupportSite (bstrName));	// zuständiges Objekt freigeben

// Event hinterher
	if (S_OK == hr) {
		RETURN_FAILED_HRESULT(Fire_PropertyDeleted (bstrName));
	}
	return hr;		// S_FALSE heißt: nicht gefunden
}

STDMETHODIMP CTRiASDatabaseBase::PutValue (BSTR Name, VARIANT Value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == Name)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDatabaseBase::PutValue");

	USES_CONVERSION;

// evtl. abschließende Leerzeichen abschneiden
CComBSTR bstrName (TrimRight (Name));

// Events vorher
VARIANT_BOOL fVal = VARIANT_FALSE;
	
	RETURN_FAILED_HRESULT(Fire_ModifyingProperty (bstrName, &fVal)); 
	if (VARIANT_TRUE == fVal)
		return S_FALSE;
	RETURN_FAILED_HRESULT(Fire_PropertyToModify (bstrName));

// HeaderEntry neu schreiben/erzeugen
CActDB ActDB (m_hPr);
CDBHeader DBProp (m_hPr, OLE2A(bstrName));
CComVariant v;

	RETURN_FAILED_HRESULT(v.ChangeType (VT_BSTR, &Value));

CComBSTR Val (V_BSTR(&v));
LONG lFlags = 0;

	DBProp.GetHeaderEntry (NULL, 0, &lFlags);	// evtl. Fehler ignorieren
	RETURN_FAILED_HRESULT(DBProp.PutHeaderEntry (OLE2A(Val), Val.Length(), lFlags));

// Event hinterher
	RETURN_FAILED_HRESULT(Fire_PropertyModified (bstrName));
	
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::GetValue (BSTR Name, VARIANT *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == Name)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDatabaseBase::GetValue");
	if (NULL == pVal)
		return E_POINTER;

	USES_CONVERSION;

// evtl. abschließende Leerzeichen abschneiden
CComBSTR bstrName (TrimRight (Name));

	COM_TRY {
	// HeaderEntry komplett einlesen
	CActDB ActDB (m_hPr);
	CDBHeader DBProp (m_hPr, OLE2A(bstrName));
	size_t iLen = 0;

		THROW_FAILED_HRESULT(DBProp.GetHeaderEntryLen(&iLen));

	char *pBuffer = (char *)_alloca(iLen);

		THROW_FAILED_HRESULT(DBProp.GetHeaderEntry (pBuffer, iLen, NULL));

	CComVariant v (pBuffer);

		THROW_FAILED_HRESULT(v.Detach(pVal));

	} COM_CATCH_EX(e) {
	// evtl. ist ein Defaultwert für diese Property vorgesehen
		if (FAILED(GetDefaultValues (bstrName, pVal)))
			return _COM_ERROR(e);
	// ansonsten durchfallen
	// ...
	} COM_CATCH_ALL;

	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::PutType (BSTR Name, PROPERTY_TYPE Value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == Name)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDatabaseBase::PutType");

	USES_CONVERSION;

// evtl. abschließende Leerzeichen abschneiden
CComBSTR bstrName (TrimRight (Name));

// Events vorher
VARIANT_BOOL fVal = VARIANT_FALSE;
	
	RETURN_FAILED_HRESULT(Fire_ModifyingProperty (bstrName, &fVal)); 
	if (VARIANT_TRUE == fVal)
		return S_FALSE;
	RETURN_FAILED_HRESULT(Fire_PropertyToModify (bstrName));

// HeaderEntry neu schreiben/erzeugen
CActDB ActDB (m_hPr);
CDBHeader DBProp (m_hPr, OLE2A(bstrName));
size_t iLen = 0;

	RETURN_FAILED_HRESULT(DBProp.GetHeaderEntryLen(&iLen));

char *pBuffer = (char *)_alloca(iLen);

	RETURN_FAILED_HRESULT(DBProp.GetHeaderEntry (pBuffer, iLen, NULL));
	RETURN_FAILED_HRESULT(DBProp.PutHeaderEntry (pBuffer, iLen-1, Value));

// Event hinterher
	RETURN_FAILED_HRESULT(Fire_PropertyModified (bstrName));
	
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::GetType (BSTR Name, PROPERTY_TYPE *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == Name)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDatabaseBase::GetType");
	TEST_OUT_PARAM(pVal);

	USES_CONVERSION;

// evtl. abschließende Leerzeichen abschneiden
CComBSTR bstrName (TrimRight (Name));

// HeaderEntry komplett einlesen
PROPERTY_TYPE lFlags;
CActDB ActDB (m_hPr);
CDBHeader DBProp (m_hPr, OLE2A(bstrName));

	RETURN_FAILED_HRESULT(DBProp.GetHeaderEntry (NULL, 0, (LONG *)&lFlags));

	*pVal = lFlags;
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::PutValueAndType(BSTR Name, VARIANT Val, PROPERTY_TYPE Type)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == Name)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDatabaseBase::PutType");

	USES_CONVERSION;

// evtl. abschließende Leerzeichen abschneiden
CComBSTR bstrName (TrimRight (Name));

// Events vorher
VARIANT_BOOL fVal = VARIANT_FALSE;
	
	RETURN_FAILED_HRESULT(Fire_ModifyingProperty (bstrName, &fVal)); 
	if (VARIANT_TRUE == fVal)
		return S_FALSE;
	RETURN_FAILED_HRESULT(Fire_PropertyToModify (bstrName));

// HeaderEntry neu schreiben/erzeugen
CActDB ActDB (m_hPr);
CDBHeader DBProp (m_hPr, OLE2A(bstrName));
CComVariant v;

	RETURN_FAILED_HRESULT(v.ChangeType (VT_BSTR, &Val));

CComBSTR bstrVal (V_BSTR(&v));

	RETURN_FAILED_HRESULT(DBProp.PutHeaderEntry (OLE2A(bstrVal), bstrVal.Length(), Type));

// Event hinterher
	RETURN_FAILED_HRESULT(Fire_PropertyModified (bstrName));
	
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::GetValueAndType(BSTR Name, VARIANT * pVal, PROPERTY_TYPE * pType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == Name || NULL == pVal || NULL == pType)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDatabaseBase::GetType");
	
	BEGIN_OUT_PARAMS()
		OUT_PARAM(pVal)
		OUT_PARAM(pType)
	END_OUT_PARAMS()

	USES_CONVERSION;

// evtl. abschließende Leerzeichen abschneiden
CComBSTR bstrName (TrimRight (Name));

	COM_TRY {
	// HeaderEntry komplett einlesen
	PROPERTY_TYPE lFlags;
	CActDB ActDB (m_hPr);
	CDBHeader DBProp (m_hPr, OLE2A(bstrName));
	size_t iLen = 0;

		THROW_FAILED_HRESULT(DBProp.GetHeaderEntryLen(&iLen));

	char *pBuffer = (char *)_alloca(iLen);

		THROW_FAILED_HRESULT(DBProp.GetHeaderEntry (pBuffer, iLen, (LONG *)&lFlags));

	CComVariant v (pBuffer);

		THROW_FAILED_HRESULT(v.Detach(pVal));
		*pType = lFlags;

	} COM_CATCH_EX(e) {
	// evtl. ist ein Defaultwert für diese Property vorgesehen
		if (FAILED(GetDefaultValues (bstrName, pVal, pType)))
			return _COM_ERROR(e);
	// ansonsten durchfallen
	// ...
	} COM_CATCH_ALL;
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::Refresh(BSTR bstrName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL != m_hPr) {
	UINT uiLen = SysStringLen(bstrName);

		if (0 == uiLen || !wcscmp (bstrName, g_cbTRiASCSTransform)) {
		// evtl. Koordinatensystem neu berechnen
			RETURN_FAILED_HRESULT(InitCoordSystemService());
		}
		if (0 == uiLen || !wcscmp (bstrName, g_cbTRiASConnectFilter)) {
		// evtl. ConnectFilter neu initialisieren
			RETURN_FAILED_HRESULT(InitConnectFilter());
		}
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CTRiASDatabaseBase::get_Name(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(pVal);

CComBSTR bstrName (m_bstrName);

	if (!bstrName)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

	*pVal = bstrName.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::get_TemporaryName(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(pVal);

CComBSTR bstrName (m_bstrName);

	if (m_fIsTemporary) {
	WStorage IStorage;
		
		if (SUCCEEDED(::GetProjectStorage (m_hPr, IStorage.ppi()))) {
		STATSTG st;

			IStorage -> Stat (&st, STATFLAG_DEFAULT);
			bstrName = st.pwcsName;
			CoTaskMemFree (st.pwcsName);	// aufräumen
		}
	} 

	if (!bstrName)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

	*pVal = bstrName.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::get_VersionLong(LONG * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(pVal);

	*pVal = ::GetDBVersion(m_hPr);
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::get_Handle(INT_PTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(pVal);

	*pVal = (LONG)m_hPr;
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::get_IsDirty(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	TEST_OUT_PARAM(pVal);

BOOL fIsDirty = FALSE;

	::IsDirty(m_hPr, &fIsDirty);
	*pVal = fIsDirty ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::put_IsDirty(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);

	::SetDirty (m_hPr, newVal ? TRUE : FALSE);
	return S_OK;
}

STDMETHODIMP CTRiASCompatibleDatabase::get_SchemaUpdatable(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(pVal);

	*pVal = VARIANT_FALSE;		// für alte TRiAS-DB's immer false
	return S_OK;
}

STDMETHODIMP CTRiASDatabase::get_SchemaUpdatable(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(pVal);

	*pVal = VARIANT_TRUE;		// für TRiAS-DB's immer true
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Methods
STDMETHODIMP CTRiASDatabaseBase::Close()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);

// bei OLE abmelden
	RenameDatabase(NULL);		// Moniker wieder aus ROT ausbauen

// ACHTUNG: Unter bestimmten Umständen kann/können die Datenbank(en) bereits durch
// TRiAS geschlossen worden sein (Übergangszustände vom alten zum neuen TRiAS), deshalb die
// total sinnlos erscheinenden Tests.
HRESULT hr = S_OK;
ErrCode RC = EC_OKAY;
BOOL fOpened = FALSE;
CComBSTR bstrTempName;

	get_TemporaryName (CLEARED(&bstrTempName));

// alle Objekte abhängen (_vor_ FreePropertiesCollection, da sonst neue Coll erzeugt wird)
	if (m_ObjectsDefs.IsValid()) {
	// nur, wenn ObjectsCollection bereits erzeugt worden ist (#HK000123)
		m_ObjectsDefs -> put_Parent (NULL);
		m_ObjectsDefs.Assign(NULL);
	}

// FeatureMap entleeren
WTRiASObjectHandleMap Map (GetPropertyFrom (GetDispatch(), g_cbFeatureMap, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab

	if (Map.IsValid())
		Map -> RemoveObject (NULL, OBJECTMAPMODE_RemoveAllObjects);

// alles freigeben
	ShutdownCoordSystemService();
	ReleasePropertySupportObjects();
	FreePropertiesCollection();
	DisconnectCookieHolder();

	m_bstrName.Empty();
	m_bstrSource.Empty();
	m_bstrLocale.Empty();

// Pbd schließen
	VERIFY(::IsOpened (m_hPrPbd, &fOpened));
	if (fOpened && NULL != m_hPrPbd) {
	CActDB ActDB (m_hPrPbd);

		RC = (ErrCode)z_close (m_hPrPbd, false);	// PBD schließen, Fehler nicht fatal
		if (EC_OKAY != RC)
			hr = HRESULT_FROM_ERRCODE(RC);
		m_hPrPbd = NULL;
		ActDB.Reset();
	} else
		m_hPrPbd = NULL;

// Datenbank schließen
	VERIFY(::IsOpened (m_hPr, &fOpened));
	if (fOpened && NULL != m_hPr) {
	CActDB ActDB (m_hPr);

		RC = (ErrCode)z_close (m_hPr, false);	// DB schließen
		if (EC_OKAY != RC)
			hr = HRESULT_FROM_ERRCODE(RC);
		m_hPr = NULL;
		ActDB.Reset();
	} else
		m_hPr = NULL;

	if (m_fIsTemporary)	{	// Datei jetzt löschen, da temporär erzeugt
		USES_CONVERSION;
		DeleteFile (OLE2A(bstrTempName));
	}

//	ReleasePropertySupportObjects();
	return hr;
}

HRESULT CTRiASDatabaseBase::Open (LPCTSTR pcName, IStorage *pIStg, bool &rfReadOnly, HPROJECT *phPr)
{
	if (NULL == phPr)
		return E_POINTER;
	*phPr = NULL;

// set corresponding StorageModeFlags
DWORD dwMode = rfReadOnly ? STGM_READ : (STGM_READWRITE | STGM_SHARE_DENY_WRITE);

// try to open without error-reporting
ErrInstall IgnoreErrors (EC_IGNOREALL);
ErrInstall IgnoreWarnings (WC_IGNOREALL);

HPROJECT hPr = NULL;

	if (NULL == pIStg) {
		if (NULL == pcName) 
			_com_issue_error(E_POINTER);
		hPr = (HPROJECT)z_open_ex ((LPTSTR)pcName, NULL, NULL, rfReadOnly ? TRUE : FALSE, dwMode, FALSE);
	} else
		hPr = (HPROJECT)z_open_storage_ex (pIStg, rfReadOnly ? TRUE : FALSE, FALSE, NULL, FALSE);

	if (NULL == hPr) {
	HRESULT hr = ::GetLastError();

		if (FACILITY_ERRCODE == HRESULT_FACILITY(hr)) {
		// Fehler ist in Wirklichkeit ein ErrCode
		ErrCode RC = ERRCODE_FROM_HRESULT(hr);

			switch (RC) {
			// nicht korrigierbare Fehler
			case EC_NOTAPROJECT:
				hr = TRIASDB_E_NOTAPROJECT;
				break;

			case EC_NOMEMORY:
				hr = E_OUTOFMEMORY;
				break;

			case EC_ACCESS:
				hr = TRIASDB_E_COULD_NOT_OPEN;
				break;

			case EC_INVDBNAME:
				hr = TRIASDB_E_SINGLEDATABASE_NOT_FOUND;		// keine Datei oder existiert nicht
				break;
			}

		} else {
		// alle anderen hier bearbeiten
		BOOL fRO = rfReadOnly ? TRUE : FALSE;

			if (STG_E_SHAREVIOLATION == hr || STG_E_LOCKVIOLATION == hr) {
			// ZugriffsKonflikt
				if (!fRO && (NULL == pcName || !TestFileRO (pcName, fRO))) 
					hr = TRIASDB_E_SINGLEDATABASE_NOT_FOUND;	// keine Datei oder existiert nicht
				else
					hr = fRO ? TRIASDB_S_MUSTOPENASCOPY : TRIASDB_S_MUSTOPENASCOPY_SHAREVIOLATION;

			} else if (STG_E_ACCESSDENIED == hr) {
			// ZugriffsRechtsÜberschreitung (Datei ist lediglich ReadOnly)
				if (NULL == pcName || !TestFileRO (pcName, fRO)) 
					hr = TRIASDB_E_SINGLEDATABASE_NOT_FOUND;	// keine Datei oder existiert nicht
				else 
					hr = TRIASDB_S_MUSTOPENASCOPY;
			}
		}

	// den Fehler nach oben propagieren
		return hr;
	}

// evtl. alle Dateien auf ReadOnly setzen
	if (rfReadOnly) 
		z_access (hPr, Z_ALL|Z_RDONLY); 	// DB ReadOnly
	*phPr = hPr;		// Resultat
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Öffnen einer Datenbank
STDMETHODIMP CTRiASDatabaseBase::OpenDatabase(
	BSTR Name, VARIANT_BOOL /*Exclusive*/, VARIANT_BOOL fReadOnly, 
	VARIANT_BOOL /*ModTrack*/, BSTR Source)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL != m_hPr)
		return REPORT_DBERROR(TRIASDB_W_ALREADY_OPENED);

// Werte aus Parametern besorgen und speichern
	m_fIsReadOnly = fReadOnly ? true : false;

	if (SysStringLen(Source) > 0)
		m_bstrSource = Source;

	m_bstrName = Name;
	if (!m_bstrName)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

	USES_CONVERSION;
	COM_TRY {
	// Datenbank jetzt entsprechend Vorgaben öffnen
	HRESULT hr = Open (OLE2A(m_bstrName), NULL, m_fIsReadOnly, &m_hPr);

		if (FAILED(hr) || NULL == m_hPr) 
			return hr;		// nicht erfolgreich geöffnet

		THROW_FAILED_HRESULT(OpenMetaDatabase());		// Pbd dazu eröffnen
		THROW_FAILED_HRESULT(CreatePropertiesCollection());

	// Featurescollection als property erzeugen
	WTRiASFeatures Feats (CLSID_TRiASSimpleFeatures);

		THROW_FAILED_HRESULT(Feats -> put_Parent (GetDispatch()));			// temporary parent
		SetProperty (GetProperties(), g_cbHasSimpleFeatures, CComVariant(false), true);
		SetProperty (GetProperties(), g_cbSimpleFeatures, static_cast<IDispatch *>(Feats), true);

	WTRiASFeatures GeoFeats (CLSID_TRiASSimpleGeoFeatures);

		THROW_FAILED_HRESULT(GeoFeats -> put_Parent (GetDispatch()));		// temporary parent
		SetProperty (GetProperties(), g_cbHasSimpleGeoFeatures, CComVariant(false), true);
		SetProperty (GetProperties(), g_cbSimpleGeoFeatures, static_cast<IDispatch *>(GeoFeats), true);

	// SourceString auswerten
	int iCompatible = 0;

		if (SUCCEEDED(GetCompatibilityModeFromSource (Source, &iCompatible)) &&
			209 == iCompatible) 
		{
		// Kompatibilitätsmodus festlegen
			SetPropertyAndType(GetProperties(), g_cbCompatibilityMode, CComBSTR("209"), PROPERTY_TYPE(PROPERTY_TYPE_System|PROPERTY_TYPE_ReadOnly), true);
		}

		THROW_FAILED_HRESULT(RetrieveLastCookie());		// LastCookies einlesen
		THROW_FAILED_HRESULT(ConnectCookieHolder());

	// Datenbank bei OLE anmelden
	WMoniker Mk;

		THROW_FAILED_HRESULT(CreateFileMoniker (m_bstrName, Mk.ppi()));
		THROW_FAILED_HRESULT(RenameDatabase (Mk));

	// KoordinatenSystemService erzeugen und initialisieren
		THROW_FAILED_HRESULT(InitCoordSystemService());

	} COM_CATCH_EX(e) {
		if (NULL != m_hPr) 
			Close();		// wieder schließen
		return _COM_ERROR(e);
	} COM_CATCH_ALL;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Öffnen einer Datenbank
STDMETHODIMP CTRiASDatabaseBase::OpenStorageAsDatabase(
	IUnknown *pIUnk, VARIANT_BOOL /*Exclusive*/, VARIANT_BOOL fReadOnly, 
	VARIANT_BOOL /*ModTrack*/, BSTR Source)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL != m_hPr)
		return REPORT_DBERROR(TRIASDB_W_ALREADY_OPENED);

// Werte aus Parametern besorgen und speichern
	m_fIsReadOnly = fReadOnly ? true : false;

	if (SysStringLen(Source) > 0)
		m_bstrSource = Source;

	USES_CONVERSION;
	COM_TRY {
	WStorage Stg (pIUnk);
	STATSTG StatStg;

		THROW_FAILED_HRESULT(Stg -> Stat (&StatStg, STATFLAG_DEFAULT));
		m_bstrName = StatStg.pwcsName;
		CoTaskMemFree (StatStg.pwcsName);
		if (!m_bstrName)
			return Error (g_cbNoMemory, E_OUTOFMEMORY);

	// Datenbank jetzt entsprechend Vorgaben öffnen
	HRESULT hr = Open (NULL, Stg, m_fIsReadOnly, &m_hPr);

		if (FAILED(hr) || NULL == m_hPr) 
			return hr;	// nicht erfolgreich geöffnet

		THROW_FAILED_HRESULT(OpenMetaDatabase());		// Pbd dazu eröffnen
		THROW_FAILED_HRESULT(CreatePropertiesCollection());

	// Featurescollection als property erzeugen
	WTRiASFeatures Feats (CLSID_TRiASSimpleFeatures);

		THROW_FAILED_HRESULT(Feats -> put_Parent (GetDispatch()));			// temporary parent
		SetProperty (GetProperties(), g_cbHasSimpleFeatures, CComVariant(false), true);
		SetProperty (GetProperties(), g_cbSimpleFeatures, static_cast<IDispatch *>(Feats), true);

	WTRiASFeatures GeoFeats (CLSID_TRiASSimpleGeoFeatures);

		THROW_FAILED_HRESULT(GeoFeats -> put_Parent (GetDispatch()));		// temporary parent
		SetProperty (GetProperties(), g_cbHasSimpleGeoFeatures, CComVariant(false), true);
		SetProperty (GetProperties(), g_cbSimpleGeoFeatures, static_cast<IDispatch *>(GeoFeats), true);

	// SourceString auswerten
	int iCompatible = 0;

		if (SUCCEEDED(GetCompatibilityModeFromSource (Source, &iCompatible)) &&
			209 == iCompatible) 
		{
		// Kompatibilitätsmodus festlegen
			SetPropertyAndType(GetProperties(), g_cbCompatibilityMode, CComBSTR("209"), PROPERTY_TYPE(PROPERTY_TYPE_System|PROPERTY_TYPE_ReadOnly), true);
		}

		THROW_FAILED_HRESULT(RetrieveLastCookie());		// LastCookies einlesen
		THROW_FAILED_HRESULT(ConnectCookieHolder());

	// Datenbank bei OLE anmelden (DB wird über Connection gebunden)
	WMoniker Mk;

		THROW_FAILED_HRESULT(GetContainerMoniker (Mk.ppi()));
		THROW_FAILED_HRESULT(RenameDatabase (Mk));

	// KoordinatenSystemService erzeugen und initialisieren
		THROW_FAILED_HRESULT(InitCoordSystemService());

	} COM_CATCH_EX(e) {
		if (NULL != m_hPr) 
			Close();		// wieder schließen
		return _COM_ERROR(e);
	} COM_CATCH_ALL;
	return S_OK;
}

HRESULT CTRiASDatabaseBase::GetContainerMoniker (IMoniker **ppIMk)
{
	COM_TRY {
	WTRiASConnection Parent;
	WMoniker mk;

		THROW_FAILED_HRESULT(FindSpecificParent(m_Parent, Parent.ppi()));
		THROW_FAILED_HRESULT(MkGetMoniker (Parent, OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJFULL, mk.ppi()));
		*ppIMk = mk.detach();

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASDatabaseBase::GetCompatibilityModeFromSource(
	BSTR bstrSrc, int *piCompatible, BOOL *pfCompressed)
{
	if (NULL == piCompatible)
		return E_POINTER;
	*piCompatible = 0;

	if (NULL != pfCompressed)
		*pfCompressed = false;

	COM_TRY {
	WParseStringPairs Parse (CLSID_ParseStringPairs);	// throws hr
	CComBSTR bstrVal;
	long lPairs = 0;

		THROW_FAILED_HRESULT(Parse -> put_Pattern(CComBSTR(g_cbCollatePattern)));
		THROW_FAILED_HRESULT(Parse -> Parse(bstrSrc, &lPairs));

		if (0 == lPairs)
			return S_FALSE;		// keine Key/Value-Paare gefunden

	// Kompatibilität mit V2.00 bzw. V3.xx/4.xx
		if (S_OK == Parse -> get_Value (CComBSTR(g_cbCompatible), CLEARED(&bstrVal)))
		{
			*piCompatible = _wtol (bstrVal);
		}

	// Komprimiert speichern
		if (pfCompressed && S_OK == Parse -> get_Value (CComBSTR(g_cbCompressed), CLEARED(&bstrVal)))
		{
			*pfCompressed = (0 != _wtol (bstrVal)) ? true : false;
		}

	// IdentBase
//		if (S_OK == Parse -> get_Value (CComBSTR(g_cbIdentBase), CLEARED(&bstrVal)))
//			SetProperty (GetProperties(), g_cbIdentBaseHdr, bstrVal, true);

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::OpenFilesAsDatabase(
	IUnknown *pIEnum, VARIANT_BOOL /*Exclusive*/, VARIANT_BOOL fReadOnly, 
	VARIANT_BOOL /*ModTrack*/, BSTR Source)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	ATLTRACENOTIMPL("CTRiASDatabaseBase::OpenFilesAsDatabase");
}

STDMETHODIMP CTRiASDatabaseBase::get_CollatingOrder (long *pCollatingOrder)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(pCollatingOrder);

	COM_TRY {
	WParseStringPairs Parse (CLSID_ParseStringPairs);
	CComBSTR bstrVal;
	long lPairs = 0;

		THROW_FAILED_HRESULT(Parse -> put_Pattern(CComBSTR(g_cbCollatePattern)));
		THROW_FAILED_HRESULT(Parse -> Parse(m_bstrLocale, &lPairs));

		if (0 < lPairs && SUCCEEDED(Parse -> get_Value (CComBSTR(g_cbLangId), CLEARED(&bstrVal))))
			*pCollatingOrder = wcstol(bstrVal, NULL, 16);
		else {
			*pCollatingOrder = COLLATEORDER_Neutral;
			return S_FALSE;
		}

	} COM_CATCH_OP(*pCollatingOrder = COLLATEORDER_Neutral);	// gdbNeutral

	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::get_Connect (BSTR *Connect)
{
	TEST_OUT_PARAM(Connect);
	ATLTRACENOTIMPL("CTRiASDatabaseBase::get_Connect");
}

//STDMETHODIMP CTRiASDatabaseBase::get_GAliasTable (BSTR *AliasTableName)
//{
//	TEST_OUT_PARAM(AliasTableName);
//	ATLTRACENOTIMPL("CTRiASDatabaseBase::get_GAliasTable");
//}

//STDMETHODIMP CTRiASDatabaseBase::get_SQLConformance (long *pSQLConformance)
//{
//	ATLTRACENOTIMPL("CTRiASDatabaseBase::get_SQLConformance");
//}

STDMETHODIMP CTRiASDatabaseBase::get_Transactions (VARIANT_BOOL *Transactions)
{
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(Transactions);

	*Transactions = VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::get_Version (BSTR *Version)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(Version);

long lV = ::GetDBVersion(m_hPr);
TCHAR cbBuffer[64];

	wsprintf (cbBuffer, "%ld.%ld.%ld", 
		HIBYTE(HIWORD(lV)), LOBYTE(HIWORD(lV)), LOBYTE(LOWORD(lV)));

CComBSTR bstr (cbBuffer);

	if (!bstr) 
		return Error (g_cbNoMemory, E_OUTOFMEMORY);
	*Version = bstr.Detach();		
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::BeginTrans (void)
{
	ATLTRACENOTIMPL("CTRiASDatabaseBase::BeginTrans");
}

STDMETHODIMP CTRiASDatabaseBase::ClearModificationLog (LONG Entry)
{
	ATLTRACENOTIMPL("CTRiASDatabaseBase::ClearModificationLog");
}

STDMETHODIMP CTRiASDatabaseBase::CommitTrans (void)
{
	ATLTRACENOTIMPL("CTRiASDatabaseBase::CommitTrans");
}

//STDMETHODIMP CTRiASDatabaseBase::GetExtension (BSTR Name, IDispatch **ppGExtension)
//{
//	TEST_OUT_PARAM(ppGExtension);
//	ATLTRACENOTIMPL("CTRiASDatabaseBase::GetExtension");
//}

STDMETHODIMP CTRiASDatabaseBase::Rollback (void)
{
	ATLTRACENOTIMPL("CTRiASDatabaseBase::Rollback");
}

STDMETHODIMP CTRiASDatabaseBase::ReLoad (RELOADDATABASE rgWhat)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

HRESULT hr = S_OK;

	if (RELOADDATABASE_All == rgWhat) {
	// alles neu einlesen
		RETURN_FAILED_HRESULT(OnResetLookupWindow());
		RETURN_FAILED_HRESULT(OnReLoadObjects());
		RETURN_FAILED_HRESULT(OnReLoadEnvelope());
		RETURN_FAILED_HRESULT(OnReLoadFeatures(RELOADDATABASE_Features));

	} else switch (rgWhat) {
	case RELOADDATABASE_Envelope:		// umschließendes Rechteck neu einlesen
		hr = OnReLoadEnvelope();
		break;

	case RELOADDATABASE_Objects:		// Objektklassen neu einlesen
		hr = OnReLoadObjects();
		break;

	case RELOADDATABASE_ResetLookupWindow:
		hr = OnResetLookupWindow();
		break;

	case RELOADDATABASE_EnsureFeatures:
	case RELOADDATABASE_Features:
		hr = OnReLoadFeatures(rgWhat);
		break;
	}
	return hr;
}

HRESULT CTRiASDatabaseBase::OnReLoadObjects()
{
	COM_TRY {
		if (m_ObjectsDefs.IsValid()) {
//		m_ObjectsDefs -> put_Parent (NULL);
//		m_ObjectsDefs.Assign(NULL);		// werden beim nächsten Zugriff neu eingelesen

		// alle uns bekannten Objektmengen zurücksetzen
		WEnumVARIANT Enum;
		CComVariant v;

			THROW_FAILED_HRESULT(m_ObjectsDefs -> _NewEnum (Enum.ppu()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
				_ASSERTE(SUCCEEDED(v.ChangeType (VT_DISPATCH)));
				THROW_FAILED_HRESULT(WTRiASObjects(V_DISPATCH(&v)) -> Refresh());
			}
		}

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASDatabaseBase::OnReLoadEnvelope()
{
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// alle Objektklassen auffordern ihre Features zu vergessen
HRESULT CTRiASDatabaseBase::OnReLoadFeatures(RELOADDATABASE rgWhat)
{
	if (!m_ObjectsDefs.IsValid()) {
	// evtl. Neuerzeugen der benötigten Collection
	WTRiASObjectsCollection Coll;

		RETURN_FAILED_HRESULT(get_ObjectsDefs (Coll.ppi()));	// fills in m_ObjectsDefs
	}
	_ASSERTE(m_ObjectsDefs.IsValid());

	if (m_ObjectsDefs.IsValid()) {
		COM_TRY {
		WEnumVARIANT Enum;
		CComVariant v;

			THROW_FAILED_HRESULT(m_ObjectsDefs -> _NewEnum (Enum.ppu()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
				_ASSERTE(SUCCEEDED(v.ChangeType (VT_DISPATCH)));

			WTRiASObjects Objs (V_DISPATCH(&v));
			WTRiASFeatures Feats;
			HRESULT hr = Objs -> get_Features (Feats.ppi());

				THROW_FAILED_HRESULT(hr);
				if (S_OK == hr && rgWhat == RELOADDATABASE_Features) {
				// Refresh muß nur dann gerufen werden, wenn die Feature-Collection nicht 
				// neu erzeugt wurde und nicht nur die Features sichergestellt werden sollen
					THROW_FAILED_HRESULT(Feats -> RefreshEx (
						SETUPFEATURESMODE(SETUPFEATURESMODE_Normal|SETUPFEATURESMODE_Force)));
				}

			// Features sicherstellen: es reicht es für eine Objektklasse zu machen
				if (rgWhat == RELOADDATABASE_EnsureFeatures)
					break;
			}
		} COM_CATCH;
	}
	return S_OK;
}

HRESULT CTRiASDatabaseBase::OnResetLookupWindow()
{
	RETURN_FAILED_HRESULT(DelProperty (GetProperties(), g_cbActLookupWindow));
	return S_OK;
}

// LastCookie verwalten
HRESULT CTRiASDatabaseBase::RetrieveLastCookie()
{
	_ASSERTE(NULL != m_hPr);
	COM_TRY {
//		THROW_FAILED_HRESULT(SaveLastCookie());		// evtl. aktuellen Zustand speichern

	INT_PTR lLastCookie = GetProperty (GetProperties(), g_cbLastObjectsCookie, INT_PTR(0), LANG_ENGLISH);
	WTRiASPropertyBase PropBase(m_Parent);

		if (0 != lLastCookie)
			THROW_FAILED_HRESULT(SetPropertyBy (PropBase, g_cbLastObjectsCookie, lLastCookie, true, LANG_ENGLISH));

		lLastCookie = GetProperty (GetProperties(), g_cbLastObjectCookie, INT_PTR(0), LANG_ENGLISH);
		if (0 != lLastCookie)
			THROW_FAILED_HRESULT(SetPropertyBy (PropBase, g_cbLastObjectCookie, lLastCookie, true, LANG_ENGLISH));
		
		lLastCookie = GetProperty (GetProperties(), g_cbLastFeatCookie, INT_PTR(0), LANG_ENGLISH);
		if (0 != lLastCookie)
			THROW_FAILED_HRESULT(SetPropertyBy (PropBase, g_cbLastFeatCookie, lLastCookie, true, LANG_ENGLISH));

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASDatabaseBase::SaveLastCookie(BSTR bstrWhich)
{
	_ASSERTE(NULL != m_hPr);
//	if (m_fMustSaveLastCookie) {
//		COM_TRY {
//		INT_PTR lLastCookie = 0L;
//
//			if (NULL == bstrWhich || !wcscmp(bstrWhich, g_cbObjectsMap)) {
//				lLastCookie = GetPropertyFrom (m_Parent, g_cbLastObjectsCookie, INT_PTR(0), LANG_ENGLISH);
//
//				if (0 != lLastCookie)
//					THROW_FAILED_HRESULT(SetProperty (GetProperties(), g_cbLastObjectsCookie, lLastCookie, true, LANG_ENGLISH));
//			}
//
//			if (NULL == bstrWhich || !wcscmp(bstrWhich, g_cbObjectMap)) {
//				lLastCookie = GetPropertyFrom (m_Parent, g_cbLastObjectCookie, INT_PTR(0), LANG_ENGLISH);
//				if (0 != lLastCookie)
//					THROW_FAILED_HRESULT(SetProperty (GetProperties(), g_cbLastObjectCookie, lLastCookie, true, LANG_ENGLISH));
//			}
//
//			if (NULL == bstrWhich || !wcscmp (bstrWhich, g_cbFeatureMap)) {
//				lLastCookie = GetPropertyFrom (m_Parent, g_cbLastFeatCookie, INT_PTR(0), LANG_ENGLISH);
//				if (0 != lLastCookie)
//					THROW_FAILED_HRESULT(SetProperty (GetProperties(), g_cbLastFeatCookie, lLastCookie, true, LANG_ENGLISH));
//			}
//
//		// Cookies wurden gespeichert
//			m_fMustSaveLastCookie = false;
//		} COM_CATCH;
//	}
	return S_OK;
}

//bool CTRiASDatabaseBase::MustSaveLastCookie()
//{
//	_ASSERTE(NULL != m_hPr);
//
//INT_PTR lLastCookie = GetPropertyFrom (m_Parent, g_cbLastObjectsCookie, INT_PTR(0), LANG_ENGLISH);
//
//	if (lLastCookie != GetPropertyFrom (this, g_cbLastObjectsCookie, lLastCookie, LANG_ENGLISH))
//		return true;	// must save
//
//	lLastCookie = GetPropertyFrom (m_Parent, g_cbLastObjectCookie, INT_PTR(0), LANG_ENGLISH);
//	if (lLastCookie != GetPropertyFrom (this, g_cbLastObjectCookie, lLastCookie, LANG_ENGLISH))
//		return true;	// must save
//
//	lLastCookie = GetPropertyFrom (m_Parent, g_cbLastFeatCookie, INT_PTR(0), LANG_ENGLISH);
//	if (lLastCookie != GetPropertyFrom (this, g_cbLastFeatCookie, lLastCookie, LANG_ENGLISH))
//		return true;	// must save
//
//	return false;	// no need to save
//}

///////////////////////////////////////////////////////////////////////////////
// 
STDMETHODIMP CTRiASDatabaseBase::RefreshChangesFromModificationLog (
	ITRiASRefreshChangesCallback *pICallback)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// ICookieHelperEvents
STDMETHODIMP CTRiASDatabaseBase::CookieHolderInitialized (BSTR Name, INT_PTR NewCookie)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	_ASSERTE(NULL != m_hPr);
	_ASSERTE(!m_fIsReadOnly);

	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::IssuedNextCookie (BSTR Name, INT_PTR NextCookie)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	_ASSERTE(NULL != m_hPr);
	_ASSERTE(!m_fIsReadOnly);

//	RETURN_FAILED_HRESULT(SaveLastCookie(Name));
	m_fMustSaveLastCookie = true;
	return S_OK;
}

HRESULT CTRiASDatabaseBase::ConnectCookieHolder()
{
	_ASSERTE(0 == m_dwCookieHolderCookie);

	if (!m_fIsReadOnly) {
	WCookieHelper CookieHelper;

		RETURN_FAILED_HRESULT(g_pDBEngine -> GetCookieHelper (CookieHelper.ppi()));
		RETURN_FAILED_HRESULT(AtlAdvise (CookieHelper, GetUnknown(), IID_ICookieHelperEvents, &m_dwCookieHolderCookie));
	}
	return S_OK;
}

HRESULT CTRiASDatabaseBase::DisconnectCookieHolder()
{
	if (!m_fIsReadOnly) {
		_ASSERTE(0 != m_dwCookieHolderCookie);

	WCookieHelper CookieHelper;

		RETURN_FAILED_HRESULT(g_pDBEngine -> GetCookieHelper (CookieHelper.ppi()));
		RETURN_FAILED_HRESULT(AtlUnadvise (CookieHelper, IID_ICookieHelperEvents, m_dwCookieHolderCookie));
		m_dwCookieHolderCookie = 0;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Vollen GeoDBNamen erzeugen 
// Der volle GeoDBName wird erzeugt, in dem die im gegebenen DateiNamen fehlenden
// Bestandteile des vollen DateiNamens durch die Teile aus den StandardPfad
// (aus der Registry) ergänzt werden. Wenn nur der Name des Projektes vorgegeben
// ist, so wird folgender Name erzeugt
//		StandardPfad\Projekt\Projekt.ris.
HRESULT GenerateFullPath (LPCTSTR pcDBName, bool fMakeSubDir, os_string &rStr)
{
	if (NULL == pcDBName) 
		return E_POINTER;	// temporäre Datei erzeugen

	COM_TRY {
	os_path Name = os_string(pcDBName);

	// wenn UNC vorliegt, dann nichts machen
		if (!Name.has_unc()) {
		// Default-Verzeichnis besorgen
		os_path Default = os_string(g_cbProjects);

		// fehlende Bestandteile des Namens ersetzen
			if (!Name.has_directory() && !Name.has_fulldrive())
				Name.directory (Default.directory());
			if (!Name.has_drive())
				Name.drive (*Default.drive().c_str());
			if (Name.base().size() > 0 && !Name.has_extension())
				Name.extension (os_string(g_cbRis));

			if (fMakeSubDir) {
			// Unterverzeichnis dranhängen, welches genau wie die Datei heißt
			os_string dir (Name.directory());

				dir += Name.path_separator();
				dir += Name.base();
				Name.directory (dir);
			}
		}
		rStr = (LPCTSTR)Name;	// Resultat kopieren
	} COM_CATCH;
	
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseOnFile::CreateDatabase(BSTR Name, BSTR Locale, BSTR Source)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL != m_hPr)
		return REPORT_DBERROR(TRIASDB_W_ALREADY_OPENED);

	m_bstrName = Name;
	if (!m_bstrName)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);
	m_bstrLocale = Locale;
	if (!m_bstrLocale)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);
	m_bstrSource = Source;
	if (!m_bstrSource)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

	COM_TRY {
	WStorage Stg;
	os_string strName;
	int iCompatible = 0;
	BOOL fCompressed = FALSE;
	UINT uiResID = IDR_DBD019;
	UINT uiResIDPbd = IDR_PBD013;

		if (SUCCEEDED(GetCompatibilityModeFromSource (Source, &iCompatible, &fCompressed)) &&
			0 != iCompatible) 
		{
			if (iCompatible < 300) {
			// kompatibel zu V2.xx
				uiResID = IDR_DBDOLD; 
				uiResIDPbd = IDR_PBD011;
			}
			else if (iCompatible < 500) {
			// kompatibel zu V3.xx/V4.xx
				uiResID = IDR_DBD017; 
				uiResIDPbd = IDR_PBD012;
			}
		}

		THROW_FAILED_HRESULT(CreateMainDatabase (Name, uiResID, fCompressed, strName, Stg.ppi()));
		THROW_FAILED_HRESULT(CreateMetaDatabase (Stg, uiResIDPbd, fCompressed, strName.c_str()));

	// Speichern
	DWORD rgStgc = STGC_DEFAULT;
		
		if (IsWin50() && IsWinNT()) 
			rgStgc |= STGC_CONSOLIDATE;
		THROW_FAILED_HRESULT(Stg -> Commit (rgStgc));		// alles wegschreiben

	} COM_CATCH;
	return S_OK;
}

// Save/SaveAs dürfen nur dann wirklich speichern, wenn der StgMode == Normal ist
// da ansonsten diese Datenquelle bereits gespeichert wurde (IPersistStorage::Save)
STDMETHODIMP CTRiASDatabaseOnStg::SaveAs (BSTR NewName)
{
	if (STGMODE_Normal == m_StgMode)
	{
		RETURN_FAILED_HRESULT(CTRiASDatabase::SaveAs (NewName));
	}
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseOnStg::Save ()
{
	if (STGMODE_Normal == m_StgMode)
	{
		RETURN_FAILED_HRESULT(CTRiASDatabase::Save());
	}
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseOnStg::OpenStorageAsDatabase(
	IUnknown *pIUnk, VARIANT_BOOL fExclusive, VARIANT_BOOL fReadOnly, 
	VARIANT_BOOL fModTrack, BSTR Source)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL != m_hPr)
		return REPORT_DBERROR(TRIASDB_W_ALREADY_OPENED);

	RETURN_FAILED_HRESULT(CTRiASDatabaseBase::OpenStorageAsDatabase(pIUnk, fExclusive, fReadOnly, fModTrack, Source));
	m_StgMode = STGMODE_Normal;			// jetzt darf gespeichert werden

	return S_OK;
}

STDMETHODIMP CTRiASDatabaseOnStg::CreateDatabaseOnStg (IUnknown *pIUnk, BSTR Name, BSTR Locale, BSTR Source)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL != m_hPr)
		return REPORT_DBERROR(TRIASDB_W_ALREADY_OPENED);

	m_bstrName = Name;
	if (!m_bstrName)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);
	m_bstrLocale = Locale;
	if (!m_bstrLocale)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);
	m_bstrSource = Source;
	if (!m_bstrSource)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

	COM_TRY {
	WStorage Stg (pIUnk);
	os_string strName;
	int iCompatible = 0;
	BOOL fCompressed = FALSE;
	UINT uiResID = IDR_DBD019;
	UINT uiResIDPbd = IDR_PBD013;

		if (SUCCEEDED(GetCompatibilityModeFromSource (Source, &iCompatible, &fCompressed)) && 
			0 != iCompatible) 
		{
			if (iCompatible < 300) {
			// kompatibel zu V2.xx
				uiResID = IDR_DBDOLD; 
				uiResIDPbd = IDR_PBD011;
			}
			else if (iCompatible < 500) {
			// kompatibel zu V3.xx/V4.xx
				uiResID = IDR_DBD017; 
				uiResIDPbd = IDR_PBD012;
			}
		}

		THROW_FAILED_HRESULT(CreateMainDatabase (Stg, uiResID, fCompressed));
		THROW_FAILED_HRESULT(CreateMetaDatabase (Stg, uiResIDPbd, fCompressed));

	DWORD rgStgc = STGC_DEFAULT;
		
		if (IsWin50() && IsWinNT()) rgStgc |= STGC_CONSOLIDATE;
		THROW_FAILED_HRESULT(Stg -> Commit (rgStgc));		// alles wegschreiben

		m_StgMode = STGMODE_Normal;			// jetzt darf gespeichert werden

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::CreateDatabase (BSTR Name, BSTR Locale, BSTR Source)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASDatabaseOnFile::CreateDatabase");
}

STDMETHODIMP CTRiASDatabaseBase::CreateDatabaseFromFiles(IUnknown *pIEnum, BSTR Locale, BSTR Source)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASDatabaseOnFile::CreateDatabaseFromFiles");
}

STDMETHODIMP CTRiASDatabaseBase::CreateDatabaseOnStg (IUnknown *pIUnk, BSTR Name, BSTR Locale, BSTR Source)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASDatabaseOnFile::CreateDatabaseOnStg");
}

HRESULT CTRiASDatabaseOnFile::CreateMainDatabase (
	BSTR Name, UINT uiResID, BOOL fCompressed, os_string &rStr, IStorage **ppIStg)
{
DWORD dwResSize;
LPBYTE lpRes = ReadResource (uiResID, dwResSize);

	if (NULL == lpRes)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

CDBDictCompoundFile *pDBDict = NULL;

	USES_CONVERSION;
	COM_TRY {
	// TRiAS.Document.2
		THROW_FAILED_HRESULT(GenerateFullPath (OLE2A(Name), false, rStr));
		ATLTRY(pDBDict = CDBDictCompoundFile::CreateInstance (lpRes, fCompressed));
		if (pDBDict == NULL) 
			return Error (g_cbNoMemory, E_OUTOFMEMORY);

	ErrCode EC = pDBDict -> CreateDBEx (rStr.c_str(), NULL, NULL, ppIStg);
	
		if (EC_OKAY != EC)
			_com_issue_error (HRESULT_FROM_ERRCODE(EC));

#if defined(_DEBUG) && defined(_DEBUG_ISTORAGE)
		THROW_FAILED_HRESULT(CStorageWrapper::CreateInstance (*ppIStg, rStr.c_str(), ppIStg));
#endif // defined(_DEBUG) && defined(_DEBUG_ISTORAGE)

	} COM_CATCH_EX(e) {
		DELETE_OBJ(lpRes);
		DELETE_OBJ(pDBDict);
		return _COM_ERROR(e);
	} 
	DELETE_OBJ(lpRes);
	DELETE_OBJ(pDBDict);
	return S_OK;
}

HRESULT CTRiASDatabaseOnStg::CreateMainDatabase (IStorage *pIStg, UINT uiResID, BOOL fCompressed)
{
DWORD dwResSize;
LPBYTE lpRes = ReadResource (uiResID, dwResSize);

	if (NULL == lpRes)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

CDBDictCompoundFile *pDBDict = NULL;

	USES_CONVERSION;
	COM_TRY {
	// TRiAS.Document.2
		ATLTRY(pDBDict = CDBDictCompoundFile::CreateInstance (lpRes, fCompressed));
		if (pDBDict == NULL) 
			return Error (g_cbNoMemory, E_OUTOFMEMORY);

	ErrCode EC = pDBDict -> CreateDBEx (NULL, NULL, NULL, &pIStg);
	
		if (EC_OKAY != EC)
			_com_issue_error (HRESULT_FROM_ERRCODE(EC));

	} COM_CATCH_EX(e) {
		DELETE_OBJ(lpRes);
		DELETE_OBJ(pDBDict);
		return _COM_ERROR(e);
	} 
	DELETE_OBJ(lpRes);
	DELETE_OBJ(pDBDict);
	return S_OK;
}

HRESULT CTRiASDatabase::CreateMetaDatabase (IStorage *pIStg, UINT uiResID, BOOL fCompressed, LPCTSTR pcName)
{
DWORD dwResSize;
LPBYTE lpRes = ReadResource (uiResID, dwResSize);

	if (NULL == lpRes)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

CDBDict *pDBDict = NULL;

	USES_CONVERSION;
	COM_TRY {
	// SubStorage erzeugen
	WStorage SubStg;
	DWORD dwMode = STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED;
	LPCOLESTR poleMetaName = A2OLE(g_cbMetaData);
	HRESULT hr = pIStg -> OpenStorage (poleMetaName, NULL, dwMode, NULL, 0, SubStg.ppi());

		if (FAILED(hr)) {	
			if (STG_E_FILENOTFOUND == hr) {
			// existiert noch nicht, anlegen
				dwMode |= STGM_CREATE;
				THROW_FAILED_HRESULT(pIStg -> CreateStorage (poleMetaName, dwMode, 0, 0, SubStg.ppi()));
			} else
				_com_issue_error(hr);			// sonstiger Fehler
		}

	// "TRiAS.MetaDocument.2"
		ATLTRY(pDBDict = CDBDictCompoundFile::CreateInstance (lpRes, fCompressed));
		if (pDBDict == NULL) 
			return Error (g_cbNoMemory, E_OUTOFMEMORY);

	IStorage *pIStg = SubStg;	// nur temporär kopieren
	ErrCode EC = ((CDBDictCompoundFile *)pDBDict) -> CreateDBEx (NULL, NULL, NULL, 
			&pIStg, &CLSID_TRiASMetaDocument, g_cbMetaProject130);
	
		if (EC_OKAY != EC)
			_com_issue_error (HRESULT_FROM_ERRCODE(EC));

	// alles Speichern			
	DWORD rgStgc = STGC_DEFAULT;
		
		if (IsWin50() && IsWinNT()) rgStgc |= STGC_CONSOLIDATE;
		THROW_FAILED_HRESULT(SubStg -> Commit (rgStgc));

	} COM_CATCH_EX(e) {
		DELETE_OBJ(lpRes);
		DELETE_OBJ(pDBDict);
		return _COM_ERROR(e);
	}

	DELETE_OBJ(lpRes);
	DELETE_OBJ(pDBDict);
	return S_OK;
}

HRESULT CTRiASDatabase::SaveMetaDatabase (void)
{
	if (NULL == m_hPrPbd)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);

	COM_TRY {
	// alle internen Buffer leeren
		{
		CAccessDB ActDB (m_hPrPbd);
		ErrCode RC = EC_OKAY;

			RC = (ErrCode)DBFlush (m_hPrPbd, FLUSH_ACTDB);		// alles wegschreiben
			if (EC_OKAY != RC) _com_issue_error(HRESULT_FROM_ERRCODE(RC));
			RC = (ErrCode)DBPageZeroFlush (m_hPrPbd, FLUSH_ACTDB|FLUSH_COMMITDATA);		// PageZero's auch wegschreiben
			if (EC_OKAY != RC) _com_issue_error(HRESULT_FROM_ERRCODE(RC));
		} // ~CAccessDB

		::SetDirty (m_hPrPbd, FALSE);
		::SetDirty (m_hPr, TRUE);
	} COM_CATCH;
	
	return S_OK;
}

STDMETHODIMP CTRiASDatabase::Save()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);

// alle internen Daten dieser Datenbank wegschreiben
VARIANT_BOOL fIsDirty = VARIANT_FALSE;

	get_IsDirty (&fIsDirty);
	if (fIsDirty) {
		COM_TRY {
		// LastCookie wegschreiben
//			THROW_FAILED_HRESULT(SaveLastCookie());

		// Pbd Speichern
			THROW_FAILED_HRESULT(SaveMetaDatabase());

		// alle internen Buffer leeren
		ErrCode RC = EC_OKAY;
		CActDB ActDB (m_hPr);

			RC = (ErrCode)DBFlush (m_hPr, FLUSH_ACTDB);		// alles wegschreiben
			if (EC_OKAY != RC) _com_issue_error(HRESULT_FROM_ERRCODE(RC));
			RC = (ErrCode)DBPageZeroFlush (m_hPr, FLUSH_ACTDB|FLUSH_COMMITDATA);		// PageZero's auch wegschreiben
			if (EC_OKAY != RC) _com_issue_error(HRESULT_FROM_ERRCODE(RC));

			DatabaseSaved();		// Timestamps in ROT aktualisieren
			::SetDirty (m_hPr, FALSE);
		} COM_CATCH;
		return S_OK;
	}
	return S_FALSE;		// nicht gespeichert, trotzdem ok
}

STDMETHODIMP CTRiASDatabase::SaveAs(BSTR bstrNewName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);

	USES_CONVERSION;
	COM_TRY {
	LPCOLESTR poleMetaName = A2OLE(g_cbMetaData);

		{
		DWORD dwMode = STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED|STGM_CREATE;
		WStorage Stg, PbdStg;
			
			THROW_FAILED_HRESULT(CopyToStorageProject (m_hPr, OLE2A(bstrNewName), Stg.ppi(), NULL, NULL));
			THROW_FAILED_HRESULT(Stg -> CreateStorage (poleMetaName, dwMode, 0, 0, PbdStg.ppi()));
		
		IStorage *pIPbdStg = PbdStg;	// HelperVar
		HRESULT hr = S_OK;

			THROW_FAILED_HRESULT(CopyToStorageProject (m_hPrPbd, g_cbMetaData, &pIPbdStg, &CLSID_TRiASMetaDocument, "TRiAS.MetaDocument.2"));

		DWORD rgStgc = STGC_DEFAULT;
			
			if (IsWin50() && IsWinNT()) rgStgc |= STGC_CONSOLIDATE;
			if (FAILED(hr = PbdStg -> Commit (rgStgc)) || FAILED(hr = Stg -> Commit (rgStgc))) {
			// Plattenplatz reicht nicht
				PbdStg.Assign(NULL);					// freigeben
				Stg -> DestroyElement (poleMetaName);	// und löschen
				return hr;
			}
			::SetDirty (m_hPr, FALSE);		// jetzt nicht mehr dirty
		}	// Stg, PbdStg goes out of scope

	// derzeitige GeoDB schließen und neue wiederöffnen
	CComBSTR bstrSrc (m_bstrSource);

		THROW_FAILED_HRESULT(Close());
		THROW_FAILED_HRESULT(OpenDatabase (bstrNewName, VARIANT_TRUE, VARIANT_FALSE, VARIANT_FALSE, bstrSrc));

	} COM_CATCH;
	return S_OK;
}

// Feststellen, ob diese Datei als Kopie eröffnet wurde
STDMETHODIMP CTRiASDatabase::get_OpenedAsCopy(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(pVal);

CActDB ActDB (m_hPr);
BOOL fIsCopy = FALSE;

	if (!::GetCopyMode (m_hPr, &fIsCopy))
		return REPORT_DBERROR(E_UNEXPECTED);

	*pVal = fIsCopy ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASDatabase::get_CouldOpenTarget(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(pVal);

CActDB ActDB (m_hPr);
BOOL fCouldOpenTarget = FALSE;

	if (!::CouldOpenTarget (m_hPr, &fCouldOpenTarget))
		return REPORT_DBERROR(E_UNEXPECTED);

	*pVal = fCouldOpenTarget ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::get_Temporary(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(pVal);

CActDB ActDB (m_hPr);

#pragma MESSAGE("CTRiASDatabaseBase::get_Temporary implementieren!\n")

	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::put_Temporary (VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);

	m_fIsTemporary = newVal ? true : false;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Pbd öffnen
HPROJECT CTRiASDatabase::OpenStoragePbd (IStorage *pIStg, bool &rfReadOnly)
{
	if (NULL == pIStg) _com_issue_error(E_POINTER);

HPROJECT hPr = (HPROJECT)z_open_storage_pbd (pIStg, rfReadOnly ? TRUE : FALSE);

	if (NULL == hPr && !rfReadOnly) {
	ErrCode EC = ERRCODE_FROM_HRESULT(::GetLastError());
	
		if (EC == EC_OPENRO) {		// muß ReadOnly geöffnet werden
			rfReadOnly = true;
			hPr = (HPROJECT)z_open_storage_pbd (pIStg, TRUE);
		}
		if (NULL == hPr)		// erfolgloser Versuch
			_com_issue_error(HRESULT_FROM_ERRCODE(EC_NOOPEN));
	}

// evtl. alle Dateien auf ReadOnly setzen
	if (rfReadOnly) 
		z_access (hPr, Z_ALL|Z_RDONLY); 	// DB ReadOnly

	return hPr;
}

STDMETHODIMP CTRiASDatabase::OpenMetaDatabase (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);

	USES_CONVERSION;
	COM_TRY {
	// Storage der Datenbank besorgen
	WStorage Stg;

		THROW_FAILED_HRESULT(GetProjectStorage(Stg.ppi()));

	// SubStg öffnen (muß existieren !)
	WStorage PbdStg;
	DWORD dwMode = STGM_TRANSACTED|STGM_SHARE_EXCLUSIVE;
	bool fReadOnly = m_fIsReadOnly;

		if (m_fIsReadOnly) 
			dwMode |= STGM_READ;
		else
			dwMode |= STGM_READWRITE;

		THROW_FAILED_HRESULT(Stg -> OpenStorage(A2OLE(g_cbMetaData), NULL, dwMode, NULL, 0L, PbdStg.ppi()));
		m_hPrPbd = OpenStoragePbd (PbdStg, fReadOnly);

		if (NULL != m_hPrPbd) {		// Pbd dem TRiAS-Projekt zuordnen
			_ASSERTE(NULL != m_hPr);
			SetRelatedProject (m_hPr, m_hPrPbd);
		}
	} COM_CATCH;
	
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Dateibasierte GeoDB erzeugen
STDMETHODIMP CTRiASCompatibleDatabase::CreateDatabase(BSTR Name, BSTR Locale, BSTR Source)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL != m_hPr)
		return REPORT_DBERROR(TRIASDB_W_ALREADY_OPENED);

	m_bstrName = Name;
	if (!m_bstrName)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);
	m_bstrLocale = Locale;
	if (!m_bstrLocale)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

	COM_TRY {
	os_string strName;

		THROW_FAILED_HRESULT(CreateMainDatabase (Name, strName));
		THROW_FAILED_HRESULT(CreateMetaDatabase (strName.c_str()));

	} COM_CATCH;
	
	return S_OK;
}

HRESULT CTRiASCompatibleDatabase::CreateMainDatabase (BSTR Name, os_string &rStr)
{
DWORD dwResSize;
LPBYTE lpRes = ReadResource (IDR_DBDOLD, dwResSize);

	if (NULL == lpRes)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

CDBDict *pDBDict = NULL;

	USES_CONVERSION;
	COM_TRY {
	// TRiAS.Document.1
		THROW_FAILED_HRESULT(GenerateFullPath (OLE2A(Name), true, rStr));
		ATLTRY(pDBDict = CDBDictDOSFiles::CreateInstance (lpRes));
		if (pDBDict == NULL) 
			return Error (g_cbNoMemory, E_OUTOFMEMORY);

	os_path name (rStr);
	ErrCode EC = pDBDict -> CreateDB (rStr.c_str(), name.base().c_str());
	
		if (EC_OKAY != EC)
			_com_issue_error (HRESULT_FROM_ERRCODE(EC));

	} COM_CATCH_EX(e) {
		DELETE_OBJ(lpRes);
		DELETE_OBJ(pDBDict);
		return _COM_ERROR(e);
	}

	DELETE_OBJ(lpRes);
	DELETE_OBJ(pDBDict);
	return S_OK;
}

// Hängt an den Verzeichnispfad nochmal den Namen der Datei dran und ändert 
// die Erweiterung auf 'pbd'
os_path MakePbdName (LPCTSTR pcMainName, LPCTSTR pcPbdName = NULL)
{
os_path path = os_string(pcMainName);
os_string dir = path.directory();

//	dir += path.path_separator();
	dir += os_string(g_cbIdentsDB);

	path.directory (dir);					// Verzeichnis ersetzen
	if (NULL != pcPbdName)
		path.base(pcPbdName);
	path.extension (os_string(g_cbPbd));	// Extension richten
	return path;
}

HRESULT CTRiASCompatibleDatabase::CreateMetaDatabase (LPCTSTR pcName)
{
DWORD dwResSize;
LPBYTE lpRes = ReadResource (IDR_PBDOLD, dwResSize);

	if (NULL == lpRes)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

CDBDict *pDBDict = NULL;

	USES_CONVERSION;
	COM_TRY {
	// TRiAS.MetaDocument.1
		ATLTRY(pDBDict = CDBDictDOSFiles::CreateInstance (lpRes));
		if (pDBDict == NULL) 
			return Error (g_cbNoMemory, E_OUTOFMEMORY);

	os_path name = MakePbdName (pcName);
	ErrCode EC = pDBDict -> CreateDB ((LPCTSTR)name);
	
		if (EC_OKAY != EC)
			_com_issue_error (HRESULT_FROM_ERRCODE(EC));

	} COM_CATCH_EX(e) {
		DELETE_OBJ(lpRes);
		DELETE_OBJ(pDBDict);
		return _COM_ERROR(e);
	}

	DELETE_OBJ(lpRes);
	DELETE_OBJ(pDBDict);
	return S_OK;
}

HRESULT CTRiASCompatibleDatabase::SaveMetaDatabase (void)
{
	if (NULL == m_hPrPbd)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);

	COM_TRY {
	// alle internen Buffer leeren
	CAccessDB ActDB (m_hPrPbd);
	ErrCode RC = EC_OKAY;

		RC = (ErrCode)DBFlush (m_hPrPbd, FLUSH_ACTDB);		// alles wegschreiben
		if (EC_OKAY != RC) _com_issue_error(HRESULT_FROM_ERRCODE(RC));
		RC = (ErrCode)DBPageZeroFlush (m_hPrPbd, FLUSH_ACTDB);		// PageZero's auch wegschreiben
		if (EC_OKAY != RC) _com_issue_error(HRESULT_FROM_ERRCODE(RC));
	} COM_CATCH;
	
	return S_OK;
}

STDMETHODIMP CTRiASCompatibleDatabase::Save()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);

// alle internen Daten dieser Datenbank wegschreiben
VARIANT_BOOL fIsDirty = VARIANT_FALSE;

	get_IsDirty (&fIsDirty);
	if (fIsDirty) {
		COM_TRY {
		// LastCookie wegschreiben
//			THROW_FAILED_HRESULT(SaveLastCookie());

		// Pbd Speichern
			THROW_FAILED_HRESULT(SaveMetaDatabase());

		// alle internen Buffer leeren
		ErrCode RC = EC_OKAY;
		CActDB ActDB (m_hPr);

			RC = (ErrCode)DBFlush (m_hPr, FLUSH_ACTDB);		// alles wegschreiben
			if (EC_OKAY != RC) _com_issue_error(HRESULT_FROM_ERRCODE(RC));
			RC = (ErrCode)DBPageZeroFlush (m_hPr, FLUSH_ACTDB);		// PageZero's auch wegschreiben
			if (EC_OKAY != RC) _com_issue_error(HRESULT_FROM_ERRCODE(RC));

			DatabaseSaved();		// Timestamps in ROT aktualisieren
			::SetDirty (m_hPr, FALSE);
		} COM_CATCH;
	}
	return S_OK;
}

STDMETHODIMP CTRiASCompatibleDatabase::SaveAs(BSTR NewName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASCompatibleDatabase::SaveAs");
}

STDMETHODIMP CTRiASCompatibleDatabase::get_OpenedAsCopy(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(pVal);

// diese Datenbanken werden nie als Kopie eröffnet
	*pVal = VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASCompatibleDatabase::get_CouldOpenTarget(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	TEST_OUT_PARAM(pVal);
	ATLTRACENOTIMPL("CTRiASCompatibleDatabase::get_CouldOpenTarget");
}

///////////////////////////////////////////////////////////////////////////////
// Pbd öffnen

STDMETHODIMP CTRiASCompatibleDatabase::OpenMetaDatabase (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);

HRESULT hr = S_OK;

	USES_CONVERSION;
	COM_TRY {
	// Pfad der Datenbank besorgen
	CDBHeader Hdr (m_hPr, g_cbPbdName);
	char cbPbdName[_MAX_PATH];

		THROW_FAILED_HRESULT(Hdr.GetHeaderEntry (cbPbdName, sizeof(cbPbdName)));

	os_path name = MakePbdName (OLE2A(m_bstrName), cbPbdName);
	bool fReadOnly = m_fIsReadOnly;
	
		hr = Open ((LPCTSTR)name, NULL, fReadOnly, &m_hPrPbd);
		if (SUCCEEDED(hr) && NULL != m_hPrPbd) {		// Pbd dem TRiAS-Projekt zuordnen
			_ASSERTE(NULL != m_hPr);
			SetRelatedProject (m_hPr, m_hPrPbd);
		}

	} COM_CATCH;
	return hr;
}

STDMETHODIMP CTRiASDatabase::get_Updatable(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(pVal);

// diese Datenbank ist prinzipiell immer beschreibbar
	*pVal = VARIANT_TRUE;
	return S_OK;
}

STDMETHODIMP CTRiASCompatibleDatabase::get_Updatable(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(pVal);

// diese Datenbank darf nie beschrieben werden 
	*pVal = VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASDatabase::get_Type(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(pVal);

CComBSTR bstr (g_cbTRiASProject130);

	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASCompatibleDatabase::get_Type(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(pVal);

CComBSTR bstr (g_cbTRiASProject120);

	*pVal = bstr.Detach();
	return S_OK;
}

// ITRiASPropertySupport
//STDMETHODIMP CTRiASCompatibleDatabase::RemoveProperty(BSTR Name)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//	if (NULL == m_hPr)
//		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
//	if (NULL == Name)
//		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASCompatibleDatabase::RemoveProperty");
//
//	COM_TRY {
//        if (S_OK == PropertyIsPredefined(Name)) {
//        // das ist eine bekannte Eigenschaft der BasisKlasse
//            THROW_FAILED_HRESULT(CTRiASDatabaseBase::RemoveProperty(Name));
//        }
//        else {
//        // alles andere wird zur Connection umgeleitet
//	    WTRiASConnection Conn;
//
//		    THROW_FAILED_HRESULT(FindSpecificParent (m_Parent, Conn.ppi()));
//            THROW_FAILED_HRESULT(WTRiASPropertySupport(Conn)->RemoveProperty(Name));
//        }
//
//	} COM_CATCH;
//	return S_OK;
//}

//STDMETHODIMP CTRiASCompatibleDatabase::PutValue(BSTR Name, VARIANT newVal)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//	if (NULL == m_hPr)
//		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
//	if (NULL == Name)
//		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASCompatibleDatabase::PutValue");
//
//	COM_TRY {
//        if (S_OK == PropertyIsPredefined(Name)) {
//        // das ist eine bekannte Eigenschaft der BasisKlasse
//            THROW_FAILED_HRESULT(CTRiASDatabaseBase::PutValue(Name, newVal));
//        }
//        else {
//        // alles andere wird zur Connection umgeleitet
//	    WTRiASConnection Conn;
//
//		    THROW_FAILED_HRESULT(FindSpecificParent (m_Parent, Conn.ppi()));
//            THROW_FAILED_HRESULT(WTRiASPropertySupport(Conn)->PutValue(Name, newVal));
//        }
//
//	} COM_CATCH;
//    return S_OK;
//}

//STDMETHODIMP CTRiASCompatibleDatabase::PutType(BSTR Name, PROPERTY_TYPE newVal)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//	if (NULL == m_hPr)
//		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
//	if (NULL == Name)
//		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASCompatibleDatabase::PutType");
//
//	COM_TRY {
//        if (S_OK == PropertyIsPredefined(Name)) {
//        // das ist eine bekannte Eigenschaft der BasisKlasse
//            THROW_FAILED_HRESULT(CTRiASDatabaseBase::PutType(Name, newVal));
//        }
//        else {
//        // alles andere wird zur Connection umgeleitet
//	    WTRiASConnection Conn;
//
//		    THROW_FAILED_HRESULT(FindSpecificParent (m_Parent, Conn.ppi()));
//            THROW_FAILED_HRESULT(WTRiASPropertySupport(Conn)->PutType(Name, newVal));
//        }
//
//	} COM_CATCH;
//    return S_OK;
//}

//STDMETHODIMP CTRiASCompatibleDatabase::PutValueAndType(BSTR Name, VARIANT Val, PROPERTY_TYPE Type)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//	if (NULL == m_hPr)
//		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
//	if (NULL == Name)
//		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASCompatibleDatabase::PutValueAndType");
//
//	COM_TRY {
//        if (S_OK == PropertyIsPredefined(Name)) {
//        // das ist eine bekannte Eigenschaft der BasisKlasse
//            THROW_FAILED_HRESULT(CTRiASDatabaseBase::PutValueAndType(Name, Val, Type));
//        }
//        else {
//        // alles andere wird zur Connection umgeleitet
//	    WTRiASConnection Conn;
//
//		    THROW_FAILED_HRESULT(FindSpecificParent (m_Parent, Conn.ppi()));
//            THROW_FAILED_HRESULT(WTRiASPropertySupport(Conn)->PutValueAndType(Name, Val, Type));
//        }
//
//	} COM_CATCH;
//    return S_OK;
//}

//STDMETHODIMP CTRiASCompatibleDatabase::GetValueAndType(BSTR Name, VARIANT * pVal, PROPERTY_TYPE * pType)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//	if (NULL == m_hPr)
//		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
//	if (NULL == Name || NULL == pVal || NULL == pType)
//		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASCompatibleDatabase::GetValueAndType");
//	
//	BEGIN_OUT_PARAMS()
//		OUT_PARAM(pVal)
//		OUT_PARAM(pType)
//	END_OUT_PARAMS()
//
//	COM_TRY {
//        if (S_OK == PropertyIsPredefined(Name)) {
//        // das ist eine bekannte Eigenschaft der BasisKlasse
//            THROW_FAILED_HRESULT(CTRiASDatabaseBase::GetValueAndType(Name, pVal, pType));
//        }
//        else {
//        // alles andere wird zur Connection umgeleitet
//	    WTRiASConnection Conn;
//
//		    THROW_FAILED_HRESULT(FindSpecificParent (m_Parent, Conn.ppi()));
//            THROW_FAILED_HRESULT(WTRiASPropertySupport(Conn)->GetValueAndType(Name, pVal, pType));
//        }
//
//	} COM_CATCH;
//	return S_OK;
//}

//STDMETHODIMP CTRiASCompatibleDatabase::Refresh(BSTR bstrName)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//	if (NULL != m_hPr) {
//	    COM_TRY {
//            if (S_OK == PropertyIsPredefined(bstrName)) {
//            // das ist eine bekannte Eigenschaft der BasisKlasse
//                THROW_FAILED_HRESULT(CTRiASDatabaseBase::Refresh(bstrName));
//            }
//            else {
//            // alles andere wird zur Connection umgeleitet
//	        WTRiASConnection Conn;
//
//		        THROW_FAILED_HRESULT(FindSpecificParent (m_Parent, Conn.ppi()));
//                THROW_FAILED_HRESULT(WTRiASPropertySupport(Conn)->Refresh(bstrName));
//            }
//
//	    } COM_CATCH;
//	}
//	return S_OK;
//}

//STDMETHODIMP CTRiASCompatibleDatabase::GetValue (BSTR Name, VARIANT *pVal)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//	if (NULL == m_hPr)
//		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
//	if (NULL == Name)
//		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASCompatibleDatabase::GetValue");
//	if (NULL == pVal)
//		return E_POINTER;
//
//	COM_TRY {
//        if (S_OK == PropertyIsPredefined(Name)) {
//        // das ist eine bekannte Eigenschaft der BasisKlasse
//            THROW_FAILED_HRESULT(CTRiASDatabaseBase::GetValue(Name, pVal));
//        }
//        else {
//        // alles andere wird zur Connection umgeleitet
//	    WTRiASConnection Conn;
//
//		    THROW_FAILED_HRESULT(FindSpecificParent (m_Parent, Conn.ppi()));
//            THROW_FAILED_HRESULT(WTRiASPropertySupport(Conn)->GetValue(Name, pVal));
//        }
//
//	} COM_CATCH;
//	return S_OK;
//}

//STDMETHODIMP CTRiASCompatibleDatabase::CreateProperty (BSTR Name, ITRiASProperty **Property)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//	if (NULL == m_hPr)
//		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
//	TEST_OUT_PARAM(Property);
//
//	COM_TRY {
//        if (S_OK == PropertyIsPredefined(Name)) {
//        // das ist eine bekannte Eigenschaft der BasisKlasse
//            THROW_FAILED_HRESULT(CTRiASDatabaseBase::CreateProperty(Name, Property));
//        }
//        else {
//        // alles andere wird zur Connection umgeleitet
//	    WTRiASConnection Conn;
//
//		    THROW_FAILED_HRESULT(FindSpecificParent (m_Parent, Conn.ppi()));
//            THROW_FAILED_HRESULT(WTRiASPropertySupport(Conn)->CreateProperty(Name, Property));
//        }
//
//	} COM_CATCH;
//	return S_OK;
//}


STDMETHODIMP CTRiASDatabaseOnStg::get_StorageMode(DATABASESTORAGEMODE * pVal)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(pVal);

	*pVal = DATABASESTORAGEMODE_StorageBased;
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::get_StorageMode(DATABASESTORAGEMODE * pVal)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(pVal);

	*pVal = DATABASESTORAGEMODE_FileBased;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IOleItemContainer

STDMETHODIMP CTRiASDatabaseBase::GetObject (
	LPOLESTR pszItem, DWORD dwSpeedNeeded, IBindCtx *pbc, 
	REFIID riid, void **ppvObject)
{
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(ppvObject);
	return COleItemContainerSupport<CTRiASDatabaseBase>::GetObject (pszItem, dwSpeedNeeded, pbc, riid, ppvObject);
}

STDMETHODIMP CTRiASDatabaseBase::GetObjectStorage (
	LPOLESTR pszItem, IBindCtx *pbc, REFIID riid, void **ppvStorage)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(ppvStorage);

	if (!wcscmp (g_cbStgService, pszItem)) {
	WStorage Stg;

		if (SUCCEEDED(GetProjectStorage(Stg.ppi())))
			return Stg -> QueryInterface (riid, ppvStorage);
	}
	return MK_E_NOOBJECT;
}

///////////////////////////////////////////////////////////////////////////////
// IOleClientSite
STDMETHODIMP CTRiASDatabaseBase::SaveObject()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASDatabaseBase::SaveObject");
}

STDMETHODIMP CTRiASDatabaseBase::GetMoniker (
	DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	TEST_OUT_PARAM(ppmk);

	switch (dwWhichMoniker) {
	case OLEWHICHMK_OBJFULL:
	case OLEWHICHMK_OBJREL:
	// This is just the file we're living in.
		if (m_FileMK.IsValid()) {
		WMoniker mk (m_FileMK);

			*ppmk = mk.detach();
		}
		break;

	case OLEWHICHMK_CONTAINER:
	default:
		break;
	}
	return (NULL == *ppmk) ? E_FAIL : S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::GetContainer (IOleContainer **ppContainer)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	TEST_OUT_PARAM(ppContainer);
	ATLTRACENOTIMPL("CTRiASDatabaseBase::GetContainer");
}

STDMETHODIMP CTRiASDatabaseBase::ShowObject()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASDatabaseBase::ShowObject");
}

STDMETHODIMP CTRiASDatabaseBase::OnShowWindow (BOOL fShow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASDatabaseBase::OnShowWindow");
}

STDMETHODIMP CTRiASDatabaseBase::RequestNewObjectLayout()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CTRiASDatabaseBase::RequestNewObjectLayout");
}

///////////////////////////////////////////////////////////////////////////////
// Supporting functions

// umbenennen einer Datenbank
HRESULT CTRiASDatabaseBase::RenameDatabase (IMoniker *pIMk)
{
	USES_CONVERSION;
	RenamingDatabase();

	if (NULL == pIMk) return S_OK;

#if defined(_DEBUG)
// BoundsChecker hat Probleme mit dem folgenden Code, 
// also evtl. einfach weitermachen
CRegKey regCfg;
DWORD dwFlags = 0;

	if (ERROR_SUCCESS == regCfg.Open (HKEY_CURRENT_USER, TEXT("Software"), KEY_READ) &&
		ERROR_SUCCESS == regCfg.Open (regCfg, REG_COMPANY_KEY, KEY_READ) &&
		ERROR_SUCCESS == regCfg.Open (regCfg, REG_PRODUCT_KEY, KEY_READ) &&
		ERROR_SUCCESS == regCfg.Open (regCfg, TEXT("Config"), KEY_READ) &&
		ERROR_SUCCESS == regCfg.QueryValue (dwFlags, TEXT("FakeBoundChecker")) &&
		0 != dwFlags)
	{
		return S_OK;
	}
#endif
HRESULT hr = S_OK;

	_ASSERTE(0 == m_dwRegROT && 0 == m_dwRegROTAll);
	{
	FILETIME ft;

		CoFileTimeNow (&ft);
		m_FileMK = pIMk;
		hr = MkRegisterAsRunning(ROTFLAGS_REGISTRATIONKEEPSALIVE, GetUnknown(), 
			m_FileMK, &m_dwRegROT); 
		if (SUCCEEDED(hr))
			MkNoteChangeTime (m_dwRegROT, &ft);

	// give moniker to linked objects in tenants (InsideOLE S. 997)
	// ...

	// register a File!"\" wildcard moniker as well
	WMoniker mkAll;

		if (SUCCEEDED(CreateItemMoniker(L"!", L"\\", mkAll.ppi()))) {
		WMoniker mkWild;

			hr = m_FileMK -> ComposeWith (mkAll, false, mkWild.ppi());
			if (SUCCEEDED(hr)) 
				hr = MkRegisterAsRunning(ROTFLAGS_REGISTRATIONKEEPSALIVE, 
					GetUnknown(), mkWild, &m_dwRegROTAll);
			if (SUCCEEDED(hr))
				MkNoteChangeTime (m_dwRegROTAll, &ft);
		}
	}
	return S_OK;
}

// Datenbank soll umbenannt werden
HRESULT CTRiASDatabaseBase::RenamingDatabase (void)
{
	MkRevokeAsRunning (&m_dwRegROT);
	MkRevokeAsRunning (&m_dwRegROTAll);

	m_FileMK.Assign(NULL);

	m_dwRegROT = 0L;
	m_dwRegROTAll = 0L;
	return S_OK;
}

// Datenbank wurde gespeichert
HRESULT CTRiASDatabaseBase::DatabaseSaved (void)
{
	_ASSERTE(0 != m_dwRegROT && 0 != m_dwRegROTAll);

FILETIME ft;

	CoFileTimeNow (&ft);
	MkNoteChangeTime (m_dwRegROT, &ft);
	MkNoteChangeTime (m_dwRegROTAll, &ft);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// OleItemContainerSupport
// nach einer bestimmten Objektklasse fragen
HRESULT CTRiASDatabaseBase::GetObjectsDef (
	LPCTSTR pcItem, DWORD dwSpeedNeeded, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly)
{
	if (!m_ObjectsDefs) {
		if (BINDSPEED_IMMEDIATE == dwSpeedNeeded)
			return MK_E_EXCEEDEDDEADLINE;

	// evtl. Neuerzeugen der benötigten Collection
	WTRiASObjectsCollection Coll;

		RETURN_FAILED_HRESULT(get_ObjectsDefs (Coll.ppi()));	// fills in m_ObjectsDefs
	}
	_ASSERTE(m_ObjectsDefs.IsValid());

HRESULT hr = S_OK;

	COM_TRY {
	WTRiASObjects Objs;
		
		hr = m_ObjectsDefs -> Item (CComVariant(pcItem), Objs.ppi());
		if (TRIASDB_E_UNKNOWN_OBJECTS == hr && !fTestRunningOnly) {
		// Objektklasse ist neu und muß erzeugt werden
			if (BINDSPEED_IMMEDIATE == dwSpeedNeeded)
				return MK_E_EXCEEDEDDEADLINE;
			hr = m_ObjectsDefs -> Add (CComBSTR(pcItem), CComBSTR("TRiASDB.TRiASSimpleObjects.1"), Objs.ppi());
		}

		if (SUCCEEDED(hr) && !fTestRunningOnly && NULL != ppvObj)	// Objektklasse ist (jetzt) bekannt
		{
			_ASSERTE(Objs.IsValid());
			THROW_FAILED_HRESULT(Objs -> QueryInterface (riid, ppvObj));
		}
	} COM_CATCH;
	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// nach einem bestimmten Objekt fragen
HRESULT CTRiASDatabaseBase::GetObjectDef (
	LPCTSTR pcItem, DWORD dwSpeedNeeded, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly)
{
	if (BINDSPEED_IMMEDIATE == dwSpeedNeeded)	// muß immer in der GeoDB gesucht werden
		return MK_E_EXCEEDEDDEADLINE;

	COM_TRY {
	long lObject = 0L;
	CIID Guid (pcItem);

		if (!Guid) return E_FAIL;
		THROW_FAILED_HRESULT(CNativeObject::FindObjectFromGUID (m_hPr, Guid, &lObject));

	INT_PTR lIdent = 0L;
	DWORD dwType = 0L;

		if (0 != lObject) {
		CNativeObject Obj (m_hPr, lObject);

			Obj.GetIdent ((LONG *)&lIdent);		// Fehler ignorieren
			Obj.GetObjectType (&dwType);
		}

	WTRiASObjectHandleMap Map (GetProperty (GetProperties(), g_cbObjectMap, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab
	CInitializeSimpleObject InitObj (m_Application, (ITRiASDatabase *)this, lIdent, 0, BitsToOBJECTTYPE(dwType));
	WTRiASObject Object;
	INT_PTR hObj = NULL;	// Handle neu vergeben

		THROW_FAILED_HRESULT(FindInMapOrCreateObjectEx(Map, lObject, hObj, Object, CLSID_TRiASSimpleObject, InitObj));
		if (!fTestRunningOnly && NULL != ppvObj) 
		{
			THROW_FAILED_HRESULT(Object -> QueryInterface (riid, ppvObj));
		}

	} COM_CATCH;
	return S_OK;
}

// DisplayName parsen und Moniker liefern
HRESULT CTRiASDatabaseBase::ParseObjectsDef (
	LPCTSTR pcItem, ULONG ulSkipped, ULONG *pulEaten, IMoniker **ppmkOut)
{
CComBSTR bstrItem(pcItem);

	RETURN_FAILED_HRESULT(CreateItemMoniker (g_cbMkDel, bstrItem, ppmkOut));
	*pulEaten += bstrItem.Length();
	return S_OK;
}

HRESULT CTRiASDatabaseBase::ParseObjectDef (
	LPCTSTR pcItem, ULONG ulSkipped, ULONG *pulEaten, IMoniker **ppmkOut)
{
CComBSTR bstrItem(pcItem);

	RETURN_FAILED_HRESULT(CreateItemMoniker (g_cbMkDel, bstrItem, ppmkOut));
	*pulEaten += bstrItem.Length();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASPropertyEvents
STDMETHODIMP CTRiASDatabaseBase::CreatingProperty (BSTR Name, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::PropertyToCreate (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::PropertyCreated (IDispatch *pIProp)
{
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::ModifyingProperty (BSTR Name, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::PropertyToModify (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::PropertyModified (BSTR Name)
{
	if (!wcscmp (Name, g_cbTRiASCSTransform) && !IsSemaphoreSignaled (m_lSemModCTF, *this)) 
		return InitCoordSystemService();	// Koordinatensystem verändert

	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::DeletingProperty (BSTR Name, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::PropertyToDelete (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::PropertyDeleted (BSTR Name)
{
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Koordinatensystem neu initialisieren
HRESULT CTRiASDatabaseBase::InitCoordSystemService()
{
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);

GUID *pGuids = NULL;

	COM_TRY {
	WTRiASPropertyBase PropBase(this);
	CCSFactory CSService;
	WTRiASCS CS;

	long lCnt = 0;

		THROW_FAILED_HRESULT(::GetGeometryGuids(m_hPr, &lCnt, &pGuids));
		_ASSERTE(0 < lCnt);

	// CTF-Service holen/initialisieren
	WTRiASCSTransform CST (GetProperty (GetProperties(), g_cbTRiASCSTransform, (IDispatch *)NULL), false);

		if (!CST.IsValid()) {
		// neuen CTF-Service erzeugen und als Property speichern
			CST = WTRiASCSTransform(CLSID_TRiASCSTransform);

			THROW_FAILED_HRESULT(CSService.RetrieveCS (PropBase, CS.ppi()));
//#if defined(_DEBUG)
//			{
//				USES_CONVERSION;
//
//			os_path strT = string(OLE2A(m_bstrName));
//
//				strT.extension("tcf");
//				THROW_FAILED_HRESULT(CS->SaveToFile(A2OLE(string(strT).c_str())));
//			}
//#endif // defined(_DEBUG)

			if (lCnt > 0) {
			CIID Guid(*pGuids);

				THROW_FAILED_HRESULT(CS -> put_GUID (CComBSTR(Guid)));
			}
			THROW_FAILED_HRESULT(CST -> AddInputCS (CS));

		CComSemaphore<_ThreadModel> Sem (m_lSemModCTF);		// endlose Rekursion verhindern
		
			THROW_FAILED_HRESULT(SetProperty (GetProperties(), g_cbTRiASCSTransform, CComVariant(CST), true));
		} 
		else {
		// bisheriges Coordsystem entfernen, neues erzeugen und hinzufügen
			_ASSERTE(lCnt > 0);

		CIID Guid(*pGuids);

			THROW_FAILED_HRESULT(CST -> RemoveInputCS (CComBSTR(Guid)));

			THROW_FAILED_HRESULT(CSService.RetrieveCS (PropBase, CS.ppi()));
			THROW_FAILED_HRESULT(CS -> put_GUID (CComBSTR(Guid)));

			THROW_FAILED_HRESULT(CST -> AddInputCS (CS));
		}

		CoTaskMemFree (pGuids);
		pGuids = NULL;		// doppeltes Freigeben verhindern

	// Ausgabesystem von der Connection holen (hat sich u.U. geändert)
	WTRiASConnection Conn;

		THROW_FAILED_HRESULT(FindSpecificParent (m_Parent, Conn.ppi()));

	WTRiASCS CSOut (GetPropertyFrom (WTRiASPropertyBase(Conn), g_cbTRiASCSService, (IDispatch *)NULL), false);

		_ASSERTE(CSOut.IsValid());	// muß bereits existieren
		THROW_FAILED_HRESULT(CST -> putref_OutputCS (CSOut));
		THROW_FAILED_HRESULT(CSOut -> Recompute());

	// unterliegende GeoDB auffordern Skalierungskoeffizienten neu einzulesen
		THROW_FAILED_HRESULT(ReReadScaleKoeffs (m_hPr));

	} COM_CATCH_OP(CoTaskMemFree(pGuids));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Koordinatensystem freigeben
HRESULT CTRiASDatabaseBase::ShutdownCoordSystemService()
{
	COM_TRY {
	WTRiASCSTransform CST (GetProperty (GetProperties(), g_cbTRiASCSTransform, (IDispatch *)NULL), false);

		if (CST.IsValid()) 
			return CST -> ShutDown();

	} COM_CATCH;
	return E_UNEXPECTED;
}

///////////////////////////////////////////////////////////////////////////////
// ConnectFilter initialisieren
HRESULT CTRiASDatabaseBase::InitConnectFilter()
{
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);

	COM_TRY {
	// ConnectFilter holen/initialisieren
	WTRiASConnection Parent;

		THROW_FAILED_HRESULT(FindSpecificParent(m_Parent, Parent.ppi()));

	WTRiASConnectionFilter ConnFilt (GetPropertyFrom(WTRiASPropertyBase(Parent), 
		g_cbTRiASConnectFilter, (IDispatch *)NULL), false);

		THROW_FAILED_HRESULT(put_ConnectionFilter(NULL));			// Reset only
		if (ConnFilt.IsValid()) {
			THROW_FAILED_HRESULT(put_ConnectionFilter(ConnFilt));
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CTRiASDatabaseOnStg::GetClassID (CLSID *pClassID)
{
	*pClassID = CLSID_TRiASDatabaseOnStg;
	return S_OK;
}

// IPersistStorage
STDMETHODIMP CTRiASDatabaseOnStg::IsDirty ()
{
BOOL fIsDirty = FALSE;

	::IsDirty(m_hPr, &fIsDirty);
	return fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CTRiASDatabaseOnStg::InitNew (IStorage *pIStg)
{
	m_StgMode = STGMODE_Normal;
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseOnStg::Load (IStorage *pIStg)
{
	m_StgMode = STGMODE_Normal;
	return S_OK;
}

// SubStorage einer Datenquelle besorgen
HRESULT CTRiASDatabaseOnStg::GetSubStorage (BSTR bstrName, IStorage *pIStgBase, IStorage **ppIStg, BOOL fCreate)
{
	_ASSERTE(NULL != ppIStg);
	COM_TRY {
	WTRiASProject Prj;

		THROW_FAILED_HRESULT(FindSpecificParent (GetDispatch(), Prj.ppi()));

	DWORD dwMode = 0;
	VARIANT_BOOL fUpdatable = VARIANT_FALSE;

		THROW_FAILED_HRESULT(Prj -> get_Updatable (&fUpdatable));
		if (fUpdatable)
			dwMode = STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED;
		else
			dwMode = STGM_READ|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED;

	// zuerst versuchen, existierendes Storage zu eröffnen
	HRESULT hr = pIStgBase -> OpenStorage (bstrName, NULL, dwMode, NULL, 0L, ppIStg);

		if (FAILED(hr) && fCreate) {
		// Storage erzeugen
			THROW_FAILED_HRESULT(hr = pIStgBase -> CreateStorage (bstrName, dwMode | STGM_CREATE, 0, 0, ppIStg));

		DWORD rgStgc = STGC_DEFAULT;
			
			if (IsWin50() && IsWinNT()) rgStgc |= STGC_CONSOLIDATE;
			THROW_FAILED_HRESULT(pIStgBase -> Commit (rgStgc));
		
			THROW_FAILED_HRESULT(Prj -> put_Dirty (VARIANT_TRUE));		// globales Commit erzwingen
		}
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseOnStg::Save (IStorage *pIStg, BOOL fSameAsLoad)
{
	_ASSERTE(STGMODE_Normal == m_StgMode);
	COM_TRY {
		if (fSameAsLoad) {
		// DB aktivieren
		CActDB Act (m_hPr);

			THROW_FAILED_HRESULT(SaveMetaDatabase());			// Pbd Speichern
			THROW_FAILED_ERRCODE(DBFlush(m_hPr, FLUSH_ACTDB));	// Datenbank speichern							// alles wegschreiben
			THROW_FAILED_ERRCODE(DBPageZeroFlush(m_hPr, FLUSH_ACTDB|FLUSH_COMMITDATA));		// PageZero's auch wegschreiben

			::SetDirty (m_hPr, FALSE);

		} else {
		// umkopieren der gesamten Datenquelle ins neue Storage
		WStorage Stg, PbdStg;

			_ASSERTE(NULL != pIStg);
			THROW_FAILED_HRESULT(GetSubStorage (m_bstrName, pIStg, Stg.ppi(), TRUE));
		
		IStorage *pIStgT = Stg;
			
			THROW_FAILED_HRESULT(CopyToStorageProject (m_hPr, NULL, &pIStgT, NULL, NULL));
			THROW_FAILED_HRESULT(GetSubStorage (CComBSTR(g_cbMetaData), Stg, PbdStg.ppi(), TRUE));

			pIStgT = PbdStg;
			THROW_FAILED_HRESULT(CopyToStorageProject (m_hPrPbd, NULL, &pIStgT, &CLSID_TRiASMetaDocument, "TRiAS.MetaDocument.2"));

		HRESULT hr = S_OK;
		DWORD rgStgc = STGC_DEFAULT;
			
			if (IsWin50() && IsWinNT()) rgStgc |= STGC_CONSOLIDATE;
			if (FAILED(hr = PbdStg -> Commit (rgStgc))) {
			// Plattenplatz reicht nicht
				USES_CONVERSION;
				PbdStg.Assign(NULL);							// freigeben
				Stg -> DestroyElement (A2OLE(g_cbMetaData));	// und löschen
				return hr;
			}
			THROW_FAILED_HRESULT(Stg -> Commit (rgStgc));
		}
		m_StgMode = STGMODE_NoScribble;

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseOnStg::SaveCompleted (IStorage *pIStg)
{
	if (STGMODE_Normal == m_StgMode)
		return E_UNEXPECTED;
	_ASSERTE(STGMODE_NoScribble == m_StgMode || (STGMODE_HandsOff & m_StgMode));

HRESULT hr = S_OK;

	COM_TRY {
		if (NULL == pIStg) {
			if (STGMODE_HandsOff & m_StgMode) 
				return E_POINTER;

		} else {
		// etvl. HandsOffStorage simulieren
			if (STGMODE_NoScribble == m_StgMode)
				THROW_FAILED_HRESULT(CTRiASDatabaseOnStg::HandsOffStorage());

		// Datenbank wieder öffnen
		WStorage Stg;

			THROW_FAILED_HRESULT(GetSubStorage (m_bstrName, pIStg, Stg.ppi()));

			hr = Open (NULL, Stg, m_fIsReadOnly, &m_hPr);
			if (SUCCEEDED(hr) && NULL != m_hPr) {
				THROW_FAILED_HRESULT(OpenMetaDatabase());		// Pbd dazu eröffnen
				THROW_FAILED_HRESULT(CreatePropertiesCollection());
			}
		}
	} COM_CATCH;

	::SetDirty (m_hPr, FALSE);
	m_StgMode = STGMODE_Normal;
	return hr;
}

STDMETHODIMP CTRiASDatabaseOnStg::HandsOffStorage (void)
{
// Pbd schließen
BOOL fOpened = TRUE;
HRESULT hr = S_OK;
ErrCode RC;

	_ASSERTE(::IsOpened (m_hPrPbd, &fOpened));
	if (fOpened && NULL != m_hPrPbd) {
	CActDB ActDB (m_hPrPbd);

		RC = (ErrCode)z_close (m_hPrPbd, false);	// PBD schließen, Fehler nicht fatal
		if (EC_OKAY != RC)
			hr = HRESULT_FROM_ERRCODE(RC);
		m_hPrPbd = NULL;
		ActDB.Reset();
	} else
		m_hPrPbd = NULL;

// Datenbank schließen
	_ASSERTE(::IsOpened (m_hPr, &fOpened));
	if (fOpened && NULL != m_hPr) {
	CActDB ActDB (m_hPr);

		RC = (ErrCode)z_close (m_hPr, false);	// DB schließen
		if (EC_OKAY != RC)
			hr = HRESULT_FROM_ERRCODE(RC);
		m_hPr = NULL;
		ActDB.Reset();
	} else
		m_hPr = NULL;

	if (STGMODE_Normal == m_StgMode)
		m_StgMode = STGMODE_HandsOffAfterNormal;
	else if (STGMODE_NoScribble == m_StgMode)
		m_StgMode = STGMODE_HandsOffAfterSave;
	else {
		_ASSERTE(STGMODE_NoScribble == m_StgMode || STGMODE_Normal == m_StgMode);
	}
	return hr;
}

