// DatabaseBase.cpp : Implementation of CDatabaseBase
#include "stdafx.h"
#include <afxdlgs.h>

#include "Wrapper.h"

#include "PDB.h"
#include "TRiASImport.h"
#include "DatabaseBase.h"

#include <ComCat.h>
#include "TrCatIDs.h"
#include "CIID.h"

#include "Helper.h"
#include "Strings.h"
#include "IXtensn.hxx"

#include "DlgImportOpt.h"

//const IID IID_ITriasXtension  = {0x07963802,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
//const IID IID_ITriasXtension2 = {0x07963814,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
//const IID IID_IImportGeoData  = {0x07963805,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
const CLSID CLSID_ParseStringPairs = {0xC21AAF96,0x2DE5,0x11D1,{0x96,0x9A,0x00,0xA0,0x24,0xD6,0xF5,0x82}};

/////////////////////////////////////////////////////////////////////////////
// CDatabaseBase

STDMETHODIMP CDatabaseBase::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASDatabase,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Properties dieses Objektes
STDMETHODIMP CDatabaseBase::get_Application(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//	if (NULL == pVal) 
//		return REPORT_DBERROR_ROUT(TRIASIMP_E_INVALID_PARAMETER, "CDatabaseBase::get_Application");

	*pVal = m_Application;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CDatabaseBase::put_Application(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Application = newVal;
	return S_OK;
}

STDMETHODIMP CDatabaseBase::get_Parent(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//	if (NULL == pVal) 
//		return REPORT_DBERROR_ROUT(TRIASIMP_E_INVALID_PARAMETER, "CDatabaseBase::get_Application");

	*pVal = m_Parent;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CDatabaseBase::put_Parent(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Parent = newVal;
	return S_OK;
}

STDMETHODIMP CDatabaseBase::get_TemporaryName(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::get_TemporaryName");
}

STDMETHODIMP CDatabaseBase::get_Temporary(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::get_Temporary");
}

STDMETHODIMP CDatabaseBase::put_Temporary(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::put_Temporary");
}

// Methoden
STDMETHODIMP CDatabaseBase::CreateDatabaseFromFiles(IUnknown *Name, BSTR Locale)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::CreateDatabaseFromFiles");
}

STDMETHODIMP CDatabaseBase::CreateDatabase(BSTR Name, BSTR Locale)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::CreateDatabase");
}

STDMETHODIMP CDatabaseBase::BeginTrans (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::BeginTrans");
}

STDMETHODIMP CDatabaseBase::CommitTrans (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::CommitTrans");
}

STDMETHODIMP CDatabaseBase::ClearModificationLog (LONG Entry)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::ClearModificationLog");
}

STDMETHODIMP CDatabaseBase::Close()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::Close");
}

STDMETHODIMP CDatabaseBase::CreateInstance( IUnknown *pUnkOuter, REFCLSID rClsID, REFIID riid,/*[out, iid_is(riid)]*/void **ppvObj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//	ATLTRACENOTIMPL("CDatabaseBase::CreateInstance");
//	CoCreateInstance(rclsid, pUnkOuter, dwClsContext, riid, ppvObj);
	return CoCreateInstance( rClsID, pUnkOuter, CLSCTX_INPROC_SERVER, riid, ppvObj);
}

STDMETHODIMP CDatabaseBase::GetXtension( REFCLSID rClsID, REFIID riid,/*[out, iid_is(riid)]*/void **ppvObj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//	ATLTRACENOTIMPL("CDatabaseBase::GetXtension");
//	CoCreateInstance(rclsid, pUnkOuter, dwClsContext, riid, ppvObj);
	return CoCreateInstance( rClsID, NULL, CLSCTX_INPROC_SERVER, riid, ppvObj);
}



/////////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CDatabaseBase::get_Name(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
/*
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASIMP_E_DATABASE_NOT_OPENED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASIMP_E_INVALID_PARAMETER, "CDatabaseBase::get_Name");

CComBSTR bstrName (m_bstrName);

	if (!bstrName)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

	*pVal = bstrName.Detach();
	return S_OK;
*/
	ATLTRACENOTIMPL("CDatabaseBase::get_Name");
}

