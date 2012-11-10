// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 15.08.2002 21:30:42 
//
// @doc
// @module MonikerHelper.h | Declaration of the <c CMonikerHelper> class

#if !defined(_MONIKERHELPER_H__A0B861D5_CF55_45A5_87E1_2C12DFF7FDCC__INCLUDED_)
#define _MONIKERHELPER_H__A0B861D5_CF55_45A5_87E1_2C12DFF7FDCC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// ItemMoniker für aktuelle process erzeugen
inline 
HRESULT CreatePIDMoniker (IMoniker **ppIMk)
{
WMoniker mkPID;
wchar_t cbPID[32];

	_ultow (GetCurrentProcessId(), cbPID, 16);
	RETURN_FAILED_HRESULT(CreateItemMoniker (L"!", cbPID, ppIMk));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// _lokales_ Binden einer Objektklasse über einen gegebenen Moniker
inline
HRESULT MkBindToObjectLocal(IMoniker *pIMk, IGetGeoOperatOptions **ppIOpts)
{
WBindCtx ctx;

	RETURN_FAILED_HRESULT(CreateBindCtx (0, ctx.ppi()));

BIND_OPTS2 bndOpts;

	bndOpts.cbStruct = sizeof(BIND_OPTS2);
	RETURN_FAILED_HRESULT(ctx -> GetBindOptions(&bndOpts));
	bndOpts.dwClassContext = CLSCTX_INPROC;		// nur lokal instantiieren
	RETURN_FAILED_HRESULT(ctx -> SetBindOptions(&bndOpts));

WMoniker mkPid, mk;

	RETURN_FAILED_HRESULT(CreatePIDMoniker (mkPid.ppi()));
	RETURN_FAILED_HRESULT(mkPid -> ComposeWith(pIMk, FALSE, mk.ppi()));

#if defined(_DEBUG)
CComBSTR bstrMk;

	MkGetDisplayName(mk, &bstrMk, NULL);
#endif // defined(_DEBUG)

// zuerst nachsehen, ob die Geokomponente überhaupt existiert
//	if (S_OK == mk -> IsRunning(ctx, NULL, NULL))
		return MkBindToObject(mk, ppIOpts, NULL, ctx);
		
//	return E_UNEXPECTED;
}

#endif // !defined(_MONIKERHELPER_H__A0B861D5_CF55_45A5_87E1_2C12DFF7FDCC__INCLUDED_)
