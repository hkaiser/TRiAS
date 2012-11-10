// MapLaBra.h: Definition der Klasse CMapLaBra
//
//////////////////////////////////////////////////////////////////////
#ifndef __MapLaBra_H_
#define __MapLaBra_H_

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CMapLaBra

class ATL_NO_VTABLE CMapLaBra
	: public CComObjectRootEx<CComSingleThreadModel>
	, public CComCoClass<CMapLaBra,&CLSID_MapLaBra>
	, public IConnectionPointContainerImpl<CMapLaBra>
	, public IDispatchImpl<IMapLaBra, &IID_IMapLaBra, &LIBID_MMLABRALib>
	, public ITopoMapImpl
{
public:
	CMapLaBra() {}
	~CMapLaBra() {}

	HRESULT FinalConstruct();
	void FinalRelease();

	DECLARE_REGISTRY_RESOURCEID(IDR_MAPLABRA)
	BEGIN_COM_MAP(CMapLaBra)
		COM_INTERFACE_ENTRY(IMapLaBra)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ITopoMap)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CMapLaBra)
	END_CONNECTION_POINT_MAP()

// IMapImport
public:
	STDMETHOD(GetAltFileFilter)(/*[out]*/ BSTR* pFilter);
	STDMETHOD(GetDisplayName)(/*[out]*/ BSTR* strDisplay);
	STDMETHOD(CheckAltFile)(BSTR strFileName, long* pValid);

// KK001120
	STDMETHOD(GetAltFileTyp)(/*[in,out]*/ BSTR* pTyp);
	STDMETHOD(HaveMultiMap)(/*[out]*/ long* pYesNo);
};

#endif // __MapLaBra_H_
