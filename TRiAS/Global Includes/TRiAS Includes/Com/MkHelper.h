// @doc 
// @module MkHelper.h | Helperfunktionen für Monikerbehandlung

#if !defined(_MKHELPER_H__73BA76CA_AF72_11D2_959F_006008447800__INCLUDED_)
#define _MKHELPER_H__73BA76CA_AF72_11D2_959F_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Wrapper für IMoniker::GetDisplayName
inline
HRESULT MkGetDisplayName (IMoniker *pIMk, BSTR *pbstrMkName, IBindCtx *pICtx = NULL)
{
__Interface<IBindCtx> ctx (pICtx);
LPOLESTR lpoleName = NULL;

	if (!ctx)
		RETURN_FAILED_HRESULT(::CreateBindCtx (0, ctx.ppi()));
	RETURN_FAILED_HRESULT(pIMk -> GetDisplayName (ctx, NULL, &lpoleName));

CComBSTR bstr (lpoleName);

	::CoTaskMemFree (lpoleName);
	if (!bstr)
		RETURN_HRESULT(E_OUTOFMEMORY);
	*pbstrMkName = bstr.Detach();
	return S_OK;
}

// Wrapper für mk -> BindToObject
inline 
HRESULT MkBindToObject (IMoniker *pIMk, REFIID riid, LPVOID *ppvObj, IMoniker *pmkLeft = NULL, IBindCtx *pICtx = NULL)
{
__Interface<IBindCtx> ctx (pICtx);

	if (!ctx)
		RETURN_FAILED_HRESULT(::CreateBindCtx (0, ctx.ppi()));
	return pIMk -> BindToObject (ctx, pmkLeft, riid, ppvObj);
}

template<typename T>
inline HRESULT MkBindToObject (IMoniker *pIMk, T **ppObj, IMoniker *pmkLeft = NULL, IBindCtx *pICtx = NULL)
{
	return MkBindToObject (pIMk, __uuidof(T), (void **)ppObj, pmkLeft, pICtx);
}

// Moniker des zugeordneten Containers liefern
inline
HRESULT MkGetMoniker (IUnknown *pIUnk, DWORD dwAssign, DWORD dwWhich, IMoniker **ppIMk)
{
// Versuchen, es über IOleClientSte zu machen
__Interface<IOleClientSite> Site;

	if (SUCCEEDED(pIUnk -> QueryInterface (Site.GetIID(), Site.ppv())))
		return Site -> GetMoniker (dwAssign, dwWhich, ppIMk);

// ansonsten muß es über IOleObject passieren
__Interface<IOleObject> OleObj;

	if (SUCCEEDED(pIUnk -> QueryInterface (OleObj.GetIID(), OleObj.ppv())))
		return OleObj -> GetMoniker (dwAssign, dwWhich, ppIMk);

	RETURN_HRESULT(E_NOINTERFACE);
}

///////////////////////////////////////////////////////////////////////////////
// Support für ROT (running object table)
inline
HRESULT MkRegisterAsRunning (DWORD grfFlags, IUnknown *pIUnk, IMoniker *pIMk, DWORD *pdwRegROT)
{
	if (NULL == pdwRegROT) 
		RETURN_HRESULT(E_POINTER);

__Interface<IRunningObjectTable> ROT;

	RETURN_FAILED_HRESULT(GetRunningObjectTable(0, ROT.ppi()));
// Revoke old entry, if needed
	if (0 != *pdwRegROT) {
		ROT -> Revoke (*pdwRegROT);
		*pdwRegROT = 0L;
	}

// Register as weak so clients can free us.
	RETURN_FAILED_HRESULT(ROT -> Register(grfFlags, pIUnk, pIMk, pdwRegROT));
	return S_OK;
}

inline
HRESULT MkRevokeAsRunning (DWORD *pdwRegROT)
{
	if (NULL == pdwRegROT)
		RETURN_HRESULT(E_POINTER);
	if (0L == *pdwRegROT) 
		return S_FALSE;

__Interface<IRunningObjectTable> ROT;

	RETURN_FAILED_HRESULT(GetRunningObjectTable (0, ROT.ppi()));

// Register as weak so clients can free us.
	RETURN_FAILED_HRESULT(ROT -> Revoke (*pdwRegROT));
	*pdwRegROT = 0;
	return S_OK;
}

inline
HRESULT MkNoteChangeTime (DWORD dwRegROT, FILETIME *pft)
{
	if (NULL == pft) 
		RETURN_HRESULT(E_POINTER);

__Interface<IRunningObjectTable> ROT;

	RETURN_FAILED_HRESULT(GetRunningObjectTable (0, ROT.ppi()));
	RETURN_FAILED_HRESULT(ROT -> NoteChangeTime (dwRegROT, pft));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Helper für BindContext
inline
HRESULT MkCreateAndInitBindCtx (IBindCtx **ppICtx, DWORD dwMode = STGM_READWRITE, DWORD rgFlags = 0)
{
__Interface<IBindCtx> Ctx;
BIND_OPTS bindOpts;

	ZeroMemory (&bindOpts, sizeof(BIND_OPTS));
	bindOpts.cbStruct = sizeof(BIND_OPTS);

	RETURN_FAILED_HRESULT(CreateBindCtx (0L, Ctx.ppi()));
	RETURN_FAILED_HRESULT(Ctx -> GetBindOptions (&bindOpts));
	bindOpts.grfFlags = rgFlags;
	bindOpts.grfMode = dwMode;
	RETURN_FAILED_HRESULT(Ctx -> SetBindOptions (&bindOpts));
	
	*ppICtx = Ctx.detach();
	return S_OK;
}

#endif // !defined(_MKHELPER_H__73BA76CA_AF72_11D2_959F_006008447800__INCLUDED_)
