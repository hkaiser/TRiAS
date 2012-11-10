#ifndef __CMAPLVERMA_H_
#define __CMAPLVERMA_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMapLVermA
class ATL_NO_VTABLE CMapLVermA
	: public CComObjectRootEx<CComSingleThreadModel>
	, public CComCoClass<CMapLVermA, &CLSID_MapLVermA>
	, public IConnectionPointContainerImpl<CMapLVermA>
	, public IDispatchImpl<IMapLVermA, &IID_IMapLVermA, &LIBID_MMFKSANHLib>
	, public ITopoMapImpl
{
public:
	CMapLVermA() {}

	HRESULT FinalConstruct();
	void FinalRelease();

	DECLARE_REGISTRY_RESOURCEID(IDR_MAPLVERMA)

	BEGIN_COM_MAP(CMapLVermA)
		COM_INTERFACE_ENTRY(IMapLVermA)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ITopoMap)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	END_COM_MAP()
	BEGIN_CONNECTION_POINT_MAP(CMapLVermA)
	END_CONNECTION_POINT_MAP()

public:
// IMapImport
	STDMETHOD(GetDisplayName)(/*[out]*/ BSTR* strDisplay);
	STDMETHOD(CheckPictureFile)(ITopoPict* pServer, long* pValid);
};

#endif //__CMAPLVERMA_H_