STDMETHODIMP CDatabaseBase::get_CollatingOrder (long *pCollatingOrder)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::get_CollatingOrder");
}

STDMETHODIMP CDatabaseBase::get_Connect (BSTR *Connect)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::get_Connect");
}

STDMETHODIMP CDatabaseBase::get_Handle(LONG * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::get_Handle");
}

STDMETHODIMP CDatabaseBase::get_IsDirty(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::get_IsDirty");
}

STDMETHODIMP CDatabaseBase::get_Updatable(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//	if (NULL == m_hPr)
//		return REPORT_DBERROR(TRIASIMP_E_DATABASE_NOT_OPENED);
//	if (NULL == pVal)
//		return REPORT_DBERROR_ROUT(TRIASIMP_E_INVALID_PARAMETER, "CDatabaseBase::get_Updatable");

// diese Datenbank ist prinzipiell nicht beschreibbar
	*pVal = VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CDatabaseBase::get_Type(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::get_Type");
}

STDMETHODIMP CDatabaseBase::get_SchemaUpdatable(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
/*
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASIMP_E_DATABASE_NOT_OPENED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASIMP_E_INVALID_PARAMETER, "CDatabaseBase::get_SchemaUpdatable");

	*pVal = VARIANT_FALSE;		// für Import-DB's auch immer false
	return S_OK;
*/
	ATLTRACENOTIMPL("CDatabaseBase::get_SchemaUpdatable");
}

STDMETHODIMP CDatabaseBase::get_Transactions (VARIANT_BOOL *Transactions)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
/*
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASIMP_E_DATABASE_NOT_OPENED);
	if (NULL == Transactions)
		return REPORT_DBERROR_ROUT(TRIASIMP_E_INVALID_PARAMETER, "CDatabaseBase::get_Transactions");

	*Transactions = VARIANT_FALSE;
	return S_OK;
*/
	ATLTRACENOTIMPL("CDatabaseBase::get_Transactions");
}

STDMETHODIMP CDatabaseBase::get_Version (BSTR *Version)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
/*
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASIMP_E_DATABASE_NOT_OPENED);
	if (NULL == Version)
		return REPORT_DBERROR_ROUT(TRIASIMP_E_INVALID_PARAMETER, "CDatabaseBase::get_Version");

long lV = ::GetDBVersion(m_hPr);
TCHAR cbBuffer[64];

	wsprintf (cbBuffer, "%ld.%ld.%ld", 
		HIBYTE(HIWORD(lV)), LOBYTE(HIWORD(lV)), LOBYTE(LOWORD(lV)));

CComBSTR bstr (cbBuffer);

	if (!bstr) 
		return Error (g_cbNoMemory, E_OUTOFMEMORY);
	*Version = bstr.Detach();		
	return S_OK;
*/
	ATLTRACENOTIMPL("CDatabaseBase::get_Version");
}

STDMETHODIMP CDatabaseBase::get_VersionLong(LONG * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
/*
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASIMP_E_DATABASE_NOT_OPENED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASIMP_E_INVALID_PARAMETER, "CDatabaseBase::get_VersionLong");

	*pVal = ::GetDBVersion(m_hPr);
	return S_OK;
*/
	ATLTRACENOTIMPL("CDatabaseBase::get_VersionLong");
}

STDMETHODIMP CDatabaseBase::OpenDatabase(
	BSTR Name, VARIANT_BOOL /*Exclusive*/, VARIANT_BOOL fReadOnly, 
	VARIANT_BOOL /*ModTrack*/, BSTR Source)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//	ATLTRACENOTIMPL("CDatabaseBase::OpenDatabase");

	HRESULT		hRes;

	if ( S_OK != ( hRes = LoadImportExtension( Source )))
		return hRes;

	hRes = ImportData( Name );

	UnLoadImportExtension();
	return hRes;
}

