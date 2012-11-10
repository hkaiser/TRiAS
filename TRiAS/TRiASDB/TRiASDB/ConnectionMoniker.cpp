// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 01/13/1999 03:26:34 PM
//
// @doc
// @module ConnectionMoniker.cpp | Implementation of CConnectionMoniker

#include "stdafx.h"

#include <Com/MkBase.h>
#include <Com/MkBase.cpp>

#include "TriasDB.h"
#include "ConnectionMoniker.h"

#define BAD_POINTER_RETURN(p) if(!p) return E_POINTER
#define BAD_POINTER_RETURN_OR_ZERO(p) if(!p) return E_POINTER; else *p = 0
const size_t GUID_LEN = 38;

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_ConnectionMoniker, CConnectionMoniker)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(RunningObjectTable);
DefineSmartInterface(EnumMoniker);
DefineSmartInterface(Moniker);
DefineSmartInterface(ParseDisplayName);

/////////////////////////////////////////////////////////////////////////////
// CConnectionMoniker

STDMETHODIMP CConnectionMoniker::IsRunning(
	IBindCtx *pbc, IMoniker *pmkToLeft, IMoniker *pmkNewlyRunning)
{
	if (NULL != pmkToLeft)
		return E_INVALIDARG;

WRunningObjectTable rot;

	RETURN_FAILED_HRESULT(pbc -> GetRunningObjectTable (rot.ppi()));
	RETURN_FAILED_HRESULT(rot -> IsRunning (this));
	return S_OK;
}

STDMETHODIMP CConnectionMoniker::BindToObject(
	IBindCtx *pbc, IMoniker *pmkToLeft, REFIID riidResult, void **ppvResult)
{
    BAD_POINTER_RETURN_OR_ZERO(ppvResult);
    BAD_POINTER_RETURN(pbc);

	if (NULL != pmkToLeft) return E_INVALIDARG;

// zuerst festellen, ob wir in der ROT registriert sind
	if (S_OK == IsRunning (pbc, NULL, NULL)) {
	WRunningObjectTable rot;
	WEnumMoniker EnumMkRot;

		RETURN_FAILED_HRESULT(pbc -> GetRunningObjectTable (rot.ppi()));
		RETURN_FAILED_HRESULT(rot -> EnumRunning (EnumMkRot.ppi()));

	// jetzt uns selbst in der ROT wiederfinden und unser Objekt binden
	WMoniker mk, mkPid;

		RETURN_FAILED_HRESULT(CreatePIDMoniker (mkPid.ppi()));
		for (EnumMkRot -> Reset(); S_OK == EnumMkRot -> Next (1, mk.ppi(), NULL); /**/) {
		WEnumMoniker EnumMk;

			if (FAILED(mk -> Enum (TRUE, EnumMk.ppi())) || !EnumMk.IsValid())
				continue;

		WMoniker mkSub1, mkSub2, mkSub3;

			EnumMk -> Reset(); 
			if (S_OK != EnumMk -> Next (1, mkSub1.ppi(), NULL) || 
				S_OK != EnumMk -> Next (1, mkSub2.ppi(), NULL) ||
				S_OK == EnumMk -> Next (1, mkSub3.ppi(), NULL))
			{
				continue;		// not for us
			}

		// jetzt wirklich vergleichen	
			if (S_OK == mkPid -> IsEqual(mkSub1) && S_OK == IsEqual (mkSub2)) {
			// the object is running
			WUnknown Unk;
			HRESULT hr = E_FAIL;

				if (SUCCEEDED(hr = rot -> GetObject (mk, Unk.ppi())))
					hr = Unk -> QueryInterface (riidResult, ppvResult);
				return hr;
			}

		}
	}
	return E_INVALIDARG;
}

#define MKLEN ((PREFIX_LEN + 1 + GUID_LEN + 4) * sizeof(OLECHAR))

