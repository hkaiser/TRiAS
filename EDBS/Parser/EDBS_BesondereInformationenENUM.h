// EDBS_BesondereInformationenENUM.h : Deklaration von CEDBS_BesondereInformationenENUM

#ifndef __EDBS_BESONDEREINFORMATIONENENUM_H_
#define __EDBS_BESONDEREINFORMATIONENENUM_H_

#include "resource.h"       // Hauptsymbole

#include "EDBS_BesondereInformationen.h"

/////////////////////////////////////////////////////////////////////////////
// CEDBS_BesondereInformationenENUM
class ATL_NO_VTABLE CEDBS_BesondereInformationenENUM : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEDBS_BesondereInformationenENUM, &CLSID_EDBS_BesondereInformationenENUM>,
	public IDispatchImpl<IEDBS_BesondereInformationenENUM, &IID_IEDBS_BesondereInformationenENUM, &LIBID_TRiAS_EDBS>,
	public IEnumVARIANT
{
public:
	CEDBS_BesondereInformationenENUM();

DECLARE_REGISTRY_RESOURCEID(IDR_EDBS_BESONDEREINFORMATIONENENUM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEDBS_BesondereInformationenENUM)
	COM_INTERFACE_ENTRY(IEDBS_BesondereInformationenENUM)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IEnumVARIANT)
END_COM_MAP()

// IEDBS_BesondereInformationenENUM
public:
	POSITION mpos;
	CEDBS_BesondereInformationen *mpobjsBesondereInformationen;
// IEnumVARIANT
	STDMETHOD(Next)(ULONG celt, VARIANT * rgvar, ULONG * pceltFetched);
	STDMETHOD(Skip)(ULONG celt);
	STDMETHOD(Clone)(IEnumVARIANT * * ppenum);
	STDMETHOD(Reset)();
};

#endif //__EDBS_BESONDEREINFORMATIONENENUM_H_
