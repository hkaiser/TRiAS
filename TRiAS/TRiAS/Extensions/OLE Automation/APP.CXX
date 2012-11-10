// Trias.Application Objekt ---------------------------------------------------
// File: APP.CXX

#include "precomp.hxx"

#include <Com/ComBool.h>

#include <dirisole.h>
#include <ioprpini.hxx>
#include "oleguid.h"

#include "doctree.hxx"
#include "connect.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface2(DDocument, IID_DDocument);
DefineSmartInterface(InitObjPropMerkmal);

///////////////////////////////////////////////////////////////////////////////
// zugehörige CriticalSection
//CComGlobalsThreadModel::AutoCriticalSection CTriasApp::m_cs;

// Das eigentliche ApplicationObject ------------------------------------------
CTriasApp::CTriasApp (void)
	: m_fValid(false)
#if _ATL_VER < 0x0200
	  , m_cp(this)
#endif // _ATL_VER
{
	CONSTRUCT_TRACE(CTriasApp);
	
	m_pDocTree = NULL;
}

bool CTriasApp::FInit (LPUNKNOWN pUnk)
{
// init GeoDoc Tree 
	m_pDocTree = CDocTree::CreateInstance (this);
	if (m_pDocTree == NULL) return false;

// pUnk merken und festhalten
	m_pUnk = pUnk;
//	ADDREF(m_pUnk);
	
return true;
}

CTriasApp::~CTriasApp (void)
{
	DESTRUCT_TRACE(CTriasApp);

	if (m_dwCookie) {
		FDisconnect (m_dwCookie);	// cancel connection
		m_dwCookie = 0L;
	}

//	RELEASE(m_pUnk);			// pUnk wieder loslassen

	DELETE_OBJ(m_pDocTree);
}

void CTriasApp::InvApp (void)
{
	m_fValid = false;

	InternalAddRef();		// künstliches AddRef, damit nichts passiert	
	{
		if (m_dwCookie) {
			FDisconnect (m_dwCookie);	// cancel connection
			m_dwCookie = 0L;
		}
	}
	InternalRelease();		// künstliches AddRef aufheben
}

// Funktionen werden gerufen, wenn externe Locks entstehen bzw.
// verschwinden
ULONG CTriasApp::InternalAddRef()
{
	_ASSERTE(m_dwRef != -1L);
	Lock();

long l = CComObjectRoot::InternalAddRef();

	if (m_dwRef == APP_EXTERNAL_THRESHOLD+1) {
		Unlock();
		FinalExternalConstruct();
	} else 
		Unlock();
	return l;
}

ULONG CTriasApp::InternalRelease()
{
	Lock();

long l = CComObjectRoot::InternalRelease();

	if (m_dwRef == APP_EXTERNAL_THRESHOLD) {
		Unlock();
		FinalExternalRelease();
	} else 
		Unlock();
	return l;
}

HRESULT CTriasApp::FinalExternalConstruct (void)
{
	ADDREF(m_pUnk);
	return S_OK;
}

void CTriasApp::FinalExternalRelease (void)
{
	RELEASE (m_pUnk);						// Parent wieder loslassen
}

///////////////////////////////////////////////////////////////////////////////
// Instanz erzeugen
CTriasApp *CTriasApp::CreateInstance (LPUNKNOWN pUnk)
{
CComObject<CTriasApp> *pApp = NULL;

	try {
	// Create an instance of CTriasApp.  Exit if an error occurs.
	HRESULT hr = CComObject<CTriasApp>::CreateInstance (&pApp);

		if(FAILED(hr)) _com_issue_error(hr);
		if (!pApp -> FInit (pUnk))
			_com_issue_error(E_FAIL);

		pApp -> AddRef();	// fertig initialisiert

	// establish connection to the application-supplied notifications
		hr = pApp -> FConnect (&pApp -> m_dwCookie);
		if (FAILED(hr)) _com_issue_error(hr);

	} catch (_com_error&) {
		DELETE_OBJ(pApp);
		return NULL;
	}

// If execution has reached this point, then no errors have occurred.
	pApp -> Validate();
	return pApp;
}

