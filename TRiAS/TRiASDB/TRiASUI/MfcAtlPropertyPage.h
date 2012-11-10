// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/29/1998 12:38:03 PM
//
// @doc
// @module MfcAtlPropertyPage.h | BasisKlasse, um MFC-PropPages als ATL-PropPage zu verwenden

#if !defined(_MFCATLPROPERTYPAGE_H__897DC464_576F_11D2_9ED0_006008447800__INCLUDED_)
#define _MFCATLPROPERTYPAGE_H__897DC464_576F_11D2_9ED0_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#pragma warning(disable:4786)

/////////////////////////////////////////////////////////////////////////////
// CMfcAtlPropertyPage
template <class TCOlePropertyPageDerived, const CLSID *pClsId, UINT uiResID>
class ATL_NO_VTABLE CMfcAtlPropertyPage : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<TCOlePropertyPageDerived, pClsId>,
	public IUnknown
{
public:
	typedef CMfcAtlPropertyPage<TCOlePropertyPageDerived, pClsId, uiResID> self_t;

	CMfcAtlPropertyPage() :
		m_pUnkPpg(NULL)
	{
	}

	DECLARE_REGISTRY_RESOURCEID(uiResID)
	DECLARE_NOT_AGGREGATABLE(self_t)

	BEGIN_COM_MAP(CMfcAtlPropertyPage)
		COM_INTERFACE_ENTRY(IUnknown)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IPropertyPage, m_pUnkPpg)
		COM_INTERFACE_ENTRY_AGGREGATE(IID_IUIContextHandle, m_pUnkPpg)
	END_COM_MAP()

public:
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{ 
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

	TCOlePropertyPageDerived *pPpg = NULL;
	
		ATLTRY(pPpg = new TCOlePropertyPageDerived);
		pPpg->EnableAutomation();
		pPpg->EnableAggregation();
		pPpg->m_pOuterUnknown = static_cast<LPUNKNOWN>(this);

	LPDISPATCH _pDispatch = pPpg->GetIDispatch(FALSE);

		m_pUnkPpg = reinterpret_cast<LPUNKNOWN>(&(pPpg->m_xInnerUnknown));
		return NOERROR;
	}
	void FinalRelease()
	{
		if (m_pUnkPpg) m_pUnkPpg->Release();
	}

private:
	LPUNKNOWN m_pUnkPpg;
};

#endif // !defined(_MFCATLPROPERTYPAGE_H__897DC464_576F_11D2_9ED0_006008447800__INCLUDED_)
