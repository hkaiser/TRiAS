/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: GenericStackList.h $ 
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

// GenericStackList.h : Declaration of the cGenericStackList

#ifndef __GENERICSTACKLIST_H_
#define __GENERICSTACKLIST_H_

#include "resource.h"       // main symbols
#include "GenericStack.h"       // main symbols

typedef CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT>, vector<CComVariant> > VecEnum;
typedef ICollectionOnSTLImpl<IGenericStackList, vector<CComVariant>, VARIANT, _Copy<VARIANT>, VecEnum> IGenStackColl;

/////////////////////////////////////////////////////////////////////////////
// cGenericStackList
class ATL_NO_VTABLE cGenericStackList : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cGenericStackList, &CLSID_GenericStackList>,
	public ISupportErrorInfo,
	public IDispatchImpl<IGenStackColl, &IID_IGenericStackList, &LIBID_TRiASQL>
{
public:
	cGenericStackList();

	void AddItem( cGenericStack *pIdent );

//	DECLARE_REGISTRY_RESOURCEID(IDR_GENERICSTACKLIST)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cGenericStackList)
		COM_INTERFACE_ENTRY(IGenericStackList)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IGenericStackList
public:
};

#endif //__GENERICSTACKLIST_H_
