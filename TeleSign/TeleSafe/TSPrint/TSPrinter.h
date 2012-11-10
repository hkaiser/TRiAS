// TSPrinter.h : Deklaration von CTSPrinter

#ifndef __TSPRINTER_H_
#define __TSPRINTER_H_

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CTSPrinter
class ATL_NO_VTABLE CTSPrinter : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTSPrinter, &CLSID_TSPrinter>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITSPrinter, &IID_ITSPrinter, &LIBID_TSPRINTLib>
{
public:
	CTSPrinter();
	~CTSPrinter();

DECLARE_REGISTRY_RESOURCEID(IDR_TSPRINTER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTSPrinter)
	COM_INTERFACE_ENTRY(ITSPrinter)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITSPrinter
public:
	STDMETHOD(spezial1)();
	STDMETHOD(SavePage)(/*[in]*/BSTR strFileName, /*[out,retval]*/long* pResult);
	STDMETHOD(LoadPrinterOutput)(/*[in]*/BSTR strFileName, /*[out,retval]*/long* pResult);
	STDMETHOD(TSFormatMessage)(/*[in]*/ long lError, /*[out]*/ BSTR* strMessage, /*[out,retval]*/long* pResult);
	STDMETHOD(DeleteTSPrinter)(/*[out,retval]*/long* pResult);
	STDMETHOD(DeleteTSPrinterDriver)(/*[out,retval]*/long* pResult);
	STDMETHOD(DeleteTSPort)(/*[in]*/ long hWnd, /*[out,retval]*/ long* pResult);
	STDMETHOD(DeleteTSMonitor)(/*[out,retval]*/ long* pResult);
	STDMETHOD(AddTSPrinter)(/*[out,retval]*/ long* pResult);
	STDMETHOD(AddTSPrinterDriver)(/*[out,retval]*/ long* pResult);
	STDMETHOD(AddTSPort)(/*[in]*/ long hWnd, /*[out,retval]*/ long* pResult);
	STDMETHOD(AddTSMonitor)(/*[out,retval]*/ long* pResult);
private:

};

#endif //__TSPRINTER_H_
