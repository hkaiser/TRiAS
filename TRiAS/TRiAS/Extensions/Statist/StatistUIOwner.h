// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 15.09.2001 09:19:17 
//
// @doc
// @module StatistUIOwner.h | Declaration of the <c CStatistUIOwner> class

#if !defined(_STATISTUIOWNER_H__9005395B_B54E_4120_9F3A_6DA438956F04__INCLUDED_)
#define _STATISTUIOWNER_H__9005395B_B54E_4120_9F3A_6DA438956F04__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CStatistUIOwner

class ATL_NO_VTABLE CStatistUIOwner : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStatistUIOwner, &CLSID_StatistUIOwner>,
	public ITRiASUIOwner
{
public:
// Construction
	CStatistUIOwner() : m_pCmdTarget(NULL) {}
	~CStatistUIOwner() {}

// Initialisation
	void SetCmdTarget(CStatist *pTarget) 
	{
		_ASSERTE(NULL == m_pCmdTarget && NULL != pTarget);		// nur einmal initialisieren
		m_pCmdTarget = pTarget;
	}

// Operations
	DECLARE_NOT_AGGREGATABLE(CStatistUIOwner)
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_NO_REGISTRY()

// Interface map
	BEGIN_COM_MAP(CStatistUIOwner)
		COM_INTERFACE_ENTRY(ITRiASUIOwner)
	END_COM_MAP()

// Implementation
protected:
// Attributes

// Operations

// Interfaces
public:
// *** ITRiASUIOwner specific functions ***
	STDMETHODIMP OnUpdateUI (ITRiASBar *pIBar, ITRiASCmdUI *pCmdUI);
	STDMETHODIMP OnSelect (ITRiASBar *pIBar, UINT uiID, LPSTR pBuffer, ULONG uiLen, ULONG *pulWritten);
	STDMETHODIMP OnCommand (ITRiASBar *pIBar, UINT uiID, int nCode);

private:
	CStatist *m_pCmdTarget;
};

#endif // !defined(_STATISTUIOWNER_H__9005395B_B54E_4120_9F3A_6DA438956F04__INCLUDED_)
