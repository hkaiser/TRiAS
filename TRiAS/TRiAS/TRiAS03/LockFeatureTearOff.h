// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 15.03.2002 16:23:19 
//
// @doc
// @module LockFeatureTearOff.h | Declaration of the <c CLockFeatureTearOff> class

#if !defined(_LOCKFEATURETEAROFF_H__1A0317C2_076A_442C_8F14_1037727DD10D__INCLUDED_)
#define _LOCKFEATURETEAROFF_H__1A0317C2_076A_442C_8F14_1037727DD10D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "DispExImpl.h"

///////////////////////////////////////////////////////////////////////////////
// CLockFeatureTearOff
template <typename BaseT>
class ATL_NO_VTABLE CLockFeatureTearOff :
	public CComTearOffObjectBase<BaseT>,
	public IDispatchExImpl<BaseT, ITRiASLockFeatureEx, &IID_ITRiASLockFeatureEx, 
		&LIBID_TRiASHelperLib, TYPELIB_HELPER_VERSION_MAJOR, TYPELIB_HELPER_VERSION_MINOR>
{
public:
	CLockFeatureTearOff() {}
	~CLockFeatureTearOff() {}

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CLockFeatureTearOff)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IDispatchEx)
		COM_INTERFACE_ENTRY(ITRiASLockFeatureEx)
	END_COM_MAP()

	HRESULT FinalConstruct()
	{
		HR(m_members.PreDefineMember(CComBSTR(L"Feature"), fdexNameCaseInsensitive|fdexNameInternal, vtMissing, DISPID_LOCKEDFEATURE));
		HR(m_members.PreDefineMember(CComBSTR(L"IsRO"), fdexNameCaseInsensitive|fdexNameInternal, vtMissing, DISPID_LOCKEDISRO));
		return S_OK;
	}
	void FinalRelease()
	{
	}

	ULONG OuterRelease()
	{
	ULONG ulCnt = CComTearOffObjectBase<BaseT>::OuterRelease();

		if (1 == ulCnt)		// wird nur noch vom Owner festgehalten
			return m_pOwner->m_TearOff.Release(), 0;

		return ulCnt;
	}

// ITRiASLockFeatureEx
	STDMETHODIMP get_Feature(INT_PTR lONr, VARIANT *pVal)
	{
		return m_pOwner->get_Feature(lONr, pVal);
	}
	STDMETHODIMP put_Feature(INT_PTR lONr, VARIANT newVal)
	{
		return m_pOwner->put_Feature(lONr, newVal);
	}
	STDMETHODIMP get_Name(BSTR *pVal)
	{
		return m_pOwner->get_Name(pVal);
	}
	STDMETHODIMP get_Description(BSTR *pVal)
	{
		return m_pOwner->get_Description(pVal);
	}
	STDMETHODIMP get_IsRO(INT_PTR lONr, VARIANT_BOOL *pVal)
	{
		return m_pOwner->get_IsRO(lONr, pVal);
	}
	STDMETHODIMP get_IsLocked(INT_PTR lONr, VARIANT_BOOL *pfLocked)
	{
		return m_pOwner->get_IsLocked(lONr, pfLocked);
	}
	STDMETHODIMP UnlockFeature(INT_PTR lONr, VARIANT_BOOL fCommit)
	{
		return m_pOwner->UnlockFeature(lONr, fCommit);
	}
	STDMETHODIMP LockFeature(INT_PTR lONr)
	{
		return m_pOwner->LockFeature(lONr);
	}
};

#endif // !defined(_LOCKFEATURETEAROFF_H__1A0317C2_076A_442C_8F14_1037727DD10D__INCLUDED_)
