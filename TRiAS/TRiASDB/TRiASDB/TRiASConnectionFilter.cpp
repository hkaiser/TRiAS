// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 12.12.2002 14:18:35 
//
// @doc
// @module TRiASConnectionFilter.cpp | Definition of the <c CTRiASConnectionFilter> class

#include "stdafx.h"

#include "Wrapper.h"		// SmartIF's
#include "Strings.h"
#include "TRiASConnectionFilter.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASConnectionFilter, CTRiASConnectionFilter)

/////////////////////////////////////////////////////////////////////////////
// CTRiASConnectionFilter

STDMETHODIMP CTRiASConnectionFilter::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASConnectionFilter
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CTRiASConnectionFilter::get_Name(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnectionFilter::get_Name");

CComBSTR bstr (m_bstrName);

	if (!bstr)
		return Error(g_cbNoMemory, E_OUTOFMEMORY);

	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASConnectionFilter::put_Name(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_bstrName = newVal;
	if (!m_bstrName)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASConnectionFilter::get_Geometry(IDispatch **ppIGeometry)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIGeometry) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnectionFilter::get_Geometry");
	*ppIGeometry = NULL;

	COM_TRY {
	WDispatch Geom (m_Geometry);

		*ppIGeometry = Geom.detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASConnectionFilter::put_Geometry(IDispatch *pIGeometry)
{
	COM_TRY {
		m_Geometry = pIGeometry;
		m_fIsDirty = true;
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASConnectionFilter::get_Type(CONNECTIONFILTERTYPE *prgType)
{
	if (NULL == prgType)
		return E_POINTER;

	*prgType = m_rgType;
	return S_OK;
}

STDMETHODIMP CTRiASConnectionFilter::put_Type(CONNECTIONFILTERTYPE rgType)
{
	_ASSERTE(CONNECTIONFILTERTYPE_Rectangle_OverlappedContainers <= rgType &&
			 CONNECTIONFILTERTYPE_Polygon_ContainedObjects >= rgType);
	m_rgType = rgType;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CTRiASConnectionFilter::GetClassID (CLSID *pClassID)
{
	if (NULL == pClassID) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnectionFilter::GetClassID");

	*pClassID = CLSID_TRiASConnectionFilter;
	return S_OK;
}

// IPersistStream
STDMETHODIMP CTRiASConnectionFilter::IsDirty ()
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CTRiASConnectionFilter::Load (LPSTREAM pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;
	
DWORD dwSignature = 0;
DWORD dwVersion = 0;

	LoadData(pStm, dwSignature);
	if (dwSignature != CONNECTFILTER_SIGNATURE)
		return E_UNEXPECTED;
	LoadData(pStm, dwVersion);
	if ((dwVersion & ~CONNECTFILTER_MINORVERSIONMASK) > CONNECTFILTER_LASTKNOWNVERSION)
		return STG_E_OLDDLL;

	RETURN_FAILED_HRESULT(m_bstrName.ReadFromStream(pStm));
	RETURN_FAILED_HRESULT(::OleLoadFromStream(pStm, IID_IDispatch, m_Geometry.ppv()));

	if (dwVersion >= CONNECTFILTER_VERSION_101) {
	// ggf. Typ des Verbindungsfilters laden
		RETURN_FAILED_HRESULT(LoadData(pStm, m_rgType));
	}
	else {
		m_rgType = CONNECTIONFILTERTYPE_Rectangle_OverlappedContainers;
	}

	m_fIsInitialized = true;
	return S_OK;
}

STDMETHODIMP CTRiASConnectionFilter::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	SaveData(pStm, CONNECTFILTER_SIGNATURE);
	SaveData(pStm, CONNECTFILTER_LASTKNOWNVERSION);

	RETURN_FAILED_HRESULT(m_bstrName.WriteToStream(pStm));
	RETURN_FAILED_HRESULT(::OleSaveToStream(WPersistStream(m_Geometry), pStm));
	RETURN_FAILED_HRESULT(SaveData(pStm, m_rgType));

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CTRiASConnectionFilter::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	RETURN_FAILED_HRESULT(WPersistStream(m_Geometry)->GetSizeMax(pcbSize));
	pcbSize->QuadPart += 2*sizeof(DWORD) + LenForStream(m_bstrName) + 
		sizeof(m_rgType);
	return S_OK;
}

// IPersistStreamInit
STDMETHODIMP CTRiASConnectionFilter::InitNew ()
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;
	
	m_rgType = CONNECTIONFILTERTYPE_Rectangle_OverlappedContainers;
	m_fIsInitialized = true;
	return S_OK;
}