HRESULT CDatabaseBase::EnumFileNames( BSTR name, IUnknown **ppIEnum )
{
// Zeiger umkopieren, damit ein zusammenhängender Vektor entsteht,
// dazu auf dem Stack den Speicher anfordern (gibt sich selbst frei!)
CComBSTR	bstrName( name  );
LPOLESTR *ppStrs = (LPOLESTR*)alloca(sizeof(LPOLESTR) * 2);

	USES_CONVERSION;
	ppStrs[0] = bstrName.Detach();		// nutzt ebenfalls alloca()

// Enumeratorobjekt anlegen und füllen
CComObject<CEnumString> *pIEnum = NULL;

	ATLTRY(pIEnum = new CComObject<CEnumString>());		// AddRef ist noch 0
//	if (NULL == pIEnum) return Error (g_cbNoMemory, E_OUTOFMEMORY);

// die Funktion Init des EnumTemplates erwartet die Adressen des ersten und 
// letzten+1 Elementes eines Vektors
HRESULT hr = pIEnum -> Init ((LPOLESTR *)&ppStrs[0], (LPOLESTR *)&ppStrs[1], (IDispatch *)this, AtlFlagCopy);

	if (SUCCEEDED(hr))
		hr = pIEnum -> QueryInterface(IID_IEnumString, (LPVOID *)ppIEnum);

	if (FAILED(hr))		// bei Fehler alles freigeben
		delete pIEnum;

	return hr;
}

STDMETHODIMP CDatabaseBase::OpenFilesAsDatabase(
	IUnknown *pIEnum, VARIANT_BOOL /*Exclusive*/, VARIANT_BOOL fReadOnly, 
	VARIANT_BOOL /*ModTrack*/, BSTR Source)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//	ATLTRACENOTIMPL("CDatabaseBase::OpenFilesAsDatabase");

	HRESULT		hRes;

	if ( S_OK != ( hRes = LoadImportExtension( Source )))
		return hRes;

	hRes = ImportData( pIEnum );

	UnLoadImportExtension();
	return hRes;
}

STDMETHODIMP CDatabaseBase::put_IsDirty(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
/*
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASIMP_E_DATABASE_NOT_OPENED);

	m_fIsDirty = newVal ? true : false;
	return S_OK;
*/
	ATLTRACENOTIMPL("CDatabaseBase::put_IsDirty");
}

STDMETHODIMP CDatabaseBase::Rollback (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::Rollback");
}

/////////////////////////////////////////////////////////////////////////////
// PropertySupport
// Callback-interface, welches für die Konkretheit der Properties zuständig ist

STDMETHODIMP CDatabaseBase::get_Properties(ITRiASProperties * * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::get_Properties");
/*
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr) 
		return REPORT_DBERROR(TRIASIMP_E_PROJECT_NOT_OPENED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASIMP_E_INVALID_PARAMETER, "CDatabaseBase::get_Properties");

	return m_Properties -> _Clone (pVal);
*/
}

STDMETHODIMP CDatabaseBase::get_Property(BSTR Which, ITRiASProperty * * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::get_Property");
/*
	if (NULL == m_hPr) 
		return REPORT_DBERROR(TRIASIMP_E_PROJECT_NOT_OPENED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASIMP_E_INVALID_PARAMETER, "CDatabaseBase::get_Property");

CComVariant vWhich (Which);

	return m_Properties -> Item (vWhich, pVal);
*/
}

