// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 16.03.2002 14:43:08 
//
// @doc
// @module DispExImpl.h | Declaration of the <c CDispExImpl> class

// dispeximpl.h

#pragma once
#ifndef INC_DISPEXIMPL
#define INC_DISPEXIMPL

#include "dynamemlist.h"

#ifndef HR
#define HR(_ex) { HRESULT _hr = _ex; if( FAILED(_hr) ) return _hr; }
#endif

// TODO: Figure out how to make this work with plain IDispatchEx?
// Otherwise, you have to define a new interface derived from IDispatchEx,
// even if you don't want anything desides IDispatchEx...
// TODO: Thread safety.
template <class DerivedT, class T, const IID* piid = &__uuidof(T), const GUID* plibid = &CComModule::m_libid, WORD wMajor = 1, WORD wMinor = 0, class tihclass = CComTypeInfoHolder>
class ATL_NO_VTABLE IDispatchExImpl : public T
{
public:
	typedef tihclass _tihclass;

    IDispatchExImpl() : m_bAutoExpando(true), m_bExcludedStaticDispIDs(false), m_fdexDefault(fdexNameCaseInsensitive)
    {
    }

// IDispatch
public:
    STDMETHODIMP GetTypeInfoCount(UINT* pctinfo)
    {
        if( !pctinfo ) return E_POINTER;
        *pctinfo = 1;
        return S_OK;
    }

    STDMETHODIMP GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo** pptinfo)
    {
        // Ensure typelib is loaded and static dispids are excluded
        HR(LoadTypeLib(lcid));

		return s_tih.GetTypeInfo(0, lcid, pptinfo);
    }

    STDMETHODIMP GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgdispid)
    {
        // Ensure typelib is loaded and static dispids are excluded
        HR(LoadTypeLib(lcid));

        // No support for named arguments
        if( cNames != 1 ) return DISP_E_NONAMEDARGS;

        // Forward to IDispatchEx (assuming case insensitive because they're using IDispatch)
        return this->GetDispID(CComBSTR(rgszNames[0]), m_fdexDefault, rgdispid);
    }

    STDMETHODIMP Invoke(DISPID id, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pdp, VARIANT* pvarRes, EXCEPINFO* pei, UINT* puArgErr)
    {
        // Ensure typelib is loaded and static dispids are excluded
        HR(LoadTypeLib(lcid));

        // Fake the arg number
        if( puArgErr ) *puArgErr = (UINT)-1;

        // Forward to IDispatchEx
        return this->InvokeEx(id, lcid, wFlags, pdp, pvarRes, pei, 0);
    }

// IDispatchEx
public:
    STDMETHODIMP GetDispID(BSTR bstrName, DWORD grfdex, DISPID* pid)
    {
        // Ensure typelib is loaded and static dispids are excluded
        HR(LoadTypeLib(0));

        HRESULT hr = E_FAIL;

        // Check for a static member
        hr = s_tih.GetIDsOfNames(IID_NULL, &bstrName, 1, 0, pid);
        if( hr != DISP_E_UNKNOWNNAME ) return hr;

        // Find the existing expando member
        hr = m_members.GetDispID(bstrName, grfdex, pid);

        // If we've had some result beside not finding the member, e.g.
        // success or some other failure or we didn't find the member,
        // but we're not allowed to add another one, we're done
        if( (hr != DISP_E_UNKNOWNNAME) || (!m_bAutoExpando) ) return hr;

        // Add a new expando member
        ATLASSERT(hr == DISP_E_UNKNOWNNAME && m_bAutoExpando);
        CComVariant varValue (((DerivedT *)this)->GetUnknown());	// Invoke ruft wieder über uns
        HR(m_members.AddMember(bstrName, grfdex, varValue, pid));

        return S_OK;
    }

    STDMETHODIMP InvokeEx(DISPID id, LCID lcid, WORD wFlags, DISPPARAMS* pdp, VARIANT* pvarRes,	EXCEPINFO* pei, IServiceProvider* pspCaller)
    {
        // Ensure typelib is loaded and static dispids are excluded
        HR(LoadTypeLib(lcid));

		HRESULT hr = E_FAIL;

        // Check static members
        UINT    uArgErr;
        hr = s_tih.Invoke(static_cast<T*>(this), id, IID_NULL, lcid, wFlags, pdp, pvarRes, pei, &uArgErr);
        if( hr != DISP_E_MEMBERNOTFOUND ) return hr;

        // Check expando members
        return m_members.InvokeEx(id, lcid, wFlags, pdp, pvarRes, pei, pspCaller);
    }

    STDMETHODIMP DeleteMemberByName(BSTR bstr, DWORD grfdex)
    {
        return m_members.DeleteMember(bstr, grfdex);
    }

    STDMETHODIMP DeleteMemberByDispID(DISPID id)
    {
        return m_members.DeleteMember(id);
    }

    STDMETHODIMP GetMemberProperties(DISPID id, DWORD grfdexFetch, DWORD* pgrfdex)
    {
        return m_members.GetMemberProperties(id, 0, 0, pgrfdex);
    }

    STDMETHODIMP GetMemberName(DISPID id, BSTR* pbstrName)
    {
        return m_members.GetMemberProperties(id, pbstrName, 0, 0);
    }

    STDMETHODIMP GetNextDispID(DWORD grfdex, DISPID id, DISPID* pid)
    {
        return m_members.GetNextDispID(grfdex, id, pid);
    }

    STDMETHODIMP GetNameSpaceParent(IUnknown** ppunk)
    {
        if( !ppunk ) return E_POINTER;
        *ppunk = 0;
        ATLTRACENOTIMPL(__T("IDispatchEx::GetNameSpaceParent"));
    }

protected:
    // Ensure typelib is loaded and static dispids are excluded
    HRESULT LoadTypeLib(LCID lcid)
    {
        // Already loaded
        if( m_bExcludedStaticDispIDs ) return S_OK;

        // Load TypeInfo and exclude static dispids
        CComPtr<ITypeInfo>  spInfo;
    	HR(s_tih.GetTI(lcid, &spInfo));
        HR(m_members.ExcludeDispIDs(spInfo));

        m_bExcludedStaticDispIDs = true;
        return S_OK;
    }

protected:
	static _tihclass    s_tih;
    CDynamicMemberList  m_members;
    bool                m_bAutoExpando:1;
    bool                m_bExcludedStaticDispIDs:1;
    DWORD               m_fdexDefault;
};

template <class DerivedT, class T, const IID* piid, const GUID* plibid, WORD wMajor, WORD wMinor, class tihclass>
IDispatchExImpl<DerivedT, T, piid, plibid, wMajor, wMinor, tihclass>::_tihclass
IDispatchExImpl<DerivedT, T, piid, plibid, wMajor, wMinor, tihclass>::s_tih = { piid, plibid, wMajor, wMinor, 0, 0, 0, 0 };

#endif  // INC_DISPEXIMPL
