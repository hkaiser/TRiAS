// IDispatch wrapper class(es) for CTRiASNotificationSinkDisp

#include "precomp.hxx"		// Alle Header auf einen Blick
#include "TRiASNotify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Initialisierung
CTRiASNotificationSinkDisp::CTRiASNotificationSinkDisp (void)
{
	for (int i = 0; i < _countof(s_pcoleNames); i++) 
		m_dwDispId[i] = DISPID_UNKNOWN;
	m_lcid = GetUserDefaultLCID();
}

HRESULT CTRiASNotificationSinkDisp::FInit (IDispatch *pIDisp)
{
	if (NULL == pIDisp) return E_POINTER;

	pIDisp -> AddRef();
	AttachDispatch(pIDisp);

	for (int i = 0; i < _countof(s_pcoleNames); i++) {
	HRESULT hr = pIDisp -> GetIDsOfNames (IID_NULL, (LPOLESTR *)&s_pcoleNames[i], 1, m_lcid, &m_dwDispId[i]);
		
		if (FAILED(hr)) {
			if (hr != DISP_E_UNKNOWNNAME)
				return hr;

		// solange dual interfaces nicht unterstützt werden hier nach
		// den alternativen Namen von VB5 fragen
			hr = pIDisp -> GetIDsOfNames (IID_NULL, (LPOLESTR *)&s_pcoleAltNames[i], 1, m_lcid, &m_dwDispId[i]);
			if (FAILED(hr) && hr != DISP_E_UNKNOWNNAME)
				return hr;
		}
	}

return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASNotificationSinkDisp operations
HRESULT CTRiASNotificationSinkDisp::ServerEvent(SERVEREVT se)
{
HRESULT result;
static BYTE parms[] = VTS_I4;

	if (DISPID_UNKNOWN == m_dwDispId[DISPID_SERVEREVENT])
		return S_OK;	// not implemented in sink

	TRY {
		InvokeHelper(m_dwDispId[DISPID_SERVEREVENT], DISPATCH_METHOD, 
			VT_I4, (void*)&result, parms,
			long(se));
		if (result)	result = S_FALSE;
	} CATCH (COleException, e) {
		result = e -> m_sc;
	} CATCH (COleDispatchException, e) {
		result = e -> m_scError;
	} END_CATCH;

	return result;
}

HRESULT CTRiASNotificationSinkDisp::ProjectEvent(long hPrj, PROJECTEVT pe, VARIANT vProj)
{
HRESULT result;
static BYTE parms[] = VTS_I4 VTS_VARIANT;

	if (DISPID_UNKNOWN == m_dwDispId[DISPID_PROJECTEVENT])
		return S_OK;	// not implemented in sink

	TRY {
		InvokeHelper(m_dwDispId[DISPID_PROJECTEVENT], DISPATCH_METHOD, 
			VT_I4, (void*)&result, parms,
			long(pe), &vProj);
		if (result)	result = S_FALSE;
	} CATCH (COleException, e) {
		result = e -> m_sc;
	} CATCH (COleDispatchException, e) {
		result = e -> m_scError;
	} END_CATCH;

	return result;
}

HRESULT CTRiASNotificationSinkDisp::GeoViewEvent(long hPrj, GEOVIEWEVT ve, VARIANT vData)
{
HRESULT result;
static BYTE parms[] = VTS_I4 VTS_I4 VTS_VARIANT;

	if (DISPID_UNKNOWN == m_dwDispId[DISPID_GEOVIEWEVENT])
		return S_OK;	// not implemented in sink

	TRY {
		InvokeHelper(m_dwDispId[DISPID_GEOVIEWEVENT], DISPATCH_METHOD, 
			VT_I4, (void*)&result, parms,
			hPrj, long(ve), &vData);
		if (result)	result = S_FALSE;
	} CATCH (COleException, e) {
		result = e -> m_sc;
	} CATCH (COleDispatchException, e) {
		result = e -> m_scError;
	} END_CATCH;

	return result;
}

HRESULT CTRiASNotificationSinkDisp::GeoClassEvent(long hPrj, GEOCLASSEVT ce, long ulIdent)
{
HRESULT result;
static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4;
	
	if (DISPID_UNKNOWN == m_dwDispId[DISPID_GEOCLASSEVENT])
		return S_OK;	// not implemented in sink

	TRY {
		InvokeHelper(m_dwDispId[DISPID_GEOCLASSEVENT], DISPATCH_METHOD, 
			VT_I4, (void*)&result, parms,
			hPrj, long(ce), ulIdent);
		if (result)	result = S_FALSE;
	} CATCH (COleException, e) {
		result = e -> m_sc;
	} CATCH (COleDispatchException, e) {
		result = e -> m_scError;
	} END_CATCH;

	return result;
}

HRESULT CTRiASNotificationSinkDisp::GeoObjectEvent(long hPrj, GEOOBJECTEVT oe, long lONr)
{
HRESULT result;
static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4;

	if (DISPID_UNKNOWN == m_dwDispId[DISPID_GEOOBJECTEVENT])
		return S_OK;	// not implemented in sink

	TRY {
		InvokeHelper(m_dwDispId[DISPID_GEOOBJECTEVENT], DISPATCH_METHOD, 
			VT_I4, (void*)&result, parms,
			hPrj, long(oe), lONr);
		if (result)	result = S_FALSE;
	} CATCH (COleException, e) {
		result = e -> m_sc;
	} CATCH (COleDispatchException, e) {
		result = e -> m_scError;
	} END_CATCH;

	return result;
}

HRESULT CTRiASNotificationSinkDisp::GeoFeatureEvent(long hPrj, GEOFEATUREEVT fe, LPARAM lParam)
{
HRESULT result;
static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BSTR;

	if (DISPID_UNKNOWN == m_dwDispId[DISPID_GEOFEATUREEVENT])
		return S_OK;	// not implemented in sink

	TRY {
	FEATUREMODIFIED *pFM = (FEATUREMODIFIED *)lParam;

		InvokeHelper(m_dwDispId[DISPID_GEOFEATUREEVENT], DISPATCH_METHOD, 
			VT_I4, (void*)&result, parms,
			hPrj, long(fe), pFM -> lONr, pFM -> pcName);
		if (result)	result = S_FALSE;
	} CATCH (COleException, e) {
		result = e -> m_sc;
	} CATCH (COleDispatchException, e) {
		result = e -> m_scError;
	} END_CATCH;

	return result;
}

HRESULT CTRiASNotificationSinkDisp::GeoRelationEvent(long hPrj, GEORELATIONEVT re, long ulRCode)
{
HRESULT result;
static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4;

	if (DISPID_UNKNOWN == m_dwDispId[DISPID_GEORELATIONEVENT])
		return S_OK;	// not implemented in sink

	TRY {
		InvokeHelper(m_dwDispId[DISPID_GEORELATIONEVENT], DISPATCH_METHOD, 
			VT_I4, (void*)&result, parms,
			hPrj, long(re), ulRCode);
		if (result)	result = S_FALSE;
	} CATCH (COleException, e) {
		result = e -> m_sc;
	} CATCH (COleDispatchException, e) {
		result = e -> m_scError;
	} END_CATCH;

	return result;
}

HRESULT CTRiASNotificationSinkDisp::ObjectWindowEvent(OBJWNDEVT oe, long hORWnd)
{
HRESULT result;
static BYTE parms[] = VTS_I4 VTS_I4;

	if (DISPID_UNKNOWN == m_dwDispId[DISPID_OBJECTWINDOWEVENT])
		return S_OK;	// not implemented in sink

	TRY {
		InvokeHelper(m_dwDispId[DISPID_OBJECTWINDOWEVENT], DISPATCH_METHOD, 
			VT_I4, (void*)&result, parms,
			long(oe), hORWnd);
		if (result)	result = S_FALSE;
	} CATCH (COleException, e) {
		result = e -> m_sc;
	} CATCH (COleDispatchException, e) {
		result = e -> m_scError;
	} END_CATCH;

	return result;
}
