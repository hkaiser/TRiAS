// ciethis.h: COM_INTERFACE_ENTRY_THIS and QueryImplementation
/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 1999, Chris Sells.
// All rights reserved. No warranties extended. Use at your own risk.
// All suggestions and bug reports to csells@sellsbrothers.com
/////////////////////////////////////////////////////////////////////////////
// Often in a COM server, we'd like to be able to ask an IUnknown* if it's
// implementation comes from a class in the server itself. dynamic_cast is
// not useful for this, because if the IUnknown* is not of the casting
// server, the behavior of dynamic_cast is undefined. However, there's
// no reason not to use QueryInterface (COM's dynamic_cast) for this purpose,
// which is what COM_INTERFACE_ENTRY_THIS and QueryImplementation are for.
/////////////////////////////////////////////////////////////////////////////
// History
// -8/29/99:
//  Inspired by Dave Stevenson [drs@rational.com] to use client-side template
//  function to make COM_INTERFACE_ENTRY_THIS compatible with _ATL_DEBUG_INTERFACES.
//
//  Changed COM_INTERFACE_ENTRY_THIS to be a bit more robust.
//
// -ATL Internals:
//  COM_INTERFACE_ENTRY_THIS didn't work with _ATL_DEBUG_INTERFACES and
//  used IID_NULL (which meant there was no way to detect a client asking
//  for an implementation class different from the one the object used).
/////////////////////////////////////////////////////////////////////////////
// Usage:
/*
// foo.h: COM component
class CFoo : public IFoo... {
...
BEGIN_COM_MAP(CFoo)
    COM_INTERFACE_ENTRY(IFoo)
    COM_INTERFACE_ENTRY_THIS()  // Expose implementation class
END_COM_MAP()
};

//  bar.h: Another COM component in the same server
void CBar::UseCFoo(IUnknown* punk) {
    CFoo*   pFoo = 0;
    HRESULT hr = QueryImplementation(punk, &pFoo);
    if( SUCCEEDED(hr) )
    {
        // Call functions on pFoo
        // Don't call Release
    }
}
*/

#pragma once
#ifndef INC_CIETHIS
#define INC_CIETHIS

inline HRESULT WINAPI _This(void* pv, REFIID clsid, void** ppv, DWORD dw)
{
    // Hand out a non-ref-counted object reference
    *ppv = pv;
    return S_OK;
}

#define COM_INTERFACE_ENTRY_THIS() { &GetObjectCLSID(), 0, _This },
#define COM_INTERFACE_ENTRY_THIS_EX(clsid) { &clsid, 0, _This },

template <typename T>
HRESULT QueryImplementation(
    IUnknown*   punk,
    REFCLSID    clsid,
    T**         ppobj)
{
    if( !ppobj ) return E_POINTER;
    *ppobj = 0;
    if( !punk ) return E_INVALIDARG;

    HRESULT hr = punk->QueryInterface(clsid, (void**)ppobj);
    if( FAILED(hr) ) return hr;

#ifdef _ATL_DEBUG_INTERFACES
    // If _ATL_DEBUG_INTERFACES, then ATL has changed the
    // pointer computed by QI to be a _QIThunk for the pointer
    _QIThunk* thunk = reinterpret_cast<_QIThunk*>(*ppobj);
    ATLASSERT(thunk);

    // The pUnk held by the thunk is the pv returned by _This.
    *ppobj = reinterpret_cast<T*>(thunk->pUnk);

    // Delete this thunk as it will never be released.
    ATLASSERT(thunk->m_dwRef == 1);
	if( !thunk->bNonAddRefThunk ) _pModule->DeleteThunk(thunk);
#endif
    
    return S_OK;
}

template <typename T>
HRESULT QueryImplementation(
    IUnknown*   punk,
    T**         ppobj)
{
    return QueryImplementation(punk, T::GetObjectCLSID(), ppobj);
}

#endif  // INC_CIETHIS
