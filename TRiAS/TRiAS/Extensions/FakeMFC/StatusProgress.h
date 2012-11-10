///////////////////////////////////////////////////////////////////////////
// @doc 
// @module StatusProgress.h | Declaration of the <c CStatusProgress> class

#if !defined(_STATUSPROGRESS_H__8FB5DAD4_E4BD_11D1_8610_00600875138A__INCLUDED_)
#define _STATUSPROGRESS_H__8FB5DAD4_E4BD_11D1_8610_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <istatus.h>
#include <AtlComx.h>

#include "fakemfc.h"		// main symbols
#include "AtlSingletonCF.h"	// SingletonClassFactory

/////////////////////////////////////////////////////////////////////////////
// CStatusProgress
class ATL_NO_VTABLE CStatusProgress : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CStatusProgress, &CLSID_StatusProgress>,
	public ISupportErrorInfo,
	public IProgressIndicator,
	public IDispatchImpl<IStatusProgress, &IID_IStatusProgress, &LIBID_ToolBarLib, 
				TOOLBAR_TYPELIB_VERSION_MAJOR, TOOLBAR_TYPELIB_VERSION_MINOR>
{
public:
	CStatusProgress()
	{
	}

	DECLARE_CLASSFACTORY_EX(CComSingletonFactory<CStatusProgress>)
	DECLARE_REGISTRY_RESOURCEID(IDR_STATUSPROGRESS)

	BEGIN_COM_MAP(CStatusProgress)
		COM_INTERFACE_ENTRY(IStatusProgress)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY_EX(IProgressIndicator)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease()
	{
		CComSingletonFactory<CStatusProgress>::ResetInstance();
	}

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IStatusProgress
public:
	STDMETHOD(get_ProgressControlActive)(/*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(StepProgress)(void);
	STDMETHOD(SetProgress)(/*[in]*/ int iPos);
	STDMETHOD(InitializeProgressControl)(/*[in]*/ BSTR pcszMsg, /*[in]*/ int iLow, /*[in]*/ int iHigh, /*[in]*/ VARIANT_BOOL bResetPos, /*[retval][out]*/ VARIANT_BOOL *pSuccess);
	STDMETHOD(UninitializeProgressControl)(void);
	STDMETHOD(get_ProgressText)(BSTR *pVal);
	STDMETHOD(put_ProgressText)(BSTR newVal);

// IProgressIndicator 
	STDMETHOD_(HWND, InitNew)(HWND hWnd, DWORD dwReserved);
	STDMETHOD(Restart)(long uiMinPos, long ulMaxPos, DWORD dwFlags);
	STDMETHOD(ChangeText)(DWORD dwWhichText, LPCSTR pcNewText);
	STDMETHOD(RetrieveText)(DWORD dwWichText, LPSTR cbText, ULONG uiLen);

	STDMETHOD_(int, SetPosition)(long uiNewPos);
	STDMETHOD_(BOOL, WasCanceled)();
	STDMETHOD(get_Canceled)(VARIANT_BOOL *pfWasCanceled);
};

#endif // !defined(_STATUSPROGRESS_H__8FB5DAD4_E4BD_11D1_8610_00600875138A__INCLUDED_)
