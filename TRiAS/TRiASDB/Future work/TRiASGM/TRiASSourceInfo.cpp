// TRiASSourceInfo.cpp : Implementation of CTRiASSourceInfo
#include "stdafx.h"

#include "TRiASGM.h"
#include "TRiASSourceInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASSourceInfo

STDMETHODIMP CTRiASSourceInfo::get_Handle(HPROJECT * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return E_POINTER;

	*pVal = m_hPr;
	return S_OK;
}

STDMETHODIMP CTRiASSourceInfo::put_Handle(HPROJECT newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_hPr = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASSourceInfo::get_TableName(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return E_POINTER;

CComBSTR bstr (m_bstrTableName);

	if (!bstr)
		return E_OUTOFMEMORY;
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASSourceInfo::put_TableName(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_bstrTableName = newVal;
	if (!m_bstrTableName)
		return E_OUTOFMEMORY;
	return S_OK;
}

STDMETHODIMP CTRiASSourceInfo::get_CoordSystemType(VARIANT * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return E_POINTER;

CComVariant val (m_CsGuid);

	return val.Detach (pVal);
}

STDMETHODIMP CTRiASSourceInfo::put_CoordSystemType(VARIANT newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return m_CsGuid.Copy(&newVal);
}

STDMETHODIMP CTRiASSourceInfo::get_Ident(LONG * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return E_POINTER;

	*pVal = m_lIdent;
	return S_OK;
}

STDMETHODIMP CTRiASSourceInfo::put_Ident(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_lIdent = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASSourceInfo::get_Types(DWORD * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return E_POINTER;

	*pVal = m_dwTypes;
	return S_OK;
}

STDMETHODIMP CTRiASSourceInfo::put_Types(DWORD newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_dwTypes = newVal;
	return S_OK;
}
