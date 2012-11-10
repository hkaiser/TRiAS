// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/05/1998 11:12:07 PM
//
// @doc
// @module MfcHelper.h | HelperMacros für die MFC

#if !defined(_MFCHELPER_H__FECFEB46_5C7D_11D2_9ED7_006008447800__INCLUDED_)
#define _MFCHELPER_H__FECFEB46_5C7D_11D2_9ED7_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define IMPLEMENT_IUNKNOWN_ADDREF(ObjectClass, InterfaceClass) \
    STDMETHODIMP_(ULONG) ObjectClass::X##InterfaceClass::AddRef(void) \
    { \
        METHOD_PROLOGUE(ObjectClass, InterfaceClass); \
        return pThis->ExternalAddRef(); \
    }

#define IMPLEMENT_IUNKNOWN_RELEASE(ObjectClass, InterfaceClass) \
    STDMETHODIMP_(ULONG) ObjectClass::X##InterfaceClass::Release(void) \
    { \
        METHOD_PROLOGUE(ObjectClass, InterfaceClass); \
        return pThis->ExternalRelease(); \
    }

#define IMPLEMENT_IUNKNOWN_QUERYINTERFACE(ObjectClass, InterfaceClass) \
    STDMETHODIMP ObjectClass::X##InterfaceClass::QueryInterface(REFIID riid, LPVOID* ppVoid) \
    { \
        METHOD_PROLOGUE(ObjectClass, InterfaceClass); \
        return (HRESULT)pThis->ExternalQueryInterface(&riid, ppVoid); \
    }

#define IMPLEMENT_IUNKNOWN(ObjectClass, InterfaceClass) \
    IMPLEMENT_IUNKNOWN_ADDREF(ObjectClass, InterfaceClass) \
    IMPLEMENT_IUNKNOWN_RELEASE(ObjectClass, InterfaceClass) \
    IMPLEMENT_IUNKNOWN_QUERYINTERFACE(ObjectClass, InterfaceClass)

// define dummy IDispatch
#define FAKE_IDISPATCH_GETTYPEINFOCOUNT(ObjectClass, InterfaceClass) \
    STDMETHODIMP ObjectClass::X##InterfaceClass::GetTypeInfoCount(UINT* pctinfo) \
    { \
        return E_NOTIMPL; \
    }

#define FAKE_IDISPATCH_GETTYPEINFO(ObjectClass, InterfaceClass) \
    STDMETHODIMP ObjectClass::X##InterfaceClass::GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo** pptinfo) \
    { \
        return E_NOTIMPL; \
    }

#define FAKE_IDISPATCH_GETIDSOFNAMES(ObjectClass, InterfaceClass) \
    STDMETHODIMP ObjectClass::X##InterfaceClass::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgdispid) \
    { \
        return E_NOTIMPL; \
    }

#define FAKE_IDISPATCH_INVOKE(ObjectClass, InterfaceClass) \
    STDMETHODIMP ObjectClass::X##InterfaceClass::Invoke(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult, EXCEPINFO* pexcepinfo, UINT* puArgErr) \
    { \
        return E_NOTIMPL; \
    }

#define FAKE_IDISPATCH(ObjectClass, InterfaceClass) \
	FAKE_IDISPATCH_GETTYPEINFOCOUNT(ObjectClass, InterfaceClass) \
	FAKE_IDISPATCH_GETTYPEINFO(ObjectClass, InterfaceClass) \
	FAKE_IDISPATCH_GETIDSOFNAMES(ObjectClass, InterfaceClass) \
	FAKE_IDISPATCH_INVOKE(ObjectClass, InterfaceClass)

#endif // !defined(_MFCHELPER_H__FECFEB46_5C7D_11D2_9ED7_006008447800__INCLUDED_)
