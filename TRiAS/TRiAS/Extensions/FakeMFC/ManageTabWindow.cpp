// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.03.2001 13:49:16 
//
// @doc
// @module ManageTabWindow.cpp | Definition of the <c CManageTabWindows> class

#include "stdafx.h"

#if defined(_USE_DOCKEDTABWINDOW)

#include "Fakemfc.h"
#include "ManageTabWindow.h"

/////////////////////////////////////////////////////////////////////////////
// CManageTabWindows

STDMETHODIMP CManageTabWindows::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IManageTabWindows
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// IManageTabWindows
STDMETHODIMP CManageTabWindows::get_Visible (VARIANT_BOOL *pfVisible)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	_ASSERTE(NULL != m_pDockingTab);
	return m_pDockingTab -> get_Visible (pfVisible);	
}

STDMETHODIMP CManageTabWindows::put_Visible (VARIANT_BOOL fVisible)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	_ASSERTE(NULL != m_pDockingTab);
	return m_pDockingTab -> put_Visible (fVisible);	
}

STDMETHODIMP CManageTabWindows::get_Count(int *pfCount)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	_ASSERTE(NULL != m_pDockingTab);
	return m_pDockingTab -> get_Count(pfCount);
}

STDMETHODIMP CManageTabWindows::get_ActiveTabWindow (INT_PTR *phHandle)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	_ASSERTE(NULL != m_pDockingTab);
	return m_pDockingTab -> get_ActiveTabWindow (phHandle);
}

STDMETHODIMP CManageTabWindows::get_ParentWindow (INT_PTR *phHandle)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	_ASSERTE(NULL != m_pDockingTab);
	return m_pDockingTab -> get_ParentWindow (phHandle);
}

STDMETHODIMP CManageTabWindows::FindTabWindow (BSTR bstrName, INT_PTR *phHandle)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	_ASSERTE(NULL != m_pDockingTab);
	return m_pDockingTab -> FindTabWindow(bstrName, phHandle);
}

STDMETHODIMP CManageTabWindows::AddTabWindow (INT_PTR hWnd, BSTR bstrName, VARIANT vPict, INT_PTR *phHandle)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	_ASSERTE(NULL != m_pDockingTab);
	return m_pDockingTab -> AddTabWindow (hWnd, bstrName, vPict, phHandle);
}

STDMETHODIMP CManageTabWindows::DeleteTabWindow (INT_PTR hHandle)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	_ASSERTE(NULL != m_pDockingTab);
	return m_pDockingTab -> DeleteTabWindow (hHandle, FALSE);
}

STDMETHODIMP CManageTabWindows::ActivateTabWindow (INT_PTR hHandle)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	_ASSERTE(NULL != m_pDockingTab);
	return m_pDockingTab -> ActivateTabWindow (hHandle);
}

STDMETHODIMP CManageTabWindows::AddTabWindowDelayed (BSTR bstrName, ITabWindowCallback *pICallback)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	_ASSERTE(NULL != m_pDockingTab);
	return m_pDockingTab -> AddTabWindowDelayed (bstrName, pICallback);
}

STDMETHODIMP CManageTabWindows::DeleteTabWindowDelayed (INT_PTR hHandle)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	_ASSERTE(NULL != m_pDockingTab);
	return m_pDockingTab -> DeleteTabWindow (hHandle, TRUE);
}

///////////////////////////////////////////////////////////////////////////////
// Setzen des Bildchens
STDMETHODIMP CManageTabWindows::SetTabIcon(INT_PTR hHandle, VARIANT vIcon)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	_ASSERTE(NULL != m_pDockingTab);
	return m_pDockingTab -> SetTabIcon (hHandle, vIcon);
}

///////////////////////////////////////////////////////////////////////////////
// Umbenennen einer Tablasche
STDMETHODIMP CManageTabWindows::RenameTabWindow (BSTR bstrOldName, BSTR bstrNewName)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	_ASSERTE(NULL != m_pDockingTab);
	return m_pDockingTab -> RenameTabWindow (bstrOldName, bstrNewName);
}

#endif // defined(_USE_DOCKEDTABWINDOW)
