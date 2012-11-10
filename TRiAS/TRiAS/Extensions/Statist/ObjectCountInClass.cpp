// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 16.12.2002 09:17:59 
//
// @doc
// @module ObjectCountInClass.cpp | Definition of the <c CObjectCountInClass> class

#include "stdafx.h"
#include "Statist.h"
#include <triastlb.h>

#include "ObjectClassStatistics.h"
#include "ObjectCountInClass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRYEX(ObjectCountInClass)

/////////////////////////////////////////////////////////////////////////////
// CObjectCountInClass

// Constructor
CObjectCountInClass::CObjectCountInClass() : 
	m_lIdent(INVALID_HOBJECTS), m_dwCookie(0), m_pICallback(NULL), 
	m_fNeedsToDelete(FALSE)
{
}

// Destructor
CObjectCountInClass::~CObjectCountInClass()
{
	_ASSERTE(!m_Cont.IsValid() && 0 == m_dwCookie);
}

/////////////////////////////////////////////////////////////////////////////
// ISupportErrorInfo

// InterfaceSupportsErrorInfo implementation
STDMETHODIMP CObjectCountInClass::InterfaceSupportsErrorInfo(REFIID riid)
{
	return riid == IID_IValueProvider ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IValueProvider

STDMETHODIMP CObjectCountInClass::get_Name(BSTR *pbstrName)
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

STDMETHODIMP CObjectCountInClass::get_Description(BSTR *pbstrDesc)
{
	if (NULL == pbstrDesc)
		return E_POINTER;

CComBSTR bstrDesc;

	bstrDesc.LoadString(IDS_OBJECTCOUNTINCLASS_DESC);
	_ASSERTE(bstrDesc.Length() > 0);
	*pbstrDesc = bstrDesc.Detach();
	return S_OK;
}

STDMETHODIMP CObjectCountInClass::get_Flags(VALUEPROVIDERPROP *prgFlags)
{
	if (NULL == prgFlags)
		return E_POINTER;

	*prgFlags = VALUEPROVIDERPROP_Integer;
	return S_OK;
}

STDMETHODIMP CObjectCountInClass::get_Value(VARIANT *pvValue)
{
	if (NULL == pvValue)
		return E_POINTER;

	_ASSERTE(INVALID_HOBJECTS != m_lIdent);
	if (INVALID_HOBJECTS == m_lIdent)
		return E_UNEXPECTED;

IDENTOBJECTCOUNT IOC;

	INITSTRUCT(IOC, IDENTOBJECTCOUNT);
	IOC.ulIdent = m_lIdent;
	IOC.iOTypes = m_rgTypes;

CComVariant vCount(DEX_GetIdentObjectCount(IOC), VT_I4);

	return vCount.Detach(pvValue);
}

///////////////////////////////////////////////////////////////////////////////
// Am TRiAS-ConnectionPoint ankoppeln

HRESULT CObjectCountInClass::SetXtsnSite (ITriasXtensionSite *pSite, 
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

HRESULT CObjectCountInClass::DisConnectFromServer (void)
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
STDMETHODIMP CObjectCountInClass::ServerEvent (SERVEREVT se)
{
	switch (se) {
	case SERVEREVT_ServerToClose:	// das letzte vom Tage
		DisConnectFromServer();
		break;
	}

	return S_OK;
}

STDMETHODIMP CObjectCountInClass::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT)
{
	switch (pe) {
	case PROJECTEVT_ProjectToClose:
		DisConnectFromServer();
		break;
	}
	return S_OK;
}

STDMETHODIMP CObjectCountInClass::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT)
{
	return S_OK;
}

STDMETHODIMP CObjectCountInClass::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
	return S_OK;
}

STDMETHODIMP CObjectCountInClass::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
	switch (oe) {
	case GEOOBJECTEVT_ObjectToDelete:
		if (NULL != m_pICallback && m_lIdent == DEX_GetObjIdent(lONr))
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
		if (NULL != m_pICallback && m_lIdent == DEX_GetObjIdent(lONr))
			m_pICallback -> NeedsRefresh();
		break;
	}
	return S_OK;
}

STDMETHODIMP CObjectCountInClass::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
	return S_OK;
}

STDMETHODIMP CObjectCountInClass::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
	return S_OK;
}

STDMETHODIMP CObjectCountInClass::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
	return S_OK;
}

