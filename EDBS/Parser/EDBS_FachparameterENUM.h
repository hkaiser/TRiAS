// EDBS_FachparameterENUM.h : Deklaration von CEDBS_FachparameterENUM

#ifndef __EDBS_FACHPARAMETERENUM_H_
#define __EDBS_FACHPARAMETERENUM_H_

#include "resource.h"       // Hauptsymbole
#include "EDBS_FachparameterDerLinie.h"

/////////////////////////////////////////////////////////////////////////////
// CEDBS_FachparameterENUM
class ATL_NO_VTABLE CEDBS_FachparameterENUM : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEDBS_FachparameterENUM, &CLSID_EDBS_FachparameterENUM>,
	public IDispatchImpl<IEDBS_FachparameterENUM, &IID_IEDBS_FachparameterENUM, &LIBID_TRiAS_EDBS>,
	public IEnumVARIANT
{
public:
	CEDBS_FachparameterENUM();

DECLARE_REGISTRY_RESOURCEID(IDR_EDBS_FACHPARAMETERENUM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEDBS_FachparameterENUM)
	COM_INTERFACE_ENTRY(IEDBS_FachparameterENUM)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IEnumVARIANT)
END_COM_MAP()

// IEDBS_FachparameterENUM
public:
	POSITION mpos;
	CEDBS_FachparameterDerLinie *mpobjsFachparameter;
// IEnumVARIANT
	STDMETHOD(Next)(ULONG celt, VARIANT * rgvar, ULONG * pceltFetched);
	STDMETHOD(Skip)(ULONG celt);
	STDMETHOD(Clone)(IEnumVARIANT * * ppenum);
	STDMETHOD(Reset)();
};

#endif //__EDBS_FACHPARAMETERENUM_H_
