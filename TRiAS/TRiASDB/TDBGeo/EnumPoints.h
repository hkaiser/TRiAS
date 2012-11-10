// EnumPoints.h : Declaration of the CEnumPoints

#ifndef __ENUMPOINTS_H_
#define __ENUMPOINTS_H_

/////////////////////////////////////////////////////////////////////////////
// CEnumPoints
class ATL_NO_VTABLE CEnumPoints : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEnumPoints, &CLSID_EnumPoints>,
	public IDispatchImpl<IEnumVARIANT, &IID_IEnumVARIANT, &LIBID_TDBGEO>
{
public:
	CEnumPoints()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ENUMPOINTS)

BEGIN_COM_MAP(CEnumPoints)
	COM_INTERFACE_ENTRY(IEnumVARIANT)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IEnumVARIANT
public:
};

#endif //__ENUMPOINTS_H_
