///////////////////////////////////////////////////////////////////////////
// RegExpr.h : Declaration of the CRegExpr

#if !defined(_REGEXPR_H__C21AAF9A_2DE5_11d1_969A_00A024D6F582__INCLUDED_)
#define _REGEXPR_H__C21AAF9A_2DE5_11d1_969A_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ospace/string/src/regex.h>	// GNU regular expression matcher
#include <ospace/string/regexp.h>
#include <ospace/std/stdexcept>
#include <atlcomx.h>

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRegExpr

class CRegExprWithRegisters
	: public os_regexp
{
public:
	re_registers *GetRegisters (void) { return registers_; }
};

class ATL_NO_VTABLE CRegExpr : 
#if defined(__ATL_20_USED__)
	public CComObjectRootEx<CComObjectThreadModel>,
	public IDispatchImpl<IParseRegularExpression, &IID_IParseRegularExpression, 
			&LIBID_TRiASSupport, TYPELIB_TRIASSUPPORT_VERSION_MAJOR, TYPELIB_TRIASSUPPORT_VERSION_MINOR>,
#else
	public CComObjectRoot,
	public CComDualImpl<IParseRegularExpression, &IID_IParseRegularExpression, 
			&LIBID_TRiASSupport>,
#endif
	public CComCoClass<CRegExpr, &CLSID_ParseRegularExpression>,
	public ISupportErrorInfo,
	public IPersistStreamInit
{
public:
	CRegExpr()
		: m_fIsDirty(false), m_fIsInitialized(false),
		  m_fIsCompiled(false), m_fIsMatched(false)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CRegExpr)
//	_ATLX_DEBUG_ADDREF_RELEASE_IMPL(CRegExpr)
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct (void) { return S_OK; }
	void FinalRelease() {}

	DECLARE_REGISTRY_RESOURCEID(IDR_REGEXPR)

	BEGIN_COM_MAP(CRegExpr)
		COM_INTERFACE_ENTRY(IParseRegularExpression)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPersist methods
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// IPersistStream methods
	STDMETHOD(IsDirty)(THIS);
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER * pcbSize);

// IPersistStreamInit methods
	STDMETHOD(InitNew)(THIS);

// IParseRegularExpression
public:
	STDMETHOD(Search)(/*[in]*/ BSTR ToSearch, /*[in, optional]*/ VARIANT *StartAt, /*[in, optional]*/ VARIANT *SearchLen, /*[out, retval]*/ BSTR *Found);
	STDMETHOD(Match)(/*[in]*/ BSTR ToMatch, /*[in, optional]*/ VARIANT StartAt, /*[in, optional]*/ VARIANT MatchLen, /*[out, retval]*/ long *Matched);
	STDMETHOD(Replace)(/*[in]*/ BSTR ToReplace, /*[in]*/ BSTR NewString, /*[in, optional]*/ VARIANT ToStart, /*[in, optional]*/ VARIANT ReplaceLen, /*[in, optional]*/ VARIANT Global, /*[out, retval]*/ BSTR *Result);

	STDMETHOD(get_Pattern)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Pattern)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Groups)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Group)(/*[in]*/ long Index, /*[out, retval]*/ BSTR *pVal);

private:
	CRegExprWithRegisters m_strRegExpr;
	os_string m_strPattern;
	os_string m_strSearch;

	bool m_fIsDirty;
	bool m_fIsInitialized;
	bool m_fIsCompiled;
	bool m_fIsMatched;
};

#endif // !defined(_REGEXPR_H__C21AAF9A_2DE5_11d1_969A_00A024D6F582__INCLUDED_)
