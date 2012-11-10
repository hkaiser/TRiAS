// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 30.10.2002 13:48:08 
//
// @doc
// @module TRiASDataObject.h | Declaration of the <c CTRiASDataObject> class

#if !defined(_TRIASDATAOBJECT_H__FC7BFA92_E720_4FE0_817F_BE4CD91CE77E__INCLUDED_)
#define _TRIASDATAOBJECT_H__FC7BFA92_E720_4FE0_817F_BE4CD91CE77E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// CTRiASDataObject class
class CTRiASDataObject :
	public CComObjectRootEx<CComSingleThreadModel>,
	IDispatchImpl<ITRiASDataObject, &IID_ITRiASDataObject, &LIBID_TRiASHelperLib, 
				TYPELIB_HELPER_VERSION_MAJOR, TYPELIB_HELPER_VERSION_MINOR>,
	ISupportErrorInfoImpl<&IID_ITRiASDataObject>,
	public CComCoClass<CTRiASDataObject, &CLSID_DataTransferObject>
{
public:
	CTRiASDataObject()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASDATAOBJECT)
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	HRESULT FinalConstruct()
	{
		RETURN_FAILED_HRESULT(m_DataObj.CreateInstance(CLSID_TRiASDataObject, 
			CLSCTX_INPROC_SERVER, GetControllingUnknown()));
		return S_OK;
	}
	void FinalRelease()
	{
		m_DataObj.Assign(NULL);
	}
		
	BEGIN_COM_MAP(CTRiASDataObject)
		COM_INTERFACE_ENTRY(ITRiASDataObject)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_DataObj.p)
	END_COM_MAP()


// ITRiASDataObject
public:
	STDMETHODIMP SetObjects(DGeoObjects *pIObjs);
	STDMETHODIMP GetObjects(DGeoObjects **ppIObjs);
	STDMETHODIMP SetData(BSTR Name, VARIANT Data);
	STDMETHODIMP GetData(BSTR Name, VARIANT *Data);
	STDMETHODIMP GetObjectWin(DGeoObjectWin **ObjWin);

private:
	WUnknown m_DataObj;
};

#endif // !defined(_TRIASDATAOBJECT_H__FC7BFA92_E720_4FE0_817F_BE4CD91CE77E__INCLUDED_)