STDMETHODIMP CDatabaseBase::CreateProperty (BSTR Name, ITRiASProperty **Property)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::CreateProperty");
/*
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASIMP_E_DATABASE_NOT_OPENED);
	if (NULL == Property)
		return REPORT_DBERROR_ROUT(TRIASIMP_E_INVALID_PARAMETER, "CDatabaseBase::CreateProperty");

	try {
	// Events vorher
	VARIANT_BOOL fVal = VARIANT_FALSE;
		
		THROW_FAILED_HRESULT(Fire_CreatingProperty (Name, &fVal)); 
		if (VARIANT_TRUE == fVal)
			return S_FALSE;
		THROW_FAILED_HRESULT(Fire_PropertyToCreate (Name));

	// eigentliche Aktion
	CComObject<CTRiASProperty> *pNew = NULL;

		THROW_FAILED_HRESULT(CComObject<CTRiASProperty>::CreateInstance (&pNew));
		THROW_FAILED_HRESULT(pNew -> put_Name (Name));

	WTRiASPropertySupport Supp;

		THROW_FAILED_HRESULT(GetPropertySupportSite (Name, GetUnknown(), Supp.ppi()));
		THROW_FAILED_HRESULT(pNew -> SetPropertySupportSite (Supp));

	WTRiASProperty Prop (pNew);		// required AddRef;

		*Property = Prop.detach();

	// Events hinterher
		THROW_FAILED_HRESULT(Fire_PropertyCreated (*Property));

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
*/
}

STDMETHODIMP CDatabaseBase::RemoveProperty (BSTR Name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::RemoveProperty");
/*
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASIMP_E_DATABASE_NOT_OPENED);
	if (NULL == Name)
		return REPORT_DBERROR_ROUT(TRIASIMP_E_INVALID_PARAMETER, "CDatabaseBase::RemoveProperty");

	USES_CONVERSION;
	try {
	// Events vorher
	VARIANT_BOOL fVal = VARIANT_FALSE;
		
		THROW_FAILED_HRESULT(Fire_DeletingProperty (Name, &fVal)); 
		if (VARIANT_TRUE == fVal)
			return S_FALSE;
		THROW_FAILED_HRESULT(Fire_PropertyToDelete (Name));

	// eigentliche Aktion
	CActDB ActDB (m_hPr);
	CDBHeader DBProp (m_hPr, OLE2A(Name));

		THROW_FAILED_HRESULT(DBProp.DeleteHeaderEntry()); 

	// Event hinterher
		THROW_FAILED_HRESULT(Fire_PropertyDeleted (Name));

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
*/
}

STDMETHODIMP CDatabaseBase::Save()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::Save");
/*
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASIMP_E_DATABASE_NOT_OPENED);

// alle internen Daten dieser Datenbank wegschreiben
	if (m_fIsDirty) {
		try {
		// Pbd Speichern
			THROW_FAILED_HRESULT(SaveMetaDatabase());

		// alle internen Buffer leeren
		ErrCode RC = EC_OKAY;
		CActDB ActDB (m_hPr);

			RC = (ErrCode)DBFlush (m_hPr, FLUSH_ACTDB);		// alles wegschreiben
			if (EC_OKAY != RC) _com_issue_error(HRESULT_FROM_ERRCODE(RC));
			RC = (ErrCode)DBPageZeroFlush (m_hPr, FLUSH_ACTDB);		// PageZero's auch wegschreiben
			if (EC_OKAY != RC) _com_issue_error(HRESULT_FROM_ERRCODE(RC));

		// jetzt das Storage Commit'n
		WStorage Stg;

			THROW_FAILED_HRESULT(GetProjectStorage(Stg.ppi()));
			THROW_FAILED_HRESULT(Stg -> Commit (STGC_DEFAULT));

			m_fIsDirty = false;

		} catch (_com_error &e) {
			return _COM_ERROR(e);
		}
	}
	return S_OK;
*/
}

STDMETHODIMP CDatabaseBase::SaveAs(BSTR NewName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::SaveAs");
}

// Feststellen, ob diese Datei als Kopie eröffnet wurde
STDMETHODIMP CDatabaseBase::get_OpenedAsCopy(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::get_OpenedAsCopy");
/*
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASIMP_E_DATABASE_NOT_OPENED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASIMP_E_INVALID_PARAMETER, "CDatabase::get_OpenedAsCopy");

CActDB ActDB (m_hPr);
BOOL fIsCopy = FALSE;

	if (!::GetCopyMode (m_hPr, &fIsCopy))
		return REPORT_DBERROR(E_UNEXPECTED);

	*pVal = fIsCopy ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
*/
}

