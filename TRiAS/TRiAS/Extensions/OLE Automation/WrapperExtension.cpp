// WrapperExtension.cpp

#include "precomp.hxx"

#include <registrx.hxx>

#include "strings.h"
#include "WrapperExtension.h"

#if _TRiAS_VER >= 0x0300
using std::bad_alloc;
#endif // _TRiAS_VER >= 0x0300

/////////////////////////////////////////////////////////////////////////////
// benötigte SmartIF's
DefineSmartInterface(Dispatch);

/////////////////////////////////////////////////////////////////////////////
// DTRiASExtensionWrapper operations
DTRiASExtensionWrapper::DTRiASExtensionWrapper (void)
{
	for (int i = 0; i < _countof(s_pcoleDTRiASExtensionNames); i++) 
		m_dwDispId[i] = DISPID_UNKNOWN;
	m_lcid = GetUserDefaultLCID();
}

HRESULT DTRiASExtensionWrapper::FInit (IDispatch *pIDisp)
{
	if (NULL == pIDisp) return E_POINTER;

	pIDisp -> AddRef();
	AttachDispatch(pIDisp);

	for (int i = 0; i < _countof(s_pcoleDTRiASExtensionNames); i++) {
	HRESULT hr = pIDisp -> GetIDsOfNames (IID_NULL, (LPOLESTR *)&s_pcoleDTRiASExtensionNames[i], 1, m_lcid, &m_dwDispId[i]);
		
		if (FAILED(hr) && hr != DISP_E_UNKNOWNNAME)
			return hr;
	}

// LoadExtension muß implementiert sein, sonst geht nichts
	if (DISPID_UNKNOWN == m_dwDispId[DISPID_LOADEXTENSION])
		return DISP_E_UNKNOWNNAME;

	return S_OK;
}

HRESULT DTRiASExtensionWrapper::LoadExtension(LPDISPATCH pIApp, const VARIANT& vDocDisp)
{
static BYTE parms[] = VTS_DISPATCH VTS_VARIANT;
HRESULT result = S_OK;

	TRY {
		InvokeHelper(m_dwDispId[DISPID_LOADEXTENSION], DISPATCH_METHOD, VT_EMPTY, NULL, parms,
			 pIApp, &vDocDisp);
	} CATCH (COleException, e) {
		result = e -> m_sc;
	} CATCH (COleDispatchException, e) {
		result = e -> m_scError;
	} END_CATCH;
	
	return result;
}

HRESULT DTRiASExtensionWrapper::UnloadingExtension(VARIANT_BOOL fMayDeny, VARIANT_BOOL *pfUnload)
{
HRESULT result = S_OK;
static BYTE parms[] = VTS_BOOL;

	if (NULL == pfUnload) return E_POINTER;

	TRY {
	BOOL fUnload = true;

		InvokeHelper(m_dwDispId[DISPID_UNLOADINGEXTENSION], DISPATCH_METHOD, VT_BOOL, (void*)&fUnload, parms,
			fMayDeny);
		*pfUnload = fUnload;
	
	} CATCH (COleException, e) {
		result = e -> m_sc;
		*pfUnload = true;
	} CATCH (COleDispatchException, e) {
		result = e -> m_scError;
		*pfUnload = true;
	} END_CATCH;

	return result;
}

HRESULT DTRiASExtensionWrapper::UnloadExtension()
{
HRESULT result = S_OK;

	TRY {
		InvokeHelper(m_dwDispId[DISPID_UNLOADEXTENSION], DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	} CATCH (COleException, e) {
		result = e -> m_sc;
	} CATCH (COleDispatchException, e) {
		result = e -> m_scError;
	} END_CATCH;

	return result;
}

/////////////////////////////////////////////////////////////////////////////
// Wrapper für DispatchExtension

/////////////////////////////////////////////////////////////////////////////
// Zähler der zusätzlichen Erweiterungen
LONG CWrapperExtension::m_lCntExts = 0;

CWrapperExtension::CWrapperExtension(void)
{
	m_pIExt = NULL;
	m_pExtWrapper = NULL;
	m_hPr = NULL;
}

CWrapperExtension::~CWrapperExtension(void)
{
	RELEASE(m_pIExt);		// freigeben, wenn definiert
	DELETE_OBJ(m_pExtWrapper);

// nicht dekrementieren, damit keine doppelten HDEX's enstehen
//	InterlockedDecrement (&m_lCntExts);
}

STDMETHODIMP_(HDEX) CWrapperExtension::LoadExtension (TRIASLOADEX *pTL, HWND hWnd)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	CTriasExtension::LoadExtension (pTL, hWnd);

// Der Rückkehrwert dieser Funktion wird in TRiAS als Schlüssel für die
// Sortierung der geladenen Erweiterungen verwendet: er muß _eindeutig_ sein !
// Da CTriasExtension::LoadExtension diesen jedoch auf den hInstance dieser DLL 
// initialisiert, würden alle Erweiterungen hier einen identischen Suchschlüssel 
// erhalten. Also ein kleiner Trick: hInstance + Zähler der instantiierten
// Erweiterungen. (ACHTUNG plattformspezifisch: der hInstance ist unter
// Win32 immer das Datensegment der DLL welches auf Segmentgrenzen 
// ausgerichtet ist und damit genug Raum für eindeutige Zahlen bietet.)
	{
	CComGlobalsThreadModel::AutoCriticalSection cs;

		cs.Lock();
		ASSERT(0 == ((DWORD)m_hDex & 0x00000FFF));	// genügend Nullen am Ende, das reicht für 0xfff Erweiterungen
		m_hDex += ++m_lCntExts;					// <<-- plattformspezifisch
		cs.Unlock();
	}

	return m_hDex;
}