///////////////////////////////////////////////////////////////////////////////
// Connection to the application-supplied notifications 
LPCONNECTIONPOINT CTriasApp :: GetConnectionPoint (void)
{
LPCONNECTIONPOINT pCP = NULL;

	if (FAILED(FindConnectionPoint (IID_INotificationSink2, &pCP))) 
		return NULL;

	return pCP;
}

HRESULT CTriasApp::FConnect (DWORD *pdwCookie)
{
// besorgen des ConnectionPoint- Interfaces
LPCONNECTIONPOINT pCP = GetConnectionPoint();

	if (pCP == NULL) return ResultFromScode (E_OUTOFMEMORY);

// Erzeugen der CExternalConnection
CAppConnection *pAC = CAppConnection::CreateInstance (this);

	if (pAC == NULL) {
		pCP -> Release();	// wird nicht mehr gebraucht
		return ResultFromScode (E_OUTOFMEMORY);
	}

HRESULT hr = pCP -> Advise (pAC, pdwCookie);

	pAC -> Release();	// wird jetzt vom ConnectionPoint gehalten
	pCP -> Release();	// wird nicht mehr gebraucht
	return hr;
}

void CTriasApp::FDisconnect (DWORD dwCookie)
{
LPCONNECTIONPOINT pCP = GetConnectionPoint();

	if (pCP != NULL) {
		pCP -> Unadvise (dwCookie);
		pCP -> Release();
	} 
}

///////////////////////////////////////////////////////////////////////////////
// Object Properties
DefineSmartInterface(EnumObjProps);
DefineSmartInterface(ObjectProps);
DefineSmartInterface(ObjectProps2);
DefineSmartInterface(ObjectProps3);
DefineSmartInterface(ObjectProperty);
DefineSmartInterface(ObjectProperty2);
DefineSmartInterface(TriasXtensionSite);

HRESULT CTriasApp::GetObjectProperty (LPCSTR pcName, LONG lONr, IObjectProperty **ppIObjProp)
{
	*ppIObjProp = NULL;

WEnumObjProps EnumObjP;
HRESULT hr = GetEnumObjProps (lONr, EnumObjP.ppi());

	if (FAILED(hr)) return hr;

	hr = EnumObjP -> FindByName (pcName, ppIObjProp);	 //???return value
	if (FAILED(hr)) 
		return S_FALSE;		// not found
	return NOERROR;
}

HRESULT CTriasApp::GetObjectPropertyIdent (LPCSTR pcName, LONG lIdent, IObjectProperty **ppIObjProp)
{
	*ppIObjProp = NULL;

WEnumObjProps EnumObjP;
HRESULT hr = GetEnumObjPropsIdent (lIdent, EnumObjP.ppi());

	if (FAILED(hr)) return hr;

	hr = EnumObjP -> FindByName (pcName, ppIObjProp);	 //???return value
	if (FAILED(hr)) 
		return S_FALSE;		// not found
	return NOERROR;
}

HRESULT CTriasApp::AddObjectProperty (
	LPCSTR pcName, DWORD dwFlags, LONG lONr, VARIANT vOptData, 
	IObjectProperty **ppIObjProp)
{
WObjectProperty ObjProp;
HRESULT hr = GetObjectProperty (pcName, 0, ObjProp.ppi());

	if (S_OK == hr) {
	WInitObjPropMerkmal Init;

		if (SUCCEEDED(ObjProp -> QueryInterface(Init.ppi()))) {
		// nochmal gegen die Objektklassen testen
		CComBool fRegistered;

			hr = Init -> HasObjects (DEX_GetObjIdent(lONr), &fRegistered);
			if (fRegistered && SUCCEEDED(hr)) {
				*ppIObjProp = ObjProp.detach();
				return S_OK;
			}
		}
	}

// OProp not exists, create new
WObjectProps2 GenProp; 

	hr = GetObjProps (IID_IObjectProps2, GenProp.ppv());
	if (FAILED(hr)) return hr;

	return GenProp -> CreateNewProp (pcName, dwFlags, lONr, vOptData, IID_IObjectProperty, (LPVOID *)ppIObjProp);
}

