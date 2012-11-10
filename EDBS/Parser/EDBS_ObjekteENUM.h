// EDBS_ObjekteENUM.h : Deklaration von CEDBS_ObjekteENUM

#ifndef __EDBS_OBJEKTEENUM_H_
#define __EDBS_OBJEKTEENUM_H_

#include "resource.h"       // Hauptsymbole
#include "EDBS_Objekte.h"
//#import "C:\WINNT\System32\StdOle2.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 
/////////////////////////////////////////////////////////////////////////////
// CEDBS_ObjekteENUM
class ATL_NO_VTABLE CEDBS_ObjekteENUM : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEDBS_ObjekteENUM, &CLSID_EDBS_ObjekteENUM>,
	public IDispatchImpl<IEDBS_ObjekteENUM, &IID_IEDBS_ObjekteENUM, &LIBID_TRiAS_EDBS>,
	public IEnumVARIANT
{
public:
	CEDBS_ObjekteENUM();

DECLARE_REGISTRY_RESOURCEID(IDR_EDBS_OBJEKTEENUM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEDBS_ObjekteENUM)
	COM_INTERFACE_ENTRY(IEDBS_ObjekteENUM)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IEnumVARIANT)
END_COM_MAP()

// IEDBS_ObjekteENUM
public:
	POSITION mpos;
	CEDBS_Objekte *mpobjsEDBS;
// IEnumVARIANT
	STDMETHOD(Next)(ULONG celt, VARIANT * rgvar, ULONG * pceltFetched);
	STDMETHOD(Skip)(ULONG celt);
	STDMETHOD(Clone)(IEnumVARIANT * * ppenum);
	STDMETHOD(Reset)();
};

#endif //__EDBS_OBJEKTEENUM_H_
