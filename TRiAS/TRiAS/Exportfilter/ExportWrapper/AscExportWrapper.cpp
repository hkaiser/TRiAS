// @doc
// @module AscExportWrapper.cpp | Implementation of the <c CAscExportWrapper> class

#include "stdafx.h"

#include "ExpWrap.h"
#include "AscExportWrapper.h"

/////////////////////////////////////////////////////////////////////////////
// CAscExportWrapper

STDMETHODIMP CAscExportWrapper::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAscExportWrapper,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CAscExportWrapper::ExportBegin(BSTR Name, OUTMODE Mode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CAscExportWrapper::ExportComment(BSTR Comment)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CAscExportWrapper::ExportHeader(BSTR Header)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CAscExportWrapper::ExportDescription(
	BSTR KeyInfo, BSTR Description, DWORD dwStyle)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CAscExportWrapper::ExportTrailer(BSTR TrailerInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CAscExportWrapper::ExportGeometry(OBJECTTYPE Type, IUnknown * pIGeom)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CAscExportWrapper::ExportFeature(VARIANT Feature)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CAscExportWrapper::ExportRelation(HRELATION RelHandle, RELTYPE Type, HOBJECT ObjHandle)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CAscExportWrapper::BeginObject(HOBJECT ObjHandle)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CAscExportWrapper::EndObject(HOBJECT ObjHandle)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CAscExportWrapper::Initialize(BSTR RegKey)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return S_OK;
}
