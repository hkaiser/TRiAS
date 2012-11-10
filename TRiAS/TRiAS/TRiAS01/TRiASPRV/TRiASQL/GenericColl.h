/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: GenericColl.h $ 
 * 
 * *****************  Version 3  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 8:47p
 * Updated in $/Products/SmallParser
 * Fixing headers so all code is in CPP-files
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:24p
 * Updated in $/Products/SmallParser
*/

// GenericColl.h : Declaration of the cGenericColl

#ifndef __GENERICCOLL_H_
#define __GENERICCOLL_H_

#include "resource.h"       // main symbols

typedef CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT>, vector<CComVariant> > VecEnum;
typedef ICollectionOnSTLImpl<IGenericColl, vector<CComVariant>, VARIANT, _Copy<VARIANT>, VecEnum> IGenColl;

/////////////////////////////////////////////////////////////////////////////
// cGenericColl
class ATL_NO_VTABLE cGenericColl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cGenericColl, &CLSID_GenericColl>,
	public ISupportErrorInfo,
	public IDispatchImpl<IGenColl, &IID_IGenericColl, &LIBID_TRiASOleDB, 
		TYPELIB_TRiASOLEDB_VERSION_MAJOR, TYPELIB_TRiASOLEDB_VERSION_MINOR>
{
public:
	cGenericColl();

//	DECLARE_REGISTRY_RESOURCEID(IDR_GENERICCOLL)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cGenericColl)
		COM_INTERFACE_ENTRY(IGenericColl)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IGenericColl
public:
};

#endif //__GENERICCOLL_H_
