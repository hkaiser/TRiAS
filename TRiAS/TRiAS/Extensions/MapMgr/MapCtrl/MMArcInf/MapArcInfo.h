#ifndef __MAPARCINFO_H_
#define __MAPARCINFO_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMapArcInfo
class ATL_NO_VTABLE CMapArcInfo
	: public CComObjectRootEx<CComSingleThreadModel>
	, public CComCoClass<CMapArcInfo, &CLSID_MapArcInfo>
	, public IConnectionPointContainerImpl<CMapArcInfo>
	, public IDispatchImpl<IMapArcInfo, &IID_IMapArcInfo, &LIBID_MMARCINFLib>
	, public ITopoMapImpl
{
public:
	CMapArcInfo() {}
	~CMapArcInfo() {}

	HRESULT FinalConstruct();
	void FinalRelease();

	DECLARE_REGISTRY_RESOURCEID(IDR_MAPARCINFO)

	BEGIN_COM_MAP(CMapArcInfo)
		COM_INTERFACE_ENTRY(IMapArcInfo)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ITopoMap)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CMapArcInfo)
	END_CONNECTION_POINT_MAP()
public:
// IMapArcInfo
// IMapImport
	STDMETHOD(GetAltFileFilter)(/*[out]*/ BSTR* pFilter);
	STDMETHOD(GetDisplayName)(/*[out]*/ BSTR* strDisplay);
	STDMETHOD(CheckAltFile)(BSTR strFileName, long* pValid);

// KK001120
	STDMETHOD(GetAltFileTyp)(/*[out]*/ BSTR* pTyp);
	STDMETHOD(HaveMultiMap)(/*[out]*/ long* pYesNo);

// #HK020318
	STDMETHOD(BitmapIndex)(/*[out, retval]*/ long *plIndex);
	STDMETHOD(GetDescription)(/*[out, retval]*/ BSTR *prgFlags);
};

#endif //__MAPARCINFO_H_
