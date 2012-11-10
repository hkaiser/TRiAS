// ImportDBEngine.h: Definition of the ImportDBEngine class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPORTDBENGINE_H__7BACA174_8C1B_11D1_A00E_0060975566B4__INCLUDED_)
#define AFX_IMPORTDBENGINE_H__7BACA174_8C1B_11D1_A00E_0060975566B4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CImportDBEngine

class CImportDBEngine : 
	public CComCoClass<CImportDBEngine,&CLSID_ImportDBEngine>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CImportDBEngine>,
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ITRiASDBEngine, &IID_ITRiASDBEngine, &LIBID_TRiASDB, 
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	typedef CComCoClass<CImportDBEngine, &CLSID_ImportDBEngine> base_t;

	CImportDBEngine() {}

	DECLARE_REGISTRY_RESOURCEID(IDR_ImportDBEngine)

	DECLARE_CLASSFACTORY_SINGLETON(CImportDBEngine)	// DBEngines existieren nur einmal

BEGIN_COM_MAP(CImportDBEngine)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ITRiASDBEngine)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(CImportDBEngine) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

BEGIN_CONNECTION_POINT_MAP(CImportDBEngine)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ErrorHandling
	HRESULT Error (HRESULT hr, LPCTSTR pcRoutine = NULL, REFIID riid = IID_ITRiASDBEngine)
		{ 
			CString str; str.FormatMessage ((UINT)hr, g_cbTRiAS, pcRoutine);
			return base_t::Error (str, riid, DISP_E_EXCEPTION); 
		}
	HRESULT Error (LPCTSTR pcText, HRESULT hr = DISP_E_EXCEPTION, REFIID riid = IID_ITRiASDBEngine)
		{ return base_t::Error (pcText, riid, hr); }

// ITRiASDBEngine
public:
	STDMETHOD(put_UserName)(/*[in]*/ BSTR newVal);
	STDMETHOD(put_Password)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Version)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);

	STDMETHOD(Start)();
	STDMETHOD(EnumDataBaseTypes)(/*[out, retval]*/ IUnknown **ppIEnum);
	STDMETHOD(Stop)();
};

#endif // !defined(AFX_IMPORTDBENGINE_H__7BACA174_8C1B_11D1_A00E_0060975566B4__INCLUDED_)
