// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.03.2001 10:43:06 
//
// @doc
// @module PropertySequenceService.cpp | Definition of the <c CPropertySequenceService> class

#include "trias03p.hxx"

#if defined(_USE_XML_GEOCOMPONENTS)

#include <funcs03.h>
#include <triastlb.h>
#include <com/errormacros2.h>
#include <com/ErrorMacros2Impl.cpp>		// nur in einem Module!

#include "PropertySequenceService.h"

DefineSmartInterface(ProgressIndicator);
DefineSmartInterface(TRiASDataObject);

/////////////////////////////////////////////////////////////////////////////
// CPropertySequenceService

STDMETHODIMP CPropertySequenceService::RunActionSequence(
	INT_PTR hWnd, BSTR bstrRsc, BSTR bstrDesc, BSTR bstrSaveAs, IProgressIndicator2 *pIStatus, 
	IDataObject *pIInData, VARIANT_BOOL fInitNew, IDataObject **ppIOutData)
{
	_ASSERTE(NULL != bstrRsc);

	if (NULL == bstrRsc || 0 == ::SysStringLen(bstrRsc))
		return E_INVALIDARG;

	if (!IsWindow(reinterpret_cast<HWND>(hWnd)))
		hWnd = reinterpret_cast<INT_PTR>(__hWndM);		// reinterpret_cast<INT_PTR>(::GetActiveWindow());

	USES_CONVERSION;

LPCSTR pcRsc = OLE2A(bstrRsc);
LPCSTR pcDesc = (NULL != bstrDesc && ::SysStringLen(bstrDesc) > 0) ? OLE2A(bstrDesc) : NULL;
LPCSTR pcSaveAs = (NULL != ::SysStringLen(bstrSaveAs) > 0) ? OLE2A(bstrSaveAs) : NULL;
WProgressIndicator Status;

	if (NULL != pIStatus)
		pIStatus -> QueryInterface(Status.ppi());

LPCSTR pcModule = m_bstrModule.Length() > 0 ? OLE2A(m_bstrModule) : NULL;

	GENERATE_ERROR_NOASSERT(RunPropertyActionSequence(
		reinterpret_cast<HWND>(hWnd), pcRsc, pcModule, pcDesc, pcSaveAs, 
		Status, pIInData, ppIOutData, fInitNew ? TRUE : FALSE, m_CtxData));
	return S_OK;
}

STDMETHODIMP CPropertySequenceService::RunActionSequenceFromFile(
	INT_PTR hWnd, BSTR bstrFile, BSTR bstrDesc, BSTR bstrSaveAs, 
	IProgressIndicator2 *pIStatus, IDataObject *pIInData, VARIANT_BOOL fInitNew, 
	IDataObject **ppIOutData)
{
	_ASSERTE(NULL == hWnd || IsWindow(reinterpret_cast<HWND>(hWnd)));
	_ASSERTE(NULL != bstrFile);

	if (NULL == bstrFile || 0 == ::SysStringLen(bstrFile))
		return E_INVALIDARG;

	if (!IsWindow(reinterpret_cast<HWND>(hWnd)))
		hWnd = reinterpret_cast<INT_PTR>(__hWndM);		// reinterpret_cast<INT_PTR>(::GetActiveWindow());

	USES_CONVERSION;

LPCSTR pcFile = OLE2A(bstrFile);
LPCSTR pcDesc = (NULL != bstrDesc && ::SysStringLen(bstrDesc) > 0) ? OLE2A(bstrDesc) : NULL;
LPCSTR pcSaveAs = (NULL != ::SysStringLen(bstrSaveAs) > 0) ? OLE2A(bstrSaveAs) : NULL;
WProgressIndicator Status;

	if (NULL != pIStatus)
		pIStatus -> QueryInterface(Status.ppi());

	GENERATE_ERROR_NOASSERT(RunPropertyActionSequence(
		reinterpret_cast<HWND>(hWnd), pcFile, NULL, pcDesc, pcSaveAs, 
		Status, pIInData, ppIOutData, fInitNew ? TRUE : FALSE, m_CtxData, TRUE));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CPropertySequenceService::get_ResourceModule (BSTR *pbstrModule)
{
	if (NULL == pbstrModule)
		return E_POINTER;
	*pbstrModule = NULL;

CComBSTR bstr (m_bstrModule);

	*pbstrModule = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CPropertySequenceService::put_ResourceModule (BSTR bstrModule)
{
	m_bstrModule = bstrModule;
	return S_OK;
}

STDMETHODIMP CPropertySequenceService::putref_ContextData(ITRiASDataObject *pICtxData)
{
	ATLTRACE(_T("CPropertySequenceService::put_ContextData\n"));
	m_CtxData = pICtxData;
	return S_OK;
}

STDMETHODIMP CPropertySequenceService::get_ContextData(ITRiASDataObject **ppICtxData)
{
	ATLTRACE(_T("CPropertySequenceService::get_ContextData\n"));
	if (NULL == ppICtxData) 
		return E_POINTER;
	*ppICtxData = NULL;

	if (m_CtxData.IsValid()) {
	WTRiASDataObject TDO (m_CtxData);

		*ppICtxData = TDO.detach();
		return S_OK;
	}
	return S_FALSE;
}

#endif // defined(_USE_XML_GEOCOMPONENTS)

