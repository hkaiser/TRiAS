// EDBS_BesondereInformationen.h : Deklaration von CEDBS_BesondereInformationen

#ifndef __EDBS_BESONDEREINFORMATIONEN_H_
#define __EDBS_BESONDEREINFORMATIONEN_H_

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CEDBS_BesondereInformationen
class ATL_NO_VTABLE CEDBS_BesondereInformationen : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEDBS_BesondereInformationen, &CLSID_EDBS_BesondereInformationen>,
	public IDispatchImpl<IEDBS_BesondereInformationen, &IID_IEDBS_BesondereInformationen, &LIBID_TRiAS_EDBS>
{
public:
	CEDBS_BesondereInformationen();
	~CEDBS_BesondereInformationen();

DECLARE_REGISTRY_RESOURCEID(IDR_EDBS_BESONDEREINFORMATIONEN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEDBS_BesondereInformationen)
	COM_INTERFACE_ENTRY(IEDBS_BesondereInformationen)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IEDBS_BesondereInformationen
public:
	STDMETHOD(get_Item)(/*[in, out]*/ VARIANT* vntIndexKey, /*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown* *pVal);
	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
	CObList mlstBesondereInformationen;
};

#endif //__EDBS_BESONDEREINFORMATIONEN_H_
