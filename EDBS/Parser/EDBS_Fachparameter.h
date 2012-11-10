// EDBS_Fachparameter.h : Deklaration von CEDBS_Fachparameter

#ifndef __EDBS_FACHPARAMETER_H_
#define __EDBS_FACHPARAMETER_H_

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CEDBS_Fachparameter
class ATL_NO_VTABLE CEDBS_Fachparameter : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEDBS_Fachparameter, &CLSID_EDBS_Fachparameter>,
	public IDispatchImpl<IEDBS_Fachparameter, &IID_IEDBS_Fachparameter, &LIBID_TRiAS_EDBS>
{
public:
	CEDBS_Fachparameter();
	~CEDBS_Fachparameter();

DECLARE_REGISTRY_RESOURCEID(IDR_EDBS_FACHPARAMETER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEDBS_Fachparameter)
	COM_INTERFACE_ENTRY(IEDBS_Fachparameter)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IEDBS_Fachparameter
public:
	STDMETHOD(get_Wert)(/*[out, retval]*/ BSTR *pVal);
//	STDMETHOD(put_Wert)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Kennung)(/*[out, retval]*/ BSTR *pVal);
//	STDMETHOD(put_Kennung)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Art)(/*[out, retval]*/ BSTR *pVal);
//	STDMETHOD(put_Art)(/*[in]*/ BSTR newVal);
	CString mstrArtDesFachparameters;
	CString mstrKennungDesFachparameters;
	CString mstrWertDesFachparameters;
};

#endif //__EDBS_FACHPARAMETER_H_