STDMETHODIMP CConnectionMoniker::GetDisplayName (
	IBindCtx *pbc, IMoniker *pmkToLeft, LPOLESTR *ppszDisplayName)
{
	BAD_POINTER_RETURN_OR_ZERO(ppszDisplayName);
	BAD_POINTER_RETURN(pbc);

// Name = "!MkConnection:<GuidPath>"
const size_t PREFIX_LEN = wcslen (ProgID());
size_t iFirst = 0;

	if (NULL != pmkToLeft) {
		RETURN_FAILED_HRESULT(pmkToLeft -> GetDisplayName (pbc, NULL, ppszDisplayName));
		iFirst = wcslen(*ppszDisplayName);

	LPOLESTR pTmp = (LPOLESTR)CoTaskMemRealloc (*ppszDisplayName, iFirst + MKLEN);

		if (NULL == pTmp) {
			CoTaskMemFree (*ppszDisplayName);
			*ppszDisplayName = NULL;
			return E_OUTOFMEMORY;
		}
		*ppszDisplayName = pTmp;
	} else
		*ppszDisplayName = (LPOLESTR)CoTaskMemAlloc(MKLEN);

	if (*ppszDisplayName) {
#if defined(_USE_CONNECTION_MK_WITHDELIMITER)
		(*ppszDisplayName)[iFirst] = m_wcDelStr;
#else
		iFirst--;
#endif // _USE_CONNECTION_MK_WITHDELIMITER
		wcscpy (*ppszDisplayName + iFirst + 1, ProgID());
		(*ppszDisplayName)[PREFIX_LEN + iFirst + 1] = ':';
		StringFromGUID2(m_Guid, *ppszDisplayName + PREFIX_LEN + iFirst + 2, GUID_LEN + 2 + 2);
		(*ppszDisplayName)[PREFIX_LEN + GUID_LEN + iFirst + 2] = 0;
		return S_OK;
	}
	return E_OUTOFMEMORY;
}

