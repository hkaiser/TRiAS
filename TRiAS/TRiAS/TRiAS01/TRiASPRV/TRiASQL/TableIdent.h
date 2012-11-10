/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: TableIdent.h $ 
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:24p
 * Updated in $/Products/SmallParser
*/

// TableIdent.h : Declaration of the cTableIdent

#ifndef __TABLEIDENT_H_
#define __TABLEIDENT_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// cTableIdent
class ATL_NO_VTABLE cTableIdent : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cTableIdent, &CLSID_TableIdent>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITableIdent, &IID_ITableIdent, &LIBID_TRiASOleDB, 
		TYPELIB_TRiASOLEDB_VERSION_MAJOR, TYPELIB_TRiASOLEDB_VERSION_MINOR>
{
public:
	cTableIdent();
	~cTableIdent();

	void SetName(CString strName);
	void SetAlias(CString strAlias);

	CString m_strName;
	CString m_strAlias;


//	DECLARE_REGISTRY_RESOURCEID(IDR_TABLEIDENT)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cTableIdent)
		COM_INTERFACE_ENTRY(ITableIdent)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITableIdent
public:
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Alias)(/*[out, retval]*/ BSTR *pVal);
};

#endif //__TABLEIDENT_H_
