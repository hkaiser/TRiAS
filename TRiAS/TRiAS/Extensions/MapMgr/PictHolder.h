// PictHolder.h : Declaration of the CPictHolder

#ifndef __PICTHOLDER_H_
#define __PICTHOLDER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPictHolder
class ATL_NO_VTABLE CPictHolder :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPictHolder, &CLSID_PictHolder>,
	public IDispatchImpl<IPictHolder, &IID_IPictHolder, &LIBID_MAPMGRLib>,
	public ITopoPict
{
private:
	CPicture	*m_pPicture;
	CFile		m_fileOfPicture;

public:
	CPictHolder()
		: m_pPicture(NULL)
	{
	}
	HRESULT FinalConstruct();
	void FinalRelease();

	DECLARE_NO_REGISTRY()

	BEGIN_COM_MAP(CPictHolder)
		COM_INTERFACE_ENTRY(IPictHolder)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ITopoPict)
	END_COM_MAP()

// IPictHolder
public:
	STDMETHOD(OpenPictureFile)(/*[in]*/ BSTR strPicture);
	STDMETHOD(Close)();

// ITopoPict
	STDMETHOD(GetTagValue)(long tag, VARIANT* pValue);
	STDMETHOD(GetGeoCodedPoints)(SAFEARRAY** ppCoordinates, IUnknown **ppICS);
};

typedef	CComQIPtr<ITopoPict,&IID_ITopoPict> PICTPOINTER;

#endif //__PICTHOLDER_H_
