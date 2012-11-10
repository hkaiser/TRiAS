///////////////////////////////////////////////////////////////////////////
// @doc
// @module TRiASProperties.h | Declaration of the <c CTRiASProperties> class

#if !defined(_TRIASPROPERTIES_H__B415E6B4_6400_11D1_9728_00A024D6F582__INCLUDED_)
#define _TRIASPROPERTIES_H__B415E6B4_6400_11D1_9728_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols
#include "EnumProperty.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASProperties

class ATL_NO_VTABLE CTRiASProperties : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public ISupportErrorInfo,
	public CReportErrorComCoClass<CTRiASProperties, &CLSID_TRiASProperties, &IID_ITRiASProperties>,
	public ITRiASPropertyEvents,
	public IDispatchImpl<ITRiASProperties, &IID_ITRiASProperties, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	typedef ITRiASProperties interface_t;
	typedef ITRiASProperty controlled_t;

	CTRiASProperties()
		: m_lSemAdd(0), m_lSemDel(0), m_dwCookie(0L)
	{
	}

	_COMX_PERF_OBJECTCOUNT_IMPL(CTRiASProperties)

	DECLARE_ONE_SIZE_PRIVATE_HEAP()
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASPROPERTIES)

	BEGIN_COM_MAP(CTRiASProperties)
		COM_INTERFACE_ENTRY(ITRiASProperties)
		COM_INTERFACE_ENTRY(ITRiASPropertyEvents)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASProperties)
		COM_INTERFACE_ENTRY(ITRiASBase)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// Initialisierung/Aufräumen
	HRESULT FinalConstruct (void)
	{
		return CreateNewEnum (m_Enum.ppi());	// Enumerator anlegen
	}
	void FinalRelease (void);

	HRESULT CreateNewEnum (IEnumTRiASProperty **ppIEnum)
	{
		ATLTRY(*ppIEnum = new TEnumWTRiASProperty());	// Konstruktor hinterläßt RefCnt==1
		return (NULL == *ppIEnum) ? E_OUTOFMEMORY : S_OK;
	}
	HRESULT InitEnum (IEnumTRiASProperty *pTarget)
	{ 
		return pTarget -> Clone (m_Enum.ppi()); 
	}

	HRESULT SetPropertySupportSite (ITRiASPropertySupport *pISupport) 
	{ 
		m_Support = pISupport; 
		return S_OK;
	}

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASProperties
public:
	STDMETHOD(SetEventSink)(IUnknown *pIUnk, VARIANT_BOOL fAdvise);
	STDMETHOD(Refresh)();
	STDMETHOD(_Clone)(/*[out, retval]*/ ITRiASProperties **Props);
	STDMETHOD(Remove)(/*[in]*/ VARIANT Which);
	STDMETHOD(Add)(/*[in]*/ VARIANT Which, /*[out, retval]*/ ITRiASProperty **Property);
	STDMETHOD(_NewEnum)(/*[out, retval]*/ IUnknown **ppIEnum);
	STDMETHOD(Item)(/*[in]*/ VARIANT Which, /*[out, retval]*/ ITRiASProperty **Property);
	STDMETHOD(_Add)(/*[in]*/ ITRiASProperty *pIProp, /*[in, optional, defaultvalue(VARIANT_TRUE)]*/ VARIANT_BOOL fFullAdd);

	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Parent)(/*[out, retval]*/ IDispatch * *pVal);
	STDMETHOD(put_Parent)(/*[in]*/ IDispatch * newVal);
	STDMETHOD(get_Application)(/*[out, retval]*/ IDispatch * *pVal);
	STDMETHOD(put_Application)(/*[in]*/ IDispatch * newVal);

// ITRiASPropertyEvents
	STDMETHOD(CreatingProperty)(BSTR Name, VARIANT_BOOL *pVal);
	STDMETHOD(PropertyToCreate)(BSTR Name);
	STDMETHOD(PropertyCreated)(IDispatch *pIProp);
	STDMETHOD(ModifyingProperty)(BSTR Name, VARIANT_BOOL *pVal);
	STDMETHOD(PropertyToModify)(BSTR Name);
	STDMETHOD(PropertyModified)(BSTR Name);
	STDMETHOD(DeletingProperty)(BSTR Name, VARIANT_BOOL *pVal);
	STDMETHOD(PropertyToDelete)(BSTR Name);
	STDMETHOD(PropertyDeleted)(BSTR Name);

protected:
	WEnumWTRiASProperty m_Enum;				// eigener Enumerator
	WTRiASPropertySupport m_Support;		// zuständig für Properties

	LONG m_lSemAdd;			// Semaphore für Eventbehandlung
	LONG m_lSemDel;
	DWORD m_dwCookie;
};

///////////////////////////////////////////////////////////////////////////////
// rechts alle vorgegebenen Zeichen abschneiden
inline BSTR TrimRight (BSTR ToTrim, wchar_t c = L' ')
{
int iLen = ::SysStringLen (ToTrim);
int iLastGoodChar = -1;
wchar_t *p = ToTrim;

	for (int i = 0; i < iLen && *p != L'\0'; i++) {
		if (*p++ != c)
			iLastGoodChar = i;
	}
	if (-1 != iLastGoodChar)
		ToTrim[iLastGoodChar+1] = L'\0';		// hinten abschneiden
	return ToTrim;
}

#endif // !defined(_TRIASPROPERTIES_H__B415E6B4_6400_11D1_9728_00A024D6F582__INCLUDED_)
