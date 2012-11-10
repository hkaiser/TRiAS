// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
//
// @doc
// @module OpenNewPropertySheet.cpp | Implementation of the <c COpenNewPropertySheet> class

#include "fakemfcp.hxx"
#include "fakemfc.h"

#include <registrx.hxx>

#include <itoolbar.h>
#include <toolguid.h>
#include <dirisole.h>

#include "Wrapper.h"
#include "Strings.h"
#include "fakemfc.hxx"
#include "ConnectParams.h"
#include "OpenNewPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(CatInformation);
DefineSmartInterface(EnumGUID);
DefineSmartInterface(EnumString);

/////////////////////////////////////////////////////////////////////////////
// COpenNewPropertySheet

IMPLEMENT_DYNAMIC(COpenNewPropertySheet, CPropertySheet)

COpenNewPropertySheet::COpenNewPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_rgOpenMode = PROJECTOPENMODE_Unknown;
	m_rgCreateMode = CREATEMODE_Unknown;
	m_rgDatasource = DATASOURCEMODE_Unknown;

DWORD dwPos = IMG_GENERAL;

	ReadDataServerParams(dwPos);	// auf TRiAS 2.0 Database initialisieren
}

COpenNewPropertySheet::COpenNewPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_rgOpenMode = PROJECTOPENMODE_Unknown;
	m_rgCreateMode = CREATEMODE_Unknown;
	m_rgDatasource = DATASOURCEMODE_Unknown;

DWORD dwPos = IMG_GENERAL;

	ReadDataServerParams(dwPos);	// auf TRiAS 2.0 Database initialisieren
}

COpenNewPropertySheet::~COpenNewPropertySheet()
{
}

BEGIN_MESSAGE_MAP(COpenNewPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(COpenNewPropertySheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
//
HRESULT COpenNewPropertySheet::ReadDataServerParams (DWORD &rdwPos)
{
	return TxGetExtension() -> ReadDataServerParams (rdwPos, &m_Params, g_cbDefaultDataBase);
}

HRESULT COpenNewPropertySheet::HandleConnectString (void)
{
	if (!m_ExtPages && !m_Pairs)
		return S_FALSE;
	USES_CONVERSION;

CComBSTR bstrPairs;

	RETURN_FAILED_HRESULT(m_Pairs -> get_ComposedData (CComBSTR(g_cbPattern), CLEARED(&bstrPairs)));
	m_Params.m_strConnect = OLE2A(bstrPairs);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Zählen, wieviele Datenserver auf der nächsten Seite angezeigt werden sollen
long COpenNewPropertySheet::CountAvailableDataServers (void)
{
long lCount = 0;

// DBEngines über CATID enumerieren
	COM_TRY {
	// gecachte GUID's verwenden
	GUID guid;

		_ASSERTE(CFakeMFCExtension::s_DBEngineGUIDs.IsValid());
		for (CFakeMFCExtension::s_DBEngineGUIDs.Reset(); 
			 S_OK == CFakeMFCExtension::s_DBEngineGUIDs.Next (1, &guid, NULL); 
			 /**/)
		{
			if (CLASS_E_NOTLICENSED == CountAvailableDataServers (guid, lCount))
				CFakeMFCExtension::s_DBEngineGUIDs.RemoveActiveItem();
		}
	
	// alles, was nicht (wirklich) gebraucht wird, wieder rauswerfen
		::CoFreeUnusedLibraries();

	} COM_CATCH_RETURN(0);
	return lCount;
}

HRESULT COpenNewPropertySheet::CountAvailableDataServers (REFGUID rGuid, 
	long &rlCount)
{
LPOLESTR poleStr = NULL;

	USES_CONVERSION;
	try {
	// DBEngine instantiieren und nach EnumString fragen
	WTRiASDBEngine DBEng; 
	WUnknown Unk;
	WEnumString EnumStr;
	HRESULT hr = S_OK, hr_global = HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	bool fFound = false;
	
		hr = DBEng.CreateInstance(rGuid);
		if (FAILED(hr)) return hr;		// ggf. nicht instantiierbar (z.B. lizensiert)

	// jetzt eigentliche Dataserver durchgehen
		THROW_FAILED_HRESULT(DBEng -> EnumDataBaseTypes (Unk.ppi()));
		EnumStr = Unk;				// throws hr

		for (EnumStr -> Reset(); S_OK == EnumStr -> Next (1, &poleStr, NULL); /**/)
		{
			hr = IsDataServerAvailable(OLE2A(poleStr));		// Fehler führt nicht zum Abbruch
			if (S_OK == hr)
				++rlCount;

			CoTaskMemFree (poleStr);
			poleStr = NULL;
		}

	} catch (_com_error &e) {
		if (poleStr)
			CoTaskMemFree (poleStr);
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT COpenNewPropertySheet::IsDataServerAvailable (LPCSTR pcProgID)
{
CDataServerItem NewItem;
DWORD dwPos = IMG_GENERAL;
HRESULT hr = TxGetExtension() -> ReadDataServerParams (dwPos, &NewItem, pcProgID);

	if (FAILED(hr)) 
		return hr;

// wenn neu erzeugt werden soll, dann nur writeable DataServer auflisten
	if (DATASOURCEMODE_CreateNew == GetDatasourceMode() && !NewItem.m_fIsReadWrite)
		return S_FALSE;		// der nächste bitte

// wenn Öffnen und Datenquelle im aktuellen Projekt, dann weiter
	if (DATASOURCEMODE_OpenExistend == GetDatasourceMode() && NewItem.m_fNameIsSubStorage)
		return S_FALSE;		// der nächste bitte

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// COpenNewPropertySheet message handlers
