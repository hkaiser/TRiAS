// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 01/19/1999 12:20:43 PM
//
// @doc
// @module OleObjectNotImpl.h | Dummyimplementation für IOleObject

#if !defined(_OLEOBJECTNOTIMPL_H__73BA76C8_AF72_11D2_959F_006008447800__INCLUDED_)
#define _OLEOBJECTNOTIMPL_H__73BA76C8_AF72_11D2_959F_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

/////////////////////////////////////////////////////////////////////////////
// IOleObject
class IOleObjectNotImpl :
	public IOleObject
{
// IOleObject
public:
	STDMETHODIMP SetClientSite (IOleClientSite *pClientSite)
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::SetClientSite");
	}

	STDMETHODIMP GetClientSite (IOleClientSite **ppClientSite)
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::GetClientSite");
	}

	STDMETHODIMP SetHostNames (LPCOLESTR szContainerApp, LPCOLESTR szContainerObj)
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::SetHostNames");
	}

	STDMETHODIMP Close (DWORD dwSaveOption)
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::Close");
	}

	STDMETHODIMP SetMoniker (DWORD dwWhichMoniker, IMoniker *pmk)
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::SetMoniker");
	}

	STDMETHODIMP GetMoniker (DWORD dwAssign, DWORD dwWhich, IMoniker **ppIMk)
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::SetMoniker");
	}

	STDMETHODIMP InitFromData (IDataObject *pDataObject, BOOL fCreation, DWORD dwReserved)
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::InitFromData");
	}

	STDMETHODIMP GetClipboardData (DWORD dwReserved, IDataObject **ppDataObject)
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::GetClipboardData");
	}

	STDMETHODIMP DoVerb (LONG iVerb, LPMSG lpmsg, IOleClientSite *pActiveSite, LONG lindex, HWND hwndParent,  LPCRECT lprcPosRect)
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::DoVerb");
	}

	STDMETHODIMP EnumVerbs (IEnumOLEVERB **ppEnumOleVerb)
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::EnumVerbs");
	}

	STDMETHODIMP Update ()
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::Update");
	}

	STDMETHODIMP IsUpToDate ()
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::IsUpToDate");
	}

	STDMETHODIMP GetUserClassID (CLSID *pClsid)
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::GetUserClassID");
	}

	STDMETHODIMP GetUserType (DWORD dwFormOfType, LPOLESTR *pszUserType)
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::GetUserType");
	}

	STDMETHODIMP SetExtent (DWORD dwDrawAspect, SIZEL *psizel)
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::SetExtent");
	}

	STDMETHODIMP GetExtent (DWORD dwDrawAspect, SIZEL *psizel)
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::GetExtent");
	}

	STDMETHODIMP Advise (IAdviseSink *pAdvSink, DWORD *pdwConnection)
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::Advise");
	}

	STDMETHODIMP Unadvise (DWORD dwConnection)
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::Unadvise");
	}

	STDMETHODIMP EnumAdvise (IEnumSTATDATA **ppenumAdvise)
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::EnumAdvise");
	}

	STDMETHODIMP GetMiscStatus (DWORD dwAspect, DWORD *pdwStatus)
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::GetMiscStatus");
	}

	STDMETHODIMP SetColorScheme (LOGPALETTE *pLogpal)
	{
		ATLTRACENOTIMPL("IOleObjectImplNotImpl::SetColorScheme");
	}
};

#endif // !defined(_OLEOBJECTNOTIMPL_H__73BA76C8_AF72_11D2_959F_006008447800__INCLUDED_)
