// MapSALayer.h: Definition der Klasse CMapSALayer
//
//////////////////////////////////////////////////////////////////////
#ifndef __MAPSALAYER_H_
#define __MAPSALAYER_H_

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CMapSALayer

class ATL_NO_VTABLE CMapSALayer
	: public CComObjectRootEx<CComSingleThreadModel>
	, public CComCoClass<CMapSALayer,&CLSID_MapSALayer>
	, public IConnectionPointContainerImpl<CMapSALayer>
	, public IDispatchImpl<IMapSALayer, &IID_IMapSALayer, &LIBID_MMSALAYERLib>
	, public ITopoMapImpl
{
public:
	CMapSALayer() {}
	~CMapSALayer() {}

	HRESULT FinalConstruct();
	void FinalRelease();

	DECLARE_REGISTRY_RESOURCEID(IDR_MAPSALAYER)

	BEGIN_COM_MAP(CMapSALayer)
		COM_INTERFACE_ENTRY(IMapSALayer)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ITopoMap)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CMapSALayer)
	END_CONNECTION_POINT_MAP()

// IMapImport
public:
	STDMETHOD(GetAltFileFilter)(/*[out]*/ BSTR* pFilter);
	STDMETHOD(GetDisplayName)(/*[out]*/ BSTR* strDisplay);
	STDMETHOD(CheckAltFile)(BSTR strFileName, long* pValid);

// KK001120
	STDMETHOD(GetAltFileTyp)(/*[out]*/ BSTR* pTyp);
	STDMETHOD(HaveMultiMap)(/*[out]*/ long* pYesNo);
};

#endif // __MAPSALAYER_H_