STDMETHODIMP CDatabaseBase::get_CouldOpenTarget(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::get_CouldOpenTarget");
/*
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASIMP_E_DATABASE_NOT_OPENED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASIMP_E_INVALID_PARAMETER, "CTRiASDatabase::get_OpenedAsCopy");

CActDB ActDB (m_hPr);
BOOL fCouldOpenTarget = FALSE;

	if (!::CouldOpenTarget (m_hPr, &fCouldOpenTarget))
		return REPORT_DBERROR(E_UNEXPECTED);

	*pVal = fCouldOpenTarget ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
*/
}


// ITRiASServiceProvider
STDMETHODIMP CDatabaseBase::DexExtensionProc (WPARAM wParam, LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//	ATLTRACENOTIMPL("CDatabaseBase::DexExtensionProc");

	HRESULT			hResult;

	switch ( wParam )
	{
	// DEX_ReadGeoDBHdrEntry(HE);
		case DEX_READHEADER:
			hResult = ReadHeader( lParam );
			break;
	// DEX_WriteGeoDBHdrEntry (HE);
		case DEX_MODIFYHEADER:
			hResult = ModifyHeader( lParam );
			break;
	// DEX_DeleteGeoDBHdrEntry (HE);
		case DEX_DELETEHEADER:
			hResult = DeleteHeader( lParam );
			break;
	// DEX_GetUniqueIdentMCode();
		case DEX_QUERYUNIQUEIDENTMCODE:
			hResult = (HRESULT)m_lUIDMCode;
			break;
	// DEX_GetIdBase();
		case DEX_QUERYIDENTBASE:
			hResult = (HRESULT)m_PDB.IdBase();
			break;
	// DEX_GetMkBase();
		case DEX_QUERYMCODEBASE:
			hResult = (HRESULT)m_PDB.MkBase();
			break;
	// DEX_FlushModifications();
		case DEX_FLUSHALLMODIFICATIONS:
			break;
	// DEX_GetProjectStorage( pIStorage );
		case DEX_QUERYPROJECTSTORAGE:
			break;
	// DEX_DeleteObject( onr );
		case DEX_DELOBJECT:
			break;
	// DEX_ModPBDData( *pbdm );
		case DEX_MODPBDDATA:
			hResult = ModPBDData( lParam );
			break;
	// DEX_GetPBDData( *pbd );
		case DEX_QUERYPBDDATA:
			hResult = QueryPBDData( lParam );
			break;
	// DEX_GetObjStatistik( *og );
		case DEX_QUERYOBJSTATISTIK:
			break;
	// DEX_GetObjGeometrie( *og );
		case DEX_QUERYOBJGEOMETRIE:
			break;
	// DEX_ModObjGeometrie( *og );
		case DEX_MODIFYOBJGEOMETRIE:
			break;
	// DEX_ModTextMerkmal( *m );
		case DEX_MODIFYMERKMAL:
			break;
		default:
			ATLTRACENOTIMPL("CDatabaseBase::DexExtensionProc");
			break;
	}

	return S_OK;
}

STDMETHODIMP CDatabaseBase::DexExtensionProc2 (HPROJECT hPr, WPARAM wParam, LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::DexExtensionProc2");
}

STDMETHODIMP CDatabaseBase::DexNotificationProc (WPARAM wParam, LPARAM lParam, BOOL fPost)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//	ATLTRACENOTIMPL("CDatabaseBase::DexNotificationProc");

	switch ( wParam )
	{
	// DEXN_ReReadContainer();
		case DEX_REREADCONTAINER:
			break;
	// DEXN_ReScale();
		case DEX_RESCALE:
			break;
	// DEXN_ReReadIdents();
		case DEX_REREADIDENTS:
			break;
	// DEXN_PBDIdentChanged( m_MMK );
		case DEX_TXICHANGED:
			break;
	// DEXN_PBDMCodeChanged( m_MMK );
		case DEX_TXMCHANGED:
			break;
		default:
			ATLTRACENOTIMPL("CDatabaseBase::DexNotificationProc");
			break;
	}

	return S_OK;
}

