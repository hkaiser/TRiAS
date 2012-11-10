// EDBS_Linien.h : Deklaration von CEDBS_Linien

#ifndef __EDBS_LINIEN_H_
#define __EDBS_LINIEN_H_

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CEDBS_Linien
class ATL_NO_VTABLE CEDBS_Linien : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEDBS_Linien, &CLSID_EDBS_Linien>,
	public IDispatchImpl<IEDBS_Linien, &IID_IEDBS_Linien, &LIBID_TRiAS_EDBS>
{
public:
	CEDBS_Linien();
	~CEDBS_Linien();

DECLARE_REGISTRY_RESOURCEID(IDR_EDBS_LINIEN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEDBS_Linien)
	COM_INTERFACE_ENTRY(IEDBS_Linien)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IEDBS_Linien
public:
	STDMETHOD(get_Item)(/*[in, out]*/ VARIANT* vntIndexKey, /*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown* *pVal);
	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
	CObList mlstLinien;

};

#endif //__EDBS_LINIEN_H_
