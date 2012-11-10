///////////////////////////////////////////////////////////////////////////
// @doc 
// @module TRiASSourceInfo.h | Declaration of the <c CTRiASSourceInfo> class

#if !defined(_TRIASSOURCEINFO_H__2C9394B5_B038_11D1_859D_00600875138A__INCLUDED_)
#define _TRIASSOURCEINFO_H__2C9394B5_B038_11D1_859D_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TRiASGMR.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTRiASSourceInfo
class ATL_NO_VTABLE CTRiASSourceInfo : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASSourceInfo, &CLSID_TRiASSourceInfo>,
	public ITRiASSourceInfo
{
public:
	CTRiASSourceInfo()
	{
		m_hPr = NULL;
		m_lIdent = 0L;
		m_dwTypes = 0L;
	}

//	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASSOURCEINFO)
	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE(CTRiASSourceInfo)

	BEGIN_COM_MAP(CTRiASSourceInfo)
		COM_INTERFACE_ENTRY(ITRiASSourceInfo)
	END_COM_MAP()

// ITRiASSourceInfo
public:
	STDMETHOD(get_Types)(/*[out, retval]*/ DWORD *pVal);
	STDMETHOD(put_Types)(/*[in]*/ DWORD newVal);
	STDMETHOD(get_Ident)(/*[out, retval]*/ LONG *pVal);
	STDMETHOD(put_Ident)(/*[in]*/ LONG newVal);
	STDMETHOD(get_CoordSystemType)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_CoordSystemType)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_TableName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_TableName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Handle)(/*[out, retval]*/ HPROJECT *pVal);
	STDMETHOD(put_Handle)(/*[in]*/ HPROJECT newVal);

private:
	CComBSTR m_bstrTableName;
	CComVariant m_CsGuid;
	HPROJECT m_hPr;
	LONG m_lIdent;
	DWORD m_dwTypes;
};

#endif // !defined(_TRIASSOURCEINFO_H__2C9394B5_B038_11D1_859D_00600875138A__INCLUDED_)
