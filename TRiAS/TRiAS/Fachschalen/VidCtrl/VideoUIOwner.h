// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 01.07.2002 11:51:21 
//
// @doc
// @module VideoUIOwner.h | Declaration of the <c CVideoUIOwner> class

#if !defined(_VIDEOUIOWNER_H__850CDD55_33EE_4C41_9180_E830B51A3FC3__INCLUDED_)
#define _VIDEOUIOWNER_H__850CDD55_33EE_4C41_9180_E830B51A3FC3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// 6CD1B760-C209-4624-BC0F-BA24985BDDB4
EXTERN_C const GUID __declspec(selectany) CLSID_VideoUIOwner = 
	{ 0x6CD1B760, 0xC209, 0x4624, 0xBC, 0x0F, 0xBA, 0x24, 0x98, 0x5B, 0xDD, 0xB4 };

/////////////////////////////////////////////////////////////////////////////
// CVideoUIOwner
class CVidCtrlExtension;

class ATL_NO_VTABLE CVideoUIOwner : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVideoUIOwner, &CLSID_VideoUIOwner>,
	public ITRiASUIOwner
{
public:
// Construction
	CVideoUIOwner() : m_pCmdTarget(NULL) {}
	~CVideoUIOwner() {}

// Initialisation
	void SetCmdTarget(CVidCtrlExtension *pTarget) 
	{
		_ASSERTE(NULL == m_pCmdTarget && NULL != pTarget);		// nur einmal initialisieren
		m_pCmdTarget = pTarget;
	}

// Operations
	DECLARE_NOT_AGGREGATABLE(CVideoUIOwner)
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_NO_REGISTRY()

// Interface map
	BEGIN_COM_MAP(CVideoUIOwner)
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
	CVidCtrlExtension *m_pCmdTarget;
};

#endif // !defined(_VIDEOUIOWNER_H__850CDD55_33EE_4C41_9180_E830B51A3FC3__INCLUDED_)
