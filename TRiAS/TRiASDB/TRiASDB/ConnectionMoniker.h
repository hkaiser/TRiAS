// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 01/13/1999 03:26:34 PM
//
// @doc
// @module ConnectionMoniker.h | Declaration of the CConnectionMoniker

#if !defined(_CONNECTIONMONIKER_H__59954E08_AACA_11D2_959C_006008447800__INCLUDED_)
#define _CONNECTIONMONIKER_H__59954E08_AACA_11D2_959C_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

#include <Com/MkBase.h>
#include <Atl/ciid.h>

/////////////////////////////////////////////////////////////////////////////
// {41DA1350-0ECF-11D3-94D6-0080C786297B}
extern "C" const IID __declspec(selectany) CLSID_ConnectionMoniker = 
	{0x41da1350,0x0ecf,0x11d3,{0x94,0xd6,0x00,0x80,0xc7,0x86,0x29,0x7b}};

/////////////////////////////////////////////////////////////////////////////
// CConnectionMoniker
class ATL_NO_VTABLE CConnectionMoniker : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CConnectionMoniker, &CLSID_ConnectionMoniker>,
	public CComMoniker<&CLSID_ConnectionMoniker>
{
public:
	CConnectionMoniker()
		: m_wcDelStr(L'!')
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CConnectionMoniker)
	DECLARE_REGISTRY_RESOURCEID(IDR_CONNECTIONMONIKER)
	DECLARE_NOT_AGGREGATABLE(CConnectionMoniker)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CConnectionMoniker)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY(IPersistStream)
		COM_INTERFACE_ENTRY(IMoniker)
		COM_INTERFACE_ENTRY(IParseDisplayName)
		COM_INTERFACE_ENTRY(IROTData)
		COM_INTERFACE_ENTRY(IMarshal)
	END_COM_MAP()

	void InitMkData (OLECHAR wcDelim, REFGUID rGuid) { m_wcDelStr = wcDelim; m_Guid = rGuid; }

// IMoniker to implement
public:
	STDMETHODIMP IsEqual(IMoniker *pmkOtherMoniker);
	STDMETHODIMP IsRunning(IBindCtx *pbc, IMoniker *pmkToLeft, IMoniker *pmkNewlyRunning);

	STDMETHODIMP BindToObject (IBindCtx *pbc, IMoniker *pmkToLeft, REFIID riidResult, void **ppvResult);
	STDMETHODIMP GetDisplayName (IBindCtx *pbc, IMoniker *pmkToLeft, LPOLESTR *ppszDisplayName);
	STDMETHODIMP ParseDisplayName (IBindCtx *pbc, IMoniker *pmkToLeft, LPOLESTR pszDisplayName, ULONG *pchEaten, IMoniker **ppmkOut);

// IPersistStream
	STDMETHODIMP Load (IStream* pstm);
	STDMETHODIMP Save (IStream *pstm, BOOL fClearDirty);

protected:
    const wchar_t *ProgID() { return L"MkConnection"; }
    const wchar_t *VersionIndependentProgID() { return ProgID(); }
	wchar_t Delimiter() { return m_wcDelStr; }

private:
	CIID m_Guid;
	OLECHAR m_wcDelStr;
};

///////////////////////////////////////////////////////////////////////////////
// Erzeugen eines ConnectionMonikers
STDAPI CreateConnectionMoniker (LPCOLESTR lpszDelim, REFGUID rGuid, IMoniker **ppIMk);

#endif // !defined(_CONNECTIONMONIKER_H__59954E08_AACA_11D2_959C_006008447800__INCLUDED_)
