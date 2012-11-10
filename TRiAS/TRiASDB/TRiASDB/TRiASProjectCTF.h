///////////////////////////////////////////////////////////////////////////
// @doc
// @module TRiASProjectCTF.h | Declaration of the CTRiASCTFProperty
// Objekt welches die 'CTFService'-Property eines TRiASProjektes verwaltet

#if !defined(_TRIASPROJECTCTF_H__97993C77_5FE6_11D1_B9E6_080036D63803__INCLUDED_)
#define _TRIASPROJECTCTF_H__97993C77_5FE6_11D1_B9E6_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// GUIDs sollten gecached werden
DefineEnumerator2(GUID, IID_IEnumGUID);

/////////////////////////////////////////////////////////////////////////////
// CTRiASCTFProperty

class ATL_NO_VTABLE CTRiASCTFProperty : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public ITRiASPropertyCallback, 
	public IObjectWithSite,
	public CReportErrorComCoClass<CTRiASCTFProperty, &CLSID_TRiASCTFProperty, &IID_ITRiASPropertyCallback>
{
public:
	CTRiASCTFProperty()
		: m_fIsDefault(false)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASCTFProperty)

//	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASPROJECTCTF)
	DECLARE_NO_REGISTRY()

	BEGIN_COM_MAP(CTRiASCTFProperty)
		COM_INTERFACE_ENTRY(ITRiASPropertyCallback)
		COM_INTERFACE_ENTRY(IObjectWithSite)
	END_COM_MAP()

	DECLARE_GET_CONTROLLING_UNKNOWN()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease()
	{
		TerminateCTF();
	}

// ITRiASPropertyCallback
public:
	STDMETHOD(PutValue)(/*[in]*/ BSTR Name, VARIANT newVal);
	STDMETHOD(GetValue)(/*[in]*/ BSTR Name, VARIANT *pVal);
	STDMETHOD(PutType)(/*[in]*/ BSTR Name, PROPERTY_TYPE newVal);
	STDMETHOD(GetType)(/*[in]*/ BSTR Name, PROPERTY_TYPE *pVal);
	STDMETHOD(GetValueAndType)(/*[in]*/ BSTR Name, /*[out]*/ VARIANT *pVal, /*[out]*/ PROPERTY_TYPE *pType);
	STDMETHOD(PutValueAndType)(/*[in]*/ BSTR Name, /*[in]*/ VARIANT Val, /*[in]*/ PROPERTY_TYPE Type);
	STDMETHOD(Refresh)(/*[in]*/ BSTR Name);

// IObjectWithSite
	STDMETHOD(SetSite)(IUnknown *pISite);
	STDMETHOD(GetSite)(REFIID riid, void **ppvSite);

protected:
	HRESULT InitCTF (void);
	HRESULT TerminateCTF(void);

private:
	os_string m_strCTF;
	WCoordTransform m_CTF;
	WTRiASPropertyBase m_PropBase;

// cache für Guids aus Registry
	class CEnumGuids
		: public NEnumGUID
	{
	public:
		CEnumGuids() : m_fIsInitialized(false) {}
		~CEnumGuids() {}

		HRESULT InitGuids (bool fForce = false);

	private:
		bool m_fIsInitialized;
	};
	static CEnumGuids s_GUIDs;

	bool m_fIsDefault;
};

#endif // !defined(_TRIASPROJECTCTF_H__97993C77_5FE6_11D1_B9E6_080036D63803__INCLUDED_)
	