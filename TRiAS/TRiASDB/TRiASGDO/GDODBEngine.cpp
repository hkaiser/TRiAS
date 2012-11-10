// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.02.2000 15:35:27 
//
// @doc
// @module GDODBEngine.cpp | Declaration of the <c CGDODBEngine> class

#include "stdafx.h"
#include "TRiASGDOImpl.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#include "GDODBEngine.h"

#define CHECK_DBENGINE_STARTED()	if(!m_bStarted) { return TRIASDB_E_NOT_STARTED; }

///////////////////////////////////////////////////////////////////////////////
// globale Instanz
CGDODBEngine *g_pDBEngine = NULL;

///////////////////////////////////////////////////////////////////////////////
//

IMPLEMENT_DEBUG_FUNCENTRY_0(CGDODBEngine,FinalConstruct) {
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_0(CGDODBEngine,FinalRelease) {
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert die Version des unterliegenden Datenbanksystems
IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODBEngine,get_Version,BSTR *, pVal) {
	CHECKINPOINTER( pVal );
	CHECK_DBENGINE_STARTED();
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
		CComBSTR	strVersion;
		ERROR_FAILED_HRESULT( strVersion.LoadString(IDS_APP_VERSION_STRING), E_FAIL );
		*pVal = strVersion.Detach();
	} COM_CATCH
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Setzt Nutzername und Password für nachfolgende Aktivitäten (optional)
IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODBEngine,put_UserName,BSTR,newVal) {
	CHECK_DBENGINE_STARTED();
	FUNC_NOT_IMPL();
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODBEngine,put_Password,BSTR, newVal) {
	CHECK_DBENGINE_STARTED();
	FUNC_NOT_IMPL();
}

///////////////////////////////////////////////////////////////////////////////
// Liefert etwas ausführlichere Beschreibung (für UI)
IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODBEngine,get_Description,BSTR*, pVal) {
	CHECKINPOINTER(pVal);
	CHECK_DBENGINE_STARTED();
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
		CComBSTR	strDescription;
		ERROR_FAILED_HRESULT( strDescription.LoadString(IDS_DBENGINE_DESC), E_FAIL );
		*pVal = strDescription.Detach();
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Methods

///////////////////////////////////////////////////////////////////////////////
// Startet das unterliegende Datenbanksystem, wird einmal am Anfang gerufen,
// nach dem alle Randbedingungen eingestellt sind.

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODBEngine,Start,/*[in]*/ STARTMODE, Mode) 
{
	COM_TRY {
	CIID clsid (_T("GDOServerRegEntries"), CIID::INITCIID_InitFromProgId);
	WDGDOServerRegEntries dataServers;
	HRESULT hr = dataServers.CreateInstance (clsid);

		if (FAILED(hr)) return hr;

	// lokale singletons instantiieren
		m_pDGMGeometryStorageService = WDGMGeometryStorageService(CLSID_GeometryStorageService);
		m_pDGMServerTransService = WDGMServerTransService(CLSID_ServerTransService);

		g_pDBEngine = this;		// globale Instanz hier speichern

		m_bStarted = true;

	} COM_CATCH
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Stoppt das unterliegende Datenbanksystem, wird einmal am Ende gerufen.
IMPLEMENT_DEBUG_FUNCENTRY_0(CGDODBEngine,Stop) 
{
	CHECK_DBENGINE_STARTED();
	m_pDGMGeometryStorageService.Assign(NULL);
	m_pDGMServerTransService.Assign(NULL);

	g_pDBEngine = NULL;

	m_bStarted = false;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert Enumerator, der die ProgID's aller bekannten Projekttypen enthält
// (z.B. 'Access.GDatabase').
// Rückgabewert ist ein IEnumString, der hier als IUnknown getarnt ist, damit
// die Funktion [oleautomation] - kompatibel ist

//#include <Com/EnumVariantIterators.h>
//typedef __InEnumIterator<VARIANT, DGDOServerRegEntries> InEnumServers;

typedef vector<CComBSTR> vectorOfOLEStrings;

//class StoreDataServer 
//{
//private:
//	vectorOfOLEStrings&	m_rServers;
//
//public:
//	StoreDataServer( vectorOfOLEStrings& rServers )
//		: m_rServers(rServers)
//	{
//	}
//	void operator()( VARIANT& _v ) 
//	{
//	CComVariant	v(_v);
//
//		THROW_FAILED_HRESULT( v.ChangeType( VT_DISPATCH ) );
//
//	WDGDOServerRegEntry dataServer (V_DISPATCH(&v));
//	CComBSTR strServerName;
//
//		if( S_OK == dataServer->get_DatabaseClass( CLEARED(strServerName) ) ) {
//			m_rServers.push_back( strServerName.Detach() );
//		}
//	}
//};
	
IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODBEngine,EnumDataBaseTypes,IUnknown**,ppIEnum) 
{
	CHECKOUTPOINTER( ppIEnum );
	CHECK_DBENGINE_STARTED();
	COM_TRY {
	CIID clsid (_T("GDOServerRegEntries"), CIID::INITCIID_InitFromProgId);
	WDGDOServerRegEntries dataServers;
	HRESULT hr = dataServers.CoCreateInstance (clsid);
	
		if (FAILED(hr)) return hr;

	vectorOfOLEStrings		arrServerNames;
//		StoreDataServer			storer(arrServerNames);
//		for_each( InEnumServers(dataServers), InEnumServers(), storer );

	WDGDOServerRegEntry		dataServer;
	WEnumVARIANT			srvEnum;
	CComVariant				v;

		hr = dataServers -> _NewEnum (srvEnum.ppu());
		for (srvEnum->Reset(); S_OK == (hr = srvEnum->Next (1, CLEARED(v), NULL)); /**/) {
			hr = v.ChangeType(VT_DISPATCH);
			dataServer = V_DISPATCH(&v);
		
		CComBSTR strServerName;
		
			if (S_OK == dataServer -> get_DatabaseClass (CLEARED(strServerName))) 
				arrServerNames.push_back (strServerName);
		}

		if (arrServerNames.size()) {
		WGDODBEngine pEngine(this);
		CComObject<CEnumString> *pIEnum = NULL;
		
			ATLTRY(pIEnum = new CComObject<CEnumString>());		// AddRef ist noch 0
			ERROR_EXPR_TRUE(NULL == pIEnum, E_OUTOFMEMORY);
			hr = pIEnum -> Init ((BSTR *)arrServerNames.begin(), (BSTR *)arrServerNames.end(), pEngine, AtlFlagCopy);
			if (SUCCEEDED(hr))
				hr = pIEnum -> QueryInterface(IID_IEnumString, (LPVOID *)ppIEnum);
			if (FAILED(hr))		// bei Fehler alles freigeben
				delete pIEnum;
		}

	} COM_CATCH;
	return S_OK;
}