HRESULT CTriasApp::AddObjectPropertyIdent (
	LPCSTR pcName, DWORD dwFlags, LONG lIdent, VARIANT vOptData, 
	IObjectProperty **ppIObjProp)
{
HRESULT hr = GetObjectPropertyIdent (pcName, 0, ppIObjProp);
	
	if (S_OK == hr) return hr;

// OProp not exists, create new
WObjectProps3 GenProp; 

	hr = GetObjProps (WObjectProps3::GetIID(), GenProp.ppv());
	if (FAILED(hr)) return hr;

	return GenProp -> CreateNewPropClass (pcName, dwFlags, lIdent, vOptData, IID_IObjectProperty, (LPVOID *)ppIObjProp);
}

HRESULT CTriasApp::RemoveObjectProperty (LPCSTR pcName, LONG lONr)
{
WObjectProperty ObjProp;
HRESULT hr = GetObjectProperty (pcName, lONr, ObjProp.ppi());
	
	if (FAILED(hr)) return hr;

	if (S_OK == hr) {
	WObjectProperty2 ObjSetP;	 

		hr = ObjProp -> QueryInterface (IID_IObjectProperty2, ObjSetP.ppv());
		if (FAILED(hr))	return hr;

		hr = ObjSetP -> Set (lONr, NULL);
	} 
	return hr;
}

HRESULT CTriasApp::GetEnumObjProps (LONG lONr, IEnumObjProps **ppIEnum)
{
	*ppIEnum = NULL;

WObjectProps ObjProps;
HRESULT	hr = GetObjProps (IID_IObjectProps, ObjProps.ppv());
	
	if (FAILED(hr)) return hr;

	/*if (DEX_MustInitOPFs())*/ {
		hr = ObjProps -> OnNewReferenceObject (-1L);		// force reread
		if (FAILED(hr)) return hr;

		hr = ObjProps -> OnNewReferenceObject (lONr);
		DEX_SetMustInitOPFs(TRUE);
	}
	if (SUCCEEDED(hr))	// Get ObjectProperty by name through Enum
		hr = ObjProps -> EnumObjectProps (ppIEnum);
	
	return hr;
}

HRESULT CTriasApp::GetEnumObjPropsIdent (LONG lIdent, IEnumObjProps **ppIEnum)
{
	*ppIEnum = NULL;

WObjectProps ObjProps;
HRESULT	hr = GetObjProps (IID_IObjectProps, ObjProps.ppv());
	
	if (FAILED(hr)) return hr;

	/*if (DEX_MustInitOPFs()) */{
		hr = ObjProps -> OnNewReferenceObjects (-1L, 0L);		// force reread
		if (FAILED(hr)) return hr;

		hr = ObjProps -> OnNewReferenceObjects (lIdent, 0L);
		DEX_SetMustInitOPFs(TRUE);
	}
	if (SUCCEEDED(hr))	// Get ObjectProperty by name through Enum
		hr = ObjProps -> EnumObjectProps (ppIEnum);
	
	return hr;
}

HRESULT CTriasApp::GetObjProps (REFIID riid, LPVOID *ppIObjProps)
{
// get TRiAS XtensionSite
WTriasXtensionSite XtnSite;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetXtensionSite (XtnSite.ppi());

	if (FAILED(hr)) return hr;

// Get all installed ObjectProperties for lONr
	return XtnSite -> QueryInterface (riid, ppIObjProps);
}

///////////////////////////////////////////////////////////////////////////////
// Liefert ProgrammierInterface eines bestimmten Documentes
DefineSmartInterface(Dispatch);
DefineSmartInterface2(_DDocument, IID_DDocument);

