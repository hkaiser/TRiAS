// EDBS_LinienENUM.h : Deklaration von CEDBS_LinienENUM

#ifndef __EDBS_LINIENENUM_H_
#define __EDBS_LINIENENUM_H_

#include "resource.h"       // Hauptsymbole
#include "EDBS_Linien.h"

/////////////////////////////////////////////////////////////////////////////
// CEDBS_LinienENUM
class ATL_NO_VTABLE CEDBS_LinienENUM : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEDBS_LinienENUM, &CLSID_EDBS_LinienENUM>,
	public IDispatchImpl<IEDBS_LinienENUM, &IID_IEDBS_LinienENUM, &LIBID_TRiAS_EDBS>,
	public IEnumVARIANT
{
public:
	CEDBS_LinienENUM();

DECLARE_REGISTRY_RESOURCEID(IDR_EDBS_LINIENENUM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEDBS_LinienENUM)
	COM_INTERFACE_ENTRY(IEDBS_LinienENUM)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IEnumVARIANT)
END_COM_MAP()

// IEDBS_LinienENUM
public:
	POSITION mpos;
	CEDBS_Linien *mpobjsLinien;
// IEnumVARIANT
	STDMETHOD(Next)(ULONG celt, VARIANT * rgvar, ULONG * pceltFetched);
	STDMETHOD(Skip)(ULONG celt);
	STDMETHOD(Clone)(IEnumVARIANT * * ppenum);
	STDMETHOD(Reset)();
};

#endif //__EDBS_LINIENENUM_H_
