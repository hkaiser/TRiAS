// ErrorItem.h: Definition of the CErrorItem class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ERRORITEM_H__40B81D36_940C_11D2_98B0_0060085FC1CE__INCLUDED_)
#define AFX_ERRORITEM_H__40B81D36_940C_11D2_98B0_0060085FC1CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CErrorItem

class CErrorItem : 
	public CComDualImpl<IErrorItem, &IID_IErrorItem, &LIBID_TERRTRKLib>
	, public CComCoClass<CErrorItem,&CLSID_ErrorItem>
	, public ISupportErrorInfo
	, public CComObjectRoot
	, public IErrorInfo
	, public ICreateErrorInfo
{
	CComBSTR	m_strDescr;
	CComBSTR	m_strHelp;
	CComBSTR	m_strSource;
	GUID		m_guidOfIF;
	DWORD		m_dwContext;
public:
	CErrorItem() {}
	BEGIN_COM_MAP(CErrorItem)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IErrorItem)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IErrorInfo)
		COM_INTERFACE_ENTRY(ICreateErrorInfo)
	END_COM_MAP()
	DECLARE_NOT_AGGREGATABLE(CErrorItem) 
	DECLARE_REGISTRY_RESOURCEID(IDR_ErrorItem)
	HRESULT FinalConstruct();
	HRESULT	FinalRelease();

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
// IErrorInfo
	STDMETHOD(GetDescription)(BSTR * pbstrDescription);
	STDMETHOD(GetGUID)(GUID * pguid);
	STDMETHOD(GetHelpContext)(DWORD * pdwHelpContext);
	STDMETHOD(GetHelpFile)(BSTR * pbstrHelpFile);
	STDMETHOD(GetSource)(BSTR * pbstrSource);
// ICreateErrorInfo
	STDMETHOD(SetDescription)(BSTR szDescription); 
	STDMETHOD(SetGUID)(REFGUID rguid); 
	STDMETHOD(SetHelpContext)(DWORD dwHelpContext); 
	STDMETHOD(SetHelpFile)(BSTR szHelpFile); 
	STDMETHOD(SetSource)(BSTR szSource); 
// IErrorItem
public:
	STDMETHOD(CloneFrom)(/*[in]*/ IUnknown* pErrInfo);
	STDMETHOD(get_GUID)(BSTR* strGUID);
	STDMETHOD(get_Description)(BSTR * pbstrDescription) { return GetDescription( pbstrDescription ); }
	STDMETHOD(get_HelpContext)(DWORD * pdwHelpContext) { return GetHelpContext(pdwHelpContext); }
	STDMETHOD(get_HelpFile)(BSTR * pbstrHelpFile) { return GetHelpFile(pbstrHelpFile); }
	STDMETHOD(get_Source)(BSTR * pbstrSource) { return GetSource(pbstrSource); }
};

#endif // !defined(AFX_ERRORITEM_H__40B81D36_940C_11D2_98B0_0060085FC1CE__INCLUDED_)
