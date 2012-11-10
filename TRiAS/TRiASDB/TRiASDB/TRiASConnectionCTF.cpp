// $Header: $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 07/10/1998 10:50:11 PM
//
// @doc
// @module TRiASConnectionCTF.cpp | Implementation of the <c CTRiASConnectionCTF> class

#include "stdafx.h"

#include "TRiASDBGuids.h"
#include "Strings.h"
#include "Wrapper.h"

#include "TRiASConnectionCTF.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASConnectionCTF

/////////////////////////////////////////////////////////////////////////////
// PropertySupport
// Callback-interface, welches für die Konkretheit der Properties zuständig ist

STDMETHODIMP CTRiASConnectionCTF::PutValue (BSTR Name, VARIANT Value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASConnectionCTF::GetValue (BSTR Name, VARIANT *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnectionCTF::GetValue");
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASConnectionCTF::PutType (BSTR Name, PROPERTY_TYPE Value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASConnectionCTF::GetType (BSTR Name, PROPERTY_TYPE *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnectionCTF::GetType");
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASConnectionCTF::PutValueAndType(BSTR Name, VARIANT Val, PROPERTY_TYPE Type)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASConnectionCTF::GetValueAndType(BSTR Name, VARIANT * pVal, PROPERTY_TYPE * pType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal || NULL == pType)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASConnectionCTF::GetType");
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
// CTF neu einlesen
STDMETHODIMP CTRiASConnectionCTF::Refresh()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// IObjectWithSite
STDMETHODIMP CTRiASConnectionCTF::SetSite (IUnknown *pISite)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL != pISite)
		return pISite -> QueryInterface(m_Conn.ppi());
	else {
		m_Conn.Assign(NULL);
		return S_OK;
	}
}

STDMETHODIMP CTRiASConnectionCTF::GetSite (REFIID riid, void **ppvSite)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_Conn) 
		return REPORT_DBERROR(TRIASDB_E_PROPERTY_NOT_INITIALIZED);
	return m_Conn -> QueryInterface (riid, ppvSite);
}

