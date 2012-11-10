// WrapperExtension.h: Definition of the CBSWrapperExtension class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WRAPPEREXTENSION_H__8E46E475_A3AC_11D0_9081_00A024D6F582__INCLUDED_)
#define AFX_WRAPPEREXTENSION_H__8E46E475_A3AC_11D0_9081_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


/////////////////////////////////////////////////////////////////////////////
// CBSWrapperExtension

EXTERN_C const GUID IID_IInitDTRiASExtension;

class CBSWrapperExtension : 
	public IInitDTRiASExtension,
	public CTriasExtension,
	public CComCoClass<CBSWrapperExtension, &CLSID_BSWrapperExtension>
{
private:
	CString m_strScriptName;
	static LONG m_lCntExts;

	HRESULT OnActiveScriptEngine();
	HRESULT GetActiveProjectIni (long hPr, os_path &path);
	WUnknown m_UnknownExt;

public:
	CBSWrapperExtension(void);
	~CBSWrapperExtension(void);

	BEGIN_COM_MAP(CBSWrapperExtension)
		COM_INTERFACE_ENTRY(ITriasXtension)
		COM_INTERFACE_ENTRY(ITriasXtension2)
		COM_INTERFACE_ENTRY(IInitDTRiASExtension)
	END_COM_MAP()

	DECLARE_REGISTRY_RESOURCEID(IDR_BSWRAPPEREXTENSION_REG)

public:
// CTriasExtension
	STDMETHOD_(HDEX, LoadExtension)		(TRIASLOADEX *pTL, HWND hWnd);
	STDMETHOD_(BOOL, InitExtension)		(short iMode);
	STDMETHOD_(BOOL, UnLoadExtension)	();
	STDMETHOD_(LRESULT, Notification)	(WPARAM wParam, LPARAM lParam);

// IInitDTRiASExtension
	STDMETHOD(InitDTRiASExtension) (IUnknown *pIUnk, long hPr);
	// bstrRegKey: Bis ..\\TRiAS\\Extensions\ProgID (Pseudo-ProgID) 
	STDMETHOD(InitDTRiASExtensionRegKey) (BSTR bstrRegKey, long hPr);
};

#endif // !defined(AFX_WRAPPEREXTENSION_H__8E46E475_A3AC_11D0_9081_00A024D6F582__INCLUDED_)
