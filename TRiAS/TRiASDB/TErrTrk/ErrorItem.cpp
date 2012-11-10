// ErrorItem.cpp : Implementation of CTErrTrkApp and DLL registration.

#include "stdafx.h"
#include "TErrTrkImpl.h"
#include "ErrorItem.h"

HRESULT CErrorItem::FinalConstruct() {
	return S_OK;
}

HRESULT CErrorItem::FinalRelease() {
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CErrorItem::InterfaceSupportsErrorInfo(REFIID riid) {
	static const IID* arr[] = {
		&IID_IErrorItem,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++) {
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//////////////////////////////////////////////////////////////////////////
// IErrorInfo
STDMETHODIMP CErrorItem::GetDescription(BSTR * pbstrDescription) {
	_ASSERTE(NULL != pbstrDescription);
	*pbstrDescription = ::SysAllocString( m_strDescr );
	return S_OK;
}
STDMETHODIMP CErrorItem::GetGUID(GUID * pguid) {
	_ASSERTE(NULL != pguid);
	*pguid = m_guidOfIF;
	return S_OK;
}
STDMETHODIMP CErrorItem::GetHelpContext(DWORD * pdwHelpContext) {
	_ASSERTE(NULL != pdwHelpContext);
	*pdwHelpContext = m_dwContext;
	return S_OK;
}
STDMETHODIMP CErrorItem::GetHelpFile(BSTR * pbstrHelpFile) {
	_ASSERTE(NULL != pbstrHelpFile);
	*pbstrHelpFile = ::SysAllocString( m_strHelp );
	return S_OK;
}
STDMETHODIMP CErrorItem::GetSource(BSTR * pbstrSource) {
	_ASSERTE(NULL != pbstrSource);
	*pbstrSource = ::SysAllocString( m_strSource );
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// ICreateErrorInfo
STDMETHODIMP CErrorItem::SetDescription(BSTR szDescription) {
	m_strDescr = szDescription;
	return S_OK;
}
STDMETHODIMP CErrorItem::SetGUID(REFGUID rguid) {
	m_guidOfIF = rguid;
	return S_OK;
}
STDMETHODIMP CErrorItem::SetHelpContext(DWORD dwHelpContext) {
	m_dwContext = dwHelpContext;
	return S_OK;
}
STDMETHODIMP CErrorItem::SetHelpFile(BSTR szHelpFile) {
	m_strHelp = szHelpFile;
	return S_OK;
}
STDMETHODIMP CErrorItem::SetSource(BSTR szSource) {
	m_strSource = szSource;
	return S_OK;
}

STDMETHODIMP CErrorItem::get_GUID(BSTR* strGUID) {
	BSTR	b;
	if( !SUCCEEDED( ::StringFromCLSID( m_guidOfIF, &b ) ) )
		return E_FAIL;
	*strGUID = ::SysAllocString( b );
	return S_OK;
}

STDMETHODIMP CErrorItem::CloneFrom(IUnknown * pErrInfo) {
	try {
		WErrorInfo	inf(pErrInfo);
		inf->GetDescription( &m_strDescr );
		inf->GetHelpFile( &m_strHelp );
		inf->GetHelpContext( &m_dwContext );
		inf->GetSource( &m_strSource );
		inf->GetGUID( &m_guidOfIF );
	} catch(...) {
		return E_FAIL;
	}
	return S_OK;
}
