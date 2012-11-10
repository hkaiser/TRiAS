/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: GenericStack.h $ 
 * 
 * *****************  Version 4  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 9:34p
 * Updated in $/Products/SmallParser
 * Added AsName property
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

// GenericStack.h : Declaration of the cGenericStack

#ifndef __GENERICSTACK_H_
#define __GENERICSTACK_H_

#include "resource.h"       // main symbols

typedef CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT>, vector<CComVariant> > VecEnum;
typedef ICollectionOnSTLImpl<IGenericStack, vector<CComVariant>, VARIANT, _Copy<VARIANT>, VecEnum> IGenStack;

/////////////////////////////////////////////////////////////////////////////
// cGenericStack
class ATL_NO_VTABLE cGenericStack : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cGenericStack, &CLSID_GenericStack>,
	public ISupportErrorInfo,
	public IDispatchImpl<IGenStack, &IID_IGenericStack, &LIBID_TRiASOleDB, 
		TYPELIB_TRiASOLEDB_VERSION_MAJOR, TYPELIB_TRiASOLEDB_VERSION_MINOR>
{
public:
	cGenericStack();
	void AddItem( CComVariant v );

	void SetAsName( const TCHAR *szName );
	CString GetAsName();
	
protected:
	CString m_strAsName;

public:
//	DECLARE_REGISTRY_RESOURCEID(IDR_GENERICSTACK)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cGenericStack)
		COM_INTERFACE_ENTRY(IGenericStack)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IGenericStack
public:
	STDMETHOD(get_AsName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(Peek)(/*[out,retval]*/ VARIANT *pvObj);
	STDMETHOD(Pop)(/*[out,retval]*/ VARIANT *pvObj);
	STDMETHOD(Push)(VARIANT vObject);
};

#endif //__GENERICSTACK_H_
