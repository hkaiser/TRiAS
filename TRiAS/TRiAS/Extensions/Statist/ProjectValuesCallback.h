// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 01.09.2001 21:20:56 
//
// @doc
// @module ProjectValuesCallback.h | Declaration of the <c CProjectValuesCallback> class

#if defined(_USE_PROJECTVALUES)

#include "resource.h"
#include <dtoolbar.h>

#include "Statist.h"

/////////////////////////////////////////////////////////////////////////////
// CProjectValuesCallback

class ATL_NO_VTABLE CProjectValuesCallback : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CProjectValuesCallback, &CLSID_ProjectValuesCallback>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITabWindowCallback, &IID_ITabWindowCallback, &LIBID_ToolBarLib,
		TOOLBAR_TYPELIB_VERSION_MAJOR, TOOLBAR_TYPELIB_VERSION_MINOR>
{
public:
// Construction
	CProjectValuesCallback() : m_pCmdTarget(NULL) {}
	~CProjectValuesCallback() {}

// Initialisation
	void SetCmdTarget (CStatist *pCmdTarget)
	{
		_ASSERTE(NULL == m_pCmdTarget && NULL != pCmdTarget);	// nur einmal und dann richtig rufen
		m_pCmdTarget = pCmdTarget;
	}

// Operations
	DECLARE_NOT_AGGREGATABLE(CProjectValuesCallback)
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_NO_REGISTRY()

// Interface map
	BEGIN_COM_MAP(CProjectValuesCallback)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ITabWindowCallback)
	END_COM_MAP()

// Implementation
protected:
// Attributes

// Operations

// Interfaces
public:
// ISupportsErrorInfo
	STDMETHODIMP InterfaceSupportsErrorInfo(REFIID riid);

// ITabWindowCallback
	STDMETHODIMP get_MayAddTabWindow(VARIANT_BOOL *pfMayAdd);
	STDMETHODIMP AddTabWindow();
	STDMETHODIMP DeleteTabWindow();

private:
	CStatist *m_pCmdTarget;
};

#endif // defined(_USE_PROJECTVALUES)
