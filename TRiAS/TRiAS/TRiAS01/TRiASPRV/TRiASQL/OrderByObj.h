/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: OrderByObj.h $ 
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

// OrderByObj.h : Declaration of the cOrderByObj

#ifndef __ORDERBYOBJ_H_
#define __ORDERBYOBJ_H_

#include "resource.h"       // main symbols
#include "ColumnIdent.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// cOrderByObj
class ATL_NO_VTABLE cOrderByObj : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cOrderByObj, &CLSID_OrderByObj>,
	public ISupportErrorInfo,
	public IDispatchImpl<IOrderByObj, &IID_IOrderByObj, &LIBID_TRiASOleDB, 
		TYPELIB_TRiASOLEDB_VERSION_MAJOR, TYPELIB_TRiASOLEDB_VERSION_MINOR>
{
public:
	cOrderByObj();
	~cOrderByObj();
	void Clear();
	void SetAsc( bool fAsc = true );

	CComObject<cColumnIdent>			*m_pColumnIdent;

protected:
	bool m_fAsc;
	
public:

//	DECLARE_REGISTRY_RESOURCEID(IDR_ORDERBYOBJ)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cOrderByObj)
		COM_INTERFACE_ENTRY(IOrderByObj)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IOrderByObj
public:
	STDMETHOD(get_ColumnIdent)(/*[out, retval]*/ IColumnIdent **pVal);
	STDMETHOD(get_Asc)(/*[out, retval]*/ VARIANT_BOOL *pVal);
};

#endif //__ORDERBYOBJ_H_