STDMETHODIMP CDatabaseBase::DexDispatchProc (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ATLTRACENOTIMPL("CDatabaseBase::DexDispatchProc");
}

STDMETHODIMP CDatabaseBase::LoadImportExtension( BSTR Source )
{
	// Im Parameter "Source" wird die zu nutzende ImportExtension in der Form
	// "TRiASDB;PROGID=[ProgID]" übergeben.
	//
	// Weiterhin enthält "Source" diverse optionale Parameter für den Import,
	// die durch den Nutzer auf der entsprechenden PropertyPage eingestellt
	// wurden.

	WParseStringPairs Parse (CLSID_ParseStringPairs);
	CComBSTR	bstrProgID, bstrFlag, bstrImpYes(g_cbImpYes);
	long		lPairs;

	THROW_FAILED_HRESULT(Parse -> put_Pattern(CComBSTR(g_cbCollatePattern)));
	THROW_FAILED_HRESULT(Parse -> Parse( Source, &lPairs ));
	THROW_FAILED_HRESULT(Parse -> get_Value (CComBSTR(g_cbProgID), &bstrProgID));

	m_dwImportFlags = 0;
	bstrFlag = g_cbNil;
	THROW_FAILED_HRESULT(Parse -> get_Value (CComBSTR(g_cbImpAnsiOEM), &bstrFlag));
	if ( 0 == wcscmp( bstrImpYes, bstrFlag ))	m_dwImportFlags |= IMPORTCAPS_OPTIMPORTANSIOEM;
	bstrFlag = g_cbNil;
	THROW_FAILED_HRESULT(Parse -> get_Value (CComBSTR(g_cbImpFeatures), &bstrFlag));
	if ( 0 == wcscmp( bstrImpYes, bstrFlag ))	m_dwImportFlags |= IMPORTCAPS_CANIMPORTFEATURES;
	bstrFlag = g_cbNil;
	THROW_FAILED_HRESULT(Parse -> get_Value (CComBSTR(g_cbImpGeometry), &bstrFlag));
	if ( 0 == wcscmp( bstrImpYes, bstrFlag ))	m_dwImportFlags |= IMPORTCAPS_CANIMPORTGEOMETRY;
	bstrFlag = g_cbNil;
	THROW_FAILED_HRESULT(Parse -> get_Value (CComBSTR(g_cbImpRelations), &bstrFlag));
	if ( 0 == wcscmp( bstrImpYes, bstrFlag ))	m_dwImportFlags |= IMPORTCAPS_CANIMPORTRELATIONS;
	bstrFlag = g_cbNil;
	THROW_FAILED_HRESULT(Parse -> get_Value (CComBSTR(g_cbImpVisualis), &bstrFlag));
	if ( 0 == wcscmp( bstrImpYes, bstrFlag ))	m_dwImportFlags |= IMPORTCAPS_CANIMPORTVISUALISATION;

/*
	CString		text;
	char		*txt;

	text = Source;
	txt = text.GetBuffer( 0 );
	while ( *txt && ( *txt != '=' ))	txt++;
	if ( *txt )		txt++;

	CComBSTR	bstrProgID( txt );
*/
	void*	pvObj = NULL;

	try {
	CIID clsID( bstrProgID, CIID::INITCIID_InitFromProgId );

		m_ImportXtension = WTriasXtension( clsID );		// throws hr

		WTriasXtension2		pTX2;

		TRIASLOADEX			tlx;
		HRESULT				hRes = S_OK;

		CWnd	*pWnd = AfxGetMainWnd();
		HWND	hWnd = NULL;
		HDEX	hDex = NULL;

		if ( pWnd != NULL )		hWnd = pWnd -> GetSafeHwnd();
		m_ImportXtension.QueryInterface( IID_ITriasXtension2, pTX2.ppv());

		if ( pTX2 )
			hRes = pTX2 -> SetXtensionSite( this );

		tlx.m_dwSize = sizeof( TRIASLOADEX );		// Größe dieser Struktur
		tlx.m_szMenuName[0] = '\0';		// Menutext im Menu des Hauptfensters 
		tlx.m_hMenu = NULL;				// MenuHandle
		tlx.m_wMenuDelta = 1000;		// MenuOffset
		tlx.m_fcDef = NULL;				// DefaultCallBack in <tr>
		tlx.m_szORMenuName[0] = '\0';	// Menutext für Objekt-Recherchefenster
		tlx.m_hORMenu = NULL;			// Menu für Objektrecherche
		tlx.m_iMode = LEFullLoad;		// AktivierungsMode

		if ( NULL == ( hDex = m_ImportXtension -> LoadExtension( &tlx, hWnd )))
			return E_FAIL;

		if ( !m_ImportXtension -> InitExtension( LEFullLoad ))
			return E_FAIL;

		// QueryInterface in EDBS-Import reagiert erst nach InitExtension richtig!
//		WImportGeoData		pIGD( m_ImportXtension );

/*		CDlgImportOpt	dlg( pWnd );

		dlg.m_bImpAnsiOEM   = m_bCanImpAnsiOEM;
		dlg.m_bImpFeatures  = m_bCanImpFeatures;
		dlg.m_bImpGeometry  = m_bCanImpGeometry;
		dlg.m_bImpRelations = m_bCanImpRelations;
		dlg.m_bImpVisu      = m_bCanImpVisu;
		dlg.m_bOptAnsiOEM   = m_bOptImpAnsiOEM;
		dlg.m_bOptFeatures  = m_bOptImpFeatures;
		dlg.m_bOptGeometry  = m_bOptImpGeometry;
		dlg.m_bOptRelations = m_bOptImpRelations;
		dlg.m_bOptVisu      = m_bOptImpVisu;
		dlg.m_bShouldConfig = m_bImpShouldConfig;
		dlg.m_ImportGeoData = pIGD;
		dlg.DoModal();

		dwImportFlags = 0;
		if ( dlg.m_bImpAnsiOEM )	dwImportFlags |= IMPORTCAPS_OPTIMPORTANSIOEM;
		if ( dlg.m_bImpFeatures )	dwImportFlags |= IMPORTCAPS_CANIMPORTFEATURES;
		if ( dlg.m_bImpGeometry )	dwImportFlags |= IMPORTCAPS_CANIMPORTGEOMETRY;
		if ( dlg.m_bImpRelations )	dwImportFlags |= IMPORTCAPS_CANIMPORTRELATIONS;
		if ( dlg.m_bImpVisu )		dwImportFlags |= IMPORTCAPS_CANIMPORTVISUALISATION;
		m_dwImportFlags = dwImportFlags;
*/
	} catch (_com_error &e) {
		m_ImportXtension.Assign(NULL);
		ASSERT(S_OK == _COM_ERROR(e));
//		return _COM_ERROR(e);
		return E_FAIL;
	}

	return S_OK;
}