CGeoDoc *CTriasApp::FGetGeoDocument (HPROJECT hPr, _DDocument **ppIDoc)
{
	if (NULL == hPr) 
		hPr = DEX_GetActiveProjectHandle();
	if (NULL == hPr) return NULL;

CGeoDoc *pDoc = NULL;

	try {
	WDDocument Doc;

		THROW_FAILED_HRESULT(FGetDocDispHandle (hPr, &pDoc, Doc.ppi()));

		if (NULL != ppIDoc) 
			*ppIDoc = Doc.detach();

	} catch (_com_error&) {
		return NULL;
	}
	return pDoc;
}

///////////////////////////////////////////////////////////////////////////////
// Document öffnen 
HRESULT CTriasApp::OpenDocument (
	LPCSTR pcName, LPCSTR pcUser, LPCSTR pcPassWd, 
	int iMode, DWORD dwMode, DDocument **ppIDoc)
{
	try {
	TRIAS_OPENEX TO;
	CGeoDoc *pDoc = NULL;

		INITSTRUCT (TO, TRIAS_OPENEX);
		TO.pcProject = pcName;
		TO.pcUser = pcUser;
		TO.pcPassWord = pcPassWd;
		TO.iMode = iMode;
		TO.dwMode = dwMode;
		
	ErrCode EC = DEX_OpenProjectEx(TO);	// Projekt eröffnen

		if (EC != EC_OKAY && EC != WC_RETURN) 	// Fehler aufgetreten
			_com_issue_error(ErrorFromErrCode (EC));

	HRESULT hr = FGetDocDisp (pcName, &pDoc, ppIDoc, DOCMODE_Get);

		if (FAILED(hr)) {
		// Add to GeoDoc Tree
			THROW_FAILED_HRESULT(FGetDocDisp (pcName, &pDoc, ppIDoc, DOCMODE_Add));
			DEX_RePaintWait();
		} else {
		HPROJECT hPr = DEX_GetProjectHandle(pcName);

			ASSERT(NULL != hPr);
			DEX_MakeProjectActive(hPr);
		}

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return S_OK;
} 

///////////////////////////////////////////////////////////////////////////////
// Helper für Monikerzugriff
HRESULT CTriasApp::GetDocMoniker (HPROJECT hPr, IMoniker **ppIMk)
{
CGeoDoc *pDoc = FGetGeoDocument (hPr);

	if (NULL != pDoc) 
		return pDoc -> GetMoniker (ppIMk);
	return E_FAIL;
}

///////////////////////////////////////////////////////////////////////////////
// diverse Helperroutinen
HRESULT RegisterAsRunning (
	DWORD grfFlags, IUnknown *pIUnk, IMoniker *pIMk, DWORD *pdwRegROT)
{
	if (NULL == pdwRegROT) return E_POINTER;

IRunningObjectTable *pROT;

	if (SUCCEEDED(GetRunningObjectTable(0, &pROT))) {
	// Revoke old entry, if needed
		if (0 != *pdwRegROT) {
			pROT -> Revoke (*pdwRegROT);
			*pdwRegROT = 0L;
		}

	// Register as weak so clients can free us.
		pROT -> Register(grfFlags, pIUnk, pIMk, pdwRegROT);
		pROT -> Release();
	}
	return S_OK;
}

HRESULT RevokeAsRunning (DWORD *pdwRegROT)
{
	if (NULL == pdwRegROT) return E_POINTER;
	if (0L == *pdwRegROT) return S_FALSE;

IRunningObjectTable *pROT;

	if (SUCCEEDED(GetRunningObjectTable (0, &pROT))) {
	// Register as weak so clients can free us.
		pROT -> Revoke (*pdwRegROT);
		pROT -> Release();

		*pdwRegROT = 0;
	}
	return S_OK;
}

HRESULT NoteChangeTime (DWORD dwRegROT, FILETIME *pft)
{
	if (NULL == pft) return E_POINTER;

IRunningObjectTable *pROT;

	if (SUCCEEDED(GetRunningObjectTable (0, &pROT))) {
		pROT -> NoteChangeTime (dwRegROT, pft);
		pROT -> Release();
	}
	return S_OK;
}


