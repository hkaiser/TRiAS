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

#endif // !defined(_MFCHELPER_H__FECFEB46_5C7D_11D2_9ED7_006008447800__INCLUDED_)