#include "PBasic.h"
STDMETHODIMP CDatabaseBase::ImportData(IUnknown *pIEnum)
{
HRESULT		hr;

	try {
		CGMPoint *pPoint = new CGMPoint;
		pPoint -> SetX( 0 );
		pPoint -> SetY( 1 );
		delete pPoint;

		WImportGeoData		pIGD( m_ImportXtension );

		hr = pIGD -> ImportData((IEnumString*)pIEnum, m_dwImportFlags );
		if ( !SUCCEEDED(hr))
			return REPORT_DBERROR(TRIASIMP_E_DATABASE_NOT_OPENED);

	} catch (_com_error &e) {
//		m_ImportXtension.Assign(NULL);
		ASSERT(S_OK == _COM_ERROR(e));
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP CDatabaseBase::ImportData(BSTR Name)
{
	try {
CComObject<CEnumString> *pIEnum = NULL;
CComBSTR	bstrName( Name );
HRESULT		hr;

		hr = EnumFileNames( bstrName, (IUnknown**)&pIEnum );
		if (SUCCEEDED(hr))
		{
			ImportData( pIEnum );
			delete pIEnum;
		}

	} catch (_com_error &e) {
//		m_ImportXtension.Assign(NULL);
		ASSERT(S_OK == _COM_ERROR(e));
		return _COM_ERROR(e);
	}
	return S_OK;
}

BOOL CDatabaseBase::UnLoadImportExtension()
{
	m_ImportXtension -> UnLoadExtension();
	return TRUE;
}

HRESULT CDatabaseBase::ModPBDData(LPARAM lParam)
{
	PBDDATA		*pPBDDATA = NULL;
	PBDMERKMAL	*pPBDM = NULL;
	PBDRELATION	*pPBDR = NULL;

	if ( NULL == lParam )	return E_FAIL;
	if ( !AfxIsValidAddress((void*)lParam, sizeof( PBDDATA )))
		return E_FAIL;

	pPBDDATA = (PBDDATA*)lParam;
	if ( pPBDDATA -> dwSize == sizeof( PBDMERKMAL ))
		pPBDM = (PBDMERKMAL*)pPBDDATA;

	if ( NULL != pPBDDATA )
		if ( pPBDDATA -> dwSize == sizeof( PBDRELATION ))
			pPBDR = (PBDRELATION*)pPBDDATA;

	if (( NULL == pPBDM ) && ( NULL == pPBDR ))
		if ( pPBDDATA -> dwSize != sizeof( PBDDATA ))
			return E_FAIL;

	if ( NULL != pPBDDATA )
	{
//		DWORD dwSize;		// Größe dieser Struktur
//		short pbdTyp;		// Typ: 'i' - Identifikator, 'm' - Merkmal, 'r' - Relation
//		long pbdCode;		// interner Code
//		char *pbdKText;		// KurzText
//		char *pbdLText;		// LangText
//		short pbdTemp;		// Flag, ob temporär oder permanent (nur 'i')
//		short pbdKTextLen;	// max. Länge der Texte
//		short pbdLTextLen;
		if ( 'i' == pPBDDATA -> pbdTyp )
		{
		}
		if ( 'm' == pPBDDATA -> pbdTyp )
		{
		}
		if ( 'r' == pPBDDATA -> pbdTyp )
			return E_FAIL;	// PBD-Relation wird z.Z. nicht unterstützt
	}
	if ( NULL != pPBDM )
	{
		if ( !AfxIsValidAddress((void*)lParam, sizeof( PBDMERKMAL )))
			return E_FAIL;
//		DWORD dwSize;		// Größe dieser Struktur
//		short pbdTyp;		// 'm' - Merkmal
//		long pbdCode;		// interner Code
//		char *pbdKText;		// KurzText
//		char *pbdLText;		// LangText
//		short pbdReserved;	// unused
//		short pbdKTextLen;	// max. Länge der Texte
//		short pbdLTextLen;
//		short ipbdMTyp;		// MerkmalsTyp
//		short ipbdMLen;		// max. Länge des Merkmales

		return E_FAIL;		// PBD-Merkmal wird z.Z. nicht unterstützt
	}
	if ( NULL != pPBDR )
	{
		if ( !AfxIsValidAddress((void*)lParam, sizeof( PBDRELATION )))
			return E_FAIL;
//		DWORD dwSize;		// Größe dieser Struktur
//		short pbdTyp;		// Typ: 'r' - Relation
//		long pbdCode;		// interner Code
//		char *pbdKText;		// KurzText
//		char *pbdLText;		// LangText
//		short pbdReserved;	// unused
//		short pbdKTextLen;	// max. Länge der Texte
//		short pbdLTextLen;
//		short ipbdRTyp;		// RelationsTyp

		return E_FAIL;		// PBD-Relation wird z.Z. nicht unterstützt
	}

	return S_OK;
}

HRESULT CDatabaseBase::QueryPBDData(LPARAM lParam)
{
	return E_FAIL;
}

HRESULT CDatabaseBase::ReadHeader(LPARAM)
{
	return E_FAIL;
}

HRESULT CDatabaseBase::ModifyHeader(LPARAM)
{
	return E_FAIL;
}

HRESULT CDatabaseBase::DeleteHeader(LPARAM)
{
	return E_FAIL;
}
