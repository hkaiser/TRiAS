// ErrorStack.cpp : Implementation of CErrorStack
#include "stdafx.h"
#include "TErrTrkImpl.h"
#include "ErrorStack.h"

HRESULT CErrorStack::FinalConstruct() {
	ATLTRY(m_Enum = new NEnumWErrorItem());
	if (!m_Enum) 
		return E_OUTOFMEMORY;
	m_Enum -> Release();	// Konstruktor hinterläßt RefCnt==1
	return S_OK;
}

HRESULT CErrorStack::FinalRelease() {
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CErrorStack

STDMETHODIMP CErrorStack::Push(IUnknown * pIError){
	try {
		WErrorItem	item( CLSID_ErrorItem );
		if( SUCCEEDED( item->CloneFrom( pIError ) ) )
			m_Enum->AddItem( item );
	} catch(...) {
		DWORD dwErr = ::GetLastError();
		_ASSERTE(NULL);
	}
	return S_OK;
}

STDMETHODIMP CErrorStack::get_Count(ULONG* pItems) {
	if( NULL == pItems )
		return E_POINTER;
	*pItems = m_Enum->Count( );
	return S_OK;
}

STDMETHODIMP CErrorStack::Clear() {
	return m_Enum->Clear();
}

STDMETHODIMP CErrorStack::_newEnum(IUnknown * * ppIEnum) {
	return MakeEnumVARIANT (m_Enum, GetUnknown(), ppIEnum);
}
