// $Header: $
// Copyright© 1999 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 28.05.99 10:34:43 
//
// @doc
// @module OleClientSiteNotImpl.h | Declaration of the <c COleClientSiteNotImpl> class

#if !defined(_OLECLIENTSITENOTIMPL_H__2E3ED760_14D8_11D3_94DC_0080C786297B__INCLUDED_)
#define _OLECLIENTSITENOTIMPL_H__2E3ED760_14D8_11D3_94DC_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

/////////////////////////////////////////////////////////////////////////////
// IOleClientSite
class IOleClientSiteNotImpl :
	public IOleClientSite
{
// IOleObject
public:
	STDMETHODIMP SaveObject() 
	{
		ATLTRACENOTIMPL("IOleClientSiteNotImpl::SaveObject");
	}

	STDMETHODIMP GetMoniker (DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk)
	{
		ATLTRACENOTIMPL("IOleClientSiteNotImpl::GetMoniker");
	}

	STDMETHODIMP GetContainer (IOleContainer **ppContainer)
	{
		ATLTRACENOTIMPL("IOleClientSiteNotImpl::GetContainer");
	}

	STDMETHODIMP ShowObject()
	{
		ATLTRACENOTIMPL("IOleClientSiteNotImpl::ShowObject");
	}

	STDMETHODIMP OnShowWindow (BOOL fShow)
	{
		ATLTRACENOTIMPL("IOleClientSiteNotImpl::OnShowWindow");
	}

	STDMETHODIMP RequestNewObjectLayout()
	{
		ATLTRACENOTIMPL("IOleClientSiteNotImpl::RequestNewObjectLayout");
	}
};

#endif // !defined(_OLECLIENTSITENOTIMPL_H__2E3ED760_14D8_11D3_94DC_0080C786297B__INCLUDED_)
