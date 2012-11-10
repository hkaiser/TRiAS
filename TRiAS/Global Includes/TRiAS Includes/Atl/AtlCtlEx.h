// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/28/1998 10:20:23 PM
//
// @doc
// @module AtlCtlEx.h | Description goes here

#if !defined(_ATLCTLEX_H__B31D1E64_56D1_11D2_9ECF_006008447800__INCLUDED_)
#define _ATLCTLEX_H__B31D1E64_56D1_11D2_9ECF_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////////////
// Macro's
#define BEGIN_PROPERTY_MAP_RUNTIME(theClass) \
	static ATL_PROPMAP_ENTRY* GetPropertyMapR(){\
	static ATL_PROPMAP_ENTRY pPropMap[] = {

#define BEGIN_PROPERTY_MAP_DESIGN(theClass) \
	static ATL_PROPMAP_ENTRY* GetPropertyMapD(){\
	static ATL_PROPMAP_ENTRY pPropMap[] = {

//////////////////////////////////////////////////////////////////////////////
// ISpecifyPropertyPagesImpl
inline HRESULT ISpecifyPropertyPages_GetPages(CAUUID* pPages, ATL_PROPMAP_ENTRY* pMap)
{
	_ASSERTE(pMap != NULL);
	int nCnt = 0;
	// Get count of unique pages
	for(int i = 0; pMap[i].pclsidPropPage != NULL; i++)
	{
		if (!InlineIsEqualGUID(*pMap[i].pclsidPropPage, CLSID_NULL))
			nCnt++;
	}
	pPages->pElems = NULL;
	pPages->pElems = (GUID*) CoTaskMemAlloc(sizeof(CLSID)*nCnt);
	if (pPages->pElems == NULL)
		return E_OUTOFMEMORY;
	nCnt = 0;
	for(i = 0; pMap[i].pclsidPropPage != NULL; i++)
	{
		if (!InlineIsEqualGUID(*pMap[i].pclsidPropPage, CLSID_NULL))
		{
			BOOL bMatch = FALSE;
			for (int j=0;j<nCnt;j++)
			{
				if (InlineIsEqualGUID(*(pMap[i].pclsidPropPage), pPages->pElems[j]))
				{
					bMatch = TRUE;
					break;
				}
			}
			if (!bMatch)
				pPages->pElems[nCnt++] = *pMap[i].pclsidPropPage;
		}
	}
	pPages->cElems = nCnt;
	return S_OK;
}

template <class T>
class ATL_NO_VTABLE ISpecifyPropertyPagesExImpl
{
public:
// IUnknown
	STDMETHOD(QueryInterface)(REFIID riid, void ** ppvObject) = 0;
	_ATL_DEBUG_ADDREF_RELEASE_IMPL(ISpecifyPropertyPagesEx);

// ISpecifyPropertyPages
	STDMETHOD(GetPages)(CAUUID* pPages)
	{
	BOOL bUserMode = FALSE;

		static_cast<T*>(this) -> GetAmbientUserMode(bUserMode);
		return ISpecifyPropertyPages_GetPages(pPages, bUserMode ? T::GetPropertyMapR() : T::GetPropertyMapD());
	}

// dummy declarations
	HRESULT GetAmbientUserMode (BOOL &rfUserMode) {	return E_NOTIMPL; }
};

#endif // !defined(_ATLCTLEX_H__B31D1E64_56D1_11D2_9ECF_006008447800__INCLUDED_)
