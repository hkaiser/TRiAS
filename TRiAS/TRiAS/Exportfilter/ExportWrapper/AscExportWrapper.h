// @doc
// @module AscExportWrapper.h | Declaration of the <c CAscExportWrapper> class

#ifndef __ASCEXPORTWRAPPER_H_
#define __ASCEXPORTWRAPPER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAscExportWrapper
class ATL_NO_VTABLE CAscExportWrapper : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAscExportWrapper, &CLSID_AscExportWrapper>,
	public ISupportErrorInfo,
	public IDispatchImpl<IAscExportWrapper, &IID_IAscExportWrapper, &LIBID_EXPWRAPLib>
{
public:
	CAscExportWrapper()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_ASCEXPORTWRAPPER)

	BEGIN_COM_MAP(CAscExportWrapper)
		COM_INTERFACE_ENTRY(IAscExportWrapper)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IAscExportWrapper
public:
	STDMETHOD(Initialize)(/*[in]*/ BSTR RegKey);
	STDMETHOD(EndObject)(/*[in]*/ HOBJECT ObjHandle);
	STDMETHOD(BeginObject)(/*[in]*/ HOBJECT ObjHandle);
	STDMETHOD(ExportRelation)(/*[in]*/ HRELATION RelHandle, /*[in]*/ RELTYPE Type,  /*[in]*/ HOBJECT ObjHandle);
	STDMETHOD(ExportFeature)(/*[in]*/ VARIANT Feature);
	STDMETHOD(ExportGeometry)(/*[in]*/ OBJECTTYPE Type, /*[in]*/ IUnknown *pIGeom);
	STDMETHOD(ExportTrailer)(/*[in]*/ BSTR TrailerInfo);
	STDMETHOD(ExportDescription)(/*[in]*/ BSTR KeyInfo, /*[in]*/ BSTR Description, /*[in, optional, defaultvalue]*/ DWORD dwStyle);
	STDMETHOD(ExportHeader)(/*[in]*/ BSTR Header);
	STDMETHOD(ExportComment)(/*[in]*/ BSTR Comment);
	STDMETHOD(ExportBegin)(/*[in]*/ BSTR Name, /*[in]*/ OUTMODE Mode);
};

#endif //__ASCEXPORTWRAPPER_H_
