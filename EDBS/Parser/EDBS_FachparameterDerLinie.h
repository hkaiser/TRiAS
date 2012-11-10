// EDBS_FachparameterDerLinie.h : Deklaration von CEDBS_FachparameterDerLinie

#ifndef __EDBS_FACHPARAMETERDERLINIE_H_
#define __EDBS_FACHPARAMETERDERLINIE_H_

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CEDBS_FachparameterDerLinie
class ATL_NO_VTABLE CEDBS_FachparameterDerLinie : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEDBS_FachparameterDerLinie, &CLSID_EDBS_FachparameterDerLinie>,
	public IDispatchImpl<IEDBS_FachparameterDerLinie, &IID_IEDBS_FachparameterDerLinie, &LIBID_TRiAS_EDBS>
{
public:
	CEDBS_FachparameterDerLinie();
	~CEDBS_FachparameterDerLinie();

DECLARE_REGISTRY_RESOURCEID(IDR_EDBS_FACHPARAMETERDERLINIE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEDBS_FachparameterDerLinie)
	COM_INTERFACE_ENTRY(IEDBS_FachparameterDerLinie)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IEDBS_FachparameterDerLinie
public:
	STDMETHOD(get_Item)(/*[in, out]*/ VARIANT* vntIndexKey, /*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown* *pVal);
	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
	CObList mlstFachparameter;

};

#endif //__EDBS_FACHPARAMETERDERLINIE_H_