STDMETHODIMP_(BOOL) CWrapperExtension::InitExtension (short iMode)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	if (!CTriasExtension::InitExtension (iMode))
		return false;

// Haupterweiterung ggf. nachladen
	if (NULL == g_pTE || !g_pTE -> isLoaded()) {
	// Haupterweiterung nachladen
		COM_TRY {
		WUnknown Ext;

			THROW_FAILED_HRESULT(m_pXtnSite -> GetXtension (CLSID_OleAutoExtension, IID_IUnknown, Ext.ppv()));
			m_Ext = Ext;		// festhalten
		} COM_CATCH_RETURN(false);		// Fehler melden

	// jetzt müßte alles geladen sein
		ASSERT(NULL != g_pTE && g_pTE -> isLoaded());
	}

OLE2AutoExtension *pExt = (OLE2AutoExtension *)g_pTE;
CComVariant vDoc;

	ASSERT(NULL != pExt);
	pExt -> GetCorrespondingDocument(m_hPr, vDoc);
	if (NULL != m_pIExt)
		return SUCCEEDED(m_pIExt -> LoadExtension (pExt->AppDisp(), vDoc));
	else if (NULL != m_pExtWrapper)
		return SUCCEEDED(m_pExtWrapper -> LoadExtension (pExt->AppDisp(), vDoc));
	
	return false;		// snh
}

STDMETHODIMP_(BOOL) CWrapperExtension::UnLoadExtension (void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

VARIANT_BOOL fMayDeny = true;

	if (NULL != g_pTE)
		fMayDeny = ((OLE2AutoExtension *)g_pTE) -> ForceUnload() ? false : true;

VARIANT_BOOL fUnload = true;

	if (NULL != m_pIExt) {
	HRESULT hr = m_pIExt -> UnloadingExtension (fMayDeny, &fUnload);

		if (SUCCEEDED(hr) && fMayDeny && !fUnload)
			return false;
		m_pIExt -> UnloadExtension();
	} else if (NULL != m_pExtWrapper) {
	HRESULT hr = m_pExtWrapper -> UnloadingExtension (fMayDeny, &fUnload);

		if (SUCCEEDED(hr) && fMayDeny && !fUnload)
			return false;
		m_pExtWrapper -> UnloadExtension();
	} else
		ASSERT(NULL != m_pIExt || NULL != m_pExtWrapper);

	m_Ext.Assign(NULL);		// Haupterweiterung wieder freigeben
	return CTriasExtension::UnLoadExtension();
}

///////////////////////////////////////////////////////////////////////////////
// IInitDTRiASExtension
STDMETHODIMP CWrapperExtension::InitDTRiASExtension (IUnknown *pIUnk, long hPr)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	ASSERT(NULL == m_pIExt && NULL == m_pExtWrapper);

HRESULT hr = pIUnk -> QueryInterface(IID_DTRiASExtension, (LPVOID *)&m_pIExt);

	if (FAILED(hr)) {
	WDispatch Disp;

		hr = pIUnk -> QueryInterface (IID_IDispatch, Disp.ppv());
		if (FAILED(hr)) return hr;

		try {
			m_pExtWrapper = new DTRiASExtensionWrapper();
			hr = m_pExtWrapper -> FInit (Disp);
			if (FAILED(hr)) return hr;

		} catch (bad_alloc) {
			return E_OUTOFMEMORY;
		}
	}

// evtl. BezugsProjekt 
	m_hPr = reinterpret_cast<HPROJECT>(hPr);
	return S_OK;
}

// Initialisierung aus der Registry
STDMETHODIMP CWrapperExtension::InitDTRiASExtensionRegKey (BSTR bstrRegKey, long hPr)
{

	AFX_MANAGE_STATE(AfxGetAppModuleState());
	USES_CONVERSION;

string strKey (OLE2A(bstrRegKey));

	strKey += string(g_cbWild) + g_cbConfig;

CCurrentUser regCfg(KEY_READ, strKey.c_str());
char cbBuffer[_MAX_PATH];
DWORD dwLen = _MAX_PATH;

	if (!regCfg.isValid() || !regCfg.GetSubSZ (g_cbTargetProgID, cbBuffer, dwLen))
		return HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND);

CLSID clsID;
HRESULT hr = CLSIDFromProgID (A2OLE(cbBuffer), &clsID);

	if (FAILED(hr)) return hr;

	try {
	// Objekt instantiieren und initialisieren
	WUnknown Unk (clsID);

		THROW_FAILED_HRESULT(InitDTRiASExtension (Unk, hPr));

	} catch (_com_error & e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}
