// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "precomp.hxx"

#include <dirisole.h>
#include "TRiASNotifyDual.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Initialisierung
COleTRiASNotificationSinkDual::COleTRiASNotificationSinkDual (void)
{
}

COleTRiASNotificationSinkDual::~COleTRiASNotificationSinkDual (void)
{
}

HRESULT COleTRiASNotificationSinkDual::FInit (DTRiASNotificationSink *pISinkDual)
{
	TEST_E_POINTER("COleTRiASNotificationSinkDual::FInit", pISinkDual);

	try {
		m_Sink = pISinkDual;	// throws hr

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// COleTRiASNotificationSinkDual operations

HRESULT COleTRiASNotificationSinkDual::ServerEvent (SERVEREVT se)
{
long lResult = 0L;

	COM_TRY {
		THROW_FAILED_HRESULT(m_Sink -> ServerEvent (se, &lResult));
	} COM_CATCH;
	return lResult ? S_OK : S_FALSE;
}

HRESULT COleTRiASNotificationSinkDual::ProjectEvent(long hPrj, PROJECTEVT pe, VARIANT vProj)
{
long lResult = 0L;

	COM_TRY {
		THROW_FAILED_HRESULT(m_Sink -> ProjectEvent (pe, vProj, &lResult));
	} COM_CATCH;
	return lResult ? S_OK : S_FALSE;
}

HRESULT COleTRiASNotificationSinkDual::GeoViewEvent(long hPrj, GEOVIEWEVT ve, VARIANT vData)
{
long lResult = 0L;

	COM_TRY {
		THROW_FAILED_HRESULT(m_Sink -> GeoViewEvent (hPrj, ve, vData, &lResult));
	} COM_CATCH;
	return lResult ? S_OK : S_FALSE;
}

HRESULT COleTRiASNotificationSinkDual::GeoClassEvent(long hPrj, GEOCLASSEVT ce, long ulIdent)
{
long lResult = 0L;

	COM_TRY {
		THROW_FAILED_HRESULT(m_Sink -> GeoClassEvent (hPrj, ce, ulIdent, &lResult));
	} COM_CATCH;
	return lResult ? S_OK : S_FALSE;
}

HRESULT COleTRiASNotificationSinkDual::GeoObjectEvent(long hPrj, GEOOBJECTEVT oe, long lONr)
{
long lResult = 0L;

	COM_TRY {
		THROW_FAILED_HRESULT(m_Sink -> GeoObjectEvent (hPrj, oe, lONr, &lResult));
	} COM_CATCH;
	return lResult ? S_OK : S_FALSE;
}

HRESULT COleTRiASNotificationSinkDual::GeoFeatureEvent(long hPrj, GEOFEATUREEVT fe, LPARAM lParam)
{
FEATUREMODIFIED *pFM = (FEATUREMODIFIED *)lParam;
long lResult = 0L;

	COM_TRY {
		THROW_FAILED_HRESULT(m_Sink -> GeoFeatureEvent (hPrj, fe, pFM -> lONr, &lResult));
	} COM_CATCH;
	return lResult ? S_OK : S_FALSE;
}

HRESULT COleTRiASNotificationSinkDual::GeoRelationEvent(long hPrj, GEORELATIONEVT re, long ulRCode)
{
long lResult = 0L;

	COM_TRY {
		THROW_FAILED_HRESULT(m_Sink -> GeoRelationEvent (hPrj, re, ulRCode, &lResult));
	} COM_CATCH;
	return lResult ? S_OK : S_FALSE;
}

HRESULT COleTRiASNotificationSinkDual::ObjectWindowEvent(OBJWNDEVT oe, long hORWnd)
{
long lResult = 0L;

	COM_TRY {
		THROW_FAILED_HRESULT(m_Sink -> ObjectWindowEvent (oe, hORWnd, &lResult));
	} COM_CATCH;
	return lResult ? S_OK : S_FALSE;
}
