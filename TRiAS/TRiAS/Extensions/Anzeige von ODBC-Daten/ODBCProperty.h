// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 10.12.2000 12:58:50 
//
// @doc
// @module ODBCProperty.h | Declaration of the <c CODBCProperty> class

#if !defined(_ODBCPROPERTY_H__2029AFD1_EF96_482A_827B_25CCFE82EB9D__INCLUDED_)
#define _ODBCPROPERTY_H__2029AFD1_EF96_482A_827B_25CCFE82EB9D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#include <Com/ObjectPropertyBase.h>

// D35CDA93-A35C-4CBF-B354-42834B851681
EXTERN_C const GUID __declspec(selectany) CLSID_ODBCProperty = 
	{ 0xD35CDA93, 0xA35C, 0x4CBF, 0xB3, 0x54, 0x42, 0x83, 0x4B, 0x85, 0x16, 0x81 };

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft CODBCProperty
class ATL_NO_VTABLE CODBCProperty : 
	public CComCoClass<CODBCProperty, &CLSID_ODBCProperty>,
	public IDispatchImpl<DSearchObjects, &IID_DSearchObjects, &LIBID_TRiASHelperLib>,
	public ISupportErrorInfoImpl<&IID_DSearchObjects>,
	public CObjectPropertyBase
{
public:

	CODBCProperty() : 
		CObjectPropertyBase (IDS_OP_NAME_ODBCPROPERTY, IDS_OP_DESCRIPTION_ODBCPROPERTY)
	{
		m_pFeldInfos = NULL;
	}

	DECLARE_NO_REGISTRY()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		m_lCnt = 0;
		m_lCntAll = 0;
		m_lLastObjNr = 0;
		return S_OK;
	}
	void FinalRelease()
	{
		DELETE_OBJ(m_pFeldInfos);
	}

	BEGIN_COM_MAP(CODBCProperty)
	// der erste Eintrag in dieser Map muß ein 'einfacher' sein
		COM_INTERFACE_ENTRY(IObjectProperty)
		COM_INTERFACE_ENTRY(DSearchObjects)
		COM_INTERFACE_ENTRY2(IDispatch, DSearchObjects)			// ist eigentlich überflüssig
		COM_INTERFACE_ENTRY(ISupportErrorInfo)

	// die folgenden werden hier nicht unterstützt 
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersistStreamInit)
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersistStream)
		COM_INTERFACE_ENTRY_NOINTERFACE(IPersist)

	// alles andere macht die Basisklasse
		COM_INTERFACE_ENTRY_CHAIN(CObjectPropertyBase)
	END_COM_MAP()

// IObjectProperty
public:
	STDMETHOD(Reset)(THIS);
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx);

// DSearchObjects specific functions
	STDMETHOD(ConsiderSearch)(THIS_ BSTR bstrToMatch, tagSEARCHMODE rgFlags, ULONG ulCnt);
	STDMETHOD(SearchObjects)(THIS_ BSTR bstrToMatch, tagSEARCHMODE rgFlags, IEnumObjectsByNumber **ppvObj);

// sonstiges
	void SetFieldInfo (CFeldInfos *pInfo)
	{
		m_pFeldInfos = pInfo;
	}

protected:
	HRESULT ReadParams(tagSEARCHMODE rgFlags, LPCSTR pcToMatch, CRecordset &rRecSet, ULONG &ulMerkmalsKode, CString &rstrClasses, CString &rstrKoppelFeld);

	BOOL GetSQLStmt (tagSEARCHMODE rgFlags, LPCSTR pcToMatch, CString &rstrKoppelFeld, CString &rstrFilter);
	BOOL GetSQLStmtNormal(tagSEARCHMODE rgModifier, LPCSTR pcToMatch, CString &rstrKoppelFeld, CString &rstrFilter);
	BOOL GetSQLStmtExistance(tagSEARCHMODE rgModifier, CString &rstrKoppelFeld, CString &rstrSelect);

private:
	long m_lCnt;				// akt. Feldnummer
	long m_lCntAll;				// Akkumulatorinhalt
	INT_PTR m_lLastObjNr;	
	CFeldInfos *m_pFeldInfos;
};

#endif // !defined(_ODBCPROPERTY_H__2029AFD1_EF96_482A_827B_25CCFE82EB9D__INCLUDED_)
