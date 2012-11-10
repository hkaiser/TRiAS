// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 16.12.2002 14:58:11 
//
// @doc
// @module ObjectCountInDatasource.cpp | Definition of the <c CObjectCountInDatasource> class

#include "stdafx.h"
#include "Statist.h"
#include <triastlb.h>

#include <Com/Thunk.h>

#include "ObjectCountInDatasource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRYEX(ObjectCountInDatasource)

/////////////////////////////////////////////////////////////////////////////
// CObjectCountInDatasource

// Constructor
CObjectCountInDatasource::CObjectCountInDatasource() :
	m_hPr(NULL), m_dwCookie(0), m_pICallback(NULL), m_fNeedsToDelete(FALSE)
{
}

// Destructor
CObjectCountInDatasource::~CObjectCountInDatasource()
{
}

/////////////////////////////////////////////////////////////////////////////
// ISupportErrorInfo

// InterfaceSupportsErrorInfo implementation
STDMETHODIMP CObjectCountInDatasource::InterfaceSupportsErrorInfo(REFIID riid)
{
	return riid == IID_IValueProvider ? S_OK : S_FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// IValueProvider

STDMETHODIMP CObjectCountInDatasource::get_Name(BSTR *pbstrName)
{
	if (NULL == pbstrName)
		return E_POINTER;

CComBSTR bstrName;
UINT uiResId = IDS_OBJECTCOUNTINCLASS;

	switch (m_rgTypes) {
	case OBJECTTYPE_Point:
		uiResId = IDS_POINTCOUNT;
		break;

	case OBJECTTYPE_Line:
		uiResId = IDS_LINECOUNT;
		break;

	case OBJECTTYPE_Area:
		uiResId = IDS_AREACOUNT;
		break;

	case OBJECTTYPE_Text:
		uiResId = IDS_TEXTCOUNT;
		break;

	default:
	case OBJECTTYPE_AllSimple:
		break;
	}

	bstrName.LoadString(uiResId);
	_ASSERTE(bstrName.Length() > 0);
	*pbstrName = bstrName.Detach();
	return S_OK;
}

STDMETHODIMP CObjectCountInDatasource::get_Description(BSTR *pbstrDesc)
{
	if (NULL == pbstrDesc)
		return E_POINTER;

CComBSTR bstrDesc;

	bstrDesc.LoadString(IDS_OBJECTCOUNTINCLASS_DESC);
	_ASSERTE(bstrDesc.Length() > 0);
	*pbstrDesc = bstrDesc.Detach();
	return S_OK;
}

STDMETHODIMP CObjectCountInDatasource::get_Flags(VALUEPROVIDERPROP *prgFlags)
{
	if (NULL == prgFlags)
		return E_POINTER;

	*prgFlags = VALUEPROVIDERPROP_Integer;
	return S_OK;
}

BOOL CObjectCountInDatasource::EnumClasses(INT_PTR lIdent, BOOL, void *pData)
{
IDENTOBJECTCOUNT IOC;

	INITSTRUCT(IOC, IDENTOBJECTCOUNT);
	IOC.ulIdent = lIdent;
	IOC.iOTypes = m_rgTypes;
	*reinterpret_cast<long *>(pData) += DEX_GetIdentObjectCount(IOC);
	return TRUE;
}

STDMETHODIMP CObjectCountInDatasource::get_Value(VARIANT *pvValue)
{
// Objektklassen durchgehen
CStdThunkImpl<CObjectCountInDatasource, ENUMNOKEYPROC> 
	Thunk(this, &CObjectCountInDatasource::EnumClasses);
ENUMNOKEY ENK;
long lCnt = 0;

	ENK.eFcn = Thunk.GetThunk();
	ENK.ePtr = reinterpret_cast<void *>(&lCnt);

	if (DEX_EnumClasses(m_hPr, ENK)) {
	CComVariant vValue (lCnt, VT_I4);

		return vValue.Detach(pvValue);
	}
	return E_FAIL;
}

///////////////////////////////////////////////////////////////////////////////
// Am TRiAS-ConnectionPoint ankoppeln

HRESULT CObjectCountInDatasource::SetXtsnSite (ITriasXtensionSite *pSite, 
	IValueProviderCallback *pICallback)
{
	COM_TRY {
		m_pICallback = pICallback;
		if (NULL != pSite) {
			m_Cont = pSite;		// throws HRESULT
			THROW_FAILED_HRESULT(AtlAdvise (m_Cont, (ITRiASNotificationSink *)this, 
				IID_ITRiASNotificationSink, &m_dwCookie));
		} else
			DisConnectFromServer();

	} COM_CATCH;
	return S_OK;
}

HRESULT CObjectCountInDatasource::DisConnectFromServer (void)
{
HRESULT hr = S_OK;

	if (m_Cont.IsValid() && 0 != m_dwCookie) {
	WUnknown Unk (GetUnknown());	// uns festhalten

		hr = AtlUnadvise (m_Cont, IID_ITRiASNotificationSink, m_dwCookie);
		if (SUCCEEDED(hr)) {
			m_dwCookie = 0L;
			m_Cont.Assign (NULL);	// Release()
		}
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASNotificationSink specific functions 
STDMETHODIMP CObjectCountInDatasource::ServerEvent (SERVEREVT se)
{
	switch (se) {
	case SERVEREVT_ServerToClose:	// das letzte vom Tage
		DisConnectFromServer();
		break;
	}

	return S_OK;
}

STDMETHODIMP CObjectCountInDatasource::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT)
{
	switch (pe) {
	case PROJECTEVT_ProjectToClose:
		DisConnectFromServer();
		break;
	}
	return S_OK;
}

STDMETHODIMP CObjectCountInDatasource::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT)
{
	return S_OK;
}

STDMETHODIMP CObjectCountInDatasource::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
	return S_OK;
}

STDMETHODIMP CObjectCountInDatasource::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
	switch (oe) {
	case GEOOBJECTEVT_ObjectToDelete:
		if (NULL != m_pICallback && m_hPr == DEX_GetObjectProject(lONr))
			m_fNeedsToDelete = TRUE;
		break;

	case GEOOBJECTEVT_ObjectDeleted:
		if (m_fNeedsToDelete) {
			m_pICallback -> NeedsRefresh();
			m_fNeedsToDelete = FALSE;
		}
		break;

	case GEOOBJECTEVT_ObjectAdded:
	case GEOOBJECTEVT_ObjectToClassify:
	case GEOOBJECTEVT_ObjectClassified:
		if (NULL != m_pICallback && m_hPr == DEX_GetObjectProject(lONr))
			m_pICallback -> NeedsRefresh();
		break;
	}
	return S_OK;
}

STDMETHODIMP CObjectCountInDatasource::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
	return S_OK;
}

STDMETHODIMP CObjectCountInDatasource::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
	return S_OK;
}

STDMETHODIMP CObjectCountInDatasource::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
	return S_OK;
}




