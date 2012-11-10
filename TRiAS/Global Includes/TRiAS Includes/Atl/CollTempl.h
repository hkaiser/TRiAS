// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/26/1998 01:08:38 PM
//
// @doc
// @module CollTempl.h | Templates zur Implementation von Collections.

#if !defined(_COLLTEMPL_H__46745265_9CBA_11D2_9F09_006008447800__INCLUDED_)
#define _COLLTEMPL_H__46745265_9CBA_11D2_9F09_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/vector>

template<
	class iElem, 
	const GUID* libid, 
	WORD wMajor = 1, 
	WORD wMinor = 0,
	class iColl = IStaticCollection, 
	const IID* iidColl = &IID_IStaticCollection
>
class IStaticCollectionImpl :
	public IDispatchImpl<iColl, iidColl, libid, wMajor, wMinor>
{
public:	
	typedef IStaticCollectionImpl<iElem, libid, wMajor, wMinor, iColl, iidColl> this_type;
	typedef IDispatchImpl<iColl, iidColl, libid, wMajor, wMinor> base_type;

public:	
// Implementation IStaticCollection
    STDMETHOD(get_Count)(ULONG *c)
	{
		*c = m_vecVarObj.size();
		return S_OK;
	}
    STDMETHOD(_NewEnum)(IUnknown **ppUnk)
	{
		typedef CComEnum<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _Copy<VARIANT> > EnumVariant;
	
	EnumVariant *p = NULL;
	
		ATLTRY(p = new CComObject<EnumVariant>);
		if (NULL == p) return E_OUTOFMEMORY;

	HRESULT hRes = p->Init (m_vecVarObj.begin(), m_vecVarObj.end(), NULL, AtlFlagCopy);

		if (SUCCEEDED(hRes))
			hRes = p->QueryInterface(IID_IUnknown, (void **)ppUnk);
		if (FAILED(hRes))
			delete p;
		return hRes;
	}
    STDMETHOD(Refresh)(void)
	{
		return S_OK;
	}
    STDMETHOD(get_Item)(VARIANT Index, VARIANT *retval)
	{
		if (retval == NULL)
			return E_POINTER;

	CComVariant vIndex;

		if (VT_BSTR != V_VT(&Index) && SUCCEEDED(vIndex.ChangeType (VT_I4, &Index))) {
			if ((V_I4(&vIndex) < 1) || (V_I4(&vIndex) > m_vecVarObj.size()))
				return E_INVALIDARG;

		CComVariant v (m_vecVarObj[V_I4(&vIndex)-1]);

			return v.Detach (retval);
		} 
		else if (SUCCEEDED(vIndex.ChangeType (VT_BSTR, &Index))) {
			for (vecVarObj::iterator it = m_vecVarObj.begin(); it != m_vecVarObj.end(); ++it) {
			CComVariant vArg;

				if (FAILED(vArg.ChangeType (VT_BSTR, &(*it))))	// using DISPID_VALUE
					return E_INVALIDARG;

				if (!wcscmp (V_BSTR(&vIndex), V_BSTR(&vArg))) {
				CComVariant v (*it);

					return v.Detach (retval);
				}
			}
		} 
		else
			return E_INVALIDARG;

		return E_INVALIDARG;		// not found
	}

public:	// external Initialization
	template<class X>
	HRESULT InitAppend(X Data)
	{
	CComVariant varData (Data);
	
		m_vecVarObj.push_back(varData);
		return S_OK;
	}
	HRESULT InitAppend(IDispatch* pDispObj)
	{
		if (0 == pDispObj)
			return E_POINTER;

	CComVariant varDispObj (pDispObj);
	
		m_vecVarObj.push_back(varDispObj);
		return S_OK;
	}

protected:	// Attributes
	typedef vector<CComVariant> vecVarObj;
	vecVarObj m_vecVarObj;
};

///////////////////////////////////////////////////////////////////////////////
// dynamic collection
template<
	class iElem, 
	const IID* iidElem, 
	const GUID* libid, 
	WORD wMajor = 1, 
	WORD wMinor = 0,
	class iColl = IDynamicCollection, 
	const IID* iidColl = &IID_IDynamicCollection
>
class IDynamicCollectionImpl :
	public IStaticCollectionImpl<iElem, libid, wMajor, wMinor, iColl, iidColl>
{
	typedef IStaticCollectionImpl<iElem, libid, wMajor, wMinor, iColl, iidColl> base_type;
	typedef IDynamicCollectionImpl<iElem, iidElem, libid, wMajor, wMinor, iColl, iidColl> this_type;

public:	
// Implementation IDynamicCollection
    STDMETHOD(Append) (IDispatch* pDispObj)
	{
		RETURN_FAILED_HRESULT(base_type::InitAppend(pDispObj));
		return S_OK;
	}
    STDMETHOD(DeleteByIndex) (VARIANT Index)
	{
	CComVariant vIndex;

		if (VT_BSTR != V_VT(&Index) && SUCCEEDED(vIndex.ChangeType (VT_I4, &Index))) {
			if ((V_I4(&vIndex) < 1) || (V_I4(&vIndex) > m_vecVarObj.size()))
				return E_INVALIDARG;

		vecVarObj::iterator it = m_vecVarObj.begin() + (V_I4(&vIndex) -1);

//			if (0 != (*it).punkVal)
//				(*it).punkVal->Release();
			m_vecVarObj.erase(it);
		}
		else if (SUCCEEDED(vIndex.ChangeType (VT_BSTR, &Index))) {
		bool fFound = false;

			for (vecVarObj::iterator it = m_vecVarObj.begin(); it != m_vecVarObj.end(); ++it) {
			CComVariant vArg;

				if (FAILED(vArg.ChangeType (VT_BSTR, &(*it))))	// using DISPID_VALUE
					return E_INVALIDARG;

				if (!wcscmp (V_BSTR(&vIndex), V_BSTR(&vArg))) {
//					if (0 != (*it).punkVal)
//						(*it).punkVal->Release();
					m_vecVarObj.erase(it);
					fFound = true;
					break;
				}
			}
			if (!fFound)	// nicht wiedergefunden
				return S_FALSE;
		}
		else
			return E_INVALIDARG;

		return S_OK;
	}
    STDMETHOD(DeleteByObject) (IDispatch* pDispObj)
	{
		if (NULL == pDispObj)
			return E_INVALIDARG;

	__Interface<iElem> Elem;

		RETURN_FAILED_HRESULT(pDispObj->QueryInterface(*iidElem, Elem.ppv()));
		for (vecVarObj::iterator it = m_vecVarObj.begin(); it != m_vecVarObj.end(); it++)
		{
			if (Elem == __Interface<iElem>((*it).punkVal))
			{
//				(*it).punkVal->Release();
				m_vecVarObj.erase(it);
				return S_OK;
			}
		}
		return S_FALSE;		// not found
	}
	STDMETHOD(Clear)()
	{
		m_vecVarObj.clear();
		return S_OK;
	}
};

#endif // !defined(_COLLTEMPL_H__46745265_9CBA_11D2_9F09_006008447800__INCLUDED_)