STDMETHODIMP CConnectionMoniker::ParseDisplayName(
	IBindCtx *pbc, IMoniker *pmkToLeft, LPOLESTR pszDisplayName, ULONG *pchEaten, IMoniker **ppmkOut)
{
	BAD_POINTER_RETURN_OR_ZERO(ppmkOut);
	BAD_POINTER_RETURN_OR_ZERO(pchEaten);
	BAD_POINTER_RETURN(pbc);
	BAD_POINTER_RETURN(pszDisplayName);
	BAD_POINTER_RETURN(pchEaten);

	if (NULL != pmkToLeft) return E_UNEXPECTED;

const wchar_t *pszDisplayParam = 0;

#if defined(_USE_CONNECTION_MK_WITHDELIMITER)
int iAdd = (*pszDisplayName == m_wcDelStr) ? 1 : 0;

	if (CComMonikerBase::MatchesProgID(pszDisplayName+iAdd, &pszDisplayParam)) {
#else
	if (CComMonikerBase::MatchesProgID(pszDisplayName, &pszDisplayParam)) {
#endif // _USE_CONNECTION_MK_WITHDELIMITER
	// Pull out param up to end of string
	size_t nParamLen = 0;

		while (pszDisplayParam[nParamLen] != OLECHAR('}') && pszDisplayParam[nParamLen] != 0)
			++nParamLen;
		if (pszDisplayParam[nParamLen] == OLECHAR('}'))
			++nParamLen;

	OLECHAR cbBuffer[GUID_LEN+1];
	int iLen = min(GUID_LEN, nParamLen);

		wcsncpy (cbBuffer, pszDisplayParam, iLen);
		cbBuffer[iLen] = 0;
		if (nParamLen == GUID_LEN) {
		// Check for CLSID
			USES_CONVERSION;
			m_Guid = CIID (OLE2A(cbBuffer), CIID::INITCIID_InitFromGuid);

		// Calculate cchEaten and hand out ourselves
			if (!!m_Guid) {
				*pchEaten = (pszDisplayParam - pszDisplayName) + GUID_LEN;
				if (pszDisplayName[*pchEaten] == OLESTR('}'))
					(*pchEaten)++;

				if (pszDisplayName[*pchEaten] == 0)
					(*ppmkOut = this) -> AddRef();		// Ende des DisplayNames
				else {
				// wir sind selbst verantwortlich für das weitere parsen
				WParseDisplayName pdn;
				WMoniker mk;
				ULONG ulEaten = 0L;

					RETURN_FAILED_HRESULT(BindToObject(pbc, NULL, pdn.GetIID(), pdn.ppv()));
					RETURN_FAILED_HRESULT(pbc -> RegisterObjectBound (pdn));
					RETURN_FAILED_HRESULT(pdn -> ParseDisplayName (pbc, &pszDisplayName[*pchEaten], &ulEaten, mk.ppi()));

				WMoniker mkOut;

					RETURN_FAILED_HRESULT(ComposeWith (mk, FALSE, mkOut.ppi()));

				// erfolgreich geparst
					*pchEaten += ulEaten;
					*ppmkOut = mkOut.detach();
				}
				return S_OK;
			}
		}
	}
	RETURN_FAILED_HRESULT(MK_E_SYNTAX);
	return S_OK;
}

STDMETHODIMP CConnectionMoniker::IsEqual(IMoniker *pmkOtherMoniker)
{
// Check the type of the other moniker for us
CLSID clsid;
CLSID clsidOther;
HRESULT hr = E_FAIL;

	if (SUCCEEDED(hr = GetClassID(&clsid)) && SUCCEEDED(hr = pmkOtherMoniker->GetClassID(&clsidOther)))	{
		if(clsid == clsidOther) {
		CComQIPtr<IROTData, &__uuidof(IROTData)> prd = pmkOtherMoniker;

			if (prd) {
			wchar_t rgb[2][1024];
			ULONG cbData[2];
	
				if (SUCCEEDED(hr = GetComparisonData((byte *)rgb[0], 2048, cbData + 0)) &&
					SUCCEEDED(hr = prd->GetComparisonData((byte *)rgb[1], 2048, cbData + 1)))
				{
				wchar_t *prgb1 = rgb[0];
				wchar_t *prgb2 = rgb[1];

					if (rgb[0][0] == Delimiter())
						prgb1++, cbData[0] -= sizeof(wchar_t);
					if (rgb[1][0] == Delimiter())
						prgb2++, cbData[1] -= sizeof(wchar_t);
						
					if (cbData[0] == cbData[1] && 0 == memcmp (prgb1, prgb2, cbData[0]))
						hr = S_OK;
					else
						hr = S_FALSE;
				}
			}
		} else
			hr = S_FALSE;
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Load und Save sind für die Kompatibilität der gespeicherten Infos mit
// älteren Varianten notwendig, wo der Delimiter noch nicht im ConnMk 
// gespeichert wurde
STDMETHODIMP CConnectionMoniker::Load (IStream* pstm)
{
	if (NULL == pstm) 
		return E_INVALIDARG;
	if (NULL != m_pwszDisplayName) 
		return E_UNEXPECTED;

// TODO: Support other platforms
DWORD cb;
DWORD nTag;
HRESULT hr = pstm -> Read (&nTag, sizeof(nTag), &cb);

	if (FAILED(hr)) return hr;
	if (nTag != NDR_LOCAL_DATA_REPRESENTATION) return E_UNEXPECTED;

DWORD nSize;
	
	hr = pstm -> Read (&nSize, sizeof(nSize), &cb);
	if (FAILED(hr)) return hr;

// Const-cast is required as Monikers are
// set once and then read-only.
	m_pwszDisplayName = (OLECHAR *)CoTaskMemAlloc(nSize+sizeof(OLECHAR));	// evtl. zusätzlichen Delimiter einplanen
	if (NULL == m_pwszDisplayName) return E_OUTOFMEMORY;

	hr = pstm -> Read(const_cast<OLECHAR *>(m_pwszDisplayName), nSize, &cb);
	if (FAILED(hr)) return hr;

// evtl. Delimiter vorne ran kopieren
	if (*m_pwszDisplayName != Delimiter()) {
		memmove (const_cast<OLECHAR *>(m_pwszDisplayName+1), m_pwszDisplayName, cb);
		*const_cast<OLECHAR *>(m_pwszDisplayName) = Delimiter();
	}
		
ULONG cch;
__Interface<IBindCtx> pbc;
__Interface<IMoniker> pmk;

	hr = CreateBindCtx(0, pbc.ppi());
	if (FAILED(hr)) return hr;

// const_cast<> required because ParseDisplayName() isn't const correct!
	return ParseDisplayName(pbc, 0, const_cast<OLECHAR *>(m_pwszDisplayName), &cch, pmk.ppi());
}

STDMETHODIMP CConnectionMoniker::Save (IStream *pstm, BOOL fClearDirty)
{
	if (!pstm) 
		return E_INVALIDARG;

HRESULT hr = E_UNEXPECTED;
LPOLESTR pcoleName = LPOLESTR(CComMonikerBase::GetDisplayName());

	if (NULL != pcoleName) {
		if (*pcoleName == Delimiter())
			pcoleName++;

	DWORD nSize = (wcslen(pcoleName) + 1) * sizeof(OLECHAR);
	DWORD nTag = NDR_LOCAL_DATA_REPRESENTATION;
	DWORD cb;

		if (SUCCEEDED(hr = pstm -> Write (&nTag, sizeof(nTag), &cb)) &&
			SUCCEEDED(hr = pstm -> Write (&nSize, sizeof(nSize), &cb)))
		{
			hr = pstm -> Write (pcoleName, nSize, &cb);
		}
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// API Funktion, welche einen neuen ConnectionMoniker erzeugt
STDAPI CreateConnectionMoniker (LPCOLESTR lpszDelim, REFGUID rGuid, IMoniker **ppIMk)
{
	BAD_POINTER_RETURN_OR_ZERO(ppIMk);
	BAD_POINTER_RETURN(lpszDelim);

CComObject<CConnectionMoniker> *pMk = NULL;

	RETURN_FAILED_HRESULT(CComObject<CConnectionMoniker>::CreateInstance (&pMk));
	pMk -> InitMkData (*lpszDelim, rGuid);
	(*ppIMk = pMk) -> AddRef();			// pending AddRef
	return S_OK;
}
